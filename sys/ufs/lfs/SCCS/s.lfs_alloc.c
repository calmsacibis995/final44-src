h44396
s 00003/00001/00222
d D 8.7 95/05/14 00:28:10 mckusick 145 144
c new lock initialization
e
s 00001/00003/00222
d D 8.6 95/05/08 12:14:39 mckusick 144 143
c update from margo
e
s 00002/00002/00223
d D 8.5 95/03/21 00:27:55 mckusick 143 142
c daddr_t => ufs_daddr_t
e
s 00001/00002/00224
d D 8.4 94/01/04 22:14:28 bostic 142 141
c lint
e
s 00004/00003/00222
d D 8.3 93/09/23 16:14:50 bostic 141 140
c changes for 4.4BSD-Lite requested by USL
e
s 00004/00004/00221
d D 8.2 93/09/21 07:26:47 bostic 140 139
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00223
d D 8.1 93/06/11 16:27:11 bostic 139 138
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00011/00217
d D 7.56 92/12/10 14:20:05 margo 138 137
c Use balloc to extend Ifile.
e
s 00014/00005/00214
d D 7.55 92/11/17 13:21:41 margo 137 136
c Initialize on-disk inode structure correctly.  Use di_inumber.
e
s 00004/00001/00215
d D 7.54 92/09/02 07:58:53 margo 136 135
c Check for out of space condition before extending ifile.
e
s 00000/00006/00216
d D 7.53 92/08/25 14:35:10 bostic 135 134
c getblk cannot return a NULL bp, don't bother checking for it.
e
s 00011/00005/00211
d D 7.52 92/08/21 17:24:40 bostic 134 133
c Change LFS_UBWRITE calls to VOP_BWRITE, add inode accounting.
e
s 00001/00010/00215
d D 7.51 92/08/01 15:40:35 bostic 133 132
c delete VERBOSE #ifdef's
e
s 00000/00004/00225
d D 7.50 92/07/29 17:12:10 bostic 132 131
c no longer need printfs; extending ifile now works
e
s 00002/00000/00227
d D 7.49 92/07/23 16:25:25 bostic 131 130
c Do block accounting in terms of disk sectors, not file system blocks.
c When initializing an inode, set blocks to 0 (ffs doesn't do this because it has
c read the inode from disk where it was zeroed).
e
s 00001/00001/00226
d D 7.48 92/07/20 16:18:06 bostic 130 129
c compute number of inode blocks in terms of disk blocks
e
s 00014/00005/00213
d D 7.47 92/07/05 14:35:18 margo 129 128
c describe ap structure (Kirk); make VDIROP set right
e
s 00001/00002/00217
d D 7.46 92/06/23 00:06:19 bostic 128 127
c directory ops, unmount, minor cleanup; from Margo Seltzer
e
s 00005/00019/00214
d D 7.45 92/05/15 13:54:53 heideman 127 126
c vnodeop argument macro expansion
e
s 00004/00001/00229
d D 7.44 92/05/15 12:20:24 heideman 126 125
c lfs_vfree now returns an int
e
s 00020/00010/00210
d D 7.43 92/05/14 17:28:37 heideman 125 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/14 17:04:54 heideman 124 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/14 16:45:46 heideman 123 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/14 16:35:43 heideman 122 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/14 15:55:34 heideman 121 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/14 15:41:49 heideman 120 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/14 14:47:45 heideman 119 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/14 12:51:06 heideman 118 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/14 11:48:26 heideman 117 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/14 10:28:55 heideman 116 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/13 23:07:15 heideman 115 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/13 18:54:06 heideman 114 112
c vnode interface conversion
e
s 00020/00010/00210
d R 7.43 92/05/13 18:26:13 heideman 113 112
c vnode interface conversion
e
s 00003/00001/00217
d D 7.42 92/05/04 16:22:03 mckusick 112 111
c lint
e
s 00014/00000/00204
d D 7.41 92/02/27 17:07:20 staelin 111 110
c only delete space used by inode, on inode deletion; required
c corresponding change in lfs_segment.c on inode allocation
e
s 00005/00004/00199
d D 7.40 92/01/30 13:08:04 bostic 110 109
c initialize the size field, FFS does it in newfs, we don't
e
s 00058/00030/00145
d D 7.39 91/12/31 14:07:43 bostic 109 108
c extend the IFILE, minor cleanups
e
s 00006/00002/00169
d D 7.38 91/12/16 17:48:26 mckusick 108 107
c dynamically allocate private part
e
s 00008/00009/00163
d D 7.37 91/12/14 18:46:09 bostic 107 106
c use LFS_IRELEASE/LFS_IWRITE macros
e
s 00006/00003/00166
d D 7.36 91/12/06 16:39:12 bostic 106 105
c LFS version 2; minor cleanups, nothing important
e
s 00018/00015/00151
d D 7.35 91/11/05 15:31:24 mckusick 105 104
c reorganization to move ufsmount ops to be vnode ops
e
s 00010/00008/00156
d D 7.34 91/11/01 17:36:17 bostic 104 103
c don't typedef struct lfs for now
c UFS/FFS split for LFS version 1; lfs moves down one level
e
s 00048/00129/00116
d D 7.33 91/11/01 17:28:50 bostic 103 102
c move ENTRY macro into lfs.h; reorganize source, checkpoint before
c integration
e
s 00001/00000/00244
d D 7.32 91/10/09 11:22:40 bostic 102 101
c lint
e
s 00006/00005/00238
d D 7.31 91/10/03 19:26:34 bostic 101 100
c minor cleanups
e
s 00079/00033/00164
d D 7.30 91/10/02 09:00:22 bostic 100 99
c checkpoint
e
s 00038/00018/00159
d D 7.29 91/09/25 14:30:03 bostic 99 98
c checkpoint, but not because it's working
e
s 00119/01017/00058
d D 7.28 91/09/20 13:47:29 bostic 98 97
c checkpoint before lfs_iupdat -> ITIMES; reads almost work...
e
s 00007/00007/01068
d D 7.27 91/08/23 16:37:25 mckusick 97 96
c use fs->fs_fmod = 1, not fs->fs_mod++
e
s 00006/00003/01069
d D 7.26 91/05/02 15:01:38 mckusick 96 95
c resize buffer only after successful allocation (avoid stray bufsize)
e
s 00002/00001/01070
d D 7.25 91/04/16 11:16:00 mckusick 95 94
c do not panic on "freeing free inode" if filesystem mounted read-only
e
s 00008/00008/01063
d D 7.24 91/03/19 10:30:20 karels 94 93
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; remove ../ufs/ from includes; consolidate *nullops();
c chown/fchmod use proc's credentials, not file's
e
s 00004/00007/01067
d D 7.23 90/12/05 16:08:23 mckusick 93 92
c update for new VM
e
s 00018/00004/01056
d D 7.22 90/09/01 18:06:23 mckusick 92 91
c need to restore quota credit if allocation fails
e
s 00001/00001/01059
d D 7.21 90/08/24 09:39:31 mckusick 91 90
c brealloc => allocbuf
e
s 00001/00011/01059
d D 7.20 90/06/28 22:30:09 bostic 90 89
c new copyright notice
e
s 00009/00022/01061
d D 7.19 90/05/24 17:00:00 mckusick 89 88
c print out offending uid for filesystem full error messages
e
s 00000/00001/01083
d D 7.18 90/05/04 14:34:19 mckusick 88 87
c delete unneeded headers
e
s 00009/00010/01075
d D 7.17 90/05/02 19:32:28 mckusick 87 86
c new interface to chkdq; clean up u. area access
e
s 00001/00001/01084
d D 7.16 90/01/05 11:42:49 mckusick 86 85
c missing fsbtodb (from noemi@osf.org)
e
s 00016/00000/01069
d D 7.15 89/12/30 22:46:51 mckusick 85 84
c badblock moves into this file
e
s 00002/00002/01067
d D 7.14 89/12/21 13:05:23 mckusick 84 83
c only account for disk blocks when they are actually allocated
e
s 00038/00047/01031
d D 7.13 89/11/30 23:05:27 mckusick 83 82
c major overhaul to handle logical buffer pool (not quite right yet)
e
s 00001/00000/01077
d D 7.12 89/11/12 10:27:13 mckusick 82 81
c clear i_flags when allocating new inodes
e
s 00008/00007/01069
d D 7.11 89/08/26 14:12:38 mckusick 81 80
c generalize the buffer pool so that NFS can become a client
e
s 00007/00001/01069
d D 7.10 89/06/07 16:51:12 mckusick 80 79
c assign a new generation number when allocating an inode
e
s 00095/00068/00975
d D 7.9 89/05/09 17:21:47 mckusick 79 78
c merge in vnodes
e
s 00010/00005/01033
d D 7.8 88/06/29 17:15:04 bostic 78 77
c install approved copyright notice
e
s 00008/00007/01030
d D 7.7 88/05/24 19:42:52 mckusick 77 76
c lint
e
s 00008/00002/01029
d D 7.6 88/05/23 20:11:03 bostic 76 75
c added Berkeley specific header
e
s 00046/00045/00985
d D 7.5 88/05/01 23:50:31 mckusick 75 74
c macroize cylinder group array references to allow dynamic tables
e
s 00001/00002/01029
d D 7.4 87/11/23 17:42:45 mckusick 74 72
c lint from torek
e
s 00001/00001/01030
d R 7.4 87/09/09 16:09:57 mckusick 73 72
c allow cg's to start at frag instead of block boundries
e
s 00006/00006/01025
d D 7.3 87/06/05 00:05:31 mckusick 72 71
c change free() to blkfree() to allow for malloc()/free()
e
s 00004/00007/01027
d D 7.2 87/04/02 15:49:06 karels 71 69
c working with pack labels
e
s 00051/00007/01027
d D 7.1.1.1 87/04/02 15:41:03 karels 70 69
c add ifdefs for dev_bsize (almost working)
e
s 00001/00001/01033
d D 7.1 86/06/05 00:11:15 mckusick 69 68
c 4.3BSD release version
e
s 00002/00001/01032
d D 6.19 86/02/19 17:56:00 karels 68 67
c lint
e
s 00011/00002/01022
d D 6.18 85/11/11 19:42:14 mckusick 67 66
c must unhash blocks at the beginning of a new fragment
e
s 00041/00002/00983
d D 6.17 85/10/23 16:53:25 mckusick 66 65
c switch between optimizing for time and space based on fragmentation
e
s 00001/00001/00984
d D 6.16 85/09/17 18:28:13 eric 65 64
c facilities in syslog
e
s 00008/00004/00977
d D 6.15 85/09/11 21:17:05 mckusick 64 63
c allow users to specify optimization preference
e
s 00007/00001/00974
d D 6.14 85/06/08 14:48:54 mckusick 63 62
c Add copyright
e
s 00000/00001/00975
d D 6.13 85/03/19 20:48:13 mckusick 62 61
c eliminate extraneous include of conf.h
e
s 00002/00001/00974
d D 6.12 85/03/12 13:34:37 ralph 61 60
c log file system full, etc. rather than printf.
e
s 00004/00001/00971
d D 6.11 85/01/14 17:02:01 mckusick 60 59
c when reallocating fragments, place in block rather than next bigger fragment
e
s 00011/00006/00961
d D 6.10 85/01/10 19:31:11 mckusick 59 58
c fully scan inode map before giving up (eg do not depend on cg_irotor)
e
s 00017/00006/00950
d D 6.9 85/01/10 19:27:53 mckusick 58 57
c tune up blkpref() routine to better handle fs_maxbpg switches
e
s 00007/00012/00949
d D 6.8 85/01/07 14:31:40 mckusick 57 56
c retain use of bcopy as savings of playing with buffers seems minimal;
c clear B_DELWRI flag on old buffer as data is no longer needed
e
s 00012/00003/00949
d D 6.7 84/12/10 16:34:08 mckusick 56 55
c swap buffers rather than copying when increasing size of fragments
e
s 00005/00005/00947
d D 6.6 84/09/28 15:50:10 mckusick 55 54
c fix units bug in fragextend
e
s 00011/00011/00941
d D 6.5 84/08/29 20:25:02 bloom 54 53
c Change to includes.  no more ../h
e
s 00027/00012/00925
d D 6.4 84/07/28 17:44:58 mckusick 53 52
c speed up inode map search in ialloccg
e
s 00007/00007/00930
d D 6.3 84/02/06 17:49:26 mckusick 52 50
c missing brelse() when determining that cylinder group is full
e
s 00004/00006/00931
d R 6.3 84/02/06 10:58:27 mckusick 51 50
c missing brelse() when checking for cylinder group full
e
s 00001/00001/00936
d D 6.2 83/09/28 17:52:32 karels 50 49
c no ifree(NULL,...) on failed iget
e
s 00000/00000/00937
d D 6.1 83/07/29 06:40:27 sam 49 48
c 4.2 distribution
e
s 00006/00004/00931
d D 2.26 83/05/27 12:49:10 sam 48 47
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00020/00006/00915
d D 2.25 83/05/21 15:41:32 sam 47 46
c implement i_blocks field; quota routines now return error (from kre)
e
s 00009/00013/00912
d D 2.24 83/03/21 19:53:22 sam 46 45
c use freespace macro and fs_fragshift where possible
e
s 00001/00001/00924
d D 2.23 83/02/10 13:23:57 mckusick 45 44
c have to start the brute force search in the right place
e
s 00003/00003/00922
d D 2.22 83/02/10 12:51:41 sam 44 43
c missing a cylinder group in brute force search
e
s 00012/00006/00913
d D 2.21 83/01/14 12:12:53 mckusick 43 42
c verify blocks available after reading cylinder group block
c read only actual cylinder group data (fs_cgsize) instead of fs_bsize.
e
s 00003/00005/00916
d D 2.20 82/12/17 11:47:58 sam 42 41
c sun merge
e
s 00086/00163/00835
d D 2.19 82/11/13 22:52:00 sam 41 40
c merge of 4.1b and 4.1c
e
s 00001/00001/00997
d D 2.18 82/10/21 20:58:49 root 40 39
c lint
e
s 00001/00001/00997
d D 2.17 82/10/19 10:31:45 root 39 38
c more lint
e
s 00007/00007/00991
d D 2.16 82/10/17 21:50:34 root 38 37
c more lint
e
s 00006/00006/00992
d D 2.15 82/10/17 20:54:36 root 37 36
c lint
e
s 00002/00005/00996
d D 2.14 82/10/17 14:06:00 root 36 35
c fix lint
e
s 00000/00133/01001
d D 2.13 82/10/16 10:53:30 root 35 34
c add ufs_subr.c
e
s 00002/00002/01132
d D 2.12 82/10/10 16:02:20 root 34 33
c move vax header files to their own directory
e
s 00008/00007/01126
d D 2.11 82/09/06 22:57:09 root 33 32
c 
e
s 00003/00003/01130
d D 2.10 82/08/03 14:01:22 sam 32 31
c cosmetics
e
s 00013/00000/01120
d D 2.9 82/07/22 13:01:47 kre 31 30
c disc quotas
e
s 00002/00002/01118
d D 2.8 82/07/15 20:47:42 root 30 29
c blkclr->bzero
e
s 00014/00022/01106
d D 2.7 82/06/14 22:59:14 root 29 28
c fixes to interactions of new fs and buffer cache with partial blocks
c including removal of superblocks from cache and refined readahead and
c brealloc routine
e
s 00005/00000/01123
d D 2.6 82/06/07 23:48:28 mckusick 28 27
c update mod times of cylinder groups
e
s 00052/00013/01071
d D 2.5 82/05/07 21:14:46 mckusick 27 26
c put in more info before panics
e
s 00016/00022/01068
d D 2.4 82/04/19 19:34:27 mckusic 26 25
c merge into new file system
e
s 00027/00024/01063
d D 2.3 82/04/11 17:04:58 mckusick 25 24
c float cylinder group info, reclaim redundant boot blocks
e
s 00003/00003/01084
d D 2.2 82/04/08 16:54:40 mckusick 24 23
c bring back changes from calder
e
s 00000/00000/01087
d D 2.1 82/03/25 01:38:54 mckusick 23 22
c merge into the kernel!
e
s 00003/00004/01084
d D 1.22 82/03/25 01:34:19 mckusick 22 21
c update to current system
e
s 00078/00077/01010
d D 1.21 82/03/23 14:42:07 mckusick 21 20
c incorporate sam's changes
e
s 00003/00003/01084
d D 1.20 82/03/23 12:57:12 mckusick 20 19
c compress frag tables
e
s 00054/00055/01033
d D 1.19 82/02/26 00:09:04 mckusic 19 18
c keep "fs" cached in incore inode to avoid constant calling of ``getfs''
e
s 00037/00023/01051
d D 1.18 82/02/25 14:53:38 mckusic 18 17
c use speed-up macros in fs.h
e
s 00000/00001/01074
d D 1.17 82/02/21 16:07:54 mckusic 17 16
c conversion to flexable length directory names
e
s 00004/00003/01071
d D 1.16 82/01/13 18:25:25 mckusic 16 15
c fix mapsearch to check for fragments at the end of partial cgs
e
s 00017/00017/01057
d D 1.15 82/01/12 22:15:07 mckusic 15 14
c change all macros taking "fs" to have it as their first argument
e
s 00163/00034/00911
d D 1.14 82/01/12 20:47:32 mckusic 14 13
c add cg_btot to summarize cg_b
e
s 00092/00064/00853
d D 1.13 82/01/10 18:21:55 mckusic 13 12
c fix rotational layout code to work with disks with nsect % bsize != 0
e
s 00001/00001/00916
d D 1.12 82/01/06 23:29:05 mckusic 12 11
c incorporate fs.h -r1.10, and param.h -r1.10 reorganization
e
s 00174/00095/00743
d D 1.11 82/01/05 01:28:19 mckusic 11 10
c parameterize BSIZE, FSIZE, and FRAG into fs_bsize, fs_fsize, and fs_frag
e
s 00018/00019/00820
d D 1.10 81/12/09 16:57:08 mckusic 10 9
c lint cleanup
e
s 00006/00000/00833
d D 1.9 81/11/19 22:29:28 mckusic 9 8
c check for bprefs to be out of legal range and if so ignore them
e
s 00048/00038/00785
d D 1.8 81/11/07 20:02:19 mckusic 8 7
c edit to incorperate -r1.6 reorganization of fs.h
e
s 00165/00082/00658
d D 1.7 81/10/29 00:34:52 mckusic 7 6
c put in optimal rotational block allocation
e
s 00005/00003/00735
d D 1.6 81/10/25 17:32:55 mckusic 6 5
c move external decls for tables.o from fs.h to alloc.c
e
s 00002/00002/00736
d D 1.5 81/10/07 18:31:36 mckusic 5 4
c fix unsigned char problem to get FRAG == 8 to work
e
s 00253/00081/00485
d D 1.4 81/10/05 20:41:36 mckusic 4 3
c maintaining and using cg_frsum to do intelligent allocation of FRAGs
e
s 00137/00025/00429
d D 1.3 81/09/22 17:42:41 mckusic 3 2
c allow files and directories to have FRAGS as their final block
e
s 00001/00001/00453
d D 1.2 81/09/09 17:18:21 mckusic 2 1
c change "version" to "vers"
e
s 00454/00000/00000
d D 1.1 81/09/09 16:33:22 mckusick 1 0
c date and time created 81/09/09 16:33:22 by mckusick
e
u
U
f b 
t
T
I 1
D 24
/* Copyright (c) 1981 Regents of the University of California */
E 24
I 24
D 26
/*	alloc.c	4.1	82/03/25	*/
E 26
I 26
D 63
/*	%M%	%I%	%E%	*/
E 63
I 63
/*
D 69
 * Copyright (c) 1982 Regents of the University of California.
E 69
I 69
D 79
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 79
I 79
D 104
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 104
I 104
D 139
 * Copyright (c) 1991 Regents of the University of California.
E 104
E 79
E 69
D 76
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 76
I 76
 * All rights reserved.
E 139
I 139
D 145
 * Copyright (c) 1991, 1993
E 145
I 145
 * Copyright (c) 1991, 1993, 1995
E 145
 *	The Regents of the University of California.  All rights reserved.
E 139
 *
D 90
 * Redistribution and use in source and binary forms are permitted
D 78
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 78
I 78
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
E 90
I 90
 * %sccs.include.redist.c%
E 90
E 78
E 76
 *
 *	%W% (Berkeley) %G%
 */
E 63
E 26
E 24

I 100
D 103
#ifdef LOGFS
E 100
D 2
static char version[] = "%Z%%M% %I% %G%";
E 2
I 2
D 24
static char vers[] = "%Z%%M% %I% %G%";
E 24
I 24
D 26
/* merged into kernel:	%Z%%M% %I% %G% */
E 24
E 2

D 24
/*	alloc.c	4.8	81/03/08	*/
E 24
I 24
/* last monet version:	alloc.c	4.8	81/03/08	*/
E 24

E 26
D 54
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mount.h"
#include "../h/fs.h"
#include "../h/conf.h"
#include "../h/buf.h"
#include "../h/inode.h"
I 22
D 26
#include "../h/ndir.h"
E 26
I 26
#include "../h/dir.h"
E 26
E 22
D 17
#include "../h/dir.h"
E 17
#include "../h/user.h"
I 31
#include "../h/quota.h"
I 33
#include "../h/kernel.h"
E 54
I 54
#include "param.h"
D 98
#include "systm.h"
E 98
I 98
#include "kernel.h"
E 98
D 88
#include "mount.h"
E 88
D 79
#include "fs.h"
E 79
D 62
#include "conf.h"
E 62
#include "buf.h"
D 79
#include "inode.h"
#include "dir.h"
E 79
D 94
#include "user.h"
E 94
I 94
D 98
#include "proc.h"
E 98
E 94
D 79
#include "quota.h"
E 79
I 79
#include "vnode.h"
E 79
D 98
#include "kernel.h"
E 98
I 61
#include "syslog.h"
I 100
#include "mount.h"
E 100
I 98
#include "../ufs/quota.h"
#include "../ufs/inode.h"
D 100
#include "mount.h"
E 100
#include "../ufs/ufsmount.h"
#include "lfs.h"
#include "lfs_extern.h"
E 103
I 103
#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/buf.h>
#include <sys/vnode.h>
#include <sys/syslog.h>
#include <sys/mount.h>
I 108
#include <sys/malloc.h>
E 108
E 103
E 98
I 68
D 94
#include "cmap.h"
I 79
#include "../ufs/quota.h"
#include "../ufs/inode.h"
#include "../ufs/fs.h"
E 94
E 79
E 68
E 61
E 54
E 33
E 31

I 112
#include <vm/vm.h>

E 112
I 100
D 103
/* Read in the block containing a specific inode from the ifile. */
E 100
I 94
D 98
#include "quota.h"
#include "inode.h"
#include "fs.h"
E 98
I 98
#define	LFS_IENTRY(I, F, IN, BP) \
	if (bread((F)->lfs_ivnode, (IN) / IFPB(F) + (F)->lfs_segtabsz, \
	    (F)->lfs_bsize, NOCRED, &BP)) \
D 100
		panic("ifile read"); \
E 100
I 100
		panic("lfs_ientry: read"); \
E 100
	(I) = (IFILE *)BP->b_un.b_addr + IN % IFPB(F);
E 103
I 103
D 104
#include <ufs/quota.h>
#include <ufs/inode.h>
#include <ufs/ufsmount.h>
E 104
I 104
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufsmount.h>
I 145
#include <ufs/ufs/ufs_extern.h>
E 145
E 104
E 103
E 98

I 100
D 103
/*
 * Allocate a new inode.
 */
E 100
E 94
D 6
long	hashalloc();
long	alloccg();
long	ialloccg();
E 6
I 6
D 10
extern long		hashalloc();
D 7
extern long		alloccg();
E 7
extern long		ialloccg();
E 10
I 10
D 98
extern u_long		hashalloc();
D 38
extern ino_t		ialloccg();
E 10
I 7
extern daddr_t		alloccg();
E 38
I 38
D 41
extern u_long		ialloccg();
extern u_long		alloccg();
E 41
I 41
extern ino_t		ialloccg();
extern daddr_t		alloccg();
E 41
E 38
extern daddr_t		alloccgblk();
extern daddr_t		fragextend();
extern daddr_t		blkpref();
extern daddr_t		mapsearch();
E 7
extern int		inside[], around[];
D 11
extern unsigned char	fragtbl[];
E 11
I 11
extern unsigned char	*fragtbl[];
E 11
E 6

I 14
/*
 * Allocate a block in the file system.
 * 
 * The size of the requested block is given, which must be some
 * multiple of fs_fsize and <= fs_bsize.
 * A preference may be optionally specified. If a preference is given
 * the following hierarchy is used to allocate a block:
 *   1) allocate the requested block.
 *   2) allocate a rotationally optimal block in the same cylinder.
 *   3) allocate a block in the same cylinder group.
 *   4) quadradically rehash into other cylinder groups, until an
 *      available block is located.
 * If no block preference is given the following heirarchy is used
 * to allocate a block:
 *   1) allocate a block in the cylinder group that contains the
 *      inode for the file.
 *   2) quadradically rehash into other cylinder groups, until an
 *      available block is located.
 */
E 14
D 79
struct buf *
D 19
alloc(dev, ip, bpref, size)
	dev_t dev;
E 19
I 19
alloc(ip, bpref, size)
E 79
I 79
D 83
alloc(ip, bpref, size, bpp, flags)
E 83
I 83
alloc(ip, lbn, bpref, size, bnp)
E 83
E 79
E 19
D 4
	struct inode *ip;
E 4
I 4
	register struct inode *ip;
E 4
D 83
	daddr_t bpref;
E 83
I 83
	daddr_t lbn, bpref;
E 83
	int size;
I 79
D 83
	struct buf **bpp;
	int flags;
E 83
I 83
	daddr_t *bnp;
E 98
I 98
ino_t
lfs_ialloc(fs, pip, ipp, cred)
	LFS *fs;
E 103
I 103
D 104
#include <lfs/lfs.h>
#include <lfs/lfs_extern.h>
E 104
I 104
#include <ufs/lfs/lfs.h>
#include <ufs/lfs/lfs_extern.h>
E 104

I 104
extern u_long nextgennumber;

E 104
/* Allocate a new inode. */
/* ARGSUSED */
int
D 105
lfs_ialloc(pip, notused, cred, ipp)
E 103
D 99
	struct inode *pip, **ipp;
	struct ucred *cred;
E 99
I 99
	INODE *pip, **ipp;
E 105
I 105
D 125
lfs_valloc(pvp, notused, cred, vpp)
D 109
	VNODE *pvp, **vpp;
E 109
I 109
	struct vnode *pvp, **vpp;
E 109
E 105
I 103
	int notused;
E 103
D 109
	UCRED *cred;
E 109
I 109
	struct ucred *cred;
E 125
I 125
D 129
lfs_valloc (ap)
	struct vop_valloc_args *ap;
E 129
I 129
lfs_valloc(ap)
	struct vop_valloc_args /* {
		struct vnode *a_pvp;
		int a_mode;
		struct ucred *a_cred;
		struct vnode **a_vpp;
	} */ *ap;
E 129
D 127
#define pvp (ap->a_pvp)
#define notused (ap->a_mode)
#define cred (ap->a_cred)
#define vpp (ap->a_vpp)
E 127
E 125
E 109
E 99
E 98
E 83
E 79
{
I 103
D 104
	LFS *fs;
E 104
I 104
	struct lfs *fs;
E 104
E 103
I 99
D 109
	BUF *bp;
E 99
D 98
	daddr_t bno;
	register struct fs *fs;
D 4
	struct buf *bp;
E 4
I 4
	register struct buf *bp;
E 4
D 79
	int cg;
E 79
I 79
	int cg, error;
I 87
D 94
	struct ucred *cred = u.u_cred;		/* XXX */
E 94
I 94
	struct ucred *cred = curproc->p_ucred;		/* XXX */
E 94
E 87
E 79
	
I 79
D 83
	*bpp = 0;
E 83
I 83
	*bnp = 0;
E 83
E 79
I 4
D 11
	if ((unsigned)size > BSIZE || size % FSIZE != 0)
		panic("alloc: bad size");
E 11
E 4
D 19
	fs = getfs(dev);
E 19
I 19
	fs = ip->i_fs;
E 19
D 7
	if (fs->fs_nbfree == 0 && size == BSIZE)
E 7
I 7
D 8
	if (size == BSIZE &&
	    (fs->fs_nbfree == 0 ||
	    (!suser() && fs->fs_nbfree < fs->fs_nbfree * minfree / 100)))
E 8
I 8
D 11
	if (size == BSIZE && fs->fs_cstotal.cs_nbfree == 0)
E 11
I 11
D 18
	if ((unsigned)size > fs->fs_bsize || size % fs->fs_fsize != 0)
E 18
I 18
D 27
	if ((unsigned)size > fs->fs_bsize || fragoff(fs, size) != 0)
E 27
I 27
	if ((unsigned)size > fs->fs_bsize || fragoff(fs, size) != 0) {
		printf("dev = 0x%x, bsize = %d, size = %d, fs = %s\n",
		    ip->i_dev, fs->fs_bsize, size, fs->fs_fsmnt);
E 27
E 18
		panic("alloc: bad size");
I 27
	}
E 27
	if (size == fs->fs_bsize && fs->fs_cstotal.cs_nbfree == 0)
E 11
E 8
E 7
		goto nospace;
I 8
D 46
	if (u.u_uid != 0 &&
D 11
	    fs->fs_cstotal.cs_nbfree * FRAG + fs->fs_cstotal.cs_nffree <
	      fs->fs_dsize * minfree / 100)
E 11
I 11
	    fs->fs_cstotal.cs_nbfree * fs->fs_frag + fs->fs_cstotal.cs_nffree <
	      fs->fs_dsize * fs->fs_minfree / 100)
E 46
I 46
D 87
	if (u.u_uid != 0 && freespace(fs, fs->fs_minfree) <= 0)
E 87
I 87
	if (cred->cr_uid != 0 && freespace(fs, fs->fs_minfree) <= 0)
E 87
E 46
E 11
		goto nospace;
I 31
D 32
#ifdef	QUOTA
E 32
I 32
#ifdef QUOTA
E 32
D 47
	if (chkdq(ip, (long)((unsigned)size/DEV_BSIZE), 0))
		return(NULL);
E 47
I 47
D 79
	u.u_error = chkdq(ip, (long)btodb(size), 0);
	if (u.u_error)
		return (NULL);
E 79
I 79
D 87
	if (error = chkdq(ip, (long)btodb(size), 0))
E 87
I 87
	if (error = chkdq(ip, (long)btodb(size), cred, 0))
E 87
		return (error);
E 79
E 47
#endif
E 31
I 9
	if (bpref >= fs->fs_size)
		bpref = 0;
E 9
E 8
	if (bpref == 0)
D 15
		cg = itog(ip->i_number, fs);
E 15
I 15
		cg = itog(fs, ip->i_number);
E 15
	else
D 15
		cg = dtog(bpref, fs);
E 15
I 15
		cg = dtog(fs, bpref);
E 15
D 10
	bno = hashalloc(dev, fs, cg, (long)bpref, size, alloccg);
E 10
I 10
D 19
	bno = (daddr_t)hashalloc(dev, fs, cg, (long)bpref, size, alloccg);
E 19
I 19
D 41
	bno = (daddr_t)hashalloc(ip, cg, (long)bpref, size, alloccg);
E 41
I 41
	bno = (daddr_t)hashalloc(ip, cg, (long)bpref, size,
		(u_long (*)())alloccg);
E 41
E 19
E 10
D 26
	if (bno == 0)
E 26
I 26
D 83
	if (bno <= 0)
E 26
		goto nospace;
I 47
	ip->i_blocks += btodb(size);
	ip->i_flag |= IUPD|ICHG;
I 70
#ifdef SECSIZE
	bp = getblk(ip->i_dev, fsbtodb(fs, bno), size, fs->fs_dbsize);
#else SECSIZE
E 70
E 47
D 3
	bp = getblk(dev, bno);
E 3
I 3
D 11
	bp = getblk(dev, bno, size);
E 11
I 11
D 19
	bp = getblk(dev, fsbtodb(fs, bno), size);
E 19
I 19
D 79
	bp = getblk(ip->i_dev, fsbtodb(fs, bno), size);
I 70
#endif SECSIZE
E 70
E 19
E 11
E 3
	clrbuf(bp);
	return (bp);
E 79
I 79
	bp = getblk(ip->i_devvp, fsbtodb(fs, bno), size);
	if (flags & B_CLRBUF)
		clrbuf(bp);
	*bpp = bp;
	return (0);
E 83
I 83
	if (bno > 0) {
		ip->i_blocks += btodb(size);
		ip->i_flag |= IUPD|ICHG;
		*bnp = bno;
		return (0);
	}
I 92
#ifdef QUOTA
	/*
	 * Restore user's disk quota because allocation failed.
	 */
	(void) chkdq(ip, (long)-btodb(size), cred, FORCE);
#endif
E 92
E 83
E 79
nospace:
D 89
	fserr(fs, "file system full");
E 89
I 89
	fserr(fs, cred->cr_uid, "file system full");
E 89
	uprintf("\n%s: write failed, file system is full\n", fs->fs_fsmnt);
D 79
	u.u_error = ENOSPC;
	return (NULL);
E 79
I 79
	return (ENOSPC);
E 79
}
E 98
I 98
	IFILE *ifp;
D 99
	struct buf *bp;
	struct inode *ip;
	struct vnode *vp;
E 99
I 99
	INODE *ip;
	VNODE *vp;
E 109
I 109
	struct buf *bp;
	struct ifile *ifp;
	struct inode *ip;
	struct vnode *vp;
D 143
	daddr_t blkno;
E 143
I 143
	ufs_daddr_t blkno;
E 143
E 109
E 99
	ino_t new_ino;
I 109
	u_long i, max;
E 109
D 136
	int error;
E 136
I 136
D 142
	int bb, error;
E 142
I 142
	int error;
E 142
E 136
E 98

I 106
D 133
#ifdef VERBOSE
	printf("lfs_valloc\n");
#endif
E 133
E 106
I 100
	/* Get the head of the freelist. */
I 103
D 105
	fs = pip->i_lfs;
E 105
I 105
D 127
	fs = VTOI(pvp)->i_lfs;
E 127
I 127
	fs = VTOI(ap->a_pvp)->i_lfs;
E 127
E 105
E 103
E 100
I 14
D 98
/*
 * Reallocate a fragment to a bigger size
 *
 * The number and size of the old block is given, and a preference
 * and new size is also specified. The allocator attempts to extend
 * the original block. Failing that, the regular block allocator is
 * invoked to get an appropriate block.
 */
E 14
I 3
D 79
struct buf *
D 4
realloccg(dev, ip, bpref, osize, nsize)
E 4
I 4
D 7
realloccg(dev, ip, bprev, osize, nsize)
E 7
I 7
D 10
realloccg(dev, ip, bprev, bpref, osize, nsize)
E 10
I 10
D 19
realloccg(dev, bprev, bpref, osize, nsize)
E 10
E 7
E 4
	dev_t dev;
E 19
I 19
realloccg(ip, bprev, bpref, osize, nsize)
E 79
I 79
D 83
realloccg(ip, bprev, bpref, osize, nsize, bpp)
E 83
I 83
realloccg(ip, lbprev, bpref, osize, nsize, bpp)
E 83
E 79
	register struct inode *ip;
E 19
D 4
	struct inode *ip;
	daddr_t bpref;
E 4
I 4
D 10
	register struct inode *ip;
E 10
D 7
	daddr_t bprev;
E 7
I 7
D 83
	daddr_t bprev, bpref;
E 83
I 83
	off_t lbprev;
	daddr_t bpref;
E 83
E 7
E 4
	int osize, nsize;
I 79
	struct buf **bpp;
E 79
{
D 67
	daddr_t bno;
E 67
	register struct fs *fs;
D 4
	struct buf *bp;
E 4
I 4
D 79
	register struct buf *bp, *obp;
E 79
I 79
	struct buf *bp, *obp;
E 79
D 26
	caddr_t cp;
E 26
E 4
D 64
	int cg;
E 64
I 64
D 93
	int cg, request;
I 67
D 83
	daddr_t bno, bn;
E 83
I 83
	daddr_t bprev, bno, bn;
E 83
D 74
	int i, count, s;
	extern struct cmap *mfind();
E 74
I 74
D 79
	int i, count;
E 79
I 79
	int i, error, count;
E 93
I 93
	int cg, request, error;
	daddr_t bprev, bno;
E 93
I 87
D 94
	struct ucred *cred = u.u_cred;		/* XXX */
E 94
I 94
	struct ucred *cred = curproc->p_ucred;		/* XXX */
E 94
E 87
E 79
E 74
E 67
E 64
	
I 79
	*bpp = 0;
E 79
I 4
D 11
	if ((unsigned)osize > BSIZE || osize % FSIZE != 0 ||
	    (unsigned)nsize > BSIZE || nsize % FSIZE != 0)
		panic("realloccg: bad size");
E 11
E 4
D 19
	fs = getfs(dev);
E 19
I 19
	fs = ip->i_fs;
E 19
I 11
D 18
	if ((unsigned)osize > fs->fs_bsize || osize % fs->fs_fsize != 0 ||
	    (unsigned)nsize > fs->fs_bsize || nsize % fs->fs_fsize != 0)
E 18
I 18
	if ((unsigned)osize > fs->fs_bsize || fragoff(fs, osize) != 0 ||
D 27
	    (unsigned)nsize > fs->fs_bsize || fragoff(fs, nsize) != 0)
E 27
I 27
	    (unsigned)nsize > fs->fs_bsize || fragoff(fs, nsize) != 0) {
		printf("dev = 0x%x, bsize = %d, osize = %d, nsize = %d, fs = %s\n",
		    ip->i_dev, fs->fs_bsize, osize, nsize, fs->fs_fsmnt);
E 27
E 18
		panic("realloccg: bad size");
E 98
I 98
	new_ino = fs->lfs_free;
D 100
printf("lfs_ialloc: next free %d\n", new_ino);
	if (new_ino == LFS_UNUSED_INUM) {	/* XXX -- allocate more */
E 100
I 100
D 109
	if (new_ino == LFS_UNUSED_INUM) {
		/*
		 * XXX
		 * Currently, no more inodes are allocated if the ifile fills
		 * up.  The ifile should be extended instead.
		 */
E 100
		uprintf("\n%s: no inodes left\n", fs->lfs_fsmnt);
		log(LOG_ERR, "uid %d on %s: out of inodes\n",
		    cred->cr_uid, fs->lfs_fsmnt);
		return (ENOSPC);
E 98
I 27
	}
E 109
I 100
D 103
printf("lfs_ialloc: allocate inode %d\n", new_ino);
E 103
I 103
#ifdef ALLOCPRINT
	printf("lfs_ialloc: allocate inode %d\n", new_ino);
#endif
E 103
E 100
E 27
E 11
I 8
D 46
	if (u.u_uid != 0 &&
D 11
	    fs->fs_cstotal.cs_nbfree * FRAG + fs->fs_cstotal.cs_nffree <
	      fs->fs_dsize * minfree / 100)
E 11
I 11
	    fs->fs_cstotal.cs_nbfree * fs->fs_frag + fs->fs_cstotal.cs_nffree <
	      fs->fs_dsize * fs->fs_minfree / 100)
E 46
I 46
D 87
	if (u.u_uid != 0 && freespace(fs, fs->fs_minfree) <= 0)
E 87
I 87
D 98
	if (cred->cr_uid != 0 && freespace(fs, fs->fs_minfree) <= 0)
E 87
E 46
E 11
		goto nospace;
E 8
D 4
	if (bpref == 0)
		cg = itog(ip->i_number, fs);
E 4
I 4
D 14
	if (bprev == 0)
		panic("realloccg: bad bprev");
E 4
	else
E 14
I 14
D 21
	if (bprev != 0)
E 14
D 4
		cg = dtog(bpref, fs);
	bno = fragalloc(dev, fs, cg, (long)bpref, osize, nsize);
	if (bno == 0)
		goto nospace;
	bp = getblk(dev, bno, osize);
	bp->b_bcount += nsize - osize;
	blkclr(bp->b_un.b_addr + osize, nsize - osize);
	return (bp);
nospace:
E 4
I 4
D 15
		cg = dtog(bprev, fs);
E 15
I 15
		cg = dtog(fs, bprev);
E 15
I 14
	else
E 21
I 21
D 27
	if (bprev == 0)
E 27
I 27
D 83
	if (bprev == 0) {
E 83
I 83
	if ((bprev = ip->i_db[lbprev]) == 0) {
E 83
		printf("dev = 0x%x, bsize = %d, bprev = %d, fs = %s\n",
		    ip->i_dev, fs->fs_bsize, bprev, fs->fs_fsmnt);
E 27
E 21
		panic("realloccg: bad bprev");
I 27
	}
I 31
D 32
#ifdef	QUOTA
E 32
I 32
D 92
#ifdef QUOTA
E 32
D 47
	if (chkdq(ip, (long)((unsigned)(nsize-osize)/DEV_BSIZE), 0))
		return(NULL);
E 47
I 47
D 79
	u.u_error = chkdq(ip, (long)btodb(nsize - osize), 0);
	if (u.u_error)
		return (NULL);
E 79
I 79
D 87
	if (error = chkdq(ip, (long)btodb(nsize - osize), 0))
E 87
I 87
	if (error = chkdq(ip, (long)btodb(nsize - osize), cred, 0))
E 87
		return (error);
E 79
E 47
#endif
E 92
I 83
	/*
	 * Allocate the extra space in the buffer.
	 */
	if (error = bread(ITOV(ip), lbprev, osize, NOCRED, &bp)) {
		brelse(bp);
		return (error);
	}
I 92
#ifdef QUOTA
	if (error = chkdq(ip, (long)btodb(nsize - osize), cred, 0)) {
		brelse(bp);
		return (error);
	}
#endif
E 92
D 91
	brealloc(bp, nsize);
E 91
I 91
D 96
	allocbuf(bp, nsize);
E 91
	bp->b_flags |= B_DONE;
	bzero(bp->b_un.b_addr + osize, (unsigned)nsize - osize);
E 96
D 84
	ip->i_blocks += btodb(nsize - osize);
	ip->i_flag |= IUPD|ICHG;
E 84
	/*
	 * Check for extension in the existing location.
	 */
E 83
E 31
E 27
I 21
	cg = dtog(fs, bprev);
E 21
E 14
D 19
	bno = fragextend(dev, fs, cg, (long)bprev, osize, nsize);
E 19
I 19
D 83
	bno = fragextend(ip, cg, (long)bprev, osize, nsize);
E 19
	if (bno != 0) {
D 11
		bp = bread(dev, bno, osize);
E 11
I 11
D 19
		bp = bread(dev, fsbtodb(fs, bno), osize);
E 19
I 19
D 29
		bp = bread(ip->i_dev, fsbtodb(fs, bno), osize);
E 19
I 13
D 18
		if (bp->b_flags & B_ERROR)
			return (0);
E 18
I 18
		if (bp->b_flags & B_ERROR) {
			brelse(bp);
D 21
			return 0;
E 21
I 21
			return (NULL);
E 21
		}
E 18
E 13
E 11
D 26
		bp->b_bcount = nsize;
E 26
I 26
		brealloc(bp, nsize);
E 29
I 29
		do {
I 70
#ifdef SECSIZE
			bp = bread(ip->i_dev, fsbtodb(fs, bno), osize,
			    fs->fs_dbsize);
#else SECSIZE
E 70
D 79
			bp = bread(ip->i_dev, fsbtodb(fs, bno), osize);
I 70
#endif SECSIZE
E 70
			if (bp->b_flags & B_ERROR) {
E 79
I 79
			error = bread(ip->i_devvp, fsbtodb(fs, bno),
D 81
				osize, &bp);
E 81
I 81
				osize, NOCRED, &bp);
E 81
			if (error) {
E 79
				brelse(bp);
D 79
				return (NULL);
E 79
I 79
				return (error);
E 79
			}
		} while (brealloc(bp, nsize) == 0);
		bp->b_flags |= B_DONE;
E 29
E 26
D 30
		blkclr(bp->b_un.b_addr + osize, nsize - osize);
E 30
I 30
D 41
		bzero(bp->b_un.b_addr + osize, nsize - osize);
E 41
I 41
		bzero(bp->b_un.b_addr + osize, (unsigned)nsize - osize);
I 47
		ip->i_blocks += btodb(nsize - osize);
		ip->i_flag |= IUPD|ICHG;
E 83
I 83
	if (bno = fragextend(ip, cg, (long)bprev, osize, nsize)) {
D 86
		if (bp->b_blkno != bno)
E 86
I 86
		if (bp->b_blkno != fsbtodb(fs, bno))
E 86
			panic("bad blockno");
I 84
		ip->i_blocks += btodb(nsize - osize);
		ip->i_flag |= IUPD|ICHG;
I 96
		allocbuf(bp, nsize);
		bp->b_flags |= B_DONE;
		bzero(bp->b_un.b_addr + osize, (unsigned)nsize - osize);
E 96
E 84
E 83
E 47
E 41
E 30
D 79
		return (bp);
E 79
I 79
		*bpp = bp;
		return (0);
E 79
	}
I 83
	/*
	 * Allocate a new disk location.
	 */
E 83
I 9
	if (bpref >= fs->fs_size)
		bpref = 0;
E 9
D 7
	bno = hashalloc(dev, fs, cg, (long)bprev, nsize, alloccg);
E 7
I 7
D 10
	bno = hashalloc(dev, fs, cg, (long)bpref, nsize, alloccg);
E 10
I 10
D 19
	bno = (daddr_t)hashalloc(dev, fs, cg, (long)bpref, nsize, alloccg);
E 19
I 19
D 41
	bno = (daddr_t)hashalloc(ip, cg, (long)bpref, nsize, alloccg);
E 41
I 41
D 60
	bno = (daddr_t)hashalloc(ip, cg, (long)bpref, nsize,
E 60
I 60
D 64
	bno = (daddr_t)hashalloc(ip, cg, (long)bpref, fs->fs_bsize,
E 64
I 64
D 66
	if (fs->fs_optim == FS_OPTSPACE)
E 66
I 66
D 68
	switch (fs->fs_optim) {
E 68
I 68
	switch ((int)fs->fs_optim) {
E 68
	case FS_OPTSPACE:
		/*
		 * Allocate an exact sized fragment. Although this makes 
		 * best use of space, we will waste time relocating it if 
		 * the file continues to grow. If the fragmentation is
		 * less than half of the minimum free reserve, we choose
		 * to begin optimizing for time.
		 */
E 66
		request = nsize;
D 66
	else /* if (fs->fs_optim == FS_OPTTIME) */
E 66
I 66
		if (fs->fs_minfree < 5 ||
		    fs->fs_cstotal.cs_nffree >
		    fs->fs_dsize * fs->fs_minfree / (2 * 100))
			break;
		log(LOG_NOTICE, "%s: optimization changed from SPACE to TIME\n",
			fs->fs_fsmnt);
		fs->fs_optim = FS_OPTTIME;
		break;
	case FS_OPTTIME:
		/*
		 * At this point we have discovered a file that is trying
		 * to grow a small fragment to a larger fragment. To save
		 * time, we allocate a full sized block, then free the 
		 * unused portion. If the file continues to grow, the 
		 * `fragextend' call above will be able to grow it in place
		 * without further copying. If aberrant programs cause
		 * disk fragmentation to grow within 2% of the free reserve,
		 * we choose to begin optimizing for space.
		 */
E 66
		request = fs->fs_bsize;
I 66
		if (fs->fs_cstotal.cs_nffree <
		    fs->fs_dsize * (fs->fs_minfree - 2) / 100)
			break;
		log(LOG_NOTICE, "%s: optimization changed from TIME to SPACE\n",
			fs->fs_fsmnt);
		fs->fs_optim = FS_OPTSPACE;
		break;
	default:
		printf("dev = 0x%x, optim = %d, fs = %s\n",
		    ip->i_dev, fs->fs_optim, fs->fs_fsmnt);
		panic("realloccg: bad optim");
		/* NOTREACHED */
	}
E 66
	bno = (daddr_t)hashalloc(ip, cg, (long)bpref, request,
E 64
E 60
		(u_long (*)())alloccg);
E 41
E 19
E 10
E 7
D 26
	if (bno != 0) {
		/*
		 * make a new copy
		 */
E 26
I 26
	if (bno > 0) {
I 70
#ifdef SECSIZE
		obp = bread(ip->i_dev, fsbtodb(fs, bprev), osize,
		    fs->fs_dbsize);
#else SECSIZE
E 70
E 26
D 11
		obp = bread(dev, bprev, osize);
		bp = getblk(dev, bno, nsize);
E 11
I 11
D 19
		obp = bread(dev, fsbtodb(fs, bprev), osize);
E 19
I 19
D 79
		obp = bread(ip->i_dev, fsbtodb(fs, bprev), osize);
I 70
#endif SECSIZE
E 70
E 19
I 13
D 18
		if (obp->b_flags & B_ERROR)
			return (0);
E 18
I 18
		if (obp->b_flags & B_ERROR) {
E 79
I 79
D 81
		error = bread(ip->i_devvp, fsbtodb(fs, bprev), osize, &obp);
E 81
I 81
D 83
		error = bread(ip->i_devvp, fsbtodb(fs, bprev), 
			osize, NOCRED, &obp);
E 81
		if (error) {
E 79
			brelse(obp);
D 21
			return 0;
E 21
I 21
D 79
			return (NULL);
E 79
I 79
			return (error);
E 79
E 21
		}
E 18
E 13
D 19
		bp = getblk(dev, fsbtodb(fs, bno), nsize);
E 19
I 19
D 56
		bp = getblk(ip->i_dev, fsbtodb(fs, bno), nsize);
E 19
E 11
D 26
		cp = bp->b_un.b_addr;
		bp->b_un.b_addr = obp->b_un.b_addr;
		obp->b_un.b_addr = cp;
		obp->b_flags |= B_INVAL;
E 26
I 26
D 37
		bcopy(obp->b_un.b_addr, bp->b_un.b_addr, osize);
E 37
I 37
		bcopy(obp->b_un.b_addr, bp->b_un.b_addr, (u_int)osize);
E 37
D 30
		blkclr(bp->b_un.b_addr + osize, nsize - osize);
E 30
I 30
D 41
		bzero(bp->b_un.b_addr + osize, nsize - osize);
E 41
I 41
		bzero(bp->b_un.b_addr + osize, (unsigned)nsize - osize);
E 56
I 56
D 57
		bp = getblk(ip->i_dev, fsbtodb(fs, bno), osize);
		swapbuf(obp, bp);
		obp->b_flags &= ~B_DELWRI;
		obp->b_flags |= B_INVAL;
E 57
I 57
D 67
		bp = getblk(ip->i_dev, fsbtodb(fs, bno), nsize);
E 67
I 67
		bn = fsbtodb(fs, bno);
I 70
#ifdef SECSIZE
		bp = getblk(ip->i_dev, bn, nsize, fs->fs_dbsize);
#else SECSIZE
E 70
D 79
		bp = getblk(ip->i_dev, bn, nsize);
E 79
I 79
		bp = getblk(ip->i_devvp, bn, nsize);
E 79
I 70
#endif SECSIZE
E 70
E 67
		bcopy(obp->b_un.b_addr, bp->b_un.b_addr, (u_int)osize);
E 83
I 83
D 93
		bp->b_blkno = bn = fsbtodb(fs, bno);
E 83
I 67
D 70
D 71
		count = howmany(osize, DEV_BSIZE);
		s = splimp();
		for (i = 0; i < count; i += CLBYTES / DEV_BSIZE)
			if (mfind(ip->i_dev, bn + i))
				munhash(ip->i_dev, bn + i);
		splx(s);
E 71
I 71
		count = howmany(osize, CLBYTES);
		for (i = 0; i < count; i++)
D 79
			munhash(ip->i_dev, bn + i * CLBYTES / DEV_BSIZE);
E 79
I 79
			munhash(ip->i_devvp, bn + i * CLBYTES / DEV_BSIZE);
E 93
I 93
		bp->b_blkno = fsbtodb(fs, bno);
		(void) vnode_pager_uncache(ITOV(ip));
E 93
E 79
E 71
E 70
I 70
		count = howmany(osize, CLBYTES);
		for (i = 0; i < count; i++)
#ifdef SECSIZE
			munhash(ip->i_dev, bn + i * CLBYTES / fs->fs_dbsize);
#else SECSIZE
			munhash(ip->i_dev, bn + i * CLBYTES / DEV_BSIZE);
#endif SECSIZE
E 70
E 67
D 83
		bzero(bp->b_un.b_addr + osize, (unsigned)nsize - osize);
		if (obp->b_flags & B_DELWRI) {
			obp->b_flags &= ~B_DELWRI;
			u.u_ru.ru_oublock--;		/* delete charge */
		}
E 57
E 56
E 41
E 30
E 26
		brelse(obp);
E 83
D 10
		fre(dev, bprev, osize);
E 10
I 10
D 19
		fre(dev, bprev, (off_t)osize);
E 19
I 19
D 41
		fre(ip, bprev, (off_t)osize);
E 41
I 41
D 72
		free(ip, bprev, (off_t)osize);
E 72
I 72
		blkfree(ip, bprev, (off_t)osize);
E 72
I 60
D 64
		if (nsize < fs->fs_bsize)
E 64
I 64
		if (nsize < request)
E 64
D 72
			free(ip, bno + numfrags(fs, nsize),
E 72
I 72
			blkfree(ip, bno + numfrags(fs, nsize),
E 72
D 64
				(off_t)(fs->fs_bsize - nsize));
E 64
I 64
				(off_t)(request - nsize));
E 64
E 60
I 56
D 57
		while (brealloc(bp, nsize) == 0) {
			bp = bread(ip->i_dev, fsbtodb(fs, bno), osize);
			if (bp->b_flags & B_ERROR) {
				brelse(bp);
				return (NULL);
			}
		}
		bzero(bp->b_un.b_addr + osize, (unsigned)nsize - osize);
E 57
E 56
I 47
		ip->i_blocks += btodb(nsize - osize);
		ip->i_flag |= IUPD|ICHG;
I 96
		allocbuf(bp, nsize);
		bp->b_flags |= B_DONE;
		bzero(bp->b_un.b_addr + osize, (unsigned)nsize - osize);
E 96
E 47
E 41
E 19
E 10
D 26
		blkclr(bp->b_un.b_addr + osize, nsize - osize);
E 26
D 21
		return(bp);
E 21
I 21
D 79
		return (bp);
E 79
I 79
		*bpp = bp;
		return (0);
E 79
E 21
	}
I 92
#ifdef QUOTA
	/*
	 * Restore user's disk quota because allocation failed.
	 */
	(void) chkdq(ip, (long)-btodb(nsize - osize), cred, FORCE);
#endif
E 98
I 98

D 100
	/* Read the appropriate block from the ifile */
	vp = fs->lfs_ivnode;
E 100
I 100
D 107
	/* Read the appropriate block from the ifile. */
E 107
I 107
	/*
D 109
	 * Remove the inode from the free list and write the free list
	 * back.
E 109
I 109
	 * Remove the inode from the free list and write the new start
	 * of the free list into the superblock.
E 109
	 */
E 107
E 100
	LFS_IENTRY(ifp, fs, new_ino, bp);
D 107

E 107
	if (ifp->if_daddr != LFS_UNUSED_DADDR)
D 100
		panic("lfs_ialloc: corrupt free list");
E 100
I 100
		panic("lfs_ialloc: inuse inode on the free list");
E 100
D 107

D 100
	/* Remove from free list, set the access time. */
E 100
I 100
	/* Remove from the free list, set the access time, write it back. */
E 107
E 100
D 99
	ifp->if_st_atime = time.tv_sec;
E 99
	fs->lfs_free = ifp->if_nextfree;
I 99
D 109
	ifp->if_st_atime = time.tv_sec;
E 99
E 98
E 92
I 83
D 100
	brelse(bp);
E 100
I 100
D 107
	lfs_bwrite(bp);
E 107
I 107
	LFS_IWRITE(fs, bp);
E 109
I 109
	brelse(bp);
E 109
E 107
E 100
E 83
I 8
D 98
nospace:
E 8
	/*
	 * no space available
	 */
E 4
D 89
	fserr(fs, "file system full");
E 89
I 89
	fserr(fs, cred->cr_uid, "file system full");
E 89
	uprintf("\n%s: write failed, file system is full\n", fs->fs_fsmnt);
D 79
	u.u_error = ENOSPC;
	return (NULL);
E 79
I 79
	return (ENOSPC);
E 79
}
E 98

I 109
	/* Extend IFILE so that the next lfs_valloc will succeed. */
	if (fs->lfs_free == LFS_UNUSED_INUM) {
I 136
D 138
		bb = fsbtodb(fs, 1);
		if (!ISSPACE(fs, bb, ap->a_cred))
			return(ENOSPC);
E 138
E 136
		vp = fs->lfs_ivnode;
		ip = VTOI(vp);
		blkno = lblkno(fs, ip->i_size);
D 132
printf("Extending ifile: blkno = %d\n", blkno);
E 132
D 138
		bp = getblk(vp, blkno, fs->lfs_bsize);
E 138
I 138
D 144
		lfs_balloc(vp, fs->lfs_bsize, blkno, &bp);
E 144
I 144
		lfs_balloc(vp, 0, fs->lfs_bsize, blkno, &bp);
E 144
		ip->i_size += fs->lfs_bsize;
		vnode_pager_setsize(vp, (u_long)ip->i_size);
		vnode_pager_uncache(vp);

E 138
D 135
		if (!bp) {
			uprintf("\n%s: no inodes left\n", fs->lfs_fsmnt);
			log(LOG_ERR, "uid %d on %s: out of inodes\n",
D 127
			    cred->cr_uid, fs->lfs_fsmnt);
E 127
I 127
			    ap->a_cred->cr_uid, fs->lfs_fsmnt);
E 127
			return (ENOSPC);
		}
E 135
		i = (blkno - fs->lfs_segtabsz - fs->lfs_cleansz) *
		    fs->lfs_ifpb;
D 132
printf("Extending ifile: first inum = %d\n", i);
E 132
		fs->lfs_free = i;
		max = i + fs->lfs_ifpb;
D 132
printf("Extending ifile: max inum = %d\n", max);
E 132
D 140
		for (ifp = (struct ifile *)bp->b_un.b_words; i < max; ++ifp) {
E 140
I 140
		for (ifp = (struct ifile *)bp->b_data; i < max; ++ifp) {
E 140
			ifp->if_version = 1;
			ifp->if_daddr = LFS_UNUSED_DADDR;
			ifp->if_nextfree = ++i;
		}
		ifp--;
		ifp->if_nextfree = LFS_UNUSED_INUM;
D 138

D 130
		++ip->i_blocks;			/* XXX This may not be right. */
E 130
I 130
		ip->i_blocks += btodb(fs->lfs_bsize);
I 131
		fs->lfs_bfree -= btodb(fs->lfs_bsize);
E 131
E 130
		ip->i_size += fs->lfs_bsize;
D 132
printf("Extending ifile: blocks = %d size = %d\n", ip->i_blocks, ip->i_size);
E 132
D 112
		vnode_pager_setsize(vp, ip->i_size);
E 112
I 112
		vnode_pager_setsize(vp, (u_long)ip->i_size);
E 112
		vnode_pager_uncache(vp);
E 138
D 134
		LFS_UBWRITE(bp);
E 134
I 134
		if (error = VOP_BWRITE(bp))
			return (error);
E 134
	}

E 109
I 100
	/* Create a vnode to associate with the inode. */
E 100
I 14
D 98
/*
 * Allocate an inode in the file system.
 * 
 * A preference may be optionally specified. If a preference is given
 * the following hierarchy is used to allocate an inode:
 *   1) allocate the requested inode.
 *   2) allocate an inode in the same cylinder group.
 *   3) quadradically rehash into other cylinder groups, until an
 *      available inode is located.
 * If no inode preference is given the following heirarchy is used
 * to allocate an inode:
 *   1) allocate an inode in cylinder group 0.
 *   2) quadradically rehash into other cylinder groups, until an
 *      available inode is located.
 */
E 14
E 3
D 79
struct inode *
D 19
ialloc(dev, ipref, mode)
	dev_t dev;
E 19
I 19
ialloc(pip, ipref, mode)
E 79
I 79
D 87
ialloc(pip, ipref, mode, ipp)
E 87
I 87
ialloc(pip, ipref, mode, cred, ipp)
E 87
E 79
	register struct inode *pip;
E 19
	ino_t ipref;
	int mode;
I 87
	struct ucred *cred;
E 87
I 79
	struct inode **ipp;
E 79
{
D 10
	daddr_t ino;
E 10
I 10
	ino_t ino;
E 10
	register struct fs *fs;
	register struct inode *ip;
D 79
	int cg;
E 79
I 79
	int cg, error;
E 79
	
I 79
	*ipp = 0;
E 79
D 19
	fs = getfs(dev);
E 19
I 19
	fs = pip->i_fs;
E 19
D 8
	if (fs->fs_nifree == 0)
E 8
I 8
	if (fs->fs_cstotal.cs_nifree == 0)
E 8
		goto noinodes;
I 31
D 32
#ifdef	QUOTA
E 32
I 32
D 87
#ifdef QUOTA
E 32
D 41
	if (chkiq(pip->i_dev, NULL, u.u_uid, 0))
E 41
I 41
D 47
	if (chkiq(pip->i_dev, (struct inode *)NULL, u.u_uid, 0))
E 41
		return(NULL);
E 47
I 47
D 79
	u.u_error = chkiq(pip->i_dev, (struct inode *)NULL, u.u_uid, 0);
	if (u.u_error)
		return (NULL);
E 79
I 79
	if (error = chkiq(pip->i_dev, (struct inode *)NULL, u.u_uid, 0))
		return (error);
E 79
E 47
#endif
E 87
E 31
I 9
	if (ipref >= fs->fs_ncg * fs->fs_ipg)
		ipref = 0;
E 9
D 15
	cg = itog(ipref, fs);
E 15
I 15
	cg = itog(fs, ipref);
E 15
D 10
	ino = hashalloc(dev, fs, cg, (long)ipref, mode, ialloccg);
E 10
I 10
D 19
	ino = (ino_t)hashalloc(dev, fs, cg, (long)ipref, mode, ialloccg);
E 19
I 19
	ino = (ino_t)hashalloc(pip, cg, (long)ipref, mode, ialloccg);
E 19
E 10
	if (ino == 0)
		goto noinodes;
D 19
	ip = iget(dev, ino);
E 19
I 19
D 79
	ip = iget(pip->i_dev, pip->i_fs, ino);
E 19
	if (ip == NULL) {
E 79
I 79
	error = iget(pip, ino, ipp);
D 80
	ip = *ipp;
E 80
	if (error) {
E 79
D 10
		ifree(dev, ino);
E 10
I 10
D 19
		ifree(dev, ino, 0);
E 19
I 19
D 50
		ifree(ip, ino, 0);
E 50
I 50
D 87
		ifree(pip, ino, 0);
E 87
I 87
		ifree(pip, ino, mode);
E 98
I 98
D 105
	error = lfs_vcreate(ITOV(pip)->v_mount, new_ino, &vp);
	if (error) 
E 105
I 105
D 127
	if (error = lfs_vcreate(pvp->v_mount, new_ino, &vp))
E 127
I 127
	if (error = lfs_vcreate(ap->a_pvp->v_mount, new_ino, &vp))
E 127
E 105
E 98
E 87
E 50
E 19
E 10
D 79
		return (NULL);
E 79
I 79
		return (error);
I 100
D 105
	*ipp = ip = VTOI(vp);
E 105
I 105
D 127
	*vpp = vp;
E 127
I 127
D 137
	*ap->a_vpp = vp;
I 129
	vp->v_flag |= VDIROP;
E 137
I 137

E 137
E 129
E 127
D 138
	ip = VTOI(vp);
E 138
D 137
	VREF(ip->i_devvp);
E 137
E 105
E 100
E 79
D 98
	}
I 80
	ip = *ipp;
E 80
D 27
	if (ip->i_mode)
E 27
I 27
	if (ip->i_mode) {
		printf("mode = 0%o, inum = %d, fs = %s\n",
		    ip->i_mode, ip->i_number, fs->fs_fsmnt);
E 27
		panic("ialloc: dup alloc");
I 47
	}
	if (ip->i_blocks) {				/* XXX */
		printf("free inode %s/%d had %d blocks\n",
		    fs->fs_fsmnt, ino, ip->i_blocks);
		ip->i_blocks = 0;
E 47
I 27
	}
I 82
	ip->i_flags = 0;
E 98
I 98

I 138
	ip = VTOI(vp);
E 138
I 109
	/* Zero out the direct and indirect block addresses. */
D 137
	bzero(ip->i_db, (NDADDR + NIADDR) * sizeof(daddr_t));
E 137
I 137
	bzero(&ip->i_din, sizeof(struct dinode));
	ip->i_din.di_inumber = new_ino;
E 137

E 109
D 100
	ip = VTOI(vp);
	VREF(ip->i_devvp);

E 98
E 82
I 80
	/*
	 * Set up a new generation number for this inode.
	 */
E 100
I 100
	/* Set a new generation number for this inode. */
E 100
	if (++nextgennumber < (u_long)time.tv_sec)
		nextgennumber = time.tv_sec;
	ip->i_gen = nextgennumber;
E 80
E 27
D 79
	return (ip);
E 79
I 79
D 98
	return (0);
E 79
noinodes:
D 89
	fserr(fs, "out of inodes");
E 89
I 89
	fserr(fs, cred->cr_uid, "out of inodes");
E 89
D 21
	uprintf("\n%s: create failed, no inodes free\n", fs->fs_fsmnt);
E 21
I 21
	uprintf("\n%s: create/symlink failed, no inodes free\n", fs->fs_fsmnt);
E 21
D 79
	u.u_error = ENOSPC;
	return (NULL);
E 79
I 79
	return (ENOSPC);
E 79
}
E 98

I 100
	/* Insert into the inode hash table. */
E 100
D 7
dipref(dev)
E 7
I 7
D 98
/*
D 14
 * find a cylinder to place a directory
E 14
I 14
 * Find a cylinder to place a directory.
 *
 * The policy implemented by this algorithm is to select from
 * among those cylinder groups with above the average number of
 * free inodes, the one with the smallest number of directories.
E 14
 */
I 41
ino_t
E 41
D 19
dirpref(dev)
E 7
	dev_t dev;
{
E 19
I 19
dirpref(fs)
E 19
	register struct fs *fs;
I 19
{
E 19
D 7
	int cg, minndir, mincg;
E 7
I 7
	int cg, minndir, mincg, avgifree;
E 98
I 98
D 103
	lfs_hqueue(ip);
E 103
I 103
	ufs_ihashins(ip);
E 103
E 98
E 7

I 137
	if (error = ufs_vinit(vp->v_mount, lfs_specop_p, LFS_FIFOOPS, &vp)) {
		vput(vp);
		*ap->a_vpp = NULL;
		return (error);
	}

	*ap->a_vpp = vp;
	vp->v_flag |= VDIROP;
	VREF(ip->i_devvp);

E 137
D 19
	fs = getfs(dev);
E 19
D 7
	minndir = fs->fs_cs[0].cs_ndir;
E 7
I 7
D 8
	avgifree = fs->fs_nifree / fs->fs_ncg;
E 8
I 8
D 98
	avgifree = fs->fs_cstotal.cs_nifree / fs->fs_ncg;
E 8
	minndir = fs->fs_ipg;
E 7
	mincg = 0;
D 7
	for (cg = 1; cg < fs->fs_ncg; cg++)
		if (fs->fs_cs[cg].cs_ndir < minndir) {
E 7
I 7
	for (cg = 0; cg < fs->fs_ncg; cg++)
D 11
		if (fs->fs_cs(cg).cs_ndir < minndir &&
		    fs->fs_cs(cg).cs_nifree >= avgifree) {
E 11
I 11
		if (fs->fs_cs(fs, cg).cs_ndir < minndir &&
		    fs->fs_cs(fs, cg).cs_nifree >= avgifree) {
E 11
E 7
			mincg = cg;
D 7
			minndir = fs->fs_cs[cg].cs_ndir;
			if (minndir == 0)
				break;
E 7
I 7
D 11
			minndir = fs->fs_cs(cg).cs_ndir;
E 11
I 11
			minndir = fs->fs_cs(fs, cg).cs_ndir;
E 11
E 7
		}
D 41
	return (fs->fs_ipg * mincg);
E 41
I 41
	return ((ino_t)(fs->fs_ipg * mincg));
E 98
I 98
D 100
	*ipp = ip;
E 100
I 100
	/* Set superblock modified bit and increment file count. */
	fs->lfs_fmod = 1;
	++fs->lfs_nfiles;
E 100
	return (0);
E 98
E 41
}
I 125
D 127
#undef pvp
#undef notused
#undef cred
#undef vpp
E 127
E 125

I 100
D 103
/* Free an inode. */
E 100
I 7
D 98
/*
D 14
 * select a cylinder to place a large block of data
E 14
I 14
D 41
 * Select a cylinder to place a large block of data.
 *
 * The policy implemented by this algorithm is to maintain a
 * rotor that sweeps the cylinder groups. When a block is 
 * needed, the rotor is advanced until a cylinder group with
 * greater than the average number of free blocks is found.
E 41
I 41
 * Select the desired position for the next block in a file.  The file is
 * logically divided into sections. The first section is composed of the
 * direct blocks. Each additional section contains fs_maxbpg blocks.
 * 
 * If no blocks have been allocated in the first section, the policy is to
 * request a block in the same cylinder group as the inode that describes
 * the file. If no blocks have been allocated in any other section, the
 * policy is to place the section in a cylinder group with a greater than
 * average number of free blocks.  An appropriate cylinder group is found
D 58
 * by maintaining a rotor that sweeps the cylinder groups. When a new
 * group of blocks is needed, the rotor is advanced until a cylinder group
 * with greater than the average number of free blocks is found.
E 58
I 58
 * by using a rotor that sweeps the cylinder groups. When a new group of
 * blocks is needed, the sweep begins in the cylinder group following the
 * cylinder group from which the previous allocation was made. The sweep
 * continues until a cylinder group with greater than the average number
 * of free blocks is found. If the allocation is for the first block in an
 * indirect block, the information on the previous allocation is unavailable;
 * here a best guess is made based upon the logical block number being
 * allocated.
E 58
 * 
 * If a section is already partially allocated, the policy is to
 * contiguously allocate fs_maxcontig blocks.  The end of one of these
 * contiguous blocks and the beginning of the next is physically separated
 * so that the disk head will be in transit between them for at least
 * fs_rotdelay milliseconds.  This is to allow time for the processor to
 * schedule another I/O transfer.
E 41
E 14
 */
I 10
daddr_t
E 10
D 19
blkpref(dev)
	dev_t dev;
{
E 19
I 19
D 41
blkpref(fs)
E 19
	register struct fs *fs;
E 41
I 41
blkpref(ip, lbn, indx, bap)
E 98
I 98
void
lfs_ifree(ip)
E 98
D 99
	struct inode *ip;
E 99
I 99
	INODE *ip;
E 99
D 98
	daddr_t lbn;
	int indx;
	daddr_t *bap;
E 98
E 41
I 19
{
I 99
	BUF *bp;
E 99
I 41
D 98
	register struct fs *fs;
E 41
E 19
D 58
	int cg, avgbfree;
E 58
I 58
	register int cg;
	int avgbfree, startcg;
E 58
I 41
	daddr_t nextblk;
E 98
I 98
	IFILE *ifp;
	LFS *fs;
D 99
	struct buf *bp;
E 99
	ino_t ino;
E 98
E 41

D 19
	fs = getfs(dev);
E 19
D 8
	avgbfree = fs->fs_nbfree / fs->fs_ncg;
E 8
I 8
D 41
	avgbfree = fs->fs_cstotal.cs_nbfree / fs->fs_ncg;
E 8
	for (cg = fs->fs_cgrotor + 1; cg < fs->fs_ncg; cg++)
D 11
		if (fs->fs_cs(cg).cs_nbfree >= avgbfree) {
E 11
I 11
		if (fs->fs_cs(fs, cg).cs_nbfree >= avgbfree) {
E 11
			fs->fs_cgrotor = cg;
E 41
I 41
D 98
	fs = ip->i_fs;
	if (indx % fs->fs_maxbpg == 0 || bap[indx - 1] == 0) {
		if (lbn < NDADDR) {
			cg = itog(fs, ip->i_number);
E 41
D 11
			return (fs->fs_fpg * cg + FRAG);
E 11
I 11
			return (fs->fs_fpg * cg + fs->fs_frag);
E 11
		}
D 41
	for (cg = 0; cg <= fs->fs_cgrotor; cg++)
D 11
		if (fs->fs_cs(cg).cs_nbfree >= avgbfree) {
E 11
I 11
		if (fs->fs_cs(fs, cg).cs_nbfree >= avgbfree) {
E 11
			fs->fs_cgrotor = cg;
D 11
			return (fs->fs_fpg * cg + FRAG);
E 11
I 11
			return (fs->fs_fpg * cg + fs->fs_frag);
E 11
		}
D 21
	return (0);
E 21
I 21
	return (NULL);
E 41
I 41
		/*
		 * Find a cylinder with greater than average number of
		 * unused data blocks.
		 */
I 58
		if (indx == 0 || bap[indx - 1] == 0)
			startcg = itog(fs, ip->i_number) + lbn / fs->fs_maxbpg;
		else
			startcg = dtog(fs, bap[indx - 1]) + 1;
		startcg %= fs->fs_ncg;
E 58
		avgbfree = fs->fs_cstotal.cs_nbfree / fs->fs_ncg;
D 58
		for (cg = fs->fs_cgrotor + 1; cg < fs->fs_ncg; cg++)
E 58
I 58
		for (cg = startcg; cg < fs->fs_ncg; cg++)
E 58
			if (fs->fs_cs(fs, cg).cs_nbfree >= avgbfree) {
				fs->fs_cgrotor = cg;
				return (fs->fs_fpg * cg + fs->fs_frag);
			}
D 58
		for (cg = 0; cg <= fs->fs_cgrotor; cg++)
E 58
I 58
		for (cg = 0; cg <= startcg; cg++)
E 58
			if (fs->fs_cs(fs, cg).cs_nbfree >= avgbfree) {
				fs->fs_cgrotor = cg;
				return (fs->fs_fpg * cg + fs->fs_frag);
			}
		return (NULL);
	}
	/*
	 * One or more previous blocks have been laid out. If less
	 * than fs_maxcontig previous blocks are contiguous, the
	 * next block is requested contiguously, otherwise it is
	 * requested rotationally delayed by fs_rotdelay milliseconds.
	 */
	nextblk = bap[indx - 1] + fs->fs_frag;
	if (indx > fs->fs_maxcontig &&
D 46
	    bap[indx - fs->fs_maxcontig] + fs->fs_frag * fs->fs_maxcontig
E 46
I 46
	    bap[indx - fs->fs_maxcontig] + blkstofrags(fs, fs->fs_maxcontig)
E 46
	    != nextblk)
		return (nextblk);
	if (fs->fs_rotdelay != 0)
		/*
		 * Here we convert ms of delay to frags as:
		 * (frags) = (ms) * (rev/sec) * (sect/rev) /
		 *	((sect/frag) * (ms/sec))
		 * then round up to the next block.
		 */
		nextblk += roundup(fs->fs_rotdelay * fs->fs_rps * fs->fs_nsect /
		    (NSPF(fs) * 1000), fs->fs_frag);
	return (nextblk);
E 41
E 21
}
E 98
I 98
printf("lfs_ifree: free %d\n", ip->i_number);
I 100
	/* Get the inode number and file system. */
E 100
	fs = ip->i_lfs;
	ino = ip->i_number;
D 100
	LFS_IENTRY(ifp, fs, ino, bp);
E 100
E 98

I 100
	/*
	 * Read the appropriate block from the ifile.  Set the inode entry to
	 * unused, increment its version number and link it into the free chain.
	 */
	LFS_IENTRY(ifp, fs, ino, bp);
E 100
I 14
D 98
/*
 * Implement the cylinder overflow algorithm.
 *
 * The policy implemented by this algorithm is:
 *   1) allocate the block in its requested cylinder group.
 *   2) quadradically rehash on the cylinder group number.
 *   3) brute force search for a free block.
 */
E 14
E 7
D 10
long
E 10
I 10
/*VARARGS5*/
u_long
E 10
D 19
hashalloc(dev, fs, cg, pref, size, allocator)
	dev_t dev;
	register struct fs *fs;
E 19
I 19
hashalloc(ip, cg, pref, size, allocator)
	struct inode *ip;
E 19
	int cg;
	long pref;
	int size;	/* size for data blocks, mode for inodes */
D 10
	long (*allocator)();
E 10
I 10
	u_long (*allocator)();
E 10
{
I 19
	register struct fs *fs;
E 19
	long result;
	int i, icg = cg;

I 19
	fs = ip->i_fs;
E 19
	/*
	 * 1: preferred cylinder group
	 */
D 19
	result = (*allocator)(dev, fs, cg, pref, size);
E 19
I 19
	result = (*allocator)(ip, cg, pref, size);
E 19
	if (result)
		return (result);
	/*
	 * 2: quadratic rehash
	 */
	for (i = 1; i < fs->fs_ncg; i *= 2) {
		cg += i;
		if (cg >= fs->fs_ncg)
			cg -= fs->fs_ncg;
D 19
		result = (*allocator)(dev, fs, cg, 0, size);
E 19
I 19
		result = (*allocator)(ip, cg, 0, size);
E 19
		if (result)
			return (result);
	}
	/*
	 * 3: brute force search
I 43
D 44
	 * Note that we start at i == 3, since 0 was checked initially,
	 * and 1 and 2 are always checked in the quadratic rehash.
E 44
I 44
	 * Note that we start at i == 2, since 0 was checked initially,
	 * and 1 is always checked in the quadratic rehash.
E 44
E 43
	 */
D 45
	cg = icg;
E 45
I 45
	cg = (icg + 2) % fs->fs_ncg;
E 45
D 43
	for (i = 0; i < fs->fs_ncg; i++) {
E 43
I 43
D 44
	for (i = 3; i < fs->fs_ncg; i++) {
E 44
I 44
	for (i = 2; i < fs->fs_ncg; i++) {
E 44
E 43
D 19
		result = (*allocator)(dev, fs, cg, 0, size);
E 19
I 19
		result = (*allocator)(ip, cg, 0, size);
E 19
		if (result)
			return (result);
		cg++;
		if (cg == fs->fs_ncg)
			cg = 0;
	}
D 21
	return (0);
E 21
I 21
	return (NULL);
E 98
I 98
	ifp->if_daddr = LFS_UNUSED_DADDR;
	++ifp->if_version;
	ifp->if_nextfree = fs->lfs_free;
D 100
	brelse(bp);
E 100
	fs->lfs_free = ino;
I 100

	lfs_bwrite(bp);

	/* Set superblock modified bit and decrement file count. */
E 100
	fs->lfs_fmod = 1;
I 100
	--fs->lfs_nfiles;
E 100
E 98
E 21
}

I 100
/* Translate an inode number to a disk address. */
E 100
I 14
D 98
/*
 * Determine whether a fragment can be extended.
 *
 * Check to see if the necessary fragments are available, and 
 * if they are, allocate them.
 */
E 98
E 14
daddr_t
I 3
D 4
fragalloc(dev, fs, cg, pref, osize, nsize)
E 4
I 4
D 19
fragextend(dev, fs, cg, bprev, osize, nsize)
E 4
	dev_t dev;
	register struct fs *fs;
E 19
I 19
D 98
fragextend(ip, cg, bprev, osize, nsize)
	struct inode *ip;
E 19
	int cg;
D 4
	long pref;
E 4
I 4
	long bprev;
E 4
	int osize, nsize;
E 98
I 98
itod(fs, ino)
	LFS *fs;
	ino_t ino;
E 98
{
I 19
D 98
	register struct fs *fs;
E 19
D 4
	struct buf *bp;
	struct cg *cgp;
E 4
I 4
D 79
	register struct buf *bp;
E 79
	register struct cg *cgp;
E 98
I 79
D 99
	struct buf *bp;
E 99
I 99
	BUF *bp;
E 99
E 79
D 98
	long bno;
	int frags, bbase;
E 4
D 79
	int i;
E 79
I 79
	int i, error;
E 98
I 98
	IFILE *ifp;
	daddr_t iaddr;
E 98
E 79

I 19
D 98
	fs = ip->i_fs;
I 25
D 55
	if (fs->fs_cs(fs, cg).cs_nffree < nsize - osize)
E 55
I 55
	if (fs->fs_cs(fs, cg).cs_nffree < numfrags(fs, nsize - osize))
E 55
		return (NULL);
E 25
E 19
D 4
	if ((unsigned)osize > BSIZE || osize % FSIZE != 0 ||
	    (unsigned)nsize > BSIZE || nsize % FSIZE != 0)
		panic("fragalloc: bad size");
E 4
I 4
D 11
	frags = nsize / FSIZE;
	bbase = bprev % FRAG;
	if (bbase > (bprev + frags - 1) % FRAG) {
E 11
I 11
D 18
	frags = nsize / fs->fs_fsize;
	bbase = bprev % fs->fs_frag;
E 18
I 18
	frags = numfrags(fs, nsize);
D 55
	bbase = fragoff(fs, bprev);
E 18
	if (bbase > (bprev + frags - 1) % fs->fs_frag) {
E 55
I 55
	bbase = fragnum(fs, bprev);
	if (bbase > fragnum(fs, (bprev + frags - 1))) {
E 55
E 11
D 70
D 71
		/* cannot extend across a block boundry */
E 71
I 71
		/* cannot extend across a block boundary */
E 71
E 70
I 70
		/* cannot extend across a block boundary */
E 70
D 21
		return (0);
E 21
I 21
		return (NULL);
E 21
	}
I 70
#ifdef SECSIZE
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_cgsize,
	    fs->fs_dbsize);
#else SECSIZE
E 70
E 4
D 11
	bp = bread(dev, cgtod(cg, fs), BSIZE);
E 11
I 11
D 15
	bp = bread(dev, fsbtodb(fs, cgtod(cg, fs)), fs->fs_bsize);
E 15
I 15
D 19
	bp = bread(dev, fsbtodb(fs, cgtod(fs, cg)), fs->fs_bsize);
E 19
I 19
D 37
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), fs->fs_bsize);
E 37
I 37
D 43
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_bsize);
E 43
I 43
D 79
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_cgsize);
E 79
I 79
	error = bread(ip->i_devvp, fsbtodb(fs, cgtod(fs, cg)),
D 81
		(int)fs->fs_cgsize, &bp);
E 81
I 81
		(int)fs->fs_cgsize, NOCRED, &bp);
E 81
	if (error) {
		brelse(bp);
		return (NULL);
	}
E 79
I 70
#endif SECSIZE
E 70
E 43
E 37
E 19
E 15
E 11
D 18
	if (bp->b_flags & B_ERROR)
		return (0);
E 18
I 18
D 25
	if (bp->b_flags & B_ERROR) {
E 25
I 25
	cgp = bp->b_un.b_cg;
D 75
	if (bp->b_flags & B_ERROR || cgp->cg_magic != CG_MAGIC) {
E 75
I 75
D 79
	if (bp->b_flags & B_ERROR || !cg_chkmagic(cgp)) {
E 79
I 79
	if (!cg_chkmagic(cgp)) {
E 79
E 75
E 25
		brelse(bp);
D 21
		return 0;
E 21
I 21
		return (NULL);
E 21
	}
I 28
D 33
	cgp->cg_time = time;
E 33
I 33
	cgp->cg_time = time.tv_sec;
E 33
E 28
E 18
D 25
	cgp = bp->b_un.b_cg;
E 25
D 4
	if (pref) {
		pref %= fs->fs_fpg;
		for (i = osize / FSIZE; i < nsize / FSIZE; i++) {
			if (isclr(cgp->cg_free, pref + i))
E 4
I 4
D 14
	bno = bprev % fs->fs_fpg;
E 14
I 14
D 15
	bno = dtogd(bprev, fs);
E 15
I 15
	bno = dtogd(fs, bprev);
E 15
E 14
D 11
	for (i = osize / FSIZE; i < frags; i++) {
E 11
I 11
D 13
	for (i = osize / fs->fs_fsize; i < frags; i++) {
E 13
I 13
D 18
	for (i = osize / fs->fs_fsize; i < frags; i++)
E 18
I 18
	for (i = numfrags(fs, osize); i < frags; i++)
E 18
D 75
		if (isclr(cgp->cg_free, bno + i)) {
E 75
I 75
		if (isclr(cg_blksfree(cgp), bno + i)) {
E 75
			brelse(bp);
D 21
			return (0);
E 21
I 21
			return (NULL);
E 21
		}
	/*
	 * the current fragment can be extended
	 * deduct the count on fragment being extended into
	 * increase the count on the remaining fragment (if any)
	 * allocate the extended piece
	 */
	for (i = frags; i < fs->fs_frag - bbase; i++)
E 13
E 11
D 75
		if (isclr(cgp->cg_free, bno + i))
E 75
I 75
		if (isclr(cg_blksfree(cgp), bno + i))
E 75
			break;
I 13
D 18
	cgp->cg_frsum[i - osize / fs->fs_fsize]--;
E 18
I 18
	cgp->cg_frsum[i - numfrags(fs, osize)]--;
E 18
	if (i != frags)
		cgp->cg_frsum[i - frags]++;
D 18
	for (i = osize / fs->fs_fsize; i < frags; i++) {
E 18
I 18
	for (i = numfrags(fs, osize); i < frags; i++) {
E 18
D 75
		clrbit(cgp->cg_free, bno + i);
E 75
I 75
		clrbit(cg_blksfree(cgp), bno + i);
E 75
		cgp->cg_cs.cs_nffree--;
		fs->fs_cstotal.cs_nffree--;
		fs->fs_cs(fs, cg).cs_nffree--;
E 13
	}
D 13
	if (i == frags) {
		/*
		 * the current fragment can be extended
		 * deduct the count on fragment being extended into
		 * increase the count on the remaining fragment (if any)
		 * allocate the extended piece
		 */
D 11
		for (i = frags; i < FRAG - bbase; i++)
E 11
I 11
		for (i = frags; i < fs->fs_frag - bbase; i++)
E 11
			if (isclr(cgp->cg_free, bno + i))
E 4
				break;
I 4
D 11
		cgp->cg_frsum[i - osize / FSIZE]--;
E 11
I 11
		cgp->cg_frsum[i - osize / fs->fs_fsize]--;
E 11
		if (i != frags)
			cgp->cg_frsum[i - frags]++;
D 11
		for (i = osize / FSIZE; i < frags; i++) {
E 11
I 11
		for (i = osize / fs->fs_fsize; i < frags; i++) {
E 11
			clrbit(cgp->cg_free, bno + i);
D 8
			cgp->cg_nffree--;
			fs->fs_nffree--;
E 8
I 8
			cgp->cg_cs.cs_nffree--;
			fs->fs_cstotal.cs_nffree--;
D 11
			fs->fs_cs(cg).cs_nffree--;
E 11
I 11
			fs->fs_cs(fs, cg).cs_nffree--;
E 11
E 8
E 4
		}
D 4
		if (i == nsize / FSIZE)
			goto extendit;
E 4
I 4
		fs->fs_fmod++;
		bdwrite(bp);
		return (bprev);
E 4
	}
D 4
	/*
	 * MUST FIND ALTERNATE LOCATION
	 */
	panic("fragalloc: reallocation too hard!");
E 4
	brelse(bp);
	return (0);
E 13
I 13
D 97
	fs->fs_fmod++;
E 97
I 97
	fs->fs_fmod = 1;
E 97
	bdwrite(bp);
	return (bprev);
E 13
D 4
extendit:
	for (i = osize / FSIZE; i < nsize / FSIZE; i++) {
		clrbit(cgp->cg_free, pref + i);
		cgp->cg_nffree--;
		fs->fs_nffree--;
	}
	fs->fs_fmod++;
	bdwrite(bp);
	return (cg * fs->fs_fpg + pref);
E 4
}
E 98
I 98
D 100
printf("itod: ino %d\n", ino);
E 100
I 100
	/* Read the appropriate block from the ifile. */
E 100
	LFS_IENTRY(ifp, fs, ino, bp);
E 98

I 14
D 98
/*
 * Determine whether a block can be allocated.
 *
 * Check to see if a block of the apprpriate size is available,
 * and if it is, allocate it.
 */
E 14
D 38
daddr_t
E 38
I 38
D 41
u_long
E 41
I 41
daddr_t
E 41
E 38
E 3
D 19
alloccg(dev, fs, cg, bpref, size)
	dev_t dev;
D 4
	struct fs *fs;
E 4
I 4
	register struct fs *fs;
E 19
I 19
alloccg(ip, cg, bpref, size)
	struct inode *ip;
E 19
E 4
	int cg;
	daddr_t bpref;
	int size;
{
I 19
	register struct fs *fs;
E 19
D 4
	struct buf *bp;
	struct cg *cgp;
	int i;
E 4
I 4
D 79
	register struct buf *bp;
E 79
	register struct cg *cgp;
D 79
	int bno, frags;
	int allocsiz;
E 79
I 79
	struct buf *bp;
E 79
D 7
	int start, len, loc;
	int blk, field, subfield, pos;
E 7
	register int i;
I 79
	int error, bno, frags, allocsiz;
E 79
E 4

I 19
	fs = ip->i_fs;
E 19
I 8
D 11
	if (fs->fs_cs(cg).cs_nbfree == 0 && size == BSIZE)
E 11
I 11
	if (fs->fs_cs(fs, cg).cs_nbfree == 0 && size == fs->fs_bsize)
E 11
D 21
		return (0);
E 21
I 21
		return (NULL);
I 70
#ifdef SECSIZE
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_cgsize,
	    fs->fs_dbsize);
#else SECSIZE
E 70
E 21
E 8
D 3
	if (size != BSIZE)
		panic("alloccg: size != BSIZE is too hard!");
	bp = bread(dev, cgtod(cg, fs));
E 3
I 3
D 4
	if ((unsigned)size > BSIZE || size % FSIZE != 0)
		panic("alloccg: bad size");
E 4
D 11
	bp = bread(dev, cgtod(cg, fs), BSIZE);
E 11
I 11
D 15
	bp = bread(dev, fsbtodb(fs, cgtod(cg, fs)), fs->fs_bsize);
E 15
I 15
D 19
	bp = bread(dev, fsbtodb(fs, cgtod(fs, cg)), fs->fs_bsize);
E 19
I 19
D 37
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), fs->fs_bsize);
E 37
I 37
D 43
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_bsize);
E 43
I 43
D 79
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_cgsize);
E 79
I 79
	error = bread(ip->i_devvp, fsbtodb(fs, cgtod(fs, cg)),
D 81
		(int)fs->fs_cgsize, &bp);
E 81
I 81
		(int)fs->fs_cgsize, NOCRED, &bp);
E 81
	if (error) {
		brelse(bp);
		return (NULL);
	}
E 79
I 70
#endif SECSIZE
E 70
E 43
E 37
E 19
E 15
E 11
E 3
D 18
	if (bp->b_flags & B_ERROR)
		return (0);
E 18
I 18
D 25
	if (bp->b_flags & B_ERROR) {
E 25
I 25
	cgp = bp->b_un.b_cg;
D 52
	if (bp->b_flags & B_ERROR || cgp->cg_magic != CG_MAGIC) {
E 52
I 52
D 75
	if (bp->b_flags & B_ERROR || cgp->cg_magic != CG_MAGIC ||
E 75
I 75
D 79
	if (bp->b_flags & B_ERROR || !cg_chkmagic(cgp) ||
E 79
I 79
	if (!cg_chkmagic(cgp) ||
E 79
E 75
	    (cgp->cg_cs.cs_nbfree == 0 && size == fs->fs_bsize)) {
E 52
E 25
		brelse(bp);
D 21
		return 0;
E 21
I 21
		return (NULL);
E 21
	}
I 43
D 52
	if (cgp->cg_cs.cs_nbfree == 0 && size == fs->fs_bsize)
		return (NULL);
E 52
E 43
I 28
D 33
	cgp->cg_time = time;
E 33
I 33
	cgp->cg_time = time.tv_sec;
E 33
E 28
E 18
D 25
	cgp = bp->b_un.b_cg;
E 25
I 4
D 11
	if (size == BSIZE) {
E 11
I 11
	if (size == fs->fs_bsize) {
E 11
D 8
		if (cgp->cg_nbfree == 0) {
			brelse(bp);
			return (0);
		}
E 8
D 10
		bno = alloccgblk(dev, fs, cgp, bpref);
E 10
I 10
		bno = alloccgblk(fs, cgp, bpref);
E 10
		bdwrite(bp);
		return (bno);
	}
	/*
	 * check to see if any fragments are already available
	 * allocsiz is the size which will be allocated, hacking
	 * it down to a smaller size if necessary
	 */
D 11
	frags = size / FSIZE;
	for (allocsiz = frags; allocsiz < FRAG; allocsiz++)
E 11
I 11
D 18
	frags = size / fs->fs_fsize;
E 18
I 18
	frags = numfrags(fs, size);
E 18
	for (allocsiz = frags; allocsiz < fs->fs_frag; allocsiz++)
E 11
		if (cgp->cg_frsum[allocsiz] != 0)
			break;
D 11
	if (allocsiz == FRAG) {
E 11
I 11
	if (allocsiz == fs->fs_frag) {
E 11
		/*
		 * no fragments were available, so a block will be 
		 * allocated, and hacked up
		 */
D 8
		if (cgp->cg_nbfree == 0) {
E 8
I 8
		if (cgp->cg_cs.cs_nbfree == 0) {
E 8
			brelse(bp);
D 21
			return (0);
E 21
I 21
			return (NULL);
E 21
		}
D 10
		bno = alloccgblk(dev, fs, cgp, bpref);
E 10
I 10
		bno = alloccgblk(fs, cgp, bpref);
E 10
D 14
		bpref = bno % fs->fs_fpg;
E 14
I 14
D 15
		bpref = dtogd(bno, fs);
E 15
I 15
		bpref = dtogd(fs, bno);
E 15
E 14
D 11
		for (i = frags; i < FRAG; i++)
E 11
I 11
		for (i = frags; i < fs->fs_frag; i++)
E 11
D 75
			setbit(cgp->cg_free, bpref + i);
E 75
I 75
			setbit(cg_blksfree(cgp), bpref + i);
E 75
D 11
		i = FRAG - frags;
E 11
I 11
		i = fs->fs_frag - frags;
E 11
D 8
		cgp->cg_nffree += i;
		fs->fs_nffree += i;
E 8
I 8
		cgp->cg_cs.cs_nffree += i;
		fs->fs_cstotal.cs_nffree += i;
D 11
		fs->fs_cs(cg).cs_nffree += i;
E 11
I 11
		fs->fs_cs(fs, cg).cs_nffree += i;
I 42
D 97
		fs->fs_fmod++;
E 97
I 97
		fs->fs_fmod = 1;
E 97
E 42
E 11
E 8
		cgp->cg_frsum[i]++;
		bdwrite(bp);
		return (bno);
	}
D 7
	/*
	 * find the fragment by searching through the free block
	 * map for an appropriate bit pattern
	 */
	if (bpref)
		start = bpref % fs->fs_fpg / NBBY;
	else
		start = cgp->cg_frotor / NBBY;
	len = roundup(fs->fs_fpg - 1, NBBY) / NBBY - start;
	loc = scanc(len, &cgp->cg_free[start], fragtbl, 1 << (allocsiz - 1));
	if (loc == 0) {
		len = start - 1;
		start = (cgdmin(cg, fs) - cgbase(cg, fs)) / NBBY;
		loc = scanc(len, &cgp->cg_free[start], fragtbl,
			1 << (allocsiz - 1));
		if (loc == 0)
			panic("alloccg: can't find frag");
	}
	bno = (start + len - loc) * NBBY;
	cgp->cg_frotor = bno;
	/*
	 * found the byte in the map
	 * sift through the bits to find the selected frag
	 */
	for (i = 0; i < NBBY; i += FRAG) {
		blk = (cgp->cg_free[bno / NBBY] >> i) & (0xff >> NBBY - FRAG);
		blk <<= 1;
		field = around[allocsiz];
		subfield = inside[allocsiz];
		for (pos = 0; pos <= FRAG - allocsiz; pos++) {
			if ((blk & field) == subfield) {
				bno += i + pos;
				goto gotit;
			}
			field <<= 1;
			subfield <<= 1;
		}
	}
	panic("alloccg: frag not in block");
gotit:
E 7
I 7
	bno = mapsearch(fs, cgp, bpref, allocsiz);
D 25
	if (bno == 0)
E 25
I 25
D 26
	if (bno == -1)
E 26
I 26
D 52
	if (bno < 0)
E 52
I 52
	if (bno < 0) {
		brelse(bp);
E 52
E 26
E 25
D 21
		return (0);
E 21
I 21
		return (NULL);
I 52
	}
E 52
E 21
E 7
	for (i = 0; i < frags; i++)
D 75
		clrbit(cgp->cg_free, bno + i);
E 75
I 75
		clrbit(cg_blksfree(cgp), bno + i);
E 75
D 8
	cgp->cg_nffree -= frags;
	fs->fs_nffree -= frags;
E 8
I 8
	cgp->cg_cs.cs_nffree -= frags;
	fs->fs_cstotal.cs_nffree -= frags;
D 11
	fs->fs_cs(cg).cs_nffree -= frags;
E 11
I 11
	fs->fs_cs(fs, cg).cs_nffree -= frags;
I 42
D 97
	fs->fs_fmod++;
E 97
I 97
	fs->fs_fmod = 1;
E 97
E 42
E 11
E 8
	cgp->cg_frsum[allocsiz]--;
	if (frags != allocsiz)
		cgp->cg_frsum[allocsiz - frags]++;
	bdwrite(bp);
	return (cg * fs->fs_fpg + bno);
E 98
I 98
	if (ifp->if_daddr == LFS_UNUSED_DADDR)
D 100
		panic("itod: unused daddr");
E 100
I 100
		panic("itod: unused disk address");
E 100
D 99
printf("itod: about to return %lx\n", ifp->if_daddr);
	return (ifp->if_daddr);
E 99
I 99
	iaddr = ifp->if_daddr;
	brelse(bp);
	return (iaddr);
E 99
E 98
}

I 100
/* Search a block for a specific dinode. */
E 100
I 14
D 98
/*
 * Allocate a block in a cylinder group.
 *
 * This algorithm implements the following policy:
 *   1) allocate the requested block.
 *   2) allocate a rotationally optimal block in the same cylinder.
 *   3) allocate the next available block on the block rotor for the
 *      specified cylinder group.
 * Note that this routine only allocates fs_bsize blocks; these
 * blocks may be fragmented by the routine that allocates them.
 */
E 14
daddr_t
D 10
alloccgblk(dev, fs, cgp, bpref)
	dev_t dev;
E 10
I 10
alloccgblk(fs, cgp, bpref)
E 10
D 19
	struct fs *fs;
E 19
I 19
	register struct fs *fs;
E 19
	register struct cg *cgp;
	daddr_t bpref;
E 98
I 98
D 99
struct dinode *
E 99
I 99
DINODE *
E 99
lfs_ifind(fs, ino, page)
	LFS *fs;
	ino_t ino;
	void *page;
E 98
{
D 7
	register int i;
E 7
I 7
D 98
	daddr_t bno;
D 21
	int cylno, pos;
E 21
I 21
	int cylno, pos, delta;
E 21
	short *cylbp;
D 13
	int i, j;
E 13
I 13
	register int i;
E 98
I 98
D 99
	register struct dinode *dip;
E 99
I 99
	register DINODE *dip;
E 99
	register int cnt;
E 98
E 13
E 7

E 4
D 7
	if (bpref) {
E 7
I 7
D 98
	if (bpref == 0) {
		bpref = cgp->cg_rotor;
I 13
		goto norot;
	}
D 55
	bpref &= ~(fs->fs_frag - 1);
E 55
I 55
	bpref = blknum(fs, bpref);
E 55
D 14
	bpref %= fs->fs_fpg;
E 14
I 14
D 15
	bpref = dtogd(bpref, fs);
E 15
I 15
	bpref = dtogd(fs, bpref);
E 15
E 14
	/*
	 * if the requested block is available, use it
	 */
I 29
D 41
/*
 * disallow sequential layout.
 *
E 41
E 29
D 46
	if (isblock(fs, cgp->cg_free, bpref/fs->fs_frag)) {
E 46
I 46
D 75
	if (isblock(fs, cgp->cg_free, fragstoblks(fs, bpref))) {
E 75
I 75
	if (isblock(fs, cg_blksfree(cgp), fragstoblks(fs, bpref))) {
E 75
E 46
		bno = bpref;
		goto gotit;
	}
I 29
D 41
 */
E 41
E 29
D 14
	if (fs->fs_cpc == 0)
		goto norot;
E 14
	/*
	 * check for a block available on the same cylinder
D 14
	 * beginning with one which is rotationally optimal
E 14
	 */
	cylno = cbtocylno(fs, bpref);
I 14
D 75
	if (cgp->cg_btot[cylno] == 0)
E 75
I 75
	if (cg_blktot(cgp)[cylno] == 0)
E 75
		goto norot;
	if (fs->fs_cpc == 0) {
		/*
		 * block layout info is not available, so just have
		 * to take any block in this cylinder.
		 */
		bpref = howmany(fs->fs_spc * cylno, NSPF(fs));
		goto norot;
	}
	/*
D 41
	 * find a block that is rotationally optimal
	 */
E 14
	cylbp = cgp->cg_b[cylno];
	if (fs->fs_rotdelay == 0) {
		pos = cbtorpos(fs, bpref);
E 13
	} else {
E 7
I 4
D 11
		bpref &= ~(FRAG - 1);
E 11
I 11
D 13
		bpref &= ~(fs->fs_frag - 1);
E 11
E 4
		bpref %= fs->fs_fpg;
E 13
D 7
		if (isblock(cgp->cg_free, bpref/FRAG))
			goto gotit;
	} else
		bpref = cgp->cg_rotor;
	for (i = 0; i < cgp->cg_ndblk; i += FRAG) {
		bpref += FRAG;
		if (bpref >= cgp->cg_ndblk)
			bpref = 0;
E 7
I 7
		/*
D 13
		 * if the requested block is available, use it
E 13
I 13
		 * here we convert ms of delay to frags as:
		 * (frags) = (ms) * (rev/sec) * (sect/rev) /
		 *	((sect/frag) * (ms/sec))
		 * then round up to the next rotational position
E 13
		 */
E 7
D 11
		if (isblock(cgp->cg_free, bpref/FRAG)) {
E 11
I 11
D 13
		if (isblock(fs, cgp->cg_free, bpref/fs->fs_frag)) {
E 11
D 7
			cgp->cg_rotor = bpref;
E 7
I 7
			bno = bpref;
E 7
			goto gotit;
		}
I 7
		/*
		 * check for a block available on the same cylinder
		 * beginning with one which is rotationally optimal
		 */
D 11
		i = bpref * NSPF;
E 11
I 11
		i = bpref * NSPF(fs);
E 11
		cylno = i / fs->fs_spc;
		cylbp = cgp->cg_b[cylno];
D 11
		pos = (i + (ROTDELAY == 0) ?
			0 : 1 + ROTDELAY * HZ * fs->fs_nsect / (NSPF * 1000)) %
			fs->fs_nsect * NRPOS / fs->fs_nsect;
E 11
I 11
		pos = (i + (fs->fs_rotdelay == 0) ? 0 :
		       1 + fs->fs_rotdelay * HZ * fs->fs_nsect /
		       (NSPF(fs) * 1000)) % fs->fs_nsect * NRPOS / fs->fs_nsect;
E 11
		for (i = pos; i < NRPOS; i++)
E 13
I 13
		bpref += fs->fs_rotdelay * fs->fs_rps * fs->fs_nsect /
		    (NSPF(fs) * 1000);
		pos = cbtorpos(fs, bpref);
		pos = (pos + 1) % NRPOS;
	}
	/*
E 41
	 * check the summary information to see if a block is 
	 * available in the requested cylinder starting at the
D 41
	 * optimal rotational position and proceeding around.
E 41
I 41
	 * requested rotational position and proceeding around.
E 41
	 */
I 41
D 75
	cylbp = cgp->cg_b[cylno];
E 75
I 75
	cylbp = cg_blks(fs, cgp, cylno);
E 75
	pos = cbtorpos(fs, bpref);
E 41
D 75
	for (i = pos; i < NRPOS; i++)
E 75
I 75
	for (i = pos; i < fs->fs_nrpos; i++)
E 75
		if (cylbp[i] > 0)
			break;
D 75
	if (i == NRPOS)
E 75
I 75
	if (i == fs->fs_nrpos)
E 75
		for (i = 0; i < pos; i++)
E 13
			if (cylbp[i] > 0)
				break;
D 13
		if (i == NRPOS)
			for (i = 0; i < pos; i++)
				if (cylbp[i] > 0)
					break;
		if (cylbp[i] > 0) {
D 11
			bpref = cylno * fs->fs_spc / (NSPF * FRAG);
E 11
I 11
			bpref = cylno * fs->fs_spc / NSPB(fs);
E 11
			for (j = fs->fs_postbl[i]; j > -1; j = fs->fs_rotbl[j]) {
D 11
				if (isblock(cgp->cg_free, bpref + j)) {
					bno = (bpref + j) * FRAG;
E 11
I 11
				if (isblock(fs, cgp->cg_free, bpref + j)) {
					bno = (bpref + j) * fs->fs_frag;
E 11
					goto gotit;
				}
E 13
I 13
	if (cylbp[i] > 0) {
		/*
		 * found a rotational position, now find the actual
		 * block. A panic if none is actually there.
		 */
		pos = cylno % fs->fs_cpc;
		bno = (cylno - pos) * fs->fs_spc / NSPB(fs);
D 27
		if (fs->fs_postbl[pos][i] == -1)
E 27
I 27
D 75
		if (fs->fs_postbl[pos][i] == -1) {
E 75
I 75
		if (fs_postbl(fs, pos)[i] == -1) {
E 75
			printf("pos = %d, i = %d, fs = %s\n",
			    pos, i, fs->fs_fsmnt);
E 27
			panic("alloccgblk: cyl groups corrupted");
I 27
		}
E 27
D 21
		for (i = fs->fs_postbl[pos][i]; ; i += fs->fs_rotbl[i]) {
E 21
I 21
D 75
		for (i = fs->fs_postbl[pos][i];; ) {
E 21
			if (isblock(fs, cgp->cg_free, bno + i)) {
E 75
I 75
		for (i = fs_postbl(fs, pos)[i];; ) {
			if (isblock(fs, cg_blksfree(cgp), bno + i)) {
E 75
D 46
				bno = (bno + i) * fs->fs_frag;
E 46
I 46
				bno = blkstofrags(fs, (bno + i));
E 46
				goto gotit;
E 13
			}
D 13
			panic("alloccgblk: can't find blk in cyl");
E 13
I 13
D 21
			if (fs->fs_rotbl[i] == 0)
E 21
I 21
D 75
			delta = fs->fs_rotbl[i];
			if (delta <= 0 || delta > MAXBPC - i)
E 75
I 75
			delta = fs_rotbl(fs)[i];
			if (delta <= 0 ||
			    delta + i > fragstoblks(fs, fs->fs_fpg))
E 75
E 21
				break;
I 21
			i += delta;
E 21
E 13
		}
I 27
		printf("pos = %d, i = %d, fs = %s\n", pos, i, fs->fs_fsmnt);
E 27
I 13
		panic("alloccgblk: can't find blk in cyl");
E 13
E 7
	}
I 13
norot:
	/*
	 * no blocks in the requested cylinder, so take next
	 * available one in this cylinder group.
	 */
E 13
D 4
	brelse(bp);
E 4
I 4
D 7
	panic("alloccgblk: can't find a blk");
E 4
	return (0);
E 7
I 7
D 11
	bno = mapsearch(fs, cgp, bpref, FRAG);
E 11
I 11
D 38
	bno = mapsearch(fs, cgp, bpref, fs->fs_frag);
E 38
I 38
	bno = mapsearch(fs, cgp, bpref, (int)fs->fs_frag);
E 38
E 11
D 25
	if (bno == 0)
E 25
I 25
D 26
	if (bno == -1)
E 26
I 26
	if (bno < 0)
E 26
E 25
D 21
		return (0);
E 21
I 21
		return (NULL);
E 21
	cgp->cg_rotor = bno;
E 7
gotit:
D 3
	clrblock(cgp->cg_free, bpref/FRAG);
	cgp->cg_nbfree--;
	fs->fs_nbfree--;
	fs->fs_cs[cg].cs_nbfree--;
E 3
I 3
D 4
	if (size == BSIZE) {
		clrblock(cgp->cg_free, bpref/FRAG);
		cgp->cg_nbfree--;
		fs->fs_nbfree--;
		fs->fs_cs[cg].cs_nbfree--;
		i = bpref * NSPF;
		cgp->cg_b[i/fs->fs_spc][i%fs->fs_nsect*NRPOS/fs->fs_nsect]--;
	} else {
		cgp->cg_nffree += FRAG;
		fs->fs_nffree += FRAG;
		for (i = 0; i < size / FSIZE; i++) {
			clrbit(cgp->cg_free, bpref + i);
			cgp->cg_nffree--;
			fs->fs_nffree--;
		}
		cgp->cg_nbfree--;
		fs->fs_nbfree--;
		fs->fs_cs[cg].cs_nbfree--;
		i = bpref * NSPF;
		cgp->cg_b[i/fs->fs_spc][i%fs->fs_nsect*NRPOS/fs->fs_nsect]--;
	}
E 4
I 4
D 7
	clrblock(cgp->cg_free, bpref/FRAG);
E 7
I 7
D 11
	clrblock(cgp->cg_free, bno/FRAG);
E 11
I 11
D 38
	clrblock(fs, cgp->cg_free, bno/fs->fs_frag);
E 38
I 38
D 40
	clrblock(fs, cgp->cg_free, (int)(bno/fs->fs_frag));
E 40
I 40
D 46
	clrblock(fs, cgp->cg_free, (long)(bno/fs->fs_frag));
E 46
I 46
D 75
	clrblock(fs, cgp->cg_free, (long)fragstoblks(fs, bno));
E 75
I 75
	clrblock(fs, cg_blksfree(cgp), (long)fragstoblks(fs, bno));
E 75
E 46
E 40
E 38
E 11
E 7
D 8
	cgp->cg_nbfree--;
	fs->fs_nbfree--;
E 8
I 8
	cgp->cg_cs.cs_nbfree--;
	fs->fs_cstotal.cs_nbfree--;
E 8
D 7
	fs->fs_cs[cgp->cg_cgx].cs_nbfree--;
	i = bpref * NSPF;
E 7
I 7
D 11
	fs->fs_cs(cgp->cg_cgx).cs_nbfree--;
	i = bno * NSPF;
E 11
I 11
	fs->fs_cs(fs, cgp->cg_cgx).cs_nbfree--;
D 13
	i = bno * NSPF(fs);
E 11
E 7
	cgp->cg_b[i/fs->fs_spc][i%fs->fs_nsect*NRPOS/fs->fs_nsect]--;
E 13
I 13
D 14
	cgp->cg_b[cbtocylno(fs, bno)][cbtorpos(fs, bno)]--;
E 14
I 14
	cylno = cbtocylno(fs, bno);
D 75
	cgp->cg_b[cylno][cbtorpos(fs, bno)]--;
	cgp->cg_btot[cylno]--;
E 75
I 75
	cg_blks(fs, cgp, cylno)[cbtorpos(fs, bno)]--;
	cg_blktot(cgp)[cylno]--;
E 75
E 14
E 13
E 4
E 3
D 97
	fs->fs_fmod++;
E 97
I 97
	fs->fs_fmod = 1;
E 97
D 3
	i = bpref * NSPF;
	cgp->cg_b[i/fs->fs_spc][i%fs->fs_nsect*NRPOS/fs->fs_nsect]--;
E 3
D 4
	bdwrite(bp);
	return (cg * fs->fs_fpg + bpref);
E 4
I 4
D 7
	return (cgp->cg_cgx * fs->fs_fpg + bpref);
E 7
I 7
	return (cgp->cg_cgx * fs->fs_fpg + bno);
E 7
E 4
}
E 98
I 98
printf("lfs_ifind: inode %d\n", ino);
	dip = page;
	for (cnt = INOPB(fs); cnt--; ++dip)
		if (dip->di_inum == ino)
			return (dip);
E 98
D 75
	
E 75
I 75

E 75
I 14
D 98
/*
 * Determine whether an inode can be allocated.
 *
 * Check to see if an inode is available, and if it is,
 * allocate it using the following policy:
 *   1) allocate the requested inode.
 *   2) allocate the next available inode after the requested
 *      inode in the specified cylinder group.
 */
E 14
D 10
long
E 10
I 10
D 38
ino_t
E 38
I 38
D 41
u_long
E 41
I 41
ino_t
E 41
E 38
E 10
D 19
ialloccg(dev, fs, cg, ipref, mode)
	dev_t dev;
D 4
	struct fs *fs;
E 4
I 4
	register struct fs *fs;
E 19
I 19
ialloccg(ip, cg, ipref, mode)
	struct inode *ip;
E 19
E 4
	int cg;
	daddr_t ipref;
	int mode;
{
I 19
	register struct fs *fs;
E 19
D 4
	struct buf *bp;
	struct cg *cgp;
E 4
I 4
D 53
	register struct buf *bp;
E 53
	register struct cg *cgp;
E 4
D 53
	int i;
E 53
I 53
	struct buf *bp;
D 79
	int start, len, loc, map, i;
E 79
I 79
	int error, start, len, loc, map, i;
E 79
E 53

I 19
	fs = ip->i_fs;
E 19
I 8
D 11
	if (fs->fs_cs(cg).cs_nifree == 0)
E 11
I 11
	if (fs->fs_cs(fs, cg).cs_nifree == 0)
E 11
D 21
		return (0);
E 21
I 21
		return (NULL);
I 70
#ifdef SECSIZE
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_cgsize,
	    fs->fs_dbsize);
#else SECSIZE
E 70
E 21
E 8
D 3
	bp = bread(dev, cgtod(cg, fs));
E 3
I 3
D 11
	bp = bread(dev, cgtod(cg, fs), BSIZE);
E 11
I 11
D 15
	bp = bread(dev, fsbtodb(fs, cgtod(cg, fs)), fs->fs_bsize);
E 15
I 15
D 19
	bp = bread(dev, fsbtodb(fs, cgtod(fs, cg)), fs->fs_bsize);
E 19
I 19
D 37
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), fs->fs_bsize);
E 37
I 37
D 43
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_bsize);
E 43
I 43
D 79
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_cgsize);
E 79
I 79
	error = bread(ip->i_devvp, fsbtodb(fs, cgtod(fs, cg)),
D 81
		(int)fs->fs_cgsize, &bp);
E 81
I 81
		(int)fs->fs_cgsize, NOCRED, &bp);
E 81
	if (error) {
		brelse(bp);
		return (NULL);
	}
E 79
I 70
#endif SECSIZE
E 70
E 43
E 37
E 19
E 15
E 11
E 3
D 18
	if (bp->b_flags & B_ERROR)
		return (0);
E 18
I 18
D 25
	if (bp->b_flags & B_ERROR) {
E 25
I 25
	cgp = bp->b_un.b_cg;
D 52
	if (bp->b_flags & B_ERROR || cgp->cg_magic != CG_MAGIC) {
E 52
I 52
D 75
	if (bp->b_flags & B_ERROR || cgp->cg_magic != CG_MAGIC ||
E 75
I 75
D 79
	if (bp->b_flags & B_ERROR || !cg_chkmagic(cgp) ||
E 75
	    cgp->cg_cs.cs_nifree == 0) {
E 79
I 79
	if (!cg_chkmagic(cgp) || cgp->cg_cs.cs_nifree == 0) {
E 79
E 52
E 25
		brelse(bp);
D 21
		return 0;
E 21
I 21
		return (NULL);
E 21
	}
I 43
D 52
	if (cgp->cg_cs.cs_nifree == 0)
		return (NULL);
E 52
E 43
I 28
D 33
	cgp->cg_time = time;
E 33
I 33
	cgp->cg_time = time.tv_sec;
E 33
E 28
E 18
D 25
	cgp = bp->b_un.b_cg;
E 25
D 8
	if (cgp->cg_nifree == 0) {
		brelse(bp);
		return (0);
	}
E 8
	if (ipref) {
		ipref %= fs->fs_ipg;
D 75
		if (isclr(cgp->cg_iused, ipref))
E 75
I 75
		if (isclr(cg_inosused(cgp), ipref))
E 75
			goto gotit;
D 53
	} else
		ipref = cgp->cg_irotor;
	for (i = 0; i < fs->fs_ipg; i++) {
		ipref++;
		if (ipref >= fs->fs_ipg)
			ipref = 0;
		if (isclr(cgp->cg_iused, ipref)) {
E 53
I 53
	}
	start = cgp->cg_irotor / NBBY;
	len = howmany(fs->fs_ipg - cgp->cg_irotor, NBBY);
D 75
	loc = skpc(0xff, len, &cgp->cg_iused[start]);
E 75
I 75
	loc = skpc(0xff, len, &cg_inosused(cgp)[start]);
E 75
	if (loc == 0) {
D 59
		printf("cg = %s, irotor = %d, fs = %s\n",
		    cg, cgp->cg_irotor, fs->fs_fsmnt);
		panic("ialloccg: map corrupted");
		/* NOTREACHED */
E 59
I 59
		len = start + 1;
		start = 0;
D 75
		loc = skpc(0xff, len, &cgp->cg_iused[0]);
E 75
I 75
		loc = skpc(0xff, len, &cg_inosused(cgp)[0]);
E 75
		if (loc == 0) {
			printf("cg = %s, irotor = %d, fs = %s\n",
			    cg, cgp->cg_irotor, fs->fs_fsmnt);
			panic("ialloccg: map corrupted");
			/* NOTREACHED */
		}
E 59
	}
	i = start + len - loc;
D 75
	map = cgp->cg_iused[i];
E 75
I 75
	map = cg_inosused(cgp)[i];
E 75
	ipref = i * NBBY;
	for (i = 1; i < (1 << NBBY); i <<= 1, ipref++) {
		if ((map & i) == 0) {
E 53
			cgp->cg_irotor = ipref;
			goto gotit;
		}
	}
D 53
	brelse(bp);
D 21
	return (0);
E 21
I 21
	return (NULL);
E 53
I 53
	printf("fs = %s\n", fs->fs_fsmnt);
	panic("ialloccg: block not in map");
E 98
I 98
D 100
	(void)printf("lfs_ifind: dinode %u not found", ino);
	panic("lfs_ifind: inode not found");
E 100
I 100
	panic("lfs_ifind: dinode %%u not found", ino);
E 100
E 98
	/* NOTREACHED */
E 53
E 21
D 98
gotit:
D 75
	setbit(cgp->cg_iused, ipref);
E 75
I 75
	setbit(cg_inosused(cgp), ipref);
E 75
D 8
	cgp->cg_nifree--;
	fs->fs_nifree--;
E 8
I 8
	cgp->cg_cs.cs_nifree--;
	fs->fs_cstotal.cs_nifree--;
E 8
D 7
	fs->fs_cs[cg].cs_nifree--;
E 7
I 7
D 11
	fs->fs_cs(cg).cs_nifree--;
E 11
I 11
	fs->fs_cs(fs, cg).cs_nifree--;
E 11
E 7
D 97
	fs->fs_fmod++;
E 97
I 97
	fs->fs_fmod = 1;
E 97
	if ((mode & IFMT) == IFDIR) {
D 8
		cgp->cg_ndir++;
E 8
I 8
		cgp->cg_cs.cs_ndir++;
		fs->fs_cstotal.cs_ndir++;
E 8
D 7
		fs->fs_cs[cg].cs_ndir++;
E 7
I 7
D 11
		fs->fs_cs(cg).cs_ndir++;
E 11
I 11
		fs->fs_cs(fs, cg).cs_ndir++;
E 11
E 7
	}
	bdwrite(bp);
	return (cg * fs->fs_ipg + ipref);
E 98
}

E 103
I 14
D 100
/*
D 98
 * Free a block or fragment.
 *
 * The specified block or fragment is placed back in the
 * free map. If a fragment is deallocated, a possible 
 * block reassembly is checked.
E 98
I 98
 * Create a new vnode/inode and initialize the fields we can.
E 98
 */
E 100
I 100
/* Create a new vnode/inode pair and initialize what fields we can. */
I 102
int
E 102
E 100
E 14
D 19
fre(dev, bno, size)
	dev_t dev;
E 19
I 19
D 41
fre(ip, bno, size)
E 41
I 41
D 72
free(ip, bno, size)
E 72
I 72
D 98
blkfree(ip, bno, size)
E 72
E 41
	register struct inode *ip;
E 19
	daddr_t bno;
D 10
	int size;
E 10
I 10
	off_t size;
E 10
{
	register struct fs *fs;
	register struct cg *cgp;
D 79
	register struct buf *bp;
D 4
	int i;
	int cg;
E 4
I 4
	int cg, blk, frags, bbase;
E 79
I 79
	struct buf *bp;
	int error, cg, blk, frags, bbase;
E 79
	register int i;
I 89
D 94
	struct ucred *cred = u.u_cred;	/* XXX */
E 94
I 94
	struct ucred *cred = curproc->p_ucred;	/* XXX */
E 94
E 89
E 4

D 3
	if (size != BSIZE)
		panic("free: size != BSIZE is too hard!");
E 3
I 3
D 11
	if ((unsigned)size > BSIZE || size % FSIZE != 0)
		panic("free: bad size");
E 11
E 3
D 19
	fs = getfs(dev);
E 19
I 19
	fs = ip->i_fs;
E 19
I 11
D 18
	if ((unsigned)size > fs->fs_bsize || size % fs->fs_fsize != 0)
E 18
I 18
D 27
	if ((unsigned)size > fs->fs_bsize || fragoff(fs, size) != 0)
E 27
I 27
	if ((unsigned)size > fs->fs_bsize || fragoff(fs, size) != 0) {
		printf("dev = 0x%x, bsize = %d, size = %d, fs = %s\n",
		    ip->i_dev, fs->fs_bsize, size, fs->fs_fsmnt);
E 27
E 18
D 72
		panic("free: bad size");
E 72
I 72
		panic("blkfree: bad size");
E 72
I 27
	}
E 27
E 11
D 15
	cg = dtog(bno, fs);
E 15
I 15
	cg = dtog(fs, bno);
E 15
D 26
	if (badblock(fs, bno))
E 26
I 26
D 89
	if (badblock(fs, bno)) {
E 89
I 89
	if ((unsigned)bno >= fs->fs_size) {
E 89
		printf("bad block %d, ino %d\n", bno, ip->i_number);
I 89
		fserr(fs, cred->cr_uid, "bad block");
E 89
E 26
		return;
I 26
	}
I 70
#ifdef SECSIZE
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_cgsize,
	    fs->fs_dbsize);
#else SECSIZE
E 70
E 26
D 3
	bp = bread(dev, cgtod(cg, fs));
E 3
I 3
D 11
	bp = bread(dev, cgtod(cg, fs), BSIZE);
E 11
I 11
D 15
	bp = bread(dev, fsbtodb(fs, cgtod(cg, fs)), fs->fs_bsize);
E 15
I 15
D 19
	bp = bread(dev, fsbtodb(fs, cgtod(fs, cg)), fs->fs_bsize);
E 19
I 19
D 37
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), fs->fs_bsize);
E 37
I 37
D 43
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_bsize);
E 43
I 43
D 79
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_cgsize);
E 79
I 79
	error = bread(ip->i_devvp, fsbtodb(fs, cgtod(fs, cg)),
D 81
		(int)fs->fs_cgsize, &bp);
E 81
I 81
		(int)fs->fs_cgsize, NOCRED, &bp);
E 81
	if (error) {
		brelse(bp);
		return;
	}
E 79
I 70
#endif SECSIZE
E 70
E 43
E 37
E 19
E 15
E 11
E 3
D 18
	if (bp->b_flags & B_ERROR)
E 18
I 18
D 25
	if (bp->b_flags & B_ERROR) {
E 25
I 25
	cgp = bp->b_un.b_cg;
D 75
	if (bp->b_flags & B_ERROR || cgp->cg_magic != CG_MAGIC) {
E 75
I 75
D 79
	if (bp->b_flags & B_ERROR || !cg_chkmagic(cgp)) {
E 79
I 79
	if (!cg_chkmagic(cgp)) {
E 79
E 75
E 25
		brelse(bp);
E 18
		return;
I 18
	}
I 28
D 33
	cgp->cg_time = time;
E 33
I 33
	cgp->cg_time = time.tv_sec;
E 33
E 28
E 18
D 25
	cgp = bp->b_un.b_cg;
E 25
D 14
	bno %= fs->fs_fpg;
E 14
I 14
D 15
	bno = dtogd(bno, fs);
E 15
I 15
	bno = dtogd(fs, bno);
E 15
E 14
D 3
	if (isblock(cgp->cg_free, bno/FRAG))
		panic("free: freeing free block");
	setblock(cgp->cg_free, bno/FRAG);
	cgp->cg_nbfree++;
	fs->fs_nbfree++;
	fs->fs_cs[cg].cs_nbfree++;
E 3
I 3
D 11
	if (size == BSIZE) {
		if (isblock(cgp->cg_free, bno/FRAG))
E 11
I 11
	if (size == fs->fs_bsize) {
D 26
		if (isblock(fs, cgp->cg_free, bno/fs->fs_frag))
E 26
I 26
D 46
		if (isblock(fs, cgp->cg_free, bno/fs->fs_frag)) {
E 46
I 46
D 75
		if (isblock(fs, cgp->cg_free, fragstoblks(fs, bno))) {
E 75
I 75
		if (isblock(fs, cg_blksfree(cgp), fragstoblks(fs, bno))) {
E 75
E 46
D 27
			printf("free block %d, fs %s\n", bno, fs->fs_fsmnt);
E 27
I 27
			printf("dev = 0x%x, block = %d, fs = %s\n",
			    ip->i_dev, bno, fs->fs_fsmnt);
E 27
E 26
E 11
D 72
			panic("free: freeing free block");
E 72
I 72
			panic("blkfree: freeing free block");
E 72
I 26
		}
E 26
D 11
		setblock(cgp->cg_free, bno/FRAG);
E 11
I 11
D 46
		setblock(fs, cgp->cg_free, bno/fs->fs_frag);
E 46
I 46
D 75
		setblock(fs, cgp->cg_free, fragstoblks(fs, bno));
E 75
I 75
		setblock(fs, cg_blksfree(cgp), fragstoblks(fs, bno));
E 75
E 46
E 11
D 8
		cgp->cg_nbfree++;
		fs->fs_nbfree++;
E 8
I 8
		cgp->cg_cs.cs_nbfree++;
		fs->fs_cstotal.cs_nbfree++;
E 8
D 7
		fs->fs_cs[cg].cs_nbfree++;
E 7
I 7
D 11
		fs->fs_cs(cg).cs_nbfree++;
E 7
		i = bno * NSPF;
E 11
I 11
		fs->fs_cs(fs, cg).cs_nbfree++;
D 13
		i = bno * NSPF(fs);
E 11
		cgp->cg_b[i/fs->fs_spc][i%fs->fs_nsect*NRPOS/fs->fs_nsect]++;
E 13
I 13
D 14
		cgp->cg_b[cbtocylno(fs, bno)][cbtorpos(fs, bno)]++;
E 14
I 14
		i = cbtocylno(fs, bno);
D 75
		cgp->cg_b[i][cbtorpos(fs, bno)]++;
		cgp->cg_btot[i]++;
E 75
I 75
		cg_blks(fs, cgp, i)[cbtorpos(fs, bno)]++;
		cg_blktot(cgp)[i]++;
E 75
E 14
E 13
	} else {
D 4
		for (i = 0; i < size / FSIZE; i++) {
E 4
I 4
D 11
		bbase = bno - (bno % FRAG);
E 11
I 11
D 55
		bbase = bno - (bno % fs->fs_frag);
E 55
I 55
		bbase = bno - fragnum(fs, bno);
E 55
E 11
		/*
		 * decrement the counts associated with the old frags
		 */
D 21
		blk = ((cgp->cg_free[bbase / NBBY] >> (bbase % NBBY)) &
D 11
		       (0xff >> (NBBY - FRAG)));
		fragacct(blk, cgp->cg_frsum, -1);
E 11
I 11
		       (0xff >> (NBBY - fs->fs_frag)));
E 21
I 21
D 75
		blk = blkmap(fs, cgp->cg_free, bbase);
E 75
I 75
		blk = blkmap(fs, cg_blksfree(cgp), bbase);
E 75
E 21
		fragacct(fs, blk, cgp->cg_frsum, -1);
E 11
		/*
		 * deallocate the fragment
		 */
D 11
		frags = size / FSIZE;
E 11
I 11
D 18
		frags = size / fs->fs_fsize;
E 18
I 18
		frags = numfrags(fs, size);
E 18
E 11
		for (i = 0; i < frags; i++) {
E 4
D 27
			if (isset(cgp->cg_free, bno + i))
E 27
I 27
D 75
			if (isset(cgp->cg_free, bno + i)) {
E 75
I 75
			if (isset(cg_blksfree(cgp), bno + i)) {
E 75
				printf("dev = 0x%x, block = %d, fs = %s\n",
				    ip->i_dev, bno + i, fs->fs_fsmnt);
E 27
D 72
				panic("free: freeing free frag");
E 72
I 72
				panic("blkfree: freeing free frag");
E 72
I 27
			}
E 27
D 75
			setbit(cgp->cg_free, bno + i);
E 75
I 75
			setbit(cg_blksfree(cgp), bno + i);
E 75
D 8
			cgp->cg_nffree++;
			fs->fs_nffree++;
E 8
I 8
D 21
			cgp->cg_cs.cs_nffree++;
			fs->fs_cstotal.cs_nffree++;
D 11
			fs->fs_cs(cg).cs_nffree++;
E 11
I 11
			fs->fs_cs(fs, cg).cs_nffree++;
E 21
E 11
E 8
		}
I 21
		cgp->cg_cs.cs_nffree += i;
		fs->fs_cstotal.cs_nffree += i;
		fs->fs_cs(fs, cg).cs_nffree += i;
E 21
D 4
		if (isblock(cgp->cg_free, (bno - bno % FRAG) / FRAG)) {
E 4
I 4
		/*
		 * add back in counts associated with the new frags
		 */
D 21
		blk = ((cgp->cg_free[bbase / NBBY] >> (bbase % NBBY)) &
D 11
		       (0xff >> (NBBY - FRAG)));
		fragacct(blk, cgp->cg_frsum, 1);
E 11
I 11
		       (0xff >> (NBBY - fs->fs_frag)));
E 21
I 21
D 75
		blk = blkmap(fs, cgp->cg_free, bbase);
E 75
I 75
		blk = blkmap(fs, cg_blksfree(cgp), bbase);
E 75
E 21
		fragacct(fs, blk, cgp->cg_frsum, 1);
E 11
		/*
		 * if a complete block has been reassembled, account for it
		 */
D 11
		if (isblock(cgp->cg_free, bbase / FRAG)) {
E 4
D 8
			cgp->cg_nffree -= FRAG;
			fs->fs_nffree -= FRAG;
			cgp->cg_nbfree++;
			fs->fs_nbfree++;
E 8
I 8
			cgp->cg_cs.cs_nffree -= FRAG;
			fs->fs_cstotal.cs_nffree -= FRAG;
			fs->fs_cs(cg).cs_nffree -= FRAG;
E 11
I 11
D 46
		if (isblock(fs, cgp->cg_free, bbase / fs->fs_frag)) {
E 46
I 46
D 75
		if (isblock(fs, cgp->cg_free, fragstoblks(fs, bbase))) {
E 75
I 75
D 77
		if (isblock(fs, cg_blksfree(cgp), fragstoblks(fs, bbase))) {
E 77
I 77
		if (isblock(fs, cg_blksfree(cgp),
		    (daddr_t)fragstoblks(fs, bbase))) {
E 77
E 75
E 46
			cgp->cg_cs.cs_nffree -= fs->fs_frag;
			fs->fs_cstotal.cs_nffree -= fs->fs_frag;
			fs->fs_cs(fs, cg).cs_nffree -= fs->fs_frag;
E 11
			cgp->cg_cs.cs_nbfree++;
			fs->fs_cstotal.cs_nbfree++;
E 8
D 7
			fs->fs_cs[cg].cs_nbfree++;
E 7
I 7
D 11
			fs->fs_cs(cg).cs_nbfree++;
E 7
D 4
			i = bno * NSPF;
E 4
I 4
			i = bbase * NSPF;
E 11
I 11
			fs->fs_cs(fs, cg).cs_nbfree++;
D 13
			i = bbase * NSPF(fs);
E 11
E 4
			cgp->cg_b[i / fs->fs_spc]
				 [i % fs->fs_nsect * NRPOS / fs->fs_nsect]++;
E 13
I 13
D 14
			cgp->cg_b[cbtocylno(fs, bbase)][cbtorpos(fs, bbase)]++;
E 14
I 14
			i = cbtocylno(fs, bbase);
D 75
			cgp->cg_b[i][cbtorpos(fs, bbase)]++;
			cgp->cg_btot[i]++;
E 75
I 75
			cg_blks(fs, cgp, i)[cbtorpos(fs, bbase)]++;
			cg_blktot(cgp)[i]++;
E 75
E 14
E 13
		}
	}
E 3
D 97
	fs->fs_fmod++;
E 97
I 97
	fs->fs_fmod = 1;
E 97
D 3
	i = bno * NSPF;
	cgp->cg_b[i/fs->fs_spc][i%fs->fs_nsect*NRPOS/fs->fs_nsect]++;
E 3
	bdwrite(bp);
}

I 14
/*
 * Free an inode.
 *
 * The specified inode is placed back in the free map.
 */
E 14
D 19
ifree(dev, ino, mode)
	dev_t dev;
E 19
I 19
ifree(ip, ino, mode)
	struct inode *ip;
E 98
I 98
lfs_vcreate(mp, ino, vpp)
D 99
	struct mount *mp;
E 99
I 99
D 109
	MOUNT *mp;
E 109
I 109
	struct mount *mp;
E 109
E 99
E 98
E 19
	ino_t ino;
D 98
	int mode;
E 98
I 98
D 99
	struct vnode **vpp;
E 99
I 99
D 109
	VNODE **vpp;
E 109
I 109
	struct vnode **vpp;
E 109
E 99
E 98
{
I 105
D 125
	extern struct vnodeops lfs_vnodeops;
E 125
I 125
	extern int (**lfs_vnodeop_p)();
E 125
E 105
D 98
	register struct fs *fs;
	register struct cg *cgp;
D 79
	register struct buf *bp;
D 10
	int i;
E 10
	int cg;
E 79
I 79
	struct buf *bp;
	int error, cg;
E 98
I 98
D 99
	struct inode *ip;
	struct ufsmount *ump;
E 99
I 99
D 109
	INODE *ip;
	UFSMOUNT *ump;
E 109
I 109
	struct inode *ip;
	struct ufsmount *ump;
E 109
E 99
	int error, i;
E 98
E 79

D 19
	fs = getfs(dev);
E 19
I 19
D 98
	fs = ip->i_fs;
E 19
D 27
	if ((unsigned)ino >= fs->fs_ipg*fs->fs_ncg)
E 27
I 27
	if ((unsigned)ino >= fs->fs_ipg*fs->fs_ncg) {
		printf("dev = 0x%x, ino = %d, fs = %s\n",
		    ip->i_dev, ino, fs->fs_fsmnt);
E 27
		panic("ifree: range");
I 27
	}
E 27
D 15
	cg = itog(ino, fs);
D 3
	bp = bread(dev, cgtod(cg, fs));
E 3
I 3
D 11
	bp = bread(dev, cgtod(cg, fs), BSIZE);
E 11
I 11
	bp = bread(dev, fsbtodb(fs, cgtod(cg, fs)), fs->fs_bsize);
E 15
I 15
	cg = itog(fs, ino);
I 70
#ifdef SECSIZE
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_cgsize,
	    fs->fs_dbsize);
#else SECSIZE
E 70
D 19
	bp = bread(dev, fsbtodb(fs, cgtod(fs, cg)), fs->fs_bsize);
E 19
I 19
D 37
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), fs->fs_bsize);
E 37
I 37
D 43
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_bsize);
E 43
I 43
D 79
	bp = bread(ip->i_dev, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_cgsize);
E 79
I 79
	error = bread(ip->i_devvp, fsbtodb(fs, cgtod(fs, cg)),
D 81
		(int)fs->fs_cgsize, &bp);
E 81
I 81
		(int)fs->fs_cgsize, NOCRED, &bp);
E 81
	if (error) {
		brelse(bp);
		return;
	}
E 79
I 70
#endif SECSIZE
E 70
E 43
E 37
E 19
E 15
E 11
E 3
D 18
	if (bp->b_flags & B_ERROR)
E 18
I 18
D 25
	if (bp->b_flags & B_ERROR) {
E 25
I 25
	cgp = bp->b_un.b_cg;
D 75
	if (bp->b_flags & B_ERROR || cgp->cg_magic != CG_MAGIC) {
E 75
I 75
D 79
	if (bp->b_flags & B_ERROR || !cg_chkmagic(cgp)) {
E 79
I 79
	if (!cg_chkmagic(cgp)) {
E 79
E 75
E 25
		brelse(bp);
E 18
		return;
I 18
	}
I 28
D 33
	cgp->cg_time = time;
E 33
I 33
	cgp->cg_time = time.tv_sec;
E 33
E 28
E 18
D 25
	cgp = bp->b_un.b_cg;
E 25
	ino %= fs->fs_ipg;
D 27
	if (isclr(cgp->cg_iused, ino))
E 27
I 27
D 75
	if (isclr(cgp->cg_iused, ino)) {
E 75
I 75
	if (isclr(cg_inosused(cgp), ino)) {
E 75
		printf("dev = 0x%x, ino = %d, fs = %s\n",
		    ip->i_dev, ino, fs->fs_fsmnt);
E 27
D 95
		panic("ifree: freeing free inode");
E 95
I 95
		if (fs->fs_ronly == 0)
			panic("ifree: freeing free inode");
E 95
I 27
	}
E 27
D 75
	clrbit(cgp->cg_iused, ino);
E 75
I 75
	clrbit(cg_inosused(cgp), ino);
E 75
I 53
	if (ino < cgp->cg_irotor)
		cgp->cg_irotor = ino;
E 53
D 8
	cgp->cg_nifree++;
	fs->fs_nifree++;
E 8
I 8
	cgp->cg_cs.cs_nifree++;
	fs->fs_cstotal.cs_nifree++;
E 8
D 7
	fs->fs_cs[cg].cs_nifree++;
E 7
I 7
D 11
	fs->fs_cs(cg).cs_nifree++;
E 11
I 11
	fs->fs_cs(fs, cg).cs_nifree++;
E 11
E 7
	if ((mode & IFMT) == IFDIR) {
D 8
		cgp->cg_ndir--;
E 8
I 8
		cgp->cg_cs.cs_ndir--;
		fs->fs_cstotal.cs_ndir--;
E 8
D 7
		fs->fs_cs[cg].cs_ndir--;
E 7
I 7
D 11
		fs->fs_cs(cg).cs_ndir--;
E 11
I 11
		fs->fs_cs(fs, cg).cs_ndir--;
E 11
E 7
	}
D 97
	fs->fs_fmod++;
E 97
I 97
	fs->fs_fmod = 1;
E 97
	bdwrite(bp);
I 4
}
E 98
I 98
D 103
printf("lfs_vcreate: ino %d\n", ino);
E 103
I 103
D 106
#ifdef ALLOCPRINT
E 106
I 106
D 133
#ifdef VERBOSE
E 106
	printf("lfs_vcreate: ino %d\n", ino);
#endif
E 133
E 103
D 100
	error = getnewvnode(VT_LFS, mp, &lfs_vnodeops, vpp);
	if (error)
E 100
I 100
	/* Create the vnode. */
D 108
	if (error = getnewvnode(VT_LFS, mp, &lfs_vnodeops, vpp))
E 108
I 108
D 125
	if (error = getnewvnode(VT_LFS, mp, &lfs_vnodeops, vpp)) {
E 125
I 125
	if (error = getnewvnode(VT_LFS, mp, lfs_vnodeop_p, vpp)) {
E 125
		*vpp = NULL;
E 108
E 100
D 101
		return(error);
E 101
I 101
		return (error);
I 108
	}
E 108
E 101
E 98

I 100
	/* Get a pointer to the private mount structure. */
E 100
D 98
/*
I 7
D 14
 * find a block of the specified size in the specified cylinder group
E 14
I 14
 * Find a block of the specified size in the specified cylinder group.
 *
E 14
 * It is a panic if a request is made to find a block if none are
 * available.
 */
daddr_t
mapsearch(fs, cgp, bpref, allocsiz)
	register struct fs *fs;
	register struct cg *cgp;
	daddr_t bpref;
	int allocsiz;
{
	daddr_t bno;
	int start, len, loc, i;
	int blk, field, subfield, pos;
E 98
I 98
	ump = VFSTOUFS(mp);
E 98

D 98
	/*
	 * find the fragment by searching through the free block
	 * map for an appropriate bit pattern
	 */
	if (bpref)
D 14
		start = bpref % fs->fs_fpg / NBBY;
E 14
I 14
D 15
		start = dtogd(bpref, fs) / NBBY;
E 15
I 15
		start = dtogd(fs, bpref) / NBBY;
E 15
E 14
	else
		start = cgp->cg_frotor / NBBY;
D 16
	len = roundup(fs->fs_fpg - 1, NBBY) / NBBY - start;
E 16
I 16
	len = howmany(fs->fs_fpg, NBBY) - start;
E 16
D 11
	loc = scanc(len, &cgp->cg_free[start], fragtbl, 1 << (allocsiz - 1));
E 11
I 11
D 48
	loc = scanc(len, &cgp->cg_free[start], fragtbl[fs->fs_frag],
D 20
		1 << (allocsiz - 1));
E 20
I 20
		1 << (allocsiz - 1 + (fs->fs_frag % NBBY)));
E 48
I 48
D 75
	loc = scanc((unsigned)len, (caddr_t)&cgp->cg_free[start],
E 75
I 75
D 77
	loc = scanc((unsigned)len, (caddr_t)&cg_blksfree(cgp)[start],
E 75
		(caddr_t)fragtbl[fs->fs_frag],
		(int)(1 << (allocsiz - 1 + (fs->fs_frag % NBBY))));
E 77
I 77
	loc = scanc((unsigned)len, (u_char *)&cg_blksfree(cgp)[start],
		(u_char *)fragtbl[fs->fs_frag],
		(u_char)(1 << (allocsiz - 1 + (fs->fs_frag % NBBY))));
E 77
E 48
E 20
E 11
	if (loc == 0) {
D 16
		len = start - 1;
D 14
		start = (cgdmin(cgp->cg_cgx, fs) -
			 cgbase(cgp->cg_cgx, fs)) / NBBY;
E 14
I 14
		start = fs->fs_dblkno / NBBY;
E 16
I 16
D 25
		loc = fs->fs_dblkno / NBBY;
		len = start - loc + 1;
		start = loc;
E 25
I 25
		len = start + 1;
		start = 0;
E 25
E 16
E 14
D 11
		loc = scanc(len, &cgp->cg_free[start], fragtbl,
E 11
I 11
D 48
		loc = scanc(len, &cgp->cg_free[start], fragtbl[fs->fs_frag],
E 11
D 20
			1 << (allocsiz - 1));
E 20
I 20
			1 << (allocsiz - 1 + (fs->fs_frag % NBBY)));
E 48
I 48
D 59
		loc = scanc((unsigned)len, (caddr_t)&cgp->cg_free[start],
E 59
I 59
D 75
		loc = scanc((unsigned)len, (caddr_t)&cgp->cg_free[0],
E 75
I 75
D 77
		loc = scanc((unsigned)len, (caddr_t)&cg_blksfree(cgp)[0],
E 75
E 59
			(caddr_t)fragtbl[fs->fs_frag],
			(int)(1 << (allocsiz - 1 + (fs->fs_frag % NBBY))));
E 77
I 77
		loc = scanc((unsigned)len, (u_char *)&cg_blksfree(cgp)[0],
			(u_char *)fragtbl[fs->fs_frag],
			(u_char)(1 << (allocsiz - 1 + (fs->fs_frag % NBBY))));
E 77
E 48
E 20
D 42
		if (loc == 0) {
I 27
			printf("start = %d, len = %d, fs = %s\n",
			    start, len, fs->fs_fsmnt);
E 27
			panic("alloccg: map corrupted");
E 42
I 42
D 53
		if (loc == 0)
E 53
I 53
		if (loc == 0) {
			printf("start = %d, len = %d, fs = %s\n",
			    start, len, fs->fs_fsmnt);
			panic("alloccg: map corrupted");
E 53
E 42
D 21
			return (0);
E 21
I 21
D 25
			return (NULL);
E 25
I 25
D 59
			return (-1);
E 59
I 59
			/* NOTREACHED */
E 59
I 53
		}
E 53
E 25
E 21
D 42
		}
E 42
	}
	bno = (start + len - loc) * NBBY;
	cgp->cg_frotor = bno;
	/*
	 * found the byte in the map
	 * sift through the bits to find the selected frag
	 */
D 11
	for (i = 0; i < NBBY; i += FRAG) {
		blk = (cgp->cg_free[bno / NBBY] >> i) & (0xff >> NBBY - FRAG);
E 11
I 11
D 21
	for (i = 0; i < NBBY; i += fs->fs_frag) {
		blk = (cgp->cg_free[bno / NBBY] >> i) &
		      (0xff >> NBBY - fs->fs_frag);
E 21
I 21
	for (i = bno + NBBY; bno < i; bno += fs->fs_frag) {
D 75
		blk = blkmap(fs, cgp->cg_free, bno);
E 75
I 75
		blk = blkmap(fs, cg_blksfree(cgp), bno);
E 75
E 21
E 11
		blk <<= 1;
		field = around[allocsiz];
		subfield = inside[allocsiz];
D 11
		for (pos = 0; pos <= FRAG - allocsiz; pos++) {
E 11
I 11
		for (pos = 0; pos <= fs->fs_frag - allocsiz; pos++) {
E 11
D 21
			if ((blk & field) == subfield) {
				return (bno + i + pos);
			}
E 21
I 21
			if ((blk & field) == subfield)
				return (bno + pos);
E 21
			field <<= 1;
			subfield <<= 1;
		}
	}
I 27
	printf("bno = %d, fs = %s\n", bno, fs->fs_fsmnt);
E 27
	panic("alloccg: block not in map");
D 21
	return (0);
E 21
I 21
D 25
	return (NULL);
E 25
I 25
	return (-1);
E 25
E 21
}

/*
I 85
D 89
 * Check that a specified block number is in range.
 */
badblock(fs, bn)
	register struct fs *fs;
	daddr_t bn;
{

	if ((unsigned)bn >= fs->fs_size) {
		printf("bad block %d, ", bn);
		fserr(fs, "bad block");
		return (1);
	}
	return (0);
}

/*
E 89
E 85
E 7
D 14
 * update the frsum fields to reflect addition or deletion 
 * of some frags
E 14
I 14
D 35
 * Update the frsum fields to reflect addition or deletion 
 * of some frags.
E 14
 */
D 11
fragacct(fragmap, fraglist, cnt)
E 11
I 11
fragacct(fs, fragmap, fraglist, cnt)
	struct fs *fs;
E 11
D 5
	char fragmap;
E 5
I 5
	int fragmap;
E 5
D 8
	short fraglist[];
E 8
I 8
	long fraglist[];
E 8
	int cnt;
{
	int inblk;
	register int field, subfield;
	register int siz, pos;

D 5
	inblk = (int)(fragtbl[fragmap] << 1);
E 5
I 5
D 11
	inblk = (int)(fragtbl[fragmap]) << 1;
E 11
I 11
	inblk = (int)(fragtbl[fs->fs_frag][fragmap]) << 1;
E 11
E 5
	fragmap <<= 1;
D 11
	for (siz = 1; siz < FRAG; siz++) {
E 11
I 11
	for (siz = 1; siz < fs->fs_frag; siz++) {
E 11
D 20
		if (((1 << siz) & inblk) == 0)
E 20
I 20
		if ((inblk & (1 << (siz + (fs->fs_frag % NBBY)))) == 0)
E 20
			continue;
		field = around[siz];
		subfield = inside[siz];
D 11
		for (pos = siz; pos <= FRAG; pos++) {
E 11
I 11
		for (pos = siz; pos <= fs->fs_frag; pos++) {
E 11
			if ((fragmap & field) == subfield) {
				fraglist[siz] += cnt;
				pos += siz;
				field <<= siz;
				subfield <<= siz;
			}
			field <<= 1;
			subfield <<= 1;
		}
	}
E 4
}

I 14
/*
 * Check that a specified block number is in range.
 */
E 14
badblock(fs, bn)
	register struct fs *fs;
	daddr_t bn;
{

D 15
	if ((unsigned)bn >= fs->fs_size || bn < cgdmin(dtog(bn, fs), fs)) {
E 15
I 15
D 25
	if ((unsigned)bn >= fs->fs_size || bn < cgdmin(fs, dtog(fs, bn))) {
E 25
I 25
	if ((unsigned)bn >= fs->fs_size) {
I 26
		printf("bad block %d, ", bn);
E 26
E 25
E 15
		fserr(fs, "bad block");
		return (1);
	}
	return (0);
}

/*
E 35
D 14
 * getfs maps a device number into
 * a pointer to the incore super
 * block.  The algorithm is a linear
 * search through the mount table.
 * A consistency check of the
 * in core free-block and i-node
 * counts is performed.
E 14
I 14
D 41
 * Getfs maps a device number into a pointer to the incore super block.
E 14
 *
I 14
 * The algorithm is a linear search through the mount table. A
 * consistency check of the super block magic number is performed.
 *
E 14
 * panic: no fs -- the device is not mounted.
 *	this "cannot happen"
 */
struct fs *
getfs(dev)
	dev_t dev;
{
	register struct mount *mp;
	register struct fs *fs;

D 21
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
		if (mp->m_bufp != NULL && mp->m_dev == dev) {
			fs = mp->m_bufp->b_un.b_fs;
			if (fs->fs_magic != FS_MAGIC)
				panic("getfs: bad magic");
			return (fs);
		}
E 21
I 21
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++) {
		if (mp->m_bufp == NULL || mp->m_dev != dev)
			continue;
		fs = mp->m_bufp->b_un.b_fs;
D 27
		if (fs->fs_magic != FS_MAGIC)
E 27
I 27
		if (fs->fs_magic != FS_MAGIC) {
			printf("dev = 0x%x, fs = %s\n", dev, fs->fs_fsmnt);
E 27
			panic("getfs: bad magic");
I 27
		}
E 27
		return (fs);
	}
I 27
	printf("dev = 0x%x\n", dev);
E 27
E 21
	panic("getfs: no fs");
	return (NULL);
}

/*
E 41
D 14
 * Fserr prints the name of a file system
 * with an error diagnostic, in the form
E 14
I 14
 * Fserr prints the name of a file system with an error diagnostic.
 * 
 * The form of the error message is:
E 14
 *	fs: error message
 */
D 89
fserr(fs, cp)
E 89
I 89
fserr(fs, uid, cp)
E 89
	struct fs *fs;
I 89
	uid_t uid;
E 89
	char *cp;
{

D 61
	printf("%s: %s\n", fs->fs_fsmnt, cp);
E 61
I 61
D 65
	log(KERN_FAIL, "%s: %s\n", fs->fs_fsmnt, cp);
E 65
I 65
D 89
	log(LOG_ERR, "%s: %s\n", fs->fs_fsmnt, cp);
E 89
I 89
	log(LOG_ERR, "uid %d on %s: %s\n", uid, fs->fs_fsmnt, cp);
E 98
I 98
	/* Initialize the inode. */
D 108
	ip = VTOI(*vpp);
E 108
I 108
	MALLOC(ip, struct inode *, sizeof(struct inode), M_LFSNODE, M_WAITOK);
I 145
	lockinit(&ip->i_lock, PINOD, "lfsinode", 0, 0);
E 145
	(*vpp)->v_data = ip;
I 128
D 129
	(*vpp)->v_flag |= VDIROP;
E 129
E 128
E 108
D 105
	ip->i_diroff = 0;
	ip->i_devvp = ump->um_devvp;
	ip->i_dev = ump->um_dev;
E 105
I 105
	ip->i_vnode = *vpp;
I 110
	ip->i_devvp = ump->um_devvp;
E 110
E 105
D 134
	ip->i_flag = 0;
E 134
I 134
D 140
	ip->i_flag = IMOD;
E 140
I 140
D 141
	ip->i_flag = IMODIFIED;
E 141
I 141
	ip->i_flag = IN_MODIFIED;
E 141
E 140
E 134
D 105
	ip->i_lfs = ump->um_lfs;
	ip->i_lockf = 0;
E 105
D 110
	ip->i_mode = 0;
I 105
	ip->i_diroff = 0;
	ip->i_lockf = 0;
E 110
	ip->i_dev = ump->um_dev;
E 105
D 99
	ip->i_number = ino;
E 99
I 99
D 137
	ip->i_number = ip->i_din.di_inum = ino;
E 137
I 137
	ip->i_number = ip->i_din.di_inumber = ino;
I 138
D 144
ip->i_din.di_spare[0] = 0xdeadbeef;
ip->i_din.di_spare[1] = 0xdeadbeef;
E 144
E 138
E 137
E 99
D 105
	ip->i_vnode = *vpp;
E 105
I 105
	ip->i_lfs = ump->um_lfs;
D 110
	ip->i_devvp = ump->um_devvp;
E 110
E 105
#ifdef QUOTA
	for (i = 0; i < MAXQUOTAS; i++)
		ip->i_dquot[i] = NODQUOT;
#endif
I 110
	ip->i_lockf = 0;
	ip->i_diroff = 0;
	ip->i_mode = 0;
	ip->i_size = 0;
I 131
	ip->i_blocks = 0;
I 134
	++ump->um_lfs->lfs_uinodes;
E 134
E 131
E 110
I 100
D 105
	VREF(ip->i_devvp);			/* XXX: Why? */
E 105
E 100
	return (0);
I 99
}

D 100
/* 
 * Return the current version number for a specific inode.
 */
E 100
I 100
D 103
/* Return the current version number for a specific inode. */
E 100
u_long
lfs_getversion(fs, ino)
	LFS *fs;
	ino_t ino;
{
D 100
	IFILE *ifp;
E 100
	BUF *bp;
D 100
	int version;
E 100
I 100
	IFILE *ifp;
	u_long version;
E 100

D 100
printf("lfs_getversion: %d\n", ino);
E 100
I 100
	/*
D 101
	 * Read the appropriate block from the ifile.  Return the version
	 * number.
E 101
I 101
	 * Read the appropriate block from the ifile.  Return the
	 * version number.
E 101
	 */
E 100
	LFS_IENTRY(ifp, fs, ino, bp);
	version = ifp->if_version;
	brelse(bp);
D 101
	return(version);
E 101
I 101
	return (version);
E 101
E 99
E 98
E 89
E 65
E 61
}
I 100

/* Set values in the ifile for the inode. */
E 103
I 103
/* Free an inode. */
/* ARGUSED */
E 103
D 126
void
E 126
I 126
int
E 126
D 103
lfs_iset(ip, daddr, atime)
E 103
I 103
D 105
lfs_ifree(ip, notused1, notused2)
E 103
	INODE *ip;
E 105
I 105
D 125
lfs_vfree(vp, notused1, notused2)
D 109
	VNODE *vp;
E 109
I 109
	struct vnode *vp;
E 109
E 105
D 103
	daddr_t daddr;
	time_t atime;
E 103
I 103
	ino_t notused1;
	int notused2;
E 125
I 125
D 129
lfs_vfree (ap)
	struct vop_vfree_args *ap;
E 129
I 129
lfs_vfree(ap)
	struct vop_vfree_args /* {
		struct vnode *a_pvp;
		ino_t a_ino;
		int a_mode;
	} */ *ap;
E 129
D 127
#define vp (ap->a_pvp)
#define notused1 (ap->a_ino)
#define notused2 (ap->a_mode)
E 127
E 125
E 103
{
I 111
	SEGUSE *sup;
E 111
D 109
	BUF *bp;
	IFILE *ifp;
I 105
	INODE *ip;
E 109
I 109
	struct buf *bp;
	struct ifile *ifp;
	struct inode *ip;
E 109
E 105
D 104
	LFS *fs;
E 104
I 104
	struct lfs *fs;
I 111
D 143
	daddr_t old_iaddr;
E 143
I 143
	ufs_daddr_t old_iaddr;
E 143
E 111
E 104
	ino_t ino;
I 134
D 142
	int error;
E 142
E 134

I 105
D 127
	ip = VTOI(vp);
E 127
I 127
D 133
	ip = VTOI(ap->a_pvp);
E 127
E 105
D 101
printf("lfs_iset: setting ino %d daddr %lx time %lx\n", ip->i_number, daddr, atime);
E 101
I 101
D 103
printf("lfs_iset: setting ino %d daddr %lx time %lx\n",
ip->i_number, daddr, atime);
E 101

E 103
I 103
D 106
#ifdef ALLOCPRINT
	printf("lfs_ifree: free %d\n", ip->i_number);
E 106
I 106
#ifdef VERBOSE
	printf("lfs_vfree: free %d\n", ip->i_number);
E 106
#endif
E 133
	/* Get the inode number and file system. */
I 133
	ip = VTOI(ap->a_pvp);
E 133
E 103
	fs = ip->i_lfs;
	ino = ip->i_number;
I 103
D 134

E 134
I 134
D 140
	if (ip->i_flag & IMOD) {
E 140
I 140
D 141
	if (ip->i_flag & IMODIFIED) {
E 141
I 141
	if (ip->i_flag & IN_MODIFIED) {
E 141
E 140
		--fs->lfs_uinodes;
D 140
		ip->i_flag &= ~(IMOD | IACC | IUPD | ICHG);
E 140
I 140
D 141
		ip->i_flag &= ~(IMODIFIED | IACCESS | IUPDATE | ICHANGE);
E 141
I 141
		ip->i_flag &=
		    ~(IN_ACCESS | IN_CHANGE | IN_MODIFIED | IN_UPDATE);
E 141
E 140
	}
E 134
	/*
D 107
	 * Read the appropriate block from the ifile.  Set the inode entry to
	 * unused, increment its version number and link it into the free chain.
E 107
I 107
	 * Set the ifile's inode entry to unused, increment its version number
	 * and link it into the free chain.
E 107
	 */
E 103
	LFS_IENTRY(ifp, fs, ino, bp);
I 111
	old_iaddr = ifp->if_daddr;
E 111
I 103
	ifp->if_daddr = LFS_UNUSED_DADDR;
	++ifp->if_version;
	ifp->if_nextfree = fs->lfs_free;
	fs->lfs_free = ino;
E 103
D 107

D 103
	ifp->if_daddr = daddr;
	ifp->if_st_atime = atime;
E 103
	lfs_bwrite(bp);
E 107
I 107
D 109
	LFS_IWRITE(fs, bp);
E 109
I 109
D 134
	LFS_UBWRITE(bp);
E 134
I 134
	(void) VOP_BWRITE(bp);
E 134
I 111

	if (old_iaddr != LFS_UNUSED_DADDR) {
		LFS_SEGENTRY(sup, fs, datosn(fs, old_iaddr), bp);
#ifdef DIAGNOSTIC
		if (sup->su_nbytes < sizeof(struct dinode))
			panic("lfs_vfree: negative byte count (segment %d)\n",
			    datosn(fs, old_iaddr));
#endif
		sup->su_nbytes -= sizeof(struct dinode);
D 134
		LFS_UBWRITE(bp);
E 134
I 134
		(void) VOP_BWRITE(bp);
E 134
	}
E 111
E 109
E 107
I 103

	/* Set superblock modified bit and decrement file count. */
	fs->lfs_fmod = 1;
	--fs->lfs_nfiles;
I 126
	return (0);
E 126
E 103
}
I 125
D 127
#undef vp
#undef notused1
#undef notused2
E 127
I 126
D 128


E 128
E 126
E 125
D 103
#endif /* LOGFS */
E 103
E 100
D 41

/*
 * Getfsx returns the index in the file system
 * table of the specified device.  The swap device
 * is also assigned a pseudo-index.  The index may
 * be used as a compressed indication of the location
 * of a block, recording
 *	<getfsx(dev),blkno>
 * rather than
 *	<dev, blkno>
 * provided the information need remain valid only
 * as long as the file system is mounted.
 */
getfsx(dev)
	dev_t dev;
{
	register struct mount *mp;

	if (dev == swapdev)
		return (MSWAPX);
	for(mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
		if (mp->m_dev == dev)
			return (mp - &mount[0]);
	return (-1);
}

/*
 * Update is the internal name of 'sync'.  It goes through the disk
 * queues to initiate sandbagged IO; goes through the inodes to write
D 14
 * modified nodes; and it goes through the mount table to initiate modified
 * super blocks.
E 14
I 14
 * modified nodes; and it goes through the mount table to initiate
 * the writing of the modified super blocks.
E 14
 */
D 21
update()
E 21
I 21
D 36
update(flag)
	int flag;
E 36
I 36
update()
E 36
E 21
{
	register struct inode *ip;
	register struct mount *mp;
D 36
	register struct buf *bp;
E 36
	struct fs *fs;
D 22
	time_t tim;
E 22
D 7
	int i;
E 7
I 7
D 36
	int i, blks;
E 36
E 7

	if (updlock)
		return;
	updlock++;
	/*
	 * Write back modified superblocks.
	 * Consistency check that the superblock
	 * of each file system is still in the buffer cache.
	 */
D 21
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
		if (mp->m_bufp != NULL) {
			fs = mp->m_bufp->b_un.b_fs;
			if (fs->fs_fmod == 0)
				continue;
			if (fs->fs_ronly != 0)
				panic("update: rofs mod");
D 3
			bp = getblk(mp->m_dev, SBLOCK);
E 3
I 3
D 11
			bp = getblk(mp->m_dev, SBLOCK, BSIZE);
E 11
I 11
D 12
			bp = getblk(mp->m_dev, SBLOCK, MAXBSIZE);
E 12
I 12
			bp = getblk(mp->m_dev, SBLOCK, SBSIZE);
E 12
E 11
E 3
			fs->fs_fmod = 0;
			fs->fs_time = TIME;
			if (bp->b_un.b_fs != fs)
				panic("update: bad b_fs");
E 21
I 21
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++) {
		if (mp->m_bufp == NULL)
			continue;
		fs = mp->m_bufp->b_un.b_fs;
		if (fs->fs_fmod == 0)
			continue;
D 27
		if (fs->fs_ronly != 0)
E 27
I 27
D 29
		if (fs->fs_ronly != 0) {
E 29
I 29
D 36
		if (fs->fs_ronly != 0) {		/* ### */
E 36
I 36
		if (fs->fs_ronly != 0) {		/* XXX */
E 36
E 29
			printf("fs = %s\n", fs->fs_fsmnt);
E 27
			panic("update: rofs mod");
I 27
		}
E 27
D 29
		bp = getblk(mp->m_dev, SBLOCK, SBSIZE);
I 25
D 27
		if (bp->b_un.b_fs != fs || fs->fs_magic != FS_MAGIC)
E 27
I 27
		if (bp->b_un.b_fs != fs || fs->fs_magic != FS_MAGIC) {
			printf("fs = %s\n", fs->fs_fsmnt);
E 27
			panic("update: bad b_fs");
I 27
		}
E 29
E 27
E 25
		fs->fs_fmod = 0;
D 22
		fs->fs_time = TIME;
E 22
I 22
D 33
		fs->fs_time = time;
E 33
I 33
		fs->fs_time = time.tv_sec;
E 33
E 22
D 25
		if (bp->b_un.b_fs != fs)
			panic("update: bad b_fs");
E 25
D 29
		bwrite(bp);
D 25
		blks = howmany(fs->fs_cssize, fs->fs_bsize);
		for (i = 0; i < blks; i++) {
E 25
I 25
		blks = howmany(fs->fs_cssize, fs->fs_fsize);
		for (i = 0; i < blks; i += fs->fs_frag) {
E 25
			bp = getblk(mp->m_dev,
D 25
			    fsbtodb(fs, fs->fs_csaddr + (i * fs->fs_frag)),
			    fs->fs_bsize);
E 25
I 25
			    fsbtodb(fs, fs->fs_csaddr + i),
			    blks - i < fs->fs_frag ? 
				(blks - i) * fs->fs_fsize :
				fs->fs_bsize);
E 25
E 21
			bwrite(bp);
D 7
			for (i = 0; i < cssize(fs); i += BSIZE) {
D 3
				bp = getblk(mp->m_dev, csaddr(fs) + i / FSIZE);
E 3
I 3
				bp = getblk(mp->m_dev, csaddr(fs) + i / FSIZE,
E 7
I 7
D 11
			blks = howmany(cssize(fs), BSIZE);
E 11
I 11
D 21
			blks = howmany(fs->fs_cssize, fs->fs_bsize);
E 11
			for (i = 0; i < blks; i++) {
D 11
				bp = getblk(mp->m_dev, csaddr(fs) + (i * FRAG),
E 7
					BSIZE);
E 11
I 11
				bp = getblk(mp->m_dev,
				    fsbtodb(fs, fs->fs_csaddr + (i * fs->fs_frag)),
				    fs->fs_bsize);
E 11
E 3
D 7
				bcopy(fs->fs_cs + i, bp->b_un.b_addr, BSIZE);
E 7
				bwrite(bp);
			}
E 21
		}
E 29
I 29
		sbupdate(mp);
E 29
I 21
	}
E 21
	/*
	 * Write back each (modified) inode.
	 */
D 21
	for (ip = inode; ip < inodeNINODE; ip++)
		if((ip->i_flag&ILOCK)==0 && ip->i_count) {
			ip->i_flag |= ILOCK;
			ip->i_count++;
			tim = TIME;
			iupdat(ip, &tim, &tim, 0);
			iput(ip);
		}
E 21
I 21
	for (ip = inode; ip < inodeNINODE; ip++) {
D 34
		if ((ip->i_flag & ILOCK) != 0 || ip->i_count == 0)
E 34
I 34
		if ((ip->i_flag & ILOCKED) != 0 || ip->i_count == 0)
E 34
			continue;
D 34
		ip->i_flag |= ILOCK;
E 34
I 34
		ip->i_flag |= ILOCKED;
E 34
		ip->i_count++;
D 22
		tim = TIME;
		iupdat(ip, &tim, &tim, 0);
E 22
I 22
D 33
		iupdat(ip, &time, &time, 0);
E 33
I 33
D 38
		iupdat(ip, &time.tv_sec, &time.tv_sec, 0);
E 38
I 38
D 39
		iupdat(ip, time, time, 0);
E 39
I 39
		iupdat(ip, &time, &time, 0);
E 39
E 38
E 33
E 22
		iput(ip);
	}
E 21
	updlock = 0;
	/*
	 * Force stale buffer cache information to be flushed,
	 * for all devices.
	 */
	bflush(NODEV);
I 11
}

E 41
D 35
/*
D 14
 * block macros
E 14
I 14
 * block operations
 *
 * check if a block is available
E 14
 */
D 14

E 14
isblock(fs, cp, h)
	struct fs *fs;
	unsigned char *cp;
	int h;
{
	unsigned char mask;

	switch (fs->fs_frag) {
	case 8:
		return (cp[h] == 0xff);
	case 4:
		mask = 0x0f << ((h & 0x1) << 2);
		return ((cp[h >> 1] & mask) == mask);
	case 2:
		mask = 0x03 << ((h & 0x3) << 1);
		return ((cp[h >> 2] & mask) == mask);
	case 1:
		mask = 0x01 << (h & 0x7);
		return ((cp[h >> 3] & mask) == mask);
	default:
D 21
		panic("isblock bad fs_frag");
		return;
E 21
I 21
		panic("isblock");
		return (NULL);
E 21
	}
}
I 14

/*
 * take a block out of the map
 */
E 14
clrblock(fs, cp, h)
	struct fs *fs;
	unsigned char *cp;
	int h;
{
	switch ((fs)->fs_frag) {
	case 8:
		cp[h] = 0;
		return;
	case 4:
		cp[h >> 1] &= ~(0x0f << ((h & 0x1) << 2));
		return;
	case 2:
		cp[h >> 2] &= ~(0x03 << ((h & 0x3) << 1));
		return;
	case 1:
		cp[h >> 3] &= ~(0x01 << (h & 0x7));
		return;
	default:
D 21
		panic("clrblock bad fs_frag");
E 21
I 21
		panic("clrblock");
E 21
		return;
	}
}
I 14

/*
 * put a block into the map
 */
E 14
setblock(fs, cp, h)
	struct fs *fs;
	unsigned char *cp;
	int h;
{
	switch (fs->fs_frag) {
	case 8:
		cp[h] = 0xff;
		return;
	case 4:
		cp[h >> 1] |= (0x0f << ((h & 0x1) << 2));
		return;
	case 2:
		cp[h >> 2] |= (0x03 << ((h & 0x3) << 1));
		return;
	case 1:
		cp[h >> 3] |= (0x01 << (h & 0x7));
		return;
	default:
D 21
		panic("setblock bad fs_frag");
E 21
I 21
		panic("setblock");
E 21
		return;
	}
E 11
}
E 35
E 1
