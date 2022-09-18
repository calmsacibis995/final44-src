h47841
s 00012/00000/00648
d D 8.14 95/05/21 19:54:47 mckusick 78 77
c inactive routine must unlock node
e
s 00010/00032/00638
d D 8.13 95/05/14 00:45:43 mckusick 77 76
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
c locking functions no longer needed (use vop_nolock* instead)
e
s 00001/00000/00669
d D 8.12 95/02/22 20:50:15 mckusick 76 75
c add spec_revoke
e
s 00002/00001/00667
d D 8.11 95/02/06 04:35:33 pendry 75 74
c fix cpy date & bmap args structure
e
s 00002/00000/00666
d D 8.10 95/02/06 04:32:39 pendry 74 73
c ensure bmap run list is initialised
e
s 00004/00004/00662
d D 8.9 95/01/03 00:18:31 mckusick 73 72
c use type in dev switch to determine if disk, tape, or tty (from mycroft)
e
s 00002/00000/00664
d D 8.8 94/11/21 15:00:31 mckusick 72 71
c set VISTTY flag if opening a tty device
e
s 00001/00000/00663
d D 8.7 94/08/10 23:59:20 mckusick 71 70
c add vop_lease
e
s 00001/00001/00662
d D 8.6 94/04/09 01:33:33 pendry 70 69
c pass V_SAVE to vinvalbuf
e
s 00002/00002/00661
d D 8.5 94/01/12 15:13:43 hibler 69 68
c ufs_mountedon is now vfs_mountedon.
e
s 00009/00008/00654
d D 8.4 94/01/05 12:53:58 mckusick 68 67
c more validity checking in reading block devices
e
s 00003/00003/00659
d D 8.3 93/12/30 16:18:22 mckusick 67 66
c new queue structure
e
s 00002/00002/00660
d D 8.2 93/09/21 08:01:45 bostic 66 65
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00660
d D 8.1 93/06/10 23:47:10 bostic 65 64
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00660
d D 7.56 93/05/28 00:41:30 mckusick 64 63
c have to check for NULL proc
e
s 00013/00000/00648
d D 7.55 93/05/27 12:53:58 mckusick 63 62
c hack from Karels to cope with last close on controlling terminal
e
s 00044/00007/00604
d D 7.54 93/05/25 15:37:03 mckusick 62 61
c add spec_pathconf
e
s 00040/00005/00571
d D 7.53 93/04/28 19:19:11 mckusick 61 60
c add checking for security levels
e
s 00002/00002/00574
d D 7.52 93/02/02 21:02:39 mckusick 60 59
c vinvalbuf and getblk now take parameters to interrupt
e
s 00003/00004/00573
d D 7.51 92/10/12 21:20:18 mckusick 59 58
c bawrite does not return an error
e
s 00003/00003/00574
d D 7.50 92/10/08 00:37:10 mckusick 58 57
c use new queue routines for buffer lists hanging off vnode
e
s 00004/00004/00573
d D 7.49 92/07/12 17:22:04 pendry 57 56
c MIN -> min
e
s 00001/00001/00576
d D 7.48 92/07/12 15:19:55 mckusick 56 55
c new include location
e
s 00000/00007/00577
d D 7.47 92/07/03 01:36:46 mckusick 55 54
c delete USES; delete spec_vget
e
s 00138/00030/00446
d D 7.46 92/06/25 13:02:13 mckusick 54 53
c add comments on parameters; add fsync function; update close to
c delete vflushbuf and use new vinvalbuf
e
s 00056/00050/00420
d D 7.45 92/06/04 09:41:26 heideman 53 52
c registerized vnodeop ops after vnode interface conversion
e
s 00071/00157/00399
d D 7.44 92/05/15 13:56:34 heideman 52 51
c vnodeop argument macro expansion
e
s 00164/00096/00392
d D 7.43 92/05/14 17:33:34 heideman 51 42
c vnode interface conversion
e
s 00164/00096/00392
d R 7.43 92/05/14 15:48:12 heideman 50 42
c vnode interface conversion
e
s 00164/00096/00392
d R 7.43 92/05/14 14:52:24 heideman 49 42
c vnode interface conversion
e
s 00164/00097/00391
d R 7.43 92/05/14 12:56:48 heideman 48 42
c vnode interface conversion
e
s 00164/00097/00391
d R 7.43 92/05/14 11:54:25 heideman 47 42
c vnode interface conversion
e
s 00164/00097/00391
d R 7.43 92/05/14 10:34:31 heideman 46 42
c vnode interface conversion
e
s 00164/00097/00391
d R 7.43 92/05/13 23:13:25 heideman 45 42
c vnode interface conversion
e
s 00164/00097/00391
d R 7.43 92/05/13 18:58:57 heideman 44 42
c vnode interface conversion
e
s 00164/00097/00391
d R 7.43 92/05/13 18:31:09 heideman 43 42
c vnode interface conversion
e
s 00006/00005/00482
d D 7.42 92/02/04 00:32:07 mckusick 42 41
c breada is generalized to breadn
e
s 00006/00006/00481
d D 7.41 92/02/04 00:31:37 heideman 41 40
c new calling convention to spec_lookup
e
s 00007/00000/00480
d D 7.40 91/11/05 15:40:39 mckusick 40 39
c reorganization to move ufsmount ops to be vnode ops
e
s 00016/00016/00464
d D 7.39 91/11/01 16:40:43 bostic 39 38
c rename mountedon to ufs_mountedon
e
s 00000/00012/00480
d D 7.38 91/09/06 15:34:59 karels 38 37
c allow "negative" offsets for cdevs
e
s 00004/00001/00488
d D 7.37 91/05/30 14:56:14 mckusick 37 36
c character device open must be called with vnode unlocked (since it
c may sleep for a long time)
e
s 00007/00007/00482
d D 7.36 91/05/06 20:13:36 karels 36 35
c update comments
e
s 00002/00002/00487
d D 7.35 91/05/04 18:24:28 karels 35 34
c remove proc from cdev d_read/d_write (it's in uio now)
e
s 00042/00049/00447
d D 7.34 91/04/15 23:42:56 mckusick 34 33
c use prototypes for spec vnode ops (from specdev.h);
c add appropriate proc pointers (eliminating lots of curproc's)
e
s 00001/00001/00495
d D 7.33 91/04/02 10:06:34 karels 33 32
c ansification: need prototype for function pointer
e
s 00001/00001/00495
d D 7.32 91/03/24 15:25:52 karels 32 31
c new device calling conventions, consolidate nullops
e
s 00025/00025/00471
d D 7.31 91/03/17 15:41:16 karels 31 30
c more-or-less working with new proc & user structs
e
s 00016/00000/00480
d D 7.30 91/02/01 16:21:10 mckusick 30 29
c add POSIX-style byte-level record locking
e
s 00002/00005/00478
d D 7.29 90/12/05 17:04:00 mckusick 29 28
c update for new VM
e
s 00001/00011/00482
d D 7.28 90/06/28 21:22:15 bostic 28 27
c new copyright notice
e
s 00002/00000/00491
d D 7.27 90/05/15 14:28:49 mckusick 27 26
c lint
e
s 00001/00001/00490
d D 7.26 90/05/04 20:55:28 mckusick 26 25
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00011/00010/00480
d D 7.25 90/04/03 21:33:10 karels 25 24
c new tsleep; rm setjmp's; strings for sleep messages
e
s 00001/00000/00489
d D 7.24 90/03/27 19:00:00 mckusick 24 23
c break specinfo structure out of vnode.h into specdev.h
e
s 00003/00000/00486
d D 7.23 90/03/09 11:35:43 mckusick 23 22
c do not allow mounted devices to be opened
e
s 00002/00002/00484
d D 7.22 90/02/21 00:09:12 mckusick 22 21
c spec_select gets the file flags
e
s 00001/00000/00485
d D 7.21 90/01/15 18:40:26 mckusick 21 20
c add islocked vnode op
e
s 00041/00004/00444
d D 7.20 89/11/30 22:40:43 mckusick 20 19
c add null bmap routine; add printing routine; now flush dev vnode directly
e
s 00006/00006/00442
d D 7.19 89/11/25 23:21:40 mckusick 19 18
c check count on all aliases in deciding to do last close
e
s 00000/00011/00448
d D 7.18 89/11/25 21:53:37 mckusick 18 17
c get rid of ufs specific code (again!)
e
s 00002/00002/00457
d D 7.17 89/11/25 21:35:41 mckusick 17 16
c maintain mount information in v_mounton rather than overloading v_mount
e
s 00080/00006/00379
d D 7.16 89/11/25 15:17:54 mckusick 16 15
c move read/writeblkvp from old ufs_io.c to spec_read/write
e
s 00071/00022/00314
d D 7.15 89/11/22 21:40:57 mckusick 15 14
c locking is now done above the vnode layer;
c read/write no longer take an offp;
c move character device functionality out of readblkvp/writeblkvp
e
s 00042/00032/00294
d D 7.14 89/11/10 12:33:57 mckusick 14 13
c cleanups; add ops returning EBADF for access, getattr, and setattr
e
s 00002/00000/00324
d D 7.13 89/11/03 15:01:06 mckusick 13 12
c lint
e
s 00011/00005/00313
d D 7.12 89/11/02 17:45:48 mckusick 12 11
c make provision for forcible close
e
s 00058/00058/00260
d D 7.11 89/10/29 23:57:40 mckusick 11 10
c blk_* => spec_*
e
s 00014/00040/00304
d D 7.10 89/10/29 23:08:32 mckusick 10 9
c get rid of all dependencies on ufs
e
s 00003/00001/00341
d D 7.9 89/10/24 18:38:23 mckusick 9 8
c add ufs_reclaim to blk_vnodeops
e
s 00006/00004/00336
d D 7.8 89/10/22 13:17:35 mckusick 8 7
c clean up include files; add NODEV enforcement
e
s 00000/00005/00340
d D 7.7 89/10/19 23:18:32 mckusick 7 6
c now handle error directly in dup2
e
s 00018/00004/00327
d D 7.6 89/10/13 17:17:40 mckusick 6 5
c need to add trivial blk_lookup routine
e
s 00002/00002/00329
d D 7.5 89/08/26 14:14:24 mckusick 5 4
c generalize the buffer pool so that NFS can become a client
e
s 00002/00001/00329
d D 7.4 89/08/15 15:26:57 mckusick 4 3
c do not try to close device if binval failed to flush all blocks
e
s 00081/00044/00249
d D 7.3 89/05/09 16:44:54 mckusick 3 2
c generalize for vnodes for NFS; move closei into blk_close
e
s 00001/00002/00292
d D 7.2 89/04/24 21:08:54 mckusick 2 1
c get rid of spurious printf
e
s 00294/00000/00000
d D 7.1 89/04/24 20:38:54 mckusick 1 0
c first bootable vnodes
e
u
U
t
T
I 1
/*
D 65
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 65
I 65
D 75
 * Copyright (c) 1989, 1993
E 75
I 75
 * Copyright (c) 1989, 1993, 1995
E 75
 *	The Regents of the University of California.  All rights reserved.
E 65
 *
D 28
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
E 28
I 28
 * %sccs.include.redist.c%
E 28
 *
 *	%W% (Berkeley) %G%
 */

D 39
#include "param.h"
I 32
#include "proc.h"
E 32
#include "systm.h"
D 3
#include "time.h"
E 3
I 3
D 32
#include "user.h"
E 32
#include "kernel.h"
E 3
#include "conf.h"
#include "buf.h"
I 8
#include "mount.h"
I 34
#include "namei.h"
E 34
E 8
#include "vnode.h"
I 24
#include "specdev.h"
E 24
I 15
D 18
#include "../ufs/inode.h"
E 18
E 15
D 10
#include "../ufs/inode.h"
E 10
I 10
#include "stat.h"
E 10
D 8
#include "stat.h"
E 8
D 3
#include "uio.h"
E 3
#include "errno.h"
I 16
#include "ioctl.h"
#include "file.h"
#include "disklabel.h"
E 39
I 39
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/vnode.h>
D 56
#include <sys/specdev.h>
E 56
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/disklabel.h>
I 56
#include <miscfs/specfs/specdev.h>
E 56
E 39
E 16
D 8
#include "malloc.h"
E 8

I 25
/* symbolic sleep message strings for devices */
char	devopn[] = "devopn";
char	devio[] = "devio";
char	devwait[] = "devwait";
char	devin[] = "devin";
char	devout[] = "devout";
char	devioc[] = "devioc";
char	devcls[] = "devcls";

E 25
D 6
int	blk_open(),
E 6
I 6
D 11
int	blk_lookup(),
	blk_open(),
E 6
D 3
	blk_access(),
E 3
	blk_read(),
	blk_write(),
	blk_strategy(),
	blk_ioctl(),
	blk_select(),
D 3
	blk_inactive(),
E 3
	blk_lock(),
	blk_unlock(),
	blk_close(),
	blk_badop(),
	blk_nullop();
E 11
I 11
D 34
int	spec_lookup(),
	spec_open(),
	spec_read(),
	spec_write(),
	spec_strategy(),
I 20
	spec_bmap(),
E 20
	spec_ioctl(),
	spec_select(),
	spec_lock(),
	spec_unlock(),
	spec_close(),
I 20
	spec_print(),
I 30
	spec_advlock(),
E 30
E 20
I 14
	spec_ebadf(),
E 14
D 31
	spec_badop(),
	spec_nullop();
E 31
I 31
	spec_badop();
E 31
E 11

I 31
int	nullop();

E 34
E 31
D 10
int	ufs_getattr(),
D 3
	ufs_setattr();
E 3
I 3
	ufs_setattr(),
	ufs_access(),
D 9
	ufs_inactive();
E 9
I 9
	ufs_inactive(),
	ufs_reclaim();
E 9
E 3

E 10
D 11
struct vnodeops blk_vnodeops = {
I 6
	blk_lookup,
E 6
	blk_badop,
	blk_badop,
D 6
	blk_badop,
E 6
	blk_open,
	blk_close,
D 3
	blk_access,
E 3
I 3
D 10
	ufs_access,
E 3
	ufs_getattr,
	ufs_setattr,
E 10
I 10
	blk_badop,
	blk_badop,
	blk_badop,
E 10
	blk_read,
	blk_write,
	blk_ioctl,
	blk_select,
	blk_badop,
	blk_nullop,
	blk_badop,
	blk_badop,
	blk_badop,
	blk_badop,
	blk_badop,
	blk_badop,
	blk_badop,
	blk_badop,
	blk_badop,
	blk_badop,
D 3
	blk_inactive,
E 3
I 3
D 10
	ufs_inactive,
I 9
	ufs_reclaim,
E 10
I 10
	blk_nullop,
	blk_nullop,
E 10
E 9
E 3
	blk_lock,
	blk_unlock,
	blk_badop,
	blk_strategy,
E 11
I 11
D 51
struct vnodeops spec_vnodeops = {
D 14
	spec_lookup,
	spec_badop,
	spec_badop,
	spec_open,
	spec_close,
	spec_badop,
	spec_badop,
	spec_badop,
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
	spec_nullop,
	spec_nullop,
	spec_lock,
	spec_unlock,
	spec_badop,
	spec_strategy,
E 14
I 14
	spec_lookup,		/* lookup */
D 34
	spec_badop,		/* create */
	spec_badop,		/* mknod */
E 34
I 34
	spec_create,		/* create */
	spec_mknod,		/* mknod */
E 34
	spec_open,		/* open */
	spec_close,		/* close */
D 34
	spec_ebadf,		/* access */
	spec_ebadf,		/* getattr */
	spec_ebadf,		/* setattr */
E 34
I 34
	spec_access,		/* access */
	spec_getattr,		/* getattr */
	spec_setattr,		/* setattr */
E 34
	spec_read,		/* read */
	spec_write,		/* write */
	spec_ioctl,		/* ioctl */
	spec_select,		/* select */
D 34
	spec_badop,		/* mmap */
D 31
	spec_nullop,		/* fsync */
E 31
I 31
	nullop,			/* fsync */
E 31
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
D 31
	spec_nullop,		/* inactive */
	spec_nullop,		/* reclaim */
E 31
I 31
	nullop,			/* inactive */
	nullop,			/* reclaim */
E 34
I 34
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
	spec_inactive,		/* inactive */
	spec_reclaim,		/* reclaim */
E 34
E 31
	spec_lock,		/* lock */
	spec_unlock,		/* unlock */
D 20
	spec_badop,		/* bmap */
E 20
I 20
	spec_bmap,		/* bmap */
E 20
	spec_strategy,		/* strategy */
I 20
	spec_print,		/* print */
I 21
D 31
	spec_nullop,		/* islocked */
E 31
I 31
D 34
	nullop,			/* islocked */
E 34
I 34
	spec_islocked,		/* islocked */
E 34
E 31
I 30
	spec_advlock,		/* advlock */
I 40
	spec_blkatoff,		/* blkatoff */
	spec_vget,		/* vget */
	spec_valloc,		/* valloc */
	spec_vfree,		/* vfree */
	spec_truncate,		/* truncate */
	spec_update,		/* update */
	spec_bwrite,		/* bwrite */
E 51
I 51
int (**spec_vnodeop_p)();
struct vnodeopv_entry_desc spec_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, spec_lookup },		/* lookup */
	{ &vop_create_desc, spec_create },		/* create */
	{ &vop_mknod_desc, spec_mknod },		/* mknod */
D 62
	{ &vop_open_desc, spec_open },		/* open */
E 62
I 62
	{ &vop_open_desc, spec_open },			/* open */
E 62
	{ &vop_close_desc, spec_close },		/* close */
	{ &vop_access_desc, spec_access },		/* access */
	{ &vop_getattr_desc, spec_getattr },		/* getattr */
	{ &vop_setattr_desc, spec_setattr },		/* setattr */
D 62
	{ &vop_read_desc, spec_read },		/* read */
E 62
I 62
	{ &vop_read_desc, spec_read },			/* read */
E 62
	{ &vop_write_desc, spec_write },		/* write */
I 71
	{ &vop_lease_desc, spec_lease_check },		/* lease */
E 71
	{ &vop_ioctl_desc, spec_ioctl },		/* ioctl */
	{ &vop_select_desc, spec_select },		/* select */
I 76
	{ &vop_revoke_desc, spec_revoke },		/* revoke */
E 76
D 62
	{ &vop_mmap_desc, spec_mmap },		/* mmap */
E 62
I 62
	{ &vop_mmap_desc, spec_mmap },			/* mmap */
E 62
	{ &vop_fsync_desc, spec_fsync },		/* fsync */
D 62
	{ &vop_seek_desc, spec_seek },		/* seek */
E 62
I 62
	{ &vop_seek_desc, spec_seek },			/* seek */
E 62
	{ &vop_remove_desc, spec_remove },		/* remove */
D 62
	{ &vop_link_desc, spec_link },		/* link */
E 62
I 62
	{ &vop_link_desc, spec_link },			/* link */
E 62
	{ &vop_rename_desc, spec_rename },		/* rename */
	{ &vop_mkdir_desc, spec_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, spec_rmdir },		/* rmdir */
	{ &vop_symlink_desc, spec_symlink },		/* symlink */
	{ &vop_readdir_desc, spec_readdir },		/* readdir */
	{ &vop_readlink_desc, spec_readlink },		/* readlink */
	{ &vop_abortop_desc, spec_abortop },		/* abortop */
	{ &vop_inactive_desc, spec_inactive },		/* inactive */
	{ &vop_reclaim_desc, spec_reclaim },		/* reclaim */
D 62
	{ &vop_lock_desc, spec_lock },		/* lock */
E 62
I 62
	{ &vop_lock_desc, spec_lock },			/* lock */
E 62
	{ &vop_unlock_desc, spec_unlock },		/* unlock */
D 62
	{ &vop_bmap_desc, spec_bmap },		/* bmap */
E 62
I 62
	{ &vop_bmap_desc, spec_bmap },			/* bmap */
E 62
	{ &vop_strategy_desc, spec_strategy },		/* strategy */
	{ &vop_print_desc, spec_print },		/* print */
	{ &vop_islocked_desc, spec_islocked },		/* islocked */
I 62
	{ &vop_pathconf_desc, spec_pathconf },		/* pathconf */
E 62
	{ &vop_advlock_desc, spec_advlock },		/* advlock */
	{ &vop_blkatoff_desc, spec_blkatoff },		/* blkatoff */
D 55
	{ &vop_vget_desc, spec_vget },		/* vget */
E 55
	{ &vop_valloc_desc, spec_valloc },		/* valloc */
	{ &vop_vfree_desc, spec_vfree },		/* vfree */
	{ &vop_truncate_desc, spec_truncate },		/* truncate */
	{ &vop_update_desc, spec_update },		/* update */
	{ &vop_bwrite_desc, spec_bwrite },		/* bwrite */
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
E 51
E 40
E 30
E 21
E 20
E 14
E 11
};
I 51
struct vnodeopv_desc spec_vnodeop_opv_desc =
	{ &spec_vnodeop_p, spec_vnodeop_entries };
E 51

/*
I 6
 * Trivial lookup routine that always fails.
 */
D 11
blk_lookup(vp, ndp)
E 11
I 11
D 34
spec_lookup(vp, ndp)
E 34
I 34
D 41
spec_lookup(vp, ndp, p)
E 34
E 11
	struct vnode *vp;
	struct nameidata *ndp;
I 34
	struct proc *p;
E 41
I 41
int
D 51
spec_lookup(dvp, vpp, cnp)
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
E 51
I 51
D 54
spec_lookup (ap)
	struct vop_lookup_args *ap;
E 54
I 54
spec_lookup(ap)
	struct vop_lookup_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
	} */ *ap;
E 54
D 52
#define dvp (ap->a_dvp)
#define vpp (ap->a_vpp)
#define cnp (ap->a_cnp)
E 52
E 51
E 41
E 34
{

D 41
	ndp->ni_dvp = vp;
	ndp->ni_vp = NULL;
E 41
I 41
D 52
	*vpp = NULL;
E 52
I 52
	*ap->a_vpp = NULL;
E 52
E 41
	return (ENOTDIR);
}
I 51
D 52
#undef dvp
#undef vpp
#undef cnp
E 52
E 51

/*
E 6
D 36
 * Open called to allow handler
 * of special files to initialize and
 * validate before actual IO.
E 36
I 36
D 61
 * Open a special file: Don't allow open if fs is mounted -nodev,
 * and don't allow opens of block devices that are currently mounted.
 * Otherwise, call device driver open function.
E 61
I 61
 * Open a special file.
E 61
E 36
 */
I 3
/* ARGSUSED */
E 3
D 11
blk_open(vp, mode, cred)
E 11
I 11
D 34
spec_open(vp, mode, cred)
E 34
I 34
D 51
spec_open(vp, mode, cred, p)
E 34
E 11
	register struct vnode *vp;
	int mode;
	struct ucred *cred;
I 34
	struct proc *p;
E 51
I 51
D 54
spec_open (ap)
	struct vop_open_args *ap;
E 54
I 54
spec_open(ap)
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 54
D 52
#define vp (ap->a_vp)
#define mode (ap->a_mode)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 52
E 51
E 34
{
I 77
	struct proc *p = ap->a_p;
E 77
I 51
D 55
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
E 55
E 51
I 31
D 34
	struct proc *p = curproc;		/* XXX */
E 34
E 31
D 52
	dev_t dev = (dev_t)vp->v_rdev;
E 52
I 52
D 53
	dev_t dev = (dev_t)ap->a_vp->v_rdev;
E 53
I 53
D 61
	register struct vnode *vp = ap->a_vp;
	dev_t dev = (dev_t)vp->v_rdev;
E 61
I 61
	struct vnode *bvp, *vp = ap->a_vp;
	dev_t bdev, dev = (dev_t)vp->v_rdev;
E 61
E 53
E 52
D 77
	register int maj = major(dev);
E 77
I 77
	int maj = major(dev);
E 77
I 23
	int error;
E 23

I 61
	/*
	 * Don't allow open if fs is mounted -nodev.
	 */
E 61
I 8
D 26
	if (vp->v_mount && (vp->v_mount->m_flag & M_NODEV))
E 26
I 26
D 52
	if (vp->v_mount && (vp->v_mount->mnt_flag & MNT_NODEV))
E 52
I 52
D 53
	if (ap->a_vp->v_mount && (ap->a_vp->v_mount->mnt_flag & MNT_NODEV))
E 53
I 53
	if (vp->v_mount && (vp->v_mount->mnt_flag & MNT_NODEV))
E 53
E 52
E 26
		return (ENXIO);

E 8
D 52
	switch (vp->v_type) {
E 52
I 52
D 53
	switch (ap->a_vp->v_type) {
E 53
I 53
	switch (vp->v_type) {
E 53
E 52

	case VCHR:
		if ((u_int)maj >= nchrdev)
			return (ENXIO);
I 61
		if (ap->a_cred != FSCRED && (ap->a_mode & FWRITE)) {
			/*
			 * When running in very secure mode, do not allow
			 * opens for writing of any disk character devices.
			 */
D 73
			if (securelevel >= 2 && isdisk(dev, VCHR))
E 73
I 73
			if (securelevel >= 2 && cdevsw[maj].d_type == D_DISK)
E 73
				return (EPERM);
			/*
			 * When running in secure mode, do not allow opens
			 * for writing of /dev/mem, /dev/kmem, or character
			 * devices whose corresponding block devices are
			 * currently mounted.
			 */
			if (securelevel >= 1) {
				if ((bdev = chrtoblk(dev)) != NODEV &&
				    vfinddev(bdev, VBLK, &bvp) &&
				    bvp->v_usecount > 0 &&
D 69
				    (error = ufs_mountedon(bvp)))
E 69
I 69
				    (error = vfs_mountedon(bvp)))
E 69
					return (error);
				if (iskmemdev(dev))
					return (EPERM);
			}
		}
I 72
D 73
		if (istty(dev))
E 73
I 73
		if (cdevsw[maj].d_type == D_TTY)
E 73
			vp->v_flag |= VISTTY;
E 72
E 61
D 8
		return ((*cdevsw[maj].d_open)(dev, mode, S_IFCHR));
E 8
I 8
D 10
		return ((*cdevsw[maj].d_open)(dev, mode, IFCHR));
E 10
I 10
D 31
		return ((*cdevsw[maj].d_open)(dev, mode, S_IFCHR));
E 31
I 31
D 37
		return ((*cdevsw[maj].d_open)(dev, mode, S_IFCHR, p));
E 37
I 37
D 52
		VOP_UNLOCK(vp);
		error = (*cdevsw[maj].d_open)(dev, mode, S_IFCHR, p);
		VOP_LOCK(vp);
E 52
I 52
D 53
		VOP_UNLOCK(ap->a_vp);
E 53
I 53
D 77
		VOP_UNLOCK(vp);
E 53
		error = (*cdevsw[maj].d_open)(dev, ap->a_mode, S_IFCHR, ap->a_p);
D 53
		VOP_LOCK(ap->a_vp);
E 53
I 53
		VOP_LOCK(vp);
E 77
I 77
		VOP_UNLOCK(vp, 0, p);
		error = (*cdevsw[maj].d_open)(dev, ap->a_mode, S_IFCHR, p);
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 77
E 53
E 52
		return (error);
E 37
E 31
E 10
E 8

	case VBLK:
		if ((u_int)maj >= nblkdev)
			return (ENXIO);
I 61
		/*
		 * When running in very secure mode, do not allow
		 * opens for writing of any disk block devices.
		 */
		if (securelevel >= 2 && ap->a_cred != FSCRED &&
D 73
		    (ap->a_mode & FWRITE) && isdisk(dev, VBLK))
E 73
I 73
		    (ap->a_mode & FWRITE) && bdevsw[maj].d_type == D_DISK)
E 73
			return (EPERM);
		/*
		 * Do not allow opens of block devices that are
		 * currently mounted.
		 */
E 61
I 23
D 39
		if (error = mountedon(vp))
E 39
I 39
D 52
		if (error = ufs_mountedon(vp))
E 52
I 52
D 53
		if (error = ufs_mountedon(ap->a_vp))
E 53
I 53
D 69
		if (error = ufs_mountedon(vp))
E 69
I 69
		if (error = vfs_mountedon(vp))
E 69
E 53
E 52
E 39
			return (error);
E 23
D 8
		return ((*bdevsw[maj].d_open)(dev, mode, S_IFBLK));
E 8
I 8
D 10
		return ((*bdevsw[maj].d_open)(dev, mode, IFBLK));
E 10
I 10
D 31
		return ((*bdevsw[maj].d_open)(dev, mode, S_IFBLK));
E 31
I 31
D 52
		return ((*bdevsw[maj].d_open)(dev, mode, S_IFBLK, p));
E 52
I 52
D 77
		return ((*bdevsw[maj].d_open)(dev, ap->a_mode, S_IFBLK, ap->a_p));
E 77
I 77
		return ((*bdevsw[maj].d_open)(dev, ap->a_mode, S_IFBLK, p));
E 77
E 52
E 31
E 10
E 8
	}
	return (0);
}
I 51
D 52
#undef vp
#undef mode
#undef cred
#undef p
E 52
E 51

/*
D 10
 * Check access permissions for a block device.
 */
blk_access(vp, mode, cred)
	struct vnode *vp;
	int mode;
	struct ucred *cred;
{
D 3
	register struct inode *ip = VTOI(vp);
	int error;
E 3

D 3
	if ((ip->i_flag & ILOCKED) == 0)
		printf("access called with %d not locked\n", ip->i_number);
	error = iaccess(ip, mode, cred);
	return (error);
E 3
I 3
	return (iaccess(VTOI(vp), mode, cred));
E 3
}

/*
E 10
 * Vnode op for read
 */
I 27
/* ARGSUSED */
E 27
D 11
blk_read(vp, uio, offp, ioflag, cred)
E 11
I 11
D 15
spec_read(vp, uio, offp, ioflag, cred)
E 15
I 15
D 51
spec_read(vp, uio, ioflag, cred)
E 15
E 11
	register struct vnode *vp;
D 16
	struct uio *uio;
E 16
I 16
	register struct uio *uio;
E 16
D 15
	off_t *offp;
E 15
	int ioflag;
	struct ucred *cred;
E 51
I 51
D 54
spec_read (ap)
	struct vop_read_args *ap;
E 54
I 54
spec_read(ap)
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 54
D 52
#define vp (ap->a_vp)
#define uio (ap->a_uio)
#define ioflag (ap->a_ioflag)
#define cred (ap->a_cred)
E 52
E 51
{
I 51
D 55
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
E 55
E 51
I 31
D 34
	struct proc *p = curproc;		/* XXX */
E 34
I 34
D 52
	struct proc *p = uio->uio_procp;
E 52
I 52
D 53
	struct proc *p = ap->a_uio->uio_procp;
E 53
I 53
	register struct vnode *vp = ap->a_vp;
	register struct uio *uio = ap->a_uio;
 	struct proc *p = uio->uio_procp;
E 53
E 52
E 34
E 31
D 3
	register struct inode *ip = VTOI(vp);
E 3
D 15
	int count, error;
E 15
I 15
D 16
	int error;
E 16
I 16
	struct buf *bp;
D 42
	daddr_t bn;
E 42
I 42
	daddr_t bn, nextbn;
E 42
	long bsize, bscale;
	struct partinfo dpart;
D 68
	register int n, on;
E 68
I 68
	int n, on, majordev, (*ioctl)();
E 68
	int error = 0;
I 68
	dev_t dev;
E 68
E 16
D 38
	extern int mem_no;
E 38
E 15

I 34
#ifdef DIAGNOSTIC
E 34
D 3
	if (vp->v_type == VBLK && ip)
		ILOCK(ip);
E 3
I 3
D 15
	if (vp->v_type == VBLK && vp->v_data)
		VOP_LOCK(vp);
E 3
	uio->uio_offset = *offp;
	count = uio->uio_resid;
D 3
	error = readblkvp(vp, uio, cred);
E 3
I 3
	error = readblkvp(vp, uio, cred, ioflag);
E 3
	*offp += count - uio->uio_resid;
D 3
	if (vp->v_type == VBLK && ip)
		IUNLOCK(ip);
E 3
I 3
	if (vp->v_type == VBLK && vp->v_data)
E 15
I 15
D 52
	if (uio->uio_rw != UIO_READ)
E 52
I 52
D 53
	if (ap->a_uio->uio_rw != UIO_READ)
E 53
I 53
	if (uio->uio_rw != UIO_READ)
E 53
E 52
		panic("spec_read mode");
I 34
D 52
	if (uio->uio_segflg == UIO_USERSPACE && uio->uio_procp != curproc)
E 52
I 52
D 53
	if (ap->a_uio->uio_segflg == UIO_USERSPACE && ap->a_uio->uio_procp != curproc)
E 53
I 53
	if (uio->uio_segflg == UIO_USERSPACE && uio->uio_procp != curproc)
E 53
E 52
		panic("spec_read proc");
#endif
E 34
D 52
	if (uio->uio_resid == 0)
E 52
I 52
D 53
	if (ap->a_uio->uio_resid == 0)
E 53
I 53
	if (uio->uio_resid == 0)
E 53
E 52
		return (0);
D 18
	/*
	 * XXX  Set access flag for the ufs filesystem.
	 */
	if (vp->v_tag == VT_UFS)
		VTOI(vp)->i_flag |= IACC;
E 18

D 52
	switch (vp->v_type) {
E 52
I 52
D 53
	switch (ap->a_vp->v_type) {
E 53
I 53
	switch (vp->v_type) {
E 53
E 52

	case VCHR:
D 38
		/*
		 * Negative offsets allowed only for /dev/kmem
		 */
		if (uio->uio_offset < 0 && major(vp->v_rdev) != mem_no)
			return (EINVAL);
E 38
E 15
D 52
		VOP_UNLOCK(vp);
E 3
D 15
	return (error);
E 15
I 15
		error = (*cdevsw[major(vp->v_rdev)].d_read)
D 31
			(vp->v_rdev, uio, ioflag);
E 31
I 31
D 35
			(vp->v_rdev, uio, ioflag, p);
E 35
I 35
			(vp->v_rdev, uio, ioflag);
E 35
E 31
		VOP_LOCK(vp);
E 52
I 52
D 53
		VOP_UNLOCK(ap->a_vp);
		error = (*cdevsw[major(ap->a_vp->v_rdev)].d_read)
			(ap->a_vp->v_rdev, ap->a_uio, ap->a_ioflag);
		VOP_LOCK(ap->a_vp);
E 53
I 53
D 77
		VOP_UNLOCK(vp);
E 77
I 77
		VOP_UNLOCK(vp, 0, p);
E 77
		error = (*cdevsw[major(vp->v_rdev)].d_read)
			(vp->v_rdev, uio, ap->a_ioflag);
D 77
		VOP_LOCK(vp);
E 77
I 77
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 77
E 53
E 52
		return (error);

	case VBLK:
D 52
		if (uio->uio_offset < 0)
E 52
I 52
D 53
		if (ap->a_uio->uio_offset < 0)
E 53
I 53
		if (uio->uio_offset < 0)
E 53
E 52
			return (EINVAL);
D 16
		return (readblkvp(vp, uio, cred, ioflag));
E 16
I 16
		bsize = BLKDEV_IOSIZE;
D 52
		if ((*bdevsw[major(vp->v_rdev)].d_ioctl)(vp->v_rdev, DIOCGPART,
E 52
I 52
D 53
		if ((*bdevsw[major(ap->a_vp->v_rdev)].d_ioctl)(ap->a_vp->v_rdev, DIOCGPART,
E 53
I 53
D 68
		if ((*bdevsw[major(vp->v_rdev)].d_ioctl)(vp->v_rdev, DIOCGPART,
E 53
E 52
D 31
		    (caddr_t)&dpart, FREAD) == 0) {
E 31
I 31
		    (caddr_t)&dpart, FREAD, p) == 0) {
E 31
			if (dpart.part->p_fstype == FS_BSDFFS &&
			    dpart.part->p_frag != 0 && dpart.part->p_fsize != 0)
				bsize = dpart.part->p_frag *
				    dpart.part->p_fsize;
		}
E 68
I 68
		dev = vp->v_rdev;
		if ((majordev = major(dev)) < nblkdev &&
		    (ioctl = bdevsw[majordev].d_ioctl) != NULL &&
		    (*ioctl)(dev, DIOCGPART, (caddr_t)&dpart, FREAD, p) == 0 &&
		    dpart.part->p_fstype == FS_BSDFFS &&
		    dpart.part->p_frag != 0 && dpart.part->p_fsize != 0)
			bsize = dpart.part->p_frag * dpart.part->p_fsize;
E 68
		bscale = bsize / DEV_BSIZE;
		do {
D 52
			bn = (uio->uio_offset / DEV_BSIZE) &~ (bscale - 1);
			on = uio->uio_offset % bsize;
			n = MIN((unsigned)(bsize - on), uio->uio_resid);
D 42
			if (vp->v_lastr + bscale == bn)
				error = breada(vp, bn, (int)bsize, bn + bscale,
					(int)bsize, NOCRED, &bp);
			else
E 42
I 42
			if (vp->v_lastr + bscale == bn) {
E 52
I 52
D 53
			bn = (ap->a_uio->uio_offset / DEV_BSIZE) &~ (bscale - 1);
			on = ap->a_uio->uio_offset % bsize;
			n = MIN((unsigned)(bsize - on), ap->a_uio->uio_resid);
			if (ap->a_vp->v_lastr + bscale == bn) {
E 53
I 53
			bn = (uio->uio_offset / DEV_BSIZE) &~ (bscale - 1);
			on = uio->uio_offset % bsize;
D 57
			n = MIN((unsigned)(bsize - on), uio->uio_resid);
E 57
I 57
			n = min((unsigned)(bsize - on), uio->uio_resid);
E 57
			if (vp->v_lastr + bscale == bn) {
E 53
E 52
				nextbn = bn + bscale;
D 52
				error = breadn(vp, bn, (int)bsize, &nextbn,
E 52
I 52
D 53
				error = breadn(ap->a_vp, bn, (int)bsize, &nextbn,
E 53
I 53
				error = breadn(vp, bn, (int)bsize, &nextbn,
E 53
E 52
					(int *)&bsize, 1, NOCRED, &bp);
			} else
E 42
D 52
				error = bread(vp, bn, (int)bsize, NOCRED, &bp);
			vp->v_lastr = bn;
E 52
I 52
D 53
				error = bread(ap->a_vp, bn, (int)bsize, NOCRED, &bp);
			ap->a_vp->v_lastr = bn;
E 53
I 53
				error = bread(vp, bn, (int)bsize, NOCRED, &bp);
			vp->v_lastr = bn;
E 53
E 52
D 57
			n = MIN(n, bsize - bp->b_resid);
E 57
I 57
			n = min(n, bsize - bp->b_resid);
E 57
			if (error) {
				brelse(bp);
				return (error);
			}
D 52
			error = uiomove(bp->b_un.b_addr + on, n, uio);
E 52
I 52
D 53
			error = uiomove(bp->b_un.b_addr + on, n, ap->a_uio);
E 53
I 53
D 66
			error = uiomove(bp->b_un.b_addr + on, n, uio);
E 66
I 66
			error = uiomove((char *)bp->b_data + on, n, uio);
E 66
E 53
E 52
			if (n + on == bsize)
				bp->b_flags |= B_AGE;
			brelse(bp);
D 52
		} while (error == 0 && uio->uio_resid > 0 && n != 0);
E 52
I 52
D 53
		} while (error == 0 && ap->a_uio->uio_resid > 0 && n != 0);
E 53
I 53
		} while (error == 0 && uio->uio_resid > 0 && n != 0);
E 53
E 52
		return (error);
E 16

	default:
		panic("spec_read type");
	}
	/* NOTREACHED */
E 15
}
I 51
D 52
#undef vp
#undef uio
#undef ioflag
#undef cred
E 52
E 51

/*
 * Vnode op for write
 */
I 27
/* ARGSUSED */
E 27
D 11
blk_write(vp, uio, offp, ioflag, cred)
E 11
I 11
D 15
spec_write(vp, uio, offp, ioflag, cred)
E 15
I 15
D 51
spec_write(vp, uio, ioflag, cred)
E 15
E 11
	register struct vnode *vp;
D 16
	struct uio *uio;
E 16
I 16
	register struct uio *uio;
E 16
D 15
	off_t *offp;
E 15
	int ioflag;
	struct ucred *cred;
E 51
I 51
D 54
spec_write (ap)
	struct vop_write_args *ap;
E 54
I 54
spec_write(ap)
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 54
D 52
#define vp (ap->a_vp)
#define uio (ap->a_uio)
#define ioflag (ap->a_ioflag)
#define cred (ap->a_cred)
E 52
E 51
{
I 51
D 55
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
E 55
E 51
I 31
D 34
	struct proc *p = curproc;		/* XXX */
E 34
I 34
D 52
	struct proc *p = uio->uio_procp;
E 52
I 52
D 53
	struct proc *p = ap->a_uio->uio_procp;
E 53
I 53
	register struct vnode *vp = ap->a_vp;
	register struct uio *uio = ap->a_uio;
	struct proc *p = uio->uio_procp;
E 53
E 52
E 34
E 31
D 3
	register struct inode *ip = VTOI(vp);
E 3
D 15
	int count, error;
E 15
I 15
D 16
	int error;
E 16
I 16
	struct buf *bp;
	daddr_t bn;
	int bsize, blkmask;
	struct partinfo dpart;
D 29
	register int n, on, i;
	int count, error = 0;
E 29
I 29
	register int n, on;
	int error = 0;
E 29
E 16
D 38
	extern int mem_no;
E 38
E 15

I 34
#ifdef DIAGNOSTIC
E 34
D 3
	if (vp->v_type == VBLK && ip)
		ILOCK(ip);
E 3
I 3
D 15
	if (vp->v_type == VBLK && vp->v_data)
		VOP_LOCK(vp);
E 3
	uio->uio_offset = *offp;
	count = uio->uio_resid;
D 3
	error = writeblkvp(vp, uio, cred);
E 3
I 3
	error = writeblkvp(vp, uio, cred, ioflag);
E 3
	*offp += count - uio->uio_resid;
D 3
	if (vp->v_type == VBLK && ip)
		IUNLOCK(ip);
E 3
I 3
	if (vp->v_type == VBLK && vp->v_data)
E 15
I 15
D 52
	if (uio->uio_rw != UIO_WRITE)
E 52
I 52
D 53
	if (ap->a_uio->uio_rw != UIO_WRITE)
E 53
I 53
	if (uio->uio_rw != UIO_WRITE)
E 53
E 52
		panic("spec_write mode");
I 34
D 52
	if (uio->uio_segflg == UIO_USERSPACE && uio->uio_procp != curproc)
E 52
I 52
D 53
	if (ap->a_uio->uio_segflg == UIO_USERSPACE && ap->a_uio->uio_procp != curproc)
E 53
I 53
	if (uio->uio_segflg == UIO_USERSPACE && uio->uio_procp != curproc)
E 53
E 52
		panic("spec_write proc");
#endif
E 34
D 18
	/*
	 * XXX  Set update and change flags for the ufs filesystem.
	 */
	if (vp->v_tag == VT_UFS)
		VTOI(vp)->i_flag |= IUPD|ICHG;
E 18

D 52
	switch (vp->v_type) {
E 52
I 52
D 53
	switch (ap->a_vp->v_type) {
E 53
I 53
	switch (vp->v_type) {
E 53
E 52

	case VCHR:
D 38
		/*
		 * Negative offsets allowed only for /dev/kmem
		 */
		if (uio->uio_offset < 0 && major(vp->v_rdev) != mem_no)
			return (EINVAL);
E 38
E 15
D 52
		VOP_UNLOCK(vp);
E 3
D 15
	return (error);
E 15
I 15
		error = (*cdevsw[major(vp->v_rdev)].d_write)
D 31
			(vp->v_rdev, uio, ioflag);
E 31
I 31
D 35
			(vp->v_rdev, uio, ioflag, p);
E 35
I 35
			(vp->v_rdev, uio, ioflag);
E 35
E 31
		VOP_LOCK(vp);
E 52
I 52
D 53
		VOP_UNLOCK(ap->a_vp);
		error = (*cdevsw[major(ap->a_vp->v_rdev)].d_write)
			(ap->a_vp->v_rdev, ap->a_uio, ap->a_ioflag);
		VOP_LOCK(ap->a_vp);
E 53
I 53
D 77
		VOP_UNLOCK(vp);
E 77
I 77
		VOP_UNLOCK(vp, 0, p);
E 77
		error = (*cdevsw[major(vp->v_rdev)].d_write)
			(vp->v_rdev, uio, ap->a_ioflag);
D 77
		VOP_LOCK(vp);
E 77
I 77
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
E 77
E 53
E 52
		return (error);

	case VBLK:
D 52
		if (uio->uio_resid == 0)
E 52
I 52
D 53
		if (ap->a_uio->uio_resid == 0)
E 53
I 53
		if (uio->uio_resid == 0)
E 53
E 52
			return (0);
D 52
		if (uio->uio_offset < 0)
E 52
I 52
D 53
		if (ap->a_uio->uio_offset < 0)
E 53
I 53
		if (uio->uio_offset < 0)
E 53
E 52
			return (EINVAL);
D 16
		return (writeblkvp(vp, uio, cred, ioflag));
E 16
I 16
		bsize = BLKDEV_IOSIZE;
D 52
		if ((*bdevsw[major(vp->v_rdev)].d_ioctl)(vp->v_rdev, DIOCGPART,
E 52
I 52
D 53
		if ((*bdevsw[major(ap->a_vp->v_rdev)].d_ioctl)(ap->a_vp->v_rdev, DIOCGPART,
E 53
I 53
		if ((*bdevsw[major(vp->v_rdev)].d_ioctl)(vp->v_rdev, DIOCGPART,
E 53
E 52
D 31
		    (caddr_t)&dpart, FREAD) == 0) {
E 31
I 31
		    (caddr_t)&dpart, FREAD, p) == 0) {
E 31
			if (dpart.part->p_fstype == FS_BSDFFS &&
			    dpart.part->p_frag != 0 && dpart.part->p_fsize != 0)
				bsize = dpart.part->p_frag *
				    dpart.part->p_fsize;
		}
		blkmask = (bsize / DEV_BSIZE) - 1;
		do {
D 52
			bn = (uio->uio_offset / DEV_BSIZE) &~ blkmask;
			on = uio->uio_offset % bsize;
			n = MIN((unsigned)(bsize - on), uio->uio_resid);
E 52
I 52
D 53
			bn = (ap->a_uio->uio_offset / DEV_BSIZE) &~ blkmask;
			on = ap->a_uio->uio_offset % bsize;
			n = MIN((unsigned)(bsize - on), ap->a_uio->uio_resid);
E 53
I 53
			bn = (uio->uio_offset / DEV_BSIZE) &~ blkmask;
			on = uio->uio_offset % bsize;
D 57
			n = MIN((unsigned)(bsize - on), uio->uio_resid);
E 57
I 57
			n = min((unsigned)(bsize - on), uio->uio_resid);
E 57
E 53
E 52
D 29
			count = howmany(bsize, CLBYTES);
			for (i = 0; i < count; i++)
				munhash(vp, bn + i * (CLBYTES / DEV_BSIZE));
E 29
			if (n == bsize)
D 52
				bp = getblk(vp, bn, bsize);
E 52
I 52
D 53
				bp = getblk(ap->a_vp, bn, bsize);
E 53
I 53
D 60
				bp = getblk(vp, bn, bsize);
E 60
I 60
				bp = getblk(vp, bn, bsize, 0, 0);
E 60
E 53
E 52
			else
D 52
				error = bread(vp, bn, bsize, NOCRED, &bp);
E 52
I 52
D 53
				error = bread(ap->a_vp, bn, bsize, NOCRED, &bp);
E 53
I 53
				error = bread(vp, bn, bsize, NOCRED, &bp);
E 53
E 52
D 57
			n = MIN(n, bsize - bp->b_resid);
E 57
I 57
			n = min(n, bsize - bp->b_resid);
E 57
			if (error) {
				brelse(bp);
				return (error);
			}
D 52
			error = uiomove(bp->b_un.b_addr + on, n, uio);
E 52
I 52
D 53
			error = uiomove(bp->b_un.b_addr + on, n, ap->a_uio);
E 53
I 53
D 66
			error = uiomove(bp->b_un.b_addr + on, n, uio);
E 66
I 66
			error = uiomove((char *)bp->b_data + on, n, uio);
E 66
E 53
E 52
			if (n + on == bsize) {
				bp->b_flags |= B_AGE;
				bawrite(bp);
			} else
				bdwrite(bp);
D 52
		} while (error == 0 && uio->uio_resid > 0 && n != 0);
E 52
I 52
D 53
		} while (error == 0 && ap->a_uio->uio_resid > 0 && n != 0);
E 53
I 53
		} while (error == 0 && uio->uio_resid > 0 && n != 0);
E 53
E 52
		return (error);
E 16

	default:
		panic("spec_write type");
	}
	/* NOTREACHED */
E 15
}
I 51
D 52
#undef vp
#undef uio
#undef ioflag
#undef cred
E 52
E 51

/*
 * Device ioctl operation.
 */
I 3
/* ARGSUSED */
E 3
D 11
blk_ioctl(vp, com, data, fflag, cred)
E 11
I 11
D 34
spec_ioctl(vp, com, data, fflag, cred)
E 34
I 34
D 51
spec_ioctl(vp, com, data, fflag, cred, p)
E 34
E 11
	struct vnode *vp;
D 20
	register int com;
E 20
I 20
	int com;
E 20
	caddr_t data;
	int fflag;
	struct ucred *cred;
I 34
	struct proc *p;
E 51
I 51
D 54
spec_ioctl (ap)
	struct vop_ioctl_args *ap;
E 54
I 54
spec_ioctl(ap)
	struct vop_ioctl_args /* {
		struct vnode *a_vp;
		int  a_command;
		caddr_t  a_data;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 54
D 52
#define vp (ap->a_vp)
#define com (ap->a_command)
#define data (ap->a_data)
#define fflag (ap->a_fflag)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 52
E 51
E 34
{
I 31
D 34
	struct proc *p = curproc;		/* XXX */
E 34
E 31
D 3
	register struct inode *ip = VTOI(vp);
	dev_t dev = ip->i_rdev;
E 3
I 3
D 52
	dev_t dev = vp->v_rdev;
E 52
I 52
	dev_t dev = ap->a_vp->v_rdev;
E 52
E 3

D 52
	switch (vp->v_type) {
E 52
I 52
	switch (ap->a_vp->v_type) {
E 52

	case VCHR:
D 31
		return ((*cdevsw[major(dev)].d_ioctl)(dev, com, data, fflag));
E 31
I 31
D 52
		return ((*cdevsw[major(dev)].d_ioctl)(dev, com, data,
		    fflag, p));
E 52
I 52
		return ((*cdevsw[major(dev)].d_ioctl)(dev, ap->a_command, ap->a_data,
		    ap->a_fflag, ap->a_p));
E 52
E 31

	case VBLK:
I 20
D 52
		if (com == 0 && (int)data == B_TAPE)
E 52
I 52
		if (ap->a_command == 0 && (int)ap->a_data == B_TAPE)
E 52
D 73
			if (bdevsw[major(dev)].d_flags & B_TAPE)
E 73
I 73
			if (bdevsw[major(dev)].d_type == D_TAPE)
E 73
				return (0);
			else
				return (1);
E 20
D 31
		return ((*bdevsw[major(dev)].d_ioctl)(dev, com, data, fflag));
E 31
I 31
D 52
		return ((*bdevsw[major(dev)].d_ioctl)(dev, com, data,
		   fflag, p));
E 52
I 52
		return ((*bdevsw[major(dev)].d_ioctl)(dev, ap->a_command, ap->a_data,
		   ap->a_fflag, ap->a_p));
E 52
E 31

	default:
D 11
		panic("blk_ioctl");
E 11
I 11
		panic("spec_ioctl");
E 11
		/* NOTREACHED */
	}
}
I 51
D 52
#undef vp
#undef com
#undef data
#undef fflag
#undef cred
#undef p
E 52
E 51

I 3
/* ARGSUSED */
E 3
D 11
blk_select(vp, which, cred)
E 11
I 11
D 22
spec_select(vp, which, cred)
E 22
I 22
D 34
spec_select(vp, which, fflags, cred)
E 34
I 34
D 51
spec_select(vp, which, fflags, cred, p)
E 34
E 22
E 11
	struct vnode *vp;
D 22
	int which;
E 22
I 22
	int which, fflags;
E 22
	struct ucred *cred;
I 34
	struct proc *p;
E 51
I 51
D 54
spec_select (ap)
	struct vop_select_args *ap;
E 54
I 54
spec_select(ap)
	struct vop_select_args /* {
		struct vnode *a_vp;
		int  a_which;
		int  a_fflags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 54
D 52
#define vp (ap->a_vp)
#define which (ap->a_which)
#define fflags (ap->a_fflags)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 52
E 51
E 34
{
I 31
D 34
	struct proc *p = curproc;		/* XXX */
E 34
E 31
D 3
	register struct inode *ip = VTOI(vp);
E 3
	register dev_t dev;

D 52
	switch (vp->v_type) {
E 52
I 52
	switch (ap->a_vp->v_type) {
E 52

	default:
		return (1);		/* XXX */

	case VCHR:
D 3
		dev = ip->i_rdev;
E 3
I 3
D 52
		dev = vp->v_rdev;
E 3
D 31
		return (*cdevsw[major(dev)].d_select)(dev, which);
E 31
I 31
		return (*cdevsw[major(dev)].d_select)(dev, which, p);
E 52
I 52
		dev = ap->a_vp->v_rdev;
		return (*cdevsw[major(dev)].d_select)(dev, ap->a_which, ap->a_p);
E 52
E 31
	}
}
I 54
/*
 * Synch buffers associated with a block device
 */
/* ARGSUSED */
int
spec_fsync(ap)
	struct vop_fsync_args /* {
		struct vnode *a_vp;
		struct ucred *a_cred;
		int  a_waitfor;
		struct proc *a_p;
	} */ *ap;
{
	register struct vnode *vp = ap->a_vp;
	register struct buf *bp;
	struct buf *nbp;
D 59
	int s, error, allerror = 0;
E 59
I 59
	int s;
E 59
E 54
I 51
D 52
#undef vp
#undef which
#undef fflags
#undef cred
#undef p
E 52
E 51

I 54
	if (vp->v_type == VCHR)
		return (0);
	/*
	 * Flush all dirty buffers associated with a block device.
	 */
loop:
	s = splbio();
D 58
	for (bp = vp->v_dirtyblkhd; bp; bp = nbp) {
		nbp = bp->b_blockf;
E 58
I 58
D 67
	for (bp = vp->v_dirtyblkhd.le_next; bp; bp = nbp) {
		nbp = bp->b_vnbufs.qe_next;
E 67
I 67
	for (bp = vp->v_dirtyblkhd.lh_first; bp; bp = nbp) {
		nbp = bp->b_vnbufs.le_next;
E 67
E 58
		if ((bp->b_flags & B_BUSY))
			continue;
		if ((bp->b_flags & B_DELWRI) == 0)
			panic("spec_fsync: not dirty");
		bremfree(bp);
		bp->b_flags |= B_BUSY;
		splx(s);
D 59
		if (error = bawrite(bp))
			allerror = error;
E 59
I 59
		bawrite(bp);
E 59
		goto loop;
	}
	if (ap->a_waitfor == MNT_WAIT) {
		while (vp->v_numoutput) {
			vp->v_flag |= VBWAIT;
			sleep((caddr_t)&vp->v_numoutput, PRIBIO + 1);
		}
#ifdef DIAGNOSTIC
D 58
		if (vp->v_dirtyblkhd) {
E 58
I 58
D 67
		if (vp->v_dirtyblkhd.le_next) {
E 67
I 67
		if (vp->v_dirtyblkhd.lh_first) {
E 67
E 58
			vprint("spec_fsync: dirty", vp);
			goto loop;
		}
#endif
	}
	splx(s);
D 59
	return (allerror);
E 59
I 59
	return (0);
E 59
}

I 78
int
spec_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
		struct proc *a_p;
	} */ *ap;
{

	VOP_UNLOCK(ap->a_vp, 0, ap->a_p);
	return (0);
}

E 78
E 54
/*
 * Just call the device strategy routine
 */
D 11
blk_strategy(bp)
E 11
I 11
D 51
spec_strategy(bp)
E 11
	register struct buf *bp;
E 51
I 51
D 54
spec_strategy (ap)
	struct vop_strategy_args *ap;
E 54
I 54
spec_strategy(ap)
	struct vop_strategy_args /* {
		struct buf *a_bp;
	} */ *ap;
E 54
D 52
#define bp (ap->a_bp)
E 52
E 51
{
I 20

E 20
D 52
	(*bdevsw[major(bp->b_dev)].d_strategy)(bp);
E 52
I 52
	(*bdevsw[major(ap->a_bp->b_dev)].d_strategy)(ap->a_bp);
E 52
	return (0);
}
I 51
D 52
#undef bp
E 52
E 51

I 10
/*
I 20
 * This is a noop, simply returning what one has been given.
 */
D 51
spec_bmap(vp, bn, vpp, bnp)
	struct vnode *vp;
	daddr_t bn;
	struct vnode **vpp;
	daddr_t *bnp;
E 51
I 51
D 54
spec_bmap (ap)
	struct vop_bmap_args *ap;
E 54
I 54
spec_bmap(ap)
	struct vop_bmap_args /* {
		struct vnode *a_vp;
		daddr_t  a_bn;
		struct vnode **a_vpp;
		daddr_t *a_bnp;
I 75
		int *a_runp;
E 75
	} */ *ap;
E 54
D 52
#define vp (ap->a_vp)
#define bn (ap->a_bn)
#define vpp (ap->a_vpp)
#define bnp (ap->a_bnp)
E 52
E 51
{

D 52
	if (vpp != NULL)
		*vpp = vp;
	if (bnp != NULL)
		*bnp = bn;
E 52
I 52
	if (ap->a_vpp != NULL)
		*ap->a_vpp = ap->a_vp;
	if (ap->a_bnp != NULL)
		*ap->a_bnp = ap->a_bn;
I 74
	if (ap->a_runp != NULL)
		*ap->a_runp = 0;
E 74
E 52
D 77
	return (0);
}
I 51
D 52
#undef vp
#undef bn
#undef vpp
#undef bnp
E 52
E 51

/*
E 20
 * At the moment we do not do any locking.
 */
I 13
/* ARGSUSED */
E 13
E 10
D 11
blk_lock(vp)
E 11
I 11
D 51
spec_lock(vp)
E 11
	struct vnode *vp;
E 51
I 51
D 54
spec_lock (ap)
	struct vop_lock_args *ap;
E 54
I 54
spec_lock(ap)
	struct vop_lock_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 54
D 52
#define vp (ap->a_vp)
E 52
E 51
{
D 10
	register struct inode *ip = VTOI(vp);
E 10

D 10
	if (ip)
		ILOCK(ip);
E 10
	return (0);
}
I 51
D 52
#undef vp
E 52
E 51

I 13
/* ARGSUSED */
E 13
D 11
blk_unlock(vp)
E 11
I 11
D 51
spec_unlock(vp)
E 11
	struct vnode *vp;
E 51
I 51
D 54
spec_unlock (ap)
	struct vop_unlock_args *ap;
E 54
I 54
spec_unlock(ap)
	struct vop_unlock_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 54
D 52
#define vp (ap->a_vp)
E 52
E 51
{
D 10
	register struct inode *ip = VTOI(vp);
E 10

E 77
D 10
	if (ip)
		IUNLOCK(ip);
E 10
	return (0);
}
I 51
D 52
#undef vp
E 52
E 51

D 3
blk_inactive(vp)
	struct vnode *vp;
{
	struct inode *ip = VTOI(vp);
	struct vnode *devvp = 0;
	int error;

	if (vp->v_count > 0)
		return (0);
D 2
printf("blk_inactive: free dev 0x%x\n", vp->v_rdev);
	return (ufs_inactive(vp));
E 2
I 2
	return (irele(ip));
E 2
}

E 3
/*
 * Device close routine
 */
I 3
/* ARGSUSED */
E 3
D 11
blk_close(vp, flag, cred)
E 11
I 11
D 34
spec_close(vp, flag, cred)
E 34
I 34
D 51
spec_close(vp, flag, cred, p)
E 34
E 11
D 3
	struct vnode *vp;
E 3
I 3
	register struct vnode *vp;
E 3
	int flag;
	struct ucred *cred;
I 34
	struct proc *p;
E 51
I 51
D 54
spec_close (ap)
	struct vop_close_args *ap;
E 54
I 54
spec_close(ap)
	struct vop_close_args /* {
		struct vnode *a_vp;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 54
D 52
#define vp (ap->a_vp)
#define flag (ap->a_fflag)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 52
E 51
E 34
{
I 31
D 34
	struct proc *p = curproc;		/* XXX */
E 34
E 31
I 3
D 10
	register struct inode *ip = VTOI(vp);
E 10
E 3
D 52
	dev_t dev = vp->v_rdev;
E 52
I 52
D 53
	dev_t dev = ap->a_vp->v_rdev;
E 53
I 53
	register struct vnode *vp = ap->a_vp;
	dev_t dev = vp->v_rdev;
E 53
E 52
D 3
	int type = vp->v_type;
E 3
I 3
D 33
	int (*cfunc)();
E 33
I 33
D 36
	int (*cfunc) __P((dev_t, int, int, struct proc *));
E 36
I 36
	int (*devclose) __P((dev_t, int, int, struct proc *));
E 36
E 33
D 25
	int error, mode;
E 25
I 25
D 54
	int mode;
E 54
I 54
	int mode, error;
E 54
E 25
E 3

D 3
	return (closei(dev, type, flag));
E 3
I 3
D 10
	if (vp->v_count > 1 && !(ip->i_flag & ILOCKED))
		ITIMES(ip, &time, &time);

E 10
D 52
	switch (vp->v_type) {
E 52
I 52
D 53
	switch (ap->a_vp->v_type) {
E 53
I 53
	switch (vp->v_type) {
E 53
E 52

	case VCHR:
D 12
		if (vp->v_count > 1)
E 12
I 12
		/*
I 63
		 * Hack: a tty device that is a controlling terminal
		 * has a reference from the session structure.
		 * We cannot easily tell that a character device is
		 * a controlling terminal, unless it is the closing
		 * process' controlling terminal.  In that case,
		 * if the reference count is 2 (this last descriptor
		 * plus the session), release the reference from the session.
		 */
D 64
		if (vp == ap->a_p->p_session->s_ttyvp && vcount(vp) == 2) {
E 64
I 64
		if (vcount(vp) == 2 && ap->a_p &&
		    vp == ap->a_p->p_session->s_ttyvp) {
E 64
			vrele(vp);
			ap->a_p->p_session->s_ttyvp = NULL;
		}
		/*
E 63
		 * If the vnode is locked, then we are in the midst
		 * of forcably closing the device, otherwise we only
		 * close on last reference.
		 */
D 19
		if (vp->v_count > 1 && (vp->v_flag & VXLOCK) == 0)
E 19
I 19
D 52
		if (vcount(vp) > 1 && (vp->v_flag & VXLOCK) == 0)
E 52
I 52
D 53
		if (vcount(ap->a_vp) > 1 && (ap->a_vp->v_flag & VXLOCK) == 0)
E 53
I 53
		if (vcount(vp) > 1 && (vp->v_flag & VXLOCK) == 0)
E 53
E 52
E 19
E 12
			return (0);
D 36
		cfunc = cdevsw[major(dev)].d_close;
E 36
I 36
		devclose = cdevsw[major(dev)].d_close;
E 36
D 10
		mode = IFCHR;
E 10
I 10
		mode = S_IFCHR;
E 10
		break;

	case VBLK:
		/*
		 * On last close of a block device (that isn't mounted)
		 * we must invalidate any in core blocks, so that
		 * we can, for instance, change floppy disks.
		 */
D 5
		bflush(dev);
D 4
		binval(dev);
E 4
I 4
		if (binval(dev))
E 5
I 5
D 17
		bflush(vp->v_mount);
		if (binval(vp->v_mount))
E 17
I 17
D 20
		bflush(vp->v_mounton);
		if (binval(vp->v_mounton))
E 20
I 20
D 52
		vflushbuf(vp, 0);
		if (vinvalbuf(vp, 1))
E 52
I 52
D 53
		vflushbuf(ap->a_vp, 0);
		if (vinvalbuf(ap->a_vp, 1))
E 53
I 53
D 54
		vflushbuf(vp, 0);
		if (vinvalbuf(vp, 1))
E 53
E 52
E 20
E 17
E 5
			return (0);
E 54
I 54
D 60
		if (error = vinvalbuf(vp, 1, ap->a_cred, ap->a_p))
E 60
I 60
D 70
		if (error = vinvalbuf(vp, 1, ap->a_cred, ap->a_p, 0, 0))
E 70
I 70
		if (error = vinvalbuf(vp, V_SAVE, ap->a_cred, ap->a_p, 0, 0))
E 70
E 60
			return (error);
E 54
E 4
		/*
D 12
		 * We don't want to really close the device if it is still
D 10
		 * in use. Since every use (buffer, inode, swap, cmap)
E 10
I 10
		 * in use. Since every use (buffer, vnode, swap, cmap)
E 12
I 12
		 * We do not want to really close the device if it
		 * is still in use unless we are trying to close it
		 * forcibly. Since every use (buffer, vnode, swap, cmap)
E 12
E 10
D 19
		 * holds a reference to the vnode, and because we ensure
		 * that there cannot be more than one vnode per device,
		 * we need only check that we are down to the last
D 12
		 * reference before closing.
E 12
I 12
		 * reference to detect last close.
E 19
I 19
		 * holds a reference to the vnode, and because we mark
		 * any other vnodes that alias this device, when the
		 * sum of the reference counts on all the aliased
		 * vnodes descends to one, we are on last close.
E 19
E 12
		 */
D 12
		if (vp->v_count > 1)
E 12
I 12
D 19
		if (vp->v_count > 1 && (vp->v_flag & VXLOCK) == 0)
E 19
I 19
D 52
		if (vcount(vp) > 1 && (vp->v_flag & VXLOCK) == 0)
E 52
I 52
D 53
		if (vcount(ap->a_vp) > 1 && (ap->a_vp->v_flag & VXLOCK) == 0)
E 53
I 53
		if (vcount(vp) > 1 && (vp->v_flag & VXLOCK) == 0)
E 53
E 52
E 19
E 12
			return (0);
D 36
		cfunc = bdevsw[major(dev)].d_close;
E 36
I 36
		devclose = bdevsw[major(dev)].d_close;
E 36
D 10
		mode = IFBLK;
E 10
I 10
		mode = S_IFBLK;
E 10
		break;

	default:
D 11
		panic("blk_close: not special");
E 11
I 11
		panic("spec_close: not special");
E 11
	}

D 10
	/* XXX what is this doing below the vnode op call */
E 10
D 25
	if (setjmp(&u.u_qsave)) {
		/*
		 * If device close routine is interrupted,
		 * must return so closef can clean up.
		 */
		error = EINTR;
	} else
		error = (*cfunc)(dev, flag, mode);
D 7
	/*
	 * Most device close routines don't return errors,
	 * and dup2() doesn't work right on error.
	 */
	error = 0;		/* XXX */
E 7
	return (error);
E 25
I 25
D 31
	return ((*cfunc)(dev, flag, mode));
E 31
I 31
D 36
	return ((*cfunc)(dev, flag, mode, p));
E 36
I 36
D 52
	return ((*devclose)(dev, flag, mode, p));
E 52
I 52
	return ((*devclose)(dev, ap->a_fflag, mode, ap->a_p));
E 52
E 36
E 31
E 25
I 20
}
I 51
D 52
#undef vp
#undef flag
#undef cred
#undef p
E 52
E 51

/*
 * Print out the contents of a special device vnode.
 */
D 51
spec_print(vp)
	struct vnode *vp;
E 51
I 51
D 54
spec_print (ap)
	struct vop_print_args *ap;
E 54
I 54
spec_print(ap)
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 54
D 52
#define vp (ap->a_vp)
E 52
E 51
{

D 52
	printf("tag VT_NON, dev %d, %d\n", major(vp->v_rdev),
		minor(vp->v_rdev));
E 52
I 52
	printf("tag VT_NON, dev %d, %d\n", major(ap->a_vp->v_rdev),
		minor(ap->a_vp->v_rdev));
I 62
}

/*
 * Return POSIX pathconf information applicable to special devices.
 */
spec_pathconf(ap)
	struct vop_pathconf_args /* {
		struct vnode *a_vp;
		int a_name;
		int *a_retval;
	} */ *ap;
{

	switch (ap->a_name) {
	case _PC_LINK_MAX:
		*ap->a_retval = LINK_MAX;
		return (0);
	case _PC_MAX_CANON:
		*ap->a_retval = MAX_CANON;
		return (0);
	case _PC_MAX_INPUT:
		*ap->a_retval = MAX_INPUT;
		return (0);
	case _PC_PIPE_BUF:
		*ap->a_retval = PIPE_BUF;
		return (0);
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 1;
		return (0);
	case _PC_VDISABLE:
		*ap->a_retval = _POSIX_VDISABLE;
		return (0);
	default:
		return (EINVAL);
	}
	/* NOTREACHED */
E 62
E 52
I 30
}
I 51
D 52
#undef vp
E 52
E 51

/*
 * Special device advisory byte-level locks.
 */
I 34
/* ARGSUSED */
E 34
D 51
spec_advlock(vp, id, op, fl, flags)
	struct vnode *vp;
	caddr_t id;
	int op;
	struct flock *fl;
	int flags;
E 51
I 51
D 54
spec_advlock (ap)
	struct vop_advlock_args *ap;
E 54
I 54
spec_advlock(ap)
	struct vop_advlock_args /* {
		struct vnode *a_vp;
		caddr_t  a_id;
		int  a_op;
		struct flock *a_fl;
		int  a_flags;
	} */ *ap;
E 54
D 52
#define vp (ap->a_vp)
#define id (ap->a_id)
#define op (ap->a_op)
#define fl (ap->a_fl)
#define flags (ap->a_flags)
E 52
E 51
{

	return (EOPNOTSUPP);
E 30
E 20
E 3
}
I 51
D 52
#undef vp
#undef id
#undef op
#undef fl
#undef flags
E 52
E 51

/*
D 14
 * Block device bad operation
E 14
I 14
 * Special device failed operation
E 14
 */
I 14
spec_ebadf()
{

	return (EBADF);
}

/*
 * Special device bad operation
 */
E 14
D 11
blk_badop()
E 11
I 11
spec_badop()
E 11
{

D 6
	printf("blk_badop called\n");
	return (ENXIO);
E 6
I 6
D 11
	panic("blk_badop called");
E 11
I 11
	panic("spec_badop called");
E 11
	/* NOTREACHED */
E 6
D 31
}

/*
D 14
 * Block device null operation
E 14
I 14
 * Special device null operation
E 14
 */
D 11
blk_nullop()
E 11
I 11
spec_nullop()
E 11
{

	return (0);
E 31
}
E 1
