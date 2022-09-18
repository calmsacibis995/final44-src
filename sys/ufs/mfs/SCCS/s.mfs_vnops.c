h35014
s 00004/00001/00322
d D 8.11 95/05/22 23:05:06 mckusick 61 60
c have to unlock at the end of inactive
e
s 00002/00001/00321
d D 8.10 95/03/30 14:22:26 mckusick 60 59
c fix declaration for mfs_init
e
s 00002/00002/00320
d D 8.9 95/03/21 00:59:27 mckusick 59 58
c daddr_t => ufs_daddr_t
e
s 00001/00000/00321
d D 8.8 95/02/22 20:55:08 mckusick 58 57
c add mfs_revoke
e
s 00002/00000/00319
d D 8.7 95/02/22 18:06:12 mckusick 57 56
c null out runp if requested in bmap
e
s 00001/00089/00318
d D 8.6 95/01/02 23:29:00 mckusick 56 55
c delete old vaxisms
e
s 00000/00000/00407
d D 8.5 94/07/28 03:39:12 pendry 55 54
c changes for whiteouts and union filesystem
e
s 00003/00002/00404
d D 8.4 94/06/16 17:13:53 mckusick 54 53
c break out reclaim operations (from mycroft)
e
s 00008/00008/00398
d D 8.3 93/09/21 07:42:36 bostic 53 52
c changes for 4.4BSD-Lite requested by USL
e
s 00001/00000/00405
d D 8.2 93/08/11 13:22:48 mckusick 52 51
c add mfs_pathconf
e
s 00002/00002/00403
d D 8.1 93/06/11 16:27:40 bostic 51 50
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00404
d D 7.42 93/04/28 18:58:18 mckusick 50 49
c vfinddev returns 1 for success
e
s 00001/00001/00404
d D 7.41 93/02/02 21:07:22 mckusick 49 48
c vinvalbuf takes parameter to indicate interrupt
e
s 00001/00000/00404
d D 7.40 92/10/07 17:17:19 margo 48 47
c Add comment in argument list to bmap.
e
s 00002/00002/00402
d D 7.39 92/10/02 00:19:41 mckusick 47 46
c av_forw/av_back are gone; now use b_actf/b_actb for linking active buffers
e
s 00002/00001/00402
d D 7.38 92/07/13 00:06:21 pendry 46 45
c specdev.h moves to new location
e
s 00046/00017/00357
d D 7.37 92/07/03 01:52:10 mckusick 45 44
c add parameter declarations
e
s 00005/00004/00369
d D 7.36 92/06/25 13:26:31 mckusick 44 43
c use spec_fsync to push buffers; new parameters to vinvalbuf
e
s 00017/00020/00356
d D 7.35 92/06/25 13:25:45 mckusick 43 42
c misc stylistic cleanups
e
s 00003/00003/00373
d D 7.34 92/06/04 14:56:34 mckusick 42 41
c add support for luna68k from Omron
e
s 00018/00016/00358
d D 7.33 92/06/04 09:50:53 heideman 41 40
c registerized vnodeop ops after vnode interface conversion
e
s 00025/00071/00349
d D 7.32 92/05/15 13:55:55 heideman 40 39
c vnodeop argument macro expansion
e
s 00108/00072/00312
d D 7.31 92/05/14 17:30:31 heideman 39 30
c vnode interface conversion
e
s 00108/00072/00312
d R 7.31 92/05/14 15:44:21 heideman 38 30
c vnode interface conversion
e
s 00108/00072/00312
d R 7.31 92/05/14 14:49:33 heideman 37 30
c vnode interface conversion
e
s 00108/00073/00311
d R 7.31 92/05/14 12:53:32 heideman 36 30
c vnode interface conversion
e
s 00108/00073/00311
d R 7.31 92/05/14 11:50:51 heideman 35 30
c vnode interface conversion
e
s 00108/00073/00311
d R 7.31 92/05/14 10:31:05 heideman 34 30
c vnode interface conversion
e
s 00108/00073/00311
d R 7.31 92/05/13 23:09:44 heideman 33 30
c vnode interface conversion
e
s 00108/00073/00311
d R 7.31 92/05/13 18:56:11 heideman 32 30
c vnode interface conversion
e
s 00108/00073/00311
d R 7.31 92/05/13 18:28:14 heideman 31 30
c vnode interface conversion
e
s 00004/00002/00380
d D 7.30 92/04/19 08:40:38 ralph 30 29
c fix mfs_inactive for incore mini-root.
e
s 00013/00002/00369
d D 7.29 92/03/22 20:32:27 ralph 29 28
c added support for memory mini-root.
e
s 00003/00003/00368
d D 7.28 92/03/10 16:32:05 torek 28 27
c sparc
e
s 00002/00000/00369
d D 7.27 92/03/01 20:55:03 ralph 27 26
c don't include mtpr.h unless needed
e
s 00014/00000/00355
d D 7.26 91/12/16 15:52:34 mckusick 26 25
c free dynamically allocated part
e
s 00007/00000/00348
d D 7.25 91/11/05 15:43:56 mckusick 25 24
c reorganization to move ufsmount ops to be vnode ops
e
s 00024/00012/00324
d D 7.24 91/11/01 17:12:57 bostic 24 23
c UFS/FFS split for LFS version 1; mfs_print returns int
e
s 00003/00003/00333
d D 7.23 91/09/06 19:18:45 ralph 23 22
c added mips to ifdef hp300, i386
e
s 00037/00050/00299
d D 7.22 91/04/16 00:14:13 mckusick 22 21
c use prototypes for MFS vnode ops (from mfsnode.h);
c add appropriate proc pointers (eliminating lots of curproc's)
e
s 00005/00005/00344
d D 7.21 91/03/19 10:30:18 karels 21 20
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; remove ../ufs/ from includes; consolidate *nullops();
c chown/fchmod use proc's credentials, not file's
e
s 00001/00000/00348
d D 7.20 91/02/01 16:29:08 mckusick 20 19
c add POSIX-style byte-level record locking
e
s 00000/00002/00348
d D 7.19 90/12/05 16:07:40 mckusick 19 18
c update for new VM
e
s 00003/00003/00347
d D 7.18 90/07/02 10:59:12 william 18 17
c added 386 ifdefs
e
s 00001/00011/00349
d D 7.17 90/06/28 22:29:48 bostic 17 16
c new copyright notice
e
s 00023/00008/00337
d D 7.16 90/06/22 09:28:40 hibler 16 15
c make separate version of mfs_doio for hp300 and vax/tahoe
e
s 00012/00000/00333
d D 7.15 90/05/10 15:20:39 mckusick 15 14
c hp300 does physical I/O mapping itself
e
s 00001/00000/00332
d D 7.14 90/01/15 18:39:34 mckusick 14 13
c add islocked vnode op
e
s 00002/00002/00330
d D 7.13 90/01/02 19:36:32 mckusick 13 12
c need null lock and unlock ops for vclean
e
s 00006/00002/00326
d D 7.12 89/12/31 15:30:47 mckusick 12 11
c use vfinddev to find vnode as b_vp may represent a file
c instead of the block device supporting the memory file system
e
s 00003/00003/00325
d D 7.11 89/12/30 22:40:18 mckusick 11 10
c v_count => v_usecount
e
s 00019/00001/00309
d D 7.10 89/11/30 23:39:38 mckusick 10 9
c add null bmap routine
e
s 00046/00032/00264
d D 7.9 89/11/30 23:04:41 mckusick 9 8
c replace bflush and binval with vflushbuf and vinvalbuf;
c add mfs_print routine; label vnops table
e
s 00002/00002/00294
d D 7.8 89/11/25 21:39:06 mckusick 8 7
c maintain mount information in v_mounton rather than overloading v_mount
e
s 00003/00003/00293
d D 7.7 89/10/31 13:27:51 mckusick 7 6
c ../machine should be machine
e
s 00014/00011/00282
d D 7.6 89/10/29 23:40:57 mckusick 6 5
c flush out any pending I/O before trying to close
e
s 00000/00001/00293
d D 7.5 89/10/26 00:06:38 mckusick 5 4
c only vrele can delete the v_type field
e
s 00028/00017/00266
d D 7.4 89/10/24 19:39:26 mckusick 4 3
c create own private data area instead of overloading an inode
e
s 00013/00010/00270
d D 7.3 89/10/20 18:36:32 mckusick 3 2
c allow multiple I/O requests; try to unmount when signalled
e
s 00001/00002/00279
d D 7.2 89/09/12 22:06:18 mckusick 2 1
c allow multiple memory based file systems
e
s 00281/00000/00000
d D 7.1 89/09/05 16:20:24 mckusick 1 0
c date and time created 89/09/05 16:20:24 by mckusick
e
u
U
t
T
I 1
/*
D 51
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 51
I 51
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 51
 *
D 17
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
E 17
I 17
 * %sccs.include.redist.c%
E 17
 *
 *	%W% (Berkeley) %G%
 */

D 24
#include "param.h"
I 22
#include "systm.h"
E 22
#include "time.h"
I 3
#include "kernel.h"
E 3
#include "proc.h"
I 3
D 21
#include "user.h"
E 21
E 3
#include "buf.h"
D 19
#include "vmmac.h"
E 19
D 21
#include "errno.h"
E 21
#include "map.h"
#include "vnode.h"
E 24
I 24
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/map.h>
#include <sys/vnode.h>
I 26
#include <sys/malloc.h>
I 44
D 46
#include <sys/specdev.h>
E 46
I 46

#include <miscfs/specfs/specdev.h>
E 46
E 44
E 26
E 24
D 4
#include "../ufs/inode.h"
E 4
I 4
D 21
#include "../ufs/mfsnode.h"
E 4
#include "../ufs/mfsiom.h"
E 21
I 21

D 24
#include "mfsnode.h"
#include "mfsiom.h"
E 24
I 24
#include <machine/vmparam.h>
I 27
D 43
#if defined(tahoe)
E 27
#include <machine/mtpr.h>
I 27
#endif
E 43
E 27
E 24

E 21
D 7
#include "../machine/vmparam.h"
#include "../machine/pte.h"
#include "../machine/mtpr.h"
E 7
I 7
D 24
#include "machine/vmparam.h"
D 19
#include "machine/pte.h"
E 19
#include "machine/mtpr.h"
E 24
I 24
#include <ufs/mfs/mfsnode.h>
#include <ufs/mfs/mfsiom.h>
#include <ufs/mfs/mfs_extern.h>
E 24
E 7

I 15
D 18
#if !defined(hp300)
E 18
I 18
D 23
#if !defined(hp300) && !defined(i386)
E 23
I 23
D 28
#if !defined(hp300) && !defined(i386) && !defined(mips)
E 28
I 28
D 42
#if !defined(hp300) && !defined(i386) && !defined(mips) && !defined(sparc)
E 42
I 42
D 56
#if !defined(hp300) && !defined(i386) && !defined(mips) && !defined(sparc) && !defined(luna68k)
E 42
E 28
E 23
E 18
E 15
D 2
int mfs_running;		/* 1 => daemon has started running */
E 2
static int mfsmap_want;		/* 1 => need kernel I/O resources */
struct map mfsmap[MFS_MAPSIZE];
extern char mfsiobuf[];
I 15
#endif
E 15

E 56
/*
 * mfs vnode operations.
 */
D 22
int	mfs_open(),
	mfs_strategy(),
I 10
	mfs_bmap(),
E 10
	mfs_ioctl(),
	mfs_close(),
D 4
	ufs_inactive(),
E 4
I 4
	mfs_inactive(),
I 9
	mfs_print(),
E 9
E 4
	mfs_badop(),
	mfs_nullop();

E 22
D 39
struct vnodeops mfs_vnodeops = {
D 9
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_open,
	mfs_close,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_ioctl,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_badop,
D 4
	ufs_inactive,
E 4
I 4
	mfs_inactive,
	mfs_nullop,
E 4
	mfs_badop,
	mfs_badop,
	mfs_badop,
	mfs_strategy,
E 9
I 9
D 22
	mfs_badop,		/* lookup */
	mfs_badop,		/* create */
	mfs_badop,		/* mknod */
E 22
I 22
	mfs_lookup,		/* lookup */
	mfs_create,		/* create */
	mfs_mknod,		/* mknod */
E 22
	mfs_open,		/* open */
	mfs_close,		/* close */
D 22
	mfs_badop,		/* access */
	mfs_badop,		/* getattr */
	mfs_badop,		/* setattr */
	mfs_badop,		/* read */
	mfs_badop,		/* write */
E 22
I 22
	mfs_access,		/* access */
	mfs_getattr,		/* getattr */
	mfs_setattr,		/* setattr */
	mfs_read,		/* read */
	mfs_write,		/* write */
E 22
	mfs_ioctl,		/* ioctl */
D 22
	mfs_badop,		/* select */
	mfs_badop,		/* mmap */
	mfs_badop,		/* fsync */
	mfs_badop,		/* seek */
	mfs_badop,		/* remove */
	mfs_badop,		/* link */
	mfs_badop,		/* rename */
	mfs_badop,		/* mkdir */
	mfs_badop,		/* rmdir */
	mfs_badop,		/* symlink */
	mfs_badop,		/* readdir */
	mfs_badop,		/* readlink */
	mfs_badop,		/* abortop */
E 22
I 22
	mfs_select,		/* select */
	mfs_mmap,		/* mmap */
	mfs_fsync,		/* fsync */
	mfs_seek,		/* seek */
	mfs_remove,		/* remove */
	mfs_link,		/* link */
	mfs_rename,		/* rename */
	mfs_mkdir,		/* mkdir */
	mfs_rmdir,		/* rmdir */
	mfs_symlink,		/* symlink */
	mfs_readdir,		/* readdir */
	mfs_readlink,		/* readlink */
	mfs_abortop,		/* abortop */
E 22
	mfs_inactive,		/* inactive */
D 22
	mfs_nullop,		/* reclaim */
D 13
	mfs_badop,		/* lock */
	mfs_badop,		/* unlock */
E 13
I 13
	mfs_nullop,		/* lock */
	mfs_nullop,		/* unlock */
E 22
I 22
	mfs_reclaim,		/* reclaim */
	mfs_lock,		/* lock */
	mfs_unlock,		/* unlock */
E 22
E 13
D 10
	mfs_badop,		/* bmap */
E 10
I 10
	mfs_bmap,		/* bmap */
E 10
	mfs_strategy,		/* strategy */
	mfs_print,		/* print */
I 14
D 22
	mfs_nullop,		/* islocked */
I 20
	mfs_badop,		/* advlock */
E 22
I 22
	mfs_islocked,		/* islocked */
	mfs_advlock,		/* advlock */
I 25
	mfs_blkatoff,		/* blkatoff */
	mfs_vget,		/* vget */
	mfs_valloc,		/* valloc */
	mfs_vfree,		/* vfree */
	mfs_truncate,		/* truncate */
	mfs_update,		/* update */
	mfs_bwrite,		/* bwrite */
E 39
I 39
int (**mfs_vnodeop_p)();
struct vnodeopv_entry_desc mfs_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, mfs_lookup },		/* lookup */
	{ &vop_create_desc, mfs_create },		/* create */
D 43
	{ &vop_mknod_desc, mfs_mknod },		/* mknod */
	{ &vop_open_desc, mfs_open },		/* open */
	{ &vop_close_desc, mfs_close },		/* close */
E 43
I 43
	{ &vop_mknod_desc, mfs_mknod },			/* mknod */
	{ &vop_open_desc, mfs_open },			/* open */
	{ &vop_close_desc, mfs_close },			/* close */
E 43
	{ &vop_access_desc, mfs_access },		/* access */
	{ &vop_getattr_desc, mfs_getattr },		/* getattr */
	{ &vop_setattr_desc, mfs_setattr },		/* setattr */
D 43
	{ &vop_read_desc, mfs_read },		/* read */
	{ &vop_write_desc, mfs_write },		/* write */
	{ &vop_ioctl_desc, mfs_ioctl },		/* ioctl */
E 43
I 43
	{ &vop_read_desc, mfs_read },			/* read */
	{ &vop_write_desc, mfs_write },			/* write */
	{ &vop_ioctl_desc, mfs_ioctl },			/* ioctl */
E 43
	{ &vop_select_desc, mfs_select },		/* select */
I 58
	{ &vop_revoke_desc, mfs_revoke },		/* revoke */
E 58
D 43
	{ &vop_mmap_desc, mfs_mmap },		/* mmap */
	{ &vop_fsync_desc, mfs_fsync },		/* fsync */
	{ &vop_seek_desc, mfs_seek },		/* seek */
E 43
I 43
	{ &vop_mmap_desc, mfs_mmap },			/* mmap */
D 44
	{ &vop_fsync_desc, mfs_fsync },			/* fsync */
E 44
I 44
	{ &vop_fsync_desc, spec_fsync },		/* fsync */
E 44
	{ &vop_seek_desc, mfs_seek },			/* seek */
E 43
	{ &vop_remove_desc, mfs_remove },		/* remove */
D 43
	{ &vop_link_desc, mfs_link },		/* link */
E 43
I 43
	{ &vop_link_desc, mfs_link },			/* link */
E 43
	{ &vop_rename_desc, mfs_rename },		/* rename */
D 43
	{ &vop_mkdir_desc, mfs_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, mfs_rmdir },		/* rmdir */
E 43
I 43
	{ &vop_mkdir_desc, mfs_mkdir },			/* mkdir */
	{ &vop_rmdir_desc, mfs_rmdir },			/* rmdir */
E 43
	{ &vop_symlink_desc, mfs_symlink },		/* symlink */
	{ &vop_readdir_desc, mfs_readdir },		/* readdir */
	{ &vop_readlink_desc, mfs_readlink },		/* readlink */
	{ &vop_abortop_desc, mfs_abortop },		/* abortop */
	{ &vop_inactive_desc, mfs_inactive },		/* inactive */
	{ &vop_reclaim_desc, mfs_reclaim },		/* reclaim */
D 43
	{ &vop_lock_desc, mfs_lock },		/* lock */
E 43
I 43
	{ &vop_lock_desc, mfs_lock },			/* lock */
E 43
	{ &vop_unlock_desc, mfs_unlock },		/* unlock */
D 43
	{ &vop_bmap_desc, mfs_bmap },		/* bmap */
E 43
I 43
	{ &vop_bmap_desc, mfs_bmap },			/* bmap */
E 43
	{ &vop_strategy_desc, mfs_strategy },		/* strategy */
D 43
	{ &vop_print_desc, mfs_print },		/* print */
E 43
I 43
	{ &vop_print_desc, mfs_print },			/* print */
E 43
	{ &vop_islocked_desc, mfs_islocked },		/* islocked */
I 52
	{ &vop_pathconf_desc, mfs_pathconf },		/* pathconf */
E 52
	{ &vop_advlock_desc, mfs_advlock },		/* advlock */
	{ &vop_blkatoff_desc, mfs_blkatoff },		/* blkatoff */
D 43
	{ &vop_vget_desc, mfs_vget },		/* vget */
E 43
I 43
D 45
	{ &vop_vget_desc, mfs_vget },			/* vget */
E 45
E 43
	{ &vop_valloc_desc, mfs_valloc },		/* valloc */
D 43
	{ &vop_vfree_desc, mfs_vfree },		/* vfree */
E 43
I 43
	{ &vop_vfree_desc, mfs_vfree },			/* vfree */
E 43
	{ &vop_truncate_desc, mfs_truncate },		/* truncate */
	{ &vop_update_desc, mfs_update },		/* update */
	{ &vop_bwrite_desc, mfs_bwrite },		/* bwrite */
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
E 39
E 25
E 22
E 20
E 14
E 9
};
I 39
struct vnodeopv_desc mfs_vnodeop_opv_desc =
	{ &mfs_vnodeop_p, mfs_vnodeop_entries };
E 39

/*
 * Vnode Operations.
 *
 * Open called to allow memory filesystem to initialize and
D 3
 * validate before actual IO. Nothing to do here as the
 * filesystem is ready to go in the process address space.
E 3
I 3
 * validate before actual IO. Record our process identifier
 * so we can tell when we are doing I/O to ourself.
E 3
 */
/* ARGSUSED */
I 24
int
E 24
D 22
mfs_open(vp, mode, cred)
E 22
I 22
D 39
mfs_open(vp, mode, cred, p)
E 22
	register struct vnode *vp;
	int mode;
	struct ucred *cred;
I 22
	struct proc *p;
E 39
I 39
D 45
mfs_open (ap)
	struct vop_open_args *ap;
E 45
I 45
mfs_open(ap)
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 45
D 40
#define vp (ap->a_vp)
#define mode (ap->a_mode)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 40
E 39
E 22
{
I 3
D 4
	register struct inode *ip = VTOI(vp);
E 4
E 3

D 40
	if (vp->v_type != VBLK) {
E 40
I 40
	if (ap->a_vp->v_type != VBLK) {
E 40
		panic("mfs_ioctl not VBLK");
		/* NOTREACHED */
	}
I 3
D 4
	ip->i_uid = u.u_procp->p_pid;
	ip->i_spare[0] = 0;
E 4
E 3
	return (0);
}
I 39
D 40
#undef vp
#undef mode
#undef cred
#undef p
E 40
E 39

/*
 * Ioctl operation.
 */
/* ARGSUSED */
I 24
int
E 24
D 22
mfs_ioctl(vp, com, data, fflag, cred)
E 22
I 22
D 39
mfs_ioctl(vp, com, data, fflag, cred, p)
E 22
	struct vnode *vp;
	int com;
	caddr_t data;
	int fflag;
	struct ucred *cred;
I 22
	struct proc *p;
E 39
I 39
D 45
mfs_ioctl (ap)
	struct vop_ioctl_args *ap;
E 45
I 45
mfs_ioctl(ap)
	struct vop_ioctl_args /* {
		struct vnode *a_vp;
		int  a_command;
		caddr_t  a_data;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 45
D 40
#define vp (ap->a_vp)
#define com (ap->a_command)
#define data (ap->a_data)
#define fflag (ap->a_fflag)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 40
E 39
E 22
{

D 29
	return (-1);
E 29
I 29
	return (ENOTTY);
E 29
}
I 39
D 40
#undef vp
#undef com
#undef data
#undef fflag
#undef cred
#undef p
E 40
E 39

/*
 * Pass I/O requests to the memory filesystem process.
 */
I 24
int
E 24
D 39
mfs_strategy(bp)
	register struct buf *bp;
E 39
I 39
D 45
mfs_strategy (ap)
	struct vop_strategy_args *ap;
E 45
I 45
mfs_strategy(ap)
	struct vop_strategy_args /* {
		struct buf *a_bp;
	} */ *ap;
E 45
D 40
#define bp (ap->a_bp)
E 40
E 39
{
I 41
	register struct buf *bp = ap->a_bp;
E 41
D 4
	register struct inode *ip = VTOI(bp->b_vp);
	int error;
E 4
I 4
D 12
	register struct mfsnode *mfsp = VTOMFS(bp->b_vp);
E 12
I 12
	register struct mfsnode *mfsp;
	struct vnode *vp;
I 22
	struct proc *p = curproc;		/* XXX */
E 22
E 12
E 4

I 12
D 40
	if (vfinddev(bp->b_dev, VBLK, &vp) || vp->v_usecount == 0)
E 40
I 40
D 41
	if (vfinddev(ap->a_bp->b_dev, VBLK, &vp) || vp->v_usecount == 0)
E 41
I 41
D 50
	if (vfinddev(bp->b_dev, VBLK, &vp) || vp->v_usecount == 0)
E 50
I 50
	if (!vfinddev(bp->b_dev, VBLK, &vp) || vp->v_usecount == 0)
E 50
E 41
E 40
		panic("mfs_strategy: bad dev");
	mfsp = VTOMFS(vp);
E 12
D 3
	ILOCK(ip);
D 2
	if (!mfs_running) {
E 2
I 2
	if (bp->b_vp->v_mount == NULL) {
E 3
I 3
D 4
	if (ip->i_uid == u.u_procp->p_pid) {
E 3
E 2
		mfs_doio(bp, (caddr_t)ip->i_diroff);
E 4
I 4
D 21
	if (mfsp->mfs_pid == u.u_procp->p_pid) {
E 21
I 21
D 22
	if (mfsp->mfs_pid == curproc->p_pid) {
E 22
I 22
D 29
	if (mfsp->mfs_pid == p->p_pid) {
E 29
I 29
	/* check for mini-root access */
	if (mfsp->mfs_pid == 0) {
		caddr_t base;

D 40
		base = mfsp->mfs_baseoff + (bp->b_blkno << DEV_BSHIFT);
		if (bp->b_flags & B_READ)
			bcopy(base, bp->b_un.b_addr, bp->b_bcount);
E 40
I 40
D 41
		base = mfsp->mfs_baseoff + (ap->a_bp->b_blkno << DEV_BSHIFT);
		if (ap->a_bp->b_flags & B_READ)
			bcopy(base, ap->a_bp->b_un.b_addr, ap->a_bp->b_bcount);
E 41
I 41
		base = mfsp->mfs_baseoff + (bp->b_blkno << DEV_BSHIFT);
		if (bp->b_flags & B_READ)
D 53
			bcopy(base, bp->b_un.b_addr, bp->b_bcount);
E 53
I 53
			bcopy(base, bp->b_data, bp->b_bcount);
E 53
E 41
E 40
		else
D 40
			bcopy(bp->b_un.b_addr, base, bp->b_bcount);
		biodone(bp);
E 40
I 40
D 41
			bcopy(ap->a_bp->b_un.b_addr, base, ap->a_bp->b_bcount);
		biodone(ap->a_bp);
E 41
I 41
D 53
			bcopy(bp->b_un.b_addr, base, bp->b_bcount);
E 53
I 53
			bcopy(bp->b_data, base, bp->b_bcount);
E 53
		biodone(bp);
E 41
E 40
	} else if (mfsp->mfs_pid == p->p_pid) {
E 29
E 22
E 21
D 40
		mfs_doio(bp, mfsp->mfs_baseoff);
E 40
I 40
D 41
		mfs_doio(ap->a_bp, mfsp->mfs_baseoff);
E 41
I 41
		mfs_doio(bp, mfsp->mfs_baseoff);
E 41
E 40
E 4
	} else {
I 3
D 4
		bp->av_forw = (struct buf *)ip->i_spare[0];
E 3
		ip->i_spare[0] = (long)bp;
E 4
I 4
D 40
		bp->av_forw = mfsp->mfs_buflist;
		mfsp->mfs_buflist = bp;
E 40
I 40
D 41
		ap->a_bp->av_forw = mfsp->mfs_buflist;
		mfsp->mfs_buflist = ap->a_bp;
E 41
I 41
D 47
		bp->av_forw = mfsp->mfs_buflist;
E 47
I 47
		bp->b_actf = mfsp->mfs_buflist;
E 47
		mfsp->mfs_buflist = bp;
E 41
E 40
E 4
D 12
		wakeup((caddr_t)bp->b_vp);
E 12
I 12
		wakeup((caddr_t)vp);
E 12
	}
D 3
	error = biowait(bp);
	IUNLOCK(ip);
	return (error);
E 3
I 3
	return (0);
E 3
}
I 39
D 40
#undef bp
E 40
E 39

I 16
D 56
#if defined(vax) || defined(tahoe)
E 56
E 16
/*
 * Memory file system I/O.
 *
D 56
 * Essentially play ubasetup() and disk interrupt service routine by
 * doing the copies to or from the memfs process. If doing physio
 * (i.e. pagein), we must map the I/O through the kernel virtual
 * address space.
 */
I 24
void
E 24
mfs_doio(bp, base)
	register struct buf *bp;
	caddr_t base;
{
I 15
D 16
#if !defined(hp300)
E 16
E 15
	register struct pte *pte, *ppte;
	register caddr_t vaddr;
	int off, npf, npf2, reg;
I 15
D 16
#endif
E 16
E 15
	caddr_t kernaddr, offset;

I 15
D 16
#if defined(hp300)
	kernaddr = bp->b_un.b_addr;
#else
E 16
E 15
	/*
D 53
	 * For phys I/O, map the b_addr into kernel virtual space using
E 53
I 53
	 * For phys I/O, map the b_data into kernel virtual space using
E 53
	 * the Mfsiomap pte's.
	 */
	if ((bp->b_flags & B_PHYS) == 0) {
D 53
		kernaddr = bp->b_un.b_addr;
E 53
I 53
		kernaddr = bp->b_data;
E 53
	} else {
		if (bp->b_flags & (B_PAGET | B_UAREA | B_DIRTY))
			panic("swap on memfs?");
D 53
		off = (int)bp->b_un.b_addr & PGOFSET;
E 53
I 53
		off = (int)bp->b_data & PGOFSET;
E 53
		npf = btoc(bp->b_bcount + off);
		/*
		 * Get some mapping page table entries
		 */
		while ((reg = rmalloc(mfsmap, (long)npf)) == 0) {
			mfsmap_want++;
			sleep((caddr_t)&mfsmap_want, PZERO-1);
		}
		reg--;
D 53
		pte = vtopte(bp->b_proc, btop(bp->b_un.b_addr));
E 53
I 53
		pte = vtopte(bp->b_proc, btop(bp->b_data));
E 53
		/*
		 * Do vmaccess() but with the Mfsiomap page table.
		 */
		ppte = &Mfsiomap[reg];
		vaddr = &mfsiobuf[reg * NBPG];
		kernaddr = vaddr + off;
		for (npf2 = npf; npf2; npf2--) {
			mapin(ppte, (u_int)vaddr, pte->pg_pfnum,
				(int)(PG_V|PG_KW));
#if defined(tahoe)
			if ((bp->b_flags & B_READ) == 0)
				mtpr(P1DC, vaddr);
#endif
			ppte++;
			pte++;
			vaddr += NBPG;
		}
	}
I 15
D 16
#endif /* !defined(hp300) */
E 16
E 15
	offset = base + (bp->b_blkno << DEV_BSHIFT);
	if (bp->b_flags & B_READ)
		bp->b_error = copyin(offset, kernaddr, bp->b_bcount);
	else
		bp->b_error = copyout(kernaddr, offset, bp->b_bcount);
	if (bp->b_error)
		bp->b_flags |= B_ERROR;
I 15
D 16
#if !defined(hp300)
E 16
E 15
	/*
	 * Release pte's used by physical I/O.
	 */
	if (bp->b_flags & B_PHYS) {
		rmfree(mfsmap, (long)npf, (long)++reg);
		if (mfsmap_want) {
			mfsmap_want = 0;
			wakeup((caddr_t)&mfsmap_want);
		}
	}
I 15
D 16
#endif
E 16
E 15
	biodone(bp);
I 10
}
I 16
#endif	/* vax || tahoe */

D 18
#if defined(hp300)
E 18
I 18
D 23
#if defined(hp300) || defined(i386)
E 23
I 23
D 28
#if defined(hp300) || defined(i386) || defined(mips)
E 28
I 28
D 42
#if defined(hp300) || defined(i386) || defined(mips) || defined(sparc)
E 42
I 42
#if defined(hp300) || defined(i386) || defined(mips) || defined(sparc) || defined(luna68k)
E 42
E 28
E 23
E 18
/*
 * Memory file system I/O.
 *
E 56
 * Trivial on the HP since buffer has already been mapping into KVA space.
 */
I 24
void
E 24
mfs_doio(bp, base)
	register struct buf *bp;
	caddr_t base;
{
I 29

E 29
	base += (bp->b_blkno << DEV_BSHIFT);
	if (bp->b_flags & B_READ)
D 53
		bp->b_error = copyin(base, bp->b_un.b_addr, bp->b_bcount);
E 53
I 53
		bp->b_error = copyin(base, bp->b_data, bp->b_bcount);
E 53
	else
D 53
		bp->b_error = copyout(bp->b_un.b_addr, base, bp->b_bcount);
E 53
I 53
		bp->b_error = copyout(bp->b_data, base, bp->b_bcount);
E 53
	if (bp->b_error)
		bp->b_flags |= B_ERROR;
	biodone(bp);
}
D 56
#endif
E 56
E 16

/*
 * This is a noop, simply returning what one has been given.
 */
I 24
int
E 24
D 39
mfs_bmap(vp, bn, vpp, bnp)
	struct vnode *vp;
	daddr_t bn;
	struct vnode **vpp;
	daddr_t *bnp;
E 39
I 39
D 45
mfs_bmap (ap)
	struct vop_bmap_args *ap;
E 45
I 45
mfs_bmap(ap)
	struct vop_bmap_args /* {
		struct vnode *a_vp;
D 59
		daddr_t  a_bn;
E 59
I 59
		ufs_daddr_t  a_bn;
E 59
		struct vnode **a_vpp;
D 59
		daddr_t *a_bnp;
E 59
I 59
		ufs_daddr_t *a_bnp;
E 59
I 48
		int *a_runp;
E 48
	} */ *ap;
E 45
D 40
#define vp (ap->a_vp)
#define bn (ap->a_bn)
#define vpp (ap->a_vpp)
#define bnp (ap->a_bnp)
E 40
E 39
{

D 40
	if (vpp != NULL)
		*vpp = vp;
	if (bnp != NULL)
		*bnp = bn;
E 40
I 40
	if (ap->a_vpp != NULL)
		*ap->a_vpp = ap->a_vp;
	if (ap->a_bnp != NULL)
		*ap->a_bnp = ap->a_bn;
I 57
	if (ap->a_runp != NULL)
		*ap->a_runp = 0;
E 57
E 40
	return (0);
E 10
}
I 39
D 40
#undef vp
#undef bn
#undef vpp
#undef bnp
E 40
E 39

/*
 * Memory filesystem close routine
 */
/* ARGSUSED */
I 24
int
E 24
D 22
mfs_close(vp, flag, cred)
E 22
I 22
D 39
mfs_close(vp, flag, cred, p)
E 22
	register struct vnode *vp;
	int flag;
	struct ucred *cred;
I 22
	struct proc *p;
E 39
I 39
D 45
mfs_close (ap)
	struct vop_close_args *ap;
E 45
I 45
mfs_close(ap)
	struct vop_close_args /* {
		struct vnode *a_vp;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 45
D 40
#define vp (ap->a_vp)
#define flag (ap->a_fflag)
#define cred (ap->a_cred)
#define p (ap->a_p)
E 40
E 39
E 22
{
D 4
	register struct inode *ip = VTOI(vp);
E 4
I 4
D 40
	register struct mfsnode *mfsp = VTOMFS(vp);
E 40
I 40
D 41
	register struct mfsnode *mfsp = VTOMFS(ap->a_vp);
E 41
I 41
	register struct vnode *vp = ap->a_vp;
	register struct mfsnode *mfsp = VTOMFS(vp);
E 41
E 40
I 6
	register struct buf *bp;
I 44
	int error;
E 44
E 6
E 4

	/*
I 6
	 * Finish any pending I/O requests.
	 */
	while (bp = mfsp->mfs_buflist) {
D 47
		mfsp->mfs_buflist = bp->av_forw;
E 47
I 47
		mfsp->mfs_buflist = bp->b_actf;
E 47
		mfs_doio(bp, mfsp->mfs_baseoff);
		wakeup((caddr_t)bp);
	}
	/*
E 6
	 * On last close of a memory filesystem
	 * we must invalidate any in core blocks, so that
	 * we can, free up its vnode.
	 */
D 8
	bflush(vp->v_mount);
	if (binval(vp->v_mount))
E 8
I 8
D 9
	bflush(vp->v_mounton);
	if (binval(vp->v_mounton))
E 9
I 9
D 40
	vflushbuf(vp, 0);
	if (vinvalbuf(vp, 1))
E 40
I 40
D 41
	vflushbuf(ap->a_vp, 0);
	if (vinvalbuf(ap->a_vp, 1))
E 41
I 41
D 44
	vflushbuf(vp, 0);
	if (vinvalbuf(vp, 1))
E 41
E 40
E 9
E 8
		return (0);
E 44
I 44
D 49
	if (error = vinvalbuf(vp, 1, ap->a_cred, ap->a_p))
E 49
I 49
	if (error = vinvalbuf(vp, 1, ap->a_cred, ap->a_p, 0, 0))
E 49
		return (error);
E 44
	/*
D 6
	 * We don't want to really close the device if it is still
	 * in use. Since every use (buffer, inode, swap, cmap)
	 * holds a reference to the vnode, and because we ensure
	 * that there cannot be more than one vnode per device,
	 * we need only check that we are down to the last
	 * reference before closing.
E 6
I 6
	 * There should be no way to have any more uses of this
	 * vnode, so if we find any other uses, it is a panic.
E 6
	 */
D 6
	if (vp->v_count > 1) {
E 6
I 6
D 11
	if (vp->v_count > 1)
E 6
		printf("mfs_close: ref count %d > 1\n", vp->v_count);
D 6
		return (0);
	}
E 6
I 6
	if (vp->v_count > 1 || mfsp->mfs_buflist)
E 11
I 11
D 40
	if (vp->v_usecount > 1)
		printf("mfs_close: ref count %d > 1\n", vp->v_usecount);
	if (vp->v_usecount > 1 || mfsp->mfs_buflist)
E 40
I 40
D 41
	if (ap->a_vp->v_usecount > 1)
		printf("mfs_close: ref count %d > 1\n", ap->a_vp->v_usecount);
	if (ap->a_vp->v_usecount > 1 || mfsp->mfs_buflist)
E 41
I 41
	if (vp->v_usecount > 1)
		printf("mfs_close: ref count %d > 1\n", vp->v_usecount);
	if (vp->v_usecount > 1 || mfsp->mfs_buflist)
E 41
E 40
E 11
		panic("mfs_close");
E 6
	/*
	 * Send a request to the filesystem server to exit.
	 */
D 3
	ILOCK(ip);
	ip->i_spare[0] = 0;
E 3
I 3
D 4
	while (ip->i_spare[0])
E 4
I 4
D 6
	while (mfsp->mfs_buflist)
E 4
		sleep(&lbolt);
E 6
D 4
	ip->i_spare[0] = -1;
E 4
I 4
	mfsp->mfs_buflist = (struct buf *)(-1);
E 4
E 3
D 40
	wakeup((caddr_t)vp);
E 40
I 40
D 41
	wakeup((caddr_t)ap->a_vp);
E 41
I 41
	wakeup((caddr_t)vp);
E 41
E 40
D 3
	IUNLOCK(ip);
E 3
	return (0);
}
I 39
D 40
#undef vp
#undef flag
#undef cred
#undef p
E 40
E 39

/*
I 4
 * Memory filesystem inactive routine
 */
/* ARGSUSED */
I 24
int
E 24
D 22
mfs_inactive(vp)
E 22
I 22
D 39
mfs_inactive(vp, p)
E 22
	struct vnode *vp;
I 22
	struct proc *p;
E 39
I 39
D 45
mfs_inactive (ap)
	struct vop_inactive_args *ap;
E 45
I 45
mfs_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
I 61
		struct proc *a_p;
E 61
	} */ *ap;
E 45
D 40
#define vp (ap->a_vp)
#define p (ap->a_p)
E 40
E 39
E 22
{
I 30
D 40
	register struct mfsnode *mfsp = VTOMFS(vp);
E 40
I 40
D 61
	register struct mfsnode *mfsp = VTOMFS(ap->a_vp);
E 61
I 61
	struct vnode *vp = ap->a_vp;
	struct mfsnode *mfsp = VTOMFS(vp);
E 61
E 40
E 30

D 30
	if (VTOMFS(vp)->mfs_buflist != (struct buf *)(-1))
		panic("mfs_inactive: not inactive");
E 30
I 30
	if (mfsp->mfs_buflist && mfsp->mfs_buflist != (struct buf *)(-1))
		panic("mfs_inactive: not inactive (mfs_buflist %x)",
			mfsp->mfs_buflist);
I 61
	VOP_UNLOCK(vp, 0, ap->a_p);
E 61
E 30
I 26
	return (0);
}
I 39
D 40
#undef vp
#undef p
E 40
E 39

/*
 * Reclaim a memory filesystem devvp so that it can be reused.
 */
int
D 39
mfs_reclaim(vp)
	register struct vnode *vp;
E 39
I 39
D 45
mfs_reclaim (ap)
	struct vop_reclaim_args *ap;
E 45
I 45
mfs_reclaim(ap)
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 45
D 40
#define vp (ap->a_vp)
E 40
E 39
{
I 54
	register struct vnode *vp = ap->a_vp;
E 54

D 40
	FREE(vp->v_data, M_MFSNODE);
	vp->v_data = NULL;
E 40
I 40
D 54
	FREE(ap->a_vp->v_data, M_MFSNODE);
	ap->a_vp->v_data = NULL;
E 54
I 54
	FREE(vp->v_data, M_MFSNODE);
	vp->v_data = NULL;
E 54
E 40
E 26
D 5
	vp->v_type = VNON;
E 5
	return (0);
I 9
}
I 39
D 40
#undef vp
E 40
E 39

/*
 * Print out the contents of an mfsnode.
 */
I 24
int
E 24
D 39
mfs_print(vp)
	struct vnode *vp;
E 39
I 39
D 45
mfs_print (ap)
	struct vop_print_args *ap;
E 45
I 45
mfs_print(ap)
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 45
D 40
#define vp (ap->a_vp)
E 40
E 39
{
D 40
	register struct mfsnode *mfsp = VTOMFS(vp);
E 40
I 40
	register struct mfsnode *mfsp = VTOMFS(ap->a_vp);
E 40

	printf("tag VT_MFS, pid %d, base %d, size %d\n", mfsp->mfs_pid,
		mfsp->mfs_baseoff, mfsp->mfs_size);
I 24
	return (0);
E 24
E 9
}
I 39
D 40
#undef vp
E 40
E 39

/*
E 4
 * Block device bad operation
 */
I 24
int
E 24
mfs_badop()
{

D 4
	printf("mfs_badop called\n");
	return (ENXIO);
E 4
I 4
	panic("mfs_badop called\n");
	/* NOTREACHED */
E 4
D 22
}

/*
 * Block device null operation
 */
mfs_nullop()
{

	return (0);
E 22
}

/*
 * Memory based filesystem initialization.
 */
D 60
mfs_init()
E 60
I 60
mfs_init(vfsp)
	struct vfsconf *vfsp;
E 60
{

I 15
D 18
#if !defined(hp300)
E 18
I 18
D 23
#if !defined(hp300) && !defined(i386)
E 23
I 23
D 28
#if !defined(hp300) && !defined(i386) && !defined(mips)
E 28
I 28
D 42
#if !defined(hp300) && !defined(i386) && !defined(mips) && !defined(sparc)
E 42
I 42
D 56
#if !defined(hp300) && !defined(i386) && !defined(mips) && !defined(sparc) && !defined(luna68k)
E 42
E 28
E 23
E 18
E 15
	rminit(mfsmap, (long)MFS_MAPREG, (long)1, "mfs mapreg", MFS_MAPSIZE);
I 15
#endif
E 56
I 56
	return;
E 56
E 15
}
E 1
