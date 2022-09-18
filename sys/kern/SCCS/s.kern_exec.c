h43985
s 00002/00002/00748
d D 8.10 95/05/14 00:18:16 mckusick 117 116
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK
e
s 00001/00001/00749
d D 8.9 95/02/14 15:56:18 cgd 116 115
c fix a substitution error in the last commit.
e
s 00018/00013/00732
d D 8.8 95/02/14 10:17:44 cgd 115 114
c access syscall arguments in the new fashion.
e
s 00002/00002/00743
d D 8.7 94/08/11 00:24:32 mckusick 114 113
c LEASE_CHECK => VOP_LEASE
e
s 00005/00000/00740
d D 8.6 94/01/21 17:17:36 bostic 113 112
c add USL's copyright notice
e
s 00002/00000/00738
d D 8.5 94/01/14 16:00:51 hibler 112 111
c missing "ifdef KTRACE" around ktrace code
e
s 00007/00000/00731
d D 8.4 93/12/13 12:22:36 pendry 111 110
c add p_textvp to track vnode of executable (for procfs)
e
s 00010/00010/00721
d D 8.3 93/09/23 15:37:36 bostic 110 109
c changes for 4.4BSD-Lite requested by USL
e
s 00000/00006/00731
d D 8.2 93/09/20 23:18:39 mckusick 109 108
c execve_args definition moves to exec.h so it can be used in init_main.c
e
s 00002/00002/00735
d D 8.1 93/06/10 21:57:04 bostic 108 107
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00736
d D 7.76 93/05/11 20:59:36 akito 107 106
c support 68040 based luna68k
e
s 00002/00000/00735
d D 7.75 93/04/27 17:50:31 mckusick 106 105
c have to lock after the other namei too
e
s 00003/00001/00732
d D 7.74 93/04/27 16:13:39 mckusick 105 104
c bug fixes for LEASES from Rick Macklem
e
s 00000/00001/00733
d D 7.73 93/04/27 15:08:11 mckusick 104 103
c kinfo_proc.h is gone
e
s 00005/00003/00729
d D 7.72 93/03/09 10:56:23 hibler 103 102
c additional parameter to vm_mmap
e
s 00004/00000/00728
d D 7.71 93/02/13 16:37:08 ralph 102 101
c add a.out support for MIPS.
e
s 00001/00004/00727
d D 7.70 93/01/14 12:19:05 mckusick 101 100
c add and use killproc when cannot exec a new process
e
s 00017/00022/00714
d D 7.69 92/12/27 09:01:34 hibler 100 99
c cleanup hp300 code
e
s 00004/00009/00732
d D 7.68 92/12/26 15:26:05 bostic 99 98
c use ALIGN macro, minor cleanup
e
s 00007/00000/00734
d D 7.67 92/11/03 22:25:43 ralph 98 97
c mips needs to align stack on 8 byte boundary for doubles & long long.
e
s 00026/00026/00708
d D 7.66 92/10/11 10:38:01 bostic 97 96
c make kernel includes standard
e
s 00006/00005/00728
d D 7.65 92/07/10 20:48:20 torek 96 95
c ANSIfy syscall args
e
s 00000/00001/00733
d D 7.64 92/07/08 00:52:11 torek 95 94
c p_prof.pr_scale replaced by SPROFIL to show profiling in use
e
s 00000/00002/00734
d D 7.63 92/07/03 01:38:31 mckusick 94 93
c delete USES
e
s 00003/00001/00733
d D 7.62 92/06/23 19:58:05 mckusick 93 92
c set SUGID when granting setuid/setgid privilege (to avoid 
c unscrupulous use of attach)
e
s 00003/00003/00731
d D 7.61 92/06/23 17:11:05 mckusick 92 91
c MAP_FILE is now the default
e
s 00002/00000/00732
d D 7.60 92/06/20 11:58:17 mckusick 91 90
c turn off profiling if on
e
s 00001/00001/00731
d D 7.59 92/06/04 17:04:30 hibler 90 89
c change include path for HP code reorg
e
s 00001/00001/00731
d D 7.58 92/06/04 14:48:25 mckusick 89 88
c support for luna68k from Omron
e
s 00001/00001/00731
d D 7.57 92/05/29 14:23:23 mccanne 88 87
c fixed bug introduced in rev 7.52: vm_ssize is in pages not bytes.
e
s 00002/00000/00730
d D 7.56 92/05/14 17:32:11 heideman 87 78
c vnode interface conversion
e
s 00002/00000/00730
d R 7.56 92/05/14 15:46:00 heideman 86 78
c vnode interface conversion
e
s 00002/00000/00730
d R 7.56 92/05/14 14:51:13 heideman 85 78
c vnode interface conversion
e
s 00002/00000/00730
d R 7.56 92/05/14 12:55:23 heideman 84 78
c vnode interface conversion
e
s 00002/00000/00730
d R 7.56 92/05/14 11:52:49 heideman 83 78
c vnode interface conversion
e
s 00002/00000/00730
d R 7.56 92/05/14 10:33:00 heideman 82 78
c vnode interface conversion
e
s 00002/00000/00730
d R 7.56 92/05/13 23:11:47 heideman 81 78
c vnode interface conversion
e
s 00002/00000/00730
d R 7.56 92/05/13 18:57:39 heideman 80 78
c vnode interface conversion
e
s 00002/00000/00730
d R 7.56 92/05/13 18:29:47 heideman 79 78
c vnode interface conversion
e
s 00006/00005/00724
d D 7.55 92/05/04 15:41:16 mckusick 78 77
c lint
e
s 00013/00004/00716
d D 7.54 92/04/03 14:57:21 mckusick 77 76
c update from Chris Torek to add argument pointer at known location
e
s 00007/00006/00713
d D 7.53 92/03/03 23:35:02 mckusick 76 75
c fix problem with window system failing to start up (from hibler)
e
s 00080/00030/00639
d D 7.52 92/02/15 22:51:33 torek 75 74
c generalizations to support sparc
e
s 00001/00001/00668
d D 7.51 92/02/05 17:10:11 mckusick 74 73
c setting stack is CPU dependent
e
s 00015/00018/00654
d D 7.50 92/02/05 17:06:24 mckusick 73 72
c new namei calling convention
e
s 00000/00001/00672
d D 7.49 91/11/19 23:48:57 torek 72 71
c purge seg.h
e
s 00064/00005/00609
d D 7.48 91/09/07 13:31:23 ralph 71 70
c added COFF support for pmax
e
s 00002/00012/00612
d D 7.47 91/06/21 10:44:05 mckusick 70 69
c just check v_writecount rather than searching the file table 
c to find out if a file is open for writing
e
s 00001/00001/00623
d D 7.46 91/06/03 20:25:39 mckusick 69 68
c file structures are now dynamically allocated and linked together on a list
e
s 00008/00016/00616
d D 7.45 91/05/15 19:27:32 mckusick 68 67
c program name now returned in ni_ptr instead of ni_dent
e
s 00004/00000/00628
d D 7.44 91/05/12 16:38:15 william 67 66
c two minor fixes for 386; others unaffected
e
s 00005/00004/00623
d D 7.43 91/05/09 21:18:15 bostic 66 65
c new copyright; att/bsd/shared
e
s 00012/00006/00615
d D 7.42 91/05/09 19:51:28 william 65 64
c added p to setregs. Also, deallocation limied to MAXUSR
e
s 00021/00013/00600
d D 7.41 91/05/01 19:02:26 karels 64 63
c remove u. entirely (p_addr is struct user *); only copy sigcode if COPY_SIGCODE
c is defined, and then don't put sigcode in pcb
e
s 00009/00007/00604
d D 7.40 91/04/15 23:46:28 mckusick 63 62
c add proc pointers to appropriate VOP operations
e
s 00018/00012/00593
d D 7.39 91/04/02 10:11:05 karels 62 61
c don't need SPAGV on proc; rm other obsol. proc flags
e
s 00000/00016/00605
d D 7.38 91/03/25 13:41:04 karels 61 60
c don't need compat_43 execv, 4.3 used execve for execv
e
s 00044/00022/00577
d D 7.37 91/03/25 12:24:23 karels 60 59
c clean up includes, rm OFILE*, release vmspace instead of replacing if shared,
c minor cleanups
e
s 00059/00063/00540
d D 7.36 91/03/17 15:41:54 karels 59 58
c more-or-less working with new proc & user structs
e
s 00014/00012/00589
d D 7.35 91/01/10 23:43:52 mckusick 58 57
c add dynamically allocated file descriptors
e
s 00001/00001/00600
d D 7.34 90/12/16 22:01:36 mckusick 57 56
c new pathname for hpux
e
s 00105/00167/00496
d D 7.33 90/12/05 16:34:18 mckusick 56 55
c update for new VM
e
s 00002/00002/00661
d D 7.32 90/10/19 16:29:08 mckusick 55 54
c copyinstr/copyoutstr now return ENAMETOOLONG when name is too long
e
s 00012/00001/00651
d D 7.31 90/10/19 15:51:29 marc 54 53
c turn off tracing on setuid and setgid programs if not root
e
s 00003/00000/00649
d D 7.30 90/06/30 19:29:16 william 53 52
c i386 support for kernel addition
e
s 00001/00011/00648
d D 7.29 90/06/28 21:18:51 bostic 52 51
c new copyright notice
e
s 00005/00005/00654
d D 7.28 90/06/28 17:10:11 karels 51 50
c RETURN => return, remove syscontext.h
e
s 00002/00001/00657
d D 7.27 90/06/26 21:58:04 hibler 50 49
c make sure vp->v_text is set before dereferencing
e
s 00001/00001/00657
d D 7.26 90/06/21 22:24:40 mckusick 49 48
c allow values to be returned from setregs
e
s 00074/00069/00584
d D 7.25 90/06/05 22:01:54 mckusick 48 47
c update to new system call convention; expunge more u.u_error
e
s 00002/00002/00651
d D 7.24 90/05/15 22:05:08 bostic 47 46
c rename size_t to segsz_t for ANSI C
e
s 00130/00019/00523
d D 7.23 90/05/15 21:37:30 mckusick 46 45
c "update for hp300 support from Utah"
e
s 00002/00002/00540
d D 7.22 90/05/04 20:55:25 mckusick 45 44
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00018/00000/00524
d D 7.21 90/02/23 17:00:48 mckusick 44 43
c check for modified text file and take appropriate action
e
s 00002/00002/00522
d D 7.20 90/02/22 16:20:26 marc 43 42
c u_comm moved to proc
e
s 00002/00004/00522
d D 7.19 90/01/04 22:23:17 mckusick 42 41
c discard argdev buffers instead of aging them
e
s 00001/00001/00525
d D 7.18 89/12/29 10:22:03 mckusick 41 40
c v_count => v_usecount
e
s 00001/00001/00525
d D 7.17 89/11/13 11:14:31 mckusick 40 39
c return error from copying in arg list, not from throwing it away
e
s 00001/00003/00525
d D 7.16 89/11/10 12:32:29 mckusick 39 38
c vinifod now kills process if errors occur during mapping
e
s 00001/00001/00527
d D 7.15 89/10/19 23:34:11 mckusick 38 37
c closef now returns and error (which is ignored)
e
s 00001/00001/00527
d D 7.14 89/10/19 22:47:08 mckusick 37 36
c use EACCES rather than ENOEXEC for "noexec" option so that shells
c do not attempt to execute the programs as shell scripts
e
s 00033/00045/00495
d D 7.13 89/09/03 18:17:46 karels 36 35
c move signal processing to kern_sig; add saved uid, gid;
c use register proc pointer instead of u.u_procp
e
s 00003/00002/00537
d D 7.12 89/08/26 13:01:13 mckusick 35 34
c bread and baddr now require a credential structure
e
s 00002/00002/00537
d D 7.11 89/07/03 17:54:46 mckusick 34 33
c use VOP_ACCESS directly
e
s 00088/00054/00451
d D 7.10 89/05/09 17:02:10 mckusick 33 32
c merge in vnodes
e
s 00005/00005/00500
d D 7.9 89/04/25 14:42:19 mckusick 32 31
c ../machine => machine
e
s 00001/00001/00504
d D 7.8 88/10/18 15:14:35 marc 31 30
c posix style job control - new process groups
e
s 00002/00002/00503
d D 7.7 88/06/05 15:39:39 karels 30 29
c another gratuitous change gone awry
e
s 00014/00008/00491
d D 7.6 88/05/25 09:11:45 karels 29 28
c clean up after bostic (remove gratuitous reformatting)
e
s 00017/00023/00482
d D 7.5 88/05/22 14:05:14 bostic 28 27
c shell scripts can't be setuid
e
s 00003/00003/00502
d D 7.4 87/04/02 15:49:01 karels 27 25
c working with pack labels
e
s 00030/00003/00502
d D 7.3.1.1 87/04/02 15:40:58 karels 26 25
c add ifdefs for dev_bsize (almost working)
e
s 00004/00005/00501
d D 7.3 87/03/03 22:25:43 bostic 25 24
c changed SHSIZE to MAXINTERP
e
s 00018/00005/00488
d D 7.2 86/11/03 11:59:36 karels 24 23
c merge in tahoe support
e
s 00001/00001/00492
d D 7.1 86/06/05 00:02:21 mckusick 23 22
c 4.3BSD release version
e
s 00011/00008/00482
d D 6.17 86/02/23 23:08:40 karels 22 21
c lint
e
s 00001/00001/00489
d D 6.16 86/02/19 17:52:25 karels 21 20
c lint
e
s 00001/00001/00489
d D 6.15 85/11/26 12:37:15 karels 20 19
c now can use XTRC again instead of IXMOD
e
s 00001/00001/00489
d D 6.14 85/08/12 15:20:56 bloom 19 18
c arglist or envlist containing -1 caused panic
e
s 00007/00001/00483
d D 6.13 85/06/08 14:35:38 mckusick 18 17
c Add copyright
e
s 00060/00065/00424
d D 6.12 85/05/27 19:57:26 karels 17 16
c change argv[0] for executable scripts to be name of interpretter;
c reorder file closes on exec (avoid wedging when a.out is open and CLEX);
c split setregs to exec and machine-dependent part;
c implement high-water mark on file descriptors in use
e
s 00006/00002/00483
d D 6.11 85/05/27 16:23:13 mckusick 16 15
c must be careful to check bss and data sizes separately to avoid
c problems if their sum overflows
e
s 00002/00002/00483
d D 6.10 85/03/12 18:12:58 mckusick 15 14
c make swkill messages more informative
e
s 00007/00000/00478
d D 6.9 85/03/12 14:59:40 mckusick 14 13
c reset signal stack on exec()
e
s 00004/00000/00474
d D 6.8 84/11/20 11:23:55 karels 13 12
c (ugly) changes to avoid executing/writing traced text segments
c (need regions done right!)
e
s 00016/00016/00458
d D 6.7 84/08/29 20:19:16 bloom 12 11
c Change to includes.  no more ../h
e
s 00012/00006/00462
d D 6.6 84/07/29 18:37:57 sam 11 10
c complete revised argument processing -- use copyoutstr to move 
c arguments from swap space to user space
e
s 00054/00040/00414
d D 6.5 84/07/23 16:39:36 sam 10 9
c use copyinstr and copystr (add copyoutstr later)
e
s 00038/00029/00416
d D 6.4 84/07/21 17:24:16 sam 9 8
c remove a.out header from u. area
e
s 00023/00020/00422
d D 6.3 84/07/08 16:18:36 mckusick 8 7
c rework `namei' interface to eliminate global variables
e
s 00001/00000/00441
d D 6.2 83/08/23 11:44:45 karels 7 6
c turn off profiling at exec
e
s 00000/00000/00441
d D 6.1 83/07/29 06:32:51 sam 6 5
c 4.2 distribution
e
s 00004/00017/00437
d D 4.5 83/07/01 02:18:18 sam 5 4
c purge #if sun's
e
s 00001/00001/00453
d D 4.4 83/06/14 01:37:02 sam 4 3
c revamp locking to be done at the file table level
e
s 00015/00013/00439
d D 4.3 83/06/12 12:47:36 sam 3 2
c mask remains so we can safely reset signals held across exec
e
s 00007/00024/00445
d D 4.2 83/06/02 15:56:40 sam 2 1
c new signals
e
s 00469/00000/00000
d D 4.1 83/05/27 14:02:42 sam 1 0
c date and time created 83/05/27 14:02:42 by sam
e
u
U
f b 
t
T
I 1
D 18
/*	%M%	%I%	%E%	*/
E 18
I 18
D 66
/*
D 23
 * Copyright (c) 1982 Regents of the University of California.
E 23
I 23
D 33
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 23
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 33
I 33
D 60
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 60
I 60
 * Copyright (c) 1982, 1986, 1989, 1991 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 66
I 66
/*-
D 108
 * Copyright (c) 1982, 1986, 1991 The Regents of the University of California.
 * All rights reserved.
E 108
I 108
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 113
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 113
E 108
 *
 * %sccs.include.proprietary.c%
E 66
E 60
E 33
 *
I 33
D 52
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
E 52
I 52
D 60
 * %sccs.include.redist.c%
E 52
 *
E 60
E 33
 *	%W% (Berkeley) %G%
 */
E 18

D 32
#include "../machine/reg.h"
#include "../machine/pte.h"
#include "../machine/psl.h"
I 24
#include "../machine/mtpr.h"
E 24

E 32
D 12
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/map.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/kernel.h"
#include "../h/proc.h"
#include "../h/buf.h"
#include "../h/inode.h"
#include "../h/seg.h"
#include "../h/vm.h"
#include "../h/text.h"
#include "../h/file.h"
#include "../h/uio.h"
D 8
#include "../h/nami.h"
E 8
#include "../h/acct.h"
I 9
#include "../h/exec.h"
E 12
I 12
D 97
#include "param.h"
#include "systm.h"
D 56
#include "map.h"
E 56
D 33
#include "dir.h"
E 33
D 48
#include "user.h"
E 48
I 48
D 51
#include "syscontext.h"
E 51
I 51
D 60
#include "user.h"
E 60
I 58
#include "filedesc.h"
E 58
E 51
E 48
#include "kernel.h"
#include "proc.h"
I 33
#include "mount.h"
D 60
#include "ucred.h"
E 60
#include "malloc.h"
I 63
#include "namei.h"
E 63
E 33
D 56
#include "buf.h"
E 56
D 33
#include "inode.h"
E 33
I 33
#include "vnode.h"
E 33
D 72
#include "seg.h"
E 72
D 56
#include "vm.h"
#include "text.h"
E 56
#include "file.h"
D 60
#include "uio.h"
E 60
#include "acct.h"
#include "exec.h"
I 54
#include "ktrace.h"
I 60
#include "resourcevar.h"
E 97
I 97
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/filedesc.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/mount.h>
#include <sys/malloc.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/file.h>
#include <sys/acct.h>
#include <sys/exec.h>
#include <sys/ktrace.h>
#include <sys/resourcevar.h>
I 115
#include <sys/syscallargs.h>
E 115
E 97
E 60
E 54
I 32

I 64
D 97
#include "machine/cpu.h"
E 64
#include "machine/reg.h"
E 97
I 97
#include <machine/cpu.h>
#include <machine/reg.h>
E 97
D 56
#include "machine/pte.h"
E 56
D 59
#include "machine/psl.h"
#include "machine/mtpr.h"
E 59
E 32
E 12
E 9

I 56
D 97
#include "mman.h"
D 59
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_kern.h"
#include "../vm/vm_pager.h"
E 59
I 59
#include "vm/vm.h"
#include "vm/vm_param.h"
#include "vm/vm_map.h"
#include "vm/vm_kern.h"
#include "vm/vm_pager.h"
E 97
I 97
#include <sys/mman.h>
#include <vm/vm.h>
#include <vm/vm_param.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <vm/vm_pager.h>
E 97
E 59

I 60
D 97
#include "signalvar.h"
#include "kinfo_proc.h"
E 97
I 97
#include <sys/signalvar.h>
D 104
#include <sys/kinfo_proc.h>
E 104
E 97
D 64
#include "user.h"			/* for pcb, sigc */
E 64

E 60
E 56
I 46
#ifdef HPUXCOMPAT
I 64
D 97
#include "user.h"			/* for pcb */
E 64
D 57
#include "../hpux/hpux_exec.h"
E 57
I 57
D 90
#include "hp300/hpux/hpux_exec.h"
E 90
I 90
#include "hp/hpux/hpux_exec.h"
E 97
I 97
#include <sys/user.h>			/* for pcb */
#include <hp/hpux/hpux_exec.h>
E 97
E 90
E 57
#endif

I 64
#ifdef COPY_SIGCODE
extern char sigcode[], esigcode[];
#define	szsigcode	(esigcode - sigcode)
#else
#define	szsigcode	0
#endif

E 64
E 46
I 5
D 24
#ifdef vax
#include "../vax/mtpr.h"
#endif

E 24
E 5
D 59
/*
 * exec system call, with and without environments.
 */
E 59
I 59
D 61
#ifdef COMPAT_43
E 59
D 48
struct execa {
	char	*fname;
	char	**argp;
	char	**envp;
};

execv()
E 48
I 48
execv(p, uap, retval)
	struct proc *p;
	struct args {
		char	*fname;
		char	**argp;
		char	**envp;
	} *uap;
	int *retval;
E 48
{
D 48
	((struct execa *)u.u_ap)->envp = NULL;
	execve();
E 48
I 48

	uap->envp = NULL;
D 51
	RETURN (execve(p, uap, retval));
E 51
I 51
	return (execve(p, uap, retval));
E 51
E 48
}
I 59
#endif
E 59

E 61
I 59
/*
 * exec system call
 */
I 96
D 109
struct execve_args {
	char	*fname;
	char	**argp;
	char	**envp;
};
E 96
E 59
D 48
execve()
E 48
I 48
/* ARGSUSED */
E 109
execve(p, uap, retval)
	register struct proc *p;
D 96
	register struct args {
		char	*fname;
		char	**argp;
		char	**envp;
	} *uap;
E 96
I 96
D 115
	register struct execve_args *uap;
E 96
	int *retval;
E 115
I 115
	register struct execve_args /* {
		syscallarg(char *) path;
		syscallarg(char **) argp;  
		syscallarg(char **) envp;
	} */ *uap;      
	register_t *retval;
E 115
E 48
{
I 87
D 94
	USES_VOP_ACCESS;
	USES_VOP_GETATTR;
E 94
E 87
D 58
	register nc;
	register char *cp;
E 58
I 58
D 59
	register struct ucred *cred = u.u_cred;
	register struct nameidata *ndp = &u.u_nd;
E 59
I 59
	register struct ucred *cred = p->p_ucred;
D 73
	register struct nameidata *ndp;
E 73
E 59
	register struct filedesc *fdp = p->p_fd;
E 58
D 56
	register struct buf *bp;
I 33
	struct buf *tbp;
E 56
E 33
D 48
	register struct execa *uap;
E 48
D 10
	int na, ne, ucp, ap, c;
E 10
I 10
D 22
	int na, ne, ucp, ap, len, cc;
E 22
I 22
D 75
	int na, ne, ucp, ap, cc;
E 75
I 75
	int na, ne, ucp, ap, cc, ssize;
E 75
I 58
	register char *cp;
	register int nc;
E 58
	unsigned len;
E 22
E 10
	int indir, uid, gid;
	char *sharg;
D 33
	struct inode *ip;
E 33
I 33
	struct vnode *vp;
I 59
D 62
	int resid, error, flags = 0;
E 62
I 62
	int resid, error, paged = 0;
E 62
D 71
	vm_offset_t execargs;
E 71
I 71
	vm_offset_t execargs = 0;
E 71
E 59
E 33
D 56
	swblk_t bno;
E 56
I 33
	struct vattr vattr;
E 33
D 68
	char cfname[MAXCOMLEN + 1];
E 68
I 9
D 25
#define	SHSIZE	32
E 9
	char cfarg[SHSIZE];
E 25
I 25
	char cfarg[MAXINTERP];
E 25
I 9
	union {
D 25
		char	ex_shell[SHSIZE];	/* #! and name of interpreter */
E 25
I 25
		char	ex_shell[MAXINTERP];	/* #! and interpreter name */
E 25
		struct	exec ex_exec;
I 46
#ifdef HPUXCOMPAT
		struct	hpux_exec ex_hexec;
#endif
E 46
	} exdata;
I 46
#ifdef HPUXCOMPAT
	struct hpux_exec hhead;
#endif
I 48
D 58
	register struct ucred *cred = u.u_cred;
E 48
E 46
E 9
I 8
	register struct nameidata *ndp = &u.u_nd;
E 58
E 8
D 10
	int resid;
E 10
I 10
D 46
	int resid, error;
E 46
I 46
D 59
	int resid, error, flags = 0;
I 56
	vm_offset_t execargs;
E 59
I 59
	struct nameidata nd;
I 77
	struct ps_strings ps;
E 77
E 59
E 56
E 46
I 26
#ifdef SECSIZE
	extern long argdbsize;			/* XXX */
#endif SECSIZE
E 26
E 10

I 59
D 73
	ndp = &nd;
E 59
I 44
D 68
  start:
E 44
D 8
	if ((ip = namei(uchar, LOOKUP, 1)) == NULL)
E 8
I 8
D 33
	ndp->ni_nameiop = LOOKUP | FOLLOW;
E 33
I 33
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
E 68
I 68
	ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF | SAVENAME;
E 68
E 33
	ndp->ni_segflg = UIO_USERSPACE;
D 48
	ndp->ni_dirp = ((struct execa *)u.u_ap)->fname;
D 33
	if ((ip = namei(ndp)) == NULL)
E 33
I 33
	if (u.u_error = namei(ndp)) {
E 33
E 8
		return;
I 33
	}
E 48
I 48
	ndp->ni_dirp = uap->fname;
D 59
	if (error = namei(ndp))
E 59
I 59
	if (error = namei(ndp, p))
E 73
I 73
D 105
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF | SAVENAME, UIO_USERSPACE,
E 105
I 105
	NDINIT(&nd, LOOKUP, FOLLOW | SAVENAME, UIO_USERSPACE,
E 105
D 115
		uap->fname, p);
E 115
I 115
		SCARG(uap, path), p);
E 115
	if (error = namei(&nd))
E 73
E 59
D 51
		RETURN (error);
E 51
I 51
		return (error);
E 51
E 48
D 73
	vp = ndp->ni_vp;
E 73
I 73
	vp = nd.ni_vp;
I 105
D 114
	LEASE_CHECK(vp, p, cred, LEASE_READ);
E 114
I 114
	VOP_LEASE(vp, p, cred, LEASE_READ);
E 114
D 117
	VOP_LOCK(vp);
E 117
I 117
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 117
E 105
E 73
E 33
D 56
	bno = 0;
	bp = 0;
E 56
	indir = 0;
D 36
	uid = u.u_uid;
	gid = u.u_gid;
E 36
I 36
D 48
	uid = u.u_cred->cr_uid;
	gid = u.u_cred->cr_gid;
E 36
D 33
	if (ip->i_mode & ISUID)
		uid = ip->i_uid;
	if (ip->i_mode & ISGID)
		gid = ip->i_gid;
E 33
I 33
	if (u.u_error = VOP_GETATTR(vp, &vattr, u.u_cred))
E 48
I 48
	uid = cred->cr_uid;
	gid = cred->cr_gid;
D 63
	if (error = VOP_GETATTR(vp, &vattr, cred))
E 63
I 63
	if (error = VOP_GETATTR(vp, &vattr, cred, p))
E 63
E 48
		goto bad;
D 45
	if (vp->v_mount->m_flag & M_NOEXEC) {
E 45
I 45
	if (vp->v_mount->mnt_flag & MNT_NOEXEC) {
E 45
D 37
		u.u_error = ENOEXEC;
E 37
I 37
D 48
		u.u_error = EACCES;
E 48
I 48
		error = EACCES;
E 48
E 37
		goto bad;
	}
D 45
	if ((vp->v_mount->m_flag & M_NOSUID) == 0) {
E 45
I 45
	if ((vp->v_mount->mnt_flag & MNT_NOSUID) == 0) {
E 45
		if (vattr.va_mode & VSUID)
			uid = vattr.va_uid;
		if (vattr.va_mode & VSGID)
			gid = vattr.va_gid;
	}
E 33

  again:
D 33
	if (access(ip, IEXEC))
E 33
I 33
D 34
	if (u.u_error = vn_access(vp, VEXEC, u.u_cred))
E 34
I 34
D 48
	if (u.u_error = VOP_ACCESS(vp, VEXEC, u.u_cred))
E 48
I 48
D 63
	if (error = VOP_ACCESS(vp, VEXEC, cred))
E 63
I 63
	if (error = VOP_ACCESS(vp, VEXEC, cred, p))
E 63
E 48
E 34
E 33
		goto bad;
D 33
	if ((u.u_procp->p_flag&STRC) && access(ip, IREAD))
E 33
I 33
D 48
	if ((u.u_procp->p_flag & STRC) &&
D 34
	    (u.u_error = vn_access(vp, VREAD, u.u_cred)))
E 34
I 34
	    (u.u_error = VOP_ACCESS(vp, VREAD, u.u_cred)))
E 48
I 48
D 63
	if ((p->p_flag & STRC) && (error = VOP_ACCESS(vp, VREAD, cred)))
E 63
I 63
D 110
	if ((p->p_flag & STRC) && (error = VOP_ACCESS(vp, VREAD, cred, p)))
E 110
I 110
	if ((p->p_flag & P_TRACED) && (error = VOP_ACCESS(vp, VREAD, cred, p)))
E 110
E 63
E 48
E 34
E 33
		goto bad;
D 33
	if ((ip->i_mode & IFMT) != IFREG ||
	   (ip->i_mode & (IEXEC|(IEXEC>>3)|(IEXEC>>6))) == 0) {
E 33
I 33
	if (vp->v_type != VREG ||
	    (vattr.va_mode & (VEXEC|(VEXEC>>3)|(VEXEC>>6))) == 0) {
E 33
D 48
		u.u_error = EACCES;
E 48
I 48
		error = EACCES;
E 48
		goto bad;
	}

	/*
D 10
	 * Read in first few bytes of file for segment sizes, ux_mag:
E 10
I 10
	 * Read in first few bytes of file for segment sizes, magic number:
E 10
D 33
	 *	407 = plain executable
	 *	410 = RO text
	 *	413 = demand paged RO text
E 33
I 33
	 *	OMAGIC = plain executable
	 *	NMAGIC = RO text
	 *	ZMAGIC = demand paged RO text
E 33
	 * Also an ASCII line beginning with #! is
	 * the file name of a ``shell'' and arguments may be prepended
	 * to the argument list if given here.
	 *
	 * SHELL NAMES ARE LIMITED IN LENGTH.
	 *
	 * ONLY ONE ARGUMENT MAY BE PASSED TO THE SHELL FROM
	 * THE ASCII LINE.
	 */
D 9
	u.u_exdata.ux_shell[0] = 0;	/* for zero length files */
	u.u_error = rdwri(UIO_READ, ip, (caddr_t)&u.u_exdata, sizeof (u.u_exdata),
	    0, 1, &resid);
E 9
I 9
	exdata.ex_shell[0] = '\0';	/* for zero length files */
D 10
	u.u_error = rdwri(UIO_READ, ip, (caddr_t)&exdata,
	   sizeof (struct exec), 0, 1, &resid);
E 10
I 10
D 33
	u.u_error = rdwri(UIO_READ, ip, (caddr_t)&exdata, sizeof (exdata),
D 22
	    0, 1, &resid);
E 22
I 22
	    (off_t)0, 1, &resid);
E 33
I 33
D 48
	u.u_error = vn_rdwr(UIO_READ, vp, (caddr_t)&exdata, sizeof (exdata),
	    (off_t)0, UIO_SYSSPACE, (IO_UNIT|IO_NODELOCKED), u.u_cred, &resid);
E 33
E 22
E 10
E 9
	if (u.u_error)
E 48
I 48
	error = vn_rdwr(UIO_READ, vp, (caddr_t)&exdata, sizeof (exdata),
D 63
	    (off_t)0, UIO_SYSSPACE, (IO_UNIT|IO_NODELOCKED), cred, &resid);
E 63
I 63
	    (off_t)0, UIO_SYSSPACE, (IO_UNIT|IO_NODELOCKED), cred, &resid,
	    (struct proc *)0);
E 63
	if (error)
E 48
		goto bad;
D 8
	u.u_count = resid;
E 8
#ifndef lint
D 8
	if (u.u_count > sizeof(u.u_exdata) - sizeof(u.u_exdata.Ux_A) &&
E 8
I 8
D 9
	if (resid > sizeof(u.u_exdata) - sizeof(u.u_exdata.Ux_A) &&
E 8
	    u.u_exdata.ux_shell[0] != '#') {
E 9
I 9
D 10
	if (resid > sizeof (struct exec) - sizeof (exdata.ex_exec.a_magic) &&
E 10
I 10
D 17
	if (resid > sizeof (exdata) - sizeof (exdata.ex_exec.a_magic) &&
E 17
I 17
	if (resid > sizeof(exdata) - sizeof(exdata.ex_exec) &&
E 17
E 10
	    exdata.ex_shell[0] != '#') {
E 9
D 48
		u.u_error = ENOEXEC;
E 48
I 48
		error = ENOEXEC;
E 48
		goto bad;
	}
#endif
I 46
D 89
#if defined(hp300)
E 89
I 89
#if defined(hp300) || defined(luna68k)
E 89
	switch ((int)exdata.ex_exec.a_mid) {

	/*
	 * An ancient hp200 or hp300 binary, shouldn't happen anymore.
	 * Mark as invalid.
	 */
	case MID_ZERO:
		exdata.ex_exec.a_magic = 0;
		break;

	/*
	 * HP200 series has a smaller page size so we cannot
	 * demand-load or even write protect text, so we just
	 * treat as OMAGIC.
	 */
	case MID_HP200:
		exdata.ex_exec.a_magic = OMAGIC;
		break;

	case MID_HP300:
		break;

#ifdef HPUXCOMPAT
	case MID_HPUX:
		/*
		 * Save a.out header.  This is eventually saved in the pcb,
		 * but we cannot do that yet in case the exec fails before
		 * the image is overlayed.
		 */
		bcopy((caddr_t)&exdata.ex_hexec,
		      (caddr_t)&hhead, sizeof hhead);
		/*
D 100
		 * If version number is 0x2bad this is a native BSD
		 * binary created via the HPUX SGS.  Should not be
		 * treated as an HPUX binary.
		 */
		if (exdata.ex_hexec.ha_version != BSDVNUM)
D 62
			flags |= SHPUX;
E 62
I 62
			paged |= SHPUX;				/* XXX */
E 62
		/*
E 100
		 * Shuffle important fields to their BSD locations.
		 * Note that the order in which this is done is important.
		 */
		exdata.ex_exec.a_text = exdata.ex_hexec.ha_text;
		exdata.ex_exec.a_data = exdata.ex_hexec.ha_data;
		exdata.ex_exec.a_bss = exdata.ex_hexec.ha_bss;
		exdata.ex_exec.a_entry = exdata.ex_hexec.ha_entry;
		/*
		 * For ZMAGIC files, make sizes consistant with those
		 * generated by BSD ld.
		 */
		if (exdata.ex_exec.a_magic == ZMAGIC) {
			exdata.ex_exec.a_text = 
				ctob(btoc(exdata.ex_exec.a_text));
			nc = exdata.ex_exec.a_data + exdata.ex_exec.a_bss;
			exdata.ex_exec.a_data =
				ctob(btoc(exdata.ex_exec.a_data));
			nc -= (int)exdata.ex_exec.a_data;
			exdata.ex_exec.a_bss = (nc < 0) ? 0 : nc;
		}
		break;
#endif
	}
#endif
E 46
D 9
	switch (u.u_exdata.ux_mag) {
E 9
I 9
D 21
	switch (exdata.ex_exec.a_magic) {
E 21
I 21
	switch ((int)exdata.ex_exec.a_magic) {
E 21
E 9

D 33
	case 0407:
E 33
I 33
	case OMAGIC:
I 71
#ifdef COFF
		if (exdata.ex_exec.ex_fhdr.magic != COFF_MAGIC) {
			error = ENOEXEC;
			goto bad;
		}
#endif
I 75
#ifdef sparc
		if (exdata.ex_exec.a_mid != MID_SUN_SPARC) {
			error = ENOEXEC;
			goto bad;
		}
#endif
E 75
E 71
E 33
D 9
		u.u_exdata.ux_dsize += u.u_exdata.ux_tsize;
		u.u_exdata.ux_tsize = 0;
E 9
I 9
		exdata.ex_exec.a_data += exdata.ex_exec.a_text;
		exdata.ex_exec.a_text = 0;
E 9
		break;

D 33
	case 0413:
	case 0410:
E 33
I 33
	case ZMAGIC:
I 76
D 100
#ifdef HPUXCOMPAT
		paged |= 1;	/* XXX fix me */
#else
E 100
E 76
I 46
D 62
		flags |= SPAGV;
E 62
I 62
D 75
		paged++;
E 75
I 75
		paged = 1;
I 76
D 100
#endif
E 100
E 76
E 75
		/* FALLTHROUGH */
I 75

E 75
E 62
E 46
	case NMAGIC:
I 71
#ifdef COFF
		if (exdata.ex_exec.ex_fhdr.magic != COFF_MAGIC) {
			error = ENOEXEC;
			goto bad;
		}
#endif
I 75
#ifdef sparc
		if (exdata.ex_exec.a_mid != MID_SUN_SPARC) {
			error = ENOEXEC;
			goto bad;
		}
#endif
E 75
E 71
E 33
D 9
		if (u.u_exdata.ux_tsize == 0) {
E 9
I 9
		if (exdata.ex_exec.a_text == 0) {
E 9
D 48
			u.u_error = ENOEXEC;
E 48
I 48
			error = ENOEXEC;
E 48
			goto bad;
		}
		break;

	default:
D 9
		if (u.u_exdata.ux_shell[0] != '#' ||
		    u.u_exdata.ux_shell[1] != '!' ||
E 9
I 9
D 28
		if (exdata.ex_shell[0] != '#' ||
		    exdata.ex_shell[1] != '!' ||
E 9
		    indir) {
E 28
I 28
D 29
		if (exdata.ex_shell[0] != '#' || exdata.ex_shell[1] != '!' ||
		    indir++) {
E 29
I 29
		if (exdata.ex_shell[0] != '#' ||
		    exdata.ex_shell[1] != '!' ||
		    indir) {
E 29
E 28
D 48
			u.u_error = ENOEXEC;
E 48
I 48
			error = ENOEXEC;
E 48
			goto bad;
		}
D 9
		cp = &u.u_exdata.ux_shell[2];		/* skip "#!" */
		while (cp < &u.u_exdata.ux_shell[SHSIZE]) {
E 9
I 9
D 28
		cp = &exdata.ex_shell[2];		/* skip "#!" */
D 25
		while (cp < &exdata.ex_shell[SHSIZE]) {
E 25
I 25
		while (cp < &exdata.ex_shell[MAXINTERP]) {
E 25
E 9
			if (*cp == '\t')
				*cp = ' ';
			else if (*cp == '\n') {
E 28
I 28
		for (cp = &exdata.ex_shell[2];; ++cp) {
D 29
			if (cp == &exdata.ex_shell[MAXINTERP]) {
E 29
I 29
			if (cp >= &exdata.ex_shell[MAXINTERP]) {
E 29
D 48
				u.u_error = ENOEXEC;
E 48
I 48
				error = ENOEXEC;
E 48
				goto bad;
			}
			if (*cp == '\n') {
E 28
				*cp = '\0';
				break;
			}
D 28
			cp++;
E 28
I 28
			if (*cp == '\t')
				*cp = ' ';
E 28
		}
D 28
		if (*cp != '\0') {
			u.u_error = ENOEXEC;
			goto bad;
		}
D 9
		cp = &u.u_exdata.ux_shell[2];
E 9
I 9
		cp = &exdata.ex_shell[2];
E 9
		while (*cp == ' ')
			cp++;
E 28
I 28
D 29
		for (cp = &exdata.ex_shell[2]; *cp == ' '; ++cp);
E 29
I 29
		cp = &exdata.ex_shell[2];
		while (*cp == ' ')
			cp++;
E 29
E 28
D 8
		u.u_dirp = cp;
E 8
I 8
D 73
		ndp->ni_dirp = cp;
E 73
I 73
		nd.ni_dirp = cp;
E 73
E 8
D 28
		while (*cp && *cp != ' ')
			cp++;
D 17
		sharg = NULL;
E 17
I 17
		cfarg[0] = '\0';
E 28
I 28
D 29
		for (; *cp && *cp != ' '; ++cp);
E 29
I 29
		while (*cp && *cp != ' ')
			cp++;
I 30
		cfarg[0] = '\0';
E 30
E 29
E 28
E 17
		if (*cp) {
D 28
			*cp++ = '\0';
			while (*cp == ' ')
				cp++;
E 28
I 28
D 29
			for (*cp++ = '\0'; *cp == ' '; ++cp);
E 29
I 29
			*cp++ = '\0';
			while (*cp == ' ')
				cp++;
E 29
E 28
D 17
			if (*cp) {
E 17
I 17
			if (*cp)
E 17
D 25
				bcopy((caddr_t)cp, (caddr_t)cfarg, SHSIZE);
E 25
I 25
				bcopy((caddr_t)cp, (caddr_t)cfarg, MAXINTERP);
E 25
D 17
				sharg = cfarg;
			}
E 17
D 29
		}
D 8
		if (u.u_dent.d_namlen > MAXCOMLEN)
			u.u_dent.d_namlen = MAXCOMLEN;
		bcopy((caddr_t)u.u_dent.d_name, (caddr_t)cfname,
		    (unsigned)(u.u_dent.d_namlen + 1));
E 8
I 8
D 17
		if (ndp->ni_dent.d_namlen > MAXCOMLEN)
			ndp->ni_dent.d_namlen = MAXCOMLEN;
		bcopy((caddr_t)ndp->ni_dent.d_name, (caddr_t)cfname,
		    (unsigned)(ndp->ni_dent.d_namlen + 1));
E 8
D 10
		cfname[MAXCOMLEN] = 0;
E 10
I 10
		cfname[MAXCOMLEN] = '\0';
E 17
E 10
D 28
		indir = 1;
E 28
I 28
		else
E 29
I 29
D 30
		} else
E 29
			cfarg[0] = '\0';
E 30
I 30
		}
E 30
I 29
		indir = 1;
E 29
E 28
D 33
		iput(ip);
D 8
		ip = namei(schar, LOOKUP, 1);
E 8
I 8
		ndp->ni_nameiop = LOOKUP | FOLLOW;
E 33
I 33
		vput(vp);
D 68
		ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
E 68
E 33
D 73
		ndp->ni_segflg = UIO_SYSSPACE;
D 33
		ip = namei(ndp);
E 8
		if (ip == NULL)
E 33
I 33
D 48
		if (u.u_error = namei(ndp))
E 33
			return;
E 48
I 48
D 59
		if (error = namei(ndp))
E 59
I 59
		if (error = namei(ndp, p))
E 73
I 73
		nd.ni_segflg = UIO_SYSSPACE;
		if (error = namei(&nd))
E 73
E 59
D 51
			RETURN (error);
E 51
I 51
			return (error);
E 51
E 48
I 33
D 73
		vp = ndp->ni_vp;
E 73
I 73
		vp = nd.ni_vp;
I 106
D 114
		LEASE_CHECK(vp, p, cred, LEASE_READ);
E 114
I 114
		VOP_LEASE(vp, p, cred, LEASE_READ);
E 114
D 117
		VOP_LOCK(vp);
E 117
I 117
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 117
E 106
E 73
D 48
		if (u.u_error = VOP_GETATTR(vp, &vattr, u.u_cred))
E 48
I 48
D 63
		if (error = VOP_GETATTR(vp, &vattr, cred))
E 63
I 63
		if (error = VOP_GETATTR(vp, &vattr, cred, p))
E 63
E 48
			goto bad;
E 33
I 17
D 68
		bcopy((caddr_t)ndp->ni_dent.d_name, (caddr_t)cfname,
		    MAXCOMLEN);
		cfname[MAXCOMLEN] = '\0';
E 68
I 28
D 36
		uid = u.u_uid;		/* shell scripts can't be setuid */
		gid = u.u_gid;
E 36
I 36
D 48
		uid = u.u_cred->cr_uid;	/* shell scripts can't be setuid */
		gid = u.u_cred->cr_gid;
E 48
I 48
		uid = cred->cr_uid;	/* shell scripts can't be setuid */
		gid = cred->cr_gid;
E 48
E 36
E 28
E 17
		goto again;
	}
I 44
D 56
	/*
	 * If the vnode has been modified since we last used it,
	 * then throw away all its pages and its text table entry.
	 */
	if (vp->v_text && vp->v_text->x_mtime != vattr.va_mtime.tv_sec) {
		/*
		 * Try once to release, if it is still busy
		 * take more drastic action.
		 */
		xrele(vp);
		if (vp->v_flag & VTEXT) {
			vput(vp);
			vgone(vp);
			goto start;
		}
	}
E 56
E 44

	/*
	 * Collect arguments on "file" in swap space.
	 */
	na = 0;
	ne = 0;
	nc = 0;
I 10
D 56
	cc = 0;
E 10
D 48
	uap = (struct execa *)u.u_ap;
E 48
I 26
#ifdef SECSIZE
	bno = rmalloc(argmap, (clrnd((int)btoc(NCARGS))) * CLBYTES / argdbsize);
#else SECSIZE
E 26
D 9
	if ((bno = rmalloc(argmap, (long)ctod(clrnd((int)btoc(NCARGS))))) == 0) {
E 9
I 9
	bno = rmalloc(argmap, (long)ctod(clrnd((int)btoc(NCARGS))));
I 26
#endif SECSIZE
E 26
	if (bno == 0) {
E 9
D 15
		swkill(u.u_procp, "exece");
E 15
I 15
D 48
		swkill(u.u_procp, "exec: no swap space");
E 48
I 48
		swkill(p, "exec: no swap space");
E 48
E 15
		goto bad;
	}
	if (bno % CLSIZE)
		panic("execa rmalloc");
I 46
#ifdef GENERIC
	if (rootdev == dumpdev)
		bno += 4096;
#endif
E 56
I 56
	cc = NCARGS;
	execargs = kmem_alloc_wait(exec_map, NCARGS);
I 71
#ifdef DIAGNOSTIC
	if (execargs == (vm_offset_t)0)
		panic("execve: kmem_alloc_wait");
#endif
E 71
	cp = (char *) execargs;
E 56
E 46
I 10
	/*
	 * Copy arguments into file in argdev area.
	 */
E 10
D 115
	if (uap->argp) for (;;) {
E 115
I 115
	if (SCARG(uap, argp)) for (;;) {
E 115
		ap = NULL;
D 17
		if (indir && (na == 1 || na == 2 && sharg))
E 17
I 17
		sharg = NULL;
		if (indir && na == 0) {
D 68
			sharg = cfname;
E 68
I 68
D 73
			sharg = ndp->ni_ptr;
E 73
I 73
			sharg = nd.ni_cnd.cn_nameptr;
E 73
E 68
			ap = (int)sharg;
D 115
			uap->argp++;		/* ignore argv[0] */
E 115
I 115
			SCARG(uap, argp)++;		/* ignore argv[0] */
E 115
		} else if (indir && (na == 1 && cfarg[0])) {
			sharg = cfarg;
			ap = (int)sharg;
		} else if (indir && (na == 1 || na == 2 && cfarg[0]))
E 17
D 115
			ap = (int)uap->fname;
		else if (uap->argp) {
			ap = fuword((caddr_t)uap->argp);
			uap->argp++;
E 115
I 115
			ap = (int)SCARG(uap, path);
		else if (SCARG(uap, argp)) {
			ap = fuword((caddr_t)SCARG(uap, argp));
			SCARG(uap, argp)++;
E 115
		}
D 10
		if (ap==NULL && uap->envp) {
E 10
I 10
D 115
		if (ap == NULL && uap->envp) {
E 10
			uap->argp = NULL;
D 10
			if ((ap = fuword((caddr_t)uap->envp)) == NULL)
				break;
			uap->envp++;
			ne++;
E 10
I 10
			if ((ap = fuword((caddr_t)uap->envp)) != NULL)
				uap->envp++, ne++;
E 115
I 115
		if (ap == NULL && SCARG(uap, envp)) {
D 116
			SCARG(uap, envp) = NULL;
E 116
I 116
			SCARG(uap, argp) = NULL;
E 116
			if ((ap = fuword((caddr_t)SCARG(uap, envp))) != NULL)
				SCARG(uap, envp)++, ne++;
E 115
E 10
		}
		if (ap == NULL)
			break;
		na++;
D 10
		if (ap == -1)
			u.u_error = EFAULT;
E 10
I 10
		if (ap == -1) {
D 19
			error = EFAULT;
E 19
I 19
D 48
			u.u_error = EFAULT;
E 48
I 48
			error = EFAULT;
E 48
E 19
D 46
			break;
E 46
I 46
D 56
			if (bp) {
				brelse(bp);
				bp = 0;
			}
			goto badarg;
E 56
I 56
			goto bad;
E 56
E 46
		}
E 10
		do {
D 10
			if (nc >= NCARGS-1)
				u.u_error = E2BIG;
			if (indir && na == 2 && sharg != NULL)
				c = *sharg++ & 0377;
			else if ((c = fubyte((caddr_t)ap++)) < 0)
				u.u_error = EFAULT;
			if (u.u_error) {
E 10
I 10
D 56
			if (cc <= 0) {
				/*
				 * We depend on NCARGS being a multiple of
D 26
D 27
				 * CLSIZE*NBPG.  This way we need only check
E 27
I 27
				 * CLBYTES.  This way we need only check
E 27
E 26
I 26
				 * CLBYTES.  This way we need only check
E 26
				 * overflow before each buffer allocation.
				 */
				if (nc >= NCARGS-1) {
					error = E2BIG;
					break;
				}
E 10
				if (bp)
D 10
					brelse(bp);
				bp = 0;
				goto badarg;
			}
			if (nc % (CLSIZE*NBPG) == 0) {
				if (bp)
E 10
					bdwrite(bp);
D 10
				bp = getblk(argdev, bno + ctod(nc / NBPG),
				    CLSIZE*NBPG);
E 10
I 10
D 26
D 27
				cc = CLSIZE*NBPG;
E 27
I 27
				cc = CLBYTES;
E 27
E 26
I 26
				cc = CLBYTES;
#ifdef SECSIZE
				bp = getblk(argdev, bno + nc / argdbsize, cc,
				    argdbsize);
#else SECSIZE
E 26
D 33
				bp = getblk(argdev, bno + ctod(nc/NBPG), cc);
E 33
I 33
				bp = getblk(argdev_vp, bno + ctod(nc/NBPG), cc);
E 33
I 26
#endif SECSIZE
E 26
E 10
				cp = bp->b_un.b_addr;
E 56
I 56
			if (nc >= NCARGS-1) {
				error = E2BIG;
				break;
E 56
			}
D 10
			nc++;
			*cp++ = c;
		} while (c > 0);
E 10
I 10
D 17
			if (indir && na == 2 && sharg != NULL)
E 17
I 17
			if (sharg) {
E 17
D 22
				error = copystr(sharg, cp, cc, &len);
E 22
I 22
				error = copystr(sharg, cp, (unsigned)cc, &len);
E 22
D 17
			else
E 17
I 17
				sharg += len;
			} else {
E 17
D 22
				error = copyinstr((caddr_t)ap, cp, cc, &len);
E 22
I 22
				error = copyinstr((caddr_t)ap, cp, (unsigned)cc,
				    &len);
E 22
D 17
			ap += len;
E 17
I 17
				ap += len;
			}
E 17
			cp += len;
			nc += len;
			cc -= len;
D 55
		} while (error == ENOENT);
E 55
I 55
		} while (error == ENAMETOOLONG);
E 55
D 56
		if (error) {
D 48
			u.u_error = error;
E 48
			if (bp)
				brelse(bp);
			bp = 0;
			goto badarg;
		}
E 56
I 56
		if (error)
			goto bad;
E 56
E 10
	}
D 56
	if (bp)
		bdwrite(bp);
	bp = 0;
E 56
D 75
	nc = (nc + NBPW-1) & ~(NBPW-1);
D 17
	if (indir) {
D 8
		u.u_dent.d_namlen = strlen(cfname);
		bcopy((caddr_t)cfname, (caddr_t)u.u_dent.d_name,
		    (unsigned)(u.u_dent.d_namlen + 1));
E 8
I 8
		ndp->ni_dent.d_namlen = strlen(cfname);
		bcopy((caddr_t)cfname, (caddr_t)ndp->ni_dent.d_name,
		    (unsigned)(ndp->ni_dent.d_namlen + 1));
E 8
	}
E 17
D 9
	getxfile(ip, nc + (na+4)*NBPW, uid, gid);
E 9
I 9
D 33
	getxfile(ip, &exdata.ex_exec, nc + (na+4)*NBPW, uid, gid);
E 33
I 33
D 46
	getxfile(vp, &exdata.ex_exec, nc + (na+4)*NBPW, uid, gid, u.u_cred);
E 46
I 46
D 48
	getxfile(vp, &exdata.ex_exec, flags, nc + (na+4)*NBPW,
	    uid, gid, u.u_cred);
E 46
E 33
E 9
	if (u.u_error) {
E 48
I 48
D 62
	error = getxfile(p, vp, &exdata.ex_exec, flags, nc + (na+4)*NBPW,
E 62
I 62
	error = getxfile(p, vp, &exdata.ex_exec, paged, nc + (na+4)*NBPW,
E 62
	    uid, gid);
E 75
I 75

	/*
	 * XXX the following is excessively bogus
	 *
	 * Compute initial process stack size and location of argc
	 * and character strings.  `nc' is currently just the number
	 * of characters of arg and env strings.
	 *
D 77
	 * nc = size of signal code + 4 bytes of NULL pointer + nc,
	 *	rounded to nearest integer;
E 77
I 77
	 * nc = size of ps_strings structure +
	 *	size of signal code +
	 *	4 bytes of NULL pointer +
	 *	nc,
	 * rounded to nearest integer;
E 77
	 * ucp = USRSTACK - nc;		[user characters pointer]
	 * apsize = padding (if any) +
	 *	4 bytes of NULL pointer +
	 *	ne 4-byte pointers to env strings +
	 *	4 bytes of NULL pointer +
	 *	(na-ne) 4-byte pointers to arg strings +
	 *	4 bytes of argc;
	 * (this is the same as nc + (na+3)*4)
	 * ap = ucp - apsize;	[user address of argc]
	 * ssize = ssize + nc + machine-dependent space;
	 */
D 77
	nc = (szsigcode + 4 + nc + NBPW-1) & ~(NBPW - 1);
E 77
I 77
	nc = (sizeof(ps) + szsigcode + 4 + nc + NBPW-1) & ~(NBPW - 1);
E 77
D 99
#ifdef sparc
E 99
I 99
#if defined(sparc) || defined(mips)
E 99
	ucp = USRSTACK;
D 99
	ssize = (nc + (na + 3) * NBPW + 7) & ~7;
E 99
I 99
	ssize = ALIGN(nc + (na + 3) * NBPW);
E 99
	ap = ucp - ssize;
	ucp -= nc;
I 99
#ifdef sparc
E 99
	ssize += sizeof(struct rwindow);
I 99
#endif
E 99
#else
I 98
D 99
#ifdef mips
	ucp = USRSTACK;
	ssize = (nc + (na + 3) * NBPW + 7) & ~7;
	ap = ucp - ssize;
	ucp -= nc;
#else
E 99
E 98
	ssize = (na + 3) * NBPW;
	ucp = USRSTACK - nc;
	ap = ucp - ssize;
	ssize += nc;
I 98
D 99
#endif
E 99
E 98
#endif
	error = getxfile(p, vp, &exdata.ex_exec, paged, ssize, uid, gid);
E 75
D 56
	if (error) {
E 48
badarg:
D 10
		for (c = 0; c < nc; c += CLSIZE*NBPG) {
			bp = baddr(argdev, bno + ctod(c / NBPG), CLSIZE*NBPG);
E 10
I 10
D 33
		for (cc = 0; cc < nc; cc += CLSIZE*NBPG) {
I 26
#ifdef SECSIZE
			bp = baddr(argdev, bno + cc / argdbsize, CLSIZE*NBPG,
			    argdbsize);
#else SECSIZE
E 26
			bp = baddr(argdev, bno + ctod(cc/NBPG), CLSIZE*NBPG);
E 33
I 33
		for (cc = 0; cc < nc; cc += CLBYTES) {
D 40
			u.u_error = baddr(argdev_vp, bno + ctod(cc/NBPG),
E 40
I 40
			(void) baddr(argdev_vp, bno + ctod(cc/NBPG),
E 40
D 35
				CLBYTES, &tbp);
E 35
I 35
				CLBYTES, NOCRED, &tbp);
E 35
			bp = tbp;
E 33
I 26
#endif SECSIZE
E 26
E 10
			if (bp) {
D 42
				bp->b_flags |= B_AGE;		/* throw away */
				bp->b_flags &= ~B_DELWRI;	/* cancel io */
E 42
I 42
				bp->b_flags |= B_INVAL;		/* throw away */
E 42
				brelse(bp);
				bp = 0;
			}
		}
E 56
I 56
	if (error)
E 56
		goto bad;
I 111

	/* take a reference to the new text vnode (for procfs) */
	if (p->p_textvp)
		vrele(p->p_textvp);
	VREF(vp);
	p->p_textvp = vp;

E 111
D 56
	}
I 44
D 50
	vp->v_text->x_mtime = vattr.va_mtime.tv_sec;
E 50
I 50
	if (vp->v_text)
		vp->v_text->x_mtime = vattr.va_mtime.tv_sec;
E 56
E 50
E 44
I 17
D 33
	iput(ip);
	ip = NULL;
E 33
I 33
	vput(vp);
	vp = NULL;
E 33
E 17

I 46
#ifdef HPUXCOMPAT
E 46
	/*
I 46
	 * We are now committed to the exec so we can save the exec
	 * header in the pcb where we can dump it if necessary in core()
	 */
D 64
	if (u.u_pcb.pcb_flags & PCB_HPUXBIN)
E 64
I 64
D 100
	if (p->p_addr->u_pcb.pcb_flags & PCB_HPUXBIN)
E 100
I 100
	if (p->p_md.md_flags & MDP_HPUX)
E 100
E 64
		bcopy((caddr_t)&hhead,
D 64
		      (caddr_t)u.u_pcb.pcb_exec, sizeof hhead);
E 64
I 64
D 100
		      (caddr_t)p->p_addr->u_pcb.pcb_exec, sizeof hhead);
E 100
I 100
		      (caddr_t)p->p_addr->u_md.md_exec, sizeof hhead);
E 100
E 64
#endif

	/*
E 46
D 10
	 * copy back arglist
E 10
I 10
	 * Copy back arglist.
E 10
	 */
D 56
	ucp = USRSTACK - nc - NBPW;
E 56
I 56
D 64
	ucp = USRSTACK - sizeof(u.u_pcb.pcb_sigc) - nc - NBPW;
E 64
I 64
D 75
	ucp = USRSTACK - szsigcode - nc - NBPW;
E 64
E 56
	ap = ucp - na*NBPW - 3*NBPW;
E 75
D 59
	u.u_ar0[SP] = ap;
E 59
I 59
D 74
	p->p_regs[SP] = ap;
E 74
I 74
	cpu_setstack(p, ap);
E 74
E 59
	(void) suword((caddr_t)ap, na-ne);
	nc = 0;
I 11
D 56
	cc = 0;
E 56
I 56
	cp = (char *) execargs;
	cc = NCARGS;
I 77
	ps.ps_argvstr = (char *)ucp;	/* first argv string */
	ps.ps_nargvstr = na - ne;	/* argc */
E 77
E 56
E 11
	for (;;) {
		ap += NBPW;
D 10
		if (na==ne) {
E 10
I 10
		if (na == ne) {
E 10
			(void) suword((caddr_t)ap, 0);
			ap += NBPW;
I 77
			ps.ps_envstr = (char *)ucp;
			ps.ps_nenvstr = ne;
E 77
		}
		if (--na < 0)
			break;
		(void) suword((caddr_t)ap, ucp);
		do {
D 11
			if (nc % (CLSIZE*NBPG) == 0) {
E 11
I 11
D 56
			if (cc <= 0) {
E 11
				if (bp)
					brelse(bp);
D 11
				bp = bread(argdev, bno + ctod(nc / NBPG),
				    CLSIZE*NBPG);
E 11
I 11
D 26
D 27
				cc = CLSIZE*NBPG;
E 27
I 27
				cc = CLBYTES;
E 27
E 26
I 26
				cc = CLBYTES;
#ifdef SECSIZE
				bp = bread(argdev, bno + nc / argdbsize, cc,
				    argdbsize);
#else SECSIZE
E 26
D 33
				bp = bread(argdev, bno + ctod(nc / NBPG), cc);
E 33
I 33
				error = bread(argdev_vp,
D 35
				    (daddr_t)(bno + ctod(nc / NBPG)), cc, &tbp);
E 35
I 35
				    (daddr_t)(bno + ctod(nc / NBPG)), cc,
				    NOCRED, &tbp);
E 35
				bp = tbp;
E 33
I 26
#endif SECSIZE
E 26
E 11
D 42
				bp->b_flags |= B_AGE;		/* throw away */
				bp->b_flags &= ~B_DELWRI;	/* cancel io */
E 42
I 42
				bp->b_flags |= B_INVAL;		/* throw away */
E 42
				cp = bp->b_un.b_addr;
			}
E 56
D 10
			(void) subyte((caddr_t)ucp++, (c = *cp++));
E 10
I 10
D 11
			(void) subyte((caddr_t)ucp++, (cc = *cp++));
E 10
			nc++;
D 10
		} while(c&0377);
E 10
I 10
		} while(cc&0377);
E 11
I 11
D 22
			error = copyoutstr(cp, (caddr_t)ucp, cc, &len);
E 22
I 22
			error = copyoutstr(cp, (caddr_t)ucp, (unsigned)cc,
			    &len);
E 22
			ucp += len;
			cp += len;
			nc += len;
			cc -= len;
D 55
		} while (error == ENOENT);
E 55
I 55
		} while (error == ENAMETOOLONG);
E 55
		if (error == EFAULT)
			panic("exec: EFAULT");
E 11
E 10
	}
	(void) suword((caddr_t)ap, 0);
I 77
	(void) copyout((caddr_t)&ps, (caddr_t)PS_STRINGS, sizeof(ps));
E 77
I 17

D 36
	/*
	 * Reset caught signals.  Held signals
	 * remain held through p_sigmask.
	 */
	while (u.u_procp->p_sigcatch) {
D 22
		nc = ffs(u.u_procp->p_sigcatch);
E 22
I 22
		nc = ffs((long)u.u_procp->p_sigcatch);
E 22
		u.u_procp->p_sigcatch &= ~sigmask(nc);
		u.u_signal[nc] = SIG_DFL;
	}
	/*
	 * Reset stack state to the user stack.
	 * Clear set of signals caught on the signal stack.
	 */
	u.u_onstack = 0;
	u.u_sigsp = 0;
	u.u_sigonstack = 0;
E 36
I 36
D 48
	execsigs(u.u_procp);
E 48
I 48
	execsigs(p);
E 48
E 36

D 58
	for (nc = u.u_lastfile; nc >= 0; --nc) {
		if (u.u_pofile[nc] & UF_EXCLOSE) {
D 38
			closef(u.u_ofile[nc]);
E 38
I 38
			(void) closef(u.u_ofile[nc]);
E 38
			u.u_ofile[nc] = NULL;
			u.u_pofile[nc] = 0;
E 58
I 58
	for (nc = fdp->fd_lastfile; nc >= 0; --nc) {
D 60
		if (OFILEFLAGS(fdp, nc) & UF_EXCLOSE) {
			(void) closef(OFILE(fdp, nc));
			OFILE(fdp, nc) = NULL;
			OFILEFLAGS(fdp, nc) = 0;
E 60
I 60
		if (fdp->fd_ofileflags[nc] & UF_EXCLOSE) {
			(void) closef(fdp->fd_ofiles[nc], p);
			fdp->fd_ofiles[nc] = NULL;
			fdp->fd_ofileflags[nc] = 0;
E 60
I 59
			if (nc < fdp->fd_freefile)
				fdp->fd_freefile = nc;
E 59
E 58
		}
D 58
		u.u_pofile[nc] &= ~UF_MAPPED;
E 58
I 58
D 60
		OFILEFLAGS(fdp, nc) &= ~UF_MAPPED;
E 60
I 60
		fdp->fd_ofileflags[nc] &= ~UF_MAPPED;
E 60
E 58
	}
D 58
	while (u.u_lastfile >= 0 && u.u_ofile[u.u_lastfile] == NULL)
		u.u_lastfile--;
E 58
I 58
D 60
	while (fdp->fd_lastfile >= 0 && OFILE(fdp, fdp->fd_lastfile) == NULL)
E 60
I 60
	/*
	 * Adjust fd_lastfile to account for descriptors closed above.
	 * Don't decrement fd_lastfile past 0, as it's unsigned.
	 */
	while (fdp->fd_lastfile > 0 && fdp->fd_ofiles[fdp->fd_lastfile] == NULL)
E 60
		fdp->fd_lastfile--;
E 58
E 17
D 9
	setregs();
E 9
I 9
D 49
	setregs(exdata.ex_exec.a_entry);
E 49
I 49
D 65
	setregs(exdata.ex_exec.a_entry, retval);
E 65
I 65
	setregs(p, exdata.ex_exec.a_entry, retval);
E 65
I 64
#ifdef COPY_SIGCODE
E 64
E 49
E 9
I 8
	/*
I 56
	 * Install sigcode at top of user stack.
	 */
D 64
	copyout((caddr_t)u.u_pcb.pcb_sigc,
		(caddr_t)(USRSTACK - sizeof(u.u_pcb.pcb_sigc)),
		sizeof(u.u_pcb.pcb_sigc));
E 64
I 64
D 77
	copyout((caddr_t)sigcode, (caddr_t)(USRSTACK - szsigcode), szsigcode);
E 77
I 77
	copyout((caddr_t)sigcode, (caddr_t)PS_STRINGS - szsigcode, szsigcode);
E 77
#endif
E 64
	/*
E 56
	 * Remember file name for accounting.
	 */
D 59
	u.u_acflag &= ~AFORK;
E 59
I 59
	p->p_acflag &= ~AFORK;
E 59
D 17
	bcopy((caddr_t)ndp->ni_dent.d_name, (caddr_t)u.u_comm,
	    (unsigned)(ndp->ni_dent.d_namlen + 1));
E 17
I 17
D 68
	if (indir)
D 43
		bcopy((caddr_t)cfname, (caddr_t)u.u_comm, MAXCOMLEN);
E 43
I 43
D 48
		bcopy((caddr_t)cfname, (caddr_t)u.u_procp->p_comm, MAXCOMLEN);
E 48
I 48
		bcopy((caddr_t)cfname, (caddr_t)p->p_comm, MAXCOMLEN);
E 48
E 43
	else {
		if (ndp->ni_dent.d_namlen > MAXCOMLEN)
			ndp->ni_dent.d_namlen = MAXCOMLEN;
D 43
		bcopy((caddr_t)ndp->ni_dent.d_name, (caddr_t)u.u_comm,
E 43
I 43
D 48
		bcopy((caddr_t)ndp->ni_dent.d_name, (caddr_t)u.u_procp->p_comm,
E 48
I 48
		bcopy((caddr_t)ndp->ni_dent.d_name, (caddr_t)p->p_comm,
E 48
E 43
		    (unsigned)(ndp->ni_dent.d_namlen + 1));
	}
E 68
I 68
D 73
	if (ndp->ni_namelen > MAXCOMLEN)
		ndp->ni_namelen = MAXCOMLEN;
	bcopy((caddr_t)ndp->ni_ptr, (caddr_t)p->p_comm,
	    (unsigned)(ndp->ni_namelen));
	p->p_comm[ndp->ni_namelen] = '\0';
E 73
I 73
	if (nd.ni_cnd.cn_namelen > MAXCOMLEN)
		nd.ni_cnd.cn_namelen = MAXCOMLEN;
	bcopy((caddr_t)nd.ni_cnd.cn_nameptr, (caddr_t)p->p_comm,
D 75
	    (unsigned)(nd.ni_cnd.cn_namelen));
E 75
I 75
	    (unsigned)nd.ni_cnd.cn_namelen);
E 75
	p->p_comm[nd.ni_cnd.cn_namelen] = '\0';
E 73
E 68
I 64
	cpu_exec(p);
E 64
E 17
E 8
bad:
I 68
D 73
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 73
I 73
	FREE(nd.ni_cnd.cn_pnbuf, M_NAMEI);
E 73
E 68
D 56
	if (bp)
		brelse(bp);
	if (bno)
I 26
#ifdef SECSIZE
		rmfree(argmap, (clrnd((int)btoc(NCARGS))) * CLBYTES / argdbsize,
		    bno);
#else SECSIZE
E 26
		rmfree(argmap, (long)ctod(clrnd((int) btoc(NCARGS))), bno);
E 56
I 56
	if (execargs)
		kmem_free_wakeup(exec_map, execargs, NCARGS);
E 56
I 26
#endif SECSIZE
E 26
D 17
	iput(ip);
E 17
I 17
D 33
	if (ip)
		iput(ip);
E 33
I 33
	if (vp)
		vput(vp);
I 48
D 51
	RETURN (error);
E 51
I 51
	return (error);
E 51
E 48
E 33
E 17
}

/*
 * Read in and set up memory for executed file.
 */
D 9
getxfile(ip, nargc, uid, gid)
E 9
I 9
D 33
getxfile(ip, ep, nargc, uid, gid)
E 9
	register struct inode *ip;
E 33
I 33
D 46
getxfile(vp, ep, nargc, uid, gid, cred)
E 46
I 46
D 48
getxfile(vp, ep, flags, nargc, uid, gid, cred)
E 48
I 48
D 62
getxfile(p, vp, ep, flags, nargc, uid, gid)
E 62
I 62
D 75
getxfile(p, vp, ep, paged, nargc, uid, gid)
E 75
I 75
getxfile(p, vp, ep, paged, ssize, uid, gid)
E 75
E 62
	register struct proc *p;
E 48
E 46
	register struct vnode *vp;
E 33
I 9
	register struct exec *ep;
E 9
D 46
	int nargc, uid, gid;
E 46
I 46
D 62
	int flags, nargc, uid, gid;
E 62
I 62
D 75
	int paged, nargc, uid, gid;
E 75
I 75
	int paged, ssize, uid, gid;
E 75
E 62
E 46
I 33
D 48
	struct ucred *cred;
E 48
E 33
{
I 36
D 48
	register struct proc *p = u.u_procp;
E 48
E 36
D 16
	register size_t ts, ds, ss;
E 16
I 16
D 47
	size_t ts, ds, ids, uds, ss;
E 47
I 47
D 56
	segsz_t ts, ds, ids, uds, ss;
E 56
I 56
D 75
	segsz_t ts, ds, ss;
E 75
E 56
I 48
D 59
	register struct ucred *cred = u.u_cred;
E 59
I 59
	register struct ucred *cred = p->p_ucred;
I 75
	register struct vmspace *vm = p->p_vmspace;
	vm_offset_t addr;
	vm_size_t xts, size;
	segsz_t ds;
E 75
E 59
E 48
E 47
E 16
D 46
	int pagi;
E 46
I 46
	off_t toff;
I 48
D 56
	int error;
E 56
I 56
	int error = 0;
D 75
	vm_offset_t addr;
	vm_size_t size;
D 59
	vm_map_t map = VM_MAP_NULL;
E 59
I 59
	struct vmspace *vm = p->p_vmspace;
E 75
E 59
E 56
E 48
E 46

D 9
	if (u.u_exdata.ux_mag == 0413)
E 9
I 9
D 33
	if (ep->a_magic == 0413)
E 9
		pagi = SPAGI;
E 33
I 33
D 46
	if (ep->a_magic == ZMAGIC)
		pagi = SPAGV;
E 46
I 46
#ifdef HPUXCOMPAT
I 62
D 100
	int hpux = (paged & SHPUX);
	paged &= ~SHPUX;
E 100
E 62
D 56
	if (ep->a_mid == MID_HPUX)
		toff = sizeof (struct hpux_exec);
E 46
E 33
	else
E 56
I 56
D 76
	if (ep->a_mid == MID_HPUX) {
D 62
		if (flags & SPAGV)
E 62
I 62
		if (paged)
E 62
			toff = CLBYTES;
		else
			toff = sizeof (struct hpux_exec);
	} else
E 76
I 76
	if (ep->a_mid == MID_HPUX)
		toff = paged ? CLBYTES : sizeof(struct hpux_exec);
	else
E 76
E 56
D 46
		pagi = 0;
E 46
I 46
#endif
I 71
#ifdef COFF
	toff = N_TXTOFF(*ep);
#else
I 75
#ifdef sparc
	if (ep->a_mid == MID_SUN_SPARC)
		toff = paged ? 0 : sizeof(struct exec);
	else
#endif
E 75
E 71
D 56
	toff = sizeof (struct exec);
E 46
I 13
D 20
	if (ip->i_flag & IXMOD) {			/* XXX */
E 20
I 20
D 33
	if (ip->i_text && (ip->i_text->x_flag & XTRC)) {
E 33
I 33
D 48
	if (vp->v_text && (vp->v_text->x_flag & XTRC)) {
E 33
E 20
		u.u_error = ETXTBSY;
		goto bad;
	}
E 48
I 48
	if (vp->v_text && (vp->v_text->x_flag & XTRC))
		return (ETXTBSY);
E 56
I 56
D 62
	if (flags & SPAGV)
E 62
I 62
	if (paged)
I 102
#ifdef mips
		toff = 0;
#else
E 102
E 62
		toff = CLBYTES;
I 102
#endif
E 102
	else
		toff = sizeof (struct exec);
I 71
#endif
E 71
E 56
E 48
E 13
D 9
	if (u.u_exdata.ux_tsize!=0 && (ip->i_flag&ITEXT)==0 &&
	    ip->i_count!=1) {
E 9
I 9
D 33
	if (ep->a_text != 0 && (ip->i_flag&ITEXT) == 0 &&
	    ip->i_count != 1) {
E 33
I 33
	if (ep->a_text != 0 && (vp->v_flag & VTEXT) == 0 &&
D 41
	    vp->v_count != 1) {
E 41
I 41
D 70
	    vp->v_usecount != 1) {
E 41
E 33
E 9
		register struct file *fp;

D 69
		for (fp = file; fp < fileNFILE; fp++) {
E 69
I 69
		for (fp = filehead; fp; fp = fp->f_filef) {
E 69
D 33
			if (fp->f_type == DTYPE_INODE &&
E 33
I 33
			if (fp->f_type == DTYPE_VNODE &&
E 33
			    fp->f_count > 0 &&
D 33
			    (struct inode *)fp->f_data == ip &&
			    (fp->f_flag&FWRITE)) {
E 33
I 33
			    (struct vnode *)fp->f_data == vp &&
			    (fp->f_flag & FWRITE)) {
E 33
D 48
				u.u_error = ETXTBSY;
				goto bad;
E 48
I 48
				return (ETXTBSY);
E 48
			}
		}
	}
E 70
I 70
	    vp->v_writecount != 0)
		return (ETXTBSY);
E 70

	/*
	 * Compute text and data sizes and make sure not too large.
I 16
D 75
	 * NB - Check data and bss separately as they may overflow 
	 * when summed together.
E 75
I 75
	 * Text size is rounded to an ``ld page''; data+bss is left
	 * in machine pages.  Check data and bss separately as they
	 * may overflow when summed together.  (XXX not done yet)
E 75
E 16
	 */
D 9
	ts = clrnd(btoc(u.u_exdata.ux_tsize));
	ds = clrnd(btoc((u.u_exdata.ux_dsize+u.u_exdata.ux_bsize)));
E 9
I 9
D 75
	ts = clrnd(btoc(ep->a_text));
E 75
I 75
	xts = roundup(ep->a_text, __LDPGSZ);
E 75
I 16
D 56
	ids = clrnd(btoc(ep->a_data));
	uds = clrnd(btoc(ep->a_bss));
E 56
E 16
D 10
	ds = clrnd(btoc((ep->a_data + ep->a_bss)));
E 10
I 10
	ds = clrnd(btoc(ep->a_data + ep->a_bss));
E 10
E 9
D 56
	ss = clrnd(SSIZE + btoc(nargc));
D 16
	if (chksize((unsigned)ts, (unsigned)ds, (unsigned)ss))
E 16
I 16
D 48
	if (chksize((unsigned)ts, (unsigned)ids, (unsigned)uds, (unsigned)ss))
E 16
		goto bad;
E 48
I 48
	if (error =
	    chksize((unsigned)ts, (unsigned)ids, (unsigned)uds, (unsigned)ss))
		return (error);
E 48

E 56
I 56
D 64
	ss = clrnd(SSIZE + btoc(nargc + sizeof(u.u_pcb.pcb_sigc)));
E 64
I 64
D 75
	ss = clrnd(SSIZE + btoc(nargc + szsigcode));
E 75
E 64
I 60

	/*
	 * If we're sharing the address space, allocate a new space
	 * and release our reference to the old one.  Otherwise,
	 * empty out the existing vmspace.
	 */
I 75
#ifdef sparc
	kill_user_windows(p);		/* before addrs go away */
#endif
E 75
	if (vm->vm_refcnt > 1) {
D 65
		p->p_vmspace = vmspace_alloc(vm_map_min(&vm->vm_map),
		    vm_map_max(&vm->vm_map), 1);
E 65
I 65
		p->p_vmspace = vmspace_alloc(VM_MIN_ADDRESS,
		    VM_MAXUSER_ADDRESS, 1);
E 65
		vmspace_free(vm);
		vm = p->p_vmspace;
	} else {
E 60
#ifdef SYSVSHM
D 59
	if (p->p_shm)
E 59
I 59
D 60
	if (vm->vm_shm)
E 59
		shmexit(p);
E 60
I 60
		if (vm->vm_shm)
			shmexit(p);
E 60
#endif
D 59
	map = p->p_map;
	(void) vm_map_remove(map, vm_map_min(map), vm_map_max(map));
E 59
I 59
D 60
	(void) vm_map_remove(&vm->vm_map, vm_map_min(&vm->vm_map),
	    vm_map_max(&vm->vm_map));
E 60
I 60
D 65
		(void) vm_map_remove(&vm->vm_map, vm_map_min(&vm->vm_map),
		    vm_map_max(&vm->vm_map));
E 65
I 65
		(void) vm_map_remove(&vm->vm_map, VM_MIN_ADDRESS,
		    VM_MAXUSER_ADDRESS);
E 65
	}
E 60
E 59
E 56
	/*
D 56
	 * Make sure enough space to start process.
E 56
I 56
D 59
	 * XXX preserve synchronization semantics of vfork
E 59
I 59
	 * If parent is waiting for us to exec or exit,
D 110
	 * SPPWAIT will be set; clear it and wakeup parent.
E 110
I 110
	 * P_PPWAIT will be set; clear it and wakeup parent.
E 110
E 59
E 56
	 */
D 56
	u.u_cdmap = zdmap;
	u.u_csmap = zdmap;
D 48
	if (swpexpand(ds, ss, &u.u_cdmap, &u.u_csmap) == NULL)
		goto bad;
E 48
I 48
	if (error = swpexpand(ds, ss, &u.u_cdmap, &u.u_csmap))
		return (error);
E 48

	/*
D 33
	 * At this point, committed to the new image!
E 33
I 33
	 * At this point, we are committed to the new image!
E 33
	 * Release virtual memory resources of old process, and
	 * initialize the virtual memory of the new process.
	 * If we resulted from vfork(), instead wakeup our
	 * parent who will set SVFDONE when he has taken back
	 * our resources.
	 */
D 36
	if ((u.u_procp->p_flag & SVFORK) == 0)
E 36
I 36
D 46
	if ((p->p_flag & SVFORK) == 0)
E 46
I 46
	if ((p->p_flag & SVFORK) == 0) {
#ifdef MAPMEM
D 48
		if (u.u_mmap)
			mmexec();
E 48
I 48
		if (u.u_mmap && (error = mmexec(p)))
			return (error);
E 48
#endif
E 46
E 36
		vrelvm();
D 46
	else {
E 46
I 46
	} else {
E 56
I 56
D 59
	if (p->p_flag & SVFORK) {
E 56
E 46
D 36
		u.u_procp->p_flag &= ~SVFORK;
		u.u_procp->p_flag |= SKEEP;
		wakeup((caddr_t)u.u_procp);
		while ((u.u_procp->p_flag & SVFDONE) == 0)
			sleep((caddr_t)u.u_procp, PZERO - 1);
		u.u_procp->p_flag &= ~(SVFDONE|SKEEP);
E 36
I 36
		p->p_flag &= ~SVFORK;
D 56
		p->p_flag |= SKEEP;
E 56
		wakeup((caddr_t)p);
		while ((p->p_flag & SVFDONE) == 0)
			sleep((caddr_t)p, PZERO - 1);
D 56
		p->p_flag &= ~(SVFDONE|SKEEP);
E 56
I 56
		p->p_flag &= ~SVFDONE;
E 59
I 59
D 110
	if (p->p_flag & SPPWAIT) {
		p->p_flag &= ~SPPWAIT;
E 110
I 110
	if (p->p_flag & P_PPWAIT) {
		p->p_flag &= ~P_PPWAIT;
E 110
		wakeup((caddr_t) p->p_pptr);
E 59
E 56
E 36
	}
I 100
D 107
#if defined(HP380)
E 107
I 107
#if defined(HP380) || defined(LUNA2)
E 107
	/* default to copyback caching on 68040 */
	if (mmutype == MMU_68040)
		p->p_md.md_flags |= (MDP_CCBDATA|MDP_CCBSTACK);
#endif
E 100
D 2
	u.u_procp->p_flag &= ~(SPAGI|SSEQL|SUANOM|SNUSIG);
E 2
I 2
D 33
	u.u_procp->p_flag &= ~(SPAGI|SSEQL|SUANOM|SOUSIG);
E 33
I 33
D 36
	u.u_procp->p_flag &= ~(SPAGV|SSEQL|SUANOM|SOUSIG);
E 33
E 2
D 31
	u.u_procp->p_flag |= pagi;
E 31
I 31
	u.u_procp->p_flag |= pagi | SEXEC;
E 36
I 36
D 46
	p->p_flag &= ~(SPAGV|SSEQL|SUANOM);
	p->p_flag |= pagi | SEXEC;
E 46
I 46
D 64
#ifdef hp300
	u.u_pcb.pcb_flags &= ~(PCB_AST|PCB_HPUXMMAP|PCB_HPUXBIN);
E 64
#ifdef HPUXCOMPAT
I 64
D 100
	p->p_addr->u_pcb.pcb_flags &= ~(PCB_HPUXMMAP|PCB_HPUXBIN);
E 64
	/* remember that we were loaded from an HPUX format file */
E 100
I 100
	p->p_md.md_flags &= ~(MDP_HPUX|MDP_HPUXMMAP);
	/* note that we are an HP-UX binary */
E 100
	if (ep->a_mid == MID_HPUX)
D 64
		u.u_pcb.pcb_flags |= PCB_HPUXBIN;
E 64
I 64
D 100
		p->p_addr->u_pcb.pcb_flags |= PCB_HPUXBIN;
E 64
I 62
	if (hpux)
		p->p_flag |= SHPUX;
	else
		p->p_flag &= ~SHPUX;
E 100
I 100
		p->p_md.md_flags |= MDP_HPUX;
	/* deal with miscellaneous attributes */
	if (ep->a_trsize & HPUXM_VALID) {
		if (ep->a_trsize & HPUXM_DATAWT)
			p->p_md.md_flags &= ~MDP_CCBDATA;
		if (ep->a_trsize & HPUXM_STKWT)
			p->p_md.md_flags &= ~MDP_CCBSTACK;
	}
E 100
E 62
#endif
I 71
#ifdef ULTRIXCOMPAT
	/*
	 * Always start out as an ULTRIX process.
	 * A system call in crt0.o will change us to BSD system calls later.
	 */
	p->p_md.md_flags |= MDP_ULTRIX;
#endif
E 71
D 64
#endif
E 64
D 62
	p->p_flag &= ~(SPAGV|SSEQL|SUANOM|SHPUX);
	p->p_flag |= flags | SEXEC;
E 62
I 62
D 110
	p->p_flag |= SEXEC;
E 110
I 110
	p->p_flag |= P_EXEC;
E 110
I 71
#ifndef COFF
E 71
E 62
E 46
E 36
E 31
D 56
	u.u_dmap = u.u_cdmap;
	u.u_smap = u.u_csmap;
	vgetvm(ts, ds, ss);
E 56
I 56
	addr = VM_MIN_ADDRESS;
D 59
	if (vm_allocate(map, &addr, round_page(ctob(ts + ds)), FALSE)) {
E 59
I 59
D 75
	if (vm_allocate(&vm->vm_map, &addr, round_page(ctob(ts + ds)), FALSE)) {
E 75
I 75
	if (vm_allocate(&vm->vm_map, &addr, xts + ctob(ds), FALSE)) {
E 75
E 59
		uprintf("Cannot allocate text+data space\n");
		error = ENOMEM;			/* XXX */
		goto badmap;
	}
I 71
	vm->vm_taddr = (caddr_t)VM_MIN_ADDRESS;
D 75
	vm->vm_daddr = (caddr_t)(VM_MIN_ADDRESS + ctob(ts));
E 75
I 75
	vm->vm_daddr = (caddr_t)(VM_MIN_ADDRESS + xts);
E 75
#else /* COFF */
	addr = (vm_offset_t)ep->ex_aout.codeStart;
	vm->vm_taddr = (caddr_t)addr;
D 75
	if (vm_allocate(&vm->vm_map, &addr, round_page(ctob(ts)), FALSE)) {
E 75
I 75
	if (vm_allocate(&vm->vm_map, &addr, xts, FALSE)) {
E 75
		uprintf("Cannot allocate text space\n");
		error = ENOMEM;			/* XXX */
		goto badmap;
	}
	addr = (vm_offset_t)ep->ex_aout.heapStart;
	vm->vm_daddr = (caddr_t)addr;
	if (vm_allocate(&vm->vm_map, &addr, round_page(ctob(ds)), FALSE)) {
		uprintf("Cannot allocate data space\n");
		error = ENOMEM;			/* XXX */
		goto badmap;
	}
#endif /* COFF */
E 71
	size = round_page(MAXSSIZ);		/* XXX */
I 67
#ifdef	i386
	addr = trunc_page(USRSTACK - size) - NBPG;	/* XXX */
#else
E 67
D 65
	addr = trunc_page(VM_MAX_ADDRESS - size);
E 65
I 65
	addr = trunc_page(USRSTACK - size);
I 67
#endif
E 67
E 65
D 59
	if (vm_allocate(map, &addr, size, FALSE)) {
E 59
I 59
	if (vm_allocate(&vm->vm_map, &addr, size, FALSE)) {
E 59
		uprintf("Cannot allocate stack space\n");
		error = ENOMEM;			/* XXX */
I 65
		goto badmap;
	}
	size -= round_page(p->p_rlimit[RLIMIT_STACK].rlim_cur);
	if (vm_map_protect(&vm->vm_map, addr, addr+size, VM_PROT_NONE, FALSE)) {
		uprintf("Cannot protect stack space\n");
		error = ENOMEM;
E 65
		goto badmap;
	}
D 59
	u.u_maxsaddr = (caddr_t)addr;
	u.u_taddr = (caddr_t)VM_MIN_ADDRESS;
	u.u_daddr = (caddr_t)(VM_MIN_ADDRESS + ctob(ts));
E 59
I 59
	vm->vm_maxsaddr = (caddr_t)addr;
D 71
	vm->vm_taddr = (caddr_t)VM_MIN_ADDRESS;
	vm->vm_daddr = (caddr_t)(VM_MIN_ADDRESS + ctob(ts));
E 71
E 59
E 56

D 46
	if (pagi == 0)
E 46
I 46
D 60
	if ((flags & SPAGV) == 0)
E 60
I 60
D 62
	if ((flags & SPAGV) == 0) {
E 62
I 62
	if (paged == 0) {
E 62
		/*
		 * Read in data segment.
		 */
E 60
E 46
D 33
		u.u_error =
		    rdwri(UIO_READ, ip,
E 33
I 33
D 48
		u.u_error = vn_rdwr(UIO_READ, vp,
E 48
I 48
D 59
		(void) vn_rdwr(UIO_READ, vp,
E 48
E 33
D 46
			(char *)ctob(dptov(u.u_procp, 0)),
E 46
I 46
D 56
			(char *)ctob(dptov(p, 0)),
E 56
I 56
			u.u_daddr,
E 56
E 46
D 9
			(int)u.u_exdata.ux_dsize,
			(int)(sizeof(u.u_exdata)+u.u_exdata.ux_tsize),
E 9
I 9
			(int)ep->a_data,
D 22
			(int)(sizeof (struct exec) + ep->a_text),
E 22
I 22
D 46
			(off_t)(sizeof (struct exec) + ep->a_text),
E 46
I 46
			(off_t)(toff + ep->a_text),
E 46
E 22
E 9
D 33
			0, (int *)0);
D 9
	xalloc(ip, pagi);
E 9
I 9
	xalloc(ip, ep, pagi);
E 33
I 33
			UIO_USERSPACE, (IO_UNIT|IO_NODELOCKED), cred, (int *)0);
E 59
I 59
		(void) vn_rdwr(UIO_READ, vp, vm->vm_daddr, (int) ep->a_data,
			(off_t)(toff + ep->a_text), UIO_USERSPACE,
D 63
			(IO_UNIT|IO_NODELOCKED), cred, (int *)0);
E 63
I 63
			(IO_UNIT|IO_NODELOCKED), cred, (int *)0, p);
E 63
E 59
D 46
	xalloc(vp, ep, pagi, cred);
E 46
I 46
D 56
	xalloc(vp, ep, toff, cred);
E 46
E 33
I 24
#if defined(tahoe)
E 56
D 60
	/*
D 56
	 * Define new keys.
E 56
I 56
	 * Read in text segment if necessary (0410), and read-protect it.
E 56
	 */
D 36
	if (u.u_procp->p_textp == 0) {	/* use existing code key if shared */
		ckeyrelease(u.u_procp->p_ckey);
		u.u_procp->p_ckey = getcodekey();
E 36
I 36
D 56
	if (p->p_textp == 0) {	/* use existing code key if shared */
		ckeyrelease(p->p_ckey);
		p->p_ckey = getcodekey();
E 56
I 56
	if ((flags & SPAGV) == 0) {
E 60
I 60
		/*
		 * Read in text segment if necessary (0410),
		 * and read-protect it.
		 */
E 60
		if (ep->a_text > 0) {
D 59
			error = vn_rdwr(UIO_READ, vp,
					u.u_taddr, (int)ep->a_text, toff,
					UIO_USERSPACE, (IO_UNIT|IO_NODELOCKED),
					cred, (int *)0);
			(void) vm_map_protect(map,
					VM_MIN_ADDRESS,
					VM_MIN_ADDRESS+trunc_page(ep->a_text),
					VM_PROT_READ|VM_PROT_EXECUTE, FALSE);
E 59
I 59
			error = vn_rdwr(UIO_READ, vp, vm->vm_taddr,
D 78
				(int)ep->a_text, toff, UIO_USERSPACE,
D 63
				(IO_UNIT|IO_NODELOCKED), cred, (int *)0);
E 63
I 63
				(IO_UNIT|IO_NODELOCKED), cred, (int *)0, p);
E 63
D 71
			(void) vm_map_protect(&vm->vm_map, VM_MIN_ADDRESS,
				VM_MIN_ADDRESS + trunc_page(ep->a_text),
E 71
I 71
			(void) vm_map_protect(&vm->vm_map, vm->vm_taddr,
				vm->vm_taddr + trunc_page(ep->a_text),
E 71
				VM_PROT_READ|VM_PROT_EXECUTE, FALSE);
E 78
I 78
			    (int)ep->a_text, toff, UIO_USERSPACE,
			    (IO_UNIT|IO_NODELOCKED), cred, (int *)0, p);
			(void) vm_map_protect(&vm->vm_map,
			    (vm_offset_t)vm->vm_taddr,
			    (vm_offset_t)vm->vm_taddr + trunc_page(ep->a_text),
			    VM_PROT_READ|VM_PROT_EXECUTE, FALSE);
E 78
E 59
		}
	} else {
		/*
		 * Allocate a region backed by the exec'ed vnode.
		 */
I 71
#ifndef COFF
E 71
		addr = VM_MIN_ADDRESS;
D 75
		size = round_page(ep->a_text + ep->a_data);
E 75
I 75
		size = round_page(xts + ep->a_data);
E 75
D 59
		error = vm_mmap(map, &addr, size, VM_PROT_ALL,
				MAP_FILE|MAP_COPY|MAP_FIXED,
				(caddr_t)vp, (vm_offset_t)toff);
		(void) vm_map_protect(map, addr,
				addr+trunc_page(ep->a_text),
				VM_PROT_READ|VM_PROT_EXECUTE, FALSE);
E 59
I 59
D 103
		error = vm_mmap(&vm->vm_map, &addr, size, VM_PROT_ALL,
E 103
I 103
		error = vm_mmap(&vm->vm_map, &addr, size,
			VM_PROT_ALL, VM_PROT_ALL,
E 103
D 92
			MAP_FILE|MAP_COPY|MAP_FIXED,
E 92
I 92
			MAP_COPY|MAP_FIXED,
E 92
			(caddr_t)vp, (vm_offset_t)toff);
D 75
		(void) vm_map_protect(&vm->vm_map, addr,
			addr + trunc_page(ep->a_text),
E 75
I 75
		(void) vm_map_protect(&vm->vm_map, addr, addr + xts,
E 75
			VM_PROT_READ|VM_PROT_EXECUTE, FALSE);
I 71
#else /* COFF */
		addr = (vm_offset_t)vm->vm_taddr;
D 75
		size = round_page(ep->a_text);
E 75
I 75
		size = xts;
E 75
		error = vm_mmap(&vm->vm_map, &addr, size,
D 103
			VM_PROT_READ|VM_PROT_EXECUTE,
E 103
I 103
			VM_PROT_READ|VM_PROT_EXECUTE, VM_PROT_ALL,
E 103
D 92
			MAP_FILE|MAP_COPY|MAP_FIXED,
E 92
I 92
			MAP_COPY|MAP_FIXED,
E 92
			(caddr_t)vp, (vm_offset_t)toff);
		toff += size;
		addr = (vm_offset_t)vm->vm_daddr;
		size = round_page(ep->a_data);
D 103
		error = vm_mmap(&vm->vm_map, &addr, size, VM_PROT_ALL,
E 103
I 103
		error = vm_mmap(&vm->vm_map, &addr, size,
			VM_PROT_ALL, VM_PROT_ALL,
E 103
D 92
			MAP_FILE|MAP_COPY|MAP_FIXED,
E 92
I 92
			MAP_COPY|MAP_FIXED,
E 92
			(caddr_t)vp, (vm_offset_t)toff);
#endif /* COFF */
E 71
I 60
		vp->v_flag |= VTEXT;
E 60
E 59
E 56
E 36
	}
D 36
	mtpr(CCK, u.u_procp->p_ckey);
	dkeyrelease(u.u_procp->p_dkey);
	u.u_procp->p_dkey = getdatakey();
	mtpr(DCK, u.u_procp->p_dkey);
E 36
I 36
D 56
	mtpr(CCK, p->p_ckey);
	dkeyrelease(p->p_dkey);
	p->p_dkey = getdatakey();
	mtpr(DCK, p->p_dkey);
E 36
#endif
E 24
E 9
D 36
	if (pagi && u.u_procp->p_textp)
		vinifod((struct fpte *)dptopte(u.u_procp, 0),
D 33
		    PG_FTEXT, u.u_procp->p_textp->x_iptr,
E 33
I 33
		    PG_FTEXT, u.u_procp->p_textp->x_vptr,
E 36
I 36
D 46
	if (pagi && p->p_textp)
D 39
		vinifod((struct fpte *)dptopte(p, 0),
E 39
I 39
		vinifod(u.u_procp, (struct fpte *)dptopte(p, 0),
E 46
I 46
	if ((flags & SPAGV) && p->p_textp)
		vinifod(p, (struct fpte *)dptopte(p, 0),
E 46
E 39
		    PG_FTEXT, p->p_textp->x_vptr,
E 36
E 33
D 9
		    (long)(1 + ts/CLSIZE), (int)btoc(u.u_exdata.ux_dsize));
E 9
I 9
D 22
		    (long)(1 + ts/CLSIZE), (int)btoc(ep->a_data));
E 22
I 22
D 47
		    (long)(1 + ts/CLSIZE), (size_t)btoc(ep->a_data));
E 47
I 47
		    (long)(1 + ts/CLSIZE), (segsz_t)btoc(ep->a_data));
E 47
E 22
E 9

D 24
#ifdef vax
E 24
I 24
#if defined(vax) || defined(tahoe)
E 24
	/* THIS SHOULD BE DONE AT A LOWER LEVEL, IF AT ALL */
D 5
#include "../vax/mtpr.h"		/* XXX */
E 5
	mtpr(TBIA, 0);
I 46
#endif
#ifdef hp300
	TBIAU();
E 46
#endif
I 53
#if defined(i386)
	tlbflush();
#endif
E 56
I 56
D 75
badmap:
E 75
	if (error) {
I 75
badmap:
E 75
D 59
		if (map != VM_MAP_NULL)
			vm_deallocate(map, vm_map_min(map), vm_map_max(map));
E 59
D 101
		printf("pid %d: VM allocation failure\n", p->p_pid);
		uprintf("sorry, pid %d was killed in exec: VM allocation\n",
			p->p_pid);
		psignal(p, SIGKILL);
E 101
I 101
		killproc(p, "VM allocation in exec");
E 101
D 62
		p->p_flag |= SULOCK;
E 62
I 62
D 110
		p->p_flag |= SKEEP;
E 110
I 110
		p->p_flag |= P_NOSWAP;
E 110
E 62
		return(error);
	}
E 56
E 53

D 39
	if (u.u_error)
D 15
		swkill(u.u_procp, "i/o error mapping pages");
E 15
I 15
		swkill(u.u_procp, "exec: I/O error mapping pages");
E 39
E 15
	/*
	 * set SUID/SGID protections, if no tracing
	 */
D 36
	if ((u.u_procp->p_flag&STRC)==0) {
I 33
		if (uid != u.u_uid || gid != u.u_gid)
E 36
I 36
D 93
	if ((p->p_flag&STRC)==0) {
E 93
I 93
D 110
	p->p_flag &= ~SUGID;
	if ((p->p_flag & STRC) == 0) {
E 110
I 110
	p->p_flag &= ~P_SUGID;
	if ((p->p_flag & P_TRACED) == 0) {
E 110
E 93
D 48
		if (uid != u.u_cred->cr_uid || gid != u.u_cred->cr_gid)
E 36
			u.u_cred = crcopy(u.u_cred);
E 33
D 36
		u.u_uid = uid;
		u.u_procp->p_uid = uid;
		u.u_gid = gid;
E 36
I 36
		u.u_cred->cr_uid = uid;
		u.u_cred->cr_gid = gid;
E 48
I 48
D 54
		if (uid != cred->cr_uid || gid != cred->cr_gid)
E 54
I 54
		if (uid != cred->cr_uid || gid != cred->cr_gid) {
E 54
D 59
			u.u_cred = cred = crcopy(cred);
E 59
I 59
			p->p_ucred = cred = crcopy(cred);
I 112
#ifdef KTRACE
E 112
E 59
I 54
			/*
			 * If process is being ktraced, turn off - unless
			 * root set it.
			 */
			if (p->p_tracep && !(p->p_traceflag & KTRFAC_ROOT)) {
				vrele(p->p_tracep);
				p->p_tracep = NULL;
				p->p_traceflag = 0;
			}
I 112
#endif
E 112
I 75
			cred->cr_uid = uid;
			cred->cr_gid = gid;
I 93
D 110
			p->p_flag |= SUGID;
E 110
I 110
			p->p_flag |= P_SUGID;
E 110
E 93
E 75
		}
E 54
D 75
		cred->cr_uid = uid;
		cred->cr_gid = gid;
E 75
E 48
D 59
		p->p_uid = uid;
E 59
E 36
	} else
D 36
		psignal(u.u_procp, SIGTRAP);
E 36
I 36
		psignal(p, SIGTRAP);
D 59
	p->p_svuid = p->p_uid;
D 48
	p->p_svgid = u.u_cred->cr_gid;
E 48
I 48
	p->p_svgid = cred->cr_gid;
E 48
E 36
	u.u_tsize = ts;
	u.u_dsize = ds;
	u.u_ssize = ss;
I 7
	u.u_prof.pr_scale = 0;
E 59
I 59
	p->p_cred->p_svuid = cred->cr_uid;
	p->p_cred->p_svgid = cred->cr_gid;
D 75
	vm->vm_tsize = ts;
E 75
I 75
	vm->vm_tsize = btoc(xts);
E 75
	vm->vm_dsize = ds;
D 75
	vm->vm_ssize = ss;
E 75
I 75
D 88
	vm->vm_ssize = ssize;
E 88
I 88
	vm->vm_ssize = btoc(ssize);
E 88
E 75
D 95
	p->p_stats->p_prof.pr_scale = 0;
E 95
I 91
D 110
	if (p->p_flag & SPROFIL)
E 110
I 110
	if (p->p_flag & P_PROFIL)
E 110
		stopprofclock(p);
E 91
E 59
I 24
#if defined(tahoe)
D 64
	u.u_pcb.pcb_savacc.faddr = (float *)NULL;
E 64
I 64
	/* move this when tahoe cpu_exec is created */
	p->p_addr->u_pcb.pcb_savacc.faddr = (float *)NULL;
E 64
#endif
E 24
E 7
D 48
bad:
	return;
E 48
I 48
	return (0);
E 48
D 17
}

/*
 * Clear registers on exec
 */
D 9
setregs()
E 9
I 9
setregs(entry)
D 10
	int entry;
E 10
I 10
	u_long entry;
E 10
E 9
{
D 3
	register int (**rp)();
	register int i, sigmask;
E 3
I 3
	register int i;
E 3
I 2
	register struct proc *p = u.u_procp;
E 2

D 2
	for (rp = &u.u_signal[1], sigmask = 1; rp < &u.u_signal[NSIG];
	    sigmask <<= 1, rp++) {
		switch (*rp) {

		case SIG_IGN:
		case SIG_DFL:
		case SIG_HOLD:
			continue;

		default:
			/*
			 * Normal or deferring catch; revert to default.
			 */
E 2
I 2
D 3
	rp = &u.u_signal[1];
	for (sigmask = 1; rp < &u.u_signal[NSIG]; sigmask <<= 1, rp++)
		/* disallow masked signals to carry over? */
		if (p->p_sigcatch & sigmask && (p->p_sigmask & sigmask) == 0) {
E 2
			(void) spl6();
I 2
			p->p_sigcatch &= ~sigmask;
E 2
			*rp = SIG_DFL;
D 2
			if ((int)*rp & 1)
				u.u_procp->p_siga0 |= sigmask;
			else
				u.u_procp->p_siga0 &= ~sigmask;
			if ((int)*rp & 2)
				u.u_procp->p_siga1 |= sigmask;
			else
				u.u_procp->p_siga1 &= ~sigmask;
E 2
			(void) spl0();
D 2
			continue;
E 2
		}
E 3
I 3
	/*
	 * Reset caught signals.  Held signals
	 * remain held through p_sigmask.
	 */
	while (p->p_sigcatch) {
		(void) spl6();
		i = ffs(p->p_sigcatch);
		p->p_sigcatch &= ~(1 << (i - 1));
		u.u_signal[i] = SIG_DFL;
		(void) spl0();
	}
I 14
	/*
	 * Reset stack state to the user stack.
	 * Clear set of signals caught on the signal stack.
	 */
	u.u_onstack = 0;
	u.u_sigsp = 0;
	u.u_sigonstack = 0;
E 14
E 3
D 2
	}
E 2
D 5
#ifdef vax
E 5
D 3
/*
E 3
I 3
#ifdef notdef
	/* should pass args to init on the stack */
E 3
	for (rp = &u.u_ar0[0]; rp < &u.u_ar0[16];)
		*rp++ = 0;
D 3
*/
E 3
I 3
#endif
E 3
D 9
	u.u_ar0[PC] = u.u_exdata.ux_entloc+2;
E 9
I 9
	u.u_ar0[PC] = entry + 2;
E 9
D 5
#endif
#ifdef sun
	{ register struct regs *r = (struct regs *)u.u_ar0;
	  for (i = 0; i < 8; i++) {
		r->r_dreg[i] = 0;
		if (&r->r_areg[i] != &r->r_sp)
			r->r_areg[i] = 0;
	  }
	  r->r_sr = PSL_USERSET;
	  r->r_pc = u.u_exdata.ux_entloc;
	}
#endif
E 5
	for (i=0; i<NOFILE; i++) {
		if (u.u_pofile[i]&UF_EXCLOSE) {
D 4
			closef(u.u_ofile[i], u.u_pofile[i]);
E 4
I 4
			closef(u.u_ofile[i]);
E 4
			u.u_ofile[i] = NULL;
			u.u_pofile[i] = 0;
		}
		u.u_pofile[i] &= ~UF_MAPPED;
	}
E 17
D 8

	/*
	 * Remember file name for accounting.
	 */
	u.u_acflag &= ~AFORK;
	bcopy((caddr_t)u.u_dent.d_name, (caddr_t)u.u_comm,
	    (unsigned)(u.u_dent.d_namlen + 1));
E 8
D 5
#ifdef sun
	u.u_eosys = REALLYRETURN;
#endif
E 5
}
E 1
