h13428
s 00001/00001/01003
d D 8.15 95/06/16 12:27:51 mckusick 159 158
c don't know last useful entry when whiteout found (from John Kohl)
e
s 00004/00002/01000
d D 8.14 95/05/27 22:19:58 mckusick 158 157
c read-only checking must be done by the filesystem layers
e
s 00001/00000/01001
d D 8.13 95/05/17 11:28:25 mckusick 157 156
c allow anyone to remove symbolic links from sticky directories
e
s 00015/00014/00986
d D 8.12 95/05/14 00:25:10 mckusick 156 155
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00003/00003/00997
d D 8.11 95/01/02 23:09:48 mckusick 155 154
c minor cleanups (from mycroft)
e
s 00002/00001/00998
d D 8.10 94/12/30 14:52:46 mckusick 154 153
c make sure type is valid (needed for little-endian machines)
e
s 00002/00005/00997
d D 8.9 94/08/11 00:38:03 mckusick 153 151
c no longer need DT_WHTD
e
s 00001/00004/00998
d R 8.9 94/08/11 00:23:03 mckusick 152 151
c no longer need DT_WHTD
e
s 00080/00024/00922
d D 8.8 94/07/28 03:38:53 pendry 151 150
c changes for whiteouts and union filesystem
e
s 00002/00000/00944
d D 8.7 94/05/29 09:53:24 mckusick 150 149
c don't check name of directory entries with zero'ed ino (from mycroft@sun-lamp.cs.berkeley.edu)
e
s 00001/00001/00943
d D 8.6 94/04/01 08:34:31 bostic 149 148
c iget() is gone, VFS_VGET is loading the vnode
e
s 00005/00000/00939
d D 8.5 94/01/21 17:30:54 bostic 148 147
c add USL's copyright notice
e
s 00002/00002/00937
d D 8.4 93/12/30 16:08:03 mckusick 147 146
c vget now locks optionally
e
s 00010/00010/00929
d D 8.3 93/09/23 16:04:16 bostic 146 145
c changes for 4.4BSD-Lite requested by USL
e
s 00008/00008/00931
d D 8.2 93/09/21 07:22:09 bostic 145 144
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00937
d D 8.1 93/06/11 16:29:05 bostic 144 143
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00004/00938
d D 7.53 93/04/27 14:09:22 mckusick 143 142
c update comments to reflect reality
e
s 00040/00038/00902
d D 7.52 92/11/14 23:21:40 mckusick 142 141
c replace use of ILOCK and IUNLOCK with VOP_LOCK and VOP_UNLOCK
e
s 00002/00002/00938
d D 7.51 92/07/13 23:03:19 mckusick 141 140
c cache_lookup may change cn_flags, so have to check that value
e
s 00007/00019/00933
d D 7.50 92/07/03 01:43:15 mckusick 140 139
c delete USES; VOP_VGET => VFS_VGET
e
s 00069/00021/00883
d D 7.49 92/07/02 17:23:13 mckusick 139 138
c compatibility with old or new style directories
e
s 00071/00075/00833
d D 7.48 92/06/27 18:00:20 mckusick 138 137
c cleanup after heidemann
e
s 00007/00002/00901
d D 7.47 92/06/25 13:19:15 mckusick 137 136
c add parameters to lookup; new parameters to VOP_TRUNCATE
e
s 00063/00069/00840
d D 7.46 92/05/15 13:53:54 heideman 136 135
c vnodeop argument macro expansion
e
s 00024/00008/00885
d D 7.45 92/05/14 17:27:35 heideman 135 122
c vnode interface conversion
e
s 00024/00008/00885
d R 7.45 92/05/14 17:03:36 heideman 134 122
c vnode interface conversion
e
s 00024/00008/00885
d R 7.45 92/05/14 16:44:30 heideman 133 122
c vnode interface conversion
e
s 00024/00008/00885
d R 7.45 92/05/14 16:34:27 heideman 132 122
c vnode interface conversion
e
s 00024/00008/00885
d R 7.45 92/05/14 15:53:23 heideman 131 122
c vnode interface conversion
e
s 00024/00008/00885
d R 7.45 92/05/14 15:40:35 heideman 130 122
c vnode interface conversion
e
s 00024/00008/00885
d R 7.45 92/05/14 14:46:38 heideman 129 122
c vnode interface conversion
e
s 00024/00008/00885
d R 7.45 92/05/14 12:49:39 heideman 128 122
c vnode interface conversion
e
s 00024/00008/00885
d R 7.45 92/05/14 11:46:47 heideman 127 122
c vnode interface conversion
e
s 00024/00008/00885
d R 7.45 92/05/14 10:27:26 heideman 126 122
c vnode interface conversion
e
s 00044/00008/00885
d R 7.45 92/05/13 23:05:40 heideman 125 122
c vnode interface conversion
e
s 00044/00008/00885
d R 7.45 92/05/13 18:52:58 heideman 124 122
c vnode interface conversion
e
s 00044/00008/00885
d R 7.45 92/05/13 18:25:03 heideman 123 122
c vnode interface conversion
e
s 00001/00001/00892
d D 7.44 92/04/21 14:46:22 mckusick 122 121
c have to pass down cred to block allocation routines
e
s 00022/00020/00871
d D 7.43 92/03/27 15:52:40 mckusick 121 120
c define doff_t for size of directory offsets
e
s 00003/00002/00888
d D 7.42 92/03/15 12:26:12 mckusick 120 119
c extra assignments to shut up GCC warnings (for torek)
e
s 00001/00000/00889
d D 7.41 92/03/02 16:43:38 mckusick 119 118
c disallow creation of files in removed directories
e
s 00002/00002/00887
d D 7.40 92/02/21 15:56:01 heideman 118 117
c clean up comment
e
s 00091/00097/00798
d D 7.39 92/02/04 14:32:54 mckusick 117 116
c ufs specific fields move from nameidata into the inode
e
s 00003/00005/00892
d D 7.38 92/02/03 16:54:28 heideman 116 115
c convert to CN
e
s 00143/00136/00754
d D 7.37 92/01/22 09:38:37 heideman 115 114
c lookup converted to new form
e
s 00002/00002/00888
d D 7.36 91/12/14 21:31:39 mckusick 114 113
c statfs.f_bsize => statfs.f_iosize; statfs.f_fsize => statfs.f_bsize (for SunOS)
e
s 00040/00049/00850
d D 7.35 91/11/05 14:36:57 mckusick 113 112
c reorganization to move ufsmount ops to be vnode ops
e
s 00124/00111/00775
d D 7.34 91/11/01 18:07:06 bostic 112 111
c UFS/FFS split for LFS version 1; move blockatoff into FFS/LFS
e
s 00002/00001/00884
d D 7.33 91/05/19 13:31:37 mckusick 111 110
c have to set the offset in the uio now
e
s 00137/00119/00748
d D 7.32 91/05/15 20:18:19 mckusick 110 109
c new naming scheme for ufs specific data in namei
e
s 00004/00000/00863
d D 7.31 91/04/16 14:50:30 mckusick 109 108
c extensive checking of directories only when DIIAGNOSTIC set
e
s 00002/00001/00861
d D 7.30 91/04/16 11:16:33 mckusick 108 107
c do not panic on "bad dir" if filesystem is mounted read-only
e
s 00009/00008/00853
d D 7.29 91/04/16 00:10:05 mckusick 107 106
c add proc pointers to appropriate VOP and vnode operations
e
s 00005/00004/00856
d D 7.28 91/03/19 10:30:35 karels 106 105
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; remove ../ufs/ from includes; consolidate *nullops();
c chown/fchmod use proc's credentials, not file's
e
s 00010/00005/00850
d D 7.27 91/03/11 18:33:38 mckusick 105 104
c setup uio vectors explicitly as they are no longer statically allocated;
c reset directory link counts on I/O failure
e
s 00008/00004/00847
d D 7.26 91/02/28 13:23:30 mckusick 104 103
c cache open with O_CREAT when the name already exists
e
s 00001/00001/00850
d D 7.25 91/02/21 23:00:43 mckusick 103 102
c fixes for multiple calls to namei (for rename in NFS)
e
s 00002/00000/00849
d D 7.24 91/01/10 23:47:30 mckusick 102 101
c delete paranoid check
e
s 00001/00011/00848
d D 7.23 90/06/28 22:30:44 bostic 101 100
c new copyright notice
e
s 00004/00002/00855
d D 7.22 90/06/19 17:10:54 mckusick 100 99
c mark inode dirty to force size update
e
s 00032/00033/00825
d D 7.21 90/05/02 19:31:19 mckusick 99 98
c iaccess => ufs_access; merge vp and vdp
e
s 00003/00000/00855
d D 7.20 90/01/03 18:26:39 mckusick 98 97
c paranoia, make sure that the uioseg flag is set properly
e
s 00002/00009/00853
d D 7.19 89/11/30 22:57:27 mckusick 97 96
c blkatoff looks up in logical buffer cache; itrunc adds IO_SYNC flag
e
s 00001/00000/00861
d D 7.18 89/11/24 19:50:46 mckusick 96 95
c make dirbad a panic
e
s 00009/00007/00852
d D 7.17 89/11/22 21:50:20 mckusick 95 94
c writeip and rdwri are gone, use ufs_write and vn_rdwr instead
e
s 00011/00007/00848
d D 7.16 89/10/29 23:26:39 mckusick 94 93
c use vget instead of igrab
e
s 00004/00003/00851
d D 7.15 89/10/13 18:24:21 mckusick 93 92
c no need to check for .. through root after cache lookup
e
s 00004/00005/00850
d D 7.14 89/10/13 16:05:49 mckusick 92 91
c avoid referencing uninitialized pointer
e
s 00001/00001/00854
d D 7.13 89/08/26 14:12:26 mckusick 91 90
c generalize the buffer pool so that NFS can become a client
e
s 00026/00007/00829
d D 7.12 89/08/26 00:10:01 mckusick 90 89
c update for soft references and negative cacheing
e
s 00003/00003/00833
d D 7.11 89/06/27 19:18:05 mckusick 89 88
c update reference counts on vnodes using VREF
e
s 00003/00000/00833
d D 7.10 89/06/24 13:03:09 mckusick 88 87
c have to set the base before each uio
e
s 00009/00011/00824
d D 7.9 89/06/07 16:45:17 mckusick 87 86
c use uio structure in nameidata rather than constructing a new one
e
s 00004/00001/00831
d D 7.8 89/05/14 15:21:40 mckusick 86 85
c LOCKPARENT flag means lock parent even on lookup
e
s 00233/00673/00599
d D 7.7 89/05/09 20:42:39 mckusick 85 84
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
D 144
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 144
I 144
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 148
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 148
E 144
E 85
 *
I 85
D 101
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
E 101
I 101
 * %sccs.include.redist.c%
E 101
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
D 112
#include "param.h"
D 85
#include "systm.h"
#include "inode.h"
#include "fs.h"
#include "mount.h"
#include "dir.h"
E 85
D 106
#include "user.h"
E 106
I 106
#include "namei.h"
E 106
#include "buf.h"
D 85
#include "conf.h"
#include "uio.h"
#include "kernel.h"
I 81
#include "malloc.h"
I 84
#ifdef KTRACE
#include "proc.h"
#include "ktrace.h"
#endif
E 85
I 85
#include "file.h"
#include "vnode.h"
E 112
I 112
#include <sys/param.h>
#include <sys/namei.h>
#include <sys/buf.h>
#include <sys/file.h>
#include <sys/mount.h>
#include <sys/vnode.h>
E 112
I 99
D 106
#include "../ufs/quota.h"
E 99
#include "../ufs/inode.h"
#include "../ufs/fs.h"
E 106
I 106

D 112
#include "quota.h"
#include "inode.h"
I 110
#include "dir.h"
E 110
#include "fs.h"
E 112
I 112
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/dir.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/ufs_extern.h>
E 112
E 106
E 85
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
E 85
I 85
D 90
struct	vnode *cache_lookup();
E 90
struct	nchstats nchstats;
I 109
#ifdef DIAGNOSTIC
E 109
E 85
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
I 109
#else
int	dirchk = 0;
#endif
E 109
E 84
I 48

I 139
#define FSFMT(vp)	((vp)->v_mount->mnt_maxsymlinklen <= 0)

E 139
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
E 85
I 85
 * Convert a component of a pathname into a pointer to a locked inode.
E 85
E 76
 * This is a very central and rather complicated routine.
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
 * If the file system is not maintained in a strict tree hierarchy,
D 76
 * this can result in a deadlock situation.  When creating and
E 76
I 76
 * this can result in a deadlock situation (see comments in code below).
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
D 115
 * The flag argument is LOOKUP, CREATE, RENAME, or DELETE depending on
E 115
I 115
D 121
 * The cnp->cn_nameiop argument is LOOKUP, CREATE, RENAME, or DELETE depending on
E 115
 * whether the name is to be looked up, created, renamed, or deleted.
E 121
I 121
 * The cnp->cn_nameiop argument is LOOKUP, CREATE, RENAME, or DELETE depending
 * on whether the name is to be looked up, created, renamed, or deleted.
E 121
 * When CREATE, RENAME, or DELETE is specified, information usable in
 * creating, renaming, or deleting a directory entry may be calculated.
 * If flag has LOCKPARENT or'ed into it and the target of the pathname
 * exists, lookup returns both the target and its parent directory locked.
 * When creating or renaming and LOCKPARENT is specified, the target may
 * not be ".".  When deleting and LOCKPARENT is specified, the target may
D 142
 * be "."., but the caller must check to ensure it does an vrele and iput
 * instead of two iputs.
E 142
I 142
 * be "."., but the caller must check to ensure it does an vrele and vput
 * instead of two vputs.
E 142
E 85
 *
D 57
 * The follow argument is 1 when symbolic links are to be followed
E 57
I 57
D 85
 * The FOLLOW flag is set when symbolic links are to be followed
E 57
 * when they occur at the end of the name translation process.
I 76
 * Symbolic links are always followed for all other pathname
 * components other than the last.
E 85
I 85
 * Overall outline of ufs_lookup:
E 85
E 76
 *
I 76
D 85
 * The segflg defines whether the name is to be copied from user
 * space or kernel space.
 *
E 76
E 34
D 48
 * Overall outline:
E 48
I 48
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
 * dirloop:
E 85
 *	check accessibility of directory
D 85
 * dirloop2:
D 57
 *	copy next component of name to u.u_dent
E 57
I 57
 *	copy next component of name to ndp->ni_dent
E 57
 *	handle degenerate case where name is null string
E 85
I 48
 *	look for name in cache, if found, then if at end of path
D 85
 *	  and deleting or creating, drop it, else to haveino
E 85
I 85
 *	  and deleting or creating, drop it, else return name
E 85
E 48
 *	search for name in directory, to found or notfound
 * notfound:
D 34
 *	if creating, return locked inode, leaving information on avail. slots
E 34
I 34
D 85
 *	if creating, return locked directory, leaving info on avail. slots
E 85
I 85
 *	if creating, return locked directory, leaving info on available slots
E 85
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
D 85
 *	if at end of path and rewriting (CREATE and LOCKPARENT), lock target
E 85
I 85
 *	if at end of path and rewriting (RENAME and LOCKPARENT), lock target
E 85
E 76
E 48
 *	  inode and return info to allow rewrite
E 34
D 85
 *	if .. and on mounted filesys, look in mount table for parent
E 85
I 48
D 76
 *	if not at end, if neither creating nor deleting, add name to cache
E 76
I 76
 *	if not at end, add name to cache; if at end and neither creating
 *	  nor deleting, add name to cache
E 76
D 85
 * haveino:
E 48
 *	if symbolic link, massage name in buffer and continue at dirloop
 *	if more components of name, do next level at dirloop
 *	return the answer as locked inode
E 85
I 34
D 143
 *
D 85
 * NOTE: (LOOKUP | LOCKPARENT) currently returns the parent inode,
 *	 but unlocked.
E 85
I 85
 * NOTE: (LOOKUP | LOCKPARENT) currently returns the parent inode unlocked.
E 143
E 85
E 34
E 23
E 13
 */
I 112
int
E 112
D 85
struct inode *
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
namei(ndp)
E 85
I 85
D 99
ufs_lookup(vp, ndp)
	struct vnode *vp;
E 99
I 99
D 107
ufs_lookup(vdp, ndp)
E 107
I 107
D 115
ufs_lookup(vdp, ndp, p)
E 107
	register struct vnode *vdp;
E 99
E 85
	register struct nameidata *ndp;
I 107
	struct proc *p;
E 115
I 115
D 116
ufs_lookup(dvp, vpp, cnp)   /* converted to CN */
E 116
I 116
D 135
ufs_lookup(dvp, vpp, cnp)
E 116
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
E 135
I 135
D 140
ufs_lookup (ap)
E 140
I 140
ufs_lookup(ap)
E 140
D 137
	struct vop_lookup_args *ap;
E 137
I 137
	struct vop_lookup_args /* {
D 138
		struct vnode * a_dvp;
		struct vnode ** a_vpp;
		struct componentname * a_cnp;
E 138
I 138
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
E 138
	} */ *ap;
E 137
D 136
#define dvp (ap->a_dvp)
#define vpp (ap->a_vpp)
#define cnp (ap->a_cnp)
E 136
E 135
E 115
E 107
E 57
E 13
E 12
{
I 135
D 140
	USES_VOP_ACCESS;
	USES_VOP_BLKATOFF;
	USES_VOP_VGET;
E 140
E 135
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
D 85
	register char *cp;		/* pointer into pathname argument */
/* these variables refer to things which must be freed or unlocked */
E 85
I 85
D 99
	register struct vnode *vdp;	/* vnode copy of dp */
E 99
E 85
D 93
	register struct inode *dp = 0;	/* the directory we are searching */
E 93
I 93
D 138
	register struct inode *dp;	/* the directory we are searching */
E 138
I 138
	register struct vnode *vdp;	/* vnode for directory being searched */
	register struct inode *dp;	/* inode for directory being searched */
E 138
E 93
I 48
D 74
	register struct nch *ncp;	/* cache slot for entry */
E 74
I 74
D 85
	register struct namecache *ncp;	/* cache slot for entry */
E 85
E 74
E 48
D 112
	register struct fs *fs;		/* file system that directory is in */
D 85
	register struct buf *bp = 0;	/* a buffer of directory entries */
E 85
I 85
	struct buf *bp = 0;		/* a buffer of directory entries */
E 112
I 112
D 113
	register struct ufsmount *ump;	/* file system that directory is in */
E 113
	struct buf *bp;			/* a buffer of directory entries */
E 112
E 85
	register struct direct *ep;	/* the current directory entry */
	int entryoffsetinblock;		/* offset of ep in bp's buffer */
D 81
	register struct buf *nbp;	/* buffer storing path name argument */
E 81
I 81
D 85
	register caddr_t nbp;		/* buffer storing path name argument */
E 81
/* these variables hold information about the search for a slot */
E 85
	enum {NONE, COMPACT, FOUND} slotstatus;
D 112
	int slotoffset = -1;		/* offset of area with free space */
E 112
I 112
D 121
	int slotoffset;			/* offset of area with free space */
E 121
I 121
	doff_t slotoffset;		/* offset of area with free space */
E 121
E 112
	int slotsize;			/* size of area at slotoffset */
	int slotfreespace;		/* amount of space free in slot */
	int slotneeded;			/* size of the entry we're seeking */
D 85
/* */
E 85
D 47
	int dirsize;
E 47
I 47
	int numdirpasses;		/* strategy for directory search */
D 121
	int endsearch;			/* offset to end directory search */
E 47
D 57
	int prevoff;			/* u.u_offset of previous entry */
E 57
I 57
D 110
	int prevoff;			/* ndp->ni_offset of previous entry */
E 110
I 110
D 112
	int prevoff;			/* ndp->ni_ufs.ufs_offset of previous entry */
E 112
I 112
D 117
	int prevoff;			/* prev entry ndp->ni_ufs.ufs_offset */
E 117
I 117
	int prevoff;			/* prev entry dp->i_offset */
E 121
I 121
	doff_t endsearch;		/* offset to end directory search */
	doff_t prevoff;			/* prev entry dp->i_offset */
E 121
E 117
E 112
E 110
E 57
D 85
	int nlink = 0;			/* number of symbolic links taken */
E 85
D 142
	struct inode *pdp;		/* saved dp during symlink work */
E 142
I 142
	struct vnode *pdp;		/* saved dp during symlink work */
E 142
D 57
	int i;
E 57
I 57
D 85
	int error, i;
E 57
I 34
	int lockparent;
I 48
D 67
	int docache;
E 67
I 67
	int docache;			/* == 0 do not cache last component */
	int makeentry;			/* != 0 if name to be added to cache */
E 67
	unsigned hash;			/* value of name hash for entry */
	union nchash *nhp;		/* cache chain head for entry */
	int isdotdot;			/* != 0 if current name is ".." */
I 57
	int flag;			/* op ie, LOOKUP, CREATE, or DELETE */
E 85
I 85
D 113
	struct inode *tdp;		/* returned by iget */
E 113
I 113
D 140
	struct vnode *tdp;		/* returned by VOP_VGET */
E 140
I 140
	struct vnode *tdp;		/* returned by VFS_VGET */
E 140
E 113
E 85
I 63
D 121
	off_t enduseful;		/* pointer past last used dir slot */
E 121
I 121
	doff_t enduseful;		/* pointer past last used dir slot */
E 121
I 112
	u_long bmask;			/* block offset mask */
E 112
I 85
D 115
	int flag;			/* LOOKUP, CREATE, RENAME, or DELETE */
E 115
	int lockparent;			/* 1 => lockparent flag is set */
	int wantparent;			/* 1 => wantparent or lockparent flag */
D 139
	int error;
E 139
I 139
	int namlen, error;
E 139
I 115
D 136
	struct vnode *vdp = dvp;	/* saved for one special case */
E 136
I 136
D 138
	struct vnode *vdp = ap->a_dvp;	/* saved for one special case */
E 138
I 138
	struct vnode **vpp = ap->a_vpp;
	struct componentname *cnp = ap->a_cnp;
	struct ucred *cred = cnp->cn_cred;
	int flags = cnp->cn_flags;
	int nameiop = cnp->cn_nameiop;
I 156
	struct proc *p = cnp->cn_proc;
E 156
E 138
E 136
E 115
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

I 112
	bp = NULL;
	slotoffset = -1;
E 112
I 85
D 99
	ndp->ni_dvp = vp;
E 99
I 99
D 115
	ndp->ni_dvp = vdp;
E 99
	ndp->ni_vp = NULL;
D 99
	dp = VTOI(vp);
E 99
I 99
	dp = VTOI(vdp);
E 99
D 112
	fs = dp->i_fs;
E 112
I 112
D 113
	ump = VFSTOUFS(vdp->v_mount);
E 113
E 112
E 85
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
	lockparent = ndp->ni_nameiop & LOCKPARENT;
D 85
	docache = (ndp->ni_nameiop & NOCACHE) ^ NOCACHE;
	flag = ndp->ni_nameiop &~ (LOCKPARENT|NOCACHE|FOLLOW);
E 57
D 67
	if (flag == DELETE)
E 67
I 67
	if (flag == DELETE || lockparent)
E 67
		docache = 0;
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
	MALLOC(nbp, caddr_t, MAXPATHLEN, M_NAMEI, M_WAITOK);
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
		error = copystr(ndp->ni_dirp, nbp, MAXPATHLEN, (u_int *)0);
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
		error = copyinstr(ndp->ni_dirp, nbp, MAXPATHLEN, (u_int *)0);
E 81
E 58
	if (error) {
		u.u_error = error;
E 57
		goto bad;
I 57
	}
I 84
#ifdef KTRACE
	if (KTRPOINT(u.u_procp, KTR_NAMEI))
		ktrnamei(u.u_procp->p_tracep, nbp);
#endif
E 85
I 85
D 103
	flag = ndp->ni_nameiop & OPFLAG;
E 103
I 103
	flag = ndp->ni_nameiop & OPMASK;
E 103
	wantparent = ndp->ni_nameiop & (LOCKPARENT|WANTPARENT);
E 115
I 115
D 136
	*vpp = NULL;
	dp = VTOI(dvp);
	lockparent = cnp->cn_flags & LOCKPARENT;
	wantparent = cnp->cn_flags & (LOCKPARENT|WANTPARENT);
E 136
I 136
D 138
	*ap->a_vpp = NULL;
	dp = VTOI(ap->a_dvp);
	lockparent = ap->a_cnp->cn_flags & LOCKPARENT;
	wantparent = ap->a_cnp->cn_flags & (LOCKPARENT|WANTPARENT);
E 138
I 138
	*vpp = NULL;
	vdp = ap->a_dvp;
	dp = VTOI(vdp);
	lockparent = flags & LOCKPARENT;
	wantparent = flags & (LOCKPARENT|WANTPARENT);
E 138
E 136
E 115
E 85
E 84
E 57

E 23
	/*
E 13
D 23
	 * If name starts with '/' start from
	 * root; otherwise start from current dir.
E 23
I 23
D 85
	 * Get starting directory.
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
I 63
	ndp->ni_endoff = 0;
E 63
E 57

E 23
E 19
D 13
seloop:
E 13
	/*
D 23
	 * dp must be a directory and
	 * must have X permission.
I 13
	 * cp is a path name relative to that directory.
E 23
I 23
	 * We come to dirloop to search a new directory.
	 * The directory must be locked so that it can be
	 * iput, and fs must be already set to dp->i_fs.
E 23
E 13
	 */
I 21
D 23
#ifdef	EFS
E 23
I 23
dirloop:
E 23
	/*
E 85
D 23
	 * But first, if the last component was a character special file
	 * and the major device is the extended file system device
	 * then return even if more pathname exists.
E 23
I 23
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
D 85
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
E 85
I 85
D 117
	if ((dp->i_mode&IFMT) != IFDIR)
E 117
I 117
	if ((dp->i_mode & IFMT) != IFDIR)
E 117
		return (ENOTDIR);
D 99
	if (error = iaccess(dp, IEXEC, ndp->ni_cred))
E 99
I 99
D 107
	if (error = ufs_access(vdp, VEXEC, ndp->ni_cred))
E 107
I 107
D 115
	if (error = ufs_access(vdp, VEXEC, ndp->ni_cred, p))
E 115
I 115
D 135
	if (error = ufs_access(dvp, VEXEC, cnp->cn_cred, cnp->cn_proc))
E 135
I 135
D 136
	if (error = VOP_ACCESS(dvp, VEXEC, cnp->cn_cred, cnp->cn_proc))
E 136
I 136
D 138
	if (error = VOP_ACCESS(ap->a_dvp, VEXEC, ap->a_cnp->cn_cred, ap->a_cnp->cn_proc))
E 138
I 138
	if (error = VOP_ACCESS(vdp, VEXEC, cred, cnp->cn_proc))
E 138
E 136
E 135
E 115
E 107
E 99
		return (error);
I 158
	if ((flags & ISLASTCN) && (vdp->v_mount->mnt_flag & MNT_RDONLY) &&
	    (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME))
		return (EROFS);
E 158
E 85

E 23
I 18
D 85
dirloop2:
E 85
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
D 57
	 * Copy next component of name to u.u_dent.
E 57
I 57
D 85
	 * Copy next component of name to ndp->ni_dent.
E 57
	 */
I 48
	hash = 0;
E 48
	for (i = 0; *cp != 0 && *cp != '/'; cp++) {
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
			u.u_error = ENAMETOOLONG;
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
				u.u_error = EINVAL;
				goto bad;
			}
E 69
		ndp->ni_dent.d_name[i++] = *cp;
E 57
I 48
		hash += (unsigned char)*cp * i;
E 48
E 23
E 15
	}
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
	isdotdot = (i == 2 &&
D 57
		u.u_dent.d_name[0] == '.' && u.u_dent.d_name[1] == '.');
E 57
I 57
		ndp->ni_dent.d_name[0] == '.' && ndp->ni_dent.d_name[1] == '.');
I 67
	makeentry = 1;
	if (*cp == '\0' && docache == 0)
		makeentry = 0;
E 67
E 57
E 53

	/*
	 * Check for degenerate name (e.g. / or "")
	 * which is a way of talking about a directory,
	 * e.g. like "/." or ".".
	 */
D 57
	if (u.u_dent.d_name[0] == 0) {
E 57
I 57
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
		FREE(nbp, M_NAMEI);
E 81
E 56
		return (dp);
E 19
	}
I 23

E 23
I 19
	/*
I 83
	 * Special handling for ".." allowing chdir out of mounted
	 * file system: indirect .. in root inode to reevaluate
	 * in directory file system was mounted on.
	 */
	if (isdotdot) {
		for (;;) {
			if (dp == u.u_rdir || dp == rootdir) {
				ndp->ni_dent.d_ino = dp->i_number;
				pdp = dp;
				dp->i_count++;
				goto haveino;
			}
			if (dp->i_number != ROOTINO)
				break;
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
		}
	}

	/*
E 85
E 83
I 48
	 * We now have a segment name to search for, and a directory to search.
	 *
	 * Before tediously performing a linear scan of the directory,
	 * check the name cache to see if the directory/name pair
D 85
	 * we are looking for is known already.  We don't do this
	 * if the segment name is long, simply so the cache can avoid
	 * holding long names (which would either waste space, or
	 * add greatly to the complexity).
E 85
I 85
	 * we are looking for is known already.
E 85
	 */
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
E 85
I 85
D 90
	if (vdp = cache_lookup(ndp)) {
E 90
I 90
D 115
	if (error = cache_lookup(ndp)) {
E 115
I 115
D 136
	if (error = cache_lookup(dvp, vpp, cnp)) {
E 136
I 136
D 138
	if (error = cache_lookup(ap->a_dvp, ap->a_vpp, ap->a_cnp)) {
E 138
I 138
	if (error = cache_lookup(vdp, vpp, cnp)) {
E 138
E 136
E 115
		int vpid;	/* capability number of vnode */

		if (error == ENOENT)
			return (error);
I 102
D 138
#ifdef PARANOID
E 102
I 93
D 99
		if (vp == ndp->ni_rdir && ndp->ni_isdotdot)
E 99
I 99
D 115
		if (vdp == ndp->ni_rdir && ndp->ni_isdotdot)
E 115
I 115
D 117
		if (dvp == ndp->ni_rdir && (cnp->cn_flags&ISDOTDOT))
E 117
I 117
D 136
		if (dvp == ndp->ni_rdir && (cnp->cn_flags & ISDOTDOT))
E 136
I 136
		if (ap->a_dvp == ndp->ni_rdir && (ap->a_cnp->cn_flags & ISDOTDOT))
E 136
E 117
E 115
E 99
D 94
			panic("lookup: .. through root");
E 94
I 94
			panic("ufs_lookup: .. through root");
I 102
#endif
E 138
E 102
E 94
E 93
E 90
		/*
		 * Get the next vnode in the path.
D 90
		 * See comment above `IUNLOCK' code for
E 90
I 90
		 * See comment below starting `Step through' for
E 90
		 * an explaination of the locking protocol.
		 */
I 115
D 138
		/*
D 118
		 * NEEDSWORK: The borrowing of variables
		 * here is quite confusing.  Usually, dvp/dp
E 118
I 118
		 * The borrowing of variables
D 136
		 * here is somewhat confusing.  Usually, dvp/dp
E 136
I 136
		 * here is somewhat confusing.  Usually, ap->a_dvp/dp
E 136
E 118
		 * is the directory being searched.
		 * Here it's the target returned from the cache.
		 */
E 138
E 115
D 142
		pdp = dp;
E 142
I 142
		pdp = vdp;
E 142
D 90
		dp = VTOI(vdp);
E 90
I 90
D 93
		if (!(ndp->ni_vp == ndp->ni_rdir && ndp->ni_isdotdot))
			dp = VTOI(ndp->ni_vp);
E 93
I 93
D 115
		dp = VTOI(ndp->ni_vp);
E 93
D 94
		vdp = ITOV(dp);
E 94
I 94
		vdp = ndp->ni_vp;
E 94
		vpid = vdp->v_id;
E 90
		if (pdp == dp) {
D 89
			vdp->v_count++;
E 89
I 89
			VREF(vdp);
E 115
I 115
D 136
		dp = VTOI(*vpp);
		dvp = *vpp;
		vpid = dvp->v_id;
E 136
I 136
D 138
		dp = VTOI(*ap->a_vpp);
		ap->a_dvp = *ap->a_vpp;
		vpid = ap->a_dvp->v_id;
E 138
I 138
		dp = VTOI(*vpp);
		vdp = *vpp;
		vpid = vdp->v_id;
E 138
E 136
D 142
		if (pdp == dp) {   /* lookup on "." */
E 142
I 142
		if (pdp == vdp) {   /* lookup on "." */
E 142
D 136
			VREF(dvp);
E 136
I 136
D 138
			VREF(ap->a_dvp);
E 138
I 138
			VREF(vdp);
E 138
E 136
E 115
I 94
			error = 0;
E 94
E 89
D 115
		} else if (ndp->ni_isdotdot) {
E 115
I 115
D 117
		} else if (cnp->cn_flags&ISDOTDOT) {
E 117
I 117
D 136
		} else if (cnp->cn_flags & ISDOTDOT) {
E 136
I 136
D 138
		} else if (ap->a_cnp->cn_flags & ISDOTDOT) {
E 138
I 138
		} else if (flags & ISDOTDOT) {
E 138
E 136
E 117
E 115
D 142
			IUNLOCK(pdp);
E 142
I 142
D 156
			VOP_UNLOCK(pdp);
E 142
D 94
			igrab(dp);
E 94
I 94
D 115
			error = vget(vdp);
I 104
			if (!error && lockparent && *ndp->ni_next == '\0')
E 115
I 115
D 136
			error = vget(dvp);
D 117
			if (!error && lockparent && (cnp->cn_flags&ISLASTCN))
E 117
I 117
			if (!error && lockparent && (cnp->cn_flags & ISLASTCN))
E 136
I 136
D 138
			error = vget(ap->a_dvp);
			if (!error && lockparent && (ap->a_cnp->cn_flags & ISLASTCN))
E 138
I 138
D 147
			error = vget(vdp);
E 147
I 147
			error = vget(vdp, 1);
E 156
I 156
			VOP_UNLOCK(pdp, 0, p);
			error = vget(vdp, LK_EXCLUSIVE, p);
E 156
E 147
			if (!error && lockparent && (flags & ISLASTCN))
E 138
E 136
E 117
E 115
D 142
				ILOCK(pdp);
E 142
I 142
D 156
				error = VOP_LOCK(pdp);
E 156
I 156
				error = vn_lock(pdp, LK_EXCLUSIVE, p);
E 156
E 142
E 104
E 94
E 85
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
D 85
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
E 85
I 85
D 94
			igrab(dp);
E 94
I 94
D 115
			error = vget(vdp);
E 94
D 104
			IUNLOCK(pdp);
E 104
I 104
			if (!lockparent || error || *ndp->ni_next != '\0')
E 115
I 115
D 136
			error = vget(dvp);
D 117
			if (!lockparent || error || !(cnp->cn_flags&ISLASTCN))
E 117
I 117
			if (!lockparent || error || !(cnp->cn_flags & ISLASTCN))
E 136
I 136
D 138
			error = vget(ap->a_dvp);
			if (!lockparent || error || !(ap->a_cnp->cn_flags & ISLASTCN))
E 138
I 138
D 147
			error = vget(vdp);
E 147
I 147
D 156
			error = vget(vdp, 1);
E 156
I 156
			error = vget(vdp, LK_EXCLUSIVE, p);
E 156
E 147
			if (!lockparent || error || !(flags & ISLASTCN))
E 138
E 136
E 117
E 115
D 142
				IUNLOCK(pdp);
E 142
I 142
D 156
				VOP_UNLOCK(pdp);
E 156
I 156
				VOP_UNLOCK(pdp, 0, p);
E 156
E 142
E 104
E 85
		}
I 85
D 90
		ndp->ni_vp = vdp;
		return (0);
E 90
I 90
		/*
		 * Check that the capability number did not change
		 * while we were waiting for the lock.
		 */
D 94
		if (vpid == vdp->v_id)
			return (0);
		iput(dp);
E 94
I 94
		if (!error) {
D 115
			if (vpid == vdp->v_id)
E 115
I 115
D 136
			if (vpid == dvp->v_id)
E 136
I 136
D 138
			if (vpid == ap->a_dvp->v_id)
E 138
I 138
			if (vpid == vdp->v_id)
E 138
E 136
E 115
				return (0);
D 104
			else
				iput(dp);
E 104
I 104
D 112
			iput(dp);
E 112
I 112
D 142
			ufs_iput(dp);
E 112
D 115
			if (lockparent && pdp != dp && *ndp->ni_next == '\0')
E 115
I 115
D 117
			if (lockparent && pdp != dp && (cnp->cn_flags&ISLASTCN))
E 117
I 117
			if (lockparent && pdp != dp &&
D 136
			    (cnp->cn_flags & ISLASTCN))
E 136
I 136
D 138
			    (ap->a_cnp->cn_flags & ISLASTCN))
E 138
I 138
			    (flags & ISLASTCN))
E 138
E 136
E 117
E 115
				IUNLOCK(pdp);
E 142
I 142
			vput(vdp);
			if (lockparent && pdp != vdp && (flags & ISLASTCN))
D 156
				VOP_UNLOCK(pdp);
E 156
I 156
				VOP_UNLOCK(pdp, 0, p);
E 156
E 142
E 104
		}
E 94
D 142
		ILOCK(pdp);
		dp = pdp;
I 99
D 115
		vdp = ITOV(dp);
E 99
		ndp->ni_vp = NULL;
E 115
I 115
D 136
		dvp = ITOV(dp);
		*vpp = NULL;
E 136
I 136
D 138
		ap->a_dvp = ITOV(dp);
		*ap->a_vpp = NULL;
E 138
I 138
		vdp = ITOV(dp);
E 142
I 142
D 156
		if (error = VOP_LOCK(pdp))
E 156
I 156
		if (error = vn_lock(pdp, LK_EXCLUSIVE, p))
E 156
			return (error);
		vdp = pdp;
		dp = VTOI(pdp);
E 142
		*vpp = NULL;
E 138
E 136
E 115
E 90
E 85
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
I 120
	slotfreespace = slotsize = slotneeded = 0;
E 120
D 34
	if (flag == 1 && *cp == 0) {
E 34
I 34
D 85
	if (flag == CREATE && *cp == 0) {
E 85
I 85
D 115
	if ((flag == CREATE || flag == RENAME) && *ndp->ni_next == 0) {
E 115
I 115
D 117
	if ((cnp->cn_nameiop == CREATE || cnp->cn_nameiop == RENAME) && (cnp->cn_flags&ISLASTCN)) {
E 117
I 117
D 136
	if ((cnp->cn_nameiop == CREATE || cnp->cn_nameiop == RENAME) &&
	    (cnp->cn_flags & ISLASTCN)) {
E 136
I 136
D 138
	if ((ap->a_cnp->cn_nameiop == CREATE || ap->a_cnp->cn_nameiop == RENAME) &&
	    (ap->a_cnp->cn_flags & ISLASTCN)) {
E 138
I 138
	if ((nameiop == CREATE || nameiop == RENAME) &&
	    (flags & ISLASTCN)) {
E 138
E 136
E 117
E 115
E 85
E 34
		slotstatus = NONE;
D 120
		slotfreespace = 0;
E 120
D 57
		slotneeded = DIRSIZ(&u.u_dent);
E 57
I 57
D 110
		slotneeded = DIRSIZ(&ndp->ni_dent);
E 110
I 110
D 121
		slotneeded = ((sizeof (struct direct) - (MAXNAMLEN + 1)) +
D 115
			((ndp->ni_namelen + 1 + 3) &~ 3));
E 115
I 115
			((cnp->cn_namelen + 1 + 3) &~ 3));
E 121
I 121
		slotneeded = (sizeof(struct direct) - MAXNAMLEN +
D 136
			cnp->cn_namelen + 3) &~ 3;
E 136
I 136
D 138
			ap->a_cnp->cn_namelen + 3) &~ 3;
E 138
I 138
			cnp->cn_namelen + 3) &~ 3;
E 138
E 136
E 121
E 115
E 110
E 57
	}
I 85

E 85
I 47
	/*
D 85
	 * If this is the same directory that this process
	 * previously searched, pick up where we last left off.
E 85
I 85
	 * If there is cached information on a previous search of
	 * this directory, pick up where we last left off.
E 85
D 48
	 * We cache only lookups as these are the most common,
E 48
I 48
	 * We cache only lookups as these are the most common
E 48
	 * and have the greatest payoff. Caching CREATE has little
	 * benefit as it usually must search the entire directory
	 * to determine that the entry does not exist. Caching the
D 85
	 * location of the last DELETE has not reduced profiling time
	 * and hence has been removed in the interest of simplicity.
E 85
I 85
	 * location of the last DELETE or RENAME has not reduced
	 * profiling time and hence has been removed in the interest
	 * of simplicity.
E 85
	 */
I 112
D 113
	bmask = ump->um_mountp->mnt_stat.f_bsize - 1;
E 113
I 113
D 114
	bmask = VFSTOUFS(vdp->v_mount)->um_mountp->mnt_stat.f_bsize - 1;
E 114
I 114
D 115
	bmask = VFSTOUFS(vdp->v_mount)->um_mountp->mnt_stat.f_iosize - 1;
E 114
E 113
E 112
D 85
	if (flag != LOOKUP || dp->i_number != u.u_ncache.nc_inumber ||
	    dp->i_dev != u.u_ncache.nc_dev) {
E 85
I 85
	if (flag != LOOKUP || dp->i_diroff == 0 || dp->i_diroff > dp->i_size) {
E 85
D 57
		u.u_offset = 0;
E 57
I 57
D 110
		ndp->ni_offset = 0;
E 110
I 110
		ndp->ni_ufs.ufs_offset = 0;
E 115
I 115
D 136
	bmask = VFSTOUFS(dvp->v_mount)->um_mountp->mnt_stat.f_iosize - 1;
D 117
	if (cnp->cn_nameiop != LOOKUP || dp->i_diroff == 0 || dp->i_diroff > dp->i_size) {
		cnp->cn_ufs.ufs_offset = 0;
E 117
I 117
	if (cnp->cn_nameiop != LOOKUP || dp->i_diroff == 0 ||
E 136
I 136
D 138
	bmask = VFSTOUFS(ap->a_dvp->v_mount)->um_mountp->mnt_stat.f_iosize - 1;
	if (ap->a_cnp->cn_nameiop != LOOKUP || dp->i_diroff == 0 ||
E 138
I 138
	bmask = VFSTOUFS(vdp->v_mount)->um_mountp->mnt_stat.f_iosize - 1;
	if (nameiop != LOOKUP || dp->i_diroff == 0 ||
E 138
E 136
	    dp->i_diroff > dp->i_size) {
D 120
		dp->i_offset = 0;
E 120
I 120
D 121
		entryoffsetinblock = dp->i_offset = 0;
E 121
I 121
		entryoffsetinblock = 0;
		dp->i_offset = 0;
E 121
E 120
E 117
E 115
E 110
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
D 85
		if (u.u_ncache.nc_prevoffset > dp->i_size)
			u.u_ncache.nc_prevoffset = 0;
E 77
D 57
		u.u_offset = u.u_ncache.nc_prevoffset;
		entryoffsetinblock = blkoff(fs, u.u_offset);
E 57
I 57
		ndp->ni_offset = u.u_ncache.nc_prevoffset;
E 85
I 85
D 110
		ndp->ni_offset = dp->i_diroff;
E 85
		entryoffsetinblock = blkoff(fs, ndp->ni_offset);
E 110
I 110
D 115
		ndp->ni_ufs.ufs_offset = dp->i_diroff;
D 112
		entryoffsetinblock = blkoff(fs, ndp->ni_ufs.ufs_offset);
E 110
E 57
		if (entryoffsetinblock != 0) {
D 57
			bp = blkatoff(dp, u.u_offset, (char **)0);
E 57
I 57
D 85
			bp = blkatoff(dp, ndp->ni_offset, (char **)0);
E 57
			if (bp == 0)
				goto bad;
E 85
I 85
D 110
			error = blkatoff(dp, ndp->ni_offset, (char **)0, &bp);
			if (error)
E 110
I 110
			if (error = blkatoff(dp, ndp->ni_ufs.ufs_offset,
			    (char **)0, &bp))
E 110
				return (error);
E 85
		}
E 112
I 112
		if ((entryoffsetinblock = ndp->ni_ufs.ufs_offset & bmask) &&
D 113
		    (error = (ump->um_blkatoff)
		    (dp, ndp->ni_ufs.ufs_offset, NULL, &bp)))
E 113
I 113
		    (error = VOP_BLKATOFF(vdp, ndp->ni_ufs.ufs_offset, NULL,
E 115
I 115
D 117
		cnp->cn_ufs.ufs_offset = dp->i_diroff;
		if ((entryoffsetinblock = cnp->cn_ufs.ufs_offset & bmask) &&
		    (error = VOP_BLKATOFF(dvp, cnp->cn_ufs.ufs_offset, NULL,
E 115
		     &bp)))
E 117
I 117
		dp->i_offset = dp->i_diroff;
		if ((entryoffsetinblock = dp->i_offset & bmask) &&
D 121
		    (error = VOP_BLKATOFF(dvp, dp->i_offset, NULL, &bp)))
E 121
I 121
D 136
		    (error = VOP_BLKATOFF(dvp, (off_t)dp->i_offset, NULL, &bp)))
E 136
I 136
D 138
		    (error = VOP_BLKATOFF(ap->a_dvp, (off_t)dp->i_offset, NULL, &bp)))
E 138
I 138
		    (error = VOP_BLKATOFF(vdp, (off_t)dp->i_offset, NULL, &bp)))
E 138
E 136
E 121
E 117
E 113
			return (error);
E 112
		numdirpasses = 2;
I 48
		nchstats.ncs_2passes++;
E 48
	}
I 120
	prevoff = dp->i_offset;
E 120
	endsearch = roundup(dp->i_size, DIRBLKSIZ);
I 63
	enduseful = 0;
E 63
E 47

I 84
D 85
#ifdef NAMEI_DIAGNOSTIC
	printf("{%s}:\n", ndp->ni_dent.d_name);
#endif
E 85
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
searchloop:
D 57
	while (u.u_offset < endsearch) {
E 57
I 57
D 110
	while (ndp->ni_offset < endsearch) {
E 110
I 110
D 115
	while (ndp->ni_ufs.ufs_offset < endsearch) {
E 115
I 115
D 117
	while (cnp->cn_ufs.ufs_offset < endsearch) {
E 117
I 117
	while (dp->i_offset < endsearch) {
E 117
E 115
E 110
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
D 112
		 * If offset is on a block boundary,
		 * read the next directory block.
		 * Release previous if it exists.
E 112
I 112
D 143
		 * If offset is on a block boundary, read the next directory
		 * block.  Release previous if it exists.
E 143
I 143
		 * If necessary, get the next directory block.
E 143
E 112
		 */
D 19
		if ((u.u_offset&BMASK) == 0) {
E 19
I 19
D 57
		if (blkoff(fs, u.u_offset) == 0) {
E 57
I 57
D 110
		if (blkoff(fs, ndp->ni_offset) == 0) {
E 110
I 110
D 112
		if (blkoff(fs, ndp->ni_ufs.ufs_offset) == 0) {
E 112
I 112
D 115
		if ((ndp->ni_ufs.ufs_offset & bmask) == 0) {
E 115
I 115
D 117
		if ((cnp->cn_ufs.ufs_offset & bmask) == 0) {
E 117
I 117
		if ((dp->i_offset & bmask) == 0) {
E 117
E 115
E 112
E 110
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
D 85
			bp = blkatoff(dp, ndp->ni_offset, (char **)0);
E 57
E 24
			if (bp == 0)
				goto bad;
E 85
I 85
D 110
			error = blkatoff(dp, ndp->ni_offset, (char **)0, &bp);
			if (error)
E 110
I 110
D 112
			if (error = blkatoff(dp, ndp->ni_ufs.ufs_offset,
			    (char **)0, &bp))
E 112
I 112
D 113
			if (error = (ump->um_blkatoff)
			    (dp, ndp->ni_ufs.ufs_offset, NULL, &bp))
E 113
I 113
D 115
			if (error = VOP_BLKATOFF(vdp, ndp->ni_ufs.ufs_offset,
E 115
I 115
D 117
			if (error = VOP_BLKATOFF(dvp, cnp->cn_ufs.ufs_offset,
E 115
			    NULL, &bp))
E 117
I 117
D 121
			if (error = VOP_BLKATOFF(dvp, dp->i_offset, NULL, &bp))
E 121
I 121
			if (error =
D 136
			    VOP_BLKATOFF(dvp, (off_t)dp->i_offset, NULL, &bp))
E 136
I 136
D 138
			    VOP_BLKATOFF(ap->a_dvp, (off_t)dp->i_offset, NULL, &bp))
E 138
I 138
			    VOP_BLKATOFF(vdp, (off_t)dp->i_offset, NULL, &bp))
E 138
E 136
E 121
E 117
E 113
E 112
E 110
				return (error);
E 85
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
D 85
		    (entryoffsetinblock&(DIRBLKSIZ-1)) == 0) {
E 85
I 85
		    (entryoffsetinblock & (DIRBLKSIZ - 1)) == 0) {
E 85
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
D 145
		ep = (struct direct *)(bp->b_un.b_addr + entryoffsetinblock);
E 145
I 145
		ep = (struct direct *)((char *)bp->b_data + entryoffsetinblock);
E 145
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
D 112
		    dirchk && dirbadentry(ep, entryoffsetinblock)) {
E 112
I 112
D 139
		    dirchk && ufs_dirbadentry(ep, entryoffsetinblock)) {
E 139
I 139
		    dirchk && ufs_dirbadentry(vdp, ep, entryoffsetinblock)) {
E 139
E 112
I 85
			int i;

E 85
E 52
E 24
D 57
			dirbad(dp, "mangled entry");
E 57
I 57
D 110
			dirbad(dp, ndp->ni_offset, "mangled entry");
E 110
I 110
D 112
			dirbad(dp, ndp->ni_ufs.ufs_offset, "mangled entry");
E 112
I 112
D 115
			ufs_dirbad(dp, ndp->ni_ufs.ufs_offset, "mangled entry");
E 115
I 115
D 117
			ufs_dirbad(dp, cnp->cn_ufs.ufs_offset, "mangled entry");
E 117
I 117
			ufs_dirbad(dp, dp->i_offset, "mangled entry");
E 117
E 115
E 112
E 110
E 57
I 52
			i = DIRBLKSIZ - (entryoffsetinblock & (DIRBLKSIZ - 1));
E 52
E 23
D 57
			u.u_offset += i;
E 57
I 57
D 110
			ndp->ni_offset += i;
E 110
I 110
D 115
			ndp->ni_ufs.ufs_offset += i;
E 115
I 115
D 117
			cnp->cn_ufs.ufs_offset += i;
E 117
I 117
			dp->i_offset += i;
E 117
E 115
E 110
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
D 139
				size -= DIRSIZ(ep);
E 139
I 139
				size -= DIRSIZ(FSFMT(vdp), ep);
E 139
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
D 110
					slotoffset = ndp->ni_offset;
E 110
I 110
D 115
					slotoffset = ndp->ni_ufs.ufs_offset;
E 115
I 115
D 117
					slotoffset = cnp->cn_ufs.ufs_offset;
E 117
I 117
					slotoffset = dp->i_offset;
E 117
E 115
E 110
E 57
					slotsize = ep->d_reclen;
				} else if (slotstatus == NONE) {
					slotfreespace += size;
					if (slotoffset == -1)
D 57
						slotoffset = u.u_offset;
E 57
I 57
D 110
						slotoffset = ndp->ni_offset;
E 110
I 110
D 117
						slotoffset =
D 115
						      ndp->ni_ufs.ufs_offset;
E 115
I 115
						      cnp->cn_ufs.ufs_offset;
E 117
I 117
						slotoffset = dp->i_offset;
E 117
E 115
E 110
E 57
					if (slotfreespace >= slotneeded) {
						slotstatus = COMPACT;
D 57
						slotsize =
						    u.u_offset+ep->d_reclen -
						      slotoffset;
E 57
I 57
D 110
						slotsize = ndp->ni_offset +
E 110
I 110
D 117
						slotsize =
D 115
						      ndp->ni_ufs.ufs_offset +
E 115
I 115
						      cnp->cn_ufs.ufs_offset +
E 117
I 117
						slotsize = dp->i_offset +
E 117
E 115
E 110
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
D 85
#ifdef NAMEI_DIAGNOSTIC
			printf("{%s} ", ep->d_name);
#endif
E 85
E 84
D 57
			if (ep->d_namlen == u.u_dent.d_namlen &&
			    !bcmp(u.u_dent.d_name, ep->d_name, ep->d_namlen))
E 57
I 57
D 110
			if (ep->d_namlen == ndp->ni_dent.d_namlen &&
E 110
I 110
D 115
			if (ep->d_namlen == ndp->ni_namelen &&
E 110
D 85
			    !bcmp(ndp->ni_dent.d_name, ep->d_name,
D 72
				ep->d_namlen))
E 72
I 72
				(unsigned)ep->d_namlen))
E 85
I 85
			    !bcmp(ndp->ni_ptr, ep->d_name,
E 115
I 115
D 136
			if (ep->d_namlen == cnp->cn_namelen &&
			    !bcmp(cnp->cn_nameptr, ep->d_name,
E 136
I 136
D 138
			if (ep->d_namlen == ap->a_cnp->cn_namelen &&
			    !bcmp(ap->a_cnp->cn_nameptr, ep->d_name,
E 138
I 138
D 139
			if (ep->d_namlen == cnp->cn_namelen &&
E 139
I 139
#			if (BYTE_ORDER == LITTLE_ENDIAN)
				if (vdp->v_mount->mnt_maxsymlinklen > 0)
					namlen = ep->d_namlen;
				else
					namlen = ep->d_type;
#			else
				namlen = ep->d_namlen;
#			endif
			if (namlen == cnp->cn_namelen &&
E 139
			    !bcmp(cnp->cn_nameptr, ep->d_name,
E 138
E 136
E 115
D 139
				(unsigned)ep->d_namlen)) {
E 139
I 139
				(unsigned)namlen)) {
E 139
				/*
				 * Save directory entry's inode number and
D 110
				 * reclen in ndp->ni_dent, and release
E 110
I 110
				 * reclen in ndp->ni_ufs area, and release
E 110
				 * directory buffer.
				 */
I 151
D 153
				if (DT_ISWHT(ep->d_type)) {
E 153
I 153
D 154
				if (ep->d_type == DT_WHT) {
E 154
I 154
				if (vdp->v_mount->mnt_maxsymlinklen > 0 &&
				    ep->d_type == DT_WHT) {
E 154
E 153
					slotstatus = FOUND;
					slotoffset = dp->i_offset;
					slotsize = ep->d_reclen;
					dp->i_reclen = slotsize;
D 159
					enduseful = slotoffset + slotsize;
E 159
I 159
					enduseful = dp->i_size;
E 159
					ap->a_cnp->cn_flags |= ISWHITEOUT;
					numdirpasses--;
					goto notfound;
				}
E 151
D 110
				ndp->ni_dent.d_ino = ep->d_ino;
				ndp->ni_dent.d_reclen = ep->d_reclen;
E 110
I 110
D 115
				ndp->ni_ufs.ufs_ino = ep->d_ino;
				ndp->ni_ufs.ufs_reclen = ep->d_reclen;
E 115
I 115
D 117
				cnp->cn_ufs.ufs_ino = ep->d_ino;
				cnp->cn_ufs.ufs_reclen = ep->d_reclen;
E 117
I 117
				dp->i_ino = ep->d_ino;
				dp->i_reclen = ep->d_reclen;
E 117
E 115
E 110
				brelse(bp);
E 85
E 72
E 57
				goto found;
I 85
			}
E 85
		}
D 57
		prevoff = u.u_offset;
E 23
		u.u_offset += ep->d_reclen;
E 57
I 57
D 110
		prevoff = ndp->ni_offset;
		ndp->ni_offset += ep->d_reclen;
E 110
I 110
D 115
		prevoff = ndp->ni_ufs.ufs_offset;
		ndp->ni_ufs.ufs_offset += ep->d_reclen;
E 115
I 115
D 117
		prevoff = cnp->cn_ufs.ufs_offset;
		cnp->cn_ufs.ufs_offset += ep->d_reclen;
E 117
I 117
		prevoff = dp->i_offset;
		dp->i_offset += ep->d_reclen;
E 117
E 115
E 110
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
D 110
			enduseful = ndp->ni_offset;
E 110
I 110
D 115
			enduseful = ndp->ni_ufs.ufs_offset;
E 115
I 115
D 117
			enduseful = cnp->cn_ufs.ufs_offset;
E 117
I 117
			enduseful = dp->i_offset;
E 117
E 115
E 110
E 63
	}
I 84
D 85
#ifdef NAMEI_DIAGNOSTIC
	printf("\nnotfound\n");
#endif
E 85
E 84
I 48
D 151
/* notfound: */
E 151
I 151
notfound:
E 151
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
D 110
		ndp->ni_offset = 0;
E 110
I 110
D 115
		ndp->ni_ufs.ufs_offset = 0;
E 115
I 115
D 117
		cnp->cn_ufs.ufs_offset = 0;
E 117
I 117
		dp->i_offset = 0;
E 117
E 115
E 110
E 57
D 85
		endsearch = u.u_ncache.nc_prevoffset;
E 85
I 85
		endsearch = dp->i_diroff;
E 85
		goto searchloop;
	}
I 85
	if (bp != NULL)
		brelse(bp);
E 85
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
D 85
	if (flag == CREATE && *cp == 0 && dp->i_nlink != 0) {
E 85
I 85
D 115
	if ((flag == CREATE || flag == RENAME) &&
	    *ndp->ni_next == 0 && dp->i_nlink != 0) {
E 115
I 115
D 136
	if ((cnp->cn_nameiop == CREATE || cnp->cn_nameiop == RENAME) &&
D 117
	    (cnp->cn_flags&ISLASTCN) && dp->i_nlink != 0) {
E 117
I 117
	    (cnp->cn_flags & ISLASTCN) && dp->i_nlink != 0) {
E 136
I 136
D 138
	if ((ap->a_cnp->cn_nameiop == CREATE || ap->a_cnp->cn_nameiop == RENAME) &&
	    (ap->a_cnp->cn_flags & ISLASTCN) && dp->i_nlink != 0) {
E 138
I 138
D 151
	if ((nameiop == CREATE || nameiop == RENAME) &&
E 151
I 151
	if ((nameiop == CREATE || nameiop == RENAME ||
	     (nameiop == DELETE &&
	      (ap->a_cnp->cn_flags & DOWHITEOUT) &&
	      (ap->a_cnp->cn_flags & ISWHITEOUT))) &&
E 151
	    (flags & ISLASTCN) && dp->i_nlink != 0) {
E 138
E 136
E 117
E 115
E 85
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
D 85
		if (access(dp, IWRITE))
			goto bad;
E 85
I 85
D 99
		if (error = iaccess(dp, IWRITE, ndp->ni_cred))
E 99
I 99
D 107
		if (error = ufs_access(vdp, VWRITE, ndp->ni_cred))
E 107
I 107
D 115
		if (error = ufs_access(vdp, VWRITE, ndp->ni_cred, p))
E 115
I 115
D 135
		if (error = ufs_access(dvp, VWRITE, cnp->cn_cred, cnp->cn_proc))
E 135
I 135
D 136
		if (error = VOP_ACCESS(dvp, VWRITE, cnp->cn_cred, cnp->cn_proc))
E 136
I 136
D 138
		if (error = VOP_ACCESS(ap->a_dvp, VWRITE, ap->a_cnp->cn_cred, ap->a_cnp->cn_proc))
E 138
I 138
		if (error = VOP_ACCESS(vdp, VWRITE, cred, cnp->cn_proc))
E 138
E 136
E 135
E 115
E 107
E 99
			return (error);
E 85
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
		 * Return an indication of where the new directory
		 * entry should be put.  If we didn't find a slot,
D 57
		 * then set u.u_count to 0 indicating that the
		 * new slot belongs at the end of the directory.
		 * If we found a slot, then the new entry can be
		 * put in the range [u.u_offset..u.u_offset+u.u_count)
E 57
I 57
D 110
		 * then set ndp->ni_count to 0 indicating that the new
		 * slot belongs at the end of the directory. If we found
		 * a slot, then the new entry can be put in the range
		 * [ndp->ni_offset .. ndp->ni_offset + ndp->ni_count)
E 110
I 110
D 117
		 * then set ndp->ni_ufs.ufs_count to 0 indicating
E 117
I 117
		 * then set dp->i_count to 0 indicating
E 117
		 * that the new slot belongs at the end of the
		 * directory. If we found a slot, then the new entry
D 117
		 * can be put in the range from ndp->ni_ufs.ufs_offset
		 * to ndp->ni_ufs.ufs_offset + ndp->ni_ufs.ufs_count.
E 117
I 117
		 * can be put in the range from dp->i_offset to
		 * dp->i_offset + dp->i_count.
E 117
E 110
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
		if (slotstatus == NONE) {
D 57
			u.u_offset = roundup(dp->i_size, DIRBLKSIZ);
E 47
			u.u_count = 0;
E 57
I 57
D 110
			ndp->ni_offset = roundup(dp->i_size, DIRBLKSIZ);
			ndp->ni_count = 0;
I 63
			enduseful = ndp->ni_offset;
E 110
I 110
D 115
			ndp->ni_ufs.ufs_offset = roundup(dp->i_size, DIRBLKSIZ);
			ndp->ni_ufs.ufs_count = 0;
			enduseful = ndp->ni_ufs.ufs_offset;
E 115
I 115
D 117
			cnp->cn_ufs.ufs_offset = roundup(dp->i_size, DIRBLKSIZ);
			cnp->cn_ufs.ufs_count = 0;
			enduseful = cnp->cn_ufs.ufs_offset;
E 117
I 117
			dp->i_offset = roundup(dp->i_size, DIRBLKSIZ);
			dp->i_count = 0;
			enduseful = dp->i_offset;
I 151
		} else if (nameiop == DELETE) {
			dp->i_offset = slotoffset;
			if ((dp->i_offset & (DIRBLKSIZ - 1)) == 0)
				dp->i_count = 0;
			else
				dp->i_count = dp->i_offset - prevoff;
E 151
E 117
E 115
E 110
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
D 110
			ndp->ni_offset = slotoffset;
			ndp->ni_count = slotsize;
E 110
I 110
D 115
			ndp->ni_ufs.ufs_offset = slotoffset;
			ndp->ni_ufs.ufs_count = slotsize;
E 115
I 115
D 117
			cnp->cn_ufs.ufs_offset = slotoffset;
			cnp->cn_ufs.ufs_count = slotsize;
E 117
I 117
			dp->i_offset = slotoffset;
			dp->i_count = slotsize;
E 117
E 115
E 110
I 63
			if (enduseful < slotoffset + slotsize)
				enduseful = slotoffset + slotsize;
E 63
E 57
E 23
		}
I 63
D 110
		ndp->ni_endoff = roundup(enduseful, DIRBLKSIZ);
E 110
I 110
D 115
		ndp->ni_ufs.ufs_endoff = roundup(enduseful, DIRBLKSIZ);
E 115
I 115
D 117
		cnp->cn_ufs.ufs_endoff = roundup(enduseful, DIRBLKSIZ);
E 117
I 117
		dp->i_endoff = roundup(enduseful, DIRBLKSIZ);
E 117
E 115
E 110
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
D 145
		dp->i_flag |= IUPD|ICHG;
E 145
I 145
D 146
		dp->i_flag |= IUPDATE | ICHANGE;
E 146
I 146
		dp->i_flag |= IN_CHANGE | IN_UPDATE;
E 146
E 145
D 85
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
E 85
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
D 85
		 * We return NULL to indicate that the entry doesn't
		 * currently exist, leaving a pointer to the (locked)
D 57
		 * directory inode in u.u_pdir.
E 57
I 57
		 * directory inode in ndp->ni_pdir.
E 85
I 85
		 * We return ni_vp == NULL to indicate that the entry
		 * does not currently exist; we leave a pointer to
		 * the (locked) directory inode in ndp->ni_dvp.
I 110
		 * The pathname buffer is saved so that the name
		 * can be obtained later.
E 110
		 *
		 * NB - if the directory is unlocked, then this
		 * information cannot be used.
E 85
E 57
E 23
		 */
I 110
D 115
		ndp->ni_nameiop |= SAVENAME;
E 115
I 115
D 136
		cnp->cn_flags |= SAVENAME;
E 136
I 136
D 138
		ap->a_cnp->cn_flags |= SAVENAME;
E 138
I 138
		cnp->cn_flags |= SAVENAME;
E 138
E 136
E 115
E 110
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
D 85
		ndp->ni_pdir = dp;
E 57
		return (NULL);
E 85
I 85
		if (!lockparent)
D 142
			IUNLOCK(dp);
E 142
I 142
D 156
			VOP_UNLOCK(vdp);
E 156
I 156
			VOP_UNLOCK(vdp, 0, p);
E 156
E 142
I 119
		return (EJUSTRETURN);
E 119
E 85
	}
I 90
	/*
	 * Insert name into cache (as non-existent) if appropriate.
	 */
D 104
	if (ndp->ni_makeentry)
E 104
I 104
D 115
	if (ndp->ni_makeentry && flag != CREATE)
E 104
		cache_enter(ndp);
E 115
I 115
D 117
	if ((cnp->cn_flags&MAKEENTRY) && cnp->cn_nameiop != CREATE)
E 117
I 117
D 136
	if ((cnp->cn_flags & MAKEENTRY) && cnp->cn_nameiop != CREATE)
E 117
		cache_enter(dvp, *vpp, cnp);
E 136
I 136
D 138
	if ((ap->a_cnp->cn_flags & MAKEENTRY) && ap->a_cnp->cn_nameiop != CREATE)
		cache_enter(ap->a_dvp, *ap->a_vpp, ap->a_cnp);
E 138
I 138
D 141
	if ((flags & MAKEENTRY) && nameiop != CREATE)
E 141
I 141
	if ((cnp->cn_flags & MAKEENTRY) && nameiop != CREATE)
E 141
		cache_enter(vdp, *vpp, cnp);
E 138
E 136
E 115
E 90
D 85
	u.u_error = ENOENT;
	goto bad;
E 85
I 85
	return (ENOENT);

E 85
found:
I 84
D 85
#ifdef NAMEI_DIAGNOSTIC
	printf("\nfound\n");
#endif
E 85
E 84
I 48
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
D 139
	if (entryoffsetinblock + DIRSIZ(ep) > dp->i_size) {
E 139
I 139
	if (entryoffsetinblock + DIRSIZ(FSFMT(vdp), ep) > dp->i_size) {
E 139
E 24
D 57
		dirbad(dp, "i_size too small");
E 57
I 57
D 110
		dirbad(dp, ndp->ni_offset, "i_size too small");
E 110
I 110
D 112
		dirbad(dp, ndp->ni_ufs.ufs_offset, "i_size too small");
E 112
I 112
D 115
		ufs_dirbad(dp, ndp->ni_ufs.ufs_offset, "i_size too small");
E 115
I 115
D 117
		ufs_dirbad(dp, cnp->cn_ufs.ufs_offset, "i_size too small");
E 117
I 117
		ufs_dirbad(dp, dp->i_offset, "i_size too small");
E 117
E 115
E 112
E 110
E 57
D 24
		dp->i_size = entryoffsetinblock + ep->d_reclen;
E 24
I 24
D 139
		dp->i_size = entryoffsetinblock + DIRSIZ(ep);
E 139
I 139
		dp->i_size = entryoffsetinblock + DIRSIZ(FSFMT(vdp), ep);
E 139
E 24
D 145
		dp->i_flag |= IUPD|ICHG;
E 145
I 145
D 146
		dp->i_flag |= IUPDATE | ICHANGE;
E 146
I 146
		dp->i_flag |= IN_CHANGE | IN_UPDATE;
E 146
E 145
	}

	/*
D 47
	 * Found component in pathname; save directory
	 * entry in u.u_dent, and release directory buffer.
E 47
I 47
	 * Found component in pathname.
D 48
	 * If final component of path name, save information
E 48
I 48
	 * If the final component of path name, save information
E 48
	 * in the cache as to where the entry was found.
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
D 115
	if (*ndp->ni_next == '\0' && flag == LOOKUP)
D 110
		dp->i_diroff = ndp->ni_offset &~ (DIRBLKSIZ - 1);
E 110
I 110
		dp->i_diroff = ndp->ni_ufs.ufs_offset &~ (DIRBLKSIZ - 1);
E 115
I 115
D 117
	if ((cnp->cn_flags&ISLASTCN) && cnp->cn_nameiop == LOOKUP)
		dp->i_diroff = cnp->cn_ufs.ufs_offset &~ (DIRBLKSIZ - 1);
E 117
I 117
D 136
	if ((cnp->cn_flags & ISLASTCN) && cnp->cn_nameiop == LOOKUP)
E 136
I 136
D 138
	if ((ap->a_cnp->cn_flags & ISLASTCN) && ap->a_cnp->cn_nameiop == LOOKUP)
E 138
I 138
	if ((flags & ISLASTCN) && nameiop == LOOKUP)
E 138
E 136
		dp->i_diroff = dp->i_offset &~ (DIRBLKSIZ - 1);
E 117
E 115
E 110
E 85

	/*
	 * If deleting, and at end of pathname, return
	 * parameters which can be used to remove file.
D 34
	 * Note that in this case we return the directory
	 * inode, not the inode of the file being deleted.
E 34
I 34
D 85
	 * If the lockparent flag isn't set, we return only
D 57
	 * the directory (in u.u_pdir), otherwise we go
E 57
I 57
	 * the directory (in ndp->ni_pdir), otherwise we go
E 85
I 85
	 * If the wantparent flag isn't set, we return only
	 * the directory (in ndp->ni_dvp), otherwise we go
E 85
E 57
	 * on and lock the inode, being careful with ".".
E 34
	 */
D 34
	if (flag == 2 && *cp == 0) {
E 34
I 34
D 85
	if (flag == DELETE && *cp == 0) {
E 85
I 85
D 115
	if (flag == DELETE && *ndp->ni_next == 0) {
E 115
I 115
D 117
	if (cnp->cn_nameiop == DELETE && (cnp->cn_flags&ISLASTCN)) {
E 117
I 117
D 136
	if (cnp->cn_nameiop == DELETE && (cnp->cn_flags & ISLASTCN)) {
E 136
I 136
D 138
	if (ap->a_cnp->cn_nameiop == DELETE && (ap->a_cnp->cn_flags & ISLASTCN)) {
E 138
I 138
	if (nameiop == DELETE && (flags & ISLASTCN)) {
E 138
E 136
E 117
E 115
E 85
E 34
		/*
		 * Write access to directory required to delete files.
		 */
D 85
		if (access(dp, IWRITE))
			goto bad;
I 34
D 57
		u.u_pdir = dp;		/* for dirremove() */
E 57
I 57
		ndp->ni_pdir = dp;		/* for dirremove() */
E 85
I 85
D 99
		if (error = iaccess(dp, IWRITE, ndp->ni_cred))
E 99
I 99
D 107
		if (error = ufs_access(vdp, VWRITE, ndp->ni_cred))
E 107
I 107
D 115
		if (error = ufs_access(vdp, VWRITE, ndp->ni_cred, p))
E 115
I 115
D 135
		if (error = ufs_access(dvp, VWRITE, cnp->cn_cred, cnp->cn_proc))
E 135
I 135
D 136
		if (error = VOP_ACCESS(dvp, VWRITE, cnp->cn_cred, cnp->cn_proc))
E 136
I 136
D 138
		if (error = VOP_ACCESS(ap->a_dvp, VWRITE, ap->a_cnp->cn_cred, ap->a_cnp->cn_proc))
E 138
I 138
		if (error = VOP_ACCESS(vdp, VWRITE, cred, cnp->cn_proc))
E 138
E 136
E 135
E 115
E 107
E 99
			return (error);
E 85
E 57
E 34
		/*
D 57
		 * Return pointer to current entry in u.u_offset,
E 57
I 57
D 110
		 * Return pointer to current entry in ndp->ni_offset,
E 110
I 110
D 115
		 * Return pointer to current entry in ndp->ni_ufs.ufs_offset,
E 115
I 115
D 117
		 * Return pointer to current entry in cnp->cn_ufs.ufs_offset,
E 117
I 117
		 * Return pointer to current entry in dp->i_offset,
E 117
E 115
E 110
E 57
		 * and distance past previous entry (if there
D 57
		 * is a previous entry in this block) in u.u_count.
		 * Save directory inode pointer in u.u_pdir for dirremove().
E 57
I 57
D 110
		 * is a previous entry in this block) in ndp->ni_count.
E 110
I 110
D 117
		 * is a previous entry in this block) in ndp->ni_ufs.ufs_count.
E 117
I 117
		 * is a previous entry in this block) in dp->i_count.
E 117
E 110
D 90
		 * Save directory inode pointer in ndp->ni_pdir for dirremove().
E 90
I 90
		 * Save directory inode pointer in ndp->ni_dvp for dirremove().
E 90
E 57
		 */
D 57
		if ((u.u_offset&(DIRBLKSIZ-1)) == 0)
			u.u_count = 0;
E 57
I 57
D 110
		if ((ndp->ni_offset&(DIRBLKSIZ-1)) == 0)
			ndp->ni_count = 0;
E 110
I 110
D 115
		if ((ndp->ni_ufs.ufs_offset&(DIRBLKSIZ-1)) == 0)
			ndp->ni_ufs.ufs_count = 0;
E 115
I 115
D 117
		if ((cnp->cn_ufs.ufs_offset&(DIRBLKSIZ-1)) == 0)
			cnp->cn_ufs.ufs_count = 0;
E 117
I 117
		if ((dp->i_offset & (DIRBLKSIZ - 1)) == 0)
			dp->i_count = 0;
E 117
E 115
E 110
E 57
		else
D 57
			u.u_count = u.u_offset - prevoff;
E 57
I 57
D 110
			ndp->ni_count = ndp->ni_offset - prevoff;
E 57
I 34
D 85
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
E 85
I 85
D 99
		vdp = ITOV(dp);
E 99
		if (dp->i_number == ndp->ni_dent.d_ino) {
E 110
I 110
D 112
			ndp->ni_ufs.ufs_count = ndp->ni_ufs.ufs_offset - prevoff;
E 112
I 112
D 115
			ndp->ni_ufs.ufs_count =
			    ndp->ni_ufs.ufs_offset - prevoff;
E 112
		if (dp->i_number == ndp->ni_ufs.ufs_ino) {
E 110
D 89
			vdp->v_count++;
E 89
I 89
			VREF(vdp);
E 89
D 99
		} else {
D 92
			pdp = dp;
E 92
			if (error = iget(dp, ndp->ni_dent.d_ino, &tdp))
				return (error);
			vdp = ITOV(tdp);
			/*
			 * If directory is "sticky", then user must own
			 * the directory, or the file in it, else he
			 * may not delete it (unless he's root). This
			 * implements append-only directories.
			 */
D 92
			if ((pdp->i_mode & ISVTX) &&
E 92
I 92
			if ((dp->i_mode & ISVTX) &&
E 92
			    ndp->ni_cred->cr_uid != 0 &&
D 92
			    ndp->ni_cred->cr_uid != pdp->i_uid &&
E 92
I 92
			    ndp->ni_cred->cr_uid != dp->i_uid &&
E 92
			    tdp->i_uid != ndp->ni_cred->cr_uid) {
				iput(tdp);
				return (EPERM);
E 85
E 48
			}
I 92
			if (!lockparent)
				IUNLOCK(dp);
E 99
I 99
			ndp->ni_vp = vdp;
E 115
I 115
D 117
			cnp->cn_ufs.ufs_count =
			    cnp->cn_ufs.ufs_offset - prevoff;
		if (dp->i_number == cnp->cn_ufs.ufs_ino) {
			VREF(vdp);   /* NEEDSWORK: is vdp necessary? */
E 117
I 117
			dp->i_count = dp->i_offset - prevoff;
		if (dp->i_number == dp->i_ino) {
			VREF(vdp);
E 117
D 136
			*vpp = vdp;
E 136
I 136
D 138
			*ap->a_vpp = vdp;
E 138
I 138
			*vpp = vdp;
E 138
E 136
E 115
			return (0);
E 99
E 92
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
E 85
I 85
D 99
		ndp->ni_vp = vdp;
E 99
I 99
D 110
		if (error = iget(dp, ndp->ni_dent.d_ino, &tdp))
E 110
I 110
D 112
		if (error = iget(dp, ndp->ni_ufs.ufs_ino, &tdp))
E 112
I 112
D 113
		if (error = (ump->um_iget)(dp, ndp->ni_ufs.ufs_ino, &tdp))
E 113
I 113
D 115
		if (error = VOP_VGET(vdp, ndp->ni_ufs.ufs_ino, &tdp))
E 115
I 115
D 117
		if (error = VOP_VGET(dvp, cnp->cn_ufs.ufs_ino, &tdp))
E 117
I 117
D 136
		if (error = VOP_VGET(dvp, dp->i_ino, &tdp))
E 136
I 136
D 138
		if (error = VOP_VGET(ap->a_dvp, dp->i_ino, &tdp))
E 138
I 138
D 140
		if (error = VOP_VGET(vdp, dp->i_ino, &tdp))
E 140
I 140
		if (error = VFS_VGET(vdp->v_mount, dp->i_ino, &tdp))
E 140
E 138
E 136
E 117
E 115
E 113
E 112
E 110
			return (error);
		/*
		 * If directory is "sticky", then user must own
		 * the directory, or the file in it, else she
		 * may not delete it (unless she's root). This
		 * implements append-only directories.
		 */
		if ((dp->i_mode & ISVTX) &&
D 115
		    ndp->ni_cred->cr_uid != 0 &&
		    ndp->ni_cred->cr_uid != dp->i_uid &&
D 113
		    tdp->i_uid != ndp->ni_cred->cr_uid) {
D 112
			iput(tdp);
E 112
I 112
			ufs_iput(tdp);
E 113
I 113
		    VTOI(tdp)->i_uid != ndp->ni_cred->cr_uid) {
E 115
I 115
D 136
		    cnp->cn_cred->cr_uid != 0 &&
		    cnp->cn_cred->cr_uid != dp->i_uid &&
		    VTOI(tdp)->i_uid != cnp->cn_cred->cr_uid) {
E 136
I 136
D 138
		    ap->a_cnp->cn_cred->cr_uid != 0 &&
		    ap->a_cnp->cn_cred->cr_uid != dp->i_uid &&
		    VTOI(tdp)->i_uid != ap->a_cnp->cn_cred->cr_uid) {
E 138
I 138
		    cred->cr_uid != 0 &&
		    cred->cr_uid != dp->i_uid &&
I 157
		    tdp->v_type != VLNK &&
E 157
		    VTOI(tdp)->i_uid != cred->cr_uid) {
E 138
E 136
E 115
			vput(tdp);
E 113
E 112
			return (EPERM);
		}
D 113
		ndp->ni_vp = ITOV(tdp);
E 113
I 113
D 115
		ndp->ni_vp = tdp;
E 115
I 115
D 136
		*vpp = tdp;
E 136
I 136
D 138
		*ap->a_vpp = tdp;
E 138
I 138
		*vpp = tdp;
E 138
E 136
E 115
E 113
		if (!lockparent)
D 142
			IUNLOCK(dp);
E 142
I 142
D 156
			VOP_UNLOCK(vdp);
E 156
I 156
			VOP_UNLOCK(vdp, 0, p);
E 156
E 142
E 99
D 92
		if (!lockparent)
			IUNLOCK(pdp);
E 92
		return (0);
E 85
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
D 85
	 * If rewriting (rename), return the inode and the
E 85
I 85
	 * If rewriting (RENAME), return the inode and the
E 85
	 * information required to rewrite the present directory
	 * Must get inode of directory entry to verify it's a
D 85
	 * regular file, or empty directory.  
E 85
I 85
	 * regular file, or empty directory.
E 85
	 */
D 85
	if ((flag == CREATE && lockparent) && *cp == 0) {
		if (access(dp, IWRITE))
			goto bad;
D 57
		u.u_pdir = dp;		/* for dirrewrite() */
E 57
I 57
		ndp->ni_pdir = dp;		/* for dirrewrite() */
E 85
I 85
D 115
	if (flag == RENAME && wantparent && *ndp->ni_next == 0) {
D 99
		if (error = iaccess(dp, IWRITE, ndp->ni_cred))
E 99
I 99
D 107
		if (error = ufs_access(vdp, VWRITE, ndp->ni_cred))
E 107
I 107
		if (error = ufs_access(vdp, VWRITE, ndp->ni_cred, p))
E 115
I 115
D 117
	if (cnp->cn_nameiop == RENAME && wantparent && (cnp->cn_flags&ISLASTCN)) {
E 117
I 117
D 136
	if (cnp->cn_nameiop == RENAME && wantparent &&
	    (cnp->cn_flags & ISLASTCN)) {
E 117
D 135
		if (error = ufs_access(dvp, VWRITE, cnp->cn_cred, cnp->cn_proc))
E 135
I 135
		if (error = VOP_ACCESS(dvp, VWRITE, cnp->cn_cred, cnp->cn_proc))
E 136
I 136
D 138
	if (ap->a_cnp->cn_nameiop == RENAME && wantparent &&
	    (ap->a_cnp->cn_flags & ISLASTCN)) {
		if (error = VOP_ACCESS(ap->a_dvp, VWRITE, ap->a_cnp->cn_cred, ap->a_cnp->cn_proc))
E 138
I 138
D 158
	if (nameiop == RENAME && wantparent &&
	    (flags & ISLASTCN)) {
E 158
I 158
	if (nameiop == RENAME && wantparent && (flags & ISLASTCN)) {
E 158
		if (error = VOP_ACCESS(vdp, VWRITE, cred, cnp->cn_proc))
E 138
E 136
E 135
E 115
E 107
E 99
			return (error);
E 85
E 57
		/*
D 85
		 * Careful about locking second inode. 
		 * This can only occur if the target is ".". 
E 85
I 85
		 * Careful about locking second inode.
		 * This can only occur if the target is ".".
E 85
		 */
D 57
		if (dp->i_number == u.u_dent.d_ino) {
E 57
I 57
D 85
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
E 85
I 85
D 110
		if (dp->i_number == ndp->ni_dent.d_ino)
E 110
I 110
D 115
		if (dp->i_number == ndp->ni_ufs.ufs_ino)
E 115
I 115
D 117
		if (dp->i_number == cnp->cn_ufs.ufs_ino)
E 117
I 117
		if (dp->i_number == dp->i_ino)
E 117
E 115
E 110
			return (EISDIR);
D 110
		if (error = iget(dp, ndp->ni_dent.d_ino, &tdp))
E 110
I 110
D 112
		if (error = iget(dp, ndp->ni_ufs.ufs_ino, &tdp))
E 112
I 112
D 113
		if (error = (ump->um_iget)(dp, ndp->ni_ufs.ufs_ino, &tdp))
E 113
I 113
D 115
		if (error = VOP_VGET(vdp, ndp->ni_ufs.ufs_ino, &tdp))
E 115
I 115
D 117
		if (error = VOP_VGET(dvp, cnp->cn_ufs.ufs_ino, &tdp))
E 117
I 117
D 136
		if (error = VOP_VGET(dvp, dp->i_ino, &tdp))
E 136
I 136
D 138
		if (error = VOP_VGET(ap->a_dvp, dp->i_ino, &tdp))
E 138
I 138
D 140
		if (error = VOP_VGET(vdp, dp->i_ino, &tdp))
E 140
I 140
		if (error = VFS_VGET(vdp->v_mount, dp->i_ino, &tdp))
E 140
E 138
E 136
E 117
E 115
E 113
E 112
E 110
			return (error);
D 113
		ndp->ni_vp = ITOV(tdp);
E 113
I 113
D 115
		ndp->ni_vp = tdp;
E 113
I 110
		ndp->ni_nameiop |= SAVENAME;
E 115
I 115
D 136
		*vpp = tdp;
		cnp->cn_flags |= SAVENAME;
E 136
I 136
D 138
		*ap->a_vpp = tdp;
		ap->a_cnp->cn_flags |= SAVENAME;
E 138
I 138
		*vpp = tdp;
		cnp->cn_flags |= SAVENAME;
E 138
E 136
E 115
E 110
		if (!lockparent)
D 142
			IUNLOCK(dp);
E 142
I 142
D 156
			VOP_UNLOCK(vdp);
E 156
I 156
			VOP_UNLOCK(vdp, 0, p);
E 156
E 142
		return (0);
E 85
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
D 85
	 * Check for symbolic link, which may require us to massage the
	 * name before we continue translation.  We do not `iput' the
	 * directory because we may need it again if the symbolic link
E 85
I 85
D 142
	 * Step through the translation in the name.  We do not `iput' the
E 142
I 142
	 * Step through the translation in the name.  We do not `vput' the
E 142
	 * directory because we may need it again if a symbolic link
E 85
	 * is relative to the current directory.  Instead we save it
	 * unlocked as "pdp".  We must get the target inode before unlocking
	 * the directory to insure that the inode will not be removed
	 * before we get it.  We prevent deadlock by always fetching
	 * inodes from the root, moving down the directory tree. Thus
	 * when following backward pointers ".." we must unlock the
	 * parent directory before getting the requested directory.
	 * There is a potential race condition here if both the current
D 149
	 * and parent directories are removed before the `iget' for the
E 149
I 149
	 * and parent directories are removed before the VFS_VGET for the
E 149
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
D 142
	pdp = dp;
E 142
I 142
	pdp = vdp;
E 142
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
D 85
	if (isdotdot) {
E 85
I 85
D 115
	if (ndp->ni_isdotdot) {
E 115
I 115
D 117
	if (cnp->cn_flags&ISDOTDOT) {
E 117
I 117
D 136
	if (cnp->cn_flags & ISDOTDOT) {
E 136
I 136
D 138
	if (ap->a_cnp->cn_flags & ISDOTDOT) {
E 138
I 138
	if (flags & ISDOTDOT) {
E 138
E 136
E 117
E 115
E 85
E 48
D 55
		iunlock(pdp);	/* race to get the inode */
E 55
I 55
D 142
		IUNLOCK(pdp);	/* race to get the inode */
E 142
I 142
D 156
		VOP_UNLOCK(pdp);	/* race to get the inode */
E 156
I 156
		VOP_UNLOCK(pdp, 0, p);	/* race to get the inode */
E 156
E 142
E 55
D 57
		dp = iget(dp->i_dev, fs, u.u_dent.d_ino);
E 57
I 57
D 85
		dp = iget(dp->i_dev, fs, ndp->ni_dent.d_ino);
E 57
		if (dp == NULL)
			goto bad2;
E 85
I 85
D 110
		if (error = iget(dp, ndp->ni_dent.d_ino, &tdp)) {
E 110
I 110
D 112
		if (error = iget(dp, ndp->ni_ufs.ufs_ino, &tdp)) {
E 112
I 112
D 113
		if (error = (ump->um_iget)(dp, ndp->ni_ufs.ufs_ino, &tdp)) {
E 113
I 113
D 115
		if (error = VOP_VGET(vdp, ndp->ni_ufs.ufs_ino, &tdp)) {
E 115
I 115
D 117
		if (error = VOP_VGET(dvp, cnp->cn_ufs.ufs_ino, &tdp)) {
E 117
I 117
D 136
		if (error = VOP_VGET(dvp, dp->i_ino, &tdp)) {
E 136
I 136
D 138
		if (error = VOP_VGET(ap->a_dvp, dp->i_ino, &tdp)) {
E 138
I 138
D 140
		if (error = VOP_VGET(vdp, dp->i_ino, &tdp)) {
E 140
I 140
		if (error = VFS_VGET(vdp->v_mount, dp->i_ino, &tdp)) {
E 140
E 138
E 136
E 117
E 115
E 113
E 112
E 110
D 142
			ILOCK(pdp);
E 142
I 142
D 156
			VOP_LOCK(pdp);
E 156
I 156
			vn_lock(pdp, LK_EXCLUSIVE | LK_RETRY, p);
E 156
E 142
			return (error);
		}
I 86
D 115
		if (lockparent && *ndp->ni_next == '\0')
E 115
I 115
D 117
		if (lockparent && (cnp->cn_flags&ISLASTCN))
E 117
I 117
D 136
		if (lockparent && (cnp->cn_flags & ISLASTCN))
E 136
I 136
D 138
		if (lockparent && (ap->a_cnp->cn_flags & ISLASTCN))
E 138
I 138
D 142
		if (lockparent && (flags & ISLASTCN))
E 138
E 136
E 117
E 115
			ILOCK(pdp);
E 142
I 142
		if (lockparent && (flags & ISLASTCN) &&
D 156
		    (error = VOP_LOCK(pdp))) {
E 156
I 156
		    (error = vn_lock(pdp, LK_EXCLUSIVE, p))) {
E 156
			vput(tdp);
			return (error);
		}
E 142
E 86
D 113
		ndp->ni_vp = ITOV(tdp);
E 113
I 113
D 115
		ndp->ni_vp = tdp;
E 113
E 85
D 57
	} else if (dp->i_number == u.u_dent.d_ino) {
E 57
I 57
D 110
	} else if (dp->i_number == ndp->ni_dent.d_ino) {
E 110
I 110
	} else if (dp->i_number == ndp->ni_ufs.ufs_ino) {
E 110
E 57
D 85
		dp->i_count++;	/* we want ourself, ie "." */
E 85
I 85
D 99
		vdp = ITOV(dp);
E 99
D 89
		vdp->v_count++;	/* we want ourself, ie "." */
E 89
I 89
		VREF(vdp);	/* we want ourself, ie "." */
E 89
		ndp->ni_vp = vdp;
E 115
I 115
D 136
		*vpp = tdp;
E 136
I 136
D 138
		*ap->a_vpp = tdp;
E 138
I 138
		*vpp = tdp;
E 138
E 136
D 117
	} else if (dp->i_number == cnp->cn_ufs.ufs_ino) {
E 117
I 117
	} else if (dp->i_number == dp->i_ino) {
E 117
D 136
		VREF(dvp);	/* we want ourself, ie "." */
		*vpp = dvp;
E 136
I 136
D 138
		VREF(ap->a_dvp);	/* we want ourself, ie "." */
		*ap->a_vpp = ap->a_dvp;
E 138
I 138
		VREF(vdp);	/* we want ourself, ie "." */
		*vpp = vdp;
E 138
E 136
E 115
E 85
	} else {
D 57
		dp = iget(dp->i_dev, fs, u.u_dent.d_ino);
E 57
I 57
D 85
		dp = iget(dp->i_dev, fs, ndp->ni_dent.d_ino);
E 85
I 85
D 110
		if (error = iget(dp, ndp->ni_dent.d_ino, &tdp))
E 110
I 110
D 112
		if (error = iget(dp, ndp->ni_ufs.ufs_ino, &tdp))
E 112
I 112
D 113
		if (error = (ump->um_iget)(dp, ndp->ni_ufs.ufs_ino, &tdp))
E 113
I 113
D 115
		if (error = VOP_VGET(vdp, ndp->ni_ufs.ufs_ino, &tdp))
E 115
I 115
D 117
		if (error = VOP_VGET(dvp, cnp->cn_ufs.ufs_ino, &tdp))
E 117
I 117
D 136
		if (error = VOP_VGET(dvp, dp->i_ino, &tdp))
E 136
I 136
D 138
		if (error = VOP_VGET(ap->a_dvp, dp->i_ino, &tdp))
E 138
I 138
D 140
		if (error = VOP_VGET(vdp, dp->i_ino, &tdp))
E 140
I 140
		if (error = VFS_VGET(vdp->v_mount, dp->i_ino, &tdp))
E 140
E 138
E 136
E 117
E 115
E 113
E 112
E 110
			return (error);
E 85
E 57
D 55
		iunlock(pdp);
E 55
I 55
D 86
		IUNLOCK(pdp);
E 86
I 86
D 115
		if (!lockparent || *ndp->ni_next != '\0')
E 115
I 115
D 117
		if (!lockparent || !(cnp->cn_flags&ISLASTCN))
E 117
I 117
D 136
		if (!lockparent || !(cnp->cn_flags & ISLASTCN))
E 136
I 136
D 138
		if (!lockparent || !(ap->a_cnp->cn_flags & ISLASTCN))
E 138
I 138
		if (!lockparent || !(flags & ISLASTCN))
E 138
E 136
E 117
E 115
D 142
			IUNLOCK(pdp);
E 142
I 142
D 156
			VOP_UNLOCK(pdp);
E 156
I 156
			VOP_UNLOCK(pdp, 0, p);
E 156
E 142
E 86
E 55
D 85
		if (dp == NULL)
			goto bad2;
E 85
I 85
D 113
		ndp->ni_vp = ITOV(tdp);
E 113
I 113
D 115
		ndp->ni_vp = tdp;
E 115
I 115
D 136
		*vpp = tdp;
E 136
I 136
D 138
		*ap->a_vpp = tdp;
E 138
I 138
		*vpp = tdp;
E 138
E 136
E 115
E 113
E 85
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
D 85
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
		}
	}

haveino:
E 48
E 41
	fs = dp->i_fs;

	/*
	 * Check for symbolic link
	 */
D 57
	if ((dp->i_mode & IFMT) == IFLNK && (follow || *cp == '/')) {
E 57
I 57
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
		}
		if (++nlink > MAXSYMLINKS) {
E 69
			u.u_error = ELOOP;
			goto bad2;
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
E 23
E 19
E 13
	}
I 23
D 34
	irele(pdp);
E 34

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
	if (*cp == '/') {
		while (*cp == '/')
			cp++;
I 34
		irele(pdp);
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
E 85
I 85
D 115
	if (ndp->ni_makeentry)
		cache_enter(ndp);
E 115
I 115
D 136
	if (cnp->cn_flags & MAKEENTRY)
		cache_enter(dvp, *vpp, cnp);
E 136
I 136
D 138
	if (ap->a_cnp->cn_flags & MAKEENTRY)
		cache_enter(ap->a_dvp, *ap->a_vpp, ap->a_cnp);
E 138
I 138
D 141
	if (flags & MAKEENTRY)
E 141
I 141
	if (cnp->cn_flags & MAKEENTRY)
E 141
		cache_enter(vdp, *vpp, cnp);
E 138
E 136
E 115
	return (0);
E 85
E 19
E 13
}
I 135
D 136
#undef dvp
#undef vpp
#undef cnp
E 136
E 135

I 48
D 112

E 48
I 23
D 57
dirbad(ip, how)
E 57
I 57
dirbad(ip, offset, how)
E 112
I 112
void
ufs_dirbad(ip, offset, how)
E 112
E 57
	struct inode *ip;
I 57
D 121
	off_t offset;
E 121
I 121
	doff_t offset;
E 121
E 57
	char *how;
{
I 112
	struct mount *mp;
E 112

D 112
	printf("%s: bad dir ino %d at offset %d: %s\n",
D 57
	    ip->i_fs->fs_fsmnt, ip->i_number, u.u_offset, how);
E 57
I 57
	    ip->i_fs->fs_fsmnt, ip->i_number, offset, how);
I 96
D 108
	panic("bad dir");
E 108
I 108
	if (ip->i_fs->fs_ronly == 0)
E 112
I 112
	mp = ITOV(ip)->v_mount;
	(void)printf("%s: bad dir ino %d at offset %d: %s\n",
	    mp->mnt_stat.f_mntonname, ip->i_number, offset, how);
	if ((mp->mnt_stat.f_flags & MNT_RDONLY) == 0)
E 112
		panic("bad dir");
E 108
E 96
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
D 112
dirbadentry(ep, entryoffsetinblock)
E 112
I 112
int
D 139
ufs_dirbadentry(ep, entryoffsetinblock)
E 139
I 139
ufs_dirbadentry(dp, ep, entryoffsetinblock)
	struct vnode *dp;
E 139
E 112
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
I 139
	int namlen;
E 139

I 139
#	if (BYTE_ORDER == LITTLE_ENDIAN)
		if (dp->v_mount->mnt_maxsymlinklen > 0)
			namlen = ep->d_namlen;
		else
			namlen = ep->d_type;
#	else
		namlen = ep->d_namlen;
#	endif
E 139
I 52
D 72
	if ((ep->d_reclen & 0x3) != 0 || ep->d_reclen <= 0 ||
E 72
I 72
	if ((ep->d_reclen & 0x3) != 0 ||
E 72
	    ep->d_reclen > DIRBLKSIZ - (entryoffsetinblock & (DIRBLKSIZ - 1)) ||
D 112
	    ep->d_reclen < DIRSIZ(ep) || ep->d_namlen > MAXNAMLEN)
		return (1);
E 112
I 112
D 139
	    ep->d_reclen < DIRSIZ(ep) || ep->d_namlen > MAXNAMLEN) {
E 139
I 139
	    ep->d_reclen < DIRSIZ(FSFMT(dp), ep) || namlen > MAXNAMLEN) {
E 139
		/*return (1); */
		printf("First bad\n");
		goto bad;
	}
I 150
	if (ep->d_ino == 0)
		return (0);
E 150
E 112
E 52
D 139
	for (i = 0; i < ep->d_namlen; i++)
E 139
I 139
	for (i = 0; i < namlen; i++)
E 139
D 57
		if (ep->d_name[i] == 0)
E 57
I 57
D 112
		if (ep->d_name[i] == '\0')
E 57
			return (1);
E 112
I 112
		if (ep->d_name[i] == '\0') {
			/*return (1); */
			printf("Second bad\n");
			goto bad;
	}
	if (ep->d_name[i])
		goto bad;
E 112
D 155
	return (ep->d_name[i]);
E 155
I 155
	return (0);
E 155
I 112
bad:
D 121
printf("ufs_dirbadentry: jumping out: reclen: %d namlen %d ino %d name %s\n",
	ep->d_reclen, ep->d_namlen, ep->d_ino, ep->d_name );
E 121
D 155
	return(1);
E 155
I 155
	return (1);
E 155
E 112
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
D 85
 * which it left in the u. area.  The argument ip is the inode which
D 57
 * the new directory entry will refer to.  The u. area field u.u_pdir is
E 57
I 57
 * the new directory entry will refer to.  The u. area field ndp->ni_pdir is
E 57
 * a pointer to the directory to be written, which was left locked by
E 85
I 85
D 110
 * which it left in nameidata.  The argument ip is the inode which the
 * new directory entry will refer to.  The nameidata field ndp->ni_dvp
 * is a pointer to the directory to be written, which was left locked by
E 85
D 57
 * namei.  Remaining parameters (u.u_offset, u.u_count) indicate
E 57
I 57
 * namei.  Remaining parameters (ndp->ni_offset, ndp->ni_count) indicate
E 57
 * how the space for the new entry is to be gotten.
E 110
I 110
 * that it left in nameidata.  The argument ip is the inode which the new
D 117
 * directory entry will refer to.  The nameidata field ndp->ni_dvp is a
 * pointer to the directory to be written, which was left locked by namei.
 * Remaining parameters (ndp->ni_ufs.ufs_offset, ndp->ni_ufs.ufs_count)
 * indicate how the space for the new entry is to be obtained.
E 117
I 117
 * directory entry will refer to.  Dvp is a pointer to the directory to
 * be written, which was left locked by namei. Remaining parameters
 * (dp->i_offset, dp->i_count) indicate how the space for the new
 * entry is to be obtained.
E 117
E 110
 */
D 57
direnter(ip)
E 57
I 57
D 112
direnter(ip, ndp)
E 112
I 112
int
D 115
ufs_direnter(ip, ndp)
E 115
I 115
D 116
ufs_direnter(ip, dvp, cnp)   /* converted to CN.  */
/* old: ufs_direnter(ip, ndp) */
E 116
I 116
ufs_direnter(ip, dvp, cnp)
E 116
E 115
E 112
E 57
	struct inode *ip;
I 57
D 115
	register struct nameidata *ndp;
E 115
I 115
	struct vnode *dvp;
	register struct componentname *cnp;
E 115
E 57
E 23
E 19
{
I 135
D 140
	USES_VOP_BLKATOFF;
	USES_VOP_BWRITE;
	USES_VOP_TRUNCATE;
	USES_VOP_WRITE;
E 140
E 135
I 23
D 151
	register struct direct *ep, *nep;
E 151
I 63
D 85
	register struct inode *dp = ndp->ni_pdir;
E 85
I 85
D 112
	register struct inode *dp = VTOI(ndp->ni_dvp);
E 112
I 112
	register struct inode *dp;
I 113
D 115
	register struct vnode *dvp;
E 115
E 113
E 112
E 85
E 63
D 27
	struct fs *fs;
E 27
D 151
	struct buf *bp;
E 151
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
D 112
	int loc, spacefree, error = 0;
E 112
I 112
	struct direct newdir;
D 151
	struct iovec aiov;
D 113
	struct ufsmount *ump;
E 113
	struct uio auio;
E 112
E 40
E 39
D 30
	u_int dsize, newentrysize;
E 30
I 30
	u_int dsize;
D 112
	int newentrysize;
E 112
I 112
	int error, loc, newentrysize, spacefree;
E 112
E 30
E 27
	char *dirbuf;
E 151
I 110
D 112
	struct uio auio;
	struct iovec aiov;
	struct direct newdir;
E 112
E 110
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
D 110
	ndp->ni_dent.d_ino = ip->i_number;
	newentrysize = DIRSIZ(&ndp->ni_dent);
	if (ndp->ni_count == 0) {
E 110
I 110
#ifdef DIAGNOSTIC
D 115
	if ((ndp->ni_nameiop & SAVENAME) == 0)
E 115
I 115
	if ((cnp->cn_flags & SAVENAME) == 0)
E 115
		panic("direnter: missing name");
#endif
I 112
D 113
	dp = VTOI(ndp->ni_dvp);
	ump = VFSTOUFS(ndp->ni_dvp->v_mount);
E 113
I 113
D 115
	dvp = ndp->ni_dvp;
E 115
	dp = VTOI(dvp);
E 113
E 112
	newdir.d_ino = ip->i_number;
D 115
	newdir.d_namlen = ndp->ni_namelen;
	bcopy(ndp->ni_ptr, newdir.d_name, (unsigned)ndp->ni_namelen + 1);
E 115
I 115
	newdir.d_namlen = cnp->cn_namelen;
	bcopy(cnp->cn_nameptr, newdir.d_name, (unsigned)cnp->cn_namelen + 1);
E 115
D 139
	newentrysize = DIRSIZ(&newdir);
E 139
I 139
	if (dvp->v_mount->mnt_maxsymlinklen > 0)
		newdir.d_type = IFTODT(ip->i_mode);
	else {
		newdir.d_type = 0;
#		if (BYTE_ORDER == LITTLE_ENDIAN)
			{ u_char tmp = newdir.d_namlen;
			newdir.d_namlen = newdir.d_type;
			newdir.d_type = tmp; }
#		endif
	}
D 151
	newentrysize = DIRSIZ(FSFMT(dvp), &newdir);
E 151
I 151
	return (ufs_direnter2(dvp, &newdir, cnp->cn_cred, cnp->cn_proc));
}

/*
 * Common entry point for directory entry removal used by ufs_direnter
 * and ufs_whiteout
 */
ufs_direnter2(dvp, dirp, cr, p)
	struct vnode *dvp;
	struct direct *dirp;
	struct ucred *cr;
	struct proc *p;
{
	int newentrysize;
	struct inode *dp;
	struct buf *bp;
	struct iovec aiov;
	struct uio auio;
	u_int dsize;
	struct direct *ep, *nep;
	int error, loc, spacefree;
	char *dirbuf;

	dp = VTOI(dvp);
	newentrysize = DIRSIZ(FSFMT(dvp), dirp);

E 151
E 139
D 115
	if (ndp->ni_ufs.ufs_count == 0) {
E 115
I 115
D 117
	if (cnp->cn_ufs.ufs_count == 0) {
E 117
I 117
	if (dp->i_count == 0) {
E 117
E 115
E 110
E 57
		/*
D 57
		 * If u.u_count is 0, then namei could find no space in the
		 * directory.  In this case u.u_offset will be on a directory
E 57
I 57
D 110
		 * If ndp->ni_count is 0, then namei could find no space in the
		 * directory. In this case ndp->ni_offset will be on a directory
E 57
		 * block boundary and we will write the new entry into a fresh
		 * block.
E 110
I 110
D 115
		 * If ndp->ni_ufs.ufs_count is 0, then namei could find no
E 115
I 115
D 117
		 * If cnp->cn_ufs.ufs_count is 0, then namei could find no
E 115
		 * space in the directory. Here, ndp->ni_ufs.ufs_offset will
E 117
I 117
		 * If dp->i_count is 0, then namei could find no
		 * space in the directory. Here, dp->i_offset will
E 117
		 * be on a directory block boundary and we will write the
		 * new entry into a fresh block.
E 110
		 */
D 57
		if (u.u_offset&(DIRBLKSIZ-1))
E 57
I 57
D 110
		if (ndp->ni_offset&(DIRBLKSIZ-1))
E 110
I 110
D 115
		if (ndp->ni_ufs.ufs_offset & (DIRBLKSIZ - 1))
E 115
I 115
D 117
		if (cnp->cn_ufs.ufs_offset & (DIRBLKSIZ - 1))
E 117
I 117
		if (dp->i_offset & (DIRBLKSIZ - 1))
E 117
E 115
E 110
E 57
D 146
			panic("wdir: newblk");
E 146
I 146
D 151
			panic("ufs_direnter: newblk");
E 151
I 151
			panic("ufs_direnter2: newblk");
E 151
E 146
I 111
D 115
		auio.uio_offset = ndp->ni_ufs.ufs_offset;
E 115
I 115
D 117
		auio.uio_offset = cnp->cn_ufs.ufs_offset;
E 117
I 117
		auio.uio_offset = dp->i_offset;
E 117
E 115
E 111
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
D 110
		ndp->ni_dent.d_reclen = DIRBLKSIZ;
D 63
		error = rdwri(UIO_WRITE, ndp->ni_pdir, (caddr_t)&ndp->ni_dent,
E 63
I 63
D 87
		error = rdwri(UIO_WRITE, dp, (caddr_t)&ndp->ni_dent,
E 63
D 85
		    newentrysize, ndp->ni_offset, 1, (int *)0);
E 85
I 85
		    newentrysize, ndp->ni_offset, UIO_SYSSPACE, ndp->ni_cred,
		    (int *)0);
E 87
I 87
		ndp->ni_count = newentrysize;
		ndp->ni_resid = newentrysize;
I 88
		ndp->ni_base = (caddr_t)&ndp->ni_dent;
I 105
		ndp->ni_iov = &ndp->ni_nd.nd_iovec;
		ndp->ni_iovcnt = 1;
		ndp->ni_rw = UIO_WRITE;
E 105
I 98
		ndp->ni_uioseg = UIO_SYSSPACE;
E 98
E 88
D 95
		error = writeip(dp, &ndp->ni_uio, ndp->ni_cred);
E 95
I 95
		error =
		    ufs_write(ndp->ni_dvp, &ndp->ni_uio, IO_SYNC, ndp->ni_cred);
E 110
I 110
D 151
		newdir.d_reclen = DIRBLKSIZ;
E 151
I 151
		dirp->d_reclen = DIRBLKSIZ;
E 151
		auio.uio_resid = newentrysize;
		aiov.iov_len = newentrysize;
D 151
		aiov.iov_base = (caddr_t)&newdir;
E 151
I 151
		aiov.iov_base = (caddr_t)dirp;
E 151
		auio.uio_iov = &aiov;
		auio.uio_iovcnt = 1;
		auio.uio_rw = UIO_WRITE;
		auio.uio_segflg = UIO_SYSSPACE;
		auio.uio_procp = (struct proc *)0;
D 112
		error = ufs_write(ndp->ni_dvp, &auio, IO_SYNC, ndp->ni_cred);
E 110
E 95
E 87
E 85
I 65
D 100
		if (DIRBLKSIZ > dp->i_fs->fs_fsize)
E 100
I 100
		if (DIRBLKSIZ > dp->i_fs->fs_fsize) {
E 100
D 85
			panic("wdir: blksize"); /* XXX - should grow w/bmap() */
E 85
I 85
			panic("wdir: blksize"); /* XXX - should grow w/balloc */
E 85
D 100
		else
E 100
I 100
D 111
		} else {
E 111
I 111
		} else if (!error) {
E 112
I 112
D 113
		error =
		    (ump->um_write)(ndp->ni_dvp, &auio, IO_SYNC, ndp->ni_cred);
		if (DIRBLKSIZ > ump->um_mountp->mnt_stat.f_fsize)
E 113
I 113
D 115
		error = VOP_WRITE(dvp, &auio, IO_SYNC, ndp->ni_cred);
E 115
I 115
D 151
		error = VOP_WRITE(dvp, &auio, IO_SYNC, cnp->cn_cred);
E 151
I 151
		error = VOP_WRITE(dvp, &auio, IO_SYNC, cr);
E 151
E 115
		if (DIRBLKSIZ >
D 114
		    VFSTOUFS(dvp->v_mount)->um_mountp->mnt_stat.f_fsize)
E 114
I 114
		    VFSTOUFS(dvp->v_mount)->um_mountp->mnt_stat.f_bsize)
E 114
E 113
			/* XXX should grow with balloc() */
D 151
			panic("ufs_direnter: frag size");
E 151
I 151
			panic("ufs_direnter2: frag size");
E 151
		else if (!error) {
E 112
E 111
E 100
			dp->i_size = roundup(dp->i_size, DIRBLKSIZ);
I 100
D 145
			dp->i_flag |= ICHG;
E 145
I 145
D 146
			dp->i_flag |= ICHANGE;
E 146
I 146
			dp->i_flag |= IN_CHANGE;
E 146
E 145
		}
E 100
E 65
D 63
		iput(ndp->ni_pdir);
E 63
I 63
D 105
		iput(dp);
E 105
E 63
E 57
D 39
		return;
E 39
I 39
		return (error);
E 39
	}

	/*
D 57
	 * If u.u_count is non-zero, then namei found space for the
	 * new entry in the range u.u_offset to u.u_offset+u.u_count.
E 57
I 57
D 110
	 * If ndp->ni_count is non-zero, then namei found space for the new
	 * entry in the range ndp->ni_offset to ndp->ni_offset + ndp->ni_count.
E 57
	 * in the directory.  To use this space, we may have to compact
	 * the entries located there, by copying them together towards
	 * the beginning of the block, leaving the free space in
	 * one usable chunk at the end.
E 110
I 110
D 115
	 * If ndp->ni_ufs.ufs_count is non-zero, then namei found space
	 * for the new entry in the range ndp->ni_ufs.ufs_offset to
	 * ndp->ni_ufs.ufs_offset + ndp->ni_ufs.ufs_count in the directory.
E 115
I 115
D 117
	 * If cnp->cn_ufs.ufs_count is non-zero, then namei found space
	 * for the new entry in the range cnp->cn_ufs.ufs_offset to
	 * cnp->cn_ufs.ufs_offset + cnp->cn_ufs.ufs_count in the directory.
E 117
I 117
	 * If dp->i_count is non-zero, then namei found space
	 * for the new entry in the range dp->i_offset to
	 * dp->i_offset + dp->i_count in the directory.
E 117
E 115
	 * To use this space, we may have to compact the entries located
	 * there, by copying them together towards the beginning of the
	 * block, leaving the free space in one usable chunk at the end.
E 110
	 */

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
D 110
	if (ndp->ni_offset + ndp->ni_count > dp->i_size)
		dp->i_size = ndp->ni_offset + ndp->ni_count;
E 110
I 110
D 115
	if (ndp->ni_ufs.ufs_offset + ndp->ni_ufs.ufs_count > dp->i_size)
		dp->i_size = ndp->ni_ufs.ufs_offset + ndp->ni_ufs.ufs_count;
E 115
I 115
D 117
	if (cnp->cn_ufs.ufs_offset + cnp->cn_ufs.ufs_count > dp->i_size)
		dp->i_size = cnp->cn_ufs.ufs_offset + cnp->cn_ufs.ufs_count;
E 117
I 117
	if (dp->i_offset + dp->i_count > dp->i_size)
		dp->i_size = dp->i_offset + dp->i_count;
E 117
E 115
E 110
E 63
E 57
D 30
	}
E 30
D 72

E 72
	/*
D 85
	 * Get the block containing the space for the new directory
D 39
	 * entry.
E 39
I 39
	 * entry.  Should return error by result instead of u.u_error.
E 85
I 85
	 * Get the block containing the space for the new directory entry.
E 85
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
D 85
	bp = blkatoff(dp, ndp->ni_offset, (char **)&dirbuf);
E 63
E 57
E 24
D 34
	if (bp == 0)
E 34
I 34
	if (bp == 0) {
E 85
I 85
D 105
	if (error = blkatoff(dp, ndp->ni_offset, (char **)&dirbuf, &bp)) {
E 85
D 57
		iput(u.u_pdir);
E 57
I 57
D 63
		iput(ndp->ni_pdir);
E 63
I 63
		iput(dp);
E 105
I 105
D 110
	if (error = blkatoff(dp, ndp->ni_offset, (char **)&dirbuf, &bp))
E 110
I 110
D 112
	if (error = blkatoff(dp, ndp->ni_ufs.ufs_offset, (char **)&dirbuf, &bp))
E 112
I 112
D 113
	if (error =
	    (ump->um_blkatoff)(dp, ndp->ni_ufs.ufs_offset, &dirbuf, &bp))
E 113
I 113
D 115
	if (error = VOP_BLKATOFF(dvp, ndp->ni_ufs.ufs_offset, &dirbuf, &bp))
E 115
I 115
D 117
	if (error = VOP_BLKATOFF(dvp, cnp->cn_ufs.ufs_offset, &dirbuf, &bp))
E 117
I 117
D 121
	if (error = VOP_BLKATOFF(dvp, dp->i_offset, &dirbuf, &bp))
E 121
I 121
	if (error = VOP_BLKATOFF(dvp, (off_t)dp->i_offset, &dirbuf, &bp))
E 121
E 117
E 115
E 113
E 112
E 110
E 105
E 63
E 57
E 34
D 39
		return;
E 39
I 39
D 85
		return (u.u_error);
E 85
I 85
		return (error);
E 85
E 39
I 34
D 105
	}
E 105
E 34
D 24
printf("direnter u.u_offset %d u.u_count %d, bpaddr %x, dirbuf %x\n",
    u.u_offset, u.u_count, bp->b_un.b_addr, dirbuf);
E 24
D 72

E 72
	/*
D 110
	 * Find space for the new entry.  In the simple case, the
	 * entry at offset base will have the space.  If it does
	 * not, then namei arranged that compacting the region
D 57
	 * u.u_offset to u.u_offset+u.u_count would yield the space.
E 57
I 57
	 * ndp->ni_offset to ndp->ni_offset+ndp->ni_count would yield the space.
E 110
I 110
	 * Find space for the new entry. In the simple case, the entry at
	 * offset base will have the space. If it does not, then namei
D 115
	 * arranged that compacting the region ndp->ni_ufs.ufs_offset to
	 * ndp->ni_ufs.ufs_offset + ndp->ni_ufs.ufs_count would yield the
E 115
I 115
D 117
	 * arranged that compacting the region cnp->cn_ufs.ufs_offset to
	 * cnp->cn_ufs.ufs_offset + cnp->cn_ufs.ufs_count would yield the
E 117
I 117
	 * arranged that compacting the region dp->i_offset to
	 * dp->i_offset + dp->i_count would yield the
E 117
E 115
	 * space.
E 110
E 57
	 */
	ep = (struct direct *)dirbuf;
D 139
	dsize = DIRSIZ(ep);
E 139
I 139
	dsize = DIRSIZ(FSFMT(dvp), ep);
E 139
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
D 110
	for (loc = ep->d_reclen; loc < ndp->ni_count; ) {
E 110
I 110
D 115
	for (loc = ep->d_reclen; loc < ndp->ni_ufs.ufs_count; ) {
E 115
I 115
D 117
	for (loc = ep->d_reclen; loc < cnp->cn_ufs.ufs_count; ) {
E 117
I 117
	for (loc = ep->d_reclen; loc < dp->i_count; ) {
E 117
E 115
E 110
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
D 85
			spacefree += dsize;	
E 85
I 85
			spacefree += dsize;
E 85
E 40
		}
D 139
		dsize = DIRSIZ(nep);
E 139
I 139
		dsize = DIRSIZ(FSFMT(dvp), nep);
E 139
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
D 151
	if (ep->d_ino == 0) {
E 151
I 151
	if (ep->d_ino == 0 ||
	    (ep->d_ino == WINO &&
	     bcmp(ep->d_name, dirp->d_name, dirp->d_namlen) == 0)) {
E 151
D 40
		if (freespace + dsize < newentrysize)
E 40
I 40
		if (spacefree + dsize < newentrysize)
E 40
D 146
			panic("wdir: compact1");
E 146
I 146
D 151
			panic("ufs_direnter: compact1");
E 146
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
D 110
		ndp->ni_dent.d_reclen = spacefree + dsize;
E 110
I 110
		newdir.d_reclen = spacefree + dsize;
E 151
I 151
			panic("ufs_direnter2: compact1");
		dirp->d_reclen = spacefree + dsize;
E 151
E 110
E 57
E 40
	} else {
D 40
		if (freespace < newentrysize)
E 40
I 40
		if (spacefree < newentrysize)
E 40
D 146
			panic("wdir: compact2");
E 146
I 146
D 151
			panic("ufs_direnter: compact2");
E 146
D 40
		u.u_dent.d_reclen = freespace;
E 40
I 40
D 57
		u.u_dent.d_reclen = spacefree;
E 57
I 57
D 110
		ndp->ni_dent.d_reclen = spacefree;
E 110
I 110
		newdir.d_reclen = spacefree;
E 151
I 151
			panic("ufs_direnter2: compact2");
		dirp->d_reclen = spacefree;
E 151
E 110
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
D 110
	bcopy((caddr_t)&ndp->ni_dent, (caddr_t)ep, (u_int)newentrysize);
E 110
I 110
D 151
	bcopy((caddr_t)&newdir, (caddr_t)ep, (u_int)newentrysize);
E 151
I 151
	bcopy((caddr_t)dirp, (caddr_t)ep, (u_int)newentrysize);
E 151
E 110
E 57
E 32
E 29
D 85
	bwrite(bp);
E 85
I 85
D 112
	error = bwrite(bp);
E 112
I 112
D 113
	error = (ump->um_bwrite)(bp);
E 113
I 113
	error = VOP_BWRITE(bp);
E 113
E 112
E 85
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
D 145
	dp->i_flag |= IUPD|ICHG;
E 145
I 145
D 146
	dp->i_flag |= IUPDATE | ICHANGE;
E 146
I 146
	dp->i_flag |= IN_CHANGE | IN_UPDATE;
E 146
E 145
D 99
	if (ndp->ni_endoff && ndp->ni_endoff < dp->i_size)
E 99
I 99
D 110
	if (!error && ndp->ni_endoff && ndp->ni_endoff < dp->i_size)
E 99
D 72
		itrunc(dp, ndp->ni_endoff);
E 72
I 72
D 85
		itrunc(dp, (u_long)ndp->ni_endoff);
E 85
I 85
D 97
		error = itrunc(dp, (u_long)ndp->ni_endoff);
E 97
I 97
		error = itrunc(dp, (u_long)ndp->ni_endoff, IO_SYNC);
E 110
I 110
D 115
	if (!error && ndp->ni_ufs.ufs_endoff &&
	    ndp->ni_ufs.ufs_endoff < dp->i_size)
D 112
		error = itrunc(dp, (u_long)ndp->ni_ufs.ufs_endoff, IO_SYNC);
E 112
I 112
D 113
		error = (ump->um_itrunc)(dp,
		    (u_long)ndp->ni_ufs.ufs_endoff, IO_SYNC);
E 113
I 113
		error = VOP_TRUNCATE(dvp, (u_long)ndp->ni_ufs.ufs_endoff,
E 115
I 115
D 117
	if (!error && cnp->cn_ufs.ufs_endoff &&
	    cnp->cn_ufs.ufs_endoff < dp->i_size)
		error = VOP_TRUNCATE(dvp, (u_long)cnp->cn_ufs.ufs_endoff,
E 115
		    IO_SYNC);
E 117
I 117
	if (!error && dp->i_endoff && dp->i_endoff < dp->i_size)
D 121
		error = VOP_TRUNCATE(dvp, (u_long)dp->i_endoff, IO_SYNC);
E 121
I 121
D 122
		error = VOP_TRUNCATE(dvp, (off_t)dp->i_endoff, IO_SYNC);
E 122
I 122
D 137
		error = VOP_TRUNCATE(dvp, (off_t)dp->i_endoff, IO_SYNC, NOCRED);
E 137
I 137
D 151
		error = VOP_TRUNCATE(dvp, (off_t)dp->i_endoff, IO_SYNC,
		    cnp->cn_cred, cnp->cn_proc);
E 151
I 151
		error = VOP_TRUNCATE(dvp, (off_t)dp->i_endoff, IO_SYNC, cr, p);
E 151
E 137
E 122
E 121
E 117
E 113
E 112
E 110
E 97
E 85
E 72
D 105
	iput(dp);
E 105
E 63
E 57
I 39
	return (error);
E 39
E 23
I 19
}

I 34
/*
D 87
 * Remove a directory entry after a call to namei, using the
 * parameters which it left in the u. area.  The u. entry
E 87
I 87
 * Remove a directory entry after a call to namei, using
 * the parameters which it left in nameidata. The entry
E 87
D 57
 * u_offset contains the offset into the directory of the
 * entry to be eliminated.  The u_count field contains the
E 57
I 57
D 110
 * ni_offset contains the offset into the directory of the
 * entry to be eliminated.  The ni_count field contains the
E 110
I 110
D 117
 * ni_ufs.ufs_offset contains the offset into the directory of the
 * entry to be eliminated.  The ni_ufs.ufs_count field contains the
E 117
I 117
 * dp->i_offset contains the offset into the directory of the
 * entry to be eliminated.  The dp->i_count field contains the
E 117
E 110
E 57
 * size of the previous record in the directory.  If this
 * is 0, the first entry is being deleted, so we need only
 * zero the inode number to mark the entry as free.  If the
D 110
 * entry isn't the first in the directory, we must reclaim
E 110
I 110
 * entry is not the first in the directory, we must reclaim
E 110
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
D 112
dirremove(ndp)
E 112
I 112
int
D 115
ufs_dirremove(ndp)
E 112
	register struct nameidata *ndp;
E 115
I 115
D 116
ufs_dirremove(dvp, cnp)   /* converted to CN.  */
E 116
I 116
ufs_dirremove(dvp, cnp)
E 116
	struct vnode *dvp;
	struct componentname *cnp;
D 116
/* old: ufs_dirremove(ndp) */
E 116
E 115
E 57
E 23
{
I 135
D 140
	USES_VOP_BLKATOFF;
	USES_VOP_BWRITE;
E 140
E 135
D 23
	register int len;
E 23
I 23
D 57
	register struct inode *dp = u.u_pdir;
E 57
I 57
D 85
	register struct inode *dp = ndp->ni_pdir;
E 57
D 27
	register struct fs *fs = dp->i_fs;
E 27
	register struct buf *bp;
E 85
I 85
D 112
	register struct inode *dp = VTOI(ndp->ni_dvp);
E 112
I 112
	register struct inode *dp;
D 113
	struct ufsmount *ump;
E 113
E 112
E 85
	struct direct *ep;
I 85
	struct buf *bp;
	int error;
E 85
E 23

I 112
D 115
	dp = VTOI(ndp->ni_dvp);
D 113
	ump = VFSTOUFS(ndp->ni_dvp->v_mount);
E 113
E 112
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
D 110
	if (ndp->ni_count == 0) {
E 110
I 110
	if (ndp->ni_ufs.ufs_count == 0) {
E 115
I 115
	dp = VTOI(dvp);
I 151

	if (cnp->cn_flags & DOWHITEOUT) {
		/*
D 155
		 * First entry in block: set d_ino to zero.
E 155
I 155
		 * Whiteout entry: set d_ino to WINO.
E 155
		 */
		if (error =
		    VOP_BLKATOFF(dvp, (off_t)dp->i_offset, (char **)&ep, &bp))
			return (error);
		ep->d_ino = WINO;
D 153
		if (ep->d_type == DT_DIR)
			ep->d_type = DT_WHTD;
		else
			ep->d_type = DT_WHT;
E 153
I 153
		ep->d_type = DT_WHT;
E 153
		error = VOP_BWRITE(bp);
		dp->i_flag |= IN_CHANGE | IN_UPDATE;
		return (error);
	}

E 151
D 117
	if (cnp->cn_ufs.ufs_count == 0) {
E 117
I 117
	if (dp->i_count == 0) {
E 117
E 115
E 110
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
D 110
		ndp->ni_dent.d_ino = 0;
D 85
		(void) rdwri(UIO_WRITE, dp, (caddr_t)&ndp->ni_dent,
		    (int)DIRSIZ(&ndp->ni_dent), ndp->ni_offset, 1, (int *)0);
E 85
I 85
D 87
		error = rdwri(UIO_WRITE, dp, (caddr_t)&ndp->ni_dent,
		    (int)DIRSIZ(&ndp->ni_dent), ndp->ni_offset, UIO_SYSSPACE,
		    ndp->ni_cred, (int *)0);
E 87
I 87
		ndp->ni_count = ndp->ni_resid = DIRSIZ(&ndp->ni_dent);
I 88
		ndp->ni_base = (caddr_t)&ndp->ni_dent;
I 105
		ndp->ni_iov = &ndp->ni_nd.nd_iovec;
		ndp->ni_iovcnt = 1;
		ndp->ni_rw = UIO_WRITE;
E 105
I 98
		ndp->ni_uioseg = UIO_SYSSPACE;
E 98
E 88
D 95
		error = writeip(dp, &ndp->ni_uio, ndp->ni_cred);
E 95
I 95
		error =
		    ufs_write(ndp->ni_dvp, &ndp->ni_uio, IO_SYNC, ndp->ni_cred);
E 95
E 87
E 85
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
D 85
		bp = blkatoff(dp, ndp->ni_offset - ndp->ni_count, (char **)&ep);
E 75
E 57
E 27
E 24
		if (bp == 0)
			return (0);
E 85
I 85
		if (error = blkatoff(dp, ndp->ni_offset - ndp->ni_count,
		    (char **)&ep, &bp)) {
E 110
I 110
D 112
		error = blkatoff(dp, ndp->ni_ufs.ufs_offset, (char **)&ep, &bp);
E 112
I 112
D 113
		error = (ump->um_blkatoff)(dp,
		    ndp->ni_ufs.ufs_offset, (char **)&ep, &bp);
E 112
		if (error)
E 113
I 113
D 115
		if (error = VOP_BLKATOFF(ndp->ni_dvp, ndp->ni_ufs.ufs_offset,
E 115
I 115
D 117
		if (error = VOP_BLKATOFF(dvp, cnp->cn_ufs.ufs_offset,
E 115
		    (char **)&ep, &bp))
E 117
I 117
D 121
		if (error = VOP_BLKATOFF(dvp, dp->i_offset, (char **)&ep, &bp))
E 121
I 121
		if (error =
		    VOP_BLKATOFF(dvp, (off_t)dp->i_offset, (char **)&ep, &bp))
E 121
E 117
E 113
E 110
			return (error);
D 110
		}
E 85
D 57
		ep->d_reclen += u.u_dent.d_reclen;
E 57
I 57
		ep->d_reclen += ndp->ni_dent.d_reclen;
E 110
I 110
		ep->d_ino = 0;
E 110
E 57
D 29
/*ZZ*/if((((char *)ep - bp->b_un.b_addr)&0x1ff)+u.u_dent.d_reclen > 512)
/*ZZ*/	panic("unlink: reclen");
E 29
D 85
		bwrite(bp);
E 85
I 85
D 112
		error = bwrite(bp);
E 112
I 112
D 113
		error = (ump->um_bwrite)(bp);
E 113
I 113
		error = VOP_BWRITE(bp);
E 113
E 112
E 85
D 145
		dp->i_flag |= IUPD|ICHG;
E 145
I 145
D 146
		dp->i_flag |= IUPDATE | ICHANGE;
E 146
I 146
		dp->i_flag |= IN_CHANGE | IN_UPDATE;
E 146
E 145
I 110
		return (error);
E 110
	}
I 110
	/*
	 * Collapse new free space into previous entry.
	 */
D 112
	if (error = blkatoff(dp, ndp->ni_ufs.ufs_offset - ndp->ni_ufs.ufs_count,
	    (char **)&ep, &bp)) {
E 112
I 112
D 113
	if (error = (ump->um_blkatoff)(dp,
E 113
I 113
D 115
	if (error = VOP_BLKATOFF(ndp->ni_dvp,
E 113
	    ndp->ni_ufs.ufs_offset - ndp->ni_ufs.ufs_count, (char **)&ep, &bp))
E 115
I 115
D 121
	if (error = VOP_BLKATOFF(dvp,
D 117
	    cnp->cn_ufs.ufs_offset - cnp->cn_ufs.ufs_count, (char **)&ep, &bp))
E 117
I 117
	    dp->i_offset - dp->i_count, (char **)&ep, &bp))
E 121
I 121
	if (error = VOP_BLKATOFF(dvp, (off_t)(dp->i_offset - dp->i_count),
	    (char **)&ep, &bp))
E 121
E 117
E 115
E 112
		return (error);
D 112
	}
E 112
D 115
	ep->d_reclen += ndp->ni_ufs.ufs_reclen;
E 115
I 115
D 117
	ep->d_reclen += cnp->cn_ufs.ufs_reclen;
E 117
I 117
	ep->d_reclen += dp->i_reclen;
E 117
E 115
D 112
	error = bwrite(bp);
E 112
I 112
D 113
	error = (ump->um_bwrite)(bp);
E 113
I 113
	error = VOP_BWRITE(bp);
E 113
E 112
D 145
	dp->i_flag |= IUPD|ICHG;
E 145
I 145
D 146
	dp->i_flag |= IUPDATE | ICHANGE;
E 146
I 146
	dp->i_flag |= IN_CHANGE | IN_UPDATE;
E 146
E 145
E 110
D 85
	return (1);
E 85
I 85
	return (error);
E 85
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
D 112
dirrewrite(dp, ip, ndp)
E 112
I 112
int
D 115
ufs_dirrewrite(dp, ip, ndp)
E 115
I 115
ufs_dirrewrite(dp, ip, cnp)
D 117
/* old: ufs_dirrewrite(dp, ip, ndp) */
E 117
E 115
E 112
E 57
	struct inode *dp, *ip;
I 57
D 115
	struct nameidata *ndp;
E 115
I 115
	struct componentname *cnp;
E 115
E 57
{
I 135
D 140
	USES_VOP_BLKATOFF;
	USES_VOP_BWRITE;
E 140
E 135
I 110
D 112
	struct direct *ep;
E 112
	struct buf *bp;
I 112
	struct direct *ep;
I 139
	struct vnode *vdp = ITOV(dp);
E 139
D 113
	struct ufsmount *ump;
E 113
E 112
	int error;
E 110

D 57
	u.u_dent.d_ino = ip->i_number;
	u.u_error = rdwri(UIO_WRITE, dp, (caddr_t)&u.u_dent,
		(int)DIRSIZ(&u.u_dent), u.u_offset, 1, (int *)0);
E 57
I 57
D 110
	ndp->ni_dent.d_ino = ip->i_number;
D 85
	u.u_error = rdwri(UIO_WRITE, dp, (caddr_t)&ndp->ni_dent,
		(int)DIRSIZ(&ndp->ni_dent), ndp->ni_offset, 1, (int *)0);
E 57
	iput(dp);
E 85
I 85
D 87
	return (rdwri(UIO_WRITE, dp, (caddr_t)&ndp->ni_dent,
	    (int)DIRSIZ(&ndp->ni_dent), ndp->ni_offset, UIO_SYSSPACE,
	    ndp->ni_cred, (int *)0));
E 87
I 87
	ndp->ni_count = ndp->ni_resid = DIRSIZ(&ndp->ni_dent);
I 88
	ndp->ni_base = (caddr_t)&ndp->ni_dent;
I 105
	ndp->ni_iov = &ndp->ni_nd.nd_iovec;
	ndp->ni_iovcnt = 1;
	ndp->ni_rw = UIO_WRITE;
E 105
I 98
	ndp->ni_uioseg = UIO_SYSSPACE;
E 98
E 88
D 95
	return (writeip(dp, &ndp->ni_uio, ndp->ni_cred));
E 95
I 95
	return (ufs_write(ITOV(dp), &ndp->ni_uio, IO_SYNC, ndp->ni_cred));
E 110
I 110
D 112
	if (error = blkatoff(dp, ndp->ni_ufs.ufs_offset, (char **)&ep, &bp))
E 112
I 112
D 113
	ump = VFSTOUFS(ndp->ni_dvp->v_mount);
	if (error =
	    (ump->um_blkatoff)(dp, ndp->ni_ufs.ufs_offset, (char **)&ep, &bp))
E 113
I 113
D 115
	if (error = VOP_BLKATOFF(ITOV(dp), ndp->ni_ufs.ufs_offset,
E 115
I 115
D 117
	if (error = VOP_BLKATOFF(ITOV(dp), cnp->cn_ufs.ufs_offset,
E 115
	    (char **)&ep, &bp))
E 117
I 117
D 121
	if (error = VOP_BLKATOFF(ITOV(dp), dp->i_offset, (char **)&ep, &bp))
E 121
I 121
D 139
	if (error =
	    VOP_BLKATOFF(ITOV(dp), (off_t)dp->i_offset, (char **)&ep, &bp))
E 139
I 139
	if (error = VOP_BLKATOFF(vdp, (off_t)dp->i_offset, (char **)&ep, &bp))
E 139
E 121
E 117
E 113
E 112
		return (error);
	ep->d_ino = ip->i_number;
I 139
	if (vdp->v_mount->mnt_maxsymlinklen > 0)
		ep->d_type = IFTODT(ip->i_mode);
E 139
D 112
	error = bwrite(bp);
E 112
I 112
D 113
	error = (ump->um_bwrite)(bp);
E 113
I 113
	error = VOP_BWRITE(bp);
E 113
E 112
D 145
	dp->i_flag |= IUPD|ICHG;
E 145
I 145
D 146
	dp->i_flag |= IUPDATE | ICHANGE;
E 146
I 146
	dp->i_flag |= IN_CHANGE | IN_UPDATE;
E 146
E 145
	return (error);
E 110
E 95
E 87
E 85
}

/*
E 34
D 112
 * Return buffer with contents of block "offset"
 * from the beginning of directory "ip".  If "res"
 * is non-zero, fill it in with a pointer to the
 * remaining space in the directory.
 */
E 24
D 85
struct buf *
D 24
batoffset(ip, offset, res)
E 24
I 24
blkatoff(ip, offset, res)
E 85
I 85
blkatoff(ip, offset, res, bpp)
E 85
E 24
	struct inode *ip;
	off_t offset;
	char **res;
I 85
	struct buf **bpp;
E 85
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
D 85
	register struct buf *bp;
E 85
I 85
	struct buf *bp;
E 85
I 68
	daddr_t bn;
I 85
	int error;
E 85
E 68

I 68
D 85
	bn = bmap(ip, lbn, B_READ, bsize);
E 68
	if (u.u_error)
		return (0);
E 85
I 85
	*bpp = 0;
D 97
	if (error = bmap(ip, lbn, &bn, (daddr_t *)0, (int *)0))
		return (error);
E 85
D 68
	bp = bread(ip->i_dev, bn, bsize);
E 68
I 68
	if (bn == (daddr_t)-1) {
		dirbad(ip, offset, "hole in dir");
D 85
		return (0);
E 85
I 85
		return (EIO);
E 85
	}
I 79
#ifdef SECSIZE
	bp = bread(ip->i_dev, fsbtodb(fs, bn), bsize, fs->fs_dbsize);
#else SECSIZE
E 79
D 85
	bp = bread(ip->i_dev, fsbtodb(fs, bn), bsize);
I 79
#endif SECSIZE
E 79
E 68
	if (bp->b_flags & B_ERROR) {
E 85
I 85
D 91
	error = bread(ip->i_devvp, bn, bsize, &bp);
E 91
I 91
	error = bread(ip->i_devvp, bn, bsize, NOCRED, &bp);
E 91
	if (error) {
E 97
I 97
	if (error = bread(ITOV(ip), lbn, bsize, NOCRED, &bp)) {
E 97
E 85
		brelse(bp);
D 85
		return (0);
E 85
I 85
		return (error);
E 85
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
D 85
	return (bp);
E 85
I 85
	*bpp = bp;
	return (0);
E 85
I 34
}

/*
E 112
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
D 85
dirempty(ip, parentino)
E 85
I 85
D 112
dirempty(ip, parentino, cred)
E 112
I 112
int
ufs_dirempty(ip, parentino, cred)
E 112
E 85
E 59
D 36
	struct inode *ip;
E 36
I 36
	register struct inode *ip;
I 59
	ino_t parentino;
I 85
	struct ucred *cred;
E 85
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
D 139
	int error, count;
E 139
I 139
	int error, count, namlen;
E 139
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
D 85
		error = rdwri(UIO_READ, ip, (caddr_t)dp, MINDIRSIZ,
		    off, 1, &count);
E 85
I 85
D 95
		error = rdwri(UIO_READ, ip, (caddr_t)dp, MINDIRSIZ, off,
		    UIO_SYSSPACE, cred, &count);
E 95
I 95
D 107
		error = vn_rdwr(UIO_READ, ITOV(ip), (caddr_t)dp, MINDIRSIZ,
		    off, UIO_SYSSPACE, IO_NODELOCKED, cred, &count);
E 107
I 107
		error = vn_rdwr(UIO_READ, ITOV(ip), (caddr_t)dp, MINDIRSIZ, off,
		   UIO_SYSSPACE, IO_NODELOCKED, cred, &count, (struct proc *)0);
E 107
E 95
E 85
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
D 151
		if (dp->d_ino == 0)
E 151
I 151
		if (dp->d_ino == 0 || dp->d_ino == WINO)
E 151
			continue;
I 44
		/* accept only "." and ".." */
D 139
		if (dp->d_namlen > 2)
E 139
I 139
#		if (BYTE_ORDER == LITTLE_ENDIAN)
			if (ITOV(ip)->v_mount->mnt_maxsymlinklen > 0)
				namlen = dp->d_namlen;
			else
				namlen = dp->d_type;
#		else
			namlen = dp->d_namlen;
#		endif
		if (namlen > 2)
E 139
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
D 139
		 * At this point d_namlen must be 1 or 2.
E 139
I 139
		 * At this point namlen must be 1 or 2.
E 139
		 * 1 implies ".", 2 implies ".." if second
		 * char is also "."
		 */
D 59
		if (dp->d_namlen == 1 || dp->d_name[1] == '.')
E 59
I 59
D 139
		if (dp->d_namlen == 1)
E 139
I 139
		if (namlen == 1)
E 139
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
D 112
 * The target is always iput() before returning.
E 112
I 112
D 142
 * The target is always iput before returning.
E 142
I 142
 * The target is always vput before returning.
E 142
E 112
 */
D 85
checkpath(source, target)
E 85
I 85
D 112
checkpath(source, target, cred)
E 112
I 112
int
ufs_checkpath(source, target, cred)
E 112
E 85
	struct inode *source, *target;
I 85
	struct ucred *cred;
E 85
{
I 135
D 140
	USES_VOP_VGET;
E 140
E 135
D 142
	struct dirtemplate dirbuf;
D 85
	register struct inode *ip;
E 85
I 85
D 113
	struct inode *ip;
E 85
D 112
	int error = 0;
E 112
I 112
	struct ufsmount *ump;
E 113
I 113
	register struct inode *ip;
E 142
	struct vnode *vp;
E 113
D 139
	int error, rootino;
E 139
I 139
	int error, rootino, namlen;
I 142
	struct dirtemplate dirbuf;
E 142
E 139
E 112

D 142
	ip = target;
	if (ip->i_number == source->i_number) {
E 142
I 142
	vp = ITOV(target);
	if (target->i_number == source->i_number) {
E 142
		error = EEXIST;
		goto out;
	}
D 112
	if (ip->i_number == ROOTINO)
E 112
I 112
D 113

	ump = VFSTOUFS(ITOV(ip)->v_mount);
E 113
	rootino = ROOTINO;
D 113

E 113
	error = 0;
D 142
	if (ip->i_number == rootino)
E 142
I 142
	if (target->i_number == rootino)
E 142
E 112
		goto out;

	for (;;) {
D 117
		if ((ip->i_mode&IFMT) != IFDIR) {
E 117
I 117
D 142
		if ((ip->i_mode & IFMT) != IFDIR) {
E 142
I 142
		if (vp->v_type != VDIR) {
E 142
E 117
			error = ENOTDIR;
			break;
		}
D 95
		error = rdwri(UIO_READ, ip, (caddr_t)&dirbuf,
E 95
I 95
D 113
		error = vn_rdwr(UIO_READ, ITOV(ip), (caddr_t)&dirbuf,
E 113
I 113
D 142
		vp = ITOV(ip);
E 142
		error = vn_rdwr(UIO_READ, vp, (caddr_t)&dirbuf,
E 113
E 95
D 85
			sizeof (struct dirtemplate), (off_t)0, 1, (int *)0);
E 85
I 85
			sizeof (struct dirtemplate), (off_t)0, UIO_SYSSPACE,
D 95
			cred, (int *)0);
E 95
I 95
D 107
			IO_NODELOCKED, cred, (int *)0);
E 107
I 107
			IO_NODELOCKED, cred, (int *)0, (struct proc *)0);
E 107
E 95
E 85
		if (error != 0)
			break;
D 139
		if (dirbuf.dotdot_namlen != 2 ||
E 139
I 139
#		if (BYTE_ORDER == LITTLE_ENDIAN)
			if (vp->v_mount->mnt_maxsymlinklen > 0)
				namlen = dirbuf.dotdot_namlen;
			else
				namlen = dirbuf.dotdot_type;
#		else
			namlen = dirbuf.dotdot_namlen;
#		endif
		if (namlen != 2 ||
E 139
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
D 112
		if (dirbuf.dotdot_ino == ROOTINO)
E 112
I 112
		if (dirbuf.dotdot_ino == rootino)
E 112
			break;
D 112
		iput(ip);
D 85
		ip = iget(ip->i_dev, ip->i_fs, dirbuf.dotdot_ino);
		if (ip == NULL) {
			error = u.u_error;
E 85
I 85
		if (error = iget(ip, dirbuf.dotdot_ino, &ip))
E 112
I 112
D 142
		ufs_iput(ip);
D 113
		if (error = (ump->um_iget)(ip, dirbuf.dotdot_ino, &ip))
E 113
I 113
D 140
		if (error = VOP_VGET(vp, dirbuf.dotdot_ino, &vp))
E 140
I 140
		if (error = VFS_VGET(vp->v_mount, dirbuf.dotdot_ino, &vp))
E 142
I 142
		vput(vp);
		if (error = VFS_VGET(vp->v_mount, dirbuf.dotdot_ino, &vp)) {
			vp = NULL;
E 142
E 140
E 113
E 112
E 85
			break;
I 113
D 142
		ip = VTOI(vp);
E 142
I 142
		}
E 142
E 113
D 85
		}
E 85
	}

out:
	if (error == ENOTDIR)
		printf("checkpath: .. not a directory\n");
D 142
	if (ip != NULL)
D 112
		iput(ip);
E 112
I 112
		ufs_iput(ip);
E 142
I 142
	if (vp != NULL)
		vput(vp);
E 142
E 112
	return (error);
I 48
D 85
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
E 62
E 43
E 23
E 13
E 1
