h46355
s 00005/00001/02386
d D 8.41 95/06/15 16:16:30 mckusick 263 262
c have to reacquire lock before continuing
e
s 00025/00053/02362
d D 8.40 95/05/27 22:17:56 mckusick 262 261
c delete read-only checking; it must be done by the filesystem layers
e
s 00057/00054/02358
d D 8.39 95/05/20 01:21:18 mckusick 261 260
c merge vfs_lock and vfs_busy; interlock mount points properly
e
s 00014/00015/02398
d D 8.38 95/05/18 17:16:14 pendry 260 259
c convert VOP_UNLOCK and vrele into vput's; add proc parameter to union_dircache
e
s 00030/00030/02383
d D 8.37 95/05/14 00:18:08 mckusick 259 258
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK
e
s 00002/00001/02411
d D 8.36 95/05/10 11:19:42 pendry 258 257
c don't call VFS_SYNC for read-only filesystems
e
s 00008/00000/02404
d D 8.35 95/05/10 06:36:36 mckusick 257 256
c disallow unmount of root fs
e
s 00012/00009/02392
d D 8.34 95/05/09 16:59:21 mckusick 256 255
c change mountlist to CIRCLEQ so we can do unmountall (from mycroft)
e
s 00045/00010/02356
d D 8.33 95/03/30 14:13:27 mckusick 255 254
c mount now takes a name rather than a number, vfssw => vfsconf
e
s 00003/00002/02363
d D 8.32 95/03/22 15:13:11 mckusick 254 253
c lstat returns inode number of symbolic link to match directory entry
e
s 00001/00001/02364
d D 8.31 95/03/19 00:02:54 mckusick 253 252
c reverse arguments to VOP_LINK (to get them right)
e
s 00001/00005/02364
d D 8.30 95/02/23 12:09:08 mckusick 252 250
c allow revoke on any file; vgoneall => VOP_REVOKE
e
s 00001/00005/02364
d R 8.30 95/02/22 21:14:04 mckusick 251 250
c allow revoke on any file; vgoneall => VOP_REVOKE
e
s 00467/00430/01902
d D 8.29 95/02/14 10:42:08 cgd 250 249
c new argument passing conventions.  minor type size cleanup.
e
s 00006/00009/02326
d D 8.28 94/12/10 13:04:32 pendry 249 248
c fix readdir for non-linear union stacks
e
s 00056/00003/02279
d D 8.27 94/11/22 14:08:15 mckusick 248 247
c check (and fix) mounted-on current directories
e
s 00001/00001/02281
d D 8.26 94/11/22 11:47:37 pendry 247 246
c get rid of usecount mount restriction (needed for union mounts)
e
s 00004/00006/02278
d D 8.25 94/11/21 17:42:10 mckusick 246 245
c return EBUSY if reference count on mount point is greater than 1 to
c avoid problems in lookup from programs referencing the hidden vnode
e
s 00003/00003/02281
d D 8.24 94/10/24 10:08:08 mckusick 245 244
c unwhiteout => undelete to be more general
e
s 00036/00006/02248
d D 8.23 94/08/30 12:25:49 mckusick 244 243
c fix olstat to give the correct symlink info
e
s 00011/00007/02243
d D 8.22 94/08/30 12:18:28 pendry 243 242
c clean up error case
e
s 00009/00000/02241
d D 8.21 94/08/14 21:54:41 mckusick 242 241
c have to recompute the next pointer after possibly sleeping in sync 
c (from mycroft)
e
s 00024/00025/02217
d D 8.20 94/08/11 00:24:22 mckusick 241 240
c LEASE_CHECK => VOP_LEASE
e
s 00047/00005/02195
d D 8.19 94/07/28 03:39:13 pendry 240 239
c changes for whiteouts and union filesystem
e
s 00047/00009/02153
d D 8.18 94/07/14 13:30:56 mckusick 239 238
c first pass at allowing user mounts/unmounts
e
s 00034/00000/02128
d D 8.17 94/07/12 23:36:06 pendry 238 237
c add unwhiteout system call to delete a whiteout entry
e
s 00001/00001/02127
d D 8.16 94/06/16 11:06:27 mckusick 237 236
c ifdef DIAGNOSTIC should be ifdef DEBUG (from mycroft)
e
s 00053/00007/02075
d D 8.15 94/06/04 17:23:02 mckusick 236 235
c add UNION support to ogetdirentries; add cookies and eofflag to VOP_READDIR
e
s 00010/00009/02072
d D 8.14 94/05/11 00:30:29 pendry 235 234
c don't panic getdirentries when a union stack has no lower layer
e
s 00002/00001/02079
d D 8.13 94/04/15 17:30:14 mckusick 234 233
c paranoid check to avoid vrele(NULL) (from polk@bsdi.com)
e
s 00001/00001/02079
d D 8.12 94/03/28 13:21:19 bostic 233 232
c change chown(2) to follow symbolic links
e
s 00011/00006/02069
d D 8.11 94/02/20 16:57:53 pendry 232 231
c add support for user mounts (MNT_USER flag)
e
s 00031/00000/02044
d D 8.10 94/02/15 10:37:54 pendry 231 230
c add support for union stacks into getdirentries.
e
s 00000/00004/02044
d D 8.9 94/01/28 09:57:03 pendry 230 229
c removed usecount check in mount()
e
s 00006/00000/02042
d D 8.8 94/01/24 00:08:42 mckusick 229 227
c disable MNT_ASYNC when doing sync and unmount
e
s 00005/00000/02042
d R 8.8 94/01/24 00:05:59 mckusick 228 227
c disable MNT_ASYNC when doing sync
e
s 00005/00000/02037
d D 8.7 94/01/21 17:18:12 bostic 227 226
c add USL's copyright notice
e
s 00002/00001/02035
d D 8.6 94/01/20 16:50:01 mckusick 226 225
c not the right fix, but avoid the deadlock
e
s 00004/00004/02032
d D 8.5 94/01/11 23:27:57 mckusick 225 224
c add ability to run ffs totally asynchronously (dangerously)
e
s 00018/00026/02018
d D 8.4 93/12/30 16:23:08 mckusick 224 223
c new queue structure
e
s 00062/00059/01982
d D 8.3 93/09/23 15:36:15 bostic 223 222
c changes for 4.4BSD-Lite requested by USL
e
s 00244/00279/01797
d D 8.2 93/09/05 09:36:41 bostic 222 221
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/02074
d D 8.1 93/06/14 15:20:43 bostic 221 220
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00004/02073
d D 7.113 93/06/14 15:20:35 bostic 220 218
c make function names match system call names
e
s 00002/00002/02075
d R 8.1 93/06/10 22:00:56 bostic 219 218
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00018/02059
d D 7.112 93/05/26 00:19:49 mckusick 218 217
c get rid of last vestiges of __
e
s 00030/00006/02047
d D 7.111 93/05/25 17:16:55 mckusick 217 216
c add pathconf; __lseek => lseek; --[f]truncate => [f]truncate
e
s 00002/00002/02051
d D 7.110 93/05/17 14:07:26 mckusick 216 215
c truncate, ftruncate, getrlimit, setrlimit become COMPAT_43
e
s 00027/00027/02026
d D 7.109 93/05/16 11:19:36 mckusick 215 214
c lseek (long form) is used too much to make it COMPAT_43
e
s 00002/00000/02051
d D 7.108 93/05/10 16:02:13 mckusick 214 213
c add sysctl debugging flag to print out buffer stats
e
s 00022/00016/02029
d D 7.107 93/04/27 16:24:35 mckusick 213 212
c bug fixes for LEASES from Rick Macklem
e
s 00036/00006/02009
d D 7.106 93/04/27 16:03:18 mckusick 212 211
c lstat of symbolic link returns attributes of its containing directory
c except for st_size, st_blocks, st_nlink, and file type in st_mode
e
s 00001/00001/02014
d D 7.105 93/03/28 19:10:57 torek 211 210
c lint
e
s 00001/00001/02014
d D 7.104 93/03/08 10:28:08 bostic 210 209
c rename va_cflags -> va_vaflags
e
s 00008/00004/02007
d D 7.103 93/03/05 17:23:38 bostic 209 208
c make utime(NULL) work for POSIX 1003.1 compatibility
e
s 00001/00001/02010
d D 7.102 93/02/02 15:34:58 mckusick 208 207
c vinvalbuf takes two more parameters
e
s 00017/00029/01994
d D 7.101 92/12/09 19:18:59 mckusick 207 206
c changes for allowing downgrade from RW to RO; reload root after fsck
e
s 00014/00013/02009
d D 7.100 92/10/11 10:39:06 bostic 206 205
c make kernel includes standard
e
s 00001/00001/02021
d D 7.99 92/10/07 17:19:42 margo 205 204
c Pass flag argument to vinvalbuf.
e
s 00008/00000/02014
d D 7.98 92/09/29 17:12:45 mckusick 204 203
c ufs_bufstats becomes vfs_bufstats
e
s 00004/00003/02010
d D 7.97 92/09/24 11:22:09 mckusick 203 202
c fix for LITTLE_ENDIAN code
e
s 00017/00001/01996
d D 7.96 92/07/20 16:02:12 pendry 202 201
c added union mounts
e
s 00013/00009/01984
d D 7.95 92/07/12 13:36:47 mckusick 201 200
c one more try at getting ogetdirentries right for LITTLE_ENDIAN
e
s 00017/00010/01976
d D 7.94 92/07/11 19:02:41 mckusick 200 198
c fix LITTLE_ENDIAN code in ogetdirentries; 
c getdirentries returns a long offset, not quad offset
e
s 00013/00006/01980
d R 7.94 92/07/11 18:45:04 mckusick 199 198
c fixes to ogetdirentries
e
s 00226/00187/01760
d D 7.93 92/07/10 20:25:00 torek 198 197
c ANSIfy syscall args
e
s 00063/00064/01884
d D 7.92 92/07/09 16:58:16 torek 197 196
c cleanup declaration of parameters; note required padding to align
c quad arguments to __lseek, __truncate, and __ftruncate
e
s 00002/00004/01946
d D 7.91 92/07/06 17:06:57 mckusick 196 195
c fix bug in dupfdopen call to pass correct descriptor
e
s 00000/00055/01950
d D 7.90 92/07/03 01:39:56 mckusick 195 194
c delete USES
e
s 00091/00001/01914
d D 7.89 92/07/02 21:50:14 mckusick 194 193
c add ogetdirentries
e
s 00008/00006/01907
d D 7.88 92/06/25 13:04:32 mckusick 193 192
c new parameters to vinvalbuf, VFS_SYNC, VOP_FSYNC, and VOP_READDIR
e
s 00009/00009/01904
d D 7.87 92/06/23 20:32:56 mckusick 192 191
c merge in changes for Sparc
e
s 00001/00002/01912
d D 7.86 92/06/20 16:34:50 mckusick 191 190
c zero out mount structure after allocation
e
s 00004/00002/01910
d D 7.85 92/06/19 19:20:26 mckusick 190 189
c timeval => timespec in vattr and dinode
e
s 00007/00013/01905
d D 7.84 92/06/03 00:10:54 pendry 189 188
c open now handles ENXIO in the same way as ENODEV.
c open ensures that dupfd is only negative during the call to vn_open.
c cross-device link and rename checks are now done in the vfs layer.
e
s 00010/00010/01908
d D 7.83 92/05/31 21:32:32 mckusick 188 187
c qseek => __lseek; stat => ostat; qstat => stat; lstat => olstat;
c lqstat => lstat; qtruncate => __truncate; fqtruncate => __ftruncate
e
s 00052/00000/01866
d D 7.82 92/05/14 17:36:40 heideman 187 178
c vnode interface conversion
e
s 00052/00000/01866
d R 7.82 92/05/14 15:53:33 heideman 186 178
c vnode interface conversion
e
s 00052/00000/01866
d R 7.82 92/05/14 14:55:25 heideman 185 178
c vnode interface conversion
e
s 00052/00000/01866
d R 7.82 92/05/14 13:00:28 heideman 184 178
c vnode interface conversion
e
s 00052/00000/01866
d R 7.82 92/05/14 11:58:14 heideman 183 178
c vnode interface conversion
e
s 00052/00000/01866
d R 7.82 92/05/14 10:38:12 heideman 182 178
c vnode interface conversion
e
s 00052/00000/01866
d R 7.82 92/05/13 23:17:23 heideman 181 178
c vnode interface conversion
e
s 00052/00000/01866
d R 7.82 92/05/13 19:01:57 heideman 180 178
c vnode interface conversion
e
s 00052/00000/01866
d R 7.82 92/05/13 18:34:05 heideman 179 178
c vnode interface conversion
e
s 00171/00004/01695
d D 7.81 92/05/13 14:49:54 mckusick 178 177
c add qseek, qstat, qlstat, qtruncate for
c 64-bit file sizes, 32-bit uid, gid, and dev's
e
s 00001/00001/01698
d D 7.80 92/03/03 13:17:28 mckusick 177 176
c must have directory vnode as first op
e
s 00002/00002/01697
d D 7.79 92/03/01 20:47:18 ralph 176 174
c calls to chdirec didn't pass 'p'.
e
s 00027/00000/01699
d D 7.78.1.1 92/02/04 00:34:47 mckusick 175 174
c together with vfs_subr.c (7.67.1.1) add reference checking
e
s 00144/00267/01555
d D 7.78 92/02/04 00:33:00 mckusick 174 173
c new calling convention for namei
e
s 00002/00000/01820
d D 7.77 92/02/03 16:17:51 mckusick 173 172
c check that mount structures are empty before deleteing them
e
s 00047/00018/01773
d D 7.76 92/01/22 09:37:26 heideman 172 171
c lookup converted to new form
e
s 00024/00001/01767
d D 7.75 92/01/14 12:23:22 mckusick 171 170
c lease checks on various operations
e
s 00007/00005/01761
d D 7.74 91/06/21 10:49:25 mckusick 170 169
c use vn_close rather than vrele after vn_open
e
s 00002/00004/01764
d D 7.73 91/06/03 20:29:06 mckusick 169 168
c call ffree to free file structures
e
s 00002/00001/01766
d D 7.72 91/05/30 15:32:12 mckusick 168 167
c use FHASLOCK and SADVLCK to track processes using locks to save work in close
e
s 00023/00001/01744
d D 7.71 91/05/30 14:58:55 mckusick 167 165
c add support for opening files with advisory locks
e
s 00002/00000/01745
d D 7.70.1.1 91/05/19 14:38:23 mckusick 166 165
c name resolution checking (need kern/kern_malloc.c 7.25.1.1,
c kern/vfs_lookup.c 7.31.1.1, kern/vfs_syscalls.c 7.70.1.1,
c nfs/nfs_serv.c 7.40.1.1, nfs/nfs_syscalls.c 7.26.1.1,
c ufs/ufs_vnops.c 7.64.1.1, and hp300/hp300/trap.c 7.14.1.1)
e
s 00021/00018/01724
d D 7.70 91/05/15 19:37:27 mckusick 165 164
c rewrite rename to use new SAVESTART flag
e
s 00000/00009/01742
d D 7.69 91/05/08 13:39:18 karels 164 163
c unifdef NVM
e
s 00025/00022/01726
d D 7.68 91/05/07 15:14:38 mckusick 163 162
c Regularize comments
e
s 00038/00035/01710
d D 7.67 91/04/15 23:58:45 mckusick 162 161
c add proc pointers to appropriate VOP, vnode, and uio setup operations
e
s 00004/00003/01741
d D 7.66 91/03/31 15:03:33 karels 161 160
c give sync a return value; rm OFILE
e
s 00239/00192/01505
d D 7.65 91/03/17 15:41:39 karels 160 159
c more-or-less working with new proc & user structs
e
s 00001/00001/01696
d D 7.64 91/02/22 14:13:01 karels 159 158
c oflags-FOPEN => FFLAGS(oflags)
e
s 00009/00000/01688
d D 7.63 91/01/10 23:59:49 mckusick 158 157
c add conditional code for new VM so can share with old VM tree
e
s 00084/00067/01613
d D 7.62 91/01/10 23:44:12 mckusick 157 156
c add dynamically allocated file descriptors
e
s 00024/00025/01656
d D 7.61 90/12/14 15:25:46 bostic 156 155
c lazy VATTR_NULL evaluation
e
s 00002/00003/01679
d D 7.60 90/12/05 17:16:46 mckusick 155 154
c update for new VM
e
s 00004/00000/01678
d D 7.59 90/09/18 22:20:57 mckusick 154 153
c have to check that renamed directory is not mounted on (from gmf@osf.org)
e
s 00002/00002/01676
d D 7.58 90/09/05 10:26:58 mckusick 153 152
c pass down index of opened file for datakit (gag)
e
s 00002/00002/01676
d D 7.57 90/07/28 09:11:18 mckusick 152 151
c handle p_dupfd as unsigned char
e
s 00001/00011/01677
d D 7.56 90/06/28 21:26:53 bostic 151 150
c new copyright notice
e
s 00001/00002/01687
d D 7.55 90/06/28 17:11:52 karels 150 149
c RETURN => return, remove syscontext.h
e
s 00004/00006/01685
d D 7.54 90/06/22 17:20:54 mckusick 149 148
c p_devtmp => p_dupfd; eliminate u.u_error from RETURN macro
e
s 00006/00002/01685
d D 7.53 90/06/21 23:49:16 mckusick 148 147
c use p_devtmp instead of r_val1 for fdopen
e
s 00000/00001/01687
d D 7.52 90/06/21 16:14:19 marc 147 146
c revoke has but one argument
e
s 00032/00008/01656
d D 7.51 90/06/21 11:10:58 mckusick 146 145
c have to check whether parent directory is "." when releasing
e
s 00004/00002/01660
d D 7.50 90/06/06 21:51:06 mckusick 145 144
c creat becomes ocreat and ifdef COMPAT_43; bug fix in revoke
e
s 00051/00031/01611
d D 7.49 90/05/30 11:38:42 mckusick 144 143
c VOP_ABORTOP is no longer responsible for unlocking and vreleing vnodes
e
s 00387/00304/01255
d D 7.48 90/05/29 18:33:53 mckusick 143 142
c new calling convension for system calls
e
s 00003/00003/01556
d D 7.47 90/05/11 15:07:35 mckusick 142 141
c check error return from sync'ing on unmount; add flags arg to revoke
e
s 00055/00054/01504
d D 7.46 90/05/04 20:55:44 mckusick 141 140
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00013/00013/01545
d D 7.45 90/05/03 18:44:43 mckusick 140 139
c vattr_null => VATTR_NULL
e
s 00039/00002/01519
d D 7.44 90/05/02 19:09:32 mckusick 139 138
c add quotactl system call; 
c use vfs_busy to single thread sync and avoid races with unmount
e
s 00004/00002/01517
d D 7.43 90/04/10 20:36:33 mckusick 138 137
c eliminate longjmp from the kernel (for karels)
e
s 00005/00006/01514
d D 7.42 90/03/26 18:58:46 mckusick 137 136
c get rid of unneeded header files
e
s 00028/00019/01492
d D 7.41 90/03/06 23:27:03 mckusick 136 135
c statfs structure is now cached in the mount table entry
e
s 00002/00002/01509
d D 7.40 90/03/06 16:30:28 mckusick 135 134
c readdir takes a new flag to indicate end-of-file
e
s 00034/00000/01477
d D 7.39 90/03/05 18:08:02 mckusick 134 133
c add mkfifo system call
e
s 00004/00001/01473
d D 7.38 90/02/16 11:39:07 mckusick 133 132
c do not change mount flags if underlying filesystem returns error (from noemi)
e
s 00011/00009/01463
d D 7.37 90/02/16 11:35:38 mckusick 132 131
c do not link new mount points into mount list until the underlying
c filesystem has successfully mounted; skip locked mount points when syncing
e
s 00004/00001/01468
d D 7.36 90/01/03 20:45:14 mckusick 131 130
c fix reference bug in fchdir
e
s 00002/00002/01467
d D 7.35 89/12/30 22:21:59 mckusick 130 129
c v_count => v_usecount
e
s 00003/00000/01466
d D 7.34 89/12/29 10:19:19 mckusick 129 128
c debugging, check lock count on exit
e
s 00001/00001/01465
d D 7.33 89/12/19 21:07:53 mckusick 128 127
c more fully check the type field
e
s 00001/00000/01465
d D 7.32 89/11/30 22:37:14 mckusick 127 126
c have to invalidate any buffer references before checking for busy status
e
s 00002/00002/01463
d D 7.31 89/11/25 23:23:09 mckusick 126 125
c get rid of all users of a particular device
e
s 00004/00002/01461
d D 7.30 89/11/24 16:52:24 mckusick 125 124
c skip over dead file systems in getfsstat
e
s 00011/00009/01452
d D 7.29 89/11/24 16:22:00 mckusick 124 123
c protect thyself with copyout to userland
e
s 00016/00006/01445
d D 7.28 89/11/22 21:43:47 mckusick 123 122
c must lock around FSYNC and READDIR
e
s 00037/00000/01414
d D 7.27 89/11/20 18:23:11 marc 122 121
c add revoke
e
s 00005/00009/01409
d D 7.26 89/11/19 18:32:06 mckusick 121 120
c do not lock vnode while doing VFS_STATFS
e
s 00001/00001/01417
d D 7.25 89/11/19 18:26:28 mckusick 120 119
c only do write check if asking about writing
e
s 00002/00001/01416
d D 7.24 89/11/12 10:18:13 mckusick 119 118
c check for null rdir before vrele'ing it
e
s 00003/00001/01414
d D 7.23 89/11/09 19:39:28 mckusick 118 117
c fdopen returns a special error so that resources get cleaned up
e
s 00002/00001/01413
d D 7.22 89/11/03 15:05:48 mckusick 117 116
c lint
e
s 00012/00002/01402
d D 7.21 89/10/31 17:27:16 mckusick 116 115
c vnode layer fills in f_flags and f_fsid for statfs()
e
s 00001/00000/01403
d D 7.20 89/10/24 18:43:03 mckusick 115 114
c initialize list of vnodes associated with a new mount point
e
s 00017/00008/01386
d D 7.19 89/10/20 18:34:53 mckusick 114 113
c break out unmounting part so it can be used by mfs
e
s 00077/00008/01317
d D 7.18 89/10/19 00:09:10 mckusick 113 112
c expand vfs_add inline; allow update of mounted file systems
e
s 00009/00001/01316
d D 7.17 89/10/13 16:05:00 mckusick 112 111
c do not return error if source and destination of rename are the same
e
s 00002/00002/01315
d D 7.16 89/10/01 15:32:35 bostic 111 110
c reverse errors returned by rename(dir,file) and rename(file,dir)
e
s 00003/00001/01314
d D 7.15 89/09/05 23:11:52 mckusick 110 109
c add VFS_START call for memory filesystem; 
c have getfsstat skip over locked mount points
e
s 00180/00142/01135
d D 7.14 89/07/04 10:54:07 mckusick 109 108
c pass in system call context pointer instead of using u. area
e
s 00007/00005/01270
d D 7.13 89/07/03 22:08:07 mckusick 108 107
c break vn_access into its constituent parts vn_writechk and VOP_ACCESS
e
s 00033/00000/01242
d D 7.12 89/06/08 16:31:01 mckusick 107 106
c add getfsstat system call
e
s 00002/00012/01240
d D 7.11 89/06/08 13:43:10 mckusick 106 105
c gather nameidata duplication and freeing code into nddup and ndrele
e
s 00088/00000/01164
d D 7.10 89/06/07 16:58:06 mckusick 105 104
c add fchdir, chflags, and fchflags system calls
e
s 00002/00000/01162
d D 7.9 89/05/27 16:49:30 mckusick 104 103
c return directory locked after mkdir (for benefit of NFS)
e
s 00003/00001/01159
d D 7.8 89/05/25 16:51:28 mckusick 103 102
c bug fix to getdirentries from Rick Macklem
e
s 00712/00942/00448
d D 7.7 89/05/09 20:44:37 mckusick 102 101
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
D 221
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 221
I 221
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 227
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 227
E 221
E 102
 *
I 102
D 151
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
E 151
I 151
 * %sccs.include.redist.c%
E 151
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
D 206
#include "param.h"
#include "systm.h"
D 102
#include "dir.h"
#include "user.h"
E 102
I 102
D 150
#include "syscontext.h"
E 150
I 150
D 160
#include "user.h"
E 160
I 160
#include "namei.h"
E 160
I 157
#include "filedesc.h"
E 157
E 150
E 102
#include "kernel.h"
#include "file.h"
#include "stat.h"
D 102
#include "inode.h"
#include "fs.h"
#include "buf.h"
E 102
I 102
#include "vnode.h"
D 137
#include "../ufs/inode.h"
E 137
#include "mount.h"
E 102
#include "proc.h"
D 102
#include "quota.h"
E 102
#include "uio.h"
D 102
#include "socket.h"
#include "socketvar.h"
#include "mount.h"
E 102
I 102
#include "malloc.h"
I 194
#include "dirent.h"
E 206
I 206
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/filedesc.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/malloc.h>
#include <sys/dirent.h>

I 250
#include <sys/syscallargs.h>

E 250
E 206
E 194
I 178
#include <vm/vm.h>
I 214
#include <sys/sysctl.h>
E 214
E 178
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

I 222
static int change_dir __P((struct nameidata *ndp, struct proc *p));
I 250
static void checkdirs __P((struct vnode *olddp));
E 250

E 222
I 175
#ifdef REF_DIAGNOSTIC
#define CURCOUNT (curproc ? curproc->p_spare[0] : 0)
#define CHECKPOINTREF int oldrefcount = CURCOUNT;
#define CHECKREFS(F) if (oldrefcount != CURCOUNT) \
	printf("REFCOUNT: %s, old=%d, new=%d\n", (F), oldrefcount, CURCOUNT);
#else
#define CHECKPOINTREF
#define CHECKREFS(D)
#endif

E 175
I 172
D 174
/* NEEDSWORK: debugging */
#define CURCOUNT (curproc?curproc->p_spare[2]:0)
#define CHECKPOINT int oldrefcount=CURCOUNT;
#define CHECKCHECK(F) if (oldrefcount!=CURCOUNT) { printf("REFCOUNT: %s, old=%d, new=%d\n", (F), oldrefcount, CURCOUNT); }

E 174
E 172
I 148
D 149
#define	p_devtmp	p_logname[11]

E 149
E 148
I 129
D 150
#undef RETURN
E 150
D 143
#define RETURN(val)	{ scp->u_error = (val); if (scp->u_spare[0] != 0) panic("lock count"); return; }
E 143
I 143
D 149
#define RETURN(val)	{ u.u_error = (val); if (u.u_spare[0] != 0) panic("lock count"); return (u.u_error); }
E 149
I 149
D 160
#define RETURN(val) {if (u.u_spare[0] != 0) panic("lock count"); return (val);}
E 149
E 143

E 160
E 129
I 63
D 102
extern	struct fileops inodeops;
struct	file *getinode();
E 102
I 102
/*
 * Virtual File System System Calls
 */
E 102

E 63
I 47
/*
D 102
 * Change current working directory (``.'').
E 102
I 102
D 163
 * mount system call
E 163
I 163
D 222
 * Mount system call.
E 222
I 222
 * Mount a file system.
E 222
E 163
E 102
 */
I 198
D 250
struct mount_args {
	int	type;
D 222
	char	*dir;
E 222
I 222
	char	*path;
E 222
	int	flags;
	caddr_t	data;
};
E 250
E 198
E 47
I 26
D 102
chdir()
E 102
I 102
D 109
mount()
E 109
I 109
D 143
mount(scp)
	register struct syscontext *scp;
E 109
E 102
{
I 102
	register struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
mount(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		int	type;
		char	*dir;
		int	flags;
		caddr_t	data;
D 109
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct mount_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct mount_args /* {
D 255
		syscallarg(int) type;
E 255
I 255
		syscallarg(char *) type;
E 255
		syscallarg(char *) path;
		syscallarg(int) flags;
		syscallarg(caddr_t) data;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_UNLOCK;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
D 113
	struct vnode *vp;
	struct mount *mp;
E 113
I 113
D 255
	register struct vnode *vp;
	register struct mount *mp;
E 255
I 255
	struct vnode *vp;
	struct mount *mp;
	struct vfsconf *vfsp;
E 255
E 113
D 133
	int error;
E 133
I 133
	int error, flag;
I 239
	struct vattr va;
I 255
	u_long fstypenum;
E 255
E 239
I 160
	struct nameidata nd;
I 255
	char fstypename[MFSNAMELEN];
E 255
E 160
E 133
E 102

D 102
	chdirec(&u.u_cdir);
E 102
I 102
	/*
D 239
	 * Must be super user
	 */
D 109
	if (error = suser(u.u_cred, &u.u_acflag))
E 109
I 109
D 143
	if (error = suser(scp->sc_cred, &scp->sc_acflag))
E 143
I 143
D 160
	if (error = suser(ndp->ni_cred, &u.u_acflag))
E 143
E 109
		RETURN (error);
E 160
I 160
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
E 160
	/*
E 239
	 * Get vnode to be covered
	 */
I 160
D 174
	ndp = &nd;
E 160
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->dir;
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->dir, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
E 174
I 113
D 141
	if (uap->flags & M_UPDATE) {
E 141
I 141
D 250
	if (uap->flags & MNT_UPDATE) {
E 250
I 250
	if (SCARG(uap, flags) & MNT_UPDATE) {
E 250
E 141
		if ((vp->v_flag & VROOT) == 0) {
			vput(vp);
D 160
			RETURN (EINVAL);
E 160
I 160
			return (EINVAL);
E 160
		}
		mp = vp->v_mount;
I 207
		flag = mp->mnt_flag;
E 207
		/*
D 207
		 * We allow going from read-only to read-write,
		 * but not from read-write to read-only.
E 207
I 207
		 * We only allow the filesystem to be reloaded if it
		 * is currently mounted read-only.
E 207
		 */
D 141
		if ((mp->m_flag & M_RDONLY) == 0 &&
		    (uap->flags & M_RDONLY) != 0) {
E 141
I 141
D 207
		if ((mp->mnt_flag & MNT_RDONLY) == 0 &&
		    (uap->flags & MNT_RDONLY) != 0) {
E 207
I 207
D 250
		if ((uap->flags & MNT_RELOAD) &&
E 250
I 250
		if ((SCARG(uap, flags) & MNT_RELOAD) &&
E 250
		    ((mp->mnt_flag & MNT_RDONLY) == 0)) {
E 207
E 141
			vput(vp);
D 160
			RETURN (EOPNOTSUPP);	/* Needs translation */
E 160
I 160
			return (EOPNOTSUPP);	/* Needs translation */
E 160
		}
I 133
D 141
		flag = mp->m_flag;
E 133
		mp->m_flag |= M_UPDATE;
E 141
I 141
D 207
		flag = mp->mnt_flag;
		mp->mnt_flag |= MNT_UPDATE;
E 207
I 207
		mp->mnt_flag |=
D 250
		    uap->flags & (MNT_RELOAD | MNT_FORCE | MNT_UPDATE);
E 250
I 250
		    SCARG(uap, flags) & (MNT_RELOAD | MNT_FORCE | MNT_UPDATE);
E 250
I 239
		/*
		 * Only root, or the user that did the original mount is
		 * permitted to update it.
		 */
		if (mp->mnt_stat.f_owner != p->p_ucred->cr_uid &&
		    (error = suser(p->p_ucred, &p->p_acflag))) {
			vput(vp);
			return (error);
		}
		/*
		 * Do not allow NFS export by non-root users. Silently
		 * enforce MNT_NOSUID and MNT_NODEV for non-root users.
		 */
		if (p->p_ucred->cr_uid != 0) {
D 250
			if (uap->flags & MNT_EXPORTED) {
E 250
I 250
			if (SCARG(uap, flags) & MNT_EXPORTED) {
E 250
				vput(vp);
				return (EPERM);
			}
D 250
			uap->flags |= MNT_NOSUID | MNT_NODEV;
E 250
I 250
			SCARG(uap, flags) |= MNT_NOSUID | MNT_NODEV;
E 250
		}
I 261
		if (vfs_busy(mp, LK_NOWAIT, 0, p)) {
			vput(vp);
			return (EBUSY);
		}
E 261
E 239
E 207
E 141
D 259
		VOP_UNLOCK(vp);
E 259
I 259
		VOP_UNLOCK(vp, 0, p);
E 259
		goto update;
	}
I 239
	/*
	 * If the user is not root, ensure that they own the directory
	 * onto which we are attempting to mount.
	 */
	if ((error = VOP_GETATTR(vp, &va, p->p_ucred, p)) ||
	    (va.va_uid != p->p_ucred->cr_uid &&
	     (error = suser(p->p_ucred, &p->p_acflag)))) {
		vput(vp);
		return (error);
	}
	/*
	 * Do not allow NFS export by non-root users. Silently
	 * enforce MNT_NOSUID and MNT_NODEV for non-root users.
	 */
	if (p->p_ucred->cr_uid != 0) {
D 250
		if (uap->flags & MNT_EXPORTED) {
E 250
I 250
		if (SCARG(uap, flags) & MNT_EXPORTED) {
E 250
			vput(vp);
			return (EPERM);
		}
D 250
		uap->flags |= MNT_NOSUID | MNT_NODEV;
E 250
I 250
		SCARG(uap, flags) |= MNT_NOSUID | MNT_NODEV;
E 250
	}
E 239
I 127
D 193
	vinvalbuf(vp, 1);
E 193
E 127
E 113
D 130
	if (vp->v_count != 1) {
E 130
I 130
D 202
	if (vp->v_usecount != 1) {
E 202
I 202
D 230
	if (vp->v_usecount != 1 && (uap->flags & MNT_UNION) == 0) {
E 202
E 130
		vput(vp);
D 160
		RETURN (EBUSY);
E 160
I 160
		return (EBUSY);
E 160
	}
E 230
I 193
D 205
	if (error = vinvalbuf(vp, 1, p->p_ucred, p))
E 205
I 205
D 208
	if (error = vinvalbuf(vp, V_SAVE, p->p_ucred, p))
E 208
I 208
	if (error = vinvalbuf(vp, V_SAVE, p->p_ucred, p, 0, 0))
E 208
E 205
		return (error);
E 193
	if (vp->v_type != VDIR) {
		vput(vp);
D 160
		RETURN (ENOTDIR);
E 160
I 160
		return (ENOTDIR);
E 160
	}
D 128
	if (uap->type > MOUNT_MAXTYPE ||
E 128
I 128
D 222
	if ((unsigned long)uap->type > MOUNT_MAXTYPE ||
E 128
	    vfssw[uap->type] == (struct vfsops *)0) {
E 222
I 222
D 250
	if ((u_long)uap->type > MOUNT_MAXTYPE || vfssw[uap->type] == NULL) {
E 250
I 250
D 255
	if ((u_long)SCARG(uap, type) > MOUNT_MAXTYPE ||
	    vfssw[SCARG(uap, type)] == NULL) {
E 255
I 255
#ifdef COMPAT_43
	/*
	 * Historically filesystem types were identified by number. If we
	 * get an integer for the filesystem type instead of a string, we
	 * check to see if it matches one of the historic filesystem types.
	 */
	fstypenum = (u_long)SCARG(uap, type);
	if (fstypenum < maxvfsconf) {
		for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next)
			if (vfsp->vfc_typenum == fstypenum)
				break;
		if (vfsp == NULL) {
			vput(vp);
			return (ENODEV);
		}
		strncpy(fstypename, vfsp->vfc_name, MFSNAMELEN);
	} else
#endif /* COMPAT_43 */
	if (error = copyinstr(SCARG(uap, type), fstypename, MFSNAMELEN, NULL)) {
E 255
E 250
E 222
		vput(vp);
I 255
		return (error);
	}
	for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next)
		if (!strcmp(vfsp->vfc_name, fstypename))
			break;
	if (vfsp == NULL) {
		vput(vp);
E 255
D 160
		RETURN (ENODEV);
E 160
I 160
		return (ENODEV);
E 160
	}
I 246
D 247
	if (vp->v_usecount > 1 || vp->v_mountedhere != NULL) {
E 247
I 247
	if (vp->v_mountedhere != NULL) {
E 247
		vput(vp);
		return (EBUSY);
	}
E 246

	/*
D 113
	 * Mount the filesystem.
E 113
I 113
D 255
	 * Allocate and initialize the file system.
E 255
I 255
	 * Allocate and initialize the filesystem.
E 255
E 113
	 */
	mp = (struct mount *)malloc((u_long)sizeof(struct mount),
		M_MOUNT, M_WAITOK);
I 191
	bzero((char *)mp, (u_long)sizeof(struct mount));
I 261
	lockinit(&mp->mnt_lock, PVFS, "vfslock", 0, 0);
	(void)vfs_busy(mp, LK_NOWAIT, 0, p);
E 261
E 191
D 141
	mp->m_op = vfssw[uap->type];
	mp->m_flag = 0;
	mp->m_exroot = 0;
I 115
	mp->m_mounth = (struct vnode *)0;
E 141
I 141
D 250
	mp->mnt_op = vfssw[uap->type];
E 250
I 250
D 255
	mp->mnt_op = vfssw[SCARG(uap, type)];
E 255
I 255
	mp->mnt_op = vfsp->vfc_vfsops;
E 255
E 250
D 191
	mp->mnt_flag = 0;
D 171
	mp->mnt_exroot = 0;
E 171
	mp->mnt_mounth = NULLVP;
E 191
E 141
E 115
D 113
	error = vfs_add(vp, mp, uap->flags);
	if (!error)
		error = VFS_MOUNT(mp, uap->dir, uap->data, ndp);
E 113
I 113
D 261
	if (error = vfs_lock(mp)) {
		free((caddr_t)mp, M_MOUNT);
		vput(vp);
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
D 246
	}
D 222
	if (vp->v_mountedhere != (struct mount *)0) {
E 222
I 222
	if (vp->v_mountedhere != NULL) {
E 222
		vfs_unlock(mp);
		free((caddr_t)mp, M_MOUNT);
		vput(vp);
D 160
		RETURN (EBUSY);
E 160
I 160
		return (EBUSY);
E 246
E 160
	}
E 261
I 255
	mp->mnt_vfc = vfsp;
	vfsp->vfc_refcount++;
	mp->mnt_stat.f_type = vfsp->vfc_typenum;
	mp->mnt_flag |= vfsp->vfc_flags & MNT_VISFLAGMASK;
	strncpy(mp->mnt_stat.f_fstypename, vfsp->vfc_name, MFSNAMELEN);
E 255
D 132
	/*
	 * Put the new filesystem on the mount list after root.
	 */
	mp->m_next = rootfs->m_next;
	mp->m_prev = rootfs;
	rootfs->m_next = mp;
	mp->m_next->m_prev = mp;
E 132
	vp->v_mountedhere = mp;
D 141
	mp->m_vnodecovered = vp;
E 141
I 141
	mp->mnt_vnodecovered = vp;
I 239
	mp->mnt_stat.f_owner = p->p_ucred->cr_uid;
E 239
E 141
update:
	/*
	 * Set the mount level flags.
	 */
D 141
	if (uap->flags & M_RDONLY)
		mp->m_flag |= M_RDONLY;
E 141
I 141
D 250
	if (uap->flags & MNT_RDONLY)
E 250
I 250
	if (SCARG(uap, flags) & MNT_RDONLY)
E 250
		mp->mnt_flag |= MNT_RDONLY;
E 141
D 207
	else
D 141
		mp->m_flag &= ~M_RDONLY;
	if (uap->flags & M_NOSUID)
		mp->m_flag |= M_NOSUID;
E 141
I 141
		mp->mnt_flag &= ~MNT_RDONLY;
	if (uap->flags & MNT_NOSUID)
		mp->mnt_flag |= MNT_NOSUID;
E 141
	else
D 141
		mp->m_flag &= ~M_NOSUID;
	if (uap->flags & M_NOEXEC)
		mp->m_flag |= M_NOEXEC;
E 141
I 141
		mp->mnt_flag &= ~MNT_NOSUID;
	if (uap->flags & MNT_NOEXEC)
		mp->mnt_flag |= MNT_NOEXEC;
E 141
	else
D 141
		mp->m_flag &= ~M_NOEXEC;
	if (uap->flags & M_NODEV)
		mp->m_flag |= M_NODEV;
E 141
I 141
		mp->mnt_flag &= ~MNT_NOEXEC;
	if (uap->flags & MNT_NODEV)
		mp->mnt_flag |= MNT_NODEV;
E 141
	else
D 141
		mp->m_flag &= ~M_NODEV;
	if (uap->flags & M_SYNCHRONOUS)
		mp->m_flag |= M_SYNCHRONOUS;
E 141
I 141
		mp->mnt_flag &= ~MNT_NODEV;
	if (uap->flags & MNT_SYNCHRONOUS)
		mp->mnt_flag |= MNT_SYNCHRONOUS;
E 141
	else
D 141
		mp->m_flag &= ~M_SYNCHRONOUS;
E 141
I 141
		mp->mnt_flag &= ~MNT_SYNCHRONOUS;
I 202
	if (uap->flags & MNT_UNION)
		mp->mnt_flag |= MNT_UNION;
	else
		mp->mnt_flag &= ~MNT_UNION;
E 207
I 207
	else if (mp->mnt_flag & MNT_RDONLY)
		mp->mnt_flag |= MNT_WANTRDWR;
D 225
	mp->mnt_flag &=~
	    (MNT_NOSUID | MNT_NOEXEC | MNT_NODEV | MNT_SYNCHRONOUS | MNT_UNION);
	mp->mnt_flag |= uap->flags &
	    (MNT_NOSUID | MNT_NOEXEC | MNT_NODEV | MNT_SYNCHRONOUS | MNT_UNION);
E 225
I 225
	mp->mnt_flag &=~ (MNT_NOSUID | MNT_NOEXEC | MNT_NODEV |
	    MNT_SYNCHRONOUS | MNT_UNION | MNT_ASYNC);
D 250
	mp->mnt_flag |= uap->flags & (MNT_NOSUID | MNT_NOEXEC | MNT_NODEV |
	    MNT_SYNCHRONOUS | MNT_UNION | MNT_ASYNC);
E 250
I 250
	mp->mnt_flag |= SCARG(uap, flags) & (MNT_NOSUID | MNT_NOEXEC |
	    MNT_NODEV | MNT_SYNCHRONOUS | MNT_UNION | MNT_ASYNC);
E 250
E 225
E 207
E 202
E 141
	/*
	 * Mount the filesystem.
	 */
D 162
	error = VFS_MOUNT(mp, uap->dir, uap->data, ndp);
E 162
I 162
D 174
	error = VFS_MOUNT(mp, uap->dir, uap->data, ndp, p);
E 174
I 174
D 222
	error = VFS_MOUNT(mp, uap->dir, uap->data, &nd, p);
E 222
I 222
D 250
	error = VFS_MOUNT(mp, uap->path, uap->data, &nd, p);
E 250
I 250
	error = VFS_MOUNT(mp, SCARG(uap, path), SCARG(uap, data), &nd, p);
E 250
E 222
E 174
E 162
D 141
	if (mp->m_flag & M_UPDATE) {
		mp->m_flag &= ~M_UPDATE;
E 141
I 141
	if (mp->mnt_flag & MNT_UPDATE) {
D 207
		mp->mnt_flag &= ~MNT_UPDATE;
E 207
E 141
		vrele(vp);
I 207
		if (mp->mnt_flag & MNT_WANTRDWR)
			mp->mnt_flag &= ~MNT_RDONLY;
		mp->mnt_flag &=~
		    (MNT_UPDATE | MNT_RELOAD | MNT_FORCE | MNT_WANTRDWR);
E 207
I 133
		if (error)
D 141
			mp->m_flag = flag;
E 141
I 141
			mp->mnt_flag = flag;
I 261
		vfs_unbusy(mp, p);
E 261
E 141
E 133
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
	}
I 132
	/*
	 * Put the new filesystem on the mount list after root.
	 */
D 141
	mp->m_next = rootfs->m_next;
	mp->m_prev = rootfs;
	rootfs->m_next = mp;
	mp->m_next->m_prev = mp;
E 141
I 141
D 224
	mp->mnt_next = rootfs->mnt_next;
	mp->mnt_prev = rootfs;
	rootfs->mnt_next = mp;
	mp->mnt_next->mnt_prev = mp;
E 224
E 141
E 132
E 113
	cache_purge(vp);
D 113
	VOP_UNLOCK(vp);
E 113
	if (!error) {
I 261
		simple_lock(&mountlist_slock);
E 261
I 224
D 256
		TAILQ_INSERT_TAIL(&mountlist, mp, mnt_list);
E 256
I 256
		CIRCLEQ_INSERT_TAIL(&mountlist, mp, mnt_list);
I 261
		simple_unlock(&mountlist_slock);
E 261
E 256
I 248
		checkdirs(vp);
E 248
E 224
I 113
D 259
		VOP_UNLOCK(vp);
E 259
I 259
		VOP_UNLOCK(vp, 0, p);
E 259
E 113
D 261
		vfs_unlock(mp);
I 110
D 162
		error = VFS_START(mp, 0);
E 162
I 162
		error = VFS_START(mp, 0, p);
E 261
I 261
		vfs_unbusy(mp, p);
		if (error = VFS_START(mp, 0, p))
			vrele(vp);
E 261
E 162
E 110
	} else {
D 224
		vfs_remove(mp);
E 224
I 224
		mp->mnt_vnodecovered->v_mountedhere = (struct mount *)0;
I 255
		mp->mnt_vfc->vfc_refcount--;
E 255
D 261
		vfs_unlock(mp);
E 261
I 261
		vfs_unbusy(mp, p);
E 261
E 224
		free((caddr_t)mp, M_MOUNT);
D 113
		vrele(vp);
E 113
I 113
		vput(vp);
E 113
	}
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
}

I 47
/*
I 248
 * Scan all active processes to see if any of them have a current
 * or root directory onto which the new filesystem has just been
 * mounted. If so, replace them with the new mount point.
 */
I 250
static void
E 250
checkdirs(olddp)
	struct vnode *olddp;
{
	struct filedesc *fdp;
	struct vnode *newdp;
	struct proc *p;

	if (olddp->v_usecount == 1)
		return;
	if (VFS_ROOT(olddp->v_mountedhere, &newdp))
		panic("mount: lost mount");
	for (p = allproc.lh_first; p != 0; p = p->p_list.le_next) {
		fdp = p->p_fd;
		if (fdp->fd_cdir == olddp) {
			vrele(fdp->fd_cdir);
			VREF(newdp);
			fdp->fd_cdir = newdp;
D 249
			printf("patch cdir for proc %d\n", p->p_pid);
E 249
		}
		if (fdp->fd_rdir == olddp) {
			vrele(fdp->fd_rdir);
			VREF(newdp);
			fdp->fd_rdir = newdp;
		}
	}
	if (rootvnode == olddp) {
		vrele(rootvnode);
		VREF(newdp);
		rootvnode = newdp;
	}
	vput(newdp);
}

/*
E 248
D 102
 * Change notion of root (``/'') directory.
E 102
I 102
D 222
 * Unmount system call.
E 222
I 222
 * Unmount a file system.
E 222
 *
 * Note: unmount takes a path to the vnode mounted on as argument,
 * not special file (as before).
E 102
 */
I 198
D 250
struct unmount_args {
D 222
	char	*pathp;
E 222
I 222
	char	*path;
E 222
	int	flags;
};
E 250
E 198
E 47
D 102
chroot()
E 102
I 102
D 109
unmount()
E 109
I 109
D 143
unmount(scp)
	register struct syscontext *scp;
E 109
E 102
{
I 102
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
unmount(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		char	*pathp;
		int	flags;
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct unmount_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct unmount_args /* {
		syscallarg(char *) path;
		syscallarg(int) flags;
	} */ *uap;
	register_t *retval;
E 250
{
E 143
E 109
	register struct vnode *vp;
D 114
	register struct mount *mp;
E 114
D 109
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
D 114
	struct vnode *coveredvp;
E 114
I 114
	struct mount *mp;
E 114
	int error;
I 160
	struct nameidata nd;
E 160
E 102

D 101
	if (suser())
		chdirec(&u.u_rdir);
E 101
I 101
D 102
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
	chdirec(&u.u_rdir);
E 102
I 102
D 232
	/*
	 * Must be super user
	 */
D 109
	if (error = suser(u.u_cred, &u.u_acflag))
E 109
I 109
D 143
	if (error = suser(scp->sc_cred, &scp->sc_acflag))
E 143
I 143
D 160
	if (error = suser(ndp->ni_cred, &u.u_acflag))
E 143
E 109
		RETURN (error);
E 160
I 160
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
E 160

E 232
I 160
D 174
	ndp = &nd;
E 160
	ndp->ni_nameiop = LOOKUP | LOCKLEAF | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->pathp;
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->pathp, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
I 239
	mp = vp->v_mount;
E 239
I 232

	/*
D 239
	 * Unless this is a user mount, then must
	 * have suser privilege.
E 239
I 239
	 * Only root, or the user that did the original mount is
	 * permitted to unmount this filesystem.
E 239
	 */
D 239
	if (((vp->v_mount->mnt_flag & MNT_USER) == 0) &&
E 239
I 239
	if ((mp->mnt_stat.f_owner != p->p_ucred->cr_uid) &&
E 239
	    (error = suser(p->p_ucred, &p->p_acflag))) {
		vput(vp);
		return (error);
	}

E 232
E 174
	/*
I 257
	 * Don't allow unmounting the root file system.
	 */
	if (mp->mnt_flag & MNT_ROOTFS) {
		vput(vp);
		return (EINVAL);
	}

	/*
E 257
	 * Must be the root of the filesystem
	 */
	if ((vp->v_flag & VROOT) == 0) {
		vput(vp);
D 160
		RETURN (EINVAL);
E 160
I 160
		return (EINVAL);
E 160
	}
D 239
	mp = vp->v_mount;
E 239
	vput(vp);
D 114
	/*
	 * Do the unmount.
	 */
E 114
I 114
D 160
	RETURN (dounmount(mp, uap->flags));
E 160
I 160
D 162
	return (dounmount(mp, uap->flags));
E 162
I 162
D 250
	return (dounmount(mp, uap->flags, p));
E 250
I 250
	return (dounmount(mp, SCARG(uap, flags), p));
E 250
E 162
E 160
}

/*
D 222
 * Do an unmount.
E 222
I 222
 * Do the actual file system unmount.
E 222
 */
I 250
int
E 250
D 162
dounmount(mp, flags)
E 162
I 162
dounmount(mp, flags, p)
E 162
	register struct mount *mp;
	int flags;
I 162
	struct proc *p;
E 162
{
	struct vnode *coveredvp;
	int error;

E 114
D 141
	coveredvp = mp->m_vnodecovered;
E 141
I 141
D 261
	coveredvp = mp->mnt_vnodecovered;
E 141
I 139
	if (vfs_busy(mp))
		return (EBUSY);
E 261
I 261
	simple_lock(&mountlist_slock);
E 261
D 141
	mp->m_flag |= M_UNMOUNT;
E 141
I 141
	mp->mnt_flag |= MNT_UNMOUNT;
E 141
E 139
D 261
	if (error = vfs_lock(mp))
D 114
		RETURN (error);
E 114
I 114
		return (error);
E 114

E 261
I 261
	lockmgr(&mp->mnt_lock, LK_DRAIN | LK_INTERLOCK, &mountlist_slock, p);
E 261
I 229
	mp->mnt_flag &=~ MNT_ASYNC;
E 229
I 158
D 164
#ifdef NVM
E 164
E 158
D 155
	xumount(mp);		/* remove unused sticky files from text table */
E 155
I 155
	vnode_pager_umount(mp);	/* release cached vnodes */
I 158
D 164
#else
	xumount(mp);		/* remove unused sticky files from text table */
#endif
E 164
E 158
E 155
	cache_purgevfs(mp);	/* remove cache entries for this file sys */
D 142
	VFS_SYNC(mp, MNT_WAIT);

D 114
	error = VFS_UNMOUNT(mp, uap->flags);
E 114
I 114
	error = VFS_UNMOUNT(mp, flags);
E 142
I 142
D 193
	if ((error = VFS_SYNC(mp, MNT_WAIT)) == 0 || (flags & MNT_FORCE))
E 193
I 193
D 258
	if ((error = VFS_SYNC(mp, MNT_WAIT, p->p_ucred, p)) == 0 ||
E 258
I 258
	if (((mp->mnt_flag & MNT_RDONLY) ||
	     (error = VFS_SYNC(mp, MNT_WAIT, p->p_ucred, p)) == 0) ||
E 258
	    (flags & MNT_FORCE))
E 193
D 162
		error = VFS_UNMOUNT(mp, flags);
E 162
I 162
		error = VFS_UNMOUNT(mp, flags, p);
E 162
E 142
I 139
D 141
	mp->m_flag &= ~M_UNMOUNT;
E 141
I 141
D 261
	mp->mnt_flag &= ~MNT_UNMOUNT;
E 141
	vfs_unbusy(mp);
E 261
I 261
	simple_lock(&mountlist_slock);
E 261
E 139
E 114
	if (error) {
D 261
		vfs_unlock(mp);
	} else {
D 256
		vrele(coveredvp);
D 224
		vfs_remove(mp);
I 173
		if (mp->mnt_mounth != NULL)
E 224
I 224
		TAILQ_REMOVE(&mountlist, mp, mnt_list);
		mp->mnt_vnodecovered->v_mountedhere = (struct mount *)0;
E 256
I 256
		CIRCLEQ_REMOVE(&mountlist, mp, mnt_list);
		if (coveredvp != NULLVP) {
			vrele(coveredvp);
			mp->mnt_vnodecovered->v_mountedhere = (struct mount *)0;
		}
E 256
I 255
		mp->mnt_vfc->vfc_refcount--;
E 255
		vfs_unlock(mp);
		if (mp->mnt_vnodelist.lh_first != NULL)
E 224
			panic("unmount: dangling vnode");
E 173
		free((caddr_t)mp, M_MOUNT);
E 261
I 261
		mp->mnt_flag &= ~MNT_UNMOUNT;
		lockmgr(&mp->mnt_lock, LK_RELEASE | LK_INTERLOCK | LK_REENABLE,
		    &mountlist_slock, p);
		return (error);
E 261
	}
D 114
	RETURN (error);
E 114
I 114
D 261
	return (error);
E 261
I 261
	CIRCLEQ_REMOVE(&mountlist, mp, mnt_list);
	if ((coveredvp = mp->mnt_vnodecovered) != NULLVP) {
		coveredvp->v_mountedhere = (struct mount *)0;
		vrele(coveredvp);
	}
	mp->mnt_vfc->vfc_refcount--;
	if (mp->mnt_vnodelist.lh_first != NULL)
		panic("unmount: dangling vnode");
	lockmgr(&mp->mnt_lock, LK_RELEASE | LK_INTERLOCK, &mountlist_slock, p);
	if (mp->mnt_flag & MNT_MWAIT)
		wakeup((caddr_t)mp);
	free((caddr_t)mp, M_MOUNT);
	return (0);
E 261
E 114
E 102
E 101
}

I 47
/*
D 102
 * Common routine for chroot and chdir.
E 102
I 102
D 222
 * Sync system call.
E 222
 * Sync each mounted filesystem.
E 102
 */
I 204
D 237
#ifdef DIAGNOSTIC
E 237
I 237
#ifdef DEBUG
E 237
int syncprt = 0;
I 214
struct ctldebug debug0 = { "syncprt", &syncprt };
E 214
#endif

E 204
I 198
D 250
struct sync_args {
	int	dummy;
};
E 250
E 198
I 117
/* ARGSUSED */
I 250
int
E 250
E 117
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
D 109
sync()
E 109
I 109
D 143
sync(scp)
D 117
	register struct syscontext *scp;
E 117
I 117
	struct syscontext *scp;
E 143
I 143
sync(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 160
	struct args *uap;
E 160
I 160
D 198
	void *uap;
E 198
I 198
D 250
	struct sync_args *uap;
E 198
E 160
	int *retval;
E 250
I 250
	void *uap;
	register_t *retval;
E 250
E 143
E 117
E 109
E 102
E 37
{
D 102
	register struct inode *ip;
E 102
I 102
D 224
	register struct mount *mp;
I 139
	struct mount *omp;
E 224
I 224
	register struct mount *mp, *nmp;
I 229
	int asyncflag;
E 229
E 224
E 139
I 132
D 136
	struct mount *nmp;
E 136
E 132

I 261
	simple_lock(&mountlist_slock);
E 261
D 224
	mp = rootfs;
	do {
E 224
I 224
D 256
	for (mp = mountlist.tqh_first; mp != NULL; mp = nmp) {
E 256
I 256
	for (mp = mountlist.cqh_first; mp != (void *)&mountlist; mp = nmp) {
E 256
I 242
D 261
		/*
		 * Get the next pointer in case we hang on vfs_busy
		 * while we are being unmounted.
		 */
E 242
D 256
		nmp = mp->mnt_list.tqe_next;
E 256
I 256
		nmp = mp->mnt_list.cqe_next;
E 256
E 224
D 132
		if ((mp->m_flag & M_RDONLY) == 0)
E 132
I 132
D 136
		nmp = mp->m_next;
E 136
I 136
		/*
		 * The lock check below is to avoid races with mount
		 * and unmount.
		 */
E 136
D 139
		if ((mp->m_flag & (M_MLOCK|M_RDONLY)) == 0)
E 139
I 139
D 141
		if ((mp->m_flag & (M_MLOCK|M_RDONLY|M_MPBUSY)) == 0 &&
E 141
I 141
		if ((mp->mnt_flag & (MNT_MLOCK|MNT_RDONLY|MNT_MPBUSY)) == 0 &&
E 141
		    !vfs_busy(mp)) {
E 261
I 261
		if (vfs_busy(mp, LK_NOWAIT, &mountlist_slock, p)) {
			nmp = mp->mnt_list.cqe_next;
			continue;
		}
		if ((mp->mnt_flag & MNT_RDONLY) == 0) {
E 261
I 229
			asyncflag = mp->mnt_flag & MNT_ASYNC;
			mp->mnt_flag &= ~MNT_ASYNC;
E 229
E 139
E 132
D 193
			VFS_SYNC(mp, MNT_NOWAIT);
E 193
I 193
			VFS_SYNC(mp, MNT_NOWAIT, p->p_ucred, p);
I 229
			if (asyncflag)
				mp->mnt_flag |= MNT_ASYNC;
I 242
D 261
			/*
			 * Get the next pointer again, as the next filesystem
			 * might have been unmounted while we were sync'ing.
			 */
D 256
			nmp = mp->mnt_list.tqe_next;
E 256
I 256
			nmp = mp->mnt_list.cqe_next;
E 256
E 242
E 229
E 193
D 132
		mp = mp->m_next;
E 132
I 132
D 136
		mp = nmp;
E 136
I 136
D 139
		mp = mp->m_next;
E 139
I 139
D 224
			omp = mp;
D 141
			mp = mp->m_next;
E 141
I 141
			mp = mp->mnt_next;
E 141
			vfs_unbusy(omp);
		} else
D 141
			mp = mp->m_next;
E 141
I 141
			mp = mp->mnt_next;
E 141
E 139
E 136
E 132
	} while (mp != rootfs);
E 224
I 224
			vfs_unbusy(mp);
E 261
		}
I 261
		simple_lock(&mountlist_slock);
		nmp = mp->mnt_list.cqe_next;
		vfs_unbusy(mp, p);
E 261
	}
I 261
	simple_unlock(&mountlist_slock);
E 261
E 224
I 204
#ifdef DIAGNOSTIC
	if (syncprt)
		vfs_bufstats();
#endif /* DIAGNOSTIC */
E 204
I 161
	return (0);
E 161
I 139
}

/*
D 163
 * operate on filesystem quotas
E 163
I 163
D 222
 * Operate on filesystem quotas.
E 222
I 222
 * Change filesystem quotas.
E 222
E 163
 */
I 198
D 250
struct quotactl_args {
	char *path;
	int cmd;
	int uid;
	caddr_t arg;
};
E 250
E 198
D 143
quotactl(scp)
	register struct syscontext *scp;
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
quotactl(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		char *path;
		int cmd;
		int uid;
		caddr_t arg;
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct quotactl_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct quotactl_args /* {
		syscallarg(char *) path;
		syscallarg(int) cmd;
		syscallarg(int) uid;
		syscallarg(caddr_t) arg;
	} */ *uap;
	register_t *retval;
E 250
{
E 143
	register struct mount *mp;
D 143
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
	int error;
I 160
	struct nameidata nd;
E 160

I 160
D 174
	ndp = &nd;
E 160
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->path;
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, path), p);
E 250
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	mp = ndp->ni_vp->v_mount;
	vrele(ndp->ni_vp);
E 174
I 174
	mp = nd.ni_vp->v_mount;
	vrele(nd.ni_vp);
E 174
D 160
	RETURN (VFS_QUOTACTL(mp, uap->cmd, uap->uid, uap->arg));
E 160
I 160
D 162
	return (VFS_QUOTACTL(mp, uap->cmd, uap->uid, uap->arg));
E 162
I 162
D 250
	return (VFS_QUOTACTL(mp, uap->cmd, uap->uid, uap->arg, p));
E 250
I 250
	return (VFS_QUOTACTL(mp, SCARG(uap, cmd), SCARG(uap, uid),
	    SCARG(uap, arg), p));
E 250
E 162
E 160
E 139
}

/*
D 163
 * get filesystem statistics
E 163
I 163
 * Get filesystem statistics.
E 163
 */
I 198
D 250
struct statfs_args {
	char *path;
	struct statfs *buf;
};
E 250
E 198
D 109
statfs()
E 109
I 109
D 143
statfs(scp)
	register struct syscontext *scp;
E 109
{
E 102
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
statfs(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
I 102
		char *path;
		struct statfs *buf;
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct statfs_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct statfs_args /* {
		syscallarg(char *) path;
		syscallarg(struct statfs *) buf;
	} */ *uap;
	register_t *retval;
E 250
{
E 143
E 109
D 121
	register struct vnode *vp;
E 121
I 116
	register struct mount *mp;
E 116
D 109
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
D 136
	struct statfs sb;
E 136
I 136
	register struct statfs *sp;
E 136
	int error;
I 160
	struct nameidata nd;
E 160

I 160
D 174
	ndp = &nd;
E 160
D 121
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
E 121
I 121
	ndp->ni_nameiop = LOOKUP | FOLLOW;
E 121
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->path;
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, path), p);
E 250
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 121
	vp = ndp->ni_vp;
D 116
	if (error = VFS_STATFS(vp->v_mount, &sb))
E 116
I 116
	mp = vp->v_mount;
E 121
I 121
D 174
	mp = ndp->ni_vp->v_mount;
E 174
I 174
	mp = nd.ni_vp->v_mount;
E 174
I 136
D 141
	sp = &mp->m_stat;
E 141
I 141
	sp = &mp->mnt_stat;
E 141
E 136
D 174
	vrele(ndp->ni_vp);
E 174
I 174
	vrele(nd.ni_vp);
E 174
E 121
D 136
	if (error = VFS_STATFS(mp, &sb))
E 136
I 136
D 162
	if (error = VFS_STATFS(mp, sp))
E 162
I 162
	if (error = VFS_STATFS(mp, sp, p))
E 162
E 136
E 116
D 121
		goto out;
E 121
I 121
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
E 121
I 116
D 136
	sb.f_flags = mp->m_flag & M_VISFLAGMASK;
	sb.f_fsid = mp->m_fsid;
E 116
D 121
	error = copyout((caddr_t)&sb, (caddr_t)uap->buf, sizeof(sb));
out:
	vput(vp);
	RETURN (error);
E 121
I 121
	RETURN (copyout((caddr_t)&sb, (caddr_t)uap->buf, sizeof(sb)));
E 136
I 136
D 141
	sp->f_flags = mp->m_flag & M_VISFLAGMASK;
E 141
I 141
	sp->f_flags = mp->mnt_flag & MNT_VISFLAGMASK;
E 141
D 160
	RETURN (copyout((caddr_t)sp, (caddr_t)uap->buf, sizeof(*sp)));
E 160
I 160
D 250
	return (copyout((caddr_t)sp, (caddr_t)uap->buf, sizeof(*sp)));
E 250
I 250
	return (copyout((caddr_t)sp, (caddr_t)SCARG(uap, buf), sizeof(*sp)));
E 250
E 160
E 136
E 121
}

D 109
fstatfs()
E 109
I 109
D 143
fstatfs(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/*
D 163
 * get filesystem statistics
E 163
I 163
 * Get filesystem statistics.
E 163
 */
I 198
D 250
struct fstatfs_args {
	int fd;
	struct statfs *buf;
};
E 250
E 198
/* ARGSUSED */
I 250
int
E 250
fstatfs(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		int fd;
		struct statfs *buf;
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct fstatfs_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct fstatfs_args /* {
		syscallarg(int) fd;
		syscallarg(struct statfs *) buf;
	} */ *uap;
	register_t *retval;
E 250
{
E 143
E 109
	struct file *fp;
I 116
	struct mount *mp;
E 116
D 136
	struct statfs sb;
E 136
I 136
	register struct statfs *sp;
E 136
	int error;

D 109
	if (error = getvnode(uap->fd, &fp))
E 109
I 109
D 143
	if (error = getvnode(scp->sc_ofile, uap->fd, &fp))
E 143
I 143
D 157
	if (error = getvnode(u.u_ofile, uap->fd, &fp))
E 157
I 157
D 250
	if (error = getvnode(p->p_fd, uap->fd, &fp))
E 250
I 250
	if (error = getvnode(p->p_fd, SCARG(uap, fd), &fp))
E 250
E 157
E 143
E 109
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
D 116
	if (error = VFS_STATFS(((struct vnode *)fp->f_data)->v_mount, &sb))
E 116
I 116
	mp = ((struct vnode *)fp->f_data)->v_mount;
D 136
	if (error = VFS_STATFS(mp, &sb))
E 136
I 136
D 141
	sp = &mp->m_stat;
E 141
I 141
	sp = &mp->mnt_stat;
E 141
D 162
	if (error = VFS_STATFS(mp, sp))
E 162
I 162
	if (error = VFS_STATFS(mp, sp, p))
E 162
E 136
E 116
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
I 116
D 136
	sb.f_flags = mp->m_flag & M_VISFLAGMASK;
	sb.f_fsid = mp->m_fsid;
E 116
	RETURN (copyout((caddr_t)&sb, (caddr_t)uap->buf, sizeof(sb)));
E 136
I 136
D 141
	sp->f_flags = mp->m_flag & M_VISFLAGMASK;
E 141
I 141
	sp->f_flags = mp->mnt_flag & MNT_VISFLAGMASK;
E 141
D 160
	RETURN (copyout((caddr_t)sp, (caddr_t)uap->buf, sizeof(*sp)));
E 160
I 160
D 250
	return (copyout((caddr_t)sp, (caddr_t)uap->buf, sizeof(*sp)));
E 250
I 250
	return (copyout((caddr_t)sp, (caddr_t)SCARG(uap, buf), sizeof(*sp)));
E 250
E 160
E 136
}

/*
I 107
D 163
 * get statistics on all filesystems
E 163
I 163
 * Get statistics on all filesystems.
E 163
 */
I 198
D 250
struct getfsstat_args {
	struct statfs *buf;
	long bufsize;
	int flags;
};
E 250
I 250
int
E 250
E 198
D 109
getfsstat()
E 109
I 109
D 143
getfsstat(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
getfsstat(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		struct statfs *buf;
		long bufsize;
I 136
		int flags;
E 136
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct getfsstat_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct getfsstat_args /* {
		syscallarg(struct statfs *) buf;
		syscallarg(long) bufsize;
		syscallarg(int) flags;
	} */ *uap;
	register_t *retval;
E 250
{
E 143
E 109
D 224
	register struct mount *mp;
E 224
I 224
	register struct mount *mp, *nmp;
E 224
I 136
	register struct statfs *sp;
E 136
D 124
	register struct statfs *sfsp;
E 124
I 124
	caddr_t sfsp;
E 124
	long count, maxcount, error;
I 124
D 136
	struct statfs sb;
E 136
E 124

D 250
	maxcount = uap->bufsize / sizeof(struct statfs);
D 124
	sfsp = uap->buf;
E 124
I 124
	sfsp = (caddr_t)uap->buf;
E 250
I 250
	maxcount = SCARG(uap, bufsize) / sizeof(struct statfs);
	sfsp = (caddr_t)SCARG(uap, buf);
E 250
E 124
D 224
	mp = rootfs;
	count = 0;
	do {
E 224
I 224
D 256
	for (count = 0, mp = mountlist.tqh_first; mp != NULL; mp = nmp) {
		nmp = mp->mnt_list.tqe_next;
E 256
I 256
	count = 0;
I 261
	simple_lock(&mountlist_slock);
E 261
	for (mp = mountlist.cqh_first; mp != (void *)&mountlist; mp = nmp) {
D 261
		nmp = mp->mnt_list.cqe_next;
E 256
E 224
D 124
		count++;
D 110
		if (sfsp && count <= maxcount) {
E 110
I 110
		if (sfsp && count <= maxcount &&
		    ((mp->m_flag & M_MLOCK) == 0)) {
E 110
			if (error = VFS_STATFS(mp, sfsp))
E 124
I 124
D 141
		if (sfsp && count < maxcount && ((mp->m_flag & M_MLOCK) == 0)) {
D 125
			if (error = VFS_STATFS(mp, &sb))
E 124
				RETURN (error);
E 125
I 125
D 136
			if (error = VFS_STATFS(mp, &sb)) {
E 136
I 136
			sp = &mp->m_stat;
E 141
I 141
		if (sfsp && count < maxcount &&
		    ((mp->mnt_flag & MNT_MLOCK) == 0)) {
E 261
I 261
		if (vfs_busy(mp, LK_NOWAIT, &mountlist_slock, p)) {
			nmp = mp->mnt_list.cqe_next;
			continue;
		}
		if (sfsp && count < maxcount) {
E 261
			sp = &mp->mnt_stat;
E 141
			/*
			 * If MNT_NOWAIT is specified, do not refresh the
			 * fsstat cache. MNT_WAIT overrides MNT_NOWAIT.
			 */
D 250
			if (((uap->flags & MNT_NOWAIT) == 0 ||
			    (uap->flags & MNT_WAIT)) &&
E 250
I 250
			if (((SCARG(uap, flags) & MNT_NOWAIT) == 0 ||
			    (SCARG(uap, flags) & MNT_WAIT)) &&
E 250
D 162
			    (error = VFS_STATFS(mp, sp))) {
E 162
I 162
D 224
			    (error = VFS_STATFS(mp, sp, p))) {
E 162
E 136
D 141
				mp = mp->m_prev;
E 141
I 141
				mp = mp->mnt_prev;
E 224
I 224
D 263
			    (error = VFS_STATFS(mp, sp, p)))
E 263
I 263
			    (error = VFS_STATFS(mp, sp, p))) {
				simple_lock(&mountlist_slock);
				nmp = mp->mnt_list.cqe_next;
				vfs_unbusy(mp, p);
E 263
E 224
E 141
				continue;
I 263
			}
E 263
D 224
			}
E 224
E 125
I 116
D 124
			sfsp->f_flags = mp->m_flag & M_VISFLAGMASK;
			sfsp->f_fsid = mp->m_fsid;
E 116
			sfsp++;
E 124
I 124
D 136
			sb.f_flags = mp->m_flag & M_VISFLAGMASK;
			sb.f_fsid = mp->m_fsid;
			if (error = copyout((caddr_t)&sb, sfsp, sizeof(sb)))
E 136
I 136
D 141
			sp->f_flags = mp->m_flag & M_VISFLAGMASK;
E 141
I 141
			sp->f_flags = mp->mnt_flag & MNT_VISFLAGMASK;
E 141
			if (error = copyout((caddr_t)sp, sfsp, sizeof(*sp)))
E 136
D 160
				RETURN (error);
E 160
I 160
				return (error);
E 160
D 136
			sfsp += sizeof(sb);
E 136
I 136
			sfsp += sizeof(*sp);
E 136
E 124
		}
I 124
		count++;
I 261
		simple_lock(&mountlist_slock);
		nmp = mp->mnt_list.cqe_next;
		vfs_unbusy(mp, p);
E 261
E 124
D 141
		mp = mp->m_prev;
E 141
I 141
D 224
		mp = mp->mnt_prev;
E 141
	} while (mp != rootfs);
E 224
I 224
	}
I 261
	simple_unlock(&mountlist_slock);
E 261
E 224
	if (sfsp && count > maxcount)
D 109
		u.u_r.r_val1 = maxcount;
E 109
I 109
D 143
		scp->sc_retval1 = maxcount;
E 143
I 143
		*retval = maxcount;
E 143
E 109
	else
D 109
		u.u_r.r_val1 = count;
E 109
I 109
D 143
		scp->sc_retval1 = count;
E 143
I 143
		*retval = count;
E 143
E 109
D 160
	RETURN (0);
E 160
I 160
	return (0);
E 160
}

/*
E 107
I 105
 * Change current working directory to a given file descriptor.
 */
I 198
D 250
struct fchdir_args {
	int	fd;
};
E 250
E 198
D 109
fchdir()
E 109
I 109
D 143
fchdir(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
fchdir(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	struct args {
E 143
		int	fd;
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	struct fchdir_args *uap;
E 198
	int *retval;
E 250
I 250
	struct fchdir_args /* {
		syscallarg(int) fd;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_ACCESS;
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 157
	register struct filedesc *fdp = p->p_fd;
E 157
E 143
E 109
D 248
	register struct vnode *vp;
E 248
I 248
	struct vnode *vp, *tdp;
	struct mount *mp;
E 248
	struct file *fp;
	int error;

D 109
	if (error = getvnode(uap->fd, &fp))
E 109
I 109
D 143
	if (error = getvnode(scp->sc_ofile, uap->fd, &fp))
E 143
I 143
D 157
	if (error = getvnode(u.u_ofile, uap->fd, &fp))
E 157
I 157
D 250
	if (error = getvnode(fdp, uap->fd, &fp))
E 250
I 250
	if (error = getvnode(fdp, SCARG(uap, fd), &fp))
E 250
E 157
E 143
E 109
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
	vp = (struct vnode *)fp->f_data;
I 248
	VREF(vp);
E 248
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
	if (vp->v_type != VDIR)
		error = ENOTDIR;
	else
D 108
		error = vn_access(vp, VEXEC, u.u_cred);
E 108
I 108
D 109
		error = VOP_ACCESS(vp, VEXEC, u.u_cred);
E 109
I 109
D 143
		error = VOP_ACCESS(vp, VEXEC, scp->sc_cred);
E 143
I 143
D 160
		error = VOP_ACCESS(vp, VEXEC, ndp->ni_cred);
E 160
I 160
D 162
		error = VOP_ACCESS(vp, VEXEC, p->p_ucred);
E 162
I 162
		error = VOP_ACCESS(vp, VEXEC, p->p_ucred, p);
I 248
	while (!error && (mp = vp->v_mountedhere) != NULL) {
D 261
		if (mp->mnt_flag & MNT_MLOCK) {
			mp->mnt_flag |= MNT_MWAIT;
			sleep((caddr_t)mp, PVFS);
E 261
I 261
		if (vfs_busy(mp, 0, 0, p))
E 261
			continue;
D 261
		}
		if (error = VFS_ROOT(mp, &tdp))
E 261
I 261
		error = VFS_ROOT(mp, &tdp);
		vfs_unbusy(mp, p);
		if (error)
E 261
			break;
		vput(vp);
		vp = tdp;
	}
E 248
E 162
E 160
E 143
E 109
E 108
D 259
	VOP_UNLOCK(vp);
E 259
I 259
D 260
	VOP_UNLOCK(vp, 0, p);
E 260
E 259
I 131
D 248
	if (error)
E 248
I 248
	if (error) {
D 260
		vrele(vp);
E 260
I 260
		vput(vp);
E 260
E 248
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
D 248
	VREF(vp);
E 248
I 248
	}
I 260
	VOP_UNLOCK(vp, 0, p);
E 260
E 248
E 131
D 109
	vrele(u.u_cdir);
	u.u_cdir = vp;
E 109
I 109
D 143
	vrele(scp->sc_cdir);
	scp->sc_cdir = vp;
E 143
I 143
D 157
	vrele(ndp->ni_cdir);
	ndp->ni_cdir = vp;
E 157
I 157
	vrele(fdp->fd_cdir);
	fdp->fd_cdir = vp;
E 157
E 143
E 109
D 131
	RETURN (error);
E 131
I 131
D 160
	RETURN (0);
E 160
I 160
	return (0);
E 160
E 131
}

/*
E 105
 * Change current working directory (``.'').
 */
I 198
D 250
struct chdir_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
};
E 250
E 198
D 109
chdir()
E 109
I 109
D 143
chdir(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
chdir(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	struct args {
E 143
E 102
		char	*fname;
D 82
	};
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	struct chdir_args *uap;
E 198
	int *retval;
E 250
I 250
	struct chdir_args /* {
		syscallarg(char *) path;
	} */ *uap;
	register_t *retval;
E 250
{
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
I 157
	register struct filedesc *fdp = p->p_fd;
E 157
E 143
E 109
I 102
	int error;
I 160
	struct nameidata nd;
E 160
E 102
E 82

I 160
D 174
	ndp = &nd;
E 160
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
E 102
I 102
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 102
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
E 102
I 102
D 160
	if (error = chdirec(ndp))
		RETURN (error);
E 160
I 160
	if (error = chdirec(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
D 176
	if (error = chdirec(&nd))
E 176
I 176
	if (error = chdirec(&nd, p))
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
E 250
	if (error = change_dir(&nd, p))
E 222
E 176
E 174
		return (error);
E 160
D 109
	vrele(u.u_cdir);
	u.u_cdir = ndp->ni_vp;
E 109
I 109
D 143
	vrele(scp->sc_cdir);
	scp->sc_cdir = ndp->ni_vp;
E 143
I 143
D 157
	vrele(ndp->ni_cdir);
	ndp->ni_cdir = ndp->ni_vp;
E 157
I 157
	vrele(fdp->fd_cdir);
D 174
	fdp->fd_cdir = ndp->ni_vp;
E 174
I 174
	fdp->fd_cdir = nd.ni_vp;
E 174
E 157
E 143
E 109
D 160
	RETURN (0);
E 160
I 160
	return (0);
E 160
}
E 102

D 102
bad:
	iput(ip);
E 102
I 102
/*
 * Change notion of root (``/'') directory.
 */
I 198
D 250
struct chroot_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
};
E 250
E 198
D 109
chroot()
E 109
I 109
D 143
chroot(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
chroot(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	struct args {
E 143
		char	*fname;
D 109
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	struct chroot_args *uap;
E 198
	int *retval;
E 250
I 250
	struct chroot_args /* {
		syscallarg(char *) path;
	} */ *uap;
	register_t *retval;
E 250
{
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
I 157
	register struct filedesc *fdp = p->p_fd;
E 157
E 143
E 109
	int error;
I 160
	struct nameidata nd;
E 160

D 109
	if (error = suser(u.u_cred, &u.u_acflag))
E 109
I 109
D 143
	if (error = suser(scp->sc_cred, &scp->sc_acflag))
E 143
I 143
D 160
	if (error = suser(ndp->ni_cred, &u.u_acflag))
E 143
E 109
		RETURN (error);
E 160
I 160
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
D 174
	ndp = &nd;
E 160
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 160
	if (error = chdirec(ndp))
		RETURN (error);
E 160
I 160
	if (error = chdirec(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
D 176
	if (error = chdirec(&nd))
E 176
I 176
	if (error = chdirec(&nd, p))
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
E 250
	if (error = change_dir(&nd, p))
E 222
E 176
E 174
		return (error);
E 160
D 109
	vrele(u.u_rdir);
	u.u_rdir = ndp->ni_vp;
E 109
I 109
D 119
	vrele(scp->sc_rdir);
E 119
I 119
D 143
	if (scp->sc_rdir != NULL)
		vrele(scp->sc_rdir);
E 119
	scp->sc_rdir = ndp->ni_vp;
E 143
I 143
D 157
	if (ndp->ni_rdir != NULL)
		vrele(ndp->ni_rdir);
	ndp->ni_rdir = ndp->ni_vp;
E 157
I 157
	if (fdp->fd_rdir != NULL)
		vrele(fdp->fd_rdir);
D 174
	fdp->fd_rdir = ndp->ni_vp;
E 174
I 174
	fdp->fd_rdir = nd.ni_vp;
E 174
E 157
E 143
E 109
D 160
	RETURN (0);
E 160
I 160
	return (0);
E 160
E 102
}

E 26
/*
I 102
 * Common routine for chroot and chdir.
 */
D 160
chdirec(ndp)
	register struct nameidata *ndp;
E 160
I 160
D 222
chdirec(ndp, p)
E 222
I 222
static int
change_dir(ndp, p)
E 222
D 174
	struct nameidata *ndp;
E 174
I 174
	register struct nameidata *ndp;
E 174
	struct proc *p;
E 160
{
I 187
D 195
	USES_VOP_ACCESS;
	USES_VOP_UNLOCK;
E 195
E 187
	struct vnode *vp;
	int error;

D 160
	if (error = namei(ndp))
E 160
I 160
D 174
	if (error = namei(ndp, p))
E 174
I 174
	if (error = namei(ndp))
E 174
E 160
		return (error);
	vp = ndp->ni_vp;
	if (vp->v_type != VDIR)
		error = ENOTDIR;
	else
D 108
		error = vn_access(vp, VEXEC, ndp->ni_cred);
E 108
I 108
D 160
		error = VOP_ACCESS(vp, VEXEC, ndp->ni_cred);
E 160
I 160
D 162
		error = VOP_ACCESS(vp, VEXEC, p->p_ucred);
E 162
I 162
		error = VOP_ACCESS(vp, VEXEC, p->p_ucred, p);
E 162
E 160
E 108
D 259
	VOP_UNLOCK(vp);
E 259
I 259
D 260
	VOP_UNLOCK(vp, 0, p);
E 260
E 259
	if (error)
D 260
		vrele(vp);
E 260
I 260
		vput(vp);
	else
		VOP_UNLOCK(vp, 0, p);
E 260
	return (error);
}

/*
E 102
I 26
D 222
 * Open system call.
E 222
I 143
 * Check permissions, allocate an open file structure,
 * and call the device open routine if any.
E 143
 */
I 198
D 250
struct open_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
	int	flags;
E 222
	int	mode;
D 222
	int	crtmode;
E 222
};
E 250
I 250
int
E 250
E 198
D 109
open()
E 109
I 109
D 143
open(scp)
	register struct syscontext *scp;
E 109
{
D 63
	register struct inode *ip;
	register struct a {
E 63
I 63
	struct a {
E 143
I 143
open(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
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
D 109
	} *uap = (struct a *) u.u_ap;
I 102
	struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *) scp->sc_ap;
	struct nameidata *ndp = &scp->sc_nd;
E 109
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
E 102
I 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 109
	RETURN (copen(uap->mode-FOPEN, uap->crtmode &~ u.u_cmask, ndp,
		&u.u_r.r_val1));
E 109
I 109
	RETURN (copen(scp, uap->mode-FOPEN, uap->crtmode &~ scp->sc_cmask, ndp,
		&scp->sc_retval1));
E 109
E 102
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
D 109
creat()
E 109
I 109
creat(scp)
	register struct syscontext *scp;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct open_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct open_args /* {
		syscallarg(char *) path;
		syscallarg(int) flags;
		syscallarg(int) mode;
	} */ *uap;
	register_t *retval;
E 250
E 143
E 109
E 63
E 35
{
I 187
D 195
	USES_VOP_ADVLOCK;
	USES_VOP_UNLOCK;
E 195
E 187
D 63
	register struct inode *ip;
	register struct a {
E 63
I 63
D 143
	struct a {
E 63
		char	*fname;
		int	fmode;
D 63
	} *uap;
E 63
I 63
D 109
	} *uap = (struct a *)u.u_ap;
I 102
	struct nameidata *ndp = &u.u_nd;
E 109
I 109
	} *uap = (struct a *)scp->sc_ap;
	struct nameidata *ndp = &scp->sc_nd;
E 109
E 102
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
D 102
	copen(FWRITE|FCREAT|FTRUNC, uap->fmode, uap->fname);
E 102
I 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 109
	RETURN (copen(FWRITE|FCREAT|FTRUNC, uap->fmode &~ u.u_cmask, ndp,
		&u.u_r.r_val1));
E 109
I 109
	RETURN (copen(scp, FWRITE|FCREAT|FTRUNC, uap->fmode &~ scp->sc_cmask,
		ndp, &scp->sc_retval1));
E 109
E 102
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
D 102
copen(mode, arg, fname)
E 82
	register int mode;
	int arg;
I 82
	caddr_t fname;
E 102
I 102
D 109
copen(fmode, cmode, ndp, resultfd)
E 109
I 109
copen(scp, fmode, cmode, ndp, resultfd)
	register struct syscontext *scp;
E 109
	int fmode, cmode;
	struct nameidata *ndp;
	int *resultfd;
E 102
E 82
E 63
{
E 143
I 143
D 160
	struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	struct nameidata *ndp;
E 174
E 160
I 157
	register struct filedesc *fdp = p->p_fd;
E 157
E 143
I 63
D 102
	register struct inode *ip;
E 102
E 63
	register struct file *fp;
I 170
	register struct vnode *vp;
E 170
I 143
D 222
	int fmode, cmode;
E 222
I 222
	int flags, cmode;
E 222
E 143
I 82
D 102
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
E 102
I 102
	struct file *nfp;
D 167
	int indx, error;
E 167
I 167
	int type, indx, error;
	struct flock lf;
E 167
I 160
	struct nameidata nd;
E 160
	extern struct fileops vnops;
E 102
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
D 102
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
E 93
	}
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
E 102
I 102
D 157
	if (error = falloc(&nfp, &indx))
E 157
I 157
	if (error = falloc(p, &nfp, &indx))
E 157
D 143
		return (error);
E 143
I 143
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
E 143
	fp = nfp;
D 109
	u.u_r.r_val1 = indx;	/* XXX for fdopen() */
E 109
I 109
D 143
	scp->sc_retval1 = indx;	/* XXX for fdopen() */
E 109
D 137
	if (error = vn_open(ndp, fmode, (cmode & 07777) &~ ISVTX)) {
E 137
I 137
	if (error = vn_open(ndp, fmode, (cmode & 07777) &~ S_ISVTX)) {
E 143
I 143
D 159
	fmode = uap->mode - FOPEN;
E 159
I 159
D 222
	fmode = FFLAGS(uap->mode);
E 159
D 157
	cmode = ((uap->crtmode &~ u.u_cmask) & 07777) &~ S_ISVTX;
E 157
I 157
	cmode = ((uap->crtmode &~ fdp->fd_cmask) & 07777) &~ S_ISVTX;
I 160
D 174
	ndp = &nd;
E 160
E 157
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
E 174
I 174
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	flags = FFLAGS(uap->flags);
	cmode = ((uap->mode &~ fdp->fd_cmask) & ALLPERMS) &~ S_ISTXT;
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->path, p);
E 250
I 250
	flags = FFLAGS(SCARG(uap, flags));
	cmode = ((SCARG(uap, mode) &~ fdp->fd_cmask) & ALLPERMS) &~ S_ISTXT;
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 222
E 174
D 148
	u.u_r.u_rv.R_val1 = indx;		/* XXX for fdopen() */
E 148
I 148
D 149
	p->p_devtmp = -1;			/* XXX check for fdopen */
E 149
I 149
D 152
	p->p_dupfd = -1;			/* XXX check for fdopen */
E 152
I 152
D 153
	p->p_dupfd = (u_char)-1;		/* XXX check for fdopen */
E 153
I 153
	p->p_dupfd = -indx - 1;			/* XXX check for fdopen */
E 153
E 152
E 149
E 148
D 160
	if (error = vn_open(ndp, fmode, cmode)) {
E 160
I 160
D 174
	if (error = vn_open(ndp, p, fmode, cmode)) {
E 174
I 174
D 222
	if (error = vn_open(&nd, fmode, cmode)) {
E 222
I 222
	if (error = vn_open(&nd, flags, cmode)) {
E 222
I 189
D 196
		int dfd = p->p_dupfd;
		p->p_dupfd = 0;
E 196
E 189
E 174
E 160
E 143
E 137
E 102
D 93
		u.u_ofile[i] = NULL;
E 93
I 93
D 109
		u.u_ofile[indx] = NULL;
E 109
I 109
D 118
		scp->sc_ofile[indx] = NULL;
E 118
E 109
E 93
D 102
		closef(fp);
E 63
E 37
		return;
E 102
I 102
D 169
		crfree(fp->f_cred);
		fp->f_count--;
E 169
I 169
		ffree(fp);
E 169
I 118
D 138
		if (error == -1)	/* XXX from fdopen */
			return (0);	/* XXX from fdopen */
E 138
I 138
D 143
		if (error == EJUSTRETURN)	/* XXX from fdopen */
			return (0);		/* XXX from fdopen */
E 143
I 143
D 148
		if (error == EJUSTRETURN) {	/* XXX from fdopen */
E 148
I 148
D 189
		if (error == ENODEV &&		/* XXX from fdopen */
D 149
		    p->p_devtmp >= 0 &&
		    (error = dupfdopen(indx, p->p_devtmp, fmode)) == 0) {
E 149
I 149
D 152
		    p->p_dupfd >= 0 &&
E 152
I 152
D 153
		    p->p_dupfd != (u_char)-1 &&
E 153
I 153
		    p->p_dupfd >= 0 &&
E 153
E 152
D 157
		    (error = dupfdopen(indx, p->p_dupfd, fmode)) == 0) {
E 157
I 157
		    (error = dupfdopen(fdp, indx, p->p_dupfd, fmode)) == 0) {
E 189
I 189
D 196
		if ((error == ENODEV || error == ENXIO) && /* XXX from fdopen */
		    dfd >= 0 &&
E 196
I 196
		if ((error == ENODEV || error == ENXIO) &&
D 250
		    p->p_dupfd >= 0 && 			/* XXX from fdopen */
E 250
I 250
		    p->p_dupfd >= 0 &&			/* XXX from fdopen */
E 250
E 196
D 222
		    (error = dupfdopen(fdp, indx, p->p_dupfd,
					fmode, error)) == 0) {
E 222
I 222
		    (error =
D 250
		        dupfdopen(fdp, indx, p->p_dupfd, flags, error)) == 0) {
E 250
I 250
			dupfdopen(fdp, indx, p->p_dupfd, flags, error)) == 0) {
E 250
E 222
E 189
E 157
E 149
E 148
			*retval = indx;
D 160
			RETURN (0);
E 160
I 160
			return (0);
E 160
		}
E 143
		if (error == ERESTART)
			error = EINTR;
E 138
D 143
		scp->sc_ofile[indx] = NULL;
E 118
		return (error);
E 143
I 143
D 157
		u.u_ofile[indx] = NULL;
E 157
I 157
D 161
		OFILE(fdp, indx) = NULL;
E 161
I 161
		fdp->fd_ofiles[indx] = NULL;
E 161
E 157
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
E 143
E 102
I 37
	}
I 189
	p->p_dupfd = 0;
E 189
I 170
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
E 174
E 170
I 168
D 222
	fp->f_flag = fmode & FMASK;
E 222
I 222
	fp->f_flag = flags & FMASK;
E 222
I 192
	fp->f_type = DTYPE_VNODE;
	fp->f_ops = &vnops;
	fp->f_data = (caddr_t)vp;
E 192
E 168
I 167
D 222
	if (fmode & (O_EXLOCK | O_SHLOCK)) {
E 222
I 222
	if (flags & (O_EXLOCK | O_SHLOCK)) {
E 222
		lf.l_whence = SEEK_SET;
		lf.l_start = 0;
		lf.l_len = 0;
D 222
		if (fmode & O_EXLOCK)
E 222
I 222
		if (flags & O_EXLOCK)
E 222
			lf.l_type = F_WRLCK;
		else
			lf.l_type = F_RDLCK;
		type = F_FLOCK;
D 222
		if ((fmode & FNONBLOCK) == 0)
E 222
I 222
		if ((flags & FNONBLOCK) == 0)
E 222
			type |= F_WAIT;
I 226
D 259
		VOP_UNLOCK(vp);
E 259
I 259
		VOP_UNLOCK(vp, 0, p);
E 259
E 226
D 170
		if (error =
		    VOP_ADVLOCK(ndp->ni_vp, (caddr_t)fp, F_SETLK, &lf, type)) {
			vput(ndp->ni_vp);
E 170
I 170
		if (error = VOP_ADVLOCK(vp, (caddr_t)fp, F_SETLK, &lf, type)) {
D 226
			VOP_UNLOCK(vp);
E 226
			(void) vn_close(vp, fp->f_flag, fp->f_cred, p);
E 170
D 169
			crfree(fp->f_cred);
			fp->f_count--;
E 169
I 169
			ffree(fp);
E 169
			fdp->fd_ofiles[indx] = NULL;
			return (error);
		}
I 226
D 259
		VOP_LOCK(vp);
E 259
I 259
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
E 226
I 168
		fp->f_flag |= FHASLOCK;
E 168
	}
D 170
	VOP_UNLOCK(ndp->ni_vp);
E 170
I 170
D 259
	VOP_UNLOCK(vp);
E 259
I 259
	VOP_UNLOCK(vp, 0, p);
E 259
E 170
E 167
I 63
D 73
#endif
E 73
D 102
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
	iput(ip);
I 93
bad1:
	u.u_ofile[indx] = NULL;
	fp->f_count--;
E 102
I 102
D 168
	fp->f_flag = fmode & FMASK;
E 168
D 192
	fp->f_type = DTYPE_VNODE;
	fp->f_ops = &vnops;
D 170
	fp->f_data = (caddr_t)ndp->ni_vp;
E 170
I 170
	fp->f_data = (caddr_t)vp;
E 192
E 170
D 143
	if (resultfd)
		*resultfd = indx;
	return (0);
E 143
I 143
	*retval = indx;
D 160
	RETURN (0);
E 160
I 160
	return (0);
E 160
E 143
E 102
E 93
E 37
E 31
}

I 145
#ifdef COMPAT_43
E 145
/*
D 143
 * Mknod system call
E 143
I 143
D 222
 * Creat system call.
E 222
I 222
 * Create a file.
E 222
E 143
 */
I 198
D 250
struct ocreat_args {
D 222
	char	*fname;
	int	fmode;
E 222
I 222
	char	*path;
	int	mode;
E 222
};
E 198
D 109
mknod()
E 109
I 109
D 143
mknod(scp)
	register struct syscontext *scp;
E 143
I 143
D 145
creat(p, uap, retval)
E 145
I 145
ocreat(p, uap, retval)
E 250
I 250
int
compat_43_creat(p, uap, retval)
E 250
E 145
	struct proc *p;
D 198
	register struct args {
		char	*fname;
		int	fmode;
	} *uap;
E 198
I 198
D 250
	register struct ocreat_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct compat_43_creat_args /* {
		syscallarg(char *) path;
		syscallarg(int) mode;
	} */ *uap;
	register_t *retval;
E 250
E 143
E 109
{
D 102
	register struct inode *ip;
E 102
D 143
	register struct a {
E 143
I 143
D 194
	struct args {
E 194
I 194
D 198
	struct nargs {
E 194
E 143
		char	*fname;
I 143
		int	mode;
		int	crtmode;
	} openuap;
E 198
I 198
D 250
	struct open_args openuap;
E 250
I 250
	struct open_args /* {
		syscallarg(char *) path;
		syscallarg(int) flags;
		syscallarg(int) mode;
	} */ nuap;
E 250
E 198

D 222
	openuap.fname = uap->fname;
	openuap.crtmode = uap->fmode;
	openuap.mode = O_WRONLY | O_CREAT | O_TRUNC;
E 222
I 222
D 250
	openuap.path = uap->path;
	openuap.mode = uap->mode;
	openuap.flags = O_WRONLY | O_CREAT | O_TRUNC;
E 222
D 160
	RETURN (open(p, &openuap, retval));
E 160
I 160
	return (open(p, &openuap, retval));
E 250
I 250
	SCARG(&nuap, path) = SCARG(uap, path);
	SCARG(&nuap, mode) = SCARG(uap, mode);
	SCARG(&nuap, flags) = O_WRONLY | O_CREAT | O_TRUNC;
	return (open(p, &nuap, retval));
E 250
E 160
}
I 145
#endif /* COMPAT_43 */
E 145

/*
D 163
 * Mknod system call
E 163
I 163
D 222
 * Mknod system call.
E 222
I 222
 * Create a special file.
E 222
E 163
 */
I 198
D 250
struct mknod_args {
D 222
	char	*fname;
	int	fmode;
E 222
I 222
	char	*path;
	int	mode;
E 222
	int	dev;
};
E 250
E 198
/* ARGSUSED */
I 250
int
E 250
mknod(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
		char	*fname;
E 143
		int	fmode;
		int	dev;
D 82
	} *uap;
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct mknod_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct mknod_args /* {
		syscallarg(char *) path;
		syscallarg(int) mode;
		syscallarg(int) dev;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_ABORTOP;
	USES_VOP_MKNOD;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
I 102
	register struct vnode *vp;
	struct vattr vattr;
	int error;
I 240
	int whiteout;
E 240
I 160
	struct nameidata nd;
E 160
E 102
E 82

I 175
	CHECKPOINTREF;
E 175
I 172
D 174
	CHECKPOINT;
E 174
E 172
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
E 102
I 102
D 109
	if (error = suser(u.u_cred, &u.u_acflag))
E 109
I 109
D 143
	if (error = suser(scp->sc_cred, &scp->sc_acflag))
E 143
I 143
D 160
	if (error = suser(ndp->ni_cred, &u.u_acflag))
E 143
E 109
		RETURN (error);
E 160
I 160
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
D 174
	ndp = &nd;
E 160
	ndp->ni_nameiop = CREATE | LOCKPARENT;
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 102
	ip = namei(ndp);
E 82
	if (ip != NULL) {
		u.u_error = EEXIST;
E 102
I 102
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
E 174
D 223
	if (vp != NULL) {
E 223
I 223
	if (vp != NULL)
E 223
		error = EEXIST;
E 102
D 223
		goto out;
E 223
I 223
	else {
		VATTR_NULL(&vattr);
D 250
		vattr.va_mode = (uap->mode & ALLPERMS) &~ p->p_fd->fd_cmask;
		vattr.va_rdev = uap->dev;
E 250
I 250
		vattr.va_mode = (SCARG(uap, mode) & ALLPERMS) &~ p->p_fd->fd_cmask;
		vattr.va_rdev = SCARG(uap, dev);
E 250
I 240
		whiteout = 0;
E 240

D 250
		switch (uap->mode & S_IFMT) {
E 250
I 250
		switch (SCARG(uap, mode) & S_IFMT) {
E 250
		case S_IFMT:	/* used by badsect to flag bad sectors */
			vattr.va_type = VBAD;
			break;
		case S_IFCHR:
			vattr.va_type = VCHR;
			break;
		case S_IFBLK:
			vattr.va_type = VBLK;
			break;
I 240
		case S_IFWHT:
			whiteout = 1;
			break;
E 240
		default:
			error = EINVAL;
			break;
		}
E 223
E 63
	}
D 102
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
E 102
I 102
D 140
	vattr_null(&vattr);
E 140
I 140
D 223
	VATTR_NULL(&vattr);
E 140
D 137
	switch (uap->fmode & IFMT) {
E 137
I 137
D 222
	switch (uap->fmode & S_IFMT) {
E 137
E 102

E 222
I 222
	switch (uap->mode & S_IFMT) {
E 222
I 72
D 137
	case IFMT:	/* used by badsect to flag bad sectors */
E 137
I 137
	case S_IFMT:	/* used by badsect to flag bad sectors */
E 137
I 102
		vattr.va_type = VBAD;
		break;
E 102
E 72
D 137
	case IFCHR:
E 137
I 137
	case S_IFCHR:
E 137
I 102
		vattr.va_type = VCHR;
		break;
E 102
D 137
	case IFBLK:
E 137
I 137
	case S_IFBLK:
E 137
D 102
		if (uap->dev) {
			/*
			 * Want to be able to use this to make badblock
			 * inodes, so don't truncate the dev number.
			 */
			ip->i_rdev = uap->dev;
			ip->i_flag |= IACC|IUPD|ICHG;
		}
E 102
I 102
		vattr.va_type = VBLK;
		break;
	default:
		error = EINVAL;
		goto out;
E 102
E 63
	}
D 102

E 102
I 102
D 109
	vattr.va_mode = (uap->fmode & 07777) &~ u.u_cmask;
E 109
I 109
D 143
	vattr.va_mode = (uap->fmode & 07777) &~ scp->sc_cmask;
E 143
I 143
D 157
	vattr.va_mode = (uap->fmode & 07777) &~ u.u_cmask;
E 157
I 157
D 222
	vattr.va_mode = (uap->fmode & 07777) &~ p->p_fd->fd_cmask;
E 222
I 222
	vattr.va_mode = (uap->mode & ALLPERMS) &~ p->p_fd->fd_cmask;
E 222
E 157
E 143
E 109
	vattr.va_rdev = uap->dev;
E 102
out:
E 223
D 102
	iput(ip);
E 102
I 102
D 144
	if (error)
		VOP_ABORTOP(ndp);
	else
E 144
I 144
D 240
	if (!error) {
E 240
I 240
D 243
	if (whiteout) {
		error = VOP_WHITEOUT(nd.ni_dvp, &nd.ni_cnd, CREATE);
		vput(nd.ni_dvp);
	} else if (!error) {
E 243
I 243
	if (!error) {
E 243
E 240
I 171
D 174
		LEASE_CHECK(ndp->ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 171
E 144
D 160
		error = VOP_MKNOD(ndp, &vattr, ndp->ni_cred);
E 160
I 160
D 162
		error = VOP_MKNOD(ndp, &vattr, p->p_ucred);
E 162
I 162
D 172
		error = VOP_MKNOD(ndp, &vattr, p->p_ucred, p);
E 172
I 172
		error = VOP_MKNOD(ndp->ni_dvp, &ndp->ni_vp, &ndp->ni_cnd, &vattr);
E 174
I 174
D 241
		LEASE_CHECK(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
		VOP_LEASE(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
D 243
		error = VOP_MKNOD(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, &vattr);
E 243
I 243
		if (whiteout) {
			error = VOP_WHITEOUT(nd.ni_dvp, &nd.ni_cnd, CREATE);
			if (error)
				VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
			vput(nd.ni_dvp);
		} else {
			error = VOP_MKNOD(nd.ni_dvp, &nd.ni_vp,
						&nd.ni_cnd, &vattr);
		}
E 243
E 174
E 172
E 162
E 160
I 144
	} else {
D 172
		VOP_ABORTOP(ndp);
E 172
I 172
D 174
		VOP_ABORTOP(ndp->ni_dvp, &ndp->ni_cnd);
E 172
D 146
		vput(ndp->ni_dvp);
E 146
I 146
		if (ndp->ni_dvp == vp)
			vrele(ndp->ni_dvp);
E 174
I 174
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
		if (nd.ni_dvp == vp)
			vrele(nd.ni_dvp);
E 174
		else
D 174
			vput(ndp->ni_dvp);
E 174
I 174
			vput(nd.ni_dvp);
E 174
E 146
		if (vp)
			vrele(vp);
	}
I 175
	CHECKREFS("mknod");
E 175
I 172
D 174
	CHECKCHECK("mknod");
E 174
E 172
E 144
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
}

/*
I 134
D 163
 * Mkfifo system call
E 163
I 163
D 222
 * Mkfifo system call.
E 222
I 222
D 250
 * Create named pipe.
E 250
I 250
 * Create a named pipe.
E 250
E 222
E 163
 */
I 198
D 250
struct mkfifo_args {
D 222
	char	*fname;
	int	fmode;
E 222
I 222
	char	*path;
	int	mode;
E 222
};
E 250
E 198
D 143
mkfifo(scp)
	register struct syscontext *scp;
{
	register struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
mkfifo(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		char	*fname;
		int	fmode;
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct mkfifo_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct mkfifo_args /* {
		syscallarg(char *) path;
		syscallarg(int) mode;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_ABORTOP;
	USES_VOP_MKNOD;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
	struct vattr vattr;
	int error;
I 160
	struct nameidata nd;
E 160

#ifndef FIFO
D 160
	RETURN (EOPNOTSUPP);
E 160
I 160
	return (EOPNOTSUPP);
E 160
#else
I 160
D 174
	ndp = &nd;
E 160
	ndp->ni_nameiop = CREATE | LOCKPARENT;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	if (ndp->ni_vp != NULL) {
D 172
		VOP_ABORTOP(ndp);
E 172
I 172
		VOP_ABORTOP(ndp->ni_dvp, &ndp->ni_cnd);
E 172
I 144
D 146
		vput(ndp->ni_dvp);
E 146
I 146
		if (ndp->ni_dvp == ndp->ni_vp)
			vrele(ndp->ni_dvp);
E 174
I 174
	if (nd.ni_vp != NULL) {
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
		if (nd.ni_dvp == nd.ni_vp)
			vrele(nd.ni_dvp);
E 174
		else
D 174
			vput(ndp->ni_dvp);
E 146
		vrele(ndp->ni_vp);
E 174
I 174
			vput(nd.ni_dvp);
		vrele(nd.ni_vp);
E 174
E 144
D 160
		RETURN (EEXIST);
E 160
I 160
		return (EEXIST);
E 160
D 156
	} else {
D 140
		vattr_null(&vattr);
E 140
I 140
		VATTR_NULL(&vattr);
E 140
		vattr.va_type = VFIFO;
D 143
		vattr.va_mode = (uap->fmode & 07777) &~ scp->sc_cmask;
E 143
I 143
		vattr.va_mode = (uap->fmode & 07777) &~ u.u_cmask;
E 156
E 143
	}
I 156
	VATTR_NULL(&vattr);
	vattr.va_type = VFIFO;
D 157
	vattr.va_mode = (uap->fmode & 07777) &~ u.u_cmask;
E 157
I 157
D 222
	vattr.va_mode = (uap->fmode & 07777) &~ p->p_fd->fd_cmask;
E 222
I 222
D 250
	vattr.va_mode = (uap->mode & ALLPERMS) &~ p->p_fd->fd_cmask;
E 250
I 250
	vattr.va_mode = (SCARG(uap, mode) & ALLPERMS) &~ p->p_fd->fd_cmask;
E 250
E 222
I 171
D 174
	LEASE_CHECK(ndp->ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 171
E 157
E 156
D 160
	RETURN (VOP_MKNOD(ndp, &vattr, ndp->ni_cred));
E 160
I 160
D 162
	return (VOP_MKNOD(ndp, &vattr, p->p_ucred));
E 162
I 162
D 172
	return (VOP_MKNOD(ndp, &vattr, p->p_ucred, p));
E 172
I 172
	return (VOP_MKNOD(ndp->ni_dvp, &ndp->ni_vp, &ndp->ni_cnd, &vattr));
E 174
I 174
D 241
	LEASE_CHECK(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
	return (VOP_MKNOD(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, &vattr));
E 174
E 172
E 162
E 160
#endif /* FIFO */
}

/*
E 134
D 163
 * link system call
E 163
I 163
D 222
 * Link system call.
E 222
I 222
 * Make a hard file link.
E 222
E 163
 */
I 198
D 250
struct link_args {
D 222
	char	*target;
	char	*linkname;
E 222
I 222
	char	*path;
	char	*link;
E 222
};
E 250
E 198
D 109
link()
E 109
I 109
D 143
link(scp)
	register struct syscontext *scp;
E 109
{
D 102
	register struct inode *ip, *xp;
E 102
	register struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
link(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		char	*target;
		char	*linkname;
D 82
	} *uap;
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct link_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct link_args /* {
		syscallarg(char *) path;
		syscallarg(char *) link;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_ABORTOP;
	USES_VOP_LINK;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
I 102
D 222
	register struct vnode *vp, *xp;
	int error;
E 222
I 222
	register struct vnode *vp;
E 222
I 160
	struct nameidata nd;
I 222
	int error;
E 222
E 160
E 102
E 82

I 175
	CHECKPOINTREF;
E 175
I 172
D 174
	CHECKPOINT;
E 172
I 160
	ndp = &nd;
E 160
D 82
	uap = (struct a *)u.u_ap;
D 47
	ip = namei(uchar, 0, 1);    /* well, this routine is doomed anyhow */
E 47
I 47
	ip = namei(uchar, LOOKUP, 1); /* well, this routine is doomed anyhow */
E 82
I 82
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->target;
D 102
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
E 102
I 102
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->target, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
E 174
D 223
	if (vp->v_type == VDIR &&
D 109
	    (error = suser(u.u_cred, &u.u_acflag)))
E 109
I 109
D 143
	    (error = suser(scp->sc_cred, &scp->sc_acflag)))
E 143
I 143
D 160
	    (error = suser(ndp->ni_cred, &u.u_acflag)))
E 160
I 160
	    (error = suser(p->p_ucred, &p->p_acflag)))
E 160
E 143
E 109
D 222
		goto out1;
E 222
I 222
		goto out;
E 222
D 174
	ndp->ni_nameiop = CREATE | LOCKPARENT;
E 102
	ndp->ni_dirp = (caddr_t)uap->linkname;
D 102
	xp = namei(ndp);
E 102
I 102
D 160
	if (error = namei(ndp))
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
	nd.ni_cnd.cn_nameiop = CREATE;
	nd.ni_cnd.cn_flags = LOCKPARENT;
D 222
	nd.ni_dirp = (caddr_t)uap->linkname;
E 222
I 222
	nd.ni_dirp = uap->link;
E 222
	if (error = namei(&nd))
E 174
E 160
D 222
		goto out1;
D 174
	xp = ndp->ni_vp;
E 174
I 174
	xp = nd.ni_vp;
E 174
E 102
E 82
E 47
	if (xp != NULL) {
D 102
		u.u_error = EEXIST;
		iput(xp);
E 102
I 102
		error = EEXIST;
E 222
E 102
		goto out;
D 222
	}
D 102
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
E 102
I 102
D 174
	xp = ndp->ni_dvp;
E 174
I 174
	xp = nd.ni_dvp;
E 174
D 189
	if (vp->v_mount != xp->v_mount)
		error = EXDEV;
E 189
E 102
E 82
E 55
E 36
out:
E 222
I 222
	if (nd.ni_vp != NULL)
		error = EEXIST;
E 222
D 102
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
D 144
	if (error)
		VOP_ABORTOP(ndp);
	else
E 144
I 144
	if (!error) {
I 171
D 222
		LEASE_CHECK(xp, p, p->p_ucred, LEASE_WRITE);
E 222
I 222
		LEASE_CHECK(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 222
		LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 171
E 144
D 162
		error = VOP_LINK(vp, ndp);
E 162
I 162
D 172
		error = VOP_LINK(vp, ndp, p);
E 172
I 172
D 174
		error = VOP_LINK(vp, ndp->ni_dvp, &ndp->ni_cnd);
E 174
I 174
D 177
		error = VOP_LINK(vp, nd.ni_dvp, &nd.ni_cnd);
E 177
I 177
		error = VOP_LINK(nd.ni_dvp, vp, &nd.ni_cnd);
E 177
E 174
E 172
E 162
I 144
	} else {
D 172
		VOP_ABORTOP(ndp);
E 172
I 172
D 174
		VOP_ABORTOP(ndp->ni_dvp, &ndp->ni_cnd);
E 172
D 146
		vput(ndp->ni_dvp);
E 146
I 146
		if (ndp->ni_dvp == ndp->ni_vp)
			vrele(ndp->ni_dvp);
E 174
I 174
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
		if (nd.ni_dvp == nd.ni_vp)
			vrele(nd.ni_dvp);
E 174
		else
D 174
			vput(ndp->ni_dvp);
E 146
		if (ndp->ni_vp)
			vrele(ndp->ni_vp);
E 174
I 174
			vput(nd.ni_dvp);
		if (nd.ni_vp)
			vrele(nd.ni_vp);
E 223
I 223
	if (vp->v_type != VDIR ||
	    (error = suser(p->p_ucred, &p->p_acflag)) == 0) {
		nd.ni_cnd.cn_nameiop = CREATE;
		nd.ni_cnd.cn_flags = LOCKPARENT;
D 250
		nd.ni_dirp = uap->link;
E 250
I 250
		nd.ni_dirp = SCARG(uap, link);
E 250
		if ((error = namei(&nd)) == 0) {
			if (nd.ni_vp != NULL)
				error = EEXIST;
			if (!error) {
D 241
				LEASE_CHECK(nd.ni_dvp,
				    p, p->p_ucred, LEASE_WRITE);
				LEASE_CHECK(vp,
				    p, p->p_ucred, LEASE_WRITE);
E 241
I 241
				VOP_LEASE(nd.ni_dvp, p, p->p_ucred,
				    LEASE_WRITE);
				VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
D 253
				error = VOP_LINK(nd.ni_dvp, vp, &nd.ni_cnd);
E 253
I 253
				error = VOP_LINK(vp, nd.ni_dvp, &nd.ni_cnd);
E 253
			} else {
				VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
				if (nd.ni_dvp == nd.ni_vp)
					vrele(nd.ni_dvp);
				else
					vput(nd.ni_dvp);
				if (nd.ni_vp)
					vrele(nd.ni_vp);
			}
		}
E 223
E 174
	}
E 144
D 222
out1:
	vrele(vp);
E 222
I 222
D 223
out:	vrele(vp);
E 223
I 223
	vrele(vp);
E 223
E 222
I 175
	CHECKREFS("link");
E 175
I 172
D 174
	CHECKCHECK("link");
E 174
E 172
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
E 31
}

/*
D 163
 * symlink -- make a symbolic link
E 163
I 163
 * Make a symbolic link.
E 163
 */
I 198
D 250
struct symlink_args {
D 222
	char	*target;
	char	*linkname;
E 222
I 222
	char	*path;
	char	*link;
E 222
};
E 250
E 198
D 109
symlink()
E 109
I 109
D 143
symlink(scp)
	register struct syscontext *scp;
E 109
{
D 102
	register struct a {
E 102
I 102
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
symlink(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
E 102
		char	*target;
		char	*linkname;
D 82
	} *uap;
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
E 82
D 102
	register struct inode *ip;
	register char *tp;
	register c, nc;
E 102
I 82
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct symlink_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct symlink_args /* {
		syscallarg(char *) path;
		syscallarg(char *) link;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_ABORTOP;
	USES_VOP_SYMLINK;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
I 102
D 144
	register struct vnode *vp;
E 144
	struct vattr vattr;
D 222
	char *target;
E 222
I 222
	char *path;
E 222
	int error;
I 160
	struct nameidata nd;
E 160
E 102
E 82

I 175
	CHECKPOINTREF;
E 175
I 172
D 174
	CHECKPOINT;
E 172
I 160
	ndp = &nd;
E 160
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
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->linkname;
E 174
D 102
	ip = namei(ndp);
E 82
E 47
	if (ip) {
		iput(ip);
		u.u_error = EEXIST;
		return;
E 102
I 102
D 222
	MALLOC(target, char *, MAXPATHLEN, M_NAMEI, M_WAITOK);
	if (error = copyinstr(uap->target, target, MAXPATHLEN, (u_int *)0))
E 222
I 222
	MALLOC(path, char *, MAXPATHLEN, M_NAMEI, M_WAITOK);
D 250
	if (error = copyinstr(uap->path, path, MAXPATHLEN, NULL))
E 250
I 250
	if (error = copyinstr(SCARG(uap, path), path, MAXPATHLEN, NULL))
E 250
E 222
D 144
		goto out1;
E 144
I 144
		goto out;
E 144
D 174
	ndp->ni_nameiop = CREATE | LOCKPARENT;
D 160
	if (error = namei(ndp))
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, uap->linkname, p);
E 222
I 222
D 250
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, uap->link, p);
E 250
I 250
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, SCARG(uap, link), p);
E 250
E 222
	if (error = namei(&nd))
E 174
E 160
D 144
		goto out1;
	vp = ndp->ni_vp;
	if (vp) {
E 144
I 144
		goto out;
D 174
	if (ndp->ni_vp) {
D 172
		VOP_ABORTOP(ndp);
E 172
I 172
		VOP_ABORTOP(ndp->ni_dvp, &ndp->ni_cnd);
E 172
D 146
		vput(ndp->ni_dvp);
E 146
I 146
		if (ndp->ni_dvp == ndp->ni_vp)
			vrele(ndp->ni_dvp);
E 174
I 174
	if (nd.ni_vp) {
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
		if (nd.ni_dvp == nd.ni_vp)
			vrele(nd.ni_dvp);
E 174
		else
D 174
			vput(ndp->ni_dvp);
E 146
		vrele(ndp->ni_vp);
E 174
I 174
			vput(nd.ni_dvp);
		vrele(nd.ni_vp);
E 174
E 144
		error = EEXIST;
		goto out;
E 102
	}
D 102
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
D 144
	vp = ndp->ni_dvp;
E 144
D 140
	vattr_null(&vattr);
E 140
I 140
	VATTR_NULL(&vattr);
E 140
D 109
	vattr.va_mode = 0777 &~ u.u_cmask;
E 109
I 109
D 143
	vattr.va_mode = 0777 &~ scp->sc_cmask;
E 143
I 143
D 157
	vattr.va_mode = 0777 &~ u.u_cmask;
E 157
I 157
D 222
	vattr.va_mode = 0777 &~ p->p_fd->fd_cmask;
E 222
I 222
	vattr.va_mode = ACCESSPERMS &~ p->p_fd->fd_cmask;
E 222
I 171
D 174
	LEASE_CHECK(ndp->ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 171
E 157
I 144
D 162
	error = VOP_SYMLINK(ndp, &vattr, target);
E 162
I 162
D 172
	error = VOP_SYMLINK(ndp, &vattr, target, p);
E 172
I 172
	error = VOP_SYMLINK(ndp->ni_dvp, &ndp->ni_vp, &ndp->ni_cnd, &vattr, target);
E 174
I 174
D 241
	LEASE_CHECK(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
D 222
	error = VOP_SYMLINK(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, &vattr, target);
E 222
I 222
	error = VOP_SYMLINK(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, &vattr, path);
E 222
E 174
E 172
E 162
E 144
E 143
E 109
out:
D 144
	if (error)
		VOP_ABORTOP(ndp);
	else
		error = VOP_SYMLINK(ndp, &vattr, target);
out1:
E 144
D 222
	FREE(target, M_NAMEI);
E 222
I 222
	FREE(path, M_NAMEI);
E 222
I 175
	CHECKREFS("symlink");
E 175
I 172
D 174
	CHECKCHECK("symlink");
E 174
E 172
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
}

/*
I 238
 * Delete a whiteout from the filesystem.
 */
D 245
struct unwhiteout_args {
E 245
I 245
D 250
struct undelete_args {
E 245
	char	*path;
};
E 250
/* ARGSUSED */
I 250
int
E 250
D 245
unwhiteout(p, uap, retval)
E 245
I 245
undelete(p, uap, retval)
E 245
	struct proc *p;
D 245
	struct unwhiteout_args *uap;
E 245
I 245
D 250
	struct undelete_args *uap;
E 245
	int *retval;
E 250
I 250
	register struct undelete_args /* {
		syscallarg(char *) path;
	} */ *uap;
	register_t *retval;
E 250
{
	int error;
	struct nameidata nd;

D 240
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, uap->path, p);
	if (error = namei(&nd))
E 240
I 240
D 250
	NDINIT(&nd, DELETE, LOCKPARENT|DOWHITEOUT, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, DELETE, LOCKPARENT|DOWHITEOUT, UIO_USERSPACE,
	    SCARG(uap, path), p);
E 250
	error = namei(&nd);
	if (error)
E 240
		return (error);
D 240
	if (nd.ni_vp || !(nd.ni_cnd.cn_flags & WHITEOUT)) {
E 240
I 240

	if (nd.ni_vp != NULLVP || !(nd.ni_cnd.cn_flags & ISWHITEOUT)) {
E 240
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
		if (nd.ni_dvp == nd.ni_vp)
			vrele(nd.ni_dvp);
		else
			vput(nd.ni_dvp);
		if (nd.ni_vp)
			vrele(nd.ni_vp);
		return (EEXIST);
	}
I 240

E 240
D 241
	LEASE_CHECK(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
D 243
	error = VOP_WHITEOUT(nd.ni_dvp, &nd.ni_cnd, DELETE);
I 240
	if (error != 0)
E 243
I 243
	if (error = VOP_WHITEOUT(nd.ni_dvp, &nd.ni_cnd, DELETE))
E 243
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 240
	vput(nd.ni_dvp);
	return (error);
}

/*
E 238
D 163
 * Unlink system call.
 * Hard to avoid races here, especially
 * in unlinking directories.
E 163
I 163
 * Delete a name from the filesystem.
E 163
 */
I 198
D 250
struct unlink_args {
D 222
	char	*name;
E 222
I 222
	char	*path;
E 222
};
E 250
E 198
D 109
unlink()
E 109
I 109
D 143
unlink(scp)
	register struct syscontext *scp;
E 109
{
D 47
	register struct inode *ip, *pp;
E 47
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
unlink(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	struct args {
E 143
D 174
		char	*fname;
E 174
I 174
		char	*name;
E 174
D 82
	};
E 82
I 82
D 109
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
D 102
	register struct inode *ip, *dp;
E 102
I 82
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	struct unlink_args *uap;
E 198
	int *retval;
E 250
I 250
	struct unlink_args /* {
		syscallarg(char *) path;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_ABORTOP;
	USES_VOP_REMOVE;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
I 102
	register struct vnode *vp;
	int error;
I 160
	struct nameidata nd;
E 160
E 102
E 82
E 47
E 31
E 28

I 175
	CHECKPOINTREF;
E 175
I 172
D 174
	CHECKPOINT;
E 172
I 160
	ndp = &nd;
E 160
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
E 102
I 102
	ndp->ni_nameiop = DELETE | LOCKPARENT | LOCKLEAF;
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 102
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
E 102
I 102
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 213
	NDINIT(&nd, DELETE, LOCKPARENT | LOCKLEAF, UIO_USERSPACE, uap->name, p);
E 213
I 213
D 222
	NDINIT(&nd, DELETE, LOCKPARENT, UIO_USERSPACE, uap->name, p);
E 222
I 222
D 250
	NDINIT(&nd, DELETE, LOCKPARENT, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, DELETE, LOCKPARENT, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 222
E 213
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
I 213
D 241
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
E 213
E 174
D 223
	if (vp->v_type == VDIR &&
D 109
	    (error = suser(u.u_cred, &u.u_acflag)))
E 109
I 109
D 143
	    (error = suser(scp->sc_cred, &scp->sc_acflag)))
E 143
I 143
D 160
	    (error = suser(ndp->ni_cred, &u.u_acflag)))
E 160
I 160
	    (error = suser(p->p_ucred, &p->p_acflag)))
E 160
E 143
E 109
E 102
E 101
E 47
		goto out;
	/*
D 163
	 * Don't unlink a mounted file.
E 163
I 163
	 * The root of a mounted filesystem cannot be deleted.
E 163
	 */
D 47
	if (ip->i_dev != pp->i_dev) {
E 47
I 47
D 102
	if (ip->i_dev != dp->i_dev) {
E 47
		u.u_error = EBUSY;
E 102
I 102
D 222
	if (vp->v_flag & VROOT) {
E 222
I 222
	if (vp->v_flag & VROOT)
E 222
		error = EBUSY;
E 102
D 222
		goto out;
	}
I 158
D 164
#ifdef NVM
E 164
E 158
D 102
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
E 102
I 102
D 155
	if (vp->v_flag & VTEXT)
		xrele(vp);	/* try once to free text */
E 155
I 155
	(void) vnode_pager_uncache(vp);
I 158
D 164
#else
	if (vp->v_flag & VTEXT)
		xrele(vp);	/* try once to free text */
#endif
E 164
E 158
E 155
E 102
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
D 102
	if (dp == ip)
E 47
		irele(ip);
E 102
I 102
D 144
	if (error)
		VOP_ABORTOP(ndp);
E 102
	else
E 144
I 144
	if (!error) {
E 222
I 222
	else
		(void)vnode_pager_uncache(vp);
E 223

D 223
out:	if (!error) {
E 223
I 223
	if (vp->v_type != VDIR ||
	    (error = suser(p->p_ucred, &p->p_acflag)) == 0) {
		/*
		 * The root of a mounted filesystem cannot be deleted.
		 */
		if (vp->v_flag & VROOT)
			error = EBUSY;
		else
			(void)vnode_pager_uncache(vp);
	}

	if (!error) {
E 223
E 222
I 171
D 174
		LEASE_CHECK(ndp->ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 174
I 174
D 241
		LEASE_CHECK(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
		VOP_LEASE(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
E 174
D 213
		LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 213
E 171
E 144
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
D 162
		error = VOP_REMOVE(ndp);
E 162
I 162
D 172
		error = VOP_REMOVE(ndp, p);
E 172
I 172
D 174
		error = VOP_REMOVE(ndp->ni_dvp, ndp->ni_vp, &ndp->ni_cnd);
E 174
I 174
		error = VOP_REMOVE(nd.ni_dvp, nd.ni_vp, &nd.ni_cnd);
E 174
E 172
E 162
I 144
	} else {
D 172
		VOP_ABORTOP(ndp);
E 172
I 172
D 174
		VOP_ABORTOP(ndp->ni_dvp, &ndp->ni_cnd);
E 172
D 146
		vput(ndp->ni_dvp);
E 146
I 146
		if (ndp->ni_dvp == vp)
			vrele(ndp->ni_dvp);
E 174
I 174
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
		if (nd.ni_dvp == vp)
			vrele(nd.ni_dvp);
E 174
		else
D 174
			vput(ndp->ni_dvp);
E 174
I 174
			vput(nd.ni_dvp);
E 174
E 146
D 240
		vput(vp);
E 240
I 240
		if (vp != NULLVP)
			vput(vp);
E 240
	}
I 175
	CHECKREFS("unlink");
E 175
I 172
D 174
	CHECKCHECK("unlink");
E 174
E 172
E 144
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
E 47
}

I 222
/*
 * Reposition read/write file offset.
 */
E 222
I 197
D 198
struct args_lseek {
E 198
I 198
D 218
struct __lseek_args {
E 218
I 218
D 250
struct lseek_args {
E 218
E 198
D 222
	int	fdes;
E 222
I 222
	int	fd;
E 222
	int	pad;
D 222
	off_t	off;
	int	sbase;
E 222
I 222
	off_t	offset;
	int	whence;
E 222
};
E 250
I 250
int
E 250
D 222

E 197
I 178
D 192
#ifdef COMPAT_43
E 192
I 192
D 215
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 215
E 192
E 178
/*
D 163
 * Seek system call
E 163
I 163
 * Seek system call.
E 163
 */
E 222
I 198
D 215
struct lseek_args {
	int	fdes;
	long	off;
	int	sbase;
};
E 198
D 41
seek()
E 41
I 41
D 109
lseek()
E 109
I 109
D 143
lseek(scp)
	register struct syscontext *scp;
E 109
E 41
{
	register struct file *fp;
	register struct a {
E 143
I 143
lseek(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
D 37
		int	fdes;
E 37
I 37
D 102
		int	fd;
E 102
I 102
		int	fdes;
I 178
		long	off;
		int	sbase;
	} *uap;
	long *retval;
E 198
I 198
	register struct lseek_args *uap;
	int *retval;
E 198
{
D 197
	struct nargs {
		int	fdes;
E 178
E 102
E 37
		off_t	off;
		int	sbase;
I 178
	} nuap;
	quad_t qret;
E 197
I 197
D 198
	struct args_lseek nuap;
E 198
I 198
	struct __lseek_args nuap;
E 198
	off_t qret;
E 197
	int error;

	nuap.fdes = uap->fdes;
	nuap.off = uap->off;
	nuap.sbase = uap->sbase;
D 188
	error = qseek(p, &nuap, &qret);
E 188
I 188
	error = __lseek(p, &nuap, &qret);
E 188
D 198
	*retval = qret;
E 198
I 198
	*(long *)retval = qret;
E 198
	return (error);
}
D 192
#endif /* COMPAT_43 */
E 192
I 192
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 192

/*
 * Seek system call.
 */
E 215
D 188
qseek(p, uap, retval)
E 188
I 188
D 217
__lseek(p, uap, retval)
E 217
I 217
lseek(p, uap, retval)
E 217
E 188
	struct proc *p;
D 197
	register struct args {
		int	fdes;
		off_t	off;
		int	sbase;
E 178
D 82
	} *uap;
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 197
I 197
D 198
	register struct args_lseek *uap;
E 197
	off_t *retval;
E 198
I 198
D 218
	register struct __lseek_args *uap;
E 218
I 218
D 250
	register struct lseek_args *uap;
E 218
	int *retval;
E 250
I 250
	register struct lseek_args /* {
		syscallarg(int) fd;
		syscallarg(int) pad;
		syscallarg(off_t) offset;
		syscallarg(int) whence;
	} */ *uap;
	register_t *retval;
E 250
E 198
{
I 187
D 195
	USES_VOP_GETATTR;
E 195
E 187
D 160
	struct ucred *cred = u.u_nd.ni_cred;
E 160
I 160
	struct ucred *cred = p->p_ucred;
E 160
I 157
	register struct filedesc *fdp = p->p_fd;
E 157
	register struct file *fp;
E 143
E 109
I 102
	struct vattr vattr;
	int error;
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
I 77
	}
E 102
I 102
D 157
	if ((unsigned)uap->fdes >= NOFILE ||
D 109
	    (fp = u.u_ofile[uap->fdes]) == NULL)
E 109
I 109
D 143
	    (fp = scp->sc_ofile[uap->fdes]) == NULL)
E 143
I 143
	    (fp = u.u_ofile[uap->fdes]) == NULL)
E 157
I 157
D 160
	if ((unsigned)uap->fdes >= fdp->fd_maxfiles ||
E 160
I 160
D 222
	if ((unsigned)uap->fdes >= fdp->fd_nfiles ||
E 160
D 161
	    (fp = OFILE(fdp, uap->fdes)) == NULL)
E 161
I 161
	    (fp = fdp->fd_ofiles[uap->fdes]) == NULL)
E 222
I 222
D 250
	if ((u_int)uap->fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[uap->fd]) == NULL)
E 250
I 250
	if ((u_int)SCARG(uap, fd) >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[SCARG(uap, fd)]) == NULL)
E 250
E 222
E 161
E 157
E 143
E 109
D 160
		RETURN (EBADF);
E 160
I 160
		return (EBADF);
E 160
	if (fp->f_type != DTYPE_VNODE)
D 160
		RETURN (ESPIPE);
E 160
I 160
		return (ESPIPE);
E 160
E 102
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
D 222
	switch (uap->sbase) {

E 222
I 222
D 250
	switch (uap->whence) {
E 250
I 250
	switch (SCARG(uap, whence)) {
E 250
E 222
	case L_INCR:
D 222
		fp->f_offset += uap->off;
E 222
I 222
D 250
		fp->f_offset += uap->offset;
E 250
I 250
		fp->f_offset += SCARG(uap, offset);
E 250
E 222
		break;
D 222

E 222
	case L_XTND:
D 102
		fp->f_offset = uap->off + ((struct inode *)fp->f_data)->i_size;
E 102
I 102
D 222
		if (error = VOP_GETATTR((struct vnode *)fp->f_data,
D 109
		    &vattr, u.u_cred))
E 109
I 109
D 143
		    &vattr, scp->sc_cred))
E 143
I 143
D 162
		    &vattr, cred))
E 162
I 162
		    &vattr, cred, p))
E 222
I 222
		if (error =
		    VOP_GETATTR((struct vnode *)fp->f_data, &vattr, cred, p))
E 222
E 162
E 143
E 109
D 160
			RETURN (error);
E 160
I 160
			return (error);
E 160
D 222
		fp->f_offset = uap->off + vattr.va_size;
E 222
I 222
D 250
		fp->f_offset = uap->offset + vattr.va_size;
E 250
I 250
		fp->f_offset = SCARG(uap, offset) + vattr.va_size;
E 250
E 222
E 102
		break;
D 222

E 222
	case L_SET:
D 222
		fp->f_offset = uap->off;
E 222
I 222
D 250
		fp->f_offset = uap->offset;
E 250
I 250
		fp->f_offset = SCARG(uap, offset);
E 250
E 222
		break;
D 222

E 222
	default:
D 102
		u.u_error = EINVAL;
		return;
E 102
I 102
D 160
		RETURN (EINVAL);
E 160
I 160
		return (EINVAL);
E 160
E 102
	}
D 109
	u.u_r.r_off = fp->f_offset;
E 109
I 109
D 143
	scp->sc_offset = fp->f_offset;
E 143
I 143
D 198
	*retval = fp->f_offset;
E 198
I 198
	*(off_t *)retval = fp->f_offset;
E 198
E 143
E 109
I 102
D 160
	RETURN (0);
E 160
I 160
	return (0);
I 215
}

I 217
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 217
/*
D 222
 * Old lseek system call.
E 222
I 222
 * Reposition read/write file offset.
E 222
D 217
 *
 * XXX should be COMPAT_43, but too much breaks.
E 217
 */
D 218
struct lseek_args {
E 218
I 218
D 250
struct olseek_args {
E 218
D 222
	int	fdes;
	long	off;
	int	sbase;
E 222
I 222
	int	fd;
	long	offset;
	int	whence;
E 222
};
D 217
lseek(p, uap, retval)
E 217
I 217
olseek(p, uap, retval)
E 250
I 250
int
compat_43_lseek(p, uap, retval)
E 250
E 217
	struct proc *p;
D 218
	register struct lseek_args *uap;
E 218
I 218
D 250
	register struct olseek_args *uap;
E 218
	int *retval;
E 250
I 250
	register struct compat_43_lseek_args /* {
		syscallarg(int) fd;
		syscallarg(long) offset;
		syscallarg(int) whence;
	} */ *uap;
	register_t *retval;
E 250
{
D 218
	struct __lseek_args nuap;
E 218
I 218
D 250
	struct lseek_args nuap;
E 250
I 250
	struct lseek_args /* {
		syscallarg(int) fd;
		syscallarg(int) pad;
		syscallarg(off_t) offset;
		syscallarg(int) whence;
	} */ nuap;
E 250
E 218
	off_t qret;
	int error;

D 222
	nuap.fdes = uap->fdes;
	nuap.off = uap->off;
	nuap.sbase = uap->sbase;
E 222
I 222
D 250
	nuap.fd = uap->fd;
	nuap.offset = uap->offset;
	nuap.whence = uap->whence;
E 250
I 250
	SCARG(&nuap, fd) = SCARG(uap, fd);
	SCARG(&nuap, offset) = SCARG(uap, offset);
	SCARG(&nuap, whence) = SCARG(uap, whence);
E 250
E 222
D 218
	error = __lseek(p, &nuap, &qret);
E 218
I 218
	error = lseek(p, &nuap, &qret);
E 218
	*(long *)retval = qret;
	return (error);
E 215
E 160
E 102
E 68
}
I 217
#endif /* COMPAT_43 */
E 217

/*
D 163
 * Access system call
E 163
I 163
 * Check access permissions.
E 163
 */
I 198
D 220
struct saccess_args {
E 220
I 220
D 250
struct access_args {
E 220
D 222
	char	*fname;
	int	fmode;
E 222
I 222
	char	*path;
	int	flags;
E 222
};
E 250
I 250
int
E 250
E 198
D 109
saccess()
E 109
I 109
D 143
saccess(scp)
	register struct syscontext *scp;
E 109
{
D 102
	register svuid, svgid;
	register struct inode *ip;
E 102
	register struct a {
E 143
I 143
D 220
/* ARGSUSED */
saccess(p, uap, retval)
E 220
I 220
access(p, uap, retval)
E 220
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		char	*fname;
		int	fmode;
D 82
	} *uap;
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 220
	register struct saccess_args *uap;
E 220
I 220
D 250
	register struct access_args *uap;
E 220
E 198
	int *retval;
E 250
I 250
	register struct access_args /* {
		syscallarg(char *) path;
		syscallarg(int) flags;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_ACCESS;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
	register struct ucred *cred = ndp->ni_cred;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
	register struct ucred *cred = p->p_ucred;
E 160
E 143
E 109
I 102
	register struct vnode *vp;
D 222
	int error, mode, svuid, svgid;
E 222
I 222
D 223
	int error, flags, saved_uid, saved_gid;
E 223
I 223
	int error, flags, t_gid, t_uid;
E 223
E 222
I 160
	struct nameidata nd;
E 160
E 102
E 82

I 160
D 174
	ndp = &nd;
E 174
E 160
D 82
	uap = (struct a *)u.u_ap;
E 82
D 109
	svuid = u.u_uid;
	svgid = u.u_gid;
	u.u_uid = u.u_ruid;
	u.u_gid = u.u_rgid;
E 109
I 109
D 143
	svuid = scp->sc_uid;
	svgid = scp->sc_gid;
	scp->sc_uid = scp->sc_ruid;
	scp->sc_gid = scp->sc_rgid;
E 143
I 143
D 222
	svuid = cred->cr_uid;
	svgid = cred->cr_groups[0];
E 222
I 222
D 223
	saved_uid = cred->cr_uid;
	saved_gid = cred->cr_groups[0];
E 223
I 223
	t_uid = cred->cr_uid;
	t_gid = cred->cr_groups[0];
E 223
E 222
D 160
	cred->cr_uid = p->p_ruid;
	cred->cr_groups[0] = p->p_rgid;
E 160
I 160
	cred->cr_uid = p->p_cred->p_ruid;
	cred->cr_groups[0] = p->p_cred->p_rgid;
E 160
E 143
E 109
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
E 102
I 102
D 174
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 102
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
D 160
	if (error = namei(ndp))
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
E 174
E 160
		goto out1;
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
E 174
D 222
	/*
	 * fmode == 0 means only check for exist
	 */
	if (uap->fmode) {
		mode = 0;
		if (uap->fmode & R_OK)
			mode |= VREAD;
		if (uap->fmode & W_OK)
			mode |= VWRITE;
		if (uap->fmode & X_OK)
			mode |= VEXEC;
D 108
		error = vn_access(vp, mode, u.u_cred);
E 108
I 108
D 120
		if ((error = vn_writechk(vp)) == 0)
E 120
I 120
		if ((mode & VWRITE) == 0 || (error = vn_writechk(vp)) == 0)
E 120
D 160
			error = VOP_ACCESS(vp, mode, ndp->ni_cred);
E 160
I 160
D 162
			error = VOP_ACCESS(vp, mode, cred);
E 162
I 162
			error = VOP_ACCESS(vp, mode, cred, p);
E 222
I 222

	/* Flags == 0 means only check for existence. */
D 250
	if (uap->flags) {
E 250
I 250
	if (SCARG(uap, flags)) {
E 250
		flags = 0;
D 250
		if (uap->flags & R_OK)
E 250
I 250
		if (SCARG(uap, flags) & R_OK)
E 250
			flags |= VREAD;
D 250
		if (uap->flags & W_OK)
E 250
I 250
		if (SCARG(uap, flags) & W_OK)
E 250
			flags |= VWRITE;
D 250
		if (uap->flags & X_OK)
E 250
I 250
		if (SCARG(uap, flags) & X_OK)
E 250
			flags |= VEXEC;
		if ((flags & VWRITE) == 0 || (error = vn_writechk(vp)) == 0)
			error = VOP_ACCESS(vp, flags, cred, p);
E 222
E 162
E 160
E 108
E 102
	}
I 102
	vput(vp);
out1:
E 102
D 109
	u.u_uid = svuid;
	u.u_gid = svgid;
E 109
I 109
D 143
	scp->sc_uid = svuid;
	scp->sc_gid = svgid;
E 143
I 143
D 222
	cred->cr_uid = svuid;
	cred->cr_groups[0] = svgid;
E 222
I 222
D 223
	cred->cr_uid = saved_uid;
	cred->cr_groups[0] = saved_gid;
E 223
I 223
	cred->cr_uid = t_uid;
	cred->cr_groups[0] = t_gid;
E 223
E 222
E 143
E 109
I 102
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
}

I 178
D 192
#ifdef COMPAT_43
E 192
I 192
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 192
E 178
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
D 163
 * Stat system call.  This version follows links.
E 163
I 163
D 222
 * Stat system call.
 * This version follows links.
E 222
I 222
 * Get file status; this version follows links.
E 222
E 163
E 28
E 27
E 23
E 17
 */
I 198
D 250
struct ostat_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
	struct ostat *ub;
};
E 250
E 198
D 109
stat()
E 109
I 109
D 143
stat(scp)
	struct syscontext *scp;
E 143
I 143
/* ARGSUSED */
D 188
stat(p, uap, retval)
E 188
I 188
D 250
ostat(p, uap, retval)
E 250
I 250
int
compat_43_stat(p, uap, retval)
E 250
E 188
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
		char	*fname;
I 178
		struct ostat *ub;
	} *uap;
E 198
I 198
D 250
	register struct ostat_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct compat_43_stat_args /* {
		syscallarg(char *) path;
		syscallarg(struct ostat *) ub;
	} */ *uap;
	register_t *retval;
E 250
{
	struct stat sb;
	struct ostat osb;
	int error;
	struct nameidata nd;

D 222
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
		return (error);
	error = vn_stat(nd.ni_vp, &sb, p);
	vput(nd.ni_vp);
	if (error)
		return (error);
	cvtstat(&sb, &osb);
D 250
	error = copyout((caddr_t)&osb, (caddr_t)uap->ub, sizeof (osb));
E 250
I 250
	error = copyout((caddr_t)&osb, (caddr_t)SCARG(uap, ub), sizeof (osb));
E 250
	return (error);
}

/*
D 222
 * Lstat system call.
 * This version does not follow links.
E 222
I 222
 * Get file status; this version does not follow links.
E 222
 */
I 198
D 250
struct olstat_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
	struct ostat *ub;
};
E 250
E 198
/* ARGSUSED */
D 188
lstat(p, uap, retval)
E 188
I 188
D 250
olstat(p, uap, retval)
E 250
I 250
int
compat_43_lstat(p, uap, retval)
E 250
E 188
	struct proc *p;
D 198
	register struct args {
		char	*fname;
		struct ostat *ub;
	} *uap;
E 198
I 198
D 250
	register struct olstat_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct compat_43_lstat_args /* {
		syscallarg(char *) path;
		syscallarg(struct ostat *) ub;
	} */ *uap;
	register_t *retval;
E 250
{
D 244
	struct stat sb;
E 244
I 244
	struct vnode *vp, *dvp;
	struct stat sb, sb1;
E 244
	struct ostat osb;
	int error;
	struct nameidata nd;

D 222
	NDINIT(&nd, LOOKUP, NOFOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 244
	NDINIT(&nd, LOOKUP, NOFOLLOW | LOCKLEAF, UIO_USERSPACE, uap->path, p);
E 244
I 244
	NDINIT(&nd, LOOKUP, NOFOLLOW | LOCKLEAF | LOCKPARENT, UIO_USERSPACE,
D 250
	    uap->path, p);
E 250
I 250
	    SCARG(uap, path), p);
E 250
E 244
E 222
	if (error = namei(&nd))
		return (error);
D 244
	error = vn_stat(nd.ni_vp, &sb, p);
	vput(nd.ni_vp);
	if (error)
		return (error);
E 244
I 244
	/*
	 * For symbolic links, always return the attributes of its
	 * containing directory, except for mode, size, and links.
	 */
	vp = nd.ni_vp;
	dvp = nd.ni_dvp;
	if (vp->v_type != VLNK) {
		if (dvp == vp)
			vrele(dvp);
		else
			vput(dvp);
		error = vn_stat(vp, &sb, p);
		vput(vp);
		if (error)
			return (error);
	} else {
		error = vn_stat(dvp, &sb, p);
		vput(dvp);
		if (error) {
			vput(vp);
			return (error);
		}
		error = vn_stat(vp, &sb1, p);
		vput(vp);
		if (error)
			return (error);
		sb.st_mode &= ~S_IFDIR;
		sb.st_mode |= S_IFLNK;
		sb.st_nlink = sb1.st_nlink;
		sb.st_size = sb1.st_size;
		sb.st_blocks = sb1.st_blocks;
	}
E 244
	cvtstat(&sb, &osb);
D 250
	error = copyout((caddr_t)&osb, (caddr_t)uap->ub, sizeof (osb));
E 250
I 250
	error = copyout((caddr_t)&osb, (caddr_t)SCARG(uap, ub), sizeof (osb));
E 250
	return (error);
}

/*
D 222
 * convert from an old to a new stat structure.
E 222
I 222
 * Convert from an old to a new stat structure.
E 222
 */
I 250
void
E 250
cvtstat(st, ost)
	struct stat *st;
	struct ostat *ost;
{

	ost->st_dev = st->st_dev;
	ost->st_ino = st->st_ino;
	ost->st_mode = st->st_mode;
	ost->st_nlink = st->st_nlink;
	ost->st_uid = st->st_uid;
	ost->st_gid = st->st_gid;
	ost->st_rdev = st->st_rdev;
	if (st->st_size < (quad_t)1 << 32)
		ost->st_size = st->st_size;
	else
		ost->st_size = -2;
	ost->st_atime = st->st_atime;
	ost->st_mtime = st->st_mtime;
	ost->st_ctime = st->st_ctime;
	ost->st_blksize = st->st_blksize;
	ost->st_blocks = st->st_blocks;
	ost->st_flags = st->st_flags;
	ost->st_gen = st->st_gen;
}
D 192
#endif /* COMPAT_43 */
E 192
I 192
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 192

/*
D 222
 * Stat system call.
 * This version follows links.
E 222
I 222
 * Get file status; this version follows links.
E 222
 */
I 198
D 250
struct stat_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
	struct stat *ub;
};
E 250
E 198
/* ARGSUSED */
I 250
int
E 250
D 188
qstat(p, uap, retval)
E 188
I 188
stat(p, uap, retval)
E 188
	struct proc *p;
D 198
	register struct args {
		char	*fname;
E 178
		struct stat *ub;
	} *uap;
E 198
I 198
D 250
	register struct stat_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct stat_args /* {
		syscallarg(char *) path;
		syscallarg(struct stat *) ub;
	} */ *uap;
	register_t *retval;
E 250
E 143
E 109
{
I 143
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
	struct stat sb;
	int error;
I 160
	struct nameidata nd;
E 160
E 143
D 63
	register struct inode *ip;
	register struct a {
		char	*fname;
		struct stat *sb;
	} *uap;
E 63

I 160
D 174
	ndp = &nd;
E 160
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
D 109
	stat1(FOLLOW);
E 109
I 109
D 143
	stat1(scp, FOLLOW);
E 143
I 143
	ndp->ni_nameiop = LOOKUP | LOCKLEAF | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 162
	error = vn_stat(ndp->ni_vp, &sb);
E 162
I 162
D 174
	error = vn_stat(ndp->ni_vp, &sb, p);
E 162
	vput(ndp->ni_vp);
E 174
I 174
	error = vn_stat(nd.ni_vp, &sb, p);
	vput(nd.ni_vp);
E 174
	if (error)
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
D 250
	error = copyout((caddr_t)&sb, (caddr_t)uap->ub, sizeof (sb));
E 250
I 250
	error = copyout((caddr_t)&sb, (caddr_t)SCARG(uap, ub), sizeof (sb));
E 250
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 143
E 109
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
D 163
 * Lstat system call.  This version does not follow links.
E 163
I 163
D 222
 * Lstat system call.
 * This version does not follow links.
E 222
I 222
 * Get file status; this version does not follow links.
E 222
E 163
E 28
E 27
 */
I 198
D 250
struct lstat_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
	struct stat *ub;
};
E 250
E 198
D 109
lstat()
E 109
I 109
D 143
lstat(scp)
	struct syscontext *scp;
E 109
{
I 63

D 82
	stat1(0);
E 82
I 82
D 109
	stat1(NOFOLLOW);
E 109
I 109
	stat1(scp, NOFOLLOW);
E 109
E 82
}

D 109
stat1(follow)
E 109
I 109
stat1(scp, follow)
	register struct syscontext *scp;
E 109
	int follow;
{
E 63
D 102
	register struct inode *ip;
E 102
	register struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
D 178
lstat(p, uap, retval)
E 178
I 178
D 188
lqstat(p, uap, retval)
E 188
I 188
lstat(p, uap, retval)
E 188
E 178
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
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
D 109
	} *uap = (struct a *)u.u_ap;
E 82
I 63
D 102
	struct stat sb;
E 102
I 82
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct lstat_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct lstat_args /* {
		syscallarg(char *) path;
		syscallarg(struct stat *) ub;
	} */ *uap;
	register_t *retval;
E 250
{
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
I 102
D 212
	struct stat sb;
E 212
	int error;
I 212
	struct vnode *vp, *dvp;
	struct stat sb, sb1;
E 212
I 160
	struct nameidata nd;
E 160
E 102
E 82
E 63

I 160
D 174
	ndp = &nd;
E 160
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
D 102
	ndp->ni_nameiop = LOOKUP | follow;
E 102
I 102
D 143
	ndp->ni_nameiop = LOOKUP | LOCKLEAF | follow;
E 143
I 143
	ndp->ni_nameiop = LOOKUP | LOCKLEAF | NOFOLLOW;
E 143
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 102
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
E 102
I 102
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 212
	NDINIT(&nd, LOOKUP, NOFOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
E 212
I 212
	NDINIT(&nd, LOOKUP, NOFOLLOW | LOCKLEAF | LOCKPARENT, UIO_USERSPACE,
D 222
	    uap->fname, p);
E 222
I 222
D 250
	    uap->path, p);
E 250
I 250
	    SCARG(uap, path), p);
E 250
E 222
E 212
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 162
	error = vn_stat(ndp->ni_vp, &sb);
E 162
I 162
D 174
	error = vn_stat(ndp->ni_vp, &sb, p);
E 162
	vput(ndp->ni_vp);
E 174
I 174
D 212
	error = vn_stat(nd.ni_vp, &sb, p);
	vput(nd.ni_vp);
E 174
	if (error)
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 212
I 212
	/*
D 254
	 * For symbolic links, always return the attributes of its
	 * containing directory, except for mode, size, and links.
E 254
I 254
	 * For symbolic links, always return the attributes of its containing
	 * directory, except for mode, size, inode number, and links.
E 254
	 */
	vp = nd.ni_vp;
	dvp = nd.ni_dvp;
	if (vp->v_type != VLNK) {
		if (dvp == vp)
			vrele(dvp);
		else
			vput(dvp);
		error = vn_stat(vp, &sb, p);
		vput(vp);
		if (error)
			return (error);
	} else {
		error = vn_stat(dvp, &sb, p);
		vput(dvp);
		if (error) {
			vput(vp);
			return (error);
		}
		error = vn_stat(vp, &sb1, p);
		vput(vp);
		if (error)
			return (error);
		sb.st_mode &= ~S_IFDIR;
		sb.st_mode |= S_IFLNK;
		sb.st_nlink = sb1.st_nlink;
		sb.st_size = sb1.st_size;
		sb.st_blocks = sb1.st_blocks;
I 254
		sb.st_ino = sb1.st_ino;
E 254
	}
E 212
E 160
D 250
	error = copyout((caddr_t)&sb, (caddr_t)uap->ub, sizeof (sb));
E 250
I 250
	error = copyout((caddr_t)&sb, (caddr_t)SCARG(uap, ub), sizeof (sb));
E 250
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
E 63
}

/*
I 217
D 222
 * Pathconf system call.
E 222
I 222
 * Get configurable pathname variables.
E 222
 */
D 250
struct pathconf_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
	int	name;
};
E 250
/* ARGSUSED */
I 250
int
E 250
pathconf(p, uap, retval)
	struct proc *p;
D 250
	register struct pathconf_args *uap;
	int *retval;
E 250
I 250
	register struct pathconf_args /* {
		syscallarg(char *) path;
		syscallarg(int) name;
	} */ *uap;
	register_t *retval;
E 250
{
	int error;
	struct nameidata nd;

D 222
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
		return (error);
D 250
	error = VOP_PATHCONF(nd.ni_vp, uap->name, retval);
E 250
I 250
	error = VOP_PATHCONF(nd.ni_vp, SCARG(uap, name), retval);
E 250
	vput(nd.ni_vp);
	return (error);
}

/*
E 217
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
D 163
 * Return target name of a symbolic link
E 163
I 163
 * Return target name of a symbolic link.
E 163
E 23
E 17
 */
I 198
D 250
struct readlink_args {
D 222
	char	*name;
E 222
I 222
	char	*path;
E 222
	char	*buf;
	int	count;
};
E 250
E 198
I 23
D 109
readlink()
E 109
I 109
D 143
readlink(scp)
	register struct syscontext *scp;
E 109
{
D 102
	register struct inode *ip;
E 102
	register struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
readlink(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		char	*name;
		char	*buf;
		int	count;
D 39
	} *uap;
E 39
I 39
D 109
	} *uap = (struct a *)u.u_ap;
I 82
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct readlink_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct readlink_args /* {
		syscallarg(char *) path;
		syscallarg(char *) buf;
		syscallarg(int) count;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_READLINK;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
E 82
D 102
	int resid;
E 102
I 102
	register struct vnode *vp;
	struct iovec aiov;
	struct uio auio;
	int error;
I 160
	struct nameidata nd;
E 160
E 102
E 39

I 175
	CHECKPOINTREF;
E 175
I 172
D 174
	CHECKPOINT;
E 172
I 160
	ndp = &nd;
E 160
D 47
	ip = namei(uchar, 0, 0);
E 47
I 47
D 82
	ip = namei(uchar, LOOKUP, 0);
E 82
I 82
D 102
	ndp->ni_nameiop = LOOKUP;
E 102
I 102
	ndp->ni_nameiop = LOOKUP | LOCKLEAF;
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->name;
D 102
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
E 102
I 102
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, LOOKUP, NOFOLLOW | LOCKLEAF, UIO_USERSPACE, uap->name, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, NOFOLLOW | LOCKLEAF, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, NOFOLLOW | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
E 174
D 222
	if (vp->v_type != VLNK) {
E 222
I 222
	if (vp->v_type != VLNK)
E 222
		error = EINVAL;
E 102
E 89
D 222
		goto out;
E 222
I 222
	else {
D 250
		aiov.iov_base = uap->buf;
		aiov.iov_len = uap->count;
E 250
I 250
		aiov.iov_base = SCARG(uap, buf);
		aiov.iov_len = SCARG(uap, count);
E 250
		auio.uio_iov = &aiov;
		auio.uio_iovcnt = 1;
		auio.uio_offset = 0;
		auio.uio_rw = UIO_READ;
		auio.uio_segflg = UIO_USERSPACE;
		auio.uio_procp = p;
D 250
		auio.uio_resid = uap->count;
E 250
I 250
		auio.uio_resid = SCARG(uap, count);
E 250
		error = VOP_READLINK(vp, &auio, p->p_ucred);
E 222
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
D 102
	u.u_error = rdwri(UIO_READ, ip, uap->buf, uap->count, (off_t)0, 0,
	    &resid);
E 102
I 102
D 222
	aiov.iov_base = uap->buf;
	aiov.iov_len = uap->count;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_offset = 0;
	auio.uio_rw = UIO_READ;
	auio.uio_segflg = UIO_USERSPACE;
I 162
	auio.uio_procp = p;
E 162
	auio.uio_resid = uap->count;
D 160
	error = VOP_READLINK(vp, &auio, ndp->ni_cred);
E 160
I 160
	error = VOP_READLINK(vp, &auio, p->p_ucred);
E 160
E 102
E 94
E 39
E 38
out:
E 222
D 102
	iput(ip);
D 39
	u.u_r.r_val1 = uap->count - u.u_count;
E 39
I 39
	u.u_r.r_val1 = uap->count - resid;
E 102
I 102
	vput(vp);
D 109
	u.u_r.r_val1 = uap->count - auio.uio_resid;
E 109
I 109
D 143
	scp->sc_retval1 = uap->count - auio.uio_resid;
E 143
I 143
D 250
	*retval = uap->count - auio.uio_resid;
E 250
I 250
	*retval = SCARG(uap, count) - auio.uio_resid;
E 250
I 175
	CHECKREFS("readlink");
E 175
I 172
D 174
	CHECKCHECK("readlink");
E 174
E 172
E 143
E 109
I 105
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
}

/*
D 222
 * Change flags of a file given path name.
E 222
I 222
 * Change flags of a file given a path name.
E 222
 */
I 198
D 250
struct chflags_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
	int	flags;
};
E 250
E 198
D 109
chflags()
E 109
I 109
D 143
chflags(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
chflags(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		char	*fname;
		int	flags;
D 109
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct chflags_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct chflags_args /* {
		syscallarg(char *) path;
		syscallarg(int) flags;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_SETATTR;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
	register struct vnode *vp;
	struct vattr vattr;
	int error;
I 160
	struct nameidata nd;
E 160

I 160
D 174
	ndp = &nd;
E 160
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 140
	vattr_null(&vattr);
E 140
I 140
D 156
	VATTR_NULL(&vattr);
E 140
	vattr.va_flags = uap->flags;
E 156
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 213
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
E 213
I 213
D 222
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 222
E 213
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
I 213
D 241
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
E 213
E 174
D 141
	if (vp->v_mount->m_flag & M_RDONLY) {
E 141
I 141
D 222
	if (vp->v_mount->mnt_flag & MNT_RDONLY) {
E 222
I 222
D 262
	if (vp->v_mount->mnt_flag & MNT_RDONLY)
E 222
E 141
		error = EROFS;
D 222
		goto out;
E 222
I 222
	else {
		VATTR_NULL(&vattr);
D 250
		vattr.va_flags = uap->flags;
E 250
I 250
		vattr.va_flags = SCARG(uap, flags);
E 250
		error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 222
	}
E 262
I 262
	VATTR_NULL(&vattr);
	vattr.va_flags = SCARG(uap, flags);
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 262
I 156
D 222
	VATTR_NULL(&vattr);
	vattr.va_flags = uap->flags;
I 171
D 213
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 213
E 171
E 156
D 160
	error = VOP_SETATTR(vp, &vattr, ndp->ni_cred);
E 160
I 160
D 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred);
E 162
I 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 162
E 160
out:
E 222
	vput(vp);
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
}

/*
 * Change flags of a file given a file descriptor.
 */
I 198
D 250
struct fchflags_args {
	int	fd;
	int	flags;
};
E 250
E 198
D 109
fchflags()
E 109
I 109
D 143
fchflags(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
fchflags(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		int	fd;
		int	flags;
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct fchflags_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct fchflags_args /* {
		syscallarg(int) fd;
		syscallarg(int) flags;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_LOCK;
	USES_VOP_SETATTR;
	USES_VOP_UNLOCK;
E 195
E 187
E 143
E 109
	struct vattr vattr;
	struct vnode *vp;
	struct file *fp;
	int error;

D 109
	if (error = getvnode(uap->fd, &fp))
E 109
I 109
D 143
	if (error = getvnode(scp->sc_ofile, uap->fd, &fp))
E 143
I 143
D 157
	if (error = getvnode(u.u_ofile, uap->fd, &fp))
E 157
I 157
D 250
	if (error = getvnode(p->p_fd, uap->fd, &fp))
E 250
I 250
	if (error = getvnode(p->p_fd, SCARG(uap, fd), &fp))
E 250
E 157
E 143
E 109
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
D 140
	vattr_null(&vattr);
E 140
I 140
D 156
	VATTR_NULL(&vattr);
E 140
	vattr.va_flags = uap->flags;
E 156
	vp = (struct vnode *)fp->f_data;
I 213
D 241
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
E 213
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
D 141
	if (vp->v_mount->m_flag & M_RDONLY) {
E 141
I 141
D 222
	if (vp->v_mount->mnt_flag & MNT_RDONLY) {
E 222
I 222
D 262
	if (vp->v_mount->mnt_flag & MNT_RDONLY)
E 222
E 141
		error = EROFS;
D 222
		goto out;
E 222
I 222
	else {
		VATTR_NULL(&vattr);
D 250
		vattr.va_flags = uap->flags;
E 250
I 250
		vattr.va_flags = SCARG(uap, flags);
E 250
		error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 222
	}
E 262
I 262
	VATTR_NULL(&vattr);
	vattr.va_flags = SCARG(uap, flags);
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 262
I 156
D 222
	VATTR_NULL(&vattr);
	vattr.va_flags = uap->flags;
I 171
D 213
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 213
E 171
E 156
D 160
	error = VOP_SETATTR(vp, &vattr, fp->f_cred);
E 160
I 160
D 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred);
E 162
I 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 162
E 160
out:
E 222
D 259
	VOP_UNLOCK(vp);
E 259
I 259
	VOP_UNLOCK(vp, 0, p);
E 259
E 105
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
E 39
}

I 47
/*
 * Change mode of a file given path name.
 */
I 198
D 250
struct chmod_args {
D 222
	char	*fname;
	int	fmode;
E 222
I 222
	char	*path;
	int	mode;
E 222
};
E 250
E 198
E 47
D 26
/*
 * symlink -- make a symbolic link
 */
symlink()
E 26
I 26
D 109
chmod()
E 109
I 109
D 143
chmod(scp)
	register struct syscontext *scp;
E 109
E 26
{
I 26
D 37
	register struct inode *ip;
E 26
	register struct a {
E 37
I 37
D 102
	struct inode *ip;
E 102
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
chmod(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
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
D 109
	} *uap = (struct a *)u.u_ap;
I 102
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct chmod_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct chmod_args /* {
		syscallarg(char *) path;
		syscallarg(int) mode;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_SETATTR;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
	register struct vnode *vp;
	struct vattr vattr;
	int error;
I 160
	struct nameidata nd;
E 160
E 102
E 82
D 26
	register struct inode *ip;
	register char *tp;
	register c, nc;
E 26

I 160
D 174
	ndp = &nd;
E 160
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
D 102
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
E 102
I 102
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 140
	vattr_null(&vattr);
E 140
I 140
D 156
	VATTR_NULL(&vattr);
E 140
	vattr.va_mode = uap->fmode & 07777;
E 156
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 213
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
E 213
I 213
D 222
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 222
E 213
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
I 213
D 241
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
E 213
E 174
D 141
	if (vp->v_mount->m_flag & M_RDONLY) {
E 141
I 141
D 222
	if (vp->v_mount->mnt_flag & MNT_RDONLY) {
E 222
I 222
D 262
	if (vp->v_mount->mnt_flag & MNT_RDONLY)
E 222
E 141
		error = EROFS;
D 222
		goto out;
E 222
I 222
	else {
		VATTR_NULL(&vattr);
D 250
		vattr.va_mode = uap->mode & ALLPERMS;
E 250
I 250
		vattr.va_mode = SCARG(uap, mode) & ALLPERMS;
E 250
		error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 222
	}
E 262
I 262
	VATTR_NULL(&vattr);
	vattr.va_mode = SCARG(uap, mode) & ALLPERMS;
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 262
I 156
D 222
	VATTR_NULL(&vattr);
	vattr.va_mode = uap->fmode & 07777;
I 171
D 213
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 213
E 171
E 156
D 160
	error = VOP_SETATTR(vp, &vattr, ndp->ni_cred);
E 160
I 160
D 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred);
E 162
I 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 162
E 160
out:
E 222
	vput(vp);
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
E 47
}
E 37

I 47
/*
 * Change mode of a file given a file descriptor.
 */
I 198
D 250
struct fchmod_args {
	int	fd;
D 222
	int	fmode;
E 222
I 222
	int	mode;
E 222
};
E 250
E 198
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
D 109
fchmod()
E 109
I 109
D 143
fchmod(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
fchmod(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		int	fd;
		int	fmode;
D 82
	} *uap;
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct fchmod_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct fchmod_args /* {
		syscallarg(int) fd;
		syscallarg(int) mode;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_LOCK;
	USES_VOP_SETATTR;
	USES_VOP_UNLOCK;
E 195
E 187
E 143
E 109
E 82
D 102
	register struct inode *ip;
	register struct file *fp;
E 102
I 102
	struct vattr vattr;
	struct vnode *vp;
	struct file *fp;
	int error;
E 102

D 82
	uap = (struct a *)u.u_ap;
E 82
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
 * Change the mode on a file.
 * Inode must be locked before calling.
 */
E 47
chmod1(ip, mode)
	register struct inode *ip;
	register int mode;
{
I 40
D 63
	register int *gp;
E 63

I 89
	if (ip->i_fs->fs_ronly)
		return (EROFS);
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
	ip->i_mode &= ~07777;
D 33
	if (u.u_uid)
E 33
I 33
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
		if (!groupmember(ip->i_gid))
			mode &= ~ISGID;
E 102
I 102
D 109
	if (error = getvnode(uap->fd, &fp))
E 109
I 109
D 143
	if (error = getvnode(scp->sc_ofile, uap->fd, &fp))
E 143
I 143
D 157
	if (error = getvnode(u.u_ofile, uap->fd, &fp))
E 157
I 157
D 250
	if (error = getvnode(p->p_fd, uap->fd, &fp))
E 250
I 250
	if (error = getvnode(p->p_fd, SCARG(uap, fd), &fp))
E 250
E 157
E 143
E 109
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
D 140
	vattr_null(&vattr);
E 140
I 140
D 156
	VATTR_NULL(&vattr);
E 140
	vattr.va_mode = uap->fmode & 07777;
E 156
	vp = (struct vnode *)fp->f_data;
I 213
D 241
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
E 213
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
D 141
	if (vp->v_mount->m_flag & M_RDONLY) {
E 141
I 141
D 222
	if (vp->v_mount->mnt_flag & MNT_RDONLY) {
E 222
I 222
D 262
	if (vp->v_mount->mnt_flag & MNT_RDONLY)
E 222
E 141
		error = EROFS;
D 222
		goto out;
E 222
I 222
	else {
		VATTR_NULL(&vattr);
D 250
		vattr.va_mode = uap->mode & ALLPERMS;
E 250
I 250
		vattr.va_mode = SCARG(uap, mode) & ALLPERMS;
E 250
		error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 222
E 102
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
E 262
I 262
	VATTR_NULL(&vattr);
	vattr.va_mode = SCARG(uap, mode) & ALLPERMS;
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 262
I 156
D 222
	VATTR_NULL(&vattr);
	vattr.va_mode = uap->fmode & 07777;
I 171
D 213
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 213
E 171
E 156
E 33
D 37
	ip->i_mode |= uap->fmode&07777;
E 37
I 37
D 102
	ip->i_mode |= mode&07777;
E 37
	ip->i_flag |= ICHG;
	if (ip->i_flag&ITEXT && (ip->i_mode&ISVTX)==0)
		xrele(ip);
I 89
	return (0);
E 102
I 102
D 160
	error = VOP_SETATTR(vp, &vattr, fp->f_cred);
E 160
I 160
D 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred);
E 162
I 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 162
E 160
out:
E 222
D 259
	VOP_UNLOCK(vp);
E 259
I 259
	VOP_UNLOCK(vp, 0, p);
E 259
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
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
 * Set ownership given a path name.
 */
I 198
D 250
struct chown_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
	int	uid;
	int	gid;
};
E 250
E 198
E 47
D 26
/*
 * the dup system call.
 */
E 23
dup()
E 26
I 26
D 109
chown()
E 109
I 109
D 143
chown(scp)
	register struct syscontext *scp;
E 109
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
D 102
	struct inode *ip;
E 102
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
chown(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
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
D 109
	} *uap = (struct a *)u.u_ap;
I 99
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct chown_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct chown_args /* {
		syscallarg(char *) path;
		syscallarg(int) uid;
		syscallarg(int) gid;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_SETATTR;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
I 102
	register struct vnode *vp;
	struct vattr vattr;
	int error;
I 160
	struct nameidata nd;
E 160
E 102
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

I 160
D 174
	ndp = &nd;
E 160
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
D 102
	ndp->ni_nameiop = LOOKUP | NOFOLLOW;
E 102
I 102
	ndp->ni_nameiop = LOOKUP | NOFOLLOW | LOCKLEAF;
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 102
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
E 102
I 102
D 140
	vattr_null(&vattr);
E 140
I 140
D 156
	VATTR_NULL(&vattr);
E 140
	vattr.va_uid = uap->uid;
	vattr.va_gid = uap->gid;
E 156
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 213
	NDINIT(&nd, LOOKUP, NOFOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
E 213
I 213
D 222
	NDINIT(&nd, LOOKUP, NOFOLLOW, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 233
	NDINIT(&nd, LOOKUP, NOFOLLOW, UIO_USERSPACE, uap->path, p);
E 233
I 233
D 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 233
E 222
E 213
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
I 213
D 241
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
E 213
E 174
D 141
	if (vp->v_mount->m_flag & M_RDONLY) {
E 141
I 141
D 222
	if (vp->v_mount->mnt_flag & MNT_RDONLY) {
E 222
I 222
D 262
	if (vp->v_mount->mnt_flag & MNT_RDONLY)
E 222
E 141
		error = EROFS;
D 222
		goto out;
E 222
I 222
	else {
		VATTR_NULL(&vattr);
D 250
		vattr.va_uid = uap->uid;
		vattr.va_gid = uap->gid;
E 250
I 250
		vattr.va_uid = SCARG(uap, uid);
		vattr.va_gid = SCARG(uap, gid);
E 250
		error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 222
	}
E 262
I 262
	VATTR_NULL(&vattr);
	vattr.va_uid = SCARG(uap, uid);
	vattr.va_gid = SCARG(uap, gid);
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 262
I 156
D 222
	VATTR_NULL(&vattr);
	vattr.va_uid = uap->uid;
	vattr.va_gid = uap->gid;
I 171
D 213
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 213
E 171
E 156
D 160
	error = VOP_SETATTR(vp, &vattr, ndp->ni_cred);
E 160
I 160
D 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred);
E 162
I 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 162
E 160
out:
E 222
	vput(vp);
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
E 47
}
E 37

I 47
/*
 * Set ownership given a file descriptor.
 */
I 198
D 250
struct fchown_args {
	int	fd;
	int	uid;
	int	gid;
};
E 250
E 198
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
D 109
fchown()
E 109
I 109
D 143
fchown(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
fchown(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		int	fd;
		int	uid;
		int	gid;
D 82
	} *uap;
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct fchown_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct fchown_args /* {
		syscallarg(int) fd;
		syscallarg(int) uid;
		syscallarg(int) gid;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_LOCK;
	USES_VOP_SETATTR;
	USES_VOP_UNLOCK;
E 195
E 187
E 143
E 109
E 82
D 102
	register struct inode *ip;
	register struct file *fp;
E 102
I 102
	struct vattr vattr;
	struct vnode *vp;
	struct file *fp;
	int error;
E 102

D 82
	uap = (struct a *)u.u_ap;
E 82
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
E 102
I 102
D 109
	if (error = getvnode(uap->fd, &fp))
E 109
I 109
D 143
	if (error = getvnode(scp->sc_ofile, uap->fd, &fp))
E 143
I 143
D 157
	if (error = getvnode(u.u_ofile, uap->fd, &fp))
E 157
I 157
D 250
	if (error = getvnode(p->p_fd, uap->fd, &fp))
E 250
I 250
	if (error = getvnode(p->p_fd, SCARG(uap, fd), &fp))
E 250
E 157
E 143
E 109
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
D 140
	vattr_null(&vattr);
E 140
I 140
D 156
	VATTR_NULL(&vattr);
E 140
	vattr.va_uid = uap->uid;
	vattr.va_gid = uap->gid;
E 156
	vp = (struct vnode *)fp->f_data;
I 213
D 241
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
E 213
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
D 141
	if (vp->v_mount->m_flag & M_RDONLY) {
E 141
I 141
D 222
	if (vp->v_mount->mnt_flag & MNT_RDONLY) {
E 222
I 222
D 262
	if (vp->v_mount->mnt_flag & MNT_RDONLY)
E 222
E 141
		error = EROFS;
D 222
		goto out;
E 222
I 222
	else {
		VATTR_NULL(&vattr);
D 250
		vattr.va_uid = uap->uid;
		vattr.va_gid = uap->gid;
E 250
I 250
		vattr.va_uid = SCARG(uap, uid);
		vattr.va_gid = SCARG(uap, gid);
E 250
		error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 222
	}
E 262
I 262
	VATTR_NULL(&vattr);
	vattr.va_uid = SCARG(uap, uid);
	vattr.va_gid = SCARG(uap, gid);
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 262
I 156
D 222
	VATTR_NULL(&vattr);
	vattr.va_uid = uap->uid;
	vattr.va_gid = uap->gid;
I 171
D 213
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 213
E 171
E 156
D 160
	error = VOP_SETATTR(vp, &vattr, fp->f_cred);
E 160
I 160
D 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred);
E 162
I 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 162
E 160
out:
E 222
D 259
	VOP_UNLOCK(vp);
E 259
I 259
	VOP_UNLOCK(vp, 0, p);
E 259
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
E 81
E 47
}

D 102
/*
 * Perform chown operation on inode ip;
 * inode must be locked prior to call.
 */
chown1(ip, uid, gid)
	register struct inode *ip;
	int uid, gid;
{
#ifdef QUOTA
	register long change;
I 60
#endif
E 60

I 89
	if (ip->i_fs->fs_ronly)
		return (EROFS);
E 89
I 60
	if (uid == -1)
		uid = ip->i_uid;
	if (gid == -1)
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
#endif
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
	ip->i_flag |= ICHG;
	if (u.u_ruid != 0)
		ip->i_mode &= ~(ISUID|ISGID);
I 34
D 37
#if	QUOTA
E 37
I 37
#ifdef QUOTA
E 37
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
I 62
#endif
E 62
E 60
E 34
D 47
	iput(ip);
E 47
E 26
}

E 102
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
D 109
utimes()
E 109
I 109
D 143
utimes(scp)
	register struct syscontext *scp;
E 109
{
	register struct a {
E 143
I 143
/*
 * Set the access and modification times of a file.
 */
I 198
D 250
struct utimes_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
	struct	timeval *tptr;
};
E 250
E 198
/* ARGSUSED */
I 250
int
E 250
utimes(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		char	*fname;
		struct	timeval *tptr;
D 109
	} *uap = (struct a *)u.u_ap;
D 102
	register struct inode *ip;
E 102
I 102
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct utimes_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct utimes_args /* {
		syscallarg(char *) path;
		syscallarg(struct timeval *) tptr;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_SETATTR;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
	register struct vnode *vp;
E 102
	struct timeval tv[2];
I 102
	struct vattr vattr;
D 209
	int error;
E 209
I 209
D 211
	int s, error;
E 211
I 211
	int error;
E 211
E 209
I 160
	struct nameidata nd;
E 160
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
E 102
I 102
D 209
	if (error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv)))
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 209
I 209
	VATTR_NULL(&vattr);
D 250
	if (uap->tptr == NULL) {
E 250
I 250
	if (SCARG(uap, tptr) == NULL) {
E 250
		microtime(&tv[0]);
		tv[1] = tv[0];
D 210
		vattr.va_cflags |= VA_UTIMES_NULL;
E 210
I 210
		vattr.va_vaflags |= VA_UTIMES_NULL;
E 210
D 250
	} else if (error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv)))
E 250
I 250
	} else if (error = copyin((caddr_t)SCARG(uap, tptr), (caddr_t)tv,
	    sizeof (tv)))
E 250
  		return (error);
E 209
D 174
	ndp = &nd;
E 160
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 140
	vattr_null(&vattr);
E 140
I 140
D 156
	VATTR_NULL(&vattr);
E 140
	vattr.va_atime = tv[0];
	vattr.va_mtime = tv[1];
E 156
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 213
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
E 213
I 213
D 222
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 222
E 213
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
I 213
D 241
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
E 213
E 174
D 141
	if (vp->v_mount->m_flag & M_RDONLY) {
E 141
I 141
D 222
	if (vp->v_mount->mnt_flag & MNT_RDONLY) {
E 222
I 222
D 262
	if (vp->v_mount->mnt_flag & MNT_RDONLY)
E 222
E 141
		error = EROFS;
D 222
		goto out;
E 222
I 222
	else {
		vattr.va_atime.ts_sec = tv[0].tv_sec;
		vattr.va_atime.ts_nsec = tv[0].tv_usec * 1000;
		vattr.va_mtime.ts_sec = tv[1].tv_sec;
		vattr.va_mtime.ts_nsec = tv[1].tv_usec * 1000;
		error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 222
E 102
	}
E 262
I 262
	vattr.va_atime.ts_sec = tv[0].tv_sec;
	vattr.va_atime.ts_nsec = tv[0].tv_usec * 1000;
	vattr.va_mtime.ts_sec = tv[1].tv_sec;
	vattr.va_mtime.ts_nsec = tv[1].tv_usec * 1000;
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 262
I 156
D 209
	VATTR_NULL(&vattr);
E 209
D 178
	vattr.va_atime = tv[0];
	vattr.va_mtime = tv[1];
E 178
I 178
D 190
	vattr.va_atime.tv_sec = tv[0].tv_sec;
	vattr.va_mtime.tv_sec = tv[1].tv_sec;
E 190
I 190
D 222
	vattr.va_atime.ts_sec = tv[0].tv_sec;
	vattr.va_atime.ts_nsec = tv[0].tv_usec * 1000;
	vattr.va_mtime.ts_sec = tv[1].tv_sec;
	vattr.va_mtime.ts_nsec = tv[1].tv_usec * 1000;
E 190
E 178
I 171
D 213
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 213
E 171
E 156
E 89
D 102
	u.u_error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv));
	if (u.u_error == 0) {
		ip->i_flag |= IACC|IUPD|ICHG;
		iupdat(ip, &tv[0], &tv[1], 0);
	}
	iput(ip);
E 102
I 102
D 160
	error = VOP_SETATTR(vp, &vattr, ndp->ni_cred);
E 160
I 160
D 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred);
E 162
I 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 162
E 160
out:
E 222
	vput(vp);
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
}

I 222
/*
 * Truncate a file given its path name.
 */
E 222
I 178
D 192
#ifdef COMPAT_43
E 192
I 192
D 197
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 192
E 178
E 60
I 47
/*
D 102
 * Flush any pending I/O.
 */
E 47
D 26
/*
 * the umount system call.
 */
sumount()
E 26
I 26
sync()
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
	update();
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
E 102
 * Truncate a file given its path name.
 */
E 47
D 109
truncate()
E 109
I 109
D 143
truncate(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
truncate(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
	register struct args {
E 143
		char	*fname;
I 178
		long	length;
	} *uap;
	int *retval;
{
	struct nargs {
		char	*fname;
E 178
D 47
		int	length;
E 47
I 47
D 95
		u_long	length;
E 95
I 95
		off_t	length;
I 178
	} nuap;
E 197
I 197
D 198
struct args_truncate {
E 198
I 198
D 218
struct __truncate_args {
E 218
I 218
D 250
struct truncate_args {
E 218
E 198
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
	int	pad;
	off_t	length;
};
E 250
E 197
D 222

D 197
	nuap.fname = uap->fname;
	nuap.length = uap->length;
D 188
	return (qtruncate(p, &nuap, retval));
E 188
I 188
	return (__truncate(p, &nuap, retval));
E 188
}

E 197
/*
D 197
 * Truncate a file given a file descriptor.
 */
/* ARGSUSED */
ftruncate(p, uap, retval)
	struct proc *p;
	register struct args {
		int	fd;
		long	length;
E 178
E 95
E 47
D 39
	} *uap;
E 39
I 39
D 109
	} *uap = (struct a *)u.u_ap;
E 39
D 102
	struct inode *ip;
E 102
I 82
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
	int *retval;
{
I 178
	struct nargs {
		int	fd;
		off_t	length;
	} nuap;

	nuap.fd = uap->fd;
	nuap.length = uap->length;
D 188
	return (fqtruncate(p, &nuap, retval));
E 188
I 188
	return (__ftruncate(p, &nuap, retval));
E 188
}
D 192
#endif /* COMPAT_43 */
E 192
I 192
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 192

/*
E 197
 * Truncate a file given its path name.
 */
E 222
/* ARGSUSED */
I 250
int
E 250
D 188
qtruncate(p, uap, retval)
E 188
I 188
D 217
__truncate(p, uap, retval)
E 217
I 217
truncate(p, uap, retval)
E 217
E 188
	struct proc *p;
D 197
	register struct args {
		char	*fname;
		off_t	length;
	} *uap;
E 197
I 197
D 198
	register struct args_truncate *uap;
E 198
I 198
D 218
	register struct __truncate_args *uap;
E 218
I 218
D 250
	register struct truncate_args *uap;
E 218
E 198
E 197
	int *retval;
E 250
I 250
	register struct truncate_args /* {
		syscallarg(char *) path;
		syscallarg(int) pad;
		syscallarg(off_t) length;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_ACCESS;
	USES_VOP_SETATTR;
E 195
E 187
E 178
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
I 102
	register struct vnode *vp;
	struct vattr vattr;
	int error;
I 160
	struct nameidata nd;
E 160
E 102
E 82

I 160
D 174
	ndp = &nd;
E 160
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
E 102
I 102
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 102
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
E 102
I 102
D 140
	vattr_null(&vattr);
E 140
I 140
D 156
	VATTR_NULL(&vattr);
E 140
	vattr.va_size = uap->length;
E 156
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 213
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
E 213
I 213
D 222
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 222
E 213
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
I 213
D 241
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
E 213
E 174
D 222
	if (vp->v_type == VDIR) {
E 222
I 222
	if (vp->v_type == VDIR)
E 222
		error = EISDIR;
D 222
		goto out;
E 222
I 222
	else if ((error = vn_writechk(vp)) == 0 &&
	    (error = VOP_ACCESS(vp, VWRITE, p->p_ucred, p)) == 0) {
		VATTR_NULL(&vattr);
D 250
		vattr.va_size = uap->length;
E 250
I 250
		vattr.va_size = SCARG(uap, length);
E 250
		error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 222
E 102
	}
D 95
	itrunc(ip, uap->length);
E 95
I 95
D 102
	itrunc(ip, (u_long)uap->length);
E 95
D 47
	return;
E 47
bad:
	iput(ip);
E 102
I 102
D 108
	if (error = vn_access(vp, VWRITE, ndp->ni_cred))
E 108
I 108
D 222
	if ((error = vn_writechk(vp)) ||
D 160
	    (error = VOP_ACCESS(vp, VWRITE, ndp->ni_cred)))
E 160
I 160
D 162
	    (error = VOP_ACCESS(vp, VWRITE, p->p_ucred)))
E 162
I 162
	    (error = VOP_ACCESS(vp, VWRITE, p->p_ucred, p)))
E 162
E 160
E 108
		goto out;
I 156
	VATTR_NULL(&vattr);
	vattr.va_size = uap->length;
I 171
D 213
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 213
E 171
E 156
D 160
	error = VOP_SETATTR(vp, &vattr, ndp->ni_cred);
E 160
I 160
D 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred);
E 162
I 162
	error = VOP_SETATTR(vp, &vattr, p->p_ucred, p);
E 162
E 160
out:
E 222
	vput(vp);
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
}

I 222
/*
 * Truncate a file given a file descriptor.
 */
E 222
I 197
D 198
struct args_ftruncate {
E 198
I 198
D 218
struct __ftruncate_args {
E 218
I 218
D 250
struct ftruncate_args {
E 218
E 198
	int	fd;
	int	pad;
	off_t	length;
};
E 250
D 222

E 197
I 47
/*
 * Truncate a file given a file descriptor.
 */
E 222
E 47
D 109
ftruncate()
E 109
I 109
D 143
ftruncate(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
D 178
ftruncate(p, uap, retval)
E 178
I 178
D 188
fqtruncate(p, uap, retval)
E 188
I 188
D 217
__ftruncate(p, uap, retval)
E 217
I 217
ftruncate(p, uap, retval)
E 217
E 188
E 178
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 197
	register struct args {
E 143
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
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 197
I 197
D 198
	register struct args_ftruncate *uap;
E 198
I 198
D 218
	register struct __ftruncate_args *uap;
E 218
I 218
D 250
	register struct ftruncate_args *uap;
E 218
E 198
E 197
	int *retval;
E 250
I 250
	register struct ftruncate_args /* {
		syscallarg(int) fd;
		syscallarg(int) pad;
		syscallarg(off_t) length;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_LOCK;
	USES_VOP_SETATTR;
	USES_VOP_UNLOCK;
E 195
E 187
E 143
E 109
E 39
D 102
	struct inode *ip;
E 102
I 102
	struct vattr vattr;
	struct vnode *vp;
E 102
	struct file *fp;
I 102
	int error;
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
D 109
	if (error = getvnode(uap->fd, &fp))
E 109
I 109
D 143
	if (error = getvnode(scp->sc_ofile, uap->fd, &fp))
E 143
I 143
D 157
	if (error = getvnode(u.u_ofile, uap->fd, &fp))
E 157
I 157
D 250
	if (error = getvnode(p->p_fd, uap->fd, &fp))
E 250
I 250
	if (error = getvnode(p->p_fd, SCARG(uap, fd), &fp))
E 250
E 157
E 143
E 109
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
	if ((fp->f_flag & FWRITE) == 0)
D 160
		RETURN (EINVAL);
E 160
I 160
		return (EINVAL);
E 160
D 140
	vattr_null(&vattr);
E 140
I 140
D 156
	VATTR_NULL(&vattr);
E 140
	vattr.va_size = uap->length;
E 156
	vp = (struct vnode *)fp->f_data;
I 213
D 241
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
E 213
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
D 222
	if (vp->v_type == VDIR) {
E 222
I 222
	if (vp->v_type == VDIR)
E 222
		error = EISDIR;
D 222
		goto out;
E 222
I 222
	else if ((error = vn_writechk(vp)) == 0) {
		VATTR_NULL(&vattr);
D 250
		vattr.va_size = uap->length;
E 250
I 250
		vattr.va_size = SCARG(uap, length);
E 250
		error = VOP_SETATTR(vp, &vattr, fp->f_cred, p);
E 222
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
D 108
	if (error = vn_access(vp, VWRITE, fp->f_cred))
E 108
I 108
D 222
	if (error = vn_writechk(vp))
E 108
		goto out;
I 156
	VATTR_NULL(&vattr);
	vattr.va_size = uap->length;
I 171
D 213
	LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 213
E 171
E 156
D 162
	error = VOP_SETATTR(vp, &vattr, fp->f_cred);
E 162
I 162
	error = VOP_SETATTR(vp, &vattr, fp->f_cred, p);
E 162
out:
E 222
D 259
	VOP_UNLOCK(vp);
E 259
I 259
	VOP_UNLOCK(vp, 0, p);
E 259
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
E 81
E 47
}
I 197

#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
/*
 * Truncate a file given its path name.
 */
I 198
D 218
struct truncate_args {
E 218
I 218
D 250
struct otruncate_args {
E 218
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
	long	length;
};
E 250
E 198
/* ARGSUSED */
D 216
truncate(p, uap, retval)
E 216
I 216
D 250
otruncate(p, uap, retval)
E 250
I 250
int
compat_43_truncate(p, uap, retval)
E 250
E 216
	struct proc *p;
D 198
	register struct args {
		char	*fname;
		long	length;
	} *uap;
E 198
I 198
D 218
	register struct truncate_args *uap;
E 218
I 218
D 250
	register struct otruncate_args *uap;
E 218
E 198
	int *retval;
E 250
I 250
	register struct compat_43_truncate_args /* {
		syscallarg(char *) path;
		syscallarg(long) length;
	} */ *uap;
	register_t *retval;
E 250
{
D 198
	struct args_truncate nuap;
E 198
I 198
D 218
	struct __truncate_args nuap;
E 218
I 218
D 250
	struct truncate_args nuap;
E 250
I 250
	struct truncate_args /* {
		syscallarg(char *) path;
		syscallarg(int) pad;
		syscallarg(off_t) length;
	} */ nuap;
E 250
E 218
E 198

D 222
	nuap.fname = uap->fname;
E 222
I 222
D 250
	nuap.path = uap->path;
E 222
	nuap.length = uap->length;
E 250
I 250
	SCARG(&nuap, path) = SCARG(uap, path);
	SCARG(&nuap, length) = SCARG(uap, length);
E 250
D 218
	return (__truncate(p, &nuap, retval));
E 218
I 218
	return (truncate(p, &nuap, retval));
E 218
}

/*
 * Truncate a file given a file descriptor.
 */
I 198
D 218
struct ftruncate_args {
E 218
I 218
D 250
struct oftruncate_args {
E 218
	int	fd;
	long	length;
};
E 250
E 198
/* ARGSUSED */
D 216
ftruncate(p, uap, retval)
E 216
I 216
D 250
oftruncate(p, uap, retval)
E 250
I 250
int
compat_43_ftruncate(p, uap, retval)
E 250
E 216
	struct proc *p;
D 198
	register struct args {
		int	fd;
		long	length;
	} *uap;
E 198
I 198
D 218
	register struct ftruncate_args *uap;
E 218
I 218
D 250
	register struct oftruncate_args *uap;
E 218
E 198
	int *retval;
E 250
I 250
	register struct compat_43_ftruncate_args /* {
		syscallarg(int) fd;
		syscallarg(long) length;
	} */ *uap;
	register_t *retval;
E 250
{
D 198
	struct args_ftruncate nuap;
E 198
I 198
D 200
	struct __truncate_args nuap;
E 200
I 200
D 218
	struct __ftruncate_args nuap;
E 218
I 218
D 250
	struct ftruncate_args nuap;
E 250
I 250
	struct ftruncate_args /* {
		syscallarg(int) fd;
		syscallarg(int) pad;
		syscallarg(off_t) length;
	} */ nuap;
E 250
E 218
E 200
E 198

D 250
	nuap.fd = uap->fd;
	nuap.length = uap->length;
E 250
I 250
	SCARG(&nuap, fd) = SCARG(uap, fd);
	SCARG(&nuap, length) = SCARG(uap, length);
E 250
D 218
	return (__ftruncate(p, &nuap, retval));
E 218
I 218
	return (ftruncate(p, &nuap, retval));
E 218
}
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 197

I 47
/*
D 222
 * Synch an open file.
E 222
I 222
 * Sync an open file.
E 222
 */
I 198
D 250
struct fsync_args {
	int	fd;
};
E 250
E 198
D 109
fsync()
E 109
I 109
D 143
fsync(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
fsync(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	struct args {
E 143
		int	fd;
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	struct fsync_args *uap;
E 198
	int *retval;
E 250
I 250
	struct fsync_args /* {
		syscallarg(int) fd;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_FSYNC;
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
E 195
E 187
E 143
I 123
	register struct vnode *vp;
E 123
E 109
D 102
	struct inode *ip;
E 102
	struct file *fp;
I 102
	int error;
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
		ip->i_flag |= ICHG;
E 97
E 81
	syncip(ip);
D 81
	iunlock(ip);
E 81
I 81
	IUNLOCK(ip);
E 102
I 102
D 109
	if (error = getvnode(uap->fd, &fp))
E 109
I 109
D 143
	if (error = getvnode(scp->sc_ofile, uap->fd, &fp))
E 143
I 143
D 157
	if (error = getvnode(u.u_ofile, uap->fd, &fp))
E 157
I 157
D 250
	if (error = getvnode(p->p_fd, uap->fd, &fp))
E 250
I 250
	if (error = getvnode(p->p_fd, SCARG(uap, fd), &fp))
E 250
E 157
E 143
E 109
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
D 123
	error = VOP_FSYNC((struct vnode *)fp->f_data, fp->f_flag, fp->f_cred);
E 123
I 123
	vp = (struct vnode *)fp->f_data;
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
D 162
	error = VOP_FSYNC(vp, fp->f_flag, fp->f_cred, MNT_WAIT);
E 162
I 162
D 193
	error = VOP_FSYNC(vp, fp->f_flag, fp->f_cred, MNT_WAIT, p);
E 193
I 193
	error = VOP_FSYNC(vp, fp->f_cred, MNT_WAIT, p);
E 193
E 162
D 259
	VOP_UNLOCK(vp);
E 259
I 259
	VOP_UNLOCK(vp, 0, p);
E 259
E 123
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
E 81
}

/*
D 222
 * Rename system call.
D 102
 * 	rename("foo", "bar");
 * is essentially
 *	unlink("bar");
 *	link("foo", "bar");
 *	unlink("foo");
 * but ``atomically''.  Can't do full commit without saving state in the
 * inode on disk which isn't feasible at this time.  Best we can do is
 * always guarantee the target exists.
E 102
 *
D 102
 * Basic algorithm is:
 *
 * 1) Bump link count on source while we're linking it to the
 *    target.  This also insure the inode won't be deleted out
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
 *
E 102
 * Source and destination must either both be directories, or both
 * not be directories.  If target is a directory, it must be empty.
E 222
I 222
 * Rename files.  Source and destination must either both be directories,
 * or both not be directories.  If target is a directory, it must be empty.
E 222
 */
I 198
D 250
struct rename_args {
	char	*from;
	char	*to;
};
E 250
E 198
E 47
D 109
rename()
E 109
I 109
D 143
rename(scp)
	register struct syscontext *scp;
E 109
{
I 39
D 47
#ifdef notdef
E 47
E 39
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
rename(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		char	*from;
		char	*to;
D 82
	} *uap;
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct rename_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct rename_args /* {
		syscallarg(char *) from;
		syscallarg(char *) to;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_ABORTOP;
	USES_VOP_RENAME;
E 195
E 187
E 143
E 109
E 82
I 39
D 47
#endif
E 47
I 47
D 102
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
E 102
I 102
	register struct vnode *tvp, *fvp, *tdvp;
E 102
E 84
I 82
D 109
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
D 160
	register struct nameidata *ndp = &u.u_nd;
E 143
E 109
E 82
I 52
D 102
	int error = 0;
E 102
I 102
	struct nameidata tond;
E 160
I 160
D 165
	register struct nameidata *ndp;
E 165
I 165
	struct nameidata fromnd, tond;
E 165
E 160
	int error;
I 160
D 165
	struct nameidata nd, tond;
E 165
E 160
E 102
E 52
E 47
E 39

I 175
	CHECKPOINTREF;
E 175
I 172
D 174
	CHECKPOINT;
E 172
I 160
D 165
	ndp = &nd;
E 160
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
E 102
I 102
	ndp->ni_nameiop = DELETE | WANTPARENT;
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->from;
D 102
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
E 82
D 84
	oldparent = 0, doingdirectory = 0;
E 84
	if ((ip->i_mode&IFMT) == IFDIR) {
		register struct direct *d;

D 82
		d = &u.u_dent;
E 82
I 82
		d = &ndp->ni_dent;
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
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 165
I 165
	fromnd.ni_nameiop = DELETE | WANTPARENT | SAVESTART;
	fromnd.ni_segflg = UIO_USERSPACE;
	fromnd.ni_dirp = uap->from;
	if (error = namei(&fromnd, p))
E 174
I 174
	NDINIT(&fromnd, DELETE, WANTPARENT | SAVESTART, UIO_USERSPACE,
D 250
		uap->from, p);
E 250
I 250
	    SCARG(uap, from), p);
E 250
	if (error = namei(&fromnd))
E 174
E 165
		return (error);
E 160
D 165
	fvp = ndp->ni_vp;
D 106
	bzero((caddr_t)&tond, sizeof(tond));
E 106
I 106
	nddup(ndp, &tond);
E 106
	tond.ni_nameiop = RENAME | LOCKPARENT | LOCKLEAF | NOCACHE;
E 165
I 165
	fvp = fromnd.ni_vp;
D 174
	tond.ni_nameiop = RENAME | LOCKPARENT | LOCKLEAF | NOCACHE | SAVESTART;
E 165
	tond.ni_segflg = UIO_USERSPACE;
	tond.ni_dirp = uap->to;
D 106
	tond.ni_cdir = ndp->ni_cdir;
	tond.ni_cdir->v_count++;
	tond.ni_rdir = ndp->ni_rdir;
	if (tond.ni_rdir)
		tond.ni_rdir->v_count++;
	tond.ni_cred = ndp->ni_cred;
	crhold(tond.ni_cred);
E 106
D 144
	error = namei(&tond);
E 144
I 144
D 160
	if (error = namei(&tond)) {
E 160
I 160
	if (error = namei(&tond, p)) {
E 174
I 174
	NDINIT(&tond, RENAME, LOCKPARENT | LOCKLEAF | NOCACHE | SAVESTART,
D 250
		UIO_USERSPACE, uap->to, p);
E 250
I 250
	    UIO_USERSPACE, SCARG(uap, to), p);
E 250
	if (error = namei(&tond)) {
E 174
E 160
D 165
		VOP_ABORTOP(ndp);
		vrele(ndp->ni_dvp);
E 165
I 165
D 172
		VOP_ABORTOP(&fromnd);
E 172
I 172
		VOP_ABORTOP(fromnd.ni_dvp, &fromnd.ni_cnd);
E 172
		vrele(fromnd.ni_dvp);
E 165
		vrele(fvp);
		goto out1;
	}
E 144
	tdvp = tond.ni_dvp;
	tvp = tond.ni_vp;
	if (tvp != NULL) {
		if (fvp->v_type == VDIR && tvp->v_type != VDIR) {
D 111
			error = EISDIR;
E 111
I 111
			error = ENOTDIR;
E 111
			goto out;
		} else if (fvp->v_type != VDIR && tvp->v_type == VDIR) {
D 111
			error = ENOTDIR;
E 111
I 111
			error = EISDIR;
E 111
			goto out;
E 102
E 58
		}
I 154
D 189
		if (fvp->v_mount != tvp->v_mount) {
			error = EXDEV;
			goto out;
		}
E 154
I 84
D 102
		ip->i_flag |= IRENAME;
E 84
		oldparent = dp->i_number;
		doingdirectory++;
E 102
	}
D 58
	irele(dp);
E 58
I 58
D 102
	iput(dp);
E 58

	/*
	 * 1) Bump link count while we're moving stuff
	 *    around.  If we crash somewhere before
	 *    completing our work, the link count
	 *    may be wrong, but correctable.
	 */
	ip->i_nlink++;
	ip->i_flag |= ICHG;
	iupdat(ip, &time, &time, 1);
D 81
	iunlock(ip);
E 81
I 81
	IUNLOCK(ip);
E 81

	/*
	 * When the target exists, both the directory
	 * and target inodes are returned locked.
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
E 102
I 102
D 144
	if (error) {
		VOP_ABORTOP(ndp);
		goto out1;
	}
E 144
	if (fvp->v_mount != tdvp->v_mount) {
		error = EXDEV;
E 102
E 52
		goto out;
E 189
I 52
	}
E 52
D 82
	dp = u.u_pdir;
E 82
I 82
D 102
	dp = ndp->ni_pdir;
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
		if (access(ip, IWRITE))
			goto bad;
		do {
D 82
			dp = u.u_pdir;
E 82
I 82
			dp = ndp->ni_pdir;
E 82
			if (xp != NULL)
				iput(xp);
			u.u_error = checkpath(ip, dp);
			if (u.u_error)
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
			xp = namei(ndp);
E 82
E 74
			if (u.u_error) {
				error = u.u_error;
				goto out;
			}
D 82
		} while (dp != u.u_pdir);
E 82
I 82
		} while (dp != ndp->ni_pdir);
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
E 84
			dp->i_nlink++;
			dp->i_flag |= ICHG;
			iupdat(dp, &time, &time, 1);
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
		error = direnter(ip, ndp);
E 82
		if (error)
E 55
E 52
			goto out;
E 102
I 102
D 112
	if (fvp == tdvp || fvp == tvp)
E 112
I 112
	if (fvp == tdvp)
E 112
		error = EINVAL;
I 112
	/*
D 165
	 * If source is the same as the destination,
E 165
I 165
	 * If source is the same as the destination (that is the
	 * same inode number with the same name in the same directory),
E 165
	 * then there is nothing to do.
	 */
D 165
	if (fvp == tvp)
E 165
I 165
	if (fvp == tvp && fromnd.ni_dvp == tdvp &&
D 174
	    fromnd.ni_namelen == tond.ni_namelen &&
	    !bcmp(fromnd.ni_ptr, tond.ni_ptr, fromnd.ni_namelen))
E 174
I 174
	    fromnd.ni_cnd.cn_namelen == tond.ni_cnd.cn_namelen &&
	    !bcmp(fromnd.ni_cnd.cn_nameptr, tond.ni_cnd.cn_nameptr,
	      fromnd.ni_cnd.cn_namelen))
E 174
E 165
		error = -1;
E 112
out:
D 144
	if (error) {
E 144
I 144
	if (!error) {
I 171
D 241
		LEASE_CHECK(tdvp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
		VOP_LEASE(tdvp, p, p->p_ucred, LEASE_WRITE);
E 241
		if (fromnd.ni_dvp != tdvp)
D 241
			LEASE_CHECK(fromnd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
			VOP_LEASE(fromnd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
		if (tvp)
D 241
			LEASE_CHECK(tvp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
			VOP_LEASE(tvp, p, p->p_ucred, LEASE_WRITE);
E 241
E 171
D 162
		error = VOP_RENAME(ndp, &tond);
E 162
I 162
D 165
		error = VOP_RENAME(ndp, &tond, p);
E 165
I 165
D 172
		error = VOP_RENAME(&fromnd, &tond, p);
E 172
I 172
D 174
		if (fromnd.ni_startdir != fromnd.ni_dvp ||
		    tond.ni_startdir != tond.ni_dvp)   /* NEEDSWORK: debug */
			printf ("rename: f.startdir=%x, dvp=%x; t.startdir=%x, dvp=%x\n", fromnd.ni_startdir, fromnd.ni_dvp, tond.ni_startdir, tond.ni_dvp);
E 174
		error = VOP_RENAME(fromnd.ni_dvp, fromnd.ni_vp, &fromnd.ni_cnd,
				   tond.ni_dvp, tond.ni_vp, &tond.ni_cnd);
D 174
		if (fromnd.ni_startdir != fromnd.ni_dvp ||
		    tond.ni_startdir != tond.ni_dvp)   /* NEEDSWORK: debug */
			printf ("rename: f.startdir=%x, dvp=%x; t.startdir=%x, dvp=%x\n", fromnd.ni_startdir, fromnd.ni_dvp, tond.ni_startdir, tond.ni_dvp);
E 174
E 172
E 165
E 162
	} else {
E 144
D 172
		VOP_ABORTOP(&tond);
E 172
I 172
		VOP_ABORTOP(tond.ni_dvp, &tond.ni_cnd);
E 172
I 144
D 146
		vput(tdvp);
E 146
I 146
		if (tdvp == tvp)
			vrele(tdvp);
		else
			vput(tdvp);
E 146
		if (tvp)
			vput(tvp);
E 144
D 165
		VOP_ABORTOP(ndp);
E 102
I 52
D 55
		}
E 55
E 52
D 144
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
I 54
		/*
		 * Short circuit rename(foo, foo).
		 */
		if (xp->i_number == ip->i_number)
			goto bad;
E 54
		/*
I 91
		 * If the parent directory is "sticky", then the user must
		 * own the parent directory, or the destination of the rename,
		 * otherwise the destination may not be changed (except by
		 * root). This implements append-only directories.
		 */
		if ((dp->i_mode & ISVTX) && u.u_uid != 0 &&
		    u.u_uid != dp->i_uid && xp->i_uid != u.u_uid) {
			error = EPERM;
			goto bad;
		}
		/*
E 91
D 52
		 * Target must be empty if a directory.
E 52
I 52
		 * Target must be empty if a directory
		 * and have no links to it.
E 52
		 * Also, insure source and target are
		 * compatible (both directories, or both
		 * not directories).
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
			if (!dirempty(xp, dp->i_number) || xp->i_nlink > 2) {
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
			cacheinval(dp);
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
			itrunc(xp, (u_long)0);
D 52
		} else
			xp->i_nlink--;
E 52
I 52
		}
E 52
		xp->i_flag |= ICHG;
		iput(xp);
I 53
		xp = NULL;
E 102
I 102
		error = VOP_RENAME(ndp, &tond);
E 144
I 144
		vrele(ndp->ni_dvp);
E 165
I 165
D 172
		VOP_ABORTOP(&fromnd);
E 172
I 172
		VOP_ABORTOP(fromnd.ni_dvp, &fromnd.ni_cnd);
E 172
		vrele(fromnd.ni_dvp);
E 165
		vrele(fvp);
E 144
E 102
E 53
	}
I 166
	p->p_spare[1]--;
E 166
I 165
	vrele(tond.ni_startdir);
D 174
	FREE(tond.ni_pnbuf, M_NAMEI);
E 174
I 174
	FREE(tond.ni_cnd.cn_pnbuf, M_NAMEI);
E 174
E 165
D 102

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
		dp = NULL;
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
	 * Insure that the directory entry still exists and has not
	 * changed while the new name has been entered. If the source is
	 * a file then the entry may have been unlinked or renamed. In
	 * either case there is no further work to be done. If the source
	 * is a directory then it cannot have been rmdir'ed; its link
	 * count of three would cause a rmdir to fail with ENOTEMPTY.
	 * The IRENAME flag insures that it cannot be moved by another
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
			error = rdwri(UIO_READ, xp, (caddr_t)&dirbuf,
				sizeof (struct dirtemplate), (off_t)0, 1,
				(int *)0);
			if (error == 0) {
				if (dirbuf.dotdot_namlen != 2 ||
				    dirbuf.dotdot_name[0] != '.' ||
				    dirbuf.dotdot_name[1] != '.') {
					printf("rename: mangled dir\n");
				} else {
					dirbuf.dotdot_ino = newparent;
					(void) rdwri(UIO_WRITE, xp,
					    (caddr_t)&dirbuf,
					    sizeof (struct dirtemplate),
					    (off_t)0, 1, (int *)0);
					cacheinval(dp);
				}
			}
E 84
		}
D 82
		if (dirremove()) {
E 82
I 82
		if (dirremove(ndp)) {
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
		if (error == 0)		/* XXX conservative */
E 84
			error = u.u_error;
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
		iput(dp);
I 84
	if (xp)
		iput(xp);
	irele(ip);
	if (error)
		u.u_error = error;
	return;
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
	iput(dp);
E 53
bad1:
	if (xp)
D 53
		irele(xp);
E 53
I 53
		iput(xp);
E 53
out:
	ip->i_nlink--;
	ip->i_flag |= ICHG;
	irele(ip);
I 52
D 84
done:
E 84
	if (error)
		u.u_error = error;
E 102
I 102
out1:
I 166
	p->p_spare[1]--;
E 166
D 106
	vrele(tond.ni_cdir);
	if (tond.ni_rdir)
		vrele(tond.ni_rdir);
	crfree(tond.ni_cred);
E 106
I 106
D 165
	ndrele(&tond);
E 165
I 165
D 234
	vrele(fromnd.ni_startdir);
E 234
I 234
	if (fromnd.ni_startdir)
		vrele(fromnd.ni_startdir);
E 234
D 174
	FREE(fromnd.ni_pnbuf, M_NAMEI);
I 172
	CHECKCHECK("rename");
E 174
I 174
	FREE(fromnd.ni_cnd.cn_pnbuf, M_NAMEI);
I 175
	CHECKREFS("rename");
E 175
E 174
E 172
E 165
I 112
	if (error == -1)
D 160
		RETURN (0);
E 112
E 106
	RETURN (error);
E 160
I 160
		return (0);
	return (error);
E 160
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
 * A virgin directory (no blushing please).
 */
struct dirtemplate mastertemplate = {
	0, 12, 1, ".",
	0, DIRBLKSIZ - 12, 2, ".."
};

/*
E 102
D 163
 * Mkdir system call
E 163
I 163
D 222
 * Mkdir system call.
E 222
I 222
 * Make a directory file.
E 222
E 163
 */
I 198
D 250
struct mkdir_args {
D 222
	char	*name;
	int	dmode;
E 222
I 222
	char	*path;
	int	mode;
E 222
};
E 250
E 198
D 109
mkdir()
E 109
I 109
D 143
mkdir(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
mkdir(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		char	*name;
		int	dmode;
D 82
	} *uap;
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
E 82
D 102
	register struct inode *ip, *dp;
	struct dirtemplate dirtemplate;
E 102
I 82
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct mkdir_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct mkdir_args /* {
		syscallarg(char *) path;
		syscallarg(int) mode;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_ABORTOP;
	USES_VOP_MKDIR;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
I 102
	register struct vnode *vp;
	struct vattr vattr;
	int error;
I 160
	struct nameidata nd;
E 160
E 102
E 82

I 175
	CHECKPOINTREF;
E 175
I 172
D 174
	CHECKPOINT;
E 172
I 160
	ndp = &nd;
E 160
D 82
	uap = (struct a *)u.u_ap;
	ip = namei(uchar, CREATE, 0);
E 82
I 82
D 102
	ndp->ni_nameiop = CREATE;
E 102
I 102
	ndp->ni_nameiop = CREATE | LOCKPARENT;
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->name;
D 102
	ip = namei(ndp);
E 82
	if (u.u_error)
		return;
	if (ip != NULL) {
		iput(ip);
		u.u_error = EEXIST;
		return;
E 102
I 102
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, uap->name, p);
E 222
I 222
D 250
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, CREATE, LOCKPARENT, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
E 174
	if (vp != NULL) {
D 172
		VOP_ABORTOP(ndp);
E 172
I 172
D 174
		VOP_ABORTOP(ndp->ni_dvp, &ndp->ni_cnd);
E 172
I 144
D 146
		vput(ndp->ni_dvp);
E 146
I 146
		if (ndp->ni_dvp == vp)
			vrele(ndp->ni_dvp);
E 174
I 174
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
		if (nd.ni_dvp == vp)
			vrele(nd.ni_dvp);
E 174
		else
D 174
			vput(ndp->ni_dvp);
E 174
I 174
			vput(nd.ni_dvp);
E 174
E 146
		vrele(vp);
I 175
		CHECKREFS("mkdir1");
E 175
I 172
D 174
		CHECKCHECK("mkdir1");
E 174
E 172
E 144
D 160
		RETURN (EEXIST);
E 160
I 160
		return (EEXIST);
E 160
E 102
	}
D 82
	dp = u.u_pdir;
E 82
I 82
D 102
	dp = ndp->ni_pdir;
E 82
	uap->dmode &= 0777;
	uap->dmode |= IFDIR;
	/*
	 * Must simulate part of maknode here
	 * in order to acquire the inode, but
	 * not have it entered in the parent
	 * directory.  The entry is made later
	 * after writing "." and ".." entries out.
	 */
	ip = ialloc(dp, dirpref(dp->i_fs), uap->dmode);
	if (ip == NULL) {
		iput(dp);
		return;
	}
#ifdef QUOTA
	if (ip->i_dquot != NODQUOT)
		panic("mkdir: dquot");
#endif
	ip->i_flag |= IACC|IUPD|ICHG;
	ip->i_mode = uap->dmode & ~u.u_cmask;
	ip->i_nlink = 2;
	ip->i_uid = u.u_uid;
	ip->i_gid = dp->i_gid;
#ifdef QUOTA
	ip->i_dquot = inoquota(ip);
#endif
	iupdat(ip, &time, &time, 1);

	/*
	 * Bump link count in parent directory
	 * to reflect work done below.  Should
	 * be done before reference is created
	 * so reparation is possible if we crash.
	 */
	dp->i_nlink++;
	dp->i_flag |= ICHG;
	iupdat(dp, &time, &time, 1);

	/*
	 * Initialize directory with "."
	 * and ".." from static template.
	 */
	dirtemplate = mastertemplate;
	dirtemplate.dot_ino = ip->i_number;
	dirtemplate.dotdot_ino = dp->i_number;
	u.u_error = rdwri(UIO_WRITE, ip, (caddr_t)&dirtemplate,
		sizeof (dirtemplate), (off_t)0, 1, (int *)0);
	if (u.u_error) {
		dp->i_nlink--;
		dp->i_flag |= ICHG;
		goto bad;
	}
I 87
	if (DIRBLKSIZ > ip->i_fs->fs_fsize)
		panic("mkdir: blksize");     /* XXX - should grow with bmap() */
	else
		ip->i_size = DIRBLKSIZ;
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
	u.u_error = direnter(ip, ndp);
E 82
	dp = NULL;
	if (u.u_error) {
D 82
		u.u_dirp = uap->name;
D 74
		dp = namei(uchar, LOOKUP, 0);
E 74
I 74
		dp = namei(uchar, LOOKUP | NOCACHE, 0);
E 82
I 82
		ndp->ni_nameiop = LOOKUP | NOCACHE;
		ndp->ni_segflg = UIO_USERSPACE;
		ndp->ni_dirp = uap->name;
		dp = namei(ndp);
E 82
E 74
		if (dp) {
			dp->i_nlink--;
			dp->i_flag |= ICHG;
		}
	}
bad:
	/*
	 * No need to do an explicit itrunc here,
	 * irele will do this for us because we set
	 * the link count to 0.
	 */
	if (u.u_error) {
		ip->i_nlink = 0;
		ip->i_flag |= ICHG;
	}
	if (dp)
		iput(dp);
	iput(ip);
E 102
I 102
D 140
	vattr_null(&vattr);
E 140
I 140
	VATTR_NULL(&vattr);
E 140
	vattr.va_type = VDIR;
D 109
	vattr.va_mode = (uap->dmode & 0777) &~ u.u_cmask;
E 109
I 109
D 143
	vattr.va_mode = (uap->dmode & 0777) &~ scp->sc_cmask;
E 143
I 143
D 157
	vattr.va_mode = (uap->dmode & 0777) &~ u.u_cmask;
E 157
I 157
D 222
	vattr.va_mode = (uap->dmode & 0777) &~ p->p_fd->fd_cmask;
E 222
I 222
D 250
	vattr.va_mode = (uap->mode & ACCESSPERMS) &~ p->p_fd->fd_cmask;
E 250
I 250
	vattr.va_mode = (SCARG(uap, mode) & ACCESSPERMS) &~ p->p_fd->fd_cmask;
E 250
E 222
I 171
D 174
	LEASE_CHECK(ndp->ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 171
E 157
E 143
E 109
D 162
	error = VOP_MKDIR(ndp, &vattr);
E 162
I 162
D 172
	error = VOP_MKDIR(ndp, &vattr, p);
E 172
I 172
	error = VOP_MKDIR(ndp->ni_dvp, &ndp->ni_vp, &ndp->ni_cnd, &vattr);
E 174
I 174
D 241
	LEASE_CHECK(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
	VOP_LEASE(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 241
	error = VOP_MKDIR(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, &vattr);
E 174
E 172
E 162
I 104
	if (!error)
D 174
		vput(ndp->ni_vp);
I 172
	CHECKCHECK("mkdir2");
E 174
I 174
		vput(nd.ni_vp);
I 175
	CHECKREFS("mkdir2");
E 175
E 174
E 172
E 104
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
}

/*
D 222
 * Rmdir system call.
E 222
I 222
 * Remove a directory file.
E 222
 */
I 198
D 250
struct rmdir_args {
D 222
	char	*name;
E 222
I 222
	char	*path;
E 222
};
E 250
E 198
D 109
rmdir()
E 109
I 109
D 143
rmdir(scp)
	register struct syscontext *scp;
E 109
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
rmdir(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	struct args {
E 143
		char	*name;
D 82
	};
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
E 82
D 102
	register struct inode *ip, *dp;
E 102
I 82
	register struct nameidata *ndp = &u.u_nd;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	struct rmdir_args *uap;
E 198
	int *retval;
E 250
I 250
	struct rmdir_args /* {
		syscallarg(char *) path;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_ABORTOP;
	USES_VOP_RMDIR;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
E 109
I 102
	register struct vnode *vp;
	int error;
I 160
	struct nameidata nd;
E 160
E 102
E 82

I 175
	CHECKPOINTREF;
E 175
I 172
D 174
	CHECKPOINT;
E 172
I 160
	ndp = &nd;
E 160
D 82
	ip = namei(uchar, DELETE | LOCKPARENT, 0);
E 82
I 82
D 102
	ndp->ni_nameiop = DELETE | LOCKPARENT;
E 102
I 102
	ndp->ni_nameiop = DELETE | LOCKPARENT | LOCKLEAF;
E 102
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->name;
D 102
	ip = namei(ndp);
E 82
	if (ip == NULL)
		return;
D 82
	dp = u.u_pdir;
E 82
I 82
	dp = ndp->ni_pdir;
E 82
	/*
	 * No rmdir "." please.
	 */
	if (dp == ip) {
		irele(dp);
		iput(ip);
		u.u_error = EINVAL;
		return;
	}
	if ((ip->i_mode&IFMT) != IFDIR) {
		u.u_error = ENOTDIR;
E 102
I 102
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, DELETE, LOCKPARENT | LOCKLEAF, UIO_USERSPACE, uap->name, p);
E 222
I 222
D 250
	NDINIT(&nd, DELETE, LOCKPARENT | LOCKLEAF, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, DELETE, LOCKPARENT | LOCKLEAF, UIO_USERSPACE,
	    SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
E 174
	if (vp->v_type != VDIR) {
		error = ENOTDIR;
E 102
		goto out;
	}
	/*
D 102
	 * Don't remove a mounted on directory.
E 102
I 102
	 * No rmdir "." please.
E 102
	 */
D 102
	if (ip->i_dev != dp->i_dev) {
		u.u_error = EBUSY;
E 102
I 102
D 174
	if (ndp->ni_dvp == vp) {
E 174
I 174
	if (nd.ni_dvp == vp) {
E 174
		error = EINVAL;
E 102
		goto out;
	}
	/*
D 102
	 * Verify the directory is empty (and valid).
	 * (Rmdir ".." won't be valid since
	 *  ".." will contain a reference to
	 *  the current directory and thus be
	 *  non-empty.)
E 102
I 102
D 163
	 * Don't unlink a mounted file.
E 163
I 163
	 * The root of a mounted filesystem cannot be deleted.
E 163
E 102
	 */
D 84
	if (ip->i_nlink != 2 || !dirempty(ip)) {
E 84
I 84
D 102
	if (ip->i_nlink != 2 || !dirempty(ip, dp->i_number)) {
E 84
		u.u_error = ENOTEMPTY;
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
	if (dirremove(ndp) == 0)
E 82
		goto out;
	dp->i_nlink--;
	dp->i_flag |= ICHG;
I 84
	cacheinval(dp);
E 84
	iput(dp);
	dp = NULL;
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
	itrunc(ip, (u_long)0);
I 83
	cacheinval(ip);
E 102
I 102
	if (vp->v_flag & VROOT)
		error = EBUSY;
E 102
E 83
out:
D 102
	if (dp)
		iput(dp);
	iput(ip);
E 102
I 102
D 144
	if (error)
		VOP_ABORTOP(ndp);
	else
E 144
I 144
	if (!error) {
I 171
D 174
		LEASE_CHECK(ndp->ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 174
I 174
D 241
		LEASE_CHECK(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
E 174
		LEASE_CHECK(vp, p, p->p_ucred, LEASE_WRITE);
E 241
I 241
		VOP_LEASE(nd.ni_dvp, p, p->p_ucred, LEASE_WRITE);
		VOP_LEASE(vp, p, p->p_ucred, LEASE_WRITE);
E 241
E 171
E 144
D 162
		error = VOP_RMDIR(ndp);
E 162
I 162
D 172
		error = VOP_RMDIR(ndp, p);
E 172
I 172
D 174
		error = VOP_RMDIR(ndp->ni_dvp, ndp->ni_vp, &ndp->ni_cnd);
E 174
I 174
		error = VOP_RMDIR(nd.ni_dvp, nd.ni_vp, &nd.ni_cnd);
E 174
E 172
E 162
I 144
	} else {
D 172
		VOP_ABORTOP(ndp);
E 172
I 172
D 174
		VOP_ABORTOP(ndp->ni_dvp, &ndp->ni_cnd);
E 172
D 146
		vput(ndp->ni_dvp);
E 146
I 146
		if (ndp->ni_dvp == vp)
			vrele(ndp->ni_dvp);
E 174
I 174
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
		if (nd.ni_dvp == vp)
			vrele(nd.ni_dvp);
E 174
		else
D 174
			vput(ndp->ni_dvp);
E 174
I 174
			vput(nd.ni_dvp);
E 174
E 146
		vput(vp);
	}
I 175
	CHECKREFS("rmdir");
E 175
I 172
D 174
	CHECKCHECK("rmdir");
E 174
E 172
E 144
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
}
I 194

#ifdef COMPAT_43
/*
 * Read a block of directory entries in a file system independent format.
 */
I 198
D 250
struct ogetdirentries_args {
	int	fd;
	char	*buf;
D 222
	unsigned count;
E 222
I 222
	u_int	count;
E 222
	long	*basep;
};
E 198
ogetdirentries(p, uap, retval)
E 250
I 250
int
compat_43_getdirentries(p, uap, retval)
E 250
	struct proc *p;
D 198
	register struct args {
		int	fd;
		char	*buf;
		unsigned count;
		long	*basep;
	} *uap;
E 198
I 198
D 250
	register struct ogetdirentries_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct compat_43_getdirentries_args /* {
		syscallarg(int) fd;
		syscallarg(char *) buf;
		syscallarg(u_int) count;
		syscallarg(long *) basep;
	} */ *uap;
	register_t *retval;
E 250
{
D 195
	USES_VOP_LOCK;
	USES_VOP_READDIR;
	USES_VOP_UNLOCK;
E 195
	register struct vnode *vp;
	struct file *fp;
	struct uio auio, kuio;
	struct iovec aiov, kiov;
	struct dirent *dp, *edp;
	caddr_t dirbuf;
D 236
	int error, readcnt;
E 236
I 236
	int error, eofflag, readcnt;
E 236
D 200
	off_t off;
E 200
I 200
	long loff;
E 200

D 250
	if (error = getvnode(p->p_fd, uap->fd, &fp))
E 250
I 250
	if (error = getvnode(p->p_fd, SCARG(uap, fd), &fp))
E 250
		return (error);
	if ((fp->f_flag & FREAD) == 0)
		return (EBADF);
	vp = (struct vnode *)fp->f_data;
I 236
unionread:
E 236
	if (vp->v_type != VDIR)
		return (EINVAL);
D 250
	aiov.iov_base = uap->buf;
	aiov.iov_len = uap->count;
E 250
I 250
	aiov.iov_base = SCARG(uap, buf);
	aiov.iov_len = SCARG(uap, count);
E 250
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_rw = UIO_READ;
	auio.uio_segflg = UIO_USERSPACE;
	auio.uio_procp = p;
D 250
	auio.uio_resid = uap->count;
E 250
I 250
	auio.uio_resid = SCARG(uap, count);
E 250
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
D 200
	auio.uio_offset = off = fp->f_offset;
E 200
I 200
	loff = auio.uio_offset = fp->f_offset;
E 200
#	if (BYTE_ORDER != LITTLE_ENDIAN)
D 203
		if (vp->v_mount->mnt_maxsymlinklen <= 0)
E 203
I 203
		if (vp->v_mount->mnt_maxsymlinklen <= 0) {
E 203
D 236
			error = VOP_READDIR(vp, &auio, fp->f_cred);
E 236
I 236
			error = VOP_READDIR(vp, &auio, fp->f_cred, &eofflag,
D 255
			    (u_long *)0, 0);
E 255
I 255
			    (int *)0, (u_long *)0);
E 255
E 236
D 203
		else
E 203
I 203
			fp->f_offset = auio.uio_offset;
		} else
E 203
#	endif
	{
		kuio = auio;
		kuio.uio_iov = &kiov;
		kuio.uio_segflg = UIO_SYSSPACE;
D 250
		kiov.iov_len = uap->count;
		MALLOC(dirbuf, caddr_t, uap->count, M_TEMP, M_WAITOK);
E 250
I 250
		kiov.iov_len = SCARG(uap, count);
		MALLOC(dirbuf, caddr_t, SCARG(uap, count), M_TEMP, M_WAITOK);
E 250
		kiov.iov_base = dirbuf;
D 236
		error = VOP_READDIR(vp, &kuio, fp->f_cred);
E 236
I 236
		error = VOP_READDIR(vp, &kuio, fp->f_cred, &eofflag,
D 255
			    (u_long *)0, 0);
E 255
I 255
			    (int *)0, (u_long *)0);
E 255
E 236
I 203
		fp->f_offset = kuio.uio_offset;
E 203
		if (error == 0) {
D 250
			readcnt = uap->count - kuio.uio_resid;
E 250
I 250
			readcnt = SCARG(uap, count) - kuio.uio_resid;
E 250
			edp = (struct dirent *)&dirbuf[readcnt];
			for (dp = (struct dirent *)dirbuf; dp < edp; ) {
D 200
				dp->d_type = 0;
E 200
#				if (BYTE_ORDER == LITTLE_ENDIAN)
D 200
					{ u_char tmp = dp->d_namlen;
E 200
I 200
					/*
D 201
					 * The expected dp->d_namlen field
					 * is in our dp->d_type.
E 201
I 201
					 * The expected low byte of
					 * dp->d_namlen is our dp->d_type.
					 * The high MBZ byte of dp->d_namlen
					 * is our dp->d_namlen.
E 201
					 */
E 200
D 201
					dp->d_namlen = dp->d_type;
E 201
I 201
					dp->d_type = dp->d_namlen;
					dp->d_namlen = 0;
#				else
					/*
					 * The dp->d_type is the high byte
					 * of the expected dp->d_namlen,
					 * so must be zero'ed.
					 */
					dp->d_type = 0;
E 201
D 200
					dp->d_type = tmp; }
E 200
#				endif
I 200
D 201
				/*
				 * The dp->d_type is the high byte
				 * of the expected dp->d_namlen,
				 * so must be zero'ed.
				 */
				dp->d_type = 0;
E 201
E 200
				if (dp->d_reclen > 0) {
					dp = (struct dirent *)
					    ((char *)dp + dp->d_reclen);
				} else {
					error = EIO;
					break;
				}
			}
			if (dp >= edp)
				error = uiomove(dirbuf, readcnt, &auio);
		}
		FREE(dirbuf, M_TEMP);
	}
D 203
	fp->f_offset = auio.uio_offset;
E 203
D 259
	VOP_UNLOCK(vp);
E 259
I 259
	VOP_UNLOCK(vp, 0, p);
E 259
	if (error)
		return (error);
I 236

#ifdef UNION
{
	extern int (**union_vnodeop_p)();
D 249
	extern struct vnode *union_lowervp __P((struct vnode *));
E 249
I 249
D 260
	extern struct vnode *union_dircache __P((struct vnode *));
E 260
I 260
	extern struct vnode *union_dircache __P((struct vnode*, struct proc*));
E 260
E 249

D 250
	if ((uap->count == auio.uio_resid) &&
E 250
I 250
	if ((SCARG(uap, count) == auio.uio_resid) &&
E 250
	    (vp->v_op == union_vnodeop_p)) {
		struct vnode *lvp;

D 249
		lvp = union_lowervp(vp);
E 249
I 249
D 260
		lvp = union_dircache(vp);
E 260
I 260
		lvp = union_dircache(vp, p);
E 260
E 249
		if (lvp != NULLVP) {
I 240
			struct vattr va;

			/*
			 * If the directory is opaque,
			 * then don't show lower entries
			 */
			error = VOP_GETATTR(vp, &va, fp->f_cred, p);
			if (va.va_flags & OPAQUE) {
D 249
				vrele(lvp);
E 249
I 249
				vput(lvp);
E 249
				lvp = NULL;
			}
		}
		
		if (lvp != NULLVP) {
E 240
D 249
			VOP_LOCK(lvp);
E 249
			error = VOP_OPEN(lvp, FREAD, fp->f_cred, p);
D 259
			VOP_UNLOCK(lvp);
E 259
I 259
D 260
			VOP_UNLOCK(lvp, 0, p);
E 259

E 260
			if (error) {
D 260
				vrele(lvp);
E 260
I 260
				vput(lvp);
E 260
				return (error);
			}
I 260
			VOP_UNLOCK(lvp, 0, p);
E 260
			fp->f_data = (caddr_t) lvp;
			fp->f_offset = 0;
			error = vn_close(vp, FREAD, fp->f_cred, p);
			if (error)
				return (error);
			vp = lvp;
			goto unionread;
		}
	}
}
#endif /* UNION */

D 250
	if ((uap->count == auio.uio_resid) &&
E 250
I 250
	if ((SCARG(uap, count) == auio.uio_resid) &&
E 250
	    (vp->v_flag & VROOT) &&
	    (vp->v_mount->mnt_flag & MNT_UNION)) {
		struct vnode *tvp = vp;
		vp = vp->v_mount->mnt_vnodecovered;
		VREF(vp);
		fp->f_data = (caddr_t) vp;
		fp->f_offset = 0;
		vrele(tvp);
		goto unionread;
	}
E 236
D 200
	error = copyout((caddr_t)&off, (caddr_t)uap->basep, sizeof(long));
E 200
I 200
D 250
	error = copyout((caddr_t)&loff, (caddr_t)uap->basep, sizeof(long));
E 200
	*retval = uap->count - auio.uio_resid;
E 250
I 250
	error = copyout((caddr_t)&loff, (caddr_t)SCARG(uap, basep),
	    sizeof(long));
	*retval = SCARG(uap, count) - auio.uio_resid;
E 250
	return (error);
}
D 236
#endif
E 236
I 236
#endif /* COMPAT_43 */
E 236
E 194

D 102
struct file *
getinode(fdes)
	int fdes;
E 102
I 102
/*
D 163
 * Read a block of directory entries in a file system independent format
E 163
I 163
 * Read a block of directory entries in a file system independent format.
E 163
 */
I 198
D 250
struct getdirentries_args {
	int	fd;
	char	*buf;
D 222
	unsigned count;
E 222
I 222
	u_int	count;
E 222
	long	*basep;
};
E 250
I 250
int
E 250
E 198
D 109
getdirentries()
E 109
I 109
D 143
getdirentries(scp)
	register struct syscontext *scp;
E 109
E 102
{
I 102
	register struct a {
E 143
I 143
getdirentries(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		int	fd;
		char	*buf;
		unsigned count;
		long	*basep;
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct getdirentries_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct getdirentries_args /* {
		syscallarg(int) fd;
		syscallarg(char *) buf;
		syscallarg(u_int) count;
		syscallarg(long *) basep;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_LOCK;
	USES_VOP_READDIR;
	USES_VOP_UNLOCK;
E 195
E 187
E 143
I 123
	register struct vnode *vp;
E 123
E 109
E 102
D 77
	register struct file *fp;
E 77
I 77
	struct file *fp;
I 102
	struct uio auio;
	struct iovec aiov;
I 103
D 200
	off_t off;
E 200
I 200
	long loff;
E 200
E 103
D 135
	int error;
E 135
I 135
D 193
	int error, eofflag;
E 193
I 193
D 236
	int error;
E 236
I 236
	int error, eofflag;
E 236
E 193
E 135
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
	}
E 77
	if (fp->f_type != DTYPE_INODE) {
		u.u_error = EINVAL;
D 77
		return (0);
E 77
I 77
		return ((struct file *)0);
E 77
	}
	return (fp);
E 102
I 102
D 109
	if (error = getvnode(uap->fd, &fp))
E 109
I 109
D 143
	if (error = getvnode(scp->sc_ofile, uap->fd, &fp))
E 143
I 143
D 157
	if (error = getvnode(u.u_ofile, uap->fd, &fp))
E 157
I 157
D 250
	if (error = getvnode(p->p_fd, uap->fd, &fp))
E 250
I 250
	if (error = getvnode(p->p_fd, SCARG(uap, fd), &fp))
E 250
E 157
E 143
E 109
D 160
		RETURN (error);
E 160
I 160
		return (error);
E 160
	if ((fp->f_flag & FREAD) == 0)
D 160
		RETURN (EBADF);
E 160
I 160
		return (EBADF);
E 160
I 123
	vp = (struct vnode *)fp->f_data;
I 202
unionread:
E 202
	if (vp->v_type != VDIR)
D 160
		RETURN (EINVAL);
E 160
I 160
		return (EINVAL);
E 160
E 123
D 250
	aiov.iov_base = uap->buf;
	aiov.iov_len = uap->count;
E 250
I 250
	aiov.iov_base = SCARG(uap, buf);
	aiov.iov_len = SCARG(uap, count);
E 250
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_rw = UIO_READ;
	auio.uio_segflg = UIO_USERSPACE;
I 162
	auio.uio_procp = p;
E 162
D 250
	auio.uio_resid = uap->count;
E 250
I 250
	auio.uio_resid = SCARG(uap, count);
E 250
I 103
D 123
	off = fp->f_offset;
E 103
	if (error = VOP_READDIR((struct vnode *)fp->f_data, &auio,
	    &(fp->f_offset), fp->f_cred))
E 123
I 123
D 259
	VOP_LOCK(vp);
E 259
I 259
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 259
D 200
	auio.uio_offset = off = fp->f_offset;
E 200
I 200
	loff = auio.uio_offset = fp->f_offset;
E 200
D 135
	error = VOP_READDIR(vp, &auio, fp->f_cred);
E 135
I 135
D 193
	error = VOP_READDIR(vp, &auio, fp->f_cred, &eofflag);
E 193
I 193
D 236
	error = VOP_READDIR(vp, &auio, fp->f_cred);
E 236
I 236
D 255
	error = VOP_READDIR(vp, &auio, fp->f_cred, &eofflag, (u_long *)0, 0);
E 255
I 255
	error = VOP_READDIR(vp, &auio, fp->f_cred, &eofflag,
			    (int *)0, (u_long *)0);
E 255
E 236
E 193
E 135
	fp->f_offset = auio.uio_offset;
D 259
	VOP_UNLOCK(vp);
E 259
I 259
	VOP_UNLOCK(vp, 0, p);
E 259
	if (error)
E 123
D 160
		RETURN (error);
E 160
I 160
		return (error);
I 231

#ifdef UNION
{
	extern int (**union_vnodeop_p)();
D 249
	extern struct vnode *union_lowervp __P((struct vnode *));
E 249
I 249
D 260
	extern struct vnode *union_dircache __P((struct vnode *));
E 260
I 260
	extern struct vnode *union_dircache __P((struct vnode*, struct proc*));
E 260
E 249

D 250
	if ((uap->count == auio.uio_resid) &&
E 250
I 250
	if ((SCARG(uap, count) == auio.uio_resid) &&
E 250
	    (vp->v_op == union_vnodeop_p)) {
D 235
		struct vnode *tvp = vp;
E 235
I 235
		struct vnode *lvp;
E 235

D 235
		vp = union_lowervp(vp);
		if (vp != NULLVP) {
			VOP_LOCK(vp);
			error = VOP_OPEN(vp, FREAD);
			VOP_UNLOCK(vp);
E 235
I 235
D 249
		lvp = union_lowervp(vp);
E 249
I 249
D 260
		lvp = union_dircache(vp);
E 260
I 260
		lvp = union_dircache(vp, p);
E 260
E 249
I 240
		if (lvp != NULLVP) {
			struct vattr va;

			/*
			 * If the directory is opaque,
			 * then don't show lower entries
			 */
			error = VOP_GETATTR(vp, &va, fp->f_cred, p);
			if (va.va_flags & OPAQUE) {
D 249
				vrele(lvp);
E 249
I 249
				vput(lvp);
E 249
				lvp = NULL;
			}
		}
D 260
		
E 260
I 260

E 260
E 240
		if (lvp != NULLVP) {
D 249
			VOP_LOCK(lvp);
E 249
D 236
			error = VOP_OPEN(lvp, FREAD);
E 236
I 236
			error = VOP_OPEN(lvp, FREAD, fp->f_cred, p);
E 236
D 259
			VOP_UNLOCK(lvp);
E 259
I 259
D 260
			VOP_UNLOCK(lvp, 0, p);
E 259
E 235

E 260
			if (error) {
D 235
				vrele(vp);
E 235
I 235
D 260
				vrele(lvp);
E 260
I 260
				vput(lvp);
E 260
E 235
				return (error);
			}
I 260
			VOP_UNLOCK(lvp, 0, p);
E 260
D 235
			fp->f_data = (caddr_t) vp;
E 235
I 235
			fp->f_data = (caddr_t) lvp;
E 235
			fp->f_offset = 0;
D 235
			error = vn_close(tvp, FREAD, fp->f_cred, p);
E 235
I 235
			error = vn_close(vp, FREAD, fp->f_cred, p);
E 235
			if (error)
				return (error);
I 235
			vp = lvp;
E 235
			goto unionread;
		}
	}
}
D 250
#endif
E 250
I 250
#endif /* UNION */
E 250

E 231
I 202
D 250
	if ((uap->count == auio.uio_resid) &&
E 250
I 250
	if ((SCARG(uap, count) == auio.uio_resid) &&
E 250
	    (vp->v_flag & VROOT) &&
	    (vp->v_mount->mnt_flag & MNT_UNION)) {
		struct vnode *tvp = vp;
		vp = vp->v_mount->mnt_vnodecovered;
		VREF(vp);
		fp->f_data = (caddr_t) vp;
		fp->f_offset = 0;
		vrele(tvp);
		goto unionread;
	}
E 202
E 160
D 103
	error = copyout((caddr_t)&fp->f_offset, (caddr_t)uap->basep,
E 103
I 103
D 123
	error = copyout((caddr_t)&off, (caddr_t)uap->basep,
E 103
		sizeof(long));
E 123
I 123
D 200
	error = copyout((caddr_t)&off, (caddr_t)uap->basep, sizeof(long));
E 200
I 200
D 250
	error = copyout((caddr_t)&loff, (caddr_t)uap->basep, sizeof(long));
E 200
E 123
D 109
	u.u_r.r_val1 = uap->count - auio.uio_resid;
E 109
I 109
D 143
	scp->sc_retval1 = uap->count - auio.uio_resid;
E 143
I 143
	*retval = uap->count - auio.uio_resid;
E 250
I 250
	error = copyout((caddr_t)&loff, (caddr_t)SCARG(uap, basep),
	    sizeof(long));
	*retval = SCARG(uap, count) - auio.uio_resid;
E 250
E 143
E 109
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
E 102
}

/*
D 163
 * mode mask for creation of files
E 163
I 163
 * Set the mode mask for creation of filesystem nodes.
E 163
 */
D 109
umask()
E 109
I 109
D 143
umask(scp)
	register struct syscontext *scp;
E 109
{
	register struct a {
E 143
I 143
D 198
mode_t
E 198
I 198
D 250
struct umask_args {
D 222
	int	mask;
E 222
I 222
	int	newmask;
E 222
};
mode_t				/* XXX */
E 250
I 250
int
E 250
E 198
umask(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	struct args {
E 143
		int	mask;
D 82
	} *uap;
E 82
I 82
D 109
	} *uap = (struct a *)u.u_ap;
E 109
I 109
D 143
	} *uap = (struct a *)scp->sc_ap;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	struct umask_args *uap;
E 198
	int *retval;
E 250
I 250
	struct umask_args /* {
		syscallarg(int) newmask;
	} */ *uap;
	register_t *retval;
E 250
{
I 157
D 222
	register struct filedesc *fdp = p->p_fd;
E 222
I 222
	register struct filedesc *fdp;
E 222
E 157
E 143
E 109
E 82

I 222
	fdp = p->p_fd;
E 222
D 82
	uap = (struct a *)u.u_ap;
E 82
D 109
	u.u_r.r_val1 = u.u_cmask;
	u.u_cmask = uap->mask & 07777;
E 109
I 109
D 143
	scp->sc_retval1 = scp->sc_cmask;
	scp->sc_cmask = uap->mask & 07777;
E 143
I 143
D 157
	*retval = u.u_cmask;
	u.u_cmask = uap->mask & 07777;
E 157
I 157
	*retval = fdp->fd_cmask;
D 222
	fdp->fd_cmask = uap->mask & 07777;
E 222
I 222
D 250
	fdp->fd_cmask = uap->newmask & ALLPERMS;
E 250
I 250
	fdp->fd_cmask = SCARG(uap, newmask) & ALLPERMS;
E 250
E 222
E 157
E 143
E 109
I 102
D 160
	RETURN (0);
E 160
I 160
	return (0);
E 160
}

I 122
/*
 * Void all references to file by ripping underlying filesystem
 * away from vnode.
 */
I 198
D 250
struct revoke_args {
D 222
	char	*fname;
E 222
I 222
	char	*path;
E 222
};
E 250
E 198
D 143
revoke(scp)
	register struct syscontext *scp;
{
	struct a {
E 143
I 143
/* ARGSUSED */
I 250
int
E 250
revoke(p, uap, retval)
D 157
	register struct proc *p;
E 157
I 157
	struct proc *p;
E 157
D 198
	register struct args {
E 143
		char	*fname;
I 142
D 147
		int	flags;
E 147
E 142
D 143
	} *uap = (struct a *)scp->sc_ap;
	register struct nameidata *ndp = &scp->sc_nd;
E 143
I 143
	} *uap;
E 198
I 198
D 250
	register struct revoke_args *uap;
E 198
	int *retval;
E 250
I 250
	register struct revoke_args /* {
		syscallarg(char *) path;
	} */ *uap;
	register_t *retval;
E 250
{
I 187
D 195
	USES_VOP_GETATTR;
E 195
E 187
D 160
	register struct nameidata *ndp = &u.u_nd;
E 160
I 160
D 174
	register struct nameidata *ndp;
E 174
E 160
E 143
	register struct vnode *vp;
	struct vattr vattr;
	int error;
I 160
	struct nameidata nd;
E 160

I 160
D 174
	ndp = &nd;
E 160
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 160
	if (error = namei(ndp))
		RETURN (error);
E 160
I 160
	if (error = namei(ndp, p))
E 174
I 174
D 222
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->fname, p);
E 222
I 222
D 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, uap->path, p);
E 250
I 250
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, SCARG(uap, path), p);
E 250
E 222
	if (error = namei(&nd))
E 174
		return (error);
E 160
D 174
	vp = ndp->ni_vp;
E 174
I 174
	vp = nd.ni_vp;
E 174
D 252
	if (vp->v_type != VCHR && vp->v_type != VBLK) {
		error = EINVAL;
		goto out;
	}
E 252
D 143
	if (error = VOP_GETATTR(vp, &vattr, scp->sc_cred))
E 143
I 143
D 160
	if (error = VOP_GETATTR(vp, &vattr, ndp->ni_cred))
E 160
I 160
D 162
	if (error = VOP_GETATTR(vp, &vattr, p->p_ucred))
E 162
I 162
	if (error = VOP_GETATTR(vp, &vattr, p->p_ucred, p))
E 162
E 160
E 143
		goto out;
D 143
	if (scp->sc_uid != vattr.va_uid ||
	    (error = suser(scp->sc_cred, &scp->sc_acflag)))
E 143
I 143
D 145
	if (ndp->ni_cred->cr_uid != vattr.va_uid ||
E 145
I 145
D 160
	if (ndp->ni_cred->cr_uid != vattr.va_uid &&
E 145
	    (error = suser(ndp->ni_cred, &u.u_acflag)))
E 160
I 160
	if (p->p_ucred->cr_uid != vattr.va_uid &&
	    (error = suser(p->p_ucred, &p->p_acflag)))
E 160
E 143
		goto out;
D 126
	if (vp->v_count > 1)
		vgone(vp);
E 126
I 126
D 130
	if (vp->v_count > 1 || (vp->v_flag & VALIASED))
E 130
I 130
	if (vp->v_usecount > 1 || (vp->v_flag & VALIASED))
E 130
D 252
		vgoneall(vp);
E 252
I 252
		VOP_REVOKE(vp, REVOKEALL);
E 252
E 126
out:
	vrele(vp);
D 160
	RETURN (error);
E 160
I 160
	return (error);
E 160
}

I 163
/*
 * Convert a user file descriptor to a kernel file entry.
 */
I 250
int
E 250
E 163
E 122
D 109
getvnode(fdes, fpp)
E 109
I 109
D 157
getvnode(ofile, fdes, fpp)
	struct file *ofile[];
E 157
I 157
D 222
getvnode(fdp, fdes, fpp)
E 222
I 222
getvnode(fdp, fd, fpp)
E 222
	struct filedesc *fdp;
E 157
E 109
	struct file **fpp;
D 222
	int fdes;
E 222
I 222
	int fd;
E 222
{
	struct file *fp;

D 109
	if ((unsigned)fdes >= NOFILE || (fp = u.u_ofile[fdes]) == NULL)
E 109
I 109
D 157
	if ((unsigned)fdes >= NOFILE || (fp = ofile[fdes]) == NULL)
E 157
I 157
D 160
	if ((unsigned)fdes >= fdp->fd_maxfiles ||
E 160
I 160
D 222
	if ((unsigned)fdes >= fdp->fd_nfiles ||
E 160
D 161
	    (fp = OFILE(fdp, fdes)) == NULL)
E 161
I 161
	    (fp = fdp->fd_ofiles[fdes]) == NULL)
E 222
I 222
	if ((u_int)fd >= fdp->fd_nfiles ||
	    (fp = fdp->fd_ofiles[fd]) == NULL)
E 222
E 161
E 157
E 109
		return (EBADF);
	if (fp->f_type != DTYPE_VNODE)
		return (EINVAL);
	*fpp = fp;
	return (0);
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
E 1
