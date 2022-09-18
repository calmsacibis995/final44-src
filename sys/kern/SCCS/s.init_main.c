h48318
s 00001/00001/00385
d D 8.16 95/05/14 00:18:00 mckusick 169 168
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK
e
s 00001/00002/00385
d D 8.15 95/05/10 13:25:09 mckusick 168 167
c replace mountroot with function vfs_mountroot
e
s 00001/00000/00386
d D 8.14 95/05/10 09:54:40 mckusick 167 166
c set MNT_ROOTFS immediately after doing mountroot rather than in filesystems
e
s 00001/00001/00385
d D 8.13 95/05/09 16:59:19 mckusick 166 165
c change mountlist to CIRCLEQ so we can do unmountall (from mycroft)
e
s 00018/00011/00368
d D 8.12 95/05/01 16:58:26 mckusick 165 164
c cleanups of init argument setup (from mycroft)
e
s 00017/00010/00362
d D 8.11 95/02/14 10:24:20 cgd 164 163
c new argument passing conventions.  minor type size cleanup.
e
s 00011/00007/00361
d D 8.10 94/08/22 10:19:49 mckusick 163 162
c use new queue.h data structures
e
s 00005/00000/00363
d D 8.9 94/01/21 17:17:30 bostic 162 161
c add USL's copyright notice
e
s 00001/00001/00362
d D 8.8 93/12/30 16:21:43 mckusick 161 160
c new queue structure
e
s 00003/00004/00360
d D 8.7 93/12/13 12:10:38 mckusick 160 159
c eliminate duplicate code
e
s 00012/00014/00352
d D 8.6 93/12/10 18:01:29 mckusick 159 158
c add cpu_set_init_frame to initialize init's syscall frame
e
s 00002/00000/00364
d D 8.5 93/11/11 14:17:45 hibler 158 157
c initialized initproc in start_init
e
s 00016/00021/00348
d D 8.4 93/09/23 15:24:56 bostic 157 156
c changes for 4.4BSD-Lite requested by USL
e
s 00113/00041/00256
d D 8.3 93/09/21 07:36:31 mckusick 156 155
c changes for 4.4BSD-Lite requested by USL
c NOT SEMANTIC SUGAR -- change to exec init, not hand-craft it
e
s 00039/00055/00258
d D 8.2 93/09/05 09:35:07 bostic 155 154
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00311
d D 8.1 93/06/10 21:56:40 bostic 154 153
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00311
d D 7.60 93/06/01 18:11:02 mckusick 153 152
c update copyright on bootup
e
s 00004/00000/00309
d D 7.59 93/04/28 19:50:30 mckusick 152 151
c set RLIMIT_RSS and RLIMIT_MEMLOCK maximums to all available user memory;
c set RLIMIT_MEMLOCK initial limit to 1/3 of available user memory
e
s 00014/00023/00295
d D 7.58 93/04/17 18:52:35 torek 151 150
c use pseudo-device initialization table instead of #if; minor KNF
e
s 00001/00001/00317
d D 7.57 92/12/01 13:41:27 mckusick 150 149
c RLIMIT_OFILE => RLIMIT_NOFILE for compatibility with other UNIX's
e
s 00019/00019/00299
d D 7.56 92/12/01 13:40:24 mckusick 149 148
c new include structure
e
s 00000/00004/00318
d D 7.55 92/09/22 22:04:09 mckusick 148 147
c rootvp and swapvp now done in ?fs_mountroot
e
s 00004/00002/00318
d D 7.54 92/07/31 10:31:58 mckusick 147 146
c update from torek to fix running time of swapper
e
s 00007/00001/00313
d D 7.53 92/07/19 23:46:39 mckusick 146 145
c set up and initialize usrinfo data structures used to count processes
e
s 00005/00000/00309
d D 7.52 92/07/19 19:10:05 mckusick 145 144
c add copyright notice for HP and Motrola when using hpux_float.o
e
s 00001/00002/00308
d D 7.51 92/07/11 06:54:47 torek 144 143
c fix swapper run stats
e
s 00013/00013/00297
d D 7.50 92/07/08 00:48:10 torek 143 142
c consolidate clock startup; volatile poison; lint
e
s 00000/00001/00310
d D 7.49 92/07/03 01:37:05 mckusick 142 141
c delete USES
e
s 00001/00000/00310
d D 7.48 92/05/14 17:31:29 heideman 141 132
c vnode interface conversion
e
s 00001/00000/00310
d R 7.48 92/05/14 15:45:21 heideman 140 132
c vnode interface conversion
e
s 00001/00000/00310
d R 7.48 92/05/14 14:50:33 heideman 139 132
c vnode interface conversion
e
s 00001/00000/00310
d R 7.48 92/05/14 12:54:36 heideman 138 132
c vnode interface conversion
e
s 00001/00000/00310
d R 7.48 92/05/14 11:51:59 heideman 137 132
c vnode interface conversion
e
s 00001/00000/00310
d R 7.48 92/05/14 10:32:11 heideman 136 132
c vnode interface conversion
e
s 00001/00000/00310
d R 7.48 92/05/13 23:10:55 heideman 135 132
c vnode interface conversion
e
s 00001/00000/00310
d R 7.48 92/05/13 18:57:05 heideman 134 132
c vnode interface conversion
e
s 00001/00000/00310
d R 7.48 92/05/13 18:29:07 heideman 133 132
c vnode interface conversion
e
s 00001/00000/00309
d D 7.47 92/03/18 18:05:41 sklower 132 131
c define boottime
e
s 00006/00004/00303
d D 7.46 92/02/14 18:01:00 torek 131 130
c have to use VM_MIN_ADDRESS instead of assuming binaries start at zero
e
s 00015/00012/00292
d D 7.45 92/02/14 17:59:55 bostic 130 129
c style police; pass init -- to indicate no arguments
e
s 00001/00001/00303
d D 7.44 91/12/19 12:27:47 mckusick 129 128
c add mono_time for NFS leases
e
s 00000/00001/00304
d D 7.43 91/11/19 23:48:55 torek 128 127
c purge seg.h
e
s 00001/00001/00304
d D 7.42 91/11/01 16:34:23 bostic 127 126
c LFS version 1; move ufs down a level
e
s 00001/00000/00304
d D 7.41 91/05/15 21:02:11 mckusick 126 125
c need to set reference count on cred0
e
s 00002/00003/00302
d D 7.40 91/05/09 18:27:41 karels 125 124
c startup => cpu_startup, remove unused arg
e
s 00011/00043/00294
d D 7.39 91/05/07 20:11:40 karels 124 123
c print copyright on startup (before msgbuf is init'ed!);
c shuffle variable definitions that didn't use to be externed in systm.h;
c move bufinit to vfs_bio.c; rm argdev
e
s 00004/00004/00333
d D 7.38 91/05/03 12:20:47 karels 123 122
c p_addr is now (struct user *); stack isn't necessarily last in address space
e
s 00003/00002/00334
d D 7.37 91/04/04 14:53:55 karels 122 121
c it's ours
e
s 00006/00005/00330
d D 7.36 91/03/31 15:04:49 karels 121 120
c move initflags from locore/icode to static in main
e
s 00020/00020/00315
d D 7.35 91/03/25 12:29:06 karels 120 119
c new filedesc structure; point p_stats, p_sigacts at p_addr instead of u.
e
s 00149/00188/00186
d D 7.34 91/03/17 15:42:07 karels 119 118
c more-or-less working with new proc & user structs
e
s 00008/00010/00366
d D 7.33 91/01/18 17:36:39 william 118 117
c amended initflag initialization, now done for all processor types
e
s 00016/00006/00360
d D 7.32 91/01/10 23:43:44 mckusick 117 116
c add dynamically allocated file descriptors
e
s 00017/00001/00349
d D 7.31 91/01/08 18:13:34 william 116 115
c added code for 386 to pass bootflags to init via argv[]
c  also moved enablertclock() due to obscure ISA floppy problem.
e
s 00033/00029/00317
d D 7.30 90/12/05 16:32:26 mckusick 115 114
c update for new VM
e
s 00000/00001/00346
d D 7.29 90/06/22 17:17:29 mckusick 114 113
c no more u.u_ap
e
s 00001/00003/00346
d D 7.28 90/05/24 12:53:14 marc 113 112
c set swapper start time in right place
e
s 00001/00001/00348
d D 7.27 90/05/15 22:05:05 bostic 112 111
c rename size_t to segsz_t for ANSI C
e
s 00005/00002/00344
d D 7.26 90/05/10 17:45:36 mckusick 111 110
c merge in support for hp300 from Utah
e
s 00001/00001/00345
d D 7.25 90/05/10 12:59:45 mckusick 110 109
c get rid of spurious #define in user.h
e
s 00001/00000/00345
d D 7.24 90/05/01 11:20:05 marc 109 108
c initialize u_start
e
s 00000/00004/00345
d D 7.23 90/04/27 09:54:32 mckusick 108 107
c no longer have per user quota structures
e
s 00002/00000/00347
d D 7.22 90/04/05 14:47:23 marc 107 106
c swapper and pagedaemon have names set in p_comm.
e
s 00003/00001/00344
d D 7.21 89/11/20 18:16:45 marc 106 105
c controlling terminal is a vnode
e
s 00002/00013/00343
d D 7.20 89/11/02 14:52:41 mckusick 105 104
c Keith Bostic says not so quick with the copyright notice
e
s 00003/00009/00353
d D 7.19 89/10/29 23:07:29 mckusick 104 103
c file system initialization is now all done by vfsinit
e
s 00001/00000/00361
d D 7.18 89/10/24 18:41:30 mckusick 103 102
c initialize systemwide vnode table
e
s 00001/00000/00360
d D 7.17 89/09/03 18:12:20 karels 102 101
c all zeros isn't good enough for signal initialization now
e
s 00003/00000/00357
d D 7.16 89/09/01 15:41:44 mckusick 101 100
c add memory filesystem initialization
e
s 00004/00000/00353
d D 7.15 89/08/26 12:56:36 mckusick 100 99
c initialize other fields in the buffers
e
s 00001/00001/00352
d D 7.14 89/06/27 19:26:32 mckusick 99 98
c update reference counts on vnodes using VREF
e
s 00001/00005/00352
d D 7.13 89/06/08 13:40:21 mckusick 98 97
c gather initialization code for nameidata into ndinit()
e
s 00004/00001/00353
d D 7.12 89/06/07 16:45:49 mckusick 97 96
c use uio structure in nameidata rather than constructing a new one
e
s 00001/00002/00353
d D 7.11 89/05/09 16:46:47 mckusick 96 95
c lint; new naming convention
e
s 00000/00004/00355
d D 7.10 89/05/01 23:39:04 mckusick 95 93
i 94
c integrate back branch -7.5.1.1
e
s 00055/00028/00274
d D 7.5.1.1 89/05/01 23:37:56 mckusick 94 89
c merge in vnode changes
e
s 00004/00000/00324
d D 7.9 89/05/01 23:01:25 marc 93 92
c init KTRACE variables
e
s 00004/00004/00320
d D 7.8 89/04/25 14:47:14 mckusick 92 91
c ../machine => machine
e
s 00018/00000/00306
d D 7.7 88/10/18 15:14:43 marc 91 90
c posix style job control - new process groups
e
s 00005/00001/00301
d D 7.6 88/05/26 09:01:30 karels 90 89
c lint
e
s 00002/00013/00300
d D 7.5 87/02/26 18:09:36 karels 89 88
c mv more tahoe stuff to machdep; clk_enable was dup;
c allow root to be mounted readonly
e
s 00021/00018/00292
d D 7.4 87/02/19 17:28:47 karels 88 87
c rearrange initialization of buffers so can be used during configure
e
s 00002/00001/00308
d D 7.3 86/12/06 22:33:55 sam 87 86
c hide tahoe-ism in enablertclock(); call startrtclock so tahoe can set interval timer
e
s 00015/00002/00294
d D 7.2 86/11/03 11:59:26 karels 86 85
c merge in tahoe support
e
s 00001/00001/00295
d D 7.1 86/06/05 00:00:38 mckusick 85 84
c 4.3BSD release version
e
s 00001/00001/00295
d D 6.15 86/02/23 23:08:32 karels 84 83
c lint
e
s 00004/00000/00292
d D 6.14 86/02/11 17:11:15 karels 83 82
c slattach
e
s 00001/00000/00291
d D 6.13 85/11/09 16:37:07 karels 82 81
c keep text free list, cache all texts as sticky
e
s 00000/00006/00291
d D 6.12 85/09/16 20:50:56 karels 81 80
c INET || BBNNET; ctlinput now takes sockaddr as arg
e
s 00009/00002/00288
d D 6.11 85/06/18 18:45:51 karels 80 78
c adjust maxpgio for number of swap devices after counting them,
c using something between what was used and what was attempted in binit
e
s 00006/00005/00285
d R 6.11 85/06/17 22:56:55 karels 79 78
c must calculate maxpgio after binit; nswdev * maxpgio in binit
c is unused
e
s 00007/00001/00283
d D 6.10 85/06/08 14:33:46 mckusick 78 77
c Add copyright
e
s 00003/00005/00281
d D 6.9 85/05/27 19:54:51 karels 77 76
c implement high-water mark on file descriptors in use;
c cleanup old comments
e
s 00007/00007/00279
d D 6.8 85/03/08 15:24:29 mckusick 76 75
c u.u_ap now set up once in process 0; limits are initialized in vminit()
e
s 00001/00006/00285
d D 6.7 85/03/03 16:20:31 mckusick 75 74
c setup of paging constants and p_maxrss is now done in the paging daemon.
e
s 00019/00019/00272
d D 6.6 84/08/29 20:18:22 bloom 74 73
c Change to includes.  no more ../h
e
s 00017/00023/00274
d D 6.5 84/08/01 11:42:54 karels 73 70
c reverse order of process creation, so we don't have to screw with
c mpid and proc order; move default umask into global so can be patched
e
s 00017/00023/00274
d R 6.5 84/08/01 11:17:10 karels 72 70
c reorder initial process creation so we don't have to screw with mpid
c and proc order; put default umask in global for patching
e
s 00017/00023/00274
d R 6.5 84/07/31 17:57:54 karels 71 70
c start init before pagedaemon; put umask in global for patching
e
s 00009/00000/00288
d D 6.4 84/07/08 16:11:58 mckusick 70 69
c rework namei interface to eliminate global variables
e
s 00007/00002/00281
d D 6.3 84/05/22 11:44:02 karels 69 68
c linked lists of active, zombie and free procs; avoid linear proc
c searches wherever possible
e
s 00001/00000/00282
d D 6.2 84/01/03 23:41:43 mckusick 68 67
c add system wide cacheing of path names in namei() (from kre)
e
s 00000/00000/00282
d D 6.1 83/07/29 06:31:46 sam 67 66
c 4.2 distribution
e
s 00000/00027/00282
d D 4.53 83/07/01 02:17:25 sam 66 65
c purge #if sun's
e
s 00002/00001/00307
d D 4.52 83/05/30 17:44:37 sam 65 64
c cleanup
e
s 00000/00018/00308
d D 4.51 83/05/21 15:28:58 sam 64 63
c purge mush
e
s 00007/00003/00319
d D 4.50 83/05/18 01:57:55 sam 63 62
c changes from sun to do swapping on variable sized devices
e
s 00000/00006/00322
d D 4.49 83/04/04 06:12:21 sam 62 61
c no more NOPAGING (yeah)
e
s 00001/00001/00327
d D 4.48 83/03/31 13:46:30 sam 61 60
c add NOGROUP identifier; add groupmember function; tighten group 
c lookup loop to stop at first NOGROUP entry
e
s 00003/00000/00325
d D 4.47 83/03/01 13:28:35 mckusick 60 59
c add startup for profiling clock
e
s 00002/00005/00323
d D 4.46 83/01/23 17:42:49 sam 59 58
c this screws up make depend otherwise
e
s 00007/00001/00321
d D 4.45 83/01/16 15:48:46 mckusick 58 57
c more intelligent buffer pool page allocation
e
s 00018/00007/00304
d D 4.44 82/12/17 11:42:36 sam 57 56
c sun merge
e
s 00013/00003/00298
d D 4.43 82/11/13 22:49:09 sam 56 55
c merge of 4.1b and 4.1c
e
s 00003/00004/00298
d D 4.42 82/11/02 23:38:47 root 55 54
c remove crud
e
s 00030/00002/00272
d D 4.41 82/10/31 14:40:48 root 54 53
c combine with 68k
e
s 00001/00010/00273
d D 4.40 82/10/17 11:28:40 root 53 52
c compute nchrdev nblkdev
e
s 00004/00004/00279
d D 4.39 82/10/10 15:01:56 root 52 51
c split header files over to vax directories
e
s 00003/00001/00280
d D 4.38 82/09/12 02:55:10 root 51 50
c fix limits initialization
e
s 00009/00001/00272
d D 4.37 82/09/06 22:38:20 root 50 49
c more work on timer stuff
e
s 00010/00019/00263
d D 4.36 82/09/04 09:02:10 root 49 48
c limits and clock startup new style
e
s 00002/00000/00280
d D 4.35 82/08/24 15:04:10 root 48 47
c new groups stuff
e
s 00001/00001/00279
d D 4.34 82/08/22 20:29:12 root 47 46
c get rid of some lint
e
s 00021/00000/00259
d D 4.33 82/07/22 13:12:23 kre 46 45
c disc quotas / mush
e
s 00003/00000/00256
d D 4.32 82/07/15 20:07:18 root 45 44
c profiling stuff
e
s 00014/00057/00242
d D 4.31 82/06/14 23:00:02 root 44 43
c fixes to interactions of new fs and buffer cache with partial blocks
c including removal of superblocks from cache and refined readahead and
c brealloc routine
e
s 00014/00000/00285
d D 4.30 82/05/31 17:51:46 mckusick 43 42
c fix time initialization; move bhinit() from bio.c to main.c
e
s 00032/00018/00253
d D 4.29 82/04/19 19:36:05 mckusic 42 41
c merge into new file system
e
s 00001/00001/00270
d D 4.28 82/03/28 14:26:48 sam 41 40
c move pfinit after ifinit so ip can init ifinet (see ip_init)
e
s 00000/00007/00271
d D 4.27 82/03/14 14:11:51 root 40 39
c flush BBN code
e
s 00001/00001/00277
d D 4.26 82/03/11 23:44:33 wnj 39 38
c fix for shannon
e
s 00003/00003/00275
d D 4.25 82/02/15 13:28:31 wnj 38 37
c new multiple-group stuff
e
s 00005/00004/00273
d D 4.24 81/12/09 20:53:24 wnj 37 36
c ifinit and loattach
e
s 00004/00000/00273
d D 4.23 81/12/03 17:27:14 wnj 36 35
c cleanup
e
s 00000/00001/00273
d D 4.22 81/11/18 15:44:59 wnj 35 34
c more cleanup
e
s 00000/00000/00274
d D 4.21 81/11/16 14:20:42 wnj 34 33
c lint
e
s 00001/00001/00273
d D 4.20 81/11/14 16:43:32 wnj 33 32
c before header overlay
e
s 00009/00004/00265
d D 4.19 81/11/08 16:53:40 wnj 32 31
c add mbinit, prinit, remove ptinit
e
s 00001/00001/00268
d D 4.18 81/08/24 12:37:39 root 31 30
c change netinit() to netmain()
e
s 00002/00000/00267
d D 4.17 81/08/13 11:06:29 ecc 30 29
c interleave swap fix
e
s 00007/00001/00260
d D 4.16 81/05/12 17:18:45 root 29 28
c add tcp/ip
e
s 00001/00000/00260
d D 4.15 81/04/28 02:53:51 root 28 27
c port init call
e
s 00005/00002/00255
d D 4.14 81/04/23 02:59:30 wnj 27 26
c call setupclock
e
s 00001/00000/00256
d D 4.13 81/04/13 20:34:16 root 26 25
c maxrss stuff
e
s 00001/00001/00255
d D 4.12 81/03/09 01:47:38 wnj 25 24
c lint and a few minor fixed
e
s 00004/00000/00252
d D 4.11 81/03/03 11:06:40 wnj 24 23
c put root name in s_fsmnt
e
s 00005/00017/00247
d D 4.10 81/02/27 17:44:57 wnj 23 22
c dynamic allocation kernel
e
s 00008/00007/00256
d D 4.9 81/02/27 02:39:32 wnj 22 21
c before compiling dynamic version
e
s 00023/00000/00240
d D 4.8 81/02/26 23:57:32 wnj 21 20
c add cinit
e
s 00000/00002/00240
d D 4.7 81/02/26 04:24:48 wnj 20 19
c FASTVAX xxx or -> UNFAST
e
s 00010/00008/00232
d D 4.6 81/02/16 20:48:52 wnj 19 18
c red zone for kernel stack
e
s 00002/00008/00238
d D 4.5 81/02/15 12:21:12 kre 18 17
c get rid of d_tab
e
s 00000/00001/00246
d D 4.4 81/02/08 18:34:44 wnj 17 16
c first working autoconf version
e
s 00013/00011/00234
d D 4.3 81/01/31 23:24:15 wnj 16 15
c changes for array of buffer queues
e
s 00001/00001/00244
d D 4.2 80/11/09 23:34:52 bill 15 14
c function results (void)'ed for minor lint
e
s 00000/00000/00245
d D 4.1 80/11/09 17:32:09 bill 14 13
c minor fixups to restart stuff; version 4.1 for distrib
e
s 00001/00001/00244
d D 3.13 80/09/16 17:10:51 bill 13 12
c s/limit/vlimit
e
s 00013/00009/00232
d D 3.12 80/09/14 13:09:09 bill 12 11
c fixup limit initialization (1/2M stack, max possible data) and clock init
e
s 00003/00002/00238
d D 3.11 80/08/27 08:36:24 bill 11 10
c buffers allocated in sysmap
e
s 00000/00000/00240
d D 3.10 80/07/16 13:44:07 bill 10 9
c limit code
e
s 00001/00000/00239
d D 3.9 80/07/12 19:17:12 bill 9 8
c include vlimit.h for INFINITY
e
s 00003/00000/00236
d D 3.8 80/07/12 17:45:54 bill 8 7
c initialize limits
e
s 00002/00000/00234
d D 3.7 80/07/06 11:20:39 bill 7 6
c first cached version
e
s 00014/00000/00220
d D 3.6 80/06/24 19:28:31 bill 6 5
c no swplo
e
s 00001/00001/00219
d D 3.5 80/06/07 02:46:07 bill 5 4
c %H%->%G%
e
s 00001/00001/00219
d D 3.4 80/05/08 10:29:39 bill 4 3
c VOID=>void
e
s 00001/00001/00219
d D 3.3 80/04/30 17:17:04 bill 3 2
c get rid of BSLOP
e
s 00001/00000/00219
d D 3.2 80/04/13 12:36:13 bill 2 1
c call bhinit
e
s 00219/00000/00000
d D 3.1 80/04/09 16:03:25 bill 1 0
c date and time created 80/04/09 16:03:25 by bill
e
u
U
f b 
t
T
I 1
D 5
/*	%M%	%I%	%H%	*/
E 5
I 5
D 25
/*	%M%	%I%	%G%	*/
E 25
I 25
D 78
/*	%M%	%I%	%E%	*/
E 78
I 78
/*
D 85
 * Copyright (c) 1982 Regents of the University of California.
E 85
I 85
D 94
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 85
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 94
I 94
D 119
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 119
I 119
D 154
 * Copyright (c) 1982, 1986, 1989, 1991 Regents of the University of California.
E 119
D 105
 * All rights reserved.
E 94
 *
I 94
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
E 105
I 105
D 122
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 122
I 122
 * All rights reserved.
E 154
I 154
 * Copyright (c) 1982, 1986, 1989, 1991, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
I 162
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 162
E 154
 *
 * %sccs.include.redist.c%
E 122
E 105
 *
E 94
 *	%W% (Berkeley) %G%
 */
E 78
E 25
E 5

I 57
D 92
D 94
#include "../machine/pte.h"

E 94
E 92
E 57
D 74
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
I 49
#include "../h/kernel.h"
E 49
D 42
#include "../h/filsys.h"
E 42
I 42
#include "../h/fs.h"
E 42
#include "../h/mount.h"
#include "../h/map.h"
#include "../h/proc.h"
#include "../h/inode.h"
#include "../h/seg.h"
#include "../h/conf.h"
#include "../h/buf.h"
D 52
#include "../h/mtpr.h"
E 52
D 57
#include "../h/pte.h"
E 57
D 49
#include "../h/clock.h"
E 49
#include "../h/vm.h"
#include "../h/cmap.h"
I 7
#include "../h/text.h"
I 9
D 13
#include "../h/limit.h"
E 13
I 13
D 49
#include "../h/vlimit.h"
E 49
I 23
#include "../h/clist.h"
E 74
I 74
D 149
#include "param.h"
D 120
#include "systm.h"
D 94
#include "dir.h"
E 94
#include "user.h"
E 120
I 117
#include "filedesc.h"
E 117
#include "kernel.h"
D 94
#include "fs.h"
E 94
#include "mount.h"
#include "map.h"
#include "proc.h"
I 120
#include "resourcevar.h"
#include "signalvar.h"
#include "systm.h"
E 120
D 94
#include "inode.h"
E 94
I 94
#include "vnode.h"
E 94
D 128
#include "seg.h"
E 128
#include "conf.h"
#include "buf.h"
D 115
#include "vm.h"
#include "cmap.h"
#include "text.h"
E 115
#include "clist.h"
I 91
D 146
#include "malloc.h"
E 146
E 91
E 74
I 32
D 81
#ifdef INET
E 81
D 35
#include "../h/protocol.h"
E 35
D 74
#include "../h/protosw.h"
E 74
I 74
#include "protosw.h"
E 74
D 81
#endif
E 81
I 46
D 74
#include "../h/quota.h"
E 74
I 74
D 94
#include "quota.h"
E 94
I 89
#include "reboot.h"
I 120
#include "user.h"
E 149
I 149
#include <sys/param.h>
#include <sys/filedesc.h>
I 156
#include <sys/errno.h>
#include <sys/exec.h>
E 156
#include <sys/kernel.h>
#include <sys/mount.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/resourcevar.h>
#include <sys/signalvar.h>
#include <sys/systm.h>
#include <sys/vnode.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/clist.h>
I 151
#include <sys/device.h>
E 151
#include <sys/protosw.h>
#include <sys/reboot.h>
#include <sys/user.h>
I 164
#include <sys/syscallargs.h>
E 164
E 149

E 120
E 89
E 74
E 46
E 32
E 23
E 13
E 9
E 7
D 59

I 57
#ifdef sun
#include "../sun/reg.h"
#include "../sun/cpu.h"
#endif
E 59
I 59
D 92
D 94
#include "../machine/reg.h"
#include "../machine/cpu.h"
E 94
I 94
D 119
#include "../ufs/quota.h"
E 119
I 119
D 127
#include "ufs/quota.h"
E 127
I 127
D 149
#include "ufs/ufs/quota.h"
E 149
I 149
#include <ufs/ufs/quota.h>
E 149
E 127
E 119
E 94
E 92
I 92

D 115
#include "machine/pte.h"
E 115
D 119
#include "machine/reg.h"
E 119
D 149
#include "machine/cpu.h"
E 149
I 149
#include <machine/cpu.h>
E 149
E 92
E 59

I 115
D 119
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
E 119
I 119
D 149
#include "vm/vm.h"
E 149
I 149
#include <vm/vm.h>
E 149
D 120
#include "vm/vm_param.h"
#include "vm/vm_map.h"
E 120
E 119

I 145
#ifdef HPFPLIB
E 145
I 124
char	copyright[] =
I 145
D 153
"Copyright (c) 1982,1986,1989,1991 The Regents of the University of California.\nCopyright (c) 1992 Hewlett-Packard Company\nCopyright (c) 1992 Motorola Inc.\nAll rights reserved.\n\n";
E 153
I 153
"Copyright (c) 1982, 1986, 1989, 1991, 1993\n\tThe Regents of the University of California.\nCopyright (c) 1992 Hewlett-Packard Company\nCopyright (c) 1992 Motorola Inc.\nAll rights reserved.\n\n";
E 153
#else
char	copyright[] =
E 145
D 153
"Copyright (c) 1982,1986,1989,1991 The Regents of the University of California.\nAll rights reserved.\n\n";
E 153
I 153
"Copyright (c) 1982, 1986, 1989, 1991, 1993\n\tThe Regents of the University of California.  All rights reserved.\n\n";
E 153
I 145
#endif
E 145

E 124
I 119
D 155
/*
 * Components of process 0;
 * never freed.
 */
E 155
I 155
/* Components of the first process -- never freed. */
E 155
struct	session session0;
struct	pgrp pgrp0;
struct	proc proc0;
struct	pcred cred0;
D 120
struct	filedesc filedesc0;
struct	file *fd0[NOEXTENT];
char	fdflags0[NOEXTENT];
E 120
I 120
struct	filedesc0 filedesc0;
E 120
struct	plimit limit0;
struct	vmspace vmspace0;
I 120
struct	proc *curproc = &proc0;
E 120
struct	proc *initproc, *pageproc;

E 119
E 115
I 94
D 95
#include "machine/pte.h"
#include "machine/reg.h"
#include "machine/cpu.h"

E 95
E 94
E 57
I 52
D 73
extern	struct user u;		/* have to declare it somewhere! */
E 73
I 73
int	cmask = CMASK;
I 115
D 123
extern	caddr_t proc0paddr;
E 123
I 123
extern	struct user *proc0paddr;
E 123
E 115
I 94
D 155
extern	int (*mountroot)();
E 155
I 116
D 118
#if defined(i386)
E 118
D 119
extern	char	initflags[];
E 119
I 119
D 121
extern	char initflags[];
E 121
E 119
D 118
#endif
E 118

I 124
struct	vnode *rootvp, *swapdev_vp;
int	boothowto;
I 132
struct	timeval boottime;
I 143
struct	timeval runtime;
E 143
E 132

I 156
D 159
static void start_init __P((struct proc *p, int *regs));
E 159
I 159
static void start_init __P((struct proc *p, void *framep));
E 159

E 156
E 124
E 116
E 94
E 73
E 52
/*
D 119
 * Initialization code.
 * Called from cold start routine as
 * soon as a stack and segmentation
 * have been established.
 * Functions:
 *	clear and free user core
 *	turn on clock
 *	hand craft 0th process
 *	call all initialization routines
 *	fork - process 0 to schedule
D 77
 *	     - process 2 to page out
E 77
 *	     - process 1 execute bootstrap
D 77
 *
D 54
 * loop at loc 13 (0xd) in user mode -- /etc/init
E 54
I 54
D 56
 * loop at loc something in user mode -- /etc/init
E 56
I 56
 * loop at loc 13 (0xd) in user mode -- /etc/init
E 56
E 54
 *	cannot be executed.
E 77
I 77
 *	     - process 2 to page out
E 119
I 119
D 155
 * System startup; initialize the world, create process 0,
 * mount root filesystem, and fork to create init and pagedaemon.
 * Most of the hard work is done in the lower-level initialization
 * routines including startup(), which does memory initialization
 * and autoconfiguration.
E 155
I 155
 * System startup; initialize the world, create process 0, mount root
 * filesystem, and fork to create init and pagedaemon.  Most of the
 * hard work is done in the lower-level initialization routines including
 * startup(), which does memory initialization and autoconfiguration.
E 155
E 119
E 77
 */
I 54
D 66
#ifdef vax
E 66
E 54
D 125
main(firstaddr)
I 54
	int firstaddr;
E 125
I 125
D 156
main()
E 156
I 156
D 159
main(regs)
	int *regs;
E 159
I 159
main(framep)
	void *framep;
E 159
E 156
E 125
D 66
#endif
#ifdef sun
main(regs)
	struct regs regs;
#endif
E 66
E 54
{
I 141
D 142
	USES_VOP_UNLOCK;
E 142
E 141
I 8
D 155
	register int i;
E 155
I 19
	register struct proc *p;
I 91
D 119
	register struct pgrp *pg;
E 119
I 117
D 120
	register struct filedesc *fdp;
E 120
I 120
	register struct filedesc0 *fdp;
I 151
	register struct pdevinit *pdev;
I 155
	register int i;
E 155
E 151
E 120
I 118
D 119
	char *ip = initflags;
E 118
E 117
E 91
I 42
D 44
	struct fs *fsp;
E 44
I 44
D 96
	struct fs *fs;
E 96
I 56
	int s;
E 119
I 119
D 164
	int s, rval[2];
E 164
I 164
	int s;
	register_t rval[2];
E 164
I 155
D 168
	extern int (*mountroot) __P((void));
E 168
E 155
I 151
	extern struct pdevinit pdevinit[];
E 151
I 143
	extern void roundrobin __P((void *));
	extern void schedcpu __P((void *));
E 143
E 119
E 56
E 44
E 42
E 19
E 8

D 17
	cpusid = mfpr(SID);		/* get system identification */
E 17
D 20
#ifdef FASTVAX
E 20
D 119
	rqinit();
I 116
D 118
#if defined(i386)
E 118
I 118

E 119
E 118
	/*
D 119
	 * set boot flags
E 119
I 119
D 155
	 * Initialize curproc before any possible traps/probes
	 * to simplify trap processing.
E 155
I 155
	 * Initialize the current process pointer (curproc) before
	 * any possible traps/probes to simplify trap processing.
E 155
E 119
	 */
I 118
D 119
	*ip++ = '-';
E 118
	if (boothowto&RB_SINGLE)
D 118
		bcopy("-s", initflags, 3);
	else
		if (boothowto&RB_ASKNAME)
			bcopy("-a", initflags, 3);
	else
		bcopy("-", initflags, 2);
#endif
E 118
I 118
		*ip++ = 's';
	/* if (boothowto&RB_FASTBOOT)
		*ip++ = 'f'; */
	*ip++ = '\0';

E 118
E 116
I 115
#if defined(hp300) && defined(DEBUG)
E 119
I 119
	p = &proc0;
	curproc = p;
E 119
	/*
D 119
	 * Assumes mapping is really on
E 119
I 119
	 * Attempt to find console and initialize
	 * in case of early panic or other messages.
E 119
	 */
D 119
	find_devs();
	cninit();
#endif
E 119
I 119
	consinit();
I 124
	printf(copyright);
E 124

E 119
	vm_mem_init();
	kmeminit();
E 115
I 37
D 111
#include "loop.h"
E 111
I 54
D 66
#ifdef vax
E 66
E 54
D 38
#if NLOOP > 0
	loattach();			/* XXX */
#endif
E 38
E 37
D 20
#endif
E 20
D 125
	startup(firstaddr);
E 125
I 125
	cpu_startup();
E 125
I 54
D 66
#endif
#ifdef sun
	startup();
#endif
E 66
E 54
D 27
	if (lotsfree == 0)
		lotsfree = LOTSFREE;
E 27

D 155
	/*
	 * set up system process 0 (swapper)
	 */
E 155
I 155
D 160
	/* Create process 0 (the swapper). */
E 155
D 19

	proc[0].p_p0br = (struct pte *)mfpr(P0BR);
	proc[0].p_szpt = 1;
	proc[0].p_addr = uaddr(&proc[0]);
	proc[0].p_stat = SRUN;
	proc[0].p_flag |= SLOAD|SSYS;
	proc[0].p_nice = NZERO;
	u.u_procp = &proc[0];
E 19
I 19
D 119
	p = &proc[0];
I 107
	bcopy("swapper", p->p_comm, sizeof ("swapper"));
E 119
I 119
	p = &proc0;
	curproc = p;

E 160
I 160
	/*
I 163
	 * Initialize process and pgrp structures.
	 */
	procinit();

	/*
E 163
	 * Create process 0 (the swapper).
	 */
E 160
D 143
	allproc = p;
	p->p_prev = &allproc;
E 143
I 143
D 163
	allproc = (volatile struct proc *)p;
	p->p_prev = (struct proc **)&allproc;
E 163
I 163
	LIST_INSERT_HEAD(&allproc, p, p_list);
E 163
E 143
	p->p_pgrp = &pgrp0;
D 163
	pgrphash[0] = &pgrp0;
	pgrp0.pg_mem = p;
E 163
I 163
	LIST_INSERT_HEAD(PGRPHASH(0), &pgrp0, pg_hash);
	LIST_INIT(&pgrp0.pg_members);
	LIST_INSERT_HEAD(&pgrp0.pg_members, p, p_pglist);

E 163
	pgrp0.pg_session = &session0;
	session0.s_count = 1;
	session0.s_leader = p;

D 157
	p->p_flag = SLOAD|SSYS;
E 157
I 157
	p->p_flag = P_INMEM | P_SYSTEM;
E 157
E 119
E 107
I 86
D 89
#if defined(tahoe)
#ifndef lint
#define	initkey(which, p, index) \
    which/**/_cache[index] = 1, which/**/_cnt[index] = 1; \
    p->p_/**/which = index;
	initkey(ckey, p, MAXCKEY);
	initkey(dkey, p, MAXDKEY);
#endif
#endif
E 89
E 86
D 52
	p->p_p0br = (struct pte *)mfpr(P0BR);
E 52
I 52
D 115
	p->p_p0br = u.u_pcb.pcb_p0br;
E 52
	p->p_szpt = 1;
	p->p_addr = uaddr(p);
E 115
	p->p_stat = SRUN;
D 119
	p->p_flag |= SLOAD|SSYS;
E 119
	p->p_nice = NZERO;
I 119
	bcopy("swapper", p->p_comm, sizeof ("swapper"));

E 119
D 115
	setredzone(p->p_addr, (caddr_t)&u);
E 115
I 115
D 155
	/*
D 119
	 * Allocate a prototype map so we have something to fork
E 119
I 119
	 * Setup credentials
E 119
	 */
E 155
I 155
	/* Create credentials. */
E 155
I 126
	cred0.p_refcnt = 1;
E 126
D 119
	p->p_map = vm_map_create(pmap_create(0),
				 round_page(VM_MIN_ADDRESS),
				 trunc_page(VM_MAX_ADDRESS), TRUE);
	p->p_addr = proc0paddr;
E 115
	u.u_procp = p;
I 91
	MALLOC(pgrphash[0], struct pgrp *, sizeof (struct pgrp), 
		M_PGRP, M_NOWAIT);
	if ((pg = pgrphash[0]) == NULL)
		panic("no space to craft zero'th process group");
	pg->pg_id = 0;
	pg->pg_hforw = 0;
	pg->pg_mem = p;
	pg->pg_jobc = 0;
	p->p_pgrp = pg;
	p->p_pgrpnxt = 0;
	MALLOC(pg->pg_session, struct session *, sizeof (struct session),
		M_SESSION, M_NOWAIT);
	if (pg->pg_session == NULL)
		panic("no space to craft zero'th session");
	pg->pg_session->s_count = 1;
D 106
	pg->pg_session->s_leader = 0;
E 106
I 106
	pg->pg_session->s_leader = NULL;
	pg->pg_session->s_ttyvp = NULL;
	pg->pg_session->s_ttyp = NULL;
E 106
I 93
#ifdef KTRACE
	p->p_tracep = NULL;
	p->p_traceflag = 0;
#endif
E 93
E 91
I 70
D 86
#ifdef vax
E 86
	/*
D 76
	 * This assumes that the u. area is always mapped 
	 * to the same physical address. Otherwise must be
E 76
I 76
	 * These assume that the u. area is always mapped 
	 * to the same virtual address. Otherwise must be
E 76
	 * handled when copying the u. area in newproc().
	 */
D 94
	u.u_nd.ni_iov = &u.u_nd.ni_iovec;
E 94
I 94
D 98
	u.u_nd.ni_iov = &u.u_nd.ni_nd.nd_iovec;
E 94
I 76
D 97
	u.u_ap = u.u_arg;
E 97
E 76
D 86
#endif
E 86
	u.u_nd.ni_iovcnt = 1;
I 97
	u.u_nd.ni_base = (caddr_t)&u.u_nd.ni_dent;
	u.u_nd.ni_rw = UIO_WRITE;
	u.u_nd.ni_segflg = UIO_SYSSPACE;
E 98
I 98
	ndinit(&u.u_nd);
E 119
I 119
	p->p_cred = &cred0;
	p->p_ucred = crget();
	p->p_ucred->cr_ngroups = 1;	/* group 0 */
E 119
E 98
D 114
	u.u_ap = u.u_arg;
E 114
I 109
D 113
	u.u_start = time;
E 113
E 109
E 97
I 86

E 86
E 70
I 54
D 66
#ifdef sun
D 57
	u.u_ar0 = &regs.r0;
E 57
I 57
	u.u_ar0 = &regs.r_r0;
E 57
#endif
E 66
E 54
E 19
D 73
	u.u_cmask = CMASK;
E 73
I 73
D 117
	u.u_cmask = cmask;
I 77
	u.u_lastfile = -1;
E 117
I 117
D 155
	/*
	 * Create the file descriptor table for process 0.
	 */
E 155
I 155
	/* Create the file descriptor table. */
E 155
D 119
	fdp = (struct filedesc *)malloc(sizeof(*fdp), M_FILE, M_WAITOK);
	bzero((char *)fdp, sizeof(struct filedesc));
E 119
I 119
	fdp = &filedesc0;
E 119
D 120
	p->p_fd = fdp;
	fdp->fd_refcnt = 1;
	fdp->fd_cmask = cmask;
D 119
	fdp->fd_lastfile = -1;
	fdp->fd_maxfiles = NDFILE;
E 117
E 77
E 73
I 48
D 94
	for (i = 1; i < NGROUPS; i++)
D 61
		u.u_groups[i] = -1;
E 61
I 61
		u.u_groups[i] = NOGROUP;
E 94
E 61
E 48
I 8
D 49
	for (i = 1; i < sizeof(u.u_limit)/sizeof(u.u_limit[0]); i++)
D 12
		u.u_limit[i] = INFINITY;
E 12
I 12
		switch (i) {

		case LIM_STACK:
			u.u_limit[i] = 512*1024;
			continue;
		case LIM_DATA:
			u.u_limit[i] = ctob(MAXDSIZ);
			continue;
		default:
			u.u_limit[i] = INFINITY;
			continue;
		}
I 26
	p->p_maxrss = INFINITY/NBPG;
E 49
I 49
	for (i = 0; i < sizeof(u.u_rlimit)/sizeof(u.u_rlimit[0]); i++)
		u.u_rlimit[i].rlim_cur = u.u_rlimit[i].rlim_max = 
		    RLIM_INFINITY;
E 119
I 119
	fdp->fd_ofiles = fd0;
	fdp->fd_ofileflags = fdflags0;
	fdp->fd_nfiles = NOEXTENT;
E 120
I 120
	p->p_fd = &fdp->fd_fd;
	fdp->fd_fd.fd_refcnt = 1;
	fdp->fd_fd.fd_cmask = cmask;
	fdp->fd_fd.fd_ofiles = fdp->fd_dfiles;
	fdp->fd_fd.fd_ofileflags = fdp->fd_dfileflags;
	fdp->fd_fd.fd_nfiles = NDFILE;
E 120

E 119
D 76
	u.u_rlimit[RLIMIT_STACK].rlim_cur = 512*1024;
D 51
	u.u_rlimit[RLIMIT_DATA].rlim_cur = ctob(MAXDSIZ);
E 51
I 51
D 69
	u.u_rlimit[RLIMIT_STACK].rlim_max = ctob(MAXDSIZ);
E 69
I 69
	u.u_rlimit[RLIMIT_STACK].rlim_max = ctob(MAXSSIZ);
E 69
	u.u_rlimit[RLIMIT_DATA].rlim_max =
	    u.u_rlimit[RLIMIT_DATA].rlim_cur = ctob(MAXDSIZ);
E 51
D 75
	p->p_maxrss = RLIM_INFINITY/NBPG;
E 75
I 75
	/* p_maxrss is set later, in pageout (process 2) */
E 76
I 76
D 155
	/*
I 119
	 * Set initial limits
	 */
E 155
I 155
	/* Create the limits structures. */
E 155
	p->p_limit = &limit0;
	for (i = 0; i < sizeof(p->p_rlimit)/sizeof(p->p_rlimit[0]); i++)
		limit0.pl_rlimit[i].rlim_cur =
		    limit0.pl_rlimit[i].rlim_max = RLIM_INFINITY;
D 150
	limit0.pl_rlimit[RLIMIT_OFILE].rlim_cur = NOFILE;
E 150
I 150
	limit0.pl_rlimit[RLIMIT_NOFILE].rlim_cur = NOFILE;
E 150
	limit0.pl_rlimit[RLIMIT_NPROC].rlim_cur = MAXUPRC;
I 152
	i = ptoa(cnt.v_free_count);
	limit0.pl_rlimit[RLIMIT_RSS].rlim_max = i;
	limit0.pl_rlimit[RLIMIT_MEMLOCK].rlim_max = i;
	limit0.pl_rlimit[RLIMIT_MEMLOCK].rlim_cur = i / 3;
E 152
	limit0.p_refcnt = 1;

D 155
	/*
	 * Allocate a prototype map so we have something to fork
	 */
E 155
I 155
	/* Allocate a prototype map so we have something to fork. */
E 155
	p->p_vmspace = &vmspace0;
	vmspace0.vm_refcnt = 1;
	pmap_pinit(&vmspace0.vm_pmap);
	vm_map_init(&p->p_vmspace->vm_map, round_page(VM_MIN_ADDRESS),
	    trunc_page(VM_MAX_ADDRESS), TRUE);
	vmspace0.vm_map.pmap = &vmspace0.vm_pmap;
	p->p_addr = proc0paddr;				/* XXX */

	/*
D 155
	 * We continue to place resource usage info
	 * and signal actions in the user struct so they're pageable.
E 155
I 155
	 * We continue to place resource usage info and signal
	 * actions in the user struct so they're pageable.
E 155
	 */
D 120
	p->p_stats = &u.u_stats;
	p->p_sigacts = &u.u_sigacts;
E 120
I 120
D 123
	p->p_stats = &((struct user *)p->p_addr)->u_stats;
	p->p_sigacts = &((struct user *)p->p_addr)->u_sigacts;
E 123
I 123
	p->p_stats = &p->p_addr->u_stats;
	p->p_sigacts = &p->p_addr->u_sigacts;
I 146

	/*
D 163
	 * Initialize per uid information structure and charge
	 * root for one process.
E 163
I 163
	 * Charge root for one process.
E 163
	 */
D 163
	usrinfoinit();
E 163
	(void)chgproccnt(0, 1);
E 146
E 123
E 120

	rqinit();

D 151
	/*
E 119
D 80
	 * Virtual memory limits get set in vminit().
E 80
I 80
	 * configure virtual memory system,
	 * set vm rlimits
E 80
	 */
E 151
I 151
	/* Configure virtual memory system, set vm rlimits. */
E 151
D 119
	vminit();
E 119
I 119
	vm_init_limits(p);
E 119
I 80

I 94
D 151
	/*
I 104
	 * Initialize the file systems.
D 148
	 *
E 104
D 124
	 * Get vnodes for swapdev, argdev, and rootdev.
E 124
I 124
	 * Get vnodes for swapdev and rootdev.
E 148
E 124
	 */
E 151
I 151
	/* Initialize the file systems. */
E 151
I 103
D 104
	vhinit();
E 103
	ihinit();
	nchinit();
E 104
I 104
	vfsinit();
E 104
D 124
	if (bdevvp(swapdev, &swapdev_vp) ||
	    bdevvp(argdev, &argdev_vp) ||
	    bdevvp(rootdev, &rootvp))
E 124
I 124
D 148
	if (bdevvp(swapdev, &swapdev_vp) || bdevvp(rootdev, &rootvp))
E 124
		panic("can't setup bdevvp's");
E 148

D 119
	/*
	 * Setup credentials
	 */
	u.u_cred = crget();
D 110
	u.u_ngroups = 1;
E 110
I 110
	u.u_cred->cr_ngroups = 1;
E 110

E 119
E 94
E 80
E 76
E 75
E 49
I 46
D 69
#ifdef QUOTA
E 69
I 69
D 108
#if defined(QUOTA)
E 69
	qtinit();
	p->p_quota = u.u_quota = getquota(0, 0, Q_NDQ);
#endif
E 108
I 86
D 87
#if defined(vax)
E 87
E 86
E 46
E 26
E 12
E 8
D 49
	clkstart();
E 49
I 49
D 55
	clockstart();
E 55
I 55
D 143
	startrtclock();
I 87
#if defined(vax)
E 87
I 60
D 65
#ifdef KGCLOCK
E 65
I 65
#include "kg.h"
#if NKG > 0
E 65
	startkgclock();
#endif
I 86
#endif
E 143
I 143
D 151
	/*
	 * Start real time and statistics clocks.
	 */
E 151
I 151
	/* Start real time and statistics clocks. */
E 151
	initclocks();
E 143
E 86
E 60
E 55
E 49

D 151
	/*
D 32
	 * Initialize devices and
	 * set up 'known' i-nodes
E 32
I 32
	 * Initialize tables, protocols, and set up well-known inodes.
E 32
	 */
E 151
I 151
D 155
	/* Initialize tables. */
E 155
I 155
	/* Initialize mbuf's. */
E 155
E 151
D 32

E 32
I 32
	mbinit();
I 39
D 77
	cinit();			/* needed by dmc-11 driver */
E 77
I 77
D 155
	cinit();
E 155
I 155

	/* Initialize clists. */
	clist_init();

E 155
I 111
#ifdef SYSVSHM
I 155
	/* Initialize System V style shared memory. */
E 155
	shminit();
#endif
E 111
I 83
D 151
#include "sl.h"
#if NSL > 0
	slattach();			/* XXX */
#endif
I 111
#include "loop.h"
E 111
E 83
E 77
E 39
D 81
#ifdef INET
E 81
D 33
	prinit();
E 33
I 33
D 41
	pfinit();
E 41
I 38
#if NLOOP > 0
	loattach();			/* XXX */
#endif
E 151
I 151

	/* Attach pseudo-devices. */
	for (pdev = pdevinit; pdev->pdev_attach != NULL; pdev++)
		(*pdev->pdev_attach)(pdev->pdev_count);

E 151
I 56
	/*
D 151
	 * Block reception of incoming packets
	 * until protocols have been initialized.
E 151
I 151
	 * Initialize protocols.  Block reception of incoming packets
	 * until everything is ready.
E 151
	 */
	s = splimp();
E 56
E 38
E 33
D 37
#endif
I 36
#include "lo.h"
#if NLOOP > 0
	loattach();
E 37
I 37
	ifinit();
I 41
D 54
	pfinit();			/* must follow interfaces */
E 54
E 41
E 37
D 81
#endif
E 81
I 54
	domaininit();
I 56
D 81
#ifdef INET
E 81
	splx(s);
D 81
#endif
E 81
I 69
D 119
	pqinit();
I 82
D 115
	xinit();
E 115
E 82
E 69
E 56
E 54
E 36
E 32
D 94
	ihinit();
E 94
I 2
D 88
	bhinit();
E 2
D 39
	cinit();
E 39
	binit();
	bswinit();
E 88
I 88
	swapinit();
E 119
I 119

E 119
E 88
I 68
D 94
	nchinit();
E 94
E 68
I 45
#ifdef GPROF
I 155
	/* Initialize kernel profiling. */
E 155
	kmstartup();
D 104
#endif
I 94
#ifdef NFS
	nfsinit();
#endif
I 101
#ifdef MFS
	mfs_init();
E 104
#endif
E 101
E 94
E 45
D 44
	iinit();
I 28
D 32
	ptinit();
E 32
E 28
D 42
	rootdir = iget(rootdev, (ino_t)ROOTINO);
E 42
I 42
	fsp = getfs(rootdev);
	rootdir = iget(rootdev, fsp, (ino_t)ROOTINO);
E 42
	rootdir->i_flag &= ~ILOCK;
D 42
	u.u_cdir = iget(rootdev, (ino_t)ROOTINO);
E 42
I 42
	u.u_cdir = iget(rootdev, fsp, (ino_t)ROOTINO);
E 42
	u.u_cdir->i_flag &= ~ILOCK;
E 44
I 44

D 47
	fs = mountfs(rootdev, 0, 0);
E 47
I 47
D 89
	fs = mountfs(rootdev, 0, (struct inode *)0);
E 89
I 89
D 94
	fs = mountfs(rootdev, boothowto & RB_RDONLY, (struct inode *)0);
E 89
E 47
	if (fs == 0)
		panic("iinit");
	bcopy("/", fs->fs_fsmnt, 2);
I 50

D 55
/* initialize wall clock */
E 50
D 49
	clkinit(fs->fs_time);
	bootime = time;
E 49
I 49
	clockinit(fs->fs_time);
E 55
I 55
	inittodr(fs->fs_time);
E 55
	boottime = time;
E 49

E 94
I 50
D 119
/* kick off timeout driven events by calling first time */
E 119
I 119
D 155
	/* kick off timeout driven events by calling first time */
E 155
I 155
	/* Kick off timeout driven events by calling first time. */
E 155
E 119
D 143
	roundrobin();
	schedcpu();
I 116
	enablertclock();		/* enable realtime clock interrupts */
E 143
I 143
	roundrobin(NULL);
	schedcpu(NULL);
E 143
E 116
D 115
	schedpaging();
E 115

D 119
/* set up the root file system */
E 119
I 119
D 155
	/*
	 * Set up the root file system and vnode.
	 */
E 155
I 155
	/* Mount the root file system. */
E 155
E 119
E 50
D 94
	rootdir = iget(rootdev, fs, (ino_t)ROOTINO);
	iunlock(rootdir);
	u.u_cdir = iget(rootdev, fs, (ino_t)ROOTINO);
	iunlock(u.u_cdir);
E 94
I 94
D 168
	if ((*mountroot)())
E 168
I 168
	if (vfs_mountroot())
E 168
		panic("cannot mount root");
I 167
	mountlist.cqh_first->mnt_flag |= MNT_ROOTFS;
E 167
D 155
	/*
	 * Get vnode for '/'.
D 117
	 * Setup rootdir and u.u_cdir to point to it.
E 117
I 117
D 120
	 * Setup rootdir and fdp->fd_cdir to point to it.
E 120
I 120
	 * Setup rootdir and fdp->fd_fd.fd_cdir to point to it.
E 120
E 117
	 */
	if (VFS_ROOT(rootfs, &rootdir))
E 155
I 155

	/* Get the vnode for '/'.  Set fdp->fd_fd.fd_cdir to reference it. */
D 161
	if (VFS_ROOT(rootfs, &rootvnode))
E 161
I 161
D 166
	if (VFS_ROOT(mountlist.tqh_first, &rootvnode))
E 166
I 166
	if (VFS_ROOT(mountlist.cqh_first, &rootvnode))
E 166
E 161
E 155
		panic("cannot find root vnode");
D 117
	u.u_cdir = rootdir;
D 99
	u.u_cdir->v_count++;
E 99
I 99
	VREF(u.u_cdir);
E 117
I 117
D 120
	fdp->fd_cdir = rootdir;
	VREF(fdp->fd_cdir);
E 120
I 120
D 155
	fdp->fd_fd.fd_cdir = rootdir;
E 155
I 155
	fdp->fd_fd.fd_cdir = rootvnode;
E 155
	VREF(fdp->fd_fd.fd_cdir);
E 120
E 117
E 99
D 96
	vop_unlock(rootdir);
E 96
I 96
D 155
	VOP_UNLOCK(rootdir);
E 155
I 155
D 169
	VOP_UNLOCK(rootvnode);
E 169
I 169
	VOP_UNLOCK(rootvnode, 0, p);
E 169
E 155
E 96
E 94
D 50

E 50
E 44
D 117
	u.u_rdir = NULL;
E 117
I 117
D 120
	fdp->fd_rdir = NULL;
E 120
I 120
	fdp->fd_fd.fd_rdir = NULL;
E 120
E 117
I 94
D 113
	boottime = time;
E 94
I 50

E 113
I 113
D 119
	boottime = u.u_start =  time;
E 119
I 119
	swapinit();
E 119
E 113
E 50
D 115
	u.u_dmap = zdmap;
	u.u_smap = zdmap;
E 115
I 27
D 75

	/*
	 * Set the scan rate and other parameters of the paging subsystem.
	 */
	setupclock();
E 75
E 27

I 87
D 116
	enablertclock();		/* enable realtime clock interrupts */
E 116
E 87
I 86
D 89
#if defined(tahoe)
	clk_enable = 1;			/* enable clock interrupt */
#endif
E 89
E 86
	/*
I 73
D 119
	 * make init process
E 119
I 119
D 147
	 * Now can look at time, having had a chance
	 * to verify the time from the file system.
E 147
I 147
	 * Now can look at time, having had a chance to verify the time
	 * from the file system.  Reset p->p_rtime as it may have been
D 157
	 * munched in swtch() after the time got set.
E 157
I 157
	 * munched in mi_switch() after the time got set.
E 157
E 147
E 119
	 */
I 119
D 129
	boottime = p->p_stats->p_start = time;
E 129
I 129
D 143
	mono_time = boottime = p->p_stats->p_start = time;
E 143
I 143
D 144
	runtime = mono_time = boottime = time;
	p->p_stats->p_start = p->p_rtime = runtime;
E 144
I 144
	p->p_stats->p_start = runtime = mono_time = boottime = time;
I 147
	p->p_rtime.tv_sec = p->p_rtime.tv_usec = 0;
E 147
E 144
E 143
E 129
E 119

I 102
D 119
	siginit(&proc[0]);
E 102
D 115
	proc[0].p_szpt = CLSIZE;
E 115
	if (newproc(0)) {
E 119
I 119
D 155
	/*
	 * make init process
	 */
E 155
I 155
	/* Initialize signal state for process 0. */
E 155
	siginit(p);
I 155

	/* Create process 1 (init(8)). */
E 155
D 130
	if (fork(p, (void *) NULL, rval))
E 130
I 130
	if (fork(p, NULL, rval))
E 130
		panic("fork init");
	if (rval[1]) {
D 121
		char *ip = initflags;
E 121
I 121
D 130
		static char initflags[] = "-sf";
		char *ip = initflags + 1;
E 121
E 119
D 115
		expand(clrnd((int)btoc(szicode)), 0);
D 84
		(void) swpexpand(u.u_dsize, 0, &u.u_dmap, &u.u_smap);
E 84
I 84
D 112
		(void) swpexpand(u.u_dsize, (size_t)0, &u.u_dmap, &u.u_smap);
E 112
I 112
		(void) swpexpand(u.u_dsize, (segsz_t)0, &u.u_dmap, &u.u_smap);
E 115
I 115
		vm_offset_t addr = 0;
E 130
I 124
D 156
		extern int icode[];		/* user init code */
		extern int szicode;		/* size of icode */
I 130
		static char initflags[] = "-sf";
		vm_offset_t addr;
		char *ip;
E 130
E 124

D 119
		(void) vm_allocate(u.u_procp->p_map,
				   &addr, round_page(szicode), FALSE);
		if (addr != 0)
E 119
I 119
		/*
D 130
		 * Now in process 1.  Set init flags into icode,
		 * get a minimal address space, copy out "icode",
		 * and return to it to do an exec of init.
E 130
I 130
		 * Now in process 1.  Set init flags into icode, get a minimal
		 * address space, copy out "icode", and return to it to do an
		 * exec of init.
E 130
		 */
D 130
		p = curproc;
		initproc = p;
E 130
I 130
		ip = initflags + 1;
E 130
D 121
		*ip++ = '-';
E 121
		if (boothowto&RB_SINGLE)
			*ip++ = 's';
#ifdef notyet
		if (boothowto&RB_FASTBOOT)
			*ip++ = 'f';
D 121
		*ip++ = '\0';
E 121
#endif
I 130
		if (ip == initflags + 1)
			*ip++ = '-';
E 130
I 121
		*ip++ = '\0';
E 121

I 130
D 131
		addr = 0;
E 131
I 131
		addr = VM_MIN_ADDRESS;
E 131
		initproc = p = curproc;
E 130
		if (vm_allocate(&p->p_vmspace->vm_map, &addr,
D 121
		    round_page(szicode), FALSE) != KERN_SUCCESS || addr != 0)
E 121
I 121
		    round_page(szicode + sizeof(initflags)), FALSE) != 0 ||
D 131
		    addr != 0)
E 131
I 131
		    addr != VM_MIN_ADDRESS)
E 131
E 121
E 119
			panic("init: couldn't allocate at zero");

D 155
		/* need just enough stack to exec from */
E 155
I 155
		/* Need just enough stack from which to exec. */
E 155
D 123
		addr = trunc_page(VM_MAX_ADDRESS - PAGE_SIZE);
E 123
I 123
		addr = trunc_page(USRSTACK - PAGE_SIZE);
E 123
D 119
		(void) vm_allocate(u.u_procp->p_map, &addr, PAGE_SIZE, FALSE);
		u.u_maxsaddr = (caddr_t)addr;
E 119
I 119
		if (vm_allocate(&p->p_vmspace->vm_map, &addr,
		    PAGE_SIZE, FALSE) != KERN_SUCCESS)
			panic("vm_allocate init stack");
		p->p_vmspace->vm_maxsaddr = (caddr_t)addr;
E 119
E 115
E 112
E 84
D 130
		(void) copyout((caddr_t)icode, (caddr_t)0, (unsigned)szicode);
I 121
		(void) copyout(initflags, (caddr_t)szicode, sizeof(initflags));
E 130
I 130
D 131
		(void)copyout((caddr_t)icode, (caddr_t)0, (u_int)szicode);
		(void)copyout(initflags, (caddr_t)szicode, sizeof(initflags));
E 131
I 131
		(void)copyout((caddr_t)icode, (caddr_t)VM_MIN_ADDRESS,
		    (u_int)szicode);
		(void)copyout(initflags, (caddr_t)(VM_MIN_ADDRESS + szicode),
		    sizeof(initflags));
E 131
E 130
E 121
D 119
		/*
		 * Return goes to loc. 0 of user init
		 * code just copied out.
		 */
		return;
E 119
I 119
		return;			/* returns to icode */
E 156
I 156
D 159
		start_init(curproc, regs);
E 159
I 159
		start_init(curproc, framep);
E 159
		return;
E 156
E 119
	}
I 119

E 119
D 155
	/*
E 73
D 115
	 * make page-out daemon (process 2)
D 22
	 * the daemon has ctopt(NSWBUF*CLSIZE*KLMAX) pages of page
E 22
I 22
	 * the daemon has ctopt(nswbuf*CLSIZE*KLMAX) pages of page
E 22
	 * table so that it can map dirty pages into
	 * its address space during asychronous pushes.
E 115
I 115
	 * Start up pageout daemon (process 2).
E 115
	 */
E 155
I 155
	/* Create process 2 (the pageout daemon). */
E 155
D 29

E 29
D 73
	mpid = 1;
E 73
D 22
	proc[0].p_szpt = clrnd(ctopt(NSWBUF*CLSIZE*KLMAX + UPAGES));
E 22
I 22
D 111
	proc[0].p_szpt = clrnd(ctopt(nswbuf*CLSIZE*KLMAX + UPAGES));
E 111
I 111
D 115
	proc[0].p_szpt = clrnd(ctopt(nswbuf*CLSIZE*KLMAX + HIGHPAGES));
E 115
E 111
E 22
D 73
	proc[1].p_stat = SZOMB;		/* force it to be in proc slot 2 */
I 69
	p = freeproc;
	freeproc = p->p_nxt;
E 73
E 69
D 119
	if (newproc(0)) {
		proc[2].p_flag |= SLOAD|SSYS;
D 22
		proc[2].p_dsize = u.u_dsize = NSWBUF*CLSIZE*KLMAX; 
E 22
I 22
D 115
		proc[2].p_dsize = u.u_dsize = nswbuf*CLSIZE*KLMAX; 
E 115
I 107
		bcopy("pagedaemon", proc[2].p_comm, sizeof ("pagedaemon"));
E 119
I 119
D 130
	if (fork(p, (void *) NULL, rval))
E 130
I 130
	if (fork(p, NULL, rval))
E 130
		panic("fork pager");
	if (rval[1]) {
		/*
		 * Now in process 2.
		 */
		p = curproc;
		pageproc = p;
D 157
		p->p_flag |= SLOAD|SSYS;		/* XXX */
E 157
I 157
		p->p_flag |= P_INMEM | P_SYSTEM;	/* XXX */
E 157
		bcopy("pagedaemon", curproc->p_comm, sizeof ("pagedaemon"));
E 119
E 107
I 54
D 62
#ifdef NOPAGING
		for (;;)
			sleep((caddr_t)&u, PSLEP);
I 57
		/*NOTREACHED*/
E 57
#else
E 62
E 54
E 22
D 115
		pageout();
E 115
I 115
		vm_pageout();
E 115
I 54
D 55
#endif
E 55
D 155
		/*NOTREACHED*/
E 155
I 155
		/* NOTREACHED */
E 155
I 55
D 62
#endif
E 62
E 55
E 54
	}

D 155
	/*
D 73
	 * make init process and
E 73
	 * enter scheduling loop
	 */
D 73

	mpid = 0;
	proc[1].p_stat = 0;
	proc[0].p_szpt = CLSIZE;
I 69
	p->p_nxt = freeproc;
	freeproc = p;
E 69
	if (newproc(0)) {
I 54
D 66
#ifdef vax
E 66
E 54
D 52
		expand(clrnd((int)btoc(szicode)), P0BR);
E 52
I 52
		expand(clrnd((int)btoc(szicode)), 0);
E 52
I 7
D 15
		swpexpand(u.u_dsize, 0, &u.u_dmap, &u.u_smap);
E 15
I 15
		(void) swpexpand(u.u_dsize, 0, &u.u_dmap, &u.u_smap);
E 15
E 7
D 4
		VOID copyout((caddr_t)icode, (caddr_t)0, (unsigned)szicode);
E 4
I 4
		(void) copyout((caddr_t)icode, (caddr_t)0, (unsigned)szicode);
I 54
D 66
#endif
#ifdef sun
		icode();
		usetup();
D 63
		regs.r_context = u.u_pcb.pcb_ctx->ctx_context;
E 63
I 63
		regs.r_context = u.u_procp->p_ctx->ctx_context;
E 63
#endif
E 66
E 54
E 4
		/*
		 * Return goes to loc. 0 of user init
		 * code just copied out.
		 */
		return;
	}
E 73
I 46
D 64
#ifdef MUSH
	/*
	 * start MUSH daemon
	 *			pid == 3
	 */
	if (newproc(0)) {
I 57
#ifdef vax
E 57
D 52
		expand(clrnd((int)btoc(szmcode)), P0BR);
E 52
I 52
		expand(clrnd((int)btoc(szmcode)), 0);
E 52
		(void) swpexpand(u.u_dsize, 0, &u.u_dmap, &u.u_smap);
		(void) copyout((caddr_t)mcode, (caddr_t)0, (unsigned)szmcode);
		/*
		 * Return goes to loc. 0 of user mush
		 * code just copied out.
		 */
		return;
I 57
#endif
E 57
	}
#endif
E 64
E 46
I 29
D 40

#ifdef BBNNET 
	/*
	 * Initialize bbn network.
	 */
D 31
	netinit();
E 31
I 31
	netmain();
E 31
#endif BBNNET
E 40
E 29
D 115
	proc[0].p_szpt = 1;
E 115
	sched();
E 155
I 155
	/* The scheduler is an infinite loop. */
	scheduler();
	/* NOTREACHED */
I 156
}

/*
 * List of paths to try when searching for "init".
 */
static char *initpaths[] = {
	"/sbin/init",
	"/sbin/oinit",
	"/sbin/init.bak",
	NULL,
};

/*
 * Start the initial user process; try exec'ing each pathname in "initpaths".
 * The program is invoked with one argument containing the boot flags.
 */
static void
D 159
start_init(p, regs)
E 159
I 159
start_init(p, framep)
E 159
	struct proc *p;
D 159
	int *regs;
E 159
I 159
	void *framep;
E 159
{
	vm_offset_t addr;
D 164
	struct execve_args args;
	int options, i, retval[2], error;
E 164
I 164
	struct execve_args /* {
		syscallarg(char *) path;
		syscallarg(char **) argp;
		syscallarg(char **) envp;
	} */ args;
	int options, i, error;
	register_t retval[2];
I 165
	char flags[4] = "-", *flagsp;
E 165
E 164
	char **pathp, *path, *ucp, **uap, *arg0, *arg1;

I 158
	initproc = p;

E 158
	/*
D 159
	 * We need to set p->p_md.md_regs since start_init acts like a
	 * system call and references the regs to set the entry point
	 * (see setregs) when it tries to exec.  On regular fork, the
	 * p->p_md.md_regs of the child is undefined since it is set on
	 * each system call.  The startup code in "locore.s" has arranged
	 * that there be some place to set "p->p_md.md_regs" to, and
	 * passed a pointer to that place as main's argument.
E 159
I 159
	 * We need to set the system call frame as if we were entered through
	 * a syscall() so that when we call execve() below, it will be able
	 * to set the entry point (see setregs) when it tries to exec.  The
	 * startup code in "locore.s" has allocated space for the frame and
	 * passed a pointer to that space as main's argument.
E 159
	 */
D 159
	p->p_md.md_regs = regs;
E 159
I 159
	cpu_set_init_frame(p, framep);
E 159

	/*
	 * Need just enough stack to hold the faked-up "execve()" arguments.
	 */
	addr = trunc_page(VM_MAX_ADDRESS - PAGE_SIZE);
	if (vm_allocate(&p->p_vmspace->vm_map, &addr, PAGE_SIZE, FALSE) != 0)
		panic("init: couldn't allocate argument space");
	p->p_vmspace->vm_maxsaddr = (caddr_t)addr;

	for (pathp = &initpaths[0]; (path = *pathp) != NULL; pathp++) {
		/*
D 165
		 * Move out the boot flag argument.
E 165
I 165
		 * Construct the boot flag argument.
E 165
		 */
		options = 0;
I 165
		flagsp = flags + 1;
E 165
		ucp = (char *)USRSTACK;
D 157
		(void) subyte(--ucp, 0);		/* trailing zero */
E 157
I 157
D 165
		(void)subyte(--ucp, 0);		/* trailing zero */
E 165
E 157
		if (boothowto & RB_SINGLE) {
D 157
			(void) subyte(--ucp, 's');
E 157
I 157
D 165
			(void)subyte(--ucp, 's');
E 165
I 165
			*flagsp++ = 's';
E 165
E 157
			options = 1;
		}
#ifdef notyet
                if (boothowto & RB_FASTBOOT) {
D 157
			(void) subyte(--ucp, 'f');
E 157
I 157
D 165
			(void)subyte(--ucp, 'f');
E 165
I 165
			*flagsp++ = 'f';
E 165
E 157
			options = 1;
		}
#endif
D 165
		if (options == 0)
D 157
			(void) subyte(--ucp, '-');
		(void) subyte(--ucp, '-');		/* leading hyphen */
E 157
I 157
			(void)subyte(--ucp, '-');
		(void)subyte(--ucp, '-');		/* leading hyphen */
E 157
		arg1 = ucp;
E 165
I 165
		/*
		 * Move out the flags (arg 1), if necessary.
		 */
		if (options != 0) {
			*flagsp++ = '\0';
			i = flagsp - flags;
			(void)copyout((caddr_t)flags, (caddr_t)(ucp -= i), i);
			arg1 = ucp;
		}
E 165

		/*
		 * Move out the file name (also arg 0).
		 */
D 165
		for (i = strlen(path) + 1; i >= 0; i--)
D 157
			(void) subyte(--ucp, path[i]);
E 157
I 157
			(void)subyte(--ucp, path[i]);
E 165
I 165
		i = strlen(path) + 1;
		(void)copyout((caddr_t)path, (caddr_t)(ucp -= i), i);
E 165
E 157
		arg0 = ucp;

		/*
		 * Move out the arg pointers.
		 */
D 164
		uap = (char **)((int)ucp & ~(NBPW-1));
E 164
I 164
		uap = (char **)((long)ucp & ~ALIGNBYTES);
E 164
D 157
		(void) suword((caddr_t)--uap, 0);	/* terminator */
		(void) suword((caddr_t)--uap, (int)arg1);
		(void) suword((caddr_t)--uap, (int)arg0);
E 157
I 157
		(void)suword((caddr_t)--uap, 0);	/* terminator */
D 164
		(void)suword((caddr_t)--uap, (int)arg1);
		(void)suword((caddr_t)--uap, (int)arg0);
E 164
I 164
D 165
		(void)suword((caddr_t)--uap, (long)arg1);
E 165
I 165
		if (options != 0)
			(void)suword((caddr_t)--uap, (long)arg1);
E 165
		(void)suword((caddr_t)--uap, (long)arg0);
E 164
E 157

		/*
		 * Point at the arguments.
		 */
D 164
		args.fname = arg0;
		args.argp = uap;
		args.envp = NULL;
E 164
I 164
		SCARG(&args, path) = arg0;
		SCARG(&args, argp) = uap;
		SCARG(&args, envp) = NULL;
E 164

		/*
D 157
		 * Now try to exec the program.
E 157
I 157
		 * Now try to exec the program.  If can't for any reason
		 * other than it doesn't exist, complain.
E 157
		 */
D 164
		if ((error = execve(p, &args, &retval)) == 0)
E 164
I 164
		if ((error = execve(p, &args, retval)) == 0)
E 164
			return;
D 157
		if (error != ENOENT) {
			/*
			 * Found "init", but couldn't execute it.
			 * Complain now.
			 */
			printf("Can't invoke %s: error %d\n", path, error);
			panic("init error");
		}
E 157
I 157
		if (error != ENOENT)
			printf("exec %s: error %d\n", path, error);
E 157
	}
	printf("init: not found\n");
	panic("no init");
E 156
E 155
D 44
}

/*
 * iinit is called once (from main)
 * very early in initialization.
 * It reads the root's super block
 * and initializes the current date
 * from the last modified date.
 *
 * panic: iinit -- cannot read the super
 * block. Usually because of an IO error.
 */
iinit()
{
D 18
	register struct buf *cp, *bp;
E 18
I 18
	register struct buf *bp;
E 18
D 42
	register struct filsys *fp;
E 42
I 42
	register struct fs *fp;
E 42
I 24
	register int i;
I 42
	int blks;
E 42
E 24
D 12
	register unsigned i, j;
E 12

	(*bdevsw[major(rootdev)].d_open)(rootdev, 1);
D 42
	bp = bread(rootdev, SUPERB);
E 42
I 42
	bp = bread(rootdev, SBLOCK, SBSIZE);
E 42
D 16
	cp = geteblk();
E 16
	if(u.u_error)
		panic("iinit");
D 16
	bcopy(bp->b_un.b_addr, cp->b_un.b_addr, sizeof(struct filsys));
E 16
I 16
	bp->b_flags |= B_LOCKED;		/* block can never be re-used */
E 16
	brelse(bp);
D 16
	mount[0].m_bufp = cp;
E 16
	mount[0].m_dev = rootdev;
D 16
	fp = cp->b_un.b_filsys;
E 16
I 16
	mount[0].m_bufp = bp;
D 42
	fp = bp->b_un.b_filsys;
E 16
	fp->s_flock = 0;
	fp->s_ilock = 0;
	fp->s_ronly = 0;
	fp->s_lasti = 1;
	fp->s_nbehind = 0;
I 24
	fp->s_fsmnt[0] = '/';
	for (i = 1; i < sizeof(fp->s_fsmnt); i++)
		fp->s_fsmnt[i] = 0;
E 24
D 12
	/* on boot, read VAX TODR register (GMT 10 ms.
	*	clicks into current year) and set software time
	*	in 'int time' (GMT seconds since year YRREF)
	*/
	for (i = 0 , j = YRREF ; j < YRCURR ; j++)
		i += (SECYR + (j%4?0:SECDAY)) ;
	time = udiv(mfpr(TODR),100) + i ;
E 12
I 12
	clkinit(fp->s_time);
E 12
	bootime = time;
E 42
I 42
	fp = bp->b_un.b_fs;
	if (fp->fs_magic != FS_MAGIC)
		panic("root bad magic number");
	if (fp->fs_bsize > MAXBSIZE)
		panic("root fs_bsize too big");
	fp->fs_ronly = 0;
	fp->fs_fsmnt[0] = '/';
	for (i = 1; i < sizeof(fp->fs_fsmnt); i++)
		fp->fs_fsmnt[i] = 0;
	blks = howmany(fp->fs_cssize, fp->fs_fsize);
	for (i = 0; i < blks; i += fp->fs_frag) {
		bp = bread(rootdev, fsbtodb(fp, fp->fs_csaddr + i),
		    blks - i < fp->fs_frag ?
			(blks - i) * fp->fs_fsize :
			fp->fs_bsize);
		if (u.u_error)
			panic("root can't read csum");
		fp->fs_csp[i / fp->fs_frag] = bp->b_un.b_cs;
		bp->b_flags |= B_LOCKED;
		brelse(bp);
	}
I 43
	clkinit(fp->fs_time);
	bootime = time;
E 44
D 124
}

I 119
/* MOVE TO vfs_bio.c (bufinit) XXX */
E 119
/*
D 119
 * Initialize hash links for buffers.
E 119
I 119
 * Initialize buffers and hash links for buffers.
E 119
 */
D 119
bhinit()
E 119
I 119
bufinit()
E 119
{
	register int i;
D 119
	register struct bufhd *bp;

	for (bp = bufhash, i = 0; i < BUFHSZ; i++, bp++)
		bp->b_forw = bp->b_back = (struct buf *)bp;
E 43
E 42
}

/*
D 23
 * This is the set of buffers proper, whose heads
 * were declared in buf.h.  There can exist buffer
 * headers not pointing here that are used purely
 * as arguments to the I/O routines to describe
 * I/O to be done-- e.g. swap headers swbuf[] for
 * swapping.
I 11
 *
 * These are actually allocated kernel map slots and space is
 * allocated in locore.s for them.
E 11
 */
D 3
char	buffers[NBUF][BSIZE+BSLOP];
E 3
I 3
char	buffers[NBUF][BSIZE];
E 3

/*
E 23
 * Initialize the buffer I/O system by freeing
 * all buffers and setting all device buffer lists to empty.
D 11
 *
 * SHOULD USE MEMALL HERE!!!
E 11
 */
binit()
{
E 119
D 53
	register struct buf *bp;
	register struct buf *dp;
E 53
I 53
	register struct buf *bp, *dp;
E 53
D 119
	register int i;
E 119
I 119
	register struct bufhd *hp;
E 119
D 53
	struct bdevsw *bdp;
E 53
I 6
D 88
	struct swdevt *swp;
E 88
I 58
	int base, residual;
E 58
E 6

I 119
	for (hp = bufhash, i = 0; i < BUFHSZ; i++, hp++)
		hp->b_forw = hp->b_back = (struct buf *)hp;

E 119
D 16
	bfreelist.b_forw = bfreelist.b_back =
	    bfreelist.av_forw = bfreelist.av_back = &bfreelist;
E 16
I 16
	for (dp = bfreelist; dp < &bfreelist[BQUEUES]; dp++) {
		dp->b_forw = dp->b_back = dp->av_forw = dp->av_back = dp;
		dp->b_flags = B_HEAD;
	}
I 58
	base = bufpages / nbuf;
	residual = bufpages % nbuf;
E 58
D 56
	dp--;				/* dp = &bfreelist[BQUEUES-1]; */
E 56
I 56
D 57
	dp = &bfreelist[BQ_AGE];
E 57
E 56
E 16
D 23
	for (i=0; i<NBUF; i++) {
E 23
I 23
D 42
	for (i=0; i<nbuf; i++) {
E 42
I 42
	for (i = 0; i < nbuf; i++) {
E 42
E 23
		bp = &buf[i];
		bp->b_dev = NODEV;
I 56
		bp->b_bcount = 0;
I 100
		bp->b_rcred = NOCRED;
		bp->b_wcred = NOCRED;
		bp->b_dirtyoff = 0;
		bp->b_dirtyend = 0;
E 100
I 57
D 66
#ifndef sun
E 66
E 57
E 56
D 23
		bp->b_un.b_addr = buffers[i];
E 23
I 23
D 42
		bp->b_un.b_addr = buffers + i * BSIZE;
E 42
I 42
		bp->b_un.b_addr = buffers + i * MAXBSIZE;
D 56
		bp->b_bcount = MAXBSIZE;
E 56
I 56
D 58
		bp->b_bufsize = 2 * CLBYTES;
E 58
I 58
		if (i < residual)
			bp->b_bufsize = (base + 1) * CLBYTES;
		else
			bp->b_bufsize = base * CLBYTES;
E 58
E 56
E 42
E 23
D 16
		bp->b_back = &bfreelist;
		bp->b_forw = bfreelist.b_forw;
		bfreelist.b_forw->b_back = bp;
		bfreelist.b_forw = bp;
		bp->b_flags = B_BUSY;
E 16
I 16
D 57
		bp->b_back = dp;
		bp->b_forw = dp->b_forw;
		dp->b_forw->b_back = bp;
		dp->b_forw = bp;
E 57
I 57
		binshash(bp, &bfreelist[BQ_AGE]);
D 66
#else
		bp->b_un.b_addr = (char *)0;
		bp->b_bufsize = 0;
		binshash(bp, &bfreelist[BQ_EMPTY]);
#endif
E 66
E 57
		bp->b_flags = B_BUSY|B_INVAL;
E 16
		brelse(bp);
D 119
	}
I 88
}

/*
 * Set up swap devices.
 * Initialize linked list of free swap
 * headers. These do not actually point
 * to buffers, but rather to pages that
 * are being swapped in and out.
 */
swapinit()
{
	register int i;
	register struct buf *sp = swbuf;
	struct swdevt *swp;
I 90
	int error;
E 90

E 88
D 18
	for (bdp = bdevsw; bdp->d_open; bdp++) {
		dp = bdp->d_tab;
		if(dp) {
			dp->b_forw = dp;
			dp->b_back = dp;
		}
E 18
I 18
D 53
	for (bdp = bdevsw; bdp->d_open; bdp++)
E 18
		nblkdev++;
E 53
D 18
	}
E 18
I 6
	/*
	 * Count swap devices, and adjust total swap space available.
D 88
	 * Some of this space will not be available until a vswapon()
E 88
I 88
	 * Some of this space will not be available until a swapon()
E 88
	 * system is issued, usually when the system goes multi-user.
	 */
	nswdev = 0;
D 63
	for (swp = swdevt; swp->sw_dev; swp++)
E 63
I 63
	nswap = 0;
	for (swp = swdevt; swp->sw_dev; swp++) {
E 63
		nswdev++;
I 63
		if (swp->sw_nblks > nswap)
			nswap = swp->sw_nblks;
	}
E 63
	if (nswdev == 0)
D 88
		panic("binit");
E 88
I 88
		panic("swapinit");
E 88
I 30
	if (nswdev > 1)
D 63
		nswap = (nswap/DMMAX)*DMMAX;
E 63
I 63
		nswap = ((nswap + dmmax - 1) / dmmax) * dmmax;
E 63
E 30
	nswap *= nswdev;
D 80
	maxpgio *= nswdev;
E 80
I 80
D 115
	/*
	 * If there are multiple swap areas,
	 * allow more paging operations per second.
	 */
	if (nswdev > 1)
		maxpgio = (maxpgio * (2 * nswdev - 1)) / 2;
E 115
I 94
	if (bdevvp(swdevt[0].sw_dev, &swdevt[0].sw_vp))
		panic("swapvp");
E 94
E 80
D 90
	swfree(0);
E 90
I 90
	if (error = swfree(0)) {
		printf("swfree errno %d\n", error);	/* XXX */
		panic("swapinit swfree 0");
	}
E 90
E 6
D 88
}
E 88

D 88
/*
 * Initialize linked list of free swap
 * headers. These do not actually point
 * to buffers, but rather to pages that
 * are being swapped in and out.
 */
bswinit()
{
	register int i;
I 22
D 23
	register struct buf *sp
E 23
I 23
	register struct buf *sp = swbuf;
E 23
E 22

E 88
I 88
	/*
	 * Now set up swap buffer headers.
	 */
E 88
D 22
	bswlist.av_forw = &swbuf[0];
	for (i=0; i<NSWBUF-1; i++)
		swbuf[i].av_forw = &swbuf[i+1];
	swbuf[NSWBUF-1].av_forw = NULL;
E 22
I 22
	bswlist.av_forw = sp;
D 23
	for (i=0; i<NSWBUF-1; i++, sp++)
E 23
I 23
	for (i=0; i<nswbuf-1; i++, sp++)
E 23
		sp->av_forw = sp+1;
	sp->av_forw = NULL;
E 22
}
I 21

/*
 * Initialize clist by freeing all character blocks, then count
 * number of character devices. (Once-only routine)
 */
cinit()
{
	register int ccp;
	register struct cblock *cp;
D 53
	register struct cdevsw *cdp;
E 53

	ccp = (int)cfree;
	ccp = (ccp+CROUND) & ~CROUND;
	for(cp=(struct cblock *)ccp; cp < &cfree[nclist-1]; cp++) {
		cp->c_next = cfreelist;
		cfreelist = cp;
		cfreecount += CBSIZE;
E 119
	}
E 124
D 53
	ccp = 0;
	for(cdp = cdevsw; cdp->d_open; cdp++)
		ccp++;
	nchrdev = ccp;
E 53
}
E 21
E 1
