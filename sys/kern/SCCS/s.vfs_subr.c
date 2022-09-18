h02029
s 00001/00001/01755
d D 8.31 95/05/26 15:19:45 mckusick 143 142
c vnode_free_list_slock has to be exported for LFS
e
s 00074/00008/01682
d D 8.30 95/05/22 23:00:35 mckusick 142 141
c make provision for shared access locks on vnodes not otherwise
c doing underlying locking
e
s 00061/00070/01629
d D 8.29 95/05/20 01:21:23 mckusick 141 140
c merge vfs_lock and vfs_busy; interlock mount points properly
e
s 00001/00001/01698
d D 8.28 95/05/19 15:07:40 pendry 140 139
c need to pass proc to vinvalbuf
e
s 00006/00002/01693
d D 8.27 95/05/18 16:07:56 mckusick 139 138
c delete reference if vget lock attempt fails
e
s 00001/00001/01694
d D 8.26 95/05/17 22:26:38 mckusick 138 137
c if mountroot != NULL, then just call it
e
s 00025/00002/01670
d D 8.25 95/05/17 11:43:35 pendry 137 136
c expand vput inline so that locking is managed properly
e
s 00297/00092/01375
d D 8.24 95/05/14 00:17:30 mckusick 136 135
c massive overhaul to use new lock manager;
c add vrecycle and vop_nolock* functions
e
s 00066/00002/01401
d D 8.23 95/05/10 13:27:09 mckusick 135 134
c add vfs_mountroot and vfs_rootmountalloc functions; 
c bdevvp always indicates when it fails
e
s 00003/00003/01400
d D 8.22 95/05/10 11:18:41 pendry 134 133
c VOP_REVOKE(vp, 0) should really be vgone(vp)
e
s 00025/00007/01378
d D 8.21 95/05/09 16:59:25 mckusick 133 132
c change mountlist to CIRCLEQ so we can do unmountall (from mycroft)
e
s 00015/00003/01370
d D 8.20 95/05/01 21:11:10 mckusick 132 131
c silently accept multiple instances of the same address in vfs_hang_addrlist
e
s 00001/00000/01372
d D 8.19 95/04/11 16:43:21 mckusick 131 130
c have to purge v_id as soon as it is cleaned
e
s 00050/00004/01322
d D 8.18 95/03/30 14:10:22 mckusick 130 129
c add vfs_sysctl
e
s 00003/00002/01323
d D 8.17 95/03/24 09:27:21 mckusick 129 128
c only remove from special device list if it is on one
e
s 00015/00010/01310
d D 8.16 95/02/23 12:16:42 mckusick 128 127
c convert vgoneall to vop_revoke
e
s 00048/00025/01272
d D 8.15 95/02/14 10:44:13 cgd 127 126
c light cleanup, return types, KNF, etc.
e
s 00001/00000/01296
d D 8.14 95/01/09 18:22:35 cgd 126 125
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00014/00007/01282
d D 8.13 94/04/18 17:46:40 mckusick 125 124
c avoid race between vget and getnewvnode (from Hibler)
e
s 00005/00004/01284
d D 8.12 94/04/11 16:06:28 mckusick 124 123
c don't vgone the vnode in vcount if it is ours
e
s 00001/00001/01287
d D 8.11 94/03/28 08:04:51 bostic 123 122
c lint
e
s 00006/00001/01282
d D 8.10 94/03/21 16:35:08 hibler 122 121
c detect a suspected vget race with getnewvnode (and panic)
e
s 00005/00000/01278
d D 8.9 94/01/21 17:18:10 bostic 121 120
c add USL's copyright notice
e
s 00002/00001/01276
d D 8.8 94/01/14 15:06:46 hibler 120 119
c correctly init v_ralen and v_maxra
e
s 00193/00000/01084
d D 8.7 94/01/12 15:41:58 hibler 119 117
c move export code from ufs layer to here (for other local FSes),
c #ifdef DIAGNOSTIC for some debug,
c init vnode fields for clustering.
e
s 00047/00002/01082
d D 8.6.1.1 94/01/11 23:29:30 mckusick 118 117
c debugging the new list code
e
s 00000/00001/01084
d D 8.6 94/01/06 22:46:50 mckusick 117 116
c NOLIST moves to buf.h so it can be used for initialization
e
s 00001/00004/01084
d D 8.5 94/01/05 11:16:19 mckusick 116 115
c lint (unused variables)
e
s 00002/00002/01086
d D 8.4 94/01/05 10:42:09 pendry 115 114
c use filesystem type as basis for major number in fsid
e
s 00016/00004/01072
d D 8.3 94/01/05 10:26:52 mckusick 114 113
c cannot bump reference count until after calling vgone (to avoid
c having vgone incorrectly trying to close the previous object)
e
s 00073/00109/01003
d D 8.2 93/12/30 16:30:29 mckusick 113 112
c new queue structure; vget now locks optionally
e
s 00002/00002/01110
d D 8.1 93/06/10 22:00:48 bostic 112 111
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/01107
d D 7.100 93/06/01 19:40:46 mckusick 111 110
c add busyprt to sysctl debug
e
s 00002/00002/01106
d D 7.99 93/04/28 18:58:01 mckusick 110 109
c vfinddev returns 1 for success
e
s 00004/00002/01104
d D 7.98 93/04/28 14:47:26 mckusick 109 108
c panic when vref is used on zero ref count vnodes
e
s 00001/00001/01105
d D 7.97 93/03/08 10:28:06 bostic 108 107
c rename va_cflags -> va_vaflags
e
s 00001/00000/01105
d D 7.96 93/03/05 17:23:36 bostic 107 106
c make utime(NULL) work for POSIX 1003.1 compatibility
e
s 00001/00001/01104
d D 7.95 93/03/04 17:58:34 bostic 106 105
c change buffer lengths of sysctl(2) to be size_t's
e
s 00012/00015/01093
d D 7.94 93/02/04 01:12:33 mckusick 105 104
c kinfo_vnode becomes sysctl_vnode
e
s 00001/00000/01107
d D 7.93 93/02/03 09:55:30 mckusick 104 103
c clear B_WRITEINPROG
e
s 00017/00004/01090
d D 7.92 93/02/02 15:33:23 mckusick 103 102
c update for 4.4BSD from Rick Macklem
e
s 00015/00001/01079
d D 7.91 92/12/09 16:01:01 margo 102 101
c add read/write cluster field initialization
e
s 00008/00000/01072
d D 7.90 92/12/09 15:28:33 mckusick 101 100
c only vgone vnodes open for writing when downgrading read-write
c filesystems to read-only
e
s 00003/00002/01069
d D 7.89 92/12/01 13:25:00 mckusick 100 99
c only move vnode to front of list when not already there
e
s 00021/00044/01050
d D 7.88 92/11/14 23:27:01 mckusick 99 98
c cannot put in deadops until done with reclaiming, thus all lock
c implementations must check for VXLOCK as well as their own
e
s 00022/00032/01072
d D 7.87 92/10/22 17:26:44 mckusick 98 97
c use new queue primitives
e
s 00015/00013/01089
d D 7.86 92/10/07 17:22:58 margo 97 96
c Pass flags to vinvalbuf so it can optionally keep indirect blocks.
e
s 00000/00001/01102
d D 7.85 92/07/25 20:48:46 mckusick 96 95
c spec_vnodeops_p now declared in specdev.h
e
s 00006/00014/01097
d D 7.84 92/07/21 01:02:57 mckusick 95 94
c speedups
e
s 00002/00001/01109
d D 7.83 92/07/12 16:19:29 pendry 94 93
c new include location of specdev.h
e
s 00004/00013/01106
d D 7.82 92/07/03 01:39:21 mckusick 93 92
c delete USES; declare vop_*_args for vclean
e
s 00018/00120/01101
d D 7.81 92/06/25 13:06:50 mckusick 92 91
c delete mntflushbuf, mntinvalbuf, and vflushbuf; 
c vinvalbuf now uses VOP_FSYNC to actually flush the buffers
e
s 00007/00008/01214
d D 7.80 92/06/23 20:31:48 mckusick 91 88
c timeval => timespec; lint; be more lenient about allocating new vnodes
e
s 00005/00000/01226
d R 7.81 92/06/23 00:09:18 bostic 90 89
c LFS unmount code; vinvalbuf should be a VOP?
e
s 00013/00009/01213
d R 7.80 92/06/22 22:14:37 mckusick 89 88
c checked in for Kirk by TK
e
s 00005/00003/01217
d D 7.79 92/06/05 16:16:02 pendry 88 87
c only call getvfs in getnewfsid when rootfs has been defined
e
s 00026/00000/01194
d D 7.78 92/06/03 00:15:32 pendry 87 86
c added getnewfsid: global fsid allocator.
e
s 00002/00001/01192
d D 7.77 92/06/02 21:17:25 mckusick 86 85
c avoid null arguments
e
s 00032/00011/01161
d D 7.76 92/05/15 12:24:16 heideman 85 84
c vclean cleaned up for new vn_if
e
s 00019/00005/01153
d D 7.75 92/05/14 17:36:12 heideman 84 80
c vnode interface conversion
e
s 00019/00005/01153
d R 7.75 92/05/14 15:52:28 heideman 83 80
c vnode interface conversion
e
s 00019/00005/01153
d R 7.75 92/05/14 14:54:59 heideman 82 80
c vnode interface conversion
e
s 00019/00005/01153
d R 7.75 92/05/14 12:59:44 heideman 81 80
c vnode interface conversion
e
s 00001/00001/01157
d D 7.74 92/05/14 12:39:55 heideman 80 77
c vpos param of getnewvnode changed type
e
s 00019/00005/01153
d R 7.74 92/05/14 11:57:33 heideman 79 77
c vnode interface conversion
e
s 00019/00005/01153
d R 7.74 92/05/14 10:37:30 heideman 78 77
c vnode interface conversion
e
s 00002/00024/01156
d D 7.73 92/05/14 10:22:06 heideman 77 73
c vfs initialization code moved to vfs_init.c
e
s 00019/00005/01175
d R 7.73 92/05/13 23:16:39 heideman 76 73
c vnode interface conversion
e
s 00019/00005/01175
d R 7.73 92/05/13 19:01:29 heideman 75 73
c vnode interface conversion
e
s 00019/00005/01175
d R 7.73 92/05/13 18:33:37 heideman 74 73
c vnode interface conversion
e
s 00002/00001/01178
d D 7.72 92/05/13 18:08:50 heideman 73 72
c minor syntax change before vnode interface conversion
e
s 00002/00002/01177
d D 7.71 92/05/04 15:44:12 mckusick 72 71
c lint
e
s 00004/00002/01175
d D 7.70 92/02/25 12:33:36 mckusick 71 70
c may get null vp to reassignbuf during shutdown
e
s 00006/00005/01171
d D 7.69 92/02/05 23:22:13 torek 70 69
c minor cleanups
e
s 00010/00000/01166
d D 7.68 92/02/05 23:16:58 mckusick 69 67
c move IFMT => VTYPE and VTYPE => IFMT to vnode since stat requires it
e
s 00010/00000/01166
d D 7.67.1.1 92/02/03 23:41:22 mckusick 68 67
c together with vfs_syscalls.c add reference checking
e
s 00001/00014/01165
d D 7.67 92/02/03 23:38:50 mckusick 67 66
c get rid of debugging; zero out v_mount when recycling vnodes
e
s 00014/00000/01165
d D 7.66 92/01/22 09:37:18 heideman 66 65
c lookup converted to new form
e
s 00001/00000/01164
d D 7.65 92/01/14 12:21:22 mckusick 65 64
c init lease
e
s 00002/00000/01162
d D 7.64 91/12/19 12:29:55 mckusick 64 63
c add panic for uncleaned vnode private areas
e
s 00006/00003/01156
d D 7.63 91/12/19 12:29:07 mckusick 63 62
c reorder vattr_null to avoid bugs in GCC quad's
e
s 00002/00003/01157
d D 7.62 91/11/05 15:41:07 mckusick 62 61
c reorganization to move ufsmount ops to be vnode ops; 
c gets rid of XXX in previous delta
e
s 00014/00013/01146
d D 7.61 91/11/01 16:44:11 bostic 61 60
c LFS version 1; XXX vinvalbuf is wrong!
e
s 00011/00004/01148
d D 7.60 91/06/21 10:45:05 mckusick 60 59
c panic if v_writecount is non-zero on last use; print out writecount in vprint
e
s 00018/00031/01134
d D 7.59 91/06/03 17:41:03 mckusick 59 58
c tighten up linked list management
e
s 00004/00004/01161
d D 7.58 91/05/16 19:01:46 mckusick 58 57
c change vn_ to vop_ (for marc :-)
e
s 00000/00037/01165
d D 7.57 91/05/15 19:36:28 mckusick 57 56
c delete nddup, ndrele, ndinit
e
s 00021/00000/01181
d D 7.56 91/05/12 16:51:48 mckusick 56 55
c add code for printing locked vnodes
e
s 00003/00005/01178
d D 7.55 91/05/08 21:42:09 mckusick 55 54
c update from Rick Macklem for race condition in NFS
e
s 00272/00000/00911
d D 7.54 91/05/06 14:36:16 mckusick 54 53
c more uncontaminated code from vfs_bio.c to vfs_subr.c
e
s 00001/00001/00910
d D 7.53 91/04/19 15:20:22 mckusick 53 52
c pass in IO_NDELAY to close in vgone/vclean
e
s 00006/00003/00905
d D 7.52 91/04/15 23:56:40 mckusick 52 51
c add proc pointers to appropriate VOP operations
e
s 00002/00000/00906
d D 7.51 91/03/04 22:53:37 mckusick 51 50
c misc fixes plus diskless support from Rick Macklem
e
s 00000/00008/00906
d D 7.50 91/02/01 16:22:24 mckusick 50 49
c add POSIX-style byte-level record locking
e
s 00000/00008/00914
d D 7.49 91/01/10 23:44:05 mckusick 49 48
c add dynamically allocated file descriptors
e
s 00006/00005/00916
d D 7.48 90/08/24 10:02:14 mckusick 48 47
c lint
e
s 00001/00011/00920
d D 7.47 90/06/28 21:26:31 bostic 47 46
c new copyright notice
e
s 00001/00000/00930
d D 7.46 90/05/16 20:06:59 mckusick 46 45
c have to initialize v_specflags
e
s 00006/00019/00924
d D 7.45 90/05/05 17:11:07 mckusick 45 44
c do not lock vnodes when copying for kinfo (if the info changes, who cares)
e
s 00014/00014/00929
d D 7.44 90/05/05 17:07:46 mckusick 44 43
c have to check that vnode is still associated with mount point before using it
e
s 00002/00002/00941
d D 7.43 90/05/05 16:28:13 mckusick 43 42
c have to check MNT_UNMOUNT flag after sleeping, not before
e
s 00038/00038/00905
d D 7.42 90/05/04 20:55:39 mckusick 42 41
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00002/00000/00941
d D 7.41 90/05/03 18:45:35 mckusick 41 40
c declare and initialize va_null for VATTR_NULL
e
s 00065/00014/00876
d D 7.40 90/05/02 19:18:23 mckusick 40 39
c add vfs_busy/vfs_unbusy to single thread access to mount points
c and avoid races with unmount; add SKIPSYSTEM to vflush to avoid quota files;
c define the flags to vflush and vclean; define new flags in vprint;
c use vfs_busy in kinfo_vnode
e
s 00074/00000/00816
d D 7.39 90/04/27 15:55:57 marc 39 38
c add kinfo_vnode to copyout vnodes
e
s 00027/00038/00789
d D 7.38 90/04/10 20:34:19 mckusick 38 37
c dynamic allocation of vnodes
e
s 00002/00000/00825
d D 7.37 90/03/29 18:15:13 mckusick 37 36
c have to reset vfreet when removing the last vnode
e
s 00029/00007/00796
d D 7.36 90/03/29 17:53:04 mckusick 36 35
c protect vgoneall from other vgone's
e
s 00001/00014/00802
d D 7.35 90/03/27 19:00:08 mckusick 35 34
c break specinfo structure out of vnode.h into specdev.h
e
s 00002/00002/00814
d D 7.34 90/03/27 15:37:48 mckusick 34 33
c va_size and va_bytes become quads
e
s 00005/00005/00811
d D 7.33 90/03/27 15:32:12 mckusick 33 32
c do not release vnode until done creating its alias
e
s 00009/00000/00807
d D 7.32 90/03/19 16:29:21 mckusick 32 31
c vgone has to avoid reentry
e
s 00002/00002/00805
d D 7.31 90/03/06 23:25:56 mckusick 31 30
c m_fsid is now found in m_stat.f_fsid
e
s 00001/00001/00806
d D 7.30 90/03/05 18:08:37 mckusick 30 29
c add VFIFO vnode type
e
s 00006/00000/00801
d D 7.29 90/02/19 16:47:26 mckusick 29 28
c move definitions out of vnode.h
e
s 00000/00010/00801
d D 7.28 90/02/16 11:32:52 marc 28 27
c strcat moves to kern_subr.c
e
s 00003/00002/00808
d D 7.27 90/02/16 11:31:49 mckusick 27 26
c have to check both the device AND the type
e
s 00002/00001/00808
d D 7.26 90/02/09 16:06:22 mckusick 26 25
c have to check type, not just device number
e
s 00002/00000/00807
d D 7.25 90/01/19 18:13:29 mckusick 25 24
c additional initialization needed for 7.24
e
s 00001/00001/00806
d D 7.24 90/01/19 14:53:09 mckusick 24 23
c cannot skip vgone when recycling VNON vnodes
e
s 00034/00001/00773
d D 7.23 90/01/15 18:40:53 mckusick 23 22
c print out flag values in vprint
e
s 00019/00000/00755
d D 7.22 89/12/31 15:28:42 mckusick 22 21
c add vfinddev to yield a device vnode from its dev
e
s 00051/00031/00704
d D 7.21 89/12/30 22:33:32 mckusick 21 20
c v_count => v_usecount; v_lastr is being used; v_mounton is gone;
c routines for vhold and holdrele; use v_hashchain
e
s 00001/00001/00734
d D 7.20 89/12/19 14:53:01 mckusick 20 19
c ni_segflg => ni_uioseg (fromgmf@osf.org)
e
s 00036/00013/00699
d D 7.19 89/11/30 22:42:05 mckusick 19 18
c add vprint routine; semantic cleanups to vgone; use vprintf
e
s 00001/00000/00711
d D 7.18 89/11/25 23:32:03 mckusick 18 17
c vclean is local to this file
e
s 00053/00004/00658
d D 7.17 89/11/25 23:25:25 mckusick 17 16
c optimize alias lookup in checkalias; 
c add vgoneall to eliminate all vnodes associated with a device; 
c add vcount to count the total number of references to a device
e
s 00003/00002/00659
d D 7.16 89/11/25 21:34:42 mckusick 16 15
c set v_mount in insmntque; unlock if keeping aliased vnode
e
s 00061/00030/00600
d D 7.15 89/11/25 15:19:25 mckusick 15 14
c set up separate specinfo structure; allow aliased vnodes
e
s 00002/00001/00628
d D 7.14 89/11/10 18:51:07 mckusick 14 13
c must set vnode type to VNON after reassigning it
e
s 00059/00001/00570
d D 7.13 89/11/10 12:35:41 mckusick 13 12
c generalize iflush into vflush; first cut at support for forcible unmount
e
s 00001/00002/00570
d D 7.12 89/11/03 15:05:15 mckusick 12 11
c lint
e
s 00026/00011/00546
d D 7.11 89/11/02 17:35:52 mckusick 11 10
c vclean optionally can close a vnode
e
s 00002/00002/00555
d D 7.10 89/10/30 00:07:53 mckusick 10 9
c blk_vnodeops => spec_vnodeops
e
s 00237/00028/00320
d D 7.9 89/10/29 23:25:17 mckusick 9 8
c implement file system initialization; ensure that the vnode is locked
c while the old file system type is being cleaned out; maintain an alias
c list for all block and character special devices
e
s 00184/00000/00164
d D 7.8 89/10/24 20:06:07 mckusick 8 7
c merge inode and nfsnode tables into a single vnode table;
c link together all vnodes associated with a particular mount point
e
s 00000/00050/00164
d D 7.7 89/10/19 00:08:08 mckusick 7 6
c vfs_add gets selectively expanded inline
e
s 00004/00002/00210
d D 7.6 89/09/05 23:12:22 mckusick 6 5
c vfs_lock really locks now
e
s 00002/00002/00210
d D 7.5 89/06/27 19:26:53 mckusick 5 4
c update reference counts on vnodes using VREF
e
s 00006/00004/00206
d D 7.4 89/06/24 13:04:12 mckusick 4 3
c fix from Rick Macklem to avoid infinite loop for stale handles
e
s 00047/00000/00163
d D 7.3 89/06/08 13:41:05 mckusick 3 2
c management routines for nameidata (ndinit, nddup, and ndrele)
e
s 00002/00001/00161
d D 7.2 89/06/07 16:56:22 mckusick 2 1
c initialize flags and generation number in vattr structure
e
s 00162/00000/00000
d D 7.1 89/04/24 20:39:01 mckusick 1 0
c first bootable vnodes
e
u
U
f b 
t
T
I 1
/*
D 112
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 112
I 112
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 121
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 121
E 112
 *
D 47
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
E 47
I 47
 * %sccs.include.redist.c%
E 47
 *
 *	%W% (Berkeley) %G%
 */

/*
 * External virtual filesystem routines
 */

D 61
#include "param.h"
I 52
#include "proc.h"
E 52
#include "mount.h"
#include "time.h"
#include "vnode.h"
I 35
#include "specdev.h"
E 35
I 3
#include "namei.h"
#include "ucred.h"
I 54
#include "buf.h"
E 54
E 3
#include "errno.h"
I 9
#include "malloc.h"
E 61
I 61
#include <sys/param.h>
I 87
#include <sys/systm.h>
E 87
#include <sys/proc.h>
#include <sys/mount.h>
#include <sys/time.h>
#include <sys/vnode.h>
I 69
#include <sys/stat.h>
E 69
D 94
#include <sys/specdev.h>
E 94
#include <sys/namei.h>
#include <sys/ucred.h>
#include <sys/buf.h>
#include <sys/errno.h>
#include <sys/malloc.h>
I 119
#include <sys/domain.h>
#include <sys/mbuf.h>
E 119
I 94

I 111
#include <vm/vm.h>
#include <sys/sysctl.h>

E 111
#include <miscfs/specfs/specdev.h>
E 94
I 69

enum vtype iftovt_tab[16] = {
	VNON, VFIFO, VCHR, VNON, VDIR, VNON, VBLK, VNON,
	VREG, VNON, VLNK, VNON, VSOCK, VNON, VNON, VBAD,
};
int	vttoif_tab[9] = {
	0, S_IFREG, S_IFDIR, S_IFBLK, S_IFCHR, S_IFLNK,
	S_IFSOCK, S_IFIFO, S_IFMT,
};
E 69
E 61
E 9

/*
I 98
 * Insq/Remq for the vnode usage lists.
 */
D 113
#define	bufinsvn(bp, dp)	list_enter_head(dp, bp, struct buf *, b_vnbufs)
#define	bufremvn(bp)		list_remove(bp, struct buf *, b_vnbufs)
E 113
I 113
D 117
#define NOLIST ((struct buf *)0x87654321)
E 117
#define	bufinsvn(bp, dp)	LIST_INSERT_HEAD(dp, bp, b_vnbufs)
D 127
#define	bufremvn(bp) {  \
	LIST_REMOVE(bp, b_vnbufs); \
	(bp)->b_vnbufs.le_next = NOLIST; \
E 127
I 127
#define	bufremvn(bp) {							\
	LIST_REMOVE(bp, b_vnbufs);					\
	(bp)->b_vnbufs.le_next = NOLIST;				\
E 127
}
E 113
D 127

E 127
I 113
TAILQ_HEAD(freelst, vnode) vnode_free_list;	/* vnode free list */
struct mntlist mountlist;			/* mounted filesystem list */
I 141
struct simplelock mountlist_slock;
E 141
I 136
static struct simplelock mntid_slock;
struct simplelock mntvnode_slock;
I 143
struct simplelock vnode_free_list_slock;
E 143
static struct simplelock spechash_slock;
D 143
static struct simplelock vnode_free_list_slock;
E 143
E 136

E 113
/*
E 98
I 29
D 35
 * Shorthand notation.
 */
#define v_hashchain v_specinfo->si_hashchain
#define v_specnext v_specinfo->si_specnext

/*
E 35
E 29
D 7
 * Add a new mount point to the list of mounted filesystems.
 * Lock the filesystem so that namei will not cross into the
 * the tree below the covered vnode.
 */
vfs_add(mountedvp, mp, flags)
	register struct vnode *mountedvp;
	register struct mount *mp;
	int flags;
{
	register int error;

	error = vfs_lock(mp);
	if (error)
		return (error);
	if (mountedvp == (struct vnode *)0) {
		/*
		 * We are mounting the root filesystem.
		 */
		rootfs = mp;
		mp->m_next = mp;
		mp->m_prev = mp;
	} else {
		if (mountedvp->v_mountedhere != (struct mount *)0) {
			vfs_unlock(mp);
			return(EBUSY);
		}
		/*
		 * Put the new filesystem on the mount list after root.
		 */
		mp->m_next = rootfs->m_next;
		mp->m_prev = rootfs;
		rootfs->m_next = mp;
		mp->m_next->m_prev = mp;
		mountedvp->v_mountedhere = mp;
	}
	mp->m_vnodecovered = mountedvp;
	if (flags & M_RDONLY) {
		mp->m_flag |= M_RDONLY;
	} else {
		mp->m_flag &= ~M_RDONLY;
	}
	if (flags & M_NOSUID) {
		mp->m_flag |= M_NOSUID;
	} else {
		mp->m_flag &= ~M_NOSUID;
	}
	return (0);
}

/*
E 7
D 113
 * Remove a mount point from the list of mounted filesystems.
 * Unmount of the root is illegal.
E 113
I 113
 * Initialize the vnode management data structures.
E 113
 */
I 127
void
E 127
D 113
void
vfs_remove(mp)
	register struct mount *mp;
E 113
I 113
vntblinit()
E 113
{

I 136
	simple_lock_init(&mntvnode_slock);
	simple_lock_init(&mntid_slock);
	simple_lock_init(&spechash_slock);
E 136
D 113
	if (mp == rootfs)
		panic("vfs_remove: unmounting root");
D 42
	mp->m_prev->m_next = mp->m_next;
	mp->m_next->m_prev = mp->m_prev;
	mp->m_vnodecovered->v_mountedhere = (struct mount *)0;
E 42
I 42
	mp->mnt_prev->mnt_next = mp->mnt_next;
	mp->mnt_next->mnt_prev = mp->mnt_prev;
	mp->mnt_vnodecovered->v_mountedhere = (struct mount *)0;
E 42
	vfs_unlock(mp);
E 113
I 113
	TAILQ_INIT(&vnode_free_list);
I 136
	simple_lock_init(&vnode_free_list_slock);
E 136
D 133
	TAILQ_INIT(&mountlist);
E 133
I 133
	CIRCLEQ_INIT(&mountlist);
E 133
E 113
}

/*
D 141
 * Lock a filesystem.
 * Used to prevent access to it while mounting and unmounting.
E 141
I 141
 * Mark a mount point as busy. Used to synchronize access and to delay
 * unmounting. Interlock is not released on failure.
E 141
 */
I 127
int
E 127
D 141
vfs_lock(mp)
	register struct mount *mp;
E 141
I 141
vfs_busy(mp, flags, interlkp, p)
	struct mount *mp;
	int flags;
	struct simplelock *interlkp;
	struct proc *p;
E 141
{
I 141
	int lkflags;
E 141

D 6
	if (mp->m_flag & M_MLOCK)
		return (EBUSY);
E 6
I 6
D 42
	while(mp->m_flag & M_MLOCK) {
		mp->m_flag |= M_MWAIT;
E 42
I 42
D 127
	while(mp->mnt_flag & MNT_MLOCK) {
E 127
I 127
D 141
	while (mp->mnt_flag & MNT_MLOCK) {
E 141
I 141
	if (mp->mnt_flag & MNT_UNMOUNT) {
		if (flags & LK_NOWAIT)
			return (ENOENT);
E 141
E 127
		mp->mnt_flag |= MNT_MWAIT;
I 142
		if (interlkp)
			simple_unlock(interlkp);
		/*
		 * Since all busy locks are shared except the exclusive
		 * lock granted when unmounting, the only place that a
		 * wakeup needs to be done is at the release of the
		 * exclusive lock at the end of dounmount.
		 */
E 142
E 42
D 127
		sleep((caddr_t)mp, PVFS);
E 127
I 127
D 141
		tsleep((caddr_t)mp, PVFS, "vfslock", 0);
E 141
I 141
		sleep((caddr_t)mp, PVFS);
I 142
		if (interlkp)
			simple_lock(interlkp);
E 142
		return (ENOENT);
E 141
E 127
	}
E 6
D 42
	mp->m_flag |= M_MLOCK;
E 42
I 42
D 141
	mp->mnt_flag |= MNT_MLOCK;
E 141
I 141
	lkflags = LK_SHARED;
	if (interlkp)
		lkflags |= LK_INTERLOCK;
	if (lockmgr(&mp->mnt_lock, lkflags, interlkp, p))
		panic("vfs_busy: unexpected lock failure");
E 141
E 42
	return (0);
}

/*
D 141
 * Unlock a locked filesystem.
 * Panic if filesystem is not locked.
 */
void
vfs_unlock(mp)
	register struct mount *mp;
{

D 42
	if ((mp->m_flag & M_MLOCK) == 0)
E 42
I 42
	if ((mp->mnt_flag & MNT_MLOCK) == 0)
E 42
D 40
		panic("vfs_unlock: locked fs");
E 40
I 40
		panic("vfs_unlock: not locked");
E 40
D 42
	mp->m_flag &= ~M_MLOCK;
	if (mp->m_flag & M_MWAIT) {
		mp->m_flag &= ~M_MWAIT;
E 42
I 42
	mp->mnt_flag &= ~MNT_MLOCK;
	if (mp->mnt_flag & MNT_MWAIT) {
		mp->mnt_flag &= ~MNT_MWAIT;
E 42
		wakeup((caddr_t)mp);
	}
}

/*
I 40
 * Mark a mount point as busy.
 * Used to synchronize access and to delay unmounting.
 */
I 127
int
E 127
vfs_busy(mp)
	register struct mount *mp;
{

D 42
	if (mp->m_flag & M_UNMOUNT)
E 42
I 42
D 43
	if (mp->mnt_flag & MNT_UNMOUNT)
E 42
		return (1);
E 43
D 42
	while(mp->m_flag & M_MPBUSY) {
		mp->m_flag |= M_MPWANT;
		sleep((caddr_t)&mp->m_flag, PVFS);
E 42
I 42
D 127
	while(mp->mnt_flag & MNT_MPBUSY) {
E 127
I 127
	while (mp->mnt_flag & MNT_MPBUSY) {
E 127
		mp->mnt_flag |= MNT_MPWANT;
D 127
		sleep((caddr_t)&mp->mnt_flag, PVFS);
E 127
I 127
		tsleep((caddr_t)&mp->mnt_flag, PVFS, "vfsbusy", 0);
E 127
E 42
	}
I 43
	if (mp->mnt_flag & MNT_UNMOUNT)
		return (1);
E 43
D 42
	mp->m_flag |= M_MPBUSY;
E 42
I 42
	mp->mnt_flag |= MNT_MPBUSY;
E 42
	return (0);
}

/*
E 141
 * Free a busy filesystem.
D 142
 * Panic if filesystem is not busy.
E 142
 */
I 127
void
E 127
D 48
void
E 48
D 141
vfs_unbusy(mp)
	register struct mount *mp;
E 141
I 141
vfs_unbusy(mp, p)
	struct mount *mp;
	struct proc *p;
E 141
{

D 42
	if ((mp->m_flag & M_MPBUSY) == 0)
E 42
I 42
D 141
	if ((mp->mnt_flag & MNT_MPBUSY) == 0)
E 42
		panic("vfs_unbusy: not busy");
D 42
	mp->m_flag &= ~M_MPBUSY;
	if (mp->m_flag & M_MPWANT) {
		mp->m_flag &= ~M_MPWANT;
		wakeup((caddr_t)&mp->m_flag);
E 42
I 42
	mp->mnt_flag &= ~MNT_MPBUSY;
	if (mp->mnt_flag & MNT_MPWANT) {
		mp->mnt_flag &= ~MNT_MPWANT;
		wakeup((caddr_t)&mp->mnt_flag);
E 42
	}
E 141
I 141
	lockmgr(&mp->mnt_lock, LK_RELEASE, NULL, p);
E 141
}

/*
I 135
 * Lookup a filesystem type, and if found allocate and initialize
 * a mount structure for it.
 *
 * Devname is usually updated by mount(8) after booting.
 */
int
vfs_rootmountalloc(fstypename, devname, mpp)
	char *fstypename;
	char *devname;
	struct mount **mpp;
{
I 141
	struct proc *p = curproc;	/* XXX */
E 141
	struct vfsconf *vfsp;
	struct mount *mp;

	for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next)
		if (!strcmp(vfsp->vfc_name, fstypename))
			break;
	if (vfsp == NULL)
		return (ENODEV);
	mp = malloc((u_long)sizeof(struct mount), M_MOUNT, M_WAITOK);
	bzero((char *)mp, (u_long)sizeof(struct mount));
I 141
	lockinit(&mp->mnt_lock, PVFS, "vfslock", 0, 0);
	(void)vfs_busy(mp, LK_NOWAIT, 0, p);
E 141
	LIST_INIT(&mp->mnt_vnodelist);
	mp->mnt_vfc = vfsp;
	mp->mnt_op = vfsp->vfc_vfsops;
	mp->mnt_flag = MNT_RDONLY;
	mp->mnt_vnodecovered = NULLVP;
	vfsp->vfc_refcount++;
	mp->mnt_stat.f_type = vfsp->vfc_typenum;
	mp->mnt_flag |= vfsp->vfc_flags & MNT_VISFLAGMASK;
	strncpy(mp->mnt_stat.f_fstypename, vfsp->vfc_name, MFSNAMELEN);
	mp->mnt_stat.f_mntonname[0] = '/';
	(void) copystr(devname, mp->mnt_stat.f_mntfromname, MNAMELEN - 1, 0);
	*mpp = mp;
	return (0);
}

/*
 * Find an appropriate filesystem to use for the root. If a filesystem
 * has not been preselected, walk through the list of known filesystems
 * trying those that have mountroot routines, and try them until one
 * works or we have tried them all.
 */
int
vfs_mountroot()
{
	struct vfsconf *vfsp;
	extern int (*mountroot)(void);
	int error;

	if (mountroot != NULL)
D 138
		return ((*vfsp->vfc_mountroot)());
E 138
I 138
		return ((*mountroot)());
E 138
	for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next) {
		if (vfsp->vfc_mountroot == NULL)
			continue;
		if ((error = (*vfsp->vfc_mountroot)()) == 0)
			return (0);
		printf("%s_mountroot failed: %d\n", vfsp->vfc_name, error);
	}
	return (ENODEV);
}

/*
E 135
E 40
 * Lookup a mount point by filesystem identifier.
 */
struct mount *
D 130
getvfs(fsid)
E 130
I 130
vfs_getvfs(fsid)
E 130
	fsid_t *fsid;
{
	register struct mount *mp;

I 141
	simple_lock(&mountlist_slock);
E 141
D 4
	for (mp = rootfs; mp; mp = mp->m_next) {
E 4
I 4
D 113
	mp = rootfs;
	do {
E 113
I 113
D 133
	for (mp = mountlist.tqh_first; mp != NULL; mp = mp->mnt_list.tqe_next) {
E 133
I 133
	for (mp = mountlist.cqh_first; mp != (void *)&mountlist;
	     mp = mp->mnt_list.cqe_next) {
E 133
E 113
E 4
D 31
		if (mp->m_fsid.val[0] == fsid->val[0] &&
		    mp->m_fsid.val[1] == fsid->val[1]) {
E 31
I 31
D 42
		if (mp->m_stat.f_fsid.val[0] == fsid->val[0] &&
		    mp->m_stat.f_fsid.val[1] == fsid->val[1]) {
E 42
I 42
		if (mp->mnt_stat.f_fsid.val[0] == fsid->val[0] &&
D 113
		    mp->mnt_stat.f_fsid.val[1] == fsid->val[1]) {
E 113
I 113
D 141
		    mp->mnt_stat.f_fsid.val[1] == fsid->val[1])
E 141
I 141
		    mp->mnt_stat.f_fsid.val[1] == fsid->val[1]) {
			simple_unlock(&mountlist_slock);
E 141
E 113
E 42
E 31
D 4
			break;
E 4
I 4
			return (mp);
I 141
		}
E 141
E 4
D 113
		}
D 4
	}
	return (mp);
E 4
I 4
D 42
		mp = mp->m_next;
E 42
I 42
		mp = mp->mnt_next;
E 42
	} while (mp != rootfs);
E 113
I 113
	}
I 141
	simple_unlock(&mountlist_slock);
E 141
E 113
	return ((struct mount *)0);
I 87
}

/*
 * Get a new unique fsid
 */
void
D 130
getnewfsid(mp, mtype)
E 130
I 130
vfs_getnewfsid(mp)
E 130
	struct mount *mp;
D 130
	int mtype;
E 130
{
static u_short xxxfs_mntid;

	fsid_t tfsid;
I 130
	int mtype;
E 130

I 136
	simple_lock(&mntid_slock);
E 136
I 130
	mtype = mp->mnt_vfc->vfc_typenum;
E 130
D 115
	mp->mnt_stat.f_fsid.val[0] = makedev(nblkdev + 11, 0);	/* XXX */
E 115
I 115
	mp->mnt_stat.f_fsid.val[0] = makedev(nblkdev + mtype, 0);
E 115
	mp->mnt_stat.f_fsid.val[1] = mtype;
	if (xxxfs_mntid == 0)
		++xxxfs_mntid;
D 115
	tfsid.val[0] = makedev(nblkdev, xxxfs_mntid);
E 115
I 115
	tfsid.val[0] = makedev(nblkdev + mtype, xxxfs_mntid);
E 115
	tfsid.val[1] = mtype;
D 88
	while (getvfs(&tfsid)) {
		tfsid.val[0]++;
		xxxfs_mntid++;
E 88
I 88
D 113
	if (rootfs) {
E 113
I 113
D 133
	if (mountlist.tqh_first != NULL) {
E 133
I 133
	if (mountlist.cqh_first != (void *)&mountlist) {
E 133
E 113
D 130
		while (getvfs(&tfsid)) {
E 130
I 130
		while (vfs_getvfs(&tfsid)) {
E 130
			tfsid.val[0]++;
			xxxfs_mntid++;
		}
E 88
	}
	mp->mnt_stat.f_fsid.val[0] = tfsid.val[0];
I 136
	simple_unlock(&mntid_slock);
E 136
E 87
E 4
}

/*
 * Set vnode attributes to VNOVAL
 */
D 127
void vattr_null(vap)
E 127
I 127
void
vattr_null(vap)
E 127
	register struct vattr *vap;
{

	vap->va_type = VNON;
I 63
	vap->va_size = vap->va_bytes = VNOVAL;
D 91
#ifdef _NOQUAD
	vap->va_size_rsv = vap->va_bytes_rsv = VNOVAL;
#endif
E 91
E 63
	vap->va_mode = vap->va_nlink = vap->va_uid = vap->va_gid =
D 63
		vap->va_fsid = vap->va_fileid = vap->va_size =
D 34
		vap->va_size1 = vap->va_blocksize = vap->va_rdev =
		vap->va_bytes = vap->va_bytes1 =
E 34
I 34
		vap->va_size_rsv = vap->va_blocksize = vap->va_rdev =
		vap->va_bytes = vap->va_bytes_rsv =
E 63
I 63
		vap->va_fsid = vap->va_fileid =
		vap->va_blocksize = vap->va_rdev =
E 63
E 34
D 91
		vap->va_atime.tv_sec = vap->va_atime.tv_usec =
		vap->va_mtime.tv_sec = vap->va_mtime.tv_usec =
D 2
		vap->va_ctime.tv_sec = vap->va_ctime.tv_usec = VNOVAL;
E 2
I 2
		vap->va_ctime.tv_sec = vap->va_ctime.tv_usec =
E 91
I 91
		vap->va_atime.ts_sec = vap->va_atime.ts_nsec =
		vap->va_mtime.ts_sec = vap->va_mtime.ts_nsec =
		vap->va_ctime.ts_sec = vap->va_ctime.ts_nsec =
E 91
		vap->va_flags = vap->va_gen = VNOVAL;
I 107
D 108
	vap->va_cflags = 0;
E 108
I 108
	vap->va_vaflags = 0;
E 108
E 107
I 3
}

/*
D 57
 * Initialize a nameidata structure
 */
ndinit(ndp)
	register struct nameidata *ndp;
{

	bzero((caddr_t)ndp, sizeof(struct nameidata));
	ndp->ni_iov = &ndp->ni_nd.nd_iovec;
	ndp->ni_iovcnt = 1;
	ndp->ni_base = (caddr_t)&ndp->ni_dent;
	ndp->ni_rw = UIO_WRITE;
D 20
	ndp->ni_segflg = UIO_SYSSPACE;
E 20
I 20
	ndp->ni_uioseg = UIO_SYSSPACE;
E 20
}

/*
 * Duplicate a nameidata structure
 */
nddup(ndp, newndp)
	register struct nameidata *ndp, *newndp;
{

	ndinit(newndp);
D 49
	newndp->ni_cdir = ndp->ni_cdir;
D 5
	newndp->ni_cdir->v_count++;
E 5
I 5
	VREF(newndp->ni_cdir);
E 5
	newndp->ni_rdir = ndp->ni_rdir;
	if (newndp->ni_rdir)
D 5
		newndp->ni_rdir->v_count++;
E 5
I 5
		VREF(newndp->ni_rdir);
E 49
E 5
	newndp->ni_cred = ndp->ni_cred;
	crhold(newndp->ni_cred);
}

/*
 * Release a nameidata structure
 */
ndrele(ndp)
	register struct nameidata *ndp;
{

D 49
	vrele(ndp->ni_cdir);
	if (ndp->ni_rdir)
		vrele(ndp->ni_rdir);
E 49
	crfree(ndp->ni_cred);
E 3
E 2
}
I 8

/*
E 57
 * Routines having to do with the management of the vnode table.
 */
D 77
struct vnode *vfreeh, **vfreet;
E 77
I 77
D 95
extern struct vnode *vfreeh, **vfreet;
E 95
I 95
D 113
struct vnode *vfreeh, **vfreet = &vfreeh;
E 113
E 95
E 77
D 9
extern struct vnodeops dead_vnodeops;
E 9
I 9
D 10
extern struct vnodeops dead_vnodeops, blk_vnodeops;
E 10
I 10
D 73
extern struct vnodeops dead_vnodeops, spec_vnodeops;
E 73
I 73
D 84
extern struct vnodeops dead_vnodeops;
extern struct vnodeops spec_vnodeops;
E 84
I 84
extern int (**dead_vnodeop_p)();
D 96
extern int (**spec_vnodeop_p)();
E 96
E 84
E 73
I 18
D 136
extern void vclean();
E 136
I 136
static void vclean __P((struct vnode *vp, int flag, struct proc *p));
extern void vgonel __P((struct vnode *vp, struct proc *p));
E 136
I 38
long numvnodes;
I 41
D 77
struct vattr va_null;
E 41
E 38
E 18
E 10
D 15
struct speclist *speclisth;
struct speclist {
	struct speclist *sl_next;
	struct vnode *sl_vp;
};
E 15
E 9
D 35

I 15
#define	SPECHSZ	64
#if	((SPECHSZ&(SPECHSZ-1)) == 0)
#define	SPECHASH(rdev)	(((rdev>>5)+(rdev))&(SPECHSZ-1))
#else
#define	SPECHASH(rdev)	(((unsigned)((rdev>>5)+(rdev)))%SPECHSZ)
#endif
struct vnode *speclisth[SPECHSZ];
E 35

E 15
/*
D 9
 * Build vnode free list.
E 9
I 9
 * Initialize the vnode structures and initialize each file system type.
E 9
 */
D 9
vhinit()
E 9
I 9
vfsinit()
E 9
{
D 38
	register struct vnode *vp = vnode;
E 38
I 9
	struct vfsops **vfsp;
E 9

I 9
	/*
D 38
	 * Build vnode free list.
	 */
E 9
	vfreeh = vp;
	vfreet = &vp->v_freef;
	vp->v_freeb = &vfreeh;
	vp->v_op = &dead_vnodeops;
I 25
	vp->v_type = VBAD;
E 25
	for (vp++; vp < vnodeNVNODE; vp++) {
		*vfreet = vp;
		vp->v_freeb = vfreet;
		vfreet = &vp->v_freef;
		vp->v_op = &dead_vnodeops;
I 25
		vp->v_type = VBAD;
E 25
	}
	vp--;
	vp->v_freef = NULL;
I 9
	/*
E 38
	 * Initialize the vnode name cache
	 */
	nchinit();
	/*
	 * Initialize each file system type.
	 */
I 41
	vattr_null(&va_null);
E 41
	for (vfsp = &vfssw[0]; vfsp <= &vfssw[MOUNT_MAXTYPE]; vfsp++) {
		if (*vfsp == NULL)
			continue;
		(*(*vfsp)->vfs_init)();
	}
E 9
}
E 77
I 77
extern struct vattr va_null;
I 118
int newnodes = 0;
int printcnt = 0;
E 118
E 77

I 102
D 113

E 113
E 102
/*
 * Return the next vnode from the free list.
 */
I 127
int
E 127
getnewvnode(tag, mp, vops, vpp)
	enum vtagtype tag;
	struct mount *mp;
D 80
	struct vnodeops *vops;
E 80
I 80
	int (**vops)();
E 80
	struct vnode **vpp;
{
D 116
	register struct vnode *vp, *vq;
E 116
I 116
D 136
	register struct vnode *vp;
E 136
I 136
	struct proc *p = curproc;	/* XXX */
	struct vnode *vp;
E 136
E 116
I 102
	int s;
I 136
	int cnt;
E 136
E 102

I 136
top:
	simple_lock(&vnode_free_list_slock);
E 136
I 118
newnodes++;
E 118
D 38
	if ((vp = vfreeh) == NULL) {
		tablefull("vnode");
		*vpp = 0;
		return (ENFILE);
E 38
I 38
D 91
	if (numvnodes < desiredvnodes) {
E 91
I 91
D 113
	if ((vfreeh == NULL && numvnodes < 2 * desiredvnodes) ||
E 113
I 113
	if ((vnode_free_list.tqh_first == NULL &&
	     numvnodes < 2 * desiredvnodes) ||
E 113
	    numvnodes < desiredvnodes) {
I 136
		simple_unlock(&vnode_free_list_slock);
E 136
E 91
D 48
		vp = (struct vnode *)malloc(sizeof *vp, M_VNODE, M_WAITOK);
E 48
I 48
		vp = (struct vnode *)malloc((u_long)sizeof *vp,
		    M_VNODE, M_WAITOK);
E 48
		bzero((char *)vp, sizeof *vp);
I 118
		vp->v_freelist.tqe_next = (struct vnode *)0xdeadf;
		vp->v_freelist.tqe_prev = (struct vnode **)0xdeadb;
		vp->v_mntvnodes.le_next = (struct vnode *)0xdeadf;
		vp->v_mntvnodes.le_prev = (struct vnode **)0xdeadb;
E 118
I 113
D 114
		vp->v_usecount = 1;
E 114
E 113
		numvnodes++;
I 118
		vp->v_spare[0] = numvnodes;
E 118
	} else {
D 113
		if ((vp = vfreeh) == NULL) {
E 113
I 113
D 136
		if ((vp = vnode_free_list.tqh_first) == NULL) {
E 136
I 136
		for (vp = vnode_free_list.tqh_first;
				vp != NULLVP; vp = vp->v_freelist.tqe_next) {
			if (simple_lock_try(&vp->v_interlock))
				break;
		}
		/*
		 * Unless this is a bad time of the month, at most
		 * the first NCPUS items on the free list are
		 * locked, so this is close enough to being empty.
		 */
		if (vp == NULLVP) {
			simple_unlock(&vnode_free_list_slock);
E 136
E 113
			tablefull("vnode");
			*vpp = 0;
			return (ENFILE);
		}
		if (vp->v_usecount)
			panic("free vnode isn't");
I 118
		if (vp->v_freelist.tqe_next == (struct vnode *)0xdeadf ||
		    vp->v_freelist.tqe_prev == (struct vnode **)0xdeadb)
			panic("getnewvnode: not on queue");
E 118
D 113
		if (vq = vp->v_freef)
			vq->v_freeb = &vfreeh;
		else
			vfreet = &vfreeh;
		vfreeh = vq;
		vp->v_freef = NULL;
		vp->v_freeb = NULL;
E 113
I 113
		TAILQ_REMOVE(&vnode_free_list, vp, v_freelist);
I 118
		vp->v_freelist.tqe_next = (struct vnode *)0xdeadf;
E 118
D 114
		vp->v_usecount = 1;
E 114
I 114
		/* see comment on why 0xdeadb is set at end of vgone (below) */
		vp->v_freelist.tqe_prev = (struct vnode **)0xdeadb;
I 136
		simple_unlock(&vnode_free_list_slock);
E 136
E 114
E 113
I 65
		vp->v_lease = NULL;
E 65
		if (vp->v_type != VBAD)
D 128
			vgone(vp);
E 128
I 128
D 134
			VOP_REVOKE(vp, 0);
E 134
I 134
D 136
			vgone(vp);
E 136
I 136
			vgonel(vp, p);
		else
			simple_unlock(&vp->v_interlock);
E 136
E 134
E 128
I 102
#ifdef DIAGNOSTIC
E 102
I 64
		if (vp->v_data)
			panic("cleaned vnode isn't");
I 102
		s = splbio();
		if (vp->v_numoutput)
			panic("Clean vnode has pending I/O's");
		splx(s);
#endif
E 102
E 64
		vp->v_flag = 0;
D 50
		vp->v_shlockc = 0;
		vp->v_exlockc = 0;
E 50
		vp->v_lastr = 0;
I 120
		vp->v_ralen = 0;
		vp->v_maxra = 0;
E 120
I 102
		vp->v_lastw = 0;
		vp->v_lasta = 0;
		vp->v_cstart = 0;
		vp->v_clen = 0;
E 102
		vp->v_socket = 0;
E 38
	}
I 102
D 120
	vp->v_ralen = 1;
E 120
E 102
D 9
	if (vp->v_count || VOP_RECLAIM(vp))
E 9
I 9
D 21
	if (vp->v_count)
E 21
I 21
D 38
	if (vp->v_usecount)
E 21
E 9
		panic("free vnode isn't");
	if (vq = vp->v_freef)
		vq->v_freeb = &vfreeh;
I 37
	else
		vfreet = &vfreeh;
E 37
	vfreeh = vq;
	vp->v_freef = NULL;
	vp->v_freeb = NULL;
D 9
	vp->v_type = VNON;
E 9
I 9
D 14
	if (vp->v_type != VNON)
E 14
I 14
D 24
	if (vp->v_type != VNON && vp->v_type != VBAD)
E 24
I 24
	if (vp->v_type != VBAD)
E 24
E 14
		vgone(vp);
E 38
I 14
	vp->v_type = VNON;
E 14
E 9
D 38
	vp->v_flag = 0;
	vp->v_shlockc = 0;
	vp->v_exlockc = 0;
I 21
	vp->v_lastr = 0;
E 21
	vp->v_socket = 0;
E 38
D 9
	vp->v_op = vops;
E 9
	cache_purge(vp);
	vp->v_tag = tag;
I 9
	vp->v_op = vops;
E 9
D 16
	vp->v_mount = mp;
E 16
	insmntque(vp, mp);
D 109
	VREF(vp);
E 109
I 109
D 113
	vp->v_usecount++;
E 113
E 109
	*vpp = vp;
I 114
	vp->v_usecount = 1;
E 114
I 113
	vp->v_data = 0;
I 118
	if (printcnt-- > 0) vprint("getnewvnode got", vp);
E 118
E 113
	return (0);
}
I 119

E 119
D 102

E 102
/*
 * Move a vnode from one mount queue to another.
 */
I 127
void
E 127
insmntque(vp, mp)
D 136
	register struct vnode *vp;
	register struct mount *mp;
E 136
I 136
	struct vnode *vp;
	struct mount *mp;
E 136
{
D 59
	struct vnode *vq;
E 59
I 59
D 116
	register struct vnode *vq;
E 116
E 59

I 136
	simple_lock(&mntvnode_slock);
E 136
	/*
	 * Delete from old mount point vnode list, if on one.
	 */
D 113
	if (vp->v_mountb) {
		if (vq = vp->v_mountf)
			vq->v_mountb = vp->v_mountb;
		*vp->v_mountb = vq;
	}
E 113
I 113
D 118
	if (vp->v_mount != NULL)
E 118
I 118
	if (vp->v_mount != NULL) {
		if (vp->v_mntvnodes.le_next == (struct vnode *)0xdeadf ||
		    vp->v_mntvnodes.le_prev == (struct vnode **)0xdeadb)
			panic("insmntque: not on queue");
E 118
		LIST_REMOVE(vp, v_mntvnodes);
I 118
		vp->v_mntvnodes.le_next = (struct vnode *)0xdeadf;
		vp->v_mntvnodes.le_prev = (struct vnode **)0xdeadb;
	}
E 118
E 113
	/*
	 * Insert into list of vnodes for the new mount point, if available.
	 */
I 16
D 113
	vp->v_mount = mp;
E 16
	if (mp == NULL) {
		vp->v_mountf = NULL;
		vp->v_mountb = NULL;
E 113
I 113
D 136
	if ((vp->v_mount = mp) == NULL)
E 113
		return;
I 118
	if (vp->v_mntvnodes.le_next != (struct vnode *)0xdeadf ||
	    vp->v_mntvnodes.le_prev != (struct vnode **)0xdeadb)
		panic("insmntque: already on queue");
E 118
D 113
	}
D 42
	if (mp->m_mounth) {
		vp->v_mountf = mp->m_mounth;
		vp->v_mountb = &mp->m_mounth;
		mp->m_mounth->v_mountb = &vp->v_mountf;
		mp->m_mounth = vp;
E 42
I 42
D 59
	if (mp->mnt_mounth) {
		vp->v_mountf = mp->mnt_mounth;
		vp->v_mountb = &mp->mnt_mounth;
		mp->mnt_mounth->v_mountb = &vp->v_mountf;
		mp->mnt_mounth = vp;
E 42
	} else {
D 42
		mp->m_mounth = vp;
		vp->v_mountb = &mp->m_mounth;
E 42
I 42
		mp->mnt_mounth = vp;
		vp->v_mountb = &mp->mnt_mounth;
E 42
		vp->v_mountf = NULL;
I 54
	}
E 59
I 59
	if (vq = mp->mnt_mounth)
		vq->v_mountb = &vp->v_mountf;
	vp->v_mountf = vq;
	vp->v_mountb = &mp->mnt_mounth;
	mp->mnt_mounth = vp;
E 113
I 113
	LIST_INSERT_HEAD(&mp->mnt_vnodelist, vp, v_mntvnodes);
E 136
I 136
	if ((vp->v_mount = mp) != NULL)
		LIST_INSERT_HEAD(&mp->mnt_vnodelist, vp, v_mntvnodes);
	simple_unlock(&mntvnode_slock);
E 136
E 113
E 59
}

/*
D 92
 * Make sure all write-behind blocks associated
 * with mount point are flushed out (from sync).
 */
mntflushbuf(mountp, flags)
	struct mount *mountp;
	int flags;
{
I 84
	USES_VOP_ISLOCKED;
E 84
	register struct vnode *vp;

	if ((mountp->mnt_flag & MNT_MPBUSY) == 0)
		panic("mntflushbuf: not busy");
loop:
	for (vp = mountp->mnt_mounth; vp; vp = vp->v_mountf) {
		if (VOP_ISLOCKED(vp))
			continue;
		if (vget(vp))
			goto loop;
		vflushbuf(vp, flags);
		vput(vp);
		if (vp->v_mount != mountp)
			goto loop;
	}
}

/*
 * Flush all dirty buffers associated with a vnode.
 */
vflushbuf(vp, flags)
	register struct vnode *vp;
	int flags;
{
	register struct buf *bp;
	struct buf *nbp;
	int s;

loop:
	s = splbio();
	for (bp = vp->v_dirtyblkhd; bp; bp = nbp) {
		nbp = bp->b_blockf;
		if ((bp->b_flags & B_BUSY))
			continue;
		if ((bp->b_flags & B_DELWRI) == 0)
			panic("vflushbuf: not dirty");
		bremfree(bp);
		bp->b_flags |= B_BUSY;
		splx(s);
		/*
		 * Wait for I/O associated with indirect blocks to complete,
		 * since there is no way to quickly wait for them below.
		 * NB: This is really specific to ufs, but is done here
		 * as it is easier and quicker.
		 */
D 55
		if (bp->b_vp == vp || (flags & B_SYNC) == 0) {
E 55
I 55
		if (bp->b_vp == vp || (flags & B_SYNC) == 0)
E 55
			(void) bawrite(bp);
D 55
			s = splbio();
		} else {
E 55
I 55
		else
E 55
			(void) bwrite(bp);
D 55
			goto loop;
		}
E 55
I 55
		goto loop;
E 55
	}
	splx(s);
	if ((flags & B_SYNC) == 0)
		return;
	s = splbio();
	while (vp->v_numoutput) {
		vp->v_flag |= VBWAIT;
		sleep((caddr_t)&vp->v_numoutput, PRIBIO + 1);
	}
	splx(s);
	if (vp->v_dirtyblkhd) {
		vprint("vflushbuf: dirty", vp);
		goto loop;
	}
}

/*
E 92
 * Update outstanding I/O count and do wakeup if requested.
 */
I 127
void
E 127
vwakeup(bp)
	register struct buf *bp;
{
	register struct vnode *vp;

I 104
	bp->b_flags &= ~B_WRITEINPROG;
E 104
D 103
	bp->b_dirtyoff = bp->b_dirtyend = 0;
E 103
	if (vp = bp->b_vp) {
D 127
		vp->v_numoutput--;
I 102
		if (vp->v_numoutput < 0)
E 127
I 127
		if (--vp->v_numoutput < 0)
E 127
			panic("vwakeup: neg numoutput");
E 102
		if ((vp->v_flag & VBWAIT) && vp->v_numoutput <= 0) {
			if (vp->v_numoutput < 0)
D 127
				panic("vwakeup: neg numoutput");
E 127
I 127
				panic("vwakeup: neg numoutput 2");
E 127
			vp->v_flag &= ~VBWAIT;
			wakeup((caddr_t)&vp->v_numoutput);
		}
	}
}

/*
D 92
 * Invalidate in core blocks belonging to closed or umounted filesystem
 *
 * Go through the list of vnodes associated with the file system;
 * for each vnode invalidate any buffers that it holds. Normally
 * this routine is preceeded by a bflush call, so that on a quiescent
 * filesystem there will be no dirty buffers when we are done. Binval
 * returns the count of dirty buffers when it is finished.
 */
mntinvalbuf(mountp)
	struct mount *mountp;
{
	register struct vnode *vp;
	int dirty = 0;

	if ((mountp->mnt_flag & MNT_MPBUSY) == 0)
		panic("mntinvalbuf: not busy");
loop:
	for (vp = mountp->mnt_mounth; vp; vp = vp->v_mountf) {
		if (vget(vp))
			goto loop;
		dirty += vinvalbuf(vp, 1);
		vput(vp);
		if (vp->v_mount != mountp)
			goto loop;
	}
	return (dirty);
}

/*
E 92
 * Flush out and invalidate all buffers associated with a vnode.
 * Called with the underlying object locked.
 */
D 92
vinvalbuf(vp, save)
E 92
I 92
int
D 97
vinvalbuf(vp, save, cred, p)
E 97
I 97
D 103
vinvalbuf(vp, flags, cred, p)
E 103
I 103
vinvalbuf(vp, flags, cred, p, slpflag, slptimeo)
E 103
E 97
E 92
	register struct vnode *vp;
D 97
	int save;
E 97
I 97
	int flags;
E 97
I 92
	struct ucred *cred;
	struct proc *p;
I 103
	int slpflag, slptimeo;
E 103
E 92
{
I 84
D 93
	USES_VOP_BWRITE;
I 92
	USES_VOP_FSYNC;
E 93
E 92
E 84
	register struct buf *bp;
	struct buf *nbp, *blist;
D 92
	int s, dirty = 0;
E 92
I 92
	int s, error;
E 92

I 92
D 97
	if (save) {
E 97
I 97
	if (flags & V_SAVE) {
E 97
		if (error = VOP_FSYNC(vp, cred, MNT_WAIT, p))
			return (error);
D 98
		if (vp->v_dirtyblkhd != NULL)
E 98
I 98
D 113
		if (vp->v_dirtyblkhd.le_next != NULL)
E 113
I 113
		if (vp->v_dirtyblkhd.lh_first != NULL)
E 113
E 98
			panic("vinvalbuf: dirty bufs");
	}
E 92
	for (;;) {
D 92
		if (blist = vp->v_dirtyblkhd)
E 92
I 92
D 97
		if (blist = vp->v_cleanblkhd)
E 92
			/* void */;
D 92
		else if (blist = vp->v_cleanblkhd)
E 92
I 92
		else if (blist = vp->v_dirtyblkhd)
E 92
			/* void */;
		else
E 97
I 97
D 98
		if ((blist = vp->v_cleanblkhd) && flags & V_SAVEMETA)
E 98
I 98
D 113
		if ((blist = vp->v_cleanblkhd.le_next) && flags & V_SAVEMETA)
E 113
I 113
		if ((blist = vp->v_cleanblkhd.lh_first) && flags & V_SAVEMETA)
E 113
E 98
			while (blist && blist->b_lblkno < 0)
D 98
				blist = blist->b_blockf;
		if (!blist && (blist = vp->v_dirtyblkhd) && flags & V_SAVEMETA)
E 98
I 98
D 113
				blist = blist->b_vnbufs.qe_next;
		if (!blist && (blist = vp->v_dirtyblkhd.le_next) && 
E 113
I 113
				blist = blist->b_vnbufs.le_next;
D 127
		if (!blist && (blist = vp->v_dirtyblkhd.lh_first) && 
E 127
I 127
		if (!blist && (blist = vp->v_dirtyblkhd.lh_first) &&
E 127
E 113
		    (flags & V_SAVEMETA))
E 98
			while (blist && blist->b_lblkno < 0)
D 98
				blist = blist->b_blockf;
E 98
I 98
D 113
				blist = blist->b_vnbufs.qe_next;
E 113
I 113
				blist = blist->b_vnbufs.le_next;
E 113
E 98
		if (!blist)
E 97
			break;
I 97

E 97
		for (bp = blist; bp; bp = nbp) {
D 98
			nbp = bp->b_blockf;
E 98
I 98
D 113
			nbp = bp->b_vnbufs.qe_next;
E 113
I 113
			nbp = bp->b_vnbufs.le_next;
E 113
E 98
I 97
			if (flags & V_SAVEMETA && bp->b_lblkno < 0)
				continue;
E 97
			s = splbio();
			if (bp->b_flags & B_BUSY) {
				bp->b_flags |= B_WANTED;
D 103
				sleep((caddr_t)bp, PRIBIO + 1);
E 103
I 103
				error = tsleep((caddr_t)bp,
					slpflag | (PRIBIO + 1), "vinvalbuf",
					slptimeo);
E 103
				splx(s);
I 103
				if (error)
					return (error);
E 103
				break;
			}
			bremfree(bp);
			bp->b_flags |= B_BUSY;
			splx(s);
I 103
			/*
			 * XXX Since there are no node locks for NFS, I believe
			 * there is a slight chance that a delayed write will
			 * occur while sleeping just above, so check for it.
			 */
			if ((bp->b_flags & B_DELWRI) && (flags & V_SAVE)) {
				(void) VOP_BWRITE(bp);
				break;
			}
E 103
D 92
			if (save && (bp->b_flags & B_DELWRI)) {
D 61
				dirty++;
				(void) bwrite(bp);
E 61
I 61
D 62
				dirty++;			/* XXX */
				if (vp->v_mount->mnt_stat.f_type != MOUNT_LFS)
					(void) bwrite(bp);
E 62
I 62
				dirty++;
				(void) VOP_BWRITE(bp);
E 62
E 61
				break;
			}
E 92
D 97
			if (bp->b_vp != vp)
				reassignbuf(bp, bp->b_vp);
			else
				bp->b_flags |= B_INVAL;
E 97
I 97
			bp->b_flags |= B_INVAL;
E 97
			brelse(bp);
		}
	}
D 97
	if (vp->v_dirtyblkhd || vp->v_cleanblkhd)
E 97
I 97
D 98
	if (!(flags & V_SAVEMETA) && (vp->v_dirtyblkhd || vp->v_cleanblkhd))
E 98
I 98
	if (!(flags & V_SAVEMETA) &&
D 113
	    (vp->v_dirtyblkhd.le_next || vp->v_cleanblkhd.le_next))
E 113
I 113
	    (vp->v_dirtyblkhd.lh_first || vp->v_cleanblkhd.lh_first))
E 113
E 98
E 97
		panic("vinvalbuf: flush failed");
D 92
	return (dirty);
E 92
I 92
	return (0);
E 92
}

/*
 * Associate a buffer with a vnode.
 */
I 127
void
E 127
bgetvp(vp, bp)
	register struct vnode *vp;
	register struct buf *bp;
{
I 59
D 116
	register struct vnode *vq;
E 116
D 98
	register struct buf *bq;
E 98
E 59

	if (bp->b_vp)
		panic("bgetvp: not free");
	VHOLD(vp);
	bp->b_vp = vp;
	if (vp->v_type == VBLK || vp->v_type == VCHR)
		bp->b_dev = vp->v_rdev;
	else
		bp->b_dev = NODEV;
	/*
	 * Insert onto list for new vnode.
	 */
D 59
	if (vp->v_cleanblkhd) {
		bp->b_blockf = vp->v_cleanblkhd;
		bp->b_blockb = &vp->v_cleanblkhd;
		vp->v_cleanblkhd->b_blockb = &bp->b_blockf;
		vp->v_cleanblkhd = bp;
	} else {
		vp->v_cleanblkhd = bp;
		bp->b_blockb = &vp->v_cleanblkhd;
		bp->b_blockf = NULL;
	}
E 59
I 59
D 98
	if (bq = vp->v_cleanblkhd)
		bq->b_blockb = &bp->b_blockf;
	bp->b_blockf = bq;
	bp->b_blockb = &vp->v_cleanblkhd;
	vp->v_cleanblkhd = bp;
E 98
I 98
	bufinsvn(bp, &vp->v_cleanblkhd);
E 98
E 59
}

/*
 * Disassociate a buffer from a vnode.
 */
I 127
void
E 127
brelvp(bp)
	register struct buf *bp;
{
D 98
	struct buf *bq;
E 98
	struct vnode *vp;

	if (bp->b_vp == (struct vnode *) 0)
		panic("brelvp: NULL");
	/*
	 * Delete from old vnode list, if on one.
	 */
D 98
	if (bp->b_blockb) {
		if (bq = bp->b_blockf)
			bq->b_blockb = bp->b_blockb;
		*bp->b_blockb = bq;
		bp->b_blockf = NULL;
		bp->b_blockb = NULL;
	}
E 98
I 98
D 113
	if (bp->b_vnbufs.qe_next != NOLIST)
E 113
I 113
	if (bp->b_vnbufs.le_next != NOLIST)
E 113
		bufremvn(bp);
E 98
	vp = bp->b_vp;
	bp->b_vp = (struct vnode *) 0;
	HOLDRELE(vp);
}

/*
 * Reassign a buffer from one vnode to another.
 * Used to assign file specific control information
 * (indirect blocks) to the vnode to which they belong.
 */
I 127
void
E 127
reassignbuf(bp, newvp)
	register struct buf *bp;
	register struct vnode *newvp;
{
D 98
	register struct buf *bq, **listheadp;
E 98
I 98
D 113
	register struct list_entry *listheadp;
E 113
I 113
	register struct buflists *listheadp;
E 113
E 98

D 71
	if (newvp == NULL)
		panic("reassignbuf: NULL");
E 71
I 71
	if (newvp == NULL) {
		printf("reassignbuf: NULL");
		return;
	}
E 71
	/*
	 * Delete from old vnode list, if on one.
	 */
D 98
	if (bp->b_blockb) {
		if (bq = bp->b_blockf)
			bq->b_blockb = bp->b_blockb;
		*bp->b_blockb = bq;
	}
E 98
I 98
D 113
	if (bp->b_vnbufs.qe_next != NOLIST)
E 113
I 113
	if (bp->b_vnbufs.le_next != NOLIST)
E 113
		bufremvn(bp);
E 98
	/*
	 * If dirty, put on list of dirty buffers;
	 * otherwise insert onto list of clean buffers.
	 */
	if (bp->b_flags & B_DELWRI)
		listheadp = &newvp->v_dirtyblkhd;
	else
		listheadp = &newvp->v_cleanblkhd;
D 59
	if (*listheadp) {
		bp->b_blockf = *listheadp;
		bp->b_blockb = listheadp;
		bp->b_blockf->b_blockb = &bp->b_blockf;
		*listheadp = bp;
	} else {
		*listheadp = bp;
		bp->b_blockb = listheadp;
		bp->b_blockf = NULL;
E 54
	}
E 59
I 59
D 98
	if (bq = *listheadp)
		bq->b_blockb = &bp->b_blockf;
	bp->b_blockf = bq;
	bp->b_blockb = listheadp;
	*listheadp = bp;
E 98
I 98
	bufinsvn(bp, listheadp);
E 98
E 59
}

/*
D 9
 * Grab a particular vnode from the free list.
E 9
I 9
 * Create a vnode for a block device.
 * Used for root filesystem, argdev, and swap areas.
 * Also used for memory file system special devices.
E 9
 */
I 127
int
E 127
I 9
bdevvp(dev, vpp)
	dev_t dev;
	struct vnode **vpp;
{
D 12
	register struct inode *ip;
E 12
	register struct vnode *vp;
	struct vnode *nvp;
	int error;

I 51
D 135
	if (dev == NODEV)
		return (0);
E 135
I 135
	if (dev == NODEV) {
		*vpp = NULLVP;
		return (ENODEV);
	}
E 135
E 51
D 10
	error = getnewvnode(VT_NON, (struct mount *)0, &blk_vnodeops, &nvp);
E 10
I 10
D 84
	error = getnewvnode(VT_NON, (struct mount *)0, &spec_vnodeops, &nvp);
E 84
I 84
	error = getnewvnode(VT_NON, (struct mount *)0, spec_vnodeop_p, &nvp);
E 84
E 10
	if (error) {
D 127
		*vpp = 0;
E 127
I 127
		*vpp = NULLVP;
E 127
		return (error);
	}
	vp = nvp;
	vp->v_type = VBLK;
D 15
	vp->v_rdev = dev;
	if (nvp = checkalias(vp, (struct mount *)0)) {
E 15
I 15
	if (nvp = checkalias(vp, dev, (struct mount *)0)) {
E 15
		vput(vp);
		vp = nvp;
	}
	*vpp = vp;
	return (0);
}

/*
 * Check to see if the new vnode represents a special device
 * for which we already have a vnode (either because of
 * bdevvp() or because of a different vnode representing
 * the same block device). If such an alias exists, deallocate
D 13
 * the existing contents and return the aliased inode. The
E 13
I 13
 * the existing contents and return the aliased vnode. The
E 13
 * caller is responsible for filling it with its new contents.
 */
struct vnode *
D 15
checkalias(nvp, mp)
E 15
I 15
checkalias(nvp, nvp_rdev, mp)
E 15
	register struct vnode *nvp;
I 15
	dev_t nvp_rdev;
E 15
	struct mount *mp;
{
I 84
D 93
	USES_VOP_UNLOCK;
E 93
E 84
D 136
	register struct vnode *vp;
E 136
I 136
	struct proc *p = curproc;	/* XXX */
	struct vnode *vp;
E 136
D 15
	register struct speclist *slp;
E 15
I 15
	struct vnode **vpp;
E 15

	if (nvp->v_type != VBLK && nvp->v_type != VCHR)
D 42
		return ((struct vnode *)0);
E 42
I 42
		return (NULLVP);
E 42
I 15

	vpp = &speclisth[SPECHASH(nvp_rdev)];
E 15
loop:
I 136
	simple_lock(&spechash_slock);
E 136
D 15
	for (slp = speclisth; slp; slp = slp->sl_next) {
		vp = slp->sl_vp;
		if (nvp->v_rdev != vp->v_rdev ||
		    nvp->v_type != vp->v_type)
E 15
I 15
	for (vp = *vpp; vp; vp = vp->v_specnext) {
		if (nvp_rdev != vp->v_rdev || nvp->v_type != vp->v_type)
E 15
			continue;
D 17
		if (vget(vp))
			goto loop;
E 17
I 15
		/*
		 * Alias, but not in use, so flush it out.
		 */
I 136
		simple_lock(&vp->v_interlock);
E 136
D 17
		if (vp->v_count == 1) {
			vput(vp);
E 17
I 17
D 21
		if (vp->v_count == 0) {
E 21
I 21
		if (vp->v_usecount == 0) {
E 21
E 17
D 136
			vgone(vp);
E 136
I 136
			simple_unlock(&spechash_slock);
			vgonel(vp, p);
E 136
			goto loop;
		}
I 17
D 113
		if (vget(vp))
E 113
I 113
D 136
		if (vget(vp, 1))
E 136
I 136
		if (vget(vp, LK_EXCLUSIVE | LK_INTERLOCK, p)) {
			simple_unlock(&spechash_slock);
E 136
E 113
			goto loop;
I 136
		}
E 136
E 17
E 15
		break;
	}
D 15
	if (slp == NULL) {
		MALLOC(slp, struct speclist *, sizeof(*slp), M_VNODE, M_WAITOK);
		slp->sl_vp = nvp;
		slp->sl_next = speclisth;
		speclisth = slp;
E 15
I 15
	if (vp == NULL || vp->v_tag != VT_NON) {
D 33
		if (vp != NULL) {
D 16
			vp->v_flag |= VALIASED;
E 16
			nvp->v_flag |= VALIASED;
I 16
			vp->v_flag |= VALIASED;
			vput(vp);
E 16
		}
E 33
		MALLOC(nvp->v_specinfo, struct specinfo *,
			sizeof(struct specinfo), M_VNODE, M_WAITOK);
		nvp->v_rdev = nvp_rdev;
D 21
		nvp->v_mounton = NULL;
		nvp->v_lastr = 0;
E 21
I 21
		nvp->v_hashchain = vpp;
E 21
		nvp->v_specnext = *vpp;
I 46
		nvp->v_specflags = 0;
I 136
		simple_unlock(&spechash_slock);
E 136
E 46
		*vpp = nvp;
I 33
D 136
		if (vp != NULL) {
E 136
I 136
		if (vp != NULLVP) {
E 136
			nvp->v_flag |= VALIASED;
			vp->v_flag |= VALIASED;
			vput(vp);
		}
E 33
E 15
D 42
		return ((struct vnode *)0);
E 42
I 42
		return (NULLVP);
E 42
	}
D 11
	vclean(vp);
E 11
I 11
D 136
	VOP_UNLOCK(vp);
	vclean(vp, 0);
E 136
I 136
	simple_unlock(&spechash_slock);
	VOP_UNLOCK(vp, 0, p);
	simple_lock(&vp->v_interlock);
	vclean(vp, 0, p);
E 136
E 11
	vp->v_op = nvp->v_op;
	vp->v_tag = nvp->v_tag;
	nvp->v_type = VNON;
	insmntque(vp, mp);
	return (vp);
}

/*
 * Grab a particular vnode from the free list, increment its
 * reference count and lock it. The vnode lock bit is set the
 * vnode is being eliminated in vgone. The process is awakened
 * when the transition is completed, and an error returned to
 * indicate that the vnode is no longer usable (possibly having
 * been changed to a new file system type).
 */
I 127
int
E 127
E 9
D 113
vget(vp)
E 113
I 113
D 136
vget(vp, lockflag)
E 113
	register struct vnode *vp;
I 113
	int lockflag;
E 136
I 136
vget(vp, flags, p)
	struct vnode *vp;
	int flags;
	struct proc *p;
E 136
E 113
{
I 139
	int error;
E 139
I 84
D 93
	USES_VOP_LOCK;
E 93
E 84
D 116
	register struct vnode *vq;
E 116

D 9
	if (vq = vp->v_freef)
		vq->v_freeb = vp->v_freeb;
	else
		vfreet = vp->v_freeb;
	*vp->v_freeb = vq;
	vp->v_freef = NULL;
	vp->v_freeb = NULL;
E 9
I 9
D 125
	if (vp->v_flag & VXLOCK) {
E 125
I 125
	/*
	 * If the vnode is in the process of being cleaned out for
	 * another use, we wait for the cleaning to finish and then
D 136
	 * return failure. Cleaning is determined either by checking
	 * that the VXLOCK flag is set, or that the use count is
	 * zero with the back pointer set to show that it has been
	 * removed from the free list by getnewvnode. The VXLOCK
	 * flag may not have been set yet because vclean is blocked in
	 * the VOP_LOCK call waiting for the VOP_INACTIVE to complete.
E 136
I 136
	 * return failure. Cleaning is determined by checking that
	 * the VXLOCK flag is set.
E 136
	 */
D 136
	if ((vp->v_flag & VXLOCK) ||
	    (vp->v_usecount == 0 &&
	     vp->v_freelist.tqe_prev == (struct vnode **)0xdeadb)) {
E 136
I 136
	if ((flags & LK_INTERLOCK) == 0)
		simple_lock(&vp->v_interlock);
	if (vp->v_flag & VXLOCK) {
E 136
E 125
		vp->v_flag |= VXWANT;
I 136
		simple_unlock(&vp->v_interlock);
E 136
D 127
		sleep((caddr_t)vp, PINOD);
E 127
I 127
		tsleep((caddr_t)vp, PINOD, "vget", 0);
E 127
D 136
		return (1);
E 136
I 136
		return (ENOENT);
E 136
	}
D 21
	if (vp->v_count == 0) {
E 21
I 21
D 113
	if (vp->v_usecount == 0) {
E 21
		if (vq = vp->v_freef)
			vq->v_freeb = vp->v_freeb;
		else
			vfreet = vp->v_freeb;
		*vp->v_freeb = vq;
		vp->v_freef = NULL;
		vp->v_freeb = NULL;
	}
E 113
I 113
D 118
D 122
	if (vp->v_usecount == 0)
E 122
I 122
D 125
	if (vp->v_usecount == 0) {
#ifdef DIAGNOSTIC
D 123
		if (vp->v_freelist.tqe_prev == 0xdeadb)
E 123
I 123
		if (vp->v_freelist.tqe_prev == (struct vnode **)0xdeadb)
E 123
			panic("vget: race with getnewvnode");
#endif
E 125
I 125
D 136
	if (vp->v_usecount == 0)
E 136
I 136
	if (vp->v_usecount == 0) {
		simple_lock(&vnode_free_list_slock);
E 136
E 125
E 122
E 118
I 118
	if (vp->v_usecount == 0) {
		if (vp->v_freelist.tqe_next == (struct vnode *)0xdeadf ||
		    vp->v_freelist.tqe_prev == (struct vnode **)0xdeadb)
			panic("vget: not on queue");
E 118
		TAILQ_REMOVE(&vnode_free_list, vp, v_freelist);
I 136
		simple_unlock(&vnode_free_list_slock);
	}
E 136
I 122
D 125
	}
E 125
E 122
I 118
		vp->v_freelist.tqe_next = (struct vnode *)0xdeadf;
		vp->v_freelist.tqe_prev = (struct vnode **)0xdeadb;
	}
E 118
E 113
E 9
D 109
	VREF(vp);
E 109
I 109
	vp->v_usecount++;
E 109
I 9
D 113
	VOP_LOCK(vp);
E 113
I 113
D 136
	if (lockflag)
		VOP_LOCK(vp);
E 136
I 136
D 139
	if (flags & LK_TYPE_MASK)
		return (vn_lock(vp, flags | LK_INTERLOCK, p));
E 139
I 139
	if (flags & LK_TYPE_MASK) {
		if (error = vn_lock(vp, flags | LK_INTERLOCK, p))
			vrele(vp);
		return (error);
	}
E 139
	simple_unlock(&vp->v_interlock);
E 136
I 118
	if (printcnt-- > 0) vprint("vget got", vp);
E 118
E 113
	return (0);
E 9
}

I 68
int bug_refs = 0;

E 68
I 66
D 67
int bug_refs = 0;

E 67
E 66
/*
D 136
 * Vnode reference, just increment the count
E 136
I 136
 * Stubs to use when there is no locking to be done on the underlying object.
D 142
 *
 * Getting a lock just clears the interlock if necessary.
E 142
I 142
 * A minimal shared lock is necessary to ensure that the underlying object
 * is not revoked while an operation is in progress. So, an active shared
 * count is maintained in an auxillary vnode lock structure.
E 142
E 136
 */
I 136
int
vop_nolock(ap)
	struct vop_lock_args /* {
		struct vnode *a_vp;
		int a_flags;
		struct proc *a_p;
	} */ *ap;
{
I 142
#ifdef notyet
	/*
	 * This code cannot be used until all the non-locking filesystems
	 * (notably NFS) are converted to properly lock and release nodes.
	 * Also, certain vnode operations change the locking state within
	 * the operation (create, mknod, remove, link, rename, mkdir, rmdir,
	 * and symlink). Ideally these operations should not change the
	 * lock state, but should be changed to let the caller of the
	 * function unlock them. Otherwise all intermediate vnode layers
	 * (such as union, umapfs, etc) must catch these functions to do
	 * the necessary locking at their layer. Note that the inactive
	 * and lookup operations also change their lock state, but this 
	 * cannot be avoided, so these two operations will always need
	 * to be handled in intermediate layers.
	 */
E 142
	struct vnode *vp = ap->a_vp;
I 142
	int vnflags, flags = ap->a_flags;
E 142

I 142
	if (vp->v_vnlock == NULL) {
		if ((flags & LK_TYPE_MASK) == LK_DRAIN)
			return (0);
		MALLOC(vp->v_vnlock, struct lock *, sizeof(struct lock),
		    M_VNODE, M_WAITOK);
		lockinit(vp->v_vnlock, PVFS, "vnlock", 0, 0);
	}
	switch (flags & LK_TYPE_MASK) {
	case LK_DRAIN:
		vnflags = LK_DRAIN;
		break;
	case LK_EXCLUSIVE:
	case LK_SHARED:
		vnflags = LK_SHARED;
		break;
	case LK_UPGRADE:
	case LK_EXCLUPGRADE:
	case LK_DOWNGRADE:
		return (0);
	case LK_RELEASE:
	default:
		panic("vop_nolock: bad operation %d", flags & LK_TYPE_MASK);
	}
	if (flags & LK_INTERLOCK)
		vnflags |= LK_INTERLOCK;
	return(lockmgr(vp->v_vnlock, vnflags, &vp->v_interlock, ap->a_p));
#else /* for now */
E 142
	/*
	 * Since we are not using the lock manager, we must clear
	 * the interlock here.
	 */
	if (ap->a_flags & LK_INTERLOCK)
D 142
		simple_unlock(&vp->v_interlock);
E 142
I 142
		simple_unlock(&ap->a_vp->v_interlock);
E 142
	return (0);
I 142
#endif
E 142
}

/*
D 142
 * Unlock has nothing to do.
E 142
I 142
 * Decrement the active use count.
E 142
 */
int
vop_nounlock(ap)
	struct vop_unlock_args /* {
		struct vnode *a_vp;
		int a_flags;
		struct proc *a_p;
	} */ *ap;
{
I 142
	struct vnode *vp = ap->a_vp;
E 142

D 142
	return (0);
E 142
I 142
	if (vp->v_vnlock == NULL)
		return (0);
	return (lockmgr(vp->v_vnlock, LK_RELEASE, NULL, ap->a_p));
E 142
}

/*
D 142
 * Nothing is ever locked.
E 142
I 142
 * Return whether or not the node is in use.
E 142
 */
int
vop_noislocked(ap)
	struct vop_islocked_args /* {
		struct vnode *a_vp;
	} */ *ap;
{
I 142
	struct vnode *vp = ap->a_vp;
E 142

D 142
	return (0);
E 142
I 142
	if (vp->v_vnlock == NULL)
		return (0);
	return (lockstatus(vp->v_vnlock));
E 142
}

/*
 * Vnode reference.
 */
E 136
D 127
void vref(vp)
E 127
I 127
void
vref(vp)
E 127
	struct vnode *vp;
{

I 136
	simple_lock(&vp->v_interlock);
E 136
I 109
	if (vp->v_usecount <= 0)
		panic("vref used where vget required");
I 118
	if (vp->v_freelist.tqe_next != (struct vnode *)0xdeadf ||
	    vp->v_freelist.tqe_prev != (struct vnode **)0xdeadb)
		panic("vref: not free");
E 118
E 109
D 21
	vp->v_count++;
E 21
I 21
	vp->v_usecount++;
I 136
	simple_unlock(&vp->v_interlock);
E 136
I 118
	if (printcnt-- > 0) vprint("vref get", vp);
E 118
I 68
	if (vp->v_type != VBLK && curproc)
		curproc->p_spare[0]++;
	if (bug_refs)
		vprint("vref: ");
E 68
I 66
D 67
	if (vp->v_type!=VBLK && curproc) {   /* NEEDSWORK: debugging */
		curproc->p_spare[2]++;
	};
	if (bug_refs) {
		vprint ("vref: ");
	};
E 67
E 66
E 21
}

/*
 * vput(), just unlock and vrele()
 */
D 127
void vput(vp)
E 127
I 127
void
vput(vp)
E 127
D 136
	register struct vnode *vp;
E 136
I 136
	struct vnode *vp;
E 136
{
I 136
	struct proc *p = curproc;	/* XXX */
E 136
I 84
D 93
	USES_VOP_UNLOCK;
E 93
E 84
I 70

E 70
D 136
	VOP_UNLOCK(vp);
E 136
I 136
D 137
	VOP_UNLOCK(vp, 0, p);
E 136
	vrele(vp);
E 137
I 137
#ifdef DIGANOSTIC
	if (vp == NULL)
		panic("vput: null vp");
#endif
	simple_lock(&vp->v_interlock);
	vp->v_usecount--;
	if (vp->v_usecount > 0) {
		simple_unlock(&vp->v_interlock);
		VOP_UNLOCK(vp, 0, p);
		return;
	}
#ifdef DIAGNOSTIC
	if (vp->v_usecount < 0 || vp->v_writecount != 0) {
		vprint("vput: bad ref count", vp);
		panic("vput: ref cnt");
	}
#endif
	/*
	 * insert at tail of LRU list
	 */
	simple_lock(&vnode_free_list_slock);
	TAILQ_INSERT_TAIL(&vnode_free_list, vp, v_freelist);
	simple_unlock(&vnode_free_list_slock);
	simple_unlock(&vp->v_interlock);
	VOP_INACTIVE(vp, p);
E 137
}

/*
 * Vnode release.
 * If count drops to zero, call inactive routine and return to freelist.
 */
D 127
void vrele(vp)
E 127
I 127
void
vrele(vp)
E 127
D 136
	register struct vnode *vp;
E 136
I 136
	struct vnode *vp;
E 136
{
I 136
	struct proc *p = curproc;	/* XXX */
E 136
I 84
D 93
	USES_VOP_INACTIVE;
E 93
E 84
I 52
D 92
	struct proc *p = curproc;		/* XXX */
E 92
E 52

I 60
#ifdef DIAGNOSTIC
E 60
	if (vp == NULL)
D 9
		return;
E 9
I 9
		panic("vrele: null vp");
I 60
#endif
I 136
	simple_lock(&vp->v_interlock);
E 136
E 60
E 9
D 21
	vp->v_count--;
	if (vp->v_count < 0)
E 21
I 21
	vp->v_usecount--;
I 118
	if (printcnt-- > 0) vprint("vrele put", vp);
E 118
I 68
	if (vp->v_type != VBLK && curproc)
		curproc->p_spare[0]--;
	if (bug_refs)
		vprint("vref: ");
E 68
I 66
D 67
	if (vp->v_type!=VBLK && curproc) {   /* NEEDSWORK: debugging */
		curproc->p_spare[2]--;
	};
	if (bug_refs) {
		vprint ("vref: ");
	};
E 67
E 66
D 60
	if (vp->v_usecount < 0)
E 21
D 19
		printf("vnode bad ref count %d, type %d, tag %d\n",
			vp->v_count, vp->v_type, vp->v_tag);
E 19
I 19
		vprint("vrele: bad ref count", vp);
E 60
E 19
D 21
	if (vp->v_count > 0)
E 21
I 21
D 136
	if (vp->v_usecount > 0)
E 136
I 136
	if (vp->v_usecount > 0) {
		simple_unlock(&vp->v_interlock);
E 136
E 21
		return;
I 136
	}
E 136
I 60
#ifdef DIAGNOSTIC
D 136
	if (vp->v_usecount != 0 || vp->v_writecount != 0) {
E 136
I 136
	if (vp->v_usecount < 0 || vp->v_writecount != 0) {
E 136
		vprint("vrele: bad ref count", vp);
		panic("vrele: ref cnt");
	}
#endif
E 60
D 9
	VOP_INACTIVE(vp);
E 9
D 42
	if (vfreeh == (struct vnode *)0) {
E 42
I 42
D 95
	if (vfreeh == NULLVP) {
E 42
		/*
		 * insert into empty list
		 */
		vfreeh = vp;
		vp->v_freeb = &vfreeh;
D 9
		vp->v_freef = NULL;
		vfreet = &vp->v_freef;
	} else if (vp->v_type == VNON) {
		/*
		 * insert at head of list
		 */
		vp->v_freef = vfreeh;
		vp->v_freeb = &vfreeh;
		vfreeh->v_freeb = &vp->v_freef;
		vfreeh = vp;
E 9
	} else {
		/*
		 * insert at tail of list
		 */
		*vfreet = vp;
		vp->v_freeb = vfreet;
D 9
		vp->v_freef = NULL;
		vfreet = &vp->v_freef;
E 9
	}
E 95
I 95
	/*
	 * insert at tail of LRU list
	 */
I 136
	simple_lock(&vnode_free_list_slock);
E 136
I 118
	if (vp->v_freelist.tqe_next != (struct vnode *)0xdeadf ||
	    vp->v_freelist.tqe_prev != (struct vnode **)0xdeadb)
		panic("vrele: not free");
E 118
D 113
	*vfreet = vp;
	vp->v_freeb = vfreet;
E 95
I 9
	vp->v_freef = NULL;
	vfreet = &vp->v_freef;
E 113
I 113
	TAILQ_INSERT_TAIL(&vnode_free_list, vp, v_freelist);
E 113
D 52
	VOP_INACTIVE(vp);
E 52
I 52
D 92
	VOP_INACTIVE(vp, p);
E 92
I 92
D 136
	VOP_INACTIVE(vp);
E 136
I 136
	simple_unlock(&vnode_free_list_slock);
	if (vn_lock(vp, LK_EXCLUSIVE | LK_INTERLOCK, p) == 0)
		VOP_INACTIVE(vp, p);
E 136
E 92
E 52
I 13
}

I 136
#ifdef DIAGNOSTIC
E 136
/*
I 21
 * Page or buffer structure gets a reference.
 */
D 72
vhold(vp)
E 72
I 72
D 127
void vhold(vp)
E 127
I 127
void
vhold(vp)
E 127
E 72
	register struct vnode *vp;
{

I 136
	simple_lock(&vp->v_interlock);
E 136
	vp->v_holdcnt++;
I 136
	simple_unlock(&vp->v_interlock);
E 136
}

/*
 * Page or buffer structure frees a reference.
 */
D 72
holdrele(vp)
E 72
I 72
D 127
void holdrele(vp)
E 127
I 127
void
holdrele(vp)
E 127
E 72
	register struct vnode *vp;
{

I 136
	simple_lock(&vp->v_interlock);
E 136
	if (vp->v_holdcnt <= 0)
		panic("holdrele: holdcnt");
	vp->v_holdcnt--;
I 136
	simple_unlock(&vp->v_interlock);
E 136
}
I 136
#endif /* DIAGNOSTIC */
E 136

/*
E 21
 * Remove any vnodes in the vnode table belonging to mount point mp.
 *
 * If MNT_NOFORCE is specified, there should not be any active ones,
 * return error if any are found (nb: this is a user error, not a
 * system error). If MNT_FORCE is specified, detach any active vnodes
 * that are found.
 */
I 119
#ifdef DIAGNOSTIC
E 119
D 111
int busyprt = 0;	/* patch to print out busy vnodes */
E 111
I 111
int busyprt = 0;	/* print out busy vnodes */
struct ctldebug debug1 = { "busyprt", &busyprt };
I 119
#endif
E 119
E 111

I 127
int
E 127
vflush(mp, skipvp, flags)
	struct mount *mp;
	struct vnode *skipvp;
	int flags;
{
D 136
	register struct vnode *vp, *nvp;
E 136
I 136
	struct proc *p = curproc;	/* XXX */
	struct vnode *vp, *nvp;
E 136
	int busy = 0;

I 136
D 141
#ifdef DIAGNOSTIC
E 136
I 40
D 42
	if ((mp->m_flag & M_MPBUSY) == 0)
E 42
I 42
	if ((mp->mnt_flag & MNT_MPBUSY) == 0)
E 42
		panic("vflush: not busy");
I 136
#endif

E 141
	simple_lock(&mntvnode_slock);
E 136
I 44
loop:
E 44
E 40
D 42
	for (vp = mp->m_mounth; vp; vp = nvp) {
E 42
I 42
D 113
	for (vp = mp->mnt_mounth; vp; vp = nvp) {
E 113
I 113
	for (vp = mp->mnt_vnodelist.lh_first; vp; vp = nvp) {
E 113
I 44
		if (vp->v_mount != mp)
			goto loop;
E 44
E 42
D 113
		nvp = vp->v_mountf;
E 113
I 113
		nvp = vp->v_mntvnodes.le_next;
E 113
		/*
		 * Skip over a selected vnode.
D 40
		 * Used by ufs to skip over the quota structure inode.
E 40
		 */
		if (vp == skipvp)
			continue;
I 136

		simple_lock(&vp->v_interlock);
E 136
		/*
I 40
		 * Skip over a vnodes marked VSYSTEM.
		 */
D 136
		if ((flags & SKIPSYSTEM) && (vp->v_flag & VSYSTEM))
E 136
I 136
		if ((flags & SKIPSYSTEM) && (vp->v_flag & VSYSTEM)) {
			simple_unlock(&vp->v_interlock);
E 136
			continue;
I 136
		}
E 136
		/*
I 101
		 * If WRITECLOSE is set, only flush out regular file
		 * vnodes open for writing.
		 */
		if ((flags & WRITECLOSE) &&
D 136
		    (vp->v_writecount == 0 || vp->v_type != VREG))
E 136
I 136
		    (vp->v_writecount == 0 || vp->v_type != VREG)) {
			simple_unlock(&vp->v_interlock);
E 136
			continue;
I 136
		}
E 136
		/*
E 101
E 40
D 21
		 * With v_count == 0, all we need to do is clear
E 21
I 21
		 * With v_usecount == 0, all we need to do is clear
E 21
		 * out the vnode data structures and we are done.
		 */
D 21
		if (vp->v_count == 0) {
E 21
I 21
		if (vp->v_usecount == 0) {
E 21
D 128
			vgone(vp);
E 128
I 128
D 134
			VOP_REVOKE(vp, 0);
E 134
I 134
D 136
			vgone(vp);
E 136
I 136
			simple_unlock(&mntvnode_slock);
			vgonel(vp, p);
			simple_lock(&mntvnode_slock);
E 136
E 134
E 128
			continue;
		}
		/*
I 101
		 * If FORCECLOSE is set, forcibly close the vnode.
E 101
		 * For block or character devices, revert to an
		 * anonymous device. For all other files, just kill them.
		 */
D 40
		if (flags & MNT_FORCE) {
E 40
I 40
		if (flags & FORCECLOSE) {
I 136
			simple_unlock(&mntvnode_slock);
E 136
E 40
			if (vp->v_type != VBLK && vp->v_type != VCHR) {
D 128
				vgone(vp);
E 128
I 128
D 134
				VOP_REVOKE(vp, 0);
E 134
I 134
D 136
				vgone(vp);
E 136
I 136
				vgonel(vp, p);
E 136
E 134
E 128
			} else {
D 136
				vclean(vp, 0);
E 136
I 136
				vclean(vp, 0, p);
E 136
D 84
				vp->v_op = &spec_vnodeops;
E 84
I 84
				vp->v_op = spec_vnodeop_p;
E 84
				insmntque(vp, (struct mount *)0);
			}
I 136
			simple_lock(&mntvnode_slock);
E 136
			continue;
		}
I 119
#ifdef DIAGNOSTIC
E 119
		if (busyprt)
D 19
			printf("vflush: busy vnode count %d type %d tag %d\n",
			    vp->v_count, vp->v_type, vp->v_tag);
E 19
I 19
			vprint("vflush: busy vnode", vp);
I 119
#endif
I 136
		simple_unlock(&vp->v_interlock);
E 136
E 119
E 19
		busy++;
	}
I 136
	simple_unlock(&mntvnode_slock);
E 136
	if (busy)
		return (EBUSY);
	return (0);
E 13
}

/*
 * Disassociate the underlying file system from a vnode.
I 136
 * The vnode interlock is held on entry.
E 136
D 11
 * If this operation is done on an active vnode (i.e. v_count > 0)
 * then the vnode must be delivered locked.
E 11
 */
D 11
void vclean(vp)
E 11
I 11
D 40
void vclean(vp, doclose)
E 40
I 40
D 91
void vclean(vp, flags)
E 91
I 91
D 136
void
vclean(vp, flags)
E 91
E 40
E 11
	register struct vnode *vp;
E 136
I 136
static void
vclean(vp, flags, p)
	struct vnode *vp;
E 136
I 11
D 40
	long doclose;
E 40
I 40
D 48
	long flags;
E 48
I 48
	int flags;
I 136
	struct proc *p;
E 136
E 48
E 40
E 11
{
I 84
D 85
	USES_VOP_INACTIVE;
E 85
D 93
	USES_VOP_LOCK;
E 84
D 85
	struct vnodeops *origops;
E 85
I 85
	USES_VOP_UNLOCK;
	USES_VOP_CLOSE;
	USES_VOP_INACTIVE;
	USES_VOP_RECLAIM;
E 93
I 93
D 99
	struct vop_inactive_args vop_inactive_a;
	struct vop_reclaim_args vop_reclaim_a;
	struct vop_unlock_args vop_unlock_a;
	struct vop_close_args vop_close_a;
E 93
	int (**origops)();
E 99
E 85
I 11
	int active;
I 52
D 92
	struct proc *p = curproc;	/* XXX */
E 92
E 52
E 11

I 11
	/*
	 * Check to see if the vnode is in use.
D 19
	 * If so we have to lock it before we clean it out.
E 19
I 19
	 * If so we have to reference it before we clean it out
	 * so that its count cannot fall to zero and generate a
	 * race against ourselves to recycle it.
E 19
	 */
D 19
	if (active = vp->v_count) {
E 19
I 19
D 21
	if (active = vp->v_count)
E 21
I 21
	if (active = vp->v_usecount)
E 21
E 19
D 136
		VREF(vp);
E 136
I 136
		vp->v_usecount++;
E 136
D 19
		VOP_LOCK(vp);
	}
E 19
	/*
I 99
D 136
	 * Even if the count is zero, the VOP_INACTIVE routine may still
	 * have the object locked while it cleans it out. The VOP_LOCK
	 * ensures that the VOP_INACTIVE routine is done with its work.
	 * For active vnodes, it ensures that no other activity can
	 * occur while the underlying object is being cleaned out.
	 */
	VOP_LOCK(vp);
	/*
E 136
E 99
	 * Prevent the vnode from being recycled or
	 * brought into use while we clean it out.
	 */
E 11
D 19
	while (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		sleep((caddr_t)vp, PINOD);
	}
E 19
I 19
	if (vp->v_flag & VXLOCK)
		panic("vclean: deadlock");
E 19
	vp->v_flag |= VXLOCK;
	/*
I 136
	 * Even if the count is zero, the VOP_INACTIVE routine may still
	 * have the object locked while it cleans it out. The VOP_LOCK
	 * ensures that the VOP_INACTIVE routine is done with its work.
	 * For active vnodes, it ensures that no other activity can
	 * occur while the underlying object is being cleaned out.
	 */
	VOP_LOCK(vp, LK_DRAIN | LK_INTERLOCK, p);
	/*
E 136
I 19
D 99
	 * Even if the count is zero, the VOP_INACTIVE routine may still
	 * have the object locked while it cleans it out. The VOP_LOCK
	 * ensures that the VOP_INACTIVE routine is done with its work.
	 * For active vnodes, it ensures that no other activity can
	 * occur while the buffer list is being cleaned out.
E 99
I 99
	 * Clean out any buffers associated with the vnode.
E 99
	 */
D 99
	VOP_LOCK(vp);
E 99
D 40
	if (doclose)
E 40
I 40
	if (flags & DOCLOSE)
E 40
D 92
		vinvalbuf(vp, 1);
E 92
I 92
D 103
		vinvalbuf(vp, 1, NOCRED, NULL);
E 103
I 103
D 140
		vinvalbuf(vp, V_SAVE, NOCRED, NULL, 0, 0);
E 140
I 140
		vinvalbuf(vp, V_SAVE, NOCRED, p, 0, 0);
E 140
E 103
E 92
	/*
E 19
D 99
	 * Prevent any further operations on the vnode from
	 * being passed through to the old file system.
E 99
I 99
D 136
	 * Any other processes trying to obtain this lock must first
	 * wait for VXLOCK to clear, then call the new lock operation.
E 99
	 */
D 99
	origops = vp->v_op;
D 84
	vp->v_op = &dead_vnodeops;
E 84
I 84
	vp->v_op = dead_vnodeop_p;
E 84
	vp->v_tag = VT_NON;
E 99
I 99
	VOP_UNLOCK(vp);
E 99
	/*
E 136
D 11
	 * If purging an active vnode, it must be unlocked and
	 * deactivated before being reclaimed.
E 11
I 11
D 99
	 * If purging an active vnode, it must be unlocked, closed,
	 * and deactivated before being reclaimed.
E 99
I 99
	 * If purging an active vnode, it must be closed and
D 136
	 * deactivated before being reclaimed.
E 136
I 136
	 * deactivated before being reclaimed. Note that the
	 * VOP_INACTIVE will unlock the vnode.
E 136
E 99
E 11
	 */
I 84
D 85
/* NEEDSWORK: Following line has potential by-hand ops invocation */
E 84
I 19
D 58
	(*(origops->vn_unlock))(vp);
E 58
I 58
	(*(origops->vop_unlock))(vp);
E 85
I 85
D 99
	vop_unlock_a.a_desc = VDESC(vop_unlock);
	vop_unlock_a.a_vp = vp;
	VOCALL(origops,VOFFSET(vop_unlock),&vop_unlock_a);
E 99
E 85
E 58
E 19
D 11
	if (vp->v_count > 0) {
E 11
I 11
	if (active) {
E 11
D 19
		(*(origops->vn_unlock))(vp);
E 19
I 11
D 40
		if (doclose)
E 40
I 40
D 85
		if (flags & DOCLOSE)
I 84
/* NEEDSWORK: Following line has potential by-hand ops invocation */
E 84
E 40
D 52
			(*(origops->vn_close))(vp, 0, NOCRED);
E 11
		(*(origops->vn_inactive))(vp);
E 52
I 52
D 53
			(*(origops->vn_close))(vp, 0, NOCRED, p);
E 53
I 53
D 58
			(*(origops->vn_close))(vp, IO_NDELAY, NOCRED, p);
E 53
		(*(origops->vn_inactive))(vp, p);
E 58
I 58
			(*(origops->vop_close))(vp, IO_NDELAY, NOCRED, p);
I 84
/* NEEDSWORK: Following line has potential by-hand ops invocation */
E 84
		(*(origops->vop_inactive))(vp, p);
E 85
I 85
D 99
		/*
		 * Note: these next two calls imply
		 * that vop_close and vop_inactive implementations
		 * cannot count on the ops vector being correctly
		 * set.
		 */
		if (flags & DOCLOSE) {
			vop_close_a.a_desc = VDESC(vop_close);
			vop_close_a.a_vp = vp;
			vop_close_a.a_fflag = IO_NDELAY;
D 92
			vop_close_a.a_p = p;
E 92
I 92
			vop_close_a.a_p = NULL;
E 92
			VOCALL(origops,VOFFSET(vop_close),&vop_close_a);
		};
		vop_inactive_a.a_desc = VDESC(vop_inactive);
		vop_inactive_a.a_vp = vp;
D 92
		vop_inactive_a.a_p = p;
E 92
		VOCALL(origops,VOFFSET(vop_inactive),&vop_inactive_a);
E 99
I 99
		if (flags & DOCLOSE)
D 136
			VOP_CLOSE(vp, IO_NDELAY, NOCRED, NULL);
		VOP_INACTIVE(vp);
E 136
I 136
			VOP_CLOSE(vp, IO_NDELAY, NOCRED, p);
		VOP_INACTIVE(vp, p);
	} else {
		/*
		 * Any other processes trying to obtain this lock must first
		 * wait for VXLOCK to clear, then call the new lock operation.
		 */
		VOP_UNLOCK(vp, 0, p);
E 136
E 99
E 85
E 58
E 52
	}
	/*
	 * Reclaim the vnode.
	 */
I 84
D 85
/* NEEDSWORK: Following line has potential by-hand ops invocation */
E 84
D 58
	if ((*(origops->vn_reclaim))(vp))
E 58
I 58
	if ((*(origops->vop_reclaim))(vp))
E 85
I 85
D 99
	/*
	 * Emulate VOP_RECLAIM.
	 */
	vop_reclaim_a.a_desc = VDESC(vop_reclaim);
	vop_reclaim_a.a_vp = vp;
	if (VOCALL(origops,VOFFSET(vop_reclaim),&vop_reclaim_a))
E 99
I 99
D 136
	if (VOP_RECLAIM(vp))
E 136
I 136
	if (VOP_RECLAIM(vp, p))
E 136
E 99
E 85
E 58
		panic("vclean: cannot reclaim");
I 11
	if (active)
		vrele(vp);
I 131
	cache_purge(vp);
I 142
	if (vp->v_vnlock) {
		if ((vp->v_vnlock->lk_flags & LK_DRAINED) == 0)
			vprint("vclean: lock not drained", vp);
		FREE(vp->v_vnlock, M_VNODE);
		vp->v_vnlock = NULL;
	}
E 142
E 131
I 85

E 85
E 11
	/*
D 99
	 * Done with purge, notify sleepers in vget of the grim news.
E 99
I 99
	 * Done with purge, notify sleepers of the grim news.
E 99
	 */
I 99
	vp->v_op = dead_vnodeop_p;
	vp->v_tag = VT_NON;
E 99
	vp->v_flag &= ~VXLOCK;
	if (vp->v_flag & VXWANT) {
		vp->v_flag &= ~VXWANT;
		wakeup((caddr_t)vp);
	}
}

/*
I 17
 * Eliminate all activity associated with  the requested vnode
 * and with all vnodes aliased to the requested vnode.
 */
D 127
void vgoneall(vp)
E 127
I 127
D 128
void
vgoneall(vp)
E 127
	register struct vnode *vp;
E 128
I 128
int
vop_revoke(ap)
	struct vop_revoke_args /* {
		struct vnode *a_vp;
		int a_flags;
	} */ *ap;
E 128
{
D 21
	register struct vnode *vq, **vpp;
E 21
I 21
D 128
	register struct vnode *vq;
E 128
I 128
D 136
	register struct vnode *vp, *vq;
E 136
I 136
	struct vnode *vp, *vq;
	struct proc *p = curproc;	/* XXX */
E 136
E 128
E 21

I 136
#ifdef DIAGNOSTIC
	if ((ap->a_flags & REVOKEALL) == 0)
		panic("vop_revoke");
#endif

E 136
D 21
	if (vp->v_flag & VALIASED) {
		vpp = &speclisth[SPECHASH(vp->v_rdev)];
	loop:
		for (vq = *vpp; vq; vq = vq->v_specnext) {
E 21
I 21
D 36
	while (vp->v_flag & VALIASED) {
		for (vq = *vp->v_hashchain; vq; vq = vq->v_specnext) {
E 21
D 26
			if (vq->v_rdev != vp->v_rdev || vp == vq)
E 26
I 26
			if (vq->v_rdev != vp->v_rdev ||
			    vq->v_type != vp->v_type || vp == vq)
E 26
				continue;
			vgone(vq);
D 21
			goto loop;
E 21
I 21
			break;
E 36
I 36
D 128
	if (vp->v_flag & VALIASED) {
E 128
I 128
	vp = ap->a_vp;
D 136
	if ((ap->a_flags & REVOKEALL) && (vp->v_flag & VALIASED)) {
E 136
I 136
	simple_lock(&vp->v_interlock);

	if (vp->v_flag & VALIASED) {
E 136
E 128
		/*
		 * If a vgone (or vclean) is already in progress,
		 * wait until it is done and return.
		 */
		if (vp->v_flag & VXLOCK) {
			vp->v_flag |= VXWANT;
I 136
			simple_unlock(&vp->v_interlock);
E 136
D 127
			sleep((caddr_t)vp, PINOD);
E 127
I 127
D 128
			tsleep((caddr_t)vp, PINOD, "vgoneall", 0);
E 127
			return;
E 128
I 128
			tsleep((caddr_t)vp, PINOD, "vop_revokeall", 0);
			return (0);
E 128
E 36
E 21
		}
I 36
		/*
		 * Ensure that vp will not be vgone'd while we
		 * are eliminating its aliases.
		 */
		vp->v_flag |= VXLOCK;
I 136
		simple_unlock(&vp->v_interlock);
E 136
		while (vp->v_flag & VALIASED) {
I 136
			simple_lock(&spechash_slock);
E 136
			for (vq = *vp->v_hashchain; vq; vq = vq->v_specnext) {
				if (vq->v_rdev != vp->v_rdev ||
				    vq->v_type != vp->v_type || vp == vq)
					continue;
I 136
				simple_unlock(&spechash_slock);
E 136
				vgone(vq);
				break;
			}
I 136
			if (vq == NULLVP)
				simple_unlock(&spechash_slock);
E 136
		}
		/*
		 * Remove the lock so that vgone below will
		 * really eliminate the vnode after which time
		 * vgone will awaken any sleepers.
		 */
I 136
		simple_lock(&vp->v_interlock);
E 136
		vp->v_flag &= ~VXLOCK;
E 36
	}
D 136
	vgone(vp);
E 136
I 136
	vgonel(vp, p);
E 136
I 128
	return (0);
E 128
}

/*
I 136
 * Recycle an unused vnode to the front of the free list.
 * Release the passed interlock if the vnode will be recycled.
 */
int
vrecycle(vp, inter_lkp, p)
	struct vnode *vp;
	struct simplelock *inter_lkp;
	struct proc *p;
{

	simple_lock(&vp->v_interlock);
	if (vp->v_usecount == 0) {
		if (inter_lkp)
			simple_unlock(inter_lkp);
		vgonel(vp, p);
		return (1);
	}
	simple_unlock(&vp->v_interlock);
	return (0);
}

/*
E 136
E 17
 * Eliminate all activity associated with a vnode
 * in preparation for reuse.
 */
D 127
void vgone(vp)
E 127
I 127
void
vgone(vp)
E 127
D 136
	register struct vnode *vp;
E 136
I 136
	struct vnode *vp;
E 136
{
D 15
	register struct speclist *slp;
	struct speclist *pslp;
	register struct vnode *vq;
E 15
I 15
D 21
	register struct vnode *vq, **vpp;
E 21
I 21
D 136
	register struct vnode *vq;
E 136
I 136
	struct proc *p = curproc;	/* XXX */

	simple_lock(&vp->v_interlock);
	vgonel(vp, p);
}

/*
 * vgone, with the vp interlock held.
 */
void
vgonel(vp, p)
	struct vnode *vp;
	struct proc *p;
{
	struct vnode *vq;
E 136
E 21
	struct vnode *vx;
D 70
	long count;
E 70
E 15

D 11
	if (vp->v_count > 0)
		panic("vgone: cannot reclaim");
E 11
	/*
I 32
	 * If a vgone (or vclean) is already in progress,
	 * wait until it is done and return.
	 */
	if (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
I 136
		simple_unlock(&vp->v_interlock);
E 136
D 127
		sleep((caddr_t)vp, PINOD);
E 127
I 127
		tsleep((caddr_t)vp, PINOD, "vgone", 0);
E 127
		return;
	}
	/*
E 32
	 * Clean out the filesystem specific data.
	 */
D 11
	vclean(vp);
E 11
I 11
D 40
	vclean(vp, 1);
E 40
I 40
D 136
	vclean(vp, DOCLOSE);
E 136
I 136
	vclean(vp, DOCLOSE, p);
E 136
E 40
E 11
	/*
	 * Delete from old mount point vnode list, if on one.
	 */
D 113
	if (vp->v_mountb) {
		if (vq = vp->v_mountf)
			vq->v_mountb = vp->v_mountb;
		*vp->v_mountb = vq;
		vp->v_mountf = NULL;
		vp->v_mountb = NULL;
E 113
I 113
D 136
	if (vp->v_mount != NULL) {
I 118
		if (vp->v_mntvnodes.le_next == (struct vnode *)0xdeadf ||
		    vp->v_mntvnodes.le_prev == (struct vnode **)0xdeadb)
			panic("vgone: not on queue");
E 118
		LIST_REMOVE(vp, v_mntvnodes);
I 118
		vp->v_mntvnodes.le_next = (struct vnode *)0xdeadf;
		vp->v_mntvnodes.le_prev = (struct vnode **)0xdeadb;
E 118
E 113
I 67
		vp->v_mount = NULL;
E 67
	}
E 136
I 136
	if (vp->v_mount != NULL)
		insmntque(vp, (struct mount *)0);
E 136
	/*
D 129
	 * If special device, remove it from special device alias list.
E 129
I 129
	 * If special device, remove it from special device alias list
	 * if it is on one.
E 129
	 */
D 129
	if (vp->v_type == VBLK || vp->v_type == VCHR) {
E 129
I 129
	if ((vp->v_type == VBLK || vp->v_type == VCHR) && vp->v_specinfo != 0) {
I 136
		simple_lock(&spechash_slock);
E 136
E 129
D 15
		if (speclisth->sl_vp == vp) {
			slp = speclisth;
			speclisth = slp->sl_next;
E 15
I 15
D 21
		vpp = &speclisth[SPECHASH(vp->v_rdev)];
		if (*vpp == vp) {
			*vpp = vp->v_specnext;
E 21
I 21
		if (*vp->v_hashchain == vp) {
			*vp->v_hashchain = vp->v_specnext;
E 21
E 15
		} else {
D 12
			for (slp = speclisth; slp;
E 12
I 12
D 15
			for (pslp = speclisth, slp = pslp->sl_next; slp;
E 12
			     pslp = slp, slp = slp->sl_next) {
				if (slp->sl_vp != vp)
E 15
I 15
D 21
			for (vq = *vpp; vq; vq = vq->v_specnext) {
E 21
I 21
			for (vq = *vp->v_hashchain; vq; vq = vq->v_specnext) {
E 21
				if (vq->v_specnext != vp)
E 15
					continue;
D 15
				pslp->sl_next = slp->sl_next;
E 15
I 15
				vq->v_specnext = vp->v_specnext;
E 15
				break;
			}
D 15
			if (slp == NULL)
E 15
I 15
			if (vq == NULL)
E 15
				panic("missing bdev");
		}
D 15
		FREE(slp, M_VNODE);
E 15
I 15
		if (vp->v_flag & VALIASED) {
D 21
			for (count = 0, vq = *vpp; vq; vq = vq->v_specnext) {
E 21
I 21
D 70
			count = 0;
E 70
I 70
			vx = NULL;
E 70
			for (vq = *vp->v_hashchain; vq; vq = vq->v_specnext) {
E 21
D 27
				if (vq->v_rdev != vp->v_rdev)
E 27
I 27
				if (vq->v_rdev != vp->v_rdev ||
				    vq->v_type != vp->v_type)
E 27
					continue;
D 70
				count++;
E 70
I 70
				if (vx)
					break;
E 70
				vx = vq;
			}
D 70
			if (count == 0)
E 70
I 70
			if (vx == NULL)
E 70
				panic("missing alias");
D 70
			if (count == 1)
E 70
I 70
			if (vq == NULL)
E 70
				vx->v_flag &= ~VALIASED;
			vp->v_flag &= ~VALIASED;
		}
I 136
		simple_unlock(&spechash_slock);
E 136
		FREE(vp->v_specinfo, M_VNODE);
		vp->v_specinfo = NULL;
E 15
	}
	/*
D 100
	 * If it is on the freelist, move it to the head of the list.
E 100
I 100
	 * If it is on the freelist and not already at the head,
D 114
	 * move it to the head of the list.
E 114
I 114
	 * move it to the head of the list. The test of the back
	 * pointer and the reference count of zero is because
	 * it will be removed from the free list by getnewvnode,
	 * but will not have its reference count incremented until
	 * after calling vgone. If the reference count were
	 * incremented first, vgone would (incorrectly) try to
	 * close the previous instance of the underlying object.
	 * So, the back pointer is explicitly set to `0xdeadb' in
	 * getnewvnode after removing it from the freelist to ensure
	 * that we do not try to move it here.
E 114
E 100
	 */
D 100
	if (vp->v_freeb) {
E 100
I 100
D 113
	if (vp->v_freeb && vfreeh != vp) {
E 100
		if (vq = vp->v_freef)
			vq->v_freeb = vp->v_freeb;
		else
			vfreet = vp->v_freeb;
		*vp->v_freeb = vq;
		vp->v_freef = vfreeh;
		vp->v_freeb = &vfreeh;
		vfreeh->v_freeb = &vp->v_freef;
		vfreeh = vp;
E 113
I 113
D 114
	if (vp->v_usecount == 0 && vnode_free_list.tqh_first != vp) {
E 114
I 114
D 136
	if (vp->v_usecount == 0 &&
	    vp->v_freelist.tqe_prev != (struct vnode **)0xdeadb &&
	    vnode_free_list.tqh_first != vp) {
I 118
		if (vp->v_freelist.tqe_next == (struct vnode *)0xdeadf)
			panic("vgone: use 0, not free");
E 118
E 114
		TAILQ_REMOVE(&vnode_free_list, vp, v_freelist);
		TAILQ_INSERT_HEAD(&vnode_free_list, vp, v_freelist);
E 136
I 136
	if (vp->v_usecount == 0) {
		simple_lock(&vnode_free_list_slock);
		if ((vp->v_freelist.tqe_prev != (struct vnode **)0xdeadb) &&
		    vnode_free_list.tqh_first != vp) {
			TAILQ_REMOVE(&vnode_free_list, vp, v_freelist);
			TAILQ_INSERT_HEAD(&vnode_free_list, vp, v_freelist);
		}
		simple_unlock(&vnode_free_list_slock);
E 136
E 113
	}
D 11
	vp->v_type = VNON;
E 11
I 11
	vp->v_type = VBAD;
I 17
}

/*
I 22
 * Lookup a vnode by device number.
 */
I 127
int
E 127
vfinddev(dev, type, vpp)
	dev_t dev;
	enum vtype type;
	struct vnode **vpp;
{
D 136
	register struct vnode *vp;
E 136
I 136
	struct vnode *vp;
	int rc = 0;
E 136

I 136
	simple_lock(&spechash_slock);
E 136
	for (vp = speclisth[SPECHASH(dev)]; vp; vp = vp->v_specnext) {
		if (dev != vp->v_rdev || type != vp->v_type)
			continue;
		*vpp = vp;
D 110
		return (0);
E 110
I 110
D 136
		return (1);
E 136
I 136
		rc = 1;
		break;
E 136
E 110
	}
D 110
	return (1);
E 110
I 110
D 136
	return (0);
E 136
I 136
	simple_unlock(&spechash_slock);
	return (rc);
E 136
E 110
}

/*
E 22
 * Calculate the total number of references to a special device.
 */
I 127
int
E 127
vcount(vp)
D 136
	register struct vnode *vp;
E 136
I 136
	struct vnode *vp;
E 136
{
D 21
	register struct vnode *vq, **vpp;
E 21
I 21
D 124
	register struct vnode *vq;
E 124
I 124
D 136
	register struct vnode *vq, *vnext;
E 136
I 136
	struct vnode *vq, *vnext;
E 136
E 124
E 21
	int count;

I 124
loop:
E 124
	if ((vp->v_flag & VALIASED) == 0)
D 21
		return (vp->v_count);
	vpp = &speclisth[SPECHASH(vp->v_rdev)];
E 21
I 21
		return (vp->v_usecount);
I 136
	simple_lock(&spechash_slock);
E 136
E 21
D 124
loop:
D 21
	for (count = 0, vq = *vpp; vq; vq = vq->v_specnext) {
E 21
I 21
	for (count = 0, vq = *vp->v_hashchain; vq; vq = vq->v_specnext) {
E 124
I 124
	for (count = 0, vq = *vp->v_hashchain; vq; vq = vnext) {
		vnext = vq->v_specnext;
E 124
E 21
D 27
		if (vq->v_rdev != vp->v_rdev)
E 27
I 27
		if (vq->v_rdev != vp->v_rdev || vq->v_type != vp->v_type)
E 27
			continue;
		/*
		 * Alias, but not in use, so flush it out.
		 */
D 21
		if (vq->v_count == 0) {
E 21
I 21
D 124
		if (vq->v_usecount == 0) {
E 124
I 124
		if (vq->v_usecount == 0 && vq != vp) {
I 136
			simple_unlock(&spechash_slock);
E 136
E 124
E 21
			vgone(vq);
			goto loop;
		}
D 21
		count += vq->v_count;
E 21
I 21
		count += vq->v_usecount;
E 21
	}
I 136
	simple_unlock(&spechash_slock);
E 136
	return (count);
I 19
}

/*
 * Print out a description of a vnode.
 */
static char *typename[] =
D 30
	{ "VNON", "VREG", "VDIR", "VBLK", "VCHR", "VLNK", "VSOCK", "VBAD" };
E 30
I 30
   { "VNON", "VREG", "VDIR", "VBLK", "VCHR", "VLNK", "VSOCK", "VFIFO", "VBAD" };
E 30

I 126
void
E 126
vprint(label, vp)
	char *label;
	register struct vnode *vp;
{
I 84
D 93
	USES_VOP_PRINT;
E 93
E 84
I 23
	char buf[64];
E 23

	if (label != NULL)
		printf("%s: ", label);
I 118
	printf("num %d ", vp->v_spare[0]);
E 118
D 21
	printf("type %s, count %d, ", typename[vp->v_type], vp->v_count);
E 21
I 21
D 23
	printf("type %s, usecount %d, refcount %d,\n\t", typename[vp->v_type],
E 23
I 23
D 60
	printf("type %s, usecount %d, refcount %d,", typename[vp->v_type],
E 23
		vp->v_usecount, vp->v_holdcnt);
E 60
I 60
	printf("type %s, usecount %d, writecount %d, refcount %d,",
		typename[vp->v_type], vp->v_usecount, vp->v_writecount,
		vp->v_holdcnt);
E 60
I 23
	buf[0] = '\0';
	if (vp->v_flag & VROOT)
		strcat(buf, "|VROOT");
	if (vp->v_flag & VTEXT)
		strcat(buf, "|VTEXT");
D 40
	if (vp->v_flag & VXLOCK)
		strcat(buf, "|VXLOCK");
	if (vp->v_flag & VXWANT)
		strcat(buf, "|VXWANT");
E 40
I 40
	if (vp->v_flag & VSYSTEM)
		strcat(buf, "|VSYSTEM");
E 40
D 50
	if (vp->v_flag & VEXLOCK)
		strcat(buf, "|VEXLOCK");
	if (vp->v_flag & VSHLOCK)
		strcat(buf, "|VSHLOCK");
	if (vp->v_flag & VLWAIT)
		strcat(buf, "|VLWAIT");
E 50
D 40
	if (vp->v_flag & VALIASED)
		strcat(buf, "|VALIASED");
E 40
I 40
	if (vp->v_flag & VXLOCK)
		strcat(buf, "|VXLOCK");
	if (vp->v_flag & VXWANT)
		strcat(buf, "|VXWANT");
E 40
	if (vp->v_flag & VBWAIT)
		strcat(buf, "|VBWAIT");
I 40
	if (vp->v_flag & VALIASED)
		strcat(buf, "|VALIASED");
E 40
	if (buf[0] != '\0')
		printf(" flags (%s)", &buf[1]);
D 113
	printf("\n\t");
E 23
E 21
	VOP_PRINT(vp);
E 113
I 113
	if (vp->v_data == NULL) {
		printf("\n");
	} else {
		printf("\n\t");
		VOP_PRINT(vp);
	}
E 113
I 23
}
I 39

I 56
#ifdef DEBUG
/*
 * List all of the locked vnodes in the system.
 * Called when debugging the kernel.
 */
I 127
void
E 127
printlockedvnodes()
{
I 84
D 93
	USES_VOP_ISLOCKED;
E 93
E 84
D 141
	register struct mount *mp;
	register struct vnode *vp;
E 141
I 141
	struct proc *p = curproc;	/* XXX */
	struct mount *mp, *nmp;
	struct vnode *vp;
E 141

	printf("Locked vnodes\n");
D 113
	mp = rootfs;
	do {
		for (vp = mp->mnt_mounth; vp; vp = vp->v_mountf)
E 113
I 113
D 133
	for (mp = mountlist.tqh_first; mp != NULL; mp = mp->mnt_list.tqe_next) {
E 133
I 133
D 141
	for (mp = mountlist.cqh_first; mp != (void *)&mountlist;
	     mp = mp->mnt_list.cqe_next) {
E 141
I 141
	simple_lock(&mountlist_slock);
	for (mp = mountlist.cqh_first; mp != (void *)&mountlist; mp = nmp) {
		if (vfs_busy(mp, LK_NOWAIT, &mountlist_slock, p)) {
			nmp = mp->mnt_list.cqe_next;
			continue;
		}
E 141
E 133
		for (vp = mp->mnt_vnodelist.lh_first;
		     vp != NULL;
D 133
		     vp = vp->v_mntvnodes.le_next)
E 133
I 133
		     vp = vp->v_mntvnodes.le_next) {
E 133
E 113
			if (VOP_ISLOCKED(vp))
				vprint((char *)0, vp);
I 133
		}
I 141
		simple_lock(&mountlist_slock);
		nmp = mp->mnt_list.cqe_next;
		vfs_unbusy(mp, p);
E 141
E 133
D 113
		mp = mp->mnt_next;
	} while (mp != rootfs);
E 113
I 113
	}
I 141
	simple_unlock(&mountlist_slock);
E 141
E 113
}
#endif
I 130

/*
 * Top level filesystem related information gathering.
 */
int
vfs_sysctl(name, namelen, oldp, oldlenp, newp, newlen, p)
	int *name;
	u_int namelen;
	void *oldp;
	size_t *oldlenp;
	void *newp;
	size_t newlen;
	struct proc *p;
{
	struct ctldebug *cdp;
	struct vfsconf *vfsp;

	/* all sysctl names at this level are at least name and field */
	if (namelen < 2)
		return (ENOTDIR);		/* overloaded */
	if (name[0] != VFS_GENERIC) {
		for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next)
			if (vfsp->vfc_typenum == name[0])
				break;
		if (vfsp == NULL)
			return (EOPNOTSUPP);
		return ((*vfsp->vfc_vfsops->vfs_sysctl)(&name[1], namelen - 1,
		    oldp, oldlenp, newp, newlen, p));
	}
	switch (name[1]) {
	case VFS_MAXTYPENUM:
		return (sysctl_rdint(oldp, oldlenp, newp, maxvfsconf));
	case VFS_CONF:
		if (namelen < 3)
			return (ENOTDIR);	/* overloaded */
		for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next)
			if (vfsp->vfc_typenum == name[2])
				break;
		if (vfsp == NULL)
			return (EOPNOTSUPP);
		return (sysctl_rdstruct(oldp, oldlenp, newp, vfsp,
		    sizeof(struct vfsconf)));
	}
	return (EOPNOTSUPP);
}
E 130

E 56
int kinfo_vdebug = 1;
int kinfo_vgetfailed;
#define KINFO_VNODESLOP	10
/*
D 105
 * Dump vnode list (via kinfo).
E 105
I 105
 * Dump vnode list (via sysctl).
E 105
 * Copyout address of vnode followed by vnode.
 */
I 48
/* ARGSUSED */
I 127
int
E 127
E 48
D 105
kinfo_vnode(op, where, acopysize, arg, aneeded)
I 48
	int op;
E 105
I 105
D 141
sysctl_vnode(where, sizep)
E 141
I 141
sysctl_vnode(where, sizep, p)
E 141
E 105
E 48
	char *where;
D 48
	int *acopysize, *aneeded;
E 48
I 48
D 105
	int *acopysize, arg, *aneeded;
E 105
I 105
D 106
	int *sizep;
E 106
I 106
	size_t *sizep;
I 141
	struct proc *p;
E 141
E 106
E 105
E 48
{
D 113
	register struct mount *mp = rootfs;
D 44
	register struct vnode *nextvp;
E 44
I 40
	struct mount *omp;
E 113
I 113
D 141
	register struct mount *mp, *nmp;
E 141
I 141
	struct mount *mp, *nmp;
E 141
E 113
E 40
D 136
	struct vnode *vp;
E 136
I 136
	struct vnode *nvp, *vp;
E 136
D 48
	register needed = 0;
E 48
D 141
	register char *bp = where, *savebp;
E 141
I 141
	char *bp = where, *savebp;
E 141
D 86
	char *ewhere = where + *acopysize;
E 86
I 86
	char *ewhere;
E 86
	int error;

#define VPTRSZ	sizeof (struct vnode *)
#define VNODESZ	sizeof (struct vnode)
	if (where == NULL) {
D 105
		*aneeded = (numvnodes + KINFO_VNODESLOP) * (VPTRSZ + VNODESZ);
E 105
I 105
		*sizep = (numvnodes + KINFO_VNODESLOP) * (VPTRSZ + VNODESZ);
E 105
		return (0);
	}
I 86
D 105
	ewhere = where + *acopysize;
E 105
I 105
	ewhere = where + *sizep;
E 105
E 86
		
I 141
	simple_lock(&mountlist_slock);
E 141
D 44
#define RETRY	bp = savebp ; goto again
E 44
D 113
	do {
I 40
		if (vfs_busy(mp)) {
D 42
			mp = mp->m_next;
E 42
I 42
			mp = mp->mnt_next;
E 113
I 113
D 133
	for (mp = mountlist.tqh_first; mp != NULL; mp = nmp) {
		nmp = mp->mnt_list.tqe_next;
E 133
I 133
	for (mp = mountlist.cqh_first; mp != (void *)&mountlist; mp = nmp) {
D 141
		nmp = mp->mnt_list.cqe_next;
E 133
		if (vfs_busy(mp))
E 141
I 141
		if (vfs_busy(mp, LK_NOWAIT, &mountlist_slock, p)) {
			nmp = mp->mnt_list.cqe_next;
E 141
E 113
E 42
			continue;
I 141
		}
E 141
D 113
		}
E 113
E 40
D 45
		/*
		 * A vget can fail if the vnode is being
		 * recycled.  In this (rare) case, we have to start
		 * over with this filesystem.  Also, have to
D 44
		 * check that nextvp is still associated
E 44
I 44
		 * check that the next vp is still associated
E 44
		 * with this filesystem.  RACE: could have been
D 44
		 * recycled onto same filesystem.
E 44
I 44
		 * recycled onto the same filesystem.
E 44
		 */
E 45
		savebp = bp;
again:
I 136
		simple_lock(&mntvnode_slock);
E 136
D 42
		nextvp = mp->m_mounth;
E 42
I 42
D 44
		nextvp = mp->mnt_mounth;
E 42
		while (vp = nextvp) {
E 44
I 44
D 113
		for (vp = mp->mnt_mounth; vp; vp = vp->v_mountf) {
E 113
I 113
		for (vp = mp->mnt_vnodelist.lh_first;
		     vp != NULL;
D 136
		     vp = vp->v_mntvnodes.le_next) {
E 136
I 136
		     vp = nvp) {
E 136
E 113
I 45
			/*
			 * Check that the vp is still associated with
			 * this filesystem.  RACE: could have been
			 * recycled onto the same filesystem.
			 */
E 45
			if (vp->v_mount != mp) {
I 136
				simple_unlock(&mntvnode_slock);
E 136
				if (kinfo_vdebug)
					printf("kinfo: vp changed\n");
				bp = savebp;
				goto again;
			}
I 136
			nvp = vp->v_mntvnodes.le_next;
E 136
E 44
D 45
			if (vget(vp)) {
				if (kinfo_vdebug)
					printf("kinfo: vget failed\n");
				kinfo_vgetfailed++;
D 44
				RETRY;
E 44
I 44
				bp = savebp;
				goto again;
E 44
			}
E 45
D 44
			if (vp->v_mount != mp) {
				if (kinfo_vdebug)
					printf("kinfo: vp changed\n");
				vput(vp);
				RETRY;
			}
E 44
D 105
			if ((bp + VPTRSZ + VNODESZ <= ewhere) && 
			    ((error = copyout((caddr_t)&vp, bp, VPTRSZ)) ||
			     (error = copyout((caddr_t)vp, bp + VPTRSZ, 
D 45
			      VNODESZ)))) {
				vput(vp);
E 45
I 45
			      VNODESZ))))
E 105
I 105
			if (bp + VPTRSZ + VNODESZ > ewhere) {
I 136
				simple_unlock(&mntvnode_slock);
E 136
				*sizep = bp - where;
				return (ENOMEM);
			}
I 136
			simple_unlock(&mntvnode_slock);
E 136
			if ((error = copyout((caddr_t)&vp, bp, VPTRSZ)) ||
			   (error = copyout((caddr_t)vp, bp + VPTRSZ, VNODESZ)))
E 105
E 45
				return (error);
D 45
			}
E 45
			bp += VPTRSZ + VNODESZ;
I 136
			simple_lock(&mntvnode_slock);
E 136
D 44
			nextvp = vp->v_mountf;
E 44
D 45
			vput(vp);
E 45
		}
I 136
		simple_unlock(&mntvnode_slock);
E 136
I 40
D 113
		omp = mp;
E 40
D 42
		mp = mp->m_next;
E 42
I 42
		mp = mp->mnt_next;
E 42
I 40
		vfs_unbusy(omp);
E 40
	} while (mp != rootfs);
E 113
I 113
D 141
		vfs_unbusy(mp);
E 141
I 141
		simple_lock(&mountlist_slock);
		nmp = mp->mnt_list.cqe_next;
		vfs_unbusy(mp, p);
E 141
	}
I 141
	simple_unlock(&mountlist_slock);
E 141
E 113

D 105
	*aneeded = bp - where;
	if (bp > ewhere)
		*acopysize = ewhere - where;
	else
		*acopysize = bp - where;
E 105
I 105
	*sizep = bp - where;
E 105
	return (0);
I 119
}

/*
 * Check to see if a filesystem is mounted on a block device.
 */
int
vfs_mountedon(vp)
D 136
	register struct vnode *vp;
E 136
I 136
	struct vnode *vp;
E 136
{
D 136
	register struct vnode *vq;
E 136
I 136
	struct vnode *vq;
	int error = 0;
E 136

	if (vp->v_specflags & SI_MOUNTEDON)
		return (EBUSY);
	if (vp->v_flag & VALIASED) {
I 136
		simple_lock(&spechash_slock);
E 136
		for (vq = *vp->v_hashchain; vq; vq = vq->v_specnext) {
			if (vq->v_rdev != vp->v_rdev ||
			    vq->v_type != vp->v_type)
				continue;
D 136
			if (vq->v_specflags & SI_MOUNTEDON)
				return (EBUSY);
E 136
I 136
			if (vq->v_specflags & SI_MOUNTEDON) {
				error = EBUSY;
				break;
			}
E 136
		}
I 136
		simple_unlock(&spechash_slock);
E 136
	}
D 136
	return (0);
E 136
I 136
	return (error);
E 136
I 133
}

/*
 * Unmount all filesystems. The list is traversed in reverse order
 * of mounting to avoid dependencies.
 */
void
vfs_unmountall()
{
	struct mount *mp, *nmp;
I 141
	struct proc *p = curproc;	/* XXX */
E 141

I 141
	/*
	 * Since this only runs when rebooting, it is not interlocked.
	 */
E 141
	for (mp = mountlist.cqh_last; mp != (void *)&mountlist; mp = nmp) {
		nmp = mp->mnt_list.cqe_prev;
D 141
		(void) dounmount(mp, MNT_FORCE, &proc0);
E 141
I 141
		(void) dounmount(mp, MNT_FORCE, p);
E 141
	}
E 133
}

/*
 * Build hash lists of net addresses and hang them off the mount point.
 * Called by ufs_mount() to set up the lists of export addresses.
 */
static int
vfs_hang_addrlist(mp, nep, argp)
	struct mount *mp;
	struct netexport *nep;
	struct export_args *argp;
{
	register struct netcred *np;
	register struct radix_node_head *rnh;
	register int i;
	struct radix_node *rn;
	struct sockaddr *saddr, *smask = 0;
	struct domain *dom;
	int error;

	if (argp->ex_addrlen == 0) {
		if (mp->mnt_flag & MNT_DEFEXPORTED)
			return (EPERM);
		np = &nep->ne_defexported;
		np->netc_exflags = argp->ex_flags;
		np->netc_anon = argp->ex_anon;
		np->netc_anon.cr_ref = 1;
		mp->mnt_flag |= MNT_DEFEXPORTED;
		return (0);
	}
	i = sizeof(struct netcred) + argp->ex_addrlen + argp->ex_masklen;
	np = (struct netcred *)malloc(i, M_NETADDR, M_WAITOK);
	bzero((caddr_t)np, i);
	saddr = (struct sockaddr *)(np + 1);
	if (error = copyin(argp->ex_addr, (caddr_t)saddr, argp->ex_addrlen))
		goto out;
	if (saddr->sa_len > argp->ex_addrlen)
		saddr->sa_len = argp->ex_addrlen;
	if (argp->ex_masklen) {
		smask = (struct sockaddr *)((caddr_t)saddr + argp->ex_addrlen);
		error = copyin(argp->ex_addr, (caddr_t)smask, argp->ex_masklen);
		if (error)
			goto out;
		if (smask->sa_len > argp->ex_masklen)
			smask->sa_len = argp->ex_masklen;
	}
	i = saddr->sa_family;
	if ((rnh = nep->ne_rtable[i]) == 0) {
		/*
		 * Seems silly to initialize every AF when most are not
		 * used, do so on demand here
		 */
		for (dom = domains; dom; dom = dom->dom_next)
			if (dom->dom_family == i && dom->dom_rtattach) {
				dom->dom_rtattach((void **)&nep->ne_rtable[i],
					dom->dom_rtoffset);
				break;
			}
		if ((rnh = nep->ne_rtable[i]) == 0) {
			error = ENOBUFS;
			goto out;
		}
	}
	rn = (*rnh->rnh_addaddr)((caddr_t)saddr, (caddr_t)smask, rnh,
		np->netc_rnodes);
D 132
	if (rn == 0 || np != (struct netcred *)rn) { /* already exists */
		error = EPERM;
		goto out;
E 132
I 132
	if (rn == 0) {
		/*
		 * One of the reasons that rnh_addaddr may fail is that
		 * the entry already exists. To check for this case, we
		 * look up the entry to see if it is there. If so, we
		 * do not need to make a new entry but do return success.
		 */
		free(np, M_NETADDR);
		rn = (*rnh->rnh_matchaddr)((caddr_t)saddr, rnh);
		if (rn != 0 && (rn->rn_flags & RNF_ROOT) == 0 &&
		    ((struct netcred *)rn)->netc_exflags == argp->ex_flags &&
		    !bcmp((caddr_t)&((struct netcred *)rn)->netc_anon,
			    (caddr_t)&argp->ex_anon, sizeof(struct ucred)))
			return (0);
		return (EPERM);
E 132
	}
	np->netc_exflags = argp->ex_flags;
	np->netc_anon = argp->ex_anon;
	np->netc_anon.cr_ref = 1;
	return (0);
out:
	free(np, M_NETADDR);
	return (error);
}

/* ARGSUSED */
static int
vfs_free_netcred(rn, w)
	struct radix_node *rn;
	caddr_t w;
{
	register struct radix_node_head *rnh = (struct radix_node_head *)w;

	(*rnh->rnh_deladdr)(rn->rn_key, rn->rn_mask, rnh);
	free((caddr_t)rn, M_NETADDR);
	return (0);
}
D 127
	
E 127
I 127

E 127
/*
 * Free the net address hash lists that are hanging off the mount points.
 */
static void
vfs_free_addrlist(nep)
	struct netexport *nep;
{
	register int i;
	register struct radix_node_head *rnh;

	for (i = 0; i <= AF_MAX; i++)
		if (rnh = nep->ne_rtable[i]) {
			(*rnh->rnh_walktree)(rnh, vfs_free_netcred,
			    (caddr_t)rnh);
			free((caddr_t)rnh, M_RTABLE);
			nep->ne_rtable[i] = 0;
		}
}

int
vfs_export(mp, nep, argp)
	struct mount *mp;
	struct netexport *nep;
	struct export_args *argp;
{
	int error;

	if (argp->ex_flags & MNT_DELEXPORT) {
		vfs_free_addrlist(nep);
		mp->mnt_flag &= ~(MNT_EXPORTED | MNT_DEFEXPORTED);
	}
	if (argp->ex_flags & MNT_EXPORTED) {
		if (error = vfs_hang_addrlist(mp, nep, argp))
			return (error);
		mp->mnt_flag |= MNT_EXPORTED;
	}
	return (0);
}

struct netcred *
vfs_export_lookup(mp, nep, nam)
	register struct mount *mp;
	struct netexport *nep;
	struct mbuf *nam;
{
	register struct netcred *np;
	register struct radix_node_head *rnh;
	struct sockaddr *saddr;

	np = NULL;
	if (mp->mnt_flag & MNT_EXPORTED) {
		/*
		 * Lookup in the export list first.
		 */
		if (nam != NULL) {
			saddr = mtod(nam, struct sockaddr *);
			rnh = nep->ne_rtable[saddr->sa_family];
			if (rnh != NULL) {
				np = (struct netcred *)
					(*rnh->rnh_matchaddr)((caddr_t)saddr,
							      rnh);
				if (np && np->netc_rnodes->rn_flags & RNF_ROOT)
					np = NULL;
			}
		}
		/*
		 * If no address match, use the default if it exists.
		 */
		if (np == NULL && mp->mnt_flag & MNT_DEFEXPORTED)
			np = &nep->ne_defexported;
	}
	return (np);
E 119
}
E 39
D 28

strcat(src, append)
	register char *src, *append;
{

	for (; *src; ++src)
		/* void */;
	while (*src++ = *append++)
		/* void */;
E 23
E 19
E 17
E 11
E 9
}
E 28
E 8
E 1
