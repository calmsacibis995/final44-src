h28200
s 00068/00001/01502
d D 8.18 95/05/26 11:02:49 mckusick 142 141
c yet more cluster checks
e
s 00007/00007/01496
d D 8.17 95/05/03 17:31:34 mckusick 141 140
c give up on rotational layout if there is only one rotational position
e
s 00003/00007/01500
d D 8.16 95/03/30 14:14:28 mckusick 140 139
c doasyncfree and prtrealloc move FFS sysctl variables
e
s 00040/00038/01467
d D 8.15 95/03/21 00:53:24 mckusick 139 138
c daddr_t => ufs_daddr_t
e
s 00009/00006/01496
d D 8.14 95/02/15 12:04:58 mckusick 138 137
c more debugging for clustering
e
s 00008/00008/01494
d D 8.13 95/01/02 23:38:53 mckusick 137 136
c convert quad => int64_t (from mycroft)
e
s 00005/00003/01497
d D 8.12 95/01/02 23:03:26 mckusick 136 135
c more consistent with DEBUG (from mycroft)
e
s 00025/00000/01475
d D 8.11 94/10/27 23:42:54 mckusick 135 134
c add more debugging code for ffs_reallocblks
e
s 00030/00006/01445
d D 8.10 94/10/27 20:42:38 mckusick 134 133
c use and maintain fs_maxcluster array
e
s 00003/00000/01448
d D 8.9 94/06/15 16:25:51 mkm 133 132
c debugging sysctl needs to be ifdef DEBUG (from mycroft)
e
s 00023/00011/01425
d D 8.8 94/02/21 03:26:30 mckusick 132 131
c conditionally avoid synchronous writes (and indicate real fix)
e
s 00005/00001/01431
d D 8.7 94/02/14 09:14:22 mckusick 131 130
c If the offset within the indirect block of the "end block" of our
c current cluster is greater than the length of the cluster, then we know
c that the start block of the cluster must also be in that indirect block
c (since the cluster is contiguous) hence the entire cluster is mapped by
c a single indirect block (or completely in the direct blocks if end_lvl == 0).
c From: mike@cs.utah.edu (Mike Hibler)
e
s 00333/00009/01099
d D 8.6 94/02/05 01:53:43 mckusick 130 129
c first cut at improving cluster allocation
e
s 00001/00001/01107
d D 8.5 94/01/13 09:14:03 bostic 129 128
c lint
e
s 00002/00003/01106
d D 8.4 94/01/04 22:12:18 bostic 128 127
c lint
e
s 00015/00014/01094
d D 8.3 93/09/23 16:12:29 bostic 127 126
c changes for 4.4BSD-Lite requested by USL
e
s 00017/00017/01091
d D 8.2 93/09/21 07:17:34 bostic 126 125
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/01106
d D 8.1 93/06/11 16:21:06 bostic 125 124
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00003/01102
d D 7.40 92/12/04 17:20:11 mckusick 124 123
c take next available block on drives of unknown geometry
e
s 00002/00003/01103
d D 7.39 92/11/02 15:58:43 margo 123 122
c Detect contiguous allocation at the beginning of files and 
c indirect blocks so that you can allocate "maxcontig" blocks before paying 
c a rot-delay.
e
s 00032/00022/01074
d D 7.38 92/07/03 01:46:30 mckusick 122 121
c delete USES; add parameter declarations; streamline unmarshalling
e
s 00004/00003/01092
d D 7.37 92/06/04 09:50:02 heideman 121 120
c registerized vnodeop ops after vnode interface conversion
e
s 00022/00036/01073
d D 7.36 92/05/15 13:52:26 heideman 120 119
c vnodeop argument macro expansion
e
s 00004/00003/01105
d D 7.35 92/05/15 12:22:16 heideman 119 118
c ffs_vfree now returns a (0) error
e
s 00022/00011/01086
d D 7.34 92/05/14 17:26:03 heideman 118 103
c vnode interface conversion
e
s 00022/00011/01086
d R 7.34 92/05/14 17:00:26 heideman 117 103
c vnode interface conversion
e
s 00022/00011/01086
d R 7.34 92/05/14 16:42:35 heideman 116 103
c vnode interface conversion
e
s 00022/00011/01086
d R 7.34 92/05/14 16:32:27 heideman 115 103
c vnode interface conversion
e
s 00022/00011/01086
d R 7.34 92/05/14 15:50:30 heideman 114 103
c vnode interface conversion
e
s 00022/00011/01086
d R 7.34 92/05/14 15:38:35 heideman 113 103
c vnode interface conversion
e
s 00022/00011/01086
d R 7.34 92/05/14 14:44:42 heideman 112 103
c vnode interface conversion
e
s 00022/00011/01086
d R 7.34 92/05/14 12:47:32 heideman 111 103
c vnode interface conversion
e
s 00022/00011/01086
d R 7.34 92/05/14 11:44:36 heideman 110 103
c vnode interface conversion
e
s 00022/00011/01086
d R 7.34 92/05/14 10:25:26 heideman 109 103
c vnode interface conversion
e
s 00032/00011/01086
d R 7.34 92/05/13 23:03:21 heideman 108 103
c vnode interface conversion
e
s 00032/00011/01086
d R 7.34 92/05/13 18:51:17 heideman 107 103
c vnode interface conversion
e
s 00032/00011/01086
d R 7.34 92/05/13 18:23:10 heideman 106 103
c vnode interface conversion
e
s 00032/00011/01086
d R 7.34 92/05/13 18:12:33 heideman 105 103
c vnode interface conversion
e
s 00032/00011/01086
d R 7.34 92/05/13 17:57:08 heideman 104 103
c vnode interface conversion
e
s 00002/00000/01095
d D 7.33 92/05/04 16:14:47 mckusick 103 102
c lint
e
s 00013/00006/01082
d D 7.32 92/04/21 14:44:00 mckusick 102 101
c have to pass down cred to block allocation routines
e
s 00004/00004/01084
d D 7.31 92/03/26 18:39:01 mckusick 101 100
c ensure proper types for local variables and parameters
e
s 00001/00001/01087
d D 7.30 91/11/20 18:12:02 marc 100 99
c declared static but wasn't
e
s 00015/00011/01073
d D 7.29 91/11/05 14:29:02 mckusick 99 98
c reorganization to move ufsmount ops to be vnode ops
e
s 00111/00102/00973
d D 7.28 91/11/01 16:56:28 bostic 98 97
c UFS/FFS split for LFS version 1; move inode pref into ffs_ialloc
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
D 125
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 79
E 69
D 76
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 76
I 76
 * All rights reserved.
E 125
I 125
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 125
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
D 98
#include "param.h"
#include "systm.h"
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
#include "proc.h"
E 94
D 79
#include "quota.h"
E 79
I 79
#include "vnode.h"
E 79
#include "kernel.h"
I 61
#include "syslog.h"
E 98
I 98
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/vnode.h>
I 122
#include <sys/mount.h>
E 122
#include <sys/kernel.h>
#include <sys/syslog.h>
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

I 103
#include <vm/vm.h>

E 103
I 94
D 98
#include "quota.h"
#include "inode.h"
#include "fs.h"
E 98
I 98
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
E 98

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
E 98
I 98
#include <ufs/ffs/fs.h>
#include <ufs/ffs/ffs_extern.h>
E 98
E 11
E 6

I 98
extern u_long nextgennumber;

D 139
static daddr_t	ffs_alloccg __P((struct inode *, int, daddr_t, int));
static daddr_t	ffs_alloccgblk __P((struct fs *, struct cg *, daddr_t));
I 130
static daddr_t	ffs_clusteralloc __P((struct inode *, int, daddr_t, int));
E 139
I 139
static ufs_daddr_t ffs_alloccg __P((struct inode *, int, ufs_daddr_t, int));
static ufs_daddr_t ffs_alloccgblk __P((struct fs *, struct cg *, ufs_daddr_t));
static ufs_daddr_t ffs_clusteralloc __P((struct inode *, int, ufs_daddr_t,
	    int));
E 139
E 130
static ino_t	ffs_dirpref __P((struct fs *));
D 139
static daddr_t	ffs_fragextend __P((struct inode *, int, long, int, int));
E 139
I 139
static ufs_daddr_t ffs_fragextend __P((struct inode *, int, long, int, int));
E 139
static void	ffs_fserr __P((struct fs *, u_int, char *));
static u_long	ffs_hashalloc
D 137
		    __P((struct inode *, int, long, int, u_long (*)()));
D 127
static ino_t	ffs_ialloccg __P((struct inode *, int, daddr_t, int));
E 127
I 127
D 134
static ino_t	ffs_nodealloccg __P((struct inode *, int, daddr_t, int));
E 134
I 134
static u_long	ffs_nodealloccg __P((struct inode *, int, daddr_t, int));
E 137
I 137
		    __P((struct inode *, int, long, int, u_int32_t (*)()));
D 139
static ino_t	ffs_nodealloccg __P((struct inode *, int, daddr_t, int));
E 137
E 134
E 127
static daddr_t	ffs_mapsearch __P((struct fs *, struct cg *, daddr_t, int));
E 139
I 139
static ino_t	ffs_nodealloccg __P((struct inode *, int, ufs_daddr_t, int));
static ufs_daddr_t ffs_mapsearch __P((struct fs *, struct cg *, ufs_daddr_t,
	    int));
E 139

E 98
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
D 98
alloc(ip, lbn, bpref, size, bnp)
E 98
I 98
D 102
ffs_alloc(ip, lbn, bpref, size, bnp)
E 102
I 102
ffs_alloc(ip, lbn, bpref, size, cred, bnp)
E 102
E 98
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
D 139
	daddr_t lbn, bpref;
E 139
I 139
	ufs_daddr_t lbn, bpref;
E 139
E 83
	int size;
I 102
	struct ucred *cred;
E 102
I 79
D 83
	struct buf **bpp;
	int flags;
E 83
I 83
D 139
	daddr_t *bnp;
E 139
I 139
	ufs_daddr_t *bnp;
E 139
E 83
E 79
{
D 128
	daddr_t bno;
E 128
	register struct fs *fs;
D 4
	struct buf *bp;
E 4
I 4
D 128
	register struct buf *bp;
E 128
I 128
D 139
	daddr_t bno;
E 139
I 139
	ufs_daddr_t bno;
E 139
E 128
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
D 102
	struct ucred *cred = curproc->p_ucred;		/* XXX */
E 102
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
I 102
#ifdef DIAGNOSTIC
E 102
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
D 126
	if ((unsigned)size > fs->fs_bsize || fragoff(fs, size) != 0) {
E 126
I 126
	if ((u_int)size > fs->fs_bsize || fragoff(fs, size) != 0) {
E 126
		printf("dev = 0x%x, bsize = %d, size = %d, fs = %s\n",
		    ip->i_dev, fs->fs_bsize, size, fs->fs_fsmnt);
E 27
E 18
D 98
		panic("alloc: bad size");
E 98
I 98
		panic("ffs_alloc: bad size");
E 98
I 27
	}
I 102
	if (cred == NOCRED)
		panic("ffs_alloc: missing credential\n");
#endif /* DIAGNOSTIC */
E 102
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
D 127
		cg = itog(fs, ip->i_number);
E 127
I 127
		cg = ino_to_cg(fs, ip->i_number);
E 127
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
D 98
	bno = (daddr_t)hashalloc(ip, cg, (long)bpref, size,
		(u_long (*)())alloccg);
E 98
I 98
D 139
	bno = (daddr_t)ffs_hashalloc(ip, cg, (long)bpref, size,
E 139
I 139
	bno = (ufs_daddr_t)ffs_hashalloc(ip, cg, (long)bpref, size,
E 139
D 137
	    (u_long (*)())ffs_alloccg);
E 137
I 137
	    (u_int32_t (*)())ffs_alloccg);
E 137
E 98
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
D 126
		ip->i_flag |= IUPD|ICHG;
E 126
I 126
D 127
		ip->i_flag |= IUPDATE | ICHANGE;
E 127
I 127
		ip->i_flag |= IN_CHANGE | IN_UPDATE;
E 127
E 126
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
D 98
	fserr(fs, cred->cr_uid, "file system full");
E 98
I 98
	ffs_fserr(fs, cred->cr_uid, "file system full");
E 98
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

I 14
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
D 98
realloccg(ip, lbprev, bpref, osize, nsize, bpp)
E 98
I 98
D 102
ffs_realloccg(ip, lbprev, bpref, osize, nsize, bpp)
E 102
I 102
ffs_realloccg(ip, lbprev, bpref, osize, nsize, cred, bpp)
E 102
E 98
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
D 101
	off_t lbprev;
E 101
I 101
D 139
	daddr_t lbprev;
E 101
	daddr_t bpref;
E 139
I 139
	ufs_daddr_t lbprev;
	ufs_daddr_t bpref;
E 139
E 83
E 7
E 4
	int osize, nsize;
I 102
	struct ucred *cred;
E 102
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
D 128
	struct buf *bp, *obp;
E 128
I 128
	struct buf *bp;
E 128
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
D 139
	daddr_t bprev, bno;
E 139
I 139
	ufs_daddr_t bprev, bno;
E 139
E 93
I 87
D 94
	struct ucred *cred = u.u_cred;		/* XXX */
E 94
I 94
D 102
	struct ucred *cred = curproc->p_ucred;		/* XXX */
E 102
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
I 102
#ifdef DIAGNOSTIC
E 102
E 19
I 11
D 18
	if ((unsigned)osize > fs->fs_bsize || osize % fs->fs_fsize != 0 ||
	    (unsigned)nsize > fs->fs_bsize || nsize % fs->fs_fsize != 0)
E 18
I 18
D 126
	if ((unsigned)osize > fs->fs_bsize || fragoff(fs, osize) != 0 ||
D 27
	    (unsigned)nsize > fs->fs_bsize || fragoff(fs, nsize) != 0)
E 27
I 27
	    (unsigned)nsize > fs->fs_bsize || fragoff(fs, nsize) != 0) {
E 126
I 126
	if ((u_int)osize > fs->fs_bsize || fragoff(fs, osize) != 0 ||
	    (u_int)nsize > fs->fs_bsize || fragoff(fs, nsize) != 0) {
E 126
D 98
		printf("dev = 0x%x, bsize = %d, osize = %d, nsize = %d, fs = %s\n",
E 98
I 98
		printf(
		    "dev = 0x%x, bsize = %d, osize = %d, nsize = %d, fs = %s\n",
E 98
		    ip->i_dev, fs->fs_bsize, osize, nsize, fs->fs_fsmnt);
E 27
E 18
D 98
		panic("realloccg: bad size");
E 98
I 98
		panic("ffs_realloccg: bad size");
E 98
I 27
	}
I 102
	if (cred == NOCRED)
		panic("ffs_realloccg: missing credential\n");
#endif /* DIAGNOSTIC */
E 102
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
D 98
		panic("realloccg: bad bprev");
E 98
I 98
		panic("ffs_realloccg: bad bprev");
E 98
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
D 98
	if (bno = fragextend(ip, cg, (long)bprev, osize, nsize)) {
E 98
I 98
	if (bno = ffs_fragextend(ip, cg, (long)bprev, osize, nsize)) {
E 98
D 86
		if (bp->b_blkno != bno)
E 86
I 86
		if (bp->b_blkno != fsbtodb(fs, bno))
E 86
			panic("bad blockno");
I 84
		ip->i_blocks += btodb(nsize - osize);
D 126
		ip->i_flag |= IUPD|ICHG;
E 126
I 126
D 127
		ip->i_flag |= IUPDATE | ICHANGE;
E 127
I 127
		ip->i_flag |= IN_CHANGE | IN_UPDATE;
E 127
E 126
I 96
		allocbuf(bp, nsize);
		bp->b_flags |= B_DONE;
D 126
		bzero(bp->b_un.b_addr + osize, (unsigned)nsize - osize);
E 126
I 126
		bzero((char *)bp->b_data + osize, (u_int)nsize - osize);
E 126
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
D 98
		 * At this point we have discovered a file that is trying
		 * to grow a small fragment to a larger fragment. To save
		 * time, we allocate a full sized block, then free the 
		 * unused portion. If the file continues to grow, the 
		 * `fragextend' call above will be able to grow it in place
		 * without further copying. If aberrant programs cause
		 * disk fragmentation to grow within 2% of the free reserve,
		 * we choose to begin optimizing for space.
E 98
I 98
		 * At this point we have discovered a file that is trying to
		 * grow a small fragment to a larger fragment. To save time,
		 * we allocate a full sized block, then free the unused portion.
		 * If the file continues to grow, the `ffs_fragextend' call
		 * above will be able to grow it in place without further
		 * copying. If aberrant programs cause disk fragmentation to
		 * grow within 2% of the free reserve, we choose to begin
		 * optimizing for space.
E 98
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
D 98
		panic("realloccg: bad optim");
E 98
I 98
		panic("ffs_realloccg: bad optim");
E 98
		/* NOTREACHED */
	}
E 66
D 98
	bno = (daddr_t)hashalloc(ip, cg, (long)bpref, request,
E 64
E 60
		(u_long (*)())alloccg);
E 98
I 98
D 139
	bno = (daddr_t)ffs_hashalloc(ip, cg, (long)bpref, request,
E 139
I 139
	bno = (ufs_daddr_t)ffs_hashalloc(ip, cg, (long)bpref, request,
E 139
D 137
	    (u_long (*)())ffs_alloccg);
E 137
I 137
	    (u_int32_t (*)())ffs_alloccg);
E 137
E 98
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
D 98
		blkfree(ip, bprev, (off_t)osize);
E 98
I 98
D 101
		ffs_blkfree(ip, bprev, (off_t)osize);
E 101
I 101
		ffs_blkfree(ip, bprev, (long)osize);
E 101
E 98
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
D 98
			blkfree(ip, bno + numfrags(fs, nsize),
E 72
D 64
				(off_t)(fs->fs_bsize - nsize));
E 64
I 64
				(off_t)(request - nsize));
E 98
I 98
			ffs_blkfree(ip, bno + numfrags(fs, nsize),
D 101
			    (off_t)(request - nsize));
E 101
I 101
			    (long)(request - nsize));
E 101
E 98
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
D 126
		ip->i_flag |= IUPD|ICHG;
E 126
I 126
D 127
		ip->i_flag |= IUPDATE | ICHANGE;
E 127
I 127
		ip->i_flag |= IN_CHANGE | IN_UPDATE;
E 127
E 126
I 96
		allocbuf(bp, nsize);
		bp->b_flags |= B_DONE;
D 126
		bzero(bp->b_un.b_addr + osize, (unsigned)nsize - osize);
E 126
I 126
		bzero((char *)bp->b_data + osize, (u_int)nsize - osize);
E 126
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
E 92
I 83
	brelse(bp);
E 83
I 8
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
D 98
	fserr(fs, cred->cr_uid, "file system full");
E 98
I 98
	ffs_fserr(fs, cred->cr_uid, "file system full");
E 98
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

I 14
/*
I 130
 * Reallocate a sequence of blocks into a contiguous sequence of blocks.
 *
 * The vnode and an array of buffer pointers for a range of sequential
 * logical blocks to be made contiguous is given. The allocator attempts
 * to find a range of sequential blocks starting as close as possible to
 * an fs_rotdelay offset from the end of the allocation for the logical
 * block immediately preceeding the current range. If successful, the
 * physical block numbers in the buffer pointers and in the inode are
 * changed to reflect the new allocation. If unsuccessful, the allocation
 * is left unchanged. The success in doing the reallocation is returned.
 * Note that the error return is not reflected back to the user. Rather
 * the previous block allocation will be used.
 */
I 136
D 140
#ifdef DEBUG
E 136
I 132
#include <sys/sysctl.h>
E 140
int doasyncfree = 1;
I 133
D 136
#ifdef DEBUG
E 136
E 133
D 140
struct ctldebug debug14 = { "doasyncfree", &doasyncfree };
E 140
I 140
int doreallocblks = 1;
E 140
I 135
int prtrealloc = 0;
D 140
struct ctldebug debug15 = { "prtrealloc", &prtrealloc };
I 136
#else
#define doasyncfree	1
E 136
E 135
I 133
#endif
E 140

E 133
E 132
int
ffs_reallocblks(ap)
	struct vop_reallocblks_args /* {
		struct vnode *a_vp;
		struct cluster_save *a_buflist;
	} */ *ap;
{
	struct fs *fs;
	struct inode *ip;
	struct vnode *vp;
	struct buf *sbp, *ebp;
D 139
	daddr_t *bap, *sbap, *ebap;
E 139
I 139
	ufs_daddr_t *bap, *sbap, *ebap;
E 139
	struct cluster_save *buflist;
D 139
	daddr_t start_lbn, end_lbn, soff, eoff, newblk, blkno;
E 139
I 139
	ufs_daddr_t start_lbn, end_lbn, soff, eoff, newblk, blkno;
E 139
	struct indir start_ap[NIADDR + 1], end_ap[NIADDR + 1], *idp;
	int i, len, start_lvl, end_lvl, pref, ssize;

I 140
	if (doreallocblks == 0)
		return (ENOSPC);
E 140
	vp = ap->a_vp;
	ip = VTOI(vp);
	fs = ip->i_fs;
	if (fs->fs_contigsumsize <= 0)
		return (ENOSPC);
	buflist = ap->a_buflist;
	len = buflist->bs_nchildren;
	start_lbn = buflist->bs_children[0]->b_lblkno;
	end_lbn = start_lbn + len - 1;
#ifdef DIAGNOSTIC
I 142
	for (i = 0; i < len; i++)
		if (!ffs_checkblk(ip,
		   dbtofsb(fs, buflist->bs_children[i]->b_blkno), fs->fs_bsize))
			panic("ffs_reallocblks: unallocated block 1");
E 142
	for (i = 1; i < len; i++)
		if (buflist->bs_children[i]->b_lblkno != start_lbn + i)
D 142
			panic("ffs_reallocblks: non-cluster");
E 142
I 142
			panic("ffs_reallocblks: non-logical cluster");
	blkno = buflist->bs_children[0]->b_blkno;
	ssize = fsbtodb(fs, fs->fs_frag);
	for (i = 1; i < len - 1; i++)
		if (buflist->bs_children[i]->b_blkno != blkno + (i * ssize))
			panic("ffs_reallocblks: non-physical cluster %d", i);
E 142
#endif
	/*
	 * If the latest allocation is in a new cylinder group, assume that
	 * the filesystem has decided to move and do not force it back to
	 * the previous cylinder group.
	 */
	if (dtog(fs, dbtofsb(fs, buflist->bs_children[0]->b_blkno)) !=
	    dtog(fs, dbtofsb(fs, buflist->bs_children[len - 1]->b_blkno)))
		return (ENOSPC);
	if (ufs_getlbns(vp, start_lbn, start_ap, &start_lvl) ||
	    ufs_getlbns(vp, end_lbn, end_ap, &end_lvl))
		return (ENOSPC);
	/*
	 * Get the starting offset and block map for the first block.
	 */
	if (start_lvl == 0) {
		sbap = &ip->i_db[0];
		soff = start_lbn;
	} else {
		idp = &start_ap[start_lvl - 1];
		if (bread(vp, idp->in_lbn, (int)fs->fs_bsize, NOCRED, &sbp)) {
			brelse(sbp);
			return (ENOSPC);
		}
D 139
		sbap = (daddr_t *)sbp->b_data;
E 139
I 139
		sbap = (ufs_daddr_t *)sbp->b_data;
E 139
		soff = idp->in_off;
	}
	/*
	 * Find the preferred location for the cluster.
	 */
	pref = ffs_blkpref(ip, start_lbn, soff, sbap);
	/*
	 * If the block range spans two block maps, get the second map.
	 */
D 131
	if (end_lvl == 0 || (idp = &end_ap[end_lvl - 1])->in_off >= len) {
E 131
I 131
	if (end_lvl == 0 || (idp = &end_ap[end_lvl - 1])->in_off + 1 >= len) {
E 131
		ssize = len;
	} else {
I 131
#ifdef DIAGNOSTIC
		if (start_ap[start_lvl-1].in_lbn == idp->in_lbn)
			panic("ffs_reallocblk: start == end");
#endif
E 131
		ssize = len - (idp->in_off + 1);
		if (bread(vp, idp->in_lbn, (int)fs->fs_bsize, NOCRED, &ebp))
			goto fail;
D 139
		ebap = (daddr_t *)ebp->b_data;
E 139
I 139
		ebap = (ufs_daddr_t *)ebp->b_data;
E 139
	}
	/*
	 * Search the block map looking for an allocation of the desired size.
	 */
D 139
	if ((newblk = (daddr_t)ffs_hashalloc(ip, dtog(fs, pref), (long)pref,
E 139
I 139
	if ((newblk = (ufs_daddr_t)ffs_hashalloc(ip, dtog(fs, pref), (long)pref,
E 139
D 137
	    len, (u_long (*)())ffs_clusteralloc)) == 0)
E 137
I 137
	    len, (u_int32_t (*)())ffs_clusteralloc)) == 0)
E 137
		goto fail;
	/*
	 * We have found a new contiguous block.
	 *
	 * First we have to replace the old block pointers with the new
	 * block pointers in the inode and indirect blocks associated
	 * with the file.
	 */
I 135
#ifdef DEBUG
	if (prtrealloc)
		printf("realloc: ino %d, lbns %d-%d\n\told:", ip->i_number,
D 136
			start_lbn, end_lbn);
#endif DEBUG
E 136
I 136
		    start_lbn, end_lbn);
#endif
E 136
E 135
	blkno = newblk;
	for (bap = &sbap[soff], i = 0; i < len; i++, blkno += fs->fs_frag) {
		if (i == ssize)
			bap = ebap;
#ifdef DIAGNOSTIC
I 142
		if (!ffs_checkblk(ip,
		   dbtofsb(fs, buflist->bs_children[i]->b_blkno), fs->fs_bsize))
			panic("ffs_reallocblks: unallocated block 2");
E 142
D 134
		if (buflist->bs_children[i]->b_blkno != fsbtodb(fs, *bap))
E 134
I 134
		if (dbtofsb(fs, buflist->bs_children[i]->b_blkno) != *bap)
E 134
			panic("ffs_reallocblks: alloc mismatch");
#endif
I 135
#ifdef DEBUG
		if (prtrealloc)
			printf(" %d,", *bap);
#endif
E 135
		*bap++ = blkno;
	}
	/*
	 * Next we must write out the modified inode and indirect blocks.
D 132
	 * The writes are synchronous since the old block values may have
	 * been written to disk.
E 132
I 132
	 * For strict correctness, the writes should be synchronous since
	 * the old block values may have been written to disk. In practise
	 * they are almost never written, but if we are concerned about 
	 * strict correctness, the `doasyncfree' flag should be set to zero.
E 132
	 *
D 132
	 * These writes should be changed to be bdwrites (and the VOP_UPDATE
	 * dropped) when a flag has been added to the buffers and inodes
	 * to detect when they have been written. It should be set when the
	 * cluster is started and cleared whenever the buffer or inode is
	 * flushed. We can then check below to see if it is set, and do
	 * the synchronous write only when it has been cleared.
E 132
I 132
	 * The test on `doasyncfree' should be changed to test a flag
	 * that shows whether the associated buffers and inodes have
	 * been written. The flag should be set when the cluster is
	 * started and cleared whenever the buffer or inode is flushed.
	 * We can then check below to see if it is set, and do the
	 * synchronous write only when it has been cleared.
E 132
	 */
	if (sbap != &ip->i_db[0]) {
D 132
		bwrite(sbp);
E 132
I 132
		if (doasyncfree)
			bdwrite(sbp);
		else
			bwrite(sbp);
E 132
	} else {
		ip->i_flag |= IN_CHANGE | IN_UPDATE;
D 132
		VOP_UPDATE(vp, &time, &time, MNT_WAIT);
E 132
I 132
		if (!doasyncfree)
			VOP_UPDATE(vp, &time, &time, MNT_WAIT);
E 132
	}
	if (ssize < len)
D 132
		bwrite(ebp);
E 132
I 132
		if (doasyncfree)
			bdwrite(ebp);
		else
			bwrite(ebp);
E 132
	/*
	 * Last, free the old blocks and assign the new blocks to the buffers.
	 */
I 135
#ifdef DEBUG
	if (prtrealloc)
		printf("\n\tnew:");
#endif
E 135
	for (blkno = newblk, i = 0; i < len; i++, blkno += fs->fs_frag) {
		ffs_blkfree(ip, dbtofsb(fs, buflist->bs_children[i]->b_blkno),
		    fs->fs_bsize);
		buflist->bs_children[i]->b_blkno = fsbtodb(fs, blkno);
I 135
#ifdef DEBUG
I 142
		if (!ffs_checkblk(ip,
		   dbtofsb(fs, buflist->bs_children[i]->b_blkno), fs->fs_bsize))
			panic("ffs_reallocblks: unallocated block 3");
E 142
		if (prtrealloc)
			printf(" %d,", blkno);
#endif
E 135
	}
I 135
#ifdef DEBUG
	if (prtrealloc) {
		prtrealloc--;
		printf("\n");
	}
#endif
E 135
	return (0);

fail:
	if (ssize < len)
		brelse(ebp);
	if (sbap != &ip->i_db[0])
		brelse(sbp);
	return (ENOSPC);
}

/*
E 130
 * Allocate an inode in the file system.
 * 
D 98
 * A preference may be optionally specified. If a preference is given
 * the following hierarchy is used to allocate an inode:
 *   1) allocate the requested inode.
E 98
I 98
 * If allocating a directory, use ffs_dirpref to select the inode.
 * If allocating in a directory, the following hierarchy is followed:
 *   1) allocate the preferred inode.
E 98
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
D 98
ialloc(pip, ipref, mode, cred, ipp)
E 98
I 98
D 99
ffs_ialloc(pip, mode, cred, ipp)
E 98
E 87
E 79
	register struct inode *pip;
E 99
I 99
D 118
ffs_valloc(pvp, mode, cred, vpp)
	register struct vnode *pvp;
E 99
E 19
D 98
	ino_t ipref;
E 98
	int mode;
I 87
	struct ucred *cred;
E 87
I 79
D 99
	struct inode **ipp;
E 99
I 99
	struct vnode **vpp;
E 118
I 118
D 122
ffs_valloc (ap)
	struct vop_valloc_args *ap;
E 122
I 122
ffs_valloc(ap)
	struct vop_valloc_args /* {
		struct vnode *a_pvp;
		int a_mode;
		struct ucred *a_cred;
		struct vnode **a_vpp;
	} */ *ap;
E 122
D 120
#define pvp (ap->a_pvp)
#define mode (ap->a_mode)
#define cred (ap->a_cred)
#define vpp (ap->a_vpp)
E 120
E 118
E 99
E 79
{
I 118
D 122
	USES_VOP_VFREE;
	USES_VOP_VGET;
E 122
I 121
	register struct vnode *pvp = ap->a_pvp;
E 121
E 118
I 99
	register struct inode *pip;
E 99
D 10
	daddr_t ino;
E 10
I 10
D 98
	ino_t ino;
E 98
E 10
	register struct fs *fs;
	register struct inode *ip;
I 122
	mode_t mode = ap->a_mode;
E 122
I 98
	ino_t ino, ipref;
E 98
D 79
	int cg;
E 79
I 79
	int cg, error;
E 79
	
I 79
D 98
	*ipp = 0;
E 98
I 98
D 99
	*ipp = NULL;
E 99
I 99
D 120
	*vpp = NULL;
	pip = VTOI(pvp);
E 120
I 120
	*ap->a_vpp = NULL;
D 121
	pip = VTOI(ap->a_pvp);
E 121
I 121
	pip = VTOI(pvp);
E 121
E 120
E 99
E 98
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
I 98

D 120
	if ((mode & IFMT) == IFDIR)
E 120
I 120
D 122
	if ((ap->a_mode & IFMT) == IFDIR)
E 122
I 122
	if ((mode & IFMT) == IFDIR)
E 122
E 120
D 99
		ipref = ffs_dirpref(pip->i_fs);
E 99
I 99
		ipref = ffs_dirpref(fs);
E 99
	else
		ipref = pip->i_number;
E 98
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
D 127
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
D 98
	ino = (ino_t)hashalloc(pip, cg, (long)ipref, mode, ialloccg);
E 98
I 98
D 120
	ino = (ino_t)ffs_hashalloc(pip, cg, (long)ipref, mode, ffs_ialloccg);
E 120
I 120
D 122
	ino = (ino_t)ffs_hashalloc(pip, cg, (long)ipref, ap->a_mode, ffs_ialloccg);
E 122
I 122
	ino = (ino_t)ffs_hashalloc(pip, cg, (long)ipref, mode, ffs_ialloccg);
E 127
I 127
	cg = ino_to_cg(fs, ipref);
	ino = (ino_t)ffs_hashalloc(pip, cg, (long)ipref, mode, ffs_nodealloccg);
E 127
E 122
E 120
E 98
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
D 98
	error = iget(pip, ino, ipp);
E 98
I 98
D 99
	error = ffs_iget(pip, ino, ipp);
E 99
I 99
D 118
	error = ffs_vget(pvp->v_mount, ino, vpp);
E 118
I 118
D 120
	error = FFS_VGET(pvp->v_mount, ino, vpp);
E 120
I 120
D 121
	error = FFS_VGET(ap->a_pvp->v_mount, ino, ap->a_vpp);
E 121
I 121
D 122
	error = FFS_VGET(pvp->v_mount, ino, ap->a_vpp);
E 122
I 122
	error = VFS_VGET(pvp->v_mount, ino, ap->a_vpp);
E 122
E 121
E 120
E 118
E 99
E 98
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
D 98
		ifree(pip, ino, mode);
E 98
I 98
D 99
		ffs_ifree(pip, ino, mode);	/* XXX already freed? */
E 99
I 99
D 118
		ffs_vfree(pvp, ino, mode);
E 118
I 118
D 120
		VOP_VFREE(pvp, ino, mode);
E 120
I 120
D 121
		VOP_VFREE(ap->a_pvp, ino, ap->a_mode);
E 121
I 121
D 122
		VOP_VFREE(pvp, ino, ap->a_mode);
E 122
I 122
		VOP_VFREE(pvp, ino, mode);
E 122
E 121
E 120
E 118
E 99
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
E 79
	}
I 80
D 99
	ip = *ipp;
E 99
I 99
D 120
	ip = VTOI(*vpp);
E 120
I 120
	ip = VTOI(*ap->a_vpp);
E 120
E 99
E 80
D 27
	if (ip->i_mode)
E 27
I 27
	if (ip->i_mode) {
D 120
		printf("mode = 0%o, inum = %d, fs = %s\n",
E 120
I 120
D 122
		printf("ap->a_mode = 0%o, inum = %d, fs = %s\n",
E 122
I 122
		printf("mode = 0%o, inum = %d, fs = %s\n",
E 122
E 120
		    ip->i_mode, ip->i_number, fs->fs_fsmnt);
E 27
D 98
		panic("ialloc: dup alloc");
E 98
I 98
D 99
		panic("ffs_ialloc: dup alloc");
E 99
I 99
		panic("ffs_valloc: dup alloc");
E 99
E 98
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
E 82
I 80
	/*
	 * Set up a new generation number for this inode.
	 */
	if (++nextgennumber < (u_long)time.tv_sec)
		nextgennumber = time.tv_sec;
	ip->i_gen = nextgennumber;
E 80
E 27
D 79
	return (ip);
E 79
I 79
	return (0);
E 79
noinodes:
D 89
	fserr(fs, "out of inodes");
E 89
I 89
D 98
	fserr(fs, cred->cr_uid, "out of inodes");
E 98
I 98
D 120
	ffs_fserr(fs, cred->cr_uid, "out of inodes");
E 120
I 120
	ffs_fserr(fs, ap->a_cred->cr_uid, "out of inodes");
E 120
E 98
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
I 118
D 120
#undef pvp
#undef mode
#undef cred
#undef vpp
E 120
E 118

D 7
dipref(dev)
E 7
I 7
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
D 98
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
E 98
I 98
static ino_t
ffs_dirpref(fs)
E 98
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
E 7

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
E 41
}

I 7
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
D 139
daddr_t
E 139
I 139
ufs_daddr_t
E 139
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
D 98
blkpref(ip, lbn, indx, bap)
E 98
I 98
ffs_blkpref(ip, lbn, indx, bap)
E 98
	struct inode *ip;
D 139
	daddr_t lbn;
E 139
I 139
	ufs_daddr_t lbn;
E 139
	int indx;
D 139
	daddr_t *bap;
E 139
I 139
	ufs_daddr_t *bap;
E 139
E 41
I 19
{
I 41
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
D 139
	daddr_t nextblk;
E 139
I 139
	ufs_daddr_t nextblk;
E 139
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
	fs = ip->i_fs;
	if (indx % fs->fs_maxbpg == 0 || bap[indx - 1] == 0) {
		if (lbn < NDADDR) {
D 127
			cg = itog(fs, ip->i_number);
E 127
I 127
			cg = ino_to_cg(fs, ip->i_number);
E 127
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
D 127
			startcg = itog(fs, ip->i_number) + lbn / fs->fs_maxbpg;
E 127
I 127
			startcg =
			    ino_to_cg(fs, ip->i_number) + lbn / fs->fs_maxbpg;
E 127
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
D 123
	if (indx > fs->fs_maxcontig &&
D 46
	    bap[indx - fs->fs_maxcontig] + fs->fs_frag * fs->fs_maxcontig
E 46
I 46
	    bap[indx - fs->fs_maxcontig] + blkstofrags(fs, fs->fs_maxcontig)
E 46
	    != nextblk)
E 123
I 123
	if (indx < fs->fs_maxcontig || bap[indx - fs->fs_maxcontig] +
	    blkstofrags(fs, fs->fs_maxcontig) != nextblk)
E 123
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

I 14
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
D 98
u_long
E 10
D 19
hashalloc(dev, fs, cg, pref, size, allocator)
	dev_t dev;
	register struct fs *fs;
E 19
I 19
hashalloc(ip, cg, pref, size, allocator)
E 98
I 98
static u_long
ffs_hashalloc(ip, cg, pref, size, allocator)
E 98
	struct inode *ip;
E 19
	int cg;
	long pref;
	int size;	/* size for data blocks, mode for inodes */
D 10
	long (*allocator)();
E 10
I 10
D 137
	u_long (*allocator)();
E 137
I 137
	u_int32_t (*allocator)();
E 137
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
E 21
}

I 14
/*
 * Determine whether a fragment can be extended.
 *
 * Check to see if the necessary fragments are available, and 
 * if they are, allocate them.
 */
E 14
D 98
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
fragextend(ip, cg, bprev, osize, nsize)
E 98
I 98
D 139
static daddr_t
E 139
I 139
static ufs_daddr_t
E 139
ffs_fragextend(ip, cg, bprev, osize, nsize)
E 98
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
{
I 19
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
I 79
	struct buf *bp;
E 79
	long bno;
	int frags, bbase;
E 4
D 79
	int i;
E 79
I 79
	int i, error;
E 79

I 19
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
D 126
	cgp = bp->b_un.b_cg;
E 126
I 126
	cgp = (struct cg *)bp->b_data;
E 126
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

I 14
/*
 * Determine whether a block can be allocated.
 *
D 127
 * Check to see if a block of the apprpriate size is available,
E 127
I 127
 * Check to see if a block of the appropriate size is available,
E 127
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
D 100
daddr_t
E 100
I 100
D 139
static daddr_t
E 139
I 139
static ufs_daddr_t
E 139
E 100
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
D 98
alloccg(ip, cg, bpref, size)
E 98
I 98
ffs_alloccg(ip, cg, bpref, size)
E 98
	struct inode *ip;
E 19
E 4
	int cg;
D 139
	daddr_t bpref;
E 139
I 139
	ufs_daddr_t bpref;
E 139
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
D 126
	cgp = bp->b_un.b_cg;
E 126
I 126
	cgp = (struct cg *)bp->b_data;
E 126
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
D 98
		bno = alloccgblk(fs, cgp, bpref);
E 98
I 98
		bno = ffs_alloccgblk(fs, cgp, bpref);
E 98
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
D 98
		bno = alloccgblk(fs, cgp, bpref);
E 98
I 98
		bno = ffs_alloccgblk(fs, cgp, bpref);
E 98
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
D 98
	bno = mapsearch(fs, cgp, bpref, allocsiz);
E 98
I 98
	bno = ffs_mapsearch(fs, cgp, bpref, allocsiz);
E 98
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
}

I 14
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
D 98
daddr_t
D 10
alloccgblk(dev, fs, cgp, bpref)
	dev_t dev;
E 10
I 10
alloccgblk(fs, cgp, bpref)
E 98
I 98
D 139
static daddr_t
E 139
I 139
static ufs_daddr_t
E 139
ffs_alloccgblk(fs, cgp, bpref)
E 98
E 10
D 19
	struct fs *fs;
E 19
I 19
	register struct fs *fs;
E 19
	register struct cg *cgp;
D 139
	daddr_t bpref;
E 139
I 139
	ufs_daddr_t bpref;
E 139
{
D 7
	register int i;
E 7
I 7
D 130
	daddr_t bno;
E 130
I 130
D 139
	daddr_t bno, blkno;
E 139
I 139
	ufs_daddr_t bno, blkno;
E 139
E 130
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
E 13
E 7

E 4
D 7
	if (bpref) {
E 7
I 7
D 130
	if (bpref == 0) {
E 130
I 130
	if (bpref == 0 || dtog(fs, bpref) != cgp->cg_cgx) {
E 130
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
D 98
	if (isblock(fs, cg_blksfree(cgp), fragstoblks(fs, bpref))) {
E 98
I 98
	if (ffs_isblock(fs, cg_blksfree(cgp), fragstoblks(fs, bpref))) {
E 98
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
D 141
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
E 141
I 141
	if (fs->fs_nrpos <= 1 || fs->fs_cpc == 0) {
E 141
		/*
D 124
		 * block layout info is not available, so just have
		 * to take any block in this cylinder.
E 124
I 124
		 * Block layout information is not available.
		 * Leaving bpref unchanged means we take the
		 * next available free block following the one 
		 * we just allocated. Hopefully this will at
		 * least hit a track cache on drives of unknown
		 * geometry (e.g. SCSI).
E 124
		 */
D 124
		bpref = howmany(fs->fs_spc * cylno, NSPF(fs));
E 124
		goto norot;
	}
I 141
	/*
	 * check for a block available on the same cylinder
	 */
	cylno = cbtocylno(fs, bpref);
	if (cg_blktot(cgp)[cylno] == 0)
		goto norot;
E 141
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
D 98
			panic("alloccgblk: cyl groups corrupted");
E 98
I 98
			panic("ffs_alloccgblk: cyl groups corrupted");
E 98
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
D 98
			if (isblock(fs, cg_blksfree(cgp), bno + i)) {
E 98
I 98
			if (ffs_isblock(fs, cg_blksfree(cgp), bno + i)) {
E 98
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
D 98
		panic("alloccgblk: can't find blk in cyl");
E 98
I 98
		panic("ffs_alloccgblk: can't find blk in cyl");
E 98
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
D 98
	bno = mapsearch(fs, cgp, bpref, (int)fs->fs_frag);
E 98
I 98
	bno = ffs_mapsearch(fs, cgp, bpref, (int)fs->fs_frag);
E 98
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
D 98
	clrblock(fs, cg_blksfree(cgp), (long)fragstoblks(fs, bno));
E 98
I 98
D 130
	ffs_clrblock(fs, cg_blksfree(cgp), (long)fragstoblks(fs, bno));
E 130
I 130
	blkno = fragstoblks(fs, bno);
	ffs_clrblock(fs, cg_blksfree(cgp), (long)blkno);
	ffs_clusteracct(fs, cgp, blkno, -1);
E 130
E 98
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
D 75
	
E 75
I 75

E 75
I 14
/*
I 130
 * Determine whether a cluster can be allocated.
 *
 * We do not currently check for optimal rotational layout if there
 * are multiple choices in the same cylinder group. Instead we just
 * take the first one that we find following bpref.
 */
D 139
static daddr_t
E 139
I 139
static ufs_daddr_t
E 139
ffs_clusteralloc(ip, cg, bpref, len)
	struct inode *ip;
	int cg;
D 139
	daddr_t bpref;
E 139
I 139
	ufs_daddr_t bpref;
E 139
	int len;
{
	register struct fs *fs;
	register struct cg *cgp;
	struct buf *bp;
D 138
	int i, run, bno, bit, map;
E 138
I 138
	int i, got, run, bno, bit, map;
E 138
	u_char *mapp;
I 134
	int32_t *lp;
E 134

	fs = ip->i_fs;
D 134
	if (fs->fs_cs(fs, cg).cs_nbfree < len)
E 134
I 134
	if (fs->fs_maxcluster[cg] < len)
E 134
		return (NULL);
	if (bread(ip->i_devvp, fsbtodb(fs, cgtod(fs, cg)), (int)fs->fs_cgsize,
	    NOCRED, &bp))
		goto fail;
	cgp = (struct cg *)bp->b_data;
	if (!cg_chkmagic(cgp))
		goto fail;
	/*
	 * Check to see if a cluster of the needed size (or bigger) is
	 * available in this cylinder group.
	 */
I 134
	lp = &cg_clustersum(cgp)[len];
E 134
	for (i = len; i <= fs->fs_contigsumsize; i++)
D 134
		if (cg_clustersum(cgp)[i] > 0)
E 134
I 134
		if (*lp++ > 0)
E 134
			break;
D 134
	if (i > fs->fs_contigsumsize)
E 134
I 134
	if (i > fs->fs_contigsumsize) {
		/*
		 * This is the first time looking for a cluster in this
		 * cylinder group. Update the cluster summary information
		 * to reflect the true maximum sized cluster so that
		 * future cluster allocation requests can avoid reading
		 * the cylinder group map only to find no clusters.
		 */
		lp = &cg_clustersum(cgp)[len - 1];
		for (i = len - 1; i > 0; i--)
			if (*lp-- > 0)
				break;
		fs->fs_maxcluster[cg] = i;
E 134
		goto fail;
I 134
	}
E 134
	/*
	 * Search the cluster map to find a big enough cluster.
	 * We take the first one that we find, even if it is larger
	 * than we need as we prefer to get one close to the previous
	 * block allocation. We do not search before the current
	 * preference point as we do not want to allocate a block
	 * that is allocated before the previous one (as we will
	 * then have to wait for another pass of the elevator
	 * algorithm before it will be read). We prefer to fail and
	 * be recalled to try an allocation in the next cylinder group.
	 */
	if (dtog(fs, bpref) != cg)
		bpref = 0;
	else
		bpref = fragstoblks(fs, dtogd(fs, blknum(fs, bpref)));
	mapp = &cg_clustersfree(cgp)[bpref / NBBY];
	map = *mapp++;
	bit = 1 << (bpref % NBBY);
D 138
	for (run = 0, i = bpref; i < cgp->cg_nclusterblks; i++) {
E 138
I 138
	for (run = 0, got = bpref; got < cgp->cg_nclusterblks; got++) {
E 138
		if ((map & bit) == 0) {
			run = 0;
		} else {
			run++;
			if (run == len)
				break;
		}
D 138
		if ((i & (NBBY - 1)) != (NBBY - 1)) {
E 138
I 138
		if ((got & (NBBY - 1)) != (NBBY - 1)) {
E 138
			bit <<= 1;
		} else {
			map = *mapp++;
			bit = 1;
		}
	}
D 138
	if (i == cgp->cg_nclusterblks)
E 138
I 138
	if (got == cgp->cg_nclusterblks)
E 138
		goto fail;
	/*
	 * Allocate the cluster that we have found.
	 */
D 138
	bno = cg * fs->fs_fpg + blkstofrags(fs, i - run + 1);
E 138
I 138
	for (i = 1; i <= len; i++)
		if (!ffs_isblock(fs, cg_blksfree(cgp), got - run + i))
			panic("ffs_clusteralloc: map mismatch");
	bno = cg * fs->fs_fpg + blkstofrags(fs, got - run + 1);
I 142
	if (dtog(fs, bno) != cg)
		panic("ffs_clusteralloc: allocated out of group");
E 142
E 138
	len = blkstofrags(fs, len);
	for (i = 0; i < len; i += fs->fs_frag)
D 138
		if (ffs_alloccgblk(fs, cgp, bno + i) != bno + i)
E 138
I 138
		if ((got = ffs_alloccgblk(fs, cgp, bno + i)) != bno + i)
E 138
			panic("ffs_clusteralloc: lost block");
	brelse(bp);
	return (bno);

fail:
	brelse(bp);
	return (0);
}

/*
E 130
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
D 98
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
E 98
I 98
D 134
static ino_t
E 134
I 134
D 137
static u_long
E 137
I 137
static ino_t
E 137
E 134
D 127
ffs_ialloccg(ip, cg, ipref, mode)
E 127
I 127
ffs_nodealloccg(ip, cg, ipref, mode)
E 127
E 98
	struct inode *ip;
E 19
E 4
	int cg;
D 139
	daddr_t ipref;
E 139
I 139
	ufs_daddr_t ipref;
E 139
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
D 126
	cgp = bp->b_un.b_cg;
E 126
I 126
	cgp = (struct cg *)bp->b_data;
E 126
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
D 129
			printf("cg = %s, irotor = %d, fs = %s\n",
E 129
I 129
			printf("cg = %d, irotor = %d, fs = %s\n",
E 129
			    cg, cgp->cg_irotor, fs->fs_fsmnt);
D 98
			panic("ialloccg: map corrupted");
E 98
I 98
D 127
			panic("ffs_ialloccg: map corrupted");
E 127
I 127
			panic("ffs_nodealloccg: map corrupted");
E 127
E 98
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
D 98
	panic("ialloccg: block not in map");
E 98
I 98
D 127
	panic("ffs_ialloccg: block not in map");
E 127
I 127
	panic("ffs_nodealloccg: block not in map");
E 127
E 98
	/* NOTREACHED */
E 53
E 21
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
}

I 14
/*
 * Free a block or fragment.
 *
 * The specified block or fragment is placed back in the
 * free map. If a fragment is deallocated, a possible 
 * block reassembly is checked.
 */
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
E 98
I 98
ffs_blkfree(ip, bno, size)
E 98
E 72
E 41
	register struct inode *ip;
E 19
D 139
	daddr_t bno;
E 139
I 139
	ufs_daddr_t bno;
E 139
D 10
	int size;
E 10
I 10
D 101
	off_t size;
E 101
I 101
	long size;
E 101
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
D 130
	int error, cg, blk, frags, bbase;
E 79
	register int i;
E 130
I 130
D 139
	daddr_t blkno;
E 139
I 139
	ufs_daddr_t blkno;
E 139
	int i, error, cg, blk, frags, bbase;
E 130
I 89
D 94
	struct ucred *cred = u.u_cred;	/* XXX */
E 94
I 94
D 102
	struct ucred *cred = curproc->p_ucred;	/* XXX */
E 102
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
D 126
	if ((unsigned)size > fs->fs_bsize || fragoff(fs, size) != 0) {
E 126
I 126
	if ((u_int)size > fs->fs_bsize || fragoff(fs, size) != 0) {
E 126
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
D 126
	if ((unsigned)bno >= fs->fs_size) {
E 126
I 126
	if ((u_int)bno >= fs->fs_size) {
E 126
E 89
		printf("bad block %d, ino %d\n", bno, ip->i_number);
I 89
D 98
		fserr(fs, cred->cr_uid, "bad block");
E 98
I 98
D 102
		ffs_fserr(fs, cred->cr_uid, "bad block");
E 102
I 102
		ffs_fserr(fs, ip->i_uid, "bad block");
E 102
E 98
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
D 126
	cgp = bp->b_un.b_cg;
E 126
I 126
	cgp = (struct cg *)bp->b_data;
E 126
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
D 98
		if (isblock(fs, cg_blksfree(cgp), fragstoblks(fs, bno))) {
E 98
I 98
D 130
		if (ffs_isblock(fs, cg_blksfree(cgp), fragstoblks(fs, bno))) {
E 130
I 130
		blkno = fragstoblks(fs, bno);
		if (ffs_isblock(fs, cg_blksfree(cgp), blkno)) {
E 130
E 98
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
D 98
		setblock(fs, cg_blksfree(cgp), fragstoblks(fs, bno));
E 98
I 98
D 130
		ffs_setblock(fs, cg_blksfree(cgp), fragstoblks(fs, bno));
E 130
I 130
		ffs_setblock(fs, cg_blksfree(cgp), blkno);
		ffs_clusteracct(fs, cgp, blkno, 1);
E 130
E 98
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
D 98
		fragacct(fs, blk, cgp->cg_frsum, -1);
E 98
I 98
		ffs_fragacct(fs, blk, cgp->cg_frsum, -1);
E 98
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
D 98
		fragacct(fs, blk, cgp->cg_frsum, 1);
E 98
I 98
		ffs_fragacct(fs, blk, cgp->cg_frsum, 1);
E 98
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
D 98
		if (isblock(fs, cg_blksfree(cgp),
E 98
I 98
D 130
		if (ffs_isblock(fs, cg_blksfree(cgp),
E 98
		    (daddr_t)fragstoblks(fs, bbase))) {
E 130
I 130
		blkno = fragstoblks(fs, bbase);
		if (ffs_isblock(fs, cg_blksfree(cgp), blkno)) {
E 130
E 77
E 75
E 46
			cgp->cg_cs.cs_nffree -= fs->fs_frag;
			fs->fs_cstotal.cs_nffree -= fs->fs_frag;
			fs->fs_cs(fs, cg).cs_nffree -= fs->fs_frag;
I 130
			ffs_clusteracct(fs, cgp, blkno, 1);
E 130
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
I 142

#ifdef DIAGNOSTIC
/*
 * Verify allocation of a block or fragment. Returns true if block or
 * fragment is allocated, false if it is free.
 */
ffs_checkblk(ip, bno, size)
	struct inode *ip;
	ufs_daddr_t bno;
	long size;
{
	struct fs *fs;
	struct cg *cgp;
	struct buf *bp;
	int i, error, frags, free;

	fs = ip->i_fs;
	if ((u_int)size > fs->fs_bsize || fragoff(fs, size) != 0) {
		printf("bsize = %d, size = %d, fs = %s\n",
		    fs->fs_bsize, size, fs->fs_fsmnt);
		panic("checkblk: bad size");
	}
	if ((u_int)bno >= fs->fs_size)
		panic("checkblk: bad block %d", bno);
	error = bread(ip->i_devvp, fsbtodb(fs, cgtod(fs, dtog(fs, bno))),
		(int)fs->fs_cgsize, NOCRED, &bp);
	if (error) {
		brelse(bp);
		return;
	}
	cgp = (struct cg *)bp->b_data;
	if (!cg_chkmagic(cgp)) {
		brelse(bp);
		return;
	}
	bno = dtogd(fs, bno);
	if (size == fs->fs_bsize) {
		free = ffs_isblock(fs, cg_blksfree(cgp), fragstoblks(fs, bno));
	} else {
		frags = numfrags(fs, size);
		for (free = 0, i = 0; i < frags; i++)
			if (isset(cg_blksfree(cgp), bno + i))
				free++;
		if (free != 0 && free != frags)
			panic("checkblk: partially free fragment");
	}
	brelse(bp);
	return (!free);
}
#endif /* DIAGNOSTIC */
E 142

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
D 98
ifree(ip, ino, mode)
	struct inode *ip;
E 98
I 98
D 119
void
E 119
I 119
int
E 119
D 99
ffs_ifree(pip, ino, mode)
	struct inode *pip;
E 99
I 99
D 118
ffs_vfree(pvp, ino, mode)
	struct vnode *pvp;
E 99
E 98
E 19
	ino_t ino;
	int mode;
E 118
I 118
D 122
ffs_vfree (ap)
	struct vop_vfree_args *ap;
E 122
I 122
ffs_vfree(ap)
	struct vop_vfree_args /* {
		struct vnode *a_pvp;
		ino_t a_ino;
		int a_mode;
	} */ *ap;
E 122
D 120
#define pvp (ap->a_pvp)
#define ino (ap->a_ino)
#define mode (ap->a_mode)
E 120
E 118
{
	register struct fs *fs;
	register struct cg *cgp;
I 99
	register struct inode *pip;
I 122
	ino_t ino = ap->a_ino;
E 122
E 99
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
E 79

I 99
D 120
	pip = VTOI(pvp);
E 120
I 120
	pip = VTOI(ap->a_pvp);
E 120
E 99
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
E 98
I 98
	fs = pip->i_fs;
D 120
	if ((u_int)ino >= fs->fs_ipg * fs->fs_ncg)
		panic("ifree: range: dev = 0x%x, ino = %d, fs = %s\n",
		    pip->i_dev, ino, fs->fs_fsmnt);
E 98
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
E 120
I 120
D 122
	if ((u_int)ap->a_ino >= fs->fs_ipg * fs->fs_ncg)
		panic("ifree: range: dev = 0x%x, ap->a_ino = %d, fs = %s\n",
		    pip->i_dev, ap->a_ino, fs->fs_fsmnt);
	cg = itog(fs, ap->a_ino);
E 122
I 122
	if ((u_int)ino >= fs->fs_ipg * fs->fs_ncg)
		panic("ifree: range: dev = 0x%x, ino = %d, fs = %s\n",
		    pip->i_dev, ino, fs->fs_fsmnt);
D 127
	cg = itog(fs, ino);
E 127
I 127
	cg = ino_to_cg(fs, ino);
E 127
E 122
E 120
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
D 98
	error = bread(ip->i_devvp, fsbtodb(fs, cgtod(fs, cg)),
E 98
I 98
	error = bread(pip->i_devvp, fsbtodb(fs, cgtod(fs, cg)),
E 98
D 81
		(int)fs->fs_cgsize, &bp);
E 81
I 81
		(int)fs->fs_cgsize, NOCRED, &bp);
E 81
	if (error) {
		brelse(bp);
D 119
		return;
E 119
I 119
		return (0);
E 119
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
D 126
	cgp = bp->b_un.b_cg;
E 126
I 126
	cgp = (struct cg *)bp->b_data;
E 126
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
D 119
		return;
E 119
I 119
		return (0);
E 119
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
D 120
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
D 98
		    ip->i_dev, ino, fs->fs_fsmnt);
E 98
I 98
		    pip->i_dev, ino, fs->fs_fsmnt);
E 120
I 120
D 122
	ap->a_ino %= fs->fs_ipg;
	if (isclr(cg_inosused(cgp), ap->a_ino)) {
		printf("dev = 0x%x, ap->a_ino = %d, fs = %s\n",
		    pip->i_dev, ap->a_ino, fs->fs_fsmnt);
E 122
I 122
	ino %= fs->fs_ipg;
	if (isclr(cg_inosused(cgp), ino)) {
		printf("dev = 0x%x, ino = %d, fs = %s\n",
		    pip->i_dev, ino, fs->fs_fsmnt);
E 122
E 120
E 98
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
D 120
	clrbit(cg_inosused(cgp), ino);
E 75
I 53
	if (ino < cgp->cg_irotor)
		cgp->cg_irotor = ino;
E 120
I 120
D 122
	clrbit(cg_inosused(cgp), ap->a_ino);
	if (ap->a_ino < cgp->cg_irotor)
		cgp->cg_irotor = ap->a_ino;
E 122
I 122
	clrbit(cg_inosused(cgp), ino);
	if (ino < cgp->cg_irotor)
		cgp->cg_irotor = ino;
E 122
E 120
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
D 120
	if ((mode & IFMT) == IFDIR) {
E 120
I 120
	if ((ap->a_mode & IFMT) == IFDIR) {
E 120
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
I 119
	return (0);
E 119
I 4
}
I 118
D 120
#undef pvp
#undef ino
#undef mode
E 120
E 118

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
D 98
daddr_t
mapsearch(fs, cgp, bpref, allocsiz)
E 98
I 98
D 139
static daddr_t
E 139
I 139
static ufs_daddr_t
E 139
ffs_mapsearch(fs, cgp, bpref, allocsiz)
E 98
	register struct fs *fs;
	register struct cg *cgp;
D 139
	daddr_t bpref;
E 139
I 139
	ufs_daddr_t bpref;
E 139
	int allocsiz;
{
D 139
	daddr_t bno;
E 139
I 139
	ufs_daddr_t bno;
E 139
	int start, len, loc, i;
	int blk, field, subfield, pos;

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
D 126
	loc = scanc((unsigned)len, (u_char *)&cg_blksfree(cgp)[start],
E 126
I 126
	loc = scanc((u_int)len, (u_char *)&cg_blksfree(cgp)[start],
E 126
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
D 126
		loc = scanc((unsigned)len, (u_char *)&cg_blksfree(cgp)[0],
E 126
I 126
		loc = scanc((u_int)len, (u_char *)&cg_blksfree(cgp)[0],
E 126
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
D 98
			panic("alloccg: map corrupted");
E 98
I 98
			panic("ffs_alloccg: map corrupted");
E 98
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
D 98
	panic("alloccg: block not in map");
E 98
I 98
	panic("ffs_alloccg: block not in map");
E 98
D 21
	return (0);
E 21
I 21
D 25
	return (NULL);
E 25
I 25
	return (-1);
I 130
}

/*
 * Update the cluster map because of an allocation or free.
 *
 * Cnt == 1 means free; cnt == -1 means allocating.
 */
ffs_clusteracct(fs, cgp, blkno, cnt)
	struct fs *fs;
	struct cg *cgp;
D 139
	daddr_t blkno;
E 139
I 139
	ufs_daddr_t blkno;
E 139
	int cnt;
{
D 137
	long *sump;
E 137
I 137
	int32_t *sump;
E 137
I 134
	int32_t *lp;
E 134
	u_char *freemapp, *mapp;
	int i, start, end, forw, back, map, bit;

	if (fs->fs_contigsumsize <= 0)
		return;
	freemapp = cg_clustersfree(cgp);
	sump = cg_clustersum(cgp);
	/*
	 * Allocate or clear the actual block.
	 */
	if (cnt > 0)
		setbit(freemapp, blkno);
	else
		clrbit(freemapp, blkno);
	/*
	 * Find the size of the cluster going forward.
	 */
	start = blkno + 1;
	end = start + fs->fs_contigsumsize;
	if (end >= cgp->cg_nclusterblks)
		end = cgp->cg_nclusterblks;
	mapp = &freemapp[start / NBBY];
	map = *mapp++;
	bit = 1 << (start % NBBY);
	for (i = start; i < end; i++) {
		if ((map & bit) == 0)
			break;
		if ((i & (NBBY - 1)) != (NBBY - 1)) {
			bit <<= 1;
		} else {
			map = *mapp++;
			bit = 1;
		}
	}
	forw = i - start;
	/*
	 * Find the size of the cluster going backward.
	 */
	start = blkno - 1;
	end = start - fs->fs_contigsumsize;
	if (end < 0)
		end = -1;
	mapp = &freemapp[start / NBBY];
	map = *mapp--;
	bit = 1 << (start % NBBY);
	for (i = start; i > end; i--) {
		if ((map & bit) == 0)
			break;
		if ((i & (NBBY - 1)) != 0) {
			bit >>= 1;
		} else {
			map = *mapp--;
			bit = 1 << (NBBY - 1);
		}
	}
	back = start - i;
	/*
	 * Account for old cluster and the possibly new forward and
	 * back clusters.
	 */
	i = back + forw + 1;
	if (i > fs->fs_contigsumsize)
		i = fs->fs_contigsumsize;
	sump[i] += cnt;
	if (back > 0)
		sump[back] -= cnt;
	if (forw > 0)
		sump[forw] -= cnt;
I 134
	/*
	 * Update cluster summary information.
	 */
	lp = &sump[fs->fs_contigsumsize];
	for (i = fs->fs_contigsumsize; i > 0; i--)
		if (*lp-- > 0)
			break;
	fs->fs_maxcluster[cgp->cg_cgx] = i;
E 134
E 130
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
D 98
fserr(fs, uid, cp)
E 98
I 98
static void
ffs_fserr(fs, uid, cp)
E 98
E 89
	struct fs *fs;
I 89
D 98
	uid_t uid;
E 98
I 98
	u_int uid;
E 98
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
E 89
E 65
E 61
}
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
