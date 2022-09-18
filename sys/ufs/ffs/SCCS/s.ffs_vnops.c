h58267
s 00002/00001/00280
d D 8.15 95/05/14 00:26:27 mckusick 228 227
c ufs_reclaim gets proc ptr
e
s 00000/00009/00281
d D 8.14 95/03/30 14:15:59 mckusick 227 226
c doclusterread and doclusterwrite become FFS sysctl variables
e
s 00003/00000/00287
d D 8.13 95/02/22 21:08:28 mckusick 226 225
c add vop_revoke
e
s 00001/00000/00286
d D 8.12 95/01/03 00:37:04 mckusick 225 224
c missing header file
e
s 00002/00001/00284
d D 8.11 95/01/02 23:23:58 mckusick 224 223
c make sure to free correct allocation type if ffs_reclaim (from mycroft)
e
s 00003/00000/00282
d D 8.10 94/08/10 23:38:30 mckusick 223 222
c add entries for leases
e
s 00001/00000/00281
d D 8.9 94/07/28 03:38:48 pendry 222 221
c changes for whiteouts and union filesystem
e
s 00022/00003/00259
d D 8.8 94/06/16 17:21:27 mckusick 221 219
c break out reclaim operations (from mycroft)
e
s 00028/00002/00260
d R 8.8 94/06/16 17:18:06 mckusick 220 219
c break out reclaim operations (from mycroft)
e
s 00003/00000/00259
d D 8.7 94/02/03 03:00:33 mckusick 219 218
c add definitions for reallocblks
e
s 00006/00000/00253
d D 8.6 94/01/12 15:21:57 hibler 218 217
c define docluster{read,write} as 1 if DEBUG not defined.
e
s 00000/00001/00253
d D 8.5 94/01/04 22:13:48 bostic 217 216
c lint
e
s 00003/00003/00251
d D 8.4 93/12/30 16:13:20 mckusick 216 215
c new queue structure
e
s 00002/00000/00252
d D 8.3 93/09/05 10:00:09 bostic 215 214
c ftp didn't transfer the last N bytes...
e
s 00001/00189/00251
d D 8.2 93/09/05 09:36:13 mckusick 214 213
c ffs_read and ffs_write shared with lfs in <ufs/ufs/ufs_rw.c>
e
s 00002/00002/00438
d D 8.1 93/06/11 16:21:37 bostic 213 212
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00437
d D 7.102 93/05/25 15:46:32 mckusick 212 211
c add pathconf
e
s 00005/00003/00432
d D 7.101 93/04/18 23:24:07 mckusick 211 209
c enable clustered read/write by default as we now believe it works;
c add sysctl debug flags to control cluster enabling
e
s 00002/00002/00433
d R 7.101 93/04/17 10:32:52 mckusick 210 209
c enable clustered read/write by default
e
s 00002/00000/00433
d D 7.100 93/03/03 15:07:14 mckusick 209 208
c enforce append-only mode (for NFS requests)
e
s 00020/00003/00413
d D 7.99 93/01/03 17:30:44 mckusick 208 207
c make clustered read/write conditional (and off by default for now)
e
s 00006/00009/00410
d D 7.98 92/12/09 15:59:10 margo 207 206
c make calls to read and write clustering
e
s 00003/00058/00416
d D 7.97 92/11/13 16:44:14 mckusick 206 204
c ffs_inactive moves back into ufs_inactive
e
s 00000/00055/00419
d R 7.97 92/11/13 16:42:47 mckusick 205 204
c ffs_inactive moves back into ufs_inactive
e
s 00004/00004/00470
d D 7.96 92/11/02 16:54:54 mckusick 204 203
c AGE flag only set for regular files, not symlinks or directories
e
s 00001/00001/00473
d D 7.95 92/10/22 13:33:51 mckusick 203 202
c check for that NULL pointer
e
s 00003/00003/00471
d D 7.94 92/10/08 00:01:20 mckusick 202 201
c use new queue routines for buffer lists hanging off vnode
e
s 00001/00001/00473
d D 7.93 92/10/07 16:55:37 margo 201 200
c Use ufs_bmap rather than ffs_bmap.
e
s 00001/00001/00473
d D 7.92 92/07/17 00:10:56 mckusick 200 199
c maxsymlinklen must be signed comparison
e
s 00002/00001/00472
d D 7.91 92/07/14 17:20:15 mckusick 199 198
c be paranoid about big file sizes
e
s 00004/00004/00469
d D 7.90 92/07/12 17:32:16 pendry 198 197
c MIN -> min
e
s 00003/00002/00470
d D 7.89 92/07/12 15:31:28 mckusick 197 196
c new include location for fifofs and specfs
e
s 00002/00000/00470
d D 7.88 92/07/12 14:06:22 mckusick 196 195
c put back in size check to avoid problems with quad math and negative sizes
e
s 00013/00005/00457
d D 7.87 92/07/07 17:30:04 mckusick 195 194
c Chris sez time is volatile
e
s 00000/00009/00462
d D 7.86 92/07/03 01:51:09 mckusick 194 193
c delete vget vop declarations; delete USES
e
s 00068/00012/00403
d D 7.85 92/06/25 13:33:11 mckusick 193 192
c spec and fifo ops need to use ffs_fsync; add parameters to vn ops;
c new parameters to TRUNCATE; inline expand vflushbuf in ffs_fsync;
e
s 00002/00002/00413
d D 7.84 92/06/23 17:33:57 mckusick 192 191
c no such thing as EFBIG on read; panic if reading short symlink
e
s 00002/00002/00413
d D 7.83 92/06/17 20:41:51 mckusick 191 190
c need to define vfree for spec and fifo ops
e
s 00033/00033/00382
d D 7.82 92/06/15 15:14:49 heideman 190 189
c cosmetic fixes to vnodeop vector delcs
e
s 00005/00005/00410
d D 7.81 92/06/04 22:47:53 mckusick 189 188
c have to limit the file size to the maximum that the filesystem can support
e
s 00059/00055/00356
d D 7.80 92/06/04 11:18:42 mckusick 188 187
c finished registerizing vnodeop ops after vnode interface conversion
e
s 00008/00007/00403
d D 7.79 92/06/04 09:50:09 heideman 187 186
c registerized vnodeop ops after vnode interface conversion
e
s 00061/00091/00349
d D 7.78 92/05/15 13:53:21 heideman 186 185
c vnodeop argument macro expansion
e
s 00003/00003/00437
d D 7.77 92/05/15 12:21:41 heideman 185 184
c bwrite -> vn_bwrite for vn_if change
e
s 00188/00148/00252
d D 7.76 92/05/14 17:26:54 heideman 184 171
c vnode interface conversion
e
s 00188/00148/00252
d R 7.76 92/05/14 17:02:07 heideman 183 171
c vnode interface conversion
e
s 00188/00148/00252
d R 7.76 92/05/14 16:43:39 heideman 182 171
c vnode interface conversion
e
s 00188/00148/00252
d R 7.76 92/05/14 16:33:34 heideman 181 171
c vnode interface conversion
e
s 00188/00148/00252
d R 7.76 92/05/14 15:52:05 heideman 180 171
c vnode interface conversion
e
s 00188/00148/00252
d R 7.76 92/05/14 15:39:45 heideman 179 171
c vnode interface conversion
e
s 00188/00148/00252
d R 7.76 92/05/14 14:45:47 heideman 178 171
c vnode interface conversion
e
s 00188/00151/00249
d R 7.76 92/05/14 12:48:42 heideman 177 171
c vnode interface conversion
e
s 00188/00151/00249
d R 7.76 92/05/14 11:45:49 heideman 176 171
c vnode interface conversion
e
s 00188/00151/00249
d R 7.76 92/05/14 10:26:32 heideman 175 171
c vnode interface conversion
e
s 00218/00151/00249
d R 7.76 92/05/13 23:04:38 heideman 174 171
c vnode interface conversion
e
s 00218/00151/00249
d R 7.76 92/05/13 18:52:13 heideman 173 171
c vnode interface conversion
e
s 00218/00151/00249
d R 7.76 92/05/13 18:24:16 heideman 172 171
c vnode interface conversion
e
s 00002/00000/00398
d D 7.75 92/05/04 16:19:00 mckusick 171 170
c lint
e
s 00003/00003/00395
d D 7.74 92/04/21 14:44:08 mckusick 170 169
c have to pass down cred to block allocation routines
e
s 00002/00002/00396
d D 7.73 92/04/21 12:00:05 mckusick 169 168
c ensure proper types for local variables and parameters
e
s 00002/00002/00396
d D 7.72 92/04/13 18:33:22 mckusick 168 167
c lint
e
s 00004/00002/00394
d D 7.71 92/03/26 18:10:12 mckusick 167 166
c ensure proper types for local variables
e
s 00002/00002/00394
d D 7.70 92/03/22 20:37:03 ralph 166 165
c remove ITOV and use vnode pointer instead.
e
s 00000/00002/00396
d D 7.69 92/02/03 22:23:00 heideman 165 164
c maknode goes away
e
s 00006/00005/00392
d D 7.68 92/01/14 12:31:03 mckusick 164 163
c breada generalizes to breadn
e
s 00001/00001/00396
d D 7.67 91/12/19 12:57:31 mckusick 163 162
c must cast long argument to vnode_pager_setsize
e
s 00151/00005/00246
d D 7.66 91/11/05 14:33:43 mckusick 162 161
c reorganization to move ufsmount ops to be vnode ops; 
c must add fifo and spec ops vectors; must add inactive routine
e
s 00072/01658/00179
d D 7.65 91/11/01 17:08:55 bostic 161 159
c UFS/FFS split for LFS version 1; move everything but ffs_read,
c ffs_write and ffs_fsync into ufs_vnops.c
e
s 00002/00000/01837
d D 7.64.1.1 91/05/19 14:34:16 mckusick 160 159
c name resolution checking (need kern/kern_malloc.c 7.25.1.1,
c kern/vfs_lookup.c 7.31.1.1, kern/vfs_syscalls.c 7.70.1.1,
c nfs/nfs_serv.c 7.40.1.1, nfs/nfs_syscalls.c 7.26.1.1,
c ufs/ufs_vnops.c 7.64.1.1, and hp300/hp300/trap.c 7.14.1.1)
e
s 00001/00001/01836
d D 7.64 91/05/16 19:09:52 mckusick 159 158
c change vn_ to vop_ (for marc :-)
e
s 00076/00033/01761
d D 7.63 91/05/15 20:15:17 mckusick 158 157
c update rename to use new namei / lookup scheme
e
s 00001/00001/01793
d D 7.62 91/05/11 18:11:42 mckusick 157 156
c for kernel I/O, may not have a proc from which to check rlimits
e
s 00001/00001/01793
d D 7.61 91/05/08 19:42:33 mckusick 156 155
c correct bogus comment
e
s 00180/00213/01614
d D 7.60 91/04/16 00:19:33 mckusick 155 154
c use prototypes for ufs vnode ops (from specdev.h, fifo.h, and inode.h);
c add appropriate proc pointers (eliminating lots of curproc's)
e
s 00002/00010/01825
d D 7.59 91/03/25 17:05:37 mckusick 154 153
c get rid of unneeded namei
e
s 00029/00024/01806
d D 7.58 91/03/19 10:30:44 karels 153 152
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; remove ../ufs/ from includes; consolidate *nullops();
c chown/fchmod use proc's credentials, not file's
e
s 00001/00000/01829
d D 7.57 91/03/11 22:11:30 mckusick 152 151
c missing iput
e
s 00018/00014/01811
d D 7.56 91/03/11 18:23:34 mckusick 151 150
c reset directory link counts on I/O failure
e
s 00011/00173/01814
d D 7.55 91/02/25 22:18:20 mckusick 150 149
c move locking specific code into ufs_lockf.c; fix numerous bugs
e
s 00006/00003/01981
d D 7.54 91/02/21 22:59:55 mckusick 149 148
c fixes for multiple calls to namei (for rename in NFS)
e
s 00013/00008/01971
d D 7.53 91/02/21 19:32:56 mckusick 148 147
c fixes for range locking
e
s 00012/00006/01967
d D 7.52 91/02/03 22:32:50 mckusick 147 146
c fix check for LINK_MAX in ufs_link; 
c add check for LINK_MAX in ufs_mkdir and ufs_rename
e
s 00007/00004/01966
d D 7.51 91/02/03 21:46:05 mckusick 146 145
c if entry is gone, do not try to release the parent
e
s 00253/00001/01717
d D 7.50 91/02/01 16:38:49 mckusick 145 144
c add POSIX-style byte-level record locking
e
s 00002/00002/01716
d D 7.49 91/02/01 16:38:07 mckusick 144 143
c keep me happy about precedence
e
s 00005/00005/01713
d D 7.48 90/12/14 12:40:40 bostic 143 142
c fail if try to set VTX on file not of type directory, or GID and not
c member of the group
e
s 00007/00007/01711
d D 7.47 90/12/05 16:10:01 mckusick 142 141
c update for new VM
e
s 00010/00000/01708
d D 7.46 90/10/19 15:26:43 mckusick 141 140
c properly decrement reference count on directory
e
s 00001/00011/01707
d D 7.45 90/06/28 22:31:21 bostic 140 139
c new copyright notice
e
s 00004/00002/01714
d D 7.44 90/06/19 17:11:01 mckusick 139 138
c mark inode dirty to force size update
e
s 00002/00000/01714
d D 7.43 90/05/30 19:19:48 mckusick 138 137
c have to write out inode if IO_SYNC is specified
e
s 00011/00016/01703
d D 7.42 90/05/30 11:39:16 mckusick 137 136
c VOP_ABORTOP is no longer responsible for unlocking and vreleing vnodes
e
s 00005/00003/01714
d D 7.41 90/05/29 18:31:10 mckusick 136 135
c have to restore quota state after chown
e
s 00004/00003/01713
d D 7.40 90/05/14 16:28:02 mckusick 135 134
c have to set the ICHG bit when a chown succeeds
e
s 00011/00006/01705
d D 7.39 90/05/10 15:44:01 mckusick 134 133
c lint; checkoverlap code is conditional on DIAGNOSTIC
e
s 00004/00001/01707
d D 7.38 90/05/08 16:30:23 mckusick 133 132
c must have vnode locked before doing ufs_access
e
s 00001/00001/01707
d D 7.37 90/05/04 20:50:21 mckusick 132 131
c use NULLVP
e
s 00160/00054/01548
d D 7.36 90/05/02 19:38:12 mckusick 131 130
c iaccess moves into ufs_access; changes for the new quota implementation
e
s 00001/00001/01601
d D 7.35 90/03/27 19:13:06 mckusick 130 129
c break specinfo structure out of vnode.h into specdev.h
e
s 00002/00003/01600
d D 7.34 90/03/27 15:36:37 mckusick 129 128
c va_size and va_bytes become quads
e
s 00006/00001/01597
d D 7.33 90/03/06 23:28:13 mckusick 128 127
c readdir now returns an eof indication
e
s 00007/00003/01591
d D 7.32 90/03/05 19:15:12 mckusick 127 126
c print out selected fifo information in ufs_print
e
s 00113/00010/01481
d D 7.31 90/03/05 18:17:59 mckusick 126 125
c add support for FIFO's
e
s 00007/00010/01484
d D 7.30 90/02/16 11:28:16 mckusick 125 124
c may be crossing a mount point, so must be generic
e
s 00022/00001/01472
d D 7.29 90/01/15 18:39:03 mckusick 124 123
c add islocked vnode op
e
s 00006/00000/01467
d D 7.28 90/01/14 10:46:19 mckusick 123 122
c debugging, print out information on processes holding and waiting for lock
e
s 00013/00010/01457
d D 7.27 90/01/13 19:52:51 mckusick 122 121
c check decision on doing read-ahead; add missing biodone;
c change diskoverlap panic to a console message
e
s 00004/00004/01460
d D 7.26 89/12/30 22:41:28 mckusick 121 120
c v_count => v_usecount
e
s 00110/00057/01354
d D 7.25 89/11/30 22:59:35 mckusick 120 119
c itrunc has to handle logical.physical buffer cache;
c ufs_strategy has to handle the bmap functions;
c add ufs_print routine
e
s 00057/00006/01354
d D 7.24 89/11/25 21:59:36 mckusick 119 118
c wrappers for read/write/close of special devices to set times as appropriate
e
s 00001/00001/01359
d D 7.23 89/11/24 19:50:08 mckusick 118 117
c use dirbad rather than printf
e
s 00160/00003/01200
d D 7.22 89/11/24 19:37:43 mckusick 117 116
c move in ufs_read and ufs_write from ufs_io.c; 
c no longer set v_rdev in mknod; get rid of spurious printf's
e
s 00050/00058/01153
d D 7.21 89/11/22 22:39:23 mckusick 116 115
c fsync takes a waitfor flag; replace rdwri with vn_rdwr;
c readdir no longer has an offp; locking is handled at the vnode level
e
s 00049/00005/01162
d D 7.20 89/10/29 23:31:50 mckusick 115 114
c create spec_inodeops; convert mknod to use vgone
e
s 00004/00002/01163
d D 7.19 89/10/24 19:44:27 mckusick 114 113
c add ufs_reclaim entry; i_size => i_qsize for dinode.h
e
s 00004/00001/01161
d D 7.18 89/10/16 09:18:01 mckusick 113 112
c delete change in 7.16, only clear setuid and setgid bits if euid != 0;
c only clear setuid if owner changes and only clear setgid when group changes
e
s 00002/00001/01160
d D 7.17 89/08/28 09:46:21 mckusick 112 111
c must nullify the type to keep getnewbuf from looking for VBLK
c vnodes when reallocating it
e
s 00001/00002/01160
d D 7.16 89/08/26 00:12:18 mckusick 111 110
c always clear setuid and setgid bits when changing owner or group
e
s 00001/00005/01161
d D 7.15 89/08/16 18:44:17 mckusick 110 109
c return vap_bytes in bytes
e
s 00003/00000/01163
d D 7.14 89/08/10 15:27:43 mckusick 109 108
c zero out usec fields (from Rick Macklem)
e
s 00001/00003/01162
d D 7.13 89/07/03 22:05:07 mckusick 108 107
c delete unnecessary check; minor cleanup
e
s 00015/00001/01150
d D 7.12 89/06/07 16:50:20 mckusick 107 106
c return flags and generation number; set flags
e
s 00003/00002/01148
d D 7.11 89/05/27 16:47:10 mckusick 106 105
c return directory locked (for benefit of NFS)
e
s 00003/00001/01147
d D 7.10 89/05/19 15:33:46 mckusick 105 104
c cleanups and paranoia
e
s 00007/00006/01141
d D 7.9 89/05/09 23:42:24 mckusick 104 103
c get the suser check in the correct places
e
s 00002/00002/01145
d D 7.8 89/05/09 20:43:17 mckusick 103 102
c read into system space, not user space!
e
s 00659/00902/00488
d D 7.7 89/05/09 17:22:38 mckusick 102 101
c merge in vnodes
e
s 00014/00008/01376
d D 7.6 89/04/26 19:21:32 mckusick 101 100
c use new form of suser()
e
s 00005/00000/01379
d D 7.5 89/02/16 14:23:38 bostic 100 99
c don't allow more than LINK_MAX links
e
s 00013/00004/01366
d D 7.4 89/01/24 21:53:52 bostic 99 98
c fix chown; don't steal groups or give away files
e
s 00001/00001/01369
d D 7.3 87/04/18 16:27:02 karels 98 97
c don't clear set-gid when su creates file when not groupmember
e
s 00002/00000/01368
d D 7.2 87/03/10 14:20:57 mckusick 97 96
c only set ICHG when fsync'ing a file descriptor that is open for writing
e
s 00001/00001/01367
d D 7.1 86/06/05 00:14:45 mckusick 96 95
c 4.3BSD release version
e
s 00009/00007/01359
d D 6.23 86/03/04 19:53:22 karels 95 94
c relax restrictions on *chown: allow owner to change group if member
e
s 00005/00003/01361
d D 6.22 86/02/23 23:11:56 karels 94 93
c lint
e
s 00013/00020/01351
d D 6.21 85/09/05 15:09:19 mckusick 93 91
c allocate file table entry before creating file in case file table is full
e
s 00010/00017/01354
d R 6.21 85/09/04 20:48:08 mckusick 92 91
c allocate file table entry before creating file in case file table is full
e
s 00011/00000/01360
d D 6.20 85/08/26 17:15:14 bloom 91 90
c fix whole in sticky directories
e
s 00007/00001/01353
d D 6.19 85/06/08 14:54:42 mckusick 90 89
c Add copyright
e
s 00015/00004/01339
d D 6.18 85/05/22 20:03:04 mckusick 89 88
c return EINVAL instead of ENXIO for readlink of a non symbolic link;
c check for read-only file system in [f]chmod, [f]chown, and utimes;
c do not clear the sticky bit when modifying directories
e
s 00004/00001/01339
d D 6.17 85/03/19 17:09:55 mckusick 88 87
c do not follow symbolic links on exclusive open (from kre)
e
s 00004/00000/01336
d D 6.16 85/02/22 15:12:05 mckusick 87 86
c insure that directories are always a multiple of DIRBLKSIZ in size
e
s 00006/00003/01330
d D 6.15 85/01/21 13:36:06 mckusick 86 85
c cannot use ni_pdir when `namei' fails
e
s 00016/00016/01317
d D 6.14 84/08/29 20:27:03 bloom 85 84
c Change to includes.  no more ../h
e
s 00066/00080/01267
d D 6.13 84/07/27 11:29:31 mckusick 84 83
c rewrite `rename' and `rmdir' to properly invalidate the cache
e
s 00002/00001/01345
d D 6.12 84/07/20 01:13:26 mckusick 83 82
c use new `cacheinval' macro
e
s 00143/00094/01203
d D 6.11 84/07/08 16:16:25 mckusick 82 81
c rework `namei' interface to eliminate global variables
e
s 00012/00012/01285
d D 6.10 84/07/04 13:21:06 mckusick 81 80
c save time, use ILOCK and IUNLOCK to avoid call overhead
e
s 00008/00004/01289
d D 6.9 84/07/02 15:15:42 mckusick 80 79
c Follow same protocol as `unlink' to prevent potential race condition.
e
s 00002/00006/01291
d D 6.8 84/06/30 16:41:02 sam 79 78
c rename: if source has gone away when time to unlink, don't touch 
c link count (consider race with unlink)
e
s 00001/00000/01296
d D 6.7 84/06/27 20:40:59 sam 78 77
c convert namei cache to hold soft references to inodes so that 
c . and .. may be placed in the cache
e
s 00010/00007/01286
d D 6.6 84/05/24 17:57:52 sam 77 76
c correct error code for lseek on pipes/sockets; in-line expand 
c getf in getinode
e
s 00001/00001/01292
d D 6.5 84/02/10 14:54:57 karels 76 74
c open(...,FTRUNC...) requires write permission
e
s 00002/00002/01291
d R 6.5 84/02/10 14:48:11 karels 75 74
c open(..,FTRUNC..) requires write permission
e
s 00003/00003/01290
d D 6.4 84/01/03 23:40:44 mckusick 74 73
c add system wide cacheing of path names in namei() (from kre)
e
s 00000/00002/01293
d D 6.3 83/09/30 11:10:26 sam 73 72
c code for interrupted open calls tested (it works)
e
s 00001/00000/01294
d D 6.2 83/09/25 16:12:15 mckusick 72 71
c kludge to allow `badsect' to set block numbers
e
s 00000/00000/01294
d D 6.1 83/08/06 10:46:24 sam 71 70
c 4.2 distribution
e
s 00001/00001/01293
d D 4.62 83/08/06 10:43:25 sam 70 68
c typo
e
s 00000/00000/01294
d R 6.1 83/07/29 06:44:41 sam 69 68
c 4.2 distribution
e
s 00019/00006/01275
d D 4.61 83/07/09 14:15:09 sam 68 66
c parameter checking in lseek
e
s 00019/00006/01275
d R 4.61 83/07/09 01:42:35 sam 67 66
c correct lseek to check whence; make code more clear?
e
s 00001/00038/01280
d D 4.60 83/06/12 14:28:56 sam 66 65
c cleanup fstat
e
s 00000/00028/01318
d D 4.59 83/05/31 01:03:56 sam 65 64
c collect all the compatibility stuff in single files
e
s 00025/00010/01321
d D 4.58 83/05/28 19:10:06 mckusick 64 63
c must do a complete path check when moving directories to new parent
e
s 00342/00211/00989
d D 4.57 83/05/27 12:49:36 sam 63 62
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00012/00035/01188
d D 4.56 83/05/21 15:46:38 sam 62 61
c purge mush; stuff for i_blocks
e
s 00002/00004/01221
d D 4.55 83/04/01 17:32:19 sam 61 60
c blew it, can't allow anyone but super-user to chown
e
s 00044/00024/01181
d D 4.54 83/03/31 13:49:40 sam 60 59
c add utimes call; protection fixes galore
e
s 00001/00001/01204
d D 4.53 83/03/22 11:36:12 sam 59 58
c oops
e
s 00019/00010/01186
d D 4.52 83/03/21 21:36:43 sam 58 57
c check delete permission on source before doing any work
e
s 00002/00000/01194
d D 4.51 83/02/20 14:54:02 sam 57 55
c fix incompatibility between access and setgid
e
s 00001/00001/01193
d R 4.51 83/02/10 18:42:13 sam 56 55
c groups set members are shorts, not ints; hz no longer in systm.h
e
s 00006/00008/01188
d D 4.50 83/02/10 13:44:32 sam 55 54
c have direnter return errors so new inodes can be thrown away
e
s 00012/00000/01184
d D 4.49 83/01/22 16:50:58 sam 54 53
c patch two holes in rename
e
s 00003/00002/01181
d D 4.48 83/01/11 14:46:19 sam 53 52
c irele should be iput in rename
e
s 00042/00023/01141
d D 4.47 83/01/01 17:14:38 sam 52 51
c avoid linked to directories as targets; iput and irele on 
c directory inodes can clear u.u_error, so kludge things for the moment 
c to insure important errors get back to the user
e
s 00003/00005/01161
d D 4.46 82/12/28 23:48:30 sam 51 50
c copyin & copyout now return EFAULT and all callers uniformly 
c return (or ignore) this value
e
s 00004/00000/01162
d D 4.45 82/12/24 18:14:00 sam 50 49
c zero trash in stat structure
e
s 00001/00001/01161
d D 4.44 82/12/19 13:04:05 sam 49 48
c use ENOTEMPTY errno
e
s 00004/00004/01158
d D 4.43 82/12/09 19:02:07 sam 48 47
c u.u_pofile flags are now UF_*
e
s 00349/00072/00813
d D 4.42 82/11/13 22:53:38 sam 47 46
c merge of 4.1b and 4.1c
e
s 00004/00004/00881
d D 4.41 82/10/19 10:32:46 root 46 45
c more lint
e
s 00008/00004/00877
d D 4.40 82/10/17 21:51:50 root 45 44
c more lint
e
s 00001/00001/00880
d D 4.39 82/10/17 11:30:27 root 44 43
c openi returns value
e
s 00000/00004/00881
d D 4.38 82/10/10 16:02:54 root 43 42
c move vax header files to their own directory
e
s 00001/00001/00884
d D 4.37 82/09/06 22:57:52 root 42 41
c 
e
s 00005/00004/00880
d D 4.36 82/09/04 09:21:40 root 41 40
c time is now a structure
e
s 00008/00004/00876
d D 4.35 82/08/24 15:06:33 root 40 39
c new groups stuff
e
s 00011/00015/00869
d D 4.34 82/08/22 21:11:10 root 39 38
c use rdwri()
e
s 00001/00005/00883
d D 4.33 82/08/14 23:56:59 root 38 37
c use readip1()
e
s 00268/00199/00620
d D 4.32 82/08/10 17:51:57 sam 37 36
c new fs system calls prior to truncate and rename
e
s 00057/00040/00762
d D 4.31 82/07/25 23:18:00 root 36 35
c first functional version with new ufs_nami.c
e
s 00009/00003/00793
d D 4.30 82/07/24 18:12:27 root 35 34
c merge with calder
e
s 00051/00000/00745
d D 4.29 82/07/22 12:13:29 kre 34 33
c disc quotas & MUSH
e
s 00151/00006/00594
d D 4.28 82/07/15 20:49:04 root 33 32
c efs crud
e
s 00000/00003/00600
d D 4.27 82/06/25 21:29:05 wnj 32 31
c drop #ifdef SIMFS for /etc/config's sake
e
s 00014/00010/00589
d D 4.26 82/06/10 12:41:08 mckusick 31 30
c change iput() to irele() when releasing unlocked inodes
e
s 00003/00003/00596
d D 4.25 82/06/07 23:54:07 mckusick 30 29
c irele() becomes iunlock(); new irele() does iput() for already unlocked inodes
e
s 00002/00003/00597
d D 4.24 82/06/04 00:15:27 mckusick 29 28
c provide blksize in stat system call
e
s 00044/00031/00556
d D 4.23 82/04/19 19:37:01 mckusic 28 27
c merge into new file system
e
s 00004/00004/00583
d D 4.22 82/04/01 11:48:05 root 27 26
c lstat <-> stat
e
s 00416/00207/00171
d D 4.21 82/03/18 19:26:30 root 26 25
c rearrange for kirk
e
s 00002/00000/00376
d D 4.20 82/03/16 17:38:47 root 25 24
c fix to symlink
e
s 00001/00001/00375
d D 4.19 82/03/12 16:29:48 sam 24 23
c lint
e
s 00097/00006/00279
d D 4.18 82/02/27 14:55:11 wnj 23 22
c symbolic links
e
s 00003/00001/00282
d D 4.17 82/01/19 06:39:56 wnj 22 21
c closef parameter indicating whether error return
c to complete non-blc
e
s 00001/00001/00282
d D 4.16 82/01/16 20:59:37 wnj 21 20
c clean crashes! 
e
s 00000/00000/00283
d D 4.15 81/11/18 15:45:57 wnj 20 19
c more cleanup
e
s 00002/00000/00281
d D 4.14 81/11/16 14:21:49 wnj 19 18
c lint
e
s 00001/00001/00280
d D 4.13 81/11/14 16:44:12 wnj 18 17
c before header overlay
e
s 00036/00046/00245
d D 4.12 81/11/08 17:06:36 wnj 17 16
c major cleanups for socket code
e
s 00006/00000/00285
d D 4.11 81/08/12 14:48:15 ecc 16 15
c new bbnnet
e
s 00008/00005/00277
d D 4.10 81/04/28 02:59:24 root 15 14
c fstat for ports now in pipe.c
e
s 00001/00001/00281
d D 4.9 81/03/09 01:49:47 wnj 14 13
c lint and a few minor fixed
e
s 00007/00002/00275
d D 4.8 81/03/03 11:08:14 wnj 13 12
c mount puts names in s_fsmnt
e
s 00001/00001/00276
d D 4.7 81/02/26 23:29:24 wnj 12 11
c rid of NINODE
e
s 00001/00001/00276
d D 4.6 81/02/16 20:51:35 wnj 11 10
c fix placement of mpurge bug
e
s 00001/00000/00276
d D 4.5 81/02/15 12:21:52 kre 10 9
c bug fix in umount
e
s 00011/00010/00265
d D 4.4 81/01/31 23:27:36 wnj 9 8
c changes for cached super-blocks
e
s 00011/00003/00264
d D 4.3 81/01/28 12:04:22 kre 8 7
c cache purging
e
s 00000/00002/00267
d D 4.2 81/01/20 19:46:34 toy 7 6
c Removed #ifdef UCB.   (MCT)
e
s 00000/00000/00269
d D 4.1 80/11/09 17:32:52 bill 6 5
c minor fixups to restart stuff; version 4.1 for distrib
e
s 00001/00001/00268
d D 3.5 80/10/03 10:45:34 bill 5 4
c file system update orderings
e
s 00001/00000/00268
d D 3.4 80/07/06 11:20:49 bill 4 3
c first cached version
e
s 00001/00001/00267
d D 3.3 80/06/07 02:48:00 bill 3 2
c %H%->%G%
e
s 00002/00001/00266
d D 3.2 80/04/14 09:58:04 bill 2 1
c IUPDAT fast inline from inline.h in stat()
e
s 00267/00000/00000
d D 3.1 80/04/09 16:04:33 bill 1 0
c date and time created 80/04/09 16:04:33 by bill
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
D 14
/*	%M%	%I%	%G%	*/
E 14
I 14
D 90
/*	%M%	%I%	%E%	*/
E 90
I 90
/*
D 96
 * Copyright (c) 1982 Regents of the University of California.
E 96
I 96
D 102
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 96
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 102
I 102
D 213
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 213
I 213
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 213
E 102
 *
I 102
D 140
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
E 140
I 140
 * %sccs.include.redist.c%
E 140
 *
E 102
 *	%W% (Berkeley) %G%
 */
E 90
E 14
E 3

I 28
D 29
/* merged into kernel:	@(#)sys3.c 2.2 4/8/82 */

E 29
D 32
#ifdef SIMFS
#include "../h/sysrenam.h"
#endif
E 32
E 28
D 85
#include "../h/param.h"
#include "../h/systm.h"
D 26
#include "../h/mount.h"
#include "../h/ino.h"
#include "../h/reg.h"
#include "../h/buf.h"
#include "../h/filsys.h"
E 26
#include "../h/dir.h"
#include "../h/user.h"
I 41
#include "../h/kernel.h"
E 41
D 26
#include "../h/inode.h"
E 26
I 26
D 28
#include "../h/reg.h"
E 28
E 26
#include "../h/file.h"
I 28
#include "../h/stat.h"
E 28
D 26
#include "../h/conf.h"
#include "../h/stat.h"
E 26
I 26
#include "../h/inode.h"
D 28
#include "../h/ino.h"
#include "../h/pte.h"
#include "../h/vm.h"
E 28
I 28
#include "../h/fs.h"
E 28
#include "../h/buf.h"
D 28
#include "../h/mtpr.h"
E 28
#include "../h/proc.h"
E 26
I 2
D 43
#include "../h/inline.h"
I 33
D 37
#ifdef EFS
#include "../net/in.h"
#include "../h/efs.h"
#endif
E 37
I 37
/* no reason to inline expand these guys here */
#undef ilock
#undef iunlock
E 43
E 37
I 34
#include "../h/quota.h"
I 35
D 63
#include "../h/descrip.h"
E 63
I 39
#include "../h/uio.h"
#include "../h/socket.h"
I 45
#include "../h/socketvar.h"
I 47
D 82
#include "../h/nami.h"
E 82
I 63
#include "../h/mount.h"
E 85
I 85
D 161
#include "param.h"
#include "systm.h"
D 102
#include "dir.h"
E 102
D 153
#include "user.h"
E 153
I 153
#include "namei.h"
#include "resourcevar.h"
E 153
#include "kernel.h"
#include "file.h"
#include "stat.h"
D 102
#include "inode.h"
#include "fs.h"
E 102
#include "buf.h"
#include "proc.h"
D 102
#include "quota.h"
E 102
D 130
#include "uio.h"
E 130
D 153
#include "socket.h"
#include "socketvar.h"
E 153
I 102
#include "conf.h"
E 102
#include "mount.h"
I 102
#include "vnode.h"
I 130
#include "specdev.h"
I 145
D 155
#include "fcntl.h"
E 155
I 155
#include "fifo.h"
E 155
#include "malloc.h"
E 161
I 161
#include <sys/param.h>
#include <sys/systm.h>
D 165
#include <sys/namei.h>
E 165
#include <sys/resourcevar.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/conf.h>
#include <sys/mount.h>
#include <sys/vnode.h>
D 197
#include <sys/specdev.h>
#include <sys/fifo.h>
E 197
#include <sys/malloc.h>
E 161
D 153
#include "../ufs/lockf.h"
E 145
I 131
#include "../ufs/quota.h"
E 131
E 130
#include "../ufs/inode.h"
#include "../ufs/fs.h"
E 153
D 131
#include "../ufs/quota.h"
E 131
E 102
E 85
E 63
E 47
E 45
E 39
E 35
E 34
E 33
I 26
D 28
#include "../h/conf.h"
E 26
I 19
#include "../h/socket.h"
#include "../h/socketvar.h"
I 26
#include "../h/stat.h"
E 28
E 26
E 19
E 2

I 171
#include <vm/vm.h>
I 197

#include <miscfs/specfs/specdev.h>
#include <miscfs/fifofs/fifo.h>
E 197

E 171
I 153
D 161
#include "lockf.h"
#include "quota.h"
#include "inode.h"
I 158
#include "dir.h"
E 158
#include "fs.h"
E 161
I 161
#include <ufs/ufs/lockf.h>
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/dir.h>
I 225
#include <ufs/ufs/ufsmount.h>
E 225
#include <ufs/ufs/ufs_extern.h>
E 161

E 153
I 63
D 102
extern	struct fileops inodeops;
struct	file *getinode();

E 102
E 63
I 47
D 161
/*
D 102
 * Change current working directory (``.'').
E 102
I 102
D 155
 * Global vfs data structures for ufs
E 102
 */
E 47
I 26
D 102
chdir()
{
E 102

D 102
	chdirec(&u.u_cdir);
}
E 102
I 102
int	ufs_lookup(),
	ufs_create(),
	ufs_mknod(),
	ufs_open(),
	ufs_close(),
	ufs_access(),
	ufs_getattr(),
	ufs_setattr(),
	ufs_read(),
	ufs_write(),
	ufs_ioctl(),
	ufs_select(),
	ufs_mmap(),
	ufs_fsync(),
	ufs_seek(),
	ufs_remove(),
	ufs_link(),
	ufs_rename(),
	ufs_mkdir(),
	ufs_rmdir(),
	ufs_symlink(),
	ufs_readdir(),
	ufs_readlink(),
	ufs_abortop(),
	ufs_inactive(),
I 114
	ufs_reclaim(),
E 114
	ufs_lock(),
	ufs_unlock(),
	ufs_bmap(),
D 120
	ufs_strategy();
E 120
I 120
	ufs_strategy(),
D 124
	ufs_print();
E 124
I 124
	ufs_print(),
D 145
	ufs_islocked();
E 145
I 145
	ufs_islocked(),
	ufs_advlock();
E 145
E 124
E 120
E 102

I 47
D 102
/*
 * Change notion of root (``/'') directory.
 */
E 47
chroot()
{
E 102
I 102
struct vnodeops ufs_vnodeops = {
D 120
	ufs_lookup,
	ufs_create,
	ufs_mknod,
	ufs_open,
	ufs_close,
	ufs_access,
	ufs_getattr,
	ufs_setattr,
	ufs_read,
	ufs_write,
	ufs_ioctl,
	ufs_select,
	ufs_mmap,
	ufs_fsync,
	ufs_seek,
	ufs_remove,
	ufs_link,
	ufs_rename,
	ufs_mkdir,
	ufs_rmdir,
	ufs_symlink,
	ufs_readdir,
	ufs_readlink,
	ufs_abortop,
	ufs_inactive,
I 114
	ufs_reclaim,
E 114
	ufs_lock,
	ufs_unlock,
	ufs_bmap,
	ufs_strategy,
E 120
I 120
	ufs_lookup,		/* lookup */
	ufs_create,		/* create */
	ufs_mknod,		/* mknod */
	ufs_open,		/* open */
	ufs_close,		/* close */
	ufs_access,		/* access */
	ufs_getattr,		/* getattr */
	ufs_setattr,		/* setattr */
	ufs_read,		/* read */
	ufs_write,		/* write */
	ufs_ioctl,		/* ioctl */
	ufs_select,		/* select */
	ufs_mmap,		/* mmap */
	ufs_fsync,		/* fsync */
	ufs_seek,		/* seek */
	ufs_remove,		/* remove */
	ufs_link,		/* link */
	ufs_rename,		/* rename */
	ufs_mkdir,		/* mkdir */
	ufs_rmdir,		/* rmdir */
	ufs_symlink,		/* symlink */
	ufs_readdir,		/* readdir */
	ufs_readlink,		/* readlink */
	ufs_abortop,		/* abortop */
	ufs_inactive,		/* inactive */
	ufs_reclaim,		/* reclaim */
	ufs_lock,		/* lock */
	ufs_unlock,		/* unlock */
	ufs_bmap,		/* bmap */
	ufs_strategy,		/* strategy */
	ufs_print,		/* print */
I 124
	ufs_islocked,		/* islocked */
I 145
	ufs_advlock,		/* advlock */
E 145
E 124
E 120
};
E 102

I 115
int	spec_lookup(),
	spec_open(),
D 119
	spec_read(),
	spec_write(),
E 119
I 119
	ufsspec_read(),
	ufsspec_write(),
E 119
	spec_strategy(),
I 120
	spec_bmap(),
E 120
	spec_ioctl(),
	spec_select(),
D 119
	spec_close(),
E 119
I 119
	ufsspec_close(),
I 145
	spec_advlock(),
E 145
E 119
D 153
	spec_badop(),
D 150
	spec_nullop();
E 150
I 150
	nullop();
E 153
I 153
	spec_badop();
E 153
E 150

struct vnodeops spec_inodeops = {
D 116
	spec_lookup,
	spec_badop,
	spec_badop,
	spec_open,
	spec_close,
	ufs_access,
	ufs_getattr,
	ufs_setattr,
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
	ufs_inactive,
	ufs_reclaim,
	ufs_lock,
	ufs_unlock,
	spec_badop,
	spec_strategy,
E 116
I 116
	spec_lookup,		/* lookup */
	spec_badop,		/* create */
	spec_badop,		/* mknod */
	spec_open,		/* open */
D 119
	spec_close,		/* close */
E 119
I 119
	ufsspec_close,		/* close */
E 119
	ufs_access,		/* access */
	ufs_getattr,		/* getattr */
	ufs_setattr,		/* setattr */
D 119
	spec_read,		/* read */
	spec_write,		/* write */
E 119
I 119
	ufsspec_read,		/* read */
	ufsspec_write,		/* write */
E 119
	spec_ioctl,		/* ioctl */
	spec_select,		/* select */
	spec_badop,		/* mmap */
D 150
	spec_nullop,		/* fsync */
E 150
I 150
	nullop,			/* fsync */
E 150
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
	ufs_inactive,		/* inactive */
	ufs_reclaim,		/* reclaim */
	ufs_lock,		/* lock */
	ufs_unlock,		/* unlock */
D 120
	spec_badop,		/* bmap */
E 120
I 120
	spec_bmap,		/* bmap */
E 120
	spec_strategy,		/* strategy */
I 120
	ufs_print,		/* print */
I 124
	ufs_islocked,		/* islocked */
I 145
	spec_advlock,		/* advlock */
E 145
E 124
E 120
E 116
};

E 115
D 101
	if (suser())
		chdirec(&u.u_rdir);
E 101
I 101
D 102
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
	chdirec(&u.u_rdir);
E 101
}
E 102
I 102
D 126
enum vtype iftovt_tab[8] = {
	VNON, VCHR, VDIR, VBLK, VREG, VLNK, VSOCK, VBAD,
E 126
I 126
#ifdef FIFO
int	fifo_lookup(),
	fifo_open(),
	ufsfifo_read(),
	ufsfifo_write(),
	fifo_bmap(),
	fifo_ioctl(),
	fifo_select(),
	ufsfifo_close(),
	fifo_print(),
I 145
	fifo_advlock(),
E 145
D 150
	fifo_badop(),
	fifo_nullop();
E 150
I 150
	fifo_badop();
E 150

struct vnodeops fifo_inodeops = {
	fifo_lookup,		/* lookup */
	fifo_badop,		/* create */
	fifo_badop,		/* mknod */
	fifo_open,		/* open */
	ufsfifo_close,		/* close */
	ufs_access,		/* access */
	ufs_getattr,		/* getattr */
	ufs_setattr,		/* setattr */
	ufsfifo_read,		/* read */
	ufsfifo_write,		/* write */
	fifo_ioctl,		/* ioctl */
	fifo_select,		/* select */
	fifo_badop,		/* mmap */
D 150
	fifo_nullop,		/* fsync */
E 150
I 150
	nullop,			/* fsync */
E 150
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
	ufs_inactive,		/* inactive */
	ufs_reclaim,		/* reclaim */
	ufs_lock,		/* lock */
	ufs_unlock,		/* unlock */
	fifo_bmap,		/* bmap */
	fifo_badop,		/* strategy */
	ufs_print,		/* print */
	ufs_islocked,		/* islocked */
I 145
	fifo_advlock,		/* advlock */
E 145
E 126
};
D 126
int	vttoif_tab[8] = {
	0, IFREG, IFDIR, IFBLK, IFCHR, IFLNK, IFSOCK, IFMT,
E 126
I 126
#endif /* FIFO */

enum vtype iftovt_tab[16] = {
	VNON, VFIFO, VCHR, VNON, VDIR, VNON, VBLK, VNON,
	VREG, VNON, VLNK, VNON, VSOCK, VNON, VNON, VBAD,
E 126
};
I 126
int	vttoif_tab[9] = {
	0, IFREG, IFDIR, IFBLK, IFCHR, IFLNK, IFSOCK, IFIFO, IFMT,
};
E 126
E 102

I 47
/*
E 155
D 102
 * Common routine for chroot and chdir.
E 102
I 102
 * Create a regular file
E 102
 */
E 47
D 102
chdirec(ipp)
D 37
register struct inode **ipp;
E 37
I 37
	register struct inode **ipp;
E 102
I 102
D 155
ufs_create(ndp, vap)
E 155
I 155
ufs_create(ndp, vap, p)
E 155
	struct nameidata *ndp;
	struct vattr *vap;
I 155
	struct proc *p;
E 155
E 102
E 37
{
D 102
	register struct inode *ip;
	struct a {
		char	*fname;
D 82
	};
E 82
I 82
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
E 102
I 102
	struct inode *ip;
	int error;
E 161
I 161
#include <ufs/ffs/fs.h>
#include <ufs/ffs/ffs_extern.h>
E 161
E 102
E 82

D 47
	ip = namei(uchar, 0, 1);
	if(ip == NULL)
E 47
I 47
D 82
	ip = namei(uchar, LOOKUP, 1);
E 82
I 82
D 102
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
	ip = namei(ndp);
E 82
	if (ip == NULL)
E 47
		return;
D 47
	if((ip->i_mode&IFMT) != IFDIR) {
E 47
I 47
	if ((ip->i_mode&IFMT) != IFDIR) {
E 47
		u.u_error = ENOTDIR;
		goto bad;
	}
D 47
	if(access(ip, IEXEC))
E 47
I 47
	if (access(ip, IEXEC))
E 47
		goto bad;
D 30
	irele(ip);
E 30
I 30
D 81
	iunlock(ip);
E 81
I 81
	IUNLOCK(ip);
E 81
E 30
D 31
	if (*ipp) {
		ilock(*ipp);
		iput(*ipp);
	}
E 31
I 31
	if (*ipp)
		irele(*ipp);
E 31
	*ipp = ip;
	return;

bad:
	iput(ip);
E 102
I 102
D 161
	if (error = maknode(MAKEIMODE(vap->va_type, vap->va_mode), ndp, &ip))
		return (error);
	ndp->ni_vp = ITOV(ip);
	return (0);
E 102
}
E 161
I 161
/* Global vfs data structures for ufs. */
D 184
struct vnodeops ffs_vnodeops = {
	ufs_lookup,		/* lookup */
	ufs_create,		/* create */
	ufs_mknod,		/* mknod */
	ufs_open,		/* open */
	ufs_close,		/* close */
	ufs_access,		/* access */
	ufs_getattr,		/* getattr */
	ufs_setattr,		/* setattr */
	ffs_read,		/* read */
	ffs_write,		/* write */
	ufs_ioctl,		/* ioctl */
	ufs_select,		/* select */
	ufs_mmap,		/* mmap */
	ffs_fsync,		/* fsync */
	ufs_seek,		/* seek */
	ufs_remove,		/* remove */
	ufs_link,		/* link */
	ufs_rename,		/* rename */
	ufs_mkdir,		/* mkdir */
	ufs_rmdir,		/* rmdir */
	ufs_symlink,		/* symlink */
	ufs_readdir,		/* readdir */
	ufs_readlink,		/* readlink */
	ufs_abortop,		/* abortop */
D 162
	ufs_inactive,		/* inactive */
E 162
I 162
	ffs_inactive,		/* inactive */
E 162
	ufs_reclaim,		/* reclaim */
	ufs_lock,		/* lock */
	ufs_unlock,		/* unlock */
D 162
	ufs_bmap,		/* bmap */
E 162
I 162
	ffs_bmap,		/* bmap */
E 162
	ufs_strategy,		/* strategy */
	ufs_print,		/* print */
	ufs_islocked,		/* islocked */
	ufs_advlock,		/* advlock */
I 162
	ffs_blkatoff,		/* blkatoff */
	ffs_vget,		/* vget */
	ffs_valloc,		/* valloc */
	ffs_vfree,		/* vfree */
	ffs_truncate,		/* truncate */
	ffs_update,		/* update */
	bwrite,			/* bwrite */
E 184
I 184
int (**ffs_vnodeop_p)();
struct vnodeopv_entry_desc ffs_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, ufs_lookup },		/* lookup */
	{ &vop_create_desc, ufs_create },		/* create */
I 222
	{ &vop_whiteout_desc, ufs_whiteout },		/* whiteout */
E 222
D 190
	{ &vop_mknod_desc, ufs_mknod },		/* mknod */
	{ &vop_open_desc, ufs_open },		/* open */
	{ &vop_close_desc, ufs_close },		/* close */
E 190
I 190
	{ &vop_mknod_desc, ufs_mknod },			/* mknod */
	{ &vop_open_desc, ufs_open },			/* open */
	{ &vop_close_desc, ufs_close },			/* close */
E 190
	{ &vop_access_desc, ufs_access },		/* access */
	{ &vop_getattr_desc, ufs_getattr },		/* getattr */
	{ &vop_setattr_desc, ufs_setattr },		/* setattr */
D 190
	{ &vop_read_desc, ffs_read },		/* read */
	{ &vop_write_desc, ffs_write },		/* write */
	{ &vop_ioctl_desc, ufs_ioctl },		/* ioctl */
E 190
I 190
	{ &vop_read_desc, ffs_read },			/* read */
	{ &vop_write_desc, ffs_write },			/* write */
I 223
	{ &vop_lease_desc, ufs_lease_check },		/* lease */
E 223
	{ &vop_ioctl_desc, ufs_ioctl },			/* ioctl */
E 190
	{ &vop_select_desc, ufs_select },		/* select */
I 226
	{ &vop_revoke_desc, ufs_revoke },		/* revoke */
E 226
D 190
	{ &vop_mmap_desc, ufs_mmap },		/* mmap */
	{ &vop_fsync_desc, ffs_fsync },		/* fsync */
	{ &vop_seek_desc, ufs_seek },		/* seek */
E 190
I 190
	{ &vop_mmap_desc, ufs_mmap },			/* mmap */
	{ &vop_fsync_desc, ffs_fsync },			/* fsync */
	{ &vop_seek_desc, ufs_seek },			/* seek */
E 190
	{ &vop_remove_desc, ufs_remove },		/* remove */
D 190
	{ &vop_link_desc, ufs_link },		/* link */
E 190
I 190
	{ &vop_link_desc, ufs_link },			/* link */
E 190
	{ &vop_rename_desc, ufs_rename },		/* rename */
D 190
	{ &vop_mkdir_desc, ufs_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, ufs_rmdir },		/* rmdir */
E 190
I 190
	{ &vop_mkdir_desc, ufs_mkdir },			/* mkdir */
	{ &vop_rmdir_desc, ufs_rmdir },			/* rmdir */
E 190
	{ &vop_symlink_desc, ufs_symlink },		/* symlink */
	{ &vop_readdir_desc, ufs_readdir },		/* readdir */
	{ &vop_readlink_desc, ufs_readlink },		/* readlink */
	{ &vop_abortop_desc, ufs_abortop },		/* abortop */
D 206
	{ &vop_inactive_desc, ffs_inactive },		/* inactive */
E 206
I 206
	{ &vop_inactive_desc, ufs_inactive },		/* inactive */
E 206
D 221
	{ &vop_reclaim_desc, ufs_reclaim },		/* reclaim */
E 221
I 221
	{ &vop_reclaim_desc, ffs_reclaim },		/* reclaim */
E 221
D 190
	{ &vop_lock_desc, ufs_lock },		/* lock */
E 190
I 190
	{ &vop_lock_desc, ufs_lock },			/* lock */
E 190
	{ &vop_unlock_desc, ufs_unlock },		/* unlock */
D 190
	{ &vop_bmap_desc, ffs_bmap },		/* bmap */
E 190
I 190
D 201
	{ &vop_bmap_desc, ffs_bmap },			/* bmap */
E 201
I 201
	{ &vop_bmap_desc, ufs_bmap },			/* bmap */
E 201
E 190
	{ &vop_strategy_desc, ufs_strategy },		/* strategy */
D 190
	{ &vop_print_desc, ufs_print },		/* print */
E 190
I 190
	{ &vop_print_desc, ufs_print },			/* print */
E 190
	{ &vop_islocked_desc, ufs_islocked },		/* islocked */
I 212
	{ &vop_pathconf_desc, ufs_pathconf },		/* pathconf */
E 212
	{ &vop_advlock_desc, ufs_advlock },		/* advlock */
	{ &vop_blkatoff_desc, ffs_blkatoff },		/* blkatoff */
D 190
	{ &vop_vget_desc, ffs_vget },		/* vget */
E 190
I 190
D 194
	{ &vop_vget_desc, ffs_vget },			/* vget */
E 194
E 190
	{ &vop_valloc_desc, ffs_valloc },		/* valloc */
I 219
	{ &vop_reallocblks_desc, ffs_reallocblks },	/* reallocblks */
E 219
D 190
	{ &vop_vfree_desc, ffs_vfree },		/* vfree */
E 190
I 190
	{ &vop_vfree_desc, ffs_vfree },			/* vfree */
E 190
	{ &vop_truncate_desc, ffs_truncate },		/* truncate */
	{ &vop_update_desc, ffs_update },		/* update */
D 185
	{ &vop_bwrite_desc, bwrite },
E 185
I 185
	{ &vop_bwrite_desc, vn_bwrite },
E 185
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
E 184
E 162
};
I 184
struct vnodeopv_desc ffs_vnodeop_opv_desc =
	{ &ffs_vnodeop_p, ffs_vnodeop_entries };
E 184
E 161

I 162
D 184
struct vnodeops ffs_specops = {
	spec_lookup,		/* lookup */
	spec_create,		/* create */
	spec_mknod,		/* mknod */
	spec_open,		/* open */
	ufsspec_close,		/* close */
	ufs_access,		/* access */
	ufs_getattr,		/* getattr */
	ufs_setattr,		/* setattr */
	ufsspec_read,		/* read */
	ufsspec_write,		/* write */
	spec_ioctl,		/* ioctl */
	spec_select,		/* select */
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
	ffs_inactive,		/* inactive */
	ufs_reclaim,		/* reclaim */
	ufs_lock,		/* lock */
	ufs_unlock,		/* unlock */
	spec_bmap,		/* bmap */
	spec_strategy,		/* strategy */
	ufs_print,		/* print */
	ufs_islocked,		/* islocked */
	spec_advlock,		/* advlock */
	spec_blkatoff,		/* blkatoff */
	spec_vget,		/* vget */
	spec_valloc,		/* valloc */
	spec_vfree,		/* vfree */
	spec_truncate,		/* truncate */
	ffs_update,		/* update */
	bwrite,			/* bwrite */
E 184
I 184
int (**ffs_specop_p)();
struct vnodeopv_entry_desc ffs_specop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, spec_lookup },		/* lookup */
	{ &vop_create_desc, spec_create },		/* create */
	{ &vop_mknod_desc, spec_mknod },		/* mknod */
D 190
	{ &vop_open_desc, spec_open },		/* open */
E 190
I 190
	{ &vop_open_desc, spec_open },			/* open */
E 190
	{ &vop_close_desc, ufsspec_close },		/* close */
	{ &vop_access_desc, ufs_access },		/* access */
	{ &vop_getattr_desc, ufs_getattr },		/* getattr */
	{ &vop_setattr_desc, ufs_setattr },		/* setattr */
	{ &vop_read_desc, ufsspec_read },		/* read */
	{ &vop_write_desc, ufsspec_write },		/* write */
I 223
	{ &vop_lease_desc, spec_lease_check },		/* lease */
E 223
	{ &vop_ioctl_desc, spec_ioctl },		/* ioctl */
	{ &vop_select_desc, spec_select },		/* select */
I 226
	{ &vop_revoke_desc, spec_revoke },		/* revoke */
E 226
D 190
	{ &vop_mmap_desc, spec_mmap },		/* mmap */
E 190
I 190
	{ &vop_mmap_desc, spec_mmap },			/* mmap */
E 190
D 193
	{ &vop_fsync_desc, spec_fsync },		/* fsync */
E 193
I 193
	{ &vop_fsync_desc, ffs_fsync },			/* fsync */
E 193
D 190
	{ &vop_seek_desc, spec_seek },		/* seek */
E 190
I 190
	{ &vop_seek_desc, spec_seek },			/* seek */
E 190
	{ &vop_remove_desc, spec_remove },		/* remove */
D 190
	{ &vop_link_desc, spec_link },		/* link */
E 190
I 190
	{ &vop_link_desc, spec_link },			/* link */
E 190
	{ &vop_rename_desc, spec_rename },		/* rename */
	{ &vop_mkdir_desc, spec_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, spec_rmdir },		/* rmdir */
	{ &vop_symlink_desc, spec_symlink },		/* symlink */
	{ &vop_readdir_desc, spec_readdir },		/* readdir */
	{ &vop_readlink_desc, spec_readlink },		/* readlink */
	{ &vop_abortop_desc, spec_abortop },		/* abortop */
D 206
	{ &vop_inactive_desc, ffs_inactive },		/* inactive */
E 206
I 206
	{ &vop_inactive_desc, ufs_inactive },		/* inactive */
E 206
D 221
	{ &vop_reclaim_desc, ufs_reclaim },		/* reclaim */
E 221
I 221
	{ &vop_reclaim_desc, ffs_reclaim },		/* reclaim */
E 221
D 190
	{ &vop_lock_desc, ufs_lock },		/* lock */
E 190
I 190
	{ &vop_lock_desc, ufs_lock },			/* lock */
E 190
	{ &vop_unlock_desc, ufs_unlock },		/* unlock */
D 190
	{ &vop_bmap_desc, spec_bmap },		/* bmap */
E 190
I 190
	{ &vop_bmap_desc, spec_bmap },			/* bmap */
E 190
	{ &vop_strategy_desc, spec_strategy },		/* strategy */
D 190
	{ &vop_print_desc, ufs_print },		/* print */
E 190
I 190
	{ &vop_print_desc, ufs_print },			/* print */
E 190
	{ &vop_islocked_desc, ufs_islocked },		/* islocked */
I 212
	{ &vop_pathconf_desc, spec_pathconf },		/* pathconf */
E 212
	{ &vop_advlock_desc, spec_advlock },		/* advlock */
	{ &vop_blkatoff_desc, spec_blkatoff },		/* blkatoff */
D 190
	{ &vop_vget_desc, spec_vget },		/* vget */
E 190
I 190
D 194
	{ &vop_vget_desc, spec_vget },			/* vget */
E 194
E 190
	{ &vop_valloc_desc, spec_valloc },		/* valloc */
I 219
	{ &vop_reallocblks_desc, spec_reallocblks },	/* reallocblks */
E 219
D 191
	{ &vop_vfree_desc, spec_vfree },		/* vfree */
E 191
I 191
	{ &vop_vfree_desc, ffs_vfree },			/* vfree */
E 191
	{ &vop_truncate_desc, spec_truncate },		/* truncate */
	{ &vop_update_desc, ffs_update },		/* update */
D 185
	{ &vop_bwrite_desc, bwrite },
E 185
I 185
	{ &vop_bwrite_desc, vn_bwrite },
E 185
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
E 184
};
I 184
struct vnodeopv_desc ffs_specop_opv_desc =
	{ &ffs_specop_p, ffs_specop_entries };
E 184

#ifdef FIFO
D 184
struct vnodeops ffs_fifoops = {
	fifo_lookup,		/* lookup */
	fifo_create,		/* create */
	fifo_mknod,		/* mknod */
	fifo_open,		/* open */
	ufsfifo_close,		/* close */
	ufs_access,		/* access */
	ufs_getattr,		/* getattr */
	ufs_setattr,		/* setattr */
	ufsfifo_read,		/* read */
	ufsfifo_write,		/* write */
	fifo_ioctl,		/* ioctl */
	fifo_select,		/* select */
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
	ffs_inactive,		/* inactive */
	ufs_reclaim,		/* reclaim */
	ufs_lock,		/* lock */
	ufs_unlock,		/* unlock */
	fifo_bmap,		/* bmap */
	fifo_strategy,		/* strategy */
	ufs_print,		/* print */
	ufs_islocked,		/* islocked */
	fifo_advlock,		/* advlock */
	fifo_blkatoff,		/* blkatoff */
	fifo_vget,		/* vget */
	fifo_valloc,		/* valloc */
	fifo_vfree,		/* vfree */
	fifo_truncate,		/* truncate */
	ffs_update,		/* update */
	bwrite,			/* bwrite */
E 184
I 184
int (**ffs_fifoop_p)();
struct vnodeopv_entry_desc ffs_fifoop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, fifo_lookup },		/* lookup */
	{ &vop_create_desc, fifo_create },		/* create */
	{ &vop_mknod_desc, fifo_mknod },		/* mknod */
D 190
	{ &vop_open_desc, fifo_open },		/* open */
E 190
I 190
	{ &vop_open_desc, fifo_open },			/* open */
E 190
	{ &vop_close_desc, ufsfifo_close },		/* close */
	{ &vop_access_desc, ufs_access },		/* access */
	{ &vop_getattr_desc, ufs_getattr },		/* getattr */
	{ &vop_setattr_desc, ufs_setattr },		/* setattr */
	{ &vop_read_desc, ufsfifo_read },		/* read */
	{ &vop_write_desc, ufsfifo_write },		/* write */
I 223
	{ &vop_lease_desc, fifo_lease_check },		/* lease */
E 223
	{ &vop_ioctl_desc, fifo_ioctl },		/* ioctl */
	{ &vop_select_desc, fifo_select },		/* select */
I 226
	{ &vop_revoke_desc, fifo_revoke },		/* revoke */
E 226
D 190
	{ &vop_mmap_desc, fifo_mmap },		/* mmap */
E 190
I 190
	{ &vop_mmap_desc, fifo_mmap },			/* mmap */
E 190
D 193
	{ &vop_fsync_desc, fifo_fsync },		/* fsync */
E 193
I 193
	{ &vop_fsync_desc, ffs_fsync },			/* fsync */
E 193
D 190
	{ &vop_seek_desc, fifo_seek },		/* seek */
E 190
I 190
	{ &vop_seek_desc, fifo_seek },			/* seek */
E 190
	{ &vop_remove_desc, fifo_remove },		/* remove */
D 190
	{ &vop_link_desc, fifo_link },		/* link */
E 190
I 190
	{ &vop_link_desc, fifo_link },			/* link */
E 190
	{ &vop_rename_desc, fifo_rename },		/* rename */
	{ &vop_mkdir_desc, fifo_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, fifo_rmdir },		/* rmdir */
	{ &vop_symlink_desc, fifo_symlink },		/* symlink */
	{ &vop_readdir_desc, fifo_readdir },		/* readdir */
	{ &vop_readlink_desc, fifo_readlink },		/* readlink */
	{ &vop_abortop_desc, fifo_abortop },		/* abortop */
D 206
	{ &vop_inactive_desc, ffs_inactive },		/* inactive */
E 206
I 206
	{ &vop_inactive_desc, ufs_inactive },		/* inactive */
E 206
D 221
	{ &vop_reclaim_desc, ufs_reclaim },		/* reclaim */
E 221
I 221
	{ &vop_reclaim_desc, ffs_reclaim },		/* reclaim */
E 221
D 190
	{ &vop_lock_desc, ufs_lock },		/* lock */
E 190
I 190
	{ &vop_lock_desc, ufs_lock },			/* lock */
E 190
	{ &vop_unlock_desc, ufs_unlock },		/* unlock */
D 190
	{ &vop_bmap_desc, fifo_bmap },		/* bmap */
E 190
I 190
	{ &vop_bmap_desc, fifo_bmap },			/* bmap */
E 190
	{ &vop_strategy_desc, fifo_strategy },		/* strategy */
D 190
	{ &vop_print_desc, ufs_print },		/* print */
E 190
I 190
	{ &vop_print_desc, ufs_print },			/* print */
E 190
	{ &vop_islocked_desc, ufs_islocked },		/* islocked */
I 212
	{ &vop_pathconf_desc, fifo_pathconf },		/* pathconf */
E 212
	{ &vop_advlock_desc, fifo_advlock },		/* advlock */
	{ &vop_blkatoff_desc, fifo_blkatoff },		/* blkatoff */
D 190
	{ &vop_vget_desc, fifo_vget },		/* vget */
E 190
I 190
D 194
	{ &vop_vget_desc, fifo_vget },			/* vget */
E 194
E 190
	{ &vop_valloc_desc, fifo_valloc },		/* valloc */
I 219
	{ &vop_reallocblks_desc, fifo_reallocblks },	/* reallocblks */
E 219
D 191
	{ &vop_vfree_desc, fifo_vfree },		/* vfree */
E 191
I 191
	{ &vop_vfree_desc, ffs_vfree },			/* vfree */
E 191
	{ &vop_truncate_desc, fifo_truncate },		/* truncate */
	{ &vop_update_desc, ffs_update },		/* update */
D 185
	{ &vop_bwrite_desc, bwrite },
E 185
I 185
	{ &vop_bwrite_desc, vn_bwrite },
E 185
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
E 184
};
I 184
struct vnodeopv_desc ffs_fifoop_opv_desc =
	{ &ffs_fifoop_p, ffs_fifoop_entries };
E 184
#endif /* FIFO */

I 218
D 227
#ifdef DEBUG
E 227
E 218
I 208
/*
 * Enabling cluster read/write operations.
D 211
 * Default is off until we trust them.
E 211
 */
D 211
int doclusterread = 0;
int doclusterwrite = 0;
E 211
I 211
D 227
#include <sys/sysctl.h>
E 227
int doclusterread = 1;
D 227
struct ctldebug debug11 = { "doclusterread", &doclusterread };
E 227
int doclusterwrite = 1;
D 227
struct ctldebug debug12 = { "doclusterwrite", &doclusterwrite };
I 218
#else
/* XXX for ufs_readwrite */
#define doclusterread 1
#define doclusterwrite 1
#endif
E 227
E 218
E 211
E 208
E 162
E 26
D 161
/*
I 26
D 102
 * Open system call.
E 102
I 102
 * Mknod vnode call
E 102
 */
D 102
open()
E 102
I 102
/* ARGSUSED */
D 155
ufs_mknod(ndp, vap, cred)
E 155
I 155
ufs_mknod(ndp, vap, cred, p)
E 155
	struct nameidata *ndp;
	struct ucred *cred;
	struct vattr *vap;
I 155
	struct proc *p;
E 155
E 102
{
I 115
	register struct vnode *vp;
E 115
D 63
	register struct inode *ip;
	register struct a {
E 63
I 63
D 102
	struct a {
E 63
		char	*fname;
D 37
		int	rwmode;
E 37
I 37
D 63
		int	flags;
E 63
		int	mode;
E 37
D 63
	} *uap;
I 37
D 47
	int checkpermissions = 1;
E 47
I 47
	int checkpermissions = 1, flags;
E 63
I 63
		int	crtmode;
	} *uap = (struct a *) u.u_ap;
E 102
I 102
	struct inode *ip;
	int error;
E 161
I 161
D 165
int	maknode __P((int, struct nameidata *, struct inode **));
E 165
E 161
E 102
E 63
E 47
E 37

D 63
	uap = (struct a *)u.u_ap;
D 37
	ip = namei(uchar, 0, 1);
E 37
I 37
D 47
	if (uap->flags&FCREATE) {
		ip = namei(uchar, 1, 1);
E 47
I 47
	flags = uap->flags + 1;
	if ((flags&FTRUNCATE) && (flags&FWRITE) == 0) {
		u.u_error = EINVAL;
		return;
	}
	if (flags&FCREATE) {
		ip = namei(uchar, CREATE, 1);
E 47
		if (ip == NULL) {
			if (u.u_error)
				return;
			ip = maknode(uap->mode&07777&(~ISVTX));
			checkpermissions = 0;
D 47
			uap->flags &= ~FTRUNCATE;
E 47
I 47
			flags &= ~FTRUNCATE;
E 47
		}
	} else
D 47
		ip = namei(uchar, 0, 1);
E 47
I 47
		ip = namei(uchar, LOOKUP, 1);
E 47
E 37
	if (ip == NULL)
		return;
D 37
	open1(ip, ++uap->rwmode, 0);
E 37
I 37
D 47
	open1(ip, ++uap->flags, checkpermissions);
E 47
I 47
	open1(ip, flags, checkpermissions);
E 63
I 63
D 82
	copen(uap->mode-FOPEN, uap->crtmode);
E 82
I 82
D 102
	copen(uap->mode-FOPEN, uap->crtmode, uap->fname);
E 82
E 63
E 47
E 37
}

I 37
D 63
#ifndef NOCOMPAT
E 63
E 37
/*
 * Creat system call.
 */
D 35
creat()
E 35
I 35
D 63
ocreat()
E 63
I 63
creat()
E 63
E 35
{
D 63
	register struct inode *ip;
	register struct a {
E 63
I 63
	struct a {
E 63
		char	*fname;
		int	fmode;
D 63
	} *uap;
E 63
I 63
	} *uap = (struct a *)u.u_ap;
E 63

D 63
	uap = (struct a *)u.u_ap;
D 47
	ip = namei(uchar, 1, 1);
E 47
I 47
	ip = namei(uchar, CREATE, 1);
E 47
	if (ip == NULL) {
		if (u.u_error)
			return;
		ip = maknode(uap->fmode&07777&(~ISVTX));
D 37
		if (ip==NULL)
E 37
I 37
		if (ip == NULL)
E 37
			return;
D 37
		open1(ip, FWRITE, 2);
E 37
I 37
		open1(ip, FWRITE, 0);
E 37
	} else
D 37
		open1(ip, FWRITE, 1);
E 37
I 37
D 47
		open1(ip, FWRITE|FTRUNCATE, 0);
E 47
I 47
		open1(ip, FWRITE|FTRUNCATE, 1);
E 63
I 63
D 82
	copen(FWRITE|FCREAT|FTRUNC, uap->fmode);
E 82
I 82
	copen(FWRITE|FCREAT|FTRUNC, uap->fmode, uap->fname);
E 82
E 63
E 47
E 37
}
I 37
D 63
#endif
E 63
E 37

/*
 * Common code for open and creat.
D 37
 * Check permissions, allocate an open file structure,
 * and call the device open routine if any.
E 37
I 37
D 63
 * Check permissions (if we haven't done so already),
 * allocate an open file structure, and call
 * the device open routine, if any.
E 63
I 63
 * Check permissions, allocate an open file structure,
 * and call the device open routine if any.
E 63
E 37
 */
D 37
open1(ip, mode, trf)
E 37
I 37
D 63
open1(ip, mode, checkpermissions)
E 37
	register struct inode *ip;
	register mode;
E 63
I 63
D 82
copen(mode, arg)
E 82
I 82
copen(mode, arg, fname)
E 82
	register int mode;
	int arg;
I 82
	caddr_t fname;
E 82
E 63
{
I 63
	register struct inode *ip;
E 63
	register struct file *fp;
I 82
	register struct nameidata *ndp = &u.u_nd;
E 82
D 37
	int i;
E 37
I 37
D 63
	int i, flags;
E 63
I 63
D 93
	int i;
E 93
I 93
	int indx;
E 93
E 63
E 37

D 37
	if (trf != 2) {
E 37
I 37
D 63
	if (checkpermissions) {
E 63
I 63
D 93
#ifdef notdef
	if ((mode&(FREAD|FWRITE)) == 0) {
		u.u_error = EINVAL;
E 93
I 93
	fp = falloc();
	if (fp == NULL)
E 93
		return;
D 93
	}
#endif
E 93
I 93
	indx = u.u_r.r_val1;
E 93
I 82
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = fname;
E 82
	if (mode&FCREAT) {
D 82
		ip = namei(uchar, CREATE, 1);
E 82
I 82
D 88
		ndp->ni_nameiop = CREATE | FOLLOW;
E 88
I 88
		if (mode & FEXCL)
			ndp->ni_nameiop = CREATE;
		else
			ndp->ni_nameiop = CREATE | FOLLOW;
E 88
		ip = namei(ndp);
E 82
		if (ip == NULL) {
			if (u.u_error)
D 93
				return;
E 93
I 93
				goto bad1;
E 93
D 82
			ip = maknode(arg&07777&(~ISVTX));
E 82
I 82
			ip = maknode(arg&07777&(~ISVTX), ndp);
E 82
			if (ip == NULL)
D 93
				return;
E 93
I 93
				goto bad1;
E 93
			mode &= ~FTRUNC;
		} else {
			if (mode&FEXCL) {
				u.u_error = EEXIST;
D 93
				iput(ip);
				return;
E 93
I 93
				goto bad;
E 93
			}
			mode &= ~FCREAT;
		}
	} else {
D 82
		ip = namei(uchar, LOOKUP, 1);
E 82
I 82
		ndp->ni_nameiop = LOOKUP | FOLLOW;
		ip = namei(ndp);
E 82
		if (ip == NULL)
D 93
			return;
E 93
I 93
			goto bad1;
E 102
I 102
D 161
	if (error = maknode(MAKEIMODE(vap->va_type, vap->va_mode), ndp, &ip))
		return (error);
I 115
D 126
	vp = ITOV(ip);
E 115
	if (vap->va_rdev) {
E 126
I 126
	ip->i_flag |= IACC|IUPD|ICHG;
	if (vap->va_rdev != VNOVAL) {
E 126
		/*
		 * Want to be able to use this to make badblock
		 * inodes, so don't truncate the dev number.
		 */
D 115
		ITOV(ip)->v_rdev = ip->i_rdev = vap->va_rdev;
E 115
I 115
D 117
		vp->v_rdev = ip->i_rdev = vap->va_rdev;
E 117
I 117
		ip->i_rdev = vap->va_rdev;
E 117
E 115
D 126
		ip->i_flag |= IACC|IUPD|ICHG;
E 126
E 102
E 93
	}
D 102
	if ((ip->i_mode & IFMT) == IFSOCK) {
		u.u_error = EOPNOTSUPP;
		goto bad;
	}
	if ((mode&FCREAT) == 0) {
E 63
E 37
		if (mode&FREAD)
D 37
			(void) access(ip, IREAD);
E 37
I 37
			if (access(ip, IREAD))
				goto bad;
E 37
D 76
		if (mode&FWRITE) {
E 76
I 76
		if (mode&(FWRITE|FTRUNC)) {
E 76
D 37
			(void) access(ip, IWRITE);
			if ((ip->i_mode&IFMT) == IFDIR)
E 37
I 37
			if (access(ip, IWRITE))
				goto bad;
			if ((ip->i_mode&IFMT) == IFDIR) {
E 37
				u.u_error = EISDIR;
I 37
				goto bad;
			}
E 37
		}
	}
D 31
	if (u.u_error)
		goto out;
E 31
I 31
D 37
	if (u.u_error) {
		iput(ip);
		return;
E 37
I 37
D 63

	/*
	 * Check locking on inode.  Release "inode lock"
	 * while doing so in case we block inside flocki.
	 */
	flags = 0;
D 47
	if (mode&(FRDLOCK|FWRLOCK)) {
E 47
I 47
	if (mode&(FSHLOCK|FEXLOCK)) {
E 47
		iunlock(ip);
		flags = flocki(ip, 0, mode);
		ilock(ip);
		if (u.u_error)
			goto bad;
E 37
	}
E 31
D 37
	if (trf == 1)
		itrunc(ip);
E 37
I 37
	if (mode&FTRUNCATE)
E 63
I 63
D 93
	fp = falloc();
	if (fp == NULL)
		goto bad;
E 93
	if (mode&FTRUNC)
E 63
D 47
		itrunc(ip, 0);
E 47
I 47
		itrunc(ip, (u_long)0);
E 47
E 37
D 30
	irele(ip);
E 30
I 30
D 81
	iunlock(ip);
E 81
I 81
	IUNLOCK(ip);
E 81
E 30
D 63
	if ((fp = falloc()) == NULL)
		goto out;
D 37
	fp->f_flag = mode&(FREAD|FWRITE);
E 37
I 37
	fp->f_flag = mode & FMODES;
E 37
I 35
	fp->f_type = DTYPE_FILE;
E 63
I 63
	fp->f_flag = mode&FMASK;
	fp->f_type = DTYPE_INODE;
	fp->f_ops = &inodeops;
	fp->f_data = (caddr_t)ip;
E 63
E 35
D 93
	i = u.u_r.r_val1;
E 93
D 63
	fp->f_inode = ip;
I 33
D 37
#ifdef EFS
	openi(ip, mode&(FREAD|FWRITE), trf);
#else
E 33
	openi(ip, mode&(FREAD|FWRITE));
I 33
#endif
E 33
	if (u.u_error == 0)
E 37
I 37
D 44
	openi(ip, mode);
E 44
I 44
	u.u_error = openi(ip, mode);
E 44
	if (u.u_error == 0) {
		u.u_pofile[i] = flags;
E 63
I 63
D 73
#ifdef notdef
E 73
	if (setjmp(&u.u_qsave)) {
		if (u.u_error == 0)
			u.u_error = EINTR;
D 93
		u.u_ofile[i] = NULL;
E 93
I 93
		u.u_ofile[indx] = NULL;
E 93
		closef(fp);
E 63
E 37
		return;
I 37
	}
I 63
D 73
#endif
E 73
	u.u_error = openi(ip, mode);
	if (u.u_error == 0)
		return;
E 63
E 37
D 93
	u.u_ofile[i] = NULL;
	fp->f_count--;
D 63
out:
E 63
D 31
	if (ip != NULL)
		iput(ip);
E 31
I 31
	irele(ip);
I 37
	return;
E 93
I 93
	ILOCK(ip);
E 93
bad:
E 102
D 112
	iput(ip);
E 112
I 93
D 102
bad1:
	u.u_ofile[indx] = NULL;
	fp->f_count--;
E 102
I 102
	/*
	 * Remove inode so that it will be reloaded by iget and
	 * checked to see if it is an alias of an existing entry
	 * in the inode cache.
	 */
D 115
	remque(ip);
	ip->i_forw = ip;
	ip->i_back = ip;
I 112
	ITOV(ip)->v_type = VNON;
E 115
D 126
	iput(ip);
E 126
I 126
	vp = ITOV(ip);
	vput(vp);
E 126
I 115
	vp->v_type = VNON;
	vgone(vp);
E 115
E 112
	return (0);
E 102
E 93
E 37
E 31
}

E 161
D 214
/*
D 102
 * Mknod system call
E 102
I 102
D 161
 * Open called.
 *
 * Nothing to do.
E 102
 */
D 102
mknod()
E 102
I 102
/* ARGSUSED */
D 155
ufs_open(vp, mode, cred)
E 155
I 155
ufs_open(vp, mode, cred, p)
E 155
	struct vnode *vp;
	int mode;
	struct ucred *cred;
I 155
	struct proc *p;
E 155
E 102
{
D 102
	register struct inode *ip;
	register struct a {
		char	*fname;
		int	fmode;
		int	dev;
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
E 102
E 82

D 82
	uap = (struct a *)u.u_ap;
E 82
D 63
	if (suser()) {
D 47
		ip = namei(uchar, 1, 0);
E 47
I 47
		ip = namei(uchar, CREATE, 0);
E 47
		if (ip != NULL) {
			u.u_error = EEXIST;
			goto out;
		}
E 63
I 63
D 101
	if (!suser())
E 101
I 101
D 102
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 101
		return;
D 82
	ip = namei(uchar, CREATE, 0);
E 82
I 82
	ndp->ni_nameiop = CREATE;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
	ip = namei(ndp);
E 82
	if (ip != NULL) {
		u.u_error = EEXIST;
		goto out;
E 63
	}
	if (u.u_error)
		return;
D 82
	ip = maknode(uap->fmode);
E 82
I 82
	ip = maknode(uap->fmode, ndp);
E 82
	if (ip == NULL)
		return;
D 63
	if (uap->dev) {
		/*
		 * Want to be able to use this to make badblock
		 * inodes, so don't truncate the dev number.
		 */
D 28
		ip->i_un.i_rdev = uap->dev;
E 28
I 28
		ip->i_rdev = uap->dev;
E 28
		ip->i_flag |= IACC|IUPD|ICHG;
E 63
I 63
	switch (ip->i_mode & IFMT) {

I 72
	case IFMT:	/* used by badsect to flag bad sectors */
E 72
	case IFCHR:
	case IFBLK:
		if (uap->dev) {
			/*
			 * Want to be able to use this to make badblock
			 * inodes, so don't truncate the dev number.
			 */
			ip->i_rdev = uap->dev;
			ip->i_flag |= IACC|IUPD|ICHG;
		}
E 63
	}

out:
	iput(ip);
E 102
I 102
	return (0);
E 102
}

/*
D 102
 * link system call
E 102
I 102
 * Close called
 *
 * Update the times on the inode.
E 102
 */
D 102
link()
E 102
I 102
/* ARGSUSED */
D 155
ufs_close(vp, fflag, cred)
E 155
I 155
ufs_close(vp, fflag, cred, p)
E 155
	struct vnode *vp;
	int fflag;
	struct ucred *cred;
I 155
	struct proc *p;
E 155
E 102
{
D 102
	register struct inode *ip, *xp;
	register struct a {
		char	*target;
		char	*linkname;
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
E 102
I 102
	register struct inode *ip = VTOI(vp);
E 102
E 82

D 82
	uap = (struct a *)u.u_ap;
D 47
	ip = namei(uchar, 0, 1);    /* well, this routine is doomed anyhow */
E 47
I 47
	ip = namei(uchar, LOOKUP, 1); /* well, this routine is doomed anyhow */
E 82
I 82
D 102
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->target;
	ip = namei(ndp);	/* well, this routine is doomed anyhow */
E 82
E 47
	if (ip == NULL)
		return;
D 33
	if ((ip->i_mode&IFMT)==IFDIR && !suser())
		goto out1;
E 33
I 33
D 47
	if ((ip->i_mode&IFMT)==IFDIR && !suser()) {
E 47
I 47
D 101
	if ((ip->i_mode&IFMT) == IFDIR && !suser()) {
E 101
I 101
	if ((ip->i_mode&IFMT) == IFDIR &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag))) {
E 101
E 47
		iput(ip);
		return;
	}
I 100
	if (ip->i_nlink == LINK_MAX - 1) {
		u.u_error = EMLINK;
		iput(ip);
		return;
	}
E 100
E 33
	ip->i_nlink++;
	ip->i_flag |= ICHG;
D 41
	iupdat(ip, &time, &time, 1);
E 41
I 41
D 45
	iupdat(ip, &time.tv_sec, &time.tv_sec, 1);
E 45
I 45
D 46
	iupdat(ip, time, time, 1);
E 46
I 46
	iupdat(ip, &time, &time, 1);
E 46
E 45
E 41
D 30
	irele(ip);
E 30
I 30
D 81
	iunlock(ip);
E 81
I 81
	IUNLOCK(ip);
E 81
E 30
D 82
	u.u_dirp = (caddr_t)uap->linkname;
D 47
	xp = namei(uchar, 1, 0);
E 47
I 47
	xp = namei(uchar, CREATE, 0);
E 82
I 82
	ndp->ni_nameiop = CREATE;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = (caddr_t)uap->linkname;
	xp = namei(ndp);
E 82
E 47
	if (xp != NULL) {
		u.u_error = EEXIST;
		iput(xp);
		goto out;
	}
	if (u.u_error)
		goto out;
D 82
	if (u.u_pdir->i_dev != ip->i_dev) {
		iput(u.u_pdir);
E 82
I 82
	if (ndp->ni_pdir->i_dev != ip->i_dev) {
		iput(ndp->ni_pdir);
E 82
		u.u_error = EXDEV;
		goto out;
	}
D 36
	wdir(ip);
E 36
I 36
D 55
	direnter(ip);
E 55
I 55
D 82
	u.u_error = direnter(ip);
E 82
I 82
	u.u_error = direnter(ip, ndp);
E 82
E 55
E 36
out:
	if (u.u_error) {
		ip->i_nlink--;
		ip->i_flag |= ICHG;
	}
D 39
out1:
E 39
D 31
	iput(ip);
E 31
I 31
	irele(ip);
E 102
I 102
D 121
	if (vp->v_count > 1 && !(ip->i_flag & ILOCKED))
E 121
I 121
	if (vp->v_usecount > 1 && !(ip->i_flag & ILOCKED))
E 121
		ITIMES(ip, &time, &time);
	return (0);
E 102
E 31
}

I 131
/*
 * Check mode permission on inode pointer. Mode is READ, WRITE or EXEC.
 * The mode is shifted to select the owner/group/other fields. The
 * super user is granted all permissions.
 */
E 131
D 102
/*
 * symlink -- make a symbolic link
 */
symlink()
E 102
I 102
D 155
ufs_access(vp, mode, cred)
E 155
I 155
ufs_access(vp, mode, cred, p)
E 155
	struct vnode *vp;
D 131
	int mode;
E 131
I 131
	register int mode;
E 131
	struct ucred *cred;
I 155
	struct proc *p;
E 155
E 102
{
I 131
	register struct inode *ip = VTOI(vp);
	register gid_t *gp;
	int i, error;
E 131
D 102
	register struct a {
		char	*target;
		char	*linkname;
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
E 82
	register struct inode *ip;
	register char *tp;
	register c, nc;
I 82
	register struct nameidata *ndp = &u.u_nd;
E 102
E 82

D 82
	uap = (struct a *)u.u_ap;
E 82
D 102
	tp = uap->target;
	nc = 0;
	while (c = fubyte(tp)) {
		if (c < 0) {
			u.u_error = EFAULT;
			return;
		}
		tp++;
		nc++;
	}
D 82
	u.u_dirp = uap->linkname;
D 47
	ip = namei(uchar, 1, 0);
E 47
I 47
	ip = namei(uchar, CREATE, 0);
E 82
I 82
	ndp->ni_nameiop = CREATE;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->linkname;
	ip = namei(ndp);
E 82
E 47
	if (ip) {
		iput(ip);
		u.u_error = EEXIST;
		return;
	}
	if (u.u_error)
		return;
D 82
	ip = maknode(IFLNK | 0777);
E 82
I 82
	ip = maknode(IFLNK | 0777, ndp);
E 82
	if (ip == NULL)
		return;
D 39
	u.u_base = uap->target;
	u.u_count = nc;
	u.u_offset = 0;
	u.u_segflg = 0;
	writei(ip);
E 39
I 39
D 94
	u.u_error = rdwri(UIO_WRITE, ip, uap->target, nc, 0, 0, (int *)0);
E 94
I 94
	u.u_error = rdwri(UIO_WRITE, ip, uap->target, nc, (off_t)0, 0,
	    (int *)0);
E 94
I 47
	/* handle u.u_error != 0 */
E 47
E 39
	iput(ip);
E 102
I 102
D 131
	return (iaccess(VTOI(vp), mode, cred));
E 131
I 131
#ifdef DIAGNOSTIC
	if (!VOP_ISLOCKED(vp)) {
		vprint("ufs_access: not locked", vp);
		panic("ufs_access: not locked");
	}
#endif
#ifdef QUOTA
	if (mode & VWRITE) {
		switch (vp->v_type) {
		case VREG: case VDIR: case VLNK:
			if (error = getinoquota(ip))
				return (error);
		}
	}
#endif /* QUOTA */
	/*
	 * If you're the super-user, you always get access.
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
E 131
E 102
}

D 102
/*
 * Unlink system call.
 * Hard to avoid races here, especially
 * in unlinking directories.
 */
unlink()
E 102
I 102
/* ARGSUSED */
D 155
ufs_getattr(vp, vap, cred)
E 155
I 155
ufs_getattr(vp, vap, cred, p)
E 155
	struct vnode *vp;
	register struct vattr *vap;
	struct ucred *cred;
I 155
	struct proc *p;
E 155
E 102
{
D 47
	register struct inode *ip, *pp;
E 47
D 102
	struct a {
		char	*fname;
D 82
	};
E 82
I 82
	} *uap = (struct a *)u.u_ap;
E 82
I 28
D 39
	struct fs *fs;
	struct buf *bp;
	int lbn, bn, base;
E 39
I 31
D 47
	int unlinkingdot = 0;
E 47
I 47
	register struct inode *ip, *dp;
I 82
	register struct nameidata *ndp = &u.u_nd;
E 102
I 102
	register struct inode *ip = VTOI(vp);
E 102
E 82
E 47
E 31
E 28

D 47
	pp = namei(uchar, 2, 0);
D 36
	if(pp == NULL)
E 36
I 36
	if (pp == NULL)
E 47
I 47
D 82
	ip = namei(uchar, DELETE | LOCKPARENT, 0);
E 82
I 82
D 102
	ndp->ni_nameiop = DELETE | LOCKPARENT;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
	ip = namei(ndp);
E 82
	if (ip == NULL)
E 47
E 36
		return;
I 33
D 37
#ifdef EFS
	/* divert to extended file system if off machine. */
	if (efsinode(pp)) {
		dev_t ndev = pp->i_rdev;
E 37
D 47

D 37
		iput(pp);	/* avoid recursive hang on inode */
		efsunlink(ndev);
		if (u.u_error != EEXIST)
			return;

		/*
		 * If a null pathname remainder, then do
		 * the unlink locally after restoring state.
		 */
		u.u_error = 0;
		u.u_dirp = (caddr_t)u.u_arg[0];
		pp = namei(uchar, 2, 0);
	}
#endif

E 37
E 33
	/*
	 * Check for unlink(".")
	 * to avoid hanging on the iget
	 */
	if (pp->i_number == u.u_dent.d_ino) {
		ip = pp;
		ip->i_count++;
I 31
		unlinkingdot++;
E 31
	} else
D 28
		ip = iget(pp->i_dev, u.u_dent.d_ino);
E 28
I 28
		ip = iget(pp->i_dev, pp->i_fs, u.u_dent.d_ino);
E 28
	if(ip == NULL)
		goto out1;
	if((ip->i_mode&IFMT)==IFDIR && !suser())
E 47
I 47
D 82
	dp = u.u_pdir;
E 82
I 82
	dp = ndp->ni_pdir;
E 82
D 101
	if ((ip->i_mode&IFMT) == IFDIR && !suser())
E 101
I 101
	if ((ip->i_mode&IFMT) == IFDIR &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 101
E 47
		goto out;
E 102
I 102
	ITIMES(ip, &time, &time);
E 102
	/*
D 102
	 * Don't unlink a mounted file.
E 102
I 102
	 * Copy from inode table
E 102
	 */
D 47
	if (ip->i_dev != pp->i_dev) {
E 47
I 47
D 102
	if (ip->i_dev != dp->i_dev) {
E 47
		u.u_error = EBUSY;
		goto out;
	}
	if (ip->i_flag&ITEXT)
		xrele(ip);	/* try once to free text */
D 36
/*
	if ((ip->i_flag&ITEXT) && ip->i_nlink==1) {
 		u.u_error = ETXTBSY;
		goto out;
E 36
I 36
D 82
	if (dirremove()) {
E 82
I 82
	if (dirremove(ndp)) {
E 82
		ip->i_nlink--;
		ip->i_flag |= ICHG;
E 36
	}
D 36
*/
D 28
	u.u_offset -= sizeof(struct direct);
	u.u_base = (caddr_t)&u.u_dent;
	u.u_count = sizeof(struct direct);
	u.u_dent.d_ino = 0;
	writei(pp);
E 28
I 28
	if (u.u_count == 0) {
		/*
		 * first entry in block, so set d_ino to zero.
		 */
I 35
/*ZZ*/if(u.u_offset&0x1ff)printf("missed dir compact dir %s/%d off %d file %s\n"
/*ZZ*/,pp->i_fs->fs_fsmnt,pp->i_number,u.u_offset,u.u_dent.d_name);
E 35
		u.u_base = (caddr_t)&u.u_dent;
		u.u_count = DIRSIZ(&u.u_dent);
		u.u_dent.d_ino = 0;
		writei(pp);
	} else {
		/*
		 * updating preceeding entry to skip over current entry.
		 */
		fs = pp->i_fs;
		lbn = lblkno(fs, u.u_offset);
		base = blkoff(fs, u.u_offset);
		bn = fsbtodb(fs, bmap(pp, lbn, B_WRITE, base + u.u_count));
		bp = bread(pp->i_dev, bn, blksize(fs, pp, lbn));
		if (bp->b_flags & B_ERROR) {
			brelse(bp);
			goto out;
		}
		((struct direct *)(bp->b_un.b_addr + base))->d_reclen +=
		    u.u_dent.d_reclen;
I 35
/*ZZ*/if(((int)(bp->b_un.b_addr + base)&0x1ff)+u.u_dent.d_reclen>512)
/*ZZ*/	panic("unlink: reclen");
E 35
		bwrite(bp);
		pp->i_flag |= IUPD|ICHG;
	}
E 28
	ip->i_nlink--;
	ip->i_flag |= ICHG;

E 36
out:
D 31
	iput(ip);
E 31
I 31
D 47
	if (unlinkingdot)
E 47
I 47
	if (dp == ip)
E 47
		irele(ip);
E 102
I 102
	vap->va_fsid = ip->i_dev;
	vap->va_fileid = ip->i_number;
	vap->va_mode = ip->i_mode & ~IFMT;
	vap->va_nlink = ip->i_nlink;
	vap->va_uid = ip->i_uid;
	vap->va_gid = ip->i_gid;
	vap->va_rdev = (dev_t)ip->i_rdev;
I 131
#ifdef tahoe
	vap->va_size = ip->i_size;
	vap->va_size_rsv = 0;
#else
E 131
D 114
	vap->va_size = ip->i_ic.ic_size.val[0];
	vap->va_size1 = ip->i_ic.ic_size.val[1];
E 114
I 114
D 129
	vap->va_size = ip->i_din.di_qsize.val[0];
	vap->va_size1 = ip->i_din.di_qsize.val[1];
E 129
I 129
	vap->va_qsize = ip->i_din.di_qsize;
I 131
#endif
E 131
E 129
E 114
	vap->va_atime.tv_sec = ip->i_atime;
I 109
	vap->va_atime.tv_usec = 0;
E 109
	vap->va_mtime.tv_sec = ip->i_mtime;
I 109
	vap->va_mtime.tv_usec = 0;
E 109
	vap->va_ctime.tv_sec = ip->i_ctime;
I 109
	vap->va_ctime.tv_usec = 0;
E 109
I 107
	vap->va_flags = ip->i_flags;
	vap->va_gen = ip->i_gen;
E 107
	/* this doesn't belong here */
	if (vp->v_type == VBLK)
		vap->va_blocksize = BLKDEV_IOSIZE;
	else if (vp->v_type == VCHR)
		vap->va_blocksize = MAXBSIZE;
E 102
	else
D 102
		iput(ip);
E 31
D 47
out1:
	iput(pp);
E 47
I 47
	iput(dp);
E 102
I 102
		vap->va_blocksize = ip->i_fs->fs_bsize;
D 110
	/*
	 * XXX THIS IS NOT CORRECT!!, but be sure to change vn_stat()
	 * if you change it.
	 */
	vap->va_bytes = ip->i_blocks;
E 110
I 110
	vap->va_bytes = dbtob(ip->i_blocks);
E 110
D 129
	vap->va_bytes1 = -1;
E 129
I 129
	vap->va_bytes_rsv = 0;
E 129
	vap->va_type = vp->v_type;
	return (0);
E 102
E 47
}

/*
D 102
 * Seek system call
E 102
I 102
 * Set attribute vnode op. called from several syscalls
E 102
 */
D 41
seek()
E 41
I 41
D 102
lseek()
E 102
I 102
D 155
ufs_setattr(vp, vap, cred)
E 155
I 155
ufs_setattr(vp, vap, cred, p)
E 155
	register struct vnode *vp;
	register struct vattr *vap;
	register struct ucred *cred;
I 155
	struct proc *p;
E 155
E 102
E 41
{
I 153
D 155
	struct proc *p = curproc;		/* XXX */
E 155
E 153
D 102
	register struct file *fp;
	register struct a {
D 37
		int	fdes;
E 37
I 37
		int	fd;
E 37
		off_t	off;
		int	sbase;
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
E 102
I 102
	register struct inode *ip = VTOI(vp);
	int error = 0;
E 102
E 82

D 82
	uap = (struct a *)u.u_ap;
E 82
D 37
	fp = getf(uap->fdes);
E 37
I 37
D 63
	fp = getf(uap->fd);
E 63
I 63
D 77
	fp = getinode(uap->fd);
E 63
E 37
	if (fp == NULL)
E 77
I 77
D 102
	GETF(fp, uap->fd);
	if (fp->f_type != DTYPE_INODE) {
		u.u_error = ESPIPE;
E 77
		return;
E 102
I 102
	/*
	 * Check for unsetable attributes.
	 */
	if ((vap->va_type != VNON) || (vap->va_nlink != VNOVAL) ||
	    (vap->va_fsid != VNOVAL) || (vap->va_fileid != VNOVAL) ||
	    (vap->va_blocksize != VNOVAL) || (vap->va_rdev != VNOVAL) ||
D 107
	    ((int)vap->va_bytes != VNOVAL)) {
E 107
I 107
	    ((int)vap->va_bytes != VNOVAL) || (vap->va_gen != VNOVAL)) {
E 107
		return (EINVAL);
E 102
I 77
	}
E 77
D 35
	if (fp->f_flag&FSOCKET) {
E 35
I 35
D 63
	if (fp->f_type == DTYPE_SOCKET) {
E 35
		u.u_error = ESPIPE;
		return;
	}
D 37
	if (uap->sbase == 1)
E 37
I 37
	if (uap->sbase == FSEEK_RELATIVE)
E 63
I 63
D 68
	if (uap->sbase == L_INCR)
E 63
E 37
		uap->off += fp->f_offset;
D 33
	else if (uap->sbase == 2)
E 33
I 33
D 37
	else if (uap->sbase == 2) {
#ifdef EFS
		struct inode *ip = fp->f_inode;
		uap->off += efsinode(ip) ? efsfilesize(fp) : ip->i_size;
#else
E 37
I 37
D 63
	else if (uap->sbase == FSEEK_EOF)
E 37
E 33
		uap->off += fp->f_inode->i_size;
E 63
I 63
	else if (uap->sbase == L_XTND)
		uap->off += ((struct inode *)fp->f_data)->i_size;
E 63
I 33
D 37
#endif
	}
E 37
E 33
	fp->f_offset = uap->off;
	u.u_r.r_off = uap->off;
E 68
I 68
D 102
	switch (uap->sbase) {

	case L_INCR:
		fp->f_offset += uap->off;
		break;

	case L_XTND:
		fp->f_offset = uap->off + ((struct inode *)fp->f_data)->i_size;
		break;

	case L_SET:
		fp->f_offset = uap->off;
		break;

	default:
		u.u_error = EINVAL;
		return;
E 102
I 102
	/*
	 * Go through the fields and update iff not VNOVAL.
	 */
	if (vap->va_uid != (u_short)VNOVAL || vap->va_gid != (u_short)VNOVAL)
D 153
		if (error = chown1(vp, vap->va_uid, vap->va_gid, cred))
E 153
I 153
		if (error = chown1(vp, vap->va_uid, vap->va_gid, p))
E 153
			return (error);
	if (vap->va_size != VNOVAL) {
		if (vp->v_type == VDIR)
			return (EISDIR);
D 108
		if (error = iaccess(ip, IWRITE, cred))
			return (error);
E 108
D 120
		if (error = itrunc(ip, vap->va_size))
E 120
I 120
		if (error = itrunc(ip, vap->va_size, 0)) /* XXX IO_SYNC? */
E 120
			return (error);
E 102
	}
D 102
	u.u_r.r_off = fp->f_offset;
E 68
}

/*
 * Access system call
 */
saccess()
{
	register svuid, svgid;
	register struct inode *ip;
	register struct a {
		char	*fname;
		int	fmode;
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
E 82

D 82
	uap = (struct a *)u.u_ap;
E 82
	svuid = u.u_uid;
	svgid = u.u_gid;
	u.u_uid = u.u_ruid;
	u.u_gid = u.u_rgid;
D 47
	ip = namei(uchar, 0, 1);
E 47
I 47
D 82
	ip = namei(uchar, LOOKUP, 1);
E 82
I 82
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
	ip = namei(ndp);
E 82
E 47
I 33
D 37
#ifdef EFS
	if (efsinode(ip)) {
		dev_t ndev = ip->i_rdev;

		iput(ip);
		efssaccess(ndev);
		if (u.u_error != EEXIST)
			return;
		u.u_error = 0;
		u.u_dirp = (caddr_t)u.u_arg[0];
		ip = namei(uchar, 0, 1);
	}
#endif
E 37
E 33
	if (ip != NULL) {
D 37
		if (uap->fmode&(IREAD>>6))
			(void) access(ip, IREAD);
		if (uap->fmode&(IWRITE>>6))
			(void) access(ip, IWRITE);
		if (uap->fmode&(IEXEC>>6))
			(void) access(ip, IEXEC);
E 37
I 37
D 47
		if (uap->fmode&FACCESS_READ && access(ip, IREAD))
E 47
I 47
D 63
		if ((uap->fmode&FACCESS_READ) && access(ip, IREAD))
E 63
I 63
		if ((uap->fmode&R_OK) && access(ip, IREAD))
E 63
E 47
			goto done;
D 47
		if (uap->fmode&FACCESS_WRITE && access(ip, IWRITE))
E 47
I 47
D 63
		if ((uap->fmode&FACCESS_WRITE) && access(ip, IWRITE))
E 63
I 63
		if ((uap->fmode&W_OK) && access(ip, IWRITE))
E 63
E 47
			goto done;
D 47
		if (uap->fmode&FACCESS_EXECUTE && access(ip, IEXEC))
E 47
I 47
D 63
		if ((uap->fmode&FACCESS_EXECUTE) && access(ip, IEXEC))
E 63
I 63
		if ((uap->fmode&X_OK) && access(ip, IEXEC))
E 63
E 47
			goto done;
done:
E 37
		iput(ip);
E 102
I 102
D 104
	/*
	 * Check whether the following attributes can be changed.
	 */
	if (cred->cr_uid != ip->i_uid &&
	    (error = suser(cred, &u.u_acflag)))
		return (error);
E 104
	if (vap->va_atime.tv_sec != VNOVAL || vap->va_mtime.tv_sec != VNOVAL) {
I 104
		if (cred->cr_uid != ip->i_uid &&
D 153
		    (error = suser(cred, &u.u_acflag)))
E 153
I 153
		    (error = suser(cred, &p->p_acflag)))
E 153
			return (error);
E 104
		if (vap->va_atime.tv_sec != VNOVAL)
			ip->i_flag |= IACC;
		if (vap->va_mtime.tv_sec != VNOVAL)
			ip->i_flag |= IUPD;
		ip->i_flag |= ICHG;
		if (error = iupdat(ip, &vap->va_atime, &vap->va_mtime, 1))
			return (error);
E 102
	}
D 102
	u.u_uid = svuid;
	u.u_gid = svgid;
E 102
I 102
	if (vap->va_mode != (u_short)VNOVAL)
D 153
		error = chmod1(vp, (int)vap->va_mode, cred);
E 153
I 153
		error = chmod1(vp, (int)vap->va_mode, p);
E 153
I 107
	if (vap->va_flags != VNOVAL) {
		if (cred->cr_uid != ip->i_uid &&
D 153
		    (error = suser(cred, &u.u_acflag)))
E 153
I 153
		    (error = suser(cred, &p->p_acflag)))
E 153
			return (error);
		if (cred->cr_uid == 0) {
			ip->i_flags = vap->va_flags;
		} else {
			ip->i_flags &= 0xffff0000;
			ip->i_flags |= (vap->va_flags & 0xffff);
		}
		ip->i_flag |= ICHG;
	}
E 107
	return (error);
E 102
}

/*
E 26
D 63
 * the fstat system call.
 */
fstat()
{
	register struct file *fp;
	register struct a {
D 37
		int	fdes;
E 37
I 37
		int	fd;
E 37
		struct stat *sb;
	} *uap;

	uap = (struct a *)u.u_ap;
D 37
	fp = getf(uap->fdes);
E 37
I 37
	fp = getf(uap->fd);
E 37
D 17
	if(fp == NULL)
E 17
I 17
	if (fp == NULL)
E 17
		return;
I 33
D 37
#ifdef EFS
	if (efsinode(fp->f_inode)) {
		efsfstat(fp->f_inode->i_rdev, fp);
		return;
	}
#endif
E 37
E 33
D 15
	stat1(fp->f_inode, uap->sb, fp->f_flag&FPIPE? fp->f_un.f_offset: 0);
E 15
I 15
D 17
	if (fp->f_flag&FPORT) {
		ptstat(fp);
		return;
	}
I 16
#ifdef BBNNET
	if (fp->f_flag&FNET) {
	    	u.u_error = EINVAL;
		return;
	}
#endif
E 16
	stat1(fp->f_inode, uap->sb);
E 17
I 17
D 35
	if (fp->f_flag & FSOCKET)
E 35
I 35
	if (fp->f_type == DTYPE_SOCKET)
E 35
D 18
		sostat(fp->f_socket);
E 18
I 18
		u.u_error = sostat(fp->f_socket, uap->sb);
E 18
	else
		stat1(fp->f_inode, uap->sb);
E 17
E 15
}

/*
E 63
D 17
 * the stat system call.
E 17
I 17
D 23
 * Stat system call.
E 23
I 23
D 27
 * Stat system call.  This version does not follow links.
E 27
I 27
D 28
 * Stat system call; this follows links.
E 28
I 28
D 102
 * Stat system call.  This version follows links.
E 28
E 27
E 23
E 17
 */
stat()
{
D 63
	register struct inode *ip;
	register struct a {
		char	*fname;
		struct stat *sb;
	} *uap;
E 63

D 63
	uap = (struct a *)u.u_ap;
D 23
	ip = namei(uchar, 0);
E 23
I 23
D 27
	ip = namei(uchar, 0, 0);
E 27
I 27
D 47
	ip = namei(uchar, 0, 1);
E 47
I 47
	ip = namei(uchar, LOOKUP, 1);
E 47
E 27
E 23
D 17
	if(ip == NULL)
E 17
I 17
	if (ip == NULL)
E 17
		return;
I 33
D 37
#ifdef EFS
	if (efsinode(ip)) {
		dev_t ndev = ip->i_rdev;

		iput(ip);
		efsstat(ndev);
		if (u.u_error != EEXIST)
			return;
		u.u_error = 0;
		u.u_dirp = (caddr_t)u.u_arg[0];
		ip = namei(uchar, 0, 1);
	}
#endif
E 37
E 33
D 15
	stat1(ip, uap->sb, (off_t)0);
E 15
I 15
	stat1(ip, uap->sb);
E 15
	iput(ip);
E 63
I 63
D 82
	stat1(1);
E 82
I 82
	stat1(FOLLOW);
E 82
E 63
}

/*
I 23
D 27
 * Lstat system call.  This version does follow links.
E 27
I 27
D 28
 * Lstat system call; like stat but doesn't follow links.
E 28
I 28
 * Lstat system call.  This version does not follow links.
E 28
E 27
 */
lstat()
{
I 63

D 82
	stat1(0);
E 82
I 82
	stat1(NOFOLLOW);
E 82
}

stat1(follow)
	int follow;
{
E 63
	register struct inode *ip;
	register struct a {
		char	*fname;
D 63
		struct stat *sb;
E 63
I 63
		struct stat *ub;
E 63
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
E 82
I 63
	struct stat sb;
I 82
	register struct nameidata *ndp = &u.u_nd;
E 82
E 63

D 82
	uap = (struct a *)u.u_ap;
D 27
	ip = namei(uchar, 0, 1);
E 27
I 27
D 47
	ip = namei(uchar, 0, 0);
E 47
I 47
D 63
	ip = namei(uchar, LOOKUP, 0);
E 63
I 63
	ip = namei(uchar, LOOKUP, follow);
E 82
I 82
	ndp->ni_nameiop = LOOKUP | follow;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
	ip = namei(ndp);
E 82
E 63
E 47
E 27
	if (ip == NULL)
		return;
I 33
D 37
#ifdef EFS
	if (efsinode(ip)) {
		dev_t ndev = ip->i_rdev;

		iput(ip);
		efslstat(ndev);
		if (u.u_error != EEXIST)
			return;
		u.u_error = 0;
		u.u_dirp = (caddr_t)u.u_arg[0];
		ip = namei(uchar, 0, 0);
	}
#endif
E 37
E 33
D 24
	stat1(ip, uap->sb, (off_t)0);
E 24
I 24
D 63
	stat1(ip, uap->sb);
E 63
I 63
D 66
	(void) statinode(ip, &sb);
E 66
I 66
	(void) ino_stat(ip, &sb);
E 66
E 63
E 24
	iput(ip);
I 63
	u.u_error = copyout((caddr_t)&sb, (caddr_t)uap->ub, sizeof (sb));
E 63
}

/*
E 23
D 63
 * The basic routine for fstat and stat:
 * get the inode and pass appropriate parts back.
 */
D 15
stat1(ip, ub, pipeadj)
E 15
I 15
stat1(ip, ub)
E 15
D 17
register struct inode *ip;
struct stat *ub;
E 17
I 17
	register struct inode *ip;
	struct stat *ub;
E 17
D 15
off_t pipeadj;
E 15
{
D 28
	register struct dinode *dp;
	register struct buf *bp;
E 28
	struct stat ds;

D 2
	iupdat(ip, &time, &time);
E 2
I 2
D 5
	IUPDAT(ip, &time, &time);
E 5
I 5
D 41
	IUPDAT(ip, &time, &time, 0);
E 41
I 41
D 45
	IUPDAT(ip, &time.tv_sec, &time.tv_sec, 0);
E 45
I 45
D 46
	IUPDAT(ip, time, time, 0);
E 46
I 46
	IUPDAT(ip, &time, &time, 0);
E 46
E 45
E 41
E 5
E 2
	/*
D 17
	 * first copy from inode table
E 17
I 17
D 29
	 * First copy from inode table
E 29
I 29
	 * Copy from inode table
E 29
E 17
	 */
	ds.st_dev = ip->i_dev;
	ds.st_ino = ip->i_number;
	ds.st_mode = ip->i_mode;
	ds.st_nlink = ip->i_nlink;
	ds.st_uid = ip->i_uid;
	ds.st_gid = ip->i_gid;
D 28
	ds.st_rdev = (dev_t)ip->i_un.i_rdev;
E 28
I 28
	ds.st_rdev = (dev_t)ip->i_rdev;
E 28
D 15
	ds.st_size = ip->i_size - pipeadj;
E 15
I 15
	ds.st_size = ip->i_size;
E 15
D 28
	/*
D 17
	 * next the dates in the disk
E 17
I 17
D 23
	 * Next the dates in the disk
E 23
I 23
	 * next the dates in the disk
E 23
E 17
	 */
	bp = bread(ip->i_dev, itod(ip->i_number));
	dp = bp->b_un.b_dino;
	dp += itoo(ip->i_number);
	ds.st_atime = dp->di_atime;
	ds.st_mtime = dp->di_mtime;
	ds.st_ctime = dp->di_ctime;
	brelse(bp);
E 28
I 28
	ds.st_atime = ip->i_atime;
I 50
	ds.st_spare1 = 0;
E 50
	ds.st_mtime = ip->i_mtime;
I 50
	ds.st_spare2 = 0;
E 50
	ds.st_ctime = ip->i_ctime;
I 50
	ds.st_spare3 = 0;
E 50
I 29
D 37
	ds.st_blksize = ip->i_fs->fs_bsize;
E 37
I 37
	/* this doesn't belong here */
	if ((ip->i_mode&IFMT) == IFBLK)
		ds.st_blksize = BLKDEV_IOSIZE;
	else if ((ip->i_mode&IFMT) == IFCHR)
		ds.st_blksize = MAXBSIZE;
	else
		ds.st_blksize = ip->i_fs->fs_bsize;
I 50
D 62
	ds.st_spare4[0] = ds.st_spare4[1] = ds.st_spare4[2] = 0;
E 62
I 62
	ds.st_blocks = ip->i_blocks;
	ds.st_spare4[0] = ds.st_spare4[1] = 0;
E 62
E 50
E 37
E 29
E 28
D 51
	if (copyout((caddr_t)&ds, (caddr_t)ub, sizeof(ds)) < 0)
		u.u_error = EFAULT;
E 51
I 51
	u.u_error = copyout((caddr_t)&ds, (caddr_t)ub, sizeof(ds));
E 51
}

/*
E 63
D 17
 * the dup system call.
E 17
I 17
D 23
 * Dup system call.
E 23
I 23
 * Return target name of a symbolic link
E 23
E 17
 */
I 23
readlink()
{
	register struct inode *ip;
	register struct a {
		char	*name;
		char	*buf;
		int	count;
D 39
	} *uap;
E 39
I 39
	} *uap = (struct a *)u.u_ap;
I 82
	register struct nameidata *ndp = &u.u_nd;
E 82
	int resid;
E 39

D 47
	ip = namei(uchar, 0, 0);
E 47
I 47
D 82
	ip = namei(uchar, LOOKUP, 0);
E 82
I 82
	ndp->ni_nameiop = LOOKUP;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->name;
	ip = namei(ndp);
E 82
E 47
	if (ip == NULL)
		return;
I 33
D 37
#ifdef EFS
	if (efsinode(ip)) {
		dev_t ndev = ip->i_rdev;

		iput(ip);
		efsreadlink(ndev);
		if (u.u_error != EEXIST)
			return;
		u.u_error = 0;
		u.u_dirp = (caddr_t)u.u_arg[0];
		ip = namei(uchar, 0, 0);
		return (0);
	}
#endif
E 37
E 33
	if ((ip->i_mode&IFMT) != IFLNK) {
D 89
		u.u_error = ENXIO;
E 89
I 89
		u.u_error = EINVAL;
E 89
		goto out;
	}
D 39
	uap = (struct a *)u.u_ap;
D 38
	u.u_offset = 0;
	u.u_base = uap->buf;
	u.u_count = uap->count;
	u.u_segflg = 0;
	readi(ip);
E 38
I 38
	u.u_error = readip1(ip, uap->buf, uap->count, 0, 0, 0);
E 39
I 39
D 94
	u.u_error = rdwri(UIO_READ, ip, uap->buf, uap->count, 0, 0, &resid);
E 94
I 94
	u.u_error = rdwri(UIO_READ, ip, uap->buf, uap->count, (off_t)0, 0,
	    &resid);
E 94
E 39
E 38
out:
	iput(ip);
D 39
	u.u_r.r_val1 = uap->count - u.u_count;
E 39
I 39
	u.u_r.r_val1 = uap->count - resid;
E 39
}

I 47
/*
 * Change mode of a file given path name.
 */
E 47
D 26
/*
 * symlink -- make a symbolic link
 */
symlink()
E 26
I 26
chmod()
E 26
{
I 26
D 37
	register struct inode *ip;
E 26
	register struct a {
E 37
I 37
	struct inode *ip;
	struct a {
E 37
D 26
		char	*target;
		char	*linkname;
E 26
I 26
		char	*fname;
		int	fmode;
E 26
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
E 82
D 26
	register struct inode *ip;
	register char *tp;
	register c, nc;
E 26

D 82
	uap = (struct a *)u.u_ap;
D 26
	tp = uap->target;
	nc = 0;
	while (c = fubyte(tp)) {
		if (c < 0) {
			u.u_error = EFAULT;
			return;
		}
		tp++;
		nc++;
	}
	u.u_dirp = uap->linkname;
	ip = namei(uchar, 1, 0);
	if (ip) {
		iput(ip);
		u.u_error = EEXIST;
E 26
I 26
	if ((ip = owner(1)) == NULL)
E 82
I 82
	if ((ip = owner(uap->fname, FOLLOW)) == NULL)
E 82
E 26
		return;
I 33
D 37
#ifdef EFS
	if (efsinode(ip)) {
		dev_t ndev = ip->i_rdev;
E 37
I 37
D 89
	chmod1(ip, uap->fmode);
E 89
I 89
	u.u_error = chmod1(ip, uap->fmode);
E 89
I 47
	iput(ip);
E 47
}
E 37

I 47
/*
 * Change mode of a file given a file descriptor.
 */
E 47
D 37
		iput(ip);
		efschmod(ndev);
		if (u.u_error != EEXIST)
			return;
		u.u_error = 0;
		u.u_dirp = (caddr_t)u.u_arg[0];
		ip = owner(1);
E 37
I 37
fchmod()
{
	struct a {
		int	fd;
		int	fmode;
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
E 82
	register struct inode *ip;
	register struct file *fp;

D 82
	uap = (struct a *)u.u_ap;
E 82
D 63
	fp = getf(uap->fd);
E 63
I 63
	fp = getinode(uap->fd);
E 63
	if (fp == NULL)
		return;
D 63
	if (fp->f_type == DTYPE_SOCKET) {
		u.u_error = EINVAL;
		return;
E 37
	}
D 37
#endif
E 37
I 37
	ip = fp->f_inode;
E 63
I 63
	ip = (struct inode *)fp->f_data;
E 63
D 47
	ilock(ip);
	if (u.u_uid != ip->i_uid && !suser()) {
		iunlock(ip);
E 47
I 47
D 101
	if (u.u_uid != ip->i_uid && !suser())
E 101
I 101
	if (u.u_uid != ip->i_uid &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 101
E 47
		return;
D 47
	}
E 47
I 47
D 81
	ilock(ip);
E 81
I 81
	ILOCK(ip);
E 81
E 47
D 89
	chmod1(ip, uap->fmode);
E 89
I 89
	u.u_error = chmod1(ip, uap->fmode);
E 89
I 47
D 81
	iunlock(ip);
E 81
I 81
	IUNLOCK(ip);
E 81
E 47
}

I 47
/*
E 102
 * Change the mode on a file.
 * Inode must be locked before calling.
 */
E 47
D 102
chmod1(ip, mode)
	register struct inode *ip;
E 102
I 102
D 153
chmod1(vp, mode, cred)
E 153
I 153
chmod1(vp, mode, p)
E 153
	register struct vnode *vp;
E 102
	register int mode;
I 102
D 153
	struct ucred *cred;
E 153
I 153
	struct proc *p;
E 153
E 102
{
I 153
	register struct ucred *cred = p->p_ucred;
E 153
I 102
	register struct inode *ip = VTOI(vp);
I 104
	int error;
E 104
E 102
I 40
D 63
	register int *gp;
E 63

I 104
	if (cred->cr_uid != ip->i_uid &&
D 153
	    (error = suser(cred, &u.u_acflag)))
E 153
I 153
	    (error = suser(cred, &p->p_acflag)))
E 153
		return (error);
E 104
I 89
D 102
	if (ip->i_fs->fs_ronly)
		return (EROFS);
E 102
E 89
E 40
E 37
E 33
D 26
	}
I 25
	if (u.u_error)
		return;
E 25
	ip = maknode(IFLNK | 0777);
	if (ip == NULL)
		return;
	u.u_base = uap->target;
	u.u_count = nc;
	u.u_offset = 0;
	u.u_segflg = 0;
	writei(ip);
E 26
I 26
D 143
	ip->i_mode &= ~07777;
E 143
D 33
	if (u.u_uid)
E 33
I 33
D 102
	if (u.u_uid) {
E 33
D 37
		uap->fmode &= ~ISVTX;
E 37
I 37
D 89
		mode &= ~ISVTX;
E 89
I 89
		if ((ip->i_mode & IFMT) != IFDIR)
E 102
I 102
	if (cred->cr_uid) {
D 143
		if (vp->v_type != VDIR)
E 102
			mode &= ~ISVTX;
E 89
I 57
D 60
		if (u.u_gid == ip->i_gid)
			goto ok;
E 57
E 37
I 33
D 40
		if (ip->i_gid >= NGRPS ||
		    (u.u_grps[ip->i_gid/(sizeof(int)*8)] &
		     (1 << ip->i_gid%(sizeof(int)*8))) == 0)
D 37
			uap->fmode &= ~ISGID;
I 34
#if	MUSH
E 37
I 37
			mode &= ~ISGID;
E 40
I 40
		for (gp = u.u_groups; gp < &u.u_groups[NGROUPS]; gp++)
			if (*gp == ip->i_gid)
				goto ok;
		mode &= ~ISGID;
ok:
		;
E 60
I 60
D 102
		if (!groupmember(ip->i_gid))
E 102
I 102
		if (!groupmember(ip->i_gid, cred))
E 102
			mode &= ~ISGID;
E 143
I 143
D 144
		if (vp->v_type != VDIR && mode & ISVTX)
E 144
I 144
		if (vp->v_type != VDIR && (mode & ISVTX))
E 144
			return (EFTYPE);
D 144
		if (!groupmember(ip->i_gid, cred) && mode & ISGID)
E 144
I 144
		if (!groupmember(ip->i_gid, cred) && (mode & ISGID))
E 144
			return (EPERM);
E 143
E 60
E 40
D 62
#ifdef MUSH
E 37
D 60
		if (u.u_quota->q_syflags & QF_UMASK && u.u_uid != 0 &&
E 60
I 60
		if (u.u_quota->q_syflags & QF_UMASK && 
E 60
		    (ip->i_mode & IFMT) != IFCHR)
D 37
			uap->fmode &= ~u.u_cmask;
E 37
I 37
			mode &= ~u.u_cmask;
E 37
#endif
E 62
E 34
	}
I 143
	ip->i_mode &= ~07777;
E 143
E 33
D 37
	ip->i_mode |= uap->fmode&07777;
E 37
I 37
D 102
	ip->i_mode |= mode&07777;
E 102
I 102
	ip->i_mode |= mode & 07777;
E 102
E 37
	ip->i_flag |= ICHG;
D 102
	if (ip->i_flag&ITEXT && (ip->i_mode&ISVTX)==0)
		xrele(ip);
E 102
I 102
	if ((vp->v_flag & VTEXT) && (ip->i_mode & ISVTX) == 0)
D 142
		xrele(vp);
E 142
I 142
		(void) vnode_pager_uncache(vp);
E 142
E 102
I 89
	return (0);
E 89
I 34
D 37
#ifdef MELB
	if ((ip->i_mode & ISUID) && ip->i_uid == 0)
		printf("%s: ino %d (%s) setuid root\n"
		    , getfs(ip->i_dev)->s_fsmnt
		    , ip->i_number
		    , u.u_dent.d_name
		);
#endif
E 37
E 34
E 26
D 47
	iput(ip);
E 47
}

I 47
/*
D 102
 * Set ownership given a path name.
 */
E 47
D 26
/*
 * the dup system call.
 */
E 23
dup()
E 26
I 26
chown()
E 26
{
D 26
	register struct file *fp;
E 26
I 26
D 37
	register struct inode *ip;
E 26
	register struct a {
E 37
I 37
	struct inode *ip;
	struct a {
E 37
D 26
		int	fdes;
		int	fdes2;
E 26
I 26
		char	*fname;
		int	uid;
		int	gid;
E 26
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
I 99
	register struct nameidata *ndp = &u.u_nd;
E 99
E 82
I 34
D 37
#if	QUOTA
	register long change;
#endif
E 37
E 34
D 26
	register i, m;
E 26

D 82
	uap = (struct a *)u.u_ap;
D 26
	m = uap->fdes & ~077;
	uap->fdes &= 077;
	fp = getf(uap->fdes);
D 17
	if(fp == NULL)
E 17
I 17
	if (fp == NULL)
E 26
I 26
D 60
	if (!suser() || (ip = owner(0)) == NULL)
E 60
I 60
D 61
	if ((ip = owner(0)) == NULL)
E 61
I 61
	if (!suser() || (ip = owner(0)) == NULL)
E 82
I 82
D 95
	if (!suser() || (ip = owner(uap->fname, NOFOLLOW)) == NULL)
E 95
I 95
D 99
	if ((ip = owner(uap->fname, NOFOLLOW)) == NULL)
E 99
I 99
	ndp->ni_nameiop = LOOKUP | NOFOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
	ip = namei(ndp);
	if (ip == NULL)
E 99
E 95
E 82
E 61
E 60
E 26
E 17
		return;
D 26
	if ((m&0100) == 0) {
		if ((i = ufalloc()) < 0)
			return;
	} else {
		i = uap->fdes2;
		if (i<0 || i>=NOFILE) {
			u.u_error = EBADF;
			return;
		}
D 17
		if (u.u_vrpages[i]) {
			u.u_error = ETXTBSY;
			return;
		}
E 17
		u.u_r.r_val1 = i;
	}
D 17
	if (i!=uap->fdes) {
E 17
I 17
	if (i != uap->fdes) {
E 17
		if (u.u_ofile[i]!=NULL)
D 22
			closef(u.u_ofile[i]);
E 22
I 22
			closef(u.u_ofile[i], 0);
		if (u.u_error)
			return;
E 22
		u.u_ofile[i] = fp;
		fp->f_count++;
	}
E 26
I 26
D 33
	ip->i_uid = uap->uid;
	ip->i_gid = uap->gid;
E 33
I 33
D 37
#ifdef EFS
	if (efsinode(ip)) {
		dev_t ndev = ip->i_rdev;
E 37
I 37
D 60
	chown1(ip, uap->uid, uap->gid);
E 60
I 60
	u.u_error = chown1(ip, uap->uid, uap->gid);
E 60
I 47
	iput(ip);
E 47
}
E 37

I 47
/*
 * Set ownership given a file descriptor.
 */
E 47
D 37
		iput(ip);
		efschown(ndev);
		if (u.u_error != EEXIST)
			return;
		u.u_error = 0;
		u.u_dirp = (caddr_t)u.u_arg[0];
		ip = owner(0);
E 37
I 37
fchown()
{
	struct a {
		int	fd;
		int	uid;
		int	gid;
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
E 82
	register struct inode *ip;
	register struct file *fp;

D 82
	uap = (struct a *)u.u_ap;
E 82
D 63
	fp = getf(uap->fd);
E 63
I 63
	fp = getinode(uap->fd);
E 63
	if (fp == NULL)
		return;
D 63
	if (fp->f_type == DTYPE_SOCKET) {
		u.u_error = EINVAL;
		return;
E 37
	}
D 37
#endif
I 34
#if	QUOTA
E 37
I 37
	ip = fp->f_inode;
E 63
I 63
	ip = (struct inode *)fp->f_data;
E 63
D 47
	ilock(ip);
	if (!suser()) {
		iunlock(ip);
E 47
I 47
D 60
	if (!suser())
E 60
I 60
D 61
	if (ip->i_uid != u.u_uid && !suser())
E 61
I 61
D 95
	if (!suser())
E 61
E 60
E 47
		return;
E 95
D 47
	}
E 47
I 47
D 81
	ilock(ip);
E 81
I 81
	ILOCK(ip);
E 81
E 47
D 60
	chown1(ip, uap->uid, uap->gid);
E 60
I 60
	u.u_error = chown1(ip, uap->uid, uap->gid);
E 60
I 47
D 81
	iunlock(ip);
E 81
I 81
	IUNLOCK(ip);
E 81
E 47
}

/*
E 102
 * Perform chown operation on inode ip;
 * inode must be locked prior to call.
 */
D 102
chown1(ip, uid, gid)
	register struct inode *ip;
	int uid, gid;
E 102
I 102
D 153
chown1(vp, uid, gid, cred)
E 153
I 153
chown1(vp, uid, gid, p)
E 153
	register struct vnode *vp;
	uid_t uid;
	gid_t gid;
D 153
	struct ucred *cred;
E 153
I 153
	struct proc *p;
E 153
E 102
{
I 102
	register struct inode *ip = VTOI(vp);
I 153
	register struct ucred *cred = p->p_ucred;
E 153
I 131
	uid_t ouid;
	gid_t ogid;
	int error = 0;
E 131
E 102
#ifdef QUOTA
D 131
	register long change;
E 131
I 131
	register int i;
	long change;
E 131
I 60
#endif
I 102
D 131
	int error;
E 131
E 102
E 60

I 89
D 102
	if (ip->i_fs->fs_ronly)
		return (EROFS);
E 89
I 60
	if (uid == -1)
E 102
I 102
	if (uid == (u_short)VNOVAL)
E 102
		uid = ip->i_uid;
D 102
	if (gid == -1)
E 102
I 102
	if (gid == (u_short)VNOVAL)
E 102
		gid = ip->i_gid;
I 95
D 99
	if (uid != ip->i_uid && !suser())
		return (u.u_error);
	if (gid != ip->i_gid && !groupmember((gid_t)gid) && !suser())
E 99
I 99
	/*
	 * If we don't own the file, are trying to change the owner
	 * of the file, or are not a member of the target group,
	 * the caller must be superuser or the call fails.
	 */
D 102
	if ((u.u_uid != ip->i_uid || uid != ip->i_uid ||
D 101
	    !groupmember((gid_t)gid)) && !suser())
E 101
I 101
	    !groupmember((gid_t)gid)) &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 101
E 99
		return (u.u_error);
E 102
I 102
	if ((cred->cr_uid != ip->i_uid || uid != ip->i_uid ||
	    !groupmember((gid_t)gid, cred)) &&
D 153
	    (error = suser(cred, &u.u_acflag)))
E 153
I 153
	    (error = suser(cred, &p->p_acflag)))
E 153
		return (error);
I 131
	ouid = ip->i_uid;
	ogid = ip->i_gid;
E 131
E 102
E 95
D 61
	if (u.u_uid && ip->i_gid != gid && !groupmember(gid))
		return (EPERM);
E 61
#ifdef QUOTA
E 60
E 37
E 34
D 62
	/*
I 34
	 * This doesn't allow for holes in files (which hopefully don't
	 * happen often in files that we chown), and is not accurate anyway
	 * (eg: it totally ignores 3 level indir blk files - but hopefully
	 * noone who can make a file that big will have a quota)
	 */
D 37
	if (ip->i_uid == uap->uid)
E 37
I 37
	if (ip->i_uid == uid)
E 62
I 62
D 70
	if (ip->i_uid != uid)		/* this just speeds things a little */
E 70
I 70
D 131
	if (ip->i_uid == uid)		/* this just speeds things a little */
E 70
E 62
E 37
		change = 0;
D 62
	else {
		register struct fs *fs = ip->i_fs;

		if (ip->i_size > (change = NDADDR * fs->fs_bsize)) {
			register off_t size;

			size = blkroundup(fs, ip->i_size) - change;
			change += size;
			change += fs->fs_bsize;
D 37
			/* This assumes NIADDR <= 2 */
E 37
I 37
			/* this assumes NIADDR <= 2 */
E 37
			if (size > NINDIR(fs) * fs->fs_bsize)
				change += fs->fs_bsize;
		} else
			change = fragroundup(fs, ip->i_size);
		change /= DEV_BSIZE;
	}
D 47
	chkdq(ip, -change, 1);
	chkiq(ip->i_dev, ip, ip->i_uid, 1);
E 47
I 47
	(void)chkdq(ip, -change, 1);
	(void)chkiq(ip->i_dev, ip, ip->i_uid, 1);
E 62
I 62
	else
		change = ip->i_blocks;
	(void) chkdq(ip, -change, 1);
	(void) chkiq(ip->i_dev, ip, ip->i_uid, 1);
E 62
E 47
	dqrele(ip->i_dquot);
E 131
I 131
	if (error = getinoquota(ip))
		return (error);
	if (ouid == uid) {
		dqrele(vp, ip->i_dquot[USRQUOTA]);
		ip->i_dquot[USRQUOTA] = NODQUOT;
	}
	if (ogid == gid) {
		dqrele(vp, ip->i_dquot[GRPQUOTA]);
		ip->i_dquot[GRPQUOTA] = NODQUOT;
	}
	change = ip->i_blocks;
	(void) chkdq(ip, -change, cred, CHOWN);
	(void) chkiq(ip, -1, cred, CHOWN);
	for (i = 0; i < MAXQUOTAS; i++) {
		dqrele(vp, ip->i_dquot[i]);
		ip->i_dquot[i] = NODQUOT;
	}
E 131
#endif
I 113
D 131
	if (ip->i_uid != uid && cred->cr_uid != 0)
		ip->i_mode &= ~ISUID;
	if (ip->i_gid != gid && cred->cr_uid != 0)
		ip->i_mode &= ~ISGID;
E 131
E 113
D 60
	/*
E 34
D 37
	 * keep uid/gid's in sane range - no err, so chown(file, uid, -1)
	 * will do something useful
E 37
I 37
	 * keep uid/gid's in sane range -- no err,
	 * so chown(file, uid, -1) will do something useful
E 37
	 */
D 37
	if (uap->uid >= 0 && uap->uid <= 32767)	/* should have a const	*/
		ip->i_uid = uap->uid;
	if (uap->gid >= 0 && uap->gid <= 32767)	/* same here		*/
		ip->i_gid = uap->gid;
E 37
I 37
	if (uid >= 0 && uid <= 32767)	/* should have a constant */
		ip->i_uid = uid;
	if (gid >= 0 && gid <= 32767)	/* same here */
		ip->i_gid = gid;
E 60
I 60
	ip->i_uid = uid;
	ip->i_gid = gid;
E 60
E 37
E 33
D 131
	ip->i_flag |= ICHG;
E 131
D 102
	if (u.u_ruid != 0)
E 102
I 102
D 111
	if (cred->cr_ruid != 0)
E 102
		ip->i_mode &= ~(ISUID|ISGID);
E 111
I 111
D 113
	ip->i_mode &= ~(ISUID|ISGID);
E 113
E 111
I 34
D 37
#if	QUOTA
E 37
I 37
#ifdef QUOTA
E 37
D 131
	ip->i_dquot = inoquota(ip);
D 47
	chkdq(ip, change, 1);
D 37
	chkiq(ip->i_dev, NULL, uap->uid, 1);
E 37
I 37
	chkiq(ip->i_dev, NULL, uid, 1);
E 47
I 47
D 62
	(void)chkdq(ip, change, 1);
	(void)chkiq(ip->i_dev, (struct inode *)NULL, uid, 1);
I 60
	return (u.u_error);
E 60
E 47
E 37
#endif
E 62
I 62
	(void) chkdq(ip, change, 1);
D 94
	(void) chkiq(ip->i_dev, (struct inode *)NULL, uid, 1);
E 94
I 94
	(void) chkiq(ip->i_dev, (struct inode *)NULL, (uid_t)uid, 1);
E 94
	return (u.u_error);		/* should == 0 ALWAYS !! */
#else
E 62
I 60
	return (0);
E 131
I 131
	if ((error = getinoquota(ip)) == 0) {
		if (ouid == uid) {
			dqrele(vp, ip->i_dquot[USRQUOTA]);
			ip->i_dquot[USRQUOTA] = NODQUOT;
		}
		if (ogid == gid) {
			dqrele(vp, ip->i_dquot[GRPQUOTA]);
			ip->i_dquot[GRPQUOTA] = NODQUOT;
		}
		if ((error = chkdq(ip, change, cred, CHOWN)) == 0) {
			if ((error = chkiq(ip, 1, cred, CHOWN)) == 0)
D 135
				return (0);
E 135
I 135
				goto good;
E 135
			else
				(void) chkdq(ip, -change, cred, CHOWN|FORCE);
		}
		for (i = 0; i < MAXQUOTAS; i++) {
			dqrele(vp, ip->i_dquot[i]);
			ip->i_dquot[i] = NODQUOT;
		}
	}
	ip->i_uid = ouid;
	ip->i_gid = ogid;
	if (getinoquota(ip) == 0) {
		if (ouid == uid) {
			dqrele(vp, ip->i_dquot[USRQUOTA]);
			ip->i_dquot[USRQUOTA] = NODQUOT;
		}
		if (ogid == gid) {
			dqrele(vp, ip->i_dquot[GRPQUOTA]);
			ip->i_dquot[GRPQUOTA] = NODQUOT;
		}
D 135
		(void) chkdq(ip, change, cred, FORCE);
		(void) chkiq(ip, 1, cred, FORCE);
E 135
I 135
		(void) chkdq(ip, change, cred, FORCE|CHOWN);
		(void) chkiq(ip, 1, cred, FORCE|CHOWN);
I 136
		(void) getinoquota(ip);
E 136
E 135
	}
D 136
	if (error)
		return (error);
E 136
I 136
	return (error);
E 136
I 135
good:
E 135
E 131
I 62
D 136
#endif
E 136
I 136
	if (getinoquota(ip))
		panic("chown: lost quota");
#endif /* QUOTA */
E 136
I 131
	if (ouid != uid || ogid != gid)
		ip->i_flag |= ICHG;
	if (ouid != uid && cred->cr_uid != 0)
		ip->i_mode &= ~ISUID;
	if (ogid != gid && cred->cr_uid != 0)
		ip->i_mode &= ~ISGID;
	return (0);
E 131
E 62
E 60
E 34
D 47
	iput(ip);
E 47
E 26
}

I 117
/*
E 161
 * Vnode op for reading.
 */
E 117
I 60
D 65
#ifndef NOCOMPAT
E 60
/*
D 17
 * the mount system call.
E 17
I 17
D 26
 * Mount system call.
E 26
I 26
 * Set IUPD and IACC times on file.
 * Can't set ICHG.
E 26
E 17
 */
D 13
smount()
{
E 13
I 13
D 17
smount() {
E 17
I 17
D 26
smount()
E 26
I 26
D 42
utime()
E 42
I 42
outime()
E 42
E 26
{
E 17
E 13
D 26
	dev_t dev;
	register struct inode *ip;
	register struct mount *mp;
	struct mount *smp;
	register struct filsys *fp;
	struct buf *bp;
E 26
	register struct a {
D 26
		char	*fspec;
		char	*freg;
		int	ronly;
E 26
I 26
		char	*fname;
		time_t	*tptr;
E 26
D 60
	} *uap;
E 60
I 60
	} *uap = (struct a *)u.u_ap;
E 60
I 13
D 26
	register char *cp;
E 26
I 26
	register struct inode *ip;
	time_t tv[2];
I 45
	struct timeval tv0, tv1;
E 45
E 26
E 13

D 60
	uap = (struct a *)u.u_ap;
E 60
D 26
	dev = getmdev();
D 17
	if(u.u_error)
E 17
I 17
	if (u.u_error)
E 26
I 26
	if ((ip = owner(1)) == NULL)
E 26
E 17
		return;
D 26
	u.u_dirp = (caddr_t)uap->freg;
D 23
	ip = namei(uchar, 0);
E 23
I 23
	ip = namei(uchar, 0, 1);
E 23
D 17
	if(ip == NULL)
E 17
I 17
	if (ip == NULL)
E 17
		return;
D 17
	if(ip->i_count!=1 || (ip->i_mode&(IFBLK&IFCHR))!=0)
E 17
I 17
	if (ip->i_count!=1 || (ip->i_mode&IFMT) != IFDIR)
E 17
		goto out;
	smp = NULL;
D 17
	for(mp = &mount[0]; mp < &mount[NMOUNT]; mp++) {
		if(mp->m_bufp != NULL) {
			if(dev == mp->m_dev)
E 17
I 17
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++) {
		if (mp->m_bufp != NULL) {
			if (dev == mp->m_dev)
E 17
				goto out;
		} else
D 17
		if(smp == NULL)
E 17
I 17
		if (smp == NULL)
E 17
			smp = mp;
E 26
I 26
D 51
	if (copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof(tv))) {
		u.u_error = EFAULT;
	} else {
E 51
I 51
D 60
	u.u_error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof(tv));
E 60
I 60
	u.u_error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv));
E 60
	if (u.u_error == 0) {
E 51
I 33
D 37
#ifdef EFS
		if (efsinode(ip)) {
			dev_t ndev = ip->i_rdev;

			iput(ip);
			efsutime(ndev, uap->fname, tv);
			if (u.u_error != EEXIST)
				return;
			u.u_error = 0;
			u.u_dirp = (caddr_t)u.u_arg[0];
			ip = owner(1);
		}
#endif
E 37
E 33
		ip->i_flag |= IACC|IUPD|ICHG;
D 45
		iupdat(ip, &tv[0], &tv[1], 0);
E 45
I 45
		tv0.tv_sec = tv[0]; tv0.tv_usec = 0;
		tv1.tv_sec = tv[1]; tv1.tv_usec = 0;
		iupdat(ip, &tv0, &tv1, 0);
E 45
E 26
	}
D 26
	mp = smp;
D 17
	if(mp == NULL)
E 17
I 17
	if (mp == NULL)
E 17
		goto out;
	(*bdevsw[major(dev)].d_open)(dev, !uap->ronly);
D 17
	if(u.u_error)
E 17
I 17
	if (u.u_error)
E 17
		goto out;
	bp = bread(dev, SUPERB);
D 17
	if(u.u_error) {
E 17
I 17
	if (u.u_error) {
E 17
		brelse(bp);
		goto out1;
	}
	mp->m_inodp = ip;
	mp->m_dev = dev;
D 9
	mp->m_bufp = geteblk();
	bcopy((caddr_t)bp->b_un.b_addr, mp->m_bufp->b_un.b_addr, BSIZE);
	fp = mp->m_bufp->b_un.b_filsys;
E 9
I 9
	bp->b_flags |= B_LOCKED;
	mp->m_bufp = bp;
	fp = bp->b_un.b_filsys;
E 9
	fp->s_ilock = 0;
	fp->s_flock = 0;
	fp->s_ronly = uap->ronly & 1;
	fp->s_nbehind = 0;
	fp->s_lasti = 1;
I 13
	u.u_dirp = uap->freg;
	for (cp = fp->s_fsmnt; cp < &fp->s_fsmnt[sizeof (fp->s_fsmnt) - 1]; )
		if ((*cp++ = uchar()) == 0)
			u.u_dirp--;		/* get 0 again */
	*cp = 0;
E 13
	brelse(bp);
	ip->i_flag |= IMOUNT;
D 17
	prele(ip);
E 17
I 17
	irele(ip);
E 17
	return;

out:
	u.u_error = EBUSY;
out1:
E 26
	iput(ip);
}
I 60
#endif
E 60

E 65
I 60
D 102
utimes()
E 102
I 102
/* ARGSUSED */
I 117
D 161
ufs_read(vp, uio, ioflag, cred)
E 161
I 161
D 184
ffs_read(vp, uio, ioflag, cred)
E 161
	struct vnode *vp;
	register struct uio *uio;
	int ioflag;
	struct ucred *cred;
E 184
I 184
D 188
ffs_read (ap)
E 188
I 188
ffs_read(ap)
E 188
D 193
	struct vop_read_args *ap;
E 193
I 193
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 193
D 186
#define vp (ap->a_vp)
#define uio (ap->a_uio)
#define ioflag (ap->a_ioflag)
#define cred (ap->a_cred)
E 186
E 184
{
D 186
	register struct inode *ip = VTOI(vp);
E 186
I 186
D 188
	register struct inode *ip = VTOI(ap->a_vp);
E 188
I 188
	register struct vnode *vp = ap->a_vp;
	register struct inode *ip = VTOI(vp);
	register struct uio *uio = ap->a_uio;
E 188
E 186
	register struct fs *fs;
	struct buf *bp;
	daddr_t lbn, bn, rablock;
D 122
	int size, rasize, diff, error = 0;
E 122
I 122
D 164
	int size, diff, error = 0;
E 164
I 164
D 167
	int size, rasize, diff, error = 0;
E 164
E 122
	long n, on, type;
E 167
I 167
	off_t diff;
D 168
	int error = 0;
	long size, rasize, n, on;
E 168
I 168
D 204
	int rasize, error = 0;
E 204
I 204
	int type, rasize, error = 0;
E 204
	long size, n, on;
E 214
I 214
#include <ufs/ufs/ufs_readwrite.c>
E 214
E 168
E 167

I 204
D 214
	type = ip->i_mode & IFMT;
E 204
I 155
#ifdef DIAGNOSTIC
I 167
D 204
	int type;
E 204
E 167
E 155
D 186
	if (uio->uio_rw != UIO_READ)
E 186
I 186
D 188
	if (ap->a_uio->uio_rw != UIO_READ)
E 188
I 188
	if (uio->uio_rw != UIO_READ)
E 188
E 186
D 161
		panic("ufs_read mode");
E 161
I 161
		panic("ffs_read mode");
E 161
D 204
	type = ip->i_mode & IFMT;
E 204
	if (type != IFDIR && type != IFREG && type != IFLNK)
D 161
		panic("ufs_read type");
E 161
I 161
		panic("ffs_read type");
I 192
D 200
	if (type == IFLNK && ip->i_size < vp->v_mount->mnt_maxsymlinklen)
E 200
I 200
	if (type == IFLNK && (int)ip->i_size < vp->v_mount->mnt_maxsymlinklen)
E 200
		panic("read short symlink");
E 192
E 161
I 155
#endif
E 155
D 186
	if (uio->uio_resid == 0)
E 186
I 186
D 188
	if (ap->a_uio->uio_resid == 0)
E 188
I 188
	if (uio->uio_resid == 0)
E 188
E 186
		return (0);
D 186
	if (uio->uio_offset < 0)
E 186
I 186
D 188
	if (ap->a_uio->uio_offset < 0)
E 188
I 188
	fs = ip->i_fs;
I 196
	if ((u_quad_t)uio->uio_offset > fs->fs_maxfilesize)
		return (EFBIG);
E 196
D 189
	if (uio->uio_offset < 0)
E 188
E 186
		return (EINVAL);
E 189
I 189
D 192
	if (uio->uio_offset + uio->uio_resid > fs->fs_maxfilesize)
		return (EFBIG);
E 192
E 189
	ip->i_flag |= IACC;
D 188
	fs = ip->i_fs;
E 188
	do {
D 186
		lbn = lblkno(fs, uio->uio_offset);
		on = blkoff(fs, uio->uio_offset);
		n = MIN((unsigned)(fs->fs_bsize - on), uio->uio_resid);
		diff = ip->i_size - uio->uio_offset;
E 186
I 186
D 188
		lbn = lblkno(fs, ap->a_uio->uio_offset);
		on = blkoff(fs, ap->a_uio->uio_offset);
		n = MIN((unsigned)(fs->fs_bsize - on), ap->a_uio->uio_resid);
		diff = ip->i_size - ap->a_uio->uio_offset;
E 188
I 188
		lbn = lblkno(fs, uio->uio_offset);
		on = blkoff(fs, uio->uio_offset);
D 198
		n = MIN((unsigned)(fs->fs_bsize - on), uio->uio_resid);
E 198
I 198
		n = min((unsigned)(fs->fs_bsize - on), uio->uio_resid);
E 198
		diff = ip->i_size - uio->uio_offset;
E 188
E 186
		if (diff <= 0)
			return (0);
		if (diff < n)
			n = diff;
D 120
		if (error = bmap(ip, lbn, &bn, &rablock, &rasize))
			return (error);
E 120
		size = blksize(fs, ip, lbn);
D 120
		if ((long)bn < 0) {
			bp = geteblk(size);
			clrbuf(bp);
		} else if (ip->i_lastr + 1 == lbn)
			error = breada(ip->i_devvp, bn, size, rablock, rasize,
E 120
I 120
D 207
		rablock = lbn + 1;
D 122
		rasize = blksize(fs, ip, rablock);
D 121
		if (ip->i_lastr + 1 == lbn)
E 121
I 121
		if (vp->v_lastr + 1 == lbn)
E 121
			error = breada(ITOV(ip), lbn, size, rablock, rasize,
E 120
				NOCRED, &bp);
E 122
I 122
D 186
		if (vp->v_lastr + 1 == lbn &&
E 186
I 186
D 188
		if (ap->a_vp->v_lastr + 1 == lbn &&
E 188
I 188
		if (vp->v_lastr + 1 == lbn &&
E 188
E 186
D 164
		    lblktosize(fs, rablock) < ip->i_size)
			error = breada(ITOV(ip), lbn, size, rablock,
				blksize(fs, ip, rablock), NOCRED, &bp);
E 122
		else
E 164
I 164
		    lblktosize(fs, rablock) < ip->i_size) {
			rasize = blksize(fs, ip, rablock);
D 166
			error = breadn(ITOV(ip), lbn, size, &rablock,
E 166
I 166
D 186
			error = breadn(vp, lbn, size, &rablock,
E 186
I 186
D 188
			error = breadn(ap->a_vp, lbn, size, &rablock,
E 188
I 188
			error = breadn(vp, lbn, size, &rablock,
E 188
E 186
E 166
				&rasize, 1, NOCRED, &bp);
		} else
E 207
I 207
D 208
		if (lblktosize(fs, (lbn + 1)) <= ip->i_size)
E 208
I 208
		rablock = lbn + 1;
		if (doclusterread && lblktosize(fs, rablock) <= ip->i_size) {
E 208
			error = cluster_read(vp, ip->i_size, lbn, size,
			    NOCRED, &bp);
D 208
		else
E 208
I 208
		} else if (vp->v_lastr + 1 == lbn &&
		    lblktosize(fs, rablock) < ip->i_size) {
			rasize = blksize(fs, ip, rablock);
			error = breadn(vp, lbn, size, &rablock,
				&rasize, 1, NOCRED, &bp);
		} else
E 208
E 207
E 164
D 120
			error = bread(ip->i_devvp, bn, size, NOCRED, &bp);
E 120
I 120
D 166
			error = bread(ITOV(ip), lbn, size, NOCRED, &bp);
E 166
I 166
D 186
			error = bread(vp, lbn, size, NOCRED, &bp);
E 166
E 120
D 121
		ip->i_lastr = lbn;
E 121
I 121
		vp->v_lastr = lbn;
E 186
I 186
D 188
			error = bread(ap->a_vp, lbn, size, NOCRED, &bp);
		ap->a_vp->v_lastr = lbn;
E 188
I 188
			error = bread(vp, lbn, size, NOCRED, &bp);
		vp->v_lastr = lbn;
E 188
E 186
E 121
D 198
		n = MIN(n, size - bp->b_resid);
E 198
I 198
		n = min(n, size - bp->b_resid);
E 198
		if (error) {
			brelse(bp);
			return (error);
		}
D 186
		error = uiomove(bp->b_un.b_addr + on, (int)n, uio);
		if (n + on == fs->fs_bsize || uio->uio_offset == ip->i_size)
E 186
I 186
D 188
		error = uiomove(bp->b_un.b_addr + on, (int)n, ap->a_uio);
		if (n + on == fs->fs_bsize || ap->a_uio->uio_offset == ip->i_size)
E 188
I 188
		error = uiomove(bp->b_un.b_addr + on, (int)n, uio);
D 204
		if (n + on == fs->fs_bsize || uio->uio_offset == ip->i_size)
E 204
I 204
		if (type == IFREG &&
		    (n + on == fs->fs_bsize || uio->uio_offset == ip->i_size))
E 204
E 188
E 186
			bp->b_flags |= B_AGE;
		brelse(bp);
D 186
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
E 186
I 186
D 188
	} while (error == 0 && ap->a_uio->uio_resid > 0 && n != 0);
E 188
I 188
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
E 188
E 186
	return (error);
}
I 184
D 186
#undef vp
#undef uio
#undef ioflag
#undef cred
E 186
E 184

E 214
/*
D 214
 * Vnode op for writing.
 */
D 161
ufs_write(vp, uio, ioflag, cred)
E 161
I 161
D 184
ffs_write(vp, uio, ioflag, cred)
E 161
	register struct vnode *vp;
	struct uio *uio;
	int ioflag;
	struct ucred *cred;
E 184
I 184
D 188
ffs_write (ap)
E 188
I 188
ffs_write(ap)
E 188
D 193
	struct vop_write_args *ap;
E 193
I 193
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 193
D 186
#define vp (ap->a_vp)
#define uio (ap->a_uio)
#define ioflag (ap->a_ioflag)
#define cred (ap->a_cred)
E 186
E 184
{
I 184
D 194
	USES_VOP_TRUNCATE;
	USES_VOP_UPDATE;
E 194
I 187
	register struct vnode *vp = ap->a_vp;
E 187
E 184
I 153
D 155
	struct proc *p = curproc;		/* XXX */
E 155
I 155
D 186
	struct proc *p = uio->uio_procp;
E 155
E 153
	register struct inode *ip = VTOI(vp);
E 186
I 186
D 188
	struct proc *p = ap->a_uio->uio_procp;
E 188
I 188
	register struct uio *uio = ap->a_uio;
E 188
D 187
	register struct inode *ip = VTOI(ap->a_vp);
E 187
I 187
	register struct inode *ip = VTOI(vp);
E 187
E 186
	register struct fs *fs;
I 188
	struct proc *p = uio->uio_procp;
	int ioflag = ap->a_ioflag;
I 195
	struct timeval tv;
E 195
E 188
	struct buf *bp;
	daddr_t lbn, bn;
D 169
	u_long osize;
E 169
I 169
	off_t osize;
E 169
D 142
	int i, n, on, flags;
	int count, size, resid, error = 0;
E 142
I 142
	int n, on, flags;
	int size, resid, error = 0;
E 142

I 155
#ifdef DIAGNOSTIC
E 155
D 186
	if (uio->uio_rw != UIO_WRITE)
E 186
I 186
D 188
	if (ap->a_uio->uio_rw != UIO_WRITE)
E 188
I 188
	if (uio->uio_rw != UIO_WRITE)
E 188
E 186
D 161
		panic("ufs_write mode");
E 161
I 161
		panic("ffs_write mode");
E 161
I 155
#endif
E 155
D 186
	switch (vp->v_type) {
E 186
I 186
D 187
	switch (ap->a_vp->v_type) {
E 187
I 187
	switch (vp->v_type) {
E 187
E 186
	case VREG:
D 186
		if (ioflag & IO_APPEND)
			uio->uio_offset = ip->i_size;
E 186
I 186
D 188
		if (ap->a_ioflag & IO_APPEND)
			ap->a_uio->uio_offset = ip->i_size;
E 188
I 188
		if (ioflag & IO_APPEND)
			uio->uio_offset = ip->i_size;
I 209
		if ((ip->i_flags & APPEND) && uio->uio_offset != ip->i_size)
			return (EPERM);
E 209
E 188
E 186
		/* fall through */
	case VLNK:
		break;

	case VDIR:
D 186
		if ((ioflag & IO_SYNC) == 0)
E 186
I 186
D 188
		if ((ap->a_ioflag & IO_SYNC) == 0)
E 188
I 188
		if ((ioflag & IO_SYNC) == 0)
E 188
E 186
D 161
			panic("ufs_write nonsync dir write");
E 161
I 161
			panic("ffs_write nonsync dir write");
E 161
		break;

	default:
D 161
		panic("ufs_write type");
E 161
I 161
		panic("ffs_write type");
E 161
	}
D 186
	if (uio->uio_offset < 0)
E 186
I 186
D 188
	if (ap->a_uio->uio_offset < 0)
E 188
I 188
D 189
	if (uio->uio_offset < 0)
E 188
E 186
		return (EINVAL);
E 189
D 186
	if (uio->uio_resid == 0)
E 186
I 186
D 188
	if (ap->a_uio->uio_resid == 0)
E 188
I 188
	if (uio->uio_resid == 0)
E 188
E 186
		return (0);
I 189
	fs = ip->i_fs;
D 199
	if (uio->uio_offset + uio->uio_resid > fs->fs_maxfilesize)
E 199
I 199
	if (uio->uio_offset < 0 ||
	    (u_quad_t)uio->uio_offset + uio->uio_resid > fs->fs_maxfilesize)
E 199
		return (EFBIG);
E 189
	/*
	 * Maybe this should be above the vnode op call, but so long as
	 * file servers have no limits, i don't think it matters
	 */
D 157
	if (vp->v_type == VREG &&
E 157
I 157
D 186
	if (vp->v_type == VREG && p &&
E 157
	    uio->uio_offset + uio->uio_resid >
E 186
I 186
D 187
	if (ap->a_vp->v_type == VREG && p &&
E 187
I 187
	if (vp->v_type == VREG && p &&
E 187
D 188
	    ap->a_uio->uio_offset + ap->a_uio->uio_resid >
E 188
I 188
	    uio->uio_offset + uio->uio_resid >
E 188
E 186
D 153
	      u.u_rlimit[RLIMIT_FSIZE].rlim_cur) {
		psignal(u.u_procp, SIGXFSZ);
E 153
I 153
	      p->p_rlimit[RLIMIT_FSIZE].rlim_cur) {
		psignal(p, SIGXFSZ);
E 153
		return (EFBIG);
	}
D 186
	resid = uio->uio_resid;
E 186
I 186
D 188
	resid = ap->a_uio->uio_resid;
E 188
I 188
	resid = uio->uio_resid;
E 188
E 186
	osize = ip->i_size;
D 189
	fs = ip->i_fs;
E 189
I 120
	flags = 0;
D 186
	if (ioflag & IO_SYNC)
E 186
I 186
D 188
	if (ap->a_ioflag & IO_SYNC)
E 188
I 188
	if (ioflag & IO_SYNC)
E 188
E 186
		flags = B_SYNC;
E 120
	do {
D 186
		lbn = lblkno(fs, uio->uio_offset);
		on = blkoff(fs, uio->uio_offset);
		n = MIN((unsigned)(fs->fs_bsize - on), uio->uio_resid);
E 186
I 186
D 188
		lbn = lblkno(fs, ap->a_uio->uio_offset);
		on = blkoff(fs, ap->a_uio->uio_offset);
		n = MIN((unsigned)(fs->fs_bsize - on), ap->a_uio->uio_resid);
E 188
I 188
		lbn = lblkno(fs, uio->uio_offset);
		on = blkoff(fs, uio->uio_offset);
D 198
		n = MIN((unsigned)(fs->fs_bsize - on), uio->uio_resid);
E 198
I 198
		n = min((unsigned)(fs->fs_bsize - on), uio->uio_resid);
E 198
E 188
E 186
		if (n < fs->fs_bsize)
D 120
			flags = B_CLRBUF;
E 120
I 120
			flags |= B_CLRBUF;
E 120
		else
D 120
			flags = 0;
		if (error = balloc(ip, lbn, (int)(on + n), &bn, flags))
E 120
I 120
			flags &= ~B_CLRBUF;
D 161
		if (error = balloc(ip, lbn, (int)(on + n), &bp, flags))
E 161
I 161
D 170
		if (error = ffs_balloc(ip, lbn, (int)(on + n), &bp, flags))
E 170
I 170
D 186
		if (error = ffs_balloc(ip, lbn, on + n, cred, &bp, flags))
E 186
I 186
		if (error = ffs_balloc(ip, lbn, on + n, ap->a_cred, &bp, flags))
E 186
E 170
E 161
E 120
			break;
I 120
		bn = bp->b_blkno;
E 120
D 142
		if (uio->uio_offset + n > ip->i_size)
E 142
I 142
D 186
		if (uio->uio_offset + n > ip->i_size) {
E 142
			ip->i_size = uio->uio_offset + n;
I 142
D 163
			vnode_pager_setsize(vp, ip->i_size);
E 163
I 163
			vnode_pager_setsize(vp, (u_long)ip->i_size);
E 186
I 186
D 188
		if (ap->a_uio->uio_offset + n > ip->i_size) {
			ip->i_size = ap->a_uio->uio_offset + n;
E 188
I 188
		if (uio->uio_offset + n > ip->i_size) {
			ip->i_size = uio->uio_offset + n;
E 188
D 187
			vnode_pager_setsize(ap->a_vp, (u_long)ip->i_size);
E 187
I 187
			vnode_pager_setsize(vp, (u_long)ip->i_size);
E 187
E 186
E 163
		}
E 142
		size = blksize(fs, ip, lbn);
D 142
		count = howmany(size, CLBYTES);
		for (i = 0; i < count; i++)
			munhash(ip->i_devvp, bn + i * CLBYTES / DEV_BSIZE);
E 142
I 142
D 186
		(void) vnode_pager_uncache(vp);
E 186
I 186
D 187
		(void) vnode_pager_uncache(ap->a_vp);
E 187
I 187
		(void) vnode_pager_uncache(vp);
E 187
E 186
E 142
D 120
		if (n == fs->fs_bsize)
			bp = getblk(ip->i_devvp, bn, size);
		else
			error = bread(ip->i_devvp, bn, size, NOCRED, &bp);
E 120
D 198
		n = MIN(n, size - bp->b_resid);
E 198
I 198
		n = min(n, size - bp->b_resid);
E 198
D 120
		if (error) {
			brelse(bp);
			break;
		}
E 120
D 186
		error = uiomove(bp->b_un.b_addr + on, n, uio);
		if (ioflag & IO_SYNC)
E 186
I 186
D 188
		error = uiomove(bp->b_un.b_addr + on, n, ap->a_uio);
		if (ap->a_ioflag & IO_SYNC)
E 188
I 188
		error = uiomove(bp->b_un.b_addr + on, n, uio);
		if (ioflag & IO_SYNC)
E 188
E 186
			(void) bwrite(bp);
		else if (n + on == fs->fs_bsize) {
D 207
			bp->b_flags |= B_AGE;
			bawrite(bp);
E 207
I 207
D 208
			cluster_write(bp, ip->i_size);
E 208
I 208
			if (doclusterwrite) {
				cluster_write(bp, ip->i_size);
			} else {
				bp->b_flags |= B_AGE;
				bawrite(bp);
			}
E 208
E 207
		} else
			bdwrite(bp);
		ip->i_flag |= IUPD|ICHG;
D 186
		if (cred->cr_uid != 0)
E 186
I 186
D 203
		if (ap->a_cred->cr_uid != 0)
E 203
I 203
		if (ap->a_cred && ap->a_cred->cr_uid != 0)
E 203
E 186
			ip->i_mode &= ~(ISUID|ISGID);
D 186
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
	if (error && (ioflag & IO_UNIT)) {
D 120
		(void) itrunc(ip, osize);
E 120
I 120
D 161
		(void) itrunc(ip, osize, ioflag & IO_SYNC);
E 161
I 161
D 162
		(void)ffs_itrunc(ip, osize, ioflag & IO_SYNC);
E 162
I 162
D 170
		(void)ffs_truncate(vp, osize, ioflag & IO_SYNC);
E 170
I 170
D 184
		(void)ffs_truncate(vp, osize, ioflag & IO_SYNC, cred);
E 184
I 184
		(void)VOP_TRUNCATE(vp, osize, ioflag & IO_SYNC, cred);
E 184
E 170
E 162
E 161
E 120
		uio->uio_offset -= resid - uio->uio_resid;
		uio->uio_resid = resid;
E 186
I 186
D 188
	} while (error == 0 && ap->a_uio->uio_resid > 0 && n != 0);
	if (error && (ap->a_ioflag & IO_UNIT)) {
D 187
		(void)VOP_TRUNCATE(ap->a_vp, osize, ap->a_ioflag & IO_SYNC, ap->a_cred);
E 187
I 187
		(void)VOP_TRUNCATE(vp, osize, ap->a_ioflag & IO_SYNC, ap->a_cred);
E 187
		ap->a_uio->uio_offset -= resid - ap->a_uio->uio_resid;
		ap->a_uio->uio_resid = resid;
E 188
I 188
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
	if (error && (ioflag & IO_UNIT)) {
D 193
		(void)VOP_TRUNCATE(vp, osize, ioflag & IO_SYNC, ap->a_cred);
E 193
I 193
		(void)VOP_TRUNCATE(vp, osize, ioflag & IO_SYNC, ap->a_cred,
		    uio->uio_procp);
E 193
		uio->uio_offset -= resid - uio->uio_resid;
		uio->uio_resid = resid;
E 188
E 186
	}
I 138
D 186
	if (!error && (ioflag & IO_SYNC))
D 161
		error = iupdat(ip, &time, &time, 1);
E 161
I 161
D 162
		error = ffs_iupdat(ip, &time, &time, 1);
E 162
I 162
D 184
		error = ffs_update(vp, &time, &time, 1);
E 184
I 184
		error = VOP_UPDATE(vp, &time, &time, 1);
E 186
I 186
D 188
	if (!error && (ap->a_ioflag & IO_SYNC))
E 188
I 188
D 195
	if (!error && (ioflag & IO_SYNC))
E 188
D 187
		error = VOP_UPDATE(ap->a_vp, &time, &time, 1);
E 187
I 187
		error = VOP_UPDATE(vp, &time, &time, 1);
E 195
I 195
	if (!error && (ioflag & IO_SYNC)) {
		tv = time;
		error = VOP_UPDATE(vp, &tv, &tv, 1);
	}
E 195
E 187
E 186
E 184
E 162
E 161
E 138
	return (error);
}
I 184
D 186
#undef vp
#undef uio
#undef ioflag
#undef cred
E 186
E 184

D 161
/* ARGSUSED */
E 117
D 155
ufs_ioctl(vp, com, data, fflag, cred)
E 155
I 155
ufs_ioctl(vp, com, data, fflag, cred, p)
E 155
	struct vnode *vp;
	int com;
	caddr_t data;
	int fflag;
	struct ucred *cred;
I 155
	struct proc *p;
E 155
E 102
{
D 102
	register struct a {
		char	*fname;
		struct	timeval *tptr;
	} *uap = (struct a *)u.u_ap;
	register struct inode *ip;
	struct timeval tv[2];
E 102

D 82
	if ((ip = owner(1)) == NULL)
E 82
I 82
D 102
	if ((ip = owner(uap->fname, FOLLOW)) == NULL)
E 82
		return;
I 89
	if (ip->i_fs->fs_ronly) {
		u.u_error = EROFS;
		iput(ip);
		return;
	}
E 89
	u.u_error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv));
	if (u.u_error == 0) {
		ip->i_flag |= IACC|IUPD|ICHG;
		iupdat(ip, &tv[0], &tv[1], 0);
	}
	iput(ip);
E 102
I 102
D 117
	printf("ufs_ioctl called with type %d\n", vp->v_type);
E 117
	return (ENOTTY);
E 102
}

I 102
/* ARGSUSED */
D 126
ufs_select(vp, which, cred)
E 126
I 126
D 155
ufs_select(vp, which, fflags, cred)
E 155
I 155
ufs_select(vp, which, fflags, cred, p)
E 155
E 126
	struct vnode *vp;
D 126
	int which;
E 126
I 126
	int which, fflags;
E 126
	struct ucred *cred;
I 155
	struct proc *p;
E 155
{

D 117
	printf("ufs_select called with type %d\n", vp->v_type);
E 117
D 155
	return (1);		/* XXX */
E 155
I 155
	/*
	 * We should really check to see if I/O is possible.
	 */
	return (1);
E 155
}

E 161
E 102
E 60
I 47
/*
E 214
D 102
 * Flush any pending I/O.
E 102
I 102
D 161
 * Mmap a file
 *
 * NB Currently unsupported.
E 102
 */
E 47
D 26
/*
 * the umount system call.
 */
sumount()
E 26
I 26
D 102
sync()
E 102
I 102
/* ARGSUSED */
D 155
ufs_mmap(vp, fflags, cred)
E 155
I 155
ufs_mmap(vp, fflags, cred, p)
E 155
	struct vnode *vp;
	int fflags;
	struct ucred *cred;
I 155
	struct proc *p;
E 155
E 102
E 26
{
D 26
	dev_t dev;
	register struct inode *ip;
	register struct mount *mp;
	struct buf *bp;
I 8
D 9
	int flag;
	int stillopen = 0;
E 9
I 9
	int stillopen, flag;
E 9
E 8
	register struct a {
		char	*fspec;
	};
E 26

D 26
	dev = getmdev();
D 17
	if(u.u_error)
E 17
I 17
	if (u.u_error)
E 17
		return;
	xumount(dev);	/* remove unused sticky files from text table */
E 26
D 21
	update();
E 21
I 21
D 46
	update(0);
E 46
I 46
D 102
	update();
E 102
I 102
	return (EINVAL);
E 102
E 46
I 36
D 66
}

I 47
/*
 * Apply an advisory lock on a file descriptor.
 */
E 47
I 37
flock()
{
D 63
	struct a {
E 63
I 63
	register struct a {
E 63
		int	fd;
		int	how;
D 63
	} *uap;
E 63
I 63
	} *uap = (struct a *)u.u_ap;
E 63
	register struct file *fp;
	register int cmd, flags;

D 63
	uap = (struct a *)u.u_ap;
	fp = getf(uap->fd);
E 63
I 63
	fp = getinode(uap->fd);
E 63
	if (fp == NULL)
		return;
D 63
	if (fp->f_type == DTYPE_SOCKET) {		/* XXX */
		u.u_error = EINVAL;
		return;
	}
E 63
	cmd = uap->how;
D 47
	flags = u.u_pofile[uap->fd] & (RDLOCK|WRLOCK);
E 47
I 47
D 48
	flags = u.u_pofile[uap->fd] & (SHLOCK|EXLOCK);
E 48
I 48
	flags = u.u_pofile[uap->fd] & (UF_SHLOCK|UF_EXLOCK);
E 48
E 47
D 63
	if (cmd&FUNLOCK) {
E 63
I 63
	if (cmd&LOCK_UN) {
E 63
		if (flags == 0) {
			u.u_error = EINVAL;
			return;
		}
D 63
		funlocki(fp->f_inode, flags);
E 63
I 63
		funlocki((struct inode *)fp->f_data, flags);
E 63
D 47
		u.u_pofile[uap->fd] &= ~(RDLOCK|WRLOCK);
E 47
I 47
D 48
		u.u_pofile[uap->fd] &= ~(SHLOCK|EXLOCK);
E 48
I 48
		u.u_pofile[uap->fd] &= ~(UF_SHLOCK|UF_EXLOCK);
E 48
E 47
		return;
	}
	/*
	 * No reason to write lock a file we've already
	 * write locked, similarly with a read lock.
	 */
D 47
	if ((flags&WRLOCK) && (cmd&FWRLOCK) ||
	    (flags&RDLOCK) && (cmd&FRDLOCK))
E 47
I 47
D 48
	if ((flags&EXLOCK) && (cmd&FEXLOCK) ||
	    (flags&SHLOCK) && (cmd&FSHLOCK))
E 48
I 48
D 63
	if ((flags&UF_EXLOCK) && (cmd&FEXLOCK) ||
	    (flags&UF_SHLOCK) && (cmd&FSHLOCK))
E 63
I 63
	if ((flags&UF_EXLOCK) && (cmd&LOCK_EX) ||
	    (flags&UF_SHLOCK) && (cmd&LOCK_SH))
E 63
E 48
E 47
		return;
D 63
	u.u_pofile[uap->fd] = flocki(fp->f_inode, u.u_pofile[uap->fd], cmd);
E 63
I 63
	u.u_pofile[uap->fd] =
	    flocki((struct inode *)fp->f_data, u.u_pofile[uap->fd], cmd);
E 66
E 63
}

I 47
/*
E 161
D 102
 * Truncate a file given its path name.
E 102
I 102
 * Synch an open file.
E 102
 */
E 47
D 102
truncate()
E 102
I 102
/* ARGSUSED */
D 116
ufs_fsync(vp, fflags, cred)
E 116
I 116
D 155
ufs_fsync(vp, fflags, cred, waitfor)
E 155
I 155
D 161
ufs_fsync(vp, fflags, cred, waitfor, p)
E 161
I 161
int
D 184
ffs_fsync(vp, fflags, cred, waitfor, p)
E 161
E 155
E 116
	struct vnode *vp;
	int fflags;
	struct ucred *cred;
I 116
	int waitfor;
I 155
	struct proc *p;
E 184
I 184
D 188
ffs_fsync (ap)
E 188
I 188
ffs_fsync(ap)
E 188
D 193
	struct vop_fsync_args *ap;
E 193
I 193
	struct vop_fsync_args /* {
		struct vnode *a_vp;
		struct ucred *a_cred;
		int a_waitfor;
		struct proc *a_p;
	} */ *ap;
E 193
D 186
#define vp (ap->a_vp)
#define fflags (ap->a_fflags)
#define cred (ap->a_cred)
#define waitfor (ap->a_waitfor)
#define p (ap->a_p)
E 186
E 184
E 155
E 116
E 102
{
I 184
D 194
	USES_VOP_UPDATE;
E 194
E 184
D 102
	struct a {
		char	*fname;
D 47
		int	length;
E 47
I 47
D 95
		u_long	length;
E 95
I 95
		off_t	length;
E 95
E 47
D 39
	} *uap;
E 39
I 39
	} *uap = (struct a *)u.u_ap;
E 39
	struct inode *ip;
I 82
	register struct nameidata *ndp = &u.u_nd;
E 102
I 102
D 116
	register struct inode *ip = VTOI(vp);
	int error;
E 116
I 116
D 186
	struct inode *ip = VTOI(vp);
E 186
I 186
D 193
	struct inode *ip = VTOI(ap->a_vp);
E 193
I 193
	register struct vnode *vp = ap->a_vp;
D 217
	struct inode *ip = VTOI(vp);
E 217
	register struct buf *bp;
I 195
	struct timeval tv;
E 195
	struct buf *nbp;
	int s;
E 193
E 186
E 116
E 102
E 82

D 47
	ip = namei(uchar, 0, 1);
E 47
I 47
D 82
	ip = namei(uchar, LOOKUP, 1);
E 82
I 82
D 102
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
	ip = namei(ndp);
E 82
E 47
	if (ip == NULL)
		return;
	if (access(ip, IWRITE))
		goto bad;
	if ((ip->i_mode&IFMT) == IFDIR) {
		u.u_error = EISDIR;
		goto bad;
	}
D 95
	itrunc(ip, uap->length);
E 95
I 95
	itrunc(ip, (u_long)uap->length);
E 95
D 47
	return;
E 47
bad:
	iput(ip);
E 102
I 102
D 116
	ILOCK(ip);
E 116
D 155
	if (fflags&FWRITE)
E 155
I 155
D 186
	if (fflags & FWRITE)
E 186
I 186
D 193
	if (ap->a_fflags & FWRITE)
E 186
E 155
		ip->i_flag |= ICHG;
D 116
	error = syncip(ip);
	IUNLOCK(ip);
	return (error);
E 116
I 116
D 120
	return (syncip(ip, waitfor));
E 120
I 120
D 186
	vflushbuf(vp, waitfor == MNT_WAIT ? B_SYNC : 0);
D 161
	return (iupdat(ip, &time, &time, waitfor == MNT_WAIT));
E 161
I 161
D 162
	return (ffs_iupdat(ip, &time, &time, waitfor == MNT_WAIT));
E 162
I 162
D 184
	return (ffs_update(vp, &time, &time, waitfor == MNT_WAIT));
E 184
I 184
	return (VOP_UPDATE(vp, &time, &time, waitfor == MNT_WAIT));
E 186
I 186
	vflushbuf(ap->a_vp, ap->a_waitfor == MNT_WAIT ? B_SYNC : 0);
E 193
I 193
	/*
	 * Flush all dirty buffers associated with a vnode.
	 */
loop:
	s = splbio();
D 202
	for (bp = vp->v_dirtyblkhd; bp; bp = nbp) {
		nbp = bp->b_blockf;
E 202
I 202
D 216
	for (bp = vp->v_dirtyblkhd.le_next; bp; bp = nbp) {
		nbp = bp->b_vnbufs.qe_next;
E 216
I 216
	for (bp = vp->v_dirtyblkhd.lh_first; bp; bp = nbp) {
		nbp = bp->b_vnbufs.le_next;
E 216
E 202
		if ((bp->b_flags & B_BUSY))
			continue;
		if ((bp->b_flags & B_DELWRI) == 0)
			panic("ffs_fsync: not dirty");
		bremfree(bp);
		bp->b_flags |= B_BUSY;
		splx(s);
		/*
		 * Wait for I/O associated with indirect blocks to complete,
		 * since there is no way to quickly wait for them below.
		 */
		if (bp->b_vp == vp || ap->a_waitfor == MNT_NOWAIT)
			(void) bawrite(bp);
		else
			(void) bwrite(bp);
		goto loop;
	}
	if (ap->a_waitfor == MNT_WAIT) {
		while (vp->v_numoutput) {
			vp->v_flag |= VBWAIT;
			sleep((caddr_t)&vp->v_numoutput, PRIBIO + 1);
		}
#ifdef DIAGNOSTIC
D 202
		if (vp->v_dirtyblkhd) {
E 202
I 202
D 216
		if (vp->v_dirtyblkhd.le_next) {
E 216
I 216
		if (vp->v_dirtyblkhd.lh_first) {
E 216
E 202
			vprint("ffs_fsync: dirty", vp);
			goto loop;
		}
#endif
	}
	splx(s);
E 193
D 195
	return (VOP_UPDATE(ap->a_vp, &time, &time, ap->a_waitfor == MNT_WAIT));
E 195
I 195
	tv = time;
I 215
	return (VOP_UPDATE(ap->a_vp, &tv, &tv, ap->a_waitfor == MNT_WAIT));
I 221
}

/*
 * Reclaim an inode so that it can be used for other purposes.
 */
int
ffs_reclaim(ap)
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
I 228
		struct proc *a_p;
E 228
	} */ *ap;
{
	register struct vnode *vp = ap->a_vp;
	int error;

D 228
	if (error = ufs_reclaim(vp))
E 228
I 228
	if (error = ufs_reclaim(vp, ap->a_p))
E 228
		return (error);
D 224
	FREE(vp->v_data, M_FFSNODE);
E 224
I 224
	FREE(vp->v_data, VFSTOUFS(vp->v_mount)->um_devvp->v_tag == VT_MFS ?
	    M_MFSNODE : M_FFSNODE);
E 224
	vp->v_data = NULL;
	return (0);
E 221
}
E 215
D 214
	return (VOP_UPDATE(ap->a_vp, &tv, &tv, ap->a_waitfor == MNT_WAIT));
E 195
E 186
E 184
D 206
}
I 184
D 186
#undef vp
#undef fflags
#undef cred
#undef waitfor
#undef p
E 186
E 184

/*
 * Last reference to an inode, write the inode out and if necessary,
 * truncate and deallocate the file.
 */
int
D 184
ffs_inactive(vp, p)
	struct vnode *vp;
	struct proc *p;
E 184
I 184
D 188
ffs_inactive (ap)
E 188
I 188
ffs_inactive(ap)
E 188
D 193
	struct vop_inactive_args *ap;
E 193
I 193
	struct vop_inactive_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 193
D 186
#define vp (ap->a_vp)
#define p (ap->a_p)
E 186
E 184
{
I 184
D 194
	USES_VOP_TRUNCATE;
	USES_VOP_UPDATE;
	USES_VOP_VFREE;
E 194
E 184
D 188
	register struct inode *ip;
E 188
I 188
	register struct vnode *vp = ap->a_vp;
	register struct inode *ip = VTOI(vp);
I 195
	struct timeval tv;
E 195
E 188
	int mode, error;
	extern int prtactive;

D 186
	if (prtactive && vp->v_usecount != 0)
		vprint("ffs_inactive: pushing active", vp);
E 186
I 186
D 188
	if (prtactive && ap->a_vp->v_usecount != 0)
		vprint("ffs_inactive: pushing active", ap->a_vp);
E 188
I 188
	if (prtactive && vp->v_usecount != 0)
		vprint("ffs_inactive: pushing active", vp);
E 188
E 186

	/* Get rid of inodes related to stale file handles. */
D 186
	ip = VTOI(vp);
E 186
I 186
D 188
	ip = VTOI(ap->a_vp);
E 188
E 186
	if (ip->i_mode == 0) {
D 186
		if ((vp->v_flag & VXLOCK) == 0)
			vgone(vp);
E 186
I 186
D 188
		if ((ap->a_vp->v_flag & VXLOCK) == 0)
			vgone(ap->a_vp);
E 188
I 188
		if ((vp->v_flag & VXLOCK) == 0)
			vgone(vp);
E 188
E 186
		return (0);
	}

	error = 0;
	ILOCK(ip);
D 186
	if (ip->i_nlink <= 0 && (vp->v_mount->mnt_flag & MNT_RDONLY) == 0) {
E 186
I 186
D 188
	if (ip->i_nlink <= 0 && (ap->a_vp->v_mount->mnt_flag & MNT_RDONLY) == 0) {
E 188
I 188
	if (ip->i_nlink <= 0 && (vp->v_mount->mnt_flag & MNT_RDONLY) == 0) {
E 188
E 186
#ifdef QUOTA
		if (!getinoquota(ip))
			(void)chkiq(ip, -1, NOCRED, 0);
#endif
D 169
		error = ffs_truncate(vp, (u_long)0, 0);
E 169
I 169
D 170
		error = ffs_truncate(vp, (off_t)0, 0);
E 170
I 170
D 184
		error = ffs_truncate(vp, (off_t)0, 0, NOCRED);
E 184
I 184
D 186
		error = VOP_TRUNCATE(vp, (off_t)0, 0, NOCRED);
E 186
I 186
D 188
		error = VOP_TRUNCATE(ap->a_vp, (off_t)0, 0, NOCRED);
E 188
I 188
D 193
		error = VOP_TRUNCATE(vp, (off_t)0, 0, NOCRED);
E 193
I 193
		error = VOP_TRUNCATE(vp, (off_t)0, 0, NOCRED, NULL);
E 193
E 188
E 186
E 184
E 170
E 169
		mode = ip->i_mode;
		ip->i_mode = 0;
		ip->i_rdev = 0;
		ip->i_flag |= IUPD|ICHG;
D 184
		ffs_vfree(vp, ip->i_number, mode);
E 184
I 184
D 186
		VOP_VFREE(vp, ip->i_number, mode);
E 186
I 186
D 188
		VOP_VFREE(ap->a_vp, ip->i_number, mode);
E 188
I 188
		VOP_VFREE(vp, ip->i_number, mode);
E 188
E 186
E 184
	}
D 195
	if (ip->i_flag&(IUPD|IACC|ICHG|IMOD))
D 184
		ffs_update(vp, &time, &time, 0);
E 184
I 184
D 186
		VOP_UPDATE(vp, &time, &time, 0);
E 186
I 186
D 188
		VOP_UPDATE(ap->a_vp, &time, &time, 0);
E 188
I 188
		VOP_UPDATE(vp, &time, &time, 0);
E 195
I 195
	if (ip->i_flag&(IUPD|IACC|ICHG|IMOD)) {
		tv = time;
		VOP_UPDATE(vp, &tv, &tv, 0);
	}
E 195
E 188
E 186
E 184
	IUNLOCK(ip);
	ip->i_flag = 0;
	/*
	 * If we are done with the inode, reclaim it
	 * so that it can be reused immediately.
	 */
D 186
	if (vp->v_usecount == 0 && ip->i_mode == 0)
		vgone(vp);
E 186
I 186
D 188
	if (ap->a_vp->v_usecount == 0 && ip->i_mode == 0)
		vgone(ap->a_vp);
E 188
I 188
	if (vp->v_usecount == 0 && ip->i_mode == 0)
		vgone(vp);
E 188
E 186
	return (error);
E 206
E 162
E 161
E 120
E 116
E 102
}
I 207

E 214
E 207
I 184
D 186
#undef vp
#undef p
E 186
E 184
D 161

I 47
/*
D 102
 * Truncate a file given a file descriptor.
E 102
I 102
 * Seek on a file
 *
 * Nothing to do, so just return.
E 102
 */
E 47
D 102
ftruncate()
E 102
I 102
/* ARGSUSED */
ufs_seek(vp, oldoff, newoff, cred)
	struct vnode *vp;
	off_t oldoff, newoff;
	struct ucred *cred;
E 102
{
D 102
	struct a {
		int	fd;
D 47
		int	length;
E 47
I 47
D 95
		u_long	length;
E 95
I 95
		off_t	length;
E 95
E 47
D 39
	} *uap;
E 39
I 39
	} *uap = (struct a *)u.u_ap;
E 39
	struct inode *ip;
	struct file *fp;
E 102

D 63
	fp = getf(uap->fd);
E 63
I 63
D 102
	fp = getinode(uap->fd);
E 63
	if (fp == NULL)
		return;
D 63
	if (fp->f_type == DTYPE_SOCKET) {
		u.u_error = EINVAL;
		return;
	}
E 63
	if ((fp->f_flag&FWRITE) == 0) {
		u.u_error = EINVAL;
		return;
E 102
I 102
	return (0);
}

/*
 * ufs remove
 * Hard to avoid races here, especially
 * in unlinking directories.
 */
D 155
ufs_remove(ndp)
E 155
I 155
ufs_remove(ndp, p)
E 155
	struct nameidata *ndp;
I 155
	struct proc *p;
E 155
{
	register struct inode *ip, *dp;
	int error;

	ip = VTOI(ndp->ni_vp);
	dp = VTOI(ndp->ni_dvp);
	error = dirremove(ndp);
	if (!error) {
		ip->i_nlink--;
		ip->i_flag |= ICHG;
E 102
	}
D 63
	ip = fp->f_inode;
E 63
I 63
D 102
	ip = (struct inode *)fp->f_data;
E 63
D 81
	ilock(ip);
E 81
I 81
	ILOCK(ip);
E 81
D 95
	itrunc(ip, uap->length);
E 95
I 95
	itrunc(ip, (u_long)uap->length);
E 95
I 47
D 81
	iunlock(ip);
E 81
I 81
	IUNLOCK(ip);
E 102
I 102
	if (dp == ip)
		vrele(ITOV(ip));
	else
		iput(ip);
	iput(dp);
	return (error);
E 102
E 81
E 47
}

I 47
/*
D 102
 * Synch an open file.
E 102
I 102
 * link vnode call
E 102
 */
D 102
fsync()
E 102
I 102
D 155
ufs_link(vp, ndp)
E 155
I 155
ufs_link(vp, ndp, p)
E 155
	register struct vnode *vp;
	register struct nameidata *ndp;
I 155
	struct proc *p;
E 155
E 102
{
D 102
	struct a {
		int	fd;
	} *uap = (struct a *)u.u_ap;
	struct inode *ip;
	struct file *fp;
E 102
I 102
	register struct inode *ip = VTOI(vp);
	int error;
E 102

I 147
D 158
	if ((unsigned short)ip->i_nlink >= LINK_MAX)
E 158
I 158
#ifdef DIANOSTIC
	if ((ndp->ni_nameiop & HASBUF) == 0)
		panic("ufs_link: no name");
#endif
	if ((unsigned short)ip->i_nlink >= LINK_MAX) {
		free(ndp->ni_pnbuf, M_NAMEI);
E 158
		return (EMLINK);
I 158
	}
E 158
E 147
D 63
	fp = getf(uap->fd);
E 63
I 63
D 102
	fp = getinode(uap->fd);
E 63
	if (fp == NULL)
		return;
D 63
	if (fp->f_type == DTYPE_SOCKET) {
		u.u_error = EINVAL;
		return;
	}
	ip = fp->f_inode;
E 63
I 63
	ip = (struct inode *)fp->f_data;
E 63
D 81
	ilock(ip);
E 81
I 81
	ILOCK(ip);
I 97
	if (fp->f_flag&FWRITE)
E 102
I 102
	if (ndp->ni_dvp != vp)
		ILOCK(ip);
D 147
	if (ip->i_nlink == LINK_MAX - 1) {
		error = EMLINK;
		goto out;
	}
E 147
	ip->i_nlink++;
	ip->i_flag |= ICHG;
	error = iupdat(ip, &time, &time, 1);
	if (!error)
		error = direnter(ip, ndp);
D 147
out:
E 147
	if (ndp->ni_dvp != vp)
		IUNLOCK(ip);
I 158
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 158
I 151
	vput(ndp->ni_dvp);
E 151
	if (error) {
		ip->i_nlink--;
E 102
		ip->i_flag |= ICHG;
E 97
E 81
D 102
	syncip(ip);
D 81
	iunlock(ip);
E 81
I 81
	IUNLOCK(ip);
E 102
I 102
	}
	return (error);
E 102
E 81
}

/*
 * Rename system call.
 * 	rename("foo", "bar");
 * is essentially
 *	unlink("bar");
 *	link("foo", "bar");
 *	unlink("foo");
 * but ``atomically''.  Can't do full commit without saving state in the
 * inode on disk which isn't feasible at this time.  Best we can do is
 * always guarantee the target exists.
 *
 * Basic algorithm is:
 *
 * 1) Bump link count on source while we're linking it to the
D 102
 *    target.  This also insure the inode won't be deleted out
E 102
I 102
 *    target.  This also ensure the inode won't be deleted out
E 102
D 84
 *    from underneath us while we work.
E 84
I 84
 *    from underneath us while we work (it may be truncated by
 *    a concurrent `trunc' or `open' for creation).
E 84
 * 2) Link source to destination.  If destination already exists,
 *    delete it first.
D 84
 * 3) Unlink source reference to inode if still around.
 * 4) If a directory was moved and the parent of the destination
E 84
I 84
 * 3) Unlink source reference to inode if still around. If a
 *    directory was moved and the parent of the destination
E 84
 *    is different from the source, patch the ".." entry in the
 *    directory.
D 102
 *
 * Source and destination must either both be directories, or both
 * not be directories.  If target is a directory, it must be empty.
E 102
 */
E 47
D 102
rename()
E 102
I 102
D 155
ufs_rename(fndp, tndp)
E 155
I 155
ufs_rename(fndp, tndp, p)
E 155
	register struct nameidata *fndp, *tndp;
I 155
	struct proc *p;
E 155
E 102
{
I 153
D 155
	struct proc *p = curproc;		/* XXX */
E 155
E 153
I 39
D 47
#ifdef notdef
E 47
E 39
D 102
	struct a {
		char	*from;
		char	*to;
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
E 102
E 82
I 39
D 47
#endif
E 47
I 47
	register struct inode *ip, *xp, *dp;
I 80
D 84
	struct inode *zp;
E 80
	int oldparent, parentdifferent, doingdirectory;
E 84
I 84
	struct dirtemplate dirbuf;
	int doingdirectory = 0, oldparent = 0, newparent = 0;
E 84
I 82
D 102
	register struct nameidata *ndp = &u.u_nd;
E 102
E 82
I 52
	int error = 0;
E 52
E 47
E 39

I 158
#ifdef DIANOSTIC
	if ((tndp->ni_nameiop & HASBUF) == 0 ||
	    (fndp->ni_nameiop & HASBUF) == 0)
		panic("ufs_rename: no name");
#endif
E 158
I 47
D 82
	uap = (struct a *)u.u_ap;
D 58
	ip = namei(uchar, LOOKUP | LOCKPARENT, 0);
E 58
I 58
	ip = namei(uchar, DELETE | LOCKPARENT, 0);
E 82
I 82
D 102
	ndp->ni_nameiop = DELETE | LOCKPARENT;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->from;
	ip = namei(ndp);
E 82
E 58
	if (ip == NULL)
		return;
D 82
	dp = u.u_pdir;
E 82
I 82
	dp = ndp->ni_pdir;
E 102
I 102
	dp = VTOI(fndp->ni_dvp);
	ip = VTOI(fndp->ni_vp);
I 158
	/*
	 * Check if just deleting a link name.
	 */
	if (fndp->ni_vp == tndp->ni_vp) {
		VOP_ABORTOP(tndp);
		vput(tndp->ni_dvp);
		vput(tndp->ni_vp);
		vrele(fndp->ni_dvp);
		if ((ip->i_mode&IFMT) == IFDIR) {
			VOP_ABORTOP(fndp);
			vrele(fndp->ni_vp);
			return (EINVAL);
		}
		doingdirectory = 0;
		goto unlinkit;
	}
E 158
	ILOCK(ip);
E 102
E 82
D 84
	oldparent = 0, doingdirectory = 0;
E 84
	if ((ip->i_mode&IFMT) == IFDIR) {
D 102
		register struct direct *d;
E 102
I 102
D 158
		register struct direct *d = &fndp->ni_dent;
E 102

E 158
D 82
		d = &u.u_dent;
E 82
I 82
D 102
		d = &ndp->ni_dent;
E 102
E 82
		/*
D 58
		 * Avoid "." and ".." for obvious reasons.
E 58
I 58
		 * Avoid ".", "..", and aliases of "." for obvious reasons.
E 58
		 */
D 58
		if (d->d_name[0] == '.') {
			if (d->d_namlen == 1 ||
			    (d->d_namlen == 2 && d->d_name[1] == '.')) {
E 58
I 58
D 102
		if ((d->d_namlen == 1 && d->d_name[0] == '.') ||
		    (d->d_namlen == 2 && bcmp(d->d_name, "..", 2) == 0) ||
D 84
		    (dp == ip)) {
E 84
I 84
		    (dp == ip) || (ip->i_flag & IRENAME)) {
E 84
			iput(dp);
			if (dp == ip)
				irele(ip);
			else
E 58
D 52
				u.u_error = EINVAL;
E 52
				iput(ip);
I 52
D 58
				u.u_error = EINVAL;
E 52
				return;
			}
E 58
I 58
			u.u_error = EINVAL;
			return;
E 102
I 102
D 158
		if ((d->d_namlen == 1 && d->d_name[0] == '.') || dp == ip ||
		    fndp->ni_isdotdot || (ip->i_flag & IRENAME)) {
E 158
I 158
		if ((fndp->ni_namelen == 1 && fndp->ni_ptr[0] == '.') ||
		    dp == ip || fndp->ni_isdotdot || (ip->i_flag & IRENAME)) {
E 158
D 137
			IUNLOCK(ip);
			ufs_abortop(fndp);
			ufs_abortop(tndp);
E 137
I 137
			VOP_ABORTOP(tndp);
			vput(tndp->ni_dvp);
			if (tndp->ni_vp)
				vput(tndp->ni_vp);
			VOP_ABORTOP(fndp);
			vrele(fndp->ni_dvp);
			vput(fndp->ni_vp);
E 137
			return (EINVAL);
E 102
E 58
		}
I 84
		ip->i_flag |= IRENAME;
E 84
		oldparent = dp->i_number;
		doingdirectory++;
	}
D 58
	irele(dp);
E 58
I 58
D 102
	iput(dp);
E 102
I 102
	vrele(fndp->ni_dvp);
E 102
E 58

	/*
	 * 1) Bump link count while we're moving stuff
	 *    around.  If we crash somewhere before
	 *    completing our work, the link count
	 *    may be wrong, but correctable.
	 */
	ip->i_nlink++;
	ip->i_flag |= ICHG;
D 102
	iupdat(ip, &time, &time, 1);
E 102
I 102
	error = iupdat(ip, &time, &time, 1);
E 102
D 81
	iunlock(ip);
E 81
I 81
	IUNLOCK(ip);
E 81

	/*
	 * When the target exists, both the directory
D 102
	 * and target inodes are returned locked.
E 102
I 102
	 * and target vnodes are returned locked.
E 102
	 */
D 82
	u.u_dirp = (caddr_t)uap->to;
D 74
	xp = namei(uchar, CREATE | LOCKPARENT, 0);
E 74
I 74
	xp = namei(uchar, CREATE | LOCKPARENT | NOCACHE, 0);
E 82
I 82
D 102
	ndp->ni_nameiop = CREATE | LOCKPARENT | NOCACHE;
	ndp->ni_dirp = (caddr_t)uap->to;
	xp = namei(ndp);
E 82
E 74
D 52
	if (u.u_error)
E 52
I 52
	if (u.u_error) {
		error = u.u_error;
E 52
		goto out;
I 52
	}
E 52
D 82
	dp = u.u_pdir;
E 82
I 82
	dp = ndp->ni_pdir;
E 102
I 102
	dp = VTOI(tndp->ni_dvp);
	xp = NULL;
	if (tndp->ni_vp)
		xp = VTOI(tndp->ni_vp);
E 102
E 82
	/*
I 58
	 * If ".." must be changed (ie the directory gets a new
D 64
	 * parent) then the user must have write permission.
E 64
I 64
	 * parent) then the source directory must not be in the
	 * directory heirarchy above the target, as this would
	 * orphan everything below the source directory. Also
	 * the user must have write permission in the source so
	 * as to be able to change "..". We must repeat the call 
	 * to namei, as the parent directory is unlocked by the
	 * call to checkpath().
E 64
	 */
D 84
	parentdifferent = oldparent != dp->i_number;
D 59
	if (parentdifferent && access(ip, IWRITE))
E 59
I 59
D 64
	if (doingdirectory && parentdifferent && access(ip, IWRITE))
E 59
		goto bad;
E 64
I 64
	if (doingdirectory && parentdifferent) {
E 84
I 84
	if (oldparent != dp->i_number)
		newparent = dp->i_number;
	if (doingdirectory && newparent) {
E 84
D 102
		if (access(ip, IWRITE))
E 102
I 102
D 131
		if (error = iaccess(ip, IWRITE, tndp->ni_cred))
E 131
I 131
D 133
		if (error = ufs_access(fndp->ni_vp, VWRITE, tndp->ni_cred))
E 133
I 133
		VOP_LOCK(fndp->ni_vp);
D 155
		error = ufs_access(fndp->ni_vp, VWRITE, tndp->ni_cred);
E 155
I 155
		error = ufs_access(fndp->ni_vp, VWRITE, tndp->ni_cred, p);
E 155
		VOP_UNLOCK(fndp->ni_vp);
		if (error)
E 133
E 131
E 102
			goto bad;
I 102
D 149
		tndp->ni_nameiop = RENAME | LOCKPARENT | LOCKLEAF | NOCACHE;
E 149
I 149
D 158
		tndp->ni_nameiop &= ~(MODMASK | OPMASK);
		tndp->ni_nameiop |= RENAME | LOCKPARENT | LOCKLEAF | NOCACHE;
E 149
E 102
		do {
D 82
			dp = u.u_pdir;
E 82
I 82
D 102
			dp = ndp->ni_pdir;
E 102
I 102
			dp = VTOI(tndp->ni_dvp);
E 102
E 82
			if (xp != NULL)
D 102
				iput(xp);
			u.u_error = checkpath(ip, dp);
			if (u.u_error)
E 102
I 102
D 105
				vput(ITOV(xp));
E 105
I 105
				iput(xp);
E 105
			if (error = checkpath(ip, dp, tndp->ni_cred))
E 102
				goto out;
D 82
			u.u_dirp = (caddr_t)uap->to;
D 74
			xp = namei(uchar, CREATE | LOCKPARENT, 0);
E 74
I 74
			xp = namei(uchar, CREATE | LOCKPARENT | NOCACHE, 0);
E 82
I 82
D 102
			xp = namei(ndp);
E 82
E 74
			if (u.u_error) {
				error = u.u_error;
E 102
I 102
D 153
			if (error = namei(tndp))
E 153
I 153
			if (error = namei(tndp, p))
E 153
E 102
				goto out;
D 102
			}
D 82
		} while (dp != u.u_pdir);
E 82
I 82
		} while (dp != ndp->ni_pdir);
E 102
I 102
			xp = NULL;
			if (tndp->ni_vp)
				xp = VTOI(tndp->ni_vp);
		} while (dp != VTOI(tndp->ni_dvp));
E 158
I 158
		if (xp != NULL)
			iput(xp);
		if (error = checkpath(ip, dp, tndp->ni_cred))
			goto out;
		if ((tndp->ni_nameiop & SAVESTART) == 0)
			panic("ufs_rename: lost to startdir");
I 160
		p->p_spare[1]--;
E 160
		if (error = lookup(tndp, p))
			goto out;
		dp = VTOI(tndp->ni_dvp);
		xp = NULL;
		if (tndp->ni_vp)
			xp = VTOI(tndp->ni_vp);
E 158
E 102
E 82
	}
E 64
	/*
E 58
	 * 2) If target doesn't exist, link the target
	 *    to the source and unlink the source. 
	 *    Otherwise, rewrite the target directory
	 *    entry to reference the source inode and
	 *    expunge the original entry's existence.
	 */
D 58
	parentdifferent = oldparent != dp->i_number;
E 58
	if (xp == NULL) {
D 102
		if (dp->i_dev != ip->i_dev) {
D 52
			u.u_error = EXDEV;
E 52
I 52
			error = EXDEV;
E 52
D 64
			goto bad;
		}
		/*
I 54
		 * Disallow rename(foo, foo/bar).
		 */
		if (dp->i_number == ip->i_number) {
			error = EEXIST;
E 64
			goto bad;
		}
E 102
I 102
		if (dp->i_dev != ip->i_dev)
			panic("rename: EXDEV");
E 102
		/*
E 54
D 84
		 * Account for ".." in directory.
		 * When source and destination have the
		 * same parent we don't fool with the
		 * link count -- this isn't required
		 * because we do a similar check below.
E 84
I 84
		 * Account for ".." in new directory.
		 * When source and destination have the same
		 * parent we don't fool with the link count.
E 84
		 */
D 84
		if (doingdirectory && parentdifferent) {
E 84
I 84
		if (doingdirectory && newparent) {
I 147
			if ((unsigned short)dp->i_nlink >= LINK_MAX) {
				error = EMLINK;
				goto bad;
			}
E 147
E 84
			dp->i_nlink++;
			dp->i_flag |= ICHG;
D 102
			iupdat(dp, &time, &time, 1);
E 102
I 102
D 147
			error = iupdat(dp, &time, &time, 1);
E 147
I 147
			if (error = iupdat(dp, &time, &time, 1))
				goto bad;
E 147
E 102
		}
D 55
		direnter(ip);
D 52
		if (u.u_error)
E 52
I 52
		if (u.u_error) {
			error = u.u_error;
E 55
I 55
D 82
		error = direnter(ip);
E 82
I 82
D 102
		error = direnter(ip, ndp);
E 82
		if (error)
E 102
I 102
D 151
		if (error = direnter(ip, tndp))
E 102
E 55
E 52
			goto out;
E 151
I 151
		if (error = direnter(ip, tndp)) {
			if (doingdirectory && newparent) {
				dp->i_nlink--;
				dp->i_flag |= ICHG;
				(void) iupdat(dp, &time, &time, 1);
			}
			goto bad;
		}
I 152
		iput(dp);
E 152
E 151
I 52
D 55
		}
E 55
E 52
	} else {
D 102
		if (xp->i_dev != dp->i_dev || xp->i_dev != ip->i_dev) {
D 52
			u.u_error = EXDEV;
E 52
I 52
			error = EXDEV;
E 52
			goto bad;
		}
E 102
I 102
		if (xp->i_dev != dp->i_dev || xp->i_dev != ip->i_dev)
			panic("rename: EXDEV");
E 102
I 54
		/*
		 * Short circuit rename(foo, foo).
		 */
		if (xp->i_number == ip->i_number)
D 102
			goto bad;
E 102
I 102
			panic("rename: same file");
E 102
E 54
		/*
I 91
		 * If the parent directory is "sticky", then the user must
		 * own the parent directory, or the destination of the rename,
		 * otherwise the destination may not be changed (except by
		 * root). This implements append-only directories.
		 */
D 102
		if ((dp->i_mode & ISVTX) && u.u_uid != 0 &&
		    u.u_uid != dp->i_uid && xp->i_uid != u.u_uid) {
E 102
I 102
		if ((dp->i_mode & ISVTX) && tndp->ni_cred->cr_uid != 0 &&
		    tndp->ni_cred->cr_uid != dp->i_uid &&
		    xp->i_uid != tndp->ni_cred->cr_uid) {
E 102
			error = EPERM;
			goto bad;
		}
		/*
E 91
D 52
		 * Target must be empty if a directory.
E 52
I 52
D 158
		 * Target must be empty if a directory
		 * and have no links to it.
E 52
		 * Also, insure source and target are
		 * compatible (both directories, or both
		 * not directories).
E 158
I 158
		 * Target must be empty if a directory and have no links
		 * to it. Also, ensure source and target are compatible
		 * (both directories, or both not directories).
E 158
		 */
		if ((xp->i_mode&IFMT) == IFDIR) {
D 52
			if (!dirempty(xp)) {
D 49
				u.u_error = EEXIST;	/* XXX */
E 49
I 49
				u.u_error = ENOTEMPTY;
E 52
I 52
D 84
			if (!dirempty(xp) || xp->i_nlink > 2) {
E 84
I 84
D 102
			if (!dirempty(xp, dp->i_number) || xp->i_nlink > 2) {
E 102
I 102
			if (!dirempty(xp, dp->i_number, tndp->ni_cred) || 
			    xp->i_nlink > 2) {
E 102
E 84
				error = ENOTEMPTY;
E 52
E 49
				goto bad;
			}
			if (!doingdirectory) {
D 52
				u.u_error = ENOTDIR;
E 52
I 52
				error = ENOTDIR;
E 52
				goto bad;
			}
I 84
D 102
			cacheinval(dp);
E 102
I 102
			cache_purge(ITOV(dp));
E 102
E 84
		} else if (doingdirectory) {
D 52
			u.u_error = EISDIR;
E 52
I 52
			error = EISDIR;
E 52
			goto bad;
		}
D 82
		dirrewrite(dp, ip);
E 82
I 82
D 102
		dirrewrite(dp, ip, ndp);
E 82
D 52
		if (u.u_error)
E 52
I 52
		if (u.u_error) {
			error = u.u_error;
E 52
			goto bad1;
I 52
		}
E 102
I 102
		if (error = dirrewrite(dp, ip, tndp))
			goto bad;
I 141
		/*
		 * If the target directory is in the same
		 * directory as the source directory,
		 * decrement the link count on the parent
		 * of the target directory.
		 */
		 if (doingdirectory && !newparent) {
			dp->i_nlink--;
			dp->i_flag |= ICHG;
		}
E 141
		vput(ITOV(dp));
E 102
E 52
		/*
D 52
		 * If this is a directory we know it is
		 * empty and we can squash the inode and
		 * any space associated with it.  Otherwise,
		 * we've got a plain file and the link count
		 * simply needs to be adjusted.
E 52
I 52
		 * Adjust the link count of the target to
		 * reflect the dirrewrite above.  If this is
		 * a directory it is empty and there are
		 * no links to it, so we can squash the inode and
		 * any space associated with it.  We disallowed
		 * renaming over top of a directory with links to
D 84
		 * it above, as we've no way to determine if
		 * we've got a link or the directory itself, and
		 * if we get a link, then ".." will be screwed up.
E 84
I 84
		 * it above, as the remaining link would point to
		 * a directory without "." or ".." entries.
E 84
E 52
		 */
I 52
		xp->i_nlink--;
E 52
		if (doingdirectory) {
D 52
			xp->i_nlink = 0;
E 52
I 52
			if (--xp->i_nlink != 0)
				panic("rename: linked directory");
E 52
D 102
			itrunc(xp, (u_long)0);
E 102
I 102
D 120
			error = itrunc(xp, (u_long)0);
E 120
I 120
			error = itrunc(xp, (u_long)0, IO_SYNC);
E 120
E 102
D 52
		} else
			xp->i_nlink--;
E 52
I 52
		}
E 52
		xp->i_flag |= ICHG;
D 102
		iput(xp);
E 102
I 102
D 108
		vput(ITOV(xp));
E 108
I 108
		iput(xp);
E 108
E 102
I 53
		xp = NULL;
E 53
	}

	/*
	 * 3) Unlink the source.
	 */
D 82
	u.u_dirp = uap->from;
D 80
	dp = namei(uchar, DELETE, 0);
E 80
I 80
	zp = namei(uchar, DELETE | LOCKPARENT, 0);
	dp = u.u_pdir;
E 82
I 82
D 102
	ndp->ni_nameiop = DELETE | LOCKPARENT;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->from;
D 84
	zp = namei(ndp);
E 84
I 84
	xp = namei(ndp);
E 84
D 86
	dp = ndp->ni_pdir;
E 86
I 86
	if (xp != NULL)
		dp = ndp->ni_pdir;
	else
E 102
I 102
D 149
	fndp->ni_nameiop = DELETE | LOCKPARENT | LOCKLEAF;
E 149
I 149
D 158
	fndp->ni_nameiop &= ~(MODMASK | OPMASK);
	fndp->ni_nameiop |= DELETE | LOCKPARENT | LOCKLEAF;
E 149
D 153
	(void)namei(fndp);
E 153
I 153
	(void)namei(fndp, p);
E 158
I 158
unlinkit:
	fndp->ni_nameiop &= ~MODMASK;
	fndp->ni_nameiop |= LOCKPARENT | LOCKLEAF;
	if ((fndp->ni_nameiop & SAVESTART) == 0)
		panic("ufs_rename: lost from startdir");
I 160
	p->p_spare[1]--;
E 160
	(void) lookup(fndp, p);
E 158
E 153
	if (fndp->ni_vp != NULL) {
		xp = VTOI(fndp->ni_vp);
		dp = VTOI(fndp->ni_dvp);
	} else {
I 105
D 146
		if (fndp->ni_dvp != NULL)
			vput(fndp->ni_dvp);
E 105
		xp = NULL;
E 102
		dp = NULL;
E 146
I 146
		/*
		 * From name has disappeared.
		 */
		if (doingdirectory)
			panic("rename: lost dir entry");
		vrele(ITOV(ip));
		return (0);
E 146
I 102
	}
E 102
E 86
E 82
E 80
	/*
D 84
	 * Insure directory entry still exists and
	 * has not changed since the start of all
	 * this.  If either has occured, forget about
D 79
	 * about deleting the original entry and just
	 * adjust the link count in the inode.
E 79
I 79
	 * about deleting the original entry.
E 84
I 84
D 102
	 * Insure that the directory entry still exists and has not
E 102
I 102
	 * Ensure that the directory entry still exists and has not
E 102
	 * changed while the new name has been entered. If the source is
	 * a file then the entry may have been unlinked or renamed. In
	 * either case there is no further work to be done. If the source
	 * is a directory then it cannot have been rmdir'ed; its link
	 * count of three would cause a rmdir to fail with ENOTEMPTY.
D 102
	 * The IRENAME flag insures that it cannot be moved by another
E 102
I 102
	 * The IRENAME flag ensures that it cannot be moved by another
E 102
	 * rename.
E 84
E 79
	 */
D 79
	if (dp == NULL || u.u_dent.d_ino != ip->i_number) {
		ip->i_nlink--;
		ip->i_flag |= ICHG;
	} else {
E 79
I 79
D 80
	if (dp != NULL && u.u_dent.d_ino == ip->i_number) {
E 80
I 80
D 84
	if (dp != NULL && zp == ip) {
E 84
I 84
D 86
	if (dp == NULL || xp != ip) {
E 86
I 86
	if (xp != ip) {
E 86
		if (doingdirectory)
D 86
			panic("rename: lost entry");
E 86
I 86
			panic("rename: lost dir entry");
E 86
	} else {
E 84
E 80
E 79
		/*
D 84
		 * If source is a directory, must adjust
		 * link count of parent directory also.
		 * If target didn't exist and source and
		 * target have the same parent, then we
		 * needn't touch the link count, it all
		 * balances out in the end.  Otherwise, we
		 * must do so to reflect deletion of ".."
		 * done above.
E 84
I 84
		 * If the source is a directory with a
		 * new parent, the link count of the old
		 * parent directory must be decremented
		 * and ".." set to point to the new parent.
E 84
		 */
D 84
		if (doingdirectory && (xp != NULL || parentdifferent)) {
E 84
I 84
		if (doingdirectory && newparent) {
E 84
			dp->i_nlink--;
			dp->i_flag |= ICHG;
I 84
D 116
			error = rdwri(UIO_READ, xp, (caddr_t)&dirbuf,
E 116
I 116
			error = vn_rdwr(UIO_READ, ITOV(xp), (caddr_t)&dirbuf,
E 116
D 102
				sizeof (struct dirtemplate), (off_t)0, 1,
				(int *)0);
E 102
I 102
				sizeof (struct dirtemplate), (off_t)0,
D 103
				UIO_USERSPACE, tndp->ni_cred, (int *)0);
E 103
I 103
D 116
				UIO_SYSSPACE, tndp->ni_cred, (int *)0);
E 116
I 116
				UIO_SYSSPACE, IO_NODELOCKED, 
D 155
				tndp->ni_cred, (int *)0);
E 155
I 155
				tndp->ni_cred, (int *)0, (struct proc *)0);
E 155
E 116
E 103
E 102
			if (error == 0) {
				if (dirbuf.dotdot_namlen != 2 ||
				    dirbuf.dotdot_name[0] != '.' ||
				    dirbuf.dotdot_name[1] != '.') {
D 118
					printf("rename: mangled dir\n");
E 118
I 118
					dirbad(xp, 12, "rename: mangled dir");
E 118
				} else {
					dirbuf.dotdot_ino = newparent;
D 116
					(void) rdwri(UIO_WRITE, xp,
E 116
I 116
					(void) vn_rdwr(UIO_WRITE, ITOV(xp),
E 116
					    (caddr_t)&dirbuf,
					    sizeof (struct dirtemplate),
D 102
					    (off_t)0, 1, (int *)0);
					cacheinval(dp);
E 102
I 102
D 103
					    (off_t)0, UIO_USERSPACE,
E 103
I 103
					    (off_t)0, UIO_SYSSPACE,
I 116
					    IO_NODELOCKED|IO_SYNC,
E 116
E 103
D 155
					    tndp->ni_cred, (int *)0);
E 155
I 155
					    tndp->ni_cred, (int *)0,
					    (struct proc *)0);
E 155
					cache_purge(ITOV(dp));
E 102
				}
			}
E 84
		}
D 82
		if (dirremove()) {
E 82
I 82
D 102
		if (dirremove(ndp)) {
E 102
I 102
		error = dirremove(fndp);
		if (!error) {
E 102
E 82
D 80
			ip->i_nlink--;
			ip->i_flag |= ICHG;
E 80
I 80
D 84
			zp->i_nlink--;
			zp->i_flag |= ICHG;
E 84
I 84
			xp->i_nlink--;
			xp->i_flag |= ICHG;
E 84
E 80
		}
I 52
D 84
		if (error == 0)		/* conservative */
E 84
I 84
		xp->i_flag &= ~IRENAME;
D 102
		if (error == 0)		/* XXX conservative */
E 84
			error = u.u_error;
E 102
E 52
	}
I 80
D 84
	if (zp != NULL)
		iput(zp);
E 80
	irele(ip);
E 84
	if (dp)
D 102
		iput(dp);
E 102
I 102
		vput(ITOV(dp));
E 102
I 84
	if (xp)
D 102
		iput(xp);
	irele(ip);
	if (error)
		u.u_error = error;
	return;
E 102
I 102
		vput(ITOV(xp));
	vrele(ITOV(ip));
	return (error);
E 102
E 84

D 84
	/*
	 * 4) Renaming a directory with the parent
	 *    different requires ".." to be rewritten.
	 *    The window is still there for ".." to
	 *    be inconsistent, but this is unavoidable,
	 *    and a lot shorter than when it was done
	 *    in a user process.
	 */
D 52
	if (doingdirectory && parentdifferent && u.u_error == 0) {
E 52
I 52
	if (doingdirectory && parentdifferent && error == 0) {
E 52
		struct dirtemplate dirbuf;

D 82
		u.u_dirp = uap->to;
		ip = namei(uchar, LOOKUP | LOCKPARENT, 0);
E 82
I 82
		ndp->ni_nameiop = LOOKUP | LOCKPARENT;
		ndp->ni_segflg = UIO_USERSPACE;
		ndp->ni_dirp = uap->to;
		ip = namei(ndp);
E 82
		if (ip == NULL) {
			printf("rename: .. went away\n");
			return;
		}
D 82
		dp = u.u_pdir;
E 82
I 82
		dp = ndp->ni_pdir;
E 82
		if ((ip->i_mode&IFMT) != IFDIR) {
			printf("rename: .. not a directory\n");
			goto stuck;
		}
D 52
		u.u_error = rdwri(UIO_READ, ip, (caddr_t)&dirbuf,
E 52
I 52
		error = rdwri(UIO_READ, ip, (caddr_t)&dirbuf,
E 52
			sizeof (struct dirtemplate), (off_t)0, 1, (int *)0);
D 52
		if (u.u_error == 0) {
E 52
I 52
		if (error == 0) {
E 52
			dirbuf.dotdot_ino = dp->i_number;
I 78
D 83
			dp->i_id = ++nextinodeid;
E 83
I 83
			cacheinval(dp);
E 83
E 78
			(void) rdwri(UIO_WRITE, ip, (caddr_t)&dirbuf,
			  sizeof (struct dirtemplate), (off_t)0, 1, (int *)0);
		}
stuck:
		irele(dp);
		iput(ip);
	}
D 52
	return;
E 52
I 52
	goto done;

E 84
E 52
bad:
D 53
	iput(u.u_pdir);
E 53
I 53
D 102
	iput(dp);
E 53
bad1:
E 102
	if (xp)
D 53
		irele(xp);
E 53
I 53
D 102
		iput(xp);
E 102
I 102
		vput(ITOV(xp));
	vput(ITOV(dp));
E 102
E 53
out:
	ip->i_nlink--;
	ip->i_flag |= ICHG;
D 102
	irele(ip);
I 52
D 84
done:
E 84
	if (error)
		u.u_error = error;
E 102
I 102
	vrele(ITOV(ip));
	return (error);
E 102
E 52
E 47
}

E 37
/*
D 102
 * Make a new file.
 */
struct inode *
D 82
maknode(mode)
E 82
I 82
maknode(mode, ndp)
E 82
	int mode;
I 82
	register struct nameidata *ndp;
E 82
{
	register struct inode *ip;
I 82
	register struct inode *pdir = ndp->ni_pdir;
E 82
	ino_t ipref;

	if ((mode & IFMT) == IFDIR)
D 82
		ipref = dirpref(u.u_pdir->i_fs);
E 82
I 82
		ipref = dirpref(pdir->i_fs);
E 82
	else
D 82
		ipref = u.u_pdir->i_number;
	ip = ialloc(u.u_pdir, ipref, mode);
E 82
I 82
		ipref = pdir->i_number;
	ip = ialloc(pdir, ipref, mode);
E 82
	if (ip == NULL) {
D 82
		iput(u.u_pdir);
E 82
I 82
		iput(pdir);
E 82
D 37
		return(NULL);
E 37
I 37
		return (NULL);
E 37
	}
D 37
#ifdef	QUOTA
E 37
I 37
#ifdef QUOTA
E 37
	if (ip->i_dquot != NODQUOT)
		panic("maknode: dquot");
#endif
	ip->i_flag |= IACC|IUPD|ICHG;
	if ((mode & IFMT) == 0)
		mode |= IFREG;
	ip->i_mode = mode & ~u.u_cmask;
	ip->i_nlink = 1;
	ip->i_uid = u.u_uid;
D 82
	ip->i_gid = u.u_pdir->i_gid;
E 82
I 82
	ip->i_gid = pdir->i_gid;
E 82
I 60
D 98
	if (ip->i_mode & ISGID && !groupmember(ip->i_gid))
E 98
I 98
D 101
	if (ip->i_mode & ISGID && !groupmember(ip->i_gid) && !suser())
E 101
I 101
	if (ip->i_mode & ISGID && !groupmember(ip->i_gid) &&
	    (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 101
E 98
		ip->i_mode &= ~ISGID;
E 60
D 37
#ifdef	QUOTA
E 37
I 37
#ifdef QUOTA
E 37
	ip->i_dquot = inoquota(ip);
#endif

	/*
	 * Make sure inode goes to disk before directory entry.
	 */
D 41
	iupdat(ip, &time, &time, 1);
E 41
I 41
D 45
	iupdat(ip, &time.tv_sec, &time.tv_sec, 1);
E 45
I 45
D 46
	iupdat(ip, time, time, 1);
E 46
I 46
	iupdat(ip, &time, &time, 1);
E 46
E 45
E 41
D 55
	direnter(ip);
E 55
I 55
D 82
	u.u_error = direnter(ip);
E 82
I 82
	u.u_error = direnter(ip, ndp);
E 82
E 55
	if (u.u_error) {
		/*
D 55
		 * write error occurred trying to update directory
		 * so must deallocate the inode
E 55
I 55
		 * Write error occurred trying to update directory
		 * so must deallocate the inode.
E 55
		 */
		ip->i_nlink = 0;
		ip->i_flag |= ICHG;
		iput(ip);
D 37
		return(NULL);
E 37
I 37
		return (NULL);
E 37
	}
D 37
	return(ip);
E 37
I 37
	return (ip);
I 63
}

/*
E 102
 * A virgin directory (no blushing please).
 */
struct dirtemplate mastertemplate = {
	0, 12, 1, ".",
	0, DIRBLKSIZ - 12, 2, ".."
};

/*
 * Mkdir system call
 */
D 102
mkdir()
E 102
I 102
D 155
ufs_mkdir(ndp, vap)
E 155
I 155
ufs_mkdir(ndp, vap, p)
E 155
	struct nameidata *ndp;
	struct vattr *vap;
I 155
	struct proc *p;
E 155
E 102
{
I 153
D 154
	struct proc *p = curproc;		/* XXX */
E 154
E 153
D 102
	struct a {
		char	*name;
		int	dmode;
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
E 102
E 82
	register struct inode *ip, *dp;
I 102
	struct inode *tip;
	struct vnode *dvp;
E 102
	struct dirtemplate dirtemplate;
I 82
D 102
	register struct nameidata *ndp = &u.u_nd;
E 102
I 102
	int error;
	int dmode;
E 102
E 82

I 158
#ifdef DIANOSTIC
	if ((ndp->ni_nameiop & HASBUF) == 0)
		panic("ufs_mkdir: no name");
#endif
E 158
D 82
	uap = (struct a *)u.u_ap;
	ip = namei(uchar, CREATE, 0);
E 82
I 82
D 102
	ndp->ni_nameiop = CREATE;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->name;
	ip = namei(ndp);
E 82
	if (u.u_error)
		return;
	if (ip != NULL) {
		iput(ip);
		u.u_error = EEXIST;
		return;
	}
D 82
	dp = u.u_pdir;
E 82
I 82
	dp = ndp->ni_pdir;
E 82
	uap->dmode &= 0777;
	uap->dmode |= IFDIR;
E 102
I 102
	dvp = ndp->ni_dvp;
	dp = VTOI(dvp);
I 147
	if ((unsigned short)dp->i_nlink >= LINK_MAX) {
I 158
		free(ndp->ni_pnbuf, M_NAMEI);
E 158
		iput(dp);
		return (EMLINK);
	}
E 147
	dmode = vap->va_mode&0777;
	dmode |= IFDIR;
E 102
	/*
D 158
	 * Must simulate part of maknode here
	 * in order to acquire the inode, but
	 * not have it entered in the parent
	 * directory.  The entry is made later
	 * after writing "." and ".." entries out.
E 158
I 158
	 * Must simulate part of maknode here to acquire the inode, but
	 * not have it entered in the parent directory. The entry is made
	 * later after writing "." and ".." entries.
E 158
	 */
D 102
	ip = ialloc(dp, dirpref(dp->i_fs), uap->dmode);
	if (ip == NULL) {
E 102
I 102
D 131
	error = ialloc(dp, dirpref(dp->i_fs), dmode, &tip);
	if (error) {
E 131
I 131
	if (error = ialloc(dp, dirpref(dp->i_fs), dmode, ndp->ni_cred, &tip)) {
I 158
		free(ndp->ni_pnbuf, M_NAMEI);
E 158
E 131
E 102
		iput(dp);
D 102
		return;
E 102
I 102
		return (error);
E 102
	}
I 102
	ip = tip;
I 131
	ip->i_uid = ndp->ni_cred->cr_uid;
	ip->i_gid = dp->i_gid;
E 131
E 102
#ifdef QUOTA
D 131
	if (ip->i_dquot != NODQUOT)
		panic("mkdir: dquot");
E 131
I 131
	if ((error = getinoquota(ip)) ||
	    (error = chkiq(ip, 1, ndp->ni_cred, 0))) {
I 158
		free(ndp->ni_pnbuf, M_NAMEI);
E 158
		ifree(ip, ip->i_number, dmode);
		iput(ip);
		iput(dp);
		return (error);
	}
E 131
#endif
	ip->i_flag |= IACC|IUPD|ICHG;
D 102
	ip->i_mode = uap->dmode & ~u.u_cmask;
E 102
I 102
	ip->i_mode = dmode;
	ITOV(ip)->v_type = VDIR;	/* Rest init'd in iget() */
E 102
	ip->i_nlink = 2;
D 102
	ip->i_uid = u.u_uid;
E 102
I 102
D 131
	ip->i_uid = ndp->ni_cred->cr_uid;
E 102
	ip->i_gid = dp->i_gid;
#ifdef QUOTA
	ip->i_dquot = inoquota(ip);
#endif
E 131
D 102
	iupdat(ip, &time, &time, 1);
E 102
I 102
	error = iupdat(ip, &time, &time, 1);
E 102

	/*
	 * Bump link count in parent directory
	 * to reflect work done below.  Should
	 * be done before reference is created
	 * so reparation is possible if we crash.
	 */
	dp->i_nlink++;
	dp->i_flag |= ICHG;
D 102
	iupdat(dp, &time, &time, 1);
E 102
I 102
D 151
	error = iupdat(dp, &time, &time, 1);
E 151
I 151
	if (error = iupdat(dp, &time, &time, 1))
		goto bad;
E 151
E 102

	/*
	 * Initialize directory with "."
	 * and ".." from static template.
	 */
	dirtemplate = mastertemplate;
	dirtemplate.dot_ino = ip->i_number;
	dirtemplate.dotdot_ino = dp->i_number;
D 102
	u.u_error = rdwri(UIO_WRITE, ip, (caddr_t)&dirtemplate,
		sizeof (dirtemplate), (off_t)0, 1, (int *)0);
	if (u.u_error) {
E 102
I 102
D 116
	error = rdwri(UIO_WRITE, ip, (caddr_t)&dirtemplate,
E 116
I 116
	error = vn_rdwr(UIO_WRITE, ITOV(ip), (caddr_t)&dirtemplate,
E 116
D 155
		sizeof (dirtemplate), (off_t)0, UIO_SYSSPACE,
D 116
		ndp->ni_cred, (int *)0);
E 116
I 116
		IO_NODELOCKED|IO_SYNC, ndp->ni_cred, (int *)0);
E 155
I 155
	    sizeof (dirtemplate), (off_t)0, UIO_SYSSPACE,
	    IO_NODELOCKED|IO_SYNC, ndp->ni_cred, (int *)0, (struct proc *)0);
E 155
E 116
	if (error) {
E 102
		dp->i_nlink--;
		dp->i_flag |= ICHG;
		goto bad;
	}
I 87
D 102
	if (DIRBLKSIZ > ip->i_fs->fs_fsize)
		panic("mkdir: blksize");     /* XXX - should grow with bmap() */
E 102
I 102
D 139
	if (DIRBLKSIZ > dp->i_fs->fs_fsize)
E 139
I 139
	if (DIRBLKSIZ > dp->i_fs->fs_fsize) {
E 139
		panic("mkdir: blksize");     /* XXX - should grow w/balloc() */
E 102
D 139
	else
E 139
I 139
	} else {
E 139
		ip->i_size = DIRBLKSIZ;
I 139
		ip->i_flag |= ICHG;
	}
E 139
E 87
	/*
	 * Directory all set up, now
	 * install the entry for it in
	 * the parent directory.
	 */
D 82
	u.u_error = direnter(ip);
E 82
I 82
D 102
	u.u_error = direnter(ip, ndp);
E 102
I 102
D 151
	error = direnter(ip, ndp);
E 102
E 82
	dp = NULL;
D 102
	if (u.u_error) {
E 102
I 102
	if (error) {
E 151
I 151
	if (error = direnter(ip, ndp)) {
E 151
E 102
D 82
		u.u_dirp = uap->name;
D 74
		dp = namei(uchar, LOOKUP, 0);
E 74
I 74
		dp = namei(uchar, LOOKUP | NOCACHE, 0);
E 82
I 82
D 149
		ndp->ni_nameiop = LOOKUP | NOCACHE;
E 149
I 149
D 154
		ndp->ni_nameiop &= ~(MODMASK | OPMASK);
D 151
		ndp->ni_nameiop |= LOOKUP | NOCACHE;
E 151
I 151
		ndp->ni_nameiop |= LOOKUP | LOCKLEAF | NOCACHE;
E 151
E 149
D 102
		ndp->ni_segflg = UIO_USERSPACE;
		ndp->ni_dirp = uap->name;
		dp = namei(ndp);
E 82
E 74
		if (dp) {
E 102
I 102
D 153
		error = namei(ndp);
E 153
I 153
		error = namei(ndp, p);
E 153
		if (!error) {
I 151
			iput(dp);
E 151
			dp = VTOI(ndp->ni_vp);
E 102
			dp->i_nlink--;
			dp->i_flag |= ICHG;
		}
E 154
I 154
		dp->i_nlink--;
		dp->i_flag |= ICHG;
E 154
	}
bad:
	/*
	 * No need to do an explicit itrunc here,
D 102
	 * irele will do this for us because we set
E 102
I 102
	 * vrele will do this for us because we set
E 102
	 * the link count to 0.
	 */
D 102
	if (u.u_error) {
E 102
I 102
	if (error) {
E 102
		ip->i_nlink = 0;
		ip->i_flag |= ICHG;
D 106
	}
I 102
	iput(ip);
E 106
I 106
		iput(ip);
	} else
		ndp->ni_vp = ITOV(ip);
I 158
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 158
E 106
E 102
D 151
	if (dp)
		iput(dp);
E 151
I 151
	iput(dp);
E 151
D 102
	iput(ip);
E 102
I 102
	return (error);
E 102
}

/*
 * Rmdir system call.
 */
D 102
rmdir()
E 102
I 102
D 155
ufs_rmdir(ndp)
E 155
I 155
ufs_rmdir(ndp, p)
E 155
	register struct nameidata *ndp;
I 155
	struct proc *p;
E 155
E 102
{
D 102
	struct a {
		char	*name;
D 82
	};
E 82
I 82
	} *uap = (struct a *)u.u_ap;
E 102
E 82
	register struct inode *ip, *dp;
I 82
D 102
	register struct nameidata *ndp = &u.u_nd;
E 102
I 102
	int error = 0;
E 102
E 82

D 82
	ip = namei(uchar, DELETE | LOCKPARENT, 0);
E 82
I 82
D 102
	ndp->ni_nameiop = DELETE | LOCKPARENT;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->name;
	ip = namei(ndp);
E 82
	if (ip == NULL)
		return;
D 82
	dp = u.u_pdir;
E 82
I 82
	dp = ndp->ni_pdir;
E 102
I 102
	ip = VTOI(ndp->ni_vp);
	dp = VTOI(ndp->ni_dvp);
E 102
E 82
	/*
	 * No rmdir "." please.
	 */
	if (dp == ip) {
D 102
		irele(dp);
E 102
I 102
		vrele(ITOV(dp));
E 102
		iput(ip);
D 102
		u.u_error = EINVAL;
		return;
E 102
I 102
		return (EINVAL);
E 102
	}
D 102
	if ((ip->i_mode&IFMT) != IFDIR) {
		u.u_error = ENOTDIR;
		goto out;
	}
E 102
	/*
D 102
	 * Don't remove a mounted on directory.
	 */
	if (ip->i_dev != dp->i_dev) {
		u.u_error = EBUSY;
		goto out;
	}
	/*
E 102
	 * Verify the directory is empty (and valid).
	 * (Rmdir ".." won't be valid since
	 *  ".." will contain a reference to
	 *  the current directory and thus be
	 *  non-empty.)
	 */
D 84
	if (ip->i_nlink != 2 || !dirempty(ip)) {
E 84
I 84
D 102
	if (ip->i_nlink != 2 || !dirempty(ip, dp->i_number)) {
E 84
		u.u_error = ENOTEMPTY;
E 102
I 102
	if (ip->i_nlink != 2 || !dirempty(ip, dp->i_number, ndp->ni_cred)) {
		error = ENOTEMPTY;
E 102
		goto out;
	}
	/*
	 * Delete reference to directory before purging
	 * inode.  If we crash in between, the directory
	 * will be reattached to lost+found,
	 */
D 82
	if (dirremove() == 0)
E 82
I 82
D 102
	if (dirremove(ndp) == 0)
E 102
I 102
	if (error = dirremove(ndp))
E 102
E 82
		goto out;
	dp->i_nlink--;
	dp->i_flag |= ICHG;
I 84
D 102
	cacheinval(dp);
E 102
I 102
	cache_purge(ITOV(dp));
E 102
E 84
	iput(dp);
D 102
	dp = NULL;
E 102
I 102
	ndp->ni_dvp = NULL;
E 102
	/*
	 * Truncate inode.  The only stuff left
	 * in the directory is "." and "..".  The
	 * "." reference is inconsequential since
	 * we're quashing it.  The ".." reference
	 * has already been adjusted above.  We've
	 * removed the "." reference and the reference
	 * in the parent directory, but there may be
	 * other hard links so decrement by 2 and
	 * worry about them later.
	 */
	ip->i_nlink -= 2;
D 102
	itrunc(ip, (u_long)0);
I 83
	cacheinval(ip);
E 102
I 102
D 120
	error = itrunc(ip, (u_long)0);
E 120
I 120
	error = itrunc(ip, (u_long)0, IO_SYNC);
E 120
	cache_purge(ITOV(ip));
E 102
E 83
out:
D 102
	if (dp)
E 102
I 102
	if (ndp->ni_dvp)
E 102
		iput(dp);
	iput(ip);
I 102
	return (error);
E 102
}

D 102
struct file *
getinode(fdes)
	int fdes;
E 102
I 102
/*
 * symlink -- make a symbolic link
 */
D 155
ufs_symlink(ndp, vap, target)
E 155
I 155
ufs_symlink(ndp, vap, target, p)
E 155
	struct nameidata *ndp;
	struct vattr *vap;
	char *target;
I 155
	struct proc *p;
E 155
E 102
{
D 77
	register struct file *fp;
E 77
I 77
D 102
	struct file *fp;
E 102
I 102
	struct inode *ip;
	int error;
E 102
E 77

D 77
	fp = getf(fdes);
	if (fp == 0)
		return (0);
E 77
I 77
D 102
	if ((unsigned)fdes >= NOFILE || (fp = u.u_ofile[fdes]) == NULL) {
		u.u_error = EBADF;
		return ((struct file *)0);
E 102
I 102
	error = maknode(IFLNK | vap->va_mode, ndp, &ip);
	if (error)
		return (error);
D 116
	error = rdwri(UIO_WRITE, ip, target, strlen(target), (off_t)0,
		UIO_SYSSPACE, ndp->ni_cred, (int *)0);
E 116
I 116
	error = vn_rdwr(UIO_WRITE, ITOV(ip), target, strlen(target), (off_t)0,
D 155
		UIO_SYSSPACE, IO_NODELOCKED, ndp->ni_cred, (int *)0);
E 155
I 155
		UIO_SYSSPACE, IO_NODELOCKED, ndp->ni_cred, (int *)0,
		(struct proc *)0);
E 155
E 116
	iput(ip);
	return (error);
}

/*
 * Vnode op for read and write
 */
D 116
ufs_readdir(vp, uio, offp, cred)
E 116
I 116
D 128
ufs_readdir(vp, uio, cred)
E 128
I 128
ufs_readdir(vp, uio, cred, eofflagp)
E 128
E 116
	struct vnode *vp;
	register struct uio *uio;
D 116
	off_t *offp;
E 116
	struct ucred *cred;
I 128
	int *eofflagp;
E 128
{
D 116
	register struct inode *ip = VTOI(vp);
	int count, error;
E 116
I 116
	int count, lost, error;
E 116

D 116
	ILOCK(ip);
	uio->uio_offset = *offp;
E 116
	count = uio->uio_resid;
	count &= ~(DIRBLKSIZ - 1);
D 116
	if (vp->v_type != VDIR || uio->uio_iovcnt != 1 ||
	    (count < DIRBLKSIZ) || (uio->uio_offset & (DIRBLKSIZ -1))) {
		IUNLOCK(ip);
E 116
I 116
	lost = uio->uio_resid - count;
	if (count < DIRBLKSIZ || (uio->uio_offset & (DIRBLKSIZ -1)))
E 116
		return (EINVAL);
E 102
D 116
	}
E 116
E 77
D 102
	if (fp->f_type != DTYPE_INODE) {
		u.u_error = EINVAL;
D 77
		return (0);
E 77
I 77
		return ((struct file *)0);
E 102
I 102
	uio->uio_resid = count;
	uio->uio_iov->iov_len = count;
D 116
	error = readip(ip, uio, cred);
	*offp += count - uio->uio_resid;
	IUNLOCK(ip);
E 116
I 116
	error = ufs_read(vp, uio, 0, cred);
	uio->uio_resid += lost;
I 128
	if ((VTOI(vp)->i_size - uio->uio_offset) <= 0)
		*eofflagp = 1;
	else
		*eofflagp = 0;
E 128
E 116
	return (error);
}

/*
 * Return target name of a symbolic link
 */
ufs_readlink(vp, uiop, cred)
	struct vnode *vp;
	struct uio *uiop;
	struct ucred *cred;
{

D 116
	return (readip(VTOI(vp), uiop, cred));
E 116
I 116
	return (ufs_read(vp, uiop, 0, cred));
E 116
}

/*
 * Ufs abort op, called after namei() when a CREATE/DELETE isn't actually
D 137
 * done. Iff ni_vp/ni_dvp not null and locked, unlock.
E 137
I 137
D 158
 * done. Nothing to do at the moment.
E 158
I 158
 * done. If a buffer has been saved in anticipation of a CREATE, delete it.
E 158
E 137
 */
I 137
/* ARGSUSED */
E 137
ufs_abortop(ndp)
D 137
	register struct nameidata *ndp;
E 137
I 137
	struct nameidata *ndp;
E 137
{
D 125
	register struct inode *ip;
E 125

I 158
	if ((ndp->ni_nameiop & (HASBUF | SAVESTART)) == HASBUF)
		FREE(ndp->ni_pnbuf, M_NAMEI);
E 158
D 125
	if (ndp->ni_vp) {
		ip = VTOI(ndp->ni_vp);
		if (ip->i_flag & ILOCKED)
			IUNLOCK(ip);
		vrele(ndp->ni_vp);
E 102
E 77
	}
E 125
D 102
	return (fp);
E 102
I 102
D 137
	if (ndp->ni_dvp) {
D 125
		ip = VTOI(ndp->ni_dvp);
		if (ip->i_flag & ILOCKED)
			IUNLOCK(ip);
E 125
I 125
		if (VOP_ISLOCKED(ndp->ni_dvp))
			VOP_UNLOCK(ndp->ni_dvp);
E 125
		vrele(ndp->ni_dvp);
I 125
	}
	if (ndp->ni_vp) {
		if (VOP_ISLOCKED(ndp->ni_vp))
			VOP_UNLOCK(ndp->ni_vp);
		vrele(ndp->ni_vp);
E 125
	}
	return;
E 137
I 137
	return (0);
E 137
E 102
}

I 124
/*
 * Lock an inode.
 */
E 124
I 102
ufs_lock(vp)
	struct vnode *vp;
{
	register struct inode *ip = VTOI(vp);

	ILOCK(ip);
	return (0);
}

I 124
/*
 * Unlock an inode.
 */
E 124
ufs_unlock(vp)
	struct vnode *vp;
{
	register struct inode *ip = VTOI(vp);

	if (!(ip->i_flag & ILOCKED))
		panic("ufs_unlock NOT LOCKED");
	IUNLOCK(ip);
I 124
	return (0);
}

/*
 * Check for a locked inode.
 */
ufs_islocked(vp)
	struct vnode *vp;
{

	if (VTOI(vp)->i_flag & ILOCKED)
		return (1);
E 124
	return (0);
}

E 102
/*
D 102
 * mode mask for creation of files
E 102
I 102
 * Get access to bmap
E 102
 */
D 102
umask()
E 102
I 102
ufs_bmap(vp, bn, vpp, bnp)
	struct vnode *vp;
	daddr_t bn;
	struct vnode **vpp;
	daddr_t *bnp;
E 102
{
D 102
	register struct a {
		int	mask;
D 82
	} *uap;
E 82
I 82
	} *uap = (struct a *)u.u_ap;
E 102
I 102
	struct inode *ip = VTOI(vp);
E 102
E 82

D 82
	uap = (struct a *)u.u_ap;
E 82
D 102
	u.u_r.r_val1 = u.u_cmask;
	u.u_cmask = uap->mask & 07777;
E 102
I 102
	if (vpp != NULL)
		*vpp = ip->i_devvp;
	if (bnp == NULL)
		return (0);
D 134
	return (bmap(ip, bn, bnp, (daddr_t *)0, (int *)0));
E 134
I 134
	return (bmap(ip, bn, bnp));
E 134
}

/*
D 134
 * Just call the device strategy routine
E 134
I 134
 * Calculate the logical to physical mapping if not done already,
 * then call the device strategy routine.
E 134
 */
I 120
D 134
int checkoverlap = 1;
E 134
I 134
int checkoverlap = 0;
E 134

E 120
ufs_strategy(bp)
	register struct buf *bp;
{
D 120
	(*bdevsw[major(bp->b_dev)].d_strategy)(bp);
E 120
I 120
	register struct inode *ip = VTOI(bp->b_vp);
D 134
	register struct buf *ep;
E 134
	struct vnode *vp;
D 134
	struct buf *ebp;
	daddr_t start, last;
E 134
	int error;

	if (bp->b_vp->v_type == VBLK || bp->b_vp->v_type == VCHR)
		panic("ufs_strategy: spec");
	if (bp->b_blkno == bp->b_lblkno) {
		if (error = bmap(ip, bp->b_lblkno, &bp->b_blkno))
			return (error);
D 122
		if ((long)bp->b_blkno == -1) {
E 122
I 122
		if ((long)bp->b_blkno == -1)
E 122
			clrbuf(bp);
D 122
			biodone(bp);
		}
E 122
	}
D 122
	if ((long)bp->b_blkno == -1)
E 122
I 122
	if ((long)bp->b_blkno == -1) {
		biodone(bp);
E 122
		return (0);
I 122
	}
I 134
#ifdef DIAGNOSTIC
E 134
E 122
	if (checkoverlap) {
I 134
		register struct buf *ep;
		struct buf *ebp;
		daddr_t start, last;

E 134
		ebp = &buf[nbuf];
		start = bp->b_blkno;
		last = start + btodb(bp->b_bcount) - 1;
		for (ep = buf; ep < ebp; ep++) {
			if (ep == bp || (ep->b_flags & B_INVAL) ||
D 132
			    ep->b_vp == (struct vnode *)0)
E 132
I 132
			    ep->b_vp == NULLVP)
E 132
				continue;
			if (VOP_BMAP(ep->b_vp, (daddr_t)0, &vp, (daddr_t)0))
				continue;
			if (vp != ip->i_devvp)
				continue;
			/* look for overlap */
			if (ep->b_bcount == 0 || ep->b_blkno > last ||
			    ep->b_blkno + btodb(ep->b_bcount) <= start)
				continue;
D 122
			panic("Disk overlap");
E 122
I 122
			vprint("Disk overlap", vp);
			printf("\tstart %d, end %d overlap start %d, end %d\n",
				start, last, ep->b_blkno,
				ep->b_blkno + btodb(ep->b_bcount) - 1);
I 134
			panic("Disk buffer overlap");
E 134
E 122
		}
	}
I 134
#endif /* DIAGNOSTIC */
E 134
	vp = ip->i_devvp;
	bp->b_dev = vp->v_rdev;
D 159
	(*(vp->v_op->vn_strategy))(bp);
E 159
I 159
	(*(vp->v_op->vop_strategy))(bp);
E 159
E 120
	return (0);
I 120
}

/*
 * Print out the contents of an inode.
 */
ufs_print(vp)
	struct vnode *vp;
{
	register struct inode *ip = VTOI(vp);

D 127
	printf("tag VT_UFS, ino %d, on dev %d, %d%s\n", ip->i_number,
		major(ip->i_dev), minor(ip->i_dev),
		(ip->i_flag & ILOCKED) ? " (LOCKED)" : "");
E 127
I 127
	printf("tag VT_UFS, ino %d, on dev %d, %d", ip->i_number,
		major(ip->i_dev), minor(ip->i_dev));
#ifdef FIFO
	if (vp->v_type == VFIFO)
		fifo_printinfo(vp);
#endif /* FIFO */
	printf("%s\n", (ip->i_flag & ILOCKED) ? " (LOCKED)" : "");
E 127
I 123
	if (ip->i_spare0 == 0)
		return;
	printf("\towner pid %d", ip->i_spare0);
	if (ip->i_spare1)
		printf(" waiting pid %d", ip->i_spare1);
	printf("\n");
E 123
E 120
I 119
}

/*
 * Read wrapper for special devices.
 */
ufsspec_read(vp, uio, ioflag, cred)
	struct vnode *vp;
	struct uio *uio;
	int ioflag;
	struct ucred *cred;
{

	/*
	 * Set access flag.
	 */
	VTOI(vp)->i_flag |= IACC;
	return (spec_read(vp, uio, ioflag, cred));
}

/*
 * Write wrapper for special devices.
 */
ufsspec_write(vp, uio, ioflag, cred)
	struct vnode *vp;
	struct uio *uio;
	int ioflag;
	struct ucred *cred;
{

	/*
	 * Set update and change flags.
	 */
	VTOI(vp)->i_flag |= IUPD|ICHG;
	return (spec_write(vp, uio, ioflag, cred));
}

/*
 * Close wrapper for special devices.
 *
 * Update the times on the inode then do device close.
 */
D 155
ufsspec_close(vp, fflag, cred)
E 155
I 155
ufsspec_close(vp, fflag, cred, p)
E 155
	struct vnode *vp;
	int fflag;
	struct ucred *cred;
I 155
	struct proc *p;
E 155
{
	register struct inode *ip = VTOI(vp);

D 121
	if (vp->v_count > 1 && !(ip->i_flag & ILOCKED))
E 121
I 121
	if (vp->v_usecount > 1 && !(ip->i_flag & ILOCKED))
E 121
		ITIMES(ip, &time, &time);
D 155
	return (spec_close(vp, fflag, cred));
E 155
I 155
	return (spec_close(vp, fflag, cred, p));
E 155
E 119
}
I 126

#ifdef FIFO
/*
 * Read wrapper for fifo's
 */
ufsfifo_read(vp, uio, ioflag, cred)
	struct vnode *vp;
	struct uio *uio;
	int ioflag;
	struct ucred *cred;
{

	/*
	 * Set access flag.
	 */
	VTOI(vp)->i_flag |= IACC;
	return (fifo_read(vp, uio, ioflag, cred));
}

/*
 * Write wrapper for fifo's.
 */
ufsfifo_write(vp, uio, ioflag, cred)
	struct vnode *vp;
	struct uio *uio;
	int ioflag;
	struct ucred *cred;
{

	/*
	 * Set update and change flags.
	 */
	VTOI(vp)->i_flag |= IUPD|ICHG;
	return (fifo_write(vp, uio, ioflag, cred));
}

/*
 * Close wrapper for fifo's.
 *
 * Update the times on the inode then do device close.
 */
D 155
ufsfifo_close(vp, fflag, cred)
E 155
I 155
ufsfifo_close(vp, fflag, cred, p)
E 155
	struct vnode *vp;
	int fflag;
	struct ucred *cred;
I 155
	struct proc *p;
E 155
{
	register struct inode *ip = VTOI(vp);

	if (vp->v_usecount > 1 && !(ip->i_flag & ILOCKED))
		ITIMES(ip, &time, &time);
D 155
	return (fifo_close(vp, fflag, cred));
E 155
I 155
	return (fifo_close(vp, fflag, cred, p));
E 155
}
#endif /* FIFO */
E 126

/*
D 156
 * Make a new file.
E 156
I 156
 * Allocate a new inode.
E 156
 */
maknode(mode, ndp, ipp)
	int mode;
	register struct nameidata *ndp;
	struct inode **ipp;
{
	register struct inode *ip;
	struct inode *tip;
	register struct inode *pdir = VTOI(ndp->ni_dvp);
	ino_t ipref;
	int error;

I 158
#ifdef DIANOSTIC
	if ((ndp->ni_nameiop & HASBUF) == 0)
		panic("maknode: no name");
#endif
E 158
	*ipp = 0;
I 131
	if ((mode & IFMT) == 0)
		mode |= IFREG;
E 131
	if ((mode & IFMT) == IFDIR)
		ipref = dirpref(pdir->i_fs);
	else
		ipref = pdir->i_number;
D 131
	error = ialloc(pdir, ipref, mode, &tip);
	if (error) {
E 131
I 131
	if (error = ialloc(pdir, ipref, mode, ndp->ni_cred, &tip)) {
I 158
		free(ndp->ni_pnbuf, M_NAMEI);
E 158
E 131
		iput(pdir);
		return (error);
	}
	ip = tip;
I 131
	ip->i_uid = ndp->ni_cred->cr_uid;
	ip->i_gid = pdir->i_gid;
E 131
#ifdef QUOTA
D 131
	if (ip->i_dquot != NODQUOT)
		panic("maknode: dquot");
E 131
I 131
	if ((error = getinoquota(ip)) ||
	    (error = chkiq(ip, 1, ndp->ni_cred, 0))) {
I 158
		free(ndp->ni_pnbuf, M_NAMEI);
E 158
		ifree(ip, ip->i_number, mode);
		iput(ip);
		iput(pdir);
		return (error);
	}
E 131
#endif
	ip->i_flag |= IACC|IUPD|ICHG;
D 131
	if ((mode & IFMT) == 0)
		mode |= IFREG;
E 131
	ip->i_mode = mode;
	ITOV(ip)->v_type = IFTOVT(mode);	/* Rest init'd in iget() */
	ip->i_nlink = 1;
D 131
	ip->i_uid = ndp->ni_cred->cr_uid;
	ip->i_gid = pdir->i_gid;
E 131
	if ((ip->i_mode & ISGID) && !groupmember(ip->i_gid, ndp->ni_cred) &&
	    suser(ndp->ni_cred, NULL))
		ip->i_mode &= ~ISGID;
D 131
#ifdef QUOTA
	ip->i_dquot = inoquota(ip);
#endif
E 131

	/*
	 * Make sure inode goes to disk before directory entry.
	 */
D 131
	if ((error = iupdat(ip, &time, &time, 1)) ||
	    (error = direnter(ip, ndp))) {
		/*
		 * Write error occurred trying to update the inode
		 * or the directory so must deallocate the inode.
		 */
		ip->i_nlink = 0;
		ip->i_flag |= ICHG;
		iput(ip);
		return (error);
E 131
I 131
	if (error = iupdat(ip, &time, &time, 1))
		goto bad;
D 151
	if (error = direnter(ip, ndp)) {
		pdir = NULL;
E 151
I 151
	if (error = direnter(ip, ndp))
E 151
		goto bad;
I 158
	if ((ndp->ni_nameiop & SAVESTART) == 0)
		FREE(ndp->ni_pnbuf, M_NAMEI);
E 158
E 131
D 151
	}
E 151
I 151
	iput(pdir);
E 151
	*ipp = ip;
	return (0);
I 131

bad:
	/*
	 * Write error occurred trying to update the inode
	 * or the directory so must deallocate the inode.
	 */
I 158
	free(ndp->ni_pnbuf, M_NAMEI);
E 158
D 151
	if (pdir)
		iput(pdir);
E 151
I 151
	iput(pdir);
E 151
	ip->i_nlink = 0;
	ip->i_flag |= ICHG;
	iput(ip);
	return (error);
I 145
}

/*
 * Advisory record locking support
 */
ufs_advlock(vp, id, op, fl, flags)
	struct vnode *vp;
	caddr_t id;
	int op;
	register struct flock *fl;
	int flags;
{
	register struct inode *ip = VTOI(vp);
	register struct lockf *lock;
	off_t start, end;
	int error;

	/*
	 * Avoid the common case of unlocking when inode has no locks.
	 */
	if (ip->i_lockf == (struct lockf *)0) {
		if (op != F_SETLK) {
			fl->l_type = F_UNLCK;
			return (0);
		}
	}
	/*
	 * Convert the flock structure into a start and end.
	 */
	switch (fl->l_whence) {

	case SEEK_SET:
	case SEEK_CUR:
		/*
		 * Caller is responsible for adding any necessary offset
		 * when SEEK_CUR is used.
		 */
		start = fl->l_start;
		break;

	case SEEK_END:
		start = ip->i_size + fl->l_start;
		break;

	default:
		return (EINVAL);
	}
	if (start < 0)
		return (EINVAL);
	if (fl->l_len == 0)
		end = -1;
	else
D 148
		end = start + fl->l_len;
E 148
I 148
		end = start + fl->l_len - 1;
E 148
	/*
	 * Create the lockf structure
	 */
	MALLOC(lock, struct lockf *, sizeof *lock, M_LOCKF, M_WAITOK);
	lock->lf_start = start;
	lock->lf_end = end;
	lock->lf_id = id;
	lock->lf_inode = ip;
	lock->lf_type = fl->l_type;
	lock->lf_next = (struct lockf *)0;
	lock->lf_block = (struct lockf *)0;
	lock->lf_flags = flags;
	/*
	 * Do the requested operation.
	 */
	switch(op) {
	case F_SETLK:
D 150
		return (ufs_setlock(lock));
E 150
I 150
		return (lf_setlock(lock));
E 150

	case F_UNLCK:
D 150
		return (ufs_advunlock(lock));
E 150
I 150
		error = lf_clearlock(lock);
		FREE(lock, M_LOCKF);
		return (error);
E 150

	case F_GETLK:
D 150
		return (ufs_advgetlock(lock, fl));
E 150
I 150
		error = lf_getlock(lock, fl);
		FREE(lock, M_LOCKF);
		return (error);
E 150
	
	default:
		free(lock, M_LOCKF);
		return (EINVAL);
	}
	/* NOTREACHED */
D 150
}

/*
 * This variable controls the maximum number of processes that will
 * be checked in doing deadlock detection.
 */
int maxlockdepth = MAXDEPTH;

/*
 * Set a byte-range lock.
 */
ufs_setlock(lock)
	register struct lockf *lock;
{
	register struct inode *ip = lock->lf_inode;
	register struct lockf *block;
	static char lockstr[] = "lockf";
	int priority, error;

#ifdef LOCKF_DEBUG
	if (lockf_debug & 4)
		lf_print("ufs_setlock", lock);
#endif /* LOCKF_DEBUG */

	/*
	 * Set the priority
	 */
	priority = PLOCK;
	if ((lock->lf_type & F_WRLCK) == 0)
		priority += 4;
	priority |= PCATCH;
	/*
	 * Scan lock list for this file looking for locks that would block us.
	 */
	while (block = lf_getblock(lock)) {
		/*
		 * Free the structure and return if nonblocking.
		 */
		if ((lock->lf_flags & F_WAIT) == 0) {
			free(lock, M_LOCKF);
			return (EAGAIN);
		}
		/*
		 * We are blocked. Since flock style locks cover
		 * the whole file, there is no chance for deadlock.
		 * For byte-range locks we must check for deadlock.
		 *
		 * Deadlock detection is done by looking through the
		 * wait channels to see if there are any cycles that
		 * involve us. MAXDEPTH is set just to make sure we
		 * do not go off into neverland.
		 */
		if ((lock->lf_flags & F_POSIX) &&
		    (block->lf_flags & F_POSIX)) {
			register struct proc *wproc;
			register struct lockf *waitblock;
			int i = 0;

			/* The block is waiting on something */
			wproc = (struct proc *)block->lf_id;
			while (wproc->p_wchan &&
			       (wproc->p_wmesg == lockstr) &&
			       (i++ < maxlockdepth)) {
				waitblock = (struct lockf *)wproc->p_wchan;
				/* Get the owner of the blocking lock */
				waitblock = waitblock->lf_next;
				if ((waitblock->lf_flags & F_POSIX) == 0)
					break;
				wproc = (struct proc *)waitblock->lf_id;
				if (wproc == (struct proc *)lock->lf_id) {
					free(lock, M_LOCKF);
					return (EDEADLK);
				}
			}
		}
		/*
		 * Add our lock to the blocked
		 * list and sleep until we're free.
		 */
D 148
#ifdef	LOCKF_DEBUG
E 148
I 148
#ifdef LOCKF_DEBUG
E 148
		if (lockf_debug & 4)
			lf_print("ufs_advlock: blocking on", block);
#endif /* LOCKF_DEBUG */
		/*
		 * Remember who blocked us (for deadlock detection)
		 */
		lock->lf_next = block;
		lf_addblock(block, lock);
		if (error = tsleep((caddr_t *)lock, priority, lockstr, 0)) {
			free(lock, M_LOCKF);
			return (error);
		}
	}
	/*
	 * No blocks!!  Add the lock.  Note that addlock will
	 * downgrade or upgrade any overlapping locks this
	 * process already owns.
	 */
D 148
#ifdef	LOCKF_DEBUG
	if (lockf_debug & 4)
E 148
I 148
	lf_addlock(lock);
#ifdef LOCKF_DEBUG
	if (lockf_debug & 4) {
E 148
		lf_print("ufs_advlock: got the lock", lock);
I 148
		lf_printlist(lock);
	}
E 148
#endif /* LOCKF_DEBUG */
D 148
	lf_addlock(lock);
E 148
	return (0);
}

/*
 * Remove a byte-range lock on an inode.
 */
ufs_advunlock(lock)
	struct lockf *lock;
{
	struct lockf *blocklist;

	if (lock->lf_inode->i_lockf == (struct lockf *)0)
		return (0);
D 148
#ifdef	LOCKF_DEBUG
E 148
I 148
#ifdef LOCKF_DEBUG
E 148
	if (lockf_debug & 4)
		lf_print("ufs_advunlock", lock);
#endif /* LOCKF_DEBUG */
	/*
	 * Generally, find the lock (or an overlap to that lock)
	 * and remove it (or shrink it), then wakeup anyone we can.
	 */
	blocklist = lf_remove(lock);
I 148
#ifdef LOCKF_DEBUG
	lf_printlist(lock);
#endif /* LOCKF_DEBUG */
E 148
	FREE(lock, M_LOCKF);
	lf_wakelock(blocklist);
	return (0);
}

/*
 * Return the blocking pid
 */
ufs_advgetlock(lock, fl)
	register struct lockf *lock;
	register struct flock *fl;
{
	register struct lockf *block;
	off_t start, end;

D 148
#ifdef	LOCKF_DEBUG
E 148
I 148
#ifdef LOCKF_DEBUG
E 148
	if (lockf_debug & 4)
		lf_print("ufs_advgetlock", lock);
#endif /* LOCKF_DEBUG */

	if (block = lf_getblock(lock)) {
		fl->l_type = block->lf_type;
		fl->l_whence = SEEK_SET;
		fl->l_start = block->lf_start;
		if (block->lf_end == -1)
			fl->l_len = 0;
		else
D 148
			fl->l_len = block->lf_end - block->lf_start;
E 148
I 148
			fl->l_len = block->lf_end - block->lf_start + 1;
E 148
		if (block->lf_flags & F_POSIX)
			fl->l_pid = ((struct proc *)(block->lf_id))->p_pid;
		else
			fl->l_pid = -1;
	}
	FREE(lock, M_LOCKF);
	return (0);
E 150
E 145
E 131
E 102
E 63
E 37
E 36
E 21
D 17
	for(mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
		if(mp->m_bufp != NULL && dev == mp->m_dev)
E 17
I 17
D 26
	for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
		if (mp->m_bufp != NULL && dev == mp->m_dev)
E 17
			goto found;
	u.u_error = EINVAL;
	return;

found:
I 10
	stillopen = 0;
E 10
D 12
	for(ip = &inode[0]; ip < &inode[NINODE]; ip++)
E 12
I 12
D 17
	for(ip = inode; ip < inodeNINODE; ip++)
E 17
I 17
	for (ip = inode; ip < inodeNINODE; ip++)
E 17
E 12
D 9
		if(ip->i_number != 0 && dev == ip->i_dev) {
E 9
I 9
		if (ip->i_number != 0 && dev == ip->i_dev) {
E 9
			u.u_error = EBUSY;
			return;
D 8
		}
I 4
	mpurge(mp - &mount[0]);
E 4
	(*bdevsw[major(dev)].d_close)(dev, 0);
E 8
I 8
D 9
		} else if (ip->i_number != 0 && (ip->i_mode&IFMT) == IFBLK
			&& ip->i_un.i_rdev == dev)
				stillopen++;
E 9
I 9
		} else if (ip->i_number != 0 && (ip->i_mode&IFMT) == IFBLK &&
		    ip->i_un.i_rdev == dev)
			stillopen++;
E 9
E 8
	ip = mp->m_inodp;
	ip->i_flag &= ~IMOUNT;
D 17
	plock(ip);
E 17
I 17
	ilock(ip);
E 17
	iput(ip);
D 9
	bp = mp->m_bufp;
E 9
I 9
	if ((bp = getblk(dev, SUPERB)) != mp->m_bufp)
		panic("umount");
	bp->b_flags &= ~B_LOCKED;
E 9
I 8
	flag = !bp->b_un.b_filsys->s_ronly;
E 8
	mp->m_bufp = NULL;
	brelse(bp);
I 11
	mpurge(mp - &mount[0]);
E 11
I 8
	if (!stillopen) {
D 11
		mpurge(mp - &mount[0]);
E 11
		(*bdevsw[major(dev)].d_close)(dev, flag);
		binval(dev);
	}
E 8
}

/*
 * Common code for mount and umount.
 * Check that the user's argument is a reasonable
 * thing on which to mount, and return the device number if so.
 */
dev_t
getmdev()
{
	dev_t dev;
	register struct inode *ip;

D 7
#ifdef UCB
E 7
	if (!suser())
		return(NODEV);
D 7
#endif
E 7
D 23
	ip = namei(uchar, 0);
E 23
I 23
	ip = namei(uchar, 0, 1);
E 23
D 17
	if(ip == NULL)
E 17
I 17
	if (ip == NULL)
E 17
		return(NODEV);
D 17
	if((ip->i_mode&IFMT) != IFBLK)
E 17
I 17
	if ((ip->i_mode&IFMT) != IFBLK)
E 17
		u.u_error = ENOTBLK;
	dev = (dev_t)ip->i_un.i_rdev;
D 17
	if(major(dev) >= nblkdev)
E 17
I 17
	if (major(dev) >= nblkdev)
E 17
		u.u_error = ENXIO;
	iput(ip);
	return(dev);
E 26
}
I 155

/*
 * Global vfs data structures for ufs
 */
struct vnodeops ufs_vnodeops = {
	ufs_lookup,		/* lookup */
	ufs_create,		/* create */
	ufs_mknod,		/* mknod */
	ufs_open,		/* open */
	ufs_close,		/* close */
	ufs_access,		/* access */
	ufs_getattr,		/* getattr */
	ufs_setattr,		/* setattr */
	ufs_read,		/* read */
	ufs_write,		/* write */
	ufs_ioctl,		/* ioctl */
	ufs_select,		/* select */
	ufs_mmap,		/* mmap */
	ufs_fsync,		/* fsync */
	ufs_seek,		/* seek */
	ufs_remove,		/* remove */
	ufs_link,		/* link */
	ufs_rename,		/* rename */
	ufs_mkdir,		/* mkdir */
	ufs_rmdir,		/* rmdir */
	ufs_symlink,		/* symlink */
	ufs_readdir,		/* readdir */
	ufs_readlink,		/* readlink */
	ufs_abortop,		/* abortop */
	ufs_inactive,		/* inactive */
	ufs_reclaim,		/* reclaim */
	ufs_lock,		/* lock */
	ufs_unlock,		/* unlock */
	ufs_bmap,		/* bmap */
	ufs_strategy,		/* strategy */
	ufs_print,		/* print */
	ufs_islocked,		/* islocked */
	ufs_advlock,		/* advlock */
};

struct vnodeops spec_inodeops = {
	spec_lookup,		/* lookup */
	spec_create,		/* create */
	spec_mknod,		/* mknod */
	spec_open,		/* open */
	ufsspec_close,		/* close */
	ufs_access,		/* access */
	ufs_getattr,		/* getattr */
	ufs_setattr,		/* setattr */
	ufsspec_read,		/* read */
	ufsspec_write,		/* write */
	spec_ioctl,		/* ioctl */
	spec_select,		/* select */
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
	ufs_inactive,		/* inactive */
	ufs_reclaim,		/* reclaim */
	ufs_lock,		/* lock */
	ufs_unlock,		/* unlock */
	spec_bmap,		/* bmap */
	spec_strategy,		/* strategy */
	ufs_print,		/* print */
	ufs_islocked,		/* islocked */
	spec_advlock,		/* advlock */
};

#ifdef FIFO
struct vnodeops fifo_inodeops = {
	fifo_lookup,		/* lookup */
	fifo_create,		/* create */
	fifo_mknod,		/* mknod */
	fifo_open,		/* open */
	ufsfifo_close,		/* close */
	ufs_access,		/* access */
	ufs_getattr,		/* getattr */
	ufs_setattr,		/* setattr */
	ufsfifo_read,		/* read */
	ufsfifo_write,		/* write */
	fifo_ioctl,		/* ioctl */
	fifo_select,		/* select */
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
	ufs_inactive,		/* inactive */
	ufs_reclaim,		/* reclaim */
	ufs_lock,		/* lock */
	ufs_unlock,		/* unlock */
	fifo_bmap,		/* bmap */
	fifo_strategy,		/* strategy */
	ufs_print,		/* print */
	ufs_islocked,		/* islocked */
	fifo_advlock,		/* advlock */
};
#endif /* FIFO */

enum vtype iftovt_tab[16] = {
	VNON, VFIFO, VCHR, VNON, VDIR, VNON, VBLK, VNON,
	VREG, VNON, VLNK, VNON, VSOCK, VNON, VNON, VBAD,
};
int	vttoif_tab[9] = {
	0, IFREG, IFDIR, IFBLK, IFCHR, IFLNK, IFSOCK, IFIFO, IFMT,
};
E 161
E 155
E 1
