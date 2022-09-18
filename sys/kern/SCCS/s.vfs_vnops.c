h38648
s 00002/00001/00421
d D 8.14 95/06/15 21:47:22 mckusick 117 116
c null pointer bug (from ralph)
e
s 00001/00013/00421
d D 8.13 95/05/27 22:17:26 mckusick 116 115
c delete read-only checking; it must be done by the filesystem layers
e
s 00000/00004/00434
d D 8.12 95/05/17 19:33:25 mckusick 115 114
c get rid of attempt to detect hanging
e
s 00048/00012/00390
d D 8.11 95/05/14 00:15:56 mckusick 114 113
c add vn_lock function; convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK
e
s 00001/00001/00401
d D 8.10 95/04/03 18:15:05 mckusick 113 112
c do synchronous writes when MNT_SYNCHRONOUS is set
e
s 00002/00000/00400
d D 8.9 95/04/02 15:07:25 mckusick 112 111
c request a synchronous write when O_FSYNC is set (from torek)
e
s 00002/00000/00398
d D 8.8 95/03/22 15:00:35 mckusick 111 110
c pass exclusive create flag in to VOP_CREATE
e
s 00001/00001/00397
d D 8.7 95/02/14 10:45:27 cgd 110 109
c insert a missing space.
e
s 00001/00001/00397
d D 8.6 95/01/09 18:22:37 cgd 109 108
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00001/00001/00397
d D 8.5 94/12/08 22:49:51 mckusick 108 107
c request IO_UNIT on writes, so failures cause truncation back to start
e
s 00002/00000/00396
d D 8.4 94/08/15 11:59:19 mckusick 107 106
c release the old controlling terminal if setting a new one
e
s 00004/00004/00392
d D 8.3 94/08/11 00:24:36 mckusick 106 105
c LEASE_CHECK => VOP_LEASE
e
s 00005/00000/00391
d D 8.2 94/01/21 17:18:19 bostic 105 104
c add USL's copyright notice
e
s 00002/00002/00389
d D 8.1 93/06/10 22:01:04 bostic 104 103
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00386
d D 7.47 93/04/27 16:18:31 mckusick 103 102
c bug fixes for LEASES from Rick Macklem
e
s 00013/00012/00378
d D 7.46 92/10/11 10:39:09 bostic 102 101
c make kernel includes standard
e
s 00001/00001/00389
d D 7.45 92/07/07 19:11:51 torek 101 100
c FIONREAD can only return 32-bit size
e
s 00000/00022/00390
d D 7.44 92/07/06 19:01:05 mckusick 100 99
c get rid of unused vn_fhtovp function
e
s 00000/00021/00412
d D 7.43 92/07/03 01:39:37 mckusick 99 98
c delete USES
e
s 00001/00001/00432
d D 7.42 92/06/25 13:02:45 mckusick 98 97
c FHTOVP no longer takes setgen parameter
e
s 00003/00006/00430
d D 7.41 92/06/19 19:20:32 mckusick 97 96
c timeval => timespec in vattr and dinode
e
s 00006/00003/00430
d D 7.40 92/05/31 21:39:16 mckusick 96 95
c stat structure now contains timespec's
e
s 00021/00000/00412
d D 7.39 92/05/14 17:36:55 heideman 95 86
c vnode interface conversion
e
s 00021/00000/00412
d R 7.39 92/05/14 15:53:57 heideman 94 86
c vnode interface conversion
e
s 00021/00000/00412
d R 7.39 92/05/14 14:55:40 heideman 93 86
c vnode interface conversion
e
s 00021/00000/00412
d R 7.39 92/05/14 13:00:49 heideman 92 86
c vnode interface conversion
e
s 00021/00000/00412
d R 7.39 92/05/14 11:58:35 heideman 91 86
c vnode interface conversion
e
s 00021/00000/00412
d R 7.39 92/05/14 10:38:33 heideman 90 86
c vnode interface conversion
e
s 00021/00000/00412
d R 7.39 92/05/13 23:17:42 heideman 89 86
c vnode interface conversion
e
s 00021/00000/00412
d R 7.39 92/05/13 19:02:12 heideman 88 86
c vnode interface conversion
e
s 00021/00000/00412
d R 7.39 92/05/13 18:34:21 heideman 87 86
c vnode interface conversion
e
s 00004/00006/00408
d D 7.38 92/05/13 14:50:28 mckusick 86 85
c stat times become timevals
e
s 00001/00001/00413
d D 7.37 92/02/04 14:28:56 mckusick 85 84
c have to get credential from the proc table
e
s 00012/00009/00402
d D 7.36 92/02/03 23:36:19 mckusick 84 83
c vn_open no longer take proc (now in ndp); new calling convention for namei
e
s 00002/00002/00409
d D 7.35 92/01/22 09:37:22 heideman 83 82
c lookup converted to new form
e
s 00010/00003/00401
d D 7.34 92/01/14 12:22:32 mckusick 82 81
c lease checks on read and write
e
s 00035/00017/00369
d D 7.33 91/06/27 12:00:10 mckusick 81 80
c add vn_closefile to avoid warnings about void * coersions
e
s 00012/00012/00374
d D 7.32 91/06/21 10:46:39 mckusick 80 79
c increment v_writecount when vn_open is called with intent to write;
c decrement v_writecount in vn_close for files open for writing
e
s 00014/00017/00372
d D 7.31 91/05/30 14:55:12 mckusick 79 78
c VOP_OPEN called with vnode locked; vn_open returns vnode locked;
c make file flags consistent
e
s 00001/00000/00388
d D 7.30 91/05/15 19:26:15 mckusick 78 77
c missing ABORTOP
e
s 00022/00019/00366
d D 7.29 91/04/16 00:06:41 mckusick 77 76
c add proc pointers to appropriate VOP and vnode operations
e
s 00000/00004/00385
d D 7.28 91/03/19 09:49:11 karels 76 75
c expunge user.h, other unneeded headers
e
s 00018/00030/00371
d D 7.27 91/03/17 15:41:14 karels 75 74
c more-or-less working with new proc & user structs
e
s 00001/00113/00400
d D 7.26 91/02/01 16:17:13 mckusick 74 73
c add POSIX-style byte-level record locking
e
s 00001/00003/00512
d D 7.25 90/12/05 17:38:37 mckusick 73 72
c update for new VM
e
s 00008/00005/00507
d D 7.24 90/08/22 12:42:09 mckusick 72 71
c fix typos in locking, streamline and fix vn_writechk
e
s 00001/00011/00511
d D 7.23 90/06/28 21:27:29 bostic 71 70
c new copyright notice
e
s 00000/00001/00522
d D 7.22 90/06/21 22:40:24 mckusick 70 69
c spurious setting of r_val1
e
s 00001/00001/00522
d D 7.21 90/06/21 11:10:03 mckusick 69 68
c do not have to check whether parent directory is NULL
e
s 00001/00001/00522
d D 7.20 90/05/04 20:55:51 mckusick 68 67
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00002/00002/00521
d D 7.19 90/05/03 18:44:51 mckusick 67 66
c vattr_null => VATTR_NULL
e
s 00013/00024/00510
d D 7.18 90/04/03 21:33:14 karels 66 65
c new tsleep; rm setjmp's; strings for sleep messages
e
s 00000/00002/00534
d D 7.17 90/03/26 17:30:55 mckusick 65 64
c get rid of unneeded includes
e
s 00006/00001/00530
d D 7.16 90/03/05 18:07:07 mckusick 64 63
c select now passes in file flags (to support FIFO's)
e
s 00001/00000/00530
d D 7.15 90/02/08 16:40:56 marc 63 62
c forgot tsleep.h
e
s 00002/00002/00528
d D 7.14 90/02/08 15:58:18 marc 62 61
c tsleep
e
s 00005/00003/00525
d D 7.13 89/12/21 11:25:12 mckusick 61 60
c do not unlock vp when trying to modify `.'
e
s 00026/00006/00502
d D 7.12 89/11/22 21:42:10 mckusick 60 59
c read/write locking is now done above the vnode layer
e
s 00006/00042/00502
d D 7.11 89/11/20 18:21:43 marc 59 58
c controlling terminal now a vnode; remove vhangup
e
s 00006/00045/00538
d D 7.10 89/10/24 18:46:26 mckusick 58 57
c header file cleanups; vput, vrele, and vref move to vfs_subr.c
e
s 00001/00005/00582
d D 7.9 89/08/26 00:04:03 mckusick 57 56
c va_bytes is really bytes; return st_blocks in S_BLKSIZE (512) units
e
s 00026/00031/00561
d D 7.8 89/07/03 22:13:40 mckusick 56 55
c replace vn_access with vn_writechk; 
c break up vn_access into its constituent parts vn_writechk and VOP_ACCESS
e
s 00014/00001/00578
d D 7.7 89/06/27 21:17:08 mckusick 55 54
c must vrelse vnode if VOP_OPEN fails; add vref
e
s 00002/00001/00577
d D 7.6 89/06/07 16:55:38 mckusick 54 53
c return flags and generation number in stat structure
e
s 00004/00004/00574
d D 7.5 89/05/27 16:57:44 mckusick 53 52
c update from Rick Macklem to generate proper error messages
e
s 00530/00100/00048
d D 7.4 89/05/09 17:05:56 mckusick 52 51
c merge in vnodes
e
s 00014/00012/00134
d D 7.3 89/04/26 19:21:41 mckusick 51 50
c use new form of suser()
e
s 00002/00002/00144
d D 7.2 89/04/25 14:42:41 mckusick 50 49
c ../machine => machine
e
s 00001/00001/00145
d D 7.1 86/06/05 00:12:38 mckusick 49 48
c 4.3BSD release version
e
s 00007/00001/00139
d D 6.5 85/06/08 14:51:25 mckusick 48 47
c Add copyright
e
s 00001/00001/00139
d D 6.4 85/03/18 15:19:00 karels 47 46
c add gid_t for groups; copy u.u_groups to int array for copyin/out
e
s 00013/00013/00127
d D 6.3 84/08/29 20:25:55 bloom 46 45
c Change to includes.  no more ../h
e
s 00007/00003/00133
d D 6.2 84/07/08 16:15:51 mckusick 45 44
c rework `namei' interface to eliminate global variables
e
s 00000/00000/00136
d D 6.1 83/07/29 06:42:02 sam 44 43
c 4.2 distribution
e
s 00000/00026/00136
d D 4.35 83/05/27 12:49:29 sam 43 42
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00002/00001/00160
d D 4.34 83/03/31 13:58:24 sam 42 40
c tighten up group search by checking for NOGROUP terminator
e
s 00002/00001/00160
d R 4.34 83/03/31 13:46:46 sam 41 40
c add NOGROUP identifier; add groupmember function; tighten group 
c lookup loop to stop at first NOGROUP entry
e
s 00025/00001/00136
d D 4.33 83/02/20 14:41:44 sam 40 37
c fix problem with access and setgid being incompatible
e
s 00040/00010/00127
d R 4.33 83/02/16 18:19:12 sam 39 37
c fix access and problems with setgid and saccess
e
s 00001/00001/00136
d R 4.33 83/02/10 18:42:06 sam 38 37
c groups set members are shorts, not ints; hz no longer in systm.h
e
s 00001/00001/00136
d D 4.32 82/12/31 16:54:27 sam 37 36
c group checks backwards
e
s 00002/00001/00135
d D 4.31 82/12/17 11:48:50 sam 36 35
c sun merge
e
s 00002/00001/00134
d D 4.30 82/11/13 22:52:51 sam 35 34
c merge of 4.1b and 4.1c
e
s 00005/00002/00130
d D 4.29 82/10/31 01:03:21 root 34 33
c allow writing on special files in read-only filesystem
e
s 00007/00013/00125
d D 4.28 82/10/17 11:35:00 root 33 32
c openi returns values
e
s 00007/00004/00131
d D 4.27 82/08/24 15:06:08 root 32 31
c new groups stuff
e
s 00004/00024/00131
d D 4.26 82/08/03 16:59:30 sam 31 29
c purge EFS crap
e
s 00004/00016/00139
d R 4.26 82/08/03 14:03:28 sam 30 29
c purge EFS stuff
e
s 00001/00168/00154
d D 4.25 82/07/24 18:12:00 root 29 28
c merge with calder
e
s 00032/00000/00290
d D 4.24 82/07/15 20:48:41 root 28 27
c EFS crud
e
s 00007/00005/00283
d D 4.23 82/04/19 19:35:26 mckusic 27 26
c merge into new file system
e
s 00003/00002/00285
d D 4.22 82/02/27 14:54:22 wnj 26 25
c symbolic links
e
s 00003/00001/00284
d D 4.21 82/02/15 13:28:16 wnj 25 24
c new multiple-group stuff
e
s 00002/00001/00283
d D 4.20 82/01/25 18:38:12 wnj 24 23
c bug fixes (round 1)
e
s 00007/00002/00277
d D 4.19 82/01/19 06:39:14 wnj 23 22
c closef parameter indicating whether error return
c to complete non-blc
e
s 00001/00001/00278
d D 4.18 82/01/19 05:16:41 root 22 21
c dont lose memory when closing non-blocking socket; this is blocking operation; set linger to 0 to not block then
e
s 00000/00000/00279
d D 4.17 81/11/18 15:44:43 wnj 21 20
c more cleanup
e
s 00002/00000/00277
d D 4.16 81/11/16 14:20:16 wnj 20 19
c lint
e
s 00001/00001/00276
d D 4.15 81/11/14 16:42:49 wnj 19 18
c before header overlay
e
s 00051/00061/00226
d D 4.14 81/11/08 16:47:41 wnj 18 17
c ilock/irele and get rid of FPORT and FNET stuff
e
s 00013/00019/00274
d D 4.13 81/10/11 13:02:05 wnj 17 16
c first bootable version
e
s 00006/00001/00287
d D 4.12 81/08/12 14:45:16 ecc 16 15
c new bbnnet
e
s 00001/00000/00287
d D 4.11 81/05/15 10:33:59 root 15 14
c zero f_inode when files allocated, so no trashy pointers for PORTs
e
s 00006/00000/00281
d D 4.10 81/05/12 17:18:12 root 14 13
c add tcp/ip
e
s 00010/00010/00271
d D 4.9 81/04/28 02:52:32 root 13 12
c changes to put in port code
e
s 00001/00001/00280
d D 4.8 81/03/09 01:47:00 wnj 12 11
c lint and a few minor fixed
e
s 00001/00010/00280
d D 4.7 81/03/06 11:36:58 wnj 11 10
c use tablefull()... no more UCBIPC
e
s 00010/00008/00280
d D 4.6 81/02/27 17:44:44 wnj 10 9
c dynamic allocation kernel
e
s 00002/00002/00286
d D 4.5 81/02/26 23:31:42 wnj 9 8
c rid of NFILE
e
s 00010/00008/00278
d D 4.4 81/02/01 18:01:24 wnj 8 7
c UCBIPC crud
e
s 00024/00009/00262
d D 4.3 81/01/28 12:03:08 kre 7 6
c call close with fp, not cp; flush buffer cache on last close
e
s 00001/00003/00270
d D 4.2 81/01/26 20:40:36 wnj 6 5
c multiplexore fix
e
s 00000/00000/00273
d D 4.1 80/11/09 17:31:51 bill 5 4
c minor fixups to restart stuff; version 4.1 for distrib
e
s 00002/00001/00271
d D 3.4 80/09/14 13:07:53 bill 4 3
c fix closef bug
e
s 00013/00007/00259
d D 3.3 80/07/19 20:11:47 bill 3 2
c circ search in falloc (poor mans 2 minute free list)
e
s 00001/00001/00265
d D 3.2 80/06/07 02:45:32 bill 2 1
c %H%->%G%
e
s 00266/00000/00000
d D 3.1 80/04/09 16:03:11 bill 1 0
c date and time created 80/04/09 16:03:11 by bill
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%H%	*/
E 2
I 2
D 12
/*	%M%	%I%	%G%	*/
E 12
I 12
D 29
/*	%M%	%I%	%E%	*/
E 29
I 29
D 31
/*	fio.c	4.25	82/07/17	*/
E 31
I 31
D 48
/*	%M%	%I%	%E%	*/
E 48
I 48
/*
D 49
 * Copyright (c) 1982 Regents of the University of California.
E 49
I 49
D 52
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 49
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 52
I 52
D 104
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 104
I 104
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 105
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 105
E 104
E 52
 *
I 52
D 71
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
E 71
I 71
 * %sccs.include.redist.c%
E 71
 *
E 52
 *	%W% (Berkeley) %G%
 */
E 48
E 31
E 29
E 12
E 2

I 36
D 50
#include "../machine/reg.h"

E 50
E 36
I 27
D 29
/* merged into kernel:	@(#)fio.c 2.2 4/8/82 */

E 29
E 27
D 46
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
D 27
#include "../h/filsys.h"
E 27
I 27
#include "../h/fs.h"
E 27
#include "../h/file.h"
#include "../h/conf.h"
#include "../h/inode.h"
D 36
#include "../h/reg.h"
E 36
#include "../h/acct.h"
I 7
#include "../h/mount.h"
I 20
#include "../h/socket.h"
#include "../h/socketvar.h"
I 23
#include "../h/proc.h"
E 46
I 46
D 102
#include "param.h"
#include "systm.h"
D 52
#include "dir.h"
E 52
D 76
#include "user.h"
E 76
D 52
#include "fs.h"
E 52
I 52
#include "kernel.h"
E 52
#include "file.h"
D 52
#include "conf.h"
#include "inode.h"
#include "acct.h"
#include "mount.h"
E 52
I 52
#include "stat.h"
#include "buf.h"
#include "proc.h"
D 76
#include "uio.h"
E 52
#include "socket.h"
#include "socketvar.h"
E 76
D 52
#include "proc.h"
E 52
I 52
#include "mount.h"
I 77
#include "namei.h"
E 77
#include "vnode.h"
D 58
#include "../ufs/inode.h"
E 58
D 65
#include "../ufs/fs.h"
#include "../ufs/quota.h"
E 65
#include "ioctl.h"
#include "tty.h"
E 102
I 102
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/ioctl.h>
#include <sys/tty.h>

E 102
I 86
#include <vm/vm.h>
E 86
I 63
D 66
#include "tsleep.h"
E 66
E 63
E 52
I 50

D 52
#include "machine/reg.h"
E 52
I 52
D 77
int	vn_read(), vn_write(), vn_ioctl(), vn_select(), vn_close();
E 77
struct 	fileops vnops =
D 81
	{ vn_read, vn_write, vn_ioctl, vn_select, vn_close };
E 81
I 81
	{ vn_read, vn_write, vn_ioctl, vn_select, vn_closefile };
E 81
E 52
E 50
E 46
I 35
D 45
#include "../h/nami.h"
E 45
E 35
I 28
D 31
#ifdef EFS
#include "../net/in.h"
#include "../h/efs.h"
#endif
E 31
E 28
E 23
E 20
E 7

/*
D 18
 * Convert a user supplied
 * file descriptor into a pointer
 * to a file structure.
 * Only task is to check range
 * of the descriptor.
E 18
I 18
D 29
 * Convert a user supplied file descriptor into a pointer
 * to a file structure.  Only task is to check range of the descriptor.
 * Critical paths should use the GETF macro, defined in inline.h.
E 18
 */
struct file *
getf(f)
D 18
register int f;
E 18
I 18
	register int f;
E 18
{
	register struct file *fp;

D 8
	if(0 <= f && f < NOFILE) {
		fp = u.u_ofile[f];
		if(fp != NULL)
			return(fp);
E 8
I 8
	if ((unsigned)f >= NOFILE || (fp = u.u_ofile[f]) == NULL) {
		u.u_error = EBADF;
		return (NULL);
E 8
	}
D 8
	u.u_error = EBADF;
	return(NULL);
E 8
I 8
D 11
#ifdef UCBIPC
	if (u.u_pofile[f] & ISPORT) {
		u.u_error = EISPORT;
		return (NULL);
	}
#endif
E 11
	return (fp);
E 8
}

/*
 * Internal form of close.
 * Decrement reference count on
 * file structure.
 * Also make sure the pipe protocol
 * does not constipate.
 *
 * Decrement reference count on the inode following
 * removal to the referencing file structure.
 * Call device handler on last close.
I 23
 * Nouser indicates that the user isn't available to present
 * errors to.
E 23
 */
D 23
closef(fp)
E 23
I 23
closef(fp, nouser)
E 23
D 18
register struct file *fp;
E 18
I 18
	register struct file *fp;
E 18
{
	register struct inode *ip;
I 7
	register struct mount *mp;
E 7
	int flag, mode;
	dev_t dev;
	register int (*cfunc)();
D 6
	struct chan *cp;
E 6

D 18
	if(fp == NULL)
E 18
I 18
	if (fp == NULL)
E 18
		return;
	if (fp->f_count > 1) {
		fp->f_count--;
		return;
	}
D 13
	ip = fp->f_inode;
E 13
	flag = fp->f_flag;
I 14
D 18
#ifdef BBNNET
	if (flag&FNET) {
		netclose(fp);
		return;
	}
#endif
E 14
I 13
	if (flag & FPORT) {
		ptclose(fp);
E 18
I 18
	if (flag & FSOCKET) {
I 24
		u.u_error = 0;			/* XXX */
E 24
D 19
		skclose(fp->f_socket);
E 19
I 19
D 22
		soclose(fp->f_socket);
E 22
I 22
D 23
		soclose(fp->f_socket, u.u_procp->p_flag&SWEXIT);
E 23
I 23
		soclose(fp->f_socket, nouser);
D 24
		if (u.u_error)
E 24
I 24
		if (nouser == 0 && u.u_error)
E 24
			return;
E 23
E 22
E 19
		fp->f_socket = 0;
E 18
		fp->f_count = 0;
		return;
	}
	ip = fp->f_inode;
E 13
D 6
	cp = fp->f_un.f_chan;
E 6
D 27
	dev = (dev_t)ip->i_un.i_rdev;
E 27
I 27
	dev = (dev_t)ip->i_rdev;
E 27
D 7
	mode = ip->i_mode;
E 7
I 7
	mode = ip->i_mode & IFMT;
E 7
D 13

E 13
D 18
	plock(ip);
E 18
I 18
	ilock(ip);
E 18
D 13
	fp->f_count = 0;
	if(flag & FPIPE) {
		ip->i_mode &= ~(IREAD|IWRITE);
		wakeup((caddr_t)ip+1);
		wakeup((caddr_t)ip+2);
	}
E 13
	iput(ip);
I 13
	fp->f_count = 0;
E 13

D 7
	switch(mode&IFMT) {
E 7
I 7
D 13
	switch(mode) {
E 13
I 13
	switch (mode) {
E 13
E 7

	case IFCHR:
D 17
	case IFMPC:
E 17
		cfunc = cdevsw[major(dev)].d_close;
I 28
#ifdef EFS
		/*
		 * Every close() must call the driver if the
		 * extended file system is being used -- not
		 * just the last close.  Pass along the file
		 * pointer for reference later.
		 */
		if (major(dev) == efs_major) {
			(*cfunc)(dev, flag, fp, nouser);
			return;
		}
#endif
E 28
		break;

	case IFBLK:
I 7
		/*
		 * We don't want to really close the device if it is mounted
		 */
		for (mp = mount; mp < &mount[NMOUNT]; mp++)
			if (mp->m_bufp != NULL && mp->m_dev == dev)
				return;
E 7
D 17
	case IFMPB:
E 17
		cfunc = bdevsw[major(dev)].d_close;
		break;
I 18

E 18
	default:
		return;
	}
D 18

D 7
	if (flag & FMP)
		goto call;
E 7
I 7
D 17
	if ((flag & FMP) == 0) {
D 9
		for(fp=file; fp < &file[NFILE]; fp++)
E 9
I 9
D 16
		for(fp=file; fp < fileNFILE; fp++)
E 16
I 16
		for(fp=file; fp < fileNFILE; fp++) {
E 17
I 17
	for(fp=file; fp < fileNFILE; fp++) {
E 17
#ifdef BBNNET
			if (fp->f_flag & FNET)
				continue;
#endif
E 18
I 18
	for (fp = file; fp < fileNFILE; fp++) {
		if (fp->f_flag & FSOCKET)
			continue;
E 18
E 16
E 9
D 13
			if (fp->f_count && (ip=fp->f_inode)->i_un.i_rdev==dev &&
E 13
I 13
D 17
			if (fp->f_count && (ip = fp->f_inode) &&
			    ip->i_un.i_rdev == dev &&
E 13
			    (ip->i_mode&IFMT) == mode)
				return;
I 16
		}
E 16
E 7
D 8

E 8
D 7
	for(fp=file; fp < &file[NFILE]; fp++)
D 4
		if (fp->f_count && fp->f_inode==ip)
E 4
I 4
		if (fp->f_count && (ip=fp->f_inode)->i_un.i_rdev==dev &&
		    (ip->i_mode&IFMT) == (mode&IFMT))
E 4
			return;
E 7
I 7
		if (mode == IFBLK) {
			/*
			 * on last close of a block device (that isn't mounted)
			 * we must invalidate any in core blocks
			 */
			bflush(dev);
			binval(dev);
		}
E 17
I 17
		if (fp->f_count && (ip = fp->f_inode) &&
D 18
		    ip->i_un.i_rdev == dev &&
		    (ip->i_mode&IFMT) == mode)
E 18
I 18
D 27
		    ip->i_un.i_rdev == dev && (ip->i_mode&IFMT) == mode)
E 27
I 27
		    ip->i_rdev == dev && (ip->i_mode&IFMT) == mode)
E 27
E 18
			return;
E 17
	}
I 17
	if (mode == IFBLK) {
		/*
D 18
		 * on last close of a block device (that isn't mounted)
E 18
I 18
		 * On last close of a block device (that isn't mounted)
E 18
		 * we must invalidate any in core blocks
		 */
		bflush(dev);
		binval(dev);
	}
E 17
E 7
D 8

E 8
D 7
call:
E 7
D 6
	(*cfunc)(dev, flag, cp);
E 6
I 6
	(*cfunc)(dev, flag, fp);
E 6
}

/*
E 29
D 18
 * openi called to allow handler
E 18
I 18
D 43
 * Openi called to allow handler
E 18
 * of special files to initialize and
 * validate before actual IO.
 */
I 28
D 31
#ifdef EFS
openi(ip, rw, trf)
#else
E 28
openi(ip, rw)
I 28
#endif
E 31
I 31
openi(ip, mode)
E 31
E 28
D 18
register struct inode *ip;
E 18
I 18
	register struct inode *ip;
E 18
{
D 33
	dev_t dev;
	register unsigned int maj;
E 33
I 33
	dev_t dev = (dev_t)ip->i_rdev;
	register u_int maj = major(dev);
E 33

D 27
	dev = (dev_t)ip->i_un.i_rdev;
E 27
I 27
D 33
	dev = (dev_t)ip->i_rdev;
E 27
	maj = major(dev);
E 33
D 18
	switch(ip->i_mode&IFMT) {
E 18
I 18
	switch (ip->i_mode&IFMT) {
E 18

	case IFCHR:
D 17
	case IFMPC:
E 17
D 18
		if(maj >= nchrdev)
E 18
I 18
		if (maj >= nchrdev)
E 18
D 33
			goto bad;
I 28
D 31
#ifdef EFS
		(*cdevsw[maj].d_open)(dev, rw, trf);
#else
E 28
		(*cdevsw[maj].d_open)(dev, rw);
I 28
#endif
E 31
I 31
		(*cdevsw[maj].d_open)(dev, mode);
E 31
E 28
		break;
E 33
I 33
			return (ENXIO);
		return ((*cdevsw[maj].d_open)(dev, mode));
E 33

	case IFBLK:
D 17
	case IFMPB:
E 17
D 18
		if(maj >= nblkdev)
E 18
I 18
		if (maj >= nblkdev)
E 18
D 33
			goto bad;
D 31
		(*bdevsw[maj].d_open)(dev, rw);
E 31
I 31
		(*bdevsw[maj].d_open)(dev, mode);
E 33
I 33
			return (ENXIO);
		return ((*bdevsw[maj].d_open)(dev, mode));
E 33
E 31
	}
D 33
	return;

bad:
	u.u_error = ENXIO;
E 33
I 33
	return (0);
E 33
}

/*
E 43
D 52
 * Check mode permission on inode pointer.
 * Mode is READ, WRITE or EXEC.
 * In the case of WRITE, the
 * read-only status of the file
 * system is checked.
 * Also in WRITE, prototype text
 * segments cannot be written.
 * The mode is shifted to select
 * the owner/group/other fields.
 * The super user is granted all
 * permissions.
E 52
I 52
 * Common code for vnode open operations.
 * Check permissions, and call the VOP_OPEN or VOP_CREATE routine.
E 52
 */
D 52
access(ip, mode)
D 18
register struct inode *ip;
E 18
I 18
	register struct inode *ip;
E 52
I 52
D 75
vn_open(ndp, fmode, cmode)
E 75
I 75
D 84
vn_open(ndp, p, fmode, cmode)
E 84
I 84
vn_open(ndp, fmode, cmode)
E 84
E 75
	register struct nameidata *ndp;
I 75
D 84
	struct proc *p;
E 84
E 75
	int fmode, cmode;
{
I 95
D 99
	USES_VOP_ABORTOP;
	USES_VOP_ACCESS;
	USES_VOP_CREATE;
	USES_VOP_OPEN;
	USES_VOP_SETATTR;
E 99
E 95
	register struct vnode *vp;
I 75
D 84
	register struct ucred *cred = p->p_ucred;
E 84
I 84
	register struct proc *p = ndp->ni_cnd.cn_proc;
D 85
	register struct ucred *cred = ndp->ni_cnd.cn_cred;
E 85
I 85
	register struct ucred *cred = p->p_ucred;
E 85
E 84
E 75
	struct vattr vat;
	struct vattr *vap = &vat;
	int error;

D 79
	if (fmode & FCREAT) {
E 79
I 79
	if (fmode & O_CREAT) {
E 79
D 84
		ndp->ni_nameiop = CREATE | LOCKPARENT | LOCKLEAF;
E 84
I 84
		ndp->ni_cnd.cn_nameiop = CREATE;
		ndp->ni_cnd.cn_flags = LOCKPARENT | LOCKLEAF;
E 84
D 79
		if ((fmode & FEXCL) == 0)
E 79
I 79
		if ((fmode & O_EXCL) == 0)
E 79
D 84
			ndp->ni_nameiop |= FOLLOW;
D 75
		if (error = namei(ndp))
E 75
I 75
		if (error = namei(ndp, p))
E 84
I 84
			ndp->ni_cnd.cn_flags |= FOLLOW;
		if (error = namei(ndp))
E 84
E 75
			return (error);
		if (ndp->ni_vp == NULL) {
D 67
			vattr_null(vap);
E 67
I 67
			VATTR_NULL(vap);
E 67
			vap->va_type = VREG;
			vap->va_mode = cmode;
I 111
			if (fmode & O_EXCL)
				vap->va_vaflags |= VA_EXCLUSIVE;
E 111
I 82
D 106
			LEASE_CHECK(ndp->ni_dvp, p, cred, LEASE_WRITE);
E 106
I 106
			VOP_LEASE(ndp->ni_dvp, p, cred, LEASE_WRITE);
E 106
E 82
D 77
			if (error = VOP_CREATE(ndp, vap))
E 77
I 77
D 83
			if (error = VOP_CREATE(ndp, vap, p))
E 83
I 83
D 84
			if (error = VOP_CREATE(ndp->ni_dvp, &ndp->ni_vp, &ndp->ni_cnd, vap))
E 84
I 84
			if (error = VOP_CREATE(ndp->ni_dvp, &ndp->ni_vp,
			    &ndp->ni_cnd, vap))
E 84
E 83
E 77
				return (error);
D 79
			fmode &= ~FTRUNC;
E 79
I 79
			fmode &= ~O_TRUNC;
E 79
			vp = ndp->ni_vp;
		} else {
I 78
D 83
			VOP_ABORTOP(ndp);
E 83
I 83
			VOP_ABORTOP(ndp->ni_dvp, &ndp->ni_cnd);
E 83
E 78
I 61
			if (ndp->ni_dvp == ndp->ni_vp)
				vrele(ndp->ni_dvp);
D 69
			else if (ndp->ni_dvp != NULL)
E 69
I 69
			else
E 69
				vput(ndp->ni_dvp);
			ndp->ni_dvp = NULL;
E 61
			vp = ndp->ni_vp;
D 61
			ndp->ni_vp = 0;
			VOP_ABORTOP(ndp);
			ndp->ni_vp = vp;
E 61
D 79
			if (fmode & FEXCL) {
E 79
I 79
			if (fmode & O_EXCL) {
E 79
				error = EEXIST;
				goto bad;
			}
D 79
			fmode &= ~FCREAT;
E 79
I 79
			fmode &= ~O_CREAT;
E 79
		}
	} else {
D 84
		ndp->ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
D 75
		if (error = namei(ndp))
E 75
I 75
		if (error = namei(ndp, p))
E 84
I 84
		ndp->ni_cnd.cn_nameiop = LOOKUP;
		ndp->ni_cnd.cn_flags = FOLLOW | LOCKLEAF;
		if (error = namei(ndp))
E 84
E 75
			return (error);
		vp = ndp->ni_vp;
	}
	if (vp->v_type == VSOCK) {
		error = EOPNOTSUPP;
		goto bad;
	}
D 79
	if ((fmode & FCREAT) == 0) {
E 79
I 79
	if ((fmode & O_CREAT) == 0) {
E 79
		if (fmode & FREAD) {
D 56
			if (error = vn_access(vp, VREAD, ndp->ni_cred))
E 56
I 56
D 75
			if (error = VOP_ACCESS(vp, VREAD, ndp->ni_cred))
E 75
I 75
D 77
			if (error = VOP_ACCESS(vp, VREAD, cred))
E 77
I 77
			if (error = VOP_ACCESS(vp, VREAD, cred, p))
E 77
E 75
E 56
				goto bad;
		}
D 79
		if (fmode & (FWRITE|FTRUNC)) {
E 79
I 79
		if (fmode & (FWRITE | O_TRUNC)) {
E 79
D 56
			if (error = vn_access(vp, VWRITE, ndp->ni_cred))
				goto bad;
E 56
			if (vp->v_type == VDIR) {
				error = EISDIR;
				goto bad;
			}
I 56
			if ((error = vn_writechk(vp)) ||
D 75
			    (error = VOP_ACCESS(vp, VWRITE, ndp->ni_cred)))
E 75
I 75
D 77
			    (error = VOP_ACCESS(vp, VWRITE, cred)))
E 77
I 77
			    (error = VOP_ACCESS(vp, VWRITE, cred, p)))
E 77
E 75
				goto bad;
E 56
		}
	}
D 79
	if (fmode & FTRUNC) {
E 79
I 79
	if (fmode & O_TRUNC) {
I 103
D 114
		VOP_UNLOCK(vp);				/* XXX */
E 114
I 114
		VOP_UNLOCK(vp, 0, p);				/* XXX */
E 114
D 106
		LEASE_CHECK(vp, p, cred, LEASE_WRITE);
E 106
I 106
		VOP_LEASE(vp, p, cred, LEASE_WRITE);
E 106
D 114
		VOP_LOCK(vp);					/* XXX */
E 114
I 114
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);	/* XXX */
E 114
E 103
E 79
D 67
		vattr_null(vap);
E 67
I 67
		VATTR_NULL(vap);
E 67
		vap->va_size = 0;
I 82
D 103
		LEASE_CHECK(vp, p, cred, LEASE_WRITE);
E 103
E 82
D 75
		if (error = VOP_SETATTR(vp, vap, ndp->ni_cred))
E 75
I 75
D 77
		if (error = VOP_SETATTR(vp, vap, cred))
E 77
I 77
		if (error = VOP_SETATTR(vp, vap, cred, p))
E 77
E 75
			goto bad;
	}
D 79
	VOP_UNLOCK(vp);
D 66
	if (setjmp(&u.u_qsave)) {
		if (error == 0)
			error = EINTR;
		return (error);
	}
E 66
D 55
	return (VOP_OPEN(vp, fmode, ndp->ni_cred));
E 55
I 55
D 75
	error = VOP_OPEN(vp, fmode, ndp->ni_cred);
E 75
I 75
D 77
	error = VOP_OPEN(vp, fmode, cred);
E 77
I 77
	error = VOP_OPEN(vp, fmode, cred, p);
E 77
E 75
	if (error)
		vrele(vp);
	return (error);
E 55

E 79
I 79
D 80
	if ((error = VOP_OPEN(vp, fmode, cred, p)) == 0)
		return (0);
E 80
I 80
	if (error = VOP_OPEN(vp, fmode, cred, p))
		goto bad;
	if (fmode & FWRITE)
		vp->v_writecount++;
	return (0);
E 80
E 79
bad:
	vput(vp);
D 66
	return(error);
E 66
I 66
	return (error);
E 66
}

/*
D 56
 * Check mode permission on vnode pointer. Mode is READ, WRITE or EXEC.
 * In the case of WRITE, the read-only status of the file system is
 * checked. Also in WRITE, prototype text segments cannot be written.
E 56
I 56
 * Check for write permissions on the specified vnode.
D 116
 * The read-only status of the file system is checked.
 * Also, prototype text segments cannot be written.
E 116
I 116
 * Prototype text segments cannot be written.
E 116
E 56
 */
D 56
vn_access(vp, mode, cred)
E 56
I 56
vn_writechk(vp)
E 56
	register struct vnode *vp;
E 52
D 56
	int mode;
I 52
	struct ucred *cred;
E 56
E 52
E 18
{
D 52
	register m;
I 32
D 47
	register int *gp;
E 47
I 47
	register gid_t *gp;
E 52
E 47
E 32

D 52
	m = mode;
D 18
	if(m == IWRITE) {
		if(getfs(ip->i_dev)->s_ronly != 0) {
E 18
I 18
	if (m == IWRITE) {
E 52
I 52
D 56
	if (mode & VWRITE) {
E 52
I 40
		/*
D 52
		 * Disallow write attempts on read-only
		 * file systems; unless the file is a block
		 * or character device resident on the
		 * file system.
E 52
I 52
		 * Disallow write attempts on read-only file systems;
		 * unless the file is a socket or a block or character
		 * device resident on the file system.
E 52
		 */
E 40
D 27
		if (getfs(ip->i_dev)->s_ronly != 0) {
E 27
I 27
D 52
		if (ip->i_fs->fs_ronly != 0) {
E 27
E 18
D 34
			u.u_error = EROFS;
D 18
			return(1);
E 18
I 18
			return (1);
E 34
I 34
			if ((ip->i_mode & IFMT) != IFCHR &&
			    (ip->i_mode & IFMT) != IFBLK) {
				u.u_error = EROFS;
				return (1);
			}
E 34
E 18
		}
E 52
I 52
		if ((vp->v_mount->m_flag & M_RDONLY) &&
			vp->v_type != VCHR &&
			vp->v_type != VBLK &&
			vp->v_type != VSOCK)
				return (EROFS);
E 52
D 40
		if (ip->i_flag&ITEXT)		/* try to free text */
E 40
I 40
		/*
		 * If there's shared text associated with
		 * the inode, try to free it up once.  If
		 * we fail, we can't allow writing.
		 */
D 52
		if (ip->i_flag&ITEXT)
E 40
			xrele(ip);
D 18
		if(ip->i_flag & ITEXT) {
E 18
I 18
		if (ip->i_flag & ITEXT) {
E 18
			u.u_error = ETXTBSY;
D 18
			return(1);
E 18
I 18
			return (1);
E 52
I 52
		if (vp->v_flag & VTEXT)
			xrele(vp);
		if (vp->v_flag & VTEXT)
			return (ETXTBSY);
	}
	return (VOP_ACCESS(vp, mode, cred));
E 56
I 56
D 116
	/*
	 * Disallow write attempts on read-only file systems;
	 * unless the file is a socket or a block or character
	 * device resident on the file system.
	 */
D 68
	if ((vp->v_mount->m_flag & M_RDONLY) && vp->v_type != VCHR &&
E 68
I 68
D 72
	if ((vp->v_mount->mnt_flag & MNT_RDONLY) && vp->v_type != VCHR &&
E 68
	    vp->v_type != VBLK && vp->v_type != VSOCK)
		return (EROFS);
E 72
I 72
	if (vp->v_mount->mnt_flag & MNT_RDONLY) {
		switch (vp->v_type) {
		case VREG: case VDIR: case VLNK:
			return (EROFS);
		}
	}
E 116
E 72
	/*
	 * If there's shared text associated with
	 * the vnode, try to free it up once.  If
	 * we fail, we can't allow writing.
	 */
D 73
	if (vp->v_flag & VTEXT)
		xrele(vp);
	if (vp->v_flag & VTEXT)
E 73
I 73
	if ((vp->v_flag & VTEXT) && !vnode_pager_uncache(vp))
E 73
		return (ETXTBSY);
	return (0);
E 56
}

/*
D 81
 * Vnode version of rdwri() for calls on file systems.
E 81
I 81
 * Vnode close call
E 81
 */
I 81
vn_close(vp, flags, cred, p)
	register struct vnode *vp;
	int flags;
	struct ucred *cred;
	struct proc *p;
{
I 95
D 99
	USES_VOP_CLOSE;
E 99
E 95
	int error;

	if (flags & FWRITE)
		vp->v_writecount--;
	error = VOP_CLOSE(vp, flags, cred, p);
	vrele(vp);
	return (error);
}

/*
 * Package up an I/O request on a vnode into a uio and do it.
 */
E 81
D 77
vn_rdwr(rw, vp, base, len, offset, segflg, ioflg, cred, aresid)
E 77
I 77
vn_rdwr(rw, vp, base, len, offset, segflg, ioflg, cred, aresid, p)
E 77
	enum uio_rw rw;
	struct vnode *vp;
	caddr_t base;
	int len;
	off_t offset;
	enum uio_seg segflg;
	int ioflg;
	struct ucred *cred;
	int *aresid;
I 77
	struct proc *p;
E 77
{
I 95
D 99
	USES_VOP_LOCK;
	USES_VOP_READ;
	USES_VOP_UNLOCK;
	USES_VOP_WRITE;
E 99
E 95
	struct uio auio;
	struct iovec aiov;
	int error;

I 60
	if ((ioflg & IO_NODELOCKED) == 0)
D 114
		VOP_LOCK(vp);
E 114
I 114
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 114
E 60
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	aiov.iov_base = base;
	aiov.iov_len = len;
	auio.uio_resid = len;
	auio.uio_offset = offset;
	auio.uio_segflg = segflg;
	auio.uio_rw = rw;
I 77
	auio.uio_procp = p;
E 77
D 82
	if (rw == UIO_READ)
E 82
I 82
	if (rw == UIO_READ) {
D 103
		LEASE_CHECK(vp, p, cred, LEASE_READ);
E 103
E 82
D 60
		error = VOP_READ(vp, &auio, &offset, ioflg, cred);
E 60
I 60
		error = VOP_READ(vp, &auio, ioflg, cred);
E 60
D 82
	else
E 82
I 82
	} else {
D 103
		LEASE_CHECK(vp, p, cred, LEASE_WRITE);
E 103
E 82
D 60
		error = VOP_WRITE(vp, &auio, &offset, ioflg, cred);
E 60
I 60
		error = VOP_WRITE(vp, &auio, ioflg, cred);
I 82
	}
E 82
E 60
	if (aresid)
		*aresid = auio.uio_resid;
	else
		if (auio.uio_resid && error == 0)
			error = EIO;
I 60
	if ((ioflg & IO_NODELOCKED) == 0)
D 114
		VOP_UNLOCK(vp);
E 114
I 114
		VOP_UNLOCK(vp, 0, p);
E 114
E 60
	return (error);
}

I 81
/*
 * File table vnode read routine.
 */
E 81
vn_read(fp, uio, cred)
	struct file *fp;
	struct uio *uio;
	struct ucred *cred;
{
I 95
D 99
	USES_VOP_LOCK;
	USES_VOP_READ;
	USES_VOP_UNLOCK;
E 99
E 95
I 60
D 114
	register struct vnode *vp = (struct vnode *)fp->f_data;
E 114
I 114
	struct vnode *vp = (struct vnode *)fp->f_data;
	struct proc *p = uio->uio_procp;
E 114
	int count, error;
E 60

I 103
D 106
	LEASE_CHECK(vp, uio->uio_procp, cred, LEASE_READ);
E 106
I 106
D 114
	VOP_LEASE(vp, uio->uio_procp, cred, LEASE_READ);
E 106
E 103
D 60
	return (VOP_READ((struct vnode *)fp->f_data, uio, &(fp->f_offset),
		(fp->f_flag & FNDELAY) ? IO_NDELAY : 0, cred));
E 60
I 60
	VOP_LOCK(vp);
E 114
I 114
	VOP_LEASE(vp, p, cred, LEASE_READ);
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 114
	uio->uio_offset = fp->f_offset;
	count = uio->uio_resid;
I 82
D 103
	LEASE_CHECK(vp, uio->uio_procp, cred, LEASE_READ);
E 103
E 82
D 79
	error = VOP_READ(vp, uio, (fp->f_flag & FNDELAY) ? IO_NDELAY : 0, cred);
E 79
I 79
	error = VOP_READ(vp, uio, (fp->f_flag & FNONBLOCK) ? IO_NDELAY : 0,
		cred);
E 79
	fp->f_offset += count - uio->uio_resid;
D 114
	VOP_UNLOCK(vp);
E 114
I 114
	VOP_UNLOCK(vp, 0, p);
E 114
	return (error);
E 60
}

I 81
/*
 * File table vnode write routine.
 */
E 81
vn_write(fp, uio, cred)
	struct file *fp;
	struct uio *uio;
	struct ucred *cred;
{
I 95
D 99
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
	USES_VOP_WRITE;
E 99
E 95
D 114
	register struct vnode *vp = (struct vnode *)fp->f_data;
E 114
I 114
	struct vnode *vp = (struct vnode *)fp->f_data;
	struct proc *p = uio->uio_procp;
E 114
D 60
	int ioflag = 0;
E 60
I 60
D 108
	int count, error, ioflag = 0;
E 108
I 108
	int count, error, ioflag = IO_UNIT;
E 108
E 60

D 79
	if (vp->v_type == VREG && (fp->f_flag & FAPPEND))
E 79
I 79
	if (vp->v_type == VREG && (fp->f_flag & O_APPEND))
E 79
		ioflag |= IO_APPEND;
D 79
	if (fp->f_flag & FNDELAY)
E 79
I 79
	if (fp->f_flag & FNONBLOCK)
E 79
		ioflag |= IO_NDELAY;
I 112
D 113
	if (fp->f_flag & O_FSYNC)
E 113
I 113
D 117
	if ((fp->f_flag & O_FSYNC) || (vp->v_mount->mnt_flag & MNT_SYNCHRONOUS))
E 117
I 117
	if ((fp->f_flag & O_FSYNC) ||
	    (vp->v_mount && (vp->v_mount->mnt_flag & MNT_SYNCHRONOUS)))
E 117
E 113
		ioflag |= IO_SYNC;
E 112
I 103
D 106
	LEASE_CHECK(vp, uio->uio_procp, cred, LEASE_WRITE);
E 106
I 106
D 114
	VOP_LEASE(vp, uio->uio_procp, cred, LEASE_WRITE);
E 106
E 103
D 60
	return (VOP_WRITE(vp, uio, &(fp->f_offset), ioflag, cred));
E 60
I 60
	VOP_LOCK(vp);
E 114
I 114
	VOP_LEASE(vp, p, cred, LEASE_WRITE);
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 114
	uio->uio_offset = fp->f_offset;
	count = uio->uio_resid;
I 82
D 103
	LEASE_CHECK(vp, uio->uio_procp, cred, LEASE_WRITE);
E 103
E 82
	error = VOP_WRITE(vp, uio, ioflag, cred);
	if (ioflag & IO_APPEND)
		fp->f_offset = uio->uio_offset;
	else
		fp->f_offset += count - uio->uio_resid;
D 114
	VOP_UNLOCK(vp);
E 114
I 114
	VOP_UNLOCK(vp, 0, p);
E 114
	return (error);
E 60
}

/*
D 81
 * Get stat info for a vnode.
E 81
I 81
 * File table vnode stat routine.
E 81
 */
D 77
vn_stat(vp, sb)
E 77
I 77
vn_stat(vp, sb, p)
E 77
	struct vnode *vp;
	register struct stat *sb;
I 77
	struct proc *p;
E 77
{
I 95
D 99
	USES_VOP_GETATTR;
E 99
E 95
	struct vattr vattr;
I 75
D 77
	struct proc *p = curproc;		/* XXX */
E 77
E 75
	register struct vattr *vap;
	int error;
	u_short mode;

	vap = &vattr;
D 75
	error = VOP_GETATTR(vp, vap, u.u_cred);
E 75
I 75
D 77
	error = VOP_GETATTR(vp, vap, p->p_ucred);
E 77
I 77
	error = VOP_GETATTR(vp, vap, p->p_ucred, p);
E 77
E 75
	if (error)
		return (error);
	/*
	 * Copy from vattr table
	 */
	sb->st_dev = vap->va_fsid;
	sb->st_ino = vap->va_fileid;
	mode = vap->va_mode;
	switch (vp->v_type) {
	case VREG:
D 58
		mode |= IFREG;
E 58
I 58
		mode |= S_IFREG;
E 58
		break;
	case VDIR:
D 58
		mode |= IFDIR;
E 58
I 58
		mode |= S_IFDIR;
E 58
		break;
	case VBLK:
D 58
		mode |= IFBLK;
E 58
I 58
		mode |= S_IFBLK;
E 58
		break;
	case VCHR:
D 58
		mode |= IFCHR;
E 58
I 58
		mode |= S_IFCHR;
E 58
		break;
	case VLNK:
D 58
		mode |= IFLNK;
E 58
I 58
		mode |= S_IFLNK;
E 58
		break;
	case VSOCK:
D 58
		mode |= IFSOCK;
E 58
I 58
		mode |= S_IFSOCK;
E 58
		break;
I 64
	case VFIFO:
		mode |= S_IFIFO;
		break;
E 64
	default:
		return (EBADF);
	};
	sb->st_mode = mode;
	sb->st_nlink = vap->va_nlink;
	sb->st_uid = vap->va_uid;
	sb->st_gid = vap->va_gid;
	sb->st_rdev = vap->va_rdev;
	sb->st_size = vap->va_size;
D 86
	sb->st_atime = vap->va_atime.tv_sec;
	sb->st_spare1 = 0;
	sb->st_mtime = vap->va_mtime.tv_sec;
	sb->st_spare2 = 0;
	sb->st_ctime = vap->va_ctime.tv_sec;
	sb->st_spare3 = 0;
E 86
I 86
D 96
	sb->st_atimeval= vap->va_atime;
	sb->st_mtimeval= vap->va_mtime;
	sb->st_ctimeval= vap->va_ctime;
E 96
I 96
D 97
	sb->st_atimespec.ts_sec = vap->va_atime.tv_sec;
	sb->st_atimespec.ts_nsec = vap->va_atime.tv_usec * 1000;
	sb->st_mtimespec.ts_sec = vap->va_mtime.tv_sec;
	sb->st_mtimespec.ts_nsec = vap->va_mtime.tv_usec * 1000;
	sb->st_ctimespec.ts_sec = vap->va_ctime.tv_sec;
	sb->st_ctimespec.ts_nsec = vap->va_ctime.tv_usec * 1000;
E 97
I 97
	sb->st_atimespec = vap->va_atime;
D 110
	sb->st_mtimespec= vap->va_mtime;
E 110
I 110
	sb->st_mtimespec = vap->va_mtime;
E 110
	sb->st_ctimespec = vap->va_ctime;
E 97
E 96
E 86
	sb->st_blksize = vap->va_blocksize;
D 54
	sb->st_spare4[0] = sb->st_spare4[1] = 0;
E 54
I 54
	sb->st_flags = vap->va_flags;
	sb->st_gen = vap->va_gen;
E 54
D 57
	/*
	 * XXX THIS IS NOT CORRECT!!, but be sure to change ufs_getattr()
	 * if you change it.
	 */
	sb->st_blocks = vap->va_bytes;
E 57
I 57
	sb->st_blocks = vap->va_bytes / S_BLKSIZE;
E 57
	return (0);
}

/*
D 81
 * Vnode ioctl call
E 81
I 81
 * File table vnode ioctl routine.
E 81
 */
D 77
vn_ioctl(fp, com, data)
E 77
I 77
vn_ioctl(fp, com, data, p)
E 77
	struct file *fp;
D 109
	int com;
E 109
I 109
	u_long com;
E 109
	caddr_t data;
I 77
	struct proc *p;
E 77
{
I 95
D 99
	USES_VOP_GETATTR;
	USES_VOP_IOCTL;
E 99
E 95
	register struct vnode *vp = ((struct vnode *)fp->f_data);
I 75
D 77
	struct proc *p = curproc;		/* XXX */
E 77
E 75
	struct vattr vattr;
	int error;

	switch (vp->v_type) {

	case VREG:
	case VDIR:
		if (com == FIONREAD) {
D 75
			if (error = VOP_GETATTR(vp, &vattr, u.u_cred))
E 75
I 75
D 77
			if (error = VOP_GETATTR(vp, &vattr, p->p_ucred))
E 77
I 77
			if (error = VOP_GETATTR(vp, &vattr, p->p_ucred, p))
E 77
E 75
				return (error);
D 101
			*(off_t *)data = vattr.va_size - fp->f_offset;
E 101
I 101
			*(int *)data = vattr.va_size - fp->f_offset;
E 101
			return (0);
E 52
E 18
		}
I 52
		if (com == FIONBIO || com == FIOASYNC)	/* XXX */
			return (0);			/* XXX */
		/* fall into ... */

	default:
		return (ENOTTY);

I 64
	case VFIFO:
E 64
	case VCHR:
	case VBLK:
D 70
		u.u_r.r_val1 = 0;
E 70
D 66
		if (setjmp(&u.u_qsave)) {
			if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
				return(EINTR);
			u.u_eosys = RESTARTSYS;
			return (0);
		}
E 66
D 59
		return (VOP_IOCTL(vp, com, data, fp->f_flag, u.u_cred));
E 59
I 59
D 75
		error = VOP_IOCTL(vp, com, data, fp->f_flag, u.u_cred);
E 75
I 75
D 77
		error = VOP_IOCTL(vp, com, data, fp->f_flag, p->p_ucred);
E 77
I 77
		error = VOP_IOCTL(vp, com, data, fp->f_flag, p->p_ucred, p);
E 77
E 75
		if (error == 0 && com == TIOCSCTTY) {
I 107
			if (p->p_session->s_ttyvp)
				vrele(p->p_session->s_ttyvp);
E 107
D 75
			u.u_procp->p_session->s_ttyvp = vp;
E 75
I 75
			p->p_session->s_ttyvp = vp;
E 75
			VREF(vp);
		}
		return (error);
E 59
E 52
	}
I 52
}

/*
D 81
 * Vnode select call
E 81
I 81
 * File table vnode select routine.
E 81
 */
D 77
vn_select(fp, which)
E 77
I 77
vn_select(fp, which, p)
E 77
	struct file *fp;
	int which;
I 77
	struct proc *p;
E 77
{
I 95
D 99
	USES_VOP_SELECT;
E 99
E 95
I 75
D 77
	struct proc *p = curproc;		/* XXX */
E 77

E 75
D 64
	return(VOP_SELECT(((struct vnode *)fp->f_data), which, u.u_cred));
E 64
I 64
D 66
	return(VOP_SELECT(((struct vnode *)fp->f_data), which, fp->f_flag,
E 66
I 66
	return (VOP_SELECT(((struct vnode *)fp->f_data), which, fp->f_flag,
E 66
D 75
		u.u_cred));
E 75
I 75
D 77
		p->p_ucred));
E 77
I 77
D 81
		p->p_ucred, p));
E 81
I 81
		fp->f_cred, p));
I 114
}

/*
 * Check that the vnode is still valid, and if so
 * acquire requested lock.
 */
int
vn_lock(vp, flags, p)
	struct vnode *vp;
	int flags;
	struct proc *p;
{
	int error;
	
	do {
		if ((flags & LK_INTERLOCK) == 0)
			simple_lock(&vp->v_interlock);
		if (vp->v_flag & VXLOCK) {
			vp->v_flag |= VXWANT;
			simple_unlock(&vp->v_interlock);
			tsleep((caddr_t)vp, PINOD, "vn_lock", 0);
			error = ENOENT;
		} else {
			error = VOP_LOCK(vp, flags | LK_INTERLOCK, p);
			if (error == 0)
				return (error);
D 115
#ifdef DEBUG
			if (error == EWOULDBLOCK)
				panic("vn_lock: hung lock");
#endif
E 115
		}
		flags &= ~LK_INTERLOCK;
	} while (flags & LK_RETRY);
	return (error);
E 114
E 81
E 77
E 75
E 64
}

/*
D 81
 * Vnode close call
E 81
I 81
 * File table vnode close routine.
E 81
 */
D 77
vn_close(fp)
E 77
I 77
D 80
vn_close(fp, p)
E 77
	register struct file *fp;
E 80
I 80
D 81
vn_close(vp, flags, cred, p)
	register struct vnode *vp;
	int flags;
	struct ucred *cred;
E 81
I 81
vn_closefile(fp, p)
	struct file *fp;
E 81
E 80
I 77
	struct proc *p;
E 77
{
D 80
	struct vnode *vp = ((struct vnode *)fp->f_data);
E 80
D 81
	int error;
E 81

D 74
	if (fp->f_flag & (FSHLOCK|FEXLOCK))
		vn_unlock(fp, FSHLOCK|FEXLOCK);
E 74
E 52
I 40
D 80
	/*
D 52
	 * If you're the super-user,
	 * you always get access.
E 52
I 52
	 * Must delete vnode reference from this file entry
	 * before VOP_CLOSE, so that only other references
	 * will prevent close.
E 52
	 */
E 40
D 18
	if(u.u_uid == 0)
		return(0);
	if(u.u_uid != ip->i_uid) {
E 18
I 18
D 52
	if (u.u_uid == 0)
E 52
I 52
	fp->f_data = (caddr_t) 0;
D 74
	error = VOP_CLOSE(vp, fp->f_flag, u.u_cred);
E 74
I 74
D 77
	error = VOP_CLOSE(vp, fp->f_flag, fp->f_cred);
E 77
I 77
	error = VOP_CLOSE(vp, fp->f_flag, fp->f_cred, p);
E 80
I 80
D 81
	if (flags & FWRITE)
		vp->v_writecount--;
	error = VOP_CLOSE(vp, flags, cred, p);
E 80
E 77
E 74
	vrele(vp);
	return (error);
E 81
I 81
	return (vn_close(((struct vnode *)fp->f_data), fp->f_flag,
		fp->f_cred, p));
E 81
D 74
}

/*
 * Place an advisory lock on a vnode.
 * !! THIS IMPLIES THAT ALL STATEFUL FILE SERVERS WILL USE file table entries
 */
vn_lock(fp, cmd)
	register struct file *fp;
	int cmd;
{
	register int priority = PLOCK;
	register struct vnode *vp = (struct vnode *)fp->f_data;
I 66
	int error = 0;
	static char lockstr[] = "flock";
E 66

	if ((cmd & LOCK_EX) == 0)
		priority += 4;
D 66
	if (setjmp(&u.u_qsave)) {
		if ((u.u_sigintr & sigmask(u.u_procp->p_cursig)) != 0)
			return(EINTR);
		u.u_eosys = RESTARTSYS;
E 52
		return (0);
I 52
	}
E 66
I 66
	priority |= PCATCH;

E 66
E 52
I 40
	/*
D 52
	 * Access check is based on only
	 * one of owner, group, public.
	 * If not owner, then check group.
	 * If not a member of the group, then
	 * check public access.
E 52
I 52
	 * If there's a exclusive lock currently applied
	 * to the file, then we've gotta wait for the
	 * lock with everyone else.
E 52
	 */
E 40
D 52
	if (u.u_uid != ip->i_uid) {
E 18
		m >>= 3;
I 40
		if (u.u_gid == ip->i_gid)
			goto found;
E 40
D 18
		if(u.u_gid != ip->i_gid)
E 18
I 18
D 25
		if (u.u_gid != ip->i_gid)
E 25
I 25
D 32
		if (ip->i_gid >= NGRPS ||
		    (u.u_grps[ip->i_gid/(sizeof(int)*8)] &
		     (1 << ip->i_gid%(sizeof(int)*8)) == 0))
E 25
E 18
			m >>= 3;
E 32
I 32
D 42
		for (gp = u.u_groups; gp < &u.u_groups[NGROUPS]; gp++)
E 42
I 42
		gp = u.u_groups;
		for (; gp < &u.u_groups[NGROUPS] && *gp != NOGROUP; gp++)
E 42
D 37
			if (ip->i_gid != *gp)
E 37
I 37
			if (ip->i_gid == *gp)
E 37
				goto found;
		m >>= 3;
found:
		;
E 52
I 52
again:
	while (vp->v_flag & VEXLOCK) {
		/*
		 * If we're holding an exclusive
		 * lock, then release it.
		 */
		if (fp->f_flag & FEXLOCK) {
			vn_unlock(fp, FEXLOCK);
			continue;
		}
		if (cmd & LOCK_NB)
			return (EWOULDBLOCK);
		vp->v_flag |= VLWAIT;
D 62
		sleep((caddr_t)&vp->v_exlockc, priority);
E 62
I 62
D 66
		tsleep((caddr_t)&vp->v_exlockc, priority, SLP_EXLCK, 0);
E 66
I 66
		if (error = tsleep((caddr_t)&vp->v_exlockc, priority,
		    lockstr, 0))
			return (error);
E 66
E 62
E 52
E 32
	}
D 18
	if((ip->i_mode&m) != 0)
		return(0);

E 18
I 18
D 52
	if ((ip->i_mode&m) != 0)
		return (0);
E 18
	u.u_error = EACCES;
D 18
	return(1);
E 18
I 18
	return (1);
E 52
I 52
D 66
	if ((cmd & LOCK_EX) && (vp->v_flag & VSHLOCK)) {
E 66
I 66
D 72
	if (error = 0 && (cmd & LOCK_EX) && (vp->v_flag & VSHLOCK)) {
E 72
I 72
	if (error == 0 && (cmd & LOCK_EX) && (vp->v_flag & VSHLOCK)) {
E 72
E 66
		/*
		 * Must wait for any shared locks to finish
		 * before we try to apply a exclusive lock.
		 *
		 * If we're holding a shared
		 * lock, then release it.
		 */
		if (fp->f_flag & FSHLOCK) {
			vn_unlock(fp, FSHLOCK);
			goto again;
		}
		if (cmd & LOCK_NB)
			return (EWOULDBLOCK);
		vp->v_flag |= VLWAIT;
D 62
		sleep((caddr_t)&vp->v_shlockc, PLOCK);
E 62
I 62
D 66
		tsleep((caddr_t)&vp->v_shlockc, PLOCK, SLP_SHLCK, 0);
E 62
		goto again;
E 66
I 66
		if (error = tsleep((caddr_t)&vp->v_shlockc, PLOCK | PCATCH,
D 72
		    lockstr, 0) == 0)
E 72
I 72
		    lockstr, 0))
E 72
			return (error);
E 66
	}
	if (fp->f_flag & FEXLOCK)
		panic("vn_lock");
	if (cmd & LOCK_EX) {
		cmd &= ~LOCK_SH;
		vp->v_exlockc++;
		vp->v_flag |= VEXLOCK;
		fp->f_flag |= FEXLOCK;
	}
	if ((cmd & LOCK_SH) && (fp->f_flag & FSHLOCK) == 0) {
		vp->v_shlockc++;
		vp->v_flag |= VSHLOCK;
		fp->f_flag |= FSHLOCK;
	}
	return (0);
E 52
E 18
}

/*
D 52
 * Look up a pathname and test if
 * the resultant inode is owned by the
 * current user.
 * If not, try for super-user.
 * If permission is granted,
 * return inode pointer.
E 52
I 52
 * Unlock a file.
E 52
 */
D 52
struct inode *
D 26
owner()
E 26
I 26
D 45
owner(follow)
E 45
I 45
owner(fname, follow)
	caddr_t fname;
E 45
	int follow;
E 52
I 52
vn_unlock(fp, kind)
	register struct file *fp;
	int kind;
E 52
E 26
{
D 52
	register struct inode *ip;
I 45
	register struct nameidata *ndp = &u.u_nd;
E 52
I 52
	register struct vnode *vp = (struct vnode *)fp->f_data;
	int flags;
E 52
E 45

D 26
	ip = namei(uchar, 0);
E 26
I 26
D 35
	ip = namei(uchar, 0, follow);
E 35
I 35
D 45
	ip = namei(uchar, LOOKUP, follow);
E 45
I 45
D 52
	ndp->ni_nameiop = LOOKUP | follow;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = fname;
	ip = namei(ndp);
E 45
E 35
E 26
D 18
	if(ip == NULL)
		return(NULL);
	if(u.u_uid == ip->i_uid)
		return(ip);
	if(suser())
		return(ip);
E 18
I 18
	if (ip == NULL)
		return (NULL);
I 28
D 31
#ifdef EFS
	/*
	 * References to extended file system are
	 * returned to the caller.
	 */
	if (efsinode(ip))
		return (ip);
#endif
E 31
E 28
	if (u.u_uid == ip->i_uid)
		return (ip);
D 51
	if (suser())
		return (ip);
E 18
	iput(ip);
D 18
	return(NULL);
E 18
I 18
	return (NULL);
E 51
I 51
	if (u.u_error = suser(u.u_cred, &u.u_acflag)) {
		iput(ip);
		return (NULL);
E 52
I 52
	kind &= fp->f_flag;
	if (vp == NULL || kind == 0)
		return;
	flags = vp->v_flag;
	if (kind & FSHLOCK) {
		if ((flags & VSHLOCK) == 0)
			panic("vn_unlock: SHLOCK");
		if (--vp->v_shlockc == 0) {
			vp->v_flag &= ~VSHLOCK;
			if (flags & VLWAIT)
				wakeup((caddr_t)&vp->v_shlockc);
		}
		fp->f_flag &= ~FSHLOCK;
E 52
	}
D 52
	return (ip);
E 52
I 52
	if (kind & FEXLOCK) {
		if ((flags & VEXLOCK) == 0)
			panic("vn_unlock: EXLOCK");
		if (--vp->v_exlockc == 0) {
			vp->v_flag &= ~(VEXLOCK|VLWAIT);
			if (flags & VLWAIT)
				wakeup((caddr_t)&vp->v_exlockc);
		}
		fp->f_flag &= ~FEXLOCK;
	}
E 74
E 52
E 51
E 18
}
D 100

/*
D 51
 * Test if the current user is the
 * super user.
E 51
I 51
D 52
 * Test if the current user is the super user.
E 52
I 52
 * vn_fhtovp() - convert a fh to a vnode ptr (optionally locked)
 * 	- look up fsid in mount list (if not found ret error)
 *	- get vp by calling VFS_FHTOVP() macro
 *	- if lockflag lock it with VOP_LOCK()
E 52
E 51
 */
D 51
suser()
E 51
I 51
D 52
suser(uid, acflag)
	uid_t uid;
	short *acflag;
E 52
I 52
vn_fhtovp(fhp, lockflag, vpp)
	fhandle_t *fhp;
	int lockflag;
	struct vnode **vpp;
E 52
E 51
{
I 95
D 99
	USES_VOP_UNLOCK;
E 99
E 95
I 52
	register struct mount *mp;
D 58
	int error;
E 58
E 52

D 18
	if(u.u_uid == 0) {
E 18
I 18
D 51
	if (u.u_uid == 0) {
E 18
		u.u_acflag |= ASU;
D 18
		return(1);
E 18
I 18
		return (1);
E 51
I 51
D 52
	if (uid == 0) {
		if (acflag)
			*acflag |= ASU;
		return (0);
E 52
I 52
	if ((mp = getvfs(&fhp->fh_fsid)) == NULL)
		return (ESTALE);
D 53
	if (error = VFS_FHTOVP(mp, &fhp->fh_fid, vpp))
		return (error);
	if (lockflag)
		VOP_LOCK(*vpp);
E 53
I 53
D 82
	if (VFS_FHTOVP(mp, &fhp->fh_fid, vpp))
E 82
I 82
D 98
	if (VFS_FHTOVP(mp, &fhp->fh_fid, 0, vpp))
E 98
I 98
	if (VFS_FHTOVP(mp, &fhp->fh_fid, vpp))
E 98
E 82
		return (ESTALE);
	if (!lockflag)
		VOP_UNLOCK(*vpp);
E 53
D 75
	return (0);
D 59
}

/*
 * Revoke access the current tty by all processes.
 * Used only by the super-user in init
 * to give ``clean'' terminals at login.
 */
vhangup()
{

	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
	if (u.u_ttyp == NULL)
		return;
	forceclose(u.u_ttyd);
	if ((u.u_ttyp->t_state) & TS_ISOPEN)
		gsignal(u.u_ttyp->t_pgid, SIGHUP);
	u.u_ttyp->t_session = 0;
	u.u_ttyp->t_pgid = 0;
}

forceclose(dev)
	dev_t dev;
{
	register struct file *fp;
	register struct vnode *vp;

	for (fp = file; fp < fileNFILE; fp++) {
		if (fp->f_count == 0)
			continue;
		if (fp->f_type != DTYPE_VNODE)
			continue;
		vp = (struct vnode *)fp->f_data;
		if (vp == 0)
			continue;
		if (vp->v_type != VCHR)
			continue;
		if (vp->v_rdev != dev)
			continue;
		fp->f_flag &= ~(FREAD|FWRITE);
E 52
E 51
E 18
	}
E 59
I 55
D 58
}

/*
 * Vnode reference, just increment the count
 */
void vref(vp)
	struct vnode *vp;
{

	vp->v_count++;
E 55
D 51
	u.u_error = EPERM;
D 18
	return(0);
E 18
I 18
	return (0);
E 51
I 51
D 52
	return (EPERM);
E 52
I 52
}

/*
 * Vnode release, just decrement the count and call VOP_INACTIVE()
 */
void vrele(vp)
	register struct vnode *vp;
{

	if (vp == NULL)
		return;
	vp->v_count--;
	if (vp->v_count < 0)
		printf("inode %d, bad ref count %d\n",
			VTOI(vp)->i_number, vp->v_count);
	if (vp->v_count == 0)
		VOP_INACTIVE(vp);
}

/*
 * vput(), just unlock and vrele()
 */
vput(vp)
	register struct vnode *vp;
{
	VOP_UNLOCK(vp);
	vrele(vp);
E 58
}

/*
 * Noop
 */
vfs_noop()
{

	return (ENXIO);
}

/*
 * Null op
 */
vfs_nullop()
{

E 75
	return (0);
E 52
E 51
E 18
D 29
}

/*
 * Allocate a user file descriptor.
 */
ufalloc()
{
	register i;

D 18
	for(i=0; i<NOFILE; i++)
		if(u.u_ofile[i] == NULL) {
E 18
I 18
	for (i=0; i<NOFILE; i++)
		if (u.u_ofile[i] == NULL) {
E 18
			u.u_r.r_val1 = i;
			u.u_pofile[i] = 0;
D 18
			return(i);
E 18
I 18
			return (i);
E 18
		}
	u.u_error = EMFILE;
D 18
	return(-1);
E 18
I 18
	return (-1);
E 18
}

I 3
D 10
struct	file *lastf = &file[0];
E 10
I 10
struct	file *lastf;
E 10
E 3
/*
 * Allocate a user file descriptor
 * and a file structure.
 * Initialize the descriptor
 * to point at the file structure.
D 11
 *
 * no file -- if there are no available
 * 	file structures.
E 11
 */
struct file *
falloc()
{
	register struct file *fp;
	register i;

	i = ufalloc();
D 10
	if(i < 0)
E 10
I 10
	if (i < 0)
E 10
D 18
		return(NULL);
E 18
I 18
		return (NULL);
E 18
D 3
	for(fp = &file[0]; fp < &file[NFILE]; fp++)
		if(fp->f_count == 0) {
			u.u_ofile[i] = fp;
			fp->f_count++;
			fp->f_un.f_offset = 0;
			return(fp);
		}
E 3
I 3
D 9
	for(fp = lastf; fp < &file[NFILE]; fp++)
E 9
I 9
D 10
	for(fp = lastf; fp < fileNFILE; fp++)
E 9
		if(fp->f_count == 0)
E 10
I 10
	if (lastf == 0)
		lastf = file;
	for (fp = lastf; fp < fileNFILE; fp++)
		if (fp->f_count == 0)
E 10
			goto slot;
D 10
	for(fp = &file[0]; fp < lastf; fp++)
		if(fp->f_count == 0)
E 10
I 10
	for (fp = file; fp < lastf; fp++)
		if (fp->f_count == 0)
E 10
			goto slot;
E 3
D 11
	printf("no file\n");
E 11
I 11
	tablefull("file");
E 11
	u.u_error = ENFILE;
D 10
	return(NULL);
E 10
I 10
	return (NULL);
E 10
I 3
slot:
	u.u_ofile[i] = fp;
	fp->f_count++;
D 18
	fp->f_un.f_offset = 0;
E 18
I 18
	fp->f_offset = 0;
E 18
I 15
	fp->f_inode = 0;
E 15
	lastf = fp + 1;
D 10
	return(fp);
E 10
I 10
	return (fp);
E 29
E 10
E 3
}
E 100
E 1
