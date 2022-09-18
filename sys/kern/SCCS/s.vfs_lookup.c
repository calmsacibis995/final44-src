h41799
s 00013/00026/00606
d D 8.10 95/05/27 22:14:40 mckusick 145 144
c delete read-only checking; it must be done by the filesystem layers
e
s 00004/00005/00628
d D 8.9 95/05/20 01:21:21 mckusick 144 143
c merge vfs_lock and vfs_busy; interlock mount points properly
e
s 00015/00012/00618
d D 8.8 95/05/14 00:18:17 mckusick 143 142
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK
e
s 00150/00000/00480
d D 8.7 95/04/28 17:01:11 mckusick 142 141
c move relookup in from ufs_vnops.c
e
s 00009/00009/00471
d D 8.6 94/11/21 16:57:11 mckusick 141 139
c check for symbolic links after mount points to keep AMD hard mounts happy
e
s 00010/00010/00470
d R 8.6 94/11/21 15:53:39 mckusick 140 139
c check for symbolic links after mount points to keep AMD hard mounts happy
e
s 00004/00004/00476
d D 8.5 94/05/21 14:19:04 mckusick 139 138
c check for ENOTDIR before EISDIR in null pathname case
e
s 00001/00001/00479
d D 8.4 94/02/16 23:29:12 pendry 138 137
c vref -> VREF
e
s 00005/00000/00475
d D 8.3 94/01/21 17:18:07 bostic 137 136
c add USL's copyright notice
e
s 00002/00002/00473
d D 8.2 93/09/05 09:38:56 bostic 136 135
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00473
d D 8.1 93/06/10 22:00:41 bostic 135 134
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00004/00468
d D 7.47 93/04/27 16:02:11 mckusick 134 133
c delete incorrect comment; allow NULL lookup to return parent
e
s 00001/00001/00471
d D 7.46 93/01/22 15:56:36 mckusick 133 132
c names may be up to NAME_MAX
e
s 00011/00011/00461
d D 7.45 92/10/11 10:39:04 bostic 132 131
c make kernel includes standard
e
s 00002/00001/00470
d D 7.44 92/09/21 21:16:12 hibler 131 130
c must always check for absolute root, ow a chroot'ed process
c could ".." its way past its own local root and go beyond the real root
c (i.e. crash the kernel)
e
s 00012/00000/00459
d D 7.43 92/07/20 16:02:15 pendry 130 129
c added union mounts
e
s 00005/00003/00454
d D 7.42 92/07/13 23:01:57 mckusick 129 128
c who wrote this code in such a retched style!
e
s 00012/00000/00445
d D 7.41 92/07/12 23:47:12 pendry 128 127
c allow lower layers to consume more of the pathname
e
s 00000/00005/00445
d D 7.40 92/07/03 01:38:44 mckusick 127 126
c delete USES
e
s 00005/00000/00445
d D 7.39 92/05/14 17:35:45 heideman 126 117
c vnode interface conversion
e
s 00005/00000/00445
d R 7.39 92/05/14 15:51:41 heideman 125 117
c vnode interface conversion
e
s 00005/00000/00445
d R 7.39 92/05/14 14:54:39 heideman 124 117
c vnode interface conversion
e
s 00005/00000/00445
d R 7.39 92/05/14 12:59:17 heideman 123 117
c vnode interface conversion
e
s 00005/00000/00445
d R 7.39 92/05/14 11:57:05 heideman 122 117
c vnode interface conversion
e
s 00005/00000/00445
d R 7.39 92/05/14 10:37:00 heideman 121 117
c vnode interface conversion
e
s 00005/00000/00445
d R 7.39 92/05/13 23:16:08 heideman 120 117
c vnode interface conversion
e
s 00005/00000/00445
d R 7.39 92/05/13 19:01:09 heideman 119 117
c vnode interface conversion
e
s 00005/00000/00445
d R 7.39 92/05/13 18:33:15 heideman 118 117
c vnode interface conversion
e
s 00001/00002/00444
d D 7.38 92/03/02 16:42:54 mckusick 117 116
c disallow creation of files in removed directories
e
s 00001/00002/00445
d D 7.37 92/02/21 15:41:36 mckusick 116 115
c use continue rather than goto
e
s 00047/00072/00400
d D 7.36 92/02/21 15:40:29 heideman 115 114
c lookup converted to new form
e
s 00089/00046/00383
d D 7.35 92/01/22 09:37:12 heideman 114 113
c lookup converted to new form
e
s 00006/00007/00423
d D 7.34 92/01/13 15:21:57 mckusick 113 112
c refine read-only checking for new NFS
e
s 00001/00001/00429
d D 7.33 92/01/07 16:32:08 marc 112 111
c minor optimization
e
s 00001/00008/00429
d D 7.32 91/05/21 15:00:23 mckusick 111 109
c remove the 8-bit restriction in namei
e
s 00002/00000/00437
d D 7.31.1.1 91/05/19 14:37:12 mckusick 110 109
c name resolution checking (need kern/kern_malloc.c 7.25.1.1,
c kern/vfs_lookup.c 7.31.1.1, kern/vfs_syscalls.c 7.70.1.1,
c nfs/nfs_serv.c 7.40.1.1, nfs/nfs_syscalls.c 7.26.1.1,
c ufs/ufs_vnops.c 7.64.1.1, and hp300/hp300/trap.c 7.14.1.1
e
s 00002/00005/00435
d D 7.31 91/05/19 14:18:27 mckusick 109 108
c must conditionally allocate buffer
e
s 00226/00183/00214
d D 7.30 91/05/15 20:01:39 mckusick 108 107
c break namei into namei + lookup
e
s 00002/00001/00395
d D 7.29 91/04/15 23:57:23 mckusick 107 106
c add proc pointers to appropriate VOP operations and uio setups
e
s 00000/00001/00396
d D 7.28 91/03/19 09:49:08 karels 106 105
c expunge user.h, other unneeded headers
e
s 00004/00003/00393
d D 7.27 91/03/17 15:41:44 karels 105 104
c more-or-less working with new proc & user structs
e
s 00001/00001/00395
d D 7.26 91/02/28 13:20:42 mckusick 104 103
c cache open with O_CREAT when the name already exists
e
s 00014/00006/00382
d D 7.25 91/02/21 22:53:16 mckusick 103 102
c fixes for rename in NFS
e
s 00002/00002/00386
d D 7.24 91/01/11 11:21:06 mckusick 102 101
c have to include user.h and proc.h always now
e
s 00007/00003/00381
d D 7.23 91/01/10 23:44:08 mckusick 101 100
c add dynamically allocated file descriptors
e
s 00001/00011/00383
d D 7.22 90/06/28 21:26:09 bostic 100 99
c new copyright notice
e
s 00008/00008/00386
d D 7.21 90/05/04 20:55:35 mckusick 99 98
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00062/00062/00332
d D 7.20 90/05/03 16:57:19 mckusick 98 97
c add support for NFS to avoid duplication
e
s 00001/00000/00393
d D 7.19 89/12/20 18:48:36 mckusick 97 96
c have to nullify ni_dvp on entry
e
s 00005/00003/00388
d D 7.18 89/08/10 16:27:29 mckusick 96 95
c check for lookup with ENOENT before setting EROFS for create
e
s 00006/00025/00385
d D 7.17 89/07/03 22:10:55 mckusick 95 94
c get rid of unnecessary access checks
e
s 00002/00002/00408
d D 7.16 89/07/02 23:58:15 mckusick 94 93
c must properly calculate whether at end of path
e
s 00002/00001/00408
d D 7.15 89/07/02 18:04:14 mckusick 93 92
c must return value in ni_vp when cd .. through the root
e
s 00004/00004/00405
d D 7.14 89/06/27 19:26:41 mckusick 92 91
c update reference counts on vnodes using VREF
e
s 00030/00002/00379
d D 7.13 89/06/08 13:44:37 mckusick 91 90
c must inline expand read-only and text busy checks as we do not
c also want to do the access check implied by vn_access
e
s 00006/00006/00375
d D 7.12 89/06/02 00:29:30 mckusick 90 89
c finally (I hope) get symbolic links working correctly
e
s 00001/00000/00380
d D 7.11 89/05/14 12:51:27 mckusick 89 88
c must null ni_vp on copyin error
e
s 00008/00002/00372
d D 7.10 89/05/13 11:36:57 mckusick 88 87
c must unlock parent directory on error; fix symlink interpretation
e
s 00023/00000/00351
d D 7.9 89/05/09 20:49:10 mckusick 87 86
c alternative method for copying in name
e
s 00002/00001/00349
d D 7.8 89/05/09 20:47:17 mckusick 86 85
c must do the lookup for RENAME as well as CREATE
e
s 00210/01132/00140
d D 7.7 89/05/09 16:10:26 mckusick 85 84
c merge in vnodes
e
s 00021/00001/01251
d D 7.6 89/05/01 22:56:23 marc 84 83
c KTRACE code 
e
s 00029/00025/01223
d D 7.5 89/01/12 13:20:14 mckusick 83 82
c move handling of `..' to prove concept and improve performance
e
s 00001/00001/01247
d D 7.4 87/06/21 15:30:59 mckusick 82 81
c geteblk => malloc, so m_bufp => m_fs as it should be
e
s 00015/00027/01233
d D 7.3 87/06/20 14:07:45 mckusick 81 80
c replace geteblk with malloc/free
e
s 00000/00000/01260
d D 7.2 87/04/02 15:49:28 karels 80 78
c working with pack labels
e
s 00004/00000/01260
d D 7.1.1.1 87/04/02 15:41:20 karels 79 78
c add ifdefs for dev_bsize (almost working)
e
s 00001/00001/01259
d D 7.1 86/06/05 00:13:45 mckusick 78 77
c 4.3BSD release version
e
s 00005/00012/01255
d D 6.30 86/05/04 15:09:13 mckusick 77 76
c always round down directory offset to a DIRBLK boundry
e
s 00020/00021/01247
d D 6.29 86/04/23 12:58:46 mckusick 76 75
c clean up block comment at top;
c must check both ICHG and IMOD to determine if inode has been modified!
e
s 00002/00003/01266
d D 6.28 86/02/23 23:11:27 karels 75 74
c lint
e
s 00015/00015/01254
d D 6.27 86/02/20 21:36:33 karels 74 72
c rename nch to avoid name conflict
e
s 00009/00009/01260
d R 6.27 86/02/20 17:44:54 karels 73 72
c rename nch to avoid name collision
e
s 00055/00087/01214
d D 6.26 86/02/20 15:20:25 karels 72 71
c lint and cleanups from Sam
e
s 00003/00002/01298
d D 6.25 85/09/04 20:50:23 mckusick 71 70
c initialize before use
e
s 00007/00001/01293
d D 6.24 85/06/08 14:52:52 mckusick 70 69
c Add copyright
e
s 00012/00011/01282
d D 6.23 85/05/22 19:57:12 mckusick 69 68
c return ENAMETOOLONG where appropriate; return EINVAL if 8th bit is set in name
e
s 00008/00004/01285
d D 6.22 85/04/19 12:39:30 mckusick 68 67
c cleanup and tighter semantic checking for blkatoff()
e
s 00024/00019/01265
d D 6.21 85/02/24 14:27:30 mckusick 67 65
c properly handle cacheing in the presence of `chroot';
c be more selective with docache flag; 
c avoid bcopy of found directory name
e
s 00013/00015/01269
d R 6.21 85/02/22 18:42:46 mckusick 66 65
c speedups; prevent `chdir ..' out of root when .. is in the cache
e
s 00006/00000/01278
d D 6.20 85/02/22 15:12:31 mckusick 65 64
c insure that directories are always a multiple of DIRBLKSIZ in size
e
s 00002/00000/01276
d D 6.19 85/02/20 19:30:02 mckusick 64 63
c prevent infinite loops in dirempty() with trashed directories
e
s 00020/00008/01256
d D 6.18 85/02/20 19:28:13 mckusick 63 62
c shrinking directories (from kre)
e
s 00012/00000/01252
d D 6.17 85/01/10 23:57:52 mckusick 62 61
c add cacheinvalall() to invalidate the entire namei cache 
e
s 00004/00001/01248
d D 6.16 85/01/10 19:33:50 mckusick 61 60
c fix "bread 0" panic: must check for cache ptr past end of directory after ICHG
e
s 00011/00011/01238
d D 6.15 84/08/29 20:26:26 bloom 60 59
c Change to includes.  no more ../h
e
s 00005/00002/01244
d D 6.14 84/07/27 11:30:21 mckusick 59 58
c rewrite `rename' and `rmdir' to properly invalidate the cache
e
s 00004/00002/01242
d D 6.13 84/07/08 22:35:21 mckusick 58 57
c use new interface to `copyinstr' and `copystr'
e
s 00146/00141/01098
d D 6.12 84/07/08 15:49:45 mckusick 57 56
c rework namei interface to eliminate global variables;
c use `copyinstr' and `copystr' to replace `uchar' and `schar'
e
s 00018/00007/01221
d D 6.11 84/07/07 19:19:17 mckusick 56 55
c maintain our own pool of buffers to avoid alloc/release costs
e
s 00011/00020/01217
d D 6.10 84/07/04 13:49:30 mckusick 55 53
c always use `igrab' to avoid race condition with `iput';
c use ILOCK and IUNLOCK to save call overhead
e
s 00009/00018/01219
d R 6.10 84/07/04 13:24:51 mckusick 54 53
c always use `igrab' to avoid race condition with `iput';
c use ILOCK and IUNLOCK to save call overhead
e
s 00049/00022/01188
d D 6.9 84/07/02 15:53:07 mckusick 53 52
c clean up locking protocol in namei cache; 
c no longer `irele' when clearing cache after a `umount'.
e
s 00024/00017/01186
d D 6.8 84/07/02 15:47:25 mckusick 52 51
c move most of the directory consistency checks out of main loop.
e
s 00019/00021/01184
d D 6.7 84/06/27 20:40:31 sam 51 50
c convert namei cache to hold soft references to inodes so that 
c . and .. may be placed in the cache
e
s 00002/00002/01203
d D 6.6 84/02/15 10:12:08 karels 50 49
c use ISVTX instead of ISUID for append-only directories
e
s 00002/00010/01203
d D 6.5 84/01/04 16:27:47 mckusick 49 48
c move namei statistics structure to h/nami.h so `vmstat' can access it
e
s 00330/00013/00883
d D 6.4 84/01/03 23:41:07 mckusick 48 47
c add system wide cacheing of path names in namei() (from kre)
e
s 00060/00008/00836
d D 6.3 83/12/03 18:52:36 mckusick 47 46
c 1 element cache per process saves 12% of namei cost!
e
s 00001/00001/00843
d D 6.2 83/09/09 17:02:46 mckusick 46 45
c return a more reasonable error message for /tmp/ (shannon)
e
s 00000/00000/00844
d D 6.1 83/07/29 06:43:30 sam 45 44
c 4.2 distribution
e
s 00025/00009/00819
d D 4.40 83/05/28 20:09:34 sam 44 43
c cleanup dirempty to cut down on stack space used and speed up a tad
e
s 00056/00000/00772
d D 4.39 83/05/28 19:03:04 mckusick 43 42
c add checkpath to verify validity of directory renames
e
s 00001/00001/00771
d D 4.38 83/05/18 01:59:39 sam 42 41
c typo
e
s 00031/00010/00741
d D 4.37 83/04/22 13:47:10 mckusick 41 40
c partial fix for race condition between getting and freeing an inode
e
s 00008/00008/00743
d D 4.36 83/03/21 19:54:37 sam 40 39
c avoid name conflict with freespace macro
e
s 00006/00005/00745
d D 4.35 83/02/10 13:44:17 sam 39 38
c have direnter return errors so new inodes can be thrown away
e
s 00001/00001/00749
d D 4.34 82/12/22 12:58:27 sam 38 37
c null pathname special case for rename (sigh)
e
s 00000/00001/00750
d D 4.33 82/12/21 14:59:21 sam 37 36
c error uninitialized in uiomove
e
s 00007/00004/00744
d D 4.32 82/12/21 14:39:23 sam 36 35
c make mkdir & rmdir work with rdwri (still kludged)
e
s 00003/00002/00745
d D 4.31 82/11/17 00:06:14 sam 35 34
c dropped a line in the merge (damn)
e
s 00140/00022/00607
d D 4.30 82/11/13 22:53:11 sam 34 33
c merge of 4.1b and 4.1c
e
s 00001/00001/00628
d D 4.29 82/10/31 01:05:10 root 33 32
c use ovbcopy
e
s 00003/00003/00626
d D 4.28 82/10/19 10:32:32 root 32 31
c more lint
e
s 00000/00000/00629
d D 4.27 82/10/17 23:03:41 root 31 30
c lint
e
s 00006/00014/00623
d D 4.26 82/10/17 21:51:35 root 30 29
c more lint
e
s 00003/00009/00634
d D 4.25 82/10/17 20:55:26 root 29 28
c lint
e
s 00000/00000/00643
d D 4.24 82/08/24 15:06:16 root 28 27
c new groups stuff
e
s 00013/00018/00630
d D 4.23 82/08/22 21:09:02 root 27 26
c rdwri()
e
s 00002/00005/00646
d D 4.22 82/08/14 18:54:51 root 26 25
c no more readi()
e
s 00000/00010/00651
d D 4.21 82/08/03 14:03:35 sam 25 24
c purge EFS stuff
e
s 00027/00048/00634
d D 4.20 82/07/30 10:58:15 sam 24 23
c rewrite of nami + reorganization of wdir
e
s 00530/00298/00152
d D 4.19 82/07/25 23:17:17 root 23 22
c first working version (created and removed a file!)
e
s 00002/00000/00448
d D 4.18 82/07/22 13:04:43 sam 22 21
c debugging stuff for dir records spanning block boundaries
e
s 00015/00000/00433
d D 4.17 82/07/15 20:50:13 root 21 20
c efs crud
e
s 00007/00007/00426
d D 4.16 82/06/07 23:52:38 mckusick 20 19
c irele() becomes iunlock(); new irele() does iput() for already unlocked inodes
c fixes race condition in adding entries to directories.
e
s 00217/00086/00216
d D 4.15 82/04/19 19:36:15 mckusic 19 18
c merge into new file system
e
s 00002/00001/00300
d D 4.14 82/03/31 09:08:44 wnj 18 17
c don't check access on .. when out of mounted file system
e
s 00004/00002/00297
d D 4.13 82/03/13 12:54:43 sam 17 16
c lint
e
s 00000/00002/00299
d D 4.12 82/03/12 16:25:48 sam 16 15
c lint
e
s 00015/00000/00286
d D 4.11 82/03/06 21:33:56 root 15 14
c remove some restrictions temporarily 
e
s 00013/00006/00273
d D 4.10 82/02/27 14:54:34 wnj 14 13
c symbolic links
e
s 00190/00141/00089
d D 4.9 82/02/26 16:43:04 wnj 13 12
c dmr's nami
e
s 00032/00053/00198
d D 4.8 81/11/08 16:55:52 wnj 12 11
c first listing, remove CHAOS and mpxip
e
s 00011/00008/00240
d D 4.7 81/05/18 01:57:33 wnj 11 10
c chaos change and also .. from rootdir change per jek
e
s 00010/00000/00238
d D 4.6 81/04/28 02:54:15 root 10 9
c cdevpath hack
e
s 00004/00001/00234
d D 4.5 81/03/09 01:47:44 wnj 9 8
c lint and a few minor fixed
e
s 00000/00007/00235
d D 4.4 81/03/06 11:38:24 wnj 8 7
c get rid of #ifdef CHAOS stuff
e
s 00008/00000/00234
d D 4.3 81/01/26 20:40:54 wnj 7 6
c chaos changes
e
s 00004/00000/00230
d D 4.2 80/11/09 17:36:37 bill 6 5
c fix '/'|0200 botch
e
s 00000/00000/00230
d D 4.1 80/11/09 17:32:15 bill 5 4
c minor fixups to restart stuff; version 4.1 for distrib
e
s 00001/00001/00229
d D 3.4 80/06/16 14:51:46 bill 4 3
c kurt'ies fix
e
s 00001/00001/00229
d D 3.3 80/06/07 02:46:41 bill 3 2
c %H%->%G%
e
s 00010/00009/00220
d D 3.2 80/05/18 11:42:24 bill 2 1
c back to truncation of names
e
s 00229/00000/00000
d D 3.1 80/04/09 16:03:42 bill 1 0
c date and time created 80/04/09 16:03:42 by bill
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
D 70
/*	%M%	%I%	%E%	*/
E 70
I 70
/*
D 78
 * Copyright (c) 1982 Regents of the University of California.
E 78
I 78
D 85
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 78
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 85
I 85
D 135
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 135
I 135
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 137
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 137
E 135
E 85
 *
I 85
D 100
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
E 100
I 100
 * %sccs.include.redist.c%
E 100
 *
E 85
 *	%W% (Berkeley) %G%
 */
E 70
E 9
E 3

I 19
D 23
/* merged into kernel:	@(#)nami.c 2.3 4/8/82 */

E 23
E 19
D 60
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/inode.h"
I 19
#include "../h/fs.h"
E 19
#include "../h/mount.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/buf.h"
I 7
#include "../h/conf.h"
I 27
#include "../h/uio.h"
I 34
D 57
#include "../h/nami.h"
E 57
I 47
#include "../h/kernel.h"
E 60
I 60
D 132
#include "param.h"
I 108
#include "syslimits.h"
E 108
D 85
#include "systm.h"
#include "inode.h"
#include "fs.h"
E 85
I 85
#include "time.h"
#include "namei.h"
#include "vnode.h"
E 85
#include "mount.h"
D 85
#include "dir.h"
#include "user.h"
#include "buf.h"
#include "conf.h"
#include "uio.h"
#include "kernel.h"
E 85
I 85
#include "errno.h"
E 85
I 81
#include "malloc.h"
I 101
#include "filedesc.h"
E 101
I 85
D 102

E 85
I 84
#ifdef KTRACE
E 102
I 85
D 106
#include "user.h"
E 106
E 85
#include "proc.h"
E 132
I 132
#include <sys/param.h>
#include <sys/syslimits.h>
#include <sys/time.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/errno.h>
#include <sys/malloc.h>
#include <sys/filedesc.h>
#include <sys/proc.h>
E 132
I 102

#ifdef KTRACE
E 102
D 132
#include "ktrace.h"
E 132
I 132
#include <sys/ktrace.h>
E 132
#endif
E 84
E 81
E 60
E 47
E 34
E 27
E 7

I 21
D 25
#ifdef	EFS
extern	int	efs_major;
#endif

E 25
I 23
D 24
struct	buf *batoffset();
E 24
I 24
D 85
struct	buf *blkatoff();
I 56
D 81
struct	buf *freenamebuf;
E 81
E 56
E 24
D 34
int	dirchk = 1;
E 34
I 34
D 84
int	dirchk = 0;
E 84
I 84
int	dirchk = 1;
E 84
I 48

E 85
E 48
E 34
E 23
E 21
/*
I 48
D 85
 * Structures associated with name cacheing.
 */
#define	NCHHASH		32	/* size of hash table */

#if	((NCHHASH)&((NCHHASH)-1)) != 0
#define	NHASH(h, i, d)	((unsigned)((h) + (i) + 13 * (int)(d)) % (NCHHASH))
#else
#define	NHASH(h, i, d)	((unsigned)((h) + (i) + 13 * (int)(d)) & ((NCHHASH)-1))
#endif

D 72
union	nchash	{
	union	nchash	*nch_head[2];
	struct	nch	*nch_chain[2];
E 72
I 72
union nchash {
	union	nchash *nch_head[2];
D 74
	struct	nch *nch_chain[2];
E 74
I 74
	struct	namecache *nch_chain[2];
E 74
E 72
} nchash[NCHHASH];
#define	nch_forw	nch_chain[0]
#define	nch_back	nch_chain[1]

D 49
struct	nch	*nchhead, **nchtail;		/* LRU chain pointers */

struct	nchstats {		/* stats on usefulness */
	long	ncs_goodhits;		/* hits that we can reall use */
	long	ncs_badhits;		/* hits we must drop */
	long	ncs_miss;		/* misses */
	long	ncs_long;		/* long names that ignore cache */
	long	ncs_pass2;		/* names found with passes == 2 */
	long	ncs_2passes;		/* number of times we attempt it */
} nchstats;
E 49
I 49
D 72
struct	nch	*nchhead, **nchtail;	/* LRU chain pointers */
E 72
I 72
D 74
struct	nch *nchhead, **nchtail;	/* LRU chain pointers */
E 74
I 74
struct	namecache *nchhead, **nchtail;	/* LRU chain pointers */
E 74
E 72
struct	nchstats nchstats;		/* cache effectiveness statistics */
E 49

/*
E 85
E 48
D 23
 * Convert a pathname into a pointer to
D 13
 * an inode. Note that the inode is locked.
E 13
I 13
 * a locked inode.
E 23
I 23
D 76
 * Convert a pathname into a pointer to a locked inode,
 * with side effects usable in creating and removing files.
E 76
I 76
 * Convert a pathname into a pointer to a locked inode.
E 76
D 108
 * This is a very central and rather complicated routine.
E 108
E 23
E 13
D 76
 *
D 23
 * func = function called to get next char of name
 *	&uchar if name is in user space
 *	&schar if name is in system space
 * flag = 0 if name is sought
 *	1 if name is to be created
 *	2 if name is to be deleted
I 13
 * follow = 1 if links are to be followed at the end of the name
E 23
I 23
D 57
 * The func argument gives the routine which returns successive
D 34
 * characters of the name to be translated.  The flag
 * argument is (0, 1, 2) depending on whether the name is to be
 * (looked up, created, deleted).  The follow argument is 1 when
 * symbolic links are to be followed when they occur at the end of
 * the name translation process.
E 34
I 34
 * characters of the name to be translated. 
E 57
I 57
 * The segflg defines whether the name is to be copied from user
 * space or kernel space.
E 57
E 34
 *
I 34
 * The flag argument is (LOOKUP, CREATE, DELETE) depending on whether
 * the name is to be (looked up, created, deleted).  If flag has
 * LOCKPARENT or'ed into it and the target of the pathname exists,
 * namei returns both the target and its parent directory locked. 
E 76
D 85
 * If the file system is not maintained in a strict tree hierarchy,
D 76
 * this can result in a deadlock situation.  When creating and
E 76
I 76
 * this can result in a deadlock situation (see comments in code below).
E 85
 *
D 85
 * The flag argument is LOOKUP, CREATE, or DELETE depending on whether
 * the name is to be looked up, created, or deleted. When CREATE or
 * DELETE is specified, information usable in creating or deleteing a
 * directory entry is also calculated. If flag has LOCKPARENT or'ed
 * into it and the target of the pathname exists, namei returns both
 * the target and its parent directory locked. When creating and
E 76
 * LOCKPARENT is specified, the target may not be ".".  When deleting
 * and LOCKPARENT is specified, the target may be ".", but the caller
 * must check to insure it does an irele and iput instead of two iputs.
E 85
I 85
D 108
 * The flag argument is LOOKUP, CREATE, RENAME, or DELETE depending on
 * whether the name is to be looked up, created, renamed, or deleted.
 * When CREATE, RENAME, or DELETE is specified, information usable in
 * creating, renaming, or deleting a directory entry may be calculated.
 * If flag has LOCKPARENT or'ed into it and the target of the pathname
 * exists, namei returns both the target and its parent directory locked.
 * When creating or renaming and LOCKPARENT is specified, the target may not
 * be ".".  When deleting and LOCKPARENT is specified, the target may be ".".
E 85
 *
E 108
D 57
 * The follow argument is 1 when symbolic links are to be followed
E 57
I 57
 * The FOLLOW flag is set when symbolic links are to be followed
E 57
 * when they occur at the end of the name translation process.
I 76
 * Symbolic links are always followed for all other pathname
 * components other than the last.
E 76
 *
I 76
 * The segflg defines whether the name is to be copied from user
 * space or kernel space.
 *
E 76
E 34
D 48
 * Overall outline:
E 48
I 48
D 85
 * Name caching works as follows:
E 48
 *
I 48
D 72
 *	names found by directory scans are retained in a cache
 *	for future reference.  It is managed LRU, so frequently
 *	used names will hang around.  Cache is indexed by hash value
 *	obtained from (ino,dev,name) where ino & dev refer to the
 *	directory containing name.
E 72
I 72
 * Names found by directory scans are retained in a cache
 * for future reference.  It is managed LRU, so frequently
 * used names will hang around.  Cache is indexed by hash value
 * obtained from (ino,dev,name) where ino & dev refer to the
 * directory containing name.
E 72
 *
D 72
 *	For simplicity (and economy of storage), names longer than
 *	some (small) maximum length are not cached, they occur
 *	infrequently in any case, and are almost never of interest.
E 72
I 72
 * For simplicity (and economy of storage), names longer than
D 76
 * some (small) maximum length are not cached, they occur
E 76
I 76
 * a maximum length of NCHNAMLEN are not cached; they occur
E 76
 * infrequently in any case, and are almost never of interest.
E 72
 *
D 72
 *	Upon reaching the last segment of a path, if the reference
 *	is for DELETE, or NOCACHE is set (rewrite), and the
 *	name is located in the cache, it will be dropped.
E 72
I 72
 * Upon reaching the last segment of a path, if the reference
 * is for DELETE, or NOCACHE is set (rewrite), and the
 * name is located in the cache, it will be dropped.
E 72
 *
E 85
D 72
 *	We must be sure never to enter the name ".." into the cache
 *	because of the extremely kludgey way that rename() alters
 *	".." in a situation like
 *		mv a/x b/x
 *	where x is a directory, and x/.. is the ".." in question.
E 72
I 72
D 76
 * We must be sure never to enter the name ".." into the cache
 * because of the extremely kludgey way that rename() alters
 * ".." in a situation like
 * 	mv a/x b/x
 * where x is a directory, and x/.. is the ".." in question.
E 72
 *
E 76
 * Overall outline of namei:
 *
E 48
 *	copy in name
 *	get starting directory
D 108
 * dirloop:
D 85
 *	check accessibility of directory
 * dirloop2:
E 85
D 57
 *	copy next component of name to u.u_dent
E 57
I 57
 *	copy next component of name to ndp->ni_dent
E 57
 *	handle degenerate case where name is null string
I 48
D 85
 *	look for name in cache, if found, then if at end of path
 *	  and deleting or creating, drop it, else to haveino
E 48
 *	search for name in directory, to found or notfound
 * notfound:
D 34
 *	if creating, return locked inode, leaving information on avail. slots
E 34
I 34
 *	if creating, return locked directory, leaving info on avail. slots
E 34
 *	else return error
 * found:
 *	if at end of path and deleting, return information to allow delete
I 34
D 48
 *	if at end of path and rewriting (create and LOCKPARENT), lock targe
E 48
I 48
D 76
 *	if at end of path and rewriting (create and LOCKPARENT), lock target
E 76
I 76
 *	if at end of path and rewriting (CREATE and LOCKPARENT), lock target
E 76
E 48
 *	  inode and return info to allow rewrite
E 34
 *	if .. and on mounted filesys, look in mount table for parent
I 48
D 76
 *	if not at end, if neither creating nor deleting, add name to cache
E 76
I 76
 *	if not at end, add name to cache; if at end and neither creating
 *	  nor deleting, add name to cache
E 76
 * haveino:
E 85
I 85
 *	if .. and on mounted filesys, find parent
 *	call lookup routine for next component name
 *	  directory vnode returned in ni_dvp, unlocked unless LOCKPARENT set
 *	  component vnode returned in ni_vp (if it exists), locked.
E 85
E 48
 *	if symbolic link, massage name in buffer and continue at dirloop
I 85
 *	if result inode is mounted on, find mounted on vnode
E 85
 *	if more components of name, do next level at dirloop
D 85
 *	return the answer as locked inode
E 85
I 85
 *	return the answer in ni_vp as locked vnode;
 *	  if LOCKPARENT set, return locked parent in ni_dvp
E 85
I 34
 *
D 85
 * NOTE: (LOOKUP | LOCKPARENT) currently returns the parent inode,
 *	 but unlocked.
E 85
I 85
 * NOTE: (LOOKUP | LOCKPARENT) currently returns the parent vnode unlocked.
E 108
I 108
 *	while (!done && !error) {
 *		call lookup to search path.
 *		if symbolic link, massage name in buffer and continue
 *	}
E 108
E 85
E 34
E 23
E 13
 */
D 85
struct inode *
E 85
D 13
namei(func, flag)
D 12
int (*func)();
E 12
I 12
	int (*func)();
E 13
I 13
D 57
namei(func, flag, follow)
	int (*func)(), flag, follow;
E 57
I 57
D 105
namei(ndp)
E 105
I 105
D 115
namei(ndp, p)
E 115
I 115
int
namei(ndp)
E 115
E 105
	register struct nameidata *ndp;
I 105
D 115
	struct proc *p;
E 115
E 105
E 57
E 13
E 12
{
I 126
D 127
	USES_VOP_READLINK;
	USES_VOP_UNLOCK;
E 127
E 126
I 101
D 105
	struct proc *p = u.u_procp;		/* XXX */
E 105
	register struct filedesc *fdp;	/* pointer to file descriptor state */
E 101
D 23
	register struct inode *dp;
D 13
	register c;
E 13
	register char *cp;
D 13
	struct buf *bp;
E 13
I 13
	register struct buf *bp, *nbp;
E 13
I 2
	register struct direct *ep;
I 19
	register struct fs *fs;
E 19
I 14
	struct inode *pdp;
E 14
E 2
D 13
	int i;
E 13
I 13
D 19
	int i, nlink;
E 19
I 19
	enum {NONE, COMPACT, FOUND} slot;
	int entryfree, entrysize;
	int spccnt, size, newsize;
	int loc, prevoff, curoff;
	int i, nlink, bsize;
	unsigned pathlen;
	daddr_t lbn, bn;
E 19
E 13
	dev_t d;
E 23
I 23
	register char *cp;		/* pointer into pathname argument */
D 85
/* these variables refer to things which must be freed or unlocked */
	register struct inode *dp = 0;	/* the directory we are searching */
I 48
D 74
	register struct nch *ncp;	/* cache slot for entry */
E 74
I 74
	register struct namecache *ncp;	/* cache slot for entry */
E 74
E 48
	register struct fs *fs;		/* file system that directory is in */
	register struct buf *bp = 0;	/* a buffer of directory entries */
	register struct direct *ep;	/* the current directory entry */
	int entryoffsetinblock;		/* offset of ep in bp's buffer */
D 81
	register struct buf *nbp;	/* buffer storing path name argument */
E 81
I 81
	register caddr_t nbp;		/* buffer storing path name argument */
E 81
/* these variables hold information about the search for a slot */
	enum {NONE, COMPACT, FOUND} slotstatus;
	int slotoffset = -1;		/* offset of area with free space */
	int slotsize;			/* size of area at slotoffset */
	int slotfreespace;		/* amount of space free in slot */
	int slotneeded;			/* size of the entry we're seeking */
/* */
D 47
	int dirsize;
E 47
I 47
	int numdirpasses;		/* strategy for directory search */
	int endsearch;			/* offset to end directory search */
E 47
D 57
	int prevoff;			/* u.u_offset of previous entry */
E 57
I 57
	int prevoff;			/* ndp->ni_offset of previous entry */
E 57
	int nlink = 0;			/* number of symbolic links taken */
	struct inode *pdp;		/* saved dp during symlink work */
D 57
	int i;
E 57
I 57
	int error, i;
E 57
I 34
	int lockparent;
E 85
I 85
D 108
	register struct vnode *dp = 0;	/* the directory we are searching */
	register int i;		   	/* Temp counter */
	struct vnode *tdp;		/* saved dp */
	struct mount *mp;		/* mount table entry */
E 85
I 48
D 67
	int docache;
E 67
I 67
	int docache;			/* == 0 do not cache last component */
D 85
	int makeentry;			/* != 0 if name to be added to cache */
E 67
	unsigned hash;			/* value of name hash for entry */
	union nchash *nhp;		/* cache chain head for entry */
	int isdotdot;			/* != 0 if current name is ".." */
I 57
	int flag;			/* op ie, LOOKUP, CREATE, or DELETE */
I 63
	off_t enduseful;		/* pointer past last used dir slot */
E 85
I 85
	int flag;			/* LOOKUP, CREATE, RENAME or DELETE */
	int wantparent;			/* 1 => wantparent or lockparent flag */
I 88
	int lockparent;			/* 1 => lockparent flag */
I 98
	int getbuf;			/* 1 => Malloc a pathname buffer */
	int rdonly;			/* mounted read-only flag bit(s) */
E 98
E 88
	int error = 0;
E 108
I 108
	register struct vnode *dp;	/* the directory we are searching */
	struct iovec aiov;		/* uio for reading symbolic links */
	struct uio auio;
	int error, linklen;
I 115
	struct componentname *cnp = &ndp->ni_cnd;
I 143
	struct proc *p = cnp->cn_proc;
E 143
E 115
E 108
E 85
E 63
E 57
E 48
E 34
E 23
I 13
D 16
	ino_t ino;
E 16
E 13
D 19
	off_t eo;
E 19
I 10
D 11
#ifdef CHAOS
	extern long cdevpath;
#endif
E 11
E 10

I 98
D 108
	/*
	 * Setup: break out flag bits into variables.
	 */
E 108
I 105
D 115
	ndp->ni_cred = p->p_ucred;
E 105
I 101
	fdp = p->p_fd;
E 115
I 115
	ndp->ni_cnd.cn_cred = ndp->ni_cnd.cn_proc->p_ucred;
#ifdef DIAGNOSTIC
	if (!cnp->cn_cred || !cnp->cn_proc)
		panic ("namei: bad cred/proc");
	if (cnp->cn_nameiop & (~OPMASK))
		panic ("namei: nameiop contaminated with flags");
	if (cnp->cn_flags & OPMASK)
		panic ("namei: flags contaminated with nameiops");
#endif
	fdp = cnp->cn_proc->p_fd;
E 115
E 101
E 98
I 97
D 108
	ndp->ni_dvp = NULL;
E 97
I 34
D 57
	lockparent = flag & LOCKPARENT;
D 48
	flag &= ~LOCKPARENT;
E 48
I 48
	docache = (flag & NOCACHE) ^ NOCACHE;
	flag &= ~(LOCKPARENT|NOCACHE);
E 57
I 57
D 85
	lockparent = ndp->ni_nameiop & LOCKPARENT;
E 85
I 85
D 103
	flag = ndp->ni_nameiop & OPFLAG;
E 103
I 103
	flag = ndp->ni_nameiop & OPMASK;
E 103
	wantparent = ndp->ni_nameiop & (LOCKPARENT|WANTPARENT);
I 88
	lockparent = ndp->ni_nameiop & LOCKPARENT;
E 88
E 85
	docache = (ndp->ni_nameiop & NOCACHE) ^ NOCACHE;
I 98
	getbuf = (ndp->ni_nameiop & HASBUF) ^ HASBUF;
E 98
D 85
	flag = ndp->ni_nameiop &~ (LOCKPARENT|NOCACHE|FOLLOW);
E 57
D 67
	if (flag == DELETE)
E 67
I 67
	if (flag == DELETE || lockparent)
E 85
I 85
D 104
	if (flag == DELETE || wantparent)
E 104
I 104
	if (flag == DELETE || (wantparent && flag != CREATE))
E 104
E 85
E 67
		docache = 0;
I 98
D 99
	rdonly = M_RDONLY;
E 99
I 99
	rdonly = MNT_RDONLY;
E 99
	if (ndp->ni_nameiop & REMOTE)
D 99
		rdonly |= M_EXRDONLY;
E 99
I 99
		rdonly |= MNT_EXRDONLY;
E 108
I 108

E 108
E 99
E 98
E 48
E 34
	/*
I 13
D 23
	 * allocate name buffer; copy name
E 23
I 23
	 * Get a buffer for the name to be translated, and copy the
	 * name into the buffer.
E 23
	 */
D 19
	nbp = geteblk();
E 19
I 19
D 56
	nbp = geteblk(MAXPATHLEN);
E 56
I 56
D 81
	nbp = freenamebuf;
	if (nbp == NULL)
		nbp = geteblk(MAXPATHLEN);
	else
		freenamebuf = nbp->av_forw;
E 81
I 81
D 85
	MALLOC(nbp, caddr_t, MAXPATHLEN, M_NAMEI, M_WAITOK);
E 85
I 85
D 98
	MALLOC(ndp->ni_pnbuf, caddr_t, MAXPATHLEN, M_NAMEI, M_WAITOK);
E 85
E 81
E 56
E 19
D 23
	nlink = 0;
D 19
	for (i=0, cp = nbp->b_un.b_addr; *cp = (*func)(); i++) {
I 15
		if ((*cp&0377) == ('/'|0200)) {
E 19
I 19
	for (i = 0, cp = nbp->b_un.b_addr; *cp = (*func)(); i++) {
		if ((*cp & 0377) == ('/'|0200)) {
E 23
I 23
D 57
	for (cp = nbp->b_un.b_addr; *cp = (*func)(); ) {
D 48
		if ((*cp&0377) == ('/'|0200) || (*cp&0200) && flag != 2) {
E 48
I 48
D 51
		if ((*cp&0377) == ('/'|0200) || (*cp&0200) && flag != LOOKUP) {
E 51
I 51
		if ((*cp&0377) == ('/'|0200) || (*cp&0200) && flag != DELETE) {
E 51
E 48
E 23
E 19
			u.u_error = EPERM;
D 23
			break;
E 23
I 23
			goto bad;
E 23
		}
D 23
#ifdef notdef
E 15
D 19
		if (*cp++&0200 && flag==1 || cp >= nbp->b_un.b_addr+BSIZE) {
E 19
I 19
		if (*cp++ & 0200 && flag == 1 ||
		    cp >= nbp->b_un.b_addr + MAXPATHLEN) {
E 19
I 15
#else
E 23
		cp++;
D 19
		if (cp >= nbp->b_un.b_addr+BSIZE) {
E 19
I 19
		if (cp >= nbp->b_un.b_addr + MAXPATHLEN) {
E 19
D 23
#endif
E 23
E 15
			u.u_error = ENOENT;
D 23
			break;
E 23
I 23
			goto bad;
E 23
		}
	}
D 23
	if (u.u_error) {
D 19
		dp = NULL;
		goto out1;
E 19
I 19
		brelse(nbp);
		return (NULL);
E 19
	}
	cp = nbp->b_un.b_addr;
E 23
I 23
	if (u.u_error)
E 57
I 57
	if (ndp->ni_segflg == UIO_SYSSPACE)
D 58
		error = copystr(ndp->ni_dirp, nbp->b_un.b_addr, MAXPATHLEN);
E 58
I 58
D 81
		error = copystr(ndp->ni_dirp, nbp->b_un.b_addr, MAXPATHLEN,
		    (u_int *)0);
E 81
I 81
D 85
		error = copystr(ndp->ni_dirp, nbp, MAXPATHLEN, (u_int *)0);
E 85
I 85
		error = copystr(ndp->ni_dirp, ndp->ni_pnbuf, MAXPATHLEN,
		    &ndp->ni_pathlen);
E 85
E 81
E 58
	else
D 58
		error = copyinstr(ndp->ni_dirp, nbp->b_un.b_addr, MAXPATHLEN);
E 58
I 58
D 81
		error = copyinstr(ndp->ni_dirp, nbp->b_un.b_addr, MAXPATHLEN,
		    (u_int *)0);
E 81
I 81
D 85
		error = copyinstr(ndp->ni_dirp, nbp, MAXPATHLEN, (u_int *)0);
E 85
I 85
		error = copyinstr(ndp->ni_dirp, ndp->ni_pnbuf, MAXPATHLEN,
		    &ndp->ni_pathlen);
E 85
E 81
E 58
	if (error) {
D 85
		u.u_error = error;
E 57
		goto bad;
E 85
I 85
		free(ndp->ni_pnbuf, M_NAMEI);
I 89
		ndp->ni_vp = NULL;
E 89
		return (error);
E 98
I 98
D 108
	if (getbuf) {
		MALLOC(ndp->ni_pnbuf, caddr_t, MAXPATHLEN, M_NAMEI, M_WAITOK);
		if (ndp->ni_segflg == UIO_SYSSPACE)
			error = copystr(ndp->ni_dirp, ndp->ni_pnbuf,
				    MAXPATHLEN, &ndp->ni_pathlen);
		else
			error = copyinstr(ndp->ni_dirp, ndp->ni_pnbuf,
				    MAXPATHLEN, &ndp->ni_pathlen);
		if (error) {
			free(ndp->ni_pnbuf, M_NAMEI);
			ndp->ni_vp = NULL;
			return (error);
		}
E 108
I 108
D 109
#ifdef DIAGNOSTIC
	if (ndp->ni_nameiop & HASBUF)
		panic("namei: reentered");
#endif
	MALLOC(ndp->ni_pnbuf, caddr_t, MAXPATHLEN, M_NAMEI, M_WAITOK);
E 109
I 109
D 115
	if ((ndp->ni_nameiop & HASBUF) == 0)
		MALLOC(ndp->ni_pnbuf, caddr_t, MAXPATHLEN, M_NAMEI, M_WAITOK);
E 115
I 115
	if ((cnp->cn_flags & HASBUF) == 0)
		MALLOC(cnp->cn_pnbuf, caddr_t, MAXPATHLEN, M_NAMEI, M_WAITOK);
E 115
E 109
	if (ndp->ni_segflg == UIO_SYSSPACE)
D 115
		error = copystr(ndp->ni_dirp, ndp->ni_pnbuf,
E 115
I 115
		error = copystr(ndp->ni_dirp, cnp->cn_pnbuf,
E 115
			    MAXPATHLEN, &ndp->ni_pathlen);
	else
D 115
		error = copyinstr(ndp->ni_dirp, ndp->ni_pnbuf,
E 115
I 115
		error = copyinstr(ndp->ni_dirp, cnp->cn_pnbuf,
E 115
			    MAXPATHLEN, &ndp->ni_pathlen);
	if (error) {
D 115
		free(ndp->ni_pnbuf, M_NAMEI);
E 115
I 115
		free(cnp->cn_pnbuf, M_NAMEI);
E 115
		ndp->ni_vp = NULL;
		return (error);
E 108
D 103
		ndp->ni_ptr = ndp->ni_pnbuf;
E 103
E 98
E 85
I 57
	}
I 103
D 108
	ndp->ni_ptr = ndp->ni_pnbuf;
E 108
E 103
I 85
D 98
	ndp->ni_ptr = ndp->ni_pnbuf;
E 98
	ndp->ni_loopcnt = 0;
D 101
	dp = ndp->ni_cdir;
E 101
I 101
D 103
	dp = fdp->fd_cdir;
E 101
D 92
	dp->v_count++;
E 92
I 92
	VREF(dp);
E 103
E 92
E 85
I 84
#ifdef KTRACE
D 103
	if (KTRPOINT(u.u_procp, KTR_NAMEI))
D 85
		ktrnamei(u.u_procp->p_tracep, nbp);
E 85
I 85
		ktrnamei(u.u_procp->p_tracep, ndp->ni_pnbuf);
E 103
I 103
D 115
	if (KTRPOINT(p, KTR_NAMEI))
		ktrnamei(p->p_tracep, ndp->ni_pnbuf);
E 115
I 115
	if (KTRPOINT(cnp->cn_proc, KTR_NAMEI))
		ktrnamei(cnp->cn_proc->p_tracep, cnp->cn_pnbuf);
E 115
E 103
E 85
#endif
E 84
E 57

I 103
	/*
	 * Get starting point for the translation.
	 */
D 108
	if (ndp->ni_nameiop & STARTDIR)
		dp = ndp->ni_startdir;
	else
		dp = fdp->fd_cdir;
E 108
I 108
	if ((ndp->ni_rootdir = fdp->fd_rdir) == NULL)
D 136
		ndp->ni_rootdir = rootdir;
E 136
I 136
		ndp->ni_rootdir = rootvnode;
E 136
	dp = fdp->fd_cdir;
E 108
	VREF(dp);
E 103
I 85
D 108
start:
E 85
E 23
	/*
E 13
D 23
	 * If name starts with '/' start from
	 * root; otherwise start from current dir.
E 23
I 23
	 * Get starting directory.
I 85
	 * Done at start of translation and after symbolic link.
E 85
E 23
	 */
D 13

E 13
D 23
	dp = u.u_cdir;
E 23
I 23
D 81
	cp = nbp->b_un.b_addr;
E 81
I 81
D 85
	cp = nbp;
E 81
E 23
D 12
	if((c=(*func)()) == '/')
E 12
I 12
D 13
	if ((c=(*func)()) == '/')
E 13
I 13
	if (*cp == '/') {
		while (*cp == '/')
			cp++;
E 13
E 12
		if ((dp = u.u_rdir) == NULL)
E 85
I 85
	if (*ndp->ni_ptr == '/') {
I 103
		if (ndp->ni_nameiop & STARTDIR)
			panic("namei: illegal path");
E 103
		vrele(dp);
		while (*ndp->ni_ptr == '/') {
			ndp->ni_ptr++;
			ndp->ni_pathlen--;
E 108
I 108
	for (;;) {
		/*
		 * Check if root directory should replace current directory.
		 * Done at start of translation and after symbolic link.
		 */
D 115
		ndp->ni_ptr = ndp->ni_pnbuf;
		if (*ndp->ni_ptr == '/') {
E 115
I 115
		cnp->cn_nameptr = cnp->cn_pnbuf;
		if (*(cnp->cn_nameptr) == '/') {
E 115
			vrele(dp);
D 115
			while (*ndp->ni_ptr == '/') {
				ndp->ni_ptr++;
E 115
I 115
			while (*(cnp->cn_nameptr) == '/') {
				cnp->cn_nameptr++;
E 115
				ndp->ni_pathlen--;
			}
			dp = ndp->ni_rootdir;
			VREF(dp);
E 108
		}
D 101
		if ((dp = ndp->ni_rdir) == NULL)
E 101
I 101
D 108
		if ((dp = fdp->fd_rdir) == NULL)
E 101
E 85
			dp = rootdir;
D 2
	VOID iget(dp->i_dev, dp->i_number);
E 2
I 2
D 13
	(void) iget(dp->i_dev, dp->i_number);
E 2
D 12
	while(c == '/')
E 12
I 12
	while (c == '/')
E 12
		c = (*func)();
D 12
	if(c == '\0' && flag != 0)
E 12
I 12
	if (c == '\0' && flag != 0)
E 12
		u.u_error = ENOENT;

cloop:
	/*
	 * Here dp contains pointer
	 * to last component matched.
	 */

D 12
	if(u.u_error)
E 12
I 12
	if (u.u_error)
E 12
		goto out;
D 12
	if(c == '\0')
E 12
I 12
	if (c == '\0')
E 12
		return(dp);
I 7

I 10
D 12
#ifdef CHAOS
E 12
D 11
	if((dp->i_mode & IFMT) == IFCHR &&
	   (cdevpath & (1 << major(dp->i_un.i_rdev)))) {
		u.u_dirp--;
E 11
I 11
	/*
D 12
	 *      If the current node is a character
	 *      special file with the SUID bit set, return anyway.
	 *	This lets the Chaos open decode the rest of the name in its own
	 *      peculiar way.  jrl 3/81
	 */
	if((dp->i_mode&(IFMT|ISUID)) == (IFCHR|ISUID)) {
		u.u_dirp--;     /* back up to the slash or null */
E 11
		return(dp);
	}
#endif
I 11

E 11
E 10
D 8
#ifdef CHAOS
	if((dp->i_mode&IFMT) == IFCHR && cdevpath & (1 << major(dp->i_un.i_rdev)) ) {
		u.u_dirp--;
		return(dp);
	}
#endif
E 7

E 8
	/*
E 12
	 * If there is another component,
	 * Gather up name into
	 * users' dir buffer.
	 */

	cp = &u.u_dbuf[0];
	while (c != '/' && c != '\0' && u.u_error == 0 ) {
D 12
		if (mpxip!=NULL && c=='!')
			break;
E 12
I 6
		if (flag==1 && c == ('/'|0200)) {
			u.u_error = ENOENT;
			goto out;
		}
E 6
D 2
		if(cp < &u.u_dbuf[DIRSIZ])
E 2
I 2
		if (cp < &u.u_dbuf[DIRSIZ])
E 2
			*cp++ = c;
		c = (*func)();
E 13
D 23
	}
E 23
I 23
D 85
	} else
		dp = u.u_cdir;
	fs = dp->i_fs;
E 23
D 12
	while(cp < &u.u_dbuf[DIRSIZ])
E 12
I 12
D 13
	while (cp < &u.u_dbuf[DIRSIZ])
E 12
		*cp++ = '\0';
D 12
	while(c == '/')
E 12
I 12
	while (c == '/')
E 12
		c = (*func)();
E 13
I 13
D 55
	ilock(dp);
E 55
I 55
	ILOCK(dp);
E 55
	dp->i_count++;
E 13
D 12
	if (c == '!' && mpxip != NULL) {
		iput(dp);
		plock(mpxip);
		mpxip->i_count++;
		return(mpxip);
	}
E 12
D 19

E 19
I 19
D 23
	fs = dp->i_fs;
	newsize = 0;
dirloop:
E 23
I 23
D 57
	u.u_pdir = (struct inode *)0xc0000000;		/* illegal */
E 57
I 57
	ndp->ni_pdir = (struct inode *)0xc0000000;		/* illegal */
E 85
I 85
D 92
		dp->v_count++;
E 92
I 92
		VREF(dp);
E 108
I 108
		ndp->ni_startdir = dp;
D 115
		if (error = lookup(ndp, p)) {
			FREE(ndp->ni_pnbuf, M_NAMEI);
E 115
I 115
		if (error = lookup(ndp)) {
			FREE(cnp->cn_pnbuf, M_NAMEI);
E 115
			return (error);
		}
		/*
		 * Check for symbolic link
		 */
D 114
		if (ndp->ni_more == 0) {
E 114
I 114
D 115
		if ((ndp->ni_cnd.cn_flags & ISSYMLINK) == 0) {
E 114
			if ((ndp->ni_nameiop & (SAVENAME | SAVESTART)) == 0)
				FREE(ndp->ni_pnbuf, M_NAMEI);
E 115
I 115
		if ((cnp->cn_flags & ISSYMLINK) == 0) {
			if ((cnp->cn_flags & (SAVENAME | SAVESTART)) == 0)
				FREE(cnp->cn_pnbuf, M_NAMEI);
E 115
			else
D 115
				ndp->ni_nameiop |= HASBUF;
E 115
I 115
				cnp->cn_flags |= HASBUF;
E 115
			return (0);
		}
D 115
		if ((ndp->ni_nameiop & LOCKPARENT) && ndp->ni_pathlen == 1)
E 115
I 115
		if ((cnp->cn_flags & LOCKPARENT) && ndp->ni_pathlen == 1)
E 115
D 143
			VOP_UNLOCK(ndp->ni_dvp);
E 143
I 143
			VOP_UNLOCK(ndp->ni_dvp, 0, p);
E 143
		if (ndp->ni_loopcnt++ >= MAXSYMLINKS) {
			error = ELOOP;
			break;
		}
		if (ndp->ni_pathlen > 1)
			MALLOC(cp, char *, MAXPATHLEN, M_NAMEI, M_WAITOK);
		else
D 115
			cp = ndp->ni_pnbuf;
E 115
I 115
			cp = cnp->cn_pnbuf;
E 115
		aiov.iov_base = cp;
		aiov.iov_len = MAXPATHLEN;
		auio.uio_iov = &aiov;
		auio.uio_iovcnt = 1;
		auio.uio_offset = 0;
		auio.uio_rw = UIO_READ;
		auio.uio_segflg = UIO_SYSSPACE;
		auio.uio_procp = (struct proc *)0;
		auio.uio_resid = MAXPATHLEN;
D 115
		if (error = VOP_READLINK(ndp->ni_vp, &auio, p->p_ucred)) {
E 115
I 115
		if (error = VOP_READLINK(ndp->ni_vp, &auio, cnp->cn_cred)) {
E 115
			if (ndp->ni_pathlen > 1)
				free(cp, M_NAMEI);
			break;
		}
		linklen = MAXPATHLEN - auio.uio_resid;
		if (linklen + ndp->ni_pathlen >= MAXPATHLEN) {
			if (ndp->ni_pathlen > 1)
				free(cp, M_NAMEI);
			error = ENAMETOOLONG;
			break;
		}
		if (ndp->ni_pathlen > 1) {
			bcopy(ndp->ni_next, cp + linklen, ndp->ni_pathlen);
D 115
			FREE(ndp->ni_pnbuf, M_NAMEI);
			ndp->ni_pnbuf = cp;
E 115
I 115
			FREE(cnp->cn_pnbuf, M_NAMEI);
			cnp->cn_pnbuf = cp;
E 115
		} else
D 115
			ndp->ni_pnbuf[linklen] = '\0';
E 115
I 115
			cnp->cn_pnbuf[linklen] = '\0';
E 115
		ndp->ni_pathlen += linklen;
		vput(ndp->ni_vp);
		dp = ndp->ni_dvp;
E 108
E 92
	}
D 108
	VOP_LOCK(dp);
E 85
I 63
	ndp->ni_endoff = 0;
E 108
I 108
D 115
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 115
I 115
	FREE(cnp->cn_pnbuf, M_NAMEI);
E 115
	vrele(ndp->ni_dvp);
	vput(ndp->ni_vp);
	ndp->ni_vp = NULL;
	return (error);
}
E 108
E 63
E 57

I 108
/*
 * Search a pathname.
 * This is a very central and rather complicated routine.
 *
 * The pathname is pointed to by ni_ptr and is of length ni_pathlen.
 * The starting directory is taken from ni_startdir. The pathname is
 * descended until done, or a symbolic link is encountered. The variable
 * ni_more is clear if the path is completed; it is set to one if a
 * symbolic link needing interpretation is encountered.
 *
 * The flag argument is LOOKUP, CREATE, RENAME, or DELETE depending on
 * whether the name is to be looked up, created, renamed, or deleted.
 * When CREATE, RENAME, or DELETE is specified, information usable in
 * creating, renaming, or deleting a directory entry may be calculated.
 * If flag has LOCKPARENT or'ed into it, the parent directory is returned
 * locked. If flag has WANTPARENT or'ed into it, the parent directory is
 * returned unlocked. Otherwise the parent directory is not returned. If
 * the target of the pathname exists and LOCKLEAF is or'ed into the flag
 * the target is returned locked, otherwise it is returned unlocked.
 * When creating or renaming and LOCKPARENT is specified, the target may not
 * be ".".  When deleting and LOCKPARENT is specified, the target may be ".".
D 134
 * NOTE: (LOOKUP | LOCKPARENT) currently returns the parent vnode unlocked.
E 134
 * 
 * Overall outline of lookup:
 *
 * dirloop:
 *	identify next component of name at ndp->ni_ptr
 *	handle degenerate case where name is null string
 *	if .. and crossing mount points and on mounted filesys, find parent
 *	call VOP_LOOKUP routine for next component name
 *	    directory vnode returned in ni_dvp, unlocked unless LOCKPARENT set
 *	    component vnode returned in ni_vp (if it exists), locked.
 *	if result vnode is mounted on and crossing mount points,
 *	    find mounted on vnode
 *	if more components of name, do next level at dirloop
 *	return the answer in ni_vp, locked if LOCKLEAF set
 *	    if LOCKPARENT set, return locked parent in ni_dvp
 *	    if WANTPARENT set, return unlocked parent in ni_dvp
 */
D 114
lookup(ndp, p)
E 114
I 114
D 115
lookup(ndp, p)   /* converted to CN */
E 115
I 115
int
lookup(ndp)
E 115
E 114
	register struct nameidata *ndp;
D 115
	struct proc *p;
E 115
{
I 126
D 127
	USES_VOP_LOCK;
	USES_VOP_LOOKUP;
	USES_VOP_UNLOCK;
E 127
E 126
	register char *cp;		/* pointer into pathname argument */
	register struct vnode *dp = 0;	/* the directory we are searching */
	struct vnode *tdp;		/* saved dp */
	struct mount *mp;		/* mount table entry */
	int docache;			/* == 0 do not cache last component */
D 114
	int flag;			/* LOOKUP, CREATE, RENAME or DELETE */
E 114
	int wantparent;			/* 1 => wantparent or lockparent flag */
D 113
	int rdonly;			/* mounted read-only flag bit(s) */
E 113
I 113
	int rdonly;			/* lookup read-only flag bit */
E 113
	int error = 0;
I 114
	struct componentname *cnp = &ndp->ni_cnd;
I 143
	struct proc *p = cnp->cn_proc;
E 143
D 115
#define COMPAT_HACK
#ifdef COMPAT_HACK
	int returncode=0;
#define RETURN(N) {returncode=(N); goto byebye;}
#else
#define RETURN(N) return((N));
#endif
E 115
E 114

I 114
D 115
#ifdef COMPAT_HACK
E 115
E 114
E 108
E 23
E 19
D 13
seloop:
E 13
	/*
I 114
D 115
	 * NEEDSWORK: We assume that the caller has the old
	 * defn of nameiop and so doesn't use flags.
	 * Here we correct this view.
	 * (Will go away when conversion is finished.)
	 */
	cnp->cn_flags = ndp->ni_nameiop & ~OPMASK;
	cnp->cn_nameiop = ndp->ni_nameiop & OPMASK;

	cnp->cn_proc = p;
#endif

	/*
E 115
E 114
D 23
	 * dp must be a directory and
	 * must have X permission.
I 13
	 * cp is a path name relative to that directory.
E 23
I 23
D 108
	 * We come to dirloop to search a new directory.
E 108
I 108
	 * Setup: break out flag bits into variables.
E 108
D 85
	 * The directory must be locked so that it can be
	 * iput, and fs must be already set to dp->i_fs.
E 85
E 23
E 13
	 */
I 108
D 114
	flag = ndp->ni_nameiop & OPMASK;
	wantparent = ndp->ni_nameiop & (LOCKPARENT|WANTPARENT);
	docache = (ndp->ni_nameiop & NOCACHE) ^ NOCACHE;
	if (flag == DELETE || (wantparent && flag != CREATE))
E 114
I 114
D 115
	wantparent = cnp->cn_flags & (LOCKPARENT|WANTPARENT);
E 115
I 115
	wantparent = cnp->cn_flags & (LOCKPARENT | WANTPARENT);
E 115
	docache = (cnp->cn_flags & NOCACHE) ^ NOCACHE;
D 115
	if (cnp->cn_nameiop == DELETE || (wantparent && cnp->cn_nameiop != CREATE))
	wantparent = cnp->cn_flags & (LOCKPARENT|WANTPARENT);
	docache = (cnp->cn_flags & NOCACHE) ^ NOCACHE;
	if (cnp->cn_nameiop == DELETE || (wantparent && cnp->cn_nameiop != CREATE))
E 115
I 115
	if (cnp->cn_nameiop == DELETE ||
	    (wantparent && cnp->cn_nameiop != CREATE))
E 115
E 114
		docache = 0;
D 113
	rdonly = MNT_RDONLY;
	if (ndp->ni_nameiop & REMOTE)
		rdonly |= MNT_EXRDONLY;
E 113
I 113
D 114
	rdonly = ndp->ni_nameiop & RDONLY;
E 114
I 114
	rdonly = cnp->cn_flags & RDONLY;
E 114
E 113
	ndp->ni_dvp = NULL;
D 114
	ndp->ni_more = 0;
E 114
I 114
	cnp->cn_flags &= ~ISSYMLINK;
E 114
	dp = ndp->ni_startdir;
	ndp->ni_startdir = NULLVP;
D 143
	VOP_LOCK(dp);
E 143
I 143
	vn_lock(dp, LK_EXCLUSIVE | LK_RETRY, p);
E 143

E 108
I 21
D 23
#ifdef	EFS
E 23
I 23
dirloop:
E 23
	/*
D 23
	 * But first, if the last component was a character special file
	 * and the major device is the extended file system device
	 * then return even if more pathname exists.
E 23
I 23
D 85
	 * Check accessiblity of directory.
E 23
	 */
I 23
D 25
#ifdef	EFS
E 23
	if ((dp->i_mode & IFMT) == IFCHR && major(dp->i_rdev) == efs_major) {
		brelse(nbp);
		return(dp);
	}
#endif
E 25
E 21
D 19

I 13
dirloop:
E 19
E 13
D 12
	if((dp->i_mode&IFMT) != IFDIR)
E 12
I 12
D 23
	if ((dp->i_mode&IFMT) != IFDIR)
E 23
I 23
	if ((dp->i_mode&IFMT) != IFDIR) {
E 23
E 12
		u.u_error = ENOTDIR;
D 2
	VOID access(dp, IEXEC);
E 2
I 2
D 23
	(void) access(dp, IEXEC);
E 23
I 23
		goto bad;
	}
	if (access(dp, IEXEC))
		goto bad;

E 23
I 18
dirloop2:
E 18
I 13
D 19
	for (i=0; *cp!='\0' && *cp!='/'; i++) {
E 19
I 19
D 23
	for (i = 0; *cp != '\0' && *cp != '/'; cp++) {
E 19
I 15
#ifdef notdef
E 23
I 23
	/*
E 85
D 57
	 * Copy next component of name to u.u_dent.
E 57
I 57
D 108
	 * Copy next component of name to ndp->ni_dent.
I 85
	 * XXX kern_exec looks at d_name
	 * ??? The ni_hash value may be useful for vfs_cache
	 * XXX There must be the last component of the filename left
	 * somewhere accessible via. ndp for NFS (and any other stateless file
	 * systems) in case they are doing a CREATE. The "Towards a..." noted
	 * that ni_ptr would be left pointing to the last component, but since
	 * the ni_pnbuf gets free'd, that is not a good idea.
E 108
I 108
	 * Search a new directory.
	 *
D 114
	 * The ni_hash value is for use by vfs_cache.
E 114
I 114
	 * The cn_hash value is for use by vfs_cache.
E 114
	 * The last component of the filename is left accessible via
D 114
	 * ndp->ptr for callers that need the name. Callers needing
E 114
I 114
	 * cnp->cn_nameptr for callers that need the name. Callers needing
E 114
	 * the name set the SAVENAME flag. When done, they assume
	 * responsibility for freeing the pathname buffer.
E 108
E 85
E 57
	 */
I 128
	cnp->cn_consume = 0;
E 128
I 87
D 98
#ifdef notdef
	for (cp = ndp->ni_ptr; *cp != 0 && *cp != '/'; cp++) {
		if ((*cp & 0200) == 0)
			continue;
		if ((*cp&0377) == ('/'|0200) || flag != DELETE) {
			error = EINVAL;
			goto bad;
		}
	}
	ndp->ni_namelen = cp - ndp->ni_ptr;
	if (ndp->ni_namelen >= MAXNAMLEN) {
		error = ENAMETOOLONG;
		goto bad;
	}
	ndp->ni_pathlen -= ndp->ni_namelen;
#ifdef NAMEI_DIAGNOSTIC
	{ char c = *cp;
	*cp = '\0';
	printf("{%s}: ", ndp->ni_ptr);
	*cp = c; }
#endif
#else fornow
E 87
I 48
D 85
	hash = 0;
E 48
	for (i = 0; *cp != 0 && *cp != '/'; cp++) {
E 85
I 85
	ndp->ni_hash = 0;
	for (cp = ndp->ni_ptr, i = 0; *cp != 0 && *cp != '/'; cp++) {
E 85
E 23
E 15
D 19
		if (i >= DIRSIZ) {
E 19
I 19
		if (i >= MAXNAMLEN) {
E 19
D 69
			u.u_error = ENOENT;
E 69
I 69
D 85
			u.u_error = ENAMETOOLONG;
E 85
I 85
			error = ENAMETOOLONG;
E 85
E 69
D 23
			break;
E 23
I 23
			goto bad;
E 23
		}
D 19
		u.u_dbuf[i] = *cp++;
E 19
I 19
D 23
		u.u_dent.d_name[i] = *cp;
E 19
I 15
#else
D 19
		if (i < DIRSIZ)
			u.u_dbuf[i] = *cp;
		cp++;
E 19
I 19
		if (i < MAXNAMLEN) {
			u.u_dent.d_name[i] = *cp;
			i++;
		}
E 19
#endif
E 23
I 23
D 57
		u.u_dent.d_name[i++] = *cp;
E 57
I 57
D 69
		if ((*cp&0377) == ('/'|0200) || (*cp&0200) && flag != DELETE) {
			u.u_error = EPERM;
			goto bad;
		}
E 69
I 69
		if (*cp & 0200)
			if ((*cp&0377) == ('/'|0200) || flag != DELETE) {
D 85
				u.u_error = EINVAL;
E 85
I 85
				error = EINVAL;
E 98
I 98
D 108
	if (getbuf) {
		ndp->ni_hash = 0;
		for (cp = ndp->ni_ptr, i = 0; *cp != 0 && *cp != '/'; cp++) {
			if (i >= MAXNAMLEN) {
				error = ENAMETOOLONG;
E 98
E 85
				goto bad;
			}
E 69
D 98
		ndp->ni_dent.d_name[i++] = *cp;
E 57
I 48
D 85
		hash += (unsigned char)*cp * i;
E 85
I 85
		ndp->ni_hash += (unsigned char)*cp * i;
E 85
E 48
E 23
E 15
	}
I 85
	ndp->ni_namelen = i;
E 85
E 13
E 2
D 12
	if(u.u_error)
E 12
I 12
D 19
	if (u.u_error)
E 12
		goto out;
E 19
I 19
D 23
	if (u.u_error) {
		iput(dp);
		brelse(nbp);
		return (NULL);
	}
E 23
D 57
	u.u_dent.d_namlen = i;
D 23
	u.u_dent.d_name[i] = '\0';
	newsize = DIRSIZ(&u.u_dent);
E 19
I 14
	u.u_pdir = dp;
E 14
D 13

	/*
	 * set up to search a directory
	 */
	u.u_offset = 0;
E 13
I 13
D 19
	while (i < DIRSIZ)
		u.u_dbuf[i++] = '\0';
	if (u.u_dbuf[0] == '\0') {		/* null name, e.g. "/" or "" */
		if (flag) {
E 19
I 19
	if (u.u_dent.d_name[0] == '\0') {	/* null name, e.g. "/" or "" */
		if (flag != 0) {
E 23
I 23
	u.u_dent.d_name[i] = 0;
E 57
I 57
	ndp->ni_dent.d_namlen = i;
	ndp->ni_dent.d_name[i] = '\0';
E 57
I 53
D 85
	isdotdot = (i == 2 &&
D 57
		u.u_dent.d_name[0] == '.' && u.u_dent.d_name[1] == '.');
E 57
I 57
		ndp->ni_dent.d_name[0] == '.' && ndp->ni_dent.d_name[1] == '.');
I 67
	makeentry = 1;
E 85
I 85
	ndp->ni_pathlen -= i;
E 98
I 98
			if (*cp & 0200)
				if ((*cp&0377) == ('/'|0200) ||
				    flag != DELETE) {
					error = EINVAL;
					goto bad;
				}
			ndp->ni_dent.d_name[i++] = *cp;
			ndp->ni_hash += (unsigned char)*cp * i;
E 108
I 108
D 114
	ndp->ni_hash = 0;
D 111
	for (cp = ndp->ni_ptr; *cp != 0 && *cp != '/'; cp++) {
E 111
I 111
	for (cp = ndp->ni_ptr; *cp != 0 && *cp != '/'; cp++)
E 111
		ndp->ni_hash += (unsigned char)*cp;
D 111
		if ((*cp & 0200) == 0)
			continue;
		if ((*cp & 0377) == ('/' | 0200) || flag != DELETE) {
			error = EINVAL;
			goto bad;
E 108
		}
D 108
		ndp->ni_namelen = i;
		ndp->ni_dent.d_namlen = i;
		ndp->ni_dent.d_name[i] = '\0';
		ndp->ni_pathlen -= i;
		ndp->ni_next = cp;
E 108
I 108
	}
E 111
	ndp->ni_namelen = cp - ndp->ni_ptr;
	if (ndp->ni_namelen >= NAME_MAX) {
E 114
I 114
	cnp->cn_hash = 0;
	for (cp = cnp->cn_nameptr; *cp != 0 && *cp != '/'; cp++)
		cnp->cn_hash += (unsigned char)*cp;
	cnp->cn_namelen = cp - cnp->cn_nameptr;
D 133
	if (cnp->cn_namelen >= NAME_MAX) {
E 133
I 133
	if (cnp->cn_namelen > NAME_MAX) {
E 133
E 114
		error = ENAMETOOLONG;
		goto bad;
	}
E 108
E 98
#ifdef NAMEI_DIAGNOSTIC
D 98
	printf("{%s}: ", ndp->ni_dent.d_name);
E 98
I 98
D 108
		printf("{%s}: ", ndp->ni_dent.d_name);
E 108
I 108
	{ char c = *cp;
	*cp = '\0';
D 114
	printf("{%s}: ", ndp->ni_ptr);
E 114
I 114
	printf("{%s}: ", cnp->cn_nameptr);
E 114
	*cp = c; }
E 108
E 98
#endif
I 87
D 98
#endif fornow
E 87
	ndp->ni_next = cp;
E 98
I 98
D 108
	}
	cp = ndp->ni_next;
E 108
I 108
D 114
	ndp->ni_pathlen -= ndp->ni_namelen;
E 114
I 114
	ndp->ni_pathlen -= cnp->cn_namelen;
E 114
	ndp->ni_next = cp;
E 108
E 98
D 114
	ndp->ni_makeentry = 1;
E 114
I 114
	cnp->cn_flags |= MAKEENTRY;
E 114
E 85
	if (*cp == '\0' && docache == 0)
D 85
		makeentry = 0;
E 85
I 85
D 114
		ndp->ni_makeentry = 0;
	ndp->ni_isdotdot = (ndp->ni_namelen == 2 &&
D 108
		ndp->ni_dent.d_name[1] == '.' && ndp->ni_dent.d_name[0] == '.');
E 108
I 108
		ndp->ni_ptr[1] == '.' && ndp->ni_ptr[0] == '.');
E 114
I 114
		cnp->cn_flags &= ~MAKEENTRY;
	if (cnp->cn_namelen == 2 &&
D 129
			cnp->cn_nameptr[1] == '.' && cnp->cn_nameptr[0] == '.')
E 129
I 129
	    cnp->cn_nameptr[1] == '.' && cnp->cn_nameptr[0] == '.')
E 129
		cnp->cn_flags |= ISDOTDOT;
D 129
	else cnp->cn_flags &= ~ISDOTDOT;
E 129
I 129
	else
		cnp->cn_flags &= ~ISDOTDOT;
E 129
	if (*ndp->ni_next == 0)
		cnp->cn_flags |= ISLASTCN;
D 129
	else cnp->cn_flags &= ~ISLASTCN;
E 129
I 129
	else
		cnp->cn_flags &= ~ISLASTCN;
E 129
E 114
E 108
E 85
E 67
E 57
E 53

I 114

E 114
	/*
	 * Check for degenerate name (e.g. / or "")
	 * which is a way of talking about a directory,
	 * e.g. like "/." or ".".
	 */
D 57
	if (u.u_dent.d_name[0] == 0) {
E 57
I 57
D 85
	if (ndp->ni_dent.d_name[0] == '\0') {
E 57
D 38
		if (flag) {
E 38
I 38
D 48
		if (flag || lockparent) {
E 48
I 48
		if (flag != LOOKUP || lockparent) {
E 48
E 38
E 23
E 19
D 46
			u.u_error = ENOENT;
E 46
I 46
			u.u_error = EISDIR;
E 85
I 85
D 114
	if (ndp->ni_ptr[0] == '\0') {
		if (flag != LOOKUP || wantparent) {
E 114
I 114
	if (cnp->cn_nameptr[0] == '\0') {
D 134
		if (cnp->cn_nameiop != LOOKUP || wantparent) {
E 134
I 134
D 139
		if (cnp->cn_nameiop != LOOKUP) {
E 134
E 114
			error = EISDIR;
E 85
E 46
D 19
			goto out;
E 19
I 19
D 23
			iput(dp);
			dp = NULL;
E 23
I 23
			goto bad;
E 23
E 19
		}
E 139
D 19
		goto out1;
E 19
I 19
D 23
		u.u_offset = 0;
		u.u_count = newsize;
E 23
D 56
		brelse(nbp);
E 56
I 56
D 81
		nbp->av_forw = freenamebuf;
		freenamebuf = nbp;
E 81
I 81
D 85
		FREE(nbp, M_NAMEI);
E 81
E 56
		return (dp);
E 85
I 85
D 98
		free(ndp->ni_pnbuf, M_NAMEI);
E 98
I 98
D 108
		if (getbuf)
			free(ndp->ni_pnbuf, M_NAMEI);
E 108
I 108
		if (dp->v_type != VDIR) {
			error = ENOTDIR;
I 139
			goto bad;
		}
		if (cnp->cn_nameiop != LOOKUP) {
			error = EISDIR;
E 139
			goto bad;
		}
E 108
E 98
D 114
		if (!(ndp->ni_nameiop & LOCKLEAF))
E 114
I 114
D 134
		if (!(cnp->cn_flags & LOCKLEAF))
E 114
			VOP_UNLOCK(dp);
E 134
I 134
		if (wantparent) {
			ndp->ni_dvp = dp;
D 138
			vref(dp);
E 138
I 138
			VREF(dp);
E 138
		}
E 134
		ndp->ni_vp = dp;
I 134
		if (!(cnp->cn_flags & (LOCKPARENT | LOCKLEAF)))
D 143
			VOP_UNLOCK(dp);
E 143
I 143
			VOP_UNLOCK(dp, 0, p);
E 143
E 134
I 108
D 114
		if (ndp->ni_nameiop & SAVESTART)
E 114
I 114
		if (cnp->cn_flags & SAVESTART)
E 114
			panic("lookup: SAVESTART");
E 108
D 114
		return (0);
E 114
I 114
D 115
		RETURN (0);
E 115
I 115
		return (0);
E 115
E 114
E 85
E 19
	}
I 23

E 23
I 19
	/*
I 83
D 85
	 * Special handling for ".." allowing chdir out of mounted
	 * file system: indirect .. in root inode to reevaluate
	 * in directory file system was mounted on.
E 85
I 85
	 * Handle "..": two special cases.
	 * 1. If at root directory (e.g. after chroot)
I 131
	 *    or at absolute root directory
E 131
	 *    then ignore it so can't get out.
	 * 2. If this vnode is the root of a mounted
D 108
	 *    file system, then replace it with the
E 108
I 108
	 *    filesystem, then replace it with the
E 108
	 *    vnode which was mounted on so we take the
	 *    .. in the other file system.
E 85
	 */
D 85
	if (isdotdot) {
E 85
I 85
D 114
	if (ndp->ni_isdotdot) {
E 114
I 114
	if (cnp->cn_flags & ISDOTDOT) {
E 114
E 85
		for (;;) {
D 85
			if (dp == u.u_rdir || dp == rootdir) {
				ndp->ni_dent.d_ino = dp->i_number;
				pdp = dp;
				dp->i_count++;
				goto haveino;
E 85
I 85
D 101
			if (dp == ndp->ni_rdir || dp == rootdir) {
E 101
I 101
D 108
			if (dp == fdp->fd_rdir || dp == rootdir) {
E 108
I 108
D 131
			if (dp == ndp->ni_rootdir) {
E 131
I 131
D 136
			if (dp == ndp->ni_rootdir || dp == rootdir) {
E 136
I 136
			if (dp == ndp->ni_rootdir || dp == rootvnode) {
E 136
E 131
E 108
E 101
				ndp->ni_dvp = dp;
I 93
				ndp->ni_vp = dp;
E 93
D 92
				dp->v_count++;
E 92
I 92
				VREF(dp);
E 92
				goto nextname;
E 85
			}
D 85
			if (dp->i_number != ROOTINO)
E 85
I 85
D 98
			if ((dp->v_flag & VROOT) == 0)
E 98
I 98
			if ((dp->v_flag & VROOT) == 0 ||
D 108
				(ndp->ni_nameiop & NOCROSSMOUNT))
E 108
I 108
D 114
			    (ndp->ni_nameiop & NOCROSSMOUNT))
E 114
I 114
			    (cnp->cn_flags & NOCROSSMOUNT))
E 114
E 108
E 98
E 85
				break;
D 85
			for (i = 1; i < NMOUNT; i++) {
				if (mount[i].m_fs != NULL &&
				    mount[i].m_dev == dp->i_dev) {
					iput(dp);
					dp = mount[i].m_inodp;
					ILOCK(dp);
					dp->i_count++;
					fs = dp->i_fs;
					break;
				}
			}
E 85
I 85
			tdp = dp;
D 99
			dp = dp->v_mount->m_vnodecovered;
E 99
I 99
			dp = dp->v_mount->mnt_vnodecovered;
E 99
			vput(tdp);
D 93
			VOP_LOCK(dp);
E 93
D 92
			dp->v_count++;
E 92
I 92
			VREF(dp);
I 93
D 143
			VOP_LOCK(dp);
E 143
I 143
			vn_lock(dp, LK_EXCLUSIVE | LK_RETRY, p);
E 143
E 93
E 92
E 85
		}
	}

	/*
E 83
I 48
	 * We now have a segment name to search for, and a directory to search.
D 85
	 *
	 * Before tediously performing a linear scan of the directory,
	 * check the name cache to see if the directory/name pair
	 * we are looking for is known already.  We don't do this
	 * if the segment name is long, simply so the cache can avoid
	 * holding long names (which would either waste space, or
	 * add greatly to the complexity).
E 85
	 */
I 130
unionlookup:
E 130
D 57
	if (u.u_dent.d_namlen > NCHNAMLEN) {
E 57
I 57
D 85
	if (ndp->ni_dent.d_namlen > NCHNAMLEN) {
E 57
		nchstats.ncs_long++;
D 67
		docache = 0;
E 67
I 67
		makeentry = 0;
E 67
	} else {
		nhp = &nchash[NHASH(hash, dp->i_number, dp->i_dev)];
D 74
		for (ncp = nhp->nch_forw; ncp != (struct nch *)nhp;
E 74
I 74
		for (ncp = nhp->nch_forw; ncp != (struct namecache *)nhp;
E 74
		    ncp = ncp->nc_forw) {
			if (ncp->nc_ino == dp->i_number &&
			    ncp->nc_dev == dp->i_dev &&
D 57
			    ncp->nc_nlen == u.u_dent.d_namlen &&
			    !bcmp(ncp->nc_name, u.u_dent.d_name, ncp->nc_nlen))
E 57
I 57
			    ncp->nc_nlen == ndp->ni_dent.d_namlen &&
			    !bcmp(ncp->nc_name, ndp->ni_dent.d_name,
D 72
				ncp->nc_nlen))
E 72
I 72
				(unsigned)ncp->nc_nlen))
E 72
E 57
				break;
		}
D 72

E 72
D 74
		if (ncp == (struct nch *)nhp) {
E 74
I 74
		if (ncp == (struct namecache *)nhp) {
E 74
			nchstats.ncs_miss++;
			ncp = NULL;
		} else {
D 51
			if (*cp == '/' || docache) {
E 51
I 51
D 53
			if (ncp->nc_id != ncp->nc_ip->i_id)
E 53
I 53
D 74
			if (ncp->nc_id != ncp->nc_ip->i_id) {
E 74
I 74
			if (ncp->nc_id != ncp->nc_ip->i_id)
E 74
E 53
				nchstats.ncs_falsehits++;
D 53
			else if (*cp == '/' || docache) {
E 53
I 53
D 67
			} else if (*cp == '\0' && !docache) {
E 67
I 67
D 74
			} else if (!makeentry) {
E 74
I 74
			else if (!makeentry)
E 74
E 67
				nchstats.ncs_badhits++;
D 74
			} else {
E 74
I 74
			else {
E 74
E 53
E 51
D 72

D 53
				nchstats.ncs_goodhits++;

E 53
					/*
					 * move this slot to end of LRU
					 * chain, if not already there
					 */
E 72
I 72
				/*
				 * move this slot to end of LRU
				 * chain, if not already there
				 */
E 72
				if (ncp->nc_nxt) {
D 72
						/* remove from LRU chain */
E 72
I 72
					/* remove from LRU chain */
E 72
					*ncp->nc_prev = ncp->nc_nxt;
					ncp->nc_nxt->nc_prev = ncp->nc_prev;

D 72
						/* and replace at end of it */
E 72
I 72
					/* and replace at end of it */
E 72
					ncp->nc_nxt = NULL;
					ncp->nc_prev = nchtail;
					*nchtail = ncp;
					nchtail = &ncp->nc_nxt;
				}

I 53
				/*
				 * Get the next inode in the path.
D 55
				 * See comment above other `iunlock' code for
E 55
I 55
				 * See comment above other `IUNLOCK' code for
E 55
				 * an explaination of the locking protocol.
				 */
E 53
				pdp = dp;
D 67
				dp = ncp->nc_ip;
E 67
I 67
				if (!isdotdot || dp != u.u_rdir)
					dp = ncp->nc_ip;
E 67
				if (dp == NULL)
D 77
					panic("nami: null cache ino");
E 77
I 77
					panic("namei: null cache ino");
E 77
D 51
				if (pdp != dp) {
					ilock(dp);
E 51
I 51
D 67
				if (pdp == dp)
E 67
I 67
D 74
				if (pdp == dp) {
E 74
I 74
				if (pdp == dp)
E 74
E 67
E 51
					dp->i_count++;
D 51
					iunlock(pdp);
				} else
E 51
I 51
D 55
				else if (dp->i_count) {
E 51
					dp->i_count++;
E 55
I 55
D 67
				else {
E 55
I 51
D 53
					ilock(dp);
					iunlock(pdp);
E 53
I 53
					if (isdotdot) {
D 55
						iunlock(pdp);
						ilock(dp);
					} else {
						ilock(dp);
						iunlock(pdp);
					}
E 53
				} else {
D 53
					igrab(dp);
					iunlock(pdp);
E 53
I 53
					if (isdotdot) {
						iunlock(pdp);
E 55
I 55
						IUNLOCK(pdp);
E 55
						igrab(dp);
					} else {
						igrab(dp);
D 55
						iunlock(pdp);
E 55
I 55
						IUNLOCK(pdp);
E 55
					}
E 67
I 67
D 74
				} else if (isdotdot) {
E 74
I 74
				else if (isdotdot) {
E 74
					IUNLOCK(pdp);
					igrab(dp);
				} else {
					igrab(dp);
					IUNLOCK(pdp);
E 67
E 53
				}
E 51

D 53
				u.u_dent.d_ino = dp->i_number;
				/* u_dent.d_reclen is garbage ... */
E 53
I 53
				/*
				 * Verify that the inode that we got
				 * did not change while we were waiting
				 * for it to be locked.
				 */
				if (ncp->nc_id != ncp->nc_ip->i_id) {
					iput(dp);
D 55
					ilock(pdp);
E 55
I 55
					ILOCK(pdp);
E 55
					dp = pdp;
					nchstats.ncs_falsehits++;
				} else {
D 57
					u.u_dent.d_ino = dp->i_number;
					/* u_dent.d_reclen is garbage ... */
E 57
I 57
					ndp->ni_dent.d_ino = dp->i_number;
					/* ni_dent.d_reclen is garbage ... */
E 57
					nchstats.ncs_goodhits++;
					goto haveino;
				}
			}
E 53

D 53
				goto haveino;
D 51
			}
E 51
I 51
			} else
				nchstats.ncs_badhits++;
E 51

E 53
			/*
D 51
			 * last segment and we are renaming or deleting
			 * or otherwise don't want cache entry to exist
E 51
I 51
			 * Last component and we are renaming or deleting,
			 * the cache entry is invalid, or otherwise don't
			 * want cache entry to exist.
E 51
			 */
D 72

D 51
			nchstats.ncs_badhits++;

E 51
				/* remove from LRU chain */
E 72
I 72
			/* remove from LRU chain */
E 72
			*ncp->nc_prev = ncp->nc_nxt;
			if (ncp->nc_nxt)
				ncp->nc_nxt->nc_prev = ncp->nc_prev;
			else
				nchtail = ncp->nc_prev;
D 72

				/* remove from hash chain */
			remque(ncp);

D 51
				/* release ref on the inode */
			irele(ncp->nc_ip);
			ncp->nc_ip = NULL;

E 51
				/* insert at head of LRU list (first to grab) */
E 72
I 72
			remque(ncp);		/* remove from hash chain */
			/* insert at head of LRU list (first to grab) */
E 72
			ncp->nc_nxt = nchhead;
			ncp->nc_prev = &nchhead;
			nchhead->nc_prev = &ncp->nc_nxt;
			nchhead = ncp;
D 72

				/* and make a dummy hash chain */
E 72
I 72
			/* and make a dummy hash chain */
E 72
			ncp->nc_forw = ncp;
			ncp->nc_back = ncp;
D 72

E 72
			ncp = NULL;
		}
	}

	/*
E 48
D 23
	 * set up to search a directory
E 23
I 23
	 * Suppress search for slots unless creating
	 * file and at end of pathname, in which case
	 * we watch for a place to put the new file in
	 * case it doesn't already exist.
E 23
	 */
D 23
	if (flag == 1)
		slot = NONE;
	else
		slot = FOUND;
E 23
I 23
	slotstatus = FOUND;
D 34
	if (flag == 1 && *cp == 0) {
E 34
I 34
	if (flag == CREATE && *cp == 0) {
E 34
		slotstatus = NONE;
		slotfreespace = 0;
D 57
		slotneeded = DIRSIZ(&u.u_dent);
E 57
I 57
		slotneeded = DIRSIZ(&ndp->ni_dent);
E 57
	}
I 47
	/*
	 * If this is the same directory that this process
	 * previously searched, pick up where we last left off.
D 48
	 * We cache only lookups as these are the most common,
E 48
I 48
	 * We cache only lookups as these are the most common
E 48
	 * and have the greatest payoff. Caching CREATE has little
	 * benefit as it usually must search the entire directory
	 * to determine that the entry does not exist. Caching the
	 * location of the last DELETE has not reduced profiling time
	 * and hence has been removed in the interest of simplicity.
	 */
	if (flag != LOOKUP || dp->i_number != u.u_ncache.nc_inumber ||
	    dp->i_dev != u.u_ncache.nc_dev) {
D 57
		u.u_offset = 0;
E 57
I 57
		ndp->ni_offset = 0;
E 57
		numdirpasses = 1;
	} else {
D 48
		if (dp->i_mtime >= u.u_ncache.nc_time) {
E 48
I 48
D 76
		if ((dp->i_flag & ICHG) || dp->i_ctime >= u.u_ncache.nc_time) {
E 76
I 76
D 77
		if ((dp->i_flag & (ICHG|IMOD)) ||
		    dp->i_ctime >= u.u_ncache.nc_time) {
E 76
E 48
D 61
			u.u_ncache.nc_prevoffset &= ~(DIRBLKSIZ - 1);
E 61
I 61
			if (u.u_ncache.nc_prevoffset > dp->i_size)
				u.u_ncache.nc_prevoffset = 0;
			else
				u.u_ncache.nc_prevoffset &= ~(DIRBLKSIZ - 1);
E 61
			u.u_ncache.nc_time = time.tv_sec;
		}
E 77
I 77
		if (u.u_ncache.nc_prevoffset > dp->i_size)
			u.u_ncache.nc_prevoffset = 0;
E 77
D 57
		u.u_offset = u.u_ncache.nc_prevoffset;
		entryoffsetinblock = blkoff(fs, u.u_offset);
E 57
I 57
		ndp->ni_offset = u.u_ncache.nc_prevoffset;
		entryoffsetinblock = blkoff(fs, ndp->ni_offset);
E 57
		if (entryoffsetinblock != 0) {
D 57
			bp = blkatoff(dp, u.u_offset, (char **)0);
E 57
I 57
			bp = blkatoff(dp, ndp->ni_offset, (char **)0);
E 57
			if (bp == 0)
				goto bad;
		}
		numdirpasses = 2;
I 48
		nchstats.ncs_2passes++;
E 48
	}
	endsearch = roundup(dp->i_size, DIRBLKSIZ);
I 63
	enduseful = 0;
E 63
E 47

E 85
I 85
D 107
	if (error = VOP_LOOKUP(dp, ndp)) {
E 107
I 107
D 114
	if (error = VOP_LOOKUP(dp, ndp, p)) {
E 114
I 114
	ndp->ni_dvp = dp;
I 145
	ndp->ni_vp = NULL;
E 145
	if (error = VOP_LOOKUP(dp, &ndp->ni_vp, cnp)) {
E 114
I 108
#ifdef DIAGNOSTIC
E 108
E 107
		if (ndp->ni_vp != NULL)
			panic("leaf should be empty");
I 108
#endif
E 108
E 85
I 84
#ifdef NAMEI_DIAGNOSTIC
D 85
	printf("{%s}:\n", ndp->ni_dent.d_name);
E 85
I 85
		printf("not found\n");
E 85
#endif
I 130
		if ((error == ENOENT) &&
		    (dp->v_flag & VROOT) &&
		    (dp->v_mount->mnt_flag & MNT_UNION)) {
			tdp = dp;
			dp = dp->v_mount->mnt_vnodecovered;
			vput(tdp);
			VREF(dp);
D 143
			VOP_LOCK(dp);
E 143
I 143
			vn_lock(dp, LK_EXCLUSIVE | LK_RETRY, p);
E 143
			goto unionlookup;
		}

E 130
I 96
D 114
		if (flag == LOOKUP || flag == DELETE ||
E 114
I 114
D 117
		if (cnp->cn_nameiop == LOOKUP || cnp->cn_nameiop == DELETE ||
E 114
		    error != ENOENT || *cp != 0)
E 117
I 117
		if (error != EJUSTRETURN)
E 117
			goto bad;
E 96
E 84
D 47
	dirsize = roundup(dp->i_size, DIRBLKSIZ);
E 23
	u.u_offset = 0;
E 19
E 13
D 23
	u.u_segflg = 1;
D 13
	eo = 0;
E 13
I 13
D 19
	eo = -1;
E 19
E 13
	bp = NULL;
I 9
D 11
	if (dp == u.u_rdir && u.u_dent.d_name[0] == '.' &&
	    u.u_dent.d_name[1] == '.' && u.u_dent.d_name[2] == 0)
E 11
I 11
D 13
	if (dp == u.u_rdir && u.u_dbuf[0] == '.' &&
	    u.u_dbuf[1] == '.' && u.u_dbuf[2] == 0)
E 11
		goto cloop;
E 13
E 9
D 19

D 13
eloop:

	/*
	 * If at the end of the directory,
	 * the search failed. Report what
	 * is appropriate as per flag.
	 */

D 12
	if(u.u_offset >= dp->i_size) {
		if(bp != NULL)
E 12
I 12
	if (u.u_offset >= dp->i_size) {
		if (bp != NULL)
E 12
			brelse(bp);
D 4
		if(flag==1 && c=='\0') {
E 4
I 4
D 12
		if(flag==1 && c=='\0' && dp->i_nlink) {
E 4
			if(access(dp, IWRITE))
E 12
I 12
		if (flag==1 && c=='\0' && dp->i_nlink) {
E 13
I 13
	for (u.u_offset=0; u.u_offset < dp->i_size;
	   u.u_offset += sizeof(struct direct), ep++) {
E 19
I 19
	spccnt = 0;
	loc = 0;
	while (u.u_offset < dp->i_size) {
E 23
I 23
	while (u.u_offset < dirsize) {
E 47
I 47
D 85
searchloop:
D 57
	while (u.u_offset < endsearch) {
E 57
I 57
	while (ndp->ni_offset < endsearch) {
E 85
E 57
E 47
E 23
E 19
		/*
I 19
D 23
		 * check to see if enough space has been accumulated to make
		 * an entry by compaction. Reset the free space counter each
		 * time a directory block is crossed.
		 */
		if (slot == NONE) {
			if (spccnt >= newsize) {
				slot = COMPACT;
				entrysize = u.u_offset - entryfree;
			} else if (loc % DIRBLKSIZ == 0) {
				entryfree = NULL;
				spccnt = 0;
			}
		}
		/*
E 23
E 19
D 85
		 * If offset is on a block boundary,
		 * read the next directory block.
		 * Release previous if it exists.
E 85
I 85
		 * If creating and at end of pathname, then can consider
		 * allowing file to be created.
E 85
		 */
D 19
		if ((u.u_offset&BMASK) == 0) {
E 19
I 19
D 57
		if (blkoff(fs, u.u_offset) == 0) {
E 57
I 57
D 85
		if (blkoff(fs, ndp->ni_offset) == 0) {
E 57
E 19
			if (bp != NULL)
				brelse(bp);
D 19
			bp = bread(dp->i_dev,
				bmap(dp,(daddr_t)(u.u_offset>>BSHIFT), B_READ));
E 19
I 19
D 23
			lbn = (daddr_t)lblkno(fs, u.u_offset);
			bsize = blksize(fs, dp, lbn);
			if ((bn = bmap(dp, lbn, B_READ)) < 0) {
				printf("hole in dir: %s i = %d\n",
				    fs->fs_fsmnt, dp->i_number);
				if (fs->fs_ronly != 0 ||
				    (bn = bmap(dp, lbn, B_WRITE, bsize)) < 0) {
					u.u_offset += bsize;
					bp = NULL;
					continue;
				}
			}
			bp = bread(dp->i_dev, fsbtodb(fs, bn), bsize);
E 19
			if (bp->b_flags & B_ERROR) {
				brelse(bp);
D 19
				goto out;
E 19
I 19
				iput(dp);
				brelse(nbp);
				return (NULL);
E 19
			}
D 19
			ep = (struct direct *)bp->b_un.b_addr;
E 19
I 19
			loc = 0;
		} else {
			loc += ep->d_reclen;
E 23
I 23
D 24
			bp = batoffset(dp, u.u_offset, (char **)0);
E 24
I 24
D 57
			bp = blkatoff(dp, u.u_offset, (char **)0);
E 57
I 57
			bp = blkatoff(dp, ndp->ni_offset, (char **)0);
E 57
E 24
			if (bp == 0)
				goto bad;
			entryoffsetinblock = 0;
E 23
E 19
		}
I 23
D 72

E 72
E 23
		/*
D 19
		 * Note first empty directory slot
		 * in eo for possible creat.
E 19
I 19
D 23
		 * calculate the next directory entry and run
		 * some rudimentary bounds checks to make sure
		 * that it is reasonable. If the check fails
		 * resync at the beginning of the next directory
		 * block.
E 23
I 23
		 * If still looking for a slot, and at a DIRBLKSIZE
D 52
		 * boundary, have to start looking for free space
		 * again.
E 52
I 52
		 * boundary, have to start looking for free space again.
E 52
E 23
		 */
D 23
		ep = (struct direct *)(bp->b_un.b_addr + loc);
		i = DIRBLKSIZ - (loc & (DIRBLKSIZ - 1));
		if (ep->d_reclen <= 0 || ep->d_reclen > i) {
I 22
printf("bad reclen: dir#=<%d,%d>, e#=%d, reclen=%d, i=%d, loc=%d\n",
	dp->i_dev, dp->i_number, ep->d_ino, ep->d_reclen, i, loc);
E 22
			loc += i;
E 23
I 23
		if (slotstatus == NONE &&
		    (entryoffsetinblock&(DIRBLKSIZ-1)) == 0) {
			slotoffset = -1;
			slotfreespace = 0;
		}
D 72

E 72
		/*
D 52
		 * Get pointer to next entry, and do consistency checking:
		 *	record length must be multiple of 4
I 24
		 *	record length must not be zero
E 24
		 *	entry must fit in rest of this DIRBLKSIZ block
		 *	record must be large enough to contain name
I 24
		 * When dirchk is set we also check:
		 *	name is not longer than MAXNAMLEN
E 24
		 *	name must be as long as advertised, and null terminated
D 24
		 * Checking last condition is expensive, it is done only
		 * when dirchk is set.
E 24
I 24
		 * Checking last two conditions is done only when dirchk is
		 * set, to save time.
E 52
I 52
		 * Get pointer to next entry.
		 * Full validation checks are slow, so we only check
		 * enough to insure forward progress through the
		 * directory. Complete checks can be run by patching
		 * "dirchk" to be true.
E 52
E 24
		 */
		ep = (struct direct *)(bp->b_un.b_addr + entryoffsetinblock);
D 52
		i = DIRBLKSIZ - (entryoffsetinblock & (DIRBLKSIZ - 1));
D 24
		if ((ep->d_reclen & 0x3) || ep->d_reclen > i ||
		    DIRSIZ(ep) > ep->d_reclen || dirchk && dirbadname(ep)) {
E 24
I 24
		if ((ep->d_reclen & 0x3) || ep->d_reclen == 0 ||
		    ep->d_reclen > i || DIRSIZ(ep) > ep->d_reclen ||
		    dirchk && (ep->d_namlen > MAXNAMLEN || dirbadname(ep))) {
E 52
I 52
D 72
		if (ep->d_reclen <= 0 ||
E 72
I 72
		if (ep->d_reclen == 0 ||
E 72
		    dirchk && dirbadentry(ep, entryoffsetinblock)) {
E 52
E 24
D 57
			dirbad(dp, "mangled entry");
E 57
I 57
			dirbad(dp, ndp->ni_offset, "mangled entry");
E 57
I 52
			i = DIRBLKSIZ - (entryoffsetinblock & (DIRBLKSIZ - 1));
E 52
E 23
D 57
			u.u_offset += i;
E 57
I 57
			ndp->ni_offset += i;
E 57
I 23
			entryoffsetinblock += i;
E 23
			continue;
		}
I 23

E 23
		/*
D 23
		 * If an appropriate sized hole has not yet been found,
E 23
I 23
		 * If an appropriate sized slot has not yet been found,
E 23
		 * check to see if one is available. Also accumulate space
		 * in the current block so that we can determine if
		 * compaction is viable.
		 */
D 23
		if (slot != FOUND) {
			size = ep->d_reclen;
E 23
I 23
		if (slotstatus != FOUND) {
			int size = ep->d_reclen;

E 23
			if (ep->d_ino != 0)
				size -= DIRSIZ(ep);
			if (size > 0) {
D 23
				if (size >= newsize) {
					slot = FOUND;
					entryfree = u.u_offset;
					entrysize = DIRSIZ(ep) + newsize;
E 23
I 23
				if (size >= slotneeded) {
					slotstatus = FOUND;
D 57
					slotoffset = u.u_offset;
E 57
I 57
					slotoffset = ndp->ni_offset;
E 57
					slotsize = ep->d_reclen;
				} else if (slotstatus == NONE) {
					slotfreespace += size;
					if (slotoffset == -1)
D 57
						slotoffset = u.u_offset;
E 57
I 57
						slotoffset = ndp->ni_offset;
E 57
					if (slotfreespace >= slotneeded) {
						slotstatus = COMPACT;
D 57
						slotsize =
						    u.u_offset+ep->d_reclen -
						      slotoffset;
E 57
I 57
						slotsize = ndp->ni_offset +
						      ep->d_reclen - slotoffset;
E 57
					}
E 23
				}
D 23
				if (entryfree == NULL)
					entryfree = u.u_offset;
				spccnt += size;
E 23
			}
		}
I 23

E 23
		/*
E 19
D 23
		 * String compare the directory entry
		 * and the current component.
I 19
		 * If they do not match, continue to the next entry.
E 23
I 23
		 * Check for a name match.
E 23
E 19
		 */
D 19
		if (ep->d_ino == 0) {
			if (eo < 0)
				eo = u.u_offset;
E 19
I 19
D 23
		prevoff = curoff;
		curoff = u.u_offset;
E 23
I 23
		if (ep->d_ino) {
I 84
#ifdef NAMEI_DIAGNOSTIC
			printf("{%s} ", ep->d_name);
#endif
E 84
D 57
			if (ep->d_namlen == u.u_dent.d_namlen &&
			    !bcmp(u.u_dent.d_name, ep->d_name, ep->d_namlen))
E 57
I 57
			if (ep->d_namlen == ndp->ni_dent.d_namlen &&
			    !bcmp(ndp->ni_dent.d_name, ep->d_name,
D 72
				ep->d_namlen))
E 72
I 72
				(unsigned)ep->d_namlen))
E 72
E 57
				goto found;
		}
D 57
		prevoff = u.u_offset;
E 23
		u.u_offset += ep->d_reclen;
E 57
I 57
		prevoff = ndp->ni_offset;
		ndp->ni_offset += ep->d_reclen;
E 57
D 23
		if (ep->d_ino == 0)
E 19
			continue;
D 19
		}
		if (strncmp(u.u_dbuf, ep->d_name, DIRSIZ) != 0)
E 19
I 19
		if (ep->d_namlen != u.u_dent.d_namlen)
E 19
			continue;
I 19
		if (bcmp(u.u_dent.d_name, ep->d_name, ep->d_namlen))
			continue;
E 23
I 23
		entryoffsetinblock += ep->d_reclen;
I 63
		if (ep->d_ino)
			enduseful = ndp->ni_offset;
E 63
	}
I 84
#ifdef NAMEI_DIAGNOSTIC
	printf("\nnotfound\n");
#endif
E 84
I 48
/* notfound: */
E 48
I 47
	/*
D 48
	 * If we started in the middle of the directory and failed 
E 48
I 48
	 * If we started in the middle of the directory and failed
E 48
	 * to find our target, we must check the beginning as well.
	 */
	if (numdirpasses == 2) {
		numdirpasses--;
D 57
		u.u_offset = 0;
E 57
I 57
		ndp->ni_offset = 0;
E 57
		endsearch = u.u_ncache.nc_prevoffset;
		goto searchloop;
	}
E 47
D 48
/* notfound: */
E 48
	/*
	 * If creating, and at end of pathname and current
D 34
	 * directory has not been removed, then can consider allowing
	 * file to be created.
E 34
I 34
	 * directory has not been removed, then can consider
	 * allowing file to be created.
E 34
	 */
D 34
	if (flag == 1 && *cp == 0 && dp->i_nlink != 0) {
E 34
I 34
	if (flag == CREATE && *cp == 0 && dp->i_nlink != 0) {
E 34
E 23
E 19
		/*
D 23
		 * Here a component matched in a directory.
		 * If there is more pathname, go back to
		 * dirloop, otherwise return.
E 23
I 23
		 * Access for write is interpreted as allowing
		 * creation of files in the directory.
E 23
		 */
D 19
		bcopy((caddr_t)ep, (caddr_t)&u.u_dent, sizeof(struct direct));
E 19
I 19
D 23
		bcopy((caddr_t)ep, (caddr_t)&u.u_dent, DIRSIZ(ep));
E 19
		brelse(bp);
D 19
		if (flag==2 && *cp=='\0') {
E 13
			if (access(dp, IWRITE))
E 12
				goto out;
D 13
			u.u_pdir = dp;
D 12
			if(eo)
E 12
I 12
			if (eo)
E 12
				u.u_offset = eo-sizeof(struct direct);
			else
				dp->i_flag |= IUPD|ICHG;
			return(NULL);
E 13
I 13
			/* should fix unlink */
			u.u_offset += sizeof(struct direct);
			goto out1;
E 19
I 19
		if (flag == 2 && *cp == '\0') {
			brelse(nbp);
			if (access(dp, IWRITE)) {
				iput(dp);
				return (NULL);
			}
			if (curoff % DIRBLKSIZ == 0) {
				u.u_offset = curoff;
				u.u_count = 0;
				return (dp);
			}
			u.u_offset = prevoff;
			u.u_count = DIRSIZ((struct direct *)
			    (bp->b_un.b_addr + blkoff(fs, prevoff)));
			return (dp);
E 19
E 13
		}
E 23
I 23
		if (access(dp, IWRITE))
E 85
I 85
D 96
		if (ndp->ni_dvp->v_mount->m_flag & M_RDONLY)
E 96
I 96
D 98
		if (ndp->ni_dvp->v_mount->m_flag & M_RDONLY) {
E 98
I 98
D 99
		if (ndp->ni_dvp->v_mount->m_flag & rdonly) {
E 99
I 99
D 113
		if (ndp->ni_dvp->v_mount->mnt_flag & rdonly) {
E 113
I 113
D 145
		if (rdonly || (ndp->ni_dvp->v_mount->mnt_flag & MNT_RDONLY)) {
E 145
I 145
		if (rdonly) {
E 145
E 113
E 99
E 98
E 96
			error = EROFS;
D 86
		if (error != ENOENT || flag != CREATE || *cp != 0)
E 86
I 86
D 96
		if (flag == LOOKUP || flag == DELETE ||
		    error != ENOENT || *cp != 0)
E 96
E 86
E 85
			goto bad;
I 96
		}
E 96
E 23
D 13
		u.u_error = ENOENT;
		goto out;
	}
E 13
I 13
		/*
D 23
		 * Special handling for ".."
E 23
I 23
D 85
		 * Return an indication of where the new directory
		 * entry should be put.  If we didn't find a slot,
D 57
		 * then set u.u_count to 0 indicating that the
		 * new slot belongs at the end of the directory.
		 * If we found a slot, then the new entry can be
		 * put in the range [u.u_offset..u.u_offset+u.u_count)
E 57
I 57
		 * then set ndp->ni_count to 0 indicating that the new
		 * slot belongs at the end of the directory. If we found
		 * a slot, then the new entry can be put in the range
		 * [ndp->ni_offset .. ndp->ni_offset + ndp->ni_count)
E 85
I 85
		 * We return with ni_vp NULL to indicate that the entry
		 * doesn't currently exist, leaving a pointer to the
		 * (possibly locked) directory inode in ndp->ni_dvp.
E 85
E 57
E 23
		 */
D 19
		if (u.u_dent.d_name[0]=='.' && u.u_dent.d_name[1]=='.' &&
		    u.u_dent.d_name[2]=='\0') {
E 19
I 19
D 23
		if (u.u_dent.d_name[0] == '.' && u.u_dent.d_name[1] == '.' &&
		    u.u_dent.d_name[2] == '\0') {
E 19
			if (dp == u.u_rdir)
				u.u_dent.d_ino = dp->i_number;
D 19
			else if (u.u_dent.d_ino==ROOTINO &&
E 19
I 19
			else if (u.u_dent.d_ino == ROOTINO &&
E 19
			   dp->i_number == ROOTINO) {
D 19
				for(i=1; i<NMOUNT; i++)
E 19
I 19
				for (i = 1; i < NMOUNT; i++)
E 19
					if (mount[i].m_bufp != NULL &&
					   mount[i].m_dev == dp->i_dev) {
						iput(dp);
						dp = mount[i].m_inodp;
						ilock(dp);
						dp->i_count++;
I 19
						fs = dp->i_fs;
E 19
						cp -= 2;     /* back over .. */
D 18
						goto dirloop;
E 18
I 18
						goto dirloop2;
E 18
					}
			}
E 23
I 23
D 47
		if (slotstatus == NONE)
E 47
I 47
D 85
		if (slotstatus == NONE) {
D 57
			u.u_offset = roundup(dp->i_size, DIRBLKSIZ);
E 47
			u.u_count = 0;
E 57
I 57
			ndp->ni_offset = roundup(dp->i_size, DIRBLKSIZ);
			ndp->ni_count = 0;
I 63
			enduseful = ndp->ni_offset;
E 63
E 57
D 47
		else {
E 47
I 47
		} else {
E 47
D 57
			u.u_offset = slotoffset;
			u.u_count = slotsize;
E 57
I 57
			ndp->ni_offset = slotoffset;
			ndp->ni_count = slotsize;
I 63
			if (enduseful < slotoffset + slotsize)
				enduseful = slotoffset + slotsize;
E 63
E 57
E 23
		}
I 63
		ndp->ni_endoff = roundup(enduseful, DIRBLKSIZ);
E 63
D 23
		d = dp->i_dev;
D 16
		ino = dp->i_number;
E 16
D 14
		iput(dp);
E 14
I 14
D 20
		irele(dp);
E 20
		pdp = dp;
I 20
		iunlock(pdp);
E 20
E 14
D 19
		dp = iget(d, u.u_dent.d_ino);
E 19
I 19
		dp = iget(d, fs, u.u_dent.d_ino);
E 19
D 14
		if (dp == NULL)
E 14
I 14
		if (dp == NULL)  {
D 20
			iput(pdp);
E 20
I 20
			irele(pdp);
E 20
E 14
D 19
			goto out1;
E 19
I 19
			brelse(nbp);
			return (NULL);
E 19
I 14
		}
I 19
		fs = dp->i_fs;
E 23
I 23
		dp->i_flag |= IUPD|ICHG;
		if (bp)
			brelse(bp);
D 56
		brelse(nbp);
E 56
I 56
D 81
		nbp->av_forw = freenamebuf;
		freenamebuf = nbp;
E 81
I 81
		FREE(nbp, M_NAMEI);
E 81
E 56
E 23
E 19
E 14
		/*
D 23
		 * Check for symbolic link
E 23
I 23
		 * We return with the directory locked, so that
		 * the parameters we set up above will still be
		 * valid if we actually decide to do a direnter().
		 * We return NULL to indicate that the entry doesn't
		 * currently exist, leaving a pointer to the (locked)
D 57
		 * directory inode in u.u_pdir.
E 57
I 57
		 * directory inode in ndp->ni_pdir.
E 57
E 23
		 */
D 19
		if ((dp->i_mode&IFMT)==IFLNK && (follow || *cp=='/')) {
			char *ocp;
E 13

D 13
	/*
	 * If offset is on a block boundary,
	 * read the next directory block.
	 * Release previous if it exists.
	 */

D 12
	if((u.u_offset&BMASK) == 0) {
		if(bp != NULL)
E 12
I 12
	if ((u.u_offset&BMASK) == 0) {
		if (bp != NULL)
E 13
I 13
			ocp = cp;
			while (*cp++)
				;
			if (dp->i_size + (cp-ocp) >= BSIZE-1 || ++nlink>8) {
E 19
I 19
D 23
		if ((dp->i_mode & IFMT) == IFLNK && (follow || *cp == '/')) {
			pathlen = strlen(cp) + 1;
			if (dp->i_size + pathlen >= MAXPATHLEN - 1 ||
			    ++nlink > MAXSYMLINKS) {
E 19
				u.u_error = ELOOP;
I 14
D 20
				iput(pdp);
E 20
I 20
				irele(pdp);
E 23
I 23
D 57
		u.u_pdir = dp;
E 57
I 57
		ndp->ni_pdir = dp;
E 57
		return (NULL);
E 85
I 85
D 98
		FREE(ndp->ni_pnbuf, M_NAMEI);
E 98
I 98
D 108
		if (getbuf)
			FREE(ndp->ni_pnbuf, M_NAMEI);
E 98
		return (0);	/* should this be ENOENT? */
E 108
I 108
D 114
		if (ndp->ni_nameiop & SAVESTART) {
E 114
I 114
		if (cnp->cn_flags & SAVESTART) {
E 114
			ndp->ni_startdir = ndp->ni_dvp;
			VREF(ndp->ni_startdir);
I 110
			p->p_spare[1]++;
E 110
		}
D 114
		return (0);
E 114
I 114
D 115
		RETURN (0);
E 115
I 115
		return (0);
E 115
E 114
E 108
E 85
	}
D 85
	u.u_error = ENOENT;
	goto bad;
found:
E 85
I 84
#ifdef NAMEI_DIAGNOSTIC
D 85
	printf("\nfound\n");
E 85
I 85
	printf("found\n");
E 85
#endif
I 128

	/*
	 * Take into account any additional components consumed by
	 * the underlying filesystem.
	 */
	if (cnp->cn_consume > 0) {
		cnp->cn_nameptr += cnp->cn_consume;
		ndp->ni_next += cnp->cn_consume;
		ndp->ni_pathlen -= cnp->cn_consume;
		cnp->cn_consume = 0;
	}
E 128
E 84
I 48
D 85
	if (numdirpasses == 2)
		nchstats.ncs_pass2++;
E 48
	/*
	 * Check that directory length properly reflects presence
	 * of this entry.
	 */
D 24
	if (entryoffsetinblock + ep->d_reclen > dp->i_size) {
E 24
I 24
	if (entryoffsetinblock + DIRSIZ(ep) > dp->i_size) {
E 24
D 57
		dirbad(dp, "i_size too small");
E 57
I 57
		dirbad(dp, ndp->ni_offset, "i_size too small");
E 57
D 24
		dp->i_size = entryoffsetinblock + ep->d_reclen;
E 24
I 24
		dp->i_size = entryoffsetinblock + DIRSIZ(ep);
E 24
		dp->i_flag |= IUPD|ICHG;
	}
E 85

I 108
	dp = ndp->ni_vp;
E 108
	/*
D 47
	 * Found component in pathname; save directory
	 * entry in u.u_dent, and release directory buffer.
E 47
I 47
D 85
	 * Found component in pathname.
D 48
	 * If final component of path name, save information
E 48
I 48
	 * If the final component of path name, save information
E 48
	 * in the cache as to where the entry was found.
E 85
I 85
D 141
	 * Check for symbolic link
E 85
	 */
D 85
	if (*cp == '\0' && flag == LOOKUP) {
D 57
		u.u_ncache.nc_prevoffset = u.u_offset;
E 57
I 57
D 77
		u.u_ncache.nc_prevoffset = ndp->ni_offset;
E 77
I 77
		u.u_ncache.nc_prevoffset = ndp->ni_offset &~ (DIRBLKSIZ - 1);
E 77
E 57
		u.u_ncache.nc_inumber = dp->i_number;
		u.u_ncache.nc_dev = dp->i_dev;
D 77
		u.u_ncache.nc_time = time.tv_sec;
E 77
	}
	/*
D 57
	 * Save directory entry in u.u_dent,
E 57
I 57
D 67
	 * Save directory entry in ndp->ni_dent,
E 67
I 67
	 * Save directory entry's inode number and reclen in ndp->ni_dent,
E 67
E 57
	 * and release directory buffer.
E 47
	 */
D 27
	bcopy((caddr_t)ep, (caddr_t)&u.u_dent, DIRSIZ(ep));
E 27
I 27
D 57
	bcopy((caddr_t)ep, (caddr_t)&u.u_dent, (u_int)DIRSIZ(ep));
E 57
I 57
D 67
	bcopy((caddr_t)ep, (caddr_t)&ndp->ni_dent, (u_int)DIRSIZ(ep));
E 67
I 67
	ndp->ni_dent.d_ino = ep->d_ino;
	ndp->ni_dent.d_reclen = ep->d_reclen;
E 67
E 57
E 27
	brelse(bp);
	bp = NULL;
E 85
I 85
D 108
	dp = ndp->ni_vp;
E 108
	if ((dp->v_type == VLNK) &&
D 114
	    ((ndp->ni_nameiop & FOLLOW) || *ndp->ni_next == '/')) {
D 108
		struct iovec aiov;
		struct uio auio;
		int linklen;
E 85

I 98
		if (!getbuf)
			panic("namei: unexpected symlink");
E 98
D 85
	/*
	 * If deleting, and at end of pathname, return
	 * parameters which can be used to remove file.
D 34
	 * Note that in this case we return the directory
	 * inode, not the inode of the file being deleted.
E 34
I 34
	 * If the lockparent flag isn't set, we return only
D 57
	 * the directory (in u.u_pdir), otherwise we go
E 57
I 57
	 * the directory (in ndp->ni_pdir), otherwise we go
E 57
	 * on and lock the inode, being careful with ".".
E 34
	 */
D 34
	if (flag == 2 && *cp == 0) {
E 34
I 34
	if (flag == DELETE && *cp == 0) {
E 34
		/*
		 * Write access to directory required to delete files.
		 */
		if (access(dp, IWRITE))
			goto bad;
I 34
D 57
		u.u_pdir = dp;		/* for dirremove() */
E 57
I 57
		ndp->ni_pdir = dp;		/* for dirremove() */
E 57
E 34
		/*
D 57
		 * Return pointer to current entry in u.u_offset,
E 57
I 57
		 * Return pointer to current entry in ndp->ni_offset,
E 57
		 * and distance past previous entry (if there
D 57
		 * is a previous entry in this block) in u.u_count.
		 * Save directory inode pointer in u.u_pdir for dirremove().
E 57
I 57
		 * is a previous entry in this block) in ndp->ni_count.
		 * Save directory inode pointer in ndp->ni_pdir for dirremove().
E 57
		 */
D 57
		if ((u.u_offset&(DIRBLKSIZ-1)) == 0)
			u.u_count = 0;
E 57
I 57
		if ((ndp->ni_offset&(DIRBLKSIZ-1)) == 0)
			ndp->ni_count = 0;
E 57
		else
D 57
			u.u_count = u.u_offset - prevoff;
E 57
I 57
			ndp->ni_count = ndp->ni_offset - prevoff;
E 57
I 34
		if (lockparent) {
D 57
			if (dp->i_number == u.u_dent.d_ino)
E 57
I 57
			if (dp->i_number == ndp->ni_dent.d_ino)
E 57
				dp->i_count++;
			else {
D 57
				dp = iget(dp->i_dev, fs, u.u_dent.d_ino);
E 57
I 57
				dp = iget(dp->i_dev, fs, ndp->ni_dent.d_ino);
E 57
				if (dp == NULL) {
D 57
					iput(u.u_pdir);
E 57
I 57
					iput(ndp->ni_pdir);
E 57
					goto bad;
				}
I 48
				/*
D 50
				 * If directory is setuid, then user must own
E 50
I 50
				 * If directory is "sticky", then user must own
E 50
				 * the directory, or the file in it, else he
				 * may not delete it (unless he's root). This
				 * implements append-only directories.
				 */
D 50
				if ((u.u_pdir->i_mode & ISUID) &&
E 50
I 50
D 57
				if ((u.u_pdir->i_mode & ISVTX) &&
E 57
I 57
				if ((ndp->ni_pdir->i_mode & ISVTX) &&
E 57
E 50
				    u.u_uid != 0 &&
D 57
				    u.u_uid != u.u_pdir->i_uid &&
E 57
I 57
				    u.u_uid != ndp->ni_pdir->i_uid &&
E 57
				    dp->i_uid != u.u_uid) {
D 57
					iput(u.u_pdir);
E 57
I 57
					iput(ndp->ni_pdir);
E 57
					u.u_error = EPERM;
					goto bad;
				}
E 48
			}
E 85
I 85
		if (++ndp->ni_loopcnt > MAXSYMLINKS) {
			error = ELOOP;
			goto bad2;
E 85
		}
E 34
D 56
		brelse(nbp);
E 56
I 56
D 81
		nbp->av_forw = freenamebuf;
		freenamebuf = nbp;
E 81
I 81
D 85
		FREE(nbp, M_NAMEI);
E 81
E 56
D 34
		u.u_pdir = dp;		/* for dirremove() */
E 34
		return (dp);
D 83
	}

	/*
	 * Special handling for ".." allowing chdir out of mounted
	 * file system: indirect .. in root inode to reevaluate
	 * in directory file system was mounted on.
	 */
D 48
	if (u.u_dent.d_name[0] == '.' && u.u_dent.d_name[1] == '.' &&
	    u.u_dent.d_name[2] == '\0') {
E 48
I 48
D 53
	isdotdot = 0;
	if (bcmp(u.u_dent.d_name, "..", 3) == 0) {
		isdotdot++;
E 53
I 53
	if (isdotdot) {
E 53
E 48
D 67
		if (dp == u.u_rdir)
E 67
I 67
		if (dp == u.u_rdir) {
E 67
D 57
			u.u_dent.d_ino = dp->i_number;
		else if (u.u_dent.d_ino == ROOTINO &&
E 57
I 57
			ndp->ni_dent.d_ino = dp->i_number;
D 67
		else if (ndp->ni_dent.d_ino == ROOTINO &&
E 67
I 67
			makeentry = 0;
		} else if (ndp->ni_dent.d_ino == ROOTINO &&
E 67
E 57
		   dp->i_number == ROOTINO) {
			for (i = 1; i < NMOUNT; i++)
D 82
			if (mount[i].m_bufp != NULL &&
E 82
I 82
			if (mount[i].m_fs != NULL &&
E 82
			   mount[i].m_dev == dp->i_dev) {
E 23
E 20
E 14
D 19
				goto out;
E 19
I 19
				iput(dp);
D 23
				brelse(nbp);
				return (NULL);
E 19
			}
D 17
			bcopy(ocp, nbp->b_un.b_addr+dp->i_size, cp-ocp);
E 17
I 17
D 19
			bcopy(ocp, nbp->b_un.b_addr+dp->i_size,
			  (unsigned)(cp-ocp));
E 17
			bp = bread(dp->i_dev, bmap(dp, (daddr_t)0, B_READ));
E 19
I 19
			bcopy(cp, nbp->b_un.b_addr + dp->i_size, pathlen);
			bn =  bmap(dp, (daddr_t)0, B_READ);
			if (bn < 0) {
				printf("hole in symlink: %s i = %d\n",
				    fs->fs_fsmnt, dp->i_number);
D 20
				iput(pdp);
E 20
I 20
				irele(pdp);
E 20
				iput(dp);
				brelse(nbp);
				return (NULL);
			}
			bp = bread(dp->i_dev, fsbtodb(fs, bn),
				   (int)blksize(fs, dp, (daddr_t)0));
E 19
			if (bp->b_flags & B_ERROR) {
				brelse(bp);
I 14
D 20
				iput(pdp);
E 20
I 20
				irele(pdp);
E 20
E 14
D 19
				goto out;
E 19
I 19
				iput(dp);
				brelse(nbp);
				return (NULL);
E 19
			}
D 17
			bcopy(bp->b_un.b_addr, nbp->b_un.b_addr, dp->i_size);
E 17
I 17
			bcopy(bp->b_un.b_addr, nbp->b_un.b_addr,
			  (unsigned)dp->i_size);
E 17
E 13
E 12
			brelse(bp);
D 13
		bp = bread(dp->i_dev,
			bmap(dp, (daddr_t)(u.u_offset>>BSHIFT), B_READ));
		if (bp->b_flags & B_ERROR) {
			brelse(bp);
			goto out;
E 13
I 13
			cp = nbp->b_un.b_addr;
			iput(dp);
			if (*cp == '/') {
I 14
D 20
				iput(pdp);
E 20
I 20
				irele(pdp);
E 20
E 14
				while (*cp == '/')
					cp++;
				if ((dp = u.u_rdir) == NULL)
					dp = rootdir;
E 23
I 23
				dp = mount[i].m_inodp;
E 23
D 55
				ilock(dp);
E 55
I 55
				ILOCK(dp);
E 55
				dp->i_count++;
D 23
			} else {
D 14
				dp = iget(d, ino);	/* retrieve directory */
				if (dp == NULL)
					goto out1;
E 14
I 14
				dp = pdp;
				ilock(dp);
E 23
I 23
				fs = dp->i_fs;
				cp -= 2;     /* back over .. */
				goto dirloop2;
E 23
E 14
			}
I 19
D 23
			fs = dp->i_fs;
E 19
			goto dirloop;
E 23
E 13
		}
E 83
I 14
D 20
		iput(pdp);
E 20
I 20
D 23
		irele(pdp);
E 23
I 23
	}

	/*
I 34
	 * If rewriting (rename), return the inode and the
	 * information required to rewrite the present directory
	 * Must get inode of directory entry to verify it's a
	 * regular file, or empty directory.  
	 */
	if ((flag == CREATE && lockparent) && *cp == 0) {
		if (access(dp, IWRITE))
			goto bad;
D 57
		u.u_pdir = dp;		/* for dirrewrite() */
E 57
I 57
		ndp->ni_pdir = dp;		/* for dirrewrite() */
E 57
		/*
		 * Careful about locking second inode. 
		 * This can only occur if the target is ".". 
		 */
D 57
		if (dp->i_number == u.u_dent.d_ino) {
E 57
I 57
		if (dp->i_number == ndp->ni_dent.d_ino) {
E 57
			u.u_error = EISDIR;		/* XXX */
			goto bad;
		}
D 57
		dp = iget(dp->i_dev, fs, u.u_dent.d_ino);
E 57
I 57
		dp = iget(dp->i_dev, fs, ndp->ni_dent.d_ino);
E 57
		if (dp == NULL) {
D 57
			iput(u.u_pdir);
E 57
I 57
			iput(ndp->ni_pdir);
E 57
			goto bad;
		}
D 56
		brelse(nbp);
E 56
I 56
D 81
		nbp->av_forw = freenamebuf;
		freenamebuf = nbp;
E 81
I 81
		FREE(nbp, M_NAMEI);
E 81
E 56
		return (dp);
	}

	/*
E 34
D 41
	 * Check for symbolic link, which may require us
	 * to massage the name before we continue translation.
	 * To avoid deadlock have to unlock the current directory,
	 * but don't iput it because we may need it again (if
	 * the symbolic link is relative to .).  Instead save
	 * it (unlocked) as pdp.
E 41
I 41
	 * Check for symbolic link, which may require us to massage the
	 * name before we continue translation.  We do not `iput' the
	 * directory because we may need it again if the symbolic link
	 * is relative to the current directory.  Instead we save it
	 * unlocked as "pdp".  We must get the target inode before unlocking
	 * the directory to insure that the inode will not be removed
	 * before we get it.  We prevent deadlock by always fetching
	 * inodes from the root, moving down the directory tree. Thus
	 * when following backward pointers ".." we must unlock the
	 * parent directory before getting the requested directory.
	 * There is a potential race condition here if both the current
	 * and parent directories are removed before the `iget' for the
	 * inode associated with ".." returns.  We hope that this occurs
	 * infrequently since we cannot avoid this race condition without
D 42
	 * implementing a sophistocated deadlock detection algorithm.
E 42
I 42
	 * implementing a sophisticated deadlock detection algorithm.
E 42
	 * Note also that this simple deadlock detection scheme will not
	 * work if the file system has any hard links other than ".."
	 * that point backwards in the directory structure.
E 41
	 */
	pdp = dp;
D 41
	iunlock(pdp);
	dp = iget(dp->i_dev, fs, u.u_dent.d_ino);
	if (dp == NULL)
		goto bad2;
E 41
I 41
D 48
	if (bcmp(u.u_dent.d_name, "..", 3) == 0) {
E 48
I 48
	if (isdotdot) {
E 48
D 55
		iunlock(pdp);	/* race to get the inode */
E 55
I 55
		IUNLOCK(pdp);	/* race to get the inode */
E 55
D 57
		dp = iget(dp->i_dev, fs, u.u_dent.d_ino);
E 57
I 57
		dp = iget(dp->i_dev, fs, ndp->ni_dent.d_ino);
E 57
		if (dp == NULL)
E 85
I 85
D 90
		if (ndp->ni_pathlen == 1)
E 90
I 90
		if (ndp->ni_pathlen > 1)
E 90
			MALLOC(cp, char *, MAXPATHLEN, M_NAMEI, M_WAITOK);
		else
			cp = ndp->ni_pnbuf;
		aiov.iov_base = cp;
		aiov.iov_len = MAXPATHLEN;
		auio.uio_iov = &aiov;
		auio.uio_iovcnt = 1;
		auio.uio_offset = 0;
		auio.uio_rw = UIO_READ;
		auio.uio_segflg = UIO_SYSSPACE;
I 107
		auio.uio_procp = (struct proc *)0;
E 107
		auio.uio_resid = MAXPATHLEN;
D 105
		if (error = VOP_READLINK(dp, &auio, ndp->ni_cred)) {
E 105
I 105
		if (error = VOP_READLINK(dp, &auio, p->p_ucred)) {
E 105
D 90
			if (ndp->ni_pathlen == 1)
E 90
I 90
			if (ndp->ni_pathlen > 1)
E 90
				free(cp, M_NAMEI);
E 85
			goto bad2;
D 57
	} else if (dp->i_number == u.u_dent.d_ino) {
E 57
I 57
D 85
	} else if (dp->i_number == ndp->ni_dent.d_ino) {
E 57
		dp->i_count++;	/* we want ourself, ie "." */
	} else {
D 57
		dp = iget(dp->i_dev, fs, u.u_dent.d_ino);
E 57
I 57
		dp = iget(dp->i_dev, fs, ndp->ni_dent.d_ino);
E 57
D 55
		iunlock(pdp);
E 55
I 55
		IUNLOCK(pdp);
E 55
		if (dp == NULL)
E 85
I 85
		}
		linklen = MAXPATHLEN - auio.uio_resid;
		if (linklen + ndp->ni_pathlen >= MAXPATHLEN) {
D 90
			if (ndp->ni_pathlen == 1)
E 90
I 90
			if (ndp->ni_pathlen > 1)
E 90
				free(cp, M_NAMEI);
			error = ENAMETOOLONG;
E 85
			goto bad2;
D 85
	}
I 48

	/*
D 69
	 * insert name into cache (if we want it, and it isn't "." or "..")
	 *
	 * all other cases where making a cache entry would be wrong
	 * have already departed from the code sequence somewhere above.
E 69
I 69
D 72
	 * insert name into cache if appropriate
E 72
I 72
	 * Insert name into cache if appropriate.
E 72
E 69
	 */
D 51
	if (bcmp(u.u_dent.d_name, ".", 2) != 0 && !isdotdot && docache) {
E 51
I 51
D 67
	if (docache) {
E 67
I 67
	if (makeentry) {
E 67
E 51
		if (ncp != NULL)
D 77
			panic("nami: duplicating cache");
E 77
I 77
			panic("namei: duplicating cache");
E 77
D 72

			/*
			 * free the cache slot at head of lru chain
			 */
E 72
I 72
		/*
		 * Free the cache slot at head of lru chain.
		 */
E 72
		if (ncp = nchhead) {
D 72
				/* remove from lru chain */
E 72
I 72
			/* remove from lru chain */
E 72
			*ncp->nc_prev = ncp->nc_nxt;
			if (ncp->nc_nxt)
				ncp->nc_nxt->nc_prev = ncp->nc_prev;
			else
				nchtail = ncp->nc_prev;
D 72

				/* remove from old hash chain */
			remque(ncp);

D 51
				/* drop hold on inode (if we had one) */
			if (ncp->nc_ip)
				irele(ncp->nc_ip);

E 51
				/* grab the inode we just found */
E 72
I 72
			remque(ncp);		/* remove from old hash chain */
			/* grab the inode we just found */
E 72
			ncp->nc_ip = dp;
D 51
			dp->i_count++;
E 51
D 72

				/* fill in cache info */
E 72
I 72
			/* fill in cache info */
E 72
			ncp->nc_ino = pdp->i_number;	/* parents inum */
			ncp->nc_dev = pdp->i_dev;	/* & device */
			ncp->nc_idev = dp->i_dev;	/* our device */
I 51
			ncp->nc_id = dp->i_id;		/* identifier */
E 51
D 57
			ncp->nc_nlen = u.u_dent.d_namlen;
			bcopy(u.u_dent.d_name, ncp->nc_name, ncp->nc_nlen);
E 57
I 57
			ncp->nc_nlen = ndp->ni_dent.d_namlen;
D 72
			bcopy(ndp->ni_dent.d_name, ncp->nc_name, ncp->nc_nlen);
E 57

				/* link at end of lru chain */
E 72
I 72
			bcopy(ndp->ni_dent.d_name, ncp->nc_name,
			    (unsigned)ncp->nc_nlen);
			/* link at end of lru chain */
E 72
			ncp->nc_nxt = NULL;
			ncp->nc_prev = nchtail;
			*nchtail = ncp;
			nchtail = &ncp->nc_nxt;
D 72

				/* and insert on hash chain */
E 72
I 72
			/* and insert on hash chain */
E 72
			insque(ncp, nhp);
E 85
		}
I 85
D 90
		if (ndp->ni_pathlen == 1) {
E 90
I 90
		if (ndp->ni_pathlen > 1) {
			bcopy(ndp->ni_next, cp + linklen, ndp->ni_pathlen);
E 90
D 88
			bcopy(ndp->ni_next, cp + linklen, ndp->ni_pathlen);
E 88
			FREE(ndp->ni_pnbuf, M_NAMEI);
			ndp->ni_pnbuf = cp;
D 88
		} else
E 88
D 90
			ndp->ni_pnbuf[linklen] = '\0';
E 90
I 88
		} else
D 90
			bcopy(ndp->ni_next, cp + linklen, ndp->ni_pathlen);
E 90
I 90
			ndp->ni_pnbuf[linklen] = '\0';
E 90
E 88
		ndp->ni_ptr = cp;
D 94
		ndp->ni_pathlen += linklen;
E 94
		vput(dp);
		dp = ndp->ni_dvp;
I 88
D 94
		if (lockparent && *ndp->ni_next == '\0')
E 94
I 94
		if (lockparent && ndp->ni_pathlen == 1)
E 94
			VOP_UNLOCK(dp);
I 94
		ndp->ni_pathlen += linklen;
E 94
E 88
		goto start;
E 108
I 108
		ndp->ni_more = 1;
		return (0);
E 114
I 114
	    ((cnp->cn_flags & FOLLOW) || *ndp->ni_next == '/')) {
		cnp->cn_flags |= ISSYMLINK;
D 115
		RETURN (0);
E 115
I 115
		return (0);
E 115
E 114
E 108
E 85
	}

D 85
haveino:
E 48
E 41
	fs = dp->i_fs;

E 85
	/*
E 141
D 85
	 * Check for symbolic link
E 85
I 85
	 * Check to see if the vnode has been mounted on;
	 * if so find the root of the mounted file system.
E 85
	 */
D 57
	if ((dp->i_mode & IFMT) == IFLNK && (follow || *cp == '/')) {
E 57
I 57
D 85
	if ((dp->i_mode & IFMT) == IFLNK &&
	    ((ndp->ni_nameiop & FOLLOW) || *cp == '/')) {
E 57
D 27
		int pathlen = strlen(cp) + 1;
		int bn;
E 27
I 27
		u_int pathlen = strlen(cp) + 1;
E 27

D 69
		if (dp->i_size + pathlen >= MAXPATHLEN - 1 ||
		    ++nlink > MAXSYMLINKS) {
E 69
I 69
		if (dp->i_size + pathlen >= MAXPATHLEN - 1) {
			u.u_error = ENAMETOOLONG;
			goto bad2;
E 85
I 85
D 116
mntloop:
E 116
D 98
	while (dp->v_type == VDIR && (mp = dp->v_mountedhere)) {
E 98
I 98
	while (dp->v_type == VDIR && (mp = dp->v_mountedhere) &&
D 114
	       (ndp->ni_nameiop & NOCROSSMOUNT) == 0) {
E 114
I 114
	       (cnp->cn_flags & NOCROSSMOUNT) == 0) {
E 114
E 98
D 99
		while(mp->m_flag & M_MLOCK) {
			mp->m_flag |= M_MWAIT;
E 99
I 99
D 112
		while(mp->mnt_flag & MNT_MLOCK) {
E 112
I 112
D 144
		if (mp->mnt_flag & MNT_MLOCK) {
E 112
			mp->mnt_flag |= MNT_MWAIT;
E 99
			sleep((caddr_t)mp, PVFS);
E 144
I 144
		if (vfs_busy(mp, 0, 0, p))
E 144
D 116
			goto mntloop;
E 116
I 116
			continue;
E 116
E 85
D 144
		}
D 85
		if (++nlink > MAXSYMLINKS) {
E 69
			u.u_error = ELOOP;
E 85
I 85
D 108
		error = VFS_ROOT(dp->v_mountedhere, &tdp);
		if (error)
E 108
I 108
		if (error = VFS_ROOT(dp->v_mountedhere, &tdp))
E 144
I 144
		error = VFS_ROOT(mp, &tdp);
		vfs_unbusy(mp, p);
		if (error)
E 144
E 108
E 85
			goto bad2;
D 85
		}
D 33
		bcopy(cp, nbp->b_un.b_addr + dp->i_size, pathlen);
E 33
I 33
D 81
		ovbcopy(cp, nbp->b_un.b_addr + dp->i_size, pathlen);
E 81
I 81
		ovbcopy(cp, nbp + dp->i_size, pathlen);
E 81
E 33
D 26
		u.u_segflg = 1;
		u.u_base = nbp->b_un.b_addr;
		u.u_count = dp->i_size;
I 24
		u.u_offset = 0;
E 24
		readi(dp);
E 26
I 26
		u.u_error =
D 27
		    readip1(dp, nbp->b_un.b_addr, dp->i_size, 0, 1, 0);
E 27
I 27
D 34
		    rdwri(UIO_READ, dp, nbp->b_un.b_addr, dp->i_size,
E 34
I 34
D 81
		    rdwri(UIO_READ, dp, nbp->b_un.b_addr, (int)dp->i_size,
E 81
I 81
		    rdwri(UIO_READ, dp, nbp, (int)dp->i_size,
E 81
E 34
D 75
			0, 1, (int *)0);
E 75
I 75
			(off_t)0, 1, (int *)0);
E 75
E 27
E 26
		if (u.u_error)
			goto bad2;
D 81
		cp = nbp->b_un.b_addr;
E 81
I 81
		cp = nbp;
E 81
		iput(dp);
E 23
E 20
E 14
D 2
	}
E 2
I 2
D 13
		ep = (struct direct *)bp->b_un.b_addr;
	} else
		ep++;
E 2

	/*
	 * Note first empty directory slot
	 * in eo for possible creat.
	 * String compare the directory entry
	 * and the current component.
	 * If they do not match, go back to eloop.
	 */

D 2
	bcopy(bp->b_un.b_addr+(u.u_offset&BMASK), (caddr_t)&u.u_dent,
		sizeof(struct direct));
E 2
	u.u_offset += sizeof(struct direct);
D 2
	if(u.u_dent.d_ino == 0) {
E 2
I 2
D 12
	if(ep->d_ino == 0) {
E 2
		if(eo == 0)
E 12
I 12
	if (ep->d_ino == 0) {
		if (eo == 0)
E 12
			eo = u.u_offset;
		goto eloop;
E 13
I 13
		if (*cp == '/') {
I 23
			irele(pdp);
E 23
			while (*cp == '/')
				cp++;
D 23
			goto dirloop;
E 23
I 23
			if ((dp = u.u_rdir) == NULL)
				dp = rootdir;
D 55
			ilock(dp);
E 55
I 55
			ILOCK(dp);
E 55
			dp->i_count++;
		} else {
			dp = pdp;
D 55
			ilock(dp);
E 55
I 55
			ILOCK(dp);
E 55
E 23
		}
D 19
		goto out1;
E 19
I 19
D 23
		/*
		 * End of path, so return name matched.
		 */
		u.u_offset -= ep->d_reclen;
		u.u_count = newsize;
		brelse(nbp);
		return (dp);
E 23
I 23
		fs = dp->i_fs;
		goto dirloop;
E 85
I 85
		vput(dp);
		ndp->ni_vp = dp = tdp;
I 141
	}

	/*
	 * Check for symbolic link
	 */
	if ((dp->v_type == VLNK) &&
	    ((cnp->cn_flags & FOLLOW) || *ndp->ni_next == '/')) {
		cnp->cn_flags |= ISSYMLINK;
		return (0);
E 141
E 85
E 23
E 19
E 13
	}
I 23
D 34
	irele(pdp);
E 34

I 85
nextname:
E 85
E 23
D 13
	for(i=0; i<DIRSIZ; i++) {
D 2
		if(u.u_dbuf[i] != u.u_dent.d_name[i])
E 2
I 2
D 12
		if(u.u_dbuf[i] != ep->d_name[i])
E 12
I 12
		if (u.u_dbuf[i] != ep->d_name[i])
E 12
E 2
			goto eloop;
D 12
		if(u.u_dbuf[i] == 0)
E 12
I 12
		if (u.u_dbuf[i] == 0)
E 12
			break;
	}

E 13
	/*
D 13
	 * Here a component matched in a directory.
	 * If there is more pathname, go back to
	 * cloop, otherwise return.
E 13
I 13
D 23
	 * Search failed.
I 19
	 * Report what is appropriate as per flag.
E 23
I 23
	 * Not a symbolic link.  If more pathname,
	 * continue at next component, else return.
E 23
E 19
E 13
	 */
D 2

E 2
I 2
D 13
	bcopy((caddr_t)ep, (caddr_t)&u.u_dent, sizeof(struct direct));
E 13
E 2
D 12
	if(bp != NULL)
E 12
I 12
D 23
	if (bp != NULL)
E 12
		brelse(bp);
D 12
	if(flag==2 && c=='\0') {
		if(access(dp, IWRITE))
E 12
I 12
D 13
	if (flag==2 && c=='\0') {
E 13
I 13
D 19
	if (flag==1 && *cp=='\0' && dp->i_nlink) {
E 13
		if (access(dp, IWRITE))
E 12
			goto out;
D 13
		return(dp);
E 13
I 13
D 14
		u.u_pdir = dp;
E 14
		if (eo>=0)
			u.u_offset = eo;
E 19
I 19
	if (flag == 1 && *cp == '\0' && dp->i_nlink != 0) {
		brelse(nbp);
		if (access(dp, IWRITE)) {
			iput(dp);
			return (NULL);
		}
		if (slot == NONE) {
			u.u_count = 0;
		} else {
			u.u_offset = entryfree;
			u.u_count = entrysize;
		}
E 19
		dp->i_flag |= IUPD|ICHG;
D 19
		dp = NULL;
		goto out1;
E 19
I 19
		return (NULL);
E 23
I 23
D 85
	if (*cp == '/') {
		while (*cp == '/')
			cp++;
I 34
		irele(pdp);
E 85
I 85
D 108
	ndp->ni_ptr = ndp->ni_next;
	if (*ndp->ni_ptr == '/') {
E 108
I 108
	if (*ndp->ni_next == '/') {
D 114
		ndp->ni_ptr = ndp->ni_next;
E 108
		while (*ndp->ni_ptr == '/') {
			ndp->ni_ptr++;
E 114
I 114
		cnp->cn_nameptr = ndp->ni_next;
		while (*cnp->cn_nameptr == '/') {
			cnp->cn_nameptr++;
E 114
			ndp->ni_pathlen--;
		}
		vrele(ndp->ni_dvp);
E 85
E 34
		goto dirloop;
E 23
E 19
E 13
	}
D 13
	d = dp->i_dev;
D 12
	if(u.u_dent.d_ino == ROOTINO)
	if(dp->i_number == ROOTINO)
	if(u.u_dent.d_name[1] == '.')
E 12
I 12
	if (u.u_dent.d_ino == ROOTINO)
	if (dp->i_number == ROOTINO)
	if (u.u_dent.d_name[1] == '.')
E 12
		for(i=1; i<NMOUNT; i++)
D 12
			if(mount[i].m_bufp != NULL)
			if(mount[i].m_dev == d) {
E 12
I 12
			if (mount[i].m_bufp != NULL)
			if (mount[i].m_dev == d) {
E 12
				iput(dp);
				dp = mount[i].m_inodp;
				dp->i_count++;
D 12
				plock(dp);
E 12
I 12
				ilock(dp);
E 12
				goto seloop;
			}
	iput(dp);
	dp = iget(d, u.u_dent.d_ino);
D 12
	if(dp == NULL)
E 12
I 12
	if (dp == NULL)
E 12
		return(NULL);
	goto cloop;

E 13
I 13
D 23
	u.u_error = ENOENT;
E 13
D 19
out:
E 19
	iput(dp);
E 23
D 13
	return(NULL);
E 13
I 13
D 19
	dp = NULL;
out1:
E 19
D 56
	brelse(nbp);
E 56
I 56
D 81
	nbp->av_forw = freenamebuf;
	freenamebuf = nbp;
E 81
I 81
D 85
	FREE(nbp, M_NAMEI);
E 81
E 56
I 34
	if (lockparent)
D 57
		u.u_pdir = pdp;
E 57
I 57
		ndp->ni_pdir = pdp;
E 57
	else
		irele(pdp);
E 34
I 23
	return (dp);
bad2:
	irele(pdp);
bad:
	if (bp)
		brelse(bp);
	if (dp)
		iput(dp);
D 56
	brelse(nbp);
E 56
I 56
D 81
	nbp->av_forw = freenamebuf;
	freenamebuf = nbp;
E 81
I 81
	FREE(nbp, M_NAMEI);
E 81
E 56
E 23
D 19
	return (dp);
E 19
I 19
	return (NULL);
E 19
E 13
}

I 48

E 48
I 23
D 57
dirbad(ip, how)
E 57
I 57
dirbad(ip, offset, how)
E 57
	struct inode *ip;
I 57
	off_t offset;
E 57
	char *how;
{

	printf("%s: bad dir ino %d at offset %d: %s\n",
D 57
	    ip->i_fs->fs_fsmnt, ip->i_number, u.u_offset, how);
E 57
I 57
	    ip->i_fs->fs_fsmnt, ip->i_number, offset, how);
E 57
}

D 52
dirbadname(ep)
E 52
I 52
/*
 * Do consistency checking on a directory entry:
 *	record length must be multiple of 4
D 72
 *	record length must not be non-negative
E 72
 *	entry must fit in rest of its DIRBLKSIZ block
 *	record must be large enough to contain entry
 *	name is not longer than MAXNAMLEN
 *	name must be as long as advertised, and null terminated
 */
dirbadentry(ep, entryoffsetinblock)
E 52
	register struct direct *ep;
I 52
	int entryoffsetinblock;
E 52
{
D 27
	register char *cp;
E 27
	register int i;

I 52
D 72
	if ((ep->d_reclen & 0x3) != 0 || ep->d_reclen <= 0 ||
E 72
I 72
	if ((ep->d_reclen & 0x3) != 0 ||
E 72
	    ep->d_reclen > DIRBLKSIZ - (entryoffsetinblock & (DIRBLKSIZ - 1)) ||
	    ep->d_reclen < DIRSIZ(ep) || ep->d_namlen > MAXNAMLEN)
		return (1);
E 52
	for (i = 0; i < ep->d_namlen; i++)
D 57
		if (ep->d_name[i] == 0)
E 57
I 57
		if (ep->d_name[i] == '\0')
E 57
			return (1);
	return (ep->d_name[i]);
}

E 23
/*
D 24
 * Return the next character from the
 * kernel string pointed at by dirp.
 */
schar()
{

D 13
	return(*u.u_dirp++ & 0377);
E 13
I 13
	return (*u.u_dirp++ & 0377);
E 13
}

/*
 * Return the next character from the
 * user string pointed at by dirp.
 */
uchar()
{
	register c;

	c = fubyte(u.u_dirp++);
D 12
	if(c == -1)
E 12
I 12
D 13
	if (c == -1)
E 13
I 13
	if (c == -1) {
E 13
E 12
		u.u_error = EFAULT;
D 13
	return(c);
E 13
I 13
		c = 0;
	}
	return (c);
E 13
}
I 13

D 23
#ifndef vax
D 19
strncmp(s1, s2, len)
E 19
I 19
bcmp(s1, s2, len)
E 19
	register char *s1, *s2;
D 19
	register len;
E 19
I 19
	register int len;
E 23
I 23
/*
E 24
 * Write a directory entry after a call to namei, using the parameters
 * which it left in the u. area.  The argument ip is the inode which
D 57
 * the new directory entry will refer to.  The u. area field u.u_pdir is
E 57
I 57
 * the new directory entry will refer to.  The u. area field ndp->ni_pdir is
E 57
 * a pointer to the directory to be written, which was left locked by
D 57
 * namei.  Remaining parameters (u.u_offset, u.u_count) indicate
E 57
I 57
 * namei.  Remaining parameters (ndp->ni_offset, ndp->ni_count) indicate
E 57
 * how the space for the new entry is to be gotten.
 */
D 57
direnter(ip)
E 57
I 57
direnter(ip, ndp)
E 57
	struct inode *ip;
I 57
	register struct nameidata *ndp;
E 57
E 23
E 19
{
I 23
	register struct direct *ep, *nep;
I 63
	register struct inode *dp = ndp->ni_pdir;
E 63
D 27
	struct fs *fs;
E 27
	struct buf *bp;
D 27
	int loc, dsize, freespace, newentrysize;
E 27
I 27
D 39
	int loc, freespace;
E 39
I 39
D 40
	int loc, freespace, error = 0;
E 40
I 40
	int loc, spacefree, error = 0;
E 40
E 39
D 30
	u_int dsize, newentrysize;
E 30
I 30
	u_int dsize;
	int newentrysize;
E 30
E 27
	char *dirbuf;
E 23

D 19
	do {
		if (*s1 != *s2++)
E 19
I 19
D 23
	while (--len)
		if (*s1++ != *s2++)
E 19
			return (1);
D 19
		if (*s1++ == '\0')
			return (0);
	} while (--len);
E 19
	return (0);
E 23
I 23
D 57
	u.u_dent.d_ino = ip->i_number;
	u.u_segflg = 1;
	newentrysize = DIRSIZ(&u.u_dent);
	if (u.u_count == 0) {
E 57
I 57
	ndp->ni_dent.d_ino = ip->i_number;
	newentrysize = DIRSIZ(&ndp->ni_dent);
	if (ndp->ni_count == 0) {
E 57
		/*
D 57
		 * If u.u_count is 0, then namei could find no space in the
		 * directory.  In this case u.u_offset will be on a directory
E 57
I 57
		 * If ndp->ni_count is 0, then namei could find no space in the
		 * directory. In this case ndp->ni_offset will be on a directory
E 57
		 * block boundary and we will write the new entry into a fresh
		 * block.
		 */
D 57
		if (u.u_offset&(DIRBLKSIZ-1))
E 57
I 57
		if (ndp->ni_offset&(DIRBLKSIZ-1))
E 57
			panic("wdir: newblk");
D 57
		u.u_dent.d_reclen = DIRBLKSIZ;
D 27
		u.u_count = newentrysize;
		u.u_base = (caddr_t)&u.u_dent;
		u.u_segflg = 1;
		writei(u.u_pdir);
E 27
I 27
D 30
		(void) rdwri(UIO_WRITE, u.u_pdir, (caddr_t)&u.u_dent, newentrysize,
		    u.u_offset, 1, (int *)0);
E 30
I 30
D 39
		(void) rdwri(UIO_WRITE, u.u_pdir, (caddr_t)&u.u_dent,
E 39
I 39
		error = rdwri(UIO_WRITE, u.u_pdir, (caddr_t)&u.u_dent,
E 39
		    newentrysize, u.u_offset, 1, (int *)0);
E 30
E 27
		iput(u.u_pdir);
E 57
I 57
		ndp->ni_dent.d_reclen = DIRBLKSIZ;
D 63
		error = rdwri(UIO_WRITE, ndp->ni_pdir, (caddr_t)&ndp->ni_dent,
E 63
I 63
		error = rdwri(UIO_WRITE, dp, (caddr_t)&ndp->ni_dent,
E 63
		    newentrysize, ndp->ni_offset, 1, (int *)0);
I 65
		if (DIRBLKSIZ > dp->i_fs->fs_fsize)
			panic("wdir: blksize"); /* XXX - should grow w/bmap() */
		else
			dp->i_size = roundup(dp->i_size, DIRBLKSIZ);
E 65
D 63
		iput(ndp->ni_pdir);
E 63
I 63
		iput(dp);
E 63
E 57
D 39
		return;
E 39
I 39
		return (error);
E 39
	}

E 85
	/*
D 57
	 * If u.u_count is non-zero, then namei found space for the
	 * new entry in the range u.u_offset to u.u_offset+u.u_count.
E 57
I 57
D 85
	 * If ndp->ni_count is non-zero, then namei found space for the new
	 * entry in the range ndp->ni_offset to ndp->ni_offset + ndp->ni_count.
E 57
	 * in the directory.  To use this space, we may have to compact
	 * the entries located there, by copying them together towards
	 * the beginning of the block, leaving the free space in
	 * one usable chunk at the end.
E 85
I 85
D 95
	 * Check for read-only file systems and executing texts
E 95
I 95
D 145
	 * Check for read-only file systems.
E 145
I 145
	 * Disallow directory write attempts on read-only file systems.
E 145
E 95
E 85
	 */
I 85
D 91
	if (flag != LOOKUP && (error = vn_access(dp, VWRITE, ndp->ni_cred)))
		goto bad2;
E 91
I 91
D 95
	if (flag != LOOKUP) {
E 95
I 95
D 114
	if (flag == DELETE || flag == RENAME) {
E 114
I 114
D 145
	if (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME) {
E 114
E 95
		/*
D 95
		 * Disallow write attempts on read-only file systems;
		 * unless the file is a socket or a block or character
		 * device resident on the file system.
E 95
I 95
		 * Disallow directory write attempts on read-only
		 * file systems.
E 95
		 */
D 95
		if ((dp->v_mount->m_flag & M_RDONLY) &&
		    dp->v_type != VCHR &&
		    dp->v_type != VBLK &&
		    dp->v_type != VSOCK) {
			error = EROFS;
			goto bad2;
		}
		/*
		 * If there's shared text associated with
		 * the inode, try to free it up once.  If
		 * we fail, we can't allow writing.
		 */
		if (dp->v_flag & VTEXT)
			xrele(dp);
		if (dp->v_flag & VTEXT) {
			error = ETXTBSY;
			goto bad2;
		}
		if (wantparent && flag != CREATE &&
		    (ndp->ni_dvp->v_mount->m_flag & M_RDONLY)) {
E 95
I 95
D 98
		if ((dp->v_mount->m_flag & M_RDONLY) ||
		    (wantparent && (ndp->ni_dvp->v_mount->m_flag & M_RDONLY))) {
E 98
I 98
D 99
		if ((dp->v_mount->m_flag & rdonly) ||
		    (wantparent && (ndp->ni_dvp->v_mount->m_flag & rdonly))) {
E 99
I 99
D 113
		if ((dp->v_mount->mnt_flag & rdonly) ||
		    (wantparent && (ndp->ni_dvp->v_mount->mnt_flag & rdonly))) {
E 113
I 113
		if (rdonly || (dp->v_mount->mnt_flag & MNT_RDONLY) ||
		    (wantparent &&
		     (ndp->ni_dvp->v_mount->mnt_flag & MNT_RDONLY))) {
E 113
E 99
E 98
E 95
			error = EROFS;
			goto bad2;
		}
E 145
I 145
	if (rdonly &&
	    (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME)) {
		error = EROFS;
		goto bad2;
E 145
	}
I 108
D 114
	if (ndp->ni_nameiop & SAVESTART) {
E 114
I 114
	if (cnp->cn_flags & SAVESTART) {
E 114
		ndp->ni_startdir = ndp->ni_dvp;
I 110
		p->p_spare[1]++;
E 110
		VREF(ndp->ni_startdir);
	}
E 108
E 91
	if (!wantparent)
		vrele(ndp->ni_dvp);
D 114
	if ((ndp->ni_nameiop & LOCKLEAF) == 0)
E 114
I 114
	if ((cnp->cn_flags & LOCKLEAF) == 0)
E 114
D 143
		VOP_UNLOCK(dp);
E 143
I 143
		VOP_UNLOCK(dp, 0, p);
E 143
D 98
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 98
I 98
D 108
	if (getbuf)
		FREE(ndp->ni_pnbuf, M_NAMEI);
E 108
E 98
D 114
	return (0);
E 114
I 114
D 115
	RETURN (0);
E 115
I 115
	return (0);
E 115
E 114
E 85

D 85
	/*
	 * Increase size of directory if entry eats into new space.
	 * This should never push the size past a new multiple of
	 * DIRBLKSIZE.
I 65
	 *
	 * N.B. - THIS IS AN ARTIFACT OF 4.2 AND SHOULD NEVER HAPPEN.
E 65
	 */
D 30
	if (u.u_offset+u.u_count > u.u_pdir->i_size) {
D 24
		if (((u.u_offset+u.u_count-1)&~(DIRBLKSIZ-1)) !=
		    ((u.u_pdir->i_size-1)&~(DIRBLKSIZ-1))) {
printf("wdir i_size dir %s/%d (of=%d,cnt=%d,psz=%d))\n",
u.u_pdir->i_fs->fs_fsmnt,u.u_pdir->i_number,u.u_offset,
u.u_count,u.u_pdir->i_size);
			panic("wdir: span");
		}
E 24
I 24
/*ZZ*/		if (((u.u_offset+u.u_count-1)&~(DIRBLKSIZ-1)) !=
/*ZZ*/		    ((u.u_pdir->i_size-1)&~(DIRBLKSIZ-1))) {
/*ZZ*/			panic("wdir: span");
/*ZZ*/		}
E 30
I 30
D 34
	if (u.u_offset+u.u_count > u.u_pdir->i_size)
E 34
I 34
D 57
	if (u.u_offset + u.u_count > u.u_pdir->i_size)
E 34
E 30
E 24
		u.u_pdir->i_size = u.u_offset + u.u_count;
E 57
I 57
D 63
	if (ndp->ni_offset + ndp->ni_count > ndp->ni_pdir->i_size)
		ndp->ni_pdir->i_size = ndp->ni_offset + ndp->ni_count;
E 63
I 63
	if (ndp->ni_offset + ndp->ni_count > dp->i_size)
		dp->i_size = ndp->ni_offset + ndp->ni_count;
E 63
E 57
D 30
	}
E 30
D 72

E 72
	/*
	 * Get the block containing the space for the new directory
D 39
	 * entry.
E 39
I 39
	 * entry.  Should return error by result instead of u.u_error.
E 39
	 */
D 24
	bp = batoffset(u.u_pdir, u.u_offset, (char **)&dirbuf);
E 24
I 24
D 57
	bp = blkatoff(u.u_pdir, u.u_offset, (char **)&dirbuf);
E 57
I 57
D 63
	bp = blkatoff(ndp->ni_pdir, ndp->ni_offset, (char **)&dirbuf);
E 63
I 63
	bp = blkatoff(dp, ndp->ni_offset, (char **)&dirbuf);
E 63
E 57
E 24
D 34
	if (bp == 0)
E 34
I 34
	if (bp == 0) {
D 57
		iput(u.u_pdir);
E 57
I 57
D 63
		iput(ndp->ni_pdir);
E 63
I 63
		iput(dp);
E 63
E 57
E 34
D 39
		return;
E 39
I 39
		return (u.u_error);
E 39
I 34
	}
E 34
D 24
printf("direnter u.u_offset %d u.u_count %d, bpaddr %x, dirbuf %x\n",
    u.u_offset, u.u_count, bp->b_un.b_addr, dirbuf);
E 24
D 72

E 72
	/*
	 * Find space for the new entry.  In the simple case, the
	 * entry at offset base will have the space.  If it does
	 * not, then namei arranged that compacting the region
D 57
	 * u.u_offset to u.u_offset+u.u_count would yield the space.
E 57
I 57
	 * ndp->ni_offset to ndp->ni_offset+ndp->ni_count would yield the space.
E 57
	 */
	ep = (struct direct *)dirbuf;
	dsize = DIRSIZ(ep);
D 40
	freespace = ep->d_reclen - dsize;
E 40
I 40
	spacefree = ep->d_reclen - dsize;
E 40
D 57
	for (loc = ep->d_reclen; loc < u.u_count; ) {
E 57
I 57
	for (loc = ep->d_reclen; loc < ndp->ni_count; ) {
E 57
		nep = (struct direct *)(dirbuf + loc);
		if (ep->d_ino) {
			/* trim the existing slot */
			ep->d_reclen = dsize;
			ep = (struct direct *)((char *)ep + dsize);
		} else {
			/* overwrite; nothing there; header is ours */
D 40
			freespace += dsize;	
E 40
I 40
			spacefree += dsize;	
E 40
		}
		dsize = DIRSIZ(nep);
D 40
		freespace += nep->d_reclen - dsize;
E 40
I 40
		spacefree += nep->d_reclen - dsize;
E 40
		loc += nep->d_reclen;
D 30
/*ZZ*/if((loc&~0x1ff)!=(loc+nep->d_reclen-1&~0x1ff))
/*ZZ*/printf("wdir: compact loc %d reclen %d (dir %s/%d)\n",loc,nep->d_reclen,
/*ZZ*/u.u_pdir->i_fs->fs_fsmnt,u.u_pdir->i_number);
E 30
D 27
		bcopy(nep, ep, dsize);
E 27
I 27
		bcopy((caddr_t)nep, (caddr_t)ep, dsize);
E 27
	}
	/*
	 * Update the pointer fields in the previous entry (if any),
	 * copy in the new entry, and write out the block.
	 */
	if (ep->d_ino == 0) {
D 40
		if (freespace + dsize < newentrysize)
E 40
I 40
		if (spacefree + dsize < newentrysize)
E 40
			panic("wdir: compact1");
D 30
/*ZZ*/if(freespace+dsize>512)panic("wdir: compact screwup");
E 30
D 40
		u.u_dent.d_reclen = freespace + dsize;
E 40
I 40
D 57
		u.u_dent.d_reclen = spacefree + dsize;
E 57
I 57
		ndp->ni_dent.d_reclen = spacefree + dsize;
E 57
E 40
	} else {
D 40
		if (freespace < newentrysize)
E 40
I 40
		if (spacefree < newentrysize)
E 40
			panic("wdir: compact2");
D 40
		u.u_dent.d_reclen = freespace;
E 40
I 40
D 57
		u.u_dent.d_reclen = spacefree;
E 57
I 57
		ndp->ni_dent.d_reclen = spacefree;
E 57
E 40
D 29
/*ZZ*/if ((((char *)ep-bp->b_un.b_addr)&0x1ff)+dsize>512) panic("wdir: reclen");
E 29
		ep->d_reclen = dsize;
		ep = (struct direct *)((char *)ep + dsize);
	}
D 29
/*ZZ*/if((((char*)ep-bp->b_un.b_addr)&0x1ff)+u.u_dent.d_reclen>512)panic("wdir: botch");
	bcopy(&u.u_dent, ep, newentrysize);
E 29
I 29
D 32
	bcopy((caddr_t)&u.u_dent, (caddr_t)ep, newentrysize);
E 32
I 32
D 57
	bcopy((caddr_t)&u.u_dent, (caddr_t)ep, (u_int)newentrysize);
E 57
I 57
	bcopy((caddr_t)&ndp->ni_dent, (caddr_t)ep, (u_int)newentrysize);
E 57
E 32
E 29
	bwrite(bp);
D 57
	u.u_pdir->i_flag |= IUPD|ICHG;
	iput(u.u_pdir);
E 57
I 57
D 63
	ndp->ni_pdir->i_flag |= IUPD|ICHG;
	iput(ndp->ni_pdir);
E 63
I 63
	dp->i_flag |= IUPD|ICHG;
	if (ndp->ni_endoff && ndp->ni_endoff < dp->i_size)
D 72
		itrunc(dp, ndp->ni_endoff);
E 72
I 72
		itrunc(dp, (u_long)ndp->ni_endoff);
E 72
	iput(dp);
E 85
I 85
bad2:
I 88
D 108
	if (lockparent && *ndp->ni_next == '\0')
E 108
I 108
D 114
	if ((ndp->ni_nameiop & LOCKPARENT) && *ndp->ni_next == '\0')
E 114
I 114
	if ((cnp->cn_flags & LOCKPARENT) && *ndp->ni_next == '\0')
E 114
E 108
D 143
		VOP_UNLOCK(ndp->ni_dvp);
E 143
I 143
		VOP_UNLOCK(ndp->ni_dvp, 0, p);
E 143
E 88
	vrele(ndp->ni_dvp);
bad:
	vput(dp);
	ndp->ni_vp = NULL;
D 98
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 98
I 98
D 108
	if (getbuf)
		FREE(ndp->ni_pnbuf, M_NAMEI);
E 108
E 98
E 85
E 63
E 57
I 39
D 114
	return (error);
E 114
I 114
D 115
	RETURN (error);

#ifdef COMPAT_HACK
 byebye:
	/*
	 * Put flags back into ni_nameiop and bail.
	 */
	if (cnp->cn_nameiop & ~OPMASK)
		panic ("lookup: nameiop is contaminated with flags.");
	ndp->ni_nameiop = (cnp->cn_nameiop & OPMASK) |
		(cnp->cn_flags & ~OPMASK);
	return (returncode);
#endif
E 115
I 115
	return (error);
E 115
E 114
E 39
E 23
I 19
D 85
}

I 34
/*
 * Remove a directory entry after a call to namei, using the
 * parameters which it left in the u. area.  The u. entry
D 57
 * u_offset contains the offset into the directory of the
 * entry to be eliminated.  The u_count field contains the
E 57
I 57
 * ni_offset contains the offset into the directory of the
 * entry to be eliminated.  The ni_count field contains the
E 57
 * size of the previous record in the directory.  If this
 * is 0, the first entry is being deleted, so we need only
 * zero the inode number to mark the entry as free.  If the
 * entry isn't the first in the directory, we must reclaim
 * the space of the now empty record by adding the record size
 * to the size of the previous entry.
 */
E 34
D 23
strlen(s1)
	register char *s1;
E 23
I 23
D 57
dirremove()
E 57
I 57
dirremove(ndp)
	register struct nameidata *ndp;
E 57
E 23
{
D 23
	register int len;
E 23
I 23
D 57
	register struct inode *dp = u.u_pdir;
E 57
I 57
	register struct inode *dp = ndp->ni_pdir;
E 57
D 27
	register struct fs *fs = dp->i_fs;
E 27
	register struct buf *bp;
	struct direct *ep;
E 23

D 23
	for (len = 0; *s1++ != '\0'; len++)
		/* void */;
	return (len);
E 23
I 23
D 24
printf("dirremove u.u_offset %d u.u_count %d\n", u.u_offset, u.u_count);
E 24
D 34
	if (u.u_count == 0) {
E 34
I 34
D 35
	if (u.u_count == 0)
E 35
I 35
D 57
	if (u.u_count == 0) {
E 57
I 57
	if (ndp->ni_count == 0) {
E 57
E 35
E 34
		/*
		 * First entry in block: set d_ino to zero.
		 */
I 35
D 57
		u.u_dent.d_ino = 0;
E 35
D 29
/*ZZ*/if(u.u_offset&0x1ff)printf("missed dir compact dir %s/%d off %d file %s\n"
/*ZZ*/,dp->i_fs->fs_fsmnt,dp->i_number,u.u_offset,u.u_dent.d_name);
E 29
D 27
		u.u_base = (caddr_t)&u.u_dent;
		u.u_count = DIRSIZ(&u.u_dent);
I 24
		u.u_segflg = 1;
E 27
E 24
D 34
		u.u_dent.d_ino = 0;
E 34
D 27
		writei(dp);
E 27
I 27
D 29
		(void) rdwri(UIO_WRITE, dp, (caddr_t)&u.u_dent, DIRSIZ(&u.u_dent),
		    u.u_offset, 1, (int *)0);
E 29
I 29
		(void) rdwri(UIO_WRITE, dp, (caddr_t)&u.u_dent,
D 30
		    DIRSIZ(&u.u_dent), u.u_offset, 1, (int *)0);
E 30
I 30
		    (int)DIRSIZ(&u.u_dent), u.u_offset, 1, (int *)0);
E 57
I 57
		ndp->ni_dent.d_ino = 0;
		(void) rdwri(UIO_WRITE, dp, (caddr_t)&ndp->ni_dent,
		    (int)DIRSIZ(&ndp->ni_dent), ndp->ni_offset, 1, (int *)0);
E 57
E 30
E 29
E 27
D 34
	} else {
E 34
I 34
D 35
	else {
E 35
I 35
	} else {
E 35
E 34
		/*
		 * Collapse new free space into previous entry.
		 */
I 36
D 37
		u.u_error = 0;	/* XXX */
E 37
E 36
D 24
		bp = batoffset(dp, u.u_offset - u.u_count, (char **)&ep);
E 24
I 24
D 27
		bp = blkatoff(dp, u.u_offset - u.u_count, (char **)&ep);
E 27
I 27
D 57
		bp = blkatoff(dp, (int)(u.u_offset - u.u_count), (char **)&ep);
E 57
I 57
D 75
		bp = blkatoff(dp, (int)(ndp->ni_offset - ndp->ni_count),
			(char **)&ep);
E 75
I 75
		bp = blkatoff(dp, ndp->ni_offset - ndp->ni_count, (char **)&ep);
E 75
E 57
E 27
E 24
		if (bp == 0)
			return (0);
D 57
		ep->d_reclen += u.u_dent.d_reclen;
E 57
I 57
		ep->d_reclen += ndp->ni_dent.d_reclen;
E 57
D 29
/*ZZ*/if((((char *)ep - bp->b_un.b_addr)&0x1ff)+u.u_dent.d_reclen > 512)
/*ZZ*/	panic("unlink: reclen");
E 29
		bwrite(bp);
		dp->i_flag |= IUPD|ICHG;
	}
	return (1);
E 23
E 19
}
D 23
#endif
E 23
I 23

I 24
/*
I 34
 * Rewrite an existing directory entry to point at the inode
 * supplied.  The parameters describing the directory entry are
 * set up by a call to namei.
 */
D 57
dirrewrite(dp, ip)
E 57
I 57
dirrewrite(dp, ip, ndp)
E 57
	struct inode *dp, *ip;
I 57
	struct nameidata *ndp;
E 57
{

D 57
	u.u_dent.d_ino = ip->i_number;
	u.u_error = rdwri(UIO_WRITE, dp, (caddr_t)&u.u_dent,
		(int)DIRSIZ(&u.u_dent), u.u_offset, 1, (int *)0);
E 57
I 57
	ndp->ni_dent.d_ino = ip->i_number;
	u.u_error = rdwri(UIO_WRITE, dp, (caddr_t)&ndp->ni_dent,
		(int)DIRSIZ(&ndp->ni_dent), ndp->ni_offset, 1, (int *)0);
E 57
	iput(dp);
}

/*
E 34
 * Return buffer with contents of block "offset"
 * from the beginning of directory "ip".  If "res"
 * is non-zero, fill it in with a pointer to the
 * remaining space in the directory.
 */
E 24
struct buf *
D 24
batoffset(ip, offset, res)
E 24
I 24
blkatoff(ip, offset, res)
E 24
	struct inode *ip;
	off_t offset;
	char **res;
{
	register struct fs *fs = ip->i_fs;
D 32
	int lbn = lblkno(fs, offset);
E 32
I 32
	daddr_t lbn = lblkno(fs, offset);
E 32
D 68
	int base = blkoff(fs, offset);
E 68
	int bsize = blksize(fs, ip, lbn);
D 32
	int bn = fsbtodb(fs, bmap(ip, lbn, B_WRITE, base, bsize));
E 32
I 32
D 68
	daddr_t bn = fsbtodb(fs, bmap(ip, lbn, B_WRITE, base, bsize));
E 68
E 32
	register struct buf *bp;
I 68
	daddr_t bn;
E 68

I 68
	bn = bmap(ip, lbn, B_READ, bsize);
E 68
	if (u.u_error)
		return (0);
D 68
	bp = bread(ip->i_dev, bn, bsize);
E 68
I 68
	if (bn == (daddr_t)-1) {
		dirbad(ip, offset, "hole in dir");
		return (0);
	}
I 79
#ifdef SECSIZE
	bp = bread(ip->i_dev, fsbtodb(fs, bn), bsize, fs->fs_dbsize);
#else SECSIZE
E 79
	bp = bread(ip->i_dev, fsbtodb(fs, bn), bsize);
I 79
#endif SECSIZE
E 79
E 68
	if (bp->b_flags & B_ERROR) {
		brelse(bp);
		return (0);
	}
	if (res)
D 68
		*res = bp->b_un.b_addr + base;
E 68
I 68
		*res = bp->b_un.b_addr + blkoff(fs, offset);
E 68
D 24
printf("b_addr %x res pointer %x\n", bp->b_un.b_addr, *res);
E 24
	return (bp);
I 34
}

/*
 * Check if a directory is empty or not.
 * Inode supplied must be locked.
I 44
 *
 * Using a struct dirtemplate here is not precisely
 * what we want, but better than using a struct direct.
 *
 * NB: does not handle corrupted directories.
E 44
 */
D 59
dirempty(ip)
E 59
I 59
dirempty(ip, parentino)
E 59
D 36
	struct inode *ip;
E 36
I 36
	register struct inode *ip;
I 59
	ino_t parentino;
E 59
E 36
{
	register off_t off;
D 44
	struct direct dbuf;
	register struct direct *dp = &dbuf;
E 44
I 44
	struct dirtemplate dbuf;
	register struct direct *dp = (struct direct *)&dbuf;
E 44
D 36
	int error;
E 36
I 36
	int error, count;
I 44
#define	MINDIRSIZ (sizeof (struct dirtemplate) / 2)
E 44
E 36

	for (off = 0; off < ip->i_size; off += dp->d_reclen) {
I 64
D 71
		if (dp->d_reclen <= 0)
			return (0);
E 71
E 64
D 44
		error = rdwri(UIO_READ, ip, (caddr_t)dp,
D 36
			sizeof (struct direct), off, 1, (int *)0);
		if (error)
E 36
I 36
			sizeof (struct direct), off, 1, &count);
		count = sizeof (struct direct) - count;
#define	MINDIRSIZ (sizeof (struct direct) - (MAXNAMLEN + 1))
		if (error || count < MINDIRSIZ || count < DIRSIZ(dp))
E 44
I 44
		error = rdwri(UIO_READ, ip, (caddr_t)dp, MINDIRSIZ,
		    off, 1, &count);
		/*
		 * Since we read MINDIRSIZ, residual must
		 * be 0 unless we're at end of file.
		 */
		if (error || count != 0)
I 71
			return (0);
		/* avoid infinite loops */
D 72
		if (dp->d_reclen <= 0)
E 72
I 72
		if (dp->d_reclen == 0)
E 72
E 71
E 44
E 36
			return (0);
I 44
		/* skip empty entries */
E 44
		if (dp->d_ino == 0)
			continue;
I 44
		/* accept only "." and ".." */
		if (dp->d_namlen > 2)
			return (0);
E 44
		if (dp->d_name[0] != '.')
			return (0);
D 44
		if (dp->d_namlen == 1 ||
		    (dp->d_namlen == 2 && dp->d_name[1] == '.'))
E 44
I 44
		/*
		 * At this point d_namlen must be 1 or 2.
		 * 1 implies ".", 2 implies ".." if second
		 * char is also "."
		 */
D 59
		if (dp->d_namlen == 1 || dp->d_name[1] == '.')
E 59
I 59
		if (dp->d_namlen == 1)
			continue;
		if (dp->d_name[1] == '.' && dp->d_ino == parentino)
E 59
E 44
			continue;
		return (0);
	}
	return (1);
E 34
}
I 43

/*
 * Check if source directory is in the path of the target directory.
 * Target is supplied locked, source is unlocked.
 * The target is always iput() before returning.
 */
checkpath(source, target)
	struct inode *source, *target;
{
	struct dirtemplate dirbuf;
	register struct inode *ip;
	int error = 0;

	ip = target;
	if (ip->i_number == source->i_number) {
		error = EEXIST;
		goto out;
	}
	if (ip->i_number == ROOTINO)
		goto out;

	for (;;) {
		if ((ip->i_mode&IFMT) != IFDIR) {
			error = ENOTDIR;
			break;
		}
		error = rdwri(UIO_READ, ip, (caddr_t)&dirbuf,
			sizeof (struct dirtemplate), (off_t)0, 1, (int *)0);
		if (error != 0)
			break;
		if (dirbuf.dotdot_namlen != 2 ||
D 53
		    bcmp(dirbuf.dotdot_name, "..", 3) != 0) {
E 53
I 53
		    dirbuf.dotdot_name[0] != '.' ||
		    dirbuf.dotdot_name[1] != '.') {
E 53
			error = ENOTDIR;
			break;
		}
		if (dirbuf.dotdot_ino == source->i_number) {
			error = EINVAL;
			break;
		}
		if (dirbuf.dotdot_ino == ROOTINO)
			break;
		iput(ip);
		ip = iget(ip->i_dev, ip->i_fs, dirbuf.dotdot_ino);
		if (ip == NULL) {
			error = u.u_error;
			break;
		}
	}

out:
	if (error == ENOTDIR)
		printf("checkpath: .. not a directory\n");
	if (ip != NULL)
		iput(ip);
	return (error);
I 48
}

/*
 * Name cache initialization, from main() when we are booting
 */
nchinit()
{
	register union nchash *nchp;
D 74
	register struct nch *ncp;
E 74
I 74
	register struct namecache *ncp;
E 74

	nchhead = 0;
	nchtail = &nchhead;
D 72

E 72
D 74
	for (ncp = nch; ncp < &nch[nchsize]; ncp++) {
E 74
I 74
	for (ncp = namecache; ncp < &namecache[nchsize]; ncp++) {
E 74
		ncp->nc_forw = ncp;			/* hash chain */
		ncp->nc_back = ncp;
D 72

E 72
		ncp->nc_nxt = NULL;			/* lru chain */
		*nchtail = ncp;
		ncp->nc_prev = nchtail;
		nchtail = &ncp->nc_nxt;
D 72

E 72
		/* all else is zero already */
	}
D 72

E 72
	for (nchp = nchash; nchp < &nchash[NCHHASH]; nchp++) {
		nchp->nch_head[0] = nchp;
		nchp->nch_head[1] = nchp;
	}
}

/*
 * Cache flush, called when filesys is umounted to
 * remove entries that would now be invalid
 *
 * The line "nxtcp = nchhead" near the end is to avoid potential problems
 * if the cache lru chain is modified while we are dumping the
 * inode.  This makes the algorithm O(n^2), but do you think I care?
 */
nchinval(dev)
	register dev_t dev;
{
D 74
	register struct nch *ncp, *nxtcp;
E 74
I 74
	register struct namecache *ncp, *nxtcp;
E 74

	for (ncp = nchhead; ncp; ncp = nxtcp) {
		nxtcp = ncp->nc_nxt;
D 72

E 72
		if (ncp->nc_ip == NULL ||
		    (ncp->nc_idev != dev && ncp->nc_dev != dev))
			continue;
D 72

I 53
			/* free the resources we had */
E 72
I 72
		/* free the resources we had */
E 72
E 53
		ncp->nc_idev = NODEV;
		ncp->nc_dev = NODEV;
I 53
		ncp->nc_id = NULL;
E 53
		ncp->nc_ino = 0;
I 53
		ncp->nc_ip = NULL;
E 53
D 72

I 53

E 53
			/* remove the entry from its hash chain */
		remque(ncp);
			/* and make a dummy one */
		ncp->nc_forw = ncp;
E 72
I 72
		remque(ncp);		/* remove entry from its hash chain */
		ncp->nc_forw = ncp;	/* and make a dummy one */
E 72
		ncp->nc_back = ncp;
D 72

			/* delete this entry from LRU chain */
E 72
I 72
		/* delete this entry from LRU chain */
E 72
		*ncp->nc_prev = nxtcp;
		if (nxtcp)
			nxtcp->nc_prev = ncp->nc_prev;
		else
			nchtail = ncp->nc_prev;
D 53

			/* free the inode we had */
		irele(ncp->nc_ip);
		ncp->nc_ip = NULL;
E 53
D 72

			/* cause rescan of list, it may have altered */
E 72
I 72
		/* cause rescan of list, it may have altered */
E 72
		nxtcp = nchhead;
D 72
			/* put the now-free entry at head of LRU */
E 72
I 72
		/* put the now-free entry at head of LRU */
E 72
		ncp->nc_nxt = nxtcp;
		ncp->nc_prev = &nchhead;
		nxtcp->nc_prev = &ncp->nc_nxt;
		nchhead = ncp;
	}
E 48
}
I 62

/*
 * Name cache invalidation of all entries.
 */
cacheinvalall()
{
D 74
	register struct nch *ncp;
E 74
I 74
	register struct namecache *ncp;
E 74

D 72
	for (ncp = nch; ncp < &nch[nchsize]; ncp++) {
E 72
I 72
D 74
	for (ncp = nch; ncp < &nch[nchsize]; ncp++)
E 74
I 74
	for (ncp = namecache; ncp < &namecache[nchsize]; ncp++)
E 74
E 72
		ncp->nc_id = 0;
E 85
D 72
	}
E 72
}
I 114

I 142
/*
 * relookup - lookup a path name component
 *    Used by lookup to re-aquire things.
 */
int
relookup(dvp, vpp, cnp)
	struct vnode *dvp, **vpp;
	struct componentname *cnp;
{
D 143
	register struct vnode *dp = 0;	/* the directory we are searching */
E 143
I 143
	struct proc *p = cnp->cn_proc;
	struct vnode *dp = 0;		/* the directory we are searching */
E 143
	int docache;			/* == 0 do not cache last component */
	int wantparent;			/* 1 => wantparent or lockparent flag */
	int rdonly;			/* lookup read-only flag bit */
	int error = 0;
#ifdef NAMEI_DIAGNOSTIC
	int newhash;			/* DEBUG: check name hash */
	char *cp;			/* DEBUG: check name ptr/len */
#endif
E 142

I 142
	/*
	 * Setup: break out flag bits into variables.
	 */
	wantparent = cnp->cn_flags & (LOCKPARENT|WANTPARENT);
	docache = (cnp->cn_flags & NOCACHE) ^ NOCACHE;
	if (cnp->cn_nameiop == DELETE ||
	    (wantparent && cnp->cn_nameiop != CREATE))
		docache = 0;
	rdonly = cnp->cn_flags & RDONLY;
	cnp->cn_flags &= ~ISSYMLINK;
	dp = dvp;
D 143
	VOP_LOCK(dp);
E 143
I 143
	vn_lock(dp, LK_EXCLUSIVE | LK_RETRY, p);
E 143

/* dirloop: */
	/*
	 * Search a new directory.
	 *
	 * The cn_hash value is for use by vfs_cache.
	 * The last component of the filename is left accessible via
	 * cnp->cn_nameptr for callers that need the name. Callers needing
	 * the name set the SAVENAME flag. When done, they assume
	 * responsibility for freeing the pathname buffer.
	 */
#ifdef NAMEI_DIAGNOSTIC
	for (newhash = 0, cp = cnp->cn_nameptr; *cp != 0 && *cp != '/'; cp++)
		newhash += (unsigned char)*cp;
	if (newhash != cnp->cn_hash)
		panic("relookup: bad hash");
	if (cnp->cn_namelen != cp - cnp->cn_nameptr)
		panic ("relookup: bad len");
	if (*cp != 0)
		panic("relookup: not last component");
	printf("{%s}: ", cnp->cn_nameptr);
#endif

	/*
	 * Check for degenerate name (e.g. / or "")
	 * which is a way of talking about a directory,
	 * e.g. like "/." or ".".
	 */
	if (cnp->cn_nameptr[0] == '\0') {
		if (cnp->cn_nameiop != LOOKUP || wantparent) {
			error = EISDIR;
			goto bad;
		}
		if (dp->v_type != VDIR) {
			error = ENOTDIR;
			goto bad;
		}
		if (!(cnp->cn_flags & LOCKLEAF))
D 143
			VOP_UNLOCK(dp);
E 143
I 143
			VOP_UNLOCK(dp, 0, p);
E 143
		*vpp = dp;
		if (cnp->cn_flags & SAVESTART)
			panic("lookup: SAVESTART");
		return (0);
	}

	if (cnp->cn_flags & ISDOTDOT)
		panic ("relookup: lookup on dot-dot");

	/*
	 * We now have a segment name to search for, and a directory to search.
	 */
	if (error = VOP_LOOKUP(dp, vpp, cnp)) {
#ifdef DIAGNOSTIC
		if (*vpp != NULL)
			panic("leaf should be empty");
#endif
		if (error != EJUSTRETURN)
			goto bad;
		/*
		 * If creating and at end of pathname, then can consider
		 * allowing file to be created.
		 */
D 145
		if (rdonly || (dvp->v_mount->mnt_flag & MNT_RDONLY)) {
E 145
I 145
		if (rdonly) {
E 145
			error = EROFS;
			goto bad;
		}
		/* ASSERT(dvp == ndp->ni_startdir) */
		if (cnp->cn_flags & SAVESTART)
			VREF(dvp);
		/*
		 * We return with ni_vp NULL to indicate that the entry
		 * doesn't currently exist, leaving a pointer to the
		 * (possibly locked) directory inode in ndp->ni_dvp.
		 */
		return (0);
	}
	dp = *vpp;

#ifdef DIAGNOSTIC
	/*
	 * Check for symbolic link
	 */
	if (dp->v_type == VLNK && (cnp->cn_flags & FOLLOW))
		panic ("relookup: symlink found.\n");
#endif

	/*
D 145
	 * Check for read-only file systems.
E 145
I 145
	 * Disallow directory write attempts on read-only file systems.
E 145
	 */
D 145
	if (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME) {
		/*
		 * Disallow directory write attempts on read-only
		 * file systems.
		 */
		if (rdonly || (dp->v_mount->mnt_flag & MNT_RDONLY) ||
		    (wantparent &&
		     (dvp->v_mount->mnt_flag & MNT_RDONLY))) {
			error = EROFS;
			goto bad2;
		}
E 145
I 145
	if (rdonly &&
	    (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME)) {
		error = EROFS;
		goto bad2;
E 145
	}
	/* ASSERT(dvp == ndp->ni_startdir) */
	if (cnp->cn_flags & SAVESTART)
		VREF(dvp);
	
	if (!wantparent)
		vrele(dvp);
	if ((cnp->cn_flags & LOCKLEAF) == 0)
D 143
		VOP_UNLOCK(dp);
E 143
I 143
		VOP_UNLOCK(dp, 0, p);
E 143
	return (0);

bad2:
	if ((cnp->cn_flags & LOCKPARENT) && (cnp->cn_flags & ISLASTCN))
D 143
		VOP_UNLOCK(dvp);
E 143
I 143
		VOP_UNLOCK(dvp, 0, p);
E 143
	vrele(dvp);
bad:
	vput(dp);
	*vpp = NULL;
	return (error);
}
E 142
E 114
E 62
E 43
E 23
E 13
E 1
