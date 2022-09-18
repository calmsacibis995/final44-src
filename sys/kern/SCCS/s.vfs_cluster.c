h25410
s 00001/00012/00729
d D 8.10 95/03/28 23:28:45 mckusick 154 153
c doreallocblks moves into ffs
e
s 00001/00001/00740
d D 8.9 95/02/14 10:44:56 cgd 153 152
c check pointer != NULL rather than cast.
e
s 00035/00014/00706
d D 8.8 94/07/28 13:59:34 hibler 152 151
c sigh...handle another "too much memory in buffer" boundary case
e
s 00012/00001/00708
d D 8.7 94/02/13 11:52:17 hibler 151 150
c add sysctl debug variable to enable/disable reallocblks
e
s 00080/00012/00629
d D 8.6 94/02/05 01:41:05 mckusick 150 149
c first cut at improving cluster allocation
e
s 00193/00061/00448
d D 8.5 94/01/12 14:49:41 hibler 149 148
c massive overhaul to the clustering strategy,
c handle buffers with excess memory,
c propogate errors on failed cluster operations.
e
s 00000/00001/00509
d D 8.4 94/01/04 18:44:24 bostic 148 147
c lint
e
s 00010/00008/00500
d D 8.3 93/10/14 22:02:03 mckusick 147 146
c VOP_BMAP must check blkno == -1 (i.e. that we have a hole in the file)
e
s 00004/00004/00504
d D 8.2 93/09/21 07:31:20 bostic 146 145
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00506
d D 8.1 93/06/10 22:00:27 bostic 145 144
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00719/00505
d D 7.60 93/05/10 17:18:21 mckusick 144 142
c break clustering code out of vfs_bio.c
e
s 00056/00004/01220
d D 7.59.1.1 93/05/10 15:37:34 mckusick 143 142
c cluster debugging; goes with 7.112.1.2 in ufs/ufs_vnops.c
e
s 00039/00034/01185
d D 7.59 93/05/10 15:02:27 margo 142 141
c Add diagnostic check on cluster_rbuild to make sure I/O. 
c Restructure cluster_write. Do not assume that this routine will always get 
c called to allocate a block.
e
s 00060/00029/01159
d D 7.58 93/02/02 21:00:54 mckusick 141 140
c update for 4.4BSD from Rick Macklem
e
s 00486/00000/00701
d D 7.57 92/12/09 16:10:42 margo 140 139
c add read and write clustering routines
e
s 00012/00000/00689
d D 7.56 92/12/09 14:19:45 margo 139 138
c add count_lock_queue for LFS
e
s 00032/00057/00657
d D 7.55 92/10/22 17:26:12 mckusick 138 137
c use new queue primitives
e
s 00120/00047/00594
d D 7.54 92/10/02 00:30:51 mckusick 137 135
c modernize the management of the hash and free lists
e
s 00150/00044/00564
d R 7.54 92/10/02 00:10:50 mckusick 136 135
c modernize the management of the hash and free lists
e
s 00033/00000/00608
d D 7.53 92/09/30 14:17:04 mckusick 135 133
c ufs_bufstats becomes vfs_bufstats
e
s 00034/00000/00608
d R 7.53 92/09/29 17:16:27 mckusick 134 133
c ufs_bufstats becomes vfs_bufstats
e
s 00000/00003/00608
d D 7.52 92/09/24 11:31:26 bostic 133 132
c get rid of unneeded lfs_flush
e
s 00000/00001/00611
d D 7.51 92/07/12 15:55:32 mckusick 132 131
c get rid of unneeded include
e
s 00000/00004/00612
d D 7.50 92/07/03 01:37:47 mckusick 131 130
c delete USES
e
s 00002/00001/00614
d D 7.49 92/06/23 19:59:34 mckusick 130 129
c lint
e
s 00008/00000/00607
d D 7.48 92/05/15 12:23:02 heideman 129 128
c vn_bwrite added as new, generic vnode op
e
s 00004/00000/00603
d D 7.47 92/05/14 17:35:22 heideman 128 119
c vnode interface conversion
e
s 00004/00000/00603
d R 7.47 92/05/14 15:51:04 heideman 127 119
c vnode interface conversion
e
s 00004/00000/00603
d R 7.47 92/05/14 14:54:17 heideman 126 119
c vnode interface conversion
e
s 00004/00000/00603
d R 7.47 92/05/14 12:58:54 heideman 125 119
c vnode interface conversion
e
s 00004/00000/00603
d R 7.47 92/05/14 11:56:33 heideman 124 119
c vnode interface conversion
e
s 00004/00000/00603
d R 7.47 92/05/14 10:36:35 heideman 123 119
c vnode interface conversion
e
s 00004/00000/00603
d R 7.47 92/05/13 23:15:41 heideman 122 119
c vnode interface conversion
e
s 00004/00000/00603
d R 7.47 92/05/13 19:00:46 heideman 121 119
c vnode interface conversion
e
s 00004/00000/00603
d R 7.47 92/05/13 18:32:53 heideman 120 119
c vnode interface conversion
e
s 00007/00005/00596
d D 7.46 92/02/05 23:11:38 torek 119 118
c protect flag manipulation; cleanup of bufinit
e
s 00018/00010/00583
d D 7.45 92/01/14 12:19:55 mckusick 118 117
c breada gets generalized to breadn
e
s 00003/00000/00590
d D 7.44 91/12/31 15:20:57 bostic 117 116
c add lfs_flush routine, just a hack until Kirk's done
e
s 00010/00008/00580
d D 7.43 91/11/01 16:37:42 bostic 116 115
c lint
e
s 00003/00001/00585
d D 7.42 91/05/10 09:10:15 mckusick 115 114
c include proper copyright header
e
s 00003/00003/00583
d D 7.41 91/05/09 21:18:24 bostic 114 113
c new copyright; att/bsd/shared
e
s 00010/00004/00576
d D 7.40 91/05/08 21:41:43 mckusick 113 112
c update from Rick Macklem for race condition in NFS
e
s 00038/00000/00542
d D 7.39 91/05/07 08:40:01 karels 112 111
c move bufinit here from init_main.c
e
s 00002/00264/00540
d D 7.38 91/05/06 14:36:11 mckusick 111 110
c more uncontaminated code from vfs_bio.c to vfs_subr.c
e
s 00003/00001/00801
d D 7.37 91/04/19 17:08:54 mckusick 110 109
c lint; when sync'ing, skip vnodes that are locked
e
s 00001/00001/00801
d D 7.36 91/04/15 23:56:03 mckusick 109 108
c add proc pointers to appropriate VOP operations
e
s 00001/00002/00801
d D 7.35 91/03/19 09:49:02 karels 108 107
c expunge user.h, other unneeded headers
e
s 00010/00005/00793
d D 7.34 91/03/17 15:42:19 karels 107 106
c more-or-less working with new proc & user structs
e
s 00001/00000/00797
d D 7.33 91/03/04 22:53:34 mckusick 106 105
c misc fixes plus diskless support from Rick Macklem
e
s 00074/00088/00723
d D 7.32 91/01/28 11:43:55 mckusick 105 104
c cleanup comments to reflect reality; minor code cleanups; lint
e
s 00068/00014/00743
d D 7.31 90/08/24 09:57:39 mckusick 104 103
c eliminate reallocbuf; merge in ufs_machdep.c
e
s 00001/00011/00756
d D 7.30 90/06/28 21:25:21 bostic 103 102
c new copyright notice
e
s 00000/00014/00767
d D 7.29 90/05/30 09:52:26 mckusick 102 101
c get rid of historic (unnecessary) code
e
s 00006/00006/00775
d D 7.28 90/05/05 17:07:41 mckusick 101 100
c have to check that vnode is still associated with mount point before using it
e
s 00004/00004/00777
d D 7.27 90/05/04 20:55:31 mckusick 100 99
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00004/00000/00777
d D 7.26 90/05/02 19:10:54 mckusick 99 98
c checks that vfs_busy is being used
e
s 00001/00000/00776
d D 7.25 90/03/27 19:00:03 mckusick 98 97
c break specinfo structure out of vnode.h into specdev.h
e
s 00001/00000/00775
d D 7.24 90/03/27 15:13:30 mckusick 97 96
c missing splbio (from Naomi@osf)
e
s 00009/00016/00766
d D 7.23 90/03/06 23:24:51 mckusick 96 95
c pack now takes a vnode instead of a dev
e
s 00003/00001/00779
d D 7.22 90/02/25 12:54:12 mckusick 95 94
c have to protect count increment with splbio to protect against biodone
e
s 00004/00001/00776
d D 7.21 90/02/08 13:54:59 mckusick 94 93
c reassign instead of invalidating buffers associated with other vnodes
c when doing vinvalbuf (fix for itrunc from noemi@osf.org)
e
s 00001/00001/00776
d D 7.20 90/01/13 18:37:20 mckusick 93 92
c minor optimization
e
s 00094/00057/00683
d D 7.19 90/01/04 22:29:20 mckusick 92 91
c manage dirty and clean buffer chains;
c track number of active I/O's;
c expand notavail inline to avoid spurious spl's
e
s 00002/00058/00738
d D 7.18 89/12/30 22:30:06 mckusick 91 90
c blkflush is no longer used;
c VREF => VHOLD and vrele => HOLDRELE as buffers use holdcnts not usecounts
e
s 00006/00002/00790
d D 7.17 89/12/22 09:15:45 mckusick 90 89
c have to save v_mountf before vput'ing the vnode
e
s 00005/00001/00787
d D 7.16 89/12/19 16:18:21 mckusick 89 88
c add missing splx's
e
s 00219/00164/00569
d D 7.15 89/11/30 22:45:44 mckusick 88 87
c major overhaul to generalize for a logical buffer pool
e
s 00010/00002/00723
d D 7.14 89/11/25 21:38:27 mckusick 87 86
c have to check both v_mount for logical buffer cache and v_mounton for
c block devices using the physical buffer cache when doing bflush and binval
e
s 00034/00024/00691
d D 7.13 89/10/15 21:19:37 mckusick 86 85
c updated version of blkflush from Torek
e
s 00004/00004/00711
d D 7.12 89/08/30 20:21:09 mckusick 85 84
c minor fixes for NFS
e
s 00003/00002/00712
d D 7.11 89/08/28 09:45:05 mckusick 84 83
c get the splx's in the right place
e
s 00054/00055/00660
d D 7.10 89/08/26 14:12:44 mckusick 83 82
c generalize the buffer pool so that NFS can become a client
e
s 00009/00001/00706
d D 7.9 89/08/16 00:25:48 mckusick 82 81
c have to remember to lock buffers before trying to grab them
e
s 00024/00020/00683
d D 7.8 89/08/15 15:30:08 mckusick 81 80
c binval must wait for I/O to complete before marking a buffer INVAL;
c use bawrite rather than setting ASYNC flag and calling bwrite
e
s 00001/00001/00702
d D 7.7 89/06/27 19:17:49 mckusick 80 79
c update reference counts on vnodes using VREF
e
s 00001/00001/00702
d D 7.6 89/06/06 14:56:04 mckusick 79 78
c bug fix from Rick Macklem
e
s 00174/00098/00529
d D 7.5 89/05/09 17:21:58 mckusick 78 77
c merge in vnodes
e
s 00002/00002/00625
d D 7.4 89/04/25 14:42:37 mckusick 77 76
c ../machine => machine
e
s 00019/00003/00608
d D 7.3 87/11/12 15:21:25 mckusick 76 75
c write dirty buffers that are growing to avoid bread'ing stale 
c data from the disk over the newer data in the buffer.
e
s 00005/00004/00606
d D 7.2 87/04/02 15:49:12 karels 75 73
c working with pack labels
e
s 00079/00004/00606
d D 7.1.1.1 87/04/02 15:41:08 karels 74 73
c add ifdefs for dev_bsize (almost working)
e
s 00001/00001/00609
d D 7.1 86/06/05 00:11:54 mckusick 73 72
c 4.3BSD release version
e
s 00012/00012/00598
d D 6.9 86/02/20 15:19:38 karels 72 71
c lint and cleanups from Sam
e
s 00004/00000/00606
d D 6.8 85/10/23 16:13:44 mckusick 71 70
c sanity checks in getblk() and geteblk()
e
s 00001/00003/00605
d D 6.7 85/09/17 10:40:42 karels 70 69
c I've wanted to make this comment untrue for a long time...
e
s 00010/00002/00598
d D 6.6 85/09/13 19:23:28 mckusick 69 68
c wrong constant used by coincidence (PGSHIFT should be DEV_BSHIFT)
e
s 00007/00001/00593
d D 6.5 85/06/08 14:50:13 mckusick 68 67
c Add copyright
e
s 00010/00010/00584
d D 6.4 84/08/29 20:25:28 bloom 67 66
c Change to includes.  no more ../h
e
s 00001/00001/00593
d D 6.3 84/08/07 22:42:49 mckusick 66 65
c avoid calling brealloc() when unnecessary
e
s 00010/00008/00584
d D 6.2 84/01/03 19:43:45 sam 65 64
c pack block size into trace record for buffer cache
e
s 00000/00000/00592
d D 6.1 83/07/29 06:40:55 sam 64 63
c 4.2 distribution
e
s 00000/00004/00592
d D 4.48 83/07/01 02:20:38 sam 63 62
c purge #if sun's
e
s 00005/00183/00591
d D 4.47 83/06/14 23:51:48 sam 62 61
c move machine dependent parts out
e
s 00004/00004/00770
d D 4.46 83/05/21 15:43:00 sam 61 60
c macro-ized for speeeeeeeeeeeeed
e
s 00000/00016/00774
d D 4.45 83/05/18 01:58:11 sam 60 58
c changes from sun to do swapping on variable sized devices
e
s 00000/00015/00775
d R 4.45 83/05/06 09:24:42 sam 59 58
c from pugs@sun.UUCP; removes dirty page pushes from bio routines
e
s 00001/00000/00789
d D 4.44 83/05/02 07:18:10 sam 58 57
c another missing splx; from shannon@sun.UUCP
e
s 00001/00000/00788
d D 4.43 83/05/01 19:21:55 sam 57 56
c missing splx causes long periods of running at spl6; 
c from shannon@sun.UUCP
e
s 00002/00001/00786
d D 4.42 83/04/04 21:48:50 sam 56 55
c hack, but it fixes EBADF
e
s 00001/00005/00786
d D 4.41 82/12/19 17:41:34 sam 55 54
c bwrite shouldn't clear B_AGE or brelse won't put it at the head 
c of the free list (Mike Karels); also geterror call is extraneous
e
s 00117/00016/00674
d D 4.40 82/12/17 11:48:23 sam 54 53
c sun merge
e
s 00179/00077/00511
d D 4.39 82/11/13 22:52:27 sam 53 52
c merge of 4.1b and 4.1c
e
s 00000/00000/00588
d D 4.39 82/10/19 10:32:02  53 52
c more lint
e
s 00000/00000/00588
d D 4.38 82/10/17 21:51:03 root 52 51
c more lint
e
s 00003/00003/00585
d D 4.37 82/10/17 14:06:17 root 51 50
c fix lint
e
s 00005/00005/00583
d D 4.36 82/09/04 09:20:52 root 50 49
c new names for some counters
e
s 00006/00004/00582
d D 4.35 82/08/13 00:04:59 wnj 49 48
c fixes to get uio'd readi for char devs
e
s 00050/00022/00536
d D 4.34 82/06/14 22:59:41 root 48 47
c fixes to interactions of new fs and buffer cache with partial blocks
c including removal of superblocks from cache and refined readahead and
c brealloc routine
e
s 00010/00009/00548
d D 4.33 82/06/07 23:47:12 mckusick 47 46
c fix read-ahead block calculation
e
s 00004/00005/00553
d D 4.32 82/06/01 23:22:04 mckusick 46 45
c incorporate brealloc into geteblk()
e
s 00072/00197/00486
d D 4.31 82/05/31 19:13:27 mckusick 45 43
c clean up code; put common queue operations into macros
e
s 00073/00199/00484
d R 4.31 82/05/22 16:28:03 mckusick 44 43
c clean up code; put common list operations into macros
e
s 00000/00214/00683
d D 4.30 82/05/22 15:55:21 mckusick 43 41
c break swap() and physio() out of bio.c
e
s 00095/00466/00431
d R 4.30 82/05/12 15:23:29 sam 42 41
c heavily reorganized
e
s 00123/00036/00774
d D 4.29 82/04/19 19:24:17 mckusic 41 40
c merge in the new file system
e
s 00002/00002/00808
d D 4.28 82/03/31 09:04:27 wnj 40 39
c 63k < 65536, but 65k >
e
s 00003/00002/00807
d D 4.27 82/03/26 21:26:49 wnj 39 38
c missing splx(s); raise physio size limit to 65k
e
s 00002/00002/00807
d D 4.26 82/03/13 12:50:00 sam 38 37
c lint
e
s 00019/00014/00790
d D 4.25 82/01/17 20:12:05 root 37 36
c make bio and disk drivers not do spl0 so can call from panic without trap 2's
e
s 00011/00005/00793
d D 4.24 82/01/17 03:57:03 wnj 36 35
c fix up rebooting via spl changes in getblk
e
s 00001/00001/00797
d D 4.23 81/07/25 21:01:43 wnj 35 34
c restore sccs line
e
s 00007/00004/00791
d D 4.22 81/07/25 20:59:50 wnj 34 33
c fixed fsdtodb() spuriously in trace() calls by removing
c added a TR_SWAPIO for green.
e
s 00003/00001/00792
d D 4.21 81/05/08 21:52:33 wnj 33 32
c fix bug in physio which weirded out tape drive
e
s 00002/00001/00791
d D 4.20 81/04/24 00:14:57 wnj 32 31
c count pages paged out
e
s 00001/00001/00791
d D 4.19 81/04/23 22:39:07 wnj 31 30
c fix per mja@cmu
e
s 00015/00015/00777
d D 4.18 81/03/11 18:32:11 wnj 30 29
c fix trace code
e
s 00001/00001/00791
d D 4.17 81/03/09 01:51:56 wnj 29 28
c %G% -> %E%
e
s 00003/00000/00789
d D 4.16 81/03/09 00:32:20 wnj 28 27
c lint
e
s 00005/00003/00784
d D 4.15 81/03/06 10:30:01 wnj 27 26
c uprintf when user procs killed
e
s 00005/00005/00782
d D 4.14 81/02/27 17:49:16 wnj 26 25
c system sized at boot version
e
s 00002/00002/00785
d D 4.13 81/02/26 04:28:30 wnj 25 24
c cosmetic for new config and 750/780
e
s 00005/00002/00782
d D 4.12 81/02/25 22:28:05 wnj 24 23
c dont throw away super-blocks on error
e
s 00003/00001/00781
d D 4.11 81/02/15 12:09:29 kre 23 22
c bootable autoconf version
e
s 00003/00003/00779
d D 4.10 81/02/10 16:06:27 kre 22 21
c first compiling autoconf version
e
s 00007/00005/00775
d D 4.9 81/02/07 15:46:40 kre 21 20
c invalidate buffer cache (correctly, through hash headers)
e
s 00000/00001/00780
d D 4.8 81/02/03 23:11:19 wnj 20 19
c random reference (still) to b_hlink
e
s 00003/00003/00778
d D 4.7 81/02/01 17:59:10 wnj 19 18
c fix to incore()
e
s 00060/00100/00721
d D 4.6 81/01/31 23:41:10 wnj 18 17
c new hashing and buffer queue stuff
e
s 00027/00002/00794
d D 4.5 81/01/28 11:46:37 kre 17 16
c buffer invalidate routine and checks for B_INVAL flag
e
s 00033/00003/00763
d D 4.4 80/12/26 12:22:07 wnj 16 15
c add EPAWNJ tracing
e
s 00004/00002/00762
d D 4.3 80/11/24 12:47:15 bill 15 14
c recover from out of range block numbers
e
s 00001/00001/00763
d D 4.2 80/11/10 00:31:03 bill 14 13
c minor lint
e
s 00000/00000/00764
d D 4.1 80/11/09 16:52:56 bill 13 12
c stamp for 4bsd
e
s 00008/00003/00756
d D 3.12 80/09/16 17:31:47 bill 12 11
c fix bufunhash race condition
e
s 00004/00002/00755
d D 3.11 80/08/24 21:22:30 bill 11 10
c fix race in swap which was crashing system regularly
e
s 00002/00000/00755
d D 3.10 80/07/29 09:14:49 bill 10 9
c new mba stuff
e
s 00001/00000/00754
d D 3.9 80/07/19 19:54:08 bill 9 8
c return in iodone
e
s 00000/00002/00754
d D 3.8 80/06/24 19:27:55 bill 8 7
c no swplo
e
s 00001/00001/00755
d D 3.7 80/06/07 02:44:26 bill 7 6
c %H%->%G%
e
s 00001/00002/00755
d D 3.6 80/05/18 11:30:50 bill 6 5
c lint
e
s 00001/00001/00756
d D 3.5 80/05/15 16:30:00 bill 5 4
c SIGKIL->SIGKILL
e
s 00019/00019/00738
d D 3.4 80/05/08 10:20:21 bill 4 3
c VOID=>void
e
s 00001/00033/00756
d D 3.3 80/04/14 10:00:08 bill 3 2
c remove distrust code and oincore
e
s 00136/00043/00653
d D 3.2 80/04/13 12:19:23 bill 2 1
c first working hashed version
e
s 00696/00000/00000
d D 3.1 80/04/09 16:02:54 bill 1 0
c date and time created 80/04/09 16:02:54 by bill
e
u
U
f b 
t
T
I 1
D 7
/*	%M%	%I%	%H%	*/
E 7
I 7
D 29
/*	%M%	%I%	%G%	*/
E 29
I 29
D 34
/*	%M%	%I%	%E%	*/
E 34
I 34
D 35
/*	bio.c	4.21	81/05/08	*/
E 35
I 35
D 68
/*	%M%	%I%	%E%	*/
E 68
I 68
D 114
/*
D 73
 * Copyright (c) 1982 Regents of the University of California.
E 73
I 73
D 78
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 73
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 78
I 78
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 114
I 114
/*-
D 144
 * Copyright (c) 1982, 1986, 1989 The Regents of the University of California.
E 144
I 144
D 145
 * Copyright (c) 1993 The Regents of the University of California.
E 144
E 114
 * All rights reserved.
E 145
I 145
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 145
E 78
 *
I 78
D 103
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
E 103
I 103
D 114
 * %sccs.include.redist.c%
E 114
I 114
D 115
 * %sccs.include.proprietary.c%
E 115
I 115
D 144
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
E 144
I 144
 * %sccs.include.redist.c%
E 144
E 115
E 114
E 103
 *
E 78
 *	%W% (Berkeley) %G%
 */
E 68
E 35
E 34
E 29
E 7

I 54
D 77
#include "../machine/pte.h"

E 77
E 54
I 41
D 45
/* merged into kernel:	 @(#)bio.c 2.3 4/8/82 */

E 45
E 41
I 2
D 3
int	distrust = 1;		/* TEST */
E 3
E 2
D 67
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/buf.h"
#include "../h/conf.h"
#include "../h/proc.h"
#include "../h/seg.h"
D 54
#include "../h/pte.h"
E 54
#include "../h/vm.h"
I 16
#include "../h/trace.h"
E 67
I 67
D 116
#include "param.h"
D 78
#include "systm.h"
#include "dir.h"
E 78
D 108
#include "user.h"
E 108
I 107
#include "proc.h"
E 107
#include "buf.h"
D 78
#include "conf.h"
#include "proc.h"
#include "seg.h"
#include "vm.h"
E 78
I 78
#include "vnode.h"
I 98
#include "specdev.h"
E 98
I 88
#include "mount.h"
E 88
E 78
#include "trace.h"
I 83
D 108
#include "ucred.h"
E 108
I 108
#include "resourcevar.h"
E 116
I 116
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/vnode.h>
D 132
#include <sys/specdev.h>
E 132
#include <sys/mount.h>
#include <sys/trace.h>
D 144
#include <sys/resourcevar.h>
E 144
I 137
#include <sys/malloc.h>
I 144
#include <sys/resourcevar.h>
E 144
#include <libkern/libkern.h>
I 143
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
E 143
E 137
E 116
E 108
E 83
I 77

I 151
D 154
#ifdef DEBUG
#include <vm/vm.h>
#include <sys/sysctl.h>
int doreallocblks = 1;
struct ctldebug debug13 = { "doreallocblks", &doreallocblks };
#else
/* XXX for cluster_write */
#define doreallocblks 1
#endif

E 154
E 151
D 78
#include "machine/pte.h"
E 77
E 67
E 16

E 78
I 48
D 53
int bioprintfs = 0;

E 53
E 48
I 2
/*
I 137
D 144
 * Definitions for the buffer hash lists.
 */
#define	BUFHASH(dvp, lbn)	\
	(&bufhashtbl[((int)(dvp) / sizeof(*(dvp)) + (int)(lbn)) & bufhash])
D 138
struct	buf **bufhashtbl, *invalhash;
E 138
I 138
struct	list_entry *bufhashtbl, invalhash;
E 138
u_long	bufhash;

/*
 * Insq/Remq for the buffer hash lists.
 */
D 138
#define	bremhash(bp) { \
	struct buf *bq; \
	if (bq = (bp)->b_forw) \
		bq->b_back = (bp)->b_back; \
	*(bp)->b_back = bq; \
}
#define	binshash(bp, dp) { \
	struct buf *bq; \
	if (bq = *(dp)) \
		bq->b_back = &(bp)->b_forw; \
	(bp)->b_forw = bq; \
	(bp)->b_back = (dp); \
	*(dp) = (bp); \
}
E 138
I 138
#define	binshash(bp, dp)	list_enter_head(dp, bp, struct buf *, b_hash)
#define	bremhash(bp)		list_remove(bp, struct buf *, b_hash)
E 138

/*
 * Definitions for the buffer free lists.
 */
#define	BQUEUES		4		/* number of free buffer queues */

#define	BQ_LOCKED	0		/* super-blocks &c */
#define	BQ_LRU		1		/* lru, useful buffers */
#define	BQ_AGE		2		/* rubbish */
#define	BQ_EMPTY	3		/* buffer headers with no memory */

D 138
struct bufqueue {
	struct	buf *buffreehead;	/* head of available list */
	struct	buf **buffreetail;	/* tail of available list */
} bufqueues[BQUEUES];
E 138
I 138
struct queue_entry bufqueues[BQUEUES];
E 138
int needbuffer;

/*
 * Insq/Remq for the buffer free lists.
 */
I 138
#define	binsheadfree(bp, dp) \
	queue_enter_head(dp, bp, struct buf *, b_freelist)
#define	binstailfree(bp, dp) \
	queue_enter_tail(dp, bp, struct buf *, b_freelist)

I 140
/*
E 144
 * Local declarations
 */
struct buf *cluster_newbuf __P((struct vnode *, struct buf *, long, daddr_t,
	    daddr_t, long, int));
struct buf *cluster_rbuild __P((struct vnode *, u_quad_t, struct buf *,
	    daddr_t, daddr_t, long, int, long));
D 147
void	    cluster_wbuild __P((struct vnode *, struct buf *, long size,
	    daddr_t start_lbn, int len, daddr_t lbn));
E 147
I 147
void	    cluster_wbuild __P((struct vnode *, struct buf *, long,
	    daddr_t, int, daddr_t));
I 150
struct cluster_save *cluster_collectbufs __P((struct vnode *, struct buf *));
E 150
E 147

I 149
#ifdef DIAGNOSTIC
E 149
E 140
E 138
D 144
void
bremfree(bp)
	struct buf *bp;
{
D 138
	struct buf *bq;
	struct bufqueue *dp;
E 138
I 138
	struct queue_entry *dp;
E 138

D 138
	if (bq = bp->b_actf) {
		bq->b_actb = bp->b_actb;
	} else {
E 138
I 138
	/*
	 * We only calculate the head of the freelist when removing
	 * the last element of the list as that is the only time that
	 * it is needed (e.g. to reset the tail pointer).
	 */
	if (bp->b_freelist.qe_next == NULL) {
E 138
		for (dp = bufqueues; dp < &bufqueues[BQUEUES]; dp++)
D 138
			if (dp->buffreetail == &bp->b_actf)
E 138
I 138
			if (dp->qe_prev == &bp->b_freelist.qe_next)
E 138
				break;
		if (dp == &bufqueues[BQUEUES])
			panic("bremfree: lost tail");
D 138
		dp->buffreetail = bp->b_actb;
E 138
	}
D 138
	*bp->b_actb = bq;
E 138
I 138
	queue_remove(dp, bp, struct buf *, b_freelist);
E 138
}

E 144
D 138
#define	binsheadfree(bp, dp) { \
	struct buf *bq; \
	if (bq = (dp)->buffreehead) \
		bq->b_actb = &(bp)->b_actf; \
	else \
		(dp)->buffreetail = &(bp)->b_actf; \
	(dp)->buffreehead = (bp); \
	(bp)->b_actf = bq; \
	(bp)->b_actb = &(dp)->buffreehead; \
}
#define	binstailfree(bp, dp) { \
	(bp)->b_actf = NULL; \
	(bp)->b_actb = (dp)->buffreetail; \
	*(dp)->buffreetail = (bp); \
	(dp)->buffreetail = &(bp)->b_actf; \
}

E 138
/*
E 137
I 112
D 144
 * Initialize buffers and hash links for buffers.
 */
I 116
void
E 116
bufinit()
{
I 137
	register struct buf *bp;
D 138
	struct bufqueue *dp;
E 138
I 138
	struct queue_entry *dp;
E 138
E 137
	register int i;
D 137
	register struct buf *bp, *dp;
	register struct bufhd *hp;
E 137
	int base, residual;

D 137
	for (hp = bufhash, i = 0; i < BUFHSZ; i++, hp++)
		hp->b_forw = hp->b_back = (struct buf *)hp;

	for (dp = bfreelist; dp < &bfreelist[BQUEUES]; dp++) {
		dp->b_forw = dp->b_back = dp->av_forw = dp->av_back = dp;
		dp->b_flags = B_HEAD;
	}
E 137
I 137
	for (dp = bufqueues; dp < &bufqueues[BQUEUES]; dp++)
D 138
		dp->buffreetail = &dp->buffreehead;
	bufhashtbl = (struct buf **)hashinit(nbuf, M_CACHE, &bufhash);
E 138
I 138
		queue_init(dp);
	bufhashtbl = (struct list_entry *)hashinit(nbuf, M_CACHE, &bufhash);
E 138
E 137
	base = bufpages / nbuf;
	residual = bufpages % nbuf;
	for (i = 0; i < nbuf; i++) {
		bp = &buf[i];
I 137
		bzero((char *)bp, sizeof *bp);
E 137
		bp->b_dev = NODEV;
D 137
		bp->b_bcount = 0;
E 137
		bp->b_rcred = NOCRED;
		bp->b_wcred = NOCRED;
D 137
		bp->b_dirtyoff = 0;
		bp->b_dirtyend = 0;
I 118
		bp->b_validoff = 0;
		bp->b_validend = 0;
E 137
E 118
		bp->b_un.b_addr = buffers + i * MAXBSIZE;
		if (i < residual)
			bp->b_bufsize = (base + 1) * CLBYTES;
		else
			bp->b_bufsize = base * CLBYTES;
D 137
		binshash(bp, &bfreelist[BQ_AGE]);
E 137
D 119
		bp->b_flags = B_BUSY|B_INVAL;
		brelse(bp);
E 119
I 119
		bp->b_flags = B_INVAL;
D 137
		dp = bp->b_bufsize ? &bfreelist[BQ_AGE] : &bfreelist[BQ_EMPTY];
E 137
I 137
		dp = bp->b_bufsize ? &bufqueues[BQ_AGE] : &bufqueues[BQ_EMPTY];
E 137
		binsheadfree(bp, dp);
I 137
		binshash(bp, &invalhash);
E 137
E 119
	}
}

/*
E 112
D 45
 * The following several routines allocate and free
 * buffers with various side effects.  In general the
 * arguments to an allocate routine are a device and
 * a block number, and the value is a pointer to
 * to the buffer header; the buffer is marked "busy"
 * so that no one else can touch it.  If the block was
 * already in core, no I/O need be done; if it is
 * already busy, the process waits until it becomes free.
 * The following routines allocate a buffer:
 *	getblk
 *	bread
 *	breada
 *	baddr	(if it is incore)
 * Eventually the buffer must be released, possibly with the
 * side effect of writing it out, by using one of
 *	bwrite
 *	bdwrite
 *	bawrite
 *	brelse
 */

I 28
struct	buf bfreelist[BQUEUES];
struct	buf bswlist, *bclnlist;

E 28
#define	BUFHSZ	63
I 41
#define RND	(MAXBSIZE/DEV_BSIZE)
E 41
D 18
#define	BUFHASH(blkno)	(blkno % BUFHSZ)
short	bufhash[BUFHSZ];
E 18
I 18
struct	bufhd bufhash[BUFHSZ];
D 19
#define	BUFHASH(dev,blkno)	\
		((struct buf *)&bufhash[((int)dev+(int)blkno) % BUFHSZ])
E 19
I 19
#define	BUFHASH(dev, dblkno)	\
D 41
		((struct buf *)&bufhash[((int)(dev)+(int)(dblkno)) % BUFHSZ])
E 41
I 41
	((struct buf *)&bufhash[((int)(dev)+(((int)(dblkno))/RND)) % BUFHSZ])
E 41
E 19
E 18

/*
 * Initialize hash links for buffers.
 */
bhinit()
{
	register int i;
I 18
	register struct bufhd *bp;
E 18

D 18
	for (i = 0; i < BUFHSZ; i++)
		bufhash[i] = -1;
E 18
I 18
	for (bp = bufhash, i = 0; i < BUFHSZ; i++, bp++)
		bp->b_forw = bp->b_back = (struct buf *)bp;
E 18
}

E 2
/* #define	DISKMON	1 */

#ifdef	DISKMON
struct {
	int	nbuf;
	long	nread;
	long	nreada;
	long	ncache;
	long	nwrite;
D 26
	long	bufcount[NBUF];
E 26
I 26
	long	bufcount[64];
E 26
} io_info;
#endif

/*
D 43
 * Swap IO headers -
 * They contain the necessary information for the swap I/O.
 * At any given time, a swap header can be in three
 * different lists. When free it is in the free list, 
 * when allocated and the I/O queued, it is on the swap 
 * device list, and finally, if the operation was a dirty 
 * page push, when the I/O completes, it is inserted 
 * in a list of cleaned pages to be processed by the pageout daemon.
 */
D 26
struct	buf swbuf[NSWBUF];
short	swsize[NSWBUF];		/* CAN WE JUST USE B_BCOUNT? */
int	swpf[NSWBUF];
E 26
I 26
struct	buf *swbuf;
short	*swsize;		/* CAN WE JUST USE B_BCOUNT? */
int	*swpf;
E 43
E 26

D 2
/*
 * The following several routines allocate and free
 * buffers with various side effects.  In general the
 * arguments to an allocate routine are a device and
 * a block number, and the value is a pointer to
 * to the buffer header; the buffer is marked "busy"
 * so that no one else can touch it.  If the block was
 * already in core, no I/O need be done; if it is
 * already busy, the process waits until it becomes free.
 * The following routines allocate a buffer:
 *	getblk
 *	bread
 *	breada
 *	baddr	(if it is incore)
 * Eventually the buffer must be released, possibly with the
 * side effect of writing it out, by using one of
 *	bwrite
 *	bdwrite
 *	bawrite
 *	brelse
 */
E 2
D 43

E 43
D 25
#ifdef	FASTVAX
E 25
I 25
#ifndef	UNFAST
E 25
#define	notavail(bp) \
{ \
D 38
	int s = spl6(); \
E 38
I 38
	int x = spl6(); \
E 38
	(bp)->av_back->av_forw = (bp)->av_forw; \
	(bp)->av_forw->av_back = (bp)->av_back; \
	(bp)->b_flags |= B_BUSY; \
D 38
	splx(s); \
E 38
I 38
	splx(x); \
E 38
}
#endif

/*
E 45
D 105
 * Read in (if necessary) the block and return a buffer pointer.
E 105
I 105
 * Find the block in the buffer pool.
 * If the buffer is not present, allocate a new buffer and load
 * its contents according to the filesystem fill routine.
E 105
 */
D 78
struct buf *
I 74
#ifdef SECSIZE
bread(dev, blkno, size, secsize)
#else SECSIZE
E 74
D 41
bread(dev, blkno)
dev_t dev;
daddr_t blkno;
E 41
I 41
bread(dev, blkno, size)
I 74
#endif SECSIZE
E 74
	dev_t dev;
E 78
I 78
D 83
bread(vp, blkno, size, bpp)
E 83
I 83
bread(vp, blkno, size, cred, bpp)
E 83
	struct vnode *vp;
E 78
	daddr_t blkno;
	int size;
I 83
	struct ucred *cred;
E 83
I 78
	struct buf **bpp;
E 78
I 74
#ifdef SECSIZE
	long secsize;
#endif SECSIZE
E 74
E 41
{
I 128
D 131
	USES_VOP_STRATEGY;
E 131
E 128
I 107
	struct proc *p = curproc;		/* XXX */
E 107
	register struct buf *bp;

I 53
	if (size == 0)
		panic("bread: size 0");
I 74
#ifdef SECSIZE
	bp = getblk(dev, blkno, size, secsize);
#else SECSIZE
E 74
E 53
D 41
	bp = getblk(dev, blkno);
E 41
I 41
D 78
	bp = getblk(dev, blkno, size);
E 78
I 78
D 141
	*bpp = bp = getblk(vp, blkno, size);
E 141
I 141
	*bpp = bp = getblk(vp, blkno, size, 0, 0);
E 141
E 78
I 74
#endif SECSIZE
E 74
E 41
D 76
	if (bp->b_flags&B_DONE) {
E 76
I 76
D 105
	if (bp->b_flags&(B_DONE|B_DELWRI)) {
E 105
I 105
	if (bp->b_flags & (B_DONE | B_DELWRI)) {
E 105
E 76
I 16
D 30
#ifdef	EPAWNJ
		trace(TR_BREAD|TR_HIT, dev, blkno);
E 30
I 30
D 45
#ifdef	TRACE
E 45
D 65
		trace(TR_BREADHIT, dev, blkno);
E 65
I 65
D 78
		trace(TR_BREADHIT, pack(dev, size), blkno);
E 65
E 30
D 45
#endif
E 16
#ifdef	DISKMON
		io_info.ncache++;
#endif
E 45
D 72
		return(bp);
E 72
I 72
		return (bp);
E 78
I 78
D 96
		trace(TR_BREADHIT, pack(vp->v_mount->m_fsid[0], size), blkno);
E 96
I 96
		trace(TR_BREADHIT, pack(vp, size), blkno);
E 96
		return (0);
E 78
E 72
	}
	bp->b_flags |= B_READ;
I 53
	if (bp->b_bcount > bp->b_bufsize)
		panic("bread");
I 83
	if (bp->b_rcred == NOCRED && cred != NOCRED) {
		crhold(cred);
		bp->b_rcred = cred;
	}
E 83
E 53
D 41
	bp->b_bcount = BSIZE;
E 41
D 78
	(*bdevsw[major(dev)].d_strategy)(bp);
I 16
D 30
#ifdef	EPAWNJ
	trace(TR_BREAD|TR_MISS, dev, blkno);
E 30
I 30
D 45
#ifdef	TRACE
E 45
D 65
	trace(TR_BREADMISS, dev, blkno);
E 65
I 65
	trace(TR_BREADMISS, pack(dev, size), blkno);
E 78
I 78
	VOP_STRATEGY(bp);
D 96
	trace(TR_BREADMISS, pack(vp->v_mount->m_fsid[0], size), blkno);
E 96
I 96
	trace(TR_BREADMISS, pack(vp, size), blkno);
E 96
E 78
E 65
E 30
D 45
#endif
E 16
#ifdef	DISKMON
	io_info.nread++;
#endif
E 45
D 50
	u.u_vm.vm_inblk++;		/* pay for read */
E 50
I 50
D 107
	u.u_ru.ru_inblock++;		/* pay for read */
E 107
I 107
	p->p_stats->p_ru.ru_inblock++;		/* pay for read */
E 107
E 50
D 45
	iowait(bp);
E 45
I 45
D 78
	biowait(bp);
E 45
D 72
	return(bp);
E 72
I 72
	return (bp);
E 78
I 78
	return (biowait(bp));
E 78
E 72
}

/*
D 105
 * Read in the block, like bread, but also start I/O on the
 * read-ahead block (which is not allocated to the caller)
E 105
I 105
D 118
 * Operates like bread, but also starts I/O on the specified
 * read-ahead block.
E 118
I 118
 * Operates like bread, but also starts I/O on the N specified
 * read-ahead blocks.
E 118
E 105
 */
D 78
struct buf *
I 74
#ifdef SECSIZE
breada(dev, blkno, size, secsize, rablkno, rabsize)
#else SECSIZE
E 74
D 41
breada(dev, blkno, rablkno)
dev_t dev;
daddr_t blkno, rablkno;
E 41
I 41
D 47
breada(dev, blkno, rablkno, size)
E 47
I 47
D 51
breada(dev, blkno, size, rablkno, rasize)
E 51
I 51
breada(dev, blkno, size, rablkno, rabsize)
I 74
#endif SECSIZE
E 74
E 51
E 47
	dev_t dev;
E 78
I 78
D 83
breada(vp, blkno, size, rablkno, rabsize, bpp)
E 83
I 83
D 118
breada(vp, blkno, size, rablkno, rabsize, cred, bpp)
E 118
I 118
breadn(vp, blkno, size, rablkno, rabsize, num, cred, bpp)
E 118
E 83
	struct vnode *vp;
E 78
D 47
	daddr_t blkno, rablkno;
	int size;
E 47
I 47
	daddr_t blkno; int size;
I 74
#ifdef SECSIZE
	long secsize;
#endif SECSIZE
E 74
D 51
	daddr_t rablkno; int rasize;
E 51
I 51
D 118
	daddr_t rablkno; int rabsize;
E 118
I 118
	daddr_t rablkno[]; int rabsize[];
	int num;
E 118
I 83
	struct ucred *cred;
E 83
I 78
	struct buf **bpp;
E 78
E 51
E 47
E 41
{
I 128
D 131
	USES_VOP_STRATEGY;
E 131
E 128
I 107
	struct proc *p = curproc;		/* XXX */
E 107
	register struct buf *bp, *rabp;
I 118
	register int i;
E 118

	bp = NULL;
I 45
	/*
D 105
	 * If the block isn't in core, then allocate
	 * a buffer and initiate i/o (getblk checks
	 * for a cache hit).
E 105
I 105
	 * If the block is not memory resident,
	 * allocate a buffer and start I/O.
E 105
	 */
E 45
D 78
	if (!incore(dev, blkno)) {
I 74
#ifdef SECSIZE
		bp = getblk(dev, blkno, size, secsize);
#else SECSIZE
E 74
D 41
		bp = getblk(dev, blkno);
E 41
I 41
		bp = getblk(dev, blkno, size);
E 78
I 78
	if (!incore(vp, blkno)) {
D 141
		*bpp = bp = getblk(vp, blkno, size);
E 141
I 141
		*bpp = bp = getblk(vp, blkno, size, 0, 0);
E 141
E 78
I 74
#endif SECSIZE
E 74
E 41
D 76
		if ((bp->b_flags&B_DONE) == 0) {
E 76
I 76
D 105
		if ((bp->b_flags&(B_DONE|B_DELWRI)) == 0) {
E 105
I 105
		if ((bp->b_flags & (B_DONE | B_DELWRI)) == 0) {
E 105
E 76
			bp->b_flags |= B_READ;
I 53
			if (bp->b_bcount > bp->b_bufsize)
D 118
				panic("breada");
E 118
I 118
				panic("breadn");
E 118
I 83
			if (bp->b_rcred == NOCRED && cred != NOCRED) {
				crhold(cred);
				bp->b_rcred = cred;
			}
E 83
E 53
D 41
			bp->b_bcount = BSIZE;
E 41
D 78
			(*bdevsw[major(dev)].d_strategy)(bp);
I 16
D 30
#ifdef	EPAWNJ
			trace(TR_BREAD|TR_MISS, dev, blkno);
E 30
I 30
D 45
#ifdef	TRACE
E 45
D 65
			trace(TR_BREADMISS, dev, blkno);
E 65
I 65
			trace(TR_BREADMISS, pack(dev, size), blkno);
E 78
I 78
			VOP_STRATEGY(bp);
D 96
			trace(TR_BREADMISS, pack(vp->v_mount->m_fsid[0], size),
			    blkno);
E 96
I 96
			trace(TR_BREADMISS, pack(vp, size), blkno);
E 96
E 78
E 65
E 30
D 45
#endif
E 16
#ifdef	DISKMON
			io_info.nread++;
#endif
E 45
D 50
			u.u_vm.vm_inblk++;		/* pay for read */
E 50
I 50
D 107
			u.u_ru.ru_inblock++;		/* pay for read */
E 107
I 107
			p->p_stats->p_ru.ru_inblock++;	/* pay for read */
E 107
E 50
D 45
		}
I 16
D 30
#ifdef	EPAWNJ
E 30
I 30
#ifdef	TRACE
E 30
		else
E 45
I 45
D 130
		} else
E 130
I 130
		} else {
E 130
E 45
D 30
			trace(TR_BREAD|TR_HIT, dev, blkno);
E 30
I 30
D 65
			trace(TR_BREADHIT, dev, blkno);
E 65
I 65
D 78
			trace(TR_BREADHIT, pack(dev, size), blkno);
E 78
I 78
D 96
			trace(TR_BREADHIT, pack(vp->v_mount->m_fsid[0], size),
			    blkno);
E 96
I 96
			trace(TR_BREADHIT, pack(vp, size), blkno);
I 130
		}
E 130
E 96
E 78
E 65
E 30
D 45
#endif
E 45
E 16
	}
I 45

	/*
D 105
	 * If there's a read-ahead block, start i/o
	 * on it also (as above).
E 105
I 105
D 118
	 * If there is a read-ahead block, start I/O on it too.
E 118
I 118
	 * If there's read-ahead block(s), start I/O
	 * on them also (as above).
E 118
E 105
	 */
E 45
D 78
	if (rablkno && !incore(dev, rablkno)) {
I 74
#ifdef SECSIZE
		rabp = getblk(dev, rablkno, rabsize, secsize);
#else SECSIZE
E 74
D 41
		rabp = getblk(dev, rablkno);
E 41
I 41
D 47
		rabp = getblk(dev, rablkno, size);
E 47
I 47
D 51
		rabp = getblk(dev, rablkno, rasize);
E 51
I 51
		rabp = getblk(dev, rablkno, rabsize);
E 78
I 78
D 93
	if (rablkno && !incore(vp, rablkno)) {
E 93
I 93
D 118
	if (!incore(vp, rablkno)) {
E 93
		rabp = getblk(vp, rablkno, rabsize);
E 118
I 118
	for (i = 0; i < num; i++) {
		if (incore(vp, rablkno[i]))
			continue;
D 141
		rabp = getblk(vp, rablkno[i], rabsize[i]);
E 141
I 141
		rabp = getblk(vp, rablkno[i], rabsize[i], 0, 0);
E 141
E 118
E 78
I 74
#endif SECSIZE
E 74
E 51
E 47
E 41
D 16
		if (rabp->b_flags & B_DONE)
E 16
I 16
D 76
		if (rabp->b_flags & B_DONE) {
E 76
I 76
D 105
		if (rabp->b_flags & (B_DONE|B_DELWRI)) {
E 105
I 105
		if (rabp->b_flags & (B_DONE | B_DELWRI)) {
E 105
E 76
E 16
			brelse(rabp);
D 16
		else {
E 16
I 16
D 30
#ifdef	EPAWNJ
			trace(TR_BREAD|TR_HIT|TR_RA, dev, blkno);
E 30
I 30
D 45
#ifdef	TRACE
E 45
D 65
			trace(TR_BREADHITRA, dev, blkno);
E 65
I 65
D 78
			trace(TR_BREADHITRA, pack(dev, rabsize), blkno);
E 78
I 78
D 96
			trace(TR_BREADHITRA,
D 85
			    pack(vp->v_mount->m_fsid[0], rabsize), blkno);
E 85
I 85
			    pack(vp->v_mount->m_fsid[0], rabsize), rablkno);
E 96
I 96
D 118
			trace(TR_BREADHITRA, pack(vp, rabsize), rablkno);
E 118
I 118
			trace(TR_BREADHITRA, pack(vp, rabsize[i]), rablkno[i]);
E 118
E 96
E 85
E 78
E 65
E 30
D 45
#endif
E 45
		} else {
E 16
D 105
			rabp->b_flags |= B_READ|B_ASYNC;
E 105
I 105
			rabp->b_flags |= B_ASYNC | B_READ;
E 105
I 53
			if (rabp->b_bcount > rabp->b_bufsize)
				panic("breadrabp");
I 83
D 85
			if (bp->b_rcred == NOCRED && cred != NOCRED) {
E 85
I 85
			if (rabp->b_rcred == NOCRED && cred != NOCRED) {
E 85
				crhold(cred);
D 85
				bp->b_rcred = cred;
E 85
I 85
				rabp->b_rcred = cred;
E 85
			}
E 83
E 53
D 41
			rabp->b_bcount = BSIZE;
E 41
D 78
			(*bdevsw[major(dev)].d_strategy)(rabp);
I 16
D 30
#ifdef	EPAWNJ
			trace(TR_BREAD|TR_MISS|TR_RA, dev, rablock);
E 30
I 30
D 45
#ifdef	TRACE
E 45
D 65
			trace(TR_BREADMISSRA, dev, rablock);
E 65
I 65
			trace(TR_BREADMISSRA, pack(dev, rabsize), rablock);
E 78
I 78
			VOP_STRATEGY(rabp);
D 96
			trace(TR_BREADMISSRA,
D 85
			    pack(vp->v_mount->m_fsid[0], rabsize), rablock);
E 85
I 85
			    pack(vp->v_mount->m_fsid[0], rabsize), rablkno);
E 96
I 96
D 118
			trace(TR_BREADMISSRA, pack(vp, rabsize), rablkno);
E 118
I 118
			trace(TR_BREADMISSRA, pack(vp, rabsize[i]), rablkno[i]);
E 118
E 96
E 85
E 78
E 65
E 30
D 45
#endif
E 16
#ifdef	DISKMON
			io_info.nreada++;
#endif
E 45
D 50
			u.u_vm.vm_inblk++;		/* pay in advance */
E 50
I 50
D 107
			u.u_ru.ru_inblock++;		/* pay in advance */
E 107
I 107
			p->p_stats->p_ru.ru_inblock++;	/* pay in advance */
E 107
E 50
		}
	}
I 45

	/*
D 47
	 * If we get here with bp NULL, then the block
	 * must've been in core and bread will find it for us.
E 47
I 47
D 105
	 * If block was in core, let bread get it.
	 * If block wasn't in core, then the read was started
	 * above, and just wait for it.
E 105
I 105
	 * If block was memory resident, let bread get it.
	 * If block was not memory resident, the read was
	 * started above, so just wait for the read to complete.
E 105
E 47
	 */
E 45
D 47
	if(bp == NULL)
D 41
		return(bread(dev, blkno));
E 41
I 41
		return(bread(dev, blkno, size));
E 47
I 47
	if (bp == NULL)
I 74
#ifdef SECSIZE
		return (bread(dev, blkno, size, secsize));
#else SECSIZE
E 74
D 78
		return (bread(dev, blkno, size));
I 74
#endif SECSIZE
E 74
E 47
E 41
D 45
	iowait(bp);
E 45
I 45
	biowait(bp);
E 45
D 47
	return(bp);
E 47
I 47
	return (bp);
E 78
I 78
D 83
		return (bread(vp, blkno, size, bpp));
E 83
I 83
		return (bread(vp, blkno, size, cred, bpp));
E 83
	return (biowait(bp));
E 78
E 47
}

/*
E 144
I 140
D 149
 * We could optimize this by keeping track of where the last read-ahead
 * was, but it would involve adding fields to the vnode.  For now, let's
 * just get it working.
E 149
I 149
 * Set to 1 if reads of block zero should cause readahead to be done.
 * Set to 0 treats a read of block zero as a non-sequential read.
E 149
 *
I 149
 * Setting to one assumes that most reads of block zero of files are due to
 * sequential passes over the files (e.g. cat, sum) where additional blocks
 * will soon be needed.  Setting to zero assumes that the majority are
 * surgical strikes to get particular info (e.g. size, file) where readahead
 * blocks will not be used and, in fact, push out other potentially useful
 * blocks from the cache.  The former seems intuitive, but some quick tests
 * showed that the latter performed better from a system-wide point of view.
 */
int	doclusterraz = 0;
#define ISSEQREAD(vp, blk) \
	(((blk) != 0 || doclusterraz) && \
	 ((blk) == (vp)->v_lastr + 1 || (blk) == (vp)->v_lastr))
#else
#define ISSEQREAD(vp, blk) \
	((blk) != 0 && ((blk) == (vp)->v_lastr + 1 || (blk) == (vp)->v_lastr))
#endif

/*
E 149
 * This replaces bread.  If this is a bread at the beginning of a file and
 * lastr is 0, we assume this is the first read and we'll read up to two
 * blocks if they are sequential.  After that, we'll do regular read ahead
 * in clustered chunks.
 *
 * There are 4 or 5 cases depending on how you count:
 *	Desired block is in the cache:
 *	    1 Not sequential access (0 I/Os).
 *	    2 Access is sequential, do read-ahead (1 ASYNC).
 *	Desired block is not in cache:
 *	    3 Not sequential access (1 SYNC).
 *	    4 Sequential access, next block is contiguous (1 SYNC).
 *	    5 Sequential access, next block is not contiguous (1 SYNC, 1 ASYNC)
 *
 * There are potentially two buffers that require I/O.
 * 	bp is the block requested.
 *	rbp is the read-ahead block.
 *	If either is NULL, then you don't have to do the I/O.
 */
cluster_read(vp, filesize, lblkno, size, cred, bpp)
	struct vnode *vp;
	u_quad_t filesize;
	daddr_t lblkno;
	long size;
	struct ucred *cred;
	struct buf **bpp;
{
	struct buf *bp, *rbp;
	daddr_t blkno, ioblkno;
	long flags;
	int error, num_ra, alreadyincore;

#ifdef DIAGNOSTIC
	if (size == 0)
		panic("cluster_read: size = 0");
#endif

	error = 0;
	flags = B_READ;
D 141
	*bpp = bp = getblk(vp, lblkno, size);
E 141
I 141
	*bpp = bp = getblk(vp, lblkno, size, 0, 0);
E 141
D 149
	if (bp->b_flags & (B_CACHE | B_DONE | B_DELWRI)) {
E 149
I 149
	if (bp->b_flags & B_CACHE) {
E 149
		/*
		 * Desired block is in cache; do any readahead ASYNC.
		 * Case 1, 2.
		 */
		trace(TR_BREADHIT, pack(vp, size), lblkno);
		flags |= B_ASYNC;
D 149
		ioblkno = lblkno +
		    (lblkno < vp->v_ralen ? vp->v_ralen >> 1 : vp->v_ralen);
E 149
I 149
		ioblkno = lblkno + (vp->v_ralen ? vp->v_ralen : 1);
E 149
D 141
		alreadyincore = incore(vp, ioblkno);
E 141
I 141
D 153
		alreadyincore = (int)incore(vp, ioblkno);
E 153
I 153
		alreadyincore = incore(vp, ioblkno) != NULL;
E 153
E 141
		bp = NULL;
	} else {
		/* Block wasn't in cache, case 3, 4, 5. */
		trace(TR_BREADMISS, pack(vp, size), lblkno);
I 149
		bp->b_flags |= B_READ;
E 149
		ioblkno = lblkno;
D 149
		bp->b_flags |= flags;
E 149
		alreadyincore = 0;
		curproc->p_stats->p_ru.ru_inblock++;		/* XXX */
	}
	/*
	 * XXX
	 * Replace 1 with a window size based on some permutation of
	 * maxcontig and rot_delay.  This will let you figure out how
	 * many blocks you should read-ahead (case 2, 4, 5).
	 *
D 149
	 * If the access isn't sequential, cut the window size in half.
E 149
I 149
	 * If the access isn't sequential, reset the window to 1.
	 * Note that a read to the same block is considered sequential.
	 * This catches the case where the file is being read sequentially,
	 * but at smaller than the filesystem block size.
E 149
	 */
	rbp = NULL;
D 149
	if (lblkno != vp->v_lastr + 1 && lblkno != 0)
		vp->v_ralen = max(vp->v_ralen >> 1, 1);
	else if ((ioblkno + 1) * size < filesize && !alreadyincore &&
E 149
I 149
	if (!ISSEQREAD(vp, lblkno)) {
		vp->v_ralen = 0;
		vp->v_maxra = lblkno;
	} else if ((ioblkno + 1) * size <= filesize && !alreadyincore &&
E 149
D 147
	    !(error = VOP_BMAP(vp, ioblkno, NULL, &blkno, &num_ra))) {
E 147
I 147
	    !(error = VOP_BMAP(vp, ioblkno, NULL, &blkno, &num_ra)) &&
	    blkno != -1) {
E 147
		/*
		 * Reading sequentially, and the next block is not in the
D 149
		 * cache.  We are going to try reading ahead. If this is
		 * the first read of a file, then limit read-ahead to a
		 * single block, else read as much as we're allowed.
E 149
I 149
		 * cache.  We are going to try reading ahead.
E 149
		 */
D 149
		if (num_ra > vp->v_ralen) {
			num_ra = vp->v_ralen;
			vp->v_ralen = min(MAXPHYS / size, vp->v_ralen << 1);
		} else 
			vp->v_ralen = num_ra + 1;
E 149
I 149
		if (num_ra) {
			/*
			 * If our desired readahead block had been read
			 * in a previous readahead but is no longer in
			 * core, then we may be reading ahead too far
			 * or are not using our readahead very rapidly.
			 * In this case we scale back the window.
			 */
			if (!alreadyincore && ioblkno <= vp->v_maxra)
				vp->v_ralen = max(vp->v_ralen >> 1, 1);
			/*
			 * There are more sequential blocks than our current
			 * window allows, scale up.  Ideally we want to get
			 * in sync with the filesystem maxcontig value.
			 */
			else if (num_ra > vp->v_ralen && lblkno != vp->v_lastr)
				vp->v_ralen = vp->v_ralen ?
					min(num_ra, vp->v_ralen << 1) : 1;
E 149

I 149
			if (num_ra > vp->v_ralen)
				num_ra = vp->v_ralen;
		}
E 149

		if (num_ra)				/* case 2, 4 */
			rbp = cluster_rbuild(vp, filesize,
			    bp, ioblkno, blkno, size, num_ra, flags);
D 149
		else if (lblkno != 0 && ioblkno == lblkno) {
E 149
I 149
		else if (ioblkno == lblkno) {
			bp->b_blkno = blkno;
E 149
			/* Case 5: check how many blocks to read ahead */
			++ioblkno;
			if ((ioblkno + 1) * size > filesize ||
D 147
			    (error = VOP_BMAP(vp,
			    ioblkno, NULL, &blkno, &num_ra)))
E 147
I 147
D 149
			    (error = VOP_BMAP(vp, ioblkno, NULL, &blkno,
			    &num_ra)) || blkno == -1)
E 149
I 149
			    incore(vp, ioblkno) || (error = VOP_BMAP(vp,
			     ioblkno, NULL, &blkno, &num_ra)) || blkno == -1)
E 149
E 147
				goto skip_readahead;
I 149
			/*
D 152
			 * Adjust readahead as above
E 152
I 152
			 * Adjust readahead as above.
			 * Don't check alreadyincore, we know it is 0 from
			 * the previous conditional.
E 152
			 */
			if (num_ra) {
D 152
				if (!alreadyincore && ioblkno <= vp->v_maxra)
E 152
I 152
				if (ioblkno <= vp->v_maxra)
E 152
					vp->v_ralen = max(vp->v_ralen >> 1, 1);
				else if (num_ra > vp->v_ralen &&
					 lblkno != vp->v_lastr)
					vp->v_ralen = vp->v_ralen ?
						min(num_ra,vp->v_ralen<<1) : 1;
				if (num_ra > vp->v_ralen)
					num_ra = vp->v_ralen;
			}
E 149
			flags |= B_ASYNC;
			if (num_ra)
				rbp = cluster_rbuild(vp, filesize,
				    NULL, ioblkno, blkno, size, num_ra, flags);
			else {
D 141
				rbp = getblk(vp, ioblkno, size);
E 141
I 141
				rbp = getblk(vp, ioblkno, size, 0, 0);
E 141
				rbp->b_flags |= flags;
				rbp->b_blkno = blkno;
			}
D 149
		} else if (lblkno != 0) {
E 149
I 149
		} else {
E 149
			/* case 2; read ahead single block */
D 141
			rbp = getblk(vp, ioblkno, size);
E 141
I 141
			rbp = getblk(vp, ioblkno, size, 0, 0);
E 141
			rbp->b_flags |= flags;
			rbp->b_blkno = blkno;
D 149
		} else if (bp)				/* case 1, 3, block 0 */
			bp->b_blkno = blkno;
		/* Case 1 on block 0; not really doing sequential I/O */
E 149
I 149
		}
E 149

D 149
		if (rbp == bp)		/* case 4 */
E 149
I 149
		if (rbp == bp)			/* case 4 */
E 149
			rbp = NULL;
		else if (rbp) {			/* case 2, 5 */
			trace(TR_BREADMISSRA,
			    pack(vp, (num_ra + 1) * size), ioblkno);
			curproc->p_stats->p_ru.ru_inblock++;	/* XXX */
		}
	}

	/* XXX Kirk, do we need to make sure the bp has creds? */
skip_readahead:
	if (bp)
		if (bp->b_flags & (B_DONE | B_DELWRI))
			panic("cluster_read: DONE bp");
		else 
			error = VOP_STRATEGY(bp);

	if (rbp)
		if (error || rbp->b_flags & (B_DONE | B_DELWRI)) {
			rbp->b_flags &= ~(B_ASYNC | B_READ);
			brelse(rbp);
		} else
			(void) VOP_STRATEGY(rbp);

I 149
	/*
	 * Recalculate our maximum readahead
	 */
	if (rbp == NULL)
		rbp = bp;
	if (rbp)
		vp->v_maxra = rbp->b_lblkno + (rbp->b_bufsize / size) - 1;

E 149
	if (bp)
		return(biowait(bp));
	return(error);
}

/*
 * If blocks are contiguous on disk, use this to provide clustered
 * read ahead.  We will read as many blocks as possible sequentially
 * and then parcel them up into logical blocks in the buffer hash table.
 */
struct buf *
cluster_rbuild(vp, filesize, bp, lbn, blkno, size, run, flags)
	struct vnode *vp;
	u_quad_t filesize;
	struct buf *bp;
	daddr_t lbn;
	daddr_t blkno;
	long size;
	int run;
	long flags;
{
	struct cluster_save *b_save;
	struct buf *tbp;
	daddr_t bn;
	int i, inc;

I 142
#ifdef DIAGNOSTIC
	if (size != vp->v_mount->mnt_stat.f_iosize)
		panic("cluster_rbuild: size %d != filesize %d\n",
			size, vp->v_mount->mnt_stat.f_iosize);
#endif
E 142
	if (size * (lbn + run + 1) > filesize)
		--run;
	if (run == 0) {
		if (!bp) {
D 141
			bp = getblk(vp, lbn, size);
E 141
I 141
			bp = getblk(vp, lbn, size, 0, 0);
E 141
			bp->b_blkno = blkno;
			bp->b_flags |= flags;
		}
		return(bp);
	}

	bp = cluster_newbuf(vp, bp, flags, blkno, lbn, size, run + 1);
	if (bp->b_flags & (B_DONE | B_DELWRI))
		return (bp);

	b_save = malloc(sizeof(struct buf *) * run + sizeof(struct cluster_save),
	    M_SEGMENT, M_WAITOK);
	b_save->bs_bufsize = b_save->bs_bcount = size;
	b_save->bs_nchildren = 0;
	b_save->bs_children = (struct buf **)(b_save + 1);
	b_save->bs_saveaddr = bp->b_saveaddr;
	bp->b_saveaddr = (caddr_t) b_save;

D 149
	inc = size / DEV_BSIZE;
E 149
I 149
	inc = btodb(size);
E 149
	for (bn = blkno + inc, i = 1; i <= run; ++i, bn += inc) {
D 152
		if (incore(vp, lbn + i)) {
			if (i == 1) {
				bp->b_saveaddr = b_save->bs_saveaddr;
				bp->b_flags &= ~B_CALL;
				bp->b_iodone = NULL;
				allocbuf(bp, size);
				free(b_save, M_SEGMENT);
			} else
				allocbuf(bp, size * i);
E 152
I 152
		/*
		 * A component of the cluster is already in core,
		 * terminate the cluster early.
		 */
		if (incore(vp, lbn + i))
E 152
			break;
D 152
		}
E 152
D 141
		tbp = getblk(vp, lbn + i, 0);
E 141
I 141
		tbp = getblk(vp, lbn + i, 0, 0, 0);
E 141
D 149
		tbp->b_bcount = tbp->b_bufsize = size;
E 149
I 149
		/*
		 * getblk may return some memory in the buffer if there were
		 * no empty buffers to shed it to.  If there is currently
		 * memory in the buffer, we move it down size bytes to make
		 * room for the valid pages that cluster_callback will insert.
		 * We do this now so we don't have to do it at interrupt time
		 * in the callback routine.
		 */
		if (tbp->b_bufsize != 0) {
			caddr_t bdata = (char *)tbp->b_data;

D 152
			if (tbp->b_bufsize + size > MAXBSIZE)
				panic("cluster_rbuild: too much memory");
E 152
I 152
			/*
			 * No room in the buffer to add another page,
			 * terminate the cluster early.
			 */
			if (tbp->b_bufsize + size > MAXBSIZE) {
#ifdef DIAGNOSTIC
				if (tbp->b_bufsize != MAXBSIZE)
					panic("cluster_rbuild: too much memory");
#endif
				brelse(tbp);
				break;
			}
E 152
			if (tbp->b_bufsize > size) {
				/*
				 * XXX if the source and destination regions
				 * overlap we have to copy backward to avoid
				 * clobbering any valid pages (i.e. pagemove
				 * implementations typically can't handle
				 * overlap).
				 */
				bdata += tbp->b_bufsize;
				while (bdata > (char *)tbp->b_data) {
					bdata -= CLBYTES;
					pagemove(bdata, bdata + size, CLBYTES);
				}
			} else 
				pagemove(bdata, bdata + size, tbp->b_bufsize);
		}
E 149
		tbp->b_blkno = bn;
I 143
		{
			daddr_t temp;
			VOP_BMAP(tbp->b_vp, tbp->b_lblkno, NULL, &temp, NULL);
			if (temp != bn) {
				printf("Block: %d Assigned address: %x Bmap address: %x\n",
					    tbp->b_lblkno, tbp->b_blkno, temp);
				panic("cluster_rbuild: wrong disk address");
			}
		}
E 143
		tbp->b_flags |= flags | B_READ | B_ASYNC;
		++b_save->bs_nchildren;
		b_save->bs_children[i - 1] = tbp;
I 152
	}
	/*
	 * The cluster may have been terminated early, adjust the cluster
	 * buffer size accordingly.  If no cluster could be formed,
	 * deallocate the cluster save info.
	 */
	if (i <= run) {
		if (i == 1) {
			bp->b_saveaddr = b_save->bs_saveaddr;
			bp->b_flags &= ~B_CALL;
			bp->b_iodone = NULL;
			free(b_save, M_SEGMENT);
		}
		allocbuf(bp, size * i);
E 152
	}
D 149
	if (!(bp->b_flags & B_ASYNC))
		vp->v_ralen = max(vp->v_ralen - 1, 1);
E 149
	return(bp);
}

/*
 * Either get a new buffer or grow the existing one.
 */
struct buf *
cluster_newbuf(vp, bp, flags, blkno, lblkno, size, run)
	struct vnode *vp;
	struct buf *bp;
	long flags;
	daddr_t blkno;
	daddr_t lblkno;
	long size;
	int run;
{
	if (!bp) {
D 141
		bp = getblk(vp, lblkno, size);
E 141
I 141
		bp = getblk(vp, lblkno, size, 0, 0);
E 141
		if (bp->b_flags & (B_DONE | B_DELWRI)) {
			bp->b_blkno = blkno;
			return(bp);
		}
	}
	allocbuf(bp, run * size);
	bp->b_blkno = blkno;
	bp->b_iodone = cluster_callback;
	bp->b_flags |= flags | B_CALL;
	return(bp);
}

/*
 * Cleanup after a clustered read or write.
I 149
 * This is complicated by the fact that any of the buffers might have
 * extra memory (if there were no empty buffer headers at allocbuf time)
 * that we will need to shift around.
E 149
 */
void
cluster_callback(bp)
	struct buf *bp;
{
	struct cluster_save *b_save;
D 149
	struct buf **tbp;
E 149
I 149
	struct buf **bpp, *tbp;
	long bsize;
E 149
D 148
	long bsize;
E 148
	caddr_t cp;
I 149
	int error = 0;
E 149
I 147

I 149
	/*
	 * Must propogate errors to all the components.
	 */
	if (bp->b_flags & B_ERROR)
		error = bp->b_error;

E 149
E 147
I 143
	daddr_t	daddr;
E 143
D 141

E 141
	b_save = (struct cluster_save *)(bp->b_saveaddr);
	bp->b_saveaddr = b_save->bs_saveaddr;

D 146
	cp = bp->b_un.b_addr + b_save->bs_bufsize;
E 146
I 146
D 149
	cp = (char *)bp->b_data + b_save->bs_bufsize;
E 146
I 143
	daddr = bp->b_blkno + b_save->bs_bufsize / DEV_BSIZE;
E 143
	for (tbp = b_save->bs_children; b_save->bs_nchildren--; ++tbp) {
D 146
		pagemove(cp, (*tbp)->b_un.b_addr, (*tbp)->b_bufsize);
E 146
I 146
		pagemove(cp, (*tbp)->b_data, (*tbp)->b_bufsize);
E 146
		cp += (*tbp)->b_bufsize;
		bp->b_bufsize -= (*tbp)->b_bufsize;
I 143
		if ((*tbp)->b_blkno != daddr) {
			struct inode *ip;
			printf("cluster_callback: bad disk address:\n");
			printf("Clustered Block: %d DiskAddr: %x bytes left: %d\n",
			    bp->b_lblkno, bp->b_blkno, bp->b_bufsize);
			printf("\toriginal size: %d flags: %x\n", bp->b_bcount,
			    bp->b_flags);
			printf("Child Block: %d DiskAddr: %x bytes: %d\n",
			    (*tbp)->b_lblkno, (*tbp)->b_blkno,
			    (*tbp)->b_bufsize);
			ip = VTOI((*tbp)->b_vp);
			printf("daddr: %x i_size %qd\n", daddr, ip->i_size);
			if ((*tbp)->b_lblkno < NDADDR)
				printf("Child block pointer from inode: %x\n",
				    ip->i_din.di_db[(*tbp)->b_lblkno]);
			spl0();
			panic ("cluster_callback: bad disk address");
		}
		daddr += (*tbp)->b_bufsize / DEV_BSIZE;
E 143
		biodone(*tbp);
E 149
I 149
	bsize = b_save->bs_bufsize;
	cp = (char *)bp->b_data + bsize;
	/*
	 * Move memory from the large cluster buffer into the component
	 * buffers and mark IO as done on these.
	 */
	for (bpp = b_save->bs_children; b_save->bs_nchildren--; ++bpp) {
		tbp = *bpp;
		pagemove(cp, tbp->b_data, bsize);
		tbp->b_bufsize += bsize;
		tbp->b_bcount = bsize;
		if (error) {
			tbp->b_flags |= B_ERROR;
			tbp->b_error = error;
		}
		biodone(tbp);
		bp->b_bufsize -= bsize;
		cp += bsize;
E 149
	}
D 149
#ifdef DIAGNOSTIC
	if (bp->b_bufsize != b_save->bs_bufsize)
		panic ("cluster_callback: more space to reclaim");
#endif
	bp->b_bcount = bp->b_bufsize;
E 149
I 149
	/*
	 * If there was excess memory in the cluster buffer,
	 * slide it up adjacent to the remaining valid data.
	 */
	if (bp->b_bufsize != bsize) {
		if (bp->b_bufsize < bsize)
			panic("cluster_callback: too little memory");
		pagemove(cp, (char *)bp->b_data + bsize, bp->b_bufsize - bsize);
	}
	bp->b_bcount = bsize;
E 149
	bp->b_iodone = NULL;
	free(b_save, M_SEGMENT);
	if (bp->b_flags & B_ASYNC)
		brelse(bp);
D 149
	else
E 149
I 149
	else {
		bp->b_flags &= ~B_WANTED;
E 149
		wakeup((caddr_t)bp);
I 149
	}
E 149
}

/*
E 140
D 105
 * Write the buffer, waiting for completion.
 * Then release the buffer.
E 105
I 105
D 144
 * Synchronous write.
 * Release buffer on completion.
E 105
 */
bwrite(bp)
D 45
register struct buf *bp;
E 45
I 45
	register struct buf *bp;
E 45
{
I 128
D 131
	USES_VOP_STRATEGY;
E 131
E 128
I 107
	struct proc *p = curproc;		/* XXX */
E 107
D 78
	register flag;
E 78
I 78
	register int flag;
D 95
	int error;
E 95
I 95
D 119
	int s, error;
E 119
I 119
	int s, error = 0;
E 119
E 95
E 78

	flag = bp->b_flags;
D 55
	bp->b_flags &= ~(B_READ | B_DONE | B_ERROR | B_DELWRI | B_AGE);
E 55
I 55
	bp->b_flags &= ~(B_READ | B_DONE | B_ERROR | B_DELWRI);
E 55
D 41
	bp->b_bcount = BSIZE;
E 41
D 45
#ifdef	DISKMON
	io_info.nwrite++;
#endif
E 45
D 105
	if ((flag&B_DELWRI) == 0)
E 105
I 105
D 113
	if ((flag & B_DELWRI) == 0)
E 105
D 50
		u.u_vm.vm_oublk++;		/* noone paid yet */
E 50
I 50
D 107
		u.u_ru.ru_oublock++;		/* noone paid yet */
E 107
I 107
		p->p_stats->p_ru.ru_oublock++;		/* no one paid yet */
E 107
I 92
	else
		reassignbuf(bp, bp->b_vp);
E 113
I 113
	if (flag & B_ASYNC) {
		if ((flag & B_DELWRI) == 0)
			p->p_stats->p_ru.ru_oublock++;	/* no one paid yet */
		else
			reassignbuf(bp, bp->b_vp);
	}
E 113
E 92
E 50
I 16
D 30
#ifdef	EPAWNJ
E 30
I 30
D 45
#ifdef	TRACE
E 45
E 30
D 34
	trace(TR_BWRITE, bp->b_dev, dbtofsb(bp->b_blkno));
E 34
I 34
D 65
	trace(TR_BWRITE, bp->b_dev, bp->b_blkno);
E 65
I 65
D 78
	trace(TR_BWRITE, pack(bp->b_dev, bp->b_bcount), bp->b_blkno);
E 78
I 78
D 96
	trace(TR_BWRITE,
D 88
	    pack(bp->b_vp->v_mount->m_fsid[0], bp->b_bcount), bp->b_blkno);
E 88
I 88
	    pack(bp->b_vp->v_mount->m_fsid[0], bp->b_bcount), bp->b_lblkno);
E 96
I 96
	trace(TR_BWRITE, pack(bp->b_vp, bp->b_bcount), bp->b_lblkno);
E 96
E 88
E 78
E 65
I 48
D 53
if (bioprintfs)
printf("write %x blk %d count %d\n", bp->b_dev, bp->b_blkno, bp->b_bcount);
E 53
I 53
	if (bp->b_bcount > bp->b_bufsize)
		panic("bwrite");
I 95
	s = splbio();
E 95
I 92
	bp->b_vp->v_numoutput++;
I 141
	bp->b_flags |= B_WRITEINPROG;
E 141
I 95
	splx(s);
E 95
E 92
E 53
E 48
E 34
D 45
#endif
E 45
E 16
D 78
	(*bdevsw[major(bp->b_dev)].d_strategy)(bp);
E 78
I 78
	VOP_STRATEGY(bp);
E 78
I 45

	/*
D 105
	 * If the write was synchronous, then await i/o completion.
E 105
I 105
	 * If the write was synchronous, then await I/O completion.
E 105
	 * If the write was "delayed", then we put the buffer on
D 105
	 * the q of blocks awaiting i/o completion status.
E 105
I 105
	 * the queue of blocks awaiting I/O completion status.
E 105
D 55
	 * Otherwise, the i/o must be finished and we check for
	 * an error.
E 55
	 */
E 45
D 105
	if ((flag&B_ASYNC) == 0) {
E 105
I 105
	if ((flag & B_ASYNC) == 0) {
E 105
D 45
		iowait(bp);
E 45
I 45
D 78
		biowait(bp);
E 78
I 78
		error = biowait(bp);
I 113
		if ((flag&B_DELWRI) == 0)
			p->p_stats->p_ru.ru_oublock++;	/* no one paid yet */
		else
			reassignbuf(bp, bp->b_vp);
I 141
		if (bp->b_flags & B_EINTR) {
			bp->b_flags &= ~B_EINTR;
			error = EINTR;
		}
E 141
E 113
E 78
E 45
		brelse(bp);
D 78
	} else if (flag & B_DELWRI)
E 78
I 78
	} else if (flag & B_DELWRI) {
I 119
		s = splbio();
E 119
E 78
		bp->b_flags |= B_AGE;
I 78
D 119
		error = 0;
E 119
I 119
		splx(s);
E 119
	}
	return (error);
E 78
D 55
	else
D 49
		geterror(bp);
E 49
I 49
		u.u_error = geterror(bp);
E 55
E 49
}

I 129
int
vn_bwrite(ap)
	struct vop_bwrite_args *ap;
{
D 137
	return bwrite (ap->a_bp);
E 137
I 137
	return (bwrite(ap->a_bp));
E 137
}


E 129
/*
D 105
 * Release the buffer, marking it so that if it is grabbed
 * for another purpose it will be written out before being
 * given up (e.g. when writing a partial block where it is
 * assumed that another write for the same block will soon follow).
 * This can't be done for magtape, since writes must be done
 * in the same order as requested.
E 105
I 105
 * Delayed write.
 *
 * The buffer is marked dirty, but is not queued for I/O.
 * This routine should be used when the buffer is expected
 * to be modified again soon, typically a small write that
 * partially fills a buffer.
 *
 * NB: magnetic tapes cannot be delayed; they must be
 * written in the order that the writes are requested.
E 105
 */
bdwrite(bp)
D 45
register struct buf *bp;
E 45
I 45
	register struct buf *bp;
E 45
{
I 128
D 131
	USES_VOP_IOCTL;
E 131
E 128
I 107
	struct proc *p = curproc;		/* XXX */
E 107
D 22
	register struct buf *dp;
E 22
I 22
D 74
D 75
	register int flags;
E 75
E 74
E 22

D 92
	if ((bp->b_flags&B_DELWRI) == 0)
E 92
I 92
	if ((bp->b_flags & B_DELWRI) == 0) {
		bp->b_flags |= B_DELWRI;
		reassignbuf(bp, bp->b_vp);
E 92
D 50
		u.u_vm.vm_oublk++;		/* noone paid yet */
E 50
I 50
D 107
		u.u_ru.ru_oublock++;		/* noone paid yet */
E 107
I 107
		p->p_stats->p_ru.ru_oublock++;		/* no one paid yet */
E 107
I 92
	}
E 92
I 78
D 88
#ifdef notdef
E 88
	/*
D 88
	 * This does not work for buffers associated with
	 * vnodes that are remote - they have no dev.
	 * Besides, we don't use bio with tapes, so rather
	 * than develop a fix, we just ifdef this out for now.
E 88
I 88
	 * If this is a tape drive, the write must be initiated.
E 88
	 */
E 78
E 50
D 22
	dp = bdevsw[major(bp->b_dev)].d_tab;
	if(dp->b_flags & B_TAPE)
E 22
I 22
D 74
D 75
	flags = bdevsw[major(bp->b_dev)].d_flags;
	if(flags & B_TAPE)
E 75
I 75
D 88
	if (bdevsw[major(bp->b_dev)].d_flags & B_TAPE)
E 88
I 88
D 109
	if (VOP_IOCTL(bp->b_vp, 0, B_TAPE, 0, NOCRED) == 0) {
E 109
I 109
D 110
	if (VOP_IOCTL(bp->b_vp, 0, B_TAPE, 0, NOCRED, p) == 0) {
E 110
I 110
	if (VOP_IOCTL(bp->b_vp, 0, (caddr_t)B_TAPE, 0, NOCRED, p) == 0) {
E 110
E 109
E 88
E 75
E 74
I 74
	if (bdevsw[major(bp->b_dev)].d_flags & B_TAPE)
E 74
E 22
		bawrite(bp);
D 88
	else {
E 88
I 88
	} else {
E 88
D 105
		bp->b_flags |= B_DELWRI | B_DONE;
E 105
I 105
		bp->b_flags |= (B_DONE | B_DELWRI);
E 105
		brelse(bp);
	}
I 78
D 88
#endif
	bp->b_flags |= B_DELWRI | B_DONE;
	brelse(bp);
E 88
E 78
}

/*
D 105
 * Release the buffer, start I/O on it, but don't wait for completion.
E 105
I 105
 * Asynchronous write.
 * Start I/O on a buffer, but do not wait for it to complete.
 * The buffer is released when the I/O completes.
E 105
 */
bawrite(bp)
D 45
register struct buf *bp;
E 45
I 45
	register struct buf *bp;
E 45
{

I 105
	/*
	 * Setting the ASYNC flag causes bwrite to return
	 * after starting the I/O.
	 */
E 105
	bp->b_flags |= B_ASYNC;
D 78
	bwrite(bp);
E 78
I 78
D 141
	(void) bwrite(bp);
E 141
I 141
	(void) VOP_BWRITE(bp);
E 141
I 140
}

/*
E 144
 * Do clustered write for FFS.
 *
 * Three cases:
 *	1. Write is not sequential (write asynchronously)
 *	Write is sequential:
 *	2.	beginning of cluster - begin cluster
 *	3.	middle of a cluster - add to cluster
 *	4.	end of a cluster - asynchronously write cluster
 */
void
cluster_write(bp, filesize)
        struct buf *bp;
	u_quad_t filesize;
{
        struct vnode *vp;
        daddr_t lbn;
D 142
        int clen, error, maxrun;
E 142
I 142
D 150
        int clen;
E 150
I 150
        int maxclen, cursize;
E 150
E 142

        vp = bp->b_vp;
        lbn = bp->b_lblkno;
D 142
	clen = 0;
E 142

D 142
	/*
	 * Handle end of file first.  If we are appending, we need to check
	 * if the current block was allocated contiguously.  If it wasn't,
	 * then we need to fire off a previous cluster if it existed.
	 * Additionally, when we're appending, we need to figure out how
	 * to initialize vp->v_clen.
	 */
	if ((lbn + 1) * bp->b_bcount == filesize) {
		if (bp->b_blkno != vp->v_lasta + bp->b_bcount / DEV_BSIZE) {
			/* This block was not allocated contiguously */
			if (vp->v_clen)
			    cluster_wbuild(vp, NULL, bp->b_bcount, vp->v_cstart,
				vp->v_lastw - vp->v_cstart + 1, lbn);
			vp->v_cstart = lbn;
			clen = vp->v_clen =
			    MAXBSIZE / vp->v_mount->mnt_stat.f_iosize - 1;
			/*
			 * Next cluster started. Write this buffer and return.
			 */
			vp->v_lastw = lbn;
			vp->v_lasta = bp->b_blkno;
			bdwrite(bp);
			return;
		}
		vp->v_lasta = bp->b_blkno;
	} else if (lbn == 0) {
		vp->v_clen = vp->v_cstart = vp->v_lastw = 0;
	}
        if (vp->v_clen == 0 || lbn != vp->v_lastw + 1) {
E 142
I 142
	/* Initialize vnode to beginning of file. */
	if (lbn == 0)
		vp->v_lasta = vp->v_clen = vp->v_cstart = vp->v_lastw = 0;

        if (vp->v_clen == 0 || lbn != vp->v_lastw + 1 ||
D 149
	    (bp->b_blkno != vp->v_lasta + bp->b_bcount / DEV_BSIZE)) {
E 149
I 149
	    (bp->b_blkno != vp->v_lasta + btodb(bp->b_bcount))) {
E 149
E 142
D 150
		if (vp->v_clen != 0)
E 150
I 150
		maxclen = MAXBSIZE / vp->v_mount->mnt_stat.f_iosize - 1;
		if (vp->v_clen != 0) {
E 150
			/*
D 150
			 * Write is not sequential.
E 150
I 150
			 * Next block is not sequential.
			 *
			 * If we are not writing at end of file, the process
			 * seeked to another point in the file since its
			 * last write, or we have reached our maximum
			 * cluster size, then push the previous cluster.
			 * Otherwise try reallocating to make it sequential.
E 150
			 */
D 150
			cluster_wbuild(vp, NULL, bp->b_bcount, vp->v_cstart,
			    vp->v_lastw - vp->v_cstart + 1, lbn);
E 150
I 150
			cursize = vp->v_lastw - vp->v_cstart + 1;
D 151
			if ((lbn + 1) * bp->b_bcount != filesize ||
E 151
I 151
D 154
			if (!doreallocblks ||
			    (lbn + 1) * bp->b_bcount != filesize ||
E 154
I 154
			if ((lbn + 1) * bp->b_bcount != filesize ||
E 154
E 151
			    lbn != vp->v_lastw + 1 || vp->v_clen <= cursize) {
				cluster_wbuild(vp, NULL, bp->b_bcount,
				    vp->v_cstart, cursize, lbn);
			} else {
				struct buf **bpp, **endbp;
				struct cluster_save *buflist;

				buflist = cluster_collectbufs(vp, bp);
				endbp = &buflist->bs_children
				    [buflist->bs_nchildren - 1];
				if (VOP_REALLOCBLKS(vp, buflist)) {
					/*
					 * Failed, push the previous cluster.
					 */
					for (bpp = buflist->bs_children;
					     bpp < endbp; bpp++)
						brelse(*bpp);
					free(buflist, M_SEGMENT);
					cluster_wbuild(vp, NULL, bp->b_bcount,
					    vp->v_cstart, cursize, lbn);
				} else {
					/*
					 * Succeeded, keep building cluster.
					 */
					for (bpp = buflist->bs_children;
					     bpp <= endbp; bpp++)
						bdwrite(*bpp);
					free(buflist, M_SEGMENT);
					vp->v_lastw = lbn;
					vp->v_lasta = bp->b_blkno;
					return;
				}
			}
		}
E 150
		/*
		 * Consider beginning a cluster.
I 150
		 * If at end of file, make cluster as large as possible,
		 * otherwise find size of existing cluster.
E 150
		 */
D 142
		if (error = VOP_BMAP(vp, lbn, NULL, &bp->b_blkno, &clen)) {
E 142
I 142
D 150
		if ((lbn + 1) * bp->b_bcount == filesize)
			/* End of file, make cluster as large as possible */
			clen = MAXBSIZE / vp->v_mount->mnt_stat.f_iosize - 1;
D 147
		else if (VOP_BMAP(vp, lbn, NULL, &bp->b_blkno, &clen)) {
E 147
I 147
		else if (VOP_BMAP(vp, lbn, NULL, &bp->b_blkno, &clen) ||
			    bp->b_blkno == -1) {
E 150
I 150
		if ((lbn + 1) * bp->b_bcount != filesize &&
		    (VOP_BMAP(vp, lbn, NULL, &bp->b_blkno, &maxclen) ||
		     bp->b_blkno == -1)) {
E 150
E 147
E 142
			bawrite(bp);
I 142
			vp->v_clen = 0;
			vp->v_lasta = bp->b_blkno;
E 142
			vp->v_cstart = lbn + 1;
			vp->v_lastw = lbn;
			return;
D 142
		}
E 142
I 142
D 147
		} else
			clen = 0;
E 147
I 147
		}
E 147
E 142
D 150
                vp->v_clen = clen;
                if (clen == 0) {		/* I/O not contiguous */
E 150
I 150
                vp->v_clen = maxclen;
                if (maxclen == 0) {		/* I/O not contiguous */
E 150
			vp->v_cstart = lbn + 1;
                        bawrite(bp);
                } else {			/* Wait for rest of cluster */
			vp->v_cstart = lbn;
                        bdwrite(bp);
		}
D 149
        } else if (lbn == vp->v_cstart + vp->v_clen) {
E 149
I 149
	} else if (lbn == vp->v_cstart + vp->v_clen) {
E 149
		/*
		 * At end of cluster, write it out.
		 */
		cluster_wbuild(vp, bp, bp->b_bcount, vp->v_cstart,
		    vp->v_clen + 1, lbn);
		vp->v_clen = 0;
		vp->v_cstart = lbn + 1;
D 149
        } else
E 149
I 149
	} else
E 149
		/*
		 * In the middle of a cluster, so just delay the
		 * I/O for now.
		 */
D 149
                bdwrite(bp);
        vp->v_lastw = lbn;
E 149
I 149
		bdwrite(bp);
	vp->v_lastw = lbn;
E 149
I 142
	vp->v_lasta = bp->b_blkno;
E 142
}


/*
 * This is an awful lot like cluster_rbuild...wish they could be combined.
 * The last lbn argument is the current block on which I/O is being
 * performed.  Check to see that it doesn't fall in the middle of
D 149
 * the current block.
E 149
I 149
 * the current block (if last_bp == NULL).
E 149
 */
void
cluster_wbuild(vp, last_bp, size, start_lbn, len, lbn)
	struct vnode *vp;
	struct buf *last_bp;
	long size;
	daddr_t start_lbn;
	int len;
	daddr_t	lbn;
{
	struct cluster_save *b_save;
	struct buf *bp, *tbp;
	caddr_t	cp;
	int i, s;

I 142
#ifdef DIAGNOSTIC
	if (size != vp->v_mount->mnt_stat.f_iosize)
		panic("cluster_wbuild: size %d != filesize %d\n",
			size, vp->v_mount->mnt_stat.f_iosize);
#endif
E 142
redo:
	while ((!incore(vp, start_lbn) || start_lbn == lbn) && len) {
		++start_lbn;
		--len;
	}

	/* Get more memory for current buffer */
	if (len <= 1) {
D 142
		if (last_bp)
E 142
I 142
		if (last_bp) {
E 142
			bawrite(last_bp);
I 142
		} else if (len) {
			bp = getblk(vp, start_lbn, size, 0, 0);
			bawrite(bp);
		}
E 142
		return;
	}

D 141
	bp = getblk(vp, start_lbn, size);
E 141
I 141
	bp = getblk(vp, start_lbn, size, 0, 0);
E 141
	if (!(bp->b_flags & B_DELWRI)) {
		++start_lbn;
		--len;
		brelse(bp);
		goto redo;
	}

I 149
	/*
	 * Extra memory in the buffer, punt on this buffer.
	 * XXX we could handle this in most cases, but we would have to
	 * push the extra memory down to after our max possible cluster
	 * size and then potentially pull it back up if the cluster was
	 * terminated prematurely--too much hassle.
	 */
	if (bp->b_bcount != bp->b_bufsize) {
		++start_lbn;
		--len;
		bawrite(bp);
		goto redo;
	}

E 149
	--len;
	b_save = malloc(sizeof(struct buf *) * len + sizeof(struct cluster_save),
	    M_SEGMENT, M_WAITOK);
	b_save->bs_bcount = bp->b_bcount;
	b_save->bs_bufsize = bp->b_bufsize;
	b_save->bs_nchildren = 0;
	b_save->bs_children = (struct buf **)(b_save + 1);
	b_save->bs_saveaddr = bp->b_saveaddr;
	bp->b_saveaddr = (caddr_t) b_save;

D 149

E 149
	bp->b_flags |= B_CALL;
	bp->b_iodone = cluster_callback;
D 146
	cp = bp->b_un.b_addr + bp->b_bufsize;
E 146
I 146
D 149
	cp = (char *)bp->b_data + bp->b_bufsize;
E 149
I 149
	cp = (char *)bp->b_data + size;
E 149
E 146
	for (++start_lbn, i = 0; i < len; ++i, ++start_lbn) {
D 149
		if (!incore(vp, start_lbn) || start_lbn == lbn)
E 149
I 149
		/*
		 * Block is not in core or the non-sequential block
		 * ending our cluster was part of the cluster (in which
		 * case we don't want to write it twice).
		 */
		if (!incore(vp, start_lbn) ||
		    last_bp == NULL && start_lbn == lbn)
E 149
			break;

D 149
		if (last_bp == NULL || start_lbn != last_bp->b_lblkno) {
E 149
I 149
		/*
		 * Get the desired block buffer (unless it is the final
		 * sequential block whose buffer was passed in explictly
		 * as last_bp).
		 */
		if (last_bp == NULL || start_lbn != lbn) {
E 149
D 141
			tbp = getblk(vp, start_lbn, size);
E 141
I 141
			tbp = getblk(vp, start_lbn, size, 0, 0);
E 141
D 149
#ifdef DIAGNOSTIC
			if (tbp->b_bcount != tbp->b_bufsize)
				panic("cluster_wbuild: Buffer too big");
#endif
E 149
			if (!(tbp->b_flags & B_DELWRI)) {
				brelse(tbp);
				break;
			}
		} else
			tbp = last_bp;

		++b_save->bs_nchildren;

		/* Move memory from children to parent */
I 142
D 149
		if (tbp->b_blkno != (bp->b_blkno + bp->b_bufsize / DEV_BSIZE)) {
E 149
I 149
		if (tbp->b_blkno != (bp->b_blkno + btodb(bp->b_bufsize))) {
E 149
			printf("Clustered Block: %d addr %x bufsize: %d\n",
			    bp->b_lblkno, bp->b_blkno, bp->b_bufsize);
			printf("Child Block: %d addr: %x\n", tbp->b_lblkno,
			    tbp->b_blkno);
			panic("Clustered write to wrong blocks");
		}

E 142
D 146
		pagemove(tbp->b_un.b_daddr, cp, size);
E 146
I 146
		pagemove(tbp->b_data, cp, size);
E 146
		bp->b_bcount += size;
		bp->b_bufsize += size;

I 149
		tbp->b_bufsize -= size;
E 149
		tbp->b_flags &= ~(B_READ | B_DONE | B_ERROR | B_DELWRI);
D 149
		tbp->b_flags |= B_ASYNC;
E 149
I 149
		tbp->b_flags |= (B_ASYNC | B_AGE);
E 149
		s = splbio();
		reassignbuf(tbp, tbp->b_vp);		/* put on clean list */
		++tbp->b_vp->v_numoutput;
		splx(s);
		b_save->bs_children[i] = tbp;

D 149
		cp += tbp->b_bufsize;
E 149
I 149
		cp += size;
E 149
	}

	if (i == 0) {
		/* None to cluster */
		bp->b_saveaddr = b_save->bs_saveaddr;
		bp->b_flags &= ~B_CALL;
		bp->b_iodone = NULL;
		free(b_save, M_SEGMENT);
	}
	bawrite(bp);
	if (i < len) {
		len -= i + 1;
		start_lbn += 1;
		goto redo;
	}
I 150
}

/*
 * Collect together all the buffers in a cluster.
 * Plus add one additional buffer.
 */
struct cluster_save *
cluster_collectbufs(vp, last_bp)
	struct vnode *vp;
	struct buf *last_bp;
{
	struct cluster_save *buflist;
	daddr_t	lbn;
	int i, len;

	len = vp->v_lastw - vp->v_cstart + 1;
	buflist = malloc(sizeof(struct buf *) * (len + 1) + sizeof(*buflist),
	    M_SEGMENT, M_WAITOK);
	buflist->bs_nchildren = 0;
	buflist->bs_children = (struct buf **)(buflist + 1);
	for (lbn = vp->v_cstart, i = 0; i < len; lbn++, i++)
		    (void)bread(vp, lbn, last_bp->b_bcount, NOCRED,
			&buflist->bs_children[i]);
	buflist->bs_children[i] = last_bp;
	buflist->bs_nchildren = i + 1;
	return (buflist);
E 150
E 140
E 78
}
D 144

/*
D 45
 * release the buffer, with no I/O implied.
E 45
I 45
D 105
 * Release the buffer, with no I/O implied.
E 105
I 105
 * Release a buffer.
 * Even if the buffer is dirty, no I/O is started.
E 105
E 45
 */
brelse(bp)
D 45
register struct buf *bp;
E 45
I 45
	register struct buf *bp;
E 45
{
D 18
	register struct buf **backp;
E 18
I 18
D 137
	register struct buf *flist;
E 137
I 137
D 138
	register struct bufqueue *flist;
E 138
I 138
	register struct queue_entry *flist;
E 138
E 137
E 18
D 105
	register s;
E 105
I 105
	int s;
E 105

I 65
D 78
	trace(TR_BRELSE, pack(bp->b_dev, bp->b_bufsize), bp->b_blkno);
E 78
I 78
D 96
	trace(TR_BRELSE,
D 88
	    pack(bp->b_vp->v_mount->m_fsid[0], bp->b_bufsize), bp->b_blkno);
E 88
I 88
	    pack(bp->b_vp->v_mount->m_fsid[0], bp->b_bufsize), bp->b_lblkno);
E 96
I 96
	trace(TR_BRELSE, pack(bp->b_vp, bp->b_bufsize), bp->b_lblkno);
E 96
E 88
E 78
E 65
I 45
	/*
D 88
	 * If someone's waiting for the buffer, or
	 * is waiting for a buffer wake 'em up.
E 88
I 88
	 * If a process is waiting for the buffer, or
	 * is waiting for a free buffer, awaken it.
E 88
	 */
E 45
D 105
	if (bp->b_flags&B_WANTED)
E 105
I 105
	if (bp->b_flags & B_WANTED)
E 105
		wakeup((caddr_t)bp);
D 18
	if (bfreelist.b_flags&B_WANTED) {
		bfreelist.b_flags &= ~B_WANTED;
		wakeup((caddr_t)&bfreelist);
E 18
I 18
D 105
	if (bfreelist[0].b_flags&B_WANTED) {
E 105
I 105
D 137
	if (bfreelist[0].b_flags & B_WANTED) {
E 105
		bfreelist[0].b_flags &= ~B_WANTED;
		wakeup((caddr_t)bfreelist);
E 137
I 137
	if (needbuffer) {
		needbuffer = 0;
		wakeup((caddr_t)&needbuffer);
E 137
E 18
	}
I 78
D 88
	if (bp->b_flags & B_NOCACHE) {
E 88
I 88
	/*
	 * Retry I/O for locked buffers rather than invalidating them.
	 */
I 119
	s = splbio();
E 119
	if ((bp->b_flags & B_ERROR) && (bp->b_flags & B_LOCKED))
		bp->b_flags &= ~B_ERROR;
D 105

E 105
	/*
	 * Disassociate buffers that are no longer valid.
	 */
D 105
	if (bp->b_flags & (B_NOCACHE|B_ERROR))
E 105
I 105
	if (bp->b_flags & (B_NOCACHE | B_ERROR))
E 105
E 88
		bp->b_flags |= B_INVAL;
I 88
D 105
	if ((bp->b_bufsize <= 0) || (bp->b_flags & (B_ERROR|B_INVAL))) {
E 105
I 105
	if ((bp->b_bufsize <= 0) || (bp->b_flags & (B_ERROR | B_INVAL))) {
E 105
		if (bp->b_vp)
			brelvp(bp);
		bp->b_flags &= ~B_DELWRI;
E 88
	}
E 78
D 2
	if (bp->b_flags&B_ERROR)
E 2
I 2
D 18
	if ((bp->b_flags&B_ERROR) && bp->b_dev != NODEV) {
		bunhash(bp);
E 18
I 18
D 24
	if ((bp->b_flags&B_ERROR) && bp->b_dev != NODEV)
E 18
E 2
		bp->b_dev = NODEV;  /* no assoc. on error */
E 24
I 24
D 88
	if (bp->b_flags&B_ERROR)
		if (bp->b_flags & B_LOCKED)
			bp->b_flags &= ~B_ERROR;	/* try again later */
		else
D 78
			bp->b_dev = NODEV;  		/* no assoc */
E 78
I 78
			brelvp(bp); 	 		/* no assoc */
E 78
I 45

E 88
	/*
	 * Stick the buffer back on a free list.
	 */
E 45
E 24
I 2
D 18
	}
E 18
E 2
D 72
	s = spl6();
E 72
I 72
D 119
	s = splbio();
E 119
E 72
D 18
	if(bp->b_flags & (B_AGE|B_ERROR)) {
		backp = &bfreelist.av_forw;
		(*backp)->av_back = bp;
		bp->av_forw = *backp;
		*backp = bp;
		bp->av_back = &bfreelist;
E 18
I 18
D 53
	if (bp->b_flags & (B_ERROR|B_INVAL)) {
E 53
I 53
	if (bp->b_bufsize <= 0) {
		/* block has no buffer ... put at front of unused buffer list */
D 137
		flist = &bfreelist[BQ_EMPTY];
E 137
I 137
		flist = &bufqueues[BQ_EMPTY];
E 137
		binsheadfree(bp, flist);
D 105
	} else if (bp->b_flags & (B_ERROR|B_INVAL)) {
E 105
I 105
	} else if (bp->b_flags & (B_ERROR | B_INVAL)) {
E 105
E 53
		/* block has no info ... put at front of most free list */
D 53
		flist = &bfreelist[BQUEUES-1];
E 53
I 53
D 137
		flist = &bfreelist[BQ_AGE];
E 137
I 137
		flist = &bufqueues[BQ_AGE];
E 137
E 53
D 45
		flist->av_forw->av_back = bp;
		bp->av_forw = flist->av_forw;
		flist->av_forw = bp;
		bp->av_back = flist;
E 45
I 45
		binsheadfree(bp, flist);
E 45
E 18
	} else {
D 18
		backp = &bfreelist.av_back;
		(*backp)->av_forw = bp;
		bp->av_back = *backp;
		*backp = bp;
		bp->av_forw = &bfreelist;
E 18
I 18
		if (bp->b_flags & B_LOCKED)
D 137
			flist = &bfreelist[BQ_LOCKED];
E 137
I 137
			flist = &bufqueues[BQ_LOCKED];
E 137
		else if (bp->b_flags & B_AGE)
D 137
			flist = &bfreelist[BQ_AGE];
E 137
I 137
			flist = &bufqueues[BQ_AGE];
E 137
		else
D 137
			flist = &bfreelist[BQ_LRU];
E 137
I 137
			flist = &bufqueues[BQ_LRU];
E 137
D 45
		flist->av_back->av_forw = bp;
		bp->av_back = flist->av_back;
		flist->av_back = bp;
		bp->av_forw = flist;
E 45
I 45
		binstailfree(bp, flist);
E 45
E 18
	}
D 78
	bp->b_flags &= ~(B_WANTED|B_BUSY|B_ASYNC|B_AGE);
E 78
I 78
D 105
	bp->b_flags &= ~(B_WANTED|B_BUSY|B_ASYNC|B_AGE|B_NOCACHE);
E 105
I 105
	bp->b_flags &= ~(B_WANTED | B_BUSY | B_ASYNC | B_AGE | B_NOCACHE);
E 105
E 78
	splx(s);
}

I 2
D 3
/* HASHING IS A GUN LIKE CHANGE, THIS IS THE SAFETY */
struct buf *
oincore(dev, blkno)
	dev_t dev;
	daddr_t blkno;
{
	register struct buf *bp;
	register struct buf *dp;
	register int dblkno = fsbtodb(blkno);

	dp = bdevsw[major(dev)].d_tab;
	for (bp=dp->b_forw; bp != dp; bp = bp->b_forw)
		if (bp->b_blkno==dblkno && bp->b_dev==dev &&
		    bp >= buf && bp < &buf[NBUF])
			return (bp);
	return ((struct buf *)0);
}

E 3
E 2
/*
D 105
 * See if the block is associated with some buffer
 * (mainly to avoid getting hung up on a wait in breada)
E 105
I 105
 * Check to see if a block is currently memory resident.
E 105
 */
I 141
struct buf *
E 141
D 78
incore(dev, blkno)
D 45
dev_t dev;
daddr_t blkno;
E 45
I 45
	dev_t dev;
E 78
I 78
incore(vp, blkno)
	struct vnode *vp;
E 78
	daddr_t blkno;
E 45
{
	register struct buf *bp;
I 18
D 137
	register struct buf *dp;
E 137
E 18
D 2
	register struct buf *dp;
E 2
D 41
	register int dblkno = fsbtodb(blkno);
E 41

D 2
	dp = bdevsw[major(dev)].d_tab;
	for (bp=dp->b_forw; bp != dp; bp = bp->b_forw)
		if (bp->b_blkno==dblkno && bp->b_dev==dev)
			return(1);
	return(0);
E 2
I 2
D 18
	for (bp = &buf[bufhash[BUFHASH(blkno)]]; bp != &buf[-1];
	    bp = &buf[bp->b_hlink])
D 3
		if (bp->b_blkno == dblkno && bp->b_dev == dev) {
			if (distrust)
			if (oincore(dev, blkno) != bp)		/* TEST */
				panic("incore 1");		/* TEST */
E 3
I 3
D 17
		if (bp->b_blkno == dblkno && bp->b_dev == dev)
E 17
I 17
		if (bp->b_blkno == dblkno && bp->b_dev == dev
					&& !(bp->b_flags & B_INVAL))
E 18
I 18
D 19
	dp = BUFHASH(dev, blkno);
E 19
I 19
D 41
	dp = BUFHASH(dev, dblkno);
E 41
I 41
D 78
	dp = BUFHASH(dev, blkno);
E 78
I 78
D 79
	dp = BUFHASH(vp->v_rdev, blkno);
E 79
I 79
D 137
	dp = BUFHASH(vp, blkno);
E 79
E 78
E 41
E 19
	for (bp = dp->b_forw; bp != dp; bp = bp->b_forw)
E 137
I 137
D 138
	for (bp = *BUFHASH(vp, blkno); bp; bp = bp->b_forw)
E 138
I 138
	for (bp = BUFHASH(vp, blkno)->le_next; bp; bp = bp->b_hash.qe_next)
E 138
E 137
D 41
		if (bp->b_blkno == dblkno && bp->b_dev == dev &&
E 41
I 41
D 78
		if (bp->b_blkno == blkno && bp->b_dev == dev &&
E 78
I 78
D 88
		if (bp->b_blkno == blkno && bp->b_vp == vp &&
E 88
I 88
		if (bp->b_lblkno == blkno && bp->b_vp == vp &&
E 88
E 78
E 41
D 45
		    !(bp->b_flags & B_INVAL))
E 45
I 45
		    (bp->b_flags & B_INVAL) == 0)
E 45
E 18
E 17
E 3
D 141
			return (1);
D 3
		}
	if (distrust)
	if (oincore(dev, blkno))				/* TEST */
		panic("incore 2");				/* TEST */
E 3
	return (0);
E 141
I 141
			return (bp);
	return (NULL);
E 141
E 2
}

I 88
/*
D 105
 * Return a block if it is in memory.
E 105
I 105
 * Check to see if a block is currently memory resident.
 * If it is resident, return it. If it is not resident,
 * allocate a new buffer and assign it to the block.
E 105
 */
E 88
D 78
struct buf *
I 74
#ifdef SECSIZE
baddr(dev, blkno, size, secsize)
#else SECSIZE
E 74
D 41
baddr(dev, blkno)
dev_t dev;
daddr_t blkno;
E 41
I 41
baddr(dev, blkno, size)
I 74
#endif SECSIZE
E 74
	dev_t dev;
E 78
I 78
D 83
baddr(vp, blkno, size, bpp)
E 83
I 83
D 105
baddr(vp, blkno, size, cred, bpp)
E 83
	struct vnode *vp;
E 78
	daddr_t blkno;
	int size;
I 83
	struct ucred *cred;
E 83
I 78
	struct buf **bpp;
E 78
I 74
#ifdef SECSIZE
	long secsize;
#endif SECSIZE
E 74
E 41
{

D 78
	if (incore(dev, blkno))
I 74
#ifdef SECSIZE
		return (bread(dev, blkno, size, secsize));
#else SECSIZE
E 74
D 41
		return (bread(dev, blkno));
E 41
I 41
		return (bread(dev, blkno, size));
E 78
I 78
	if (incore(vp, blkno))
D 83
		return (bread(vp, blkno, size, bpp));
E 83
I 83
		return (bread(vp, blkno, size, cred, bpp));
E 83
	*bpp = 0;
E 78
I 74
#endif SECSIZE
E 74
E 41
	return (0);
}

/*
 * Assign a buffer for the given block.  If the appropriate
 * block is already associated, return it; otherwise search
 * for the oldest non-busy buffer and reassign it.
I 36
 *
I 76
D 88
 * If we find the buffer, but it is dirty (marked DELWRI) and
 * its size is changing, we must write it out first. When the
 * buffer is shrinking, the write is done by brealloc to avoid
 * losing the unwritten data. When the buffer is growing, the
 * write is done by getblk, so that bread will not read stale
 * disk data over the modified data in the buffer.
 *
E 88
E 76
 * We use splx here because this routine may be called
 * on the interrupt stack during a dump, and we don't
 * want to lower the ipl back to 0.
E 36
 */
E 105
struct buf *
I 74
#ifdef SECSIZE
getblk(dev, blkno, size, secsize)
#else SECSIZE
E 74
D 41
getblk(dev, blkno)
dev_t dev;
daddr_t blkno;
E 41
I 41
D 78
getblk(dev, blkno, size)
I 74
#endif SECSIZE
E 74
	dev_t dev;
E 78
I 78
D 141
getblk(vp, blkno, size)
E 141
I 141
getblk(vp, blkno, size, slpflag, slptimeo)
E 141
	register struct vnode *vp;
E 78
	daddr_t blkno;
D 141
	int size;
E 141
I 141
	int size, slpflag, slptimeo;
E 141
I 74
#ifdef SECSIZE
	long secsize;
#endif SECSIZE
E 74
E 41
{
D 2
	register struct buf *bp;
	register struct buf *dp;
#ifdef	DISKMON
	register i;
#endif
E 2
I 2
D 53
	register struct buf *bp, *dp, *ep;
E 53
I 53
D 137
	register struct buf *bp, *dp;
E 137
I 137
D 138
	register struct buf *bp, **dp;
E 138
I 138
	register struct buf *bp;
	struct list_entry *dp;
E 138
E 137
E 53
D 15
	register int i, x;
E 2
	register int dblkno = fsbtodb(blkno);
E 15
I 15
D 18
	register int i, x, dblkno;
E 18
I 18
D 23
	register int i, x;
E 23
D 41
	register int dblkno = fsbtodb(blkno);
E 41
I 23
D 45
#ifdef	DISKMON
	register int i;
#endif
E 45
I 36
D 141
	int s;
E 141
I 141
	int s, error;
E 141
E 36
E 23
E 18
E 15

I 71
	if (size > MAXBSIZE)
		panic("getblk: size too big");
E 71
I 15
D 54
	if ((unsigned)blkno >= 1 << (sizeof(int)*NBBY-PGSHIFT))
E 54
I 54
D 69
	if ((unsigned)blkno >= 1 << (sizeof(int)*NBBY-PGSHIFT))	/* XXX */
E 54
		blkno = 1 << ((sizeof(int)*NBBY-PGSHIFT) + 1);
E 69
I 69
	/*
D 102
	 * To prevent overflow of 32-bit ints when converting block
	 * numbers to byte offsets, blknos > 2^32 / DEV_BSIZE are set
	 * to the maximum number that can be converted to a byte offset
	 * without overflow. This is historic code; what bug it fixed,
	 * or whether it is still a reasonable thing to do is open to
	 * dispute. mkm 9/85
I 88
	 *
	 * Make it a panic to see if it ever really happens. mkm 11/89
E 88
	 */
D 88
	if ((unsigned)blkno >= 1 << (sizeof(int)*NBBY-DEV_BSHIFT))
E 88
I 88
	if ((unsigned)blkno >= 1 << (sizeof(int)*NBBY-DEV_BSHIFT)) {
		panic("getblk: blkno too big");
E 88
		blkno = 1 << ((sizeof(int)*NBBY-DEV_BSHIFT) + 1);
I 88
	}
E 88
E 69
I 45
	/*
E 102
D 105
	 * Search the cache for the block.  If we hit, but
	 * the buffer is in use for i/o, then we wait until
	 * the i/o has completed.
E 105
I 105
	 * Search the cache for the block. If the buffer is found,
	 * but it is currently locked, the we must wait for it to
	 * become available.
E 105
	 */
E 45
D 41
	dblkno = fsbtodb(blkno);
I 18
	dp = BUFHASH(dev, dblkno);
E 41
I 41
D 78
	dp = BUFHASH(dev, blkno);
E 78
I 78
	dp = BUFHASH(vp, blkno);
E 78
E 41
E 18
E 15
D 2
	if(major(dev) >= nblkdev)
		panic("blkdev");

E 2
D 45
    loop:
E 45
I 45
loop:
E 45
D 4
	VOID spl0();
E 4
I 4
D 36
	(void) spl0();
E 36
E 4
D 2
	dp = bdevsw[major(dev)].d_tab;
	if(dp == NULL)
		panic("devtab");
	for (bp=dp->b_forw; bp != dp; bp = bp->b_forw) {
		if (bp->b_blkno!=dblkno || bp->b_dev!=dev)
E 2
I 2
D 18
	for (bp = &buf[bufhash[BUFHASH(blkno)]]; bp != &buf[-1];
	    bp = &buf[bp->b_hlink]) {
D 17
		if (bp->b_blkno != dblkno || bp->b_dev != dev)
E 17
I 17
		if (bp->b_blkno != dblkno || bp->b_dev != dev
					|| bp->b_flags & B_INVAL)
E 18
I 18
D 137
	for (bp = dp->b_forw; bp != dp; bp = bp->b_forw) {
E 137
I 137
D 138
	for (bp = *dp; bp; bp = bp->b_forw) {
E 138
I 138
	for (bp = dp->le_next; bp; bp = bp->b_hash.qe_next) {
E 138
E 137
D 41
		if (bp->b_blkno != dblkno || bp->b_dev != dev ||
E 41
I 41
D 78
		if (bp->b_blkno != blkno || bp->b_dev != dev ||
E 78
I 78
D 88
		if (bp->b_blkno != blkno || bp->b_vp != vp ||
E 88
I 88
D 141
		if (bp->b_lblkno != blkno || bp->b_vp != vp ||
E 88
E 78
E 41
D 105
		    bp->b_flags&B_INVAL)
E 105
I 105
		    (bp->b_flags & B_INVAL))
E 141
I 141
		if (bp->b_lblkno != blkno || bp->b_vp != vp)
E 141
E 105
E 18
E 17
E 2
			continue;
I 2
D 3
		if (distrust)
		if (bp != oincore(dev, blkno))		/* TEST */
			panic("getblk 1");		/* TEST */
E 3
E 2
D 4
		VOID spl6();
E 4
I 4
D 36
		(void) spl6();
E 36
I 36
D 72
		s = spl6();
E 72
I 72
		s = splbio();
E 72
E 36
E 4
D 105
		if (bp->b_flags&B_BUSY) {
E 105
I 105
		if (bp->b_flags & B_BUSY) {
E 105
			bp->b_flags |= B_WANTED;
D 105
			sleep((caddr_t)bp, PRIBIO+1);
E 105
I 105
D 141
			sleep((caddr_t)bp, PRIBIO + 1);
E 141
I 141
			error = tsleep((caddr_t)bp, slpflag | (PRIBIO + 1),
				"getblk", slptimeo);
E 141
E 105
I 36
			splx(s);
I 141
			if (error)
				return (NULL);
E 141
E 36
			goto loop;
		}
I 141
		/*
		 * The test for B_INVAL is moved down here, since there
		 * are cases where B_INVAL is set before VOP_BWRITE() is
		 * called and for NFS, the process cannot be allowed to
		 * allocate a new buffer for the same block until the write
		 * back to the server has been completed. (ie. B_BUSY clears)
		 */
		if (bp->b_flags & B_INVAL) {
			splx(s);
			continue;
		}
E 141
I 92
		bremfree(bp);
		bp->b_flags |= B_BUSY;
E 92
D 4
		VOID spl0();
E 4
I 4
D 36
		(void) spl0();
E 36
I 36
		splx(s);
E 36
E 4
D 45
#ifdef	DISKMON
		i = 0;
		dp = bp->av_forw;
D 18
		while (dp != &bfreelist) {
E 18
I 18
		while ((dp->b_flags & B_HEAD) == 0) {
E 18
			i++;
			dp = dp->av_forw;
		}
D 26
		if (i<NBUF)
E 26
I 26
		if (i<64)
E 26
			io_info.bufcount[i]++;
#endif
E 45
D 92
		notavail(bp);
E 92
I 76
		if (bp->b_bcount != size) {
D 88
			if (bp->b_bcount < size && (bp->b_flags&B_DELWRI)) {
				bp->b_flags &= ~B_ASYNC;
D 78
				bwrite(bp);
E 78
I 78
				(void) bwrite(bp);
E 78
				goto loop;
			}
			if (brealloc(bp, size) == 0)
				goto loop;
		}
E 76
I 41
D 48
		brealloc(bp, size);
E 48
I 48
D 66
		if (brealloc(bp, size) == 0)
E 66
I 66
		if (bp->b_bcount != size && brealloc(bp, size) == 0)
E 88
I 88
			printf("getblk: stray size");
			bp->b_flags |= B_INVAL;
D 141
			bwrite(bp);
E 141
I 141
			VOP_BWRITE(bp);
E 141
E 88
E 66
			goto loop;
I 88
		}
E 88
E 48
E 41
		bp->b_flags |= B_CACHE;
D 72
		return(bp);
E 72
I 72
		return (bp);
E 72
	}
I 2
D 3
	if (distrust)
	if (oincore(dev, blkno))		/* TEST */
		panic("getblk 2");		/* TEST */
E 3
D 78
	if (major(dev) >= nblkdev)
		panic("blkdev");
E 78
I 45
D 53
	/*
	 * Not found in the cache, select something from
	 * a free list.  Preference is to LRU list, then AGE list.
	 */
E 45
D 18
	dp = bdevsw[major(dev)].d_tab;
	if (dp == NULL)
		panic("devtab");
E 18
E 2
D 4
	VOID spl6();
E 4
I 4
D 36
	(void) spl6();
E 36
I 36
	s = spl6();
E 36
E 4
D 18
	if (bfreelist.av_forw == &bfreelist) {
		bfreelist.b_flags |= B_WANTED;
		sleep((caddr_t)&bfreelist, PRIBIO+1);
E 18
I 18
	for (ep = &bfreelist[BQUEUES-1]; ep > bfreelist; ep--)
		if (ep->av_forw != ep)
			break;
	if (ep == bfreelist) {		/* no free blocks at all */
		ep->b_flags |= B_WANTED;
		sleep((caddr_t)ep, PRIBIO+1);
I 36
		splx(s);
E 36
E 18
		goto loop;
	}
D 14
	spl0();
E 14
I 14
D 36
	(void) spl0();
E 36
I 36
	splx(s);
E 36
E 14
D 18
	bp = bfreelist.av_forw;
E 18
I 18
	bp = ep->av_forw;
E 18
	notavail(bp);
	if (bp->b_flags & B_DELWRI) {
		bp->b_flags |= B_ASYNC;
		bwrite(bp);
		goto loop;
	}
I 2
D 18
	if (bp->b_dev == NODEV)
		goto done;
	/* INLINE EXPANSION OF bunhash(bp) */
E 18
I 16
D 30
#ifdef EPAWNJ
E 30
I 30
D 45
#ifdef TRACE
E 45
E 30
D 34
	trace(TR_BRELSE, bp->b_dev, dbtofsb(bp->b_blkno));
E 34
I 34
	trace(TR_BRELSE, bp->b_dev, bp->b_blkno);
E 34
D 45
#endif
E 45
E 16
I 12
D 18
	(void) spl6();
E 12
	i = BUFHASH(dbtofsb(bp->b_blkno));
	x = bp - buf;
	if (bufhash[i] == x) {
		bufhash[i] = bp->b_hlink;
	} else {
		for (ep = &buf[bufhash[i]]; ep != &buf[-1];
		    ep = &buf[ep->b_hlink])
			if (ep->b_hlink == x) {
				ep->b_hlink = bp->b_hlink;
				goto done;
			}
		panic("getblk");
	}
done:
I 12
	(void) spl0();
E 12
	/* END INLINE EXPANSION */
E 18
E 2
	bp->b_flags = B_BUSY;
E 53
I 53
D 141
	bp = getnewbuf();
E 141
I 141
	/*
	 * The loop back to the top when getnewbuf() fails is because
	 * stateless filesystems like NFS have no node locks. Thus,
	 * there is a slight chance that more than one process will
	 * try and getnewbuf() for the same block concurrently when
	 * the first sleeps in getnewbuf(). So after a sleep, go back
	 * up to the top to check the hash lists again.
	 */
	if ((bp = getnewbuf(slpflag, slptimeo)) == 0)
		goto loop;
E 141
E 53
I 41
D 104
	bfree(bp);
E 104
E 41
D 45
	bp->b_back->b_forw = bp->b_forw;
	bp->b_forw->b_back = bp->b_back;
	bp->b_forw = dp->b_forw;
	bp->b_back = dp;
	dp->b_forw->b_back = bp;
	dp->b_forw = bp;
E 45
I 45
	bremhash(bp);
D 78
	binshash(bp, dp);
E 45
	bp->b_dev = dev;
E 78
I 78
D 88
	if (bp->b_vp)
		brelvp(bp);
D 80
	vp->v_count++;
E 80
I 80
	VREF(vp);
E 80
	bp->b_vp = vp;
	bp->b_dev = vp->v_rdev;
E 88
I 88
	bgetvp(vp, bp);
I 104
	bp->b_bcount = 0;
E 104
	bp->b_lblkno = blkno;
E 88
E 78
I 74
#ifdef SECSIZE
	bp->b_blksize = secsize;
#endif SECSIZE
E 74
D 41
	bp->b_blkno = dblkno;
E 41
I 41
	bp->b_blkno = blkno;
I 53
	bp->b_error = 0;
I 78
	bp->b_resid = 0;
	binshash(bp, dp);
E 78
E 53
D 48
	brealloc(bp, size);
E 48
I 48
D 88
	if (brealloc(bp, size) == 0)
		goto loop;
E 88
I 88
D 104
	brealloc(bp, size);
E 104
I 104
	allocbuf(bp, size);
E 104
E 88
E 48
E 41
I 2
D 18
	i = BUFHASH(blkno);
	bp->b_hlink = bufhash[i];
	bufhash[i] = bp - buf;
E 18
E 2
D 72
	return(bp);
E 72
I 72
	return (bp);
E 72
}

/*
D 105
 * get an empty block,
 * not assigned to any particular device
E 105
I 105
 * Allocate a buffer.
 * The caller will assign it to a block.
E 105
 */
struct buf *
D 41
geteblk()
E 41
I 41
geteblk(size)
	int size;
E 41
{
D 2
	register struct buf *bp;
	register struct buf *dp;
E 2
I 2
D 6
	register struct buf *bp, *dp, *ep;
	register int i, x;
E 6
I 6
D 53
	register struct buf *bp, *dp;
I 37
	int s;
E 53
I 53
D 137
	register struct buf *bp, *flist;
E 137
I 137
	register struct buf *bp;
E 137
E 53
E 37
E 6
E 2

I 71
	if (size > MAXBSIZE)
		panic("geteblk: size too big");
E 71
D 88
loop:
E 88
D 4
	VOID spl6();
E 4
I 4
D 37
	(void) spl6();
E 37
I 37
D 53
	s = spl6();
E 37
E 4
D 18
	while (bfreelist.av_forw == &bfreelist) {
		bfreelist.b_flags |= B_WANTED;
		sleep((caddr_t)&bfreelist, PRIBIO+1);
E 18
I 18
	for (dp = &bfreelist[BQUEUES-1]; dp > bfreelist; dp--)
		if (dp->av_forw != dp)
			break;
	if (dp == bfreelist) {		/* no free blocks */
		dp->b_flags |= B_WANTED;
		sleep((caddr_t)dp, PRIBIO+1);
		goto loop;
E 18
	}
D 4
	VOID spl0();
E 4
I 4
D 37
	(void) spl0();
E 37
I 37
	splx(s);
E 37
E 4
D 18
	dp = &bfreelist;
	bp = bfreelist.av_forw;
E 18
I 18
	bp = dp->av_forw;
E 18
	notavail(bp);
	if (bp->b_flags & B_DELWRI) {
		bp->b_flags |= B_ASYNC;
		bwrite(bp);
		goto loop;
	}
I 2
D 16
	if (bp->b_dev != NODEV)
E 16
I 16
D 18
	if (bp->b_dev != NODEV) {
E 18
D 30
#ifdef EPAWNJ
E 30
I 30
D 45
#ifdef TRACE
E 45
E 30
D 18
		trace(TR_BRELSE, bp->b_dev, dbtofsb(bp->b_blkno));
E 18
I 18
D 34
	trace(TR_BRELSE, bp->b_dev, dbtofsb(bp->b_blkno));
E 34
I 34
	trace(TR_BRELSE, bp->b_dev, bp->b_blkno);
E 34
E 18
D 45
#endif
E 45
E 16
D 18
		bunhash(bp);
I 16
	}
E 16
E 2
	bp->b_flags = B_BUSY;
E 18
I 18
	bp->b_flags = B_BUSY|B_INVAL;
E 53
I 53
D 141
	bp = getnewbuf();
E 141
I 141
	while ((bp = getnewbuf(0, 0)) == NULL)
		/* void */;
E 141
	bp->b_flags |= B_INVAL;
E 53
E 18
D 45
	bp->b_back->b_forw = bp->b_forw;
	bp->b_forw->b_back = bp->b_back;
	bp->b_forw = dp->b_forw;
	bp->b_back = dp;
	dp->b_forw->b_back = bp;
	dp->b_forw = bp;
E 45
I 45
D 104
	bfree(bp);
E 104
	bremhash(bp);
D 53
	binshash(bp, dp);
E 53
I 53
D 137
	flist = &bfreelist[BQ_AGE];
E 137
I 137
	binshash(bp, &invalhash);
E 137
I 104
	bp->b_bcount = 0;
E 104
D 78
	binshash(bp, flist);
E 53
E 45
	bp->b_dev = (dev_t)NODEV;
E 78
I 78
D 88
	brelvp(bp);
E 88
E 78
I 74
#ifdef SECSIZE
	bp->b_blksize = DEV_BSIZE;
#endif SECSIZE
E 74
I 53
	bp->b_error = 0;
I 78
	bp->b_resid = 0;
D 137
	binshash(bp, flist);
E 137
E 78
E 53
I 41
D 46
	bp->b_bcount = size;
E 46
I 46
D 48
	brealloc(bp, size);
E 48
I 48
D 88
	if (brealloc(bp, size) == 0)
		goto loop;
E 88
I 88
D 104
	brealloc(bp, size);
E 104
I 104
	allocbuf(bp, size);
E 104
E 88
E 48
E 46
E 41
I 2
D 20
	bp->b_hlink = -1;
E 20
E 2
D 72
	return(bp);
E 72
I 72
	return (bp);
E 72
I 2
}

D 18
bunhash(bp)
	register struct buf *bp;
{
	register struct buf *ep;
D 12
	register int i, x;
E 12
I 12
	register int i, x, s;
E 12

	if (bp->b_dev == NODEV)
		return;
I 12
	s = spl6();
E 12
	i = BUFHASH(dbtofsb(bp->b_blkno));
	x = bp - buf;
	if (bufhash[i] == x) {
		bufhash[i] = bp->b_hlink;
D 12
		return;
E 12
I 12
		goto ret;
E 12
	}
	for (ep = &buf[bufhash[i]]; ep != &buf[-1];
	    ep = &buf[ep->b_hlink])
		if (ep->b_hlink == x) {
			ep->b_hlink = bp->b_hlink;
D 12
			return;
E 12
I 12
			goto ret;
E 12
		}
	panic("bunhash");
I 12
ret:
	splx(s);
E 12
E 2
}

E 18
/*
I 41
D 104
 * Allocate space associated with a buffer.
E 104
I 104
 * Expand or contract the actual memory allocated to a buffer.
D 105
 * If no memory is available, release buffer and take error exit
E 105
I 105
 * If no memory is available, release buffer and take error exit.
E 105
E 104
I 54
D 88
 * If can't get space, buffer is released
E 88
E 54
 */
D 104
brealloc(bp, size)
	register struct buf *bp;
E 104
I 104
allocbuf(tp, size)
	register struct buf *tp;
E 104
	int size;
{
D 104
	daddr_t start, last;
	register struct buf *ep;
	struct buf *dp;
	int s;
E 104
I 104
	register struct buf *bp, *ep;
	int sizealloc, take, s;
E 104

D 88
	/*
D 74
D 75
	 * First need to make sure that all overlaping previous I/O
E 75
I 75
	 * First need to make sure that all overlapping previous I/O
E 75
E 74
I 74
	 * First need to make sure that all overlapping previous I/O
E 74
	 * is dispatched with.
	 */
E 88
D 104
	if (size == bp->b_bcount)
D 48
		return;
D 46
	if (size < bp->b_bcount) {
		bp->b_bcount = size;
		return;
	}
E 46
I 46
	if (size < bp->b_bcount || bp->b_dev == NODEV)
E 48
I 48
D 88
		return (1);
	if (size < bp->b_bcount) { 
		if (bp->b_flags & B_DELWRI) {
D 78
			bwrite(bp);
E 78
I 78
			(void) bwrite(bp);
E 78
			return (0);
		}
		if (bp->b_flags & B_LOCKED)
			panic("brealloc");
E 48
D 53
		goto allocit;
E 53
I 53
D 54
		allocbuf(bp, size);
		return (1);
E 54
I 54
		return (allocbuf(bp, size));
E 54
E 53
D 48

E 46
	start = bp->b_blkno + (bp->b_bcount / DEV_BSIZE);
	last = bp->b_blkno + (size / DEV_BSIZE) - 1;
	if (bp->b_bcount == 0) {
		start++;
		if (start == last)
			goto allocit;
E 48
	}
I 48
	bp->b_flags &= ~B_DONE;
D 53
	if (bp->b_dev == NODEV)
		goto allocit;
E 53
I 53
D 54
	if (bp->b_dev == NODEV) {
		allocbuf(bp, size);
		return (1);
	}
E 54
I 54
D 78
	if (bp->b_dev == NODEV)
E 78
I 78
	if (bp->b_vp == (struct vnode *)0)
E 78
		return (allocbuf(bp, size));
E 54
E 53

I 65
D 78
	trace(TR_BREALLOC, pack(bp->b_dev, size), bp->b_blkno);
E 78
I 78
	trace(TR_BREALLOC,
	    pack(bp->b_vp->v_mount->m_fsid[0], size), bp->b_blkno);
E 78
E 65
	/*
	 * Search cache for any buffers that overlap the one that we
	 * are trying to allocate. Overlapping buffers must be marked
	 * invalid, after being written out if they are dirty. (indicated
	 * by B_DELWRI) A disk block must be mapped by at most one buffer
	 * at any point in time. Care must be taken to avoid deadlocking
	 * when two buffer are trying to get the same set of disk blocks.
	 */
	start = bp->b_blkno;
I 74
#ifdef SECSIZE
	last = start + size/bp->b_blksize - 1;
#else SECSIZE
E 74
D 61
	last = start + (size / DEV_BSIZE) - 1;
E 61
I 61
	last = start + btodb(size) - 1;
I 74
#endif SECSIZE
E 74
E 61
E 48
D 78
	dp = BUFHASH(bp->b_dev, bp->b_blkno);
E 78
I 78
	dp = BUFHASH(bp->b_vp, bp->b_blkno);
E 78
loop:
D 45
	(void) spl0();
E 45
	for (ep = dp->b_forw; ep != dp; ep = ep->b_forw) {
D 48
		if (ep->b_blkno < start || ep->b_blkno > last ||
		    ep->b_dev != bp->b_dev || ep->b_flags&B_INVAL)
E 48
I 48
D 78
		if (ep == bp || ep->b_dev != bp->b_dev || (ep->b_flags&B_INVAL))
E 78
I 78
		if (ep == bp || ep->b_vp != bp->b_vp ||
		    (ep->b_flags & B_INVAL))
E 78
E 48
			continue;
I 48
		/* look for overlap */
		if (ep->b_bcount == 0 || ep->b_blkno > last ||
I 74
#ifdef SECSIZE
		    ep->b_blkno + ep->b_bcount/ep->b_blksize <= start)
#else SECSIZE
E 74
D 61
		    ep->b_blkno + (ep->b_bcount / DEV_BSIZE) <= start)
E 61
I 61
		    ep->b_blkno + btodb(ep->b_bcount) <= start)
I 74
#endif SECSIZE
E 74
E 61
			continue;
D 53
if (bioprintfs)
if (ep->b_flags&B_BUSY)
printf("sleeping on:dev 0x%x, blks %d-%d, flg 0%o allocing dev 0x%x, blks %d-%d, flg 0%o\n",
ep->b_dev, ep->b_blkno, ep->b_blkno + (ep->b_bcount / DEV_BSIZE) - 1,
ep->b_flags, bp->b_dev, start, last, bp->b_flags);
E 53
E 48
D 72
		s = spl6();
E 72
I 72
		s = splbio();
E 72
		if (ep->b_flags&B_BUSY) {
			ep->b_flags |= B_WANTED;
			sleep((caddr_t)ep, PRIBIO+1);
D 45
			splx(s);
E 45
I 45
D 53
			(void) splx(s);
E 53
I 53
			splx(s);
E 53
E 45
			goto loop;
		}
D 45
		(void) spl0();
E 45
I 45
D 53
		(void) splx(s);
E 53
I 53
		splx(s);
E 53
E 45
D 48
		/*
		 * What we would really like to do is kill this
		 * I/O since it is now useless. We cannot do that
		 * so we force it to complete, so that it cannot
		 * over-write our useful data later.
		 */
E 48
I 48
		notavail(ep);
E 48
		if (ep->b_flags & B_DELWRI) {
D 48
			notavail(ep);
			ep->b_flags |= B_ASYNC;
E 48
I 48
D 53
if (bioprintfs)
printf("DELWRI:dev 0x%x, blks %d-%d, flg 0%o allocing dev 0x%x, blks %d-%d, flg 0%o\n",
ep->b_dev, ep->b_blkno, ep->b_blkno + (ep->b_bcount / DEV_BSIZE) - 1,
ep->b_flags, bp->b_dev, start, last, bp->b_flags);
E 53
E 48
D 78
			bwrite(ep);
E 78
I 78
			(void) bwrite(ep);
E 78
			goto loop;
		}
I 48
		ep->b_flags |= B_INVAL;
		brelse(ep);
E 48
	}
D 53
allocit:
E 53
I 53
D 54
	allocbuf(bp, size);
	return (1);
E 54
I 54
	return (allocbuf(bp, size));
E 88
I 88
		return;
	allocbuf(bp, size);
E 104
I 104
	sizealloc = roundup(size, CLBYTES);
	/*
	 * Buffer size does not change
	 */
	if (sizealloc == tp->b_bufsize)
		goto out;
	/*
	 * Buffer size is shrinking.
	 * Place excess space in a buffer header taken from the
	 * BQ_EMPTY buffer list and placed on the "most free" list.
	 * If no extra buffer headers are available, leave the
	 * extra space in the present buffer.
	 */
	if (sizealloc < tp->b_bufsize) {
D 137
		ep = bfreelist[BQ_EMPTY].av_forw;
		if (ep == &bfreelist[BQ_EMPTY])
E 137
I 137
D 138
		if ((ep = bufqueues[BQ_EMPTY].buffreehead) == NULL)
E 138
I 138
		if ((ep = bufqueues[BQ_EMPTY].qe_next) == NULL)
E 138
E 137
			goto out;
		s = splbio();
		bremfree(ep);
		ep->b_flags |= B_BUSY;
		splx(s);
		pagemove(tp->b_un.b_addr + sizealloc, ep->b_un.b_addr,
		    (int)tp->b_bufsize - sizealloc);
		ep->b_bufsize = tp->b_bufsize - sizealloc;
		tp->b_bufsize = sizealloc;
		ep->b_flags |= B_INVAL;
		ep->b_bcount = 0;
		brelse(ep);
		goto out;
	}
	/*
	 * More buffer space is needed. Get it out of buffers on
	 * the "most free" list, placing the empty headers on the
	 * BQ_EMPTY buffer header list.
	 */
	while (tp->b_bufsize < sizealloc) {
		take = sizealloc - tp->b_bufsize;
D 141
		bp = getnewbuf();
E 141
I 141
		while ((bp = getnewbuf(0, 0)) == NULL)
			/* void */;
E 141
		if (take >= bp->b_bufsize)
			take = bp->b_bufsize;
		pagemove(&bp->b_un.b_addr[bp->b_bufsize - take],
		    &tp->b_un.b_addr[tp->b_bufsize], take);
		tp->b_bufsize += take;
		bp->b_bufsize = bp->b_bufsize - take;
		if (bp->b_bcount > bp->b_bufsize)
			bp->b_bcount = bp->b_bufsize;
		if (bp->b_bufsize <= 0) {
			bremhash(bp);
D 137
			binshash(bp, &bfreelist[BQ_EMPTY]);
E 137
I 137
			binshash(bp, &invalhash);
E 137
D 105
			bp->b_dev = (dev_t)NODEV;
E 105
I 105
			bp->b_dev = NODEV;
E 105
			bp->b_error = 0;
			bp->b_flags |= B_INVAL;
		}
		brelse(bp);
	}
out:
	tp->b_bcount = size;
	return (1);
E 104
E 88
E 54
}

/*
D 62
 * Expand or contract the actual memory allocated to a buffer.
I 54
 * If no memory is available, release buffer and take error exit
E 54
 */
allocbuf(tp, size)
	register struct buf *tp;
	int size;
{
	register struct buf *bp, *ep;
	int sizealloc, take;
I 54
#ifdef sun
	register char *a;
	int osize;
#endif
E 54

I 54
#ifndef sun
E 54
	sizealloc = roundup(size, CLBYTES);
I 54
#else
	sizealloc = roundup(size, BUFALLOCSIZE);
#endif
E 54
E 53
	/*
D 53
	 * Here the buffer is already available, so all we
	 * need to do is set the size. Someday a better memory
	 * management scheme will be implemented.
E 53
I 53
	 * Buffer size does not change
E 53
	 */
D 53
	bp->b_bcount = size;
I 48
	return (1);
E 53
I 53
	if (sizealloc == tp->b_bufsize)
		goto out;
I 54
#ifndef sun
E 54
	/*
	 * Buffer size is shrinking.
	 * Place excess space in a buffer header taken from the
	 * BQ_EMPTY buffer list and placed on the "most free" list.
	 * If no extra buffer headers are available, leave the
	 * extra space in the present buffer.
	 */
	if (sizealloc < tp->b_bufsize) {
		ep = bfreelist[BQ_EMPTY].av_forw;
		if (ep == &bfreelist[BQ_EMPTY])
			goto out;
		notavail(ep);
		pagemove(tp->b_un.b_addr + sizealloc, ep->b_un.b_addr,
		    (int)tp->b_bufsize - sizealloc);
		ep->b_bufsize = tp->b_bufsize - sizealloc;
		tp->b_bufsize = sizealloc;
		ep->b_flags |= B_INVAL;
		ep->b_bcount = 0;
		brelse(ep);
		goto out;
	}
	/*
	 * More buffer space is needed. Get it out of buffers on
	 * the "most free" list, placing the empty headers on the
	 * BQ_EMPTY buffer header list.
	 */
	while (tp->b_bufsize < sizealloc) {
		take = sizealloc - tp->b_bufsize;
		bp = getnewbuf();
		if (take >= bp->b_bufsize)
			take = bp->b_bufsize;
		pagemove(&bp->b_un.b_addr[bp->b_bufsize - take],
		    &tp->b_un.b_addr[tp->b_bufsize], take);
		tp->b_bufsize += take;
		bp->b_bufsize = bp->b_bufsize - take;
		if (bp->b_bcount > bp->b_bufsize)
			bp->b_bcount = bp->b_bufsize;
		if (bp->b_bufsize <= 0) {
			bremhash(bp);
			binshash(bp, &bfreelist[BQ_EMPTY]);
			bp->b_dev = (dev_t)NODEV;
			bp->b_error = 0;
			bp->b_flags |= B_INVAL;
		}
		brelse(bp);
	}
I 54
#else
	/*
	 * Buffer size is shrinking
	 * Just put the tail end back in the map
	 */
	if (sizealloc < tp->b_bufsize) {
		rmfree(buffermap, (long)(tp->b_bufsize - sizealloc),
			(long)(tp->b_un.b_addr + sizealloc));
		tp->b_bufsize = sizealloc;
		goto out;
	}
	/*
	 * Buffer is being expanded or created
	 * If being expanded, attempt to get contiguous
	 * section, otherwise get a new chunk and copy.
	 * If no space, free up a buffer on the AGE list
	 * and try again.
	 */
	do {
		if ((osize = tp->b_bufsize)) {
			a = (char *)rmget(buffermap, (long)(sizealloc-osize),
				(long)(tp->b_un.b_addr + osize));
			if (a == 0) {
				a = (char *)rmalloc(buffermap, (long)sizealloc);
				if (a != 0) {
					bcopy(tp->b_un.b_addr, a, osize);
					rmfree(buffermap, (long)osize,
						(long)tp->b_un.b_addr);
					tp->b_un.b_addr = a;
				}
			}
		} else {
			a = (char *)rmalloc(buffermap, (long)sizealloc);
			if (a != 0)
				tp->b_un.b_addr = a;
		}
	} while (a == 0 && bfreemem());
	if (a == 0) {
		brelse(tp);
		return (0);
	}
	tp->b_bufsize = sizealloc;
#endif
E 54
out:
	tp->b_bcount = size;
I 54
	return (1);
E 54
E 53
E 48
}

/*
 * Release space associated with a buffer.
 */
bfree(bp)
	struct buf *bp;
{
D 54
	/*
D 53
	 * Here the buffer does not change, so all we
	 * need to do is set the size. Someday a better memory
	 * management scheme will be implemented.
E 53
I 53
	 * This stub is provided to allow the system to reclaim
	 * memory from the buffer pool. Currently we do not migrate
	 * memory between the buffer memory pool and the user memory
	 * pool.
E 53
	 */
E 54
I 54
#ifdef sun
	if (bp->b_bufsize) {
		rmfree(buffermap, (long)bp->b_bufsize, (long)bp->b_un.b_addr);
		bp->b_bufsize = 0;
	}
#endif
E 54
	bp->b_bcount = 0;
}

I 54
#ifdef sun
E 54
/*
I 54
 * Attempt to free up buffer space by flushing
 * something in the free list.
 * Don't wait for something, that could cause deadlocks
 * We start with BQ_AGE because we know BQ_EMPTY take no memory.
 */
bfreemem()
{
	register struct buf *bp, *dp;
	int s;

loop:
	s = spl6();
	for (dp = &bfreelist[BQ_AGE]; dp > bfreelist; dp--)
		if (dp->av_forw != dp)
			break;
	splx(s);
	if (dp == bfreelist) {		/* no free blocks */
		return (0);
	}
	bp = dp->av_forw;
	notavail(bp);
	if (bp->b_flags & B_DELWRI) {
		bp->b_flags |= B_ASYNC;
		bwrite(bp);
		goto loop;
	}
	trace(TR_BRELSE, bp->b_dev, bp->b_blkno);
	bp->b_flags = B_BUSY | B_INVAL;
	bfree(bp);
	bremhash(bp);
	binshash(bp, &bfreelist[BQ_EMPTY]);
	bp->b_dev = (dev_t)NODEV;
	bp->b_error = 0;
	brelse(bp);
	return (1);
}
#endif

/*
E 62
E 54
I 53
 * Find a buffer which is available for use.
 * Select something from a free list.
 * Preference is to AGE list, then LRU list.
 */
struct buf *
D 141
getnewbuf()
E 141
I 141
getnewbuf(slpflag, slptimeo)
	int slpflag, slptimeo;
E 141
{
D 137
	register struct buf *bp, *dp;
E 137
I 137
	register struct buf *bp;
D 138
	register struct bufqueue *dp;
E 138
I 138
	register struct queue_entry *dp;
E 138
E 137
I 83
	register struct ucred *cred;
E 83
	int s;
I 143
	struct buf *abp;
	static int losecnt = 0;
E 143

I 117
D 133
#ifdef LFS
	lfs_flush();
#endif
E 133
E 117
loop:
D 72
	s = spl6();
E 72
I 72
	s = splbio();
E 72
I 54
D 63
#ifndef sun
E 63
E 54
D 137
	for (dp = &bfreelist[BQ_AGE]; dp > bfreelist; dp--)
I 54
D 63
#else
	for (dp = &bfreelist[BQ_EMPTY]; dp > bfreelist; dp--)
#endif
E 63
E 54
		if (dp->av_forw != dp)
E 137
I 137
D 143
	for (dp = &bufqueues[BQ_AGE]; dp > bufqueues; dp--)
D 138
		if (dp->buffreehead)
E 138
I 138
		if (dp->qe_next)
E 138
E 137
			break;
E 143
I 143
	abp = NULL;
	for (dp = &bufqueues[BQ_AGE]; dp > bufqueues; dp--) {
		for (bp = dp->qe_next; bp; bp = bp->b_freelist.qe_next) {
			if (abp == NULL)
				abp = bp;
			if ((bp->b_flags & B_DELWRI) &&
			    bp->b_vp && VOP_ISLOCKED(bp->b_vp))
				continue;
			goto found;
		}
	}
E 143
D 137
	if (dp == bfreelist) {		/* no free blocks */
		dp->b_flags |= B_WANTED;
D 105
		sleep((caddr_t)dp, PRIBIO+1);
E 105
I 105
		sleep((caddr_t)dp, PRIBIO + 1);
E 137
I 137
	if (dp == bufqueues) {		/* no free blocks */
I 143
		if (abp) {
			bp = abp;
			bp->b_flags |= B_XXX;
			if (losecnt++ < 20) {
				vprint("skipping blkno check", bp->b_vp);
				printf("\tlblkno %d, blkno %d\n",
				   bp->b_lblkno, bp->b_blkno);
			}
			goto found;
		}
E 143
		needbuffer = 1;
D 141
		sleep((caddr_t)&needbuffer, PRIBIO + 1);
E 141
I 141
		(void) tsleep((caddr_t)&needbuffer, slpflag | (PRIBIO + 1),
			"getnewbuf", slptimeo);
E 141
E 137
E 105
I 57
		splx(s);
E 57
D 141
		goto loop;
E 141
I 141
		return (NULL);
E 141
	}
D 92
	splx(s);
E 92
D 137
	bp = dp->av_forw;
E 137
I 137
D 138
	bp = dp->buffreehead;
E 138
I 138
D 143
	bp = dp->qe_next;
E 143
I 143
found:
E 143
E 138
E 137
D 92
	notavail(bp);
E 92
I 92
	bremfree(bp);
	bp->b_flags |= B_BUSY;
	splx(s);
E 92
	if (bp->b_flags & B_DELWRI) {
D 81
		bp->b_flags |= B_ASYNC;
D 78
		bwrite(bp);
E 78
I 78
		(void) bwrite(bp);
E 81
I 81
		(void) bawrite(bp);
E 81
E 78
		goto loop;
	}
D 65
	trace(TR_BRELSE, bp->b_dev, bp->b_blkno);
E 65
I 65
D 78
	trace(TR_BRELSE, pack(bp->b_dev, bp->b_bufsize), bp->b_blkno);
E 78
I 78
D 96
	trace(TR_BRELSE,
D 88
	    pack(bp->b_vp->v_mount->m_fsid[0], bp->b_bufsize), bp->b_blkno);
	brelvp(bp);
E 88
I 88
	    pack(bp->b_vp->v_mount->m_fsid[0], bp->b_bufsize), bp->b_lblkno);
E 96
I 96
	trace(TR_BRELSE, pack(bp->b_vp, bp->b_bufsize), bp->b_lblkno);
E 96
	if (bp->b_vp)
		brelvp(bp);
E 88
I 83
	if (bp->b_rcred != NOCRED) {
		cred = bp->b_rcred;
		bp->b_rcred = NOCRED;
		crfree(cred);
	}
	if (bp->b_wcred != NOCRED) {
		cred = bp->b_wcred;
		bp->b_wcred = NOCRED;
		crfree(cred);
	}
E 83
E 78
E 65
	bp->b_flags = B_BUSY;
I 106
	bp->b_dirtyoff = bp->b_dirtyend = 0;
I 118
	bp->b_validoff = bp->b_validend = 0;
E 118
E 106
	return (bp);
}

/*
E 53
E 41
D 105
 * Wait for I/O completion on the buffer; return errors
 * to the user.
E 105
I 105
 * Wait for I/O to complete.
 *
 * Extract and return any errors associated with the I/O.
 * If the error flag is set, but no specific error is
 * given, return EIO.
E 105
 */
D 45
iowait(bp)
E 45
I 45
biowait(bp)
E 45
D 41
register struct buf *bp;
E 41
I 41
	register struct buf *bp;
E 41
{
I 37
	int s;
E 37

D 4
	VOID spl6();
E 4
I 4
D 37
	(void) spl6();
E 37
I 37
D 72
	s = spl6();
E 72
I 72
	s = splbio();
E 72
E 37
E 4
D 83
	while ((bp->b_flags&B_DONE)==0)
E 83
I 83
	while ((bp->b_flags & B_DONE) == 0)
E 83
		sleep((caddr_t)bp, PRIBIO);
D 4
	VOID spl0();
E 4
I 4
D 37
	(void) spl0();
E 37
I 37
	splx(s);
E 37
E 4
D 49
	geterror(bp);
E 49
I 49
D 56
	u.u_error = geterror(bp);
E 56
I 56
D 78
	if (u.u_error == 0)			/* XXX */
		u.u_error = geterror(bp);
E 78
I 78
D 105
	/*
	 * Pick up the device's error number and pass it to the user;
	 * if there is an error but the number is 0 set a generalized code.
	 */
E 105
	if ((bp->b_flags & B_ERROR) == 0)
		return (0);
	if (bp->b_error)
		return (bp->b_error);
	return (EIO);
E 78
E 56
E 49
}

D 25
#ifndef FASTVAX
E 25
I 25
D 45
#ifdef UNFAST
E 45
E 25
/*
D 45
 * Unlink a buffer from the available list and mark it busy.
 * (internal interface)
 */
notavail(bp)
register struct buf *bp;
{
	register s;

	s = spl6();
	bp->av_back->av_forw = bp->av_forw;
	bp->av_forw->av_back = bp->av_back;
	bp->b_flags |= B_BUSY;
	splx(s);
}
#endif

/*
E 45
D 62
 * Mark I/O complete on a buffer. If the header
 * indicates a dirty page push completion, the
 * header is inserted into the ``cleaned'' list
 * to be processed by the pageout daemon. Otherwise
 * release it if I/O is asynchronous, and wake 
 * up anyone waiting for it.
E 62
I 62
 * Mark I/O complete on a buffer.
D 105
 * If someone should be called, e.g. the pageout
 * daemon, do so.  Otherwise, wake up anyone
 * waiting for it.
E 105
I 105
 *
 * If a callback has been requested, e.g. the pageout
 * daemon, do so. Otherwise, awaken waiting processes.
E 105
E 62
 */
I 116
void
E 116
D 45
iodone(bp)
register struct buf *bp;
E 45
I 45
biodone(bp)
	register struct buf *bp;
E 45
{
I 92
D 111
	register struct vnode *vp;
E 111
E 92
D 60
	register int s;
E 60

I 10
	if (bp->b_flags & B_DONE)
D 45
		panic("dup iodone");
E 45
I 45
		panic("dup biodone");
E 45
E 10
	bp->b_flags |= B_DONE;
I 83
D 92
	if ((bp->b_flags & B_READ) == 0)
E 92
I 92
D 111
	if ((bp->b_flags & B_READ) == 0) {
E 92
		bp->b_dirtyoff = bp->b_dirtyend = 0;
I 92
		if (vp = bp->b_vp) {
			vp->v_numoutput--;
			if ((vp->v_flag & VBWAIT) && vp->v_numoutput <= 0) {
				if (vp->v_numoutput < 0)
					panic("biodone: neg numoutput");
				vp->v_flag &= ~VBWAIT;
				wakeup((caddr_t)&vp->v_numoutput);
			}
		}
	}
E 111
I 111
	if ((bp->b_flags & B_READ) == 0)
		vwakeup(bp);
E 111
E 92
E 83
D 60
	if (bp->b_flags & B_DIRTY) {
		if (bp->b_flags & B_ERROR)
			panic("IO err in push");
		s = spl6();
D 32
		cnt.v_pgout++;
E 32
		bp->av_forw = bclnlist;
		bp->b_bcount = swsize[bp - swbuf];
		bp->b_pfcent = swpf[bp - swbuf];
I 32
		cnt.v_pgout++;
		cnt.v_pgpgout += bp->b_bcount / NBPG;
E 32
		bclnlist = bp;
		if (bswlist.b_flags & B_WANTED)
			wakeup((caddr_t)&proc[2]);
		splx(s);
I 54
		return;
	}
E 60
	if (bp->b_flags & B_CALL) {
		bp->b_flags &= ~B_CALL;
		(*bp->b_iodone)(bp);
E 54
I 9
		return;
E 9
	}
D 105
	if (bp->b_flags&B_ASYNC)
E 105
I 105
	if (bp->b_flags & B_ASYNC)
E 105
		brelse(bp);
	else {
		bp->b_flags &= ~B_WANTED;
		wakeup((caddr_t)bp);
D 111
	}
}

/*
I 53
D 78
 * Insure that no part of a specified block is in an incore buffer.
E 78
I 78
D 91
 * Ensure that no part of a specified block is in an incore buffer.
E 78
I 75
#ifdef SECSIZE
D 88
 * "size" is given in device blocks (the units of b_blkno).
E 88
I 88
 * "size" is given in device blocks (the units of b_lblkno).
E 88
#endif SECSIZE
E 75
I 74
#ifdef SECSIZE
 * "size" is given in device blocks (the units of b_blkno).
#endif SECSIZE
E 74
 */
D 78
blkflush(dev, blkno, size)
	dev_t dev;
E 78
I 78
blkflush(vp, blkno, size)
	struct vnode *vp;
E 78
	daddr_t blkno;
I 74
#ifdef SECSIZE
	int size;
#else SECSIZE
E 74
	long size;
I 74
#endif SECSIZE
E 74
{
	register struct buf *ep;
	struct buf *dp;
D 86
	daddr_t start, last;
E 86
I 86
	daddr_t curblk, nextblk, ecurblk, lastblk;
E 86
D 78
	int s;
E 78
I 78
	int s, error, allerrors = 0;
E 78

D 86
	start = blkno;
I 74
#ifdef SECSIZE
	last = start + size - 1;
#else SECSIZE
E 74
D 61
	last = start + (size / DEV_BSIZE) - 1;
E 61
I 61
	last = start + btodb(size) - 1;
I 74
#endif SECSIZE
E 74
E 61
D 78
	dp = BUFHASH(dev, blkno);
E 78
I 78
	dp = BUFHASH(vp, blkno);
E 86
I 86
	/*
	 * Iterate through each possible hash chain.
	 */
	lastblk = blkno + btodb(size) - 1;
	for (curblk = blkno; curblk <= lastblk; curblk = nextblk) {
#if RND & (RND-1)
		nextblk = ((curblk / RND) + 1) * RND;
#else
		nextblk = ((curblk & ~(RND-1)) + RND);
#endif
		ecurblk = nextblk > lastblk ? lastblk : nextblk - 1;
		dp = BUFHASH(vp, curblk);
E 86
E 78
loop:
D 86
	for (ep = dp->b_forw; ep != dp; ep = ep->b_forw) {
D 78
		if (ep->b_dev != dev || (ep->b_flags&B_INVAL))
E 78
I 78
		if (ep->b_vp != vp || (ep->b_flags & B_INVAL))
E 78
			continue;
		/* look for overlap */
		if (ep->b_bcount == 0 || ep->b_blkno > last ||
I 74
#ifdef SECSIZE
		    ep->b_blkno + ep->b_bcount / ep->b_blksize <= start)
#else SECSIZE
E 74
D 61
		    ep->b_blkno + (ep->b_bcount / DEV_BSIZE) <= start)
E 61
I 61
		    ep->b_blkno + btodb(ep->b_bcount) <= start)
I 74
#endif SECSIZE
E 74
E 61
			continue;
D 72
		s = spl6();
E 72
I 72
		s = splbio();
E 72
		if (ep->b_flags&B_BUSY) {
			ep->b_flags |= B_WANTED;
			sleep((caddr_t)ep, PRIBIO+1);
E 86
I 86
		for (ep = dp->b_forw; ep != dp; ep = ep->b_forw) {
			if (ep->b_vp != vp || (ep->b_flags & B_INVAL))
				continue;
			/* look for overlap */
D 88
			if (ep->b_bcount == 0 || ep->b_blkno > ecurblk ||
			    ep->b_blkno + btodb(ep->b_bcount) <= curblk)
E 88
I 88
			if (ep->b_bcount == 0 || ep->b_lblkno > ecurblk ||
			    ep->b_lblkno + btodb(ep->b_bcount) <= curblk)
E 88
				continue;
			s = splbio();
			if (ep->b_flags&B_BUSY) {
				ep->b_flags |= B_WANTED;
				sleep((caddr_t)ep, PRIBIO+1);
				splx(s);
				goto loop;
			}
			if (ep->b_flags & B_DELWRI) {
				splx(s);
				notavail(ep);
				if (error = bwrite(ep))
					allerrors = error;
				goto loop;
			}
E 86
			splx(s);
D 86
			goto loop;
E 86
		}
D 86
		if (ep->b_flags & B_DELWRI) {
			splx(s);
			notavail(ep);
D 78
			bwrite(ep);
E 78
I 78
			if (error = bwrite(ep))
				allerrors = error;
E 78
			goto loop;
		}
		splx(s);
E 86
	}
I 78
	return (allerrors);
E 78
}

/*
E 91
E 53
D 45
 * Zero the core associated with a buffer.
 */
clrbuf(bp)
D 41
struct buf *bp;
E 41
I 41
	struct buf *bp;
E 41
{
D 41
	register *p;
	register c;
E 41
I 41
	register int *p;
	register int c;
E 41

	p = bp->b_un.b_words;
D 41
	c = BSIZE/sizeof(int);
E 41
I 41
	c = bp->b_bcount/sizeof(int);
E 41
	do
		*p++ = 0;
	while (--c);
	bp->b_resid = 0;
}

/*
E 45
D 43
 * swap I/O -
 *
 * If the flag indicates a dirty page push initiated
 * by the pageout daemon, we map the page into the i th
 * virtual page of process 2 (the daemon itself) where i is
 * the index of the swap header that has been allocated.
 * We simply initialize the header and queue the I/O but
 * do not wait for completion. When the I/O completes,
 * iodone() will link the header to a list of cleaned
 * pages to be processed by the pageout daemon.
 */
swap(p, dblkno, addr, nbytes, rdflg, flag, dev, pfcent)
	struct proc *p;
	swblk_t dblkno;
	caddr_t addr;
	int flag, nbytes;
	dev_t dev;
	unsigned pfcent;
{
	register struct buf *bp;
	register int c;
	int p2dp;
	register struct pte *dpte, *vpte;
I 37
	int s;
E 37

D 4
	VOID spl6();
E 4
I 4
D 37
	(void) spl6();
E 37
I 37
	s = spl6();
E 37
E 4
	while (bswlist.av_forw == NULL) {
		bswlist.b_flags |= B_WANTED;
		sleep((caddr_t)&bswlist, PSWP+1);
	}
	bp = bswlist.av_forw;
	bswlist.av_forw = bp->av_forw;
D 4
	VOID spl0();
E 4
I 4
D 37
	(void) spl0();
E 37
I 37
	splx(s);
E 37
E 4

	bp->b_flags = B_BUSY | B_PHYS | rdflg | flag;
	if ((bp->b_flags & (B_DIRTY|B_PGIN)) == 0)
		if (rdflg == B_READ)
			sum.v_pswpin += btoc(nbytes);
		else
			sum.v_pswpout += btoc(nbytes);
	bp->b_proc = p;
	if (flag & B_DIRTY) {
		p2dp = ((bp - swbuf) * CLSIZE) * KLMAX;
		dpte = dptopte(&proc[2], p2dp);
		vpte = vtopte(p, btop(addr));
		for (c = 0; c < nbytes; c += NBPG) {
			if (vpte->pg_pfnum == 0 || vpte->pg_fod)
				panic("swap bad pte");
			*dpte++ = *vpte++;
		}
		bp->b_un.b_addr = (caddr_t)ctob(p2dp);
	} else
		bp->b_un.b_addr = addr;
	while (nbytes > 0) {
		c = imin(ctob(120), nbytes);
		bp->b_bcount = c;
		bp->b_blkno = dblkno;
		bp->b_dev = dev;
I 11
		if (flag & B_DIRTY) {
			swpf[bp - swbuf] = pfcent;
			swsize[bp - swbuf] = nbytes;
		}
I 34
#ifdef TRACE
		trace(TR_SWAPIO, dev, bp->b_blkno);
#endif
E 34
E 11
D 8
		if (dev == swapdev)
			bp->b_blkno += swplo;
E 8
		(*bdevsw[major(dev)].d_strategy)(bp);
		if (flag & B_DIRTY) {
			if (c < nbytes)
				panic("big push");
D 11
			swsize[bp - swbuf] = nbytes;
			swpf[bp - swbuf] = pfcent;
E 11
			return;
		}
D 4
		VOID spl6();
E 4
I 4
D 37
		(void) spl6();
E 37
I 37
		s = spl6();
E 37
E 4
		while((bp->b_flags&B_DONE)==0)
			sleep((caddr_t)bp, PSWP);
D 4
		VOID spl0();
E 4
I 4
D 37
		(void) spl0();
E 37
I 37
		splx(s);
E 37
E 4
		bp->b_un.b_addr += c;
		bp->b_flags &= ~B_DONE;
		if (bp->b_flags & B_ERROR) {
			if ((flag & (B_UAREA|B_PAGET)) || rdflg == B_WRITE)
				panic("hard IO err in swap");
			swkill(p, (char *)0);
		}
		nbytes -= c;
		dblkno += btoc(c);
	}
D 4
	VOID spl6();
E 4
I 4
D 37
	(void) spl6();
E 37
I 37
	s = spl6();
E 37
E 4
	bp->b_flags &= ~(B_BUSY|B_WANTED|B_PHYS|B_PAGET|B_UAREA|B_DIRTY);
	bp->av_forw = bswlist.av_forw;
	bswlist.av_forw = bp;
	if (bswlist.b_flags & B_WANTED) {
		bswlist.b_flags &= ~B_WANTED;
		wakeup((caddr_t)&bswlist);
		wakeup((caddr_t)&proc[2]);
	}
D 4
	VOID spl0();
E 4
I 4
D 37
	(void) spl0();
E 37
I 37
	splx(s);
E 37
E 4
}

/*
 * If rout == 0 then killed on swap error, else
 * rout is the name of the routine where we ran out of
 * swap space.
 */
swkill(p, rout)
	struct proc *p;
	char *rout;
{
I 27
	char *mesg;
E 27

D 27
	printf("%d: ", p->p_pid);
E 27
I 27
	printf("pid %d: ", p->p_pid);
E 27
	if (rout)
D 27
		printf("out of swap space in %s\n", rout);
E 27
I 27
		printf(mesg = "killed due to no swap space\n");
E 27
	else
D 27
		printf("killed on swap error\n");
E 27
I 27
		printf(mesg = "killed on swap error\n");
	uprintf("sorry, pid %d was %s", p->p_pid, mesg);
E 27
	/*
	 * To be sure no looping (e.g. in vmsched trying to
	 * swap out) mark process locked in core (as though
	 * done by user) after killing it so noone will try
	 * to swap it out.
	 */
D 5
	psignal(p, SIGKIL);
E 5
I 5
	psignal(p, SIGKILL);
E 5
	p->p_flag |= SULOCK;
}

/*
E 43
D 62
 * make sure all write-behind blocks
E 62
I 62
D 78
 * Make sure all write-behind blocks
E 62
 * on dev (or NODEV for all)
 * are flushed out.
 * (from umount and update)
E 78
I 78
 * Make sure all write-behind blocks associated
D 83
 * with vp are flushed out (from sync).
E 83
I 83
 * with mount point are flushed out (from sync).
E 83
E 78
I 41
D 62
 * (and temporarily pagein)
E 62
E 41
 */
D 83
bflush(dev)
D 45
dev_t dev;
E 45
I 45
	dev_t dev;
E 83
I 83
D 88
bflush(mountp)
E 88
I 88
mntflushbuf(mountp, flags)
E 88
	struct mount *mountp;
I 88
	int flags;
E 88
E 83
E 45
{
D 88
	register struct buf *bp;
E 88
I 87
	register struct vnode *vp;
I 90
D 101
	struct vnode *nvp;
E 101
E 90
E 87
I 18
D 88
	register struct buf *flist;
E 88
I 88

I 99
D 100
	if ((mountp->m_flag & M_MPBUSY) == 0)
E 100
I 100
	if ((mountp->mnt_flag & MNT_MPBUSY) == 0)
E 100
		panic("mntflushbuf: not busy");
E 99
loop:
D 90
	for (vp = mountp->m_mounth; vp; vp = vp->v_mountf) {
E 90
I 90
D 100
	for (vp = mountp->m_mounth; vp; vp = nvp) {
E 100
I 100
D 101
	for (vp = mountp->mnt_mounth; vp; vp = nvp) {
E 100
		nvp = vp->v_mountf;
E 101
I 101
	for (vp = mountp->mnt_mounth; vp; vp = vp->v_mountf) {
I 110
		if (VOP_ISLOCKED(vp))
			continue;
E 110
E 101
E 90
		if (vget(vp))
			goto loop;
		vflushbuf(vp, flags);
		vput(vp);
I 101
		if (vp->v_mount != mountp)
			goto loop;
E 101
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
E 88
I 37
	int s;
E 37
E 18

loop:
D 4
	VOID spl6();
E 4
I 4
D 37
	(void) spl6();
E 37
I 37
D 72
	s = spl6();
E 72
I 72
	s = splbio();
E 72
E 37
E 4
D 18
	for (bp = bfreelist.av_forw; bp != &bfreelist; bp = bp->av_forw) {
E 18
I 18
D 53
	for (flist = bfreelist; flist < &bfreelist[BQUEUES]; flist++)
E 53
I 53
D 83
	for (flist = bfreelist; flist < &bfreelist[BQ_EMPTY]; flist++)
E 53
	for (bp = flist->av_forw; bp != flist; bp = bp->av_forw) {
E 18
D 45
		if (bp->b_flags&B_DELWRI && (dev == NODEV||dev==bp->b_dev)) {
E 45
I 45
		if ((bp->b_flags & B_DELWRI) == 0)
			continue;
		if (dev == NODEV || dev == bp->b_dev) {
E 45
D 81
			bp->b_flags |= B_ASYNC;
E 81
			notavail(bp);
D 78
			bwrite(bp);
E 78
I 78
D 81
			(void) bwrite(bp);
E 81
I 81
			(void) bawrite(bp);
E 81
E 78
I 58
			splx(s);
E 58
			goto loop;
		}
	}
D 4
	VOID spl0();
E 4
I 4
D 37
	(void) spl0();
E 37
I 37
	splx(s);
E 37
E 4
}
D 43

/*
 * Raw I/O. The arguments are
 *	The strategy routine for the device
 *	A buffer, which will always be a special buffer
 *	  header owned exclusively by the device for this purpose
 *	The device number
 *	Read/write flag
 * Essentially all the work is computing physical addresses and
 * validating them.
 * If the user has the proper access privilidges, the process is
 * marked 'delayed unlock' and the pages involved in the I/O are
 * faulted and locked. After the completion of the I/O, the above pages
 * are unlocked.
 */
physio(strat, bp, dev, rw, mincnt)
int (*strat)(); 
register struct buf *bp;
unsigned (*mincnt)();
{
	register int c;
	char *a;
I 37
	int s;
E 37

	if (useracc(u.u_base,u.u_count,rw==B_READ?B_WRITE:B_READ) == NULL) {
		u.u_error = EFAULT;
		return;
	}
D 4
	VOID spl6();
E 4
I 4
D 37
	(void) spl6();
E 37
I 37
	s = spl6();
E 37
E 4
	while (bp->b_flags&B_BUSY) {
		bp->b_flags |= B_WANTED;
		sleep((caddr_t)bp, PRIBIO+1);
	}
I 39
	splx(s);
E 39
	bp->b_error = 0;
	bp->b_proc = u.u_procp;
	bp->b_un.b_addr = u.u_base;
D 31
	while (u.u_count != 0 && bp->b_error==0) {
E 31
I 31
D 33
	while (u.u_count != 0 && (bp->b_flags&B_ERROR)==0) {
E 33
I 33
	while (u.u_count != 0) {
E 33
E 31
		bp->b_flags = B_BUSY | B_PHYS | rw;
		bp->b_dev = dev;
		bp->b_blkno = u.u_offset >> PGSHIFT;
		bp->b_bcount = u.u_count;
		(*mincnt)(bp);
		c = bp->b_bcount;
		u.u_procp->p_flag |= SPHYSIO;
		vslock(a = bp->b_un.b_addr, c);
		(*strat)(bp);
D 4
		VOID spl6();
E 4
I 4
		(void) spl6();
E 4
		while ((bp->b_flags&B_DONE) == 0)
			sleep((caddr_t)bp, PRIBIO);
		vsunlock(a, c, rw);
		u.u_procp->p_flag &= ~SPHYSIO;
		if (bp->b_flags&B_WANTED)
			wakeup((caddr_t)bp);
D 4
		VOID spl0();
E 4
I 4
D 37
		(void) spl0();
E 37
I 37
		splx(s);
E 37
E 4
		bp->b_un.b_addr += c;
		u.u_count -= c;
		u.u_offset += c;
I 33
		if (bp->b_flags&B_ERROR)
			break;
E 33
	}
	bp->b_flags &= ~(B_BUSY|B_WANTED|B_PHYS);
	u.u_count = bp->b_resid;
	geterror(bp);
}

/*ARGSUSED*/
unsigned
minphys(bp)
struct buf *bp;
{

D 39
	if (bp->b_bcount > 60 * 1024)
		bp->b_bcount = 60 * 1024;
E 39
I 39
D 40
	if (bp->b_bcount > 65 * 1024)
		bp->b_bcount = 65 * 1024;
E 40
I 40
	if (bp->b_bcount > 63 * 1024)
		bp->b_bcount = 63 * 1024;
E 40
E 39
}
I 41

E 43
E 41

I 78
#ifdef unused
E 78
/*
D 78
 * Pick up the device's error number and pass it to the user;
D 70
 * if there is an error but the number is 0 set a generalized
 * code.  Actually the latter is always true because devices
 * don't yet return specific errors.
E 70
I 70
 * if there is an error but the number is 0 set a generalized code.
E 78
I 78
 * Invalidate blocks associated with vp which are on the freelist.
 * Make sure all write-behind blocks associated with vp are flushed out.
E 78
E 70
 */
D 78
geterror(bp)
D 45
register struct buf *bp;
E 45
I 45
	register struct buf *bp;
E 78
I 78
binvalfree(vp)
	struct vnode *vp;
E 78
E 45
{
I 49
D 78
	int error = 0;
E 78
I 78
	register struct buf *bp;
	register struct buf *flist;
	int s;
E 78
E 49

D 78
	if (bp->b_flags&B_ERROR)
D 49
		if ((u.u_error = bp->b_error)==0)
			u.u_error = EIO;
E 49
I 49
		if ((error = bp->b_error)==0)
			return (EIO);
	return (error);
E 78
I 78
loop:
	s = splbio();
	for (flist = bfreelist; flist < &bfreelist[BQ_EMPTY]; flist++)
	for (bp = flist->av_forw; bp != flist; bp = bp->av_forw) {
		if (vp == (struct vnode *) 0 || vp == bp->b_vp) {
			if (bp->b_flags & B_DELWRI) {
E 83
I 83
D 88
	for (flist = bfreelist; flist < &bfreelist[BQ_EMPTY]; flist++) {
		for (bp = flist->av_forw; bp != flist; bp = bp->av_forw) {
			if ((bp->b_flags & B_BUSY))
				continue;
			if ((bp->b_flags & B_DELWRI) == 0)
				continue;
D 87
			if (bp->b_vp && bp->b_vp->v_mount == mountp) {
E 87
I 87
			if ((vp = bp->b_vp) == NULL)
				continue;
			if (vp->v_mount == mountp ||
			    (vp->v_type == VBLK && vp->v_mounton == mountp)) {
E 87
I 84
				splx(s);
E 84
E 83
D 81
				bp->b_flags |= B_ASYNC;
E 81
				notavail(bp);
D 83
				(void) splx(s);
E 83
D 81
				(void) bwrite(bp);
E 81
I 81
				(void) bawrite(bp);
E 81
D 83
			} else {
				bp->b_flags |= B_INVAL;
				brelvp(bp);
				(void) splx(s);
E 83
I 83
D 84
				splx(s);
E 84
				goto loop;
E 83
			}
E 88
I 88
D 92
	for (bp = vp->v_blockh; bp; bp = nbp) {
E 92
I 92
	for (bp = vp->v_dirtyblkhd; bp; bp = nbp) {
E 92
		nbp = bp->b_blockf;
		if ((bp->b_flags & B_BUSY))
			continue;
		if ((bp->b_flags & B_DELWRI) == 0)
D 92
			continue;
E 92
I 92
			panic("vflushbuf: not dirty");
		bremfree(bp);
		bp->b_flags |= B_BUSY;
E 92
		splx(s);
D 92
		notavail(bp);
		(void) bawrite(bp);
		goto loop;
E 92
I 92
		/*
		 * Wait for I/O associated with indirect blocks to complete,
		 * since there is no way to quickly wait for them below.
D 105
		 * NB - This is really specific to ufs, but is done here
E 105
I 105
		 * NB: This is really specific to ufs, but is done here
E 105
		 * as it is easier and quicker.
		 */
		if (bp->b_vp == vp || (flags & B_SYNC) == 0) {
			(void) bawrite(bp);
I 97
			s = splbio();
E 97
		} else {
			(void) bwrite(bp);
			goto loop;
		}
E 92
	}
I 89
	splx(s);
E 89
	if ((flags & B_SYNC) == 0)
		return;
D 92
wloop:
E 92
	s = splbio();
D 92
	for (bp = vp->v_blockh; bp; bp = nbp) {
		nbp = bp->b_blockf;
		if (bp->b_flags & B_BUSY) {
			bp->b_flags |= B_WANTED;
			sleep((caddr_t)bp, PRIBIO+1);
			splx(s);
			goto wloop;
E 88
D 83
			goto loop;
E 83
		}
I 88
D 89
		if ((bp->b_flags & B_DELWRI))
E 89
I 89
		if ((bp->b_flags & B_DELWRI)) {
			splx(s);
E 89
			goto loop;
I 89
		}
E 92
I 92
	while (vp->v_numoutput) {
		vp->v_flag |= VBWAIT;
D 105
		sleep((caddr_t)&vp->v_numoutput, PRIBIO+1);
E 105
I 105
		sleep((caddr_t)&vp->v_numoutput, PRIBIO + 1);
E 105
E 92
E 89
E 88
	}
I 89
	splx(s);
I 92
	if (vp->v_dirtyblkhd) {
		vprint("vflushbuf: dirty", vp);
		goto loop;
	}
E 92
E 89
D 83
	(void) splx(s);
E 83
I 83
D 88
	splx(s);
E 88
E 83
E 78
E 49
I 17
}
I 78
D 83
#endif /* unused */
E 83
E 78

/*
 * Invalidate in core blocks belonging to closed or umounted filesystem
 *
D 81
 * This is not nicely done at all - the buffer ought to be removed from the
 * hash chains & have its dev/blkno fields clobbered, but unfortunately we
 * can't do that here, as it is quite possible that the block is still
 * being used for i/o. Eventually, all disc drivers should be forced to
 * have a close routine, which ought ensure that the queue is empty, then
 * properly flush the queues. Until that happy day, this suffices for
 * correctness.						... kre
E 81
I 81
D 88
 * We walk through the buffer pool and invalidate any buffers for the
D 83
 * indicated device. Normally this routine is preceeded by a bflush
E 83
I 83
 * indicated mount point. Normally this routine is preceeded by a bflush
E 83
 * call, so that on a quiescent filesystem there will be no dirty
 * buffers when we are done. We return the count of dirty buffers when
 * we are finished.
E 88
I 88
 * Go through the list of vnodes associated with the file system;
 * for each vnode invalidate any buffers that it holds. Normally
 * this routine is preceeded by a bflush call, so that on a quiescent
 * filesystem there will be no dirty buffers when we are done. Binval
 * returns the count of dirty buffers when it is finished.
E 88
E 81
 */
D 83
binval(dev)
D 45
dev_t dev;
E 45
I 45
	dev_t dev;
E 83
I 83
D 88
binval(mountp)
E 88
I 88
mntinvalbuf(mountp)
E 88
	struct mount *mountp;
E 83
E 45
{
D 21
	register struct buf *bp, *dp;
E 21
I 21
D 88
	register struct buf *bp;
	register struct bufhd *hp;
E 88
I 87
	register struct vnode *vp;
I 90
D 101
	struct vnode *nvp;
E 101
E 90
I 88
	int dirty = 0;

I 99
D 100
	if ((mountp->m_flag & M_MPBUSY) == 0)
E 100
I 100
	if ((mountp->mnt_flag & MNT_MPBUSY) == 0)
E 100
		panic("mntinvalbuf: not busy");
E 99
loop:
D 90
	for (vp = mountp->m_mounth; vp; vp = vp->v_mountf) {
E 90
I 90
D 100
	for (vp = mountp->m_mounth; vp; vp = nvp) {
E 100
I 100
D 101
	for (vp = mountp->mnt_mounth; vp; vp = nvp) {
E 100
		nvp = vp->v_mountf;
E 101
I 101
	for (vp = mountp->mnt_mounth; vp; vp = vp->v_mountf) {
E 101
E 90
		if (vget(vp))
			goto loop;
		dirty += vinvalbuf(vp, 1);
		vput(vp);
I 101
		if (vp->v_mount != mountp)
			goto loop;
E 101
	}
	return (dirty);
}

/*
 * Flush out and invalidate all buffers associated with a vnode.
 * Called with the underlying object locked.
 */
vinvalbuf(vp, save)
	register struct vnode *vp;
	int save;
{
	register struct buf *bp;
D 92
	struct buf *nbp;
E 92
I 92
	struct buf *nbp, *blist;
E 92
E 88
E 87
I 81
D 82
	int dirty = 0;
E 82
I 82
	int s, dirty = 0;
E 82
E 81
D 88
#define dp ((struct buf *)hp)
E 88
E 21

I 83
D 92
loop:
D 84
	s = splbio();
E 84
E 83
I 78
D 81
loop:
E 78
D 21
	dp = bdevsw[major(dev)].d_tab;
D 18

E 18
	for (bp = dp->b_forw; bp != dp; bp = bp->b_forw)
		if (bp->b_dev == dev)
			bp->b_flags |= B_INVAL;
E 21
I 21
	for (hp = bufhash; hp < &bufhash[BUFHSZ]; hp++)
		for (bp = dp->b_forw; bp != dp; bp = bp->b_forw)
D 78
			if (bp->b_dev == dev)
E 78
I 78
			if (bp->b_dev == dev && (bp->b_flags & B_INVAL) == 0) {
E 78
				bp->b_flags |= B_INVAL;
I 78
				brelvp(bp);
				goto loop;
E 81
I 81
D 88
	for (hp = bufhash; hp < &bufhash[BUFHSZ]; hp++) {
		for (bp = dp->b_forw; bp != dp; bp = bp->b_forw) {
D 83
			if (bp->b_dev != dev || (bp->b_flags & B_INVAL))
E 83
I 83
D 87
			if (bp->b_vp == NULL || bp->b_vp->v_mount != mountp)
E 87
I 87
			if ((vp = bp->b_vp) == NULL)
				continue;
			if (vp->v_mount != mountp &&
			    (vp->v_type != VBLK || vp->v_mounton != mountp))
E 87
E 83
				continue;
I 84
			s = splbio();
E 84
I 82
D 83
		loop:
			s = splbio();
E 83
			if (bp->b_flags & B_BUSY) {
				bp->b_flags |= B_WANTED;
				sleep((caddr_t)bp, PRIBIO+1);
				splx(s);
				goto loop;
			}
E 88
I 88
	for (bp = vp->v_blockh; bp; bp = nbp) {
		nbp = bp->b_blockf;
		s = splbio();
		if (bp->b_flags & B_BUSY) {
			bp->b_flags |= B_WANTED;
			sleep((caddr_t)bp, PRIBIO+1);
E 92
I 92
	for (;;) {
		if (blist = vp->v_dirtyblkhd)
			/* void */;
		else if (blist = vp->v_cleanblkhd)
			/* void */;
		else
			break;
		for (bp = blist; bp; bp = nbp) {
			nbp = bp->b_blockf;
			s = splbio();
			if (bp->b_flags & B_BUSY) {
				bp->b_flags |= B_WANTED;
D 105
				sleep((caddr_t)bp, PRIBIO+1);
E 105
I 105
				sleep((caddr_t)bp, PRIBIO + 1);
E 105
				splx(s);
				break;
			}
			bremfree(bp);
			bp->b_flags |= B_BUSY;
E 92
E 88
I 84
			splx(s);
E 84
E 82
D 88
			notavail(bp);
E 88
I 88
D 92
			goto loop;
		}
		splx(s);
		notavail(bp);
		if (save) {
E 88
			if (bp->b_flags & B_DELWRI) {
E 92
I 92
			if (save && (bp->b_flags & B_DELWRI)) {
E 92
D 88
				(void) bawrite(bp);
E 88
				dirty++;
D 88
				continue;
E 88
I 88
				(void) bwrite(bp);
D 92
				goto loop;
E 92
I 92
				break;
E 92
E 88
E 81
			}
I 92
D 94
			bp->b_flags |= B_INVAL;
E 94
I 94
			if (bp->b_vp != vp)
				reassignbuf(bp, bp->b_vp);
			else
				bp->b_flags |= B_INVAL;
E 94
			brelse(bp);
E 92
I 81
D 88
			bp->b_flags |= B_INVAL;
			brelvp(bp);
			brelse(bp);
E 88
		}
I 88
D 92
		bp->b_flags |= B_INVAL;
		brelse(bp);
E 92
E 88
	}
I 88
D 92
	if (vp->v_blockh != 0)
E 92
I 92
	if (vp->v_dirtyblkhd || vp->v_cleanblkhd)
E 92
		panic("vinvalbuf: flush failed");
E 88
	return (dirty);
E 81
}

I 88
/*
 * Associate a buffer with a vnode.
 */
bgetvp(vp, bp)
	register struct vnode *vp;
	register struct buf *bp;
{

	if (bp->b_vp)
		panic("bgetvp: not free");
D 91
	VREF(vp);
E 91
I 91
	VHOLD(vp);
E 91
	bp->b_vp = vp;
	if (vp->v_type == VBLK || vp->v_type == VCHR)
		bp->b_dev = vp->v_rdev;
	else
		bp->b_dev = NODEV;
	/*
	 * Insert onto list for new vnode.
	 */
D 92
	if (vp->v_blockh) {
		bp->b_blockf = vp->v_blockh;
		bp->b_blockb = &vp->v_blockh;
		vp->v_blockh->b_blockb = &bp->b_blockf;
		vp->v_blockh = bp;
E 92
I 92
	if (vp->v_cleanblkhd) {
		bp->b_blockf = vp->v_cleanblkhd;
		bp->b_blockb = &vp->v_cleanblkhd;
		vp->v_cleanblkhd->b_blockb = &bp->b_blockf;
		vp->v_cleanblkhd = bp;
E 92
	} else {
D 92
		vp->v_blockh = bp;
		bp->b_blockb = &vp->v_blockh;
E 92
I 92
		vp->v_cleanblkhd = bp;
		bp->b_blockb = &vp->v_cleanblkhd;
E 92
		bp->b_blockf = NULL;
	}
}

/*
 * Disassociate a buffer from a vnode.
 */
E 88
brelvp(bp)
D 88
	struct buf *bp;
E 88
I 88
	register struct buf *bp;
E 88
{
I 88
	struct buf *bq;
E 88
	struct vnode *vp;

	if (bp->b_vp == (struct vnode *) 0)
D 88
		return;
E 88
I 88
		panic("brelvp: NULL");
	/*
	 * Delete from old vnode list, if on one.
	 */
	if (bp->b_blockb) {
		if (bq = bp->b_blockf)
			bq->b_blockb = bp->b_blockb;
		*bp->b_blockb = bq;
		bp->b_blockf = NULL;
		bp->b_blockb = NULL;
	}
E 88
	vp = bp->b_vp;
	bp->b_vp = (struct vnode *) 0;
D 91
	vrele(vp);
E 91
I 91
	HOLDRELE(vp);
E 91
I 88
}

/*
 * Reassign a buffer from one vnode to another.
 * Used to assign file specific control information
 * (indirect blocks) to the vnode to which they belong.
 */
reassignbuf(bp, newvp)
	register struct buf *bp;
	register struct vnode *newvp;
{
D 92
	register struct buf *bq;
E 92
I 92
	register struct buf *bq, **listheadp;
E 92

I 92
	if (newvp == NULL)
		panic("reassignbuf: NULL");
E 92
	/*
	 * Delete from old vnode list, if on one.
	 */
	if (bp->b_blockb) {
		if (bq = bp->b_blockf)
			bq->b_blockb = bp->b_blockb;
		*bp->b_blockb = bq;
	}
	/*
D 92
	 * Insert onto list for new vnode.
E 92
I 92
	 * If dirty, put on list of dirty buffers;
	 * otherwise insert onto list of clean buffers.
E 92
	 */
D 92
	if (newvp->v_blockh) {
		bp->b_blockf = newvp->v_blockh;
		bp->b_blockb = &newvp->v_blockh;
		newvp->v_blockh->b_blockb = &bp->b_blockf;
		newvp->v_blockh = bp;
E 92
I 92
	if (bp->b_flags & B_DELWRI)
		listheadp = &newvp->v_dirtyblkhd;
	else
		listheadp = &newvp->v_cleanblkhd;
	if (*listheadp) {
		bp->b_blockf = *listheadp;
		bp->b_blockb = listheadp;
		bp->b_blockf->b_blockb = &bp->b_blockf;
		*listheadp = bp;
E 92
	} else {
D 92
		newvp->v_blockh = bp;
		bp->b_blockb = &newvp->v_blockh;
E 92
I 92
		*listheadp = bp;
		bp->b_blockb = listheadp;
E 92
		bp->b_blockf = NULL;
E 111
	}
E 88
E 78
E 21
E 17
}
I 135

I 139
int
count_lock_queue()
{
	register struct buf *bp;
	register int ret;

	for (ret = 0, bp = (struct buf *)bufqueues[BQ_LOCKED].qe_next;
	    bp; bp = (struct buf *)bp->b_freelist.qe_next)
		++ret;
	return(ret);
}

E 139
#ifdef DIAGNOSTIC
/*
 * Print out statistics on the current allocation of the buffer pool.
 * Can be enabled to print out on every ``sync'' by setting "syncprt"
 * above.
 */
void
vfs_bufstats()
{
	int s, i, j, count;
D 137
	register struct buf *dp, *bp;
E 137
I 137
	register struct buf *bp;
D 138
	register struct bufqueue *dp;
E 138
I 138
	register struct queue_entry *dp;
E 138
E 137
	int counts[MAXBSIZE/CLBYTES+1];
	static char *bname[BQUEUES] = { "LOCKED", "LRU", "AGE", "EMPTY" };

D 137
	for (dp = bfreelist, i = 0; dp < &bfreelist[BQUEUES]; dp++, i++) {
E 137
I 137
	for (dp = bufqueues, i = 0; dp < &bufqueues[BQUEUES]; dp++, i++) {
E 137
		count = 0;
		for (j = 0; j <= MAXBSIZE/CLBYTES; j++)
			counts[j] = 0;
		s = splbio();
D 137
		for (bp = dp->av_forw; dp != bp; bp = bp->av_forw) {
E 137
I 137
D 138
		for (bp = dp->buffreehead; bp; bp = bp->b_actf) {
E 138
I 138
		for (bp = dp->qe_next; bp; bp = bp->b_freelist.qe_next) {
E 138
E 137
			counts[bp->b_bufsize/CLBYTES]++;
			count++;
		}
		splx(s);
		printf("%s: total-%d", bname[i], count);
		for (j = 0; j <= MAXBSIZE/CLBYTES; j++)
			if (counts[j] != 0)
				printf(", %d-%d", j * CLBYTES, counts[j]);
		printf("\n");
	}
}
#endif /* DIAGNOSTIC */
E 144
E 135
E 1
