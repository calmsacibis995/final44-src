h32685
s 00049/00003/03175
d D 8.16 95/05/27 22:24:08 mckusick 135 134
c read-only checking must be done by the filesystem layers
e
s 00002/00001/03176
d D 8.15 95/05/14 00:33:08 mckusick 134 133
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 01421/00785/01756
d D 8.14 95/03/30 11:26:40 mckusick 133 132
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00010/00013/02531
d D 8.13 95/03/19 00:03:14 mckusick 132 131
c reverse arguments to VOP_LINK (to get them right)
e
s 00003/00000/02541
d D 8.12 95/02/22 21:07:33 mckusick 131 130
c add vop_revoke
e
s 00002/00000/02539
d D 8.11 95/02/22 18:04:47 mckusick 130 129
c fill in runp in bmap if requested to do so
e
s 00007/00000/02532
d D 8.10 94/08/11 11:59:00 mckusick 129 128
c bug fix from Macklem
e
s 00003/00000/02529
d D 8.9 94/08/11 00:01:55 mckusick 128 127
c add vop_lease
e
s 00001/00004/02528
d D 8.8 94/08/05 11:49:23 mckusick 127 126
c cannot use append mode in a stateless server (from macklem)
e
s 00021/00012/02511
d D 8.7 94/06/16 14:36:45 mckusick 126 125
c avoid trying to truncate BLK and CHR special devices (from mycroft)
e
s 00010/00000/02513
d D 8.6 94/06/04 19:49:10 mckusick 125 124
c add cookie and eofflag parameters to readdir
e
s 00003/00000/02510
d D 8.5 94/02/13 11:35:49 hibler 124 123
c add null nfs_reallocblks routine (is this needed?)
e
s 00001/00003/02509
d D 8.4 94/01/21 20:10:05 bostic 123 122
c lint
e
s 00004/00006/02508
d D 8.3 93/12/30 16:20:34 mckusick 122 121
c new queue structure; vget now locks optionally
e
s 00012/00001/02502
d D 8.2 93/08/10 15:45:09 mckusick 121 120
c flush attribute cache when adding or deleteing entries (from macklem)
e
s 00002/00002/02501
d D 8.1 93/06/16 17:30:29 bostic 120 119
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/02500
d D 7.109 93/06/16 17:16:01 mckusick 119 117
c fix for trashed TCP/IP connections from Macklem
e
s 00002/00002/02501
d R 8.1 93/06/10 23:39:28 bostic 118 117
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00001/02497
d D 7.108 93/05/25 15:59:22 mckusick 117 116
c lease buglet from Macklem
e
s 00021/00000/02477
d D 7.107 93/05/25 15:52:56 mckusick 116 115
c add pathconf
e
s 00002/00001/02475
d D 7.106 93/05/03 18:37:43 mckusick 115 114
c the final polish to leases from Rick Macklem
e
s 00021/00003/02455
d D 7.105 93/04/17 15:55:50 mckusick 114 113
c take gid from parent directory, not user
e
s 00001/00002/02457
d D 7.104 93/03/30 15:34:25 mckusick 113 112
c eliminate flags and generation number in times hack
e
s 00003/00003/02456
d D 7.103 93/02/02 21:09:12 mckusick 112 111
c nfs_bwrite => vn_bwrite
e
s 00098/00177/02361
d D 7.102 93/02/02 15:22:07 mckusick 111 110
c update for 4.4BSD from Rick Macklem
e
s 00004/00003/02534
d D 7.101 92/11/30 22:04:00 mckusick 110 109
c check name length before entering in cache
e
s 00008/00006/02529
d D 7.100 92/11/10 10:58:54 mckusick 109 108
c use local access checks when NQNFS ACCESS check cannot be used to server
e
s 00010/00018/02525
d D 7.99 92/11/01 23:16:39 mckusick 108 107
c fix from Jeff Forys for tracking changing NFS file sizes
e
s 00001/00001/02542
d D 7.98 92/10/12 21:17:15 mckusick 107 106
c bawrite does not return a value
e
s 00001/00001/02542
d D 7.97 92/10/09 22:44:33 mckusick 106 105
c have to dup, not copy credentials in nfs_doio
e
s 00005/00009/02538
d D 7.96 92/10/08 00:24:51 mckusick 105 104
c use new queue routines for buffer lists hanging off vnode;
c use new queue routines to manage list of I/O requests
e
s 00001/00000/02546
d D 7.95 92/10/07 17:14:57 margo 104 103
c Add comment for extra argument in bmap call.
e
s 00007/00012/02539
d D 7.94 92/10/02 00:18:14 mckusick 103 102
c update to modern list management
e
s 00085/00034/02466
d D 7.93 92/09/30 16:07:30 mckusick 102 101
c September update from Rick Macklem to add accept protocol to NQMFS
e
s 00001/00010/02499
d D 7.92 92/09/22 18:10:34 mckusick 101 100
c do not update local times of special devices on stat or close (from leres@lbl)
e
s 00230/00158/02279
d D 7.91 92/09/16 18:29:42 mckusick 100 99
c update from Rick Macklem
e
s 00000/00003/02437
d D 7.90 92/07/25 20:51:47 mckusick 99 98
c spec_vnodeops_p now declared in specdev.h
e
s 00013/00012/02427
d D 7.89 92/07/13 23:08:17 mckusick 98 97
c minor optimization
e
s 00003/00002/02436
d D 7.88 92/07/12 15:52:44 mckusick 97 96
c new location for includes
e
s 00005/00002/02433
d D 7.87 92/07/12 11:09:21 mckusick 96 95
c clear d_type for normal nfs_readdir; set it when using nqnfs_readdir
e
s 00011/00010/02424
d D 7.86 92/07/06 18:53:28 mckusick 95 94
c struct readdir should really be struct dirent since we are building
c a structure to be returned as part of a VOP_READDIR
e
s 00182/00062/02252
d D 7.85 92/07/03 01:57:14 mckusick 94 93
c add paramter declarations; delete USES; streamline unmarshalling;
c nfs_vget moves to nfs_vfsops.c
e
s 00082/00031/02232
d D 7.84 92/06/25 13:17:53 mckusick 93 92
c need to use nfs_fsync for spec and fifo hybrid ops;
c expand vnops parameters; new parameters to vinvalbuf; dump NOQUAD;
c drop proc pointer parameter from removeit; drop eofflag from readdir;
c inline expand vflushbuf in fsync
e
s 00027/00015/02236
d D 7.83 92/06/19 19:29:39 mckusick 92 91
c timeval => timespec in vattr and dinode
e
s 00000/00001/02251
d D 7.82 92/06/18 14:22:42 pendry 91 90
c remove spurious vrele in nfs_link
e
s 00013/00005/02239
d D 7.81 92/06/17 20:42:49 mckusick 90 89
c for now update times when reading or writing
e
s 00411/00362/01833
d D 7.80 92/06/02 15:47:36 mckusick 89 88
c put frequently used arguments into separate variables
e
s 00021/00007/02174
d D 7.79 92/06/02 14:44:23 mckusick 88 87
c fix to locally record mtime and atime on NFS nodes
e
s 00019/00000/02162
d D 7.78 92/06/02 14:30:17 pendry 87 86
c have to move cross device check below the VFS interface
e
s 00151/00014/02011
d D 7.77 92/05/20 11:23:44 mckusick 86 84
c update for spec and fifo times for NFS (from Macklem)
e
s 00149/00014/02011
d R 7.77 92/05/20 10:58:42 mckusick 85 84
c update for spec and fifo times for NFS (from Macklem)
e
s 00251/00467/01774
d D 7.76 92/05/15 13:57:45 heideman 84 83
c vnodeop argument macro expansion
e
s 00005/00005/02236
d D 7.75 92/05/15 12:25:05 heideman 83 82
c bwrite->vn_bwrite and vfree returns error for vn_if
e
s 00419/00259/01822
d D 7.74 92/05/14 17:40:11 heideman 82 81
c vnode interface conversion
e
s 00001/00002/02080
d D 7.73 92/05/14 16:28:44 heideman 81 72
c nfs_rename made one line
e
s 00405/00254/01828
d R 7.73 92/05/14 15:59:11 heideman 80 72
c vnode interface conversion
e
s 00405/00254/01828
d R 7.73 92/05/14 14:58:37 heideman 79 72
c vnode interface conversion
e
s 00313/00173/01909
d R 7.73 92/05/14 13:06:23 heideman 78 72
c vnode interface conversion
e
s 00313/00173/01909
d R 7.73 92/05/14 12:02:53 heideman 77 72
c vnode interface conversion
e
s 00313/00173/01909
d R 7.73 92/05/14 11:26:23 heideman 76 72
c vnode interface conversion
e
s 00328/00173/01909
d R 7.73 92/05/13 23:22:06 heideman 75 72
c vnode interface conversion
e
s 00328/00173/01909
d R 7.73 92/05/13 19:05:02 heideman 74 72
c vnode interface conversion
e
s 00328/00173/01909
d R 7.73 92/05/13 18:37:15 heideman 73 72
c vnode interface conversion
e
s 00024/00022/02058
d D 7.72 92/05/04 16:38:25 mckusick 72 71
c lint; clean up include directives
e
s 00002/00001/02078
d D 7.71 92/04/21 13:28:54 mckusick 71 70
c VOP_TRUNCATE now takes a cred argument
e
s 00001/00001/02078
d D 7.70 92/04/21 10:55:25 mckusick 70 69
c ensure proper types for local variables and parameters
e
s 00005/00002/02074
d D 7.69 92/03/03 13:20:04 mckusick 69 68
c must have directory vnode as first op;
c must convert to proper return value for name lookup when creating
e
s 00008/00012/02068
d D 7.68 92/02/06 17:40:46 mckusick 68 67
c get rid of ufs dependencies; define RPC format of directories
e
s 00018/00030/02062
d D 7.67 92/02/04 00:25:33 heideman 67 66
c cleanups for new nameidata organization
e
s 00259/00203/01833
d D 7.66 92/01/22 09:39:42 heideman 66 65
c lookup converted to new form
e
s 00486/00265/01550
d D 7.65 92/01/14 12:41:27 mckusick 65 64
c update from Rick Macklem (including leases)
e
s 00006/00000/01809
d D 7.64 91/12/16 17:27:09 mckusick 64 63
c sillyrename now in nfsnode
e
s 00104/00000/01704
d D 7.63 91/11/05 15:47:24 mckusick 63 62
c reorganization to move ufsmount ops to be vnode ops;
c (some ops just added in a skeletal way)
e
s 00003/00003/01701
d D 7.62 91/11/01 16:49:49 bostic 62 61
c ufs moved down one level
e
s 00000/00058/01704
d D 7.61 91/09/06 16:51:13 ralph 61 60
c remove machine dependencies
e
s 00003/00003/01759
d D 7.60 91/05/24 15:56:05 mckusick 60 59
c only set SAVENAME on last pathname component
e
s 00038/00027/01724
d D 7.59 91/05/15 20:22:19 mckusick 59 58
c use ni_ptr and ni_namelen to find name to be used instead of ni_dent
e
s 00042/00044/01709
d D 7.58 91/04/19 18:35:46 mckusick 58 57
c redefine sillyrename structure to avoid use of nameidata structure
c (thus reducing its allocation size from 512 to 64 bytes)
e
s 00190/00206/01563
d D 7.57 91/04/16 00:43:15 mckusick 57 56
c u_long tl used in place of u_long p; 
c use prototypes for NFS vnode ops (from specdev.h, fifo.h, and nfsmount.h); 
c add appropriate proc pointers (eliminating lots of curproc's)
e
s 00022/00021/01747
d D 7.56 91/03/19 11:24:50 karels 56 55
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; consolidate *nullops()
e
s 00008/00006/01760
d D 7.55 91/03/13 15:17:38 mckusick 55 54
c cache open with O_CREAT when the name already exists
e
s 00019/00028/01747
d D 7.54 91/03/04 22:52:18 mckusick 54 53
c misc fixes plus diskless support from Rick Macklem
e
s 00012/00016/01763
d D 7.53 91/03/04 14:14:28 karels 53 52
c first pass at proc reorg; merge *nullops, other cleanups; use correct proc's
c credentials in nfs_doio
e
s 00001/00001/01778
d D 7.52 91/02/21 22:56:04 mckusick 52 51
c fixes for multiple calls to namei (for rename in NFS)
e
s 00006/00005/01773
d D 7.51 91/02/18 16:40:05 karels 51 50
c fill in b_proc iff proc will wait for operation, so tprintf won't fail;
c don't bother having nfs daemon do operation if we're going to block
e
s 00024/00003/01754
d D 7.50 91/02/01 16:27:10 mckusick 50 49
c add POSIX-style byte-level record locking
e
s 00002/00000/01755
d D 7.49 91/01/10 23:53:41 mckusick 49 48
c eliminate paranoid check
e
s 00001/00012/01754
d D 7.48 90/12/05 16:04:32 mckusick 48 47
c update for new VM
e
s 00001/00000/01765
d D 7.47 90/08/17 21:54:47 mckusick 47 46
c patch those mbuf holes
e
s 00005/00004/01760
d D 7.46 90/07/26 15:29:49 mckusick 46 45
c "bug fix for utimes from Rick Macklem"
e
s 00003/00003/01761
d D 7.45 90/07/02 11:12:57 william 45 44
c added 386 ifdefs
e
s 00001/00011/01763
d D 7.44 90/06/28 21:53:18 bostic 44 43
c new copyright notice
e
s 00004/00001/01770
d D 7.43 90/06/21 12:15:56 mckusick 43 42
c have to check for "." when releasing parent directory
e
s 00034/00024/01737
d D 7.42 90/06/21 11:48:03 mckusick 42 41
c "update from Rick Macklem"
e
s 00008/00002/01753
d D 7.41 90/05/30 11:39:59 mckusick 41 40
c VOP_ABORTOP is no longer responsible for unlocking and vreleing vnodes
e
s 00045/00005/01710
d D 7.40 90/05/18 15:07:31 mckusick 40 39
c nfs_mknod update from Rick Macklem
e
s 00208/00151/01507
d D 7.39 90/05/14 11:46:42 mckusick 39 38
c "update from Rick Macklem adding TCP support to NFS"
e
s 00017/00008/01641
d D 7.38 90/05/10 15:55:04 mckusick 38 37
c hp300 handles physical I/O elsewhere
e
s 00009/00009/01640
d D 7.37 90/05/04 20:52:20 mckusick 37 36
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00002/00000/01647
d D 7.36 90/04/07 12:16:15 mckusick 36 35
c unlock during readlink RPC (from Rick Macklem)
e
s 00002/00000/01645
d D 7.35 90/04/07 12:15:00 mckusick 35 34
c do not do direof cacheing
e
s 00001/00001/01644
d D 7.34 90/03/13 14:32:58 mckusick 34 33
c return real error, not always ENOENT (from gmf@osf.org)
e
s 00005/00005/01640
d D 7.33 90/03/06 23:32:14 mckusick 33 32
c m_bsize is now m_stat.f_bsize; m_fsid is now m_stat.f_fsid;
c only copy mntfrom and mnton if going to a new structure
e
s 00123/00063/01522
d D 7.32 90/03/05 19:38:08 mckusick 32 31
c readdir fixes from Rick Macklem
e
s 00056/00003/01529
d D 7.31 90/03/05 19:15:53 mckusick 31 30
c add support for fifo's
e
s 00022/00005/01510
d D 7.30 90/03/01 14:00:23 mckusick 30 29
c invalidate name cache entries when directory is modified;
c kill running processes when file modification is detected at pagein time
e
s 00000/00001/01515
d D 7.29 90/02/17 15:23:48 mckusick 29 28
c get rid of bogus `strings.h' include file
e
s 00000/00005/01516
d D 7.28 90/02/17 10:26:54 mckusick 28 27
c get rid of unneeded header files
e
s 00008/00003/01512
d D 7.27 90/02/16 13:31:19 mckusick 27 26
c have to null terminate name if rounding up packet size (from gmf@osf.org)
e
s 00051/00025/01464
d D 7.26 90/02/16 13:21:55 mckusick 26 25
c pass indication of idempotency through to the nfsm_request routine;
c in remove, unlock parent directory first to avoid deadlock with
c removal of silly rename file on final vrele;
c map ENOENT on rename, and EEXIST on link, symlink, and mkdir to zero
c as they would have been detected on lookup, so come about because
c of non-idempotency on retries
e
s 00003/00000/01487
d D 7.25 90/02/08 17:12:24 mckusick 25 24
c have to invalidate the cache for certain NFS transactions (from gmf@osf.org)
e
s 00006/00000/01481
d D 7.24 90/01/15 18:42:05 mckusick 24 23
c debugging, print out holder and waiter of nfsnode lock
e
s 00004/00001/01477
d D 7.23 90/01/15 18:26:51 mckusick 23 22
c add islocked function to vnode switch
e
s 00003/00005/01475
d D 7.22 90/01/04 22:10:33 mckusick 22 21
c v_blockh is split into clean and dirty lists
e
s 00003/00003/01477
d D 7.21 89/12/31 16:20:32 mckusick 21 20
c I/O routines should use b_blkno, not b_lblkno
e
s 00002/00002/01478
d D 7.20 89/12/30 22:34:53 mckusick 20 19
c v_count => v_usecount
e
s 00098/00068/01382
d D 7.19 89/12/20 18:02:41 mckusick 19 18
c "December update from Rick Macklem"
e
s 00003/00003/01447
d D 7.18 89/12/19 16:22:28 mckusick 18 17
c use proper address in mapping (from mike@cs.utah.edu)
e
s 00052/00035/01398
d D 7.17 89/11/30 22:54:32 mckusick 17 16
c use b_lblkno in place of b_blkno; add print routine
e
s 00030/00030/01403
d D 7.16 89/11/22 22:46:23 mckusick 16 15
c label special device operations
e
s 00013/00023/01420
d D 7.15 89/11/22 21:38:37 mckusick 15 14
c readrpc, writerpc, and readdir no longer take an offp;
c fsync locks above the vnode layer
e
s 00002/00013/01441
d D 7.14 89/11/03 15:32:21 mckusick 14 13
c get rid of notdef code (and make lint happy)
e
s 00149/00039/01305
d D 7.13 89/11/03 11:05:07 mckusick 13 12
c lint
e
s 00000/00003/01344
d D 7.12 89/10/31 17:17:51 mckusick 12 11
c vnode layer fills in f_flags and f_fsid
e
s 00023/00005/01324
d D 7.11 89/10/31 16:03:30 mckusick 11 10
c mknod must do an abortop and return an error;
c must pass reference to vnode pointer to nfs_loadattrcache so it can be updated
e
s 00050/00061/01279
d D 7.10 89/10/29 23:48:31 mckusick 10 9
c create spec_nfsv2nodeops; ngrab is replaced by vget; device aliasing
c is handled at the vnode level
e
s 00004/00001/01336
d D 7.9 89/10/24 19:50:32 mckusick 9 8
c add nfs_inactive to support single vnode table
e
s 00003/00002/01334
d D 7.8 89/10/21 13:20:15 mckusick 8 7
c add lookup routine that will fail gracefully
e
s 00011/00037/01325
d D 7.7 89/10/21 11:32:11 mckusick 7 6
c "bug fixes and cleanups from Rick Macklem"
e
s 00086/00027/01276
d D 7.6 89/10/19 22:33:01 mckusick 6 5
c "update from Rick Macklem"
e
s 00250/00162/01053
d D 7.5 89/08/30 20:29:49 macklem 5 4
c first buffer cache implementation; name cache usage; code cleanups
e
s 00002/00002/01213
d D 7.4 89/08/22 22:30:01 mckusick 4 3
c zero out fields for number of free and used inodes
e
s 00000/00002/01215
d D 7.3 89/07/06 17:45:12 mckusick 3 2
c do not nput when mkdir fails (from Rick Macklem)
e
s 00016/00015/01201
d D 7.2 89/07/06 17:42:18 mckusick 2 1
c update of July 5th from Rick Macklem
e
s 01216/00000/00000
d D 7.1 89/07/05 11:32:21 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 120
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 120
I 120
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 120
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 44
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
E 44
I 44
 * %sccs.include.redist.c%
E 44
 *
 *	%W% (Berkeley) %G%
 */

I 133

E 133
/*
D 133
 * vnode op calls for sun nfs version 2
E 133
I 133
 * vnode op calls for Sun NFS version 2 and 3
E 133
 */

D 48
#include "machine/pte.h"
E 48
D 56
#include "machine/mtpr.h"
E 56
D 29
#include "strings.h"
E 29
D 72
#include "param.h"
D 56
#include "user.h"
E 56
#include "proc.h"
I 32
#include "kernel.h"
I 53
#include "systm.h"
E 53
E 32
#include "mount.h"
#include "buf.h"
D 48
#include "vm.h"
E 48
D 2
#include "dir.h"
E 2
I 2
D 28
#include "../ufs/dir.h"
E 28
E 2
#include "malloc.h"
#include "mbuf.h"
D 28
#include "uio.h"
#include "ucred.h"
#include "namei.h"
E 28
D 56
#include "errno.h"
E 56
D 57
#include "file.h"
E 57
#include "conf.h"
I 57
#include "namei.h"
E 57
#include "vnode.h"
I 57
#include "specdev.h"
#include "fifo.h"
E 57
I 30
D 48
#include "text.h"
E 48
E 30
D 28
#include "../ufs/inode.h"
E 28
I 5
#include "map.h"
E 72
I 72
#include <sys/param.h>
D 133
#include <sys/proc.h>
E 133
#include <sys/kernel.h>
#include <sys/systm.h>
I 133
#include <sys/resourcevar.h>
#include <sys/proc.h>
E 133
#include <sys/mount.h>
#include <sys/buf.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/conf.h>
#include <sys/namei.h>
#include <sys/vnode.h>
D 97
#include <sys/specdev.h>
#include <sys/fifo.h>
E 97
D 133
#include <sys/map.h>
E 133
I 95
#include <sys/dirent.h>
I 133
#include <sys/fcntl.h>
#include <ufs/ufs/dir.h>
E 133
E 95
E 72
I 56

E 56
I 40
D 62
#include "../ufs/quota.h"
#include "../ufs/inode.h"
I 59
#include "../ufs/dir.h"
E 62
I 62
D 68
#include "ufs/ufs/quota.h"
#include "ufs/ufs/inode.h"
#include "ufs/ufs/dir.h"
E 62
E 59
I 56

E 68
I 65
D 72
#include "rpcv2.h"
E 65
E 56
E 40
E 5
#include "nfsv2.h"
#include "nfs.h"
#include "nfsnode.h"
#include "nfsmount.h"
#include "xdr_subs.h"
#include "nfsm_subs.h"
I 5
D 65
#include "nfsiom.h"
E 65
I 65
#include "nqnfs.h"
E 72
I 72
#include <vm/vm.h>
I 97

#include <miscfs/specfs/specdev.h>
#include <miscfs/fifofs/fifo.h>
E 97

#include <nfs/rpcv2.h>
D 133
#include <nfs/nfsv2.h>
E 133
I 133
#include <nfs/nfsproto.h>
E 133
#include <nfs/nfs.h>
#include <nfs/nfsnode.h>
#include <nfs/nfsmount.h>
#include <nfs/xdr_subs.h>
#include <nfs/nfsm_subs.h>
#include <nfs/nqnfs.h>
E 72
E 65
E 5

I 133
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/in_var.h>

E 133
I 56
D 61
#include "machine/mtpr.h"

E 61
E 56
/* Defs */
#define	TRUE	1
#define	FALSE	0

D 57
/* Global vars */
int	nfs_lookup(),
	nfs_create(),
I 11
	nfs_mknod(),
E 11
	nfs_open(),
	nfs_close(),
	nfs_access(),
	nfs_getattr(),
	nfs_setattr(),
	nfs_read(),
	nfs_write(),
D 53
	vfs_noop(),
	vfs_nullop(),
E 53
	nfs_remove(),
	nfs_link(),
	nfs_rename(),
	nfs_mkdir(),
	nfs_rmdir(),
	nfs_symlink(),
	nfs_readdir(),
	nfs_readlink(),
	nfs_abortop(),
	nfs_lock(),
	nfs_unlock(),
	nfs_bmap(),
	nfs_strategy(),
I 5
	nfs_fsync(),
E 5
D 9
	nfs_inactive();
E 9
I 9
	nfs_inactive(),
D 17
	nfs_reclaim();
E 17
I 17
	nfs_reclaim(),
D 23
	nfs_print();
E 23
I 23
	nfs_print(),
D 50
	nfs_islocked();
E 50
I 50
	nfs_islocked(),
D 53
	nfs_advlock();
E 53
I 53
	nfs_advlock(),
	eopnotsupp(),
	seltrue();
E 53
E 50
E 23
E 17
E 9

E 57
I 57
/*
 * Global vfs data structures for nfs
 */
E 57
D 82
struct vnodeops nfsv2_vnodeops = {
D 17
	nfs_lookup,
	nfs_create,
D 11
	vfs_noop,
E 11
I 11
	nfs_mknod,
E 11
	nfs_open,
	nfs_close,
	nfs_access,
	nfs_getattr,
	nfs_setattr,
	nfs_read,
	nfs_write,
	vfs_noop,
	vfs_noop,
	vfs_noop,
D 5
	vfs_nullop,
E 5
I 5
	nfs_fsync,
E 5
D 11
	vfs_noop,
E 11
I 11
	vfs_nullop,
E 11
	nfs_remove,
	nfs_link,
	nfs_rename,
	nfs_mkdir,
	nfs_rmdir,
	nfs_symlink,
	nfs_readdir,
	nfs_readlink,
	nfs_abortop,
	nfs_inactive,
I 9
	nfs_reclaim,
E 9
	nfs_lock,
	nfs_unlock,
	nfs_bmap,
	nfs_strategy,
E 17
I 17
	nfs_lookup,		/* lookup */
	nfs_create,		/* create */
	nfs_mknod,		/* mknod */
	nfs_open,		/* open */
	nfs_close,		/* close */
	nfs_access,		/* access */
	nfs_getattr,		/* getattr */
	nfs_setattr,		/* setattr */
	nfs_read,		/* read */
	nfs_write,		/* write */
D 53
	vfs_noop,		/* ioctl */
	vfs_noop,		/* select */
	vfs_noop,		/* mmap */
E 53
I 53
D 57
	eopnotsupp,		/* ioctl */
	seltrue,		/* select */
	eopnotsupp,		/* mmap */
E 57
I 57
	nfs_ioctl,		/* ioctl */
	nfs_select,		/* select */
	nfs_mmap,		/* mmap */
E 57
E 53
	nfs_fsync,		/* fsync */
D 53
	vfs_nullop,		/* seek */
E 53
I 53
D 57
	nullop,			/* seek */
E 57
I 57
	nfs_seek,		/* seek */
E 57
E 53
	nfs_remove,		/* remove */
	nfs_link,		/* link */
	nfs_rename,		/* rename */
	nfs_mkdir,		/* mkdir */
	nfs_rmdir,		/* rmdir */
	nfs_symlink,		/* symlink */
	nfs_readdir,		/* readdir */
	nfs_readlink,		/* readlink */
	nfs_abortop,		/* abortop */
	nfs_inactive,		/* inactive */
	nfs_reclaim,		/* reclaim */
	nfs_lock,		/* lock */
	nfs_unlock,		/* unlock */
	nfs_bmap,		/* bmap */
	nfs_strategy,		/* strategy */
	nfs_print,		/* print */
I 23
	nfs_islocked,		/* islocked */
I 50
	nfs_advlock,		/* advlock */
I 63
	nfs_blkatoff,		/* blkatoff */
	nfs_vget,		/* vget */
	nfs_valloc,		/* valloc */
	nfs_vfree,		/* vfree */
	nfs_truncate,		/* truncate */
	nfs_update,		/* update */
	bwrite,			/* bwrite */
E 82
I 82
int (**nfsv2_vnodeop_p)();
struct vnodeopv_entry_desc nfsv2_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
D 89
	{ &vop_lookup_desc, nfs_lookup },		/* lookup */
	{ &vop_create_desc, nfs_create },		/* create */
E 89
I 89
	{ &vop_lookup_desc, nfs_lookup },	/* lookup */
	{ &vop_create_desc, nfs_create },	/* create */
E 89
	{ &vop_mknod_desc, nfs_mknod },		/* mknod */
	{ &vop_open_desc, nfs_open },		/* open */
	{ &vop_close_desc, nfs_close },		/* close */
D 89
	{ &vop_access_desc, nfs_access },		/* access */
	{ &vop_getattr_desc, nfs_getattr },		/* getattr */
	{ &vop_setattr_desc, nfs_setattr },		/* setattr */
E 89
I 89
	{ &vop_access_desc, nfs_access },	/* access */
	{ &vop_getattr_desc, nfs_getattr },	/* getattr */
	{ &vop_setattr_desc, nfs_setattr },	/* setattr */
E 89
	{ &vop_read_desc, nfs_read },		/* read */
	{ &vop_write_desc, nfs_write },		/* write */
I 128
	{ &vop_lease_desc, nfs_lease_check },	/* lease */
E 128
	{ &vop_ioctl_desc, nfs_ioctl },		/* ioctl */
D 89
	{ &vop_select_desc, nfs_select },		/* select */
E 89
I 89
	{ &vop_select_desc, nfs_select },	/* select */
I 131
	{ &vop_revoke_desc, nfs_revoke },	/* revoke */
E 131
E 89
	{ &vop_mmap_desc, nfs_mmap },		/* mmap */
	{ &vop_fsync_desc, nfs_fsync },		/* fsync */
	{ &vop_seek_desc, nfs_seek },		/* seek */
D 89
	{ &vop_remove_desc, nfs_remove },		/* remove */
E 89
I 89
	{ &vop_remove_desc, nfs_remove },	/* remove */
E 89
	{ &vop_link_desc, nfs_link },		/* link */
D 89
	{ &vop_rename_desc, nfs_rename },		/* rename */
E 89
I 89
	{ &vop_rename_desc, nfs_rename },	/* rename */
E 89
	{ &vop_mkdir_desc, nfs_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, nfs_rmdir },		/* rmdir */
D 89
	{ &vop_symlink_desc, nfs_symlink },		/* symlink */
	{ &vop_readdir_desc, nfs_readdir },		/* readdir */
	{ &vop_readlink_desc, nfs_readlink },		/* readlink */
	{ &vop_abortop_desc, nfs_abortop },		/* abortop */
	{ &vop_inactive_desc, nfs_inactive },		/* inactive */
	{ &vop_reclaim_desc, nfs_reclaim },		/* reclaim */
E 89
I 89
	{ &vop_symlink_desc, nfs_symlink },	/* symlink */
	{ &vop_readdir_desc, nfs_readdir },	/* readdir */
	{ &vop_readlink_desc, nfs_readlink },	/* readlink */
	{ &vop_abortop_desc, nfs_abortop },	/* abortop */
	{ &vop_inactive_desc, nfs_inactive },	/* inactive */
	{ &vop_reclaim_desc, nfs_reclaim },	/* reclaim */
E 89
	{ &vop_lock_desc, nfs_lock },		/* lock */
D 89
	{ &vop_unlock_desc, nfs_unlock },		/* unlock */
E 89
I 89
	{ &vop_unlock_desc, nfs_unlock },	/* unlock */
E 89
	{ &vop_bmap_desc, nfs_bmap },		/* bmap */
D 89
	{ &vop_strategy_desc, nfs_strategy },		/* strategy */
E 89
I 89
	{ &vop_strategy_desc, nfs_strategy },	/* strategy */
E 89
	{ &vop_print_desc, nfs_print },		/* print */
D 89
	{ &vop_islocked_desc, nfs_islocked },		/* islocked */
	{ &vop_advlock_desc, nfs_advlock },		/* advlock */
	{ &vop_blkatoff_desc, nfs_blkatoff },		/* blkatoff */
E 89
I 89
	{ &vop_islocked_desc, nfs_islocked },	/* islocked */
I 116
	{ &vop_pathconf_desc, nfs_pathconf },	/* pathconf */
E 116
	{ &vop_advlock_desc, nfs_advlock },	/* advlock */
	{ &vop_blkatoff_desc, nfs_blkatoff },	/* blkatoff */
E 89
D 94
	{ &vop_vget_desc, nfs_vget },		/* vget */
E 94
D 89
	{ &vop_valloc_desc, nfs_valloc },		/* valloc */
E 89
I 89
	{ &vop_valloc_desc, nfs_valloc },	/* valloc */
I 124
	{ &vop_reallocblks_desc, nfs_reallocblks },	/* reallocblks */
E 124
E 89
	{ &vop_vfree_desc, nfs_vfree },		/* vfree */
D 89
	{ &vop_truncate_desc, nfs_truncate },		/* truncate */
	{ &vop_update_desc, nfs_update },		/* update */
E 89
I 89
	{ &vop_truncate_desc, nfs_truncate },	/* truncate */
	{ &vop_update_desc, nfs_update },	/* update */
E 89
D 83
	{ &vop_bwrite_desc, bwrite },
E 83
I 83
D 111
	{ &vop_bwrite_desc, vn_bwrite },
E 111
I 111
D 112
	{ &vop_bwrite_desc, nfs_bwrite },
E 112
I 112
D 133
	{ &vop_bwrite_desc, vn_bwrite },
E 133
I 133
	{ &vop_bwrite_desc, nfs_bwrite },
E 133
E 112
E 111
E 83
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
E 82
E 63
E 50
E 23
E 17
};
I 82
struct vnodeopv_desc nfsv2_vnodeop_opv_desc =
	{ &nfsv2_vnodeop_p, nfsv2_vnodeop_entries };
E 82

D 57
/* Special device vnode ops */
D 8
int	blk_open(),
E 8
I 8
D 10
int	blk_lookup(),
	blk_open(),
E 8
	blk_read(),
	blk_write(),
	blk_ioctl(),
D 7
	blk_select(),
	ufs_bmap(),
	blk_strategy();
E 7
I 7
	blk_select();
E 10
I 10
int	spec_lookup(),
	spec_open(),
	spec_read(),
	spec_write(),
	spec_strategy(),
I 17
	spec_bmap(),
E 17
	spec_ioctl(),
	spec_select(),
	spec_close(),
	spec_badop(),
D 50
	spec_nullop();
E 50
I 50
D 53
	spec_nullop(),
E 53
	spec_advlock();
E 50
E 10
E 7

E 57
I 57
/*
 * Special device vnode ops
 */
E 57
D 10
struct vnodeops nfsv2chr_vnodeops = {
D 8
	vfs_noop,
E 8
I 8
	blk_lookup,
E 8
	vfs_noop,
	vfs_noop,
	blk_open,
	nfs_close,
E 10
I 10
D 82
struct vnodeops spec_nfsv2nodeops = {
D 16
	spec_lookup,
	spec_badop,
	spec_badop,
	spec_open,
	spec_close,
E 10
	nfs_access,
	nfs_getattr,
	nfs_setattr,
D 10
	blk_read,
	blk_write,
	blk_ioctl,
	blk_select,
	vfs_noop,
	vfs_nullop,
	vfs_noop,
	nfs_remove,
	nfs_link,
	nfs_rename,
	vfs_noop,
	vfs_noop,
	nfs_symlink,
	vfs_noop,
	vfs_noop,
	nfs_abortop,
E 10
I 10
	spec_read,
	spec_write,
	spec_ioctl,
	spec_select,
	spec_badop,
	spec_nullop,
	spec_badop,
	spec_badop,
	spec_badop,
	spec_badop,
	spec_badop,
	spec_badop,
	spec_badop,
	spec_badop,
	spec_badop,
	spec_badop,
E 10
	nfs_inactive,
I 9
	nfs_reclaim,
E 9
	nfs_lock,
	nfs_unlock,
D 7
	ufs_bmap,
	blk_strategy,
E 7
I 7
D 10
	vfs_noop,
	vfs_noop,
E 10
I 10
	spec_badop,
	spec_strategy,
E 16
I 16
	spec_lookup,		/* lookup */
D 57
	spec_badop,		/* create */
	spec_badop,		/* mknod */
E 57
I 57
	spec_create,		/* create */
	spec_mknod,		/* mknod */
E 57
	spec_open,		/* open */
	spec_close,		/* close */
	nfs_access,		/* access */
	nfs_getattr,		/* getattr */
	nfs_setattr,		/* setattr */
	spec_read,		/* read */
	spec_write,		/* write */
	spec_ioctl,		/* ioctl */
	spec_select,		/* select */
D 57
	spec_badop,		/* mmap */
D 53
	spec_nullop,		/* fsync */
E 53
I 53
	nullop,			/* fsync */
E 53
	spec_badop,		/* seek */
	spec_badop,		/* remove */
	spec_badop,		/* link */
	spec_badop,		/* rename */
	spec_badop,		/* mkdir */
	spec_badop,		/* rmdir */
	spec_badop,		/* symlink */
	spec_badop,		/* readdir */
	spec_badop,		/* readlink */
	spec_badop,		/* abortop */
E 57
I 57
	spec_mmap,		/* mmap */
	spec_fsync,		/* fsync */
	spec_seek,		/* seek */
	spec_remove,		/* remove */
	spec_link,		/* link */
	spec_rename,		/* rename */
	spec_mkdir,		/* mkdir */
	spec_rmdir,		/* rmdir */
	spec_symlink,		/* symlink */
	spec_readdir,		/* readdir */
	spec_readlink,		/* readlink */
	spec_abortop,		/* abortop */
E 57
	nfs_inactive,		/* inactive */
	nfs_reclaim,		/* reclaim */
	nfs_lock,		/* lock */
	nfs_unlock,		/* unlock */
D 17
	spec_badop,		/* bmap */
E 17
I 17
	spec_bmap,		/* bmap */
E 17
	spec_strategy,		/* strategy */
I 17
	nfs_print,		/* print */
I 23
	nfs_islocked,		/* islocked */
I 50
	spec_advlock,		/* advlock */
I 63
	spec_blkatoff,		/* blkatoff */
	spec_vget,		/* vget */
	spec_valloc,		/* valloc */
	spec_vfree,		/* vfree */
	spec_truncate,		/* truncate */
	nfs_update,		/* update */
	bwrite,			/* bwrite */
E 82
I 82
int (**spec_nfsv2nodeop_p)();
struct vnodeopv_entry_desc spec_nfsv2nodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
D 89
	{ &vop_lookup_desc, spec_lookup },		/* lookup */
	{ &vop_create_desc, spec_create },		/* create */
	{ &vop_mknod_desc, spec_mknod },		/* mknod */
E 89
I 89
	{ &vop_lookup_desc, spec_lookup },	/* lookup */
	{ &vop_create_desc, spec_create },	/* create */
	{ &vop_mknod_desc, spec_mknod },	/* mknod */
E 89
	{ &vop_open_desc, spec_open },		/* open */
D 86
	{ &vop_close_desc, spec_close },		/* close */
E 86
I 86
D 89
	{ &vop_close_desc, nfsspec_close },		/* close */
E 86
	{ &vop_access_desc, nfs_access },		/* access */
	{ &vop_getattr_desc, nfs_getattr },		/* getattr */
	{ &vop_setattr_desc, nfs_setattr },		/* setattr */
D 86
	{ &vop_read_desc, spec_read },		/* read */
	{ &vop_write_desc, spec_write },		/* write */
E 86
I 86
	{ &vop_read_desc, nfsspec_read },		/* read */
	{ &vop_write_desc, nfsspec_write },		/* write */
E 86
	{ &vop_ioctl_desc, spec_ioctl },		/* ioctl */
	{ &vop_select_desc, spec_select },		/* select */
E 89
I 89
	{ &vop_close_desc, nfsspec_close },	/* close */
D 102
	{ &vop_access_desc, nfs_access },	/* access */
E 102
I 102
	{ &vop_access_desc, nfsspec_access },	/* access */
E 102
	{ &vop_getattr_desc, nfs_getattr },	/* getattr */
	{ &vop_setattr_desc, nfs_setattr },	/* setattr */
	{ &vop_read_desc, nfsspec_read },	/* read */
	{ &vop_write_desc, nfsspec_write },	/* write */
I 128
	{ &vop_lease_desc, spec_lease_check },	/* lease */
E 128
	{ &vop_ioctl_desc, spec_ioctl },	/* ioctl */
	{ &vop_select_desc, spec_select },	/* select */
I 131
	{ &vop_revoke_desc, spec_revoke },	/* revoke */
E 131
E 89
	{ &vop_mmap_desc, spec_mmap },		/* mmap */
D 89
	{ &vop_fsync_desc, spec_fsync },		/* fsync */
E 89
I 89
D 93
	{ &vop_fsync_desc, spec_fsync },	/* fsync */
E 93
I 93
	{ &vop_fsync_desc, nfs_fsync },		/* fsync */
E 93
E 89
	{ &vop_seek_desc, spec_seek },		/* seek */
D 89
	{ &vop_remove_desc, spec_remove },		/* remove */
E 89
I 89
	{ &vop_remove_desc, spec_remove },	/* remove */
E 89
	{ &vop_link_desc, spec_link },		/* link */
D 89
	{ &vop_rename_desc, spec_rename },		/* rename */
	{ &vop_mkdir_desc, spec_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, spec_rmdir },		/* rmdir */
	{ &vop_symlink_desc, spec_symlink },		/* symlink */
	{ &vop_readdir_desc, spec_readdir },		/* readdir */
	{ &vop_readlink_desc, spec_readlink },		/* readlink */
	{ &vop_abortop_desc, spec_abortop },		/* abortop */
	{ &vop_inactive_desc, nfs_inactive },		/* inactive */
	{ &vop_reclaim_desc, nfs_reclaim },		/* reclaim */
E 89
I 89
	{ &vop_rename_desc, spec_rename },	/* rename */
	{ &vop_mkdir_desc, spec_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, spec_rmdir },	/* rmdir */
	{ &vop_symlink_desc, spec_symlink },	/* symlink */
	{ &vop_readdir_desc, spec_readdir },	/* readdir */
	{ &vop_readlink_desc, spec_readlink },	/* readlink */
	{ &vop_abortop_desc, spec_abortop },	/* abortop */
	{ &vop_inactive_desc, nfs_inactive },	/* inactive */
	{ &vop_reclaim_desc, nfs_reclaim },	/* reclaim */
E 89
	{ &vop_lock_desc, nfs_lock },		/* lock */
D 89
	{ &vop_unlock_desc, nfs_unlock },		/* unlock */
E 89
I 89
	{ &vop_unlock_desc, nfs_unlock },	/* unlock */
E 89
	{ &vop_bmap_desc, spec_bmap },		/* bmap */
D 89
	{ &vop_strategy_desc, spec_strategy },		/* strategy */
E 89
I 89
	{ &vop_strategy_desc, spec_strategy },	/* strategy */
E 89
	{ &vop_print_desc, nfs_print },		/* print */
D 89
	{ &vop_islocked_desc, nfs_islocked },		/* islocked */
	{ &vop_advlock_desc, spec_advlock },		/* advlock */
	{ &vop_blkatoff_desc, spec_blkatoff },		/* blkatoff */
E 89
I 89
	{ &vop_islocked_desc, nfs_islocked },	/* islocked */
I 116
	{ &vop_pathconf_desc, spec_pathconf },	/* pathconf */
E 116
	{ &vop_advlock_desc, spec_advlock },	/* advlock */
	{ &vop_blkatoff_desc, spec_blkatoff },	/* blkatoff */
E 89
D 94
	{ &vop_vget_desc, spec_vget },		/* vget */
E 94
D 89
	{ &vop_valloc_desc, spec_valloc },		/* valloc */
	{ &vop_vfree_desc, spec_vfree },		/* vfree */
	{ &vop_truncate_desc, spec_truncate },		/* truncate */
	{ &vop_update_desc, nfs_update },		/* update */
E 89
I 89
	{ &vop_valloc_desc, spec_valloc },	/* valloc */
I 124
	{ &vop_reallocblks_desc, spec_reallocblks },	/* reallocblks */
E 124
	{ &vop_vfree_desc, spec_vfree },	/* vfree */
	{ &vop_truncate_desc, spec_truncate },	/* truncate */
	{ &vop_update_desc, nfs_update },	/* update */
E 89
D 83
	{ &vop_bwrite_desc, bwrite },
E 83
I 83
D 111
	{ &vop_bwrite_desc, vn_bwrite },
E 111
I 111
D 112
	{ &vop_bwrite_desc, nfs_bwrite },
E 112
I 112
	{ &vop_bwrite_desc, vn_bwrite },
E 112
E 111
E 83
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
E 82
E 63
E 50
E 23
E 17
E 16
E 10
E 7
};
I 82
struct vnodeopv_desc spec_nfsv2nodeop_opv_desc =
	{ &spec_nfsv2nodeop_p, spec_nfsv2nodeop_entries };
E 82

I 31
D 133
#ifdef FIFO
E 133
D 57
int	fifo_lookup(),
	fifo_open(),
	fifo_read(),
	fifo_write(),
	fifo_bmap(),
	fifo_ioctl(),
	fifo_select(),
	fifo_close(),
	fifo_print(),
	fifo_badop(),
D 50
	fifo_nullop();
E 50
I 50
D 53
	fifo_nullop(),
E 53
	fifo_advlock();
E 50

E 57
D 82
struct vnodeops fifo_nfsv2nodeops = {
	fifo_lookup,		/* lookup */
D 57
	fifo_badop,		/* create */
	fifo_badop,		/* mknod */
E 57
I 57
	fifo_create,		/* create */
	fifo_mknod,		/* mknod */
E 57
	fifo_open,		/* open */
	fifo_close,		/* close */
	nfs_access,		/* access */
	nfs_getattr,		/* getattr */
	nfs_setattr,		/* setattr */
	fifo_read,		/* read */
	fifo_write,		/* write */
	fifo_ioctl,		/* ioctl */
	fifo_select,		/* select */
D 57
	fifo_badop,		/* mmap */
D 53
	fifo_nullop,		/* fsync */
E 53
I 53
	nullop,			/* fsync */
E 53
	fifo_badop,		/* seek */
	fifo_badop,		/* remove */
	fifo_badop,		/* link */
	fifo_badop,		/* rename */
	fifo_badop,		/* mkdir */
	fifo_badop,		/* rmdir */
	fifo_badop,		/* symlink */
	fifo_badop,		/* readdir */
	fifo_badop,		/* readlink */
	fifo_badop,		/* abortop */
E 57
I 57
	fifo_mmap,		/* mmap */
	fifo_fsync,		/* fsync */
	fifo_seek,		/* seek */
	fifo_remove,		/* remove */
	fifo_link,		/* link */
	fifo_rename,		/* rename */
	fifo_mkdir,		/* mkdir */
	fifo_rmdir,		/* rmdir */
	fifo_symlink,		/* symlink */
	fifo_readdir,		/* readdir */
	fifo_readlink,		/* readlink */
	fifo_abortop,		/* abortop */
E 57
	nfs_inactive,		/* inactive */
	nfs_reclaim,		/* reclaim */
	nfs_lock,		/* lock */
	nfs_unlock,		/* unlock */
	fifo_bmap,		/* bmap */
	fifo_badop,		/* strategy */
	nfs_print,		/* print */
	nfs_islocked,		/* islocked */
I 50
	fifo_advlock,		/* advlock */
I 63
	fifo_blkatoff,		/* blkatoff */
	fifo_vget,		/* vget */
	fifo_valloc,		/* valloc */
	fifo_vfree,		/* vfree */
	fifo_truncate,		/* truncate */
	nfs_update,		/* update */
	bwrite,			/* bwrite */
E 82
I 82
int (**fifo_nfsv2nodeop_p)();
struct vnodeopv_entry_desc fifo_nfsv2nodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
D 89
	{ &vop_lookup_desc, fifo_lookup },		/* lookup */
	{ &vop_create_desc, fifo_create },		/* create */
	{ &vop_mknod_desc, fifo_mknod },		/* mknod */
E 89
I 89
	{ &vop_lookup_desc, fifo_lookup },	/* lookup */
	{ &vop_create_desc, fifo_create },	/* create */
	{ &vop_mknod_desc, fifo_mknod },	/* mknod */
E 89
	{ &vop_open_desc, fifo_open },		/* open */
D 86
	{ &vop_close_desc, fifo_close },		/* close */
E 86
I 86
D 89
	{ &vop_close_desc, nfsfifo_close },		/* close */
E 86
	{ &vop_access_desc, nfs_access },		/* access */
	{ &vop_getattr_desc, nfs_getattr },		/* getattr */
	{ &vop_setattr_desc, nfs_setattr },		/* setattr */
D 86
	{ &vop_read_desc, fifo_read },		/* read */
	{ &vop_write_desc, fifo_write },		/* write */
E 86
I 86
	{ &vop_read_desc, nfsfifo_read },		/* read */
	{ &vop_write_desc, nfsfifo_write },		/* write */
E 86
	{ &vop_ioctl_desc, fifo_ioctl },		/* ioctl */
	{ &vop_select_desc, fifo_select },		/* select */
E 89
I 89
	{ &vop_close_desc, nfsfifo_close },	/* close */
D 102
	{ &vop_access_desc, nfs_access },	/* access */
E 102
I 102
	{ &vop_access_desc, nfsspec_access },	/* access */
E 102
	{ &vop_getattr_desc, nfs_getattr },	/* getattr */
	{ &vop_setattr_desc, nfs_setattr },	/* setattr */
	{ &vop_read_desc, nfsfifo_read },	/* read */
	{ &vop_write_desc, nfsfifo_write },	/* write */
I 128
	{ &vop_lease_desc, fifo_lease_check },	/* lease */
E 128
	{ &vop_ioctl_desc, fifo_ioctl },	/* ioctl */
	{ &vop_select_desc, fifo_select },	/* select */
I 131
	{ &vop_revoke_desc, fifo_revoke },	/* revoke */
E 131
E 89
	{ &vop_mmap_desc, fifo_mmap },		/* mmap */
D 89
	{ &vop_fsync_desc, fifo_fsync },		/* fsync */
E 89
I 89
D 93
	{ &vop_fsync_desc, fifo_fsync },	/* fsync */
E 93
I 93
	{ &vop_fsync_desc, nfs_fsync },		/* fsync */
E 93
E 89
	{ &vop_seek_desc, fifo_seek },		/* seek */
D 89
	{ &vop_remove_desc, fifo_remove },		/* remove */
E 89
I 89
	{ &vop_remove_desc, fifo_remove },	/* remove */
E 89
	{ &vop_link_desc, fifo_link },		/* link */
D 89
	{ &vop_rename_desc, fifo_rename },		/* rename */
	{ &vop_mkdir_desc, fifo_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, fifo_rmdir },		/* rmdir */
	{ &vop_symlink_desc, fifo_symlink },		/* symlink */
	{ &vop_readdir_desc, fifo_readdir },		/* readdir */
	{ &vop_readlink_desc, fifo_readlink },		/* readlink */
	{ &vop_abortop_desc, fifo_abortop },		/* abortop */
	{ &vop_inactive_desc, nfs_inactive },		/* inactive */
	{ &vop_reclaim_desc, nfs_reclaim },		/* reclaim */
E 89
I 89
	{ &vop_rename_desc, fifo_rename },	/* rename */
	{ &vop_mkdir_desc, fifo_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, fifo_rmdir },	/* rmdir */
	{ &vop_symlink_desc, fifo_symlink },	/* symlink */
	{ &vop_readdir_desc, fifo_readdir },	/* readdir */
	{ &vop_readlink_desc, fifo_readlink },	/* readlink */
	{ &vop_abortop_desc, fifo_abortop },	/* abortop */
	{ &vop_inactive_desc, nfs_inactive },	/* inactive */
	{ &vop_reclaim_desc, nfs_reclaim },	/* reclaim */
E 89
	{ &vop_lock_desc, nfs_lock },		/* lock */
D 89
	{ &vop_unlock_desc, nfs_unlock },		/* unlock */
E 89
I 89
	{ &vop_unlock_desc, nfs_unlock },	/* unlock */
E 89
	{ &vop_bmap_desc, fifo_bmap },		/* bmap */
D 89
	{ &vop_strategy_desc, fifo_badop },		/* strategy */
E 89
I 89
	{ &vop_strategy_desc, fifo_badop },	/* strategy */
E 89
	{ &vop_print_desc, nfs_print },		/* print */
D 89
	{ &vop_islocked_desc, nfs_islocked },		/* islocked */
	{ &vop_advlock_desc, fifo_advlock },		/* advlock */
	{ &vop_blkatoff_desc, fifo_blkatoff },		/* blkatoff */
E 89
I 89
	{ &vop_islocked_desc, nfs_islocked },	/* islocked */
I 116
	{ &vop_pathconf_desc, fifo_pathconf },	/* pathconf */
E 116
	{ &vop_advlock_desc, fifo_advlock },	/* advlock */
	{ &vop_blkatoff_desc, fifo_blkatoff },	/* blkatoff */
E 89
D 94
	{ &vop_vget_desc, fifo_vget },		/* vget */
E 94
D 89
	{ &vop_valloc_desc, fifo_valloc },		/* valloc */
	{ &vop_vfree_desc, fifo_vfree },		/* vfree */
	{ &vop_truncate_desc, fifo_truncate },		/* truncate */
	{ &vop_update_desc, nfs_update },		/* update */
E 89
I 89
	{ &vop_valloc_desc, fifo_valloc },	/* valloc */
I 124
	{ &vop_reallocblks_desc, fifo_reallocblks },	/* reallocblks */
E 124
	{ &vop_vfree_desc, fifo_vfree },	/* vfree */
	{ &vop_truncate_desc, fifo_truncate },	/* truncate */
	{ &vop_update_desc, nfs_update },	/* update */
E 89
D 83
	{ &vop_bwrite_desc, bwrite },
E 83
I 83
D 111
	{ &vop_bwrite_desc, vn_bwrite },
E 111
I 111
D 112
	{ &vop_bwrite_desc, nfs_bwrite },
E 112
I 112
	{ &vop_bwrite_desc, vn_bwrite },
E 112
E 111
E 83
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
E 82
E 63
E 50
};
I 82
struct vnodeopv_desc fifo_nfsv2nodeop_opv_desc =
	{ &fifo_nfsv2nodeop_p, fifo_nfsv2nodeop_entries };
E 82
D 133
#endif /* FIFO */
E 133

I 100
void nqnfs_clientlease();
I 133
int nfs_commit();
E 133

E 100
I 57
/*
D 65
 * Global vars
E 65
I 65
 * Global variables
E 65
 */
E 57
E 31
D 133
extern u_long nfs_procids[NFS_NPROCS];
D 102
extern u_long nfs_prog, nfs_vers;
E 102
I 102
extern u_long nfs_prog, nfs_vers, nfs_true, nfs_false;
E 102
D 5
extern struct vnode *cache_lookup();
E 5
extern char nfsiobuf[MAXPHYS+NBPG];
E 133
I 133
extern u_long nfs_true, nfs_false;
extern struct nfsstats nfsstats;
extern nfstype nfsv3_type[9];
E 133
I 26
D 39
extern int nonidempotent[NFS_NPROCS];
E 39
E 26
I 5
D 65
struct map nfsmap[NFS_MSIZ];
E 65
E 5
D 40
enum vtype v_type[NFLNK+1];
E 40
I 5
D 103
struct buf nfs_bqueue;		/* Queue head for nfsiod's */
E 103
D 6
int nfs_iodwant = 0;
E 6
I 6
D 54
int nfs_asyncdaemons = 0;
E 54
D 39
struct proc *nfs_iodwant[MAX_ASYNCDAEMON];
E 39
I 39
struct proc *nfs_iodwant[NFS_MAXASYNCDAEMON];
I 54
int nfs_numasync = 0;
I 103
D 122
/* Queue head for nfsiod's */
D 105
struct buf *nfs_bqueuehead;
struct buf **nfs_bqueuetail = &nfs_bqueuehead;
E 105
I 105
struct queue_entry nfs_bufq;
E 122
E 105
E 103
E 54
E 39
E 6
D 65
static int nfsmap_want = 0;
E 65
I 65
D 68
#define	DIRHDSIZ	(sizeof (struct direct) - (MAXNAMLEN + 1))
E 68
I 68
D 95
#define	DIRHDSIZ	(sizeof (struct readdir) - (MAXNAMLEN + 1))
E 95
I 95
#define	DIRHDSIZ	(sizeof (struct dirent) - (MAXNAMLEN + 1))
E 95
E 68
E 65
E 5

/*
 * nfs null call from vfs.
 */
I 66
int
E 66
D 57
nfs_null(vp, cred)
E 57
I 57
D 65
nfs_null(vp, cred, p)
E 65
I 65
nfs_null(vp, cred, procp)
E 65
E 57
	struct vnode *vp;
	struct ucred *cred;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 65
E 57
{
D 13
	nfsm_vars;
E 13
I 13
	caddr_t bpos, dpos;
D 65
	u_long xid;
E 65
	int error = 0;
	struct mbuf *mreq, *mrep, *md, *mb;
E 13
	
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_NULL], cred, 0);
D 26
	nfsm_request(vp);
E 26
I 26
D 39
	nfsm_request(vp, nonidempotent[NFSPROC_NULL]);
E 39
I 39
D 42
	nfsm_request(vp, NFSPROC_NULL, u.u_procp);
E 42
I 42
D 56
	nfsm_request(vp, NFSPROC_NULL, u.u_procp, 0);
E 56
I 56
D 57
	nfsm_request(vp, NFSPROC_NULL, curproc, 0);
E 57
I 57
	nfsm_request(vp, NFSPROC_NULL, p, 0);
E 65
I 65
	nfsm_reqhead(vp, NFSPROC_NULL, 0);
	nfsm_request(vp, NFSPROC_NULL, procp, cred);
E 65
E 57
E 56
E 42
E 39
E 26
	nfsm_reqdone;
	return (error);
}

/*
 * nfs access vnode op.
D 102
 * Essentially just get vattr and then imitate iaccess()
E 102
I 102
D 133
 * For nfs, just return ok. File accesses may fail later.
 * For nqnfs, use the access rpc to check accessibility. If file modes are
 * changed on the server, accesses might still fail later.
E 133
I 133
 * For nfs version 2, just return ok. File accesses may fail later.
 * For nfs version 3, use the access rpc to check accessibility. If file modes
 * are changed on the server, accesses might still fail later.
E 133
E 102
 */
I 66
int
E 66
D 57
nfs_access(vp, mode, cred)
E 57
I 57
D 65
nfs_access(vp, mode, cred, p)
E 65
I 65
D 82
nfs_access(vp, mode, cred, procp)
E 65
E 57
	struct vnode *vp;
	int mode;
	register struct ucred *cred;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 82
I 82
D 89
nfs_access (ap)
E 89
I 89
nfs_access(ap)
E 89
D 94
	struct vop_access_args *ap;
E 94
I 94
	struct vop_access_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define mode (ap->a_mode)
#define cred (ap->a_cred)
#define procp (ap->a_p)
E 84
E 82
E 65
E 57
{
I 82
D 94
	USES_VOP_GETATTR;
E 94
E 82
D 102
	register struct vattr *vap;
	register gid_t *gp;
I 89
	register struct ucred *cred = ap->a_cred;
	mode_t mode = ap->a_mode;
E 89
	struct vattr vattr;
	register int i;
	int error;
E 102
I 102
	register struct vnode *vp = ap->a_vp;
	register u_long *tl;
	register caddr_t cp;
D 133
	caddr_t bpos, dpos;
	int error = 0;
E 133
I 133
	register int t1, t2;
	caddr_t bpos, dpos, cp2;
	int error = 0, attrflag;
E 133
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
I 133
	u_long mode, rmode;
	int v3 = NFS_ISV3(vp);
E 133
E 102

	/*
I 135
	 * Disallow write attempts on filesystems mounted read-only;
	 * unless the file is a socket, fifo, or a block or character
	 * device resident on the filesystem.
	 */
	if ((ap->a_mode & VWRITE) && (vp->v_mount->mnt_flag & MNT_RDONLY)) {
		switch (vp->v_type) {
		case VREG: case VDIR: case VLNK:
			return (EROFS);
		}
	}
	/*
E 135
D 102
	 * If you're the super-user,
	 * you always get access.
E 102
I 102
D 109
	 * There is no way to check accessibility via. ordinary nfs, so if
	 * access isn't allowed they will get burned later.
E 109
I 109
D 133
	 * For nqnfs, do an access rpc, otherwise you are stuck emulating
E 133
I 133
	 * For nfs v3, do an access rpc, otherwise you are stuck emulating
E 133
	 * ufs_access() locally using the vattr. This may not be correct,
	 * since the server may apply other access criteria such as
	 * client uid-->server uid mapping that we do not know about, but
	 * this is better than just returning anything that is lying about
	 * in the cache.
E 109
E 102
	 */
D 84
	if (cred->cr_uid == 0)
E 84
I 84
D 89
	if (ap->a_cred->cr_uid == 0)
E 89
I 89
D 102
	if (cred->cr_uid == 0)
E 89
E 84
		return (0);
	vap = &vattr;
D 5
	if (nfs_getattrcache(vp, vap)) {
		if (error = nfs_getattr(vp, vap, cred))
			return (error);
	}
E 5
I 5
D 42
	if (error = nfs_getattr(vp, vap, cred))
E 42
I 42
D 57
	if (error = nfs_dogetattr(vp, vap, cred, 0))
E 57
I 57
D 65
	if (error = nfs_dogetattr(vp, vap, cred, 0, p))
E 65
I 65
D 82
	if (error = nfs_getattr(vp, vap, cred, procp))
E 82
I 82
D 84
	if (error = VOP_GETATTR(vp, vap, cred, procp))
E 84
I 84
D 89
	if (error = VOP_GETATTR(ap->a_vp, vap, ap->a_cred, ap->a_p))
E 89
I 89
	if (error = VOP_GETATTR(ap->a_vp, vap, cred, ap->a_p))
E 102
I 102
D 133
	if (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS) {
		nfsstats.rpccnt[NQNFSPROC_ACCESS]++;
		nfsm_reqhead(vp, NQNFSPROC_ACCESS, NFSX_FH + 3 * NFSX_UNSIGNED);
		nfsm_fhtom(vp);
		nfsm_build(tl, u_long *, 3 * NFSX_UNSIGNED);
E 133
I 133
	if (v3) {
		nfsstats.rpccnt[NFSPROC_ACCESS]++;
		nfsm_reqhead(vp, NFSPROC_ACCESS, NFSX_FH(v3) + NFSX_UNSIGNED);
		nfsm_fhtom(vp, v3);
		nfsm_build(tl, u_long *, NFSX_UNSIGNED);
E 133
		if (ap->a_mode & VREAD)
D 133
			*tl++ = nfs_true;
E 133
I 133
			mode = NFSV3ACCESS_READ;
E 133
		else
D 133
			*tl++ = nfs_false;
		if (ap->a_mode & VWRITE)
			*tl++ = nfs_true;
		else
			*tl++ = nfs_false;
		if (ap->a_mode & VEXEC)
			*tl = nfs_true;
		else
			*tl = nfs_false;
		nfsm_request(vp, NQNFSPROC_ACCESS, ap->a_p, ap->a_cred);
E 133
I 133
			mode = 0;
		if (vp->v_type == VDIR) {
			if (ap->a_mode & VWRITE)
				mode |= (NFSV3ACCESS_MODIFY | NFSV3ACCESS_EXTEND |
					 NFSV3ACCESS_DELETE);
			if (ap->a_mode & VEXEC)
				mode |= NFSV3ACCESS_LOOKUP;
		} else {
			if (ap->a_mode & VWRITE)
				mode |= (NFSV3ACCESS_MODIFY | NFSV3ACCESS_EXTEND);
			if (ap->a_mode & VEXEC)
				mode |= NFSV3ACCESS_EXECUTE;
		}
		*tl = txdr_unsigned(mode);
		nfsm_request(vp, NFSPROC_ACCESS, ap->a_p, ap->a_cred);
		nfsm_postop_attr(vp, attrflag);
		if (!error) {
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
			rmode = fxdr_unsigned(u_long, *tl);
			/*
			 * The NFS V3 spec does not clarify whether or not
			 * the returned access bits can be a superset of
			 * the ones requested, so...
			 */
			if ((rmode & mode) != mode)
				error = EACCES;
		}
E 133
		nfsm_reqdone;
E 102
E 89
E 84
E 82
E 65
E 57
E 42
		return (error);
E 5
D 102
	/*
	 * Access check is based on only one of owner, group, public.
	 * If not owner, then check group. If not a member of the
	 * group, then check public access.
	 */
D 84
	if (cred->cr_uid != vap->va_uid) {
		mode >>= 3;
		gp = cred->cr_groups;
		for (i = 0; i < cred->cr_ngroups; i++, gp++)
E 84
I 84
D 89
	if (ap->a_cred->cr_uid != vap->va_uid) {
		ap->a_mode >>= 3;
		gp = ap->a_cred->cr_groups;
		for (i = 0; i < ap->a_cred->cr_ngroups; i++, gp++)
E 89
I 89
	if (cred->cr_uid != vap->va_uid) {
		mode >>= 3;
		gp = cred->cr_groups;
		for (i = 0; i < cred->cr_ngroups; i++, gp++)
E 89
E 84
			if (vap->va_gid == *gp)
				goto found;
D 84
		mode >>= 3;
E 84
I 84
D 89
		ap->a_mode >>= 3;
E 89
I 89
		mode >>= 3;
E 89
E 84
found:
		;
	}
D 84
	if ((vap->va_mode & mode) != 0)
E 84
I 84
D 89
	if ((vap->va_mode & ap->a_mode) != 0)
E 89
I 89
	if ((vap->va_mode & mode) != 0)
E 102
I 102
	} else
E 102
E 89
E 84
D 109
		return (0);
E 109
I 109
		return (nfsspec_access(ap));
E 109
D 102
	return (EACCES);
E 102
}
I 82
D 84
#undef vp
#undef mode
#undef cred
#undef procp
E 84
E 82

/*
 * nfs open vnode op
D 100
 * Just check to see if the type is ok
E 100
I 100
 * Check to see if the type is ok
E 100
I 65
 * and that deletion is not in progress.
I 100
 * For paged in text files, you will need to flush the page cache
 * if consistency is lost.
E 100
E 65
 */
I 13
/* ARGSUSED */
I 66
int
E 66
E 13
D 57
nfs_open(vp, mode, cred)
E 57
I 57
D 65
nfs_open(vp, mode, cred, p)
E 57
	struct vnode *vp;
E 65
I 65
D 82
nfs_open(vp, mode, cred, procp)
	register struct vnode *vp;
E 65
	int mode;
	struct ucred *cred;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 82
I 82
D 89
nfs_open (ap)
E 89
I 89
nfs_open(ap)
E 89
D 94
	struct vop_open_args *ap;
E 94
I 94
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define mode (ap->a_mode)
#define cred (ap->a_cred)
#define procp (ap->a_p)
E 84
E 82
E 65
E 57
{
I 89
	register struct vnode *vp = ap->a_vp;
I 100
	struct nfsnode *np = VTONFS(vp);
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
	struct vattr vattr;
	int error;
E 100
E 89
D 65
	register enum vtype vtyp;
E 65

D 65
	vtyp = vp->v_type;
	if (vtyp == VREG || vtyp == VDIR || vtyp == VLNK)
		return (0);
	else
E 65
I 65
D 84
	if (vp->v_type != VREG && vp->v_type != VDIR && vp->v_type != VLNK)
E 84
I 84
D 89
	if (ap->a_vp->v_type != VREG && ap->a_vp->v_type != VDIR && ap->a_vp->v_type != VLNK)
E 89
I 89
	if (vp->v_type != VREG && vp->v_type != VDIR && vp->v_type != VLNK)
I 133
{ printf("open eacces vtyp=%d\n",vp->v_type);
E 133
E 89
E 84
E 65
		return (EACCES);
I 65
D 84
	if ((VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS) == 0)
		VTONFS(vp)->n_attrstamp = 0; /* For Open/Close consistency */
E 84
I 84
D 89
	if ((VFSTONFS(ap->a_vp->v_mount)->nm_flag & NFSMNT_NQNFS) == 0)
		VTONFS(ap->a_vp)->n_attrstamp = 0; /* For Open/Close consistency */
E 89
I 89
D 100
	if ((VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS) == 0)
		VTONFS(vp)->n_attrstamp = 0; /* For Open/Close consistency */
E 100
I 100
D 133
	if (vp->v_flag & VTEXT) {
	    /*
	     * Get a valid lease. If cached data is stale, flush it.
	     */
	    if (nmp->nm_flag & NFSMNT_NQNFS) {
		if (NQNFS_CKINVALID(vp, np, NQL_READ)) {
E 133
I 133
}
	/*
	 * Get a valid lease. If cached data is stale, flush it.
	 */
	if (nmp->nm_flag & NFSMNT_NQNFS) {
		if (NQNFS_CKINVALID(vp, np, ND_READ)) {
E 133
		    do {
D 133
			error = nqnfs_getlease(vp, NQL_READ, ap->a_cred, ap->a_p);
E 133
I 133
			error = nqnfs_getlease(vp, ND_READ, ap->a_cred,
			    ap->a_p);
E 133
		    } while (error == NQNFS_EXPIRED);
		    if (error)
			return (error);
D 115
		    if (np->n_lrev != np->n_brev) {
E 115
I 115
		    if (np->n_lrev != np->n_brev ||
			(np->n_flag & NQNFSNONCACHE)) {
E 115
D 108
			np->n_flag &= ~NMODIFIED;
			vinvalbuf(vp, TRUE, ap->a_cred, ap->a_p);
E 108
I 108
D 111
			NFS_VINVBUF(np, vp, TRUE, ap->a_cred, ap->a_p);
E 111
I 111
			if ((error = nfs_vinvalbuf(vp, V_SAVE, ap->a_cred,
				ap->a_p, 1)) == EINTR)
				return (error);
E 111
E 108
			(void) vnode_pager_uncache(vp);
			np->n_brev = np->n_lrev;
		    }
		}
D 133
	    } else {
E 133
I 133
	} else {
E 133
		if (np->n_flag & NMODIFIED) {
D 108
			np->n_flag &= ~NMODIFIED;
			vinvalbuf(vp, TRUE, ap->a_cred, ap->a_p);
E 108
I 108
D 111
			NFS_VINVBUF(np, vp, TRUE, ap->a_cred, ap->a_p);
E 111
I 111
			if ((error = nfs_vinvalbuf(vp, V_SAVE, ap->a_cred,
				ap->a_p, 1)) == EINTR)
				return (error);
E 111
E 108
			(void) vnode_pager_uncache(vp);
			np->n_attrstamp = 0;
D 133
			np->n_direofoffset = 0;
			if (error = VOP_GETATTR(vp, &vattr, ap->a_cred, ap->a_p))
E 133
I 133
			if (vp->v_type == VDIR)
				np->n_direofoffset = 0;
			error = VOP_GETATTR(vp, &vattr, ap->a_cred, ap->a_p);
			if (error)
E 133
				return (error);
			np->n_mtime = vattr.va_mtime.ts_sec;
		} else {
D 133
			if (error = VOP_GETATTR(vp, &vattr, ap->a_cred, ap->a_p))
E 133
I 133
			error = VOP_GETATTR(vp, &vattr, ap->a_cred, ap->a_p);
			if (error)
E 133
				return (error);
			if (np->n_mtime != vattr.va_mtime.ts_sec) {
D 133
				np->n_direofoffset = 0;
E 133
I 133
				if (vp->v_type == VDIR)
					np->n_direofoffset = 0;
E 133
D 108
				vinvalbuf(vp, TRUE, ap->a_cred, ap->a_p);
E 108
I 108
D 111
				NFS_VINVBUF(np, vp, TRUE, ap->a_cred, ap->a_p);
E 111
I 111
				if ((error = nfs_vinvalbuf(vp, V_SAVE,
					ap->a_cred, ap->a_p, 1)) == EINTR)
					return (error);
E 111
E 108
				(void) vnode_pager_uncache(vp);
				np->n_mtime = vattr.va_mtime.ts_sec;
			}
		}
D 133
	    }
	} else if ((nmp->nm_flag & NFSMNT_NQNFS) == 0)
E 133
I 133
	}
	if ((nmp->nm_flag & NFSMNT_NQNFS) == 0)
E 133
		np->n_attrstamp = 0; /* For Open/Close consistency */
E 100
E 89
E 84
	return (0);
E 65
}
I 82
D 84
#undef vp
#undef mode
#undef cred
#undef procp
E 84
E 82

/*
 * nfs close vnode op
D 5
 * Nothin to do unless its a VCHR
E 5
I 5
D 133
 * For reg files, invalidate any buffer cache entries.
E 133
I 133
 * What an NFS client should do upon close after writing is a debatable issue.
 * Most NFS clients push delayed writes to the server upon close, basically for
 * two reasons:
 * 1 - So that any write errors may be reported back to the client process
 *     doing the close system call. By far the two most likely errors are
 *     NFSERR_NOSPC and NFSERR_DQUOT to indicate space allocation failure.
 * 2 - To put a worst case upper bound on cache inconsistency between
 *     multiple clients for the file.
 * There is also a consistency problem for Version 2 of the protocol w.r.t.
 * not being able to tell if other clients are writing a file concurrently,
 * since there is no way of knowing if the changed modify time in the reply
 * is only due to the write for this client.
 * (NFS Version 3 provides weak cache consistency data in the reply that
 *  should be sufficient to detect and handle this case.)
 *
 * The current code does the following:
 * for NFS Version 2 - play it safe and flush/invalidate all dirty buffers
 * for NFS Version 3 - flush dirty buffers to the server but don't invalidate
 *                     or commit them (this satisfies 1 and 2 except for the
 *                     case where the server crashes after this close but
 *                     before the commit RPC, which is felt to be "good
 *                     enough". Changing the last argument to nfs_flush() to
 *                     a 1 would force a commit operation, if it is felt a
 *                     commit is necessary now.
 * for NQNFS         - do nothing now, since 2 is dealt with via leases and
 *                     1 should be dealt with via an fsync() system call for
 *                     cases where write errors are important.
E 133
D 10
 * For VCHR, do the device close
E 10
E 5
 */
I 13
/* ARGSUSED */
I 66
int
E 66
E 13
D 57
nfs_close(vp, fflags, cred)
E 57
I 57
D 65
nfs_close(vp, fflags, cred, p)
E 65
I 65
D 82
nfs_close(vp, fflags, cred, procp)
E 65
E 57
	register struct vnode *vp;
	int fflags;
	struct ucred *cred;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 82
I 82
D 89
nfs_close (ap)
E 89
I 89
nfs_close(ap)
E 89
D 93
	struct vop_close_args *ap;
E 93
I 93
	struct vop_close_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode *a_vp;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 93
D 84
#define vp (ap->a_vp)
#define fflags (ap->a_fflag)
#define cred (ap->a_cred)
#define procp (ap->a_p)
E 84
E 82
E 65
E 57
{
I 5
D 13
	struct nfsnode *np = VTONFS(vp);
E 5
	dev_t dev;
E 13
I 13
D 84
	register struct nfsnode *np = VTONFS(vp);
E 84
I 84
D 89
	register struct nfsnode *np = VTONFS(ap->a_vp);
E 89
I 89
	register struct vnode *vp = ap->a_vp;
	register struct nfsnode *np = VTONFS(vp);
E 89
E 84
E 13
D 6
	int error;
E 6
I 6
	int error = 0;
E 6

I 5
D 10
	nfs_lock(vp);
E 10
D 6
	if (vp->v_type == VREG && (np->n_flag & NMODIFIED)) {
		np->n_flag &= ~NMODIFIED;
		nfs_blkflush(vp, (daddr_t)0, np->n_size, TRUE);
E 6
I 6
D 19
	if (vp->v_type == VREG && ((np->n_flag & NMODIFIED) ||
E 19
I 19
D 22
	if (vp->v_type == VREG && vp->v_blockh && ((np->n_flag & NMODIFIED) ||
E 22
I 22
D 39
	if (vp->v_type == VREG && ((np->n_flag & NMODIFIED) ||
E 22
E 19
	   ((np->n_flag & NBUFFERED) && np->n_sillyrename))) {
E 39
I 39
D 65
	if (vp->v_type == VREG && (np->n_flag & NMODIFIED)) {
E 39
I 10
		nfs_lock(vp);
E 65
I 65
D 86
	if ((np->n_flag & NMODIFIED) &&
D 84
	    (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS) == 0 &&
	    vp->v_type == VREG) {
E 84
I 84
	    (VFSTONFS(ap->a_vp->v_mount)->nm_flag & NFSMNT_NQNFS) == 0 &&
	    ap->a_vp->v_type == VREG) {
E 86
I 86
D 89
	if (ap->a_vp->v_type == VREG) {
	    if ((VFSTONFS(ap->a_vp->v_mount)->nm_flag & NFSMNT_NQNFS) == 0 &&
E 89
I 89
	if (vp->v_type == VREG) {
	    if ((VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS) == 0 &&
E 89
		(np->n_flag & NMODIFIED)) {
I 93
D 108
		error = vinvalbuf(vp, TRUE, ap->a_cred, ap->a_p);
E 93
E 86
E 84
E 65
E 10
D 39
		np->n_flag &= ~(NMODIFIED|NBUFFERED);
E 39
I 39
		np->n_flag &= ~NMODIFIED;
E 108
I 108
D 111
		NFS_VINVBUFE(np, vp, TRUE, ap->a_cred, ap->a_p, error);
E 111
I 111
D 133
		error = nfs_vinvalbuf(vp, V_SAVE, ap->a_cred, ap->a_p, 1);
E 133
I 133
		if (NFS_ISV3(vp))
		    error = nfs_flush(vp, ap->a_cred, MNT_WAIT, ap->a_p, 0);
		else
		    error = nfs_vinvalbuf(vp, V_SAVE, ap->a_cred, ap->a_p, 1);
E 133
E 111
E 108
E 39
D 19
		error = nfs_blkflush(vp, (daddr_t)0, np->n_size, TRUE);
E 19
I 19
D 84
		vinvalbuf(vp, TRUE);
E 84
I 84
D 89
		vinvalbuf(ap->a_vp, TRUE);
E 89
I 89
D 93
		vinvalbuf(vp, TRUE);
E 93
E 89
E 84
I 39
		np->n_attrstamp = 0;
E 39
E 19
D 86
		if (np->n_flag & NWRITEERR) {
			np->n_flag &= ~NWRITEERR;
D 19
			if (!error)
				error = np->n_error ? np->n_error : EIO;
E 19
I 19
			error = np->n_error;
E 19
		}
E 86
I 86
	    }
	    if (np->n_flag & NWRITEERR) {
		np->n_flag &= ~NWRITEERR;
		error = np->n_error;
	    }
E 86
I 10
D 65
		nfs_unlock(vp);
E 65
E 10
E 6
	}
D 10
	nfs_unlock(vp);
E 5
	if (vp->v_type != VCHR || vp->v_count > 1)
D 6
		return (0);
E 6
I 6
		return (error);
E 6
	dev = vp->v_rdev;
	/* XXX what is this doing below the vnode op call */
	if (setjmp(&u.u_qsave)) {
		/*
		 * If device close routine is interrupted,
		 * must return so closef can clean up.
		 */
		error = EINTR;
	} else
		error = (*cdevsw[major(dev)].d_close)(dev, fflags, IFCHR);
	/*
	 * Most device close routines don't return errors,
	 * and dup2() doesn't work right on error.
	 */
	error = 0;		/* XXX */
E 10
	return (error);
}
I 82
D 84
#undef vp
#undef fflags
#undef cred
#undef procp
E 84
E 82

/*
 * nfs getattr call from vfs.
 */
I 66
int
E 66
D 57
nfs_getattr(vp, vap, cred)
E 57
I 57
D 65
nfs_getattr(vp, vap, cred, p)
E 65
I 65
D 82
nfs_getattr(vp, vap, cred, procp)
E 65
E 57
D 13
	struct vnode *vp;
	register struct vattr *vap;
E 13
I 13
	register struct vnode *vp;
	struct vattr *vap;
E 13
	struct ucred *cred;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 82
I 82
D 88
nfs_getattr (ap)
E 88
I 88
nfs_getattr(ap)
E 88
D 94
	struct vop_getattr_args *ap;
E 94
I 94
	struct vop_getattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define vap (ap->a_vap)
#define cred (ap->a_cred)
#define procp (ap->a_p)
E 84
E 82
E 65
E 57
{
I 88
	register struct vnode *vp = ap->a_vp;
	register struct nfsnode *np = VTONFS(vp);
E 88
I 42
D 57
	return (nfs_dogetattr(vp, vap, cred, 0));
E 57
I 57
D 65
	return (nfs_dogetattr(vp, vap, cred, 0, p));
E 57
}

D 57
nfs_dogetattr(vp, vap, cred, tryhard)
E 57
I 57
nfs_dogetattr(vp, vap, cred, tryhard, p)
E 57
	register struct vnode *vp;
	struct vattr *vap;
	struct ucred *cred;
	int tryhard;
I 57
	struct proc *p;
E 57
{
E 65
E 42
D 13
	nfsm_vars;
E 13
I 13
	register caddr_t cp;
I 133
	register u_long *tl;
	register int t1, t2;
E 133
D 65
	register long t1;
E 65
	caddr_t bpos, dpos;
D 65
	u_long xid;
E 65
	int error = 0;
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
I 133
	int v3 = NFS_ISV3(vp);
E 133
E 13
	
D 88
	/* First look in the cache.. */
D 84
	if (nfs_getattrcache(vp, vap) == 0)
E 84
I 84
	if (nfs_getattrcache(ap->a_vp, ap->a_vap) == 0)
E 88
I 88
	/*
	 * Update local times for special files.
	 */
D 101
	if (np->n_flag & (NACC | NUPD)) {
		if (np->n_flag & NACC)
			np->n_atim = time;
		if (np->n_flag & NUPD)
			np->n_mtim = time;
E 101
I 101
	if (np->n_flag & (NACC | NUPD))
E 101
		np->n_flag |= NCHG;
D 101
	}
E 101
	/*
	 * First look in the cache.
	 */
	if (nfs_getattrcache(vp, ap->a_vap) == 0)
E 88
E 84
		return (0);
	nfsstats.rpccnt[NFSPROC_GETATTR]++;
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_GETATTR], cred, NFSX_FH);
E 65
I 65
D 84
	nfsm_reqhead(vp, NFSPROC_GETATTR, NFSX_FH);
E 65
	nfsm_fhtom(vp);
D 26
	nfsm_request(vp);
E 26
I 26
D 39
	nfsm_request(vp, nonidempotent[NFSPROC_GETATTR]);
E 39
I 39
D 42
	nfsm_request(vp, NFSPROC_GETATTR, u.u_procp);
E 42
I 42
D 56
	nfsm_request(vp, NFSPROC_GETATTR, u.u_procp, tryhard);
E 56
I 56
D 57
	nfsm_request(vp, NFSPROC_GETATTR, curproc, tryhard);
E 57
I 57
D 65
	nfsm_request(vp, NFSPROC_GETATTR, p, tryhard);
E 65
I 65
	nfsm_request(vp, NFSPROC_GETATTR, procp, cred);
E 65
E 57
E 56
E 42
E 39
E 26
	nfsm_loadattr(vp, vap);
E 84
I 84
D 88
	nfsm_reqhead(ap->a_vp, NFSPROC_GETATTR, NFSX_FH);
	nfsm_fhtom(ap->a_vp);
	nfsm_request(ap->a_vp, NFSPROC_GETATTR, ap->a_p, ap->a_cred);
	nfsm_loadattr(ap->a_vp, ap->a_vap);
E 88
I 88
D 133
	nfsm_reqhead(vp, NFSPROC_GETATTR, NFSX_FH);
	nfsm_fhtom(vp);
E 133
I 133
	nfsm_reqhead(vp, NFSPROC_GETATTR, NFSX_FH(v3));
	nfsm_fhtom(vp, v3);
E 133
	nfsm_request(vp, NFSPROC_GETATTR, ap->a_p, ap->a_cred);
D 133
	nfsm_loadattr(vp, ap->a_vap);
E 133
I 133
	if (!error)
		nfsm_loadattr(vp, ap->a_vap);
E 133
E 88
E 84
	nfsm_reqdone;
	return (error);
}
I 82
D 84
#undef vp
#undef vap
#undef cred
#undef procp
E 84
E 82

/*
 * nfs setattr call.
 */
I 66
int
E 66
D 57
nfs_setattr(vp, vap, cred)
E 57
I 57
D 65
nfs_setattr(vp, vap, cred, p)
E 65
I 65
D 82
nfs_setattr(vp, vap, cred, procp)
E 65
E 57
D 13
	struct vnode *vp;
E 13
I 13
	register struct vnode *vp;
E 13
	register struct vattr *vap;
	struct ucred *cred;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 82
I 82
D 89
nfs_setattr (ap)
E 89
I 89
nfs_setattr(ap)
E 89
D 93
	struct vop_setattr_args *ap;
E 93
I 93
	struct vop_setattr_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 93
D 84
#define vp (ap->a_vp)
#define vap (ap->a_vap)
#define cred (ap->a_cred)
#define procp (ap->a_p)
E 84
E 82
E 65
E 57
{
I 133
	register struct vnode *vp = ap->a_vp;
	register struct nfsnode *np = VTONFS(vp);
	register struct vattr *vap = ap->a_vap;
	int error = 0;
	u_quad_t tsize;

#ifndef nolint
	tsize = (u_quad_t)0;
#endif
I 135
	/*
	 * Disallow write attempts if the filesystem is mounted read-only.
	 */
  	if ((vap->va_flags != VNOVAL || vap->va_uid != (uid_t)VNOVAL ||
	    vap->va_gid != (gid_t)VNOVAL || vap->va_atime.ts_sec != VNOVAL ||
	    vap->va_mtime.ts_sec != VNOVAL || vap->va_mode != (mode_t)VNOVAL) &&
	    (vp->v_mount->mnt_flag & MNT_RDONLY))
		return (EROFS);
E 135
	if (vap->va_size != VNOVAL) {
 		switch (vp->v_type) {
 		case VDIR:
 			return (EISDIR);
 		case VCHR:
 		case VBLK:
I 135
 		case VSOCK:
 		case VFIFO:
E 135
			if (vap->va_mtime.ts_sec == VNOVAL &&
			    vap->va_atime.ts_sec == VNOVAL &&
			    vap->va_mode == (u_short)VNOVAL &&
			    vap->va_uid == (uid_t)VNOVAL &&
			    vap->va_gid == (gid_t)VNOVAL)
				return (0);
 			vap->va_size = VNOVAL;
 			break;
 		default:
I 135
			/*
			 * Disallow write attempts if the filesystem is
			 * mounted read-only.
			 */
			if (vp->v_mount->mnt_flag & MNT_RDONLY)
				return (EROFS);
E 135
 			if (np->n_flag & NMODIFIED) {
 			    if (vap->va_size == 0)
 				error = nfs_vinvalbuf(vp, 0,
 					ap->a_cred, ap->a_p, 1);
 			    else
 				error = nfs_vinvalbuf(vp, V_SAVE,
 					ap->a_cred, ap->a_p, 1);
 			    if (error)
 				return (error);
 			}
 			tsize = np->n_size;
 			np->n_size = np->n_vattr.va_size = vap->va_size;
 			vnode_pager_setsize(vp, (u_long)np->n_size);
  		};
  	} else if ((vap->va_mtime.ts_sec != VNOVAL ||
		vap->va_atime.ts_sec != VNOVAL) && (np->n_flag & NMODIFIED) &&
		vp->v_type == VREG &&
  		(error = nfs_vinvalbuf(vp, V_SAVE, ap->a_cred,
		 ap->a_p, 1)) == EINTR)
		return (error);
	error = nfs_setattrrpc(vp, vap, ap->a_cred, ap->a_p);
	if (error) {
		np->n_size = np->n_vattr.va_size = tsize;
		vnode_pager_setsize(vp, (u_long)np->n_size);
	}
	return (error);
}

/*
 * Do an nfs setattr rpc.
 */
int
nfs_setattrrpc(vp, vap, cred, procp)
	register struct vnode *vp;
	register struct vattr *vap;
	struct ucred *cred;
	struct proc *procp;
{
E 133
I 5
	register struct nfsv2_sattr *sp;
E 5
D 13
	nfsm_vars;
E 13
I 13
	register caddr_t cp;
D 133
	register long t1;
E 133
I 133
	register long t1, t2;
E 133
D 65
	caddr_t bpos, dpos;
	u_long xid;
E 65
I 65
	caddr_t bpos, dpos, cp2;
	u_long *tl;
E 65
D 100
	int error = 0;
E 100
I 100
D 133
	int error = 0, isnq;
E 133
I 133
	int error = 0, wccflag = NFSV3_WCCRATTR;
E 133
E 100
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
E 13
I 7
D 65
	struct nfsnode *np;
E 65
I 65
D 84
	struct nfsnode *np = VTONFS(vp);
E 84
I 84
D 89
	struct nfsnode *np = VTONFS(ap->a_vp);
E 89
I 89
D 133
	register struct vnode *vp = ap->a_vp;
	register struct nfsnode *np = VTONFS(vp);
	register struct vattr *vap = ap->a_vap;
E 89
E 84
D 117
	u_quad_t frev;
E 117
I 117
	u_quad_t frev, tsize;
E 133
I 133
	u_quad_t frev;
	int v3 = NFS_ISV3(vp);
E 133
E 117
E 65
E 7

I 111
D 133
	if (vap->va_size != VNOVAL || vap->va_mtime.ts_sec != VNOVAL ||
		vap->va_atime.ts_sec != VNOVAL) {
		if (vap->va_size != VNOVAL) {
D 126
			if (np->n_flag & NMODIFIED) {
			    if (vap->va_size == 0)
				error = nfs_vinvalbuf(vp, 0, ap->a_cred,
					ap->a_p, 1);
			    else
				error = nfs_vinvalbuf(vp, V_SAVE, ap->a_cred,
					ap->a_p, 1);
			    if (error)
				return (error);
E 126
I 126
			switch (vp->v_type) {
			case VDIR:
				return (EISDIR);
			case VCHR:
			case VBLK:
				vap->va_size = VNOVAL;
				break;
			default:
				if (np->n_flag & NMODIFIED) {
				    if (vap->va_size == 0)
					error = nfs_vinvalbuf(vp, 0,
						ap->a_cred, ap->a_p, 1);
				    else
					error = nfs_vinvalbuf(vp, V_SAVE,
						ap->a_cred, ap->a_p, 1);
				    if (error)
					return (error);
				}
				tsize = np->n_size;
				np->n_size = np->n_vattr.va_size = vap->va_size;
				vnode_pager_setsize(vp, (u_long)np->n_size);
E 133
I 133
	nfsstats.rpccnt[NFSPROC_SETATTR]++;
	nfsm_reqhead(vp, NFSPROC_SETATTR, NFSX_FH(v3) + NFSX_SATTR(v3));
	nfsm_fhtom(vp, v3);
	if (v3) {
		if (vap->va_mode != (u_short)VNOVAL) {
			nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
			*tl++ = nfs_true;
			*tl = txdr_unsigned(vap->va_mode);
		} else {
			nfsm_build(tl, u_long *, NFSX_UNSIGNED);
			*tl = nfs_false;
		}
		if (vap->va_uid != (uid_t)VNOVAL) {
			nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
			*tl++ = nfs_true;
			*tl = txdr_unsigned(vap->va_uid);
		} else {
			nfsm_build(tl, u_long *, NFSX_UNSIGNED);
			*tl = nfs_false;
		}
		if (vap->va_gid != (gid_t)VNOVAL) {
			nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
			*tl++ = nfs_true;
			*tl = txdr_unsigned(vap->va_gid);
		} else {
			nfsm_build(tl, u_long *, NFSX_UNSIGNED);
			*tl = nfs_false;
		}
		if (vap->va_size != VNOVAL) {
			nfsm_build(tl, u_long *, 3 * NFSX_UNSIGNED);
			*tl++ = nfs_true;
			txdr_hyper(&vap->va_size, tl);
		} else {
			nfsm_build(tl, u_long *, NFSX_UNSIGNED);
			*tl = nfs_false;
		}
		if (vap->va_atime.ts_sec != VNOVAL) {
			if (vap->va_atime.ts_sec != time.tv_sec) {
				nfsm_build(tl, u_long *, 3 * NFSX_UNSIGNED);
				*tl++ = txdr_unsigned(NFSV3SATTRTIME_TOCLIENT);
				txdr_nfsv3time(&vap->va_atime, tl);
			} else {
				nfsm_build(tl, u_long *, NFSX_UNSIGNED);
				*tl = txdr_unsigned(NFSV3SATTRTIME_TOSERVER);
E 133
E 126
			}
I 117
D 126
			tsize = np->n_size;
E 117
			np->n_size = np->n_vattr.va_size = vap->va_size;
			vnode_pager_setsize(vp, (u_long)np->n_size);
E 126
D 133
		} else if ((np->n_flag & NMODIFIED) &&
			(error = nfs_vinvalbuf(vp, V_SAVE, ap->a_cred,
			 ap->a_p, 1)) == EINTR)
			return (error);
	}
E 111
	nfsstats.rpccnt[NFSPROC_SETATTR]++;
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_SETATTR], cred, NFSX_FH+NFSX_SATTR);
E 65
I 65
D 84
	nfsm_reqhead(vp, NFSPROC_SETATTR, NFSX_FH+NFSX_SATTR);
E 65
	nfsm_fhtom(vp);
E 84
I 84
D 89
	nfsm_reqhead(ap->a_vp, NFSPROC_SETATTR, NFSX_FH+NFSX_SATTR);
	nfsm_fhtom(ap->a_vp);
E 89
I 89
D 100
	nfsm_reqhead(vp, NFSPROC_SETATTR, NFSX_FH+NFSX_SATTR);
E 100
I 100
	isnq = (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS);
	nfsm_reqhead(vp, NFSPROC_SETATTR, NFSX_FH+NFSX_SATTR(isnq));
E 100
	nfsm_fhtom(vp);
E 89
E 84
D 5
	nfsm_build(p, u_long *, NFSX_SATTR);
E 5
I 5
D 100
	nfsm_build(sp, struct nfsv2_sattr *, NFSX_SATTR);
E 5
D 84
	if (vap->va_mode == 0xffff)
E 84
I 84
D 89
	if (ap->a_vap->va_mode == 0xffff)
E 89
I 89
	if (vap->va_mode == 0xffff)
E 100
I 100
	nfsm_build(sp, struct nfsv2_sattr *, NFSX_SATTR(isnq));
	if (vap->va_mode == (u_short)-1)
E 100
E 89
E 84
D 5
		*p++ = VNOVAL;
E 5
I 5
		sp->sa_mode = VNOVAL;
E 5
	else
D 5
		*p++ = vtonfs_mode(vp->v_type, vap->va_mode);
E 5
I 5
D 84
		sp->sa_mode = vtonfs_mode(vp->v_type, vap->va_mode);
E 5
	if (vap->va_uid == 0xffff)
E 84
I 84
D 89
		sp->sa_mode = vtonfs_mode(ap->a_vp->v_type, ap->a_vap->va_mode);
	if (ap->a_vap->va_uid == 0xffff)
E 89
I 89
		sp->sa_mode = vtonfs_mode(vp->v_type, vap->va_mode);
D 100
	if (vap->va_uid == 0xffff)
E 100
I 100
	if (vap->va_uid == (uid_t)-1)
E 100
E 89
E 84
D 5
		*p++ = VNOVAL;
E 5
I 5
		sp->sa_uid = VNOVAL;
E 5
	else
D 5
		*p++ = txdr_unsigned(vap->va_uid);
E 5
I 5
D 84
		sp->sa_uid = txdr_unsigned(vap->va_uid);
E 5
	if (vap->va_gid == 0xffff)
E 84
I 84
D 89
		sp->sa_uid = txdr_unsigned(ap->a_vap->va_uid);
	if (ap->a_vap->va_gid == 0xffff)
E 89
I 89
		sp->sa_uid = txdr_unsigned(vap->va_uid);
D 100
	if (vap->va_gid == 0xffff)
E 100
I 100
	if (vap->va_gid == (gid_t)-1)
E 100
E 89
E 84
D 5
		*p++ = VNOVAL;
E 5
I 5
		sp->sa_gid = VNOVAL;
E 5
	else
D 5
		*p++ = txdr_unsigned(vap->va_gid);
	*p++ = txdr_unsigned(vap->va_size);
	txdr_time(&(vap->va_atime), p);
	p += 2;
	txdr_time(&(vap->va_mtime), p);
E 5
I 5
D 84
		sp->sa_gid = txdr_unsigned(vap->va_gid);
	sp->sa_size = txdr_unsigned(vap->va_size);
D 7
	if (vap->va_size != VNOVAL)
		VTONFS(vp)->n_size = vap->va_size;
E 7
I 7
D 46
	if (vap->va_size != VNOVAL) {
E 46
I 46
	sp->sa_atime.tv_sec = txdr_unsigned(vap->va_atime.tv_sec);
	sp->sa_atime.tv_usec = txdr_unsigned(vap->va_flags);
	txdr_time(&vap->va_mtime, &sp->sa_mtime);
	if (vap->va_size != VNOVAL || vap->va_mtime.tv_sec != VNOVAL ||
	    vap->va_atime.tv_sec != VNOVAL) {
E 84
I 84
D 89
		sp->sa_gid = txdr_unsigned(ap->a_vap->va_gid);
	sp->sa_size = txdr_unsigned(ap->a_vap->va_size);
	sp->sa_atime.tv_sec = txdr_unsigned(ap->a_vap->va_atime.tv_sec);
	sp->sa_atime.tv_usec = txdr_unsigned(ap->a_vap->va_flags);
	txdr_time(&ap->a_vap->va_mtime, &sp->sa_mtime);
	if (ap->a_vap->va_size != VNOVAL || ap->a_vap->va_mtime.tv_sec != VNOVAL ||
	    ap->a_vap->va_atime.tv_sec != VNOVAL) {
E 89
I 89
		sp->sa_gid = txdr_unsigned(vap->va_gid);
D 100
	sp->sa_size = txdr_unsigned(vap->va_size);
D 92
	sp->sa_atime.tv_sec = txdr_unsigned(vap->va_atime.tv_sec);
E 92
I 92
	sp->sa_atime.tv_sec = txdr_unsigned(vap->va_atime.ts_sec);
E 92
	sp->sa_atime.tv_usec = txdr_unsigned(vap->va_flags);
	txdr_time(&vap->va_mtime, &sp->sa_mtime);
E 100
I 100
	if (isnq) {
		txdr_hyper(&vap->va_size, &sp->sa_nqsize);
		txdr_nqtime(&vap->va_atime, &sp->sa_nqatime);
		txdr_nqtime(&vap->va_mtime, &sp->sa_nqmtime);
		sp->sa_nqflags = txdr_unsigned(vap->va_flags);
		sp->sa_nqrdev = VNOVAL;
E 133
I 133
		} else {
			nfsm_build(tl, u_long *, NFSX_UNSIGNED);
			*tl = txdr_unsigned(NFSV3SATTRTIME_DONTCHANGE);
		}
		if (vap->va_mtime.ts_sec != VNOVAL) {
			if (vap->va_mtime.ts_sec != time.tv_sec) {
				nfsm_build(tl, u_long *, 3 * NFSX_UNSIGNED);
				*tl++ = txdr_unsigned(NFSV3SATTRTIME_TOCLIENT);
				txdr_nfsv3time(&vap->va_atime, tl);
			} else {
				nfsm_build(tl, u_long *, NFSX_UNSIGNED);
				*tl = txdr_unsigned(NFSV3SATTRTIME_TOSERVER);
			}
		} else {
			nfsm_build(tl, u_long *, NFSX_UNSIGNED);
			*tl = txdr_unsigned(NFSV3SATTRTIME_DONTCHANGE);
		}
		nfsm_build(tl, u_long *, NFSX_UNSIGNED);
		*tl = nfs_false;
E 133
	} else {
D 133
		sp->sa_nfssize = txdr_unsigned(vap->va_size);
D 113
		sp->sa_nfsatime.nfs_sec = txdr_unsigned(vap->va_atime.ts_sec);
		sp->sa_nfsatime.nfs_usec = txdr_unsigned(vap->va_flags);
E 113
I 113
		txdr_nfstime(&vap->va_atime, &sp->sa_nfsatime);
E 113
		txdr_nfstime(&vap->va_mtime, &sp->sa_nfsmtime);
E 133
I 133
		nfsm_build(sp, struct nfsv2_sattr *, NFSX_V2SATTR);
		if (vap->va_mode == (u_short)VNOVAL)
			sp->sa_mode = VNOVAL;
		else
			sp->sa_mode = vtonfsv2_mode(vp->v_type, vap->va_mode);
		if (vap->va_uid == (uid_t)VNOVAL)
			sp->sa_uid = VNOVAL;
		else
			sp->sa_uid = txdr_unsigned(vap->va_uid);
		if (vap->va_gid == (gid_t)VNOVAL)
			sp->sa_gid = VNOVAL;
		else
			sp->sa_gid = txdr_unsigned(vap->va_gid);
		sp->sa_size = txdr_unsigned(vap->va_size);
		txdr_nfsv2time(&vap->va_atime, &sp->sa_atime);
		txdr_nfsv2time(&vap->va_mtime, &sp->sa_mtime);
E 133
	}
E 100
D 92
	if (vap->va_size != VNOVAL || vap->va_mtime.tv_sec != VNOVAL ||
	    vap->va_atime.tv_sec != VNOVAL) {
E 92
I 92
D 111
	if (vap->va_size != VNOVAL || vap->va_mtime.ts_sec != VNOVAL ||
	    vap->va_atime.ts_sec != VNOVAL) {
E 92
E 89
E 84
E 46
D 65
		np = VTONFS(vp);
E 65
		if (np->n_flag & NMODIFIED) {
D 93
			np->n_flag &= ~NMODIFIED;
E 93
D 19
			nfs_blkflush(vp, (daddr_t)0, np->n_size, TRUE);
E 19
I 19
D 22
			if (vp->v_blockh)
				vinvalbuf(vp, TRUE);
E 22
I 22
D 54
			vinvalbuf(vp, TRUE);
E 54
I 54
D 84
			if (vap->va_size == 0)
				vinvalbuf(vp, FALSE);
E 84
I 84
D 89
			if (ap->a_vap->va_size == 0)
				vinvalbuf(ap->a_vp, FALSE);
E 89
I 89
D 108
			if (vap->va_size == 0)
D 93
				vinvalbuf(vp, FALSE);
E 93
I 93
				error =
				    vinvalbuf(vp, FALSE, ap->a_cred, ap->a_p);
E 93
E 89
E 84
			else
D 84
				vinvalbuf(vp, TRUE);
E 84
I 84
D 89
				vinvalbuf(ap->a_vp, TRUE);
E 89
I 89
D 93
				vinvalbuf(vp, TRUE);
E 93
I 93
				error =
				    vinvalbuf(vp, TRUE, ap->a_cred, ap->a_p);
			np->n_flag &= ~NMODIFIED;
E 108
I 108
			NFS_VINVBUFE(np, vp, vap->va_size? TRUE: FALSE,
			             ap->a_cred, ap->a_p, error);
E 108
E 93
E 89
E 84
E 54
I 39
D 65
			np->n_attrstamp = 0;
E 65
E 39
E 22
E 19
		}
I 100
		if (vap->va_size != VNOVAL)
			np->n_size = np->n_vattr.va_size = vap->va_size;
E 100
	}
E 111
E 7
D 19
	txdr_time(&vap->va_atime, &sp->sa_atime);
E 19
I 19
D 46
	sp->sa_atime.tv_sec = txdr_unsigned(vap->va_atime.tv_sec);
	sp->sa_atime.tv_usec = txdr_unsigned(vap->va_flags);
E 19
	txdr_time(&vap->va_mtime, &sp->sa_mtime);
E 46
E 5
D 26
	nfsm_request(vp);
E 26
I 26
D 39
	nfsm_request(vp, nonidempotent[NFSPROC_SETATTR]);
E 39
I 39
D 42
	nfsm_request(vp, NFSPROC_SETATTR, u.u_procp);
E 42
I 42
D 56
	nfsm_request(vp, NFSPROC_SETATTR, u.u_procp, 1);
E 56
I 56
D 57
	nfsm_request(vp, NFSPROC_SETATTR, curproc, 1);
E 57
I 57
D 65
	nfsm_request(vp, NFSPROC_SETATTR, p, 1);
E 65
I 65
D 84
	nfsm_request(vp, NFSPROC_SETATTR, procp, cred);
E 65
E 57
E 56
E 42
E 39
E 26
	nfsm_loadattr(vp, (struct vattr *)0);
D 65
	/* should we fill in any vap fields ?? */
E 65
I 65
	if ((VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS) &&
	    NQNFS_CKCACHABLE(vp, NQL_WRITE)) {
E 84
I 84
D 89
	nfsm_request(ap->a_vp, NFSPROC_SETATTR, ap->a_p, ap->a_cred);
	nfsm_loadattr(ap->a_vp, (struct vattr *)0);
	if ((VFSTONFS(ap->a_vp->v_mount)->nm_flag & NFSMNT_NQNFS) &&
	    NQNFS_CKCACHABLE(ap->a_vp, NQL_WRITE)) {
E 89
I 89
D 133
	nfsm_request(vp, NFSPROC_SETATTR, ap->a_p, ap->a_cred);
	nfsm_loadattr(vp, (struct vattr *)0);
	if ((VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS) &&
	    NQNFS_CKCACHABLE(vp, NQL_WRITE)) {
E 89
E 84
		nfsm_dissect(tl, u_long *, 2*NFSX_UNSIGNED);
		fxdr_hyper(tl, &frev);
D 93
		if (QUADGT(frev, np->n_brev))
E 93
I 93
		if (frev > np->n_brev)
E 93
			np->n_brev = frev;
	}
E 133
I 133
	nfsm_request(vp, NFSPROC_SETATTR, procp, cred);
	if (v3) {
		nfsm_wcc_data(vp, wccflag);
	} else
		nfsm_loadattr(vp, (struct vattr *)0);
E 133
E 65
	nfsm_reqdone;
I 117
D 133
	if (error) {
		np->n_size = np->n_vattr.va_size = tsize;
		vnode_pager_setsize(vp, (u_long)np->n_size);
	}
E 133
E 117
	return (error);
}
I 82
D 84
#undef vp
#undef vap
#undef cred
#undef procp
E 84
E 82

/*
 * nfs lookup call, one step at a time...
 * First look in cache
 * If not found, unlock the directory nfsnode and do the rpc
 */
D 57
nfs_lookup(vp, ndp)
E 57
I 57
D 65
nfs_lookup(vp, ndp, p)
E 65
I 65
D 66
nfs_lookup(vp, ndp, procp)
E 65
E 57
	register struct vnode *vp;
	register struct nameidata *ndp;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 66
I 66
int
D 67
nfs_lookup(dvp, vpp, cnp)   /* converted to CN */
/* old: nfs_lookup(vp, ndp, procp) */
E 67
I 67
D 82
nfs_lookup(dvp, vpp, cnp)
E 67
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
E 82
I 82
D 89
nfs_lookup (ap)
E 89
I 89
nfs_lookup(ap)
E 89
D 93
	struct vop_lookup_args *ap;
E 93
I 93
	struct vop_lookup_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
	} */ *ap;
E 93
D 84
#define dvp (ap->a_dvp)
#define vpp (ap->a_vpp)
#define cnp (ap->a_cnp)
E 84
E 82
E 66
E 65
E 57
{
I 82
D 94
	USES_VOP_GETATTR;
E 94
I 89
	register struct componentname *cnp = ap->a_cnp;
	register struct vnode *dvp = ap->a_dvp;
I 94
	register struct vnode **vpp = ap->a_vpp;
I 98
	register int flags = cnp->cn_flags;
I 134
	register struct proc *p = cnp->cn_proc;
E 134
E 98
E 94
E 89
E 82
D 133
	register struct vnode *vdp;
E 133
I 133
	register struct vnode *newvp;
E 133
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
	register long t1, t2;
I 65
	struct nfsmount *nmp;
D 123
	struct nfsnode *tp;
E 123
E 65
	caddr_t bpos, dpos, cp2;
D 65
	u_long xid;
E 65
I 65
D 133
	time_t reqtime;
E 133
E 65
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
E 13
D 133
	struct vnode *newvp;
E 133
	long len;
D 133
	nfsv2fh_t *fhp;
E 133
I 133
	nfsfh_t *fhp;
E 133
	struct nfsnode *np;
D 13
	int lockparent, wantparent, flag;
	dev_t rdev;
E 13
I 13
D 66
	int lockparent, wantparent, flag, error = 0;
E 66
I 66
D 133
	int lockparent, wantparent, error = 0;
E 66
I 65
	int nqlflag, cachable;
	u_quad_t frev;
E 133
I 133
	int lockparent, wantparent, error = 0, attrflag, fhsize;
	int v3 = NFS_ISV3(dvp);
E 133
E 65
E 13

I 135
	if ((flags & ISLASTCN) && (dvp->v_mount->mnt_flag & MNT_RDONLY) &&
	    (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME))
		return (EROFS);
E 135
D 66
	ndp->ni_dvp = vp;
	ndp->ni_vp = NULL;
	if (vp->v_type != VDIR)
E 66
I 66
D 84
	*vpp = NULL;
	if (dvp->v_type != VDIR)
E 84
I 84
D 94
	*ap->a_vpp = NULL;
E 94
I 94
D 133
	*vpp = NULL;
E 133
I 133
	*vpp = NULLVP;
E 133
E 94
D 89
	if (ap->a_dvp->v_type != VDIR)
E 89
I 89
	if (dvp->v_type != VDIR)
E 89
E 84
E 66
		return (ENOTDIR);
D 66
	lockparent = ndp->ni_nameiop & LOCKPARENT;
D 52
	flag = ndp->ni_nameiop & OPFLAG;
E 52
I 52
	flag = ndp->ni_nameiop & OPMASK;
E 52
	wantparent = ndp->ni_nameiop & (LOCKPARENT|WANTPARENT);
I 65
	nmp = VFSTONFS(vp->v_mount);
	np = VTONFS(vp);
E 65
D 5
#ifdef notyet
	if (vdp = cache_lookup(ndp)) {
		nfsstats.lookupcache_hits++;
E 5
I 5
D 7
#ifndef notyet
E 7
D 6
	if (error = cache_lookup(ndp)) {
E 6
I 6
	if ((error = cache_lookup(ndp)) && error != ENOENT) {
E 66
I 66
D 84
	lockparent = cnp->cn_flags & LOCKPARENT;
	wantparent = cnp->cn_flags & (LOCKPARENT|WANTPARENT);
	nmp = VFSTONFS(dvp->v_mount);
	np = VTONFS(dvp);
	if ((error = cache_lookup(dvp, vpp, cnp)) && error != ENOENT) {
E 84
I 84
D 89
	lockparent = ap->a_cnp->cn_flags & LOCKPARENT;
	wantparent = ap->a_cnp->cn_flags & (LOCKPARENT|WANTPARENT);
	nmp = VFSTONFS(ap->a_dvp->v_mount);
	np = VTONFS(ap->a_dvp);
	if ((error = cache_lookup(ap->a_dvp, ap->a_vpp, ap->a_cnp)) && error != ENOENT) {
E 89
I 89
D 98
	lockparent = cnp->cn_flags & LOCKPARENT;
	wantparent = cnp->cn_flags & (LOCKPARENT|WANTPARENT);
E 98
I 98
	lockparent = flags & LOCKPARENT;
	wantparent = flags & (LOCKPARENT|WANTPARENT);
E 98
	nmp = VFSTONFS(dvp->v_mount);
	np = VTONFS(dvp);
D 94
	if ((error = cache_lookup(dvp, ap->a_vpp, cnp)) && error != ENOENT) {
E 94
I 94
	if ((error = cache_lookup(dvp, vpp, cnp)) && error != ENOENT) {
E 94
E 89
E 84
E 66
E 6
		struct vattr vattr;
		int vpid;

I 49
D 59
#ifdef PARANOID
E 49
D 10
		if (ndp->ni_vp == ndp->ni_rdir && ndp->ni_isdotdot)
			vdp = vp;
		else
			vdp = ndp->ni_vp;
E 10
I 10
		if (vp == ndp->ni_rdir && ndp->ni_isdotdot)
			panic("nfs_lookup: .. through root");
I 49
#endif
E 59
E 49
D 66
		vdp = ndp->ni_vp;
E 66
I 66
D 84
		vdp = *vpp;
E 84
I 84
D 94
		vdp = *ap->a_vpp;
E 94
I 94
D 133
		vdp = *vpp;
E 94
E 84
E 66
E 10
		vpid = vdp->v_id;
E 133
I 133
		newvp = *vpp;
		vpid = newvp->v_id;
E 133
E 5
		/*
D 5
		 * Get the next vnode in the path.
		 * See comment above `IUNLOCK' code for
		 * an explaination of the locking protocol.
E 5
I 5
		 * See the comment starting `Step through' in ufs/ufs_lookup.c
		 * for an explanation of the locking protocol
E 5
		 */
D 66
		if (vp == vdp) {
E 66
I 66
D 84
		if (dvp == vdp) {
E 84
I 84
D 89
		if (ap->a_dvp == vdp) {
E 89
I 89
D 133
		if (dvp == vdp) {
E 89
E 84
E 66
D 2
			vdp->v_count++;
E 2
I 2
			VREF(vdp);
E 133
I 133
		if (dvp == newvp) {
			VREF(newvp);
E 133
I 10
			error = 0;
E 10
E 2
D 65
		} else if (ndp->ni_isdotdot) {
			nfs_unlock(vp);
E 65
I 65
		} else
E 65
D 10
			nfs_ngrab(VTONFS(vdp));
E 10
I 10
D 122
			error = vget(vdp);
E 122
I 122
D 133
			error = vget(vdp, 1);
E 133
I 133
D 134
			error = vget(newvp, 1);
E 134
I 134
			error = vget(newvp, LK_EXCLUSIVE, p);
E 134
E 133
E 122
I 55
D 65
			if (!error && lockparent && *ndp->ni_next == '\0')
				nfs_lock(vp);
E 55
E 10
		} else {
D 10
			nfs_ngrab(VTONFS(vdp));
E 10
I 10
			error = vget(vdp);
E 10
D 55
			nfs_unlock(vp);
E 55
I 55
			if (!lockparent || error || *ndp->ni_next != '\0')
				nfs_unlock(vp);
E 55
		}
E 65
D 5
		ndp->ni_vp = vdp;
		return (0);
E 5
I 5
D 10
		if (vpid == vdp->v_id &&
D 6
		   !nfs_getattr(vp, &vattr, ndp->ni_cred)) {
E 6
I 6
		   !nfs_getattr(vdp, &vattr, ndp->ni_cred)) {
E 6
			nfsstats.lookupcache_hits++;
I 6
D 7
			if (vdp->v_type == VNON) {
				vdp->v_type = vattr.va_type;
				VTONFS(vdp)->n_mtime = vattr.va_mtime.tv_sec;
			}
E 7
E 6
			return (0);
E 10
I 10
		if (!error) {
D 30
			if (vpid == vdp->v_id &&
			   !nfs_getattr(vdp, &vattr, ndp->ni_cred)) {
E 30
I 30
D 133
			if (vpid == vdp->v_id) {
D 42
			   if (!nfs_getattr(vdp, &vattr, ndp->ni_cred) &&
E 42
I 42
D 57
			   if (!nfs_dogetattr(vdp, &vattr, ndp->ni_cred, 0) &&
E 57
I 57
D 65
			   if (!nfs_dogetattr(vdp, &vattr, ndp->ni_cred, 0, p)&&
E 65
I 65
			   if (nmp->nm_flag & NFSMNT_NQNFS) {
D 66
			        if (NQNFS_CKCACHABLE(vp, NQL_READ)) {
E 66
I 66
D 84
			        if (NQNFS_CKCACHABLE(dvp, NQL_READ)) {
E 84
I 84
D 89
			        if (NQNFS_CKCACHABLE(ap->a_dvp, NQL_READ)) {
E 89
I 89
D 100
			        if (NQNFS_CKCACHABLE(dvp, NQL_READ)) {
E 100
I 100
				if ((nmp->nm_flag & NFSMNT_NQLOOKLEASE) == 0) {
					nfsstats.lookupcache_hits++;
					if (cnp->cn_nameiop != LOOKUP &&
					    (flags & ISLASTCN))
					    cnp->cn_flags |= SAVENAME;
					return (0);
			        } else if (NQNFS_CKCACHABLE(dvp, NQL_READ)) {
E 100
E 89
E 84
E 66
D 93
					if (QUADNE(np->n_lrev, np->n_brev) ||
E 93
I 93
					if (np->n_lrev != np->n_brev ||
E 93
					    (np->n_flag & NMODIFIED)) {
						np->n_direofoffset = 0;
D 66
						cache_purge(vp);
E 66
I 66
D 84
						cache_purge(dvp);
E 84
I 84
D 89
						cache_purge(ap->a_dvp);
E 89
I 89
						cache_purge(dvp);
I 93
D 108
						error = vinvalbuf(dvp, FALSE,
						    cnp->cn_cred, cnp->cn_proc);
E 93
E 89
E 84
E 66
						np->n_flag &= ~NMODIFIED;
E 108
I 108
D 111
						NFS_VINVBUFE(np, dvp, FALSE,
E 111
I 111
						error = nfs_vinvalbuf(dvp, 0,
E 111
						    cnp->cn_cred, cnp->cn_proc,
D 111
						    error);
E 111
I 111
						    1);
						if (error == EINTR)
							return (error);
E 111
E 108
D 66
						vinvalbuf(vp, FALSE);
E 66
I 66
D 84
						vinvalbuf(dvp, FALSE);
E 84
I 84
D 89
						vinvalbuf(ap->a_dvp, FALSE);
E 89
I 89
D 93
						vinvalbuf(dvp, FALSE);
E 93
E 89
E 84
E 66
						np->n_brev = np->n_lrev;
					} else {
						nfsstats.lookupcache_hits++;
D 66
						if (flag != LOOKUP &&
						    *ndp->ni_next == '\0')
						    ndp->ni_nameiop |= SAVENAME;
E 66
I 66
D 84
						if (cnp->cn_nameiop != LOOKUP &&
						    (cnp->cn_flags&ISLASTCN))
						    cnp->cn_flags |= SAVENAME;
E 84
I 84
D 89
						if (ap->a_cnp->cn_nameiop != LOOKUP &&
						    (ap->a_cnp->cn_flags&ISLASTCN))
						    ap->a_cnp->cn_flags |= SAVENAME;
E 89
I 89
						if (cnp->cn_nameiop != LOOKUP &&
D 98
						    (cnp->cn_flags&ISLASTCN))
E 98
I 98
						    (flags & ISLASTCN))
E 98
						    cnp->cn_flags |= SAVENAME;
E 89
E 84
E 66
						return (0);
					}
				}
D 66
			   } else if (!nfs_getattr(vdp, &vattr, ndp->ni_cred, procp) &&
E 66
I 66
D 82
			   } else if (!nfs_getattr(vdp, &vattr, cnp->cn_cred, cnp->cn_proc) &&
E 82
I 82
D 84
			   } else if (!VOP_GETATTR(vdp, &vattr, cnp->cn_cred, cnp->cn_proc) &&
E 84
I 84
D 89
			   } else if (!VOP_GETATTR(vdp, &vattr, ap->a_cnp->cn_cred, ap->a_cnp->cn_proc) &&
E 89
I 89
			   } else if (!VOP_GETATTR(vdp, &vattr, cnp->cn_cred, cnp->cn_proc) &&
E 89
E 84
E 82
E 66
E 65
E 57
E 42
D 92
			       vattr.va_ctime.tv_sec == VTONFS(vdp)->n_ctime) {
E 92
I 92
			       vattr.va_ctime.ts_sec == VTONFS(vdp)->n_ctime) {
E 133
I 133
			if (vpid == newvp->v_id) {
			   if (!VOP_GETATTR(newvp, &vattr, cnp->cn_cred, cnp->cn_proc)
			    && vattr.va_ctime.ts_sec == VTONFS(newvp)->n_ctime) {
E 133
E 92
E 30
				nfsstats.lookupcache_hits++;
I 59
D 60
				if (flag != LOOKUP)
E 60
I 60
D 65
				if (flag != LOOKUP && *ndp->ni_next == 0)
E 65
I 65
D 66
				if (flag != LOOKUP && *ndp->ni_next == '\0')
E 65
E 60
					ndp->ni_nameiop |= SAVENAME;
E 66
I 66
D 84
				if (cnp->cn_nameiop != LOOKUP && (cnp->cn_flags&ISLASTCN))
					cnp->cn_flags |= SAVENAME;
E 84
I 84
D 89
				if (ap->a_cnp->cn_nameiop != LOOKUP && (ap->a_cnp->cn_flags&ISLASTCN))
					ap->a_cnp->cn_flags |= SAVENAME;
E 89
I 89
				if (cnp->cn_nameiop != LOOKUP &&
D 98
				    (cnp->cn_flags&ISLASTCN))
E 98
I 98
				    (flags & ISLASTCN))
E 98
					cnp->cn_flags |= SAVENAME;
E 89
E 84
E 66
E 59
				return (0);
I 30
D 55
			   } else {
				cache_purge(vdp);
				nfs_nput(vdp);
E 55
			   }
E 30
D 55
			} else {
				nfs_nput(vdp);
E 55
I 55
D 133
			   cache_purge(vdp);
E 133
I 133
			   cache_purge(newvp);
E 133
E 55
			}
I 55
D 65
			nfs_nput(vdp);
			if (lockparent && vdp != vp && *ndp->ni_next == '\0')
				nfs_unlock(vp);
E 65
I 65
D 133
			vrele(vdp);
E 133
I 133
			vrele(newvp);
E 133
E 65
E 55
E 10
		}
D 10
		nfs_nput(vdp);
E 10
D 19
		nfs_lock(vp);
E 19
D 37
		ndp->ni_vp = (struct vnode *)0;
E 37
I 37
D 66
		ndp->ni_vp = NULLVP;
E 66
I 66
D 84
		*vpp = NULLVP;
E 84
I 84
D 94
		*ap->a_vpp = NULLVP;
E 94
I 94
		*vpp = NULLVP;
E 94
E 84
E 66
E 37
E 5
D 19
	}
E 19
I 19
D 65
	} else
		nfs_unlock(vp);
E 65
I 65
	}
E 65
E 19
I 6
	error = 0;
I 133
	newvp = NULLVP;
E 133
E 6
	nfsstats.lookupcache_misses++;
D 2
#endif notyet
E 2
I 2
D 7
#endif
E 7
E 2
	nfsstats.rpccnt[NFSPROC_LOOKUP]++;
D 66
	len = ndp->ni_namelen;
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_LOOKUP], ndp->ni_cred, NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(len));
E 65
I 65
	nfsm_reqhead(vp, NFSPROC_LOOKUP, NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(len));
E 66
I 66
D 84
	len = cnp->cn_namelen;
	nfsm_reqhead(dvp, NFSPROC_LOOKUP, NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(len));
E 84
I 84
D 89
	len = ap->a_cnp->cn_namelen;
	nfsm_reqhead(ap->a_dvp, NFSPROC_LOOKUP, NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(len));
E 89
I 89
	len = cnp->cn_namelen;
D 133
	nfsm_reqhead(dvp, NFSPROC_LOOKUP, NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(len));
E 89
E 84
E 66

	/*
	 * For nqnfs optionally piggyback a getlease request for the name
	 * being looked up.
	 */
	if (nmp->nm_flag & NFSMNT_NQNFS) {
I 100
		nfsm_build(tl, u_long *, NFSX_UNSIGNED);
E 100
		if ((nmp->nm_flag & NFSMNT_NQLOOKLEASE) &&
D 66
		    (ndp->ni_makeentry && (flag != DELETE || *ndp->ni_next))) {
E 66
I 66
D 84
		    ((cnp->cn_flags&MAKEENTRY) && (cnp->cn_nameiop != DELETE || !(cnp->cn_flags&ISLASTCN)))) {
E 84
I 84
D 89
		    ((ap->a_cnp->cn_flags&MAKEENTRY) && (ap->a_cnp->cn_nameiop != DELETE || !(ap->a_cnp->cn_flags&ISLASTCN)))) {
E 89
I 89
D 98
		    ((cnp->cn_flags&MAKEENTRY) &&
		    (cnp->cn_nameiop != DELETE || !(cnp->cn_flags&ISLASTCN)))) {
E 98
I 98
		    ((cnp->cn_flags & MAKEENTRY) &&
D 100
		    (cnp->cn_nameiop != DELETE || !(flags & ISLASTCN)))) {
E 98
E 89
E 84
E 66
			nfsm_build(tl, u_long *, 2*NFSX_UNSIGNED);
			*tl++ = txdr_unsigned(NQL_READ);
E 100
I 100
		    (cnp->cn_nameiop != DELETE || !(flags & ISLASTCN))))
E 100
			*tl = txdr_unsigned(nmp->nm_leaseterm);
D 100
		} else {
			nfsm_build(tl, u_long *, NFSX_UNSIGNED);
E 100
I 100
		else
E 100
			*tl = 0;
D 100
		}
E 100
	}
E 65
D 66
	nfsm_fhtom(vp);
	nfsm_strtom(ndp->ni_ptr, len, NFS_MAXNAMLEN);
E 66
I 66
D 84
	nfsm_fhtom(dvp);
	nfsm_strtom(cnp->cn_nameptr, len, NFS_MAXNAMLEN);
E 84
I 84
D 89
	nfsm_fhtom(ap->a_dvp);
	nfsm_strtom(ap->a_cnp->cn_nameptr, len, NFS_MAXNAMLEN);
E 89
I 89
	nfsm_fhtom(dvp);
E 133
I 133
	nfsm_reqhead(dvp, NFSPROC_LOOKUP,
		NFSX_FH(v3) + NFSX_UNSIGNED + nfsm_rndup(len));
	nfsm_fhtom(dvp, v3);
E 133
	nfsm_strtom(cnp->cn_nameptr, len, NFS_MAXNAMLEN);
E 89
E 84
E 66
D 26
	nfsm_request(vp);
E 26
I 26
D 39
	nfsm_request(vp, nonidempotent[NFSPROC_LOOKUP]);
E 39
I 39
D 42
	nfsm_request(vp, NFSPROC_LOOKUP, u.u_procp);
E 42
I 42
D 56
	nfsm_request(vp, NFSPROC_LOOKUP, u.u_procp, 0);
E 56
I 56
D 57
	nfsm_request(vp, NFSPROC_LOOKUP, curproc, 0);
E 57
I 57
D 65
	nfsm_request(vp, NFSPROC_LOOKUP, p, 0);
E 65
I 65
D 133
	reqtime = time.tv_sec;
E 133
D 66
	nfsm_request(vp, NFSPROC_LOOKUP, procp, ndp->ni_cred);
E 66
I 66
D 84
	nfsm_request(dvp, NFSPROC_LOOKUP, cnp->cn_proc, cnp->cn_cred);
E 84
I 84
D 89
	nfsm_request(ap->a_dvp, NFSPROC_LOOKUP, ap->a_cnp->cn_proc, ap->a_cnp->cn_cred);
E 89
I 89
	nfsm_request(dvp, NFSPROC_LOOKUP, cnp->cn_proc, cnp->cn_cred);
E 89
E 84
E 66
E 65
E 57
E 56
E 42
E 39
E 26
D 133
nfsmout:
E 133
	if (error) {
I 69
D 84
		if ((cnp->cn_nameiop == CREATE || cnp->cn_nameiop == RENAME) &&
		    (cnp->cn_flags & ISLASTCN) && error == ENOENT)
E 84
I 84
D 89
		if ((ap->a_cnp->cn_nameiop == CREATE || ap->a_cnp->cn_nameiop == RENAME) &&
		    (ap->a_cnp->cn_flags & ISLASTCN) && error == ENOENT)
E 89
I 89
D 133
		if ((cnp->cn_nameiop == CREATE || cnp->cn_nameiop == RENAME) &&
D 98
		    (cnp->cn_flags & ISLASTCN) && error == ENOENT)
E 98
I 98
		    (flags & ISLASTCN) && error == ENOENT)
E 98
E 89
E 84
			error = EJUSTRETURN;
E 69
D 19
		if ((flag == CREATE || flag == RENAME) &&
			*ndp->ni_next == 0) {
			if (!lockparent)
				nfs_unlock(vp);
		}
E 19
I 19
D 65
		if (lockparent || (flag != CREATE && flag != RENAME) ||
		    *ndp->ni_next != 0)
			nfs_lock(vp);
I 59
D 60
		if (flag != LOOKUP)
E 60
I 60
		if (flag != LOOKUP && *ndp->ni_next == 0)
E 65
I 65
D 66
		if (flag != LOOKUP && *ndp->ni_next == '\0')
E 65
E 60
			ndp->ni_nameiop |= SAVENAME;
E 66
I 66
D 84
		if (cnp->cn_nameiop != LOOKUP && (cnp->cn_flags&ISLASTCN))
			cnp->cn_flags |= SAVENAME;
E 84
I 84
D 89
		if (ap->a_cnp->cn_nameiop != LOOKUP && (ap->a_cnp->cn_flags&ISLASTCN))
			ap->a_cnp->cn_flags |= SAVENAME;
E 89
I 89
D 98
		if (cnp->cn_nameiop != LOOKUP && (cnp->cn_flags&ISLASTCN))
E 98
I 98
		if (cnp->cn_nameiop != LOOKUP && (flags & ISLASTCN))
E 98
			cnp->cn_flags |= SAVENAME;
E 89
E 84
E 66
E 59
E 19
D 34
		return (ENOENT);
E 34
I 34
		return (error);
E 133
I 133
		nfsm_postop_attr(dvp, attrflag);
		m_freem(mrep);
		goto nfsmout;
E 133
E 34
	}
D 65
	nfsm_disect(fhp,nfsv2fh_t *,NFSX_FH);
E 65
I 65
D 133
	if (nmp->nm_flag & NFSMNT_NQNFS) {
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
		if (*tl) {
			nqlflag = fxdr_unsigned(int, *tl);
			nfsm_dissect(tl, u_long *, 4*NFSX_UNSIGNED);
			cachable = fxdr_unsigned(int, *tl++);
			reqtime += fxdr_unsigned(int, *tl++);
			fxdr_hyper(tl, &frev);
		} else
			nqlflag = 0;
	}
	nfsm_dissect(fhp, nfsv2fh_t *, NFSX_FH);
E 133
I 133
	nfsm_getfh(fhp, fhsize, v3);
E 133
E 65

	/*
D 65
	 * Handle DELETE and RENAME cases...
E 65
I 65
	 * Handle RENAME case...
E 65
	 */
D 65
	if (flag == DELETE && *ndp->ni_next == 0) {
		if (!bcmp(VTONFS(vp)->n_fh.fh_bytes, (caddr_t)fhp, NFSX_FH)) {
D 2
			vp->v_count++;
E 2
I 2
			VREF(vp);
E 2
			newvp = vp;
			np = VTONFS(vp);
		} else {
			if (error = nfs_nget(vp->v_mount, fhp, &np)) {
I 19
				nfs_lock(vp);
E 19
				m_freem(mrep);
				return (error);
			}
			newvp = NFSTOV(np);
		}
D 11
		if (error = nfs_loadattrcache(newvp, &md, &dpos, (struct vattr *)0)) {
E 11
I 11
		if (error =
		    nfs_loadattrcache(&newvp, &md, &dpos, (struct vattr *)0)) {
I 19
			nfs_lock(vp);
E 19
E 11
			if (newvp != vp)
				nfs_nput(newvp);
			else
D 2
				vp->v_count--;
E 2
I 2
				vrele(vp);
E 2
			m_freem(mrep);
			return (error);
		}
D 5
		newvp->v_type = np->n_vattr.va_type;
E 5
I 5
D 7
		if (newvp->v_type == VNON) {
			newvp->v_type = np->n_vattr.va_type;
			np->n_mtime = np->n_vattr.va_mtime.tv_sec;
		}
E 7
E 5
		ndp->ni_vp = newvp;
D 19
		if (!lockparent)
			nfs_unlock(vp);
E 19
I 19
		if (lockparent || vp == newvp)
			nfs_lock(vp);
E 19
		m_freem(mrep);
I 59
		ndp->ni_nameiop |= SAVENAME;
E 59
		return (0);
	}

E 65
D 66
	if (flag == RENAME && wantparent && *ndp->ni_next == 0) {
E 66
I 66
D 84
	if (cnp->cn_nameiop == RENAME && wantparent && (cnp->cn_flags&ISLASTCN)) {
E 84
I 84
D 89
	if (ap->a_cnp->cn_nameiop == RENAME && wantparent && (ap->a_cnp->cn_flags&ISLASTCN)) {
E 89
I 89
D 98
	if (cnp->cn_nameiop == RENAME && wantparent && (cnp->cn_flags&ISLASTCN)) {
E 98
I 98
	if (cnp->cn_nameiop == RENAME && wantparent && (flags & ISLASTCN)) {
E 98
E 89
E 84
E 66
D 65
		if (!bcmp(VTONFS(vp)->n_fh.fh_bytes, (caddr_t)fhp, NFSX_FH)) {
I 19
			nfs_lock(vp);
E 65
I 65
D 133
		if (!bcmp(np->n_fh.fh_bytes, (caddr_t)fhp, NFSX_FH)) {
E 133
I 133
		if (NFS_CMPFH(np, fhp, fhsize)) {
E 133
E 65
E 19
			m_freem(mrep);
			return (EISDIR);
		}
D 66
		if (error = nfs_nget(vp->v_mount, fhp, &np)) {
E 66
I 66
D 84
		if (error = nfs_nget(dvp->v_mount, fhp, &np)) {
E 84
I 84
D 89
		if (error = nfs_nget(ap->a_dvp->v_mount, fhp, &np)) {
E 89
I 89
D 133
		if (error = nfs_nget(dvp->v_mount, fhp, &np)) {
E 133
I 133
		if (error = nfs_nget(dvp->v_mount, fhp, fhsize, &np)) {
E 133
E 89
E 84
E 66
I 19
D 65
			nfs_lock(vp);
E 65
E 19
			m_freem(mrep);
			return (error);
		}
		newvp = NFSTOV(np);
D 11
		if (error = nfs_loadattrcache(newvp, &md, &dpos, (struct vattr *)0)) {
E 11
I 11
D 133
		if (error =
		    nfs_loadattrcache(&newvp, &md, &dpos, (struct vattr *)0)) {
I 19
D 65
			nfs_lock(vp);
E 19
E 11
D 2
			if (newvp != vp)
				nfs_nput(newvp);
			else
				vp->v_count--;
E 2
I 2
			nfs_nput(newvp);
E 65
I 65
			vrele(newvp);
E 65
E 2
			m_freem(mrep);
			return (error);
		}
E 133
I 133
		if (v3) {
			nfsm_postop_attr(newvp, attrflag);
			nfsm_postop_attr(dvp, attrflag);
		} else
			nfsm_loadattr(newvp, (struct vattr *)0);
E 133
D 66
		ndp->ni_vp = newvp;
E 66
I 66
D 84
		*vpp = newvp;
E 84
I 84
D 94
		*ap->a_vpp = newvp;
E 94
I 94
		*vpp = newvp;
E 94
E 84
E 66
D 19
		if (!lockparent)
			nfs_unlock(vp);
E 19
I 19
D 65
		if (lockparent)
			nfs_lock(vp);
E 65
I 47
		m_freem(mrep);
I 59
D 66
		ndp->ni_nameiop |= SAVENAME;
E 66
I 66
D 84
		cnp->cn_flags |= SAVENAME;
E 84
I 84
D 89
		ap->a_cnp->cn_flags |= SAVENAME;
E 89
I 89
		cnp->cn_flags |= SAVENAME;
E 89
E 84
E 66
E 59
E 47
E 19
		return (0);
	}

D 65
	if (!bcmp(VTONFS(vp)->n_fh.fh_bytes, (caddr_t)fhp, NFSX_FH)) {
E 65
I 65
D 133
	if (!bcmp(np->n_fh.fh_bytes, (caddr_t)fhp, NFSX_FH)) {
E 133
I 133
	if (NFS_CMPFH(np, fhp, fhsize)) {
E 133
E 65
D 2
		vp->v_count++;
E 2
I 2
D 66
		VREF(vp);
E 2
		newvp = vp;
E 66
I 66
D 84
		VREF(dvp);
		newvp = dvp;
E 84
I 84
D 89
		VREF(ap->a_dvp);
		newvp = ap->a_dvp;
E 89
I 89
		VREF(dvp);
		newvp = dvp;
E 89
E 84
E 66
D 65
		np = VTONFS(vp);
	} else if (ndp->ni_isdotdot) {
D 19
		nfs_unlock(vp);
E 19
		if (error = nfs_nget(vp->v_mount, fhp, &np)) {
			nfs_lock(vp);
			m_freem(mrep);
			return (error);
		}
D 19
		nfs_lock(vp);
E 19
		newvp = NFSTOV(np);
E 65
	} else {
D 66
		if (error = nfs_nget(vp->v_mount, fhp, &np)) {
E 66
I 66
D 84
		if (error = nfs_nget(dvp->v_mount, fhp, &np)) {
E 84
I 84
D 89
		if (error = nfs_nget(ap->a_dvp->v_mount, fhp, &np)) {
E 89
I 89
D 133
		if (error = nfs_nget(dvp->v_mount, fhp, &np)) {
E 133
I 133
		if (error = nfs_nget(dvp->v_mount, fhp, fhsize, &np)) {
E 133
E 89
E 84
E 66
I 19
D 65
			nfs_lock(vp);
E 65
E 19
			m_freem(mrep);
			return (error);
		}
		newvp = NFSTOV(np);
	}
D 11
	if (error = nfs_loadattrcache(newvp, &md, &dpos, (struct vattr *)0)) {
E 11
I 11
D 133
	if (error = nfs_loadattrcache(&newvp, &md, &dpos, (struct vattr *)0)) {
I 19
D 65
		nfs_lock(vp);
E 19
E 11
		if (newvp != vp)
			nfs_nput(newvp);
		else
D 2
			vp->v_count--;
E 2
I 2
			vrele(vp);
E 65
I 65
		vrele(newvp);
E 65
E 2
		m_freem(mrep);
		return (error);
	}
	m_freem(mrep);
D 5
	newvp->v_type = np->n_vattr.va_type;
E 5
I 5
D 7
	if (newvp->v_type == VNON) {
		newvp->v_type = np->n_vattr.va_type;
		np->n_mtime = np->n_vattr.va_mtime.tv_sec;
	}
E 7
E 5
D 65

D 7
	/*
	 * Handling special files...
	 * For VCHR, use the nfs_node, but with the nfsv2chr_vnodeops
	 * that are a mix of nfs and blk vnode ops.
D 5
	 * For VBLK, get a block dev. inode using bdevvp() and release
	 * the nfs_node. This means that ufs_inactive() had better know
	 * how to release inodes that do not have an underlying ufs.
	 * (i_fs == 0)
E 5
	 * Also, returns right away to avoid loading the name cache
	 */
	if (newvp->v_type == VCHR) {
		newvp->v_rdev = np->n_vattr.va_rdev;
		newvp->v_op = &nfsv2chr_vnodeops;
D 5
	} else if (newvp->v_type == VBLK) {
		rdev = np->n_vattr.va_rdev;
		nfs_nput(newvp);
		if (error = bdevvp(rdev, &newvp))
			return (error);
E 5
	}
E 7
D 19
	if (vp != newvp && (!lockparent || *ndp->ni_next != '\0'))
		nfs_unlock(vp);
E 19
I 19
	if (vp == newvp || (lockparent && *ndp->ni_next == '\0'))
		nfs_lock(vp);
E 65
E 19
D 66
	ndp->ni_vp = newvp;
I 59
D 60
	if (flag != LOOKUP)
E 60
I 60
D 65
	if (flag != LOOKUP && *ndp->ni_next == 0)
E 65
I 65
	if (flag != LOOKUP && *ndp->ni_next == '\0')
E 65
E 60
		ndp->ni_nameiop |= SAVENAME;
E 59
D 5
#ifdef notyet
E 5
I 5
D 7
#ifndef notyet
E 7
E 5
D 30
	if (error == 0 && ndp->ni_makeentry)
E 30
I 30
D 65
	if (error == 0 && ndp->ni_makeentry) {
		np->n_ctime = np->n_vattr.va_ctime.tv_sec;
E 65
I 65
	if (ndp->ni_makeentry && (flag != DELETE || *ndp->ni_next)) {
E 66
I 66
D 84
	*vpp = newvp;
	if (cnp->cn_nameiop != LOOKUP && (cnp->cn_flags&ISLASTCN))
		cnp->cn_flags |= SAVENAME;
	if ((cnp->cn_flags&MAKEENTRY) && (cnp->cn_nameiop != DELETE || !(cnp->cn_flags&ISLASTCN))) {
E 84
I 84
D 94
	*ap->a_vpp = newvp;
E 94
I 94
	*vpp = newvp;
E 133
I 133
	if (v3) {
		nfsm_postop_attr(newvp, attrflag);
		nfsm_postop_attr(dvp, attrflag);
	} else
		nfsm_loadattr(newvp, (struct vattr *)0);
E 133
E 94
D 89
	if (ap->a_cnp->cn_nameiop != LOOKUP && (ap->a_cnp->cn_flags&ISLASTCN))
		ap->a_cnp->cn_flags |= SAVENAME;
	if ((ap->a_cnp->cn_flags&MAKEENTRY) && (ap->a_cnp->cn_nameiop != DELETE || !(ap->a_cnp->cn_flags&ISLASTCN))) {
E 89
I 89
D 98
	if (cnp->cn_nameiop != LOOKUP && (cnp->cn_flags&ISLASTCN))
E 98
I 98
	if (cnp->cn_nameiop != LOOKUP && (flags & ISLASTCN))
E 98
		cnp->cn_flags |= SAVENAME;
D 98
	if ((cnp->cn_flags&MAKEENTRY) &&
	    (cnp->cn_nameiop != DELETE || !(cnp->cn_flags&ISLASTCN))) {
E 98
I 98
	if ((cnp->cn_flags & MAKEENTRY) &&
	    (cnp->cn_nameiop != DELETE || !(flags & ISLASTCN))) {
E 98
E 89
E 84
E 66
D 133
		if ((nmp->nm_flag & NFSMNT_NQNFS) == 0)
D 92
			np->n_ctime = np->n_vattr.va_ctime.tv_sec;
E 92
I 92
			np->n_ctime = np->n_vattr.va_ctime.ts_sec;
E 92
D 100
		else if (nqlflag && reqtime > time.tv_sec) {
			if (np->n_tnext) {
				if (np->n_tnext == (struct nfsnode *)nmp)
					nmp->nm_tprev = np->n_tprev;
				else
					np->n_tnext->n_tprev = np->n_tprev;
				if (np->n_tprev == (struct nfsnode *)nmp)
					nmp->nm_tnext = np->n_tnext;
				else
					np->n_tprev->n_tnext = np->n_tnext;
				if (nqlflag == NQL_WRITE)
					np->n_flag |= NQNFSWRITE;
			} else if (nqlflag == NQL_READ)
				np->n_flag &= ~NQNFSWRITE;
			else
				np->n_flag |= NQNFSWRITE;
			if (cachable)
				np->n_flag &= ~NQNFSNONCACHE;
			else
				np->n_flag |= NQNFSNONCACHE;
			np->n_expiry = reqtime;
			np->n_lrev = frev;
			tp = nmp->nm_tprev;
			while (tp != (struct nfsnode *)nmp && tp->n_expiry > np->n_expiry)
				tp = tp->n_tprev;
			if (tp == (struct nfsnode *)nmp) {
				np->n_tnext = nmp->nm_tnext;
				nmp->nm_tnext = np;
			} else {
				np->n_tnext = tp->n_tnext;
				tp->n_tnext = np;
			}
			np->n_tprev = tp;
			if (np->n_tnext == (struct nfsnode *)nmp)
				nmp->nm_tprev = np;
			else
				np->n_tnext->n_tprev = np;
		}
E 100
I 100
		else if (nqlflag && reqtime > time.tv_sec)
			nqnfs_clientlease(nmp, np, nqlflag, cachable, reqtime,
				frev);
E 100
E 65
E 30
D 66
		cache_enter(ndp);
E 66
I 66
D 84
		cache_enter(dvp, *vpp, cnp);
E 84
I 84
D 89
		cache_enter(ap->a_dvp, *ap->a_vpp, ap->a_cnp);
E 89
I 89
D 94
		cache_enter(dvp, *ap->a_vpp, cnp);
E 94
I 94
		cache_enter(dvp, *vpp, cnp);
E 133
I 133
		np->n_ctime = np->n_vattr.va_ctime.ts_sec;
		cache_enter(dvp, newvp, cnp);
E 133
E 94
E 89
E 84
E 66
I 30
	}
E 30
D 2
#endif notyet
E 2
I 2
D 7
#endif
E 7
E 2
D 65
	return (error);
E 65
I 65
D 133
	return (0);
E 133
I 133
	*vpp = newvp;
	nfsm_reqdone;
	if (error) {
		if (newvp != NULLVP)
			vrele(newvp);
		if ((cnp->cn_nameiop == CREATE || cnp->cn_nameiop == RENAME) &&
D 135
		    (flags & ISLASTCN) && error == ENOENT)
			error = EJUSTRETURN;
E 135
I 135
		    (flags & ISLASTCN) && error == ENOENT) {
			if (dvp->v_mount->mnt_flag & MNT_RDONLY)
				error = EROFS;
			else
				error = EJUSTRETURN;
		}
E 135
		if (cnp->cn_nameiop != LOOKUP && (flags & ISLASTCN))
			cnp->cn_flags |= SAVENAME;
	}
	return (error);
E 133
E 65
}
I 82
D 84
#undef dvp
#undef vpp
#undef cnp
E 84
E 82

/*
I 39
 * nfs read call.
 * Just call nfs_bioread() to do the work.
 */
I 66
int
E 66
D 82
nfs_read(vp, uiop, ioflag, cred)
	register struct vnode *vp;
	struct uio *uiop;
	int ioflag;
	struct ucred *cred;
E 82
I 82
D 89
nfs_read (ap)
E 89
I 89
nfs_read(ap)
E 89
D 94
	struct vop_read_args *ap;
E 94
I 94
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define uiop (ap->a_uio)
#define ioflag (ap->a_ioflag)
#define cred (ap->a_cred)
E 84
E 82
{
D 84
	if (vp->v_type != VREG)
E 84
I 84
D 89
	if (ap->a_vp->v_type != VREG)
E 89
I 89
	register struct vnode *vp = ap->a_vp;

	if (vp->v_type != VREG)
E 89
E 84
		return (EPERM);
D 84
	return (nfs_bioread(vp, uiop, ioflag, cred));
E 84
I 84
D 89
	return (nfs_bioread(ap->a_vp, ap->a_uio, ap->a_ioflag, ap->a_cred));
E 89
I 89
	return (nfs_bioread(vp, ap->a_uio, ap->a_ioflag, ap->a_cred));
E 89
E 84
}
I 82
D 84
#undef vp
#undef uiop
#undef ioflag
#undef cred
E 84
E 82

/*
E 39
 * nfs readlink call
 */
I 66
int
E 66
D 82
nfs_readlink(vp, uiop, cred)
I 39
	struct vnode *vp;
	struct uio *uiop;
	struct ucred *cred;
E 82
I 82
D 89
nfs_readlink (ap)
E 89
I 89
nfs_readlink(ap)
E 89
D 94
	struct vop_readlink_args *ap;
E 94
I 94
	struct vop_readlink_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define uiop (ap->a_uio)
#define cred (ap->a_cred)
E 84
E 82
{
D 84
	if (vp->v_type != VLNK)
E 84
I 84
D 89
	if (ap->a_vp->v_type != VLNK)
E 89
I 89
	register struct vnode *vp = ap->a_vp;

	if (vp->v_type != VLNK)
E 89
E 84
		return (EPERM);
D 84
	return (nfs_bioread(vp, uiop, 0, cred));
E 84
I 84
D 89
	return (nfs_bioread(ap->a_vp, ap->a_uio, 0, ap->a_cred));
E 89
I 89
	return (nfs_bioread(vp, ap->a_uio, 0, ap->a_cred));
E 89
E 84
}
I 82
D 84
#undef vp
#undef uiop
#undef cred
E 84
E 82

/*
 * Do a readlink rpc.
 * Called by nfs_doio() from below the buffer cache.
 */
I 66
int
E 66
D 57
nfs_readlinkrpc(vp, uiop, cred, procp)
E 57
I 57
nfs_readlinkrpc(vp, uiop, cred)
E 57
E 39
D 13
	struct vnode *vp;
E 13
I 13
	register struct vnode *vp;
E 13
	struct uio *uiop;
	struct ucred *cred;
I 39
D 57
	struct proc *procp;
E 57
E 39
{
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
D 133
	register long t1;
E 133
I 133
	register long t1, t2;
E 133
	caddr_t bpos, dpos, cp2;
D 65
	u_long xid;
E 65
D 133
	int error = 0;
E 133
I 133
	int error = 0, len, attrflag;
E 133
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
E 13
D 133
	long len;
E 133
I 133
	int v3 = NFS_ISV3(vp);
E 133

	nfsstats.rpccnt[NFSPROC_READLINK]++;
I 39
D 54
	nfs_unlock(vp);
E 54
E 39
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_READLINK], cred, NFSX_FH);
E 65
I 65
D 133
	nfsm_reqhead(vp, NFSPROC_READLINK, NFSX_FH);
E 65
	nfsm_fhtom(vp);
E 133
I 133
	nfsm_reqhead(vp, NFSPROC_READLINK, NFSX_FH(v3));
	nfsm_fhtom(vp, v3);
E 133
I 36
D 39
	nfs_unlock(vp);
E 36
D 26
	nfsm_request(vp);
E 26
I 26
	nfsm_request(vp, nonidempotent[NFSPROC_READLINK]);
E 39
I 39
D 42
	nfsm_request(vp, NFSPROC_READLINK, procp);
E 42
I 42
D 57
	nfsm_request(vp, NFSPROC_READLINK, procp, 0);
E 57
I 57
D 65
	nfsm_request(vp, NFSPROC_READLINK, uiop->uio_procp, 0);
E 65
I 65
	nfsm_request(vp, NFSPROC_READLINK, uiop->uio_procp, cred);
E 65
E 57
E 42
E 39
E 26
D 133
	nfsm_strsiz(len, NFS_MAXPATHLEN);
	nfsm_mtouio(uiop, len);
E 133
I 133
	if (v3)
		nfsm_postop_attr(vp, attrflag);
	if (!error) {
		nfsm_strsiz(len, NFS_MAXPATHLEN);
		nfsm_mtouio(uiop, len);
	}
E 133
	nfsm_reqdone;
I 36
D 54
	nfs_lock(vp);
E 54
E 36
	return (error);
}

/*
D 39
 * nfs read call
E 39
I 39
 * nfs read rpc call
 * Ditto above
E 39
 */
I 66
int
E 66
D 5
nfs_read(vp, uiop, offp, ioflag, cred)
E 5
I 5
D 15
nfs_readrpc(vp, uiop, offp, cred)
E 15
I 15
D 39
nfs_readrpc(vp, uiop, cred)
E 39
I 39
D 57
nfs_readrpc(vp, uiop, cred, procp)
E 57
I 57
nfs_readrpc(vp, uiop, cred)
E 57
E 39
E 15
E 5
D 13
	struct vnode *vp;
E 13
I 13
	register struct vnode *vp;
E 13
	struct uio *uiop;
D 15
	off_t *offp;
E 15
D 5
	int ioflag;
E 5
	struct ucred *cred;
I 39
D 57
	struct proc *procp;
E 57
E 39
{
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
D 133
	register long t1;
E 133
I 133
	register long t1, t2;
E 133
	caddr_t bpos, dpos, cp2;
D 65
	u_long xid;
E 65
D 133
	int error = 0;
E 133
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
E 13
	struct nfsmount *nmp;
D 133
	long len, retlen, tsiz;
E 133
I 133
	int error = 0, len, retlen, tsiz, eof, attrflag;
	int v3 = NFS_ISV3(vp);
E 133

I 133
#ifndef nolint
	eof = 0;
#endif
E 133
D 37
	nmp = vfs_to_nfs(vp->v_mount);
E 37
I 37
	nmp = VFSTONFS(vp->v_mount);
E 37
	tsiz = uiop->uio_resid;
I 100
D 133
	if (uiop->uio_offset + tsiz > 0xffffffff &&
	    (nmp->nm_flag & NFSMNT_NQNFS) == 0)
E 133
I 133
	if (uiop->uio_offset + tsiz > 0xffffffff && !v3)
E 133
		return (EFBIG);
E 100
D 5
	if (!(ioflag & IO_NODELOCKED))
		nfs_lock(vp);
E 5
	while (tsiz > 0) {
		nfsstats.rpccnt[NFSPROC_READ]++;
		len = (tsiz > nmp->nm_rsize) ? nmp->nm_rsize : tsiz;
D 65
		nfsm_reqhead(nfs_procids[NFSPROC_READ], cred, NFSX_FH+NFSX_UNSIGNED*3);
E 65
I 65
D 133
		nfsm_reqhead(vp, NFSPROC_READ, NFSX_FH+NFSX_UNSIGNED*3);
E 65
		nfsm_fhtom(vp);
D 57
		nfsm_build(p, u_long *, NFSX_UNSIGNED*3);
D 15
		*p++ = txdr_unsigned(*offp);
E 15
I 15
		*p++ = txdr_unsigned(uiop->uio_offset);
E 15
		*p++ = txdr_unsigned(len);
		*p = 0;
D 26
		nfsm_request(vp);
E 26
I 26
D 39
		nfsm_request(vp, nonidempotent[NFSPROC_READ]);
E 39
I 39
D 42
		nfsm_request(vp, NFSPROC_READ, procp);
E 42
I 42
		nfsm_request(vp, NFSPROC_READ, procp, 1);
E 57
I 57
		nfsm_build(tl, u_long *, NFSX_UNSIGNED*3);
D 100
		*tl++ = txdr_unsigned(uiop->uio_offset);
		*tl++ = txdr_unsigned(len);
		*tl = 0;
E 100
I 100
		if (nmp->nm_flag & NFSMNT_NQNFS) {
E 133
I 133
		nfsm_reqhead(vp, NFSPROC_READ, NFSX_FH(v3) + NFSX_UNSIGNED * 3);
		nfsm_fhtom(vp, v3);
		nfsm_build(tl, u_long *, NFSX_UNSIGNED * 3);
		if (v3) {
E 133
			txdr_hyper(&uiop->uio_offset, tl);
			*(tl + 2) = txdr_unsigned(len);
		} else {
			*tl++ = txdr_unsigned(uiop->uio_offset);
			*tl++ = txdr_unsigned(len);
			*tl = 0;
		}
E 100
D 65
		nfsm_request(vp, NFSPROC_READ, uiop->uio_procp, 1);
E 65
I 65
		nfsm_request(vp, NFSPROC_READ, uiop->uio_procp, cred);
E 65
E 57
E 42
E 39
E 26
D 133
		nfsm_loadattr(vp, (struct vattr *)0);
E 133
I 133
		if (v3) {
			nfsm_postop_attr(vp, attrflag);
			if (error) {
				m_freem(mrep);
				goto nfsmout;
			}
			nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
			eof = fxdr_unsigned(int, *(tl + 1));
		} else
			nfsm_loadattr(vp, (struct vattr *)0);
E 133
		nfsm_strsiz(retlen, nmp->nm_rsize);
		nfsm_mtouio(uiop, retlen);
		m_freem(mrep);
D 15
		*offp += retlen;
E 15
D 133
		if (retlen < len)
E 133
I 133
		tsiz -= retlen;
		if (v3) {
			if (eof || retlen == 0)
				tsiz = 0;
		} else if (retlen < len)
E 133
			tsiz = 0;
D 133
		else
			tsiz -= len;
E 133
	}
nfsmout:
D 5
	if (!(ioflag & IO_NODELOCKED))
		nfs_unlock(vp);
E 5
	return (error);
}

/*
 * nfs write call
 */
I 66
int
E 66
D 5
nfs_write(vp, uiop, offp, ioflag, cred)
E 5
I 5
D 15
nfs_writerpc(vp, uiop, offp, cred)
E 15
I 15
D 39
nfs_writerpc(vp, uiop, cred)
E 39
I 39
D 57
nfs_writerpc(vp, uiop, cred, procp)
E 57
I 57
D 100
nfs_writerpc(vp, uiop, cred)
E 100
I 100
D 133
nfs_writerpc(vp, uiop, cred, ioflags)
E 133
I 133
nfs_writerpc(vp, uiop, cred, iomode, must_commit)
E 133
E 100
E 57
E 39
E 15
E 5
D 13
	struct vnode *vp;
E 13
I 13
	register struct vnode *vp;
E 13
D 133
	struct uio *uiop;
E 133
I 133
	register struct uio *uiop;
E 133
D 15
	off_t *offp;
E 15
D 5
	int ioflag;
E 5
	struct ucred *cred;
I 100
D 133
	int ioflags;
E 133
I 133
	int *iomode, *must_commit;
E 133
E 100
I 39
D 57
	struct proc *procp;
E 57
E 39
{
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
D 133
	register long t1;
E 133
I 133
	register int t1, t2, backup;
E 133
D 65
	caddr_t bpos, dpos;
	u_long xid;
E 65
I 65
	caddr_t bpos, dpos, cp2;
E 65
D 133
	int error = 0;
E 133
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
E 13
D 133
	struct nfsmount *nmp;
E 133
I 133
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
E 133
I 65
	struct nfsnode *np = VTONFS(vp);
	u_quad_t frev;
E 65
D 133
	long len, tsiz;
E 133
I 133
	int error = 0, len, tsiz, wccflag = NFSV3_WCCRATTR, rlen, commit;
	int v3 = NFS_ISV3(vp), committed = NFSV3WRITE_FILESYNC;
E 133
D 5
	u_long osize;
	off_t ooff;
	struct vattr va;
E 5

D 37
	nmp = vfs_to_nfs(vp->v_mount);
E 37
I 37
D 133
	nmp = VFSTONFS(vp->v_mount);
E 133
I 133
#ifndef DIAGNOSTIC
	if (uiop->uio_iovcnt != 1)
		panic("nfs: writerpc iovcnt > 1");
#endif
	*must_commit = 0;
E 133
E 37
	tsiz = uiop->uio_resid;
I 100
D 133
	if (uiop->uio_offset + tsiz > 0xffffffff &&
	    (nmp->nm_flag & NFSMNT_NQNFS) == 0)
E 133
I 133
	if (uiop->uio_offset + tsiz > 0xffffffff && !v3)
E 133
		return (EFBIG);
E 100
D 5
	if (!(ioflag & IO_NODELOCKED))
		nfs_lock(vp);
	if ((ioflag&IO_UNIT) || (vp->v_type == VREG && (ioflag&IO_APPEND))) {
		if (error = nfs_getattr(vp, &va, cred))
			goto nfsmout;
		osize = va.va_size;
		if (vp->v_type == VREG && (ioflag & IO_APPEND))
			*offp = osize;
		ooff = *offp;
	}
E 5
	while (tsiz > 0) {
		nfsstats.rpccnt[NFSPROC_WRITE]++;
		len = (tsiz > nmp->nm_wsize) ? nmp->nm_wsize : tsiz;
D 65
		nfsm_reqhead(nfs_procids[NFSPROC_WRITE], cred,
			NFSX_FH+NFSX_UNSIGNED*4);
E 65
I 65
		nfsm_reqhead(vp, NFSPROC_WRITE,
D 133
			NFSX_FH+NFSX_UNSIGNED*4+nfsm_rndup(len));
E 65
		nfsm_fhtom(vp);
D 57
		nfsm_build(p, u_long *, NFSX_UNSIGNED*4);
D 15
		*(p+1) = txdr_unsigned(*offp);
E 15
I 15
		*(p+1) = txdr_unsigned(uiop->uio_offset);
E 15
		*(p+3) = txdr_unsigned(len);
E 57
I 57
D 100
		nfsm_build(tl, u_long *, NFSX_UNSIGNED*4);
		*(tl+1) = txdr_unsigned(uiop->uio_offset);
		*(tl+3) = txdr_unsigned(len);
E 100
I 100
		nfsm_build(tl, u_long *, NFSX_UNSIGNED * 4);
		if (nmp->nm_flag & NFSMNT_NQNFS) {
E 133
I 133
			NFSX_FH(v3) + 5 * NFSX_UNSIGNED + nfsm_rndup(len));
		nfsm_fhtom(vp, v3);
		if (v3) {
			nfsm_build(tl, u_long *, 5 * NFSX_UNSIGNED);
E 133
			txdr_hyper(&uiop->uio_offset, tl);
			tl += 2;
D 127
			if (ioflags & IO_APPEND)
				*tl++ = txdr_unsigned(1);
			else
				*tl++ = 0;
E 127
I 127
D 133
			*tl++ = 0;
E 133
I 133
			*tl++ = txdr_unsigned(len);
			*tl++ = txdr_unsigned(*iomode);
E 133
E 127
		} else {
I 133
			nfsm_build(tl, u_long *, 4 * NFSX_UNSIGNED);
E 133
			*++tl = txdr_unsigned(uiop->uio_offset);
			tl += 2;
		}
		*tl = txdr_unsigned(len);
E 100
E 57
		nfsm_uiotom(uiop, len);
D 26
		nfsm_request(vp);
E 26
I 26
D 39
		nfsm_request(vp, nonidempotent[NFSPROC_WRITE]);
E 39
I 39
D 42
		nfsm_request(vp, NFSPROC_WRITE, procp);
E 42
I 42
D 57
		nfsm_request(vp, NFSPROC_WRITE, procp, 1);
E 57
I 57
D 65
		nfsm_request(vp, NFSPROC_WRITE, uiop->uio_procp, 1);
E 65
I 65
		nfsm_request(vp, NFSPROC_WRITE, uiop->uio_procp, cred);
E 65
E 57
E 42
E 39
E 26
D 133
		nfsm_loadattr(vp, (struct vattr *)0);
I 65
		if (nmp->nm_flag & NFSMNT_MYWRITE)
D 92
			VTONFS(vp)->n_mtime = VTONFS(vp)->n_vattr.va_mtime.tv_sec;
E 92
I 92
			VTONFS(vp)->n_mtime = VTONFS(vp)->n_vattr.va_mtime.ts_sec;
E 92
		else if ((nmp->nm_flag & NFSMNT_NQNFS) &&
			 NQNFS_CKCACHABLE(vp, NQL_WRITE)) {
			nfsm_dissect(tl, u_long *, 2*NFSX_UNSIGNED);
			fxdr_hyper(tl, &frev);
D 93
			if (QUADGT(frev, np->n_brev))
E 93
I 93
			if (frev > np->n_brev)
E 93
				np->n_brev = frev;
		}
E 133
I 133
		if (v3) {
			wccflag = NFSV3_WCCCHK;
			nfsm_wcc_data(vp, wccflag);
			if (!error) {
				nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED +
					NFSX_V3WRITEVERF);
				rlen = fxdr_unsigned(int, *tl++);
				if (rlen == 0) {
					error = NFSERR_IO;
					break;
				} else if (rlen < len) {
					backup = len - rlen;
					uiop->uio_iov->iov_base -= backup;
					uiop->uio_iov->iov_len += backup;
					uiop->uio_offset -= backup;
					uiop->uio_resid += backup;
					len = rlen;
				}
				commit = fxdr_unsigned(int, *tl++);

				/*
				 * Return the lowest committment level
				 * obtained by any of the RPCs.
				 */
				if (committed == NFSV3WRITE_FILESYNC)
					committed = commit;
				else if (committed == NFSV3WRITE_DATASYNC &&
					commit == NFSV3WRITE_UNSTABLE)
					committed = commit;
				if ((nmp->nm_flag & NFSMNT_HASWRITEVERF) == 0) {
				    bcopy((caddr_t)tl, (caddr_t)nmp->nm_verf,
					NFSX_V3WRITEVERF);
				    nmp->nm_flag |= NFSMNT_HASWRITEVERF;
				} else if (bcmp((caddr_t)tl,
				    (caddr_t)nmp->nm_verf, NFSX_V3WRITEVERF)) {
				    *must_commit = 1;
				    bcopy((caddr_t)tl, (caddr_t)nmp->nm_verf,
					NFSX_V3WRITEVERF);
				}
			}
		} else
		    nfsm_loadattr(vp, (struct vattr *)0);
		if (wccflag)
		    VTONFS(vp)->n_mtime = VTONFS(vp)->n_vattr.va_mtime.ts_sec;
E 133
E 65
		m_freem(mrep);
		tsiz -= len;
D 15
		*offp += len;
E 15
	}
nfsmout:
I 133
	*iomode = committed;
E 133
I 65
	if (error)
		uiop->uio_resid = tsiz;
E 65
D 5
	if (error && (ioflag & IO_UNIT)) {
		vattr_null(&va);
		va.va_size = osize;
		nfs_setattr(vp, &va, cred);
		*offp = ooff;
	}
	if (!(ioflag & IO_NODELOCKED))
		nfs_unlock(vp);
E 5
	return (error);
I 11
}

/*
D 133
 * nfs mknod call
D 40
 * This call is currently not supported.
E 40
I 40
 * This is a kludge. Use a create rpc but with the IFMT bits of the mode
 * set to specify the file type and the size field for rdev.
E 133
I 133
 * nfs mknod rpc
 * For NFS v2 this is a kludge. Use a create rpc but with the IFMT bits of the
 * mode set to specify the file type and the size field for rdev.
E 133
E 40
 */
D 133
/* ARGSUSED */
E 133
D 57
nfs_mknod(ndp, vap, cred)
E 57
I 57
D 65
nfs_mknod(ndp, vap, cred, p)
E 65
I 65
D 66
nfs_mknod(ndp, vap, cred, procp)
E 65
E 57
	struct nameidata *ndp;
	struct ucred *cred;
D 40
	struct vattr *vap;
E 40
I 40
	register struct vattr *vap;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 66
I 66
int
D 67
nfs_mknod(dvp, vpp, cnp, vap)   /* converted to CN.   */
/* old: nfs_mknod(ndp, vap, cred, procp) */
E 67
I 67
D 82
nfs_mknod(dvp, vpp, cnp, vap)
E 67
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
	struct vattr *vap;
E 82
I 82
D 89
nfs_mknod (ap)
E 89
I 89
D 133
nfs_mknod(ap)
E 89
D 94
	struct vop_mknod_args *ap;
E 94
I 94
	struct vop_mknod_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
	} */ *ap;
E 133
I 133
nfs_mknodrpc(dvp, vpp, cnp, vap)
	register struct vnode *dvp;
	register struct vnode **vpp;
	register struct componentname *cnp;
	register struct vattr *vap;
E 133
E 94
D 84
#define dvp (ap->a_dvp)
#define vpp (ap->a_vpp)
#define cnp (ap->a_cnp)
#define vap (ap->a_vap)
E 84
E 82
E 66
E 65
E 57
E 40
{
I 82
D 94
	USES_VOP_ABORTOP;
E 94
I 89
D 133
	register struct vnode *dvp = ap->a_dvp;
	register struct vattr *vap = ap->a_vap;
	register struct componentname *cnp = ap->a_cnp;
E 133
E 89
E 82
I 40
	register struct nfsv2_sattr *sp;
I 133
	register struct nfsv3_sattr *sp3;
E 133
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
D 65
	register long t1, t2;
E 65
I 65
D 100
	register long t2;
E 100
I 100
	register long t1, t2;
D 133
	struct vnode *newvp;
E 133
I 133
	struct vnode *newvp = (struct vnode *)0;
	struct nfsnode *np;
E 133
I 114
	struct vattr vattr;
E 114
	char *cp2;
E 100
E 65
	caddr_t bpos, dpos;
D 65
	u_long xid;
E 65
D 100
	int error = 0;
E 100
I 100
D 133
	int error = 0, isnq;
E 133
I 133
	int error = 0, wccflag = NFSV3_WCCRATTR, gotvp = 0;
E 133
E 100
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
	u_long rdev;
I 133
	int v3 = NFS_ISV3(dvp);
E 133
E 40

I 100
D 133
	isnq = (VFSTONFS(dvp->v_mount)->nm_flag & NFSMNT_NQNFS);
E 133
E 100
D 40
	nfs_abortop(ndp);
	return (EOPNOTSUPP);
E 40
I 40
D 84
	if (vap->va_type == VCHR || vap->va_type == VBLK)
		rdev = txdr_unsigned(vap->va_rdev);
E 84
I 84
D 89
	if (ap->a_vap->va_type == VCHR || ap->a_vap->va_type == VBLK)
		rdev = txdr_unsigned(ap->a_vap->va_rdev);
E 89
I 89
	if (vap->va_type == VCHR || vap->va_type == VBLK)
		rdev = txdr_unsigned(vap->va_rdev);
E 89
E 84
D 133
#ifdef FIFO
D 84
	else if (vap->va_type == VFIFO)
E 84
I 84
D 89
	else if (ap->a_vap->va_type == VFIFO)
E 89
I 89
	else if (vap->va_type == VFIFO)
E 133
I 133
	else if (vap->va_type == VFIFO || vap->va_type == VSOCK)
E 133
E 89
E 84
		rdev = 0xffffffff;
D 133
#endif /* FIFO */
E 133
	else {
D 66
		VOP_ABORTOP(ndp);
I 41
		vput(ndp->ni_dvp);
E 66
I 66
D 84
		VOP_ABORTOP(dvp, cnp);
		vput(dvp);
E 84
I 84
D 89
		VOP_ABORTOP(ap->a_dvp, ap->a_cnp);
		vput(ap->a_dvp);
E 89
I 89
		VOP_ABORTOP(dvp, cnp);
		vput(dvp);
E 89
E 84
E 66
E 41
		return (EOPNOTSUPP);
	}
I 114
	if (error = VOP_GETATTR(dvp, &vattr, cnp->cn_cred, cnp->cn_proc)) {
		VOP_ABORTOP(dvp, cnp);
		vput(dvp);
		return (error);
	}
E 114
D 133
	nfsstats.rpccnt[NFSPROC_CREATE]++;
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_CREATE], ndp->ni_cred,
E 65
I 65
D 66
	nfsm_reqhead(ndp->ni_dvp, NFSPROC_CREATE,
E 65
D 59
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_dent.d_namlen)+NFSX_SATTR);
E 59
I 59
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_namelen)+NFSX_SATTR);
E 59
	nfsm_fhtom(ndp->ni_dvp);
D 59
	nfsm_strtom(ndp->ni_dent.d_name, ndp->ni_dent.d_namlen, NFS_MAXNAMLEN);
E 59
I 59
	nfsm_strtom(ndp->ni_ptr, ndp->ni_namelen, NFS_MAXNAMLEN);
E 66
I 66
D 84
	nfsm_reqhead(dvp, NFSPROC_CREATE,
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen)+NFSX_SATTR);
	nfsm_fhtom(dvp);
	nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
E 84
I 84
D 89
	nfsm_reqhead(ap->a_dvp, NFSPROC_CREATE,
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ap->a_cnp->cn_namelen)+NFSX_SATTR);
	nfsm_fhtom(ap->a_dvp);
	nfsm_strtom(ap->a_cnp->cn_nameptr, ap->a_cnp->cn_namelen, NFS_MAXNAMLEN);
E 89
I 89
	nfsm_reqhead(dvp, NFSPROC_CREATE,
D 100
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen)+NFSX_SATTR);
E 100
I 100
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen)+NFSX_SATTR(isnq));
E 100
	nfsm_fhtom(dvp);
E 133
I 133
	nfsstats.rpccnt[NFSPROC_MKNOD]++;
	nfsm_reqhead(dvp, NFSPROC_MKNOD, NFSX_FH(v3) + 4 * NFSX_UNSIGNED +
		+ nfsm_rndup(cnp->cn_namelen) + NFSX_SATTR(v3));
	nfsm_fhtom(dvp, v3);
E 133
	nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
E 89
E 84
E 66
E 59
D 100
	nfsm_build(sp, struct nfsv2_sattr *, NFSX_SATTR);
E 100
I 100
D 133
	nfsm_build(sp, struct nfsv2_sattr *, NFSX_SATTR(isnq));
E 100
D 84
	sp->sa_mode = vtonfs_mode(vap->va_type, vap->va_mode);
D 66
	sp->sa_uid = txdr_unsigned(ndp->ni_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(ndp->ni_cred->cr_gid);
E 66
I 66
	sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(cnp->cn_cred->cr_gid);
E 84
I 84
D 89
	sp->sa_mode = vtonfs_mode(ap->a_vap->va_type, ap->a_vap->va_mode);
	sp->sa_uid = txdr_unsigned(ap->a_cnp->cn_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(ap->a_cnp->cn_cred->cr_gid);
E 89
I 89
	sp->sa_mode = vtonfs_mode(vap->va_type, vap->va_mode);
	sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
D 114
	sp->sa_gid = txdr_unsigned(cnp->cn_cred->cr_gid);
E 114
I 114
	sp->sa_gid = txdr_unsigned(vattr.va_gid);
E 114
E 89
E 84
E 66
D 100
	sp->sa_size = rdev;
	/* or should these be VNOVAL ?? */
D 84
	txdr_time(&vap->va_atime, &sp->sa_atime);
	txdr_time(&vap->va_mtime, &sp->sa_mtime);
D 42
	nfsm_request(ndp->ni_dvp, NFSPROC_CREATE, u.u_procp);
E 42
I 42
D 56
	nfsm_request(ndp->ni_dvp, NFSPROC_CREATE, u.u_procp, 1);
E 56
I 56
D 57
	nfsm_request(ndp->ni_dvp, NFSPROC_CREATE, curproc, 1);
E 57
I 57
D 65
	nfsm_request(ndp->ni_dvp, NFSPROC_CREATE, p, 1);
E 65
I 65
D 66
	nfsm_request(ndp->ni_dvp, NFSPROC_CREATE, procp, cred);
E 66
I 66
	nfsm_request(dvp, NFSPROC_CREATE, cnp->cn_proc, cnp->cn_cred);
E 84
I 84
D 89
	txdr_time(&ap->a_vap->va_atime, &sp->sa_atime);
	txdr_time(&ap->a_vap->va_mtime, &sp->sa_mtime);
	nfsm_request(ap->a_dvp, NFSPROC_CREATE, ap->a_cnp->cn_proc, ap->a_cnp->cn_cred);
E 89
I 89
	txdr_time(&vap->va_atime, &sp->sa_atime);
	txdr_time(&vap->va_mtime, &sp->sa_mtime);
E 100
I 100
	if (isnq) {
		sp->sa_nqrdev = rdev;
		sp->sa_nqflags = 0;
		txdr_nqtime(&vap->va_atime, &sp->sa_nqatime);
		txdr_nqtime(&vap->va_mtime, &sp->sa_nqmtime);
E 133
I 133
	if (v3) {
		nfsm_build(tl, u_long *, NFSX_UNSIGNED + NFSX_V3SRVSATTR);
		*tl++ = vtonfsv3_type(vap->va_type);
		sp3 = (struct nfsv3_sattr *)tl;
		nfsm_v3sattr(sp3, vap, cnp->cn_cred->cr_uid, vattr.va_gid);
		if (vap->va_type == VCHR || vap->va_type == VBLK) {
			nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
			*tl++ = txdr_unsigned(major(vap->va_rdev));
			*tl = txdr_unsigned(minor(vap->va_rdev));
		}
E 133
	} else {
D 133
		sp->sa_nfssize = rdev;
		txdr_nfstime(&vap->va_atime, &sp->sa_nfsatime);
		txdr_nfstime(&vap->va_mtime, &sp->sa_nfsmtime);
E 133
I 133
		nfsm_build(sp, struct nfsv2_sattr *, NFSX_V2SATTR);
		sp->sa_mode = vtonfsv2_mode(vap->va_type, vap->va_mode);
		sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
		sp->sa_gid = txdr_unsigned(vattr.va_gid);
		sp->sa_size = rdev;
		txdr_nfsv2time(&vap->va_atime, &sp->sa_atime);
		txdr_nfsv2time(&vap->va_mtime, &sp->sa_mtime);
E 133
	}
E 100
D 133
	nfsm_request(dvp, NFSPROC_CREATE, cnp->cn_proc, cnp->cn_cred);
I 100
	nfsm_mtofh(dvp, newvp);
E 133
I 133
	nfsm_request(dvp, NFSPROC_MKNOD, cnp->cn_proc, cnp->cn_cred);
	if (!error) {
		nfsm_mtofh(dvp, newvp, v3, gotvp);
		if (!gotvp) {
			if (newvp) {
				vrele(newvp);
				newvp = (struct vnode *)0;
			}
			error = nfs_lookitup(dvp, cnp->cn_nameptr,
			    cnp->cn_namelen, cnp->cn_cred, cnp->cn_proc, &np);
			if (!error)
				newvp = NFSTOV(np);
		}
	}
	if (v3)
		nfsm_wcc_data(dvp, wccflag);
E 133
E 100
E 89
E 84
E 66
E 65
E 57
E 56
E 42
	nfsm_reqdone;
I 100
D 110
	if (!error)
E 110
I 110
D 133
	if (!error && (cnp->cn_flags & MAKEENTRY))
E 110
		cache_enter(dvp, newvp, cnp);
E 133
I 133
	if (error) {
		if (newvp)
			vrele(newvp);
	} else {
		if (cnp->cn_flags & MAKEENTRY)
			cache_enter(dvp, newvp, cnp);
		*vpp = newvp;
	}
E 133
E 100
I 59
D 66
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 59
	VTONFS(ndp->ni_dvp)->n_flag |= NMODIFIED;
D 65
	nfs_nput(ndp->ni_dvp);
E 65
I 65
	vrele(ndp->ni_dvp);
E 66
I 66
D 84
	FREE(cnp->cn_pnbuf, M_NAMEI);
	VTONFS(dvp)->n_flag |= NMODIFIED;
	vrele(dvp);
E 84
I 84
D 89
	FREE(ap->a_cnp->cn_pnbuf, M_NAMEI);
	VTONFS(ap->a_dvp)->n_flag |= NMODIFIED;
	vrele(ap->a_dvp);
E 89
I 89
	FREE(cnp->cn_pnbuf, M_NAMEI);
	VTONFS(dvp)->n_flag |= NMODIFIED;
I 121
D 133
	VTONFS(dvp)->n_attrstamp = 0;
E 133
I 133
	if (!wccflag)
		VTONFS(dvp)->n_attrstamp = 0;
E 133
E 121
	vrele(dvp);
E 89
E 84
E 66
E 65
	return (error);
E 40
E 11
}
I 82
D 84
#undef dvp
#undef vpp
#undef cnp
#undef vap
E 84
E 82

/*
I 133
 * nfs mknod vop
 * just call nfs_mknodrpc() to do the work.
 */
/* ARGSUSED */
int
nfs_mknod(ap)
	struct vop_mknod_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
	} */ *ap;
{
	struct vnode *newvp;
	int error;

	error = nfs_mknodrpc(ap->a_dvp, &newvp, ap->a_cnp, ap->a_vap);
	if (!error)
		vrele(newvp);
	return (error);
}

static u_long create_verf;
/*
E 133
 * nfs file create call
 */
D 57
nfs_create(ndp, vap)
E 57
I 57
D 65
nfs_create(ndp, vap, p)
E 65
I 65
D 66
nfs_create(ndp, vap, procp)
E 65
E 57
	register struct nameidata *ndp;
	register struct vattr *vap;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 66
I 66
int
D 67
nfs_create(dvp, vpp, cnp, vap)   /* converted to CN.   */
/* old: nfs_create(ndp, vap, procp) */
E 67
I 67
D 82
nfs_create(dvp, vpp, cnp, vap)
E 67
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
	struct vattr *vap;
E 82
I 82
D 89
nfs_create (ap)
E 89
I 89
nfs_create(ap)
E 89
D 94
	struct vop_create_args *ap;
E 94
I 94
	struct vop_create_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
	} */ *ap;
E 94
D 84
#define dvp (ap->a_dvp)
#define vpp (ap->a_vpp)
#define cnp (ap->a_cnp)
#define vap (ap->a_vap)
E 84
E 82
E 66
E 65
E 57
{
I 89
	register struct vnode *dvp = ap->a_dvp;
	register struct vattr *vap = ap->a_vap;
	register struct componentname *cnp = ap->a_cnp;
E 89
I 5
	register struct nfsv2_sattr *sp;
I 133
	register struct nfsv3_sattr *sp3;
E 133
E 5
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
	register long t1, t2;
I 133
	struct nfsnode *np = (struct nfsnode *)0;
	struct vnode *newvp = (struct vnode *)0;
E 133
	caddr_t bpos, dpos, cp2;
D 65
	u_long xid;
E 65
D 100
	int error = 0;
E 100
I 100
D 133
	int error = 0, isnq;
E 133
I 133
	int error = 0, wccflag = NFSV3_WCCRATTR, gotvp = 0, fmode = 0;
E 133
E 100
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
I 114
	struct vattr vattr;
I 133
	int v3 = NFS_ISV3(dvp);
E 133
E 114
E 13

I 133
	/*
	 * Oops, not for me..
	 */
	if (vap->va_type == VSOCK)
		return (nfs_mknodrpc(dvp, ap->a_vpp, cnp, vap));

E 133
I 114
	if (error = VOP_GETATTR(dvp, &vattr, cnp->cn_cred, cnp->cn_proc)) {
		VOP_ABORTOP(dvp, cnp);
		vput(dvp);
		return (error);
	}
I 133
	if (vap->va_vaflags & VA_EXCLUSIVE)
		fmode |= O_EXCL;
again:
E 133
E 114
	nfsstats.rpccnt[NFSPROC_CREATE]++;
I 100
D 133
	isnq = (VFSTONFS(dvp->v_mount)->nm_flag & NFSMNT_NQNFS);
E 100
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_CREATE], ndp->ni_cred,
E 65
I 65
D 66
	nfsm_reqhead(ndp->ni_dvp, NFSPROC_CREATE,
E 65
D 59
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_dent.d_namlen)+NFSX_SATTR);
E 59
I 59
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_namelen)+NFSX_SATTR);
E 59
	nfsm_fhtom(ndp->ni_dvp);
D 59
	nfsm_strtom(ndp->ni_dent.d_name, ndp->ni_dent.d_namlen, NFS_MAXNAMLEN);
E 59
I 59
	nfsm_strtom(ndp->ni_ptr, ndp->ni_namelen, NFS_MAXNAMLEN);
E 66
I 66
D 84
	nfsm_reqhead(dvp, NFSPROC_CREATE,
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen)+NFSX_SATTR);
	nfsm_fhtom(dvp);
	nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
E 84
I 84
D 89
	nfsm_reqhead(ap->a_dvp, NFSPROC_CREATE,
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ap->a_cnp->cn_namelen)+NFSX_SATTR);
	nfsm_fhtom(ap->a_dvp);
	nfsm_strtom(ap->a_cnp->cn_nameptr, ap->a_cnp->cn_namelen, NFS_MAXNAMLEN);
E 89
I 89
	nfsm_reqhead(dvp, NFSPROC_CREATE,
D 100
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen)+NFSX_SATTR);
E 100
I 100
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen)+NFSX_SATTR(isnq));
E 100
	nfsm_fhtom(dvp);
E 133
I 133
	nfsm_reqhead(dvp, NFSPROC_CREATE, NFSX_FH(v3) + 2 * NFSX_UNSIGNED +
		nfsm_rndup(cnp->cn_namelen) + NFSX_SATTR(v3));
	nfsm_fhtom(dvp, v3);
E 133
	nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
E 89
E 84
E 66
E 59
D 5
	nfsm_build(p, u_long *, NFSX_UNSIGNED*8);
	*p++ = vtonfs_mode(VREG, vap->va_mode);
	*p++ = txdr_unsigned(ndp->ni_cred->cr_uid);
	*p++ = txdr_unsigned(ndp->ni_cred->cr_gid);
	*p++ = txdr_unsigned(0);
E 5
I 5
D 100
	nfsm_build(sp, struct nfsv2_sattr *, NFSX_SATTR);
E 100
I 100
D 133
	nfsm_build(sp, struct nfsv2_sattr *, NFSX_SATTR(isnq));
E 100
D 54
	sp->sa_mode = vtonfs_mode(VREG, vap->va_mode);
E 54
I 54
D 84
	sp->sa_mode = vtonfs_mode(vap->va_type, vap->va_mode);
E 54
D 66
	sp->sa_uid = txdr_unsigned(ndp->ni_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(ndp->ni_cred->cr_gid);
E 66
I 66
	sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(cnp->cn_cred->cr_gid);
E 84
I 84
D 89
	sp->sa_mode = vtonfs_mode(ap->a_vap->va_type, ap->a_vap->va_mode);
	sp->sa_uid = txdr_unsigned(ap->a_cnp->cn_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(ap->a_cnp->cn_cred->cr_gid);
E 89
I 89
	sp->sa_mode = vtonfs_mode(vap->va_type, vap->va_mode);
	sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
D 114
	sp->sa_gid = txdr_unsigned(cnp->cn_cred->cr_gid);
E 114
I 114
	sp->sa_gid = txdr_unsigned(vattr.va_gid);
E 114
E 89
E 84
E 66
D 100
	sp->sa_size = txdr_unsigned(0);
E 5
	/* or should these be VNOVAL ?? */
D 5
	txdr_time(&(vap->va_atime), p);
	txdr_time(&(vap->va_mtime), p+2);
E 5
I 5
D 84
	txdr_time(&vap->va_atime, &sp->sa_atime);
	txdr_time(&vap->va_mtime, &sp->sa_mtime);
E 5
D 26
	nfsm_request(ndp->ni_dvp);
E 26
I 26
D 39
	nfsm_request(ndp->ni_dvp, nonidempotent[NFSPROC_CREATE]);
E 39
I 39
D 42
	nfsm_request(ndp->ni_dvp, NFSPROC_CREATE, u.u_procp);
E 42
I 42
D 56
	nfsm_request(ndp->ni_dvp, NFSPROC_CREATE, u.u_procp, 1);
E 56
I 56
D 57
	nfsm_request(ndp->ni_dvp, NFSPROC_CREATE, curproc, 1);
E 57
I 57
D 65
	nfsm_request(ndp->ni_dvp, NFSPROC_CREATE, p, 1);
E 65
I 65
D 66
	nfsm_request(ndp->ni_dvp, NFSPROC_CREATE, procp, ndp->ni_cred);
E 65
E 57
E 56
E 42
E 39
E 26
	nfsm_mtofh(ndp->ni_dvp, ndp->ni_vp);
E 66
I 66
	nfsm_request(dvp, NFSPROC_CREATE, cnp->cn_proc, cnp->cn_cred);
	nfsm_mtofh(dvp, *vpp);
E 84
I 84
D 89
	txdr_time(&ap->a_vap->va_atime, &sp->sa_atime);
	txdr_time(&ap->a_vap->va_mtime, &sp->sa_mtime);
	nfsm_request(ap->a_dvp, NFSPROC_CREATE, ap->a_cnp->cn_proc, ap->a_cnp->cn_cred);
	nfsm_mtofh(ap->a_dvp, *ap->a_vpp);
E 89
I 89
	txdr_time(&vap->va_atime, &sp->sa_atime);
	txdr_time(&vap->va_mtime, &sp->sa_mtime);
E 100
I 100
	if (isnq) {
		u_quad_t qval = 0;

		txdr_hyper(&qval, &sp->sa_nqsize);
		sp->sa_nqflags = 0;
		sp->sa_nqrdev = -1;
		txdr_nqtime(&vap->va_atime, &sp->sa_nqatime);
		txdr_nqtime(&vap->va_mtime, &sp->sa_nqmtime);
E 133
I 133
	if (v3) {
		nfsm_build(tl, u_long *, NFSX_UNSIGNED);
		if (fmode & O_EXCL) {
		    *tl = txdr_unsigned(NFSV3CREATE_EXCLUSIVE);
		    nfsm_build(tl, u_long *, NFSX_V3CREATEVERF);
		    if (in_ifaddr)
			*tl++ = IA_SIN(in_ifaddr)->sin_addr.s_addr;
		    else
			*tl++ = create_verf;
		    *tl = ++create_verf;
		} else {
		    *tl = txdr_unsigned(NFSV3CREATE_UNCHECKED);
		    nfsm_build(tl, u_long *, NFSX_V3SRVSATTR);
		    sp3 = (struct nfsv3_sattr *)tl;
		    nfsm_v3sattr(sp3, vap, cnp->cn_cred->cr_uid, vattr.va_gid);
		}
E 133
	} else {
D 133
		sp->sa_nfssize = 0;
		txdr_nfstime(&vap->va_atime, &sp->sa_nfsatime);
		txdr_nfstime(&vap->va_mtime, &sp->sa_nfsmtime);
E 133
I 133
		nfsm_build(sp, struct nfsv2_sattr *, NFSX_V2SATTR);
		sp->sa_mode = vtonfsv2_mode(vap->va_type, vap->va_mode);
		sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
		sp->sa_gid = txdr_unsigned(vattr.va_gid);
		sp->sa_size = 0;
		txdr_nfsv2time(&vap->va_atime, &sp->sa_atime);
		txdr_nfsv2time(&vap->va_mtime, &sp->sa_mtime);
E 133
	}
E 100
	nfsm_request(dvp, NFSPROC_CREATE, cnp->cn_proc, cnp->cn_cred);
D 133
	nfsm_mtofh(dvp, *ap->a_vpp);
E 133
I 133
	if (!error) {
		nfsm_mtofh(dvp, newvp, v3, gotvp);
		if (!gotvp) {
			if (newvp) {
				vrele(newvp);
				newvp = (struct vnode *)0;
			}
			error = nfs_lookitup(dvp, cnp->cn_nameptr,
			    cnp->cn_namelen, cnp->cn_cred, cnp->cn_proc, &np);
			if (!error)
				newvp = NFSTOV(np);
		}
	}
	if (v3)
		nfsm_wcc_data(dvp, wccflag);
E 133
E 89
E 84
E 66
	nfsm_reqdone;
I 100
D 110
	if (!error)
E 110
I 110
D 133
	if (!error && (cnp->cn_flags & MAKEENTRY))
E 110
		cache_enter(dvp, *ap->a_vpp, cnp);
E 133
I 133
	if (error) {
		if (v3 && (fmode & O_EXCL) && error == NFSERR_NOTSUPP) {
			fmode &= ~O_EXCL;
			goto again;
		}
		if (newvp)
			vrele(newvp);
	} else if (v3 && (fmode & O_EXCL))
		error = nfs_setattrrpc(newvp, vap, cnp->cn_cred, cnp->cn_proc);
	if (!error) {
		if (cnp->cn_flags & MAKEENTRY)
			cache_enter(dvp, newvp, cnp);
		*ap->a_vpp = newvp;
	}
E 133
E 100
I 59
D 66
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 59
I 32
D 39
	VTONFS(ndp->ni_dvp)->n_direofstamp = 0;
E 39
I 39
	VTONFS(ndp->ni_dvp)->n_flag |= NMODIFIED;
E 39
E 32
D 65
	nfs_nput(ndp->ni_dvp);
E 65
I 65
	vrele(ndp->ni_dvp);
E 66
I 66
D 84
	FREE(cnp->cn_pnbuf, M_NAMEI);
	VTONFS(dvp)->n_flag |= NMODIFIED;
	vrele(dvp);
E 84
I 84
D 89
	FREE(ap->a_cnp->cn_pnbuf, M_NAMEI);
	VTONFS(ap->a_dvp)->n_flag |= NMODIFIED;
	vrele(ap->a_dvp);
E 89
I 89
	FREE(cnp->cn_pnbuf, M_NAMEI);
	VTONFS(dvp)->n_flag |= NMODIFIED;
I 121
D 133
	VTONFS(dvp)->n_attrstamp = 0;
E 133
I 133
	if (!wccflag)
		VTONFS(dvp)->n_attrstamp = 0;
E 133
E 121
	vrele(dvp);
E 89
E 84
E 66
E 65
	return (error);
}
I 82
D 84
#undef dvp
#undef vpp
#undef cnp
#undef vap
E 84
E 82

/*
 * nfs file remove call
I 6
D 39
 * To try and make nfs semantics closer to vfs semantics, a file that has
 * other references to the vnode is renamed instead of removed and then
E 39
I 39
 * To try and make nfs semantics closer to ufs semantics, a file that has
 * other processes using the vnode is renamed instead of removed and then
E 39
 * removed later on the last close.
D 39
 * Unfortunately you must flush the buffer cache and cmap to get rid of
 * all extraneous vnode references before you check the reference cnt.
 * 1 - If the file could have blocks in the buffer cache
 *	  flush them out and invalidate them
 *	  mpurge the vnode to flush out cmap references
 *	  (This is necessary to update the vnode ref cnt as well as sensible
 *	   for actual removes, to free up the buffers)
D 20
 * 2 - If v_count > 1
E 20
I 20
 * 2 - If v_usecount > 1
E 39
I 39
 * - If v_usecount > 1
E 39
E 20
 *	  If a rename is not already in the works
 *	     call nfs_sillyrename() to set it up
 *     else
 *	  do the remove rpc
E 6
 */
D 57
nfs_remove(ndp)
E 57
I 57
D 65
nfs_remove(ndp, p)
E 65
I 65
D 66
nfs_remove(ndp, procp)
E 65
E 57
	register struct nameidata *ndp;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 66
I 66
int
D 67
nfs_remove(dvp, vp, cnp)   /* converted to CN.   */
/* old: ufs_remove(ndp, p) */
E 67
I 67
D 82
nfs_remove(dvp, vp, cnp)
E 67
	struct vnode *dvp, *vp;
	struct componentname *cnp;
E 82
I 82
D 89
nfs_remove (ap)
E 89
I 89
nfs_remove(ap)
E 89
D 93
	struct vop_remove_args *ap;
E 93
I 93
	struct vop_remove_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode * a_dvp;
		struct vnode * a_vp;
		struct componentname * a_cnp;
	} */ *ap;
E 93
D 84
#define dvp (ap->a_dvp)
#define vp (ap->a_vp)
#define cnp (ap->a_cnp)
E 84
E 82
E 66
E 65
E 57
{
I 6
D 66
	register struct vnode *vp = ndp->ni_vp;
	register struct nfsnode *np = VTONFS(ndp->ni_vp);
E 66
I 66
D 84
	register struct nfsnode *np = VTONFS(vp);
E 84
I 84
D 89
	register struct nfsnode *np = VTONFS(ap->a_vp);
E 89
I 89
	register struct vnode *vp = ap->a_vp;
	register struct vnode *dvp = ap->a_dvp;
	register struct componentname *cnp = ap->a_cnp;
	register struct nfsnode *np = VTONFS(vp);
E 89
E 84
E 66
E 6
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
D 65
	register long t1, t2;
E 65
I 65
	register long t2;
E 65
	caddr_t bpos, dpos;
D 65
	u_long xid;
E 65
	int error = 0;
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
I 133
	struct vattr vattr;
	int v3 = NFS_ISV3(dvp);
E 133
E 13

D 6
	if (ndp->ni_vp->v_count > 1)
		error = nfs_sillyrename(ndp, REMOVE);
	else {
E 6
I 6
D 39
	if (vp->v_type == VREG) {
		if (np->n_flag & (NMODIFIED|NBUFFERED)) {
			np->n_flag &= ~(NMODIFIED|NBUFFERED);
D 19
			nfs_blkflush(vp, (daddr_t)0, np->n_size, TRUE);
E 19
I 19
D 22
			if (vp->v_blockh)
				vinvalbuf(vp, TRUE);
E 22
I 22
			vinvalbuf(vp, TRUE);
E 22
E 19
		}
D 19
		if (np->n_flag & NPAGEDON)
E 19
I 19
		if (np->n_flag & NPAGEDON) {
			np->n_flag &= ~NPAGEDON;
E 19
			mpurge(vp);	/* In case cmap entries still ref it */
I 19
		}
E 19
	}
E 39
D 20
	if (vp->v_count > 1) {
E 20
I 20
D 84
	if (vp->v_usecount > 1) {
E 84
I 84
D 89
	if (ap->a_vp->v_usecount > 1) {
E 89
I 89
D 133
	if (vp->v_usecount > 1) {
E 89
E 84
E 20
		if (!np->n_sillyrename)
D 57
			error = nfs_sillyrename(ndp, REMOVE);
E 57
I 57
D 58
			error = nfs_sillyrename(ndp, REMOVE, p);
E 58
I 58
D 65
			error = nfs_sillyrename(ndp, p);
E 65
I 65
D 66
			error = nfs_sillyrename(ndp, procp);
E 66
I 66
D 67
			error = nfs_sillyrename(dvp, vp, cnp);   /* NEEDSWORK */
E 67
I 67
D 84
			error = nfs_sillyrename(dvp, vp, cnp);
E 84
I 84
D 89
			error = nfs_sillyrename(ap->a_dvp, ap->a_vp, ap->a_cnp);
E 89
I 89
			error = nfs_sillyrename(dvp, vp, cnp);
E 89
E 84
E 67
E 66
E 65
E 58
E 57
	} else {
E 133
I 133
#ifndef DIAGNOSTIC
	if ((cnp->cn_flags & HASBUF) == 0)
		panic("nfs_remove: no name");
	if (vp->v_usecount < 1)
		panic("nfs_remove: bad v_usecount");
#endif
	if (vp->v_usecount == 1 || (np->n_sillyrename &&
	    VOP_GETATTR(vp, &vattr, cnp->cn_cred, cnp->cn_proc) == 0 &&
	    vattr.va_nlink > 1)) {
E 133
I 65
		/*
		 * Purge the name cache so that the chance of a lookup for
		 * the name succeeding while the remove is in progress is
		 * minimized. Without node locking it can still happen, such
		 * that an I/O op returns ESTALE, but since you get this if
		 * another host removes the file..
		 */
D 84
		cache_purge(vp);
E 84
I 84
D 89
		cache_purge(ap->a_vp);
E 89
I 89
		cache_purge(vp);
E 89
E 84
		/*
D 133
		 * Throw away biocache buffers. Mainly to avoid
		 * unnecessary delayed writes.
E 133
I 133
		 * throw away biocache buffers, mainly to avoid
		 * unnecessary delayed writes later.
E 133
		 */
D 84
		vinvalbuf(vp, FALSE);
E 84
I 84
D 89
		vinvalbuf(ap->a_vp, FALSE);
E 89
I 89
D 93
		vinvalbuf(vp, FALSE);
E 93
I 93
D 108
		error = vinvalbuf(vp, FALSE, cnp->cn_cred, cnp->cn_proc);
E 108
I 108
D 111
		NFS_VINVBUFE(np, vp, FALSE, cnp->cn_cred, cnp->cn_proc, error);
E 111
I 111
		error = nfs_vinvalbuf(vp, 0, cnp->cn_cred, cnp->cn_proc, 1);
D 133
		if (error == EINTR)
			return (error);
E 133
E 111
E 108
E 93
E 89
E 84
		/* Do the rpc */
E 65
E 6
D 133
		nfsstats.rpccnt[NFSPROC_REMOVE]++;
D 65
		nfsm_reqhead(nfs_procids[NFSPROC_REMOVE], ndp->ni_cred,
E 65
I 65
D 66
		nfsm_reqhead(ndp->ni_dvp, NFSPROC_REMOVE,
E 65
D 59
			NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_dent.d_namlen));
E 59
I 59
			NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_namelen));
E 59
		nfsm_fhtom(ndp->ni_dvp);
D 59
		nfsm_strtom(ndp->ni_dent.d_name, ndp->ni_dent.d_namlen, NFS_MAXNAMLEN);
E 59
I 59
		nfsm_strtom(ndp->ni_ptr, ndp->ni_namelen, NFS_MAXNAMLEN);
E 59
D 26
		nfsm_request(ndp->ni_dvp);
E 26
I 26
D 39
		nfsm_request(ndp->ni_dvp, nonidempotent[NFSPROC_REMOVE]);
E 39
I 39
D 42
		nfsm_request(ndp->ni_dvp, NFSPROC_REMOVE, u.u_procp);
E 42
I 42
D 56
		nfsm_request(ndp->ni_dvp, NFSPROC_REMOVE, u.u_procp, 1);
E 56
I 56
D 57
		nfsm_request(ndp->ni_dvp, NFSPROC_REMOVE, curproc, 1);
E 57
I 57
D 65
		nfsm_request(ndp->ni_dvp, NFSPROC_REMOVE, p, 1);
E 65
I 65
		nfsm_request(ndp->ni_dvp, NFSPROC_REMOVE, procp, ndp->ni_cred);
E 66
I 66
D 84
		nfsm_reqhead(dvp, NFSPROC_REMOVE,
			NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen));
		nfsm_fhtom(dvp);
		nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
		nfsm_request(dvp, NFSPROC_REMOVE, cnp->cn_proc, cnp->cn_cred);
E 84
I 84
D 89
		nfsm_reqhead(ap->a_dvp, NFSPROC_REMOVE,
			NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ap->a_cnp->cn_namelen));
		nfsm_fhtom(ap->a_dvp);
		nfsm_strtom(ap->a_cnp->cn_nameptr, ap->a_cnp->cn_namelen, NFS_MAXNAMLEN);
		nfsm_request(ap->a_dvp, NFSPROC_REMOVE, ap->a_cnp->cn_proc, ap->a_cnp->cn_cred);
E 89
I 89
		nfsm_reqhead(dvp, NFSPROC_REMOVE,
			NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen));
		nfsm_fhtom(dvp);
		nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
		nfsm_request(dvp, NFSPROC_REMOVE, cnp->cn_proc, cnp->cn_cred);
E 89
E 84
E 66
E 65
E 57
E 56
E 42
E 39
E 26
		nfsm_reqdone;
I 59
D 66
		FREE(ndp->ni_pnbuf, M_NAMEI);
E 59
I 32
D 39
		VTONFS(ndp->ni_dvp)->n_direofstamp = 0;
E 39
I 39
		VTONFS(ndp->ni_dvp)->n_flag |= NMODIFIED;
E 66
I 66
D 84
		FREE(cnp->cn_pnbuf, M_NAMEI);
		VTONFS(dvp)->n_flag |= NMODIFIED;
E 84
I 84
D 89
		FREE(ap->a_cnp->cn_pnbuf, M_NAMEI);
		VTONFS(ap->a_dvp)->n_flag |= NMODIFIED;
E 89
I 89
		FREE(cnp->cn_pnbuf, M_NAMEI);
		VTONFS(dvp)->n_flag |= NMODIFIED;
I 121
		VTONFS(dvp)->n_attrstamp = 0;
E 133
I 133
		if (error != EINTR)
			error = nfs_removerpc(dvp, cnp->cn_nameptr,
				cnp->cn_namelen, cnp->cn_cred, cnp->cn_proc);
E 133
E 121
E 89
E 84
E 66
E 39
E 32
I 19
		/*
		 * Kludge City: If the first reply to the remove rpc is lost..
		 *   the reply to the retransmitted request will be ENOENT
		 *   since the file was in fact removed
		 *   Therefore, we cheat and return success.
		 */
		if (error == ENOENT)
			error = 0;
E 19
D 133
	}
E 133
I 133
	} else if (!np->n_sillyrename)
		error = nfs_sillyrename(dvp, vp, cnp);
	FREE(cnp->cn_pnbuf, M_NAMEI);
E 133
I 25
	np->n_attrstamp = 0;
E 25
D 26
	if (ndp->ni_dvp == ndp->ni_vp)
D 2
		vrele(ndp->ni_dvp);
E 2
I 2
		vrele(ndp->ni_vp);
E 26
I 26
D 65
	if (ndp->ni_dvp == vp)
		vrele(vp);
E 26
E 2
	else
D 2
		nfs_nput(ndp->ni_dvp);
	nfs_nput(ndp->ni_vp);
E 2
I 2
D 26
		nfs_nput(ndp->ni_vp);
	nfs_nput(ndp->ni_dvp);
E 26
I 26
		nfs_nput(ndp->ni_dvp);
	nfs_nput(vp);
E 65
I 65
D 66
	vrele(ndp->ni_dvp);
E 66
I 66
D 84
	vrele(dvp);
E 66
	vrele(vp);
E 84
I 84
D 89
	vrele(ap->a_dvp);
	vrele(ap->a_vp);
E 89
I 89
	vrele(dvp);
	vrele(vp);
E 89
E 84
E 65
E 26
E 2
	return (error);
}
I 82
D 84
#undef dvp
#undef vp
#undef cnp
E 84
E 82

/*
 * nfs file remove rpc called from nfs_inactive
 */
I 66
int
E 66
D 57
nfs_removeit(ndp)
E 57
I 57
D 58
nfs_removeit(ndp, p)
E 57
	register struct nameidata *ndp;
E 58
I 58
D 65
nfs_removeit(sp, p)
E 65
I 65
D 93
nfs_removeit(sp, procp)
E 93
I 93
nfs_removeit(sp)
E 93
E 65
	register struct sillyrename *sp;
E 58
I 57
D 65
	struct proc *p;
E 65
I 65
D 93
	struct proc *procp;
E 93
E 65
E 57
{
I 133

	return (nfs_removerpc(sp->s_dvp, sp->s_name, sp->s_namlen, sp->s_cred,
		(struct proc *)0));
}

/*
 * Nfs remove rpc, called from nfs_remove() and nfs_removeit().
 */
int
nfs_removerpc(dvp, name, namelen, cred, proc)
	register struct vnode *dvp;
	char *name;
	int namelen;
	struct ucred *cred;
	struct proc *proc;
{
E 133
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
D 65
	register long t1, t2;
E 65
I 65
D 133
	register long t2;
E 65
	caddr_t bpos, dpos;
D 65
	u_long xid;
E 65
	int error = 0;
E 133
I 133
	register long t1, t2;
	caddr_t bpos, dpos, cp2;
	int error = 0, wccflag = NFSV3_WCCRATTR;
E 133
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
I 133
	int v3 = NFS_ISV3(dvp);
E 133
E 13

I 5
D 6
printf("in removeit\n");
E 6
E 5
	nfsstats.rpccnt[NFSPROC_REMOVE]++;
D 58
	nfsm_reqhead(nfs_procids[NFSPROC_REMOVE], ndp->ni_cred,
		NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_dent.d_namlen));
	nfsm_fhtom(ndp->ni_dvp);
	nfsm_strtom(ndp->ni_dent.d_name, ndp->ni_dent.d_namlen, NFS_MAXNAMLEN);
D 26
	nfsm_request(ndp->ni_dvp);
E 26
I 26
D 39
	nfsm_request(ndp->ni_dvp, nonidempotent[NFSPROC_REMOVE]);
E 39
I 39
D 42
	nfsm_request(ndp->ni_dvp, NFSPROC_REMOVE, u.u_procp);
E 42
I 42
D 56
	nfsm_request(ndp->ni_dvp, NFSPROC_REMOVE, u.u_procp, 1);
E 56
I 56
D 57
	nfsm_request(ndp->ni_dvp, NFSPROC_REMOVE, curproc, 1);
E 57
I 57
	nfsm_request(ndp->ni_dvp, NFSPROC_REMOVE, p, 1);
E 58
I 58
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_REMOVE], sp->s_cred,
E 65
I 65
D 133
	nfsm_reqhead(sp->s_dvp, NFSPROC_REMOVE,
E 65
		NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(sp->s_namlen));
	nfsm_fhtom(sp->s_dvp);
	nfsm_strtom(sp->s_name, sp->s_namlen, NFS_MAXNAMLEN);
D 65
	nfsm_request(sp->s_dvp, NFSPROC_REMOVE, p, 1);
E 65
I 65
D 93
	nfsm_request(sp->s_dvp, NFSPROC_REMOVE, procp, sp->s_cred);
E 93
I 93
	nfsm_request(sp->s_dvp, NFSPROC_REMOVE, NULL, sp->s_cred);
E 133
I 133
	nfsm_reqhead(dvp, NFSPROC_REMOVE,
		NFSX_FH(v3) + NFSX_UNSIGNED + nfsm_rndup(namelen));
	nfsm_fhtom(dvp, v3);
	nfsm_strtom(name, namelen, NFS_MAXNAMLEN);
	nfsm_request(dvp, NFSPROC_REMOVE, proc, cred);
	if (v3)
		nfsm_wcc_data(dvp, wccflag);
E 133
E 93
E 65
E 58
E 57
E 56
E 42
E 39
E 26
	nfsm_reqdone;
I 32
D 39
	VTONFS(ndp->ni_dvp)->n_direofstamp = 0;
E 39
I 39
D 58
	VTONFS(ndp->ni_dvp)->n_flag |= NMODIFIED;
E 58
I 58
D 133
	VTONFS(sp->s_dvp)->n_flag |= NMODIFIED;
I 121
	VTONFS(sp->s_dvp)->n_attrstamp = 0;
E 133
I 133
	VTONFS(dvp)->n_flag |= NMODIFIED;
	if (!wccflag)
		VTONFS(dvp)->n_attrstamp = 0;
E 133
E 121
E 58
E 39
E 32
I 5
D 6
printf("eo removeit err=%d\n",error);
E 6
E 5
	return (error);
}

/*
 * nfs file rename call
 */
D 57
nfs_rename(sndp, tndp)
E 57
I 57
D 65
nfs_rename(sndp, tndp, p)
E 65
I 65
D 66
nfs_rename(sndp, tndp, procp)
E 65
E 57
	register struct nameidata *sndp, *tndp;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 66
I 66
int
D 81
nfs_rename(fdvp, fvp, fcnp,
D 67
	   tdvp, tvp, tcnp)   /* converted to CN.   */
/* old: nfs_rename(sndp, tndp, procp) */
E 67
I 67
	   tdvp, tvp, tcnp)
E 81
I 81
D 82
nfs_rename(fdvp, fvp, fcnp, tdvp, tvp, tcnp)
E 81
E 67
	struct vnode *fdvp, *fvp;
	struct componentname *fcnp;
	struct vnode *tdvp, *tvp;
	struct componentname *tcnp;
E 82
I 82
D 89
nfs_rename (ap)
E 89
I 89
nfs_rename(ap)
E 89
D 94
	struct vop_rename_args *ap;
E 94
I 94
	struct vop_rename_args  /* {
		struct vnode *a_fdvp;
		struct vnode *a_fvp;
		struct componentname *a_fcnp;
		struct vnode *a_tdvp;
		struct vnode *a_tvp;
		struct componentname *a_tcnp;
	} */ *ap;
E 94
D 84
#define fdvp (ap->a_fdvp)
#define fvp (ap->a_fvp)
#define fcnp (ap->a_fcnp)
#define tdvp (ap->a_tdvp)
#define tvp (ap->a_tvp)
#define tcnp (ap->a_tcnp)
E 84
E 82
E 66
E 65
E 57
{
I 89
	register struct vnode *fvp = ap->a_fvp;
	register struct vnode *tvp = ap->a_tvp;
	register struct vnode *fdvp = ap->a_fdvp;
	register struct vnode *tdvp = ap->a_tdvp;
	register struct componentname *tcnp = ap->a_tcnp;
	register struct componentname *fcnp = ap->a_fcnp;
E 89
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
D 133
	register u_long *tl;
E 57
	register caddr_t cp;
D 65
	register long t1, t2;
E 65
I 65
	register long t2;
E 65
	caddr_t bpos, dpos;
D 65
	u_long xid;
E 65
	int error = 0;
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
E 133
I 133
	int error;
E 133
E 13

I 133
#ifndef DIAGNOSTIC
	if ((tcnp->cn_flags & HASBUF) == 0 ||
	    (fcnp->cn_flags & HASBUF) == 0)
		panic("nfs_rename: no name");
#endif
E 133
I 87
	/* Check for cross-device rename */
D 89
	if ((ap->a_fvp->v_mount != ap->a_tdvp->v_mount) ||
	    (ap->a_tvp && (ap->a_fvp->v_mount != ap->a_tvp->v_mount))) {
E 89
I 89
	if ((fvp->v_mount != tdvp->v_mount) ||
	    (tvp && (fvp->v_mount != tvp->v_mount))) {
E 89
		error = EXDEV;
		goto out;
	}

I 133
	/*
	 * If the tvp exists and is in use, sillyrename it before doing the
	 * rename of the new file over it.
	 */
	if (tvp && tvp->v_usecount > 1 && !VTONFS(tvp)->n_sillyrename &&
		!nfs_sillyrename(tdvp, tvp, tcnp)) {
		vrele(tvp);
		tvp = NULL;
	}
E 133

E 87
D 133
	nfsstats.rpccnt[NFSPROC_RENAME]++;
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_RENAME], tndp->ni_cred,
D 59
		(NFSX_FH+NFSX_UNSIGNED)*2+nfsm_rndup(sndp->ni_dent.d_namlen)+
		nfsm_rndup(tndp->ni_dent.d_namlen)); /* or sndp->ni_cred?*/
E 59
I 59
		(NFSX_FH+NFSX_UNSIGNED)*2+nfsm_rndup(sndp->ni_namelen) +
E 65
I 65
D 66
	nfsm_reqhead(sndp->ni_dvp, NFSPROC_RENAME,
		(NFSX_FH+NFSX_UNSIGNED)*2+nfsm_rndup(sndp->ni_namelen)+
E 65
		nfsm_rndup(tndp->ni_namelen)); /* or sndp->ni_cred?*/
E 59
	nfsm_fhtom(sndp->ni_dvp);
D 59
	nfsm_strtom(sndp->ni_dent.d_name,sndp->ni_dent.d_namlen,NFS_MAXNAMLEN);
E 59
I 59
	nfsm_strtom(sndp->ni_ptr, sndp->ni_namelen, NFS_MAXNAMLEN);
E 59
	nfsm_fhtom(tndp->ni_dvp);
D 59
	nfsm_strtom(tndp->ni_dent.d_name,tndp->ni_dent.d_namlen,NFS_MAXNAMLEN);
E 59
I 59
	nfsm_strtom(tndp->ni_ptr, tndp->ni_namelen, NFS_MAXNAMLEN);
E 59
D 26
	nfsm_request(sndp->ni_dvp);
E 26
I 26
D 39
	nfsm_request(sndp->ni_dvp, nonidempotent[NFSPROC_RENAME]);
E 39
I 39
D 42
	nfsm_request(sndp->ni_dvp, NFSPROC_RENAME, u.u_procp);
E 42
I 42
D 56
	nfsm_request(sndp->ni_dvp, NFSPROC_RENAME, u.u_procp, 1);
E 56
I 56
D 57
	nfsm_request(sndp->ni_dvp, NFSPROC_RENAME, curproc, 1);
E 57
I 57
D 65
	nfsm_request(sndp->ni_dvp, NFSPROC_RENAME, p, 1);
E 65
I 65
	nfsm_request(sndp->ni_dvp, NFSPROC_RENAME, procp, tndp->ni_cred);
E 66
I 66
D 84
	nfsm_reqhead(fdvp, NFSPROC_RENAME,
		(NFSX_FH+NFSX_UNSIGNED)*2+nfsm_rndup(fcnp->cn_namelen)+
		nfsm_rndup(fcnp->cn_namelen)); /* or fcnp->cn_cred?*/
	nfsm_fhtom(fdvp);
	nfsm_strtom(fcnp->cn_nameptr, fcnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_fhtom(tdvp);
	nfsm_strtom(tcnp->cn_nameptr, tcnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_request(fdvp, NFSPROC_RENAME, tcnp->cn_proc, tcnp->cn_cred);
E 84
I 84
D 89
	nfsm_reqhead(ap->a_fdvp, NFSPROC_RENAME,
		(NFSX_FH+NFSX_UNSIGNED)*2+nfsm_rndup(ap->a_fcnp->cn_namelen)+
		nfsm_rndup(ap->a_fcnp->cn_namelen)); /* or ap->a_fcnp->cn_cred?*/
	nfsm_fhtom(ap->a_fdvp);
	nfsm_strtom(ap->a_fcnp->cn_nameptr, ap->a_fcnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_fhtom(ap->a_tdvp);
	nfsm_strtom(ap->a_tcnp->cn_nameptr, ap->a_tcnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_request(ap->a_fdvp, NFSPROC_RENAME, ap->a_tcnp->cn_proc, ap->a_tcnp->cn_cred);
E 89
I 89
	nfsm_reqhead(fdvp, NFSPROC_RENAME,
		(NFSX_FH+NFSX_UNSIGNED)*2+nfsm_rndup(fcnp->cn_namelen)+
		nfsm_rndup(fcnp->cn_namelen)); /* or fcnp->cn_cred?*/
	nfsm_fhtom(fdvp);
	nfsm_strtom(fcnp->cn_nameptr, fcnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_fhtom(tdvp);
	nfsm_strtom(tcnp->cn_nameptr, tcnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_request(fdvp, NFSPROC_RENAME, tcnp->cn_proc, tcnp->cn_cred);
E 89
E 84
E 66
E 65
E 57
E 56
E 42
E 39
E 26
	nfsm_reqdone;
I 32
D 39
	VTONFS(sndp->ni_dvp)->n_direofstamp = 0;
	VTONFS(tndp->ni_dvp)->n_direofstamp = 0;
E 39
I 39
D 66
	VTONFS(sndp->ni_dvp)->n_flag |= NMODIFIED;
	VTONFS(tndp->ni_dvp)->n_flag |= NMODIFIED;
E 39
E 32
D 5
#ifdef notyet
E 5
I 5
D 7
#ifndef notyet
E 7
E 5
	if (sndp->ni_vp->v_type == VDIR) {
		if (tndp->ni_vp != NULL && tndp->ni_vp->v_type == VDIR)
			cache_purge(tndp->ni_dvp);
		cache_purge(sndp->ni_dvp);
E 66
I 66
D 84
	VTONFS(fdvp)->n_flag |= NMODIFIED;
	VTONFS(tdvp)->n_flag |= NMODIFIED;
	if (fvp->v_type == VDIR) {
		if (tvp != NULL && tvp->v_type == VDIR)
			cache_purge(tdvp);
		cache_purge(fdvp);
E 84
I 84
D 89
	VTONFS(ap->a_fdvp)->n_flag |= NMODIFIED;
	VTONFS(ap->a_tdvp)->n_flag |= NMODIFIED;
	if (ap->a_fvp->v_type == VDIR) {
		if (ap->a_tvp != NULL && ap->a_tvp->v_type == VDIR)
			cache_purge(ap->a_tdvp);
		cache_purge(ap->a_fdvp);
E 89
I 89
	VTONFS(fdvp)->n_flag |= NMODIFIED;
I 121
	VTONFS(fdvp)->n_attrstamp = 0;
E 121
	VTONFS(tdvp)->n_flag |= NMODIFIED;
I 121
	VTONFS(tdvp)->n_attrstamp = 0;
E 133
I 133
	error = nfs_renamerpc(fdvp, fcnp->cn_nameptr, fcnp->cn_namelen,
		tdvp, tcnp->cn_nameptr, tcnp->cn_namelen, tcnp->cn_cred,
		tcnp->cn_proc);

E 133
E 121
	if (fvp->v_type == VDIR) {
		if (tvp != NULL && tvp->v_type == VDIR)
			cache_purge(tdvp);
		cache_purge(fdvp);
E 89
E 84
E 66
	}
I 87
out:
E 87
D 7
#endif
E 7
D 41
	nfs_abortop(sndp);
	nfs_abortop(tndp);
E 41
I 41
D 59
	VOP_ABORTOP(tndp);
E 59
D 43
	vput(tndp->ni_dvp);
E 43
I 43
D 66
	if (tndp->ni_dvp == tndp->ni_vp)
		vrele(tndp->ni_dvp);
E 66
I 66
D 84
	if (tdvp == tvp)
		vrele(tdvp);
E 84
I 84
D 89
	if (ap->a_tdvp == ap->a_tvp)
		vrele(ap->a_tdvp);
E 89
I 89
	if (tdvp == tvp)
		vrele(tdvp);
E 89
E 84
E 66
	else
D 66
		vput(tndp->ni_dvp);
E 43
	if (tndp->ni_vp)
		vput(tndp->ni_vp);
D 59
	VOP_ABORTOP(sndp);
E 59
	vrele(sndp->ni_dvp);
	vrele(sndp->ni_vp);
E 66
I 66
D 84
		vput(tdvp);
	if (tvp)
		vput(tvp);
	vrele(fdvp);
	vrele(fvp);
E 84
I 84
D 89
		vput(ap->a_tdvp);
	if (ap->a_tvp)
		vput(ap->a_tvp);
	vrele(ap->a_fdvp);
	vrele(ap->a_fvp);
E 89
I 89
		vput(tdvp);
	if (tvp)
		vput(tvp);
	vrele(fdvp);
	vrele(fvp);
E 89
E 84
E 66
E 41
I 26
	/*
	 * Kludge: Map ENOENT => 0 assuming that it is a reply to a retry.
	 */
	if (error == ENOENT)
		error = 0;
E 26
	return (error);
}
I 82
D 84
#undef fdvp
#undef fvp
#undef fcnp
#undef tdvp
#undef tvp
#undef tcnp
E 84
E 82

/*
D 39
 * nfs file rename rpc called from above
E 39
I 39
 * nfs file rename rpc called from nfs_remove() above
E 39
 */
D 57
nfs_renameit(sndp, tndp)
E 57
I 57
D 58
nfs_renameit(sndp, tndp, p)
E 57
	register struct nameidata *sndp, *tndp;
E 58
I 58
D 65
nfs_renameit(sndp, sp, p)
E 65
I 65
D 66
nfs_renameit(sndp, sp, procp)
E 65
	register struct nameidata *sndp;
E 66
I 66
int
nfs_renameit(sdvp, scnp, sp)
	struct vnode *sdvp;
	struct componentname *scnp;
E 66
	register struct sillyrename *sp;
E 58
I 57
D 65
	struct proc *p;
E 65
I 65
D 66
	struct proc *procp;
E 66
E 65
E 57
{
I 133
	return (nfs_renamerpc(sdvp, scnp->cn_nameptr, scnp->cn_namelen,
		sdvp, sp->s_name, sp->s_namlen, scnp->cn_cred, scnp->cn_proc));
}

/*
 * Do an nfs rename rpc. Called from nfs_rename() and nfs_renameit().
 */
int
nfs_renamerpc(fdvp, fnameptr, fnamelen, tdvp, tnameptr, tnamelen, cred, proc)
	register struct vnode *fdvp;
	char *fnameptr;
	int fnamelen;
	register struct vnode *tdvp;
	char *tnameptr;
	int tnamelen;
	struct ucred *cred;
	struct proc *proc;
{
E 133
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
D 65
	register long t1, t2;
E 65
I 65
D 133
	register long t2;
E 65
	caddr_t bpos, dpos;
D 65
	u_long xid;
E 65
	int error = 0;
E 133
I 133
	register long t1, t2;
	caddr_t bpos, dpos, cp2;
	int error = 0, fwccflag = NFSV3_WCCRATTR, twccflag = NFSV3_WCCRATTR;
E 133
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
I 133
	int v3 = NFS_ISV3(fdvp);
E 133
E 13

	nfsstats.rpccnt[NFSPROC_RENAME]++;
D 58
	nfsm_reqhead(nfs_procids[NFSPROC_RENAME], tndp->ni_cred,
E 58
I 58
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_RENAME], sp->s_cred,
E 58
D 59
		(NFSX_FH+NFSX_UNSIGNED)*2+nfsm_rndup(sndp->ni_dent.d_namlen)+
E 59
I 59
		(NFSX_FH+NFSX_UNSIGNED)*2+nfsm_rndup(sndp->ni_namelen) +
E 59
D 58
		nfsm_rndup(tndp->ni_dent.d_namlen)); /* or sndp->ni_cred?*/
E 58
I 58
		nfsm_rndup(sp->s_namlen)); /* or sndp->ni_cred?*/
E 65
I 65
D 66
	nfsm_reqhead(sndp->ni_dvp, NFSPROC_RENAME,
		(NFSX_FH+NFSX_UNSIGNED)*2+nfsm_rndup(sndp->ni_namelen)+
E 66
I 66
D 133
	nfsm_reqhead(sdvp, NFSPROC_RENAME,
		(NFSX_FH+NFSX_UNSIGNED)*2+nfsm_rndup(scnp->cn_namelen)+
E 66
		nfsm_rndup(sp->s_namlen));
E 65
E 58
D 66
	nfsm_fhtom(sndp->ni_dvp);
D 59
	nfsm_strtom(sndp->ni_dent.d_name,sndp->ni_dent.d_namlen,NFS_MAXNAMLEN);
E 59
I 59
	nfsm_strtom(sndp->ni_ptr, sndp->ni_namelen, NFS_MAXNAMLEN);
E 59
D 58
	nfsm_fhtom(tndp->ni_dvp);
	nfsm_strtom(tndp->ni_dent.d_name,tndp->ni_dent.d_namlen,NFS_MAXNAMLEN);
E 58
I 58
	nfsm_fhtom(sp->s_dvp);
E 66
I 66
	nfsm_fhtom(sdvp);
	nfsm_strtom(scnp->cn_nameptr, scnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_fhtom(sdvp);
E 66
	nfsm_strtom(sp->s_name, sp->s_namlen, NFS_MAXNAMLEN);
E 58
D 26
	nfsm_request(sndp->ni_dvp);
E 26
I 26
D 39
	nfsm_request(sndp->ni_dvp, nonidempotent[NFSPROC_RENAME]);
E 39
I 39
D 42
	nfsm_request(sndp->ni_dvp, NFSPROC_RENAME, u.u_procp);
E 42
I 42
D 56
	nfsm_request(sndp->ni_dvp, NFSPROC_RENAME, u.u_procp, 1);
E 56
I 56
D 57
	nfsm_request(sndp->ni_dvp, NFSPROC_RENAME, curproc, 1);
E 57
I 57
D 65
	nfsm_request(sndp->ni_dvp, NFSPROC_RENAME, p, 1);
E 65
I 65
D 66
	nfsm_request(sndp->ni_dvp, NFSPROC_RENAME, procp, sndp->ni_cred);
E 66
I 66
	nfsm_request(sdvp, NFSPROC_RENAME, scnp->cn_proc, scnp->cn_cred);
E 133
I 133
	nfsm_reqhead(fdvp, NFSPROC_RENAME,
		(NFSX_FH(v3) + NFSX_UNSIGNED)*2 + nfsm_rndup(fnamelen) +
		nfsm_rndup(tnamelen));
	nfsm_fhtom(fdvp, v3);
	nfsm_strtom(fnameptr, fnamelen, NFS_MAXNAMLEN);
	nfsm_fhtom(tdvp, v3);
	nfsm_strtom(tnameptr, tnamelen, NFS_MAXNAMLEN);
	nfsm_request(fdvp, NFSPROC_RENAME, proc, cred);
	if (v3) {
		nfsm_wcc_data(fdvp, fwccflag);
		nfsm_wcc_data(tdvp, twccflag);
	}
E 133
E 66
E 65
E 57
E 56
E 42
E 39
E 26
	nfsm_reqdone;
I 59
D 66
	FREE(sndp->ni_pnbuf, M_NAMEI);
E 59
I 32
D 39
	VTONFS(sndp->ni_dvp)->n_direofstamp = 0;
	VTONFS(tndp->ni_dvp)->n_direofstamp = 0;
E 39
I 39
	VTONFS(sndp->ni_dvp)->n_flag |= NMODIFIED;
E 66
I 66
D 133
	FREE(scnp->cn_pnbuf, M_NAMEI);
	VTONFS(sdvp)->n_flag |= NMODIFIED;
I 121
	VTONFS(sdvp)->n_attrstamp = 0;
E 133
I 133
	VTONFS(fdvp)->n_flag |= NMODIFIED;
	VTONFS(tdvp)->n_flag |= NMODIFIED;
	if (!fwccflag)
		VTONFS(fdvp)->n_attrstamp = 0;
	if (!twccflag)
		VTONFS(tdvp)->n_attrstamp = 0;
E 133
E 121
E 66
D 58
	VTONFS(tndp->ni_dvp)->n_flag |= NMODIFIED;
E 58
I 58
D 65
	VTONFS(sp->s_dvp)->n_flag |= NMODIFIED;
E 65
E 58
E 39
E 32
	return (error);
}

/*
 * nfs hard link create call
 */
D 57
nfs_link(vp, ndp)
E 57
I 57
D 65
nfs_link(vp, ndp, p)
E 65
I 65
D 66
nfs_link(vp, ndp, procp)
E 65
E 57
D 13
	struct vnode *vp;
E 13
I 13
	register struct vnode *vp;
E 13
	register struct nameidata *ndp;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 66
I 66
int
D 67
nfs_link(vp, tdvp, cnp)   /* converted to CN.   */
/* old: nfs_link(vp, ndp, procp) */
E 67
I 67
D 69
nfs_link(vp, tdvp, cnp)
E 67
	register struct vnode *vp;   /* source vnode */
E 69
I 69
D 82
nfs_link(tdvp, vp, cnp)
E 69
	struct vnode *tdvp;
I 69
	register struct vnode *vp;   /* source vnode */
E 69
	struct componentname *cnp;
E 82
I 82
D 89
nfs_link (ap)
E 89
I 89
nfs_link(ap)
E 89
D 94
	struct vop_link_args *ap;
E 94
I 94
	struct vop_link_args /* {
		struct vnode *a_vp;
		struct vnode *a_tdvp;
		struct componentname *a_cnp;
	} */ *ap;
E 94
D 84
#define tdvp (ap->a_vp)
#define vp (ap->a_tdvp)
#define cnp (ap->a_cnp)
E 84
E 82
E 66
E 65
E 57
{
I 89
	register struct vnode *vp = ap->a_vp;
	register struct vnode *tdvp = ap->a_tdvp;
	register struct componentname *cnp = ap->a_cnp;
E 89
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
D 65
	register long t1, t2;
E 65
I 65
D 133
	register long t2;
E 65
	caddr_t bpos, dpos;
D 65
	u_long xid;
E 65
	int error = 0;
E 133
I 133
	register long t1, t2;
	caddr_t bpos, dpos, cp2;
	int error = 0, wccflag = NFSV3_WCCRATTR, attrflag = 0;
E 133
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
I 133
	int v3 = NFS_ISV3(vp);
E 133
I 87

D 89
	if (ap->a_vp->v_mount != ap->a_tdvp->v_mount) {
		/*VOP_ABORTOP(ap->a_vp, ap->a_cnp);*/
		if (ap->a_tdvp == ap->a_vp)
			vrele(ap->a_vp);
E 89
I 89
D 132
	if (vp->v_mount != tdvp->v_mount) {
		/*VOP_ABORTOP(vp, cnp);*/
		if (tdvp == vp)
			vrele(vp);
E 89
		else
D 89
			vput(ap->a_vp);
		vrele(ap->a_tdvp);
E 89
I 89
			vput(vp);
E 132
I 132
D 133
	if (tdvp->v_mount != vp->v_mount) {
		VOP_ABORTOP(tdvp, cnp);
		vput(tdvp);
E 133
I 133
	if (vp->v_mount != tdvp->v_mount) {
		/*VOP_ABORTOP(vp, cnp);*/
		if (tdvp == vp)
			vrele(tdvp);
		else
			vput(tdvp);
E 133
E 132
D 91
		vrele(tdvp);
E 91
E 89
		return (EXDEV);
	}
E 87
E 13

I 129
	/*
	 * Push all writes to the server, so that the attribute cache
	 * doesn't get "out of sync" with the server.
	 * XXX There should be a better way!
	 */
D 132
	VOP_FSYNC(tdvp, cnp->cn_cred, MNT_WAIT, cnp->cn_proc);
E 132
I 132
	VOP_FSYNC(vp, cnp->cn_cred, MNT_WAIT, cnp->cn_proc);
E 132

E 129
I 2
D 65
	if (ndp->ni_dvp != vp)
		nfs_lock(vp);
E 65
E 2
	nfsstats.rpccnt[NFSPROC_LINK]++;
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_LINK], ndp->ni_cred,
E 65
I 65
D 84
	nfsm_reqhead(vp, NFSPROC_LINK,
E 65
D 59
		NFSX_FH*2+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_dent.d_namlen));
E 59
I 59
D 66
		NFSX_FH*2+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_namelen));
E 66
I 66
		NFSX_FH*2+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen));
E 66
E 59
	nfsm_fhtom(vp);
D 66
	nfsm_fhtom(ndp->ni_dvp);
D 59
	nfsm_strtom(ndp->ni_dent.d_name, ndp->ni_dent.d_namlen, NFS_MAXNAMLEN);
E 59
I 59
	nfsm_strtom(ndp->ni_ptr, ndp->ni_namelen, NFS_MAXNAMLEN);
E 59
D 26
	nfsm_request(vp);
E 26
I 26
D 39
	nfsm_request(vp, nonidempotent[NFSPROC_LINK]);
E 39
I 39
D 42
	nfsm_request(vp, NFSPROC_LINK, u.u_procp);
E 42
I 42
D 56
	nfsm_request(vp, NFSPROC_LINK, u.u_procp, 1);
E 56
I 56
D 57
	nfsm_request(vp, NFSPROC_LINK, curproc, 1);
E 57
I 57
D 65
	nfsm_request(vp, NFSPROC_LINK, p, 1);
E 65
I 65
	nfsm_request(vp, NFSPROC_LINK, procp, ndp->ni_cred);
E 66
I 66
	nfsm_fhtom(tdvp);
	nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_request(vp, NFSPROC_LINK, cnp->cn_proc, cnp->cn_cred);
E 84
I 84
D 89
	nfsm_reqhead(ap->a_tdvp, NFSPROC_LINK,
		NFSX_FH*2+NFSX_UNSIGNED+nfsm_rndup(ap->a_cnp->cn_namelen));
	nfsm_fhtom(ap->a_tdvp);
	nfsm_fhtom(ap->a_vp);
	nfsm_strtom(ap->a_cnp->cn_nameptr, ap->a_cnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_request(ap->a_tdvp, NFSPROC_LINK, ap->a_cnp->cn_proc, ap->a_cnp->cn_cred);
E 89
I 89
D 132
	nfsm_reqhead(tdvp, NFSPROC_LINK,
E 132
I 132
	nfsm_reqhead(vp, NFSPROC_LINK,
E 132
D 133
		NFSX_FH*2+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen));
D 132
	nfsm_fhtom(tdvp);
E 132
	nfsm_fhtom(vp);
I 132
	nfsm_fhtom(tdvp);
E 133
I 133
		NFSX_FH(v3)*2 + NFSX_UNSIGNED + nfsm_rndup(cnp->cn_namelen));
	nfsm_fhtom(vp, v3);
	nfsm_fhtom(tdvp, v3);
E 133
E 132
	nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
D 132
	nfsm_request(tdvp, NFSPROC_LINK, cnp->cn_proc, cnp->cn_cred);
E 132
I 132
	nfsm_request(vp, NFSPROC_LINK, cnp->cn_proc, cnp->cn_cred);
I 133
	if (v3) {
		nfsm_postop_attr(vp, attrflag);
		nfsm_wcc_data(tdvp, wccflag);
	}
E 133
E 132
E 89
E 84
E 66
E 65
E 57
E 56
E 42
E 39
E 26
	nfsm_reqdone;
I 59
D 66
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 66
I 66
D 84
	FREE(cnp->cn_pnbuf, M_NAMEI);
E 66
E 59
I 25
	VTONFS(vp)->n_attrstamp = 0;
I 32
D 39
	VTONFS(ndp->ni_dvp)->n_direofstamp = 0;
E 39
I 39
D 66
	VTONFS(ndp->ni_dvp)->n_flag |= NMODIFIED;
E 39
E 32
E 25
I 2
D 65
	if (ndp->ni_dvp != vp)
		nfs_unlock(vp);
E 2
	nfs_nput(ndp->ni_dvp);
E 65
I 65
	vrele(ndp->ni_dvp);
E 66
I 66
	VTONFS(tdvp)->n_flag |= NMODIFIED;
	vrele(tdvp);
E 84
I 84
D 89
	FREE(ap->a_cnp->cn_pnbuf, M_NAMEI);
	VTONFS(ap->a_tdvp)->n_attrstamp = 0;
	VTONFS(ap->a_vp)->n_flag |= NMODIFIED;
	vrele(ap->a_vp);
E 89
I 89
	FREE(cnp->cn_pnbuf, M_NAMEI);
D 132
	VTONFS(tdvp)->n_attrstamp = 0;
D 121
	VTONFS(vp)->n_flag |= NMODIFIED;
E 121
I 121
	VTONFS(tdvp)->n_flag |= NMODIFIED;
E 132
D 133
	VTONFS(vp)->n_attrstamp = 0;
E 121
D 132
	vrele(vp);
E 132
I 132
	VTONFS(vp)->n_flag |= NMODIFIED;
	VTONFS(tdvp)->n_attrstamp = 0;
	vput(tdvp);
E 133
I 133
	VTONFS(tdvp)->n_flag |= NMODIFIED;
	if (!attrflag)
		VTONFS(vp)->n_attrstamp = 0;
	if (!wccflag)
		VTONFS(tdvp)->n_attrstamp = 0;
	vrele(tdvp);
E 133
E 132
E 89
E 84
E 66
E 65
I 26
	/*
	 * Kludge: Map EEXIST => 0 assuming that it is a reply to a retry.
	 */
	if (error == EEXIST)
		error = 0;
E 26
	return (error);
}
I 82
D 84
#undef tdvp
#undef vp
#undef cnp
E 84
E 82

/*
 * nfs symbolic link create call
 */
D 57
nfs_symlink(ndp, vap, nm)
E 57
I 57
D 65
nfs_symlink(ndp, vap, nm, p)
E 65
I 65
D 66
nfs_symlink(ndp, vap, nm, procp)
E 65
E 57
	struct nameidata *ndp;
E 66
I 66
D 133
/* start here */
E 133
int
D 67
nfs_symlink(dvp, vpp, cnp, vap, nm)   /* converted to CN.   */
/* old: nfs_symlink(ndp, vap, nm, procp) */
E 67
I 67
D 82
nfs_symlink(dvp, vpp, cnp, vap, nm)
E 67
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
E 66
	struct vattr *vap;
D 65
	char *nm;		/* is this the path ?? */
I 57
	struct proc *p;
E 65
I 65
	char *nm;
E 82
I 82
D 89
nfs_symlink (ap)
E 89
I 89
nfs_symlink(ap)
E 89
D 94
	struct vop_symlink_args *ap;
E 94
I 94
	struct vop_symlink_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
		char *a_target;
	} */ *ap;
E 94
D 84
#define dvp (ap->a_dvp)
#define vpp (ap->a_vpp)
#define cnp (ap->a_cnp)
#define vap (ap->a_vap)
#define nm (ap->a_target)
E 84
E 82
D 66
	struct proc *procp;
E 66
E 65
E 57
{
I 89
	register struct vnode *dvp = ap->a_dvp;
	register struct vattr *vap = ap->a_vap;
	register struct componentname *cnp = ap->a_cnp;
E 89
I 5
	register struct nfsv2_sattr *sp;
I 133
	register struct nfsv3_sattr *sp3;
E 133
E 5
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
D 65
	register long t1, t2;
E 65
I 65
D 133
	register long t2;
E 65
	caddr_t bpos, dpos;
D 65
	u_long xid;
	int error = 0;
E 65
I 65
D 100
	int slen, error = 0;
E 100
I 100
	int slen, error = 0, isnq;
E 133
I 133
	register long t1, t2;
	caddr_t bpos, dpos, cp2;
	int slen, error = 0, wccflag = NFSV3_WCCRATTR, gotvp;
E 133
E 100
E 65
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
I 133
	struct vnode *newvp = (struct vnode *)0;
	int v3 = NFS_ISV3(dvp);
E 133
E 13

	nfsstats.rpccnt[NFSPROC_SYMLINK]++;
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_SYMLINK], ndp->ni_cred,
D 59
	NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_dent.d_namlen)+NFSX_UNSIGNED);
E 59
I 59
	NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_namelen)+NFSX_UNSIGNED);
E 65
I 65
D 84
	slen = strlen(nm);
D 66
	nfsm_reqhead(ndp->ni_dvp, NFSPROC_SYMLINK,
	 NFSX_FH+2*NFSX_UNSIGNED+nfsm_rndup(ndp->ni_namelen)+nfsm_rndup(slen)+NFSX_SATTR);
E 65
E 59
	nfsm_fhtom(ndp->ni_dvp);
D 59
	nfsm_strtom(ndp->ni_dent.d_name, ndp->ni_dent.d_namlen, NFS_MAXNAMLEN);
E 59
I 59
	nfsm_strtom(ndp->ni_ptr, ndp->ni_namelen, NFS_MAXNAMLEN);
E 66
I 66
	nfsm_reqhead(dvp, NFSPROC_SYMLINK,
	 NFSX_FH+2*NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen)+nfsm_rndup(slen)+NFSX_SATTR);
	nfsm_fhtom(dvp);
	nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
E 66
E 59
D 65
	nfsm_strtom(nm, strlen(nm), NFS_MAXPATHLEN);
E 65
I 65
	nfsm_strtom(nm, slen, NFS_MAXPATHLEN);
E 84
I 84
	slen = strlen(ap->a_target);
I 100
D 133
	isnq = (VFSTONFS(dvp->v_mount)->nm_flag & NFSMNT_NQNFS);
E 100
D 89
	nfsm_reqhead(ap->a_dvp, NFSPROC_SYMLINK,
	 NFSX_FH+2*NFSX_UNSIGNED+nfsm_rndup(ap->a_cnp->cn_namelen)+nfsm_rndup(slen)+NFSX_SATTR);
	nfsm_fhtom(ap->a_dvp);
	nfsm_strtom(ap->a_cnp->cn_nameptr, ap->a_cnp->cn_namelen, NFS_MAXNAMLEN);
E 89
I 89
	nfsm_reqhead(dvp, NFSPROC_SYMLINK, NFSX_FH+2*NFSX_UNSIGNED+
D 100
	    nfsm_rndup(cnp->cn_namelen)+nfsm_rndup(slen)+NFSX_SATTR);
E 100
I 100
	    nfsm_rndup(cnp->cn_namelen)+nfsm_rndup(slen)+NFSX_SATTR(isnq));
E 100
	nfsm_fhtom(dvp);
E 133
I 133
	nfsm_reqhead(dvp, NFSPROC_SYMLINK, NFSX_FH(v3) + 2*NFSX_UNSIGNED +
	    nfsm_rndup(cnp->cn_namelen) + nfsm_rndup(slen) + NFSX_SATTR(v3));
	nfsm_fhtom(dvp, v3);
E 133
	nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
I 133
	if (v3) {
		nfsm_build(sp3, struct nfsv3_sattr *, NFSX_V3SRVSATTR);
		nfsm_v3sattr(sp3, vap, cnp->cn_cred->cr_uid,
			cnp->cn_cred->cr_gid);
	}
E 133
E 89
	nfsm_strtom(ap->a_target, slen, NFS_MAXPATHLEN);
E 84
E 65
D 5
	nfsm_build(p, u_long *, NFSX_SATTR);
	*p++ = vtonfs_mode(VLNK, vap->va_mode);
	*p++ = txdr_unsigned(ndp->ni_cred->cr_uid);
	*p++ = txdr_unsigned(ndp->ni_cred->cr_gid);
	*p++ = txdr_unsigned(VNOVAL);
	txdr_time(&(vap->va_atime), p);		/* or VNOVAL ?? */
	txdr_time(&(vap->va_mtime), p+2);	/* or VNOVAL ?? */
E 5
I 5
D 100
	nfsm_build(sp, struct nfsv2_sattr *, NFSX_SATTR);
E 100
I 100
D 133
	nfsm_build(sp, struct nfsv2_sattr *, NFSX_SATTR(isnq));
E 100
D 84
	sp->sa_mode = vtonfs_mode(VLNK, vap->va_mode);
D 66
	sp->sa_uid = txdr_unsigned(ndp->ni_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(ndp->ni_cred->cr_gid);
E 66
I 66
	sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(cnp->cn_cred->cr_gid);
E 84
I 84
D 89
	sp->sa_mode = vtonfs_mode(VLNK, ap->a_vap->va_mode);
	sp->sa_uid = txdr_unsigned(ap->a_cnp->cn_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(ap->a_cnp->cn_cred->cr_gid);
E 89
I 89
	sp->sa_mode = vtonfs_mode(VLNK, vap->va_mode);
	sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(cnp->cn_cred->cr_gid);
E 89
E 84
E 66
D 100
	sp->sa_size = txdr_unsigned(VNOVAL);
D 26
	txdr_time(&vap->va_atime, &sp->sa_atime);		/* or VNOVAL ?? */
E 26
I 26
D 84
	txdr_time(&vap->va_atime, &sp->sa_atime);	/* or VNOVAL ?? */
E 26
	txdr_time(&vap->va_mtime, &sp->sa_mtime);	/* or VNOVAL ?? */
E 5
D 26
	nfsm_request(ndp->ni_dvp);
E 26
I 26
D 39
	nfsm_request(ndp->ni_dvp, nonidempotent[NFSPROC_SYMLINK]);
E 39
I 39
D 42
	nfsm_request(ndp->ni_dvp, NFSPROC_SYMLINK, u.u_procp);
E 42
I 42
D 56
	nfsm_request(ndp->ni_dvp, NFSPROC_SYMLINK, u.u_procp, 1);
E 56
I 56
D 57
	nfsm_request(ndp->ni_dvp, NFSPROC_SYMLINK, curproc, 1);
E 57
I 57
D 65
	nfsm_request(ndp->ni_dvp, NFSPROC_SYMLINK, p, 1);
E 65
I 65
D 66
	nfsm_request(ndp->ni_dvp, NFSPROC_SYMLINK, procp, ndp->ni_cred);
E 66
I 66
	nfsm_request(dvp, NFSPROC_SYMLINK, cnp->cn_proc, cnp->cn_cred);
E 84
I 84
D 89
	txdr_time(&ap->a_vap->va_atime, &sp->sa_atime);	/* or VNOVAL ?? */
	txdr_time(&ap->a_vap->va_mtime, &sp->sa_mtime);	/* or VNOVAL ?? */
	nfsm_request(ap->a_dvp, NFSPROC_SYMLINK, ap->a_cnp->cn_proc, ap->a_cnp->cn_cred);
E 89
I 89
	txdr_time(&vap->va_atime, &sp->sa_atime);	/* or VNOVAL ?? */
	txdr_time(&vap->va_mtime, &sp->sa_mtime);	/* or VNOVAL ?? */
E 100
I 100
	if (isnq) {
		quad_t qval = -1;

		txdr_hyper(&qval, &sp->sa_nqsize);
		sp->sa_nqflags = 0;
		txdr_nqtime(&vap->va_atime, &sp->sa_nqatime);
		txdr_nqtime(&vap->va_mtime, &sp->sa_nqmtime);
	} else {
		sp->sa_nfssize = -1;
		txdr_nfstime(&vap->va_atime, &sp->sa_nfsatime);
		txdr_nfstime(&vap->va_mtime, &sp->sa_nfsmtime);
E 133
I 133
	if (!v3) {
		nfsm_build(sp, struct nfsv2_sattr *, NFSX_V2SATTR);
		sp->sa_mode = vtonfsv2_mode(VLNK, vap->va_mode);
		sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
		sp->sa_gid = txdr_unsigned(cnp->cn_cred->cr_gid);
		sp->sa_size = -1;
		txdr_nfsv2time(&vap->va_atime, &sp->sa_atime);
		txdr_nfsv2time(&vap->va_mtime, &sp->sa_mtime);
E 133
	}
E 100
	nfsm_request(dvp, NFSPROC_SYMLINK, cnp->cn_proc, cnp->cn_cred);
I 133
	if (v3) {
		if (!error)
			nfsm_mtofh(dvp, newvp, v3, gotvp);
		nfsm_wcc_data(dvp, wccflag);
	}
E 133
E 89
E 84
E 66
E 65
E 57
E 56
E 42
E 39
E 26
	nfsm_reqdone;
I 133
	if (newvp)
		vrele(newvp);
E 133
I 59
D 66
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 59
I 32
D 39
	VTONFS(ndp->ni_dvp)->n_direofstamp = 0;
E 39
I 39
	VTONFS(ndp->ni_dvp)->n_flag |= NMODIFIED;
E 39
E 32
D 65
	nfs_nput(ndp->ni_dvp);
E 65
I 65
	vrele(ndp->ni_dvp);
E 66
I 66
D 84
	FREE(cnp->cn_pnbuf, M_NAMEI);
	VTONFS(dvp)->n_flag |= NMODIFIED;
	vrele(dvp);
E 84
I 84
D 89
	FREE(ap->a_cnp->cn_pnbuf, M_NAMEI);
	VTONFS(ap->a_dvp)->n_flag |= NMODIFIED;
	vrele(ap->a_dvp);
E 89
I 89
	FREE(cnp->cn_pnbuf, M_NAMEI);
	VTONFS(dvp)->n_flag |= NMODIFIED;
I 121
D 133
	VTONFS(dvp)->n_attrstamp = 0;
E 133
I 133
	if (!wccflag)
		VTONFS(dvp)->n_attrstamp = 0;
E 133
E 121
	vrele(dvp);
E 89
E 84
E 66
E 65
I 26
	/*
	 * Kludge: Map EEXIST => 0 assuming that it is a reply to a retry.
	 */
I 66
D 67
	/*
	 * NEEDSWORK: what about *vpp?
	 */
E 67
E 66
	if (error == EEXIST)
		error = 0;
E 26
	return (error);
}
I 82
D 84
#undef dvp
#undef vpp
#undef cnp
#undef vap
#undef nm
E 84
E 82

/*
 * nfs make dir call
 */
D 57
nfs_mkdir(ndp, vap)
E 57
I 57
D 65
nfs_mkdir(ndp, vap, p)
E 65
I 65
D 66
nfs_mkdir(ndp, vap, procp)
E 65
E 57
D 13
	struct nameidata *ndp;
E 13
I 13
	register struct nameidata *ndp;
E 66
I 66
int
D 67
nfs_mkdir(dvp, vpp, cnp, vap)   /* converted to CN.   */
/* old: nfs_mkdir(ndp, vap, procp) */
E 67
I 67
D 82
nfs_mkdir(dvp, vpp, cnp, vap)
E 67
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
E 66
E 13
	struct vattr *vap;
E 82
I 82
D 89
nfs_mkdir (ap)
E 89
I 89
nfs_mkdir(ap)
E 89
D 94
	struct vop_mkdir_args *ap;
E 94
I 94
	struct vop_mkdir_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
	} */ *ap;
E 94
D 84
#define dvp (ap->a_dvp)
#define vpp (ap->a_vpp)
#define cnp (ap->a_cnp)
#define vap (ap->a_vap)
E 84
E 82
I 57
D 65
	struct proc *p;
E 65
I 65
D 66
	struct proc *procp;
E 66
E 65
E 57
{
I 89
	register struct vnode *dvp = ap->a_dvp;
	register struct vattr *vap = ap->a_vap;
	register struct componentname *cnp = ap->a_cnp;
I 94
D 133
	register struct vnode **vpp = ap->a_vpp;
E 133
E 94
E 89
I 5
	register struct nfsv2_sattr *sp;
I 133
	register struct nfsv3_sattr *sp3;
E 133
E 5
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
	register long t1, t2;
I 39
	register int len;
I 133
	struct nfsnode *np = (struct nfsnode *)0;
	struct vnode *newvp = (struct vnode *)0;
E 133
E 39
	caddr_t bpos, dpos, cp2;
D 65
	u_long xid;
E 65
D 39
	int error = 0;
E 39
I 39
D 100
	int error = 0, firsttry = 1;
E 100
I 100
D 133
	int error = 0, firsttry = 1, isnq;
E 133
I 133
	nfsfh_t *fhp;
	int error = 0, wccflag = NFSV3_WCCRATTR, attrflag;
	int fhsize, gotvp = 0;
E 133
E 100
E 39
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
I 114
	struct vattr vattr;
I 133
	int v3 = NFS_ISV3(dvp);
E 133
E 114
E 13

I 114
	if (error = VOP_GETATTR(dvp, &vattr, cnp->cn_cred, cnp->cn_proc)) {
		VOP_ABORTOP(dvp, cnp);
		vput(dvp);
		return (error);
	}
E 114
I 39
D 59
	len = ndp->ni_dent.d_namlen;
E 59
I 59
D 66
	len = ndp->ni_namelen;
E 66
I 66
D 84
	len = cnp->cn_namelen;
E 84
I 84
D 89
	len = ap->a_cnp->cn_namelen;
E 89
I 89
	len = cnp->cn_namelen;
I 100
D 133
	isnq = (VFSTONFS(dvp->v_mount)->nm_flag & NFSMNT_NQNFS);
E 133
E 100
E 89
E 84
E 66
E 59
E 39
	nfsstats.rpccnt[NFSPROC_MKDIR]++;
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_MKDIR], ndp->ni_cred,
E 65
I 65
D 66
	nfsm_reqhead(ndp->ni_dvp, NFSPROC_MKDIR,
E 66
I 66
D 84
	nfsm_reqhead(dvp, NFSPROC_MKDIR,
E 84
I 84
D 89
	nfsm_reqhead(ap->a_dvp, NFSPROC_MKDIR,
E 89
I 89
	nfsm_reqhead(dvp, NFSPROC_MKDIR,
E 89
E 84
E 66
E 65
D 39
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_dent.d_namlen)+NFSX_SATTR);
E 39
I 39
D 100
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(len)+NFSX_SATTR);
E 100
I 100
D 133
	  NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(len)+NFSX_SATTR(isnq));
E 100
E 39
D 66
	nfsm_fhtom(ndp->ni_dvp);
D 39
	nfsm_strtom(ndp->ni_dent.d_name, ndp->ni_dent.d_namlen, NFS_MAXNAMLEN);
E 39
I 39
D 59
	nfsm_strtom(ndp->ni_dent.d_name, len, NFS_MAXNAMLEN);
E 59
I 59
	nfsm_strtom(ndp->ni_ptr, len, NFS_MAXNAMLEN);
E 66
I 66
D 84
	nfsm_fhtom(dvp);
	nfsm_strtom(cnp->cn_nameptr, len, NFS_MAXNAMLEN);
E 84
I 84
D 89
	nfsm_fhtom(ap->a_dvp);
	nfsm_strtom(ap->a_cnp->cn_nameptr, len, NFS_MAXNAMLEN);
E 89
I 89
	nfsm_fhtom(dvp);
E 133
I 133
	  NFSX_FH(v3) + NFSX_UNSIGNED + nfsm_rndup(len) + NFSX_SATTR(v3));
	nfsm_fhtom(dvp, v3);
E 133
	nfsm_strtom(cnp->cn_nameptr, len, NFS_MAXNAMLEN);
E 89
E 84
E 66
E 59
E 39
D 5
	nfsm_build(p, u_long *, NFSX_SATTR);
	*p++ = vtonfs_mode(VDIR, vap->va_mode);
	*p++ = txdr_unsigned(ndp->ni_cred->cr_uid);
	*p++ = txdr_unsigned(ndp->ni_cred->cr_gid);
	*p++ = txdr_unsigned(VNOVAL);
	txdr_time(&(vap->va_atime), p);		/* or VNOVAL ?? */
	txdr_time(&(vap->va_mtime), p+2);	/* or VNOVAL ?? */
E 5
I 5
D 100
	nfsm_build(sp, struct nfsv2_sattr *, NFSX_SATTR);
E 100
I 100
D 133
	nfsm_build(sp, struct nfsv2_sattr *, NFSX_SATTR(isnq));
E 100
D 84
	sp->sa_mode = vtonfs_mode(VDIR, vap->va_mode);
D 66
	sp->sa_uid = txdr_unsigned(ndp->ni_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(ndp->ni_cred->cr_gid);
E 66
I 66
	sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(cnp->cn_cred->cr_gid);
E 84
I 84
D 89
	sp->sa_mode = vtonfs_mode(VDIR, ap->a_vap->va_mode);
	sp->sa_uid = txdr_unsigned(ap->a_cnp->cn_cred->cr_uid);
	sp->sa_gid = txdr_unsigned(ap->a_cnp->cn_cred->cr_gid);
E 89
I 89
	sp->sa_mode = vtonfs_mode(VDIR, vap->va_mode);
	sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
D 114
	sp->sa_gid = txdr_unsigned(cnp->cn_cred->cr_gid);
E 114
I 114
	sp->sa_gid = txdr_unsigned(vattr.va_gid);
E 114
E 89
E 84
E 66
D 100
	sp->sa_size = txdr_unsigned(VNOVAL);
D 26
	txdr_time(&vap->va_atime, &sp->sa_atime);		/* or VNOVAL ?? */
E 26
I 26
D 84
	txdr_time(&vap->va_atime, &sp->sa_atime);	/* or VNOVAL ?? */
E 26
	txdr_time(&vap->va_mtime, &sp->sa_mtime);	/* or VNOVAL ?? */
E 5
D 26
	nfsm_request(ndp->ni_dvp);
E 26
I 26
D 39
	nfsm_request(ndp->ni_dvp, nonidempotent[NFSPROC_MKDIR]);
E 39
I 39
D 42
	nfsm_request(ndp->ni_dvp, NFSPROC_MKDIR, u.u_procp);
E 42
I 42
D 56
	nfsm_request(ndp->ni_dvp, NFSPROC_MKDIR, u.u_procp, 1);
E 56
I 56
D 57
	nfsm_request(ndp->ni_dvp, NFSPROC_MKDIR, curproc, 1);
E 57
I 57
D 65
	nfsm_request(ndp->ni_dvp, NFSPROC_MKDIR, p, 1);
E 65
I 65
D 66
	nfsm_request(ndp->ni_dvp, NFSPROC_MKDIR, procp, ndp->ni_cred);
E 65
E 57
E 56
E 42
E 39
E 26
	nfsm_mtofh(ndp->ni_dvp, ndp->ni_vp);
E 66
I 66
	nfsm_request(dvp, NFSPROC_MKDIR, cnp->cn_proc, cnp->cn_cred);
	nfsm_mtofh(dvp, *vpp);
E 84
I 84
D 89
	txdr_time(&ap->a_vap->va_atime, &sp->sa_atime);	/* or VNOVAL ?? */
	txdr_time(&ap->a_vap->va_mtime, &sp->sa_mtime);	/* or VNOVAL ?? */
	nfsm_request(ap->a_dvp, NFSPROC_MKDIR, ap->a_cnp->cn_proc, ap->a_cnp->cn_cred);
	nfsm_mtofh(ap->a_dvp, *ap->a_vpp);
E 89
I 89
	txdr_time(&vap->va_atime, &sp->sa_atime);	/* or VNOVAL ?? */
	txdr_time(&vap->va_mtime, &sp->sa_mtime);	/* or VNOVAL ?? */
E 100
I 100
	if (isnq) {
		quad_t qval = -1;

		txdr_hyper(&qval, &sp->sa_nqsize);
		sp->sa_nqflags = 0;
		txdr_nqtime(&vap->va_atime, &sp->sa_nqatime);
		txdr_nqtime(&vap->va_mtime, &sp->sa_nqmtime);
E 133
I 133
	if (v3) {
		nfsm_build(sp3, struct nfsv3_sattr *, NFSX_V3SRVSATTR);
		nfsm_v3sattr(sp3, vap, cnp->cn_cred->cr_uid, vattr.va_gid);
E 133
	} else {
D 133
		sp->sa_nfssize = -1;
		txdr_nfstime(&vap->va_atime, &sp->sa_nfsatime);
		txdr_nfstime(&vap->va_mtime, &sp->sa_nfsmtime);
E 133
I 133
		nfsm_build(sp, struct nfsv2_sattr *, NFSX_V2SATTR);
		sp->sa_mode = vtonfsv2_mode(VDIR, vap->va_mode);
		sp->sa_uid = txdr_unsigned(cnp->cn_cred->cr_uid);
		sp->sa_gid = txdr_unsigned(vattr.va_gid);
		sp->sa_size = -1;
		txdr_nfsv2time(&vap->va_atime, &sp->sa_atime);
		txdr_nfsv2time(&vap->va_mtime, &sp->sa_mtime);
E 133
	}
E 100
	nfsm_request(dvp, NFSPROC_MKDIR, cnp->cn_proc, cnp->cn_cred);
D 94
	nfsm_mtofh(dvp, *ap->a_vpp);
E 94
I 94
D 133
	nfsm_mtofh(dvp, *vpp);
E 133
I 133
	if (!error)
		nfsm_mtofh(dvp, newvp, v3, gotvp);
	if (v3)
		nfsm_wcc_data(dvp, wccflag);
E 133
E 94
E 89
E 84
E 66
	nfsm_reqdone;
I 32
D 39
	VTONFS(ndp->ni_dvp)->n_direofstamp = 0;
E 32
D 3
	if (error)
		nfs_nput(ndp->ni_vp);
E 3
	nfs_nput(ndp->ni_dvp);
E 39
I 39
D 66
	VTONFS(ndp->ni_dvp)->n_flag |= NMODIFIED;
E 66
I 66
D 84
	VTONFS(dvp)->n_flag |= NMODIFIED;
E 84
I 84
D 89
	VTONFS(ap->a_dvp)->n_flag |= NMODIFIED;
E 89
I 89
	VTONFS(dvp)->n_flag |= NMODIFIED;
I 121
D 133
	VTONFS(dvp)->n_attrstamp = 0;
E 133
I 133
	if (!wccflag)
		VTONFS(dvp)->n_attrstamp = 0;
E 133
E 121
E 89
E 84
E 66
E 39
I 26
	/*
D 39
	 * Kludge: Map EEXIST => 0 assuming that you have a reply to a retry.
E 39
I 39
	 * Kludge: Map EEXIST => 0 assuming that you have a reply to a retry
	 * if we can succeed in looking up the directory.
D 133
	 * "firsttry" is necessary since the macros may "goto nfsmout" which
	 * is above the if on errors. (Ugh)
E 133
E 39
	 */
D 39
	if (error == EEXIST)
E 39
I 39
D 133
	if (error == EEXIST && firsttry) {
		firsttry = 0;
E 39
		error = 0;
I 39
		nfsstats.rpccnt[NFSPROC_LOOKUP]++;
D 66
		ndp->ni_vp = NULL;
D 65
		nfsm_reqhead(nfs_procids[NFSPROC_LOOKUP], ndp->ni_cred,
E 65
I 65
		nfsm_reqhead(ndp->ni_dvp, NFSPROC_LOOKUP,
E 66
I 66
D 84
		*vpp = NULL;
		nfsm_reqhead(dvp, NFSPROC_LOOKUP,
E 84
I 84
D 94
		*ap->a_vpp = NULL;
E 94
I 94
		*vpp = NULL;
E 94
D 89
		nfsm_reqhead(ap->a_dvp, NFSPROC_LOOKUP,
E 89
I 89
		nfsm_reqhead(dvp, NFSPROC_LOOKUP,
E 89
E 84
E 66
E 65
		    NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(len));
D 66
		nfsm_fhtom(ndp->ni_dvp);
D 59
		nfsm_strtom(ndp->ni_dent.d_name, len, NFS_MAXNAMLEN);
E 59
I 59
		nfsm_strtom(ndp->ni_ptr, len, NFS_MAXNAMLEN);
E 59
D 42
		nfsm_request(ndp->ni_dvp, NFSPROC_LOOKUP, u.u_procp);
E 42
I 42
D 56
		nfsm_request(ndp->ni_dvp, NFSPROC_LOOKUP, u.u_procp, 1);
E 56
I 56
D 57
		nfsm_request(ndp->ni_dvp, NFSPROC_LOOKUP, curproc, 1);
E 57
I 57
D 65
		nfsm_request(ndp->ni_dvp, NFSPROC_LOOKUP, p, 1);
E 65
I 65
		nfsm_request(ndp->ni_dvp, NFSPROC_LOOKUP, procp, ndp->ni_cred);
E 65
E 57
E 56
E 42
		nfsm_mtofh(ndp->ni_dvp, ndp->ni_vp);
		if (ndp->ni_vp->v_type != VDIR) {
			vput(ndp->ni_vp);
E 66
I 66
D 84
		nfsm_fhtom(dvp);
		nfsm_strtom(cnp->cn_nameptr, len, NFS_MAXNAMLEN);
		nfsm_request(dvp, NFSPROC_LOOKUP, cnp->cn_proc, cnp->cn_cred);
		nfsm_mtofh(dvp, *vpp);
		if ((*vpp)->v_type != VDIR) {
			vput(*vpp);
E 84
I 84
D 89
		nfsm_fhtom(ap->a_dvp);
		nfsm_strtom(ap->a_cnp->cn_nameptr, len, NFS_MAXNAMLEN);
		nfsm_request(ap->a_dvp, NFSPROC_LOOKUP, ap->a_cnp->cn_proc, ap->a_cnp->cn_cred);
		nfsm_mtofh(ap->a_dvp, *ap->a_vpp);
E 89
I 89
		nfsm_fhtom(dvp);
		nfsm_strtom(cnp->cn_nameptr, len, NFS_MAXNAMLEN);
		nfsm_request(dvp, NFSPROC_LOOKUP, cnp->cn_proc, cnp->cn_cred);
D 94
		nfsm_mtofh(dvp, *ap->a_vpp);
E 89
		if ((*ap->a_vpp)->v_type != VDIR) {
			vput(*ap->a_vpp);
E 94
I 94
		nfsm_mtofh(dvp, *vpp);
		if ((*vpp)->v_type != VDIR) {
			vput(*vpp);
E 94
E 84
E 66
			error = EEXIST;
E 133
I 133
	if (error == EEXIST || (!error && !gotvp)) {
		if (newvp) {
			vrele(newvp);
			newvp = (struct vnode *)0;
E 133
		}
D 133
		m_freem(mrep);
E 133
I 133
		error = nfs_lookitup(dvp, cnp->cn_nameptr, len, cnp->cn_cred,
			cnp->cn_proc, &np);
		if (!error) {
			newvp = NFSTOV(np);
			if (newvp->v_type != VDIR)
				error = EEXIST;
		}
E 133
	}
I 133
	if (error) {
		if (newvp)
			vrele(newvp);
	} else
		*ap->a_vpp = newvp;
E 133
I 59
D 66
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 59
D 65
	nfs_nput(ndp->ni_dvp);
E 65
I 65
	vrele(ndp->ni_dvp);
E 66
I 66
D 84
	FREE(cnp->cn_pnbuf, M_NAMEI);
	vrele(dvp);
E 84
I 84
D 89
	FREE(ap->a_cnp->cn_pnbuf, M_NAMEI);
	vrele(ap->a_dvp);
E 89
I 89
	FREE(cnp->cn_pnbuf, M_NAMEI);
	vrele(dvp);
E 89
E 84
E 66
E 65
E 39
E 26
	return (error);
}
I 82
D 84
#undef dvp
#undef vpp
#undef cnp
#undef vap
E 84
E 82

/*
 * nfs remove directory call
 */
D 57
nfs_rmdir(ndp)
E 57
I 57
D 65
nfs_rmdir(ndp, p)
E 65
I 65
D 66
nfs_rmdir(ndp, procp)
E 65
E 57
	register struct nameidata *ndp;
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
E 66
I 66
int
D 67
nfs_rmdir(dvp, vp, cnp)   /* converted to CN.   */
/* old: nfs_rmdir(ndp, procp) */
E 67
I 67
D 82
nfs_rmdir(dvp, vp, cnp)
E 67
	struct vnode *dvp, *vp;
	struct componentname *cnp;
E 82
I 82
D 89
nfs_rmdir (ap)
E 89
I 89
nfs_rmdir(ap)
E 89
D 94
	struct vop_rmdir_args *ap;
E 94
I 94
	struct vop_rmdir_args /* {
		struct vnode *a_dvp;
		struct vnode *a_vp;
		struct componentname *a_cnp;
	} */ *ap;
E 94
D 84
#define dvp (ap->a_dvp)
#define vp (ap->a_vp)
#define cnp (ap->a_cnp)
E 84
E 82
E 66
E 65
E 57
{
I 89
	register struct vnode *vp = ap->a_vp;
	register struct vnode *dvp = ap->a_dvp;
	register struct componentname *cnp = ap->a_cnp;
E 89
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
D 65
	register long t1, t2;
E 65
I 65
D 133
	register long t2;
E 65
	caddr_t bpos, dpos;
D 65
	u_long xid;
E 65
	int error = 0;
E 133
I 133
	register long t1, t2;
	caddr_t bpos, dpos, cp2;
	int error = 0, wccflag = NFSV3_WCCRATTR;
E 133
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
I 133
	int v3 = NFS_ISV3(dvp);
E 133
E 13

D 66
	if (ndp->ni_dvp == ndp->ni_vp) {
		vrele(ndp->ni_dvp);
D 65
		nfs_nput(ndp->ni_dvp);
E 65
I 65
		vrele(ndp->ni_dvp);
		FREE(ndp->ni_pnbuf, M_NAMEI);
E 66
I 66
D 84
	if (dvp == vp) {
		vrele(dvp);
		vrele(dvp);
		FREE(cnp->cn_pnbuf, M_NAMEI);
E 84
I 84
D 89
	if (ap->a_dvp == ap->a_vp) {
		vrele(ap->a_dvp);
		vrele(ap->a_dvp);
		FREE(ap->a_cnp->cn_pnbuf, M_NAMEI);
E 89
I 89
	if (dvp == vp) {
		vrele(dvp);
		vrele(dvp);
		FREE(cnp->cn_pnbuf, M_NAMEI);
E 89
E 84
E 66
E 65
		return (EINVAL);
	}
D 5
	if (ndp->ni_vp->v_count > 1)
		error = nfs_sillyrename(ndp, RMDIR);
	else {
		nfsstats.rpccnt[NFSPROC_RMDIR]++;
		nfsm_reqhead(nfs_procids[NFSPROC_RMDIR], ndp->ni_cred,
			NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_dent.d_namlen));
		nfsm_fhtom(ndp->ni_dvp);
		nfsm_strtom(ndp->ni_dent.d_name, ndp->ni_dent.d_namlen, NFS_MAXNAMLEN);
		nfsm_request(ndp->ni_dvp);
		nfsm_reqdone;
	}
#ifdef notyet
	cache_purge(ndp->ni_dvp);
	cache_purge(ndp->ni_vp);
#endif
	nfs_nput(ndp->ni_vp);
	nfs_nput(ndp->ni_dvp);
	return (error);
}

/*
 * nfs remove dir rpc called from above
 */
nfs_rmdirit(ndp)
	register struct nameidata *ndp;
{
	nfsm_vars;

E 5
	nfsstats.rpccnt[NFSPROC_RMDIR]++;
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_RMDIR], ndp->ni_cred,
E 65
I 65
D 66
	nfsm_reqhead(ndp->ni_dvp, NFSPROC_RMDIR,
E 65
D 59
		NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_dent.d_namlen));
E 59
I 59
		NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ndp->ni_namelen));
E 59
	nfsm_fhtom(ndp->ni_dvp);
D 59
	nfsm_strtom(ndp->ni_dent.d_name, ndp->ni_dent.d_namlen, NFS_MAXNAMLEN);
E 59
I 59
	nfsm_strtom(ndp->ni_ptr, ndp->ni_namelen, NFS_MAXNAMLEN);
E 59
D 26
	nfsm_request(ndp->ni_dvp);
E 26
I 26
D 39
	nfsm_request(ndp->ni_dvp, nonidempotent[NFSPROC_RMDIR]);
E 39
I 39
D 42
	nfsm_request(ndp->ni_dvp, NFSPROC_RMDIR, u.u_procp);
E 42
I 42
D 56
	nfsm_request(ndp->ni_dvp, NFSPROC_RMDIR, u.u_procp, 1);
E 56
I 56
D 57
	nfsm_request(ndp->ni_dvp, NFSPROC_RMDIR, curproc, 1);
E 57
I 57
D 65
	nfsm_request(ndp->ni_dvp, NFSPROC_RMDIR, p, 1);
E 65
I 65
	nfsm_request(ndp->ni_dvp, NFSPROC_RMDIR, procp, ndp->ni_cred);
E 66
I 66
D 84
	nfsm_reqhead(dvp, NFSPROC_RMDIR,
		NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen));
	nfsm_fhtom(dvp);
	nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_request(dvp, NFSPROC_RMDIR, cnp->cn_proc, cnp->cn_cred);
E 84
I 84
D 89
	nfsm_reqhead(ap->a_dvp, NFSPROC_RMDIR,
		NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(ap->a_cnp->cn_namelen));
	nfsm_fhtom(ap->a_dvp);
	nfsm_strtom(ap->a_cnp->cn_nameptr, ap->a_cnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_request(ap->a_dvp, NFSPROC_RMDIR, ap->a_cnp->cn_proc, ap->a_cnp->cn_cred);
E 89
I 89
	nfsm_reqhead(dvp, NFSPROC_RMDIR,
D 133
		NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(cnp->cn_namelen));
	nfsm_fhtom(dvp);
E 133
I 133
		NFSX_FH(v3) + NFSX_UNSIGNED + nfsm_rndup(cnp->cn_namelen));
	nfsm_fhtom(dvp, v3);
E 133
	nfsm_strtom(cnp->cn_nameptr, cnp->cn_namelen, NFS_MAXNAMLEN);
	nfsm_request(dvp, NFSPROC_RMDIR, cnp->cn_proc, cnp->cn_cred);
I 133
	if (v3)
		nfsm_wcc_data(dvp, wccflag);
E 133
E 89
E 84
E 66
E 65
E 57
E 56
E 42
E 39
E 26
	nfsm_reqdone;
I 59
D 66
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 59
I 32
D 39
	VTONFS(ndp->ni_dvp)->n_direofstamp = 0;
E 39
I 39
	VTONFS(ndp->ni_dvp)->n_flag |= NMODIFIED;
E 39
E 32
I 5
D 7
#ifndef notyet
E 7
	cache_purge(ndp->ni_dvp);
	cache_purge(ndp->ni_vp);
D 7
#endif
E 7
D 65
	nfs_nput(ndp->ni_vp);
	nfs_nput(ndp->ni_dvp);
E 65
I 65
	vrele(ndp->ni_vp);
	vrele(ndp->ni_dvp);
E 66
I 66
D 84
	FREE(cnp->cn_pnbuf, M_NAMEI);
	VTONFS(dvp)->n_flag |= NMODIFIED;
	cache_purge(dvp);
	cache_purge(vp);
	vrele(vp);
	vrele(dvp);
E 84
I 84
D 89
	FREE(ap->a_cnp->cn_pnbuf, M_NAMEI);
	VTONFS(ap->a_dvp)->n_flag |= NMODIFIED;
	cache_purge(ap->a_dvp);
	cache_purge(ap->a_vp);
	vrele(ap->a_vp);
	vrele(ap->a_dvp);
E 89
I 89
	FREE(cnp->cn_pnbuf, M_NAMEI);
	VTONFS(dvp)->n_flag |= NMODIFIED;
I 121
D 133
	VTONFS(dvp)->n_attrstamp = 0;
E 133
I 133
	if (!wccflag)
		VTONFS(dvp)->n_attrstamp = 0;
E 133
E 121
	cache_purge(dvp);
	cache_purge(vp);
	vrele(vp);
	vrele(dvp);
E 89
E 84
E 66
E 65
I 26
	/*
	 * Kludge: Map ENOENT => 0 assuming that you have a reply to a retry.
	 */
	if (error == ENOENT)
		error = 0;
E 26
E 5
	return (error);
}
I 82
D 84
#undef dvp
#undef vp
#undef cnp
E 84
E 82

/*
 * nfs readdir call
D 133
 * Although cookie is defined as opaque, I translate it to/from net byte
 * order so that it looks more sensible. This appears consistent with the
 * Ultrix implementation of NFS.
E 133
 */
I 66
int
E 66
I 35
D 39
int direof = 0;
E 39
E 35
D 15
nfs_readdir(vp, uiop, offp, cred)
E 15
I 15
D 32
nfs_readdir(vp, uiop, cred)
E 32
I 32
D 82
nfs_readdir(vp, uiop, cred, eofflagp)
E 32
E 15
D 13
	struct vnode *vp;
E 13
I 13
	register struct vnode *vp;
E 13
	struct uio *uiop;
D 15
	off_t *offp;
E 15
	struct ucred *cred;
I 32
	int *eofflagp;
E 82
I 82
D 89
nfs_readdir (ap)
E 89
I 89
nfs_readdir(ap)
E 89
D 94
	struct vop_readdir_args *ap;
E 94
I 94
	struct vop_readdir_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
I 125
D 133
		int *a_eofflag;
		u_long *a_cookies;
		int a_ncookies;
E 133
E 125
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define uiop (ap->a_uio)
#define cred (ap->a_cred)
#define eofflagp (ap->a_eofflagp)
E 84
E 82
E 32
{
I 82
D 94
	USES_VOP_GETATTR;
E 94
E 82
I 39
D 84
	register struct nfsnode *np = VTONFS(vp);
E 84
I 84
D 89
	register struct nfsnode *np = VTONFS(ap->a_vp);
E 89
I 89
	register struct vnode *vp = ap->a_vp;
	register struct nfsnode *np = VTONFS(vp);
	register struct uio *uio = ap->a_uio;
D 93
	register int *eofflagp = ap->a_eofflagp;
E 93
E 89
E 84
	int tresid, error;
	struct vattr vattr;
I 125

D 133
	/*
	 * We don't allow exporting NFS mounts, and currently local requests
	 * do not need cookies.
	 */
	if (ap->a_ncookies)
		panic("nfs_readdir: not hungry");
E 125

E 133
D 84
	if (vp->v_type != VDIR)
E 84
I 84
D 89
	if (ap->a_vp->v_type != VDIR)
E 89
I 89
	if (vp->v_type != VDIR)
E 89
E 84
		return (EPERM);
	/*
	 * First, check for hit on the EOF offset cache
	 */
D 84
	if (uiop->uio_offset != 0 && uiop->uio_offset == np->n_direofoffset &&
E 84
I 84
D 89
	if (ap->a_uio->uio_offset != 0 && ap->a_uio->uio_offset == np->n_direofoffset &&
E 89
I 89
D 133
	if (uio->uio_offset != 0 && uio->uio_offset == np->n_direofoffset &&
E 133
I 133
	if (np->n_direofoffset > 0 && uio->uio_offset >= np->n_direofoffset &&
E 133
E 89
E 84
D 65
	    (np->n_flag & NMODIFIED) == 0 &&
D 42
	    nfs_getattr(vp, &vattr, cred) == 0 &&
E 42
I 42
D 57
	    nfs_dogetattr(vp, &vattr, cred, 0) == 0 &&
E 57
I 57
	    nfs_dogetattr(vp, &vattr, cred, 0, uiop->uio_procp) == 0 &&
E 57
E 42
	    np->n_mtime == vattr.va_mtime.tv_sec) {
		*eofflagp = 1;
		nfsstats.direofcache_hits++;
		return (0);
E 65
I 65
	    (np->n_flag & NMODIFIED) == 0) {
D 84
		if (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS) {
			if (NQNFS_CKCACHABLE(vp, NQL_READ)) {
				*eofflagp = 1;
E 84
I 84
D 89
		if (VFSTONFS(ap->a_vp->v_mount)->nm_flag & NFSMNT_NQNFS) {
			if (NQNFS_CKCACHABLE(ap->a_vp, NQL_READ)) {
				*ap->a_eofflagp = 1;
E 89
I 89
		if (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS) {
D 133
			if (NQNFS_CKCACHABLE(vp, NQL_READ)) {
E 133
I 133
			if (NQNFS_CKCACHABLE(vp, ND_READ)) {
E 133
D 93
				*eofflagp = 1;
E 93
E 89
E 84
				nfsstats.direofcache_hits++;
				return (0);
			}
D 82
		} else if (nfs_getattr(vp, &vattr, cred, uiop->uio_procp) == 0 &&
E 82
I 82
D 84
		} else if (VOP_GETATTR(vp, &vattr, cred, uiop->uio_procp) == 0 &&
E 84
I 84
D 89
		} else if (VOP_GETATTR(ap->a_vp, &vattr, ap->a_cred, ap->a_uio->uio_procp) == 0 &&
E 89
I 89
		} else if (VOP_GETATTR(vp, &vattr, ap->a_cred, uio->uio_procp) == 0 &&
E 89
E 84
E 82
D 92
			np->n_mtime == vattr.va_mtime.tv_sec) {
E 92
I 92
			np->n_mtime == vattr.va_mtime.ts_sec) {
E 92
D 84
			*eofflagp = 1;
E 84
I 84
D 89
			*ap->a_eofflagp = 1;
E 89
I 89
D 93
			*eofflagp = 1;
E 93
E 89
E 84
			nfsstats.direofcache_hits++;
			return (0);
		}
E 65
	}

	/*
	 * Call nfs_bioread() to do the real work.
	 */
D 84
	tresid = uiop->uio_resid;
	error = nfs_bioread(vp, uiop, 0, cred);
E 84
I 84
D 89
	tresid = ap->a_uio->uio_resid;
	error = nfs_bioread(ap->a_vp, ap->a_uio, 0, ap->a_cred);
E 89
I 89
	tresid = uio->uio_resid;
	error = nfs_bioread(vp, uio, 0, ap->a_cred);
E 89
E 84

D 84
	if (!error && uiop->uio_resid == tresid) {
		*eofflagp = 1;
E 84
I 84
D 89
	if (!error && ap->a_uio->uio_resid == tresid) {
		*ap->a_eofflagp = 1;
E 89
I 89
D 93
	if (!error && uio->uio_resid == tresid) {
		*eofflagp = 1;
E 93
I 93
	if (!error && uio->uio_resid == tresid)
E 93
E 89
E 84
		nfsstats.direofcache_misses++;
D 93
	} else
D 84
		*eofflagp = 0;
E 84
I 84
D 89
		*ap->a_eofflagp = 0;
E 89
I 89
		*eofflagp = 0;
E 93
E 89
E 84
	return (error);
}
I 82
D 84
#undef vp
#undef uiop
#undef cred
#undef eofflagp
E 84
E 82

/*
 * Readdir rpc call.
 * Called from below the buffer cache by nfs_doio().
 */
I 66
int
E 66
D 57
nfs_readdirrpc(vp, uiop, cred, procp)
E 57
I 57
nfs_readdirrpc(vp, uiop, cred)
E 57
D 133
	register struct vnode *vp;
	struct uio *uiop;
E 133
I 133
	struct vnode *vp;
	register struct uio *uiop;
E 133
	struct ucred *cred;
D 57
	struct proc *procp;
E 57
{
E 39
D 133
	register long len;
E 133
I 133
	register int len, left;
E 133
D 68
	register struct direct *dp;
E 68
I 68
D 95
	register struct readdir *dp;
E 95
I 95
	register struct dirent *dp;
E 95
E 68
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
D 133
	register long t1;
I 27
D 39
	long tlen;
E 39
I 39
	long tlen, lastlen;
E 133
I 133
	register long t1, t2;
	register nfsuint64 *cookiep;
E 133
E 39
E 27
	caddr_t bpos, dpos, cp2;
D 65
	u_long xid;
E 65
D 133
	int error = 0;
E 133
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
E 13
D 133
	struct mbuf *md2;
	caddr_t dpos2;
	int siz;
D 14
	int more_dirs, eofflg;
E 14
I 14
D 32
	int more_dirs;
E 32
I 32
	int more_dirs = 1;
E 32
E 14
D 100
	off_t off, savoff;
E 100
I 100
	u_long off, savoff;
E 100
D 68
	struct direct *savdp;
E 68
I 68
D 95
	struct readdir *savdp;
E 95
I 95
	struct dirent *savdp;
E 95
E 68
I 32
	struct nfsmount *nmp;
	struct nfsnode *np = VTONFS(vp);
	long tresid;
E 133
I 133
	nfsuint64 cookie;
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
	struct nfsnode *dnp = VTONFS(vp);
	nfsfh_t *fhp;
	u_quad_t frev, fileno;
	int error = 0, tlen, more_dirs = 1, blksiz = 0, bigenough = 1, i;
	int cachable, attrflag, fhsize;
	int v3 = NFS_ISV3(vp);
E 133
E 32

D 15
	nfs_lock(vp);
E 15
D 32
	nfsstats.rpccnt[NFSPROC_READDIR]++;
	nfsm_reqhead(nfs_procids[NFSPROC_READDIR], cred, xid);
	nfsm_fhtom(vp);
	nfsm_build(p, u_long *, 2*NFSX_UNSIGNED);
D 15
	off = *offp;
	*p++ = txdr_unsigned(off);
E 15
I 15
	*p++ = txdr_unsigned(uiop->uio_offset);
E 15
	*p = txdr_unsigned(uiop->uio_resid);
D 26
	nfsm_request(vp);
E 26
I 26
	nfsm_request(vp, nonidempotent[NFSPROC_READDIR]);
E 26
	siz = 0;
	nfsm_disect(p, u_long *, NFSX_UNSIGNED);
	more_dirs = fxdr_unsigned(int, *p);
E 32
I 32
D 39
	/*
	 * First, check for hit on the EOF offset cache
	 */
I 35
	if (direof)
E 35
	if (uiop->uio_offset != 0 && uiop->uio_offset == np->n_direofoffset &&
	    (time.tv_sec - np->n_direofstamp) < NFS_ATTRTIMEO) {
		*eofflagp = 1;
		nfsstats.direofcache_hits++;
		return (0);
	}
E 32

E 39
D 32
	/* Save the position so that we can do nfsm_mtouio() later */
	dpos2 = dpos;
	md2 = md;
E 32
I 32
D 37
	nmp = vfs_to_nfs(vp->v_mount);
E 37
I 37
D 133
	nmp = VFSTONFS(vp->v_mount);
E 37
	tresid = uiop->uio_resid;
E 133
I 133
#ifndef nolint
	dp = (struct dirent *)0;
#endif
#ifndef DIAGNOSTIC
	if (uiop->uio_iovcnt != 1 || (uiop->uio_offset & (NFS_DIRBLKSIZ - 1)) ||
		(uiop->uio_resid & (NFS_DIRBLKSIZ - 1)))
		panic("nfs readdirrpc bad uio");
#endif

E 133
	/*
D 133
	 * Loop around doing readdir rpc's of size uio_resid or nm_rsize,
D 57
	 * whichever is smaller, truncated to a multiple of DIRBLKSIZ.
E 57
I 57
	 * whichever is smaller, truncated to a multiple of NFS_DIRBLKSIZ.
E 133
I 133
	 * If there is no cookie, assume end of directory.
	 */
	cookiep = nfs_getcookie(dnp, uiop->uio_offset, 0);
	if (cookiep)
		cookie = *cookiep;
	else
		return (0);
	/*
	 * Loop around doing readdir rpc's of size nm_readdirsize
	 * truncated to a multiple of DIRBLKSIZ.
E 133
E 57
D 39
	 * The stopping criteria is EOF or less than DIRBLKSIZ of the
	 * request left.
E 39
I 39
	 * The stopping criteria is EOF or buffer full.
E 39
	 */
D 57
	while (more_dirs && uiop->uio_resid >= DIRBLKSIZ) {
E 57
I 57
D 133
	while (more_dirs && uiop->uio_resid >= NFS_DIRBLKSIZ) {
E 133
I 133
	while (more_dirs && bigenough) {
E 133
E 57
		nfsstats.rpccnt[NFSPROC_READDIR]++;
D 65
		nfsm_reqhead(nfs_procids[NFSPROC_READDIR], cred, xid);
E 65
I 65
D 133
		nfsm_reqhead(vp, NFSPROC_READDIR,
D 100
			NFSX_FH+2*NFSX_UNSIGNED);
E 100
I 100
			NFSX_FH + 2 * NFSX_UNSIGNED);
E 100
E 65
		nfsm_fhtom(vp);
D 57
		nfsm_build(p, u_long *, 2*NFSX_UNSIGNED);
		*p++ = txdr_unsigned(uiop->uio_offset);
		*p = txdr_unsigned(((uiop->uio_resid > nmp->nm_rsize) ?
			nmp->nm_rsize : uiop->uio_resid) & ~(DIRBLKSIZ-1));
D 39
		nfsm_request(vp, nonidempotent[NFSPROC_READDIR]);
E 39
I 39
D 42
		nfsm_request(vp, NFSPROC_READDIR, procp);
E 42
I 42
		nfsm_request(vp, NFSPROC_READDIR, procp, 0);
E 57
I 57
D 100
		nfsm_build(tl, u_long *, 2*NFSX_UNSIGNED);
		*tl++ = txdr_unsigned(uiop->uio_offset);
E 100
I 100
		nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
		off = (u_long)uiop->uio_offset;
		*tl++ = txdr_unsigned(off);
E 100
		*tl = txdr_unsigned(((uiop->uio_resid > nmp->nm_rsize) ?
			nmp->nm_rsize : uiop->uio_resid) & ~(NFS_DIRBLKSIZ-1));
E 133
I 133
		nfsm_reqhead(vp, NFSPROC_READDIR, NFSX_FH(v3) +
			NFSX_READDIR(v3));
		nfsm_fhtom(vp, v3);
		if (v3) {
			nfsm_build(tl, u_long *, 5 * NFSX_UNSIGNED);
			*tl++ = cookie.nfsuquad[0];
			*tl++ = cookie.nfsuquad[1];
			*tl++ = dnp->n_cookieverf.nfsuquad[0];
			*tl++ = dnp->n_cookieverf.nfsuquad[1];
		} else {
			nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
			*tl++ = cookie.nfsuquad[0];
		}
		*tl = txdr_unsigned(nmp->nm_readdirsize);
E 133
D 65
		nfsm_request(vp, NFSPROC_READDIR, uiop->uio_procp, 0);
E 65
I 65
		nfsm_request(vp, NFSPROC_READDIR, uiop->uio_procp, cred);
E 65
E 57
E 42
E 39
D 133
		siz = 0;
E 133
I 133
		if (v3) {
			nfsm_postop_attr(vp, attrflag);
			if (!error) {
				nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
				dnp->n_cookieverf.nfsuquad[0] = *tl++;
				dnp->n_cookieverf.nfsuquad[1] = *tl;
			} else {
				m_freem(mrep);
				goto nfsmout;
			}
		}
E 133
D 57
		nfsm_disect(p, u_long *, NFSX_UNSIGNED);
		more_dirs = fxdr_unsigned(int, *p);
E 57
I 57
D 65
		nfsm_disect(tl, u_long *, NFSX_UNSIGNED);
E 65
I 65
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
E 65
		more_dirs = fxdr_unsigned(int, *tl);
E 57
	
D 133
		/* Save the position so that we can do nfsm_mtouio() later */
		dpos2 = dpos;
		md2 = md;
	
E 133
		/* loop thru the dir entries, doctoring them to 4bsd form */
D 39
		savoff = off = 0;
		savdp = dp = NULL;
E 39
I 39
D 100
		off = uiop->uio_offset;
E 100
I 40
D 133
#ifdef lint
D 68
		dp = (struct direct *)0;
E 68
I 68
D 95
		dp = (struct readdir *)0;
E 95
I 95
		dp = (struct dirent *)0;
E 95
E 68
#endif /* lint */
E 40
E 39
		while (more_dirs && siz < uiop->uio_resid) {
			savoff = off;		/* Hold onto offset and dp */
			savdp = dp;
D 57
			nfsm_disecton(p, u_long *, 2*NFSX_UNSIGNED);
			dp = (struct direct *)p;
			dp->d_ino = fxdr_unsigned(u_long, *p++);
			len = fxdr_unsigned(int, *p);
E 57
I 57
D 65
			nfsm_disecton(tl, u_long *, 2*NFSX_UNSIGNED);
E 65
I 65
D 100
			nfsm_dissecton(tl, u_long *, 2*NFSX_UNSIGNED);
E 100
I 100
D 119
			nfsm_dissecton(tl, u_long *, 2 * NFSX_UNSIGNED);
E 119
I 119
			nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
E 119
E 100
E 65
D 68
			dp = (struct direct *)tl;
E 68
I 68
D 95
			dp = (struct readdir *)tl;
E 68
			dp->d_ino = fxdr_unsigned(u_long, *tl++);
E 95
I 95
			dp = (struct dirent *)tl;
			dp->d_fileno = fxdr_unsigned(u_long, *tl++);
E 95
			len = fxdr_unsigned(int, *tl);
E 133
I 133
		while (more_dirs && bigenough) {
			if (v3) {
				nfsm_dissect(tl, u_long *, 3 * NFSX_UNSIGNED);
				fxdr_hyper(tl, &fileno);
				len = fxdr_unsigned(int, *(tl + 2));
			} else {
				nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
				fileno = fxdr_unsigned(u_quad_t, *tl++);
				len = fxdr_unsigned(int, *tl);
			}
E 133
E 57
			if (len <= 0 || len > NFS_MAXNAMLEN) {
				error = EBADRPC;
				m_freem(mrep);
				goto nfsmout;
			}
D 96
			dp->d_namlen = (u_short)len;
E 96
I 96
D 133
			dp->d_namlen = (u_char)len;
			dp->d_type = DT_UNKNOWN;
E 96
			nfsm_adv(len);		/* Point past name */
E 133
			tlen = nfsm_rndup(len);
D 133
			/*
			 * This should not be necessary, but some servers have
			 * broken XDR such that these bytes are not null filled.
			 */
			if (tlen != len) {
				*dpos = '\0';	/* Null-terminate */
				nfsm_adv(tlen - len);
				len = tlen;
E 133
I 133
			if (tlen == len)
				tlen += 4;	/* To ensure null termination */
			left = DIRBLKSIZ - blksiz;
			if ((tlen + DIRHDSIZ) > left) {
				dp->d_reclen += left;
				uiop->uio_iov->iov_base += left;
				uiop->uio_iov->iov_len -= left;
				uiop->uio_offset += left;
				uiop->uio_resid -= left;
				blksiz = 0;
E 133
			}
D 57
			nfsm_disecton(p, u_long *, 2*NFSX_UNSIGNED);
			off = fxdr_unsigned(off_t, *p);
			*p++ = 0;	/* Ensures null termination of name */
			more_dirs = fxdr_unsigned(int, *p);
E 57
I 57
D 65
			nfsm_disecton(tl, u_long *, 2*NFSX_UNSIGNED);
E 65
I 65
D 100
			nfsm_dissecton(tl, u_long *, 2*NFSX_UNSIGNED);
E 100
I 100
D 119
			nfsm_dissecton(tl, u_long *, 2 * NFSX_UNSIGNED);
E 119
I 119
D 133
			nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
E 119
E 100
E 65
D 96
			off = fxdr_unsigned(off_t, *tl);
E 96
I 96
			off = fxdr_unsigned(u_long, *tl);
E 96
			*tl++ = 0;	/* Ensures null termination of name */
E 133
I 133
			if ((tlen + DIRHDSIZ) > uiop->uio_resid)
				bigenough = 0;
			if (bigenough) {
				dp = (struct dirent *)uiop->uio_iov->iov_base;
				dp->d_fileno = (int)fileno;
				dp->d_namlen = len;
				dp->d_reclen = tlen + DIRHDSIZ;
				dp->d_type = DT_UNKNOWN;
				blksiz += dp->d_reclen;
				if (blksiz == DIRBLKSIZ)
					blksiz = 0;
				uiop->uio_offset += DIRHDSIZ;
				uiop->uio_resid -= DIRHDSIZ;
				uiop->uio_iov->iov_base += DIRHDSIZ;
				uiop->uio_iov->iov_len -= DIRHDSIZ;
				nfsm_mtouio(uiop, len);
				cp = uiop->uio_iov->iov_base;
				tlen -= len;
				*cp = '\0';	/* null terminate */
				uiop->uio_iov->iov_base += tlen;
				uiop->uio_iov->iov_len -= tlen;
				uiop->uio_offset += tlen;
				uiop->uio_resid -= tlen;
			} else
				nfsm_adv(nfsm_rndup(len));
			if (v3) {
				nfsm_dissect(tl, u_long *, 3 * NFSX_UNSIGNED);
			} else {
				nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
			}
			if (bigenough) {
				cookie.nfsuquad[0] = *tl++;
				if (v3)
					cookie.nfsuquad[1] = *tl++;
			} else if (v3)
				tl += 2;
			else
				tl++;
E 133
			more_dirs = fxdr_unsigned(int, *tl);
E 57
D 100
			dp->d_reclen = len+4*NFSX_UNSIGNED;
E 100
I 100
D 133
			dp->d_reclen = len + 4 * NFSX_UNSIGNED;
E 100
			siz += dp->d_reclen;
E 133
		}
		/*
		 * If at end of rpc data, get the eof boolean
		 */
		if (!more_dirs) {
D 57
			nfsm_disecton(p, u_long *, NFSX_UNSIGNED);
			more_dirs = (fxdr_unsigned(int, *p) == 0);
E 57
I 57
D 65
			nfsm_disecton(tl, u_long *, NFSX_UNSIGNED);
E 65
I 65
D 119
			nfsm_dissecton(tl, u_long *, NFSX_UNSIGNED);
E 119
I 119
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
E 119
E 65
			more_dirs = (fxdr_unsigned(int, *tl) == 0);
E 57
E 32
D 133

D 32
	/* loop thru the dir entries, doctoring them to 4bsd form */
I 13
	savoff = off = 0;
	savdp = dp = NULL;
E 13
	while (more_dirs && siz < uiop->uio_resid) {
		savoff = off;		/* Hold onto offset and dp */
		savdp = dp;
		nfsm_disecton(p, u_long *, 2*NFSX_UNSIGNED);
		dp = (struct direct *)p;
		dp->d_ino = fxdr_unsigned(u_long, *p++);
		len = fxdr_unsigned(int, *p);
		if (len <= 0 || len > NFS_MAXNAMLEN) {
			error = EBADRPC;
			m_freem(mrep);
			goto nfsmout;
E 32
I 32
			/*
			 * If at EOF, cache directory offset
			 */
D 39
			if (!more_dirs) {
E 39
I 39
			if (!more_dirs)
E 39
				np->n_direofoffset = off;
E 133
D 39
				np->n_direofstamp = time.tv_sec;
			}
E 39
E 32
		}
D 32
		dp->d_namlen = (u_short)len;
D 27
		len = nfsm_rndup(len);
		nfsm_adv(len);
E 27
I 27
		nfsm_adv(len);		/* Point past name */
		tlen = nfsm_rndup(len);
		if (tlen != len) {	/* If name not on rounded boundary */
			*dpos = '\0';	/* Null-terminate */
			nfsm_adv(tlen - len);
			len = tlen;
E 32
I 32
D 133
		/*
		 * If there is too much to fit in the data buffer, use savoff and
		 * savdp to trim off the last record.
		 * --> we are not at eof
		 */
		if (siz > uiop->uio_resid) {
			off = savoff;
			siz -= dp->d_reclen;
			dp = savdp;
			more_dirs = 0;	/* Paranoia */
E 32
		}
E 27
D 32
		nfsm_disecton(p, u_long *, 2*NFSX_UNSIGNED);
		off = fxdr_unsigned(off_t, *p);
		*p++ = 0;		/* Ensures null termination of name */
		more_dirs = fxdr_unsigned(int, *p);
		dp->d_reclen = len+4*NFSX_UNSIGNED;
		siz += dp->d_reclen;
E 32
I 32
		if (siz > 0) {
I 39
			lastlen = dp->d_reclen;
E 39
			md = md2;
			dpos = dpos2;
			nfsm_mtouio(uiop, siz);
D 100
			uiop->uio_offset = off;
E 100
I 100
			uiop->uio_offset = (off_t)off;
E 100
		} else
			more_dirs = 0;	/* Ugh, never happens, but in case.. */
E 133
		m_freem(mrep);
E 32
	}
D 32
	/*
	 * If at end of rpc data, get the eof boolean
	 */
D 14
	if (!more_dirs) {
E 14
I 14
	if (!more_dirs)
E 14
		nfsm_disecton(p, u_long *, NFSX_UNSIGNED);
D 14
		eofflg = fxdr_unsigned(long, *p);
	}
E 14
	/*
	 * If there is too much to fit in the data buffer, use savoff and
	 * savdp to trim off the last record.
	 * --> we are not at eof
	 */
	if (siz > uiop->uio_resid) {
D 14
		eofflg = FALSE;
E 14
		off = savoff;
		siz -= dp->d_reclen;
		dp = savdp;
E 32
I 32
D 39
nfsmout:
	if (tresid == uiop->uio_resid) {
		*eofflagp = 1;
		nfsstats.direofcache_misses++;
	} else {
		*eofflagp = 0;
E 39
I 39
	/*
D 57
	 * Fill last record, iff any, out to a multiple of DIRBLKSIZ
E 57
I 57
D 133
	 * Fill last record, iff any, out to a multiple of NFS_DIRBLKSIZ
E 133
I 133
	 * Fill last record, iff any, out to a multiple of DIRBLKSIZ
E 133
E 57
	 * by increasing d_reclen for the last record.
	 */
D 133
	if (uiop->uio_resid < tresid) {
D 57
		len = uiop->uio_resid & (DIRBLKSIZ - 1);
E 57
I 57
		len = uiop->uio_resid & (NFS_DIRBLKSIZ - 1);
E 57
		if (len > 0) {
D 68
			dp = (struct direct *)
E 68
I 68
D 95
			dp = (struct readdir *)
E 95
I 95
			dp = (struct dirent *)
E 95
E 68
				(uiop->uio_iov->iov_base - lastlen);
			dp->d_reclen += len;
			uiop->uio_iov->iov_base += len;
			uiop->uio_iov->iov_len -= len;
			uiop->uio_resid -= len;
		}
E 133
I 133
	if (blksiz > 0) {
		left = DIRBLKSIZ - blksiz;
		dp->d_reclen += left;
		uiop->uio_iov->iov_base += left;
		uiop->uio_iov->iov_len -= left;
		uiop->uio_offset += left;
		uiop->uio_resid -= left;
E 133
E 39
E 32
	}
I 133

	/*
	 * We are now either at the end of the directory or have filled the
	 * block.
	 */
	if (bigenough)
		dnp->n_direofoffset = uiop->uio_offset;
	else {
		if (uiop->uio_resid > 0)
			printf("EEK! readdirrpc resid > 0\n");
		cookiep = nfs_getcookie(dnp, uiop->uio_offset, 1);
		*cookiep = cookie;
	}
E 133
I 39
nfsmout:
E 39
D 32
	if (siz > 0) {
D 14
#ifdef notdef
		if (!eofflg)
			dp->d_reclen += (uiop->uio_resid-siz);
#endif
E 14
		md = md2;
		dpos = dpos2;
		nfsm_mtouio(uiop, siz);
D 14
#ifdef notdef
		if (!eofflg)
			uiop->uio_resid = 0;
#endif
E 14
D 15
		*offp = off;
E 15
I 15
		uiop->uio_offset = off;
E 15
	}
	nfsm_reqdone;
E 32
D 15
	nfs_unlock(vp);
E 15
	return (error);
}

I 65
/*
D 100
 * Nqnfs readdir_and_lookup RPC. Used in place of nfs_readdirrpc() when
 * the "rdirlook" mount option is specified.
E 100
I 100
D 133
 * Nqnfs readdir_and_lookup RPC. Used in place of nfs_readdirrpc().
E 133
I 133
 * NFS V3 readdir plus RPC. Used in place of nfs_readdirrpc().
E 133
E 100
 */
I 66
int
E 66
D 133
nfs_readdirlookrpc(vp, uiop, cred)
E 133
I 133
nfs_readdirplusrpc(vp, uiop, cred)
E 133
	struct vnode *vp;
	register struct uio *uiop;
	struct ucred *cred;
{
D 133
	register int len;
E 133
I 133
	register int len, left;
E 133
D 68
	register struct direct *dp;
E 68
I 68
D 95
	register struct readdir *dp;
E 95
I 95
	register struct dirent *dp;
E 95
E 68
	register u_long *tl;
	register caddr_t cp;
D 133
	register long t1;
	caddr_t bpos, dpos, cp2;
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
E 133
I 133
	register long t1, t2;
	register struct vnode *newvp;
	register nfsuint64 *cookiep;
	caddr_t bpos, dpos, cp2, dpossav1, dpossav2;
	struct mbuf *mreq, *mrep, *md, *mb, *mb2, *mdsav1, *mdsav2;
E 133
	struct nameidata nami, *ndp = &nami;
I 67
	struct componentname *cnp = &ndp->ni_cnd;
E 67
D 100
	off_t off, endoff;
E 100
I 100
D 133
	u_long off, endoff, fileno;
E 100
	time_t reqtime, ltime;
	struct nfsmount *nmp;
D 123
	struct nfsnode *np, *tp;
E 123
I 123
	struct nfsnode *np;
E 123
	struct vnode *newvp;
	nfsv2fh_t *fhp;
D 100
	u_long fileno;
E 100
	u_quad_t frev;
	int error = 0, tlen, more_dirs = 1, tresid, doit, bigenough, i;
	int cachable;
E 133
I 133
	nfsuint64 cookie;
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
	struct nfsnode *dnp = VTONFS(vp), *np;
	nfsfh_t *fhp;
	u_quad_t frev, fileno;
	int error = 0, tlen, more_dirs = 1, blksiz = 0, doit, bigenough = 1, i;
	int cachable, attrflag, fhsize;
E 133

D 133
	if (uiop->uio_iovcnt != 1)
		panic("nfs rdirlook");
	nmp = VFSTONFS(vp->v_mount);
	tresid = uiop->uio_resid;
E 133
I 133
#ifndef nolint
	dp = (struct dirent *)0;
#endif
#ifndef DIAGNOSTIC
	if (uiop->uio_iovcnt != 1 || (uiop->uio_offset & (DIRBLKSIZ - 1)) ||
		(uiop->uio_resid & (DIRBLKSIZ - 1)))
		panic("nfs readdirplusrpc bad uio");
#endif
E 133
	ndp->ni_dvp = vp;
	newvp = NULLVP;
I 133

E 133
	/*
D 133
	 * Loop around doing readdir rpc's of size uio_resid or nm_rsize,
	 * whichever is smaller, truncated to a multiple of NFS_DIRBLKSIZ.
E 133
I 133
	 * If there is no cookie, assume end of directory.
	 */
	cookiep = nfs_getcookie(dnp, uiop->uio_offset, 0);
	if (cookiep)
		cookie = *cookiep;
	else
		return (0);
	/*
	 * Loop around doing readdir rpc's of size nm_readdirsize
	 * truncated to a multiple of DIRBLKSIZ.
E 133
	 * The stopping criteria is EOF or buffer full.
	 */
D 133
	while (more_dirs && uiop->uio_resid >= NFS_DIRBLKSIZ) {
		nfsstats.rpccnt[NQNFSPROC_READDIRLOOK]++;
		nfsm_reqhead(vp, NQNFSPROC_READDIRLOOK,
D 100
			NFSX_FH+3*NFSX_UNSIGNED);
E 100
I 100
			NFSX_FH + 3 * NFSX_UNSIGNED);
E 100
		nfsm_fhtom(vp);
D 100
		nfsm_build(tl, u_long *, 3*NFSX_UNSIGNED);
		*tl++ = txdr_unsigned(uiop->uio_offset);
E 100
I 100
 		nfsm_build(tl, u_long *, 3 * NFSX_UNSIGNED);
		off = (u_long)uiop->uio_offset;
		*tl++ = txdr_unsigned(off);
E 100
		*tl++ = txdr_unsigned(((uiop->uio_resid > nmp->nm_rsize) ?
			nmp->nm_rsize : uiop->uio_resid) & ~(NFS_DIRBLKSIZ-1));
D 100
		*tl = txdr_unsigned(nmp->nm_leaseterm);
E 100
I 100
		if (nmp->nm_flag & NFSMNT_NQLOOKLEASE)
			*tl = txdr_unsigned(nmp->nm_leaseterm);
		else
			*tl = 0;
E 100
		reqtime = time.tv_sec;
		nfsm_request(vp, NQNFSPROC_READDIRLOOK, uiop->uio_procp, cred);
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
E 133
I 133
	while (more_dirs && bigenough) {
		nfsstats.rpccnt[NFSPROC_READDIRPLUS]++;
		nfsm_reqhead(vp, NFSPROC_READDIRPLUS,
			NFSX_FH(1) + 6 * NFSX_UNSIGNED);
		nfsm_fhtom(vp, 1);
 		nfsm_build(tl, u_long *, 6 * NFSX_UNSIGNED);
		*tl++ = cookie.nfsuquad[0];
		*tl++ = cookie.nfsuquad[1];
		*tl++ = dnp->n_cookieverf.nfsuquad[0];
		*tl++ = dnp->n_cookieverf.nfsuquad[1];
		*tl++ = txdr_unsigned(nmp->nm_readdirsize);
		*tl = txdr_unsigned(nmp->nm_rsize);
		nfsm_request(vp, NFSPROC_READDIRPLUS, uiop->uio_procp, cred);
		nfsm_postop_attr(vp, attrflag);
		if (error) {
			m_freem(mrep);
			goto nfsmout;
		}
		nfsm_dissect(tl, u_long *, 3 * NFSX_UNSIGNED);
		dnp->n_cookieverf.nfsuquad[0] = *tl++;
		dnp->n_cookieverf.nfsuquad[1] = *tl++;
E 133
		more_dirs = fxdr_unsigned(int, *tl);
	
		/* loop thru the dir entries, doctoring them to 4bsd form */
D 100
		off = uiop->uio_offset;
E 100
D 133
		bigenough = 1;
E 133
		while (more_dirs && bigenough) {
D 133
			doit = 1;
D 100
			nfsm_dissect(tl, u_long *, 4*NFSX_UNSIGNED);
			cachable = fxdr_unsigned(int, *tl++);
			ltime = reqtime + fxdr_unsigned(int, *tl++);
			fxdr_hyper(tl, &frev);
E 100
I 100
			nfsm_dissect(tl, u_long *, 4 * NFSX_UNSIGNED);
			if (nmp->nm_flag & NFSMNT_NQLOOKLEASE) {
				cachable = fxdr_unsigned(int, *tl++);
				ltime = reqtime + fxdr_unsigned(int, *tl++);
				fxdr_hyper(tl, &frev);
			}
E 100
			nfsm_dissect(fhp, nfsv2fh_t *, NFSX_FH);
			if (!bcmp(VTONFS(vp)->n_fh.fh_bytes, (caddr_t)fhp, NFSX_FH)) {
				VREF(vp);
				newvp = vp;
				np = VTONFS(vp);
			} else {
				if (error = nfs_nget(vp->v_mount, fhp, &np))
					doit = 0;
				newvp = NFSTOV(np);
			}
			if (error = nfs_loadattrcache(&newvp, &md, &dpos,
				(struct vattr *)0))
				doit = 0;
D 100
			nfsm_dissect(tl, u_long *, 2*NFSX_UNSIGNED);
E 100
I 100
			nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
E 100
			fileno = fxdr_unsigned(u_long, *tl++);
			len = fxdr_unsigned(int, *tl);
E 133
I 133
			nfsm_dissect(tl, u_long *, 3 * NFSX_UNSIGNED);
			fxdr_hyper(tl, &fileno);
			len = fxdr_unsigned(int, *(tl + 2));
E 133
			if (len <= 0 || len > NFS_MAXNAMLEN) {
				error = EBADRPC;
				m_freem(mrep);
				goto nfsmout;
			}
D 133
			tlen = (len + 4) & ~0x3;
E 133
I 133
			tlen = nfsm_rndup(len);
			if (tlen == len)
				tlen += 4;	/* To ensure null termination*/
			left = DIRBLKSIZ - blksiz;
			if ((tlen + DIRHDSIZ) > left) {
				dp->d_reclen += left;
				uiop->uio_iov->iov_base += left;
				uiop->uio_iov->iov_len -= left;
				uiop->uio_offset += left;
				uiop->uio_resid -= left;
				blksiz = 0;
			}
E 133
			if ((tlen + DIRHDSIZ) > uiop->uio_resid)
				bigenough = 0;
D 133
			if (bigenough && doit) {
E 133
I 133
			if (bigenough) {
E 133
D 68
				dp = (struct direct *)uiop->uio_iov->iov_base;
E 68
I 68
D 95
				dp = (struct readdir *)uiop->uio_iov->iov_base;
E 68
				dp->d_ino = fileno;
E 95
I 95
				dp = (struct dirent *)uiop->uio_iov->iov_base;
D 133
				dp->d_fileno = fileno;
E 133
I 133
				dp->d_fileno = (int)fileno;
E 133
E 95
				dp->d_namlen = len;
				dp->d_reclen = tlen + DIRHDSIZ;
I 96
D 133
				dp->d_type =
				    IFTODT(VTTOIF(np->n_vattr.va_type));
E 133
I 133
				dp->d_type = DT_UNKNOWN;
				blksiz += dp->d_reclen;
				if (blksiz == DIRBLKSIZ)
					blksiz = 0;
				uiop->uio_offset += DIRHDSIZ;
E 133
E 96
				uiop->uio_resid -= DIRHDSIZ;
				uiop->uio_iov->iov_base += DIRHDSIZ;
				uiop->uio_iov->iov_len -= DIRHDSIZ;
D 67
				ndp->ni_ptr = uiop->uio_iov->iov_base;
				ndp->ni_namelen = len;
E 67
I 67
				cnp->cn_nameptr = uiop->uio_iov->iov_base;
				cnp->cn_namelen = len;
E 67
D 133
				ndp->ni_vp = newvp;
E 133
				nfsm_mtouio(uiop, len);
				cp = uiop->uio_iov->iov_base;
				tlen -= len;
D 133
				for (i = 0; i < tlen; i++)
					*cp++ = '\0';
E 133
I 133
				*cp = '\0';
E 133
				uiop->uio_iov->iov_base += tlen;
				uiop->uio_iov->iov_len -= tlen;
I 133
				uiop->uio_offset += tlen;
E 133
				uiop->uio_resid -= tlen;
I 133
			} else
				nfsm_adv(nfsm_rndup(len));
			nfsm_dissect(tl, u_long *, 3 * NFSX_UNSIGNED);
			if (bigenough) {
				cookie.nfsuquad[0] = *tl++;
				cookie.nfsuquad[1] = *tl++;
			} else
				tl += 2;

			/*
			 * Since the attributes are before the file handle
			 * (sigh), we must skip over the attributes and then
			 * come back and get them.
			 */
			attrflag = fxdr_unsigned(int, *tl);
			if (attrflag) {
			    dpossav1 = dpos;
			    mdsav1 = md;
			    nfsm_adv(NFSX_V3FATTR);
			    nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
			    doit = fxdr_unsigned(int, *tl);
			    if (doit) {
				nfsm_getfh(fhp, fhsize, 1);
				if (NFS_CMPFH(dnp, fhp, fhsize)) {
				    VREF(vp);
				    newvp = vp;
				    np = dnp;
				} else {
				    if (error = nfs_nget(vp->v_mount, fhp,
					fhsize, &np))
					doit = 0;
				    else
					newvp = NFSTOV(np);
				}
			    }
			    if (doit) {
				dpossav2 = dpos;
				dpos = dpossav1;
				mdsav2 = md;
				md = mdsav1;
				nfsm_loadattr(newvp, (struct vattr *)0);
				dpos = dpossav2;
				md = mdsav2;
				dp->d_type =
				    IFTODT(VTTOIF(np->n_vattr.va_type));
				ndp->ni_vp = newvp;
E 133
D 67
				ndp->ni_hash = 0;
				for (cp = ndp->ni_ptr, i = 1; i <= len; i++, cp++)
					ndp->ni_hash += (unsigned char)*cp * i;
E 67
I 67
				cnp->cn_hash = 0;
D 133
				for (cp = cnp->cn_nameptr, i = 1; i <= len; i++, cp++)
					cnp->cn_hash += (unsigned char)*cp * i;
E 67
D 100
				if (ltime > time.tv_sec) {
					if (np->n_tnext) {
						if (np->n_tnext == (struct nfsnode *)nmp)
							nmp->nm_tprev = np->n_tprev;
						else
							np->n_tnext->n_tprev = np->n_tprev;
						if (np->n_tprev == (struct nfsnode *)nmp)
							nmp->nm_tnext = np->n_tnext;
						else
							np->n_tprev->n_tnext = np->n_tnext;
					} else
						np->n_flag &= ~NQNFSWRITE;
					if (cachable)
						np->n_flag &= ~NQNFSNONCACHE;
					else
						np->n_flag |= NQNFSNONCACHE;
					np->n_expiry = ltime;
					np->n_lrev = frev;
					tp = nmp->nm_tprev;
					while (tp != (struct nfsnode *)nmp && tp->n_expiry > np->n_expiry)
						tp = tp->n_tprev;
					if (tp == (struct nfsnode *)nmp) {
						np->n_tnext = nmp->nm_tnext;
						nmp->nm_tnext = np;
					} else {
						np->n_tnext = tp->n_tnext;
						tp->n_tnext = np;
					}
					np->n_tprev = tp;
					if (np->n_tnext == (struct nfsnode *)nmp)
						nmp->nm_tprev = np;
					else
						np->n_tnext->n_tprev = np;
D 67
					cache_enter(ndp);
E 67
I 67
					cache_enter(ndp->ni_dvp, ndp->ni_vp, cnp);
E 67
				}
E 100
I 100
				if ((nmp->nm_flag & NFSMNT_NQLOOKLEASE) &&
					ltime > time.tv_sec)
					nqnfs_clientlease(nmp, np, NQL_READ,
						cachable, ltime, frev);
E 133
I 133
				for (cp = cnp->cn_nameptr, i = 1; i <= len;
				    i++, cp++)
				    cnp->cn_hash += (unsigned char)*cp * i;
E 133
D 110
				cache_enter(ndp->ni_dvp, ndp->ni_vp, cnp);
E 110
I 110
				if (cnp->cn_namelen <= NCHNAMLEN)
D 111
					cache_enter(ndp->ni_dvp, ndp->ni_vp, cnp);
E 111
I 111
				    cache_enter(ndp->ni_dvp, ndp->ni_vp, cnp);
I 133
			    }
E 133
E 111
E 110
E 100
			} else {
D 133
				nfsm_adv(nfsm_rndup(len));
E 133
I 133
			    /* Just skip over the file handle */
			    nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
			    i = fxdr_unsigned(int, *tl);
			    nfsm_adv(nfsm_rndup(i));
E 133
			}
			if (newvp != NULLVP) {
D 133
				vrele(newvp);
				newvp = NULLVP;
E 133
I 133
			    vrele(newvp);
			    newvp = NULLVP;
E 133
			}
D 100
			nfsm_dissect(tl, u_long *, 2*NFSX_UNSIGNED);
E 100
I 100
D 133
			nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
E 100
			if (bigenough)
D 100
				endoff = off = fxdr_unsigned(off_t, *tl++);
E 100
I 100
				endoff = off = fxdr_unsigned(u_long, *tl++);
E 100
			else
D 100
				endoff = fxdr_unsigned(off_t, *tl++);
E 100
I 100
				endoff = fxdr_unsigned(u_long, *tl++);
E 133
I 133
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
E 133
E 100
			more_dirs = fxdr_unsigned(int, *tl);
		}
		/*
		 * If at end of rpc data, get the eof boolean
		 */
		if (!more_dirs) {
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
			more_dirs = (fxdr_unsigned(int, *tl) == 0);
D 133

			/*
			 * If at EOF, cache directory offset
			 */
			if (!more_dirs)
				VTONFS(vp)->n_direofoffset = endoff;
E 133
		}
D 133
		if (uiop->uio_resid < tresid)
D 100
			uiop->uio_offset = off;
E 100
I 100
			uiop->uio_offset = (off_t)off;
E 100
		else
			more_dirs = 0;
E 133
		m_freem(mrep);
	}
	/*
	 * Fill last record, iff any, out to a multiple of NFS_DIRBLKSIZ
	 * by increasing d_reclen for the last record.
	 */
D 133
	if (uiop->uio_resid < tresid) {
		len = uiop->uio_resid & (NFS_DIRBLKSIZ - 1);
		if (len > 0) {
			dp->d_reclen += len;
			uiop->uio_iov->iov_base += len;
			uiop->uio_iov->iov_len -= len;
			uiop->uio_resid -= len;
		}
E 133
I 133
	if (blksiz > 0) {
		left = DIRBLKSIZ - blksiz;
		dp->d_reclen += left;
		uiop->uio_iov->iov_base += left;
		uiop->uio_iov->iov_len -= left;
		uiop->uio_offset += left;
		uiop->uio_resid -= left;
E 133
	}
I 133

	/*
	 * We are now either at the end of the directory or have filled the
	 * block.
	 */
	if (bigenough)
		dnp->n_direofoffset = uiop->uio_offset;
	else {
		if (uiop->uio_resid > 0)
			printf("EEK! readdirplusrpc resid > 0\n");
		cookiep = nfs_getcookie(dnp, uiop->uio_offset, 1);
		*cookiep = cookie;
	}
E 133
nfsmout:
	if (newvp != NULLVP)
		vrele(newvp);
	return (error);
}
E 65
D 39
/*
 * nfs statfs call
 * (Actually a vfsop, not a vnode op)
 */
nfs_statfs(mp, sbp)
	struct mount *mp;
	register struct statfs *sbp;
{
I 13
	register struct vnode *vp;
E 13
D 5
	register struct nfsmount *nmp;
E 5
I 5
	register struct nfsv2_statfs *sfp;
E 5
D 13
	nfsm_vars;
E 13
I 13
	register caddr_t cp;
	register long t1;
	caddr_t bpos, dpos, cp2;
	u_long xid;
	int error = 0;
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
E 13
I 5
	struct nfsmount *nmp;
E 5
	struct ucred *cred;
	struct nfsnode *np;
D 13
	struct vnode *vp;
E 13

D 37
	nmp = vfs_to_nfs(mp);
E 37
I 37
	nmp = VFSTONFS(mp);
E 37
	if (error = nfs_nget(mp, &nmp->nm_fh, &np))
		return (error);
	vp = NFSTOV(np);
	nfsstats.rpccnt[NFSPROC_STATFS]++;
	cred = crget();
	cred->cr_ngroups = 1;
	nfsm_reqhead(nfs_procids[NFSPROC_STATFS], cred, NFSX_FH);
	nfsm_fhtom(vp);
D 26
	nfsm_request(vp);
E 26
I 26
	nfsm_request(vp, nonidempotent[NFSPROC_STATFS]);
E 26
D 5
	nfsm_disect(p, u_long *, 5*NFSX_UNSIGNED);
E 5
I 5
	nfsm_disect(sfp, struct nfsv2_statfs *, NFSX_STATFS);
E 5
	sbp->f_type = MOUNT_NFS;
I 19
	sbp->f_flags = nmp->nm_flag;
E 19
D 12
	sbp->f_flags = nmp->nm_flag;
E 12
D 5
	sbp->f_bsize = fxdr_unsigned(long, *p++);
	sbp->f_fsize = fxdr_unsigned(long, *p++);
	sbp->f_blocks = fxdr_unsigned(long, *p++);
	sbp->f_bfree = fxdr_unsigned(long, *p++);
	sbp->f_bavail = fxdr_unsigned(long, *p);
E 5
I 5
	sbp->f_bsize = fxdr_unsigned(long, sfp->sf_tsize);
	sbp->f_fsize = fxdr_unsigned(long, sfp->sf_bsize);
	sbp->f_blocks = fxdr_unsigned(long, sfp->sf_blocks);
	sbp->f_bfree = fxdr_unsigned(long, sfp->sf_bfree);
	sbp->f_bavail = fxdr_unsigned(long, sfp->sf_bavail);
E 5
D 4
	sbp->f_files = 0x7fffffff;
	sbp->f_ffree = 0x7fffffff;
E 4
I 4
	sbp->f_files = 0;
	sbp->f_ffree = 0;
I 19
D 33
	sbp->f_fsid.val[0] = mp->m_fsid.val[0];
	sbp->f_fsid.val[1] = mp->m_fsid.val[1];
E 19
E 4
D 12
	sbp->f_fsid.val[0] = mp->m_fsid.val[0];
	sbp->f_fsid.val[1] = mp->m_fsid.val[1];
E 12
	bcopy(nmp->nm_path, sbp->f_mntonname, MNAMELEN);
	bcopy(nmp->nm_host, sbp->f_mntfromname, MNAMELEN);
E 33
I 33
D 37
	if (sbp != &mp->m_stat) {
		bcopy(mp->m_stat.f_mntonname, sbp->f_mntonname, MNAMELEN);
		bcopy(mp->m_stat.f_mntfromname, sbp->f_mntfromname, MNAMELEN);
E 37
I 37
	if (sbp != &mp->mnt_stat) {
		bcopy(mp->mnt_stat.f_mntonname, sbp->f_mntonname, MNAMELEN);
		bcopy(mp->mnt_stat.f_mntfromname, sbp->f_mntfromname, MNAMELEN);
E 37
	}
E 33
	nfsm_reqdone;
	nfs_nput(vp);
	crfree(cred);
	return (error);
}

E 39
D 13
#define	HEXTOASC(x)	"0123456789abcdef"[x]
E 13
I 13
static char hextoasc[] = "0123456789abcdef";
E 13

/*
 * Silly rename. To make the NFS filesystem that is stateless look a little
 * more like the "ufs" a remove of an active vnode is translated to a rename
 * to a funny looking filename that is removed by nfs_inactive on the
 * nfsnode. There is the potential for another process on a different client
 * to create the same funny name between the nfs_lookitup() fails and the
 * nfs_rename() completes, but...
 */
D 57
nfs_sillyrename(ndp, flag)
E 57
I 57
D 58
nfs_sillyrename(ndp, flag, p)
E 58
I 58
D 66
nfs_sillyrename(ndp, p)
E 58
E 57
D 13
	struct nameidata *ndp;
E 13
I 13
	register struct nameidata *ndp;
E 13
D 58
	int flag;
E 58
I 57
	struct proc *p;
E 66
I 66
int
D 67
nfs_sillyrename(dvp, vp, cnp)   /* NEEDSWORK */
/* old: nfs_sillyrename(ndp, p) */
E 67
I 67
nfs_sillyrename(dvp, vp, cnp)
E 67
	struct vnode *dvp, *vp;
	struct componentname *cnp;
E 66
E 57
{
D 133
	register struct nfsnode *np;
E 133
	register struct sillyrename *sp;
I 133
	struct nfsnode *np;
E 133
D 58
	register struct nameidata *tndp;
E 58
	int error;
	short pid;

D 65
	np = VTONFS(ndp->ni_dvp);
E 65
I 6
D 66
	cache_purge(ndp->ni_dvp);
I 65
	np = VTONFS(ndp->ni_vp);
E 66
I 66
	cache_purge(dvp);
	np = VTONFS(vp);
E 66
E 65
I 64
D 133
#ifdef SILLYSEPARATE
E 133
I 133
#ifndef DIAGNOSTIC
	if (vp->v_type == VDIR)
		panic("nfs: sillyrename dir");
#endif
E 133
E 64
E 6
	MALLOC(sp, struct sillyrename *, sizeof (struct sillyrename),
D 5
		M_WAITOK, M_TEMP);
E 5
I 5
D 58
		M_TEMP, M_WAITOK);
E 5
	sp->s_flag = flag;
E 58
I 58
		M_NFSREQ, M_WAITOK);
I 64
D 133
#else
	sp = &np->n_silly;
#endif
E 133
E 64
E 58
D 65
	bcopy((caddr_t)&np->n_fh, (caddr_t)&sp->s_fh, NFSX_FH);
	np = VTONFS(ndp->ni_vp);
E 65
D 58
	tndp = &sp->s_namei;
	tndp->ni_cred = crdup(ndp->ni_cred);
E 58
I 58
D 66
	sp->s_cred = crdup(ndp->ni_cred);
	sp->s_dvp = ndp->ni_dvp;
	VREF(sp->s_dvp);
E 66
I 66
	sp->s_cred = crdup(cnp->cn_cred);
	sp->s_dvp = dvp;
	VREF(dvp);
E 66
E 58

	/* Fudge together a funny name */
D 56
	pid = u.u_procp->p_pid;
E 56
I 56
D 57
	pid = curproc->p_pid;
E 57
I 57
D 66
	pid = p->p_pid;
E 66
I 66
	pid = cnp->cn_proc->p_pid;
E 66
E 57
E 56
D 58
	bcopy(".nfsAxxxx4.4", tndp->ni_dent.d_name, 13);
	tndp->ni_dent.d_namlen = 12;
D 13
	tndp->ni_dent.d_name[8] = HEXTOASC(pid & 0xf);
	tndp->ni_dent.d_name[7] = HEXTOASC((pid >> 4) & 0xf);
	tndp->ni_dent.d_name[6] = HEXTOASC((pid >> 8) & 0xf);
	tndp->ni_dent.d_name[5] = HEXTOASC((pid >> 12) & 0xf);
E 13
I 13
	tndp->ni_dent.d_name[8] = hextoasc[pid & 0xf];
	tndp->ni_dent.d_name[7] = hextoasc[(pid >> 4) & 0xf];
	tndp->ni_dent.d_name[6] = hextoasc[(pid >> 8) & 0xf];
	tndp->ni_dent.d_name[5] = hextoasc[(pid >> 12) & 0xf];
E 58
I 58
	bcopy(".nfsAxxxx4.4", sp->s_name, 13);
	sp->s_namlen = 12;
	sp->s_name[8] = hextoasc[pid & 0xf];
	sp->s_name[7] = hextoasc[(pid >> 4) & 0xf];
	sp->s_name[6] = hextoasc[(pid >> 8) & 0xf];
	sp->s_name[5] = hextoasc[(pid >> 12) & 0xf];
E 58
E 13

	/* Try lookitups until we get one that isn't there */
D 57
	while (nfs_lookitup(ndp->ni_dvp, tndp, (nfsv2fh_t *)0) == 0) {
E 57
I 57
D 58
	while (nfs_lookitup(ndp->ni_dvp, tndp, (nfsv2fh_t *)0, p) == 0) {
E 57
		tndp->ni_dent.d_name[4]++;
		if (tndp->ni_dent.d_name[4] > 'z') {
E 58
I 58
D 66
	while (nfs_lookitup(sp, (nfsv2fh_t *)0, p) == 0) {
E 66
I 66
D 133
	while (nfs_lookitup(sp, (nfsv2fh_t *)0, cnp->cn_proc) == 0) {
E 133
I 133
	while (nfs_lookitup(dvp, sp->s_name, sp->s_namlen, sp->s_cred,
		cnp->cn_proc, (struct nfsnode **)0) == 0) {
E 133
E 66
		sp->s_name[4]++;
		if (sp->s_name[4] > 'z') {
E 58
			error = EINVAL;
			goto bad;
		}
	}
D 57
	if (error = nfs_renameit(ndp, tndp))
E 57
I 57
D 58
	if (error = nfs_renameit(ndp, tndp, p))
E 58
I 58
D 66
	if (error = nfs_renameit(ndp, sp, p))
E 66
I 66
	if (error = nfs_renameit(dvp, cnp, sp))
E 66
E 58
E 57
		goto bad;
D 57
	nfs_lookitup(ndp->ni_dvp, tndp, &np->n_fh);
E 57
I 57
D 58
	nfs_lookitup(ndp->ni_dvp, tndp, &np->n_fh, p);
E 58
I 58
D 66
	nfs_lookitup(sp, &np->n_fh, p);
E 66
I 66
D 133
	nfs_lookitup(sp, &np->n_fh, cnp->cn_proc);
E 133
I 133
	error = nfs_lookitup(dvp, sp->s_name, sp->s_namlen, sp->s_cred,
		cnp->cn_proc, &np);
E 133
E 66
E 58
E 57
	np->n_sillyrename = sp;
	return (0);
bad:
D 5
	crfree(ndp->ni_cred);
E 5
I 5
D 58
	crfree(tndp->ni_cred);
E 5
	free((caddr_t)sp, M_TEMP);
E 58
I 58
	vrele(sp->s_dvp);
	crfree(sp->s_cred);
I 64
D 133
#ifdef SILLYSEPARATE
E 133
E 64
	free((caddr_t)sp, M_NFSREQ);
I 64
D 133
#endif
E 133
E 64
E 58
	return (error);
}

/*
D 133
 * Look up a file name for silly rename stuff.
 * Just like nfs_lookup() except that it doesn't load returned values
 * into the nfsnode table.
 * If fhp != NULL it copies the returned file handle out
E 133
I 133
 * Look up a file name and optionally either update the file handle or
 * allocate an nfsnode, depending on the value of npp.
 * npp == NULL	--> just do the lookup
 * *npp == NULL --> allocate a new nfsnode and make sure attributes are
 *			handled too
 * *npp != NULL --> update the file handle in the vnode
E 133
 */
I 66
int
E 66
D 57
nfs_lookitup(vp, ndp, fhp)
E 57
I 57
D 58
nfs_lookitup(vp, ndp, fhp, p)
E 57
	register struct vnode *vp;
	register struct nameidata *ndp;
E 58
I 58
D 65
nfs_lookitup(sp, fhp, p)
E 65
I 65
D 133
nfs_lookitup(sp, fhp, procp)
E 65
	register struct sillyrename *sp;
E 58
	nfsv2fh_t *fhp;
E 133
I 133
nfs_lookitup(dvp, name, len, cred, procp, npp)
	register struct vnode *dvp;
	char *name;
	int len;
	struct ucred *cred;
E 133
I 57
D 65
	struct proc *p;
E 65
I 65
	struct proc *procp;
I 133
	struct nfsnode **npp;
E 133
E 65
E 57
{
I 58
D 133
	register struct vnode *vp = sp->s_dvp;
E 133
E 58
D 13
	nfsm_vars;
E 13
I 13
D 57
	register u_long *p;
E 57
I 57
	register u_long *tl;
E 57
	register caddr_t cp;
	register long t1, t2;
I 133
	struct vnode *newvp = (struct vnode *)0;
	struct nfsnode *np, *dnp = VTONFS(dvp);
E 133
	caddr_t bpos, dpos, cp2;
D 123
	u_long xid;
E 123
D 100
	int error = 0;
E 100
I 100
D 133
	int error = 0, isnq;
E 133
I 133
	int error = 0, fhlen, attrflag;
E 133
E 100
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
E 13
D 133
	long len;
E 133
I 133
	nfsfh_t *nfhp;
	int v3 = NFS_ISV3(dvp);
E 133

I 100
D 133
	isnq = (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS);
E 133
E 100
	nfsstats.rpccnt[NFSPROC_LOOKUP]++;
D 58
	ndp->ni_dvp = vp;
	ndp->ni_vp = NULL;
	len = ndp->ni_dent.d_namlen;
	nfsm_reqhead(nfs_procids[NFSPROC_LOOKUP], ndp->ni_cred, NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(len));
E 58
I 58
D 133
	len = sp->s_namlen;
D 65
	nfsm_reqhead(nfs_procids[NFSPROC_LOOKUP], sp->s_cred, NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(len));
E 65
I 65
	nfsm_reqhead(vp, NFSPROC_LOOKUP, NFSX_FH+NFSX_UNSIGNED+nfsm_rndup(len));
I 100
	if (isnq) {
		nfsm_build(tl, u_long *, NFSX_UNSIGNED);
		*tl = 0;
E 133
I 133
	nfsm_reqhead(dvp, NFSPROC_LOOKUP,
		NFSX_FH(v3) + NFSX_UNSIGNED + nfsm_rndup(len));
	nfsm_fhtom(dvp, v3);
	nfsm_strtom(name, len, NFS_MAXNAMLEN);
	nfsm_request(dvp, NFSPROC_LOOKUP, procp, cred);
	if (npp && !error) {
		nfsm_getfh(nfhp, fhlen, v3);
		if (*npp) {
		    np = *npp;
		    if (np->n_fhsize > NFS_SMALLFH && fhlen <= NFS_SMALLFH) {
			free((caddr_t)np->n_fhp, M_NFSBIGFH);
			np->n_fhp = &np->n_fh;
		    } else if (np->n_fhsize <= NFS_SMALLFH && fhlen>NFS_SMALLFH)
			np->n_fhp =(nfsfh_t *)malloc(fhlen,M_NFSBIGFH,M_WAITOK);
		    bcopy((caddr_t)nfhp, (caddr_t)np->n_fhp, fhlen);
		    np->n_fhsize = fhlen;
		    newvp = NFSTOV(np);
		} else if (NFS_CMPFH(dnp, nfhp, fhlen)) {
		    VREF(dvp);
		    newvp = dvp;
		} else {
		    error = nfs_nget(dvp->v_mount, nfhp, fhlen, &np);
		    if (error) {
			m_freem(mrep);
			return (error);
		    }
		    newvp = NFSTOV(np);
		}
		if (v3) {
			nfsm_postop_attr(newvp, attrflag);
			if (!attrflag && *npp == NULL) {
				m_freem(mrep);
				vrele(newvp);
				return (ENOENT);
			}
		} else
			nfsm_loadattr(newvp, (struct vattr *)0);
E 133
	}
E 100
E 65
E 58
D 133
	nfsm_fhtom(vp);
D 58
	nfsm_strtom(ndp->ni_dent.d_name, len, NFS_MAXNAMLEN);
E 58
I 58
	nfsm_strtom(sp->s_name, len, NFS_MAXNAMLEN);
E 58
D 26
	nfsm_request(vp);
E 26
I 26
D 39
	nfsm_request(vp, nonidempotent[NFSPROC_LOOKUP]);
E 39
I 39
D 42
	nfsm_request(vp, NFSPROC_LOOKUP, u.u_procp);
E 42
I 42
D 56
	nfsm_request(vp, NFSPROC_LOOKUP, u.u_procp, 1);
E 56
I 56
D 57
	nfsm_request(vp, NFSPROC_LOOKUP, curproc, 1);
E 57
I 57
D 65
	nfsm_request(vp, NFSPROC_LOOKUP, p, 1);
E 65
I 65
	nfsm_request(vp, NFSPROC_LOOKUP, procp, sp->s_cred);
E 65
E 57
E 56
E 42
E 39
E 26
	if (fhp != NULL) {
I 100
		if (isnq)
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
E 100
D 65
		nfsm_disect(cp, caddr_t, NFSX_FH);
E 65
I 65
		nfsm_dissect(cp, caddr_t, NFSX_FH);
E 65
		bcopy(cp, (caddr_t)fhp, NFSX_FH);
E 133
I 133
	nfsm_reqdone;
	if (npp && *npp == NULL) {
		if (error) {
			if (newvp)
				vrele(newvp);
		} else
			*npp = np;
E 133
	}
I 133
	return (error);
}

/*
 * Nfs Version 3 commit rpc
 */
int
nfs_commit(vp, offset, cnt, cred, procp)
	register struct vnode *vp;
	u_quad_t offset;
	int cnt;
	struct ucred *cred;
	struct proc *procp;
{
	register caddr_t cp;
	register u_long *tl;
	register int t1, t2;
	register struct nfsmount *nmp = VFSTONFS(vp->v_mount);
	caddr_t bpos, dpos, cp2;
	int error = 0, wccflag = NFSV3_WCCRATTR;
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
	
	if ((nmp->nm_flag & NFSMNT_HASWRITEVERF) == 0)
		return (0);
	nfsstats.rpccnt[NFSPROC_COMMIT]++;
	nfsm_reqhead(vp, NFSPROC_COMMIT, NFSX_FH(1));
	nfsm_fhtom(vp, 1);
	nfsm_build(tl, u_long *, 3 * NFSX_UNSIGNED);
	txdr_hyper(&offset, tl);
	tl += 2;
	*tl = txdr_unsigned(cnt);
	nfsm_request(vp, NFSPROC_COMMIT, procp, cred);
	nfsm_wcc_data(vp, wccflag);
	if (!error) {
		nfsm_dissect(tl, u_long *, NFSX_V3WRITEVERF);
		if (bcmp((caddr_t)nmp->nm_verf, (caddr_t)tl,
			NFSX_V3WRITEVERF)) {
			bcopy((caddr_t)tl, (caddr_t)nmp->nm_verf,
				NFSX_V3WRITEVERF);
			error = NFSERR_STALEWRITEVERF;
		}
	}
E 133
	nfsm_reqdone;
	return (error);
}

/*
 * Kludge City..
 * - make nfs_bmap() essentially a no-op that does no translation
D 39
 * - do nfs_strategy() by faking physical I/O with nfs_readit/nfs_writeit
E 39
I 39
D 133
 * - do nfs_strategy() by faking physical I/O with nfs_readrpc/nfs_writerpc
E 39
 *   after mapping the physical addresses into Kernel Virtual space in the
 *   nfsiobuf area.
E 133
I 133
 * - do nfs_strategy() by doing I/O with nfs_readrpc/nfs_writerpc
E 133
 *   (Maybe I could use the process's page mapping, but I was concerned that
 *    Kernel Write might not be enabled and also figured copyout() would do
 *    a lot more work than bcopy() and also it currently happens in the
 *    context of the swapper process (2).
 */
I 66
int
E 66
D 82
nfs_bmap(vp, bn, vpp, bnp)
	struct vnode *vp;
	daddr_t bn;
	struct vnode **vpp;
	daddr_t *bnp;
E 82
I 82
D 89
nfs_bmap (ap)
E 89
I 89
nfs_bmap(ap)
E 89
D 94
	struct vop_bmap_args *ap;
E 94
I 94
	struct vop_bmap_args /* {
		struct vnode *a_vp;
		daddr_t  a_bn;
		struct vnode **a_vpp;
		daddr_t *a_bnp;
I 104
		int *a_runp;
E 104
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define bn (ap->a_bn)
#define vpp (ap->a_vpp)
#define bnp (ap->a_bnp)
E 84
E 82
{
I 89
	register struct vnode *vp = ap->a_vp;

E 89
D 84
	if (vpp != NULL)
		*vpp = vp;
	if (bnp != NULL)
D 33
		*bnp = bn * btodb(vp->v_mount->m_bsize);
E 33
I 33
D 37
		*bnp = bn * btodb(vp->v_mount->m_stat.f_bsize);
E 37
I 37
D 65
		*bnp = bn * btodb(vp->v_mount->mnt_stat.f_bsize);
E 65
I 65
		*bnp = bn * btodb(vp->v_mount->mnt_stat.f_iosize);
E 84
I 84
	if (ap->a_vpp != NULL)
D 89
		*ap->a_vpp = ap->a_vp;
E 89
I 89
		*ap->a_vpp = vp;
E 89
	if (ap->a_bnp != NULL)
D 89
		*ap->a_bnp = ap->a_bn * btodb(ap->a_vp->v_mount->mnt_stat.f_iosize);
E 89
I 89
		*ap->a_bnp = ap->a_bn * btodb(vp->v_mount->mnt_stat.f_iosize);
I 130
D 133
	if (ap->a_runp != NULL)
		*ap->a_runp = 0;
E 133
E 130
E 89
E 84
E 65
E 37
E 33
	return (0);
}
I 82
D 84
#undef vp
#undef bn
#undef vpp
#undef bnp
E 84
E 82

/*
D 5
 * Fun and games with phys i/o
E 5
I 5
D 111
 * Strategy routine for phys. i/o
 * If the biod's are running, queue a request
 * otherwise just call nfs_doio() to get it done
E 111
I 111
 * Strategy routine.
 * For async requests when nfsiod(s) are running, queue the request by
 * calling nfs_asyncio(), otherwise just all nfs_doio() to do the
 * request.
E 111
E 5
 */
I 66
int
E 66
D 82
nfs_strategy(bp)
	register struct buf *bp;
E 82
I 82
D 89
nfs_strategy (ap)
E 89
I 89
nfs_strategy(ap)
E 89
D 94
	struct vop_strategy_args *ap;
E 94
I 94
D 111
	struct vop_strategy_args /* {
		struct buf *a_bp;
	} */ *ap;
E 111
I 111
	struct vop_strategy_args *ap;
E 111
E 94
D 84
#define bp (ap->a_bp)
E 84
E 82
{
I 89
	register struct buf *bp = ap->a_bp;
E 89
I 5
D 103
	register struct buf *dp;
E 103
I 6
D 111
	register int i;
E 111
I 111
	struct ucred *cr;
	struct proc *p;
E 111
E 6
D 54
	struct proc *rp;
E 54
	int error = 0;
I 6
D 111
	int fnd = 0;
E 111
E 6

I 111
	if (bp->b_flags & B_PHYS)
		panic("nfs physio");
	if (bp->b_flags & B_ASYNC)
		p = (struct proc *)0;
	else
		p = curproc;	/* XXX */
	if (bp->b_flags & B_READ)
		cr = bp->b_rcred;
	else
		cr = bp->b_wcred;
E 111
	/*
I 39
D 111
	 * Set b_proc. It seems a bit silly to do it here, but since bread()
	 * doesn't set it, I will.
D 51
	 * Set b_proc == NULL for asynchronous reads, since these may still
E 51
I 51
	 * Set b_proc == NULL for asynchronous ops, since these may still
E 51
	 * be hanging about after the process terminates.
	 */
D 51
	if ((bp->b_flags & (B_READ | B_ASYNC)) == (B_READ | B_ASYNC))
E 51
I 51
D 54
	if (bp->b_flags & B_ASYNC)
E 51
		bp->b_proc = (struct proc *)0;
	else
		bp->b_proc = u.u_procp;

E 54
I 54
D 84
	if ((bp->b_flags & B_PHYS) == 0) {
		if (bp->b_flags & B_ASYNC)
			bp->b_proc = (struct proc *)0;
E 84
I 84
D 89
	if ((ap->a_bp->b_flags & B_PHYS) == 0) {
		if (ap->a_bp->b_flags & B_ASYNC)
			ap->a_bp->b_proc = (struct proc *)0;
E 89
I 89
	if ((bp->b_flags & B_PHYS) == 0) {
		if (bp->b_flags & B_ASYNC)
			bp->b_proc = (struct proc *)0;
E 89
E 84
		else
D 56
			bp->b_proc = u.u_procp;
E 56
I 56
D 84
			bp->b_proc = curproc;
E 84
I 84
D 89
			ap->a_bp->b_proc = curproc;
E 89
I 89
			bp->b_proc = curproc;
E 89
E 84
E 56
	}
E 54
	/*
E 111
E 39
D 51
	 * If an i/o daemon is waiting
E 51
I 51
	 * If the op is asynchronous and an i/o daemon is waiting
E 51
	 * queue the request, wake it up and wait for completion
D 51
	 * otherwise just do it ourselves
E 51
I 51
	 * otherwise just do it ourselves.
E 51
	 */
D 6
	if (nfs_iodwant) {
		dp = &nfs_bqueue;
		if (dp->b_actf == NULL) {
			dp->b_actl = bp;
			bp->b_actf = dp;
		} else {
			dp->b_actf->b_actl = bp;
			bp->b_actf = dp->b_actf;
E 6
I 6
D 51
	for (i = 0; i < nfs_asyncdaemons; i++) {
E 51
I 51
D 54
	if (bp->b_proc == (struct proc *)NULL)
	    for (i = 0; i < nfs_asyncdaemons; i++) {
E 51
		if (rp = nfs_iodwant[i]) {
			/*
			 * Ensure that the async_daemon is still waiting here
			 */
			if (rp->p_stat != SSLEEP ||
			    rp->p_wchan != ((caddr_t)&nfs_iodwant[i])) {
				nfs_iodwant[i] = (struct proc *)0;
				continue;
			}
E 54
I 54
D 84
	if ((bp->b_flags & B_ASYNC) == 0 || nfs_numasync == 0)
		return (nfs_doio(bp));
E 84
I 84
D 89
	if ((ap->a_bp->b_flags & B_ASYNC) == 0 || nfs_numasync == 0)
		return (nfs_doio(ap->a_bp));
E 89
I 89
D 111
	if ((bp->b_flags & B_ASYNC) == 0 || nfs_numasync == 0)
		return (nfs_doio(bp));
E 89
E 84
	for (i = 0; i < NFS_MAXASYNCDAEMON; i++) {
		if (nfs_iodwant[i]) {
E 54
D 103
			dp = &nfs_bqueue;
			if (dp->b_actf == NULL) {
D 84
				dp->b_actl = bp;
				bp->b_actf = dp;
E 84
I 84
D 89
				dp->b_actl = ap->a_bp;
				ap->a_bp->b_actf = dp;
E 89
I 89
				dp->b_actl = bp;
				bp->b_actf = dp;
E 89
E 84
			} else {
D 84
				dp->b_actf->b_actl = bp;
				bp->b_actf = dp->b_actf;
E 84
I 84
D 89
				dp->b_actf->b_actl = ap->a_bp;
				ap->a_bp->b_actf = dp->b_actf;
E 89
I 89
				dp->b_actf->b_actl = bp;
				bp->b_actf = dp->b_actf;
E 89
E 84
			}
D 84
			dp->b_actf = bp;
			bp->b_actl = dp;
E 84
I 84
D 89
			dp->b_actf = ap->a_bp;
			ap->a_bp->b_actl = dp;
E 89
I 89
			dp->b_actf = bp;
			bp->b_actl = dp;
E 103
I 103
D 105
			bp->b_actf = NULL;
			bp->b_actb = nfs_bqueuetail;
			*nfs_bqueuetail = bp;
			nfs_bqueuetail = &bp->b_actf;
E 105
I 105
			queue_enter_tail(&nfs_bufq, bp, struct buf *, b_freelist);
E 105
E 103
E 89
E 84
			fnd++;
D 54
			nfs_iodwant[i] = (struct proc *)0;
E 54
			wakeup((caddr_t)&nfs_iodwant[i]);
			break;
E 6
		}
D 6
		dp->b_actf = bp;
		bp->b_actl = dp;
		nfs_iodwant = 0;
		wakeup((caddr_t)&nfs_iodwant);
	} else
E 6
I 6
	}
	if (!fnd)
E 6
D 84
		error = nfs_doio(bp);
E 84
I 84
D 89
		error = nfs_doio(ap->a_bp);
E 89
I 89
		error = nfs_doio(bp);
E 111
I 111
	if ((bp->b_flags & B_ASYNC) == 0 ||
		nfs_asyncio(bp, NOCRED))
		error = nfs_doio(bp, cr, p);
E 111
E 89
E 84
	return (error);
}
I 82
D 84
#undef bp
E 84
E 82

/*
D 111
 * Fun and games with i/o
 * Essentially play ubasetup() and disk interrupt service routine by
 * mapping the data buffer into kernel virtual space and doing the
 * nfs read or write rpc's from it.
D 39
 * If the biod's are not running, this is just called from nfs_strategy(),
 * otherwise it is called by the biod's to do what would normally be
E 39
I 39
 * If the nfsiod's are not running, this is just called from nfs_strategy(),
 * otherwise it is called by the nfsiods to do what would normally be
E 39
 * partially disk interrupt driven.
 */
I 66
int
E 66
nfs_doio(bp)
	register struct buf *bp;
{
E 5
D 38
	register struct pte *pte, *ppte;
	register caddr_t vaddr;
E 38
	register struct uio *uiop;
D 5
	register struct ucred *cr;
E 5
	register struct vnode *vp;
I 6
	struct nfsnode *np;
E 6
D 5
	int npf;
E 5
I 5
	struct ucred *cr;
D 38
	int npf, npf2;
	int reg;
	caddr_t vbase;
D 19
	caddr_t addr;
E 19
E 5
	unsigned v;
E 38
D 57
	struct proc *rp;
E 57
D 38
	int o, error;
E 38
I 38
	int error;
E 38
I 5
D 19
	int bcnt;
E 19
E 5
D 15
	off_t off;
E 15
	struct uio uio;
	struct iovec io;
I 38
D 45
#if !defined(hp300)
E 45
I 45
D 61
#if !defined(hp300) && !defined(i386)
E 45
	register struct pte *pte, *ppte;
	register caddr_t vaddr;
	int npf, npf2;
	int reg, o;
	caddr_t vbase;
	unsigned v;
#endif
E 61
E 38

	vp = bp->b_vp;
I 30
	np = VTONFS(vp);
E 30
D 5
	cr = crget();
	cr->cr_gid = 10;	/* Pick anything ?? */
	cr->cr_ngroups = 1;
E 5
	uiop = &uio;
	uiop->uio_iov = &io;
	uiop->uio_iovcnt = 1;
D 5
	io.iov_len = uiop->uio_resid = bp->b_bcount;
E 5
	uiop->uio_segflg = UIO_SYSSPACE;
I 57
D 65
	uiop->uio_procp = (struct proc *)0;
E 65
I 65
	uiop->uio_procp = bp->b_proc;
E 65
E 57
D 5
	uiop->uio_offset = off = bp->b_blkno*DEV_BSIZE;
	o = (int)bp->b_un.b_addr & PGOFSET;
	npf = btoc(bp->b_bcount + o);
	rp = bp->b_flags&B_DIRTY ? &proc[2] : bp->b_proc;
	cr->cr_uid = rp->p_uid;
	if ((bp->b_flags & B_PHYS) == 0)
		panic("nfs strategy Not PHYS IO");
	if (bp->b_flags & B_PAGET)
		pte = &Usrptmap[btokmx((struct pte *)bp->b_un.b_addr)];
	else {
		v = btop(bp->b_un.b_addr);
		if (bp->b_flags & B_UAREA)
			pte = &rp->p_addr[v];
		else
			pte = vtopte(rp, v);
E 5
I 5
D 19
	if (bp->b_flags & B_READ) {
		io.iov_len = uiop->uio_resid = bp->b_bcount;
D 15
		uiop->uio_offset = off = bp->b_blkno*DEV_BSIZE;
E 15
I 15
D 17
		uiop->uio_offset = bp->b_blkno*DEV_BSIZE;
E 17
I 17
		uiop->uio_offset = bp->b_lblkno * DEV_BSIZE;
E 17
E 15
		addr = bp->b_un.b_addr;
		bcnt = bp->b_bcount;
	} else {
D 17
		io.iov_len = uiop->uio_resid = bp->b_dirtyend-bp->b_dirtyoff;
D 15
		uiop->uio_offset = off = (bp->b_blkno*DEV_BSIZE)+bp->b_dirtyoff;
E 15
I 15
		uiop->uio_offset = (bp->b_blkno*DEV_BSIZE)+bp->b_dirtyoff;
E 17
I 17
		io.iov_len = uiop->uio_resid = bp->b_dirtyend - bp->b_dirtyoff;
		uiop->uio_offset = (bp->b_lblkno * DEV_BSIZE) + bp->b_dirtyoff;
E 17
E 15
		addr = bp->b_un.b_addr+bp->b_dirtyoff;
		bcnt = bp->b_dirtyend-bp->b_dirtyoff;
E 5
	}
E 19
I 19

E 19
	/*
D 5
	 * Play vmaccess() but with the Nfsiomap page table
E 5
I 5
	 * For phys i/o, map the b_addr into kernel virtual space using
	 * the Nfsiomap pte's
	 * Also, add a temporary b_rcred for reading using the process's uid
	 * and a guess at a group
E 5
	 */
D 5
	ppte = &Nfsiomap[0];
	vaddr = nfsiobuf;
	while (npf != 0) {
		mapin(ppte, (u_int)vaddr, pte->pg_pfnum, (int)(PG_V|PG_KW));
E 5
I 5
	if (bp->b_flags & B_PHYS) {
I 6
D 30
		VTONFS(vp)->n_flag |= NPAGEDON;
E 30
I 30
D 39
		np->n_flag |= NPAGEDON;
E 39
E 30
E 6
D 53
		bp->b_rcred = cr = crget();
		rp = (bp->b_flags & B_DIRTY) ? &proc[2] : bp->b_proc;
		cr->cr_uid = rp->p_uid;
		cr->cr_gid = 0;		/* Anything ?? */
		cr->cr_ngroups = 1;
E 53
I 53
D 57
		rp = (bp->b_flags & B_DIRTY) ? pageproc : bp->b_proc;
D 54
		bp->b_rcred = cr = crcopy(rp->p_ucred);
E 54
I 54
		cr = crcopy(rp->p_ucred);
E 57
I 57
		if (bp->b_flags & B_DIRTY)
			uiop->uio_procp = pageproc;
D 106
		cr = crcopy(uiop->uio_procp->p_ucred);
E 106
I 106
		cr = crdup(uiop->uio_procp->p_ucred);
E 106
E 57
E 54
E 53
I 38
D 45
#if defined(hp300)
E 45
I 45
D 61
#if defined(hp300) || defined(i386)
E 61
E 45
		/* mapping was already done by vmapbuf */
		io.iov_base = bp->b_un.b_addr;
D 61
#else
E 38
D 19
		o = (int)addr & PGOFSET;
		npf2 = npf = btoc(bcnt + o);
E 19
I 19
		o = (int)bp->b_un.b_addr & PGOFSET;
		npf2 = npf = btoc(bp->b_bcount + o);
E 61

E 19
		/*
D 61
		 * Get some mapping page table entries
		 */
		while ((reg = rmalloc(nfsmap, (long)npf)) == 0) {
			nfsmap_want++;
D 42
			sleep((caddr_t)&nfsmap_want, PZERO-1);
E 42
I 42
			(void) tsleep((caddr_t)&nfsmap_want, PZERO-1, "nfsmap",
					0);
E 42
		}
		reg--;
D 19
		/* I know it is always the else, but that may change someday */
		if ((bp->b_flags & B_PHYS) == 0)
D 18
			pte = kvtopte(bp->b_un.b_addr);
E 18
I 18
			pte = kvtopte(addr);
E 18
		else if (bp->b_flags & B_PAGET)
D 18
			pte = &Usrptmap[btokmx((struct pte *)bp->b_un.b_addr)];
E 18
I 18
			pte = &Usrptmap[btokmx((struct pte *)addr)];
E 19
I 19
		if (bp->b_flags & B_PAGET)
			pte = &Usrptmap[btokmx((struct pte *)bp->b_un.b_addr)];
E 19
E 18
		else {
D 18
			v = btop(bp->b_un.b_addr);
E 18
I 18
D 19
			v = btop(addr);
E 19
I 19
			v = btop(bp->b_un.b_addr);
E 19
E 18
			if (bp->b_flags & B_UAREA)
D 57
				pte = &rp->p_addr[v];
E 57
I 57
				pte = &uiop->uio_procp->p_addr[v];
E 57
			else
D 57
				pte = vtopte(rp, v);
E 57
I 57
				pte = vtopte(uiop->uio_procp, v);
E 57
		}
I 19

E 19
		/*
		 * Play vmaccess() but with the Nfsiomap page table
		 */
		ppte = &Nfsiomap[reg];
		vbase = vaddr = &nfsiobuf[reg*NBPG];
		while (npf != 0) {
			mapin(ppte, (u_int)vaddr, pte->pg_pfnum, (int)(PG_V|PG_KW));
E 5
#if defined(tahoe)
D 5
		mtpr(P1DC, vaddr);
E 5
I 5
			mtpr(P1DC, vaddr);
E 5
#endif
D 5
		ppte++;
		pte++;
		vaddr += NBPG;
		--npf;
E 5
I 5
			ppte++;
			pte++;
			vaddr += NBPG;
			--npf;
		}
I 38
		io.iov_base = vbase+o;
#endif /* !defined(hp300) */
E 38
I 19

		/*
E 61
		 * And do the i/o rpc
		 */
E 19
D 38
		io.iov_base = vbase+o;
E 38
D 19
	} else {
		io.iov_base = addr;
E 5
	}
D 5
	io.iov_base = nfsiobuf+o;
E 5
	if (bp->b_flags & B_READ) {
		uiop->uio_rw = UIO_READ;
D 5
		bp->b_error = error = nfs_read(vp, uiop, &off, 0, cr);
E 5
I 5
D 15
		bp->b_error = error = nfs_readrpc(vp, uiop, &off, bp->b_rcred);
E 15
I 15
		bp->b_error = error = nfs_readrpc(vp, uiop, bp->b_rcred);
E 15
E 5
	} else {
		uiop->uio_rw = UIO_WRITE;
D 5
		bp->b_error = error = nfs_write(vp, uiop, &off, 0, cr);
E 5
I 5
D 15
		bp->b_error = error = nfs_writerpc(vp, uiop, &off, bp->b_wcred);
E 15
I 15
		bp->b_error = error = nfs_writerpc(vp, uiop, bp->b_wcred);
E 15
I 6
		if (error) {
			np = VTONFS(vp);
			np->n_error = error;
			np->n_flag |= NWRITEERR;
E 19
I 19
		io.iov_len = uiop->uio_resid = bp->b_bcount;
D 21
		uiop->uio_offset = bp->b_lblkno * DEV_BSIZE;
E 21
I 21
		uiop->uio_offset = bp->b_blkno * DEV_BSIZE;
E 21
		if (bp->b_flags & B_READ) {
			uiop->uio_rw = UIO_READ;
			nfsstats.read_physios++;
D 39
			bp->b_error = error = nfs_readrpc(vp, uiop, bp->b_rcred);
E 39
I 39
D 54
			bp->b_error = error = nfs_readrpc(vp, uiop,
				bp->b_rcred, bp->b_proc);
E 54
I 54
D 57
			bp->b_error = error = nfs_readrpc(vp, uiop, cr, rp);
E 57
I 57
			bp->b_error = error = nfs_readrpc(vp, uiop, cr);
E 57
E 54
E 39
I 30
D 48
			/*
			 * If a text file has been modified since it was exec'd
			 * blow the process' out of the water. This is the
			 * closest we can come to "Text File Busy" in good old
			 * stateless nfs.
			 */
			if ((vp->v_flag & VTEXT) &&
			    (vp->v_text->x_mtime != np->n_vattr.va_mtime.tv_sec))
				xinval(vp);
E 48
I 48
			(void) vnode_pager_uncache(vp);
E 48
E 30
		} else {
			uiop->uio_rw = UIO_WRITE;
			nfsstats.write_physios++;
D 39
			bp->b_error = error = nfs_writerpc(vp, uiop, bp->b_wcred);
E 39
I 39
D 54
			bp->b_error = error = nfs_writerpc(vp, uiop,
				bp->b_wcred, bp->b_proc);
E 54
I 54
D 57
			bp->b_error = error = nfs_writerpc(vp, uiop, cr, rp);
E 57
I 57
D 100
			bp->b_error = error = nfs_writerpc(vp, uiop, cr);
E 100
I 100
			bp->b_error = error = nfs_writerpc(vp, uiop, cr, 0);
E 100
E 57
E 54
E 39
E 19
		}
E 6
D 19
		bp->b_dirtyoff = bp->b_dirtyend = 0;
E 5
	}
I 5
	if (error)
		bp->b_flags |= B_ERROR;
E 5
	bp->b_resid = uiop->uio_resid;
I 5
	/*
	 * Release pte's used by physical i/o
	 */
	if (bp->b_flags & B_PHYS) {
E 19
I 19

		/*
		 * Finally, release pte's used by physical i/o
		 */
E 19
		crfree(cr);
I 38
D 45
#if !defined(hp300)
E 45
I 45
D 61
#if !defined(hp300) && !defined(i386)
E 45
E 38
		rmfree(nfsmap, (long)npf2, (long)++reg);
		if (nfsmap_want) {
			nfsmap_want = 0;
			wakeup((caddr_t)&nfsmap_want);
		}
I 38
#endif
E 61
E 38
I 19
	} else {
		if (bp->b_flags & B_READ) {
			io.iov_len = uiop->uio_resid = bp->b_bcount;
D 21
			uiop->uio_offset = bp->b_lblkno * DEV_BSIZE;
E 21
I 21
D 39
			uiop->uio_offset = bp->b_blkno * DEV_BSIZE;
E 39
E 21
			io.iov_base = bp->b_un.b_addr;
			uiop->uio_rw = UIO_READ;
D 39
			nfsstats.read_bios++;
			bp->b_error = error = nfs_readrpc(vp, uiop, bp->b_rcred);
E 39
I 39
			switch (vp->v_type) {
			case VREG:
				uiop->uio_offset = bp->b_blkno * DEV_BSIZE;
				nfsstats.read_bios++;
D 57
				error = nfs_readrpc(vp, uiop, bp->b_rcred,
					bp->b_proc);
E 57
I 57
				error = nfs_readrpc(vp, uiop, bp->b_rcred);
E 57
				break;
			case VLNK:
				uiop->uio_offset = 0;
				nfsstats.readlink_bios++;
D 57
				error = nfs_readlinkrpc(vp, uiop, bp->b_rcred,
						bp->b_proc);
E 57
I 57
				error = nfs_readlinkrpc(vp, uiop, bp->b_rcred);
E 57
				break;
			case VDIR:
				uiop->uio_offset = bp->b_lblkno;
				nfsstats.readdir_bios++;
D 57
				error = nfs_readdirrpc(vp, uiop, bp->b_rcred,
					    bp->b_proc);
E 57
I 57
D 65
				error = nfs_readdirrpc(vp, uiop, bp->b_rcred);
E 65
I 65
D 100
				if (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_RDIRALOOK)
E 100
I 100
				if (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS)
E 100
				    error = nfs_readdirlookrpc(vp, uiop, bp->b_rcred);
				else
				    error = nfs_readdirrpc(vp, uiop, bp->b_rcred);
E 65
E 57
				/*
				 * Save offset cookie in b_blkno.
				 */
				bp->b_blkno = uiop->uio_offset;
				break;
			};
			bp->b_error = error;
E 39
		} else {
			io.iov_len = uiop->uio_resid = bp->b_dirtyend
				- bp->b_dirtyoff;
D 21
			uiop->uio_offset = (bp->b_lblkno * DEV_BSIZE)
E 21
I 21
			uiop->uio_offset = (bp->b_blkno * DEV_BSIZE)
E 21
				+ bp->b_dirtyoff;
			io.iov_base = bp->b_un.b_addr + bp->b_dirtyoff;
			uiop->uio_rw = UIO_WRITE;
			nfsstats.write_bios++;
D 39
			bp->b_error = error = nfs_writerpc(vp, uiop, bp->b_wcred);
E 39
I 39
			bp->b_error = error = nfs_writerpc(vp, uiop,
D 57
				bp->b_wcred, bp->b_proc);
E 57
I 57
D 100
				bp->b_wcred);
E 100
I 100
				bp->b_wcred, 0);
E 100
E 57
E 39
			if (error) {
D 30
				np = VTONFS(vp);
E 30
				np->n_error = error;
				np->n_flag |= NWRITEERR;
			}
			bp->b_dirtyoff = bp->b_dirtyend = 0;
		}
E 19
	}
I 19
	if (error)
		bp->b_flags |= B_ERROR;
	bp->b_resid = uiop->uio_resid;
E 19
E 5
	biodone(bp);
D 5
	crfree(cr);
E 5
I 5
	return (error);
}

/*
E 111
I 57
 * Mmap a file
 *
 * NB Currently unsupported.
 */
/* ARGSUSED */
I 66
int
E 66
D 82
nfs_mmap(vp, fflags, cred, p)
	struct vnode *vp;
	int fflags;
	struct ucred *cred;
	struct proc *p;
E 82
I 82
D 89
nfs_mmap (ap)
E 89
I 89
nfs_mmap(ap)
E 89
D 94
	struct vop_mmap_args *ap;
E 94
I 94
	struct vop_mmap_args /* {
		struct vnode *a_vp;
		int  a_fflags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define fflags (ap->a_fflags)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 84
E 82
{

	return (EINVAL);
}
I 82
D 84
#undef vp
#undef fflags
#undef cred
#undef p
E 84
E 82

/*
E 57
D 133
 * Flush all the blocks associated with a vnode.
 * 	Walk through the buffer pool and push any dirty pages
 *	associated with the vnode.
E 133
I 133
 * fsync vnode op. Just call nfs_flush() with commit == 1.
E 133
 */
I 13
/* ARGSUSED */
I 66
int
E 66
E 13
D 15
nfs_fsync(vp, fflags, cred)
E 15
I 15
D 57
nfs_fsync(vp, fflags, cred, waitfor)
E 57
I 57
D 82
nfs_fsync(vp, fflags, cred, waitfor, p)
E 57
E 15
	register struct vnode *vp;
	int fflags;
	struct ucred *cred;
I 15
	int waitfor;
I 57
	struct proc *p;
E 82
I 82
D 89
nfs_fsync (ap)
E 89
I 89
nfs_fsync(ap)
E 89
D 93
	struct vop_fsync_args *ap;
E 93
I 93
	struct vop_fsync_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode * a_vp;
		struct ucred * a_cred;
		int  a_waitfor;
		struct proc * a_p;
	} */ *ap;
E 93
D 84
#define vp (ap->a_vp)
#define fflags (ap->a_fflags)
#define cred (ap->a_cred)
#define waitfor (ap->a_waitfor)
#define p (ap->a_p)
E 84
E 82
E 57
E 15
{
D 84
	register struct nfsnode *np = VTONFS(vp);
E 84
I 84
D 93
	register struct nfsnode *np = VTONFS(ap->a_vp);
E 84
D 19
	int error;
E 19
I 19
	int error = 0;
E 93
I 93
D 133
	register struct vnode *vp = ap->a_vp;
E 133
I 133

	return (nfs_flush(ap->a_vp, ap->a_cred, ap->a_waitfor, ap->a_p, 1));
}

/*
 * Flush all the blocks associated with a vnode.
 * 	Walk through the buffer pool and push any dirty pages
 *	associated with the vnode.
 */
int
nfs_flush(vp, cred, waitfor, p, commit)
	register struct vnode *vp;
	struct ucred *cred;
	int waitfor;
	struct proc *p;
	int commit;
{
E 133
	register struct nfsnode *np = VTONFS(vp);
	register struct buf *bp;
I 133
	register int i;
E 133
	struct buf *nbp;
D 111
	int s, error = 0;
E 111
I 111
D 133
	struct nfsmount *nmp;
	int s, error = 0, slptimeo = 0, slpflag = 0;
E 133
I 133
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
	int s, error = 0, slptimeo = 0, slpflag = 0, retv, bvecpos;
	int passone = 1;
	u_quad_t off = (u_quad_t)-1, endoff = 0, toff;
#ifndef NFS_COMMITBVECSIZ
#define NFS_COMMITBVECSIZ	20
#endif
	struct buf *bvec[NFS_COMMITBVECSIZ];
E 133
E 111
E 93
E 19

I 111
D 133
	nmp = VFSTONFS(vp->v_mount);
E 133
	if (nmp->nm_flag & NFSMNT_INT)
		slpflag = PCATCH;
I 133
	if (!commit)
		passone = 0;
	/*
	 * A b_flags == (B_DELWRI | B_NEEDCOMMIT) block has been written to the
	 * server, but nas not been committed to stable storage on the server
	 * yet. On the first pass, the byte range is worked out and the commit
	 * rpc is done. On the second pass, nfs_writebp() is called to do the
	 * job.
	 */
again:
	bvecpos = 0;
	if (NFS_ISV3(vp) && commit) {
		s = splbio();
		for (bp = vp->v_dirtyblkhd.lh_first; bp; bp = nbp) {
			nbp = bp->b_vnbufs.le_next;
			if (bvecpos >= NFS_COMMITBVECSIZ)
				break;
			if ((bp->b_flags & (B_BUSY | B_DELWRI | B_NEEDCOMMIT))
				!= (B_DELWRI | B_NEEDCOMMIT))
				continue;
			bremfree(bp);
			bp->b_flags |= (B_BUSY | B_WRITEINPROG);
			/*
			 * A list of these buffers is kept so that the
			 * second loop knows which buffers have actually
			 * been committed. This is necessary, since there
			 * may be a race between the commit rpc and new
			 * uncommitted writes on the file.
			 */
			bvec[bvecpos++] = bp;
			toff = ((u_quad_t)bp->b_blkno) * DEV_BSIZE +
				bp->b_dirtyoff;
			if (toff < off)
				off = toff;
			toff += (u_quad_t)(bp->b_dirtyend - bp->b_dirtyoff);
			if (toff > endoff)
				endoff = toff;
		}
		splx(s);
	}
	if (bvecpos > 0) {
		/*
		 * Commit data on the server, as required.
		 */
		retv = nfs_commit(vp, off, (int)(endoff - off), cred, p);
		if (retv == NFSERR_STALEWRITEVERF)
			nfs_clearcommit(vp->v_mount);
		/*
		 * Now, either mark the blocks I/O done or mark the
		 * blocks dirty, depending on whether the commit
		 * succeeded.
		 */
		for (i = 0; i < bvecpos; i++) {
			bp = bvec[i];
			bp->b_flags &= ~(B_NEEDCOMMIT | B_WRITEINPROG);
			if (retv) {
			    brelse(bp);
			} else {
			    vp->v_numoutput++;
			    bp->b_flags |= B_ASYNC;
			    bp->b_flags &= ~(B_READ|B_DONE|B_ERROR|B_DELWRI);
			    bp->b_dirtyoff = bp->b_dirtyend = 0;
			    reassignbuf(bp, vp);
			    biodone(bp);
			}
		}
	}

	/*
	 * Start/do any write(s) that are required.
	 */
E 133
E 111
D 15
	nfs_lock(vp);
E 15
D 93
	if (np->n_flag & NMODIFIED) {
		np->n_flag &= ~NMODIFIED;
D 6
		error = nfs_blkflush(vp, (daddr_t)0, VTONFS(vp)->n_size, FALSE);
E 6
I 6
D 19
		error = nfs_blkflush(vp, (daddr_t)0, np->n_size, FALSE);
E 19
I 19
D 84
		vflushbuf(vp, waitfor == MNT_WAIT ? B_SYNC : 0);
E 84
I 84
		vflushbuf(ap->a_vp, ap->a_waitfor == MNT_WAIT ? B_SYNC : 0);
E 93
I 93
loop:
	s = splbio();
D 105
	for (bp = vp->v_dirtyblkhd; bp; bp = nbp) {
		nbp = bp->b_blockf;
E 105
I 105
D 122
	for (bp = vp->v_dirtyblkhd.le_next; bp; bp = nbp) {
		nbp = bp->b_vnbufs.qe_next;
E 122
I 122
	for (bp = vp->v_dirtyblkhd.lh_first; bp; bp = nbp) {
		nbp = bp->b_vnbufs.le_next;
E 122
E 105
D 111
		if ((bp->b_flags & B_BUSY))
			continue;
E 111
I 111
		if (bp->b_flags & B_BUSY) {
D 133
			if (ap->a_waitfor != MNT_WAIT)
E 133
I 133
			if (waitfor != MNT_WAIT || passone)
E 133
				continue;
			bp->b_flags |= B_WANTED;
			error = tsleep((caddr_t)bp, slpflag | (PRIBIO + 1),
				"nfsfsync", slptimeo);
			splx(s);
			if (error) {
D 133
			    if (nfs_sigintr(nmp, (struct nfsreq *)0, ap->a_p))
E 133
I 133
			    if (nfs_sigintr(nmp, (struct nfsreq *)0, p))
E 133
				return (EINTR);
			    if (slpflag == PCATCH) {
				slpflag = 0;
				slptimeo = 2 * hz;
			    }
			}
			goto loop;
		}
E 111
		if ((bp->b_flags & B_DELWRI) == 0)
			panic("nfs_fsync: not dirty");
I 133
		if ((passone || !commit) && (bp->b_flags & B_NEEDCOMMIT))
			continue;
E 133
		bremfree(bp);
D 133
		bp->b_flags |= B_BUSY;
E 133
I 133
		if (passone || !commit)
		    bp->b_flags |= (B_BUSY|B_ASYNC);
		else
		    bp->b_flags |= (B_BUSY|B_ASYNC|B_WRITEINPROG|B_NEEDCOMMIT);
E 133
		splx(s);
D 107
		error = bawrite(bp);
E 107
I 107
D 111
		bawrite(bp);
E 111
I 111
D 133
		bp->b_flags |= B_ASYNC;
E 133
		VOP_BWRITE(bp);
E 111
E 107
		goto loop;
E 93
E 84
E 19
E 6
	}
I 111
	splx(s);
E 111
I 93
D 133
	if (ap->a_waitfor == MNT_WAIT) {
E 133
I 133
	if (passone) {
		passone = 0;
		goto again;
	}
	if (waitfor == MNT_WAIT) {
E 133
		while (vp->v_numoutput) {
			vp->v_flag |= VBWAIT;
D 111
			sleep((caddr_t)&vp->v_numoutput, PRIBIO + 1);
E 111
I 111
			error = tsleep((caddr_t)&vp->v_numoutput,
				slpflag | (PRIBIO + 1), "nfsfsync", slptimeo);
			if (error) {
D 133
			    if (nfs_sigintr(nmp, (struct nfsreq *)0, ap->a_p))
E 133
I 133
			    if (nfs_sigintr(nmp, (struct nfsreq *)0, p))
E 133
				return (EINTR);
			    if (slpflag == PCATCH) {
				slpflag = 0;
				slptimeo = 2 * hz;
			    }
			}
E 111
		}
D 111
#ifdef DIAGNOSTIC
E 111
D 105
		if (vp->v_dirtyblkhd) {
E 105
I 105
D 122
		if (vp->v_dirtyblkhd.le_next) {
E 122
I 122
D 133
		if (vp->v_dirtyblkhd.lh_first) {
E 122
I 111
#ifdef DIAGNOSTIC
E 133
I 133
		if (vp->v_dirtyblkhd.lh_first && commit) {
#ifndef DIAGNOSTIC
E 133
E 111
E 105
			vprint("nfs_fsync: dirty", vp);
I 111
#endif
E 111
			goto loop;
		}
D 111
#endif
E 111
	}
D 111
	splx(s);
	np->n_flag &= ~NMODIFIED;
E 111
E 93
I 19
D 86
	if (!error && (np->n_flag & NWRITEERR))
E 86
I 86
	if (np->n_flag & NWRITEERR) {
E 86
		error = np->n_error;
I 86
		np->n_flag &= ~NWRITEERR;
	}
E 86
E 19
D 15
	nfs_unlock(vp);
E 15
E 5
	return (error);
I 116
}

/*
 * Return POSIX pathconf information applicable to nfs.
 *
D 133
 * Currently the NFS protocol does not support getting such
 * information from the remote server.
E 133
I 133
 * The NFS V2 protocol doesn't support this, so just return EINVAL
 * for V2.
E 133
 */
/* ARGSUSED */
I 133
int
E 133
nfs_pathconf(ap)
	struct vop_pathconf_args /* {
		struct vnode *a_vp;
		int a_name;
		int *a_retval;
	} */ *ap;
{

	return (EINVAL);
E 116
I 50
}
I 82
D 84
#undef vp
#undef fflags
#undef cred
#undef waitfor
#undef p
E 84
E 82

/*
 * NFS advisory byte-level locks.
 * Currently unsupported.
 */
I 66
int
E 66
D 82
nfs_advlock(vp, id, op, fl, flags)
	struct vnode *vp;
	caddr_t id;
	int op;
	struct flock *fl;
	int flags;
E 82
I 82
D 89
nfs_advlock (ap)
E 89
I 89
nfs_advlock(ap)
E 89
D 94
	struct vop_advlock_args *ap;
E 94
I 94
	struct vop_advlock_args /* {
		struct vnode *a_vp;
		caddr_t  a_id;
		int  a_op;
		struct flock *a_fl;
		int  a_flags;
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define id (ap->a_id)
#define op (ap->a_op)
#define fl (ap->a_fl)
#define flags (ap->a_flags)
E 84
E 82
{

	return (EOPNOTSUPP);
E 50
I 17
}
I 82
D 84
#undef vp
#undef id
#undef op
#undef fl
#undef flags
E 84
E 82

/*
 * Print out the contents of an nfsnode.
 */
I 66
int
E 66
D 82
nfs_print(vp)
	struct vnode *vp;
E 82
I 82
D 89
nfs_print (ap)
E 89
I 89
nfs_print(ap)
E 89
D 94
	struct vop_print_args *ap;
E 94
I 94
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
E 84
E 82
{
D 84
	register struct nfsnode *np = VTONFS(vp);
E 84
I 84
D 89
	register struct nfsnode *np = VTONFS(ap->a_vp);
E 89
I 89
	register struct vnode *vp = ap->a_vp;
	register struct nfsnode *np = VTONFS(vp);
E 89
E 84

D 31
	printf("tag VT_NFS, fileid %d fsid 0x%x%s\n",
		np->n_vattr.va_fileid, np->n_vattr.va_fsid,
		(np->n_flag & NLOCKED) ? " (LOCKED)" : "");
E 31
I 31
D 133
	printf("tag VT_NFS, fileid %d fsid 0x%x",
E 133
I 133
	printf("tag VT_NFS, fileid %ld fsid 0x%lx",
E 133
		np->n_vattr.va_fileid, np->n_vattr.va_fsid);
D 133
#ifdef FIFO
E 133
D 84
	if (vp->v_type == VFIFO)
		fifo_printinfo(vp);
E 84
I 84
D 89
	if (ap->a_vp->v_type == VFIFO)
		fifo_printinfo(ap->a_vp);
E 89
I 89
	if (vp->v_type == VFIFO)
		fifo_printinfo(vp);
E 89
E 84
D 133
#endif /* FIFO */
E 133
D 65
	printf("%s\n", (np->n_flag & NLOCKED) ? " (LOCKED)" : "");
E 31
I 24
	if (np->n_lockholder == 0)
		return;
	printf("\towner pid %d", np->n_lockholder);
	if (np->n_lockwaiter)
		printf(" waiting pid %d", np->n_lockwaiter);
E 65
	printf("\n");
I 133
	return (0);
E 133
I 63
}
I 82
D 84
#undef vp
E 84
E 82

/*
 * NFS directory offset lookup.
 * Currently unsupported.
 */
I 66
int
E 66
D 82
nfs_blkatoff(vp, offset, res, bpp)
	struct vnode *vp;
	off_t offset;
	char **res;
	struct buf **bpp;
E 82
I 82
D 89
nfs_blkatoff (ap)
E 89
I 89
nfs_blkatoff(ap)
E 89
D 94
	struct vop_blkatoff_args *ap;
E 94
I 94
	struct vop_blkatoff_args /* {
		struct vnode *a_vp;
		off_t a_offset;
		char **a_res;
		struct buf **a_bpp;
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define offset (ap->a_offset)
#define res (ap->a_res)
#define bpp (ap->a_bpp)
E 84
E 82
{

	return (EOPNOTSUPP);
}
I 82
D 84
#undef vp
#undef offset
#undef res
#undef bpp
E 84
E 82

/*
D 94
 * NFS flat namespace lookup.
 * Currently unsupported.
 */
I 66
int
E 66
D 82
nfs_vget(mp, ino, vpp)
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
E 82
I 82
D 89
nfs_vget (ap)
E 89
I 89
nfs_vget(ap)
E 89
	struct vop_vget_args *ap;
D 84
#define mp (ap->a_mp)
#define ino (ap->a_ino)
#define vpp (ap->a_vpp)
E 84
E 82
{

	return (EOPNOTSUPP);
}
I 82
D 84
#undef mp
#undef ino
#undef vpp
E 84
E 82

/*
E 94
 * NFS flat namespace allocation.
 * Currently unsupported.
 */
I 66
int
E 66
D 82
nfs_valloc(pvp, mode, cred, vpp)
	struct vnode *pvp;
	int mode;
	struct ucred *cred;
	struct vnode **vpp;
E 82
I 82
D 89
nfs_valloc (ap)
E 89
I 89
nfs_valloc(ap)
E 89
D 94
	struct vop_valloc_args *ap;
E 94
I 94
	struct vop_valloc_args /* {
		struct vnode *a_pvp;
		int a_mode;
		struct ucred *a_cred;
		struct vnode **a_vpp;
	} */ *ap;
E 94
D 84
#define pvp (ap->a_pvp)
#define mode (ap->a_mode)
#define cred (ap->a_cred)
#define vpp (ap->a_vpp)
E 84
E 82
{

	return (EOPNOTSUPP);
}
I 82
D 84
#undef pvp
#undef mode
#undef cred
#undef vpp
E 84
E 82

/*
 * NFS flat namespace free.
 * Currently unsupported.
 */
D 83
void
E 83
I 83
int
E 83
D 82
nfs_vfree(pvp, ino, mode)
	struct vnode *pvp;
	ino_t ino;
	int mode;
E 82
I 82
D 89
nfs_vfree (ap)
E 89
I 89
nfs_vfree(ap)
E 89
D 94
	struct vop_vfree_args *ap;
E 94
I 94
	struct vop_vfree_args /* {
		struct vnode *a_pvp;
		ino_t a_ino;
		int a_mode;
	} */ *ap;
E 94
D 84
#define pvp (ap->a_pvp)
#define ino (ap->a_ino)
#define mode (ap->a_mode)
E 84
E 82
{

D 83
	return;
E 83
I 83
	return (EOPNOTSUPP);
E 83
}
I 82
D 84
#undef pvp
#undef ino
#undef mode
E 84
E 82

/*
 * NFS file truncation.
 */
I 66
int
E 66
D 71
nfs_truncate(vp, length, flags)
E 71
I 71
D 82
nfs_truncate(vp, length, flags, cred)
E 71
	struct vnode *vp;
D 70
	u_long length;
E 70
I 70
	off_t length;
E 70
	int flags;
I 71
	struct ucred *cred;
E 82
I 82
D 89
nfs_truncate (ap)
E 89
I 89
nfs_truncate(ap)
E 89
D 94
	struct vop_truncate_args *ap;
E 94
I 94
	struct vop_truncate_args /* {
		struct vnode *a_vp;
		off_t a_length;
		int a_flags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define length (ap->a_length)
#define flags (ap->a_flags)
#define cred (ap->a_cred)
E 84
E 82
E 71
{

	/* Use nfs_setattr */
	printf("nfs_truncate: need to implement!!");
	return (EOPNOTSUPP);
}
I 82
D 84
#undef vp
#undef length
#undef flags
#undef cred
E 84
E 82

/*
 * NFS update.
 */
I 66
int
E 66
D 82
nfs_update(vp, ta, tm, waitfor)
	struct vnode *vp;
	struct timeval *ta;
	struct timeval *tm;
	int waitfor;
E 82
I 82
D 89
nfs_update (ap)
E 89
I 89
nfs_update(ap)
E 89
D 94
	struct vop_update_args *ap;
E 94
I 94
	struct vop_update_args /* {
		struct vnode *a_vp;
		struct timeval *a_ta;
		struct timeval *a_tm;
		int a_waitfor;
	} */ *ap;
E 94
D 84
#define vp (ap->a_vp)
#define ta (ap->a_ta)
#define tm (ap->a_tm)
#define waitfor (ap->a_waitfor)
E 84
E 82
{

	/* Use nfs_setattr */
	printf("nfs_update: need to implement!!");
	return (EOPNOTSUPP);
I 102
}

/*
I 133
 * Just call nfs_writebp() with the force argument set to 1.
 */
int
nfs_bwrite(ap)
	struct vop_bwrite_args /* {
		struct vnode *a_bp;
	} */ *ap;
{

	return (nfs_writebp(ap->a_bp, 1));
}

/*
 * This is a clone of vn_bwrite(), except that B_WRITEINPROG isn't set unless
 * the force flag is one and it also handles the B_NEEDCOMMIT flag.
 */
int
nfs_writebp(bp, force)
	register struct buf *bp;
	int force;
{
	register int oldflags = bp->b_flags, retv = 1;
	register struct proc *p = curproc;	/* XXX */
	off_t off;

	if(!(bp->b_flags & B_BUSY))
		panic("bwrite: buffer is not busy???");

	bp->b_flags &= ~(B_READ|B_DONE|B_ERROR|B_DELWRI);

	if (oldflags & B_ASYNC) {
		if (oldflags & B_DELWRI) {
			reassignbuf(bp, bp->b_vp);
		} else if (p) {
			++p->p_stats->p_ru.ru_oublock;
		}
	}
	bp->b_vp->v_numoutput++;

	/*
	 * If B_NEEDCOMMIT is set, a commit rpc may do the trick. If not
	 * an actual write will have to be scheduled via. VOP_STRATEGY().
	 * If B_WRITEINPROG is already set, then push it with a write anyhow.
	 */
	if (oldflags & (B_NEEDCOMMIT | B_WRITEINPROG) == B_NEEDCOMMIT) {
		off = ((u_quad_t)bp->b_blkno) * DEV_BSIZE + bp->b_dirtyoff;
		bp->b_flags |= B_WRITEINPROG;
		retv = nfs_commit(bp->b_vp, off, bp->b_dirtyend-bp->b_dirtyoff,
			bp->b_wcred, bp->b_proc);
		bp->b_flags &= ~B_WRITEINPROG;
		if (!retv) {
			bp->b_dirtyoff = bp->b_dirtyend = 0;
			bp->b_flags &= ~B_NEEDCOMMIT;
			biodone(bp);
		} else if (retv == NFSERR_STALEWRITEVERF)
			nfs_clearcommit(bp->b_vp->v_mount);
	}
	if (retv) {
		if (force)
			bp->b_flags |= B_WRITEINPROG;
		VOP_STRATEGY(bp);
	}

	if( (oldflags & B_ASYNC) == 0) {
		int rtval = biowait(bp);
		if (oldflags & B_DELWRI) {
			reassignbuf(bp, bp->b_vp);
		} else if (p) {
			++p->p_stats->p_ru.ru_oublock;
		}
		brelse(bp);
		return (rtval);
	} 

	return (0);
}

/*
E 133
 * nfs special file access vnode op.
 * Essentially just get vattr and then imitate iaccess() since the device is
 * local to the client.
 */
int
nfsspec_access(ap)
	struct vop_access_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	register struct vattr *vap;
	register gid_t *gp;
	register struct ucred *cred = ap->a_cred;
I 135
	struct vnode *vp = ap->a_vp;
E 135
	mode_t mode = ap->a_mode;
	struct vattr vattr;
	register int i;
	int error;

	/*
I 135
	 * Disallow write attempts on filesystems mounted read-only;
	 * unless the file is a socket, fifo, or a block or character
	 * device resident on the filesystem.
	 */
	if ((mode & VWRITE) && (vp->v_mount->mnt_flag & MNT_RDONLY)) {
		switch (vp->v_type) {
		case VREG: case VDIR: case VLNK:
			return (EROFS);
		}
	}
	/*
E 135
	 * If you're the super-user,
	 * you always get access.
	 */
	if (cred->cr_uid == 0)
		return (0);
	vap = &vattr;
D 133
	if (error = VOP_GETATTR(ap->a_vp, vap, cred, ap->a_p))
E 133
I 133
D 135
	error = VOP_GETATTR(ap->a_vp, vap, cred, ap->a_p);
E 135
I 135
	error = VOP_GETATTR(vp, vap, cred, ap->a_p);
E 135
	if (error)
E 133
		return (error);
	/*
	 * Access check is based on only one of owner, group, public.
	 * If not owner, then check group. If not a member of the
	 * group, then check public access.
	 */
	if (cred->cr_uid != vap->va_uid) {
		mode >>= 3;
		gp = cred->cr_groups;
		for (i = 0; i < cred->cr_ngroups; i++, gp++)
			if (vap->va_gid == *gp)
				goto found;
		mode >>= 3;
found:
		;
	}
D 109
	if ((vap->va_mode & mode) != 0)
		return (0);
	return (EACCES);
E 109
I 109
D 133
	return ((vap->va_mode & mode) == mode ? 0 : EACCES);
E 133
I 133
	error = (vap->va_mode & mode) == mode ? 0 : EACCES;
	return (error);
E 133
E 109
E 102
E 63
E 24
E 17
}
I 86

/*
 * Read wrapper for special devices.
 */
int
nfsspec_read(ap)
D 94
	struct vop_read_args *ap;
E 94
I 94
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 94
{
D 99
	extern int (**spec_vnodeop_p)();
E 99
I 90
	register struct nfsnode *np = VTONFS(ap->a_vp);
E 90

	/*
	 * Set access flag.
	 */
D 90
	VTONFS(ap->a_vp)->n_flag |= NACC;
E 90
I 90
	np->n_flag |= NACC;
D 133
	np->n_atim = time;
E 133
I 133
	np->n_atim.ts_sec = time.tv_sec;
	np->n_atim.ts_nsec = time.tv_usec * 1000;
E 133
E 90
	return (VOCALL(spec_vnodeop_p, VOFFSET(vop_read), ap));
}

/*
 * Write wrapper for special devices.
 */
int
nfsspec_write(ap)
D 94
	struct vop_write_args *ap;
E 94
I 94
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 94
{
D 99
	extern int (**spec_vnodeop_p)();
E 99
I 90
	register struct nfsnode *np = VTONFS(ap->a_vp);
E 90

	/*
D 90
	 * Set update flags.
E 90
I 90
	 * Set update flag.
E 90
	 */
D 90
	VTONFS(ap->a_vp)->n_flag |= NUPD;
E 90
I 90
	np->n_flag |= NUPD;
D 133
	np->n_mtim = time;
E 133
I 133
	np->n_mtim.ts_sec = time.tv_sec;
	np->n_mtim.ts_nsec = time.tv_usec * 1000;
E 133
E 90
	return (VOCALL(spec_vnodeop_p, VOFFSET(vop_write), ap));
}

/*
 * Close wrapper for special devices.
 *
 * Update the times on the nfsnode then do device close.
 */
int
nfsspec_close(ap)
D 94
	struct vop_close_args *ap;
E 94
I 94
	struct vop_close_args /* {
		struct vnode *a_vp;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 94
{
D 94
	USES_VOP_SETATTR;
E 94
D 89
	register struct nfsnode *np = VTONFS(ap->a_vp);
E 89
I 89
	register struct vnode *vp = ap->a_vp;
	register struct nfsnode *np = VTONFS(vp);
E 89
	struct vattr vattr;
D 99
	extern int (**spec_vnodeop_p)();
E 99

	if (np->n_flag & (NACC | NUPD)) {
D 101
		if (np->n_flag & NACC)
			np->n_atim = time;
		if (np->n_flag & NUPD)
			np->n_mtim = time;
E 101
		np->n_flag |= NCHG;
D 89
		if (ap->a_vp->v_usecount == 1 &&
		    (ap->a_vp->v_mount->mnt_flag & MNT_RDONLY) == 0) {
E 89
I 89
		if (vp->v_usecount == 1 &&
		    (vp->v_mount->mnt_flag & MNT_RDONLY) == 0) {
E 89
			VATTR_NULL(&vattr);
D 92
			if (np->n_flag & NACC)
				vattr.va_atime = np->n_atim;
			if (np->n_flag & NUPD)
				vattr.va_mtime = np->n_mtim;
E 92
I 92
D 133
			if (np->n_flag & NACC) {
				vattr.va_atime.ts_sec = np->n_atim.tv_sec;
				vattr.va_atime.ts_nsec =
				    np->n_atim.tv_usec * 1000;
			}
			if (np->n_flag & NUPD) {
				vattr.va_mtime.ts_sec = np->n_mtim.tv_sec;
				vattr.va_mtime.ts_nsec =
				    np->n_mtim.tv_usec * 1000;
			}
E 133
I 133
			if (np->n_flag & NACC)
				vattr.va_atime = np->n_atim;
			if (np->n_flag & NUPD)
				vattr.va_mtime = np->n_mtim;
E 133
E 92
D 89
			(void)VOP_SETATTR(ap->a_vp, &vattr, ap->a_cred,
			    ap->a_p);
E 89
I 89
			(void)VOP_SETATTR(vp, &vattr, ap->a_cred, ap->a_p);
E 89
		}
	}
	return (VOCALL(spec_vnodeop_p, VOFFSET(vop_close), ap));
}

D 133
#ifdef FIFO
E 133
/*
 * Read wrapper for fifos.
 */
int
nfsfifo_read(ap)
D 94
	struct vop_read_args *ap;
E 94
I 94
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 94
{
	extern int (**fifo_vnodeop_p)();
I 90
	register struct nfsnode *np = VTONFS(ap->a_vp);
E 90

	/*
	 * Set access flag.
	 */
D 90
	VTONFS(ap->a_vp)->n_flag |= NACC;
E 90
I 90
	np->n_flag |= NACC;
D 133
	np->n_atim = time;
E 133
I 133
	np->n_atim.ts_sec = time.tv_sec;
	np->n_atim.ts_nsec = time.tv_usec * 1000;
E 133
E 90
	return (VOCALL(fifo_vnodeop_p, VOFFSET(vop_read), ap));
}

/*
 * Write wrapper for fifos.
 */
int
nfsfifo_write(ap)
D 94
	struct vop_write_args *ap;
E 94
I 94
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 94
{
	extern int (**fifo_vnodeop_p)();
I 90
	register struct nfsnode *np = VTONFS(ap->a_vp);
E 90

	/*
	 * Set update flag.
	 */
D 90
	VTONFS(ap->a_vp)->n_flag |= NUPD;
E 90
I 90
	np->n_flag |= NUPD;
D 133
	np->n_mtim = time;
E 133
I 133
	np->n_mtim.ts_sec = time.tv_sec;
	np->n_mtim.ts_nsec = time.tv_usec * 1000;
E 133
E 90
	return (VOCALL(fifo_vnodeop_p, VOFFSET(vop_write), ap));
}

/*
 * Close wrapper for fifos.
 *
 * Update the times on the nfsnode then do fifo close.
 */
int
nfsfifo_close(ap)
D 94
	struct vop_close_args *ap;
E 94
I 94
	struct vop_close_args /* {
		struct vnode *a_vp;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 94
{
D 94
	USES_VOP_SETATTR;
E 94
D 89
	register struct nfsnode *np = VTONFS(ap->a_vp);
E 89
I 89
	register struct vnode *vp = ap->a_vp;
	register struct nfsnode *np = VTONFS(vp);
E 89
	struct vattr vattr;
	extern int (**fifo_vnodeop_p)();

	if (np->n_flag & (NACC | NUPD)) {
D 133
		if (np->n_flag & NACC)
			np->n_atim = time;
		if (np->n_flag & NUPD)
			np->n_mtim = time;
E 133
I 133
		if (np->n_flag & NACC) {
			np->n_atim.ts_sec = time.tv_sec;
			np->n_atim.ts_nsec = time.tv_usec * 1000;
		}
		if (np->n_flag & NUPD) {
			np->n_mtim.ts_sec = time.tv_sec;
			np->n_mtim.ts_nsec = time.tv_usec * 1000;
		}
E 133
		np->n_flag |= NCHG;
D 89
		if (ap->a_vp->v_usecount == 1 &&
		    (ap->a_vp->v_mount->mnt_flag & MNT_RDONLY) == 0) {
E 89
I 89
		if (vp->v_usecount == 1 &&
		    (vp->v_mount->mnt_flag & MNT_RDONLY) == 0) {
E 89
			VATTR_NULL(&vattr);
D 92
			if (np->n_flag & NACC)
				vattr.va_atime = np->n_atim;
			if (np->n_flag & NUPD)
				vattr.va_mtime = np->n_mtim;
E 92
I 92
D 133
			if (np->n_flag & NACC) {
				vattr.va_atime.ts_sec = np->n_atim.tv_sec;
				vattr.va_atime.ts_nsec =
				    np->n_atim.tv_usec * 1000;
			}
			if (np->n_flag & NUPD) {
				vattr.va_mtime.ts_sec = np->n_mtim.tv_sec;
				vattr.va_mtime.ts_nsec =
				    np->n_mtim.tv_usec * 1000;
			}
E 133
I 133
			if (np->n_flag & NACC)
				vattr.va_atime = np->n_atim;
			if (np->n_flag & NUPD)
				vattr.va_mtime = np->n_mtim;
E 133
E 92
D 89
			(void)VOP_SETATTR(ap->a_vp, &vattr, ap->a_cred,
			    ap->a_p);
E 89
I 89
			(void)VOP_SETATTR(vp, &vattr, ap->a_cred, ap->a_p);
E 89
		}
	}
	return (VOCALL(fifo_vnodeop_p, VOFFSET(vop_close), ap));
}
D 133
#endif /* FIFO */
E 133
E 86
I 82
D 84
#undef vp
#undef ta
#undef tm
#undef waitfor
E 84
E 82
E 1
