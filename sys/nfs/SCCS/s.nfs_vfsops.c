h09382
s 00020/00015/00885
d D 8.12 95/05/20 01:18:42 mckusick 65 64
c merge vfs_lock and vfs_busy; interlock mount points properly
e
s 00001/00001/00899
d D 8.11 95/05/14 00:33:06 mckusick 64 63
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00048/00044/00852
d D 8.10 95/05/10 12:28:16 mckusick 63 61
c return error rather than panic when mountroot fails; use vfs_rootmountalloc
e
s 00009/00020/00876
d R 8.10 95/05/10 11:54:59 mckusick 62 61
c use vfs_rootmountalloc
e
s 00001/00006/00895
d D 8.9 95/05/10 09:52:57 mckusick 61 60
c check for forcible unmount at syscall level
e
s 00001/00001/00900
d D 8.8 95/05/09 12:17:49 mckusick 60 59
c change mountlist to CIRCLEQ so we can do unmountall (from mycroft)
e
s 00002/00000/00899
d D 8.7 95/05/01 15:44:09 mckusick 59 58
c check for current nfs_args structure
e
s 00014/00008/00885
d D 8.6 95/04/12 13:00:11 mckusick 58 57
c add vfsconf support
e
s 00284/00104/00609
d D 8.5 95/03/30 11:26:38 mckusick 57 55
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00001/00001/00712
d R 8.5 95/02/22 20:14:42 mckusick 56 55
c vgone => VOP_REVOKE
e
s 00001/00002/00712
d D 8.4 94/08/18 23:33:44 mckusick 55 54
c conversion to queue.h list manipulation (from mycroft)
e
s 00001/00003/00713
d D 8.3 94/01/04 22:08:50 bostic 54 53
c lint
e
s 00009/00008/00707
d D 8.2 93/12/30 16:20:15 mckusick 53 52
c new queue structure; vget now locks optionally
e
s 00002/00002/00712
d D 8.1 93/06/10 23:39:21 bostic 52 51
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00006/00713
d D 7.51 93/05/06 13:22:06 mckusick 51 50
c update for pwd bug from Rick Macklem
e
s 00006/00007/00713
d D 7.50 93/04/08 15:17:06 sklower 50 49
c in_sockmaskof has gone away; just do right thing for default.
e
s 00008/00002/00712
d D 7.49 93/02/02 15:21:13 mckusick 49 48
c update for 4.4BSD from Rick Macklem
e
s 00025/00025/00689
d D 7.48 92/10/11 12:35:14 bostic 48 47
c make kernel includes standard
e
s 00001/00001/00713
d D 7.47 92/10/08 00:05:31 mckusick 47 46
c use new queue routines for buffer lists hanging off vnode
e
s 00002/00001/00712
d D 7.46 92/09/22 22:02:27 mckusick 46 45
c rootvp and swapvp now done in ?fs_mountroot
e
s 00010/00004/00703
d D 7.45 92/09/16 18:26:19 mckusick 45 44
c update from Rick Macklem
e
s 00096/00064/00611
d D 7.44 92/07/12 22:55:06 torek 44 43
c move common diskless mount code to subroutine; must set time for arp to work;
c setup for update mount (incomplete); lint
e
s 00012/00004/00663
d D 7.43 92/07/12 11:06:59 mckusick 43 42
c set mnt_maxsymlinklen to a non-zero value so that COMPAT_43 routines 
c will know that we are setting the d_type field in directories (and can zero it 
c for unsuspecting binaries)
e
s 00005/00002/00662
d D 7.42 92/07/06 18:47:49 mckusick 42 41
c new parameters for fhtovp
e
s 00016/00002/00648
d D 7.41 92/07/03 01:55:46 mckusick 41 40
c delete USES; nfs_vget moves from nfs_vnops.c
e
s 00027/00014/00623
d D 7.40 92/06/25 13:14:51 mckusick 40 39
c new parameters to sync plus inline expand mntflushbuf;
c drop setgen parameter from fhtovp
e
s 00001/00029/00636
d D 7.39 92/06/05 16:17:47 pendry 39 38
c use getnewfsid instead of rolling our own
e
s 00014/00002/00651
d D 7.38 92/02/06 18:07:22 mckusick 38 37
c add hostname to diskless header (from Rick Macklem)
e
s 00001/00000/00652
d D 7.37 92/02/03 16:19:33 mckusick 37 36
c have to vgone root vnode to ensure that no vnodes remain on mount point
e
s 00139/00059/00513
d D 7.36 92/01/14 12:41:25 mckusick 36 35
c update from Rick Macklem (including leases)
e
s 00001/00001/00571
d D 7.35 91/12/15 14:49:31 mckusick 35 34
c include file ordering
e
s 00002/00002/00570
d D 7.34 91/12/14 21:12:03 mckusick 34 33
c statfs.f_bsize => statfs.f_iosize; statfs.f_fsize => statfs.f_bsize (for SunOS)
e
s 00003/00004/00569
d D 7.33 91/11/05 16:49:43 mckusick 33 32
c lint
e
s 00001/00001/00572
d D 7.32 91/11/01 16:49:37 bostic 32 31
c rename bufstats to ufs_bufstats
e
s 00000/00002/00573
d D 7.31 91/05/06 10:48:15 karels 31 30
c argdev is gone
e
s 00004/00004/00571
d D 7.30 91/05/04 16:46:03 karels 30 29
c lint
e
s 00003/00003/00572
d D 7.29 91/04/19 17:11:10 mckusick 29 28
c add doforce flag to allow forcible unmount attempts
e
s 00004/00003/00571
d D 7.28 91/04/16 14:48:43 mckusick 28 27
c enable forcible unmount
e
s 00016/00021/00558
d D 7.27 91/04/16 00:45:02 mckusick 27 26
c add proc pointers to appropriate VFS and internal NFS operations
e
s 00003/00003/00576
d D 7.26 91/03/19 11:24:48 karels 26 25
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; consolidate *nullops()
e
s 00135/00006/00444
d D 7.25 91/03/04 22:52:07 mckusick 25 24
c misc fixes plus diskless support from Rick Macklem
e
s 00001/00011/00449
d D 7.24 90/06/28 21:53:01 bostic 24 23
c new copyright notice
e
s 00006/00002/00454
d D 7.23 90/06/21 11:47:08 mckusick 23 22
c "update from Rick Macklem"
e
s 00003/00003/00453
d D 7.22 90/05/18 14:59:05 mckusick 22 21
c "nfs_mknod update from Rick Macklem"
e
s 00069/00012/00387
d D 7.21 90/05/14 11:45:36 mckusick 21 20
c "update from Rick Macklem adding TCP support to NFS"
e
s 00010/00011/00389
d D 7.20 90/05/04 20:52:39 mckusick 20 19
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00022/00003/00378
d D 7.19 90/05/02 19:03:29 mckusick 19 18
c add null nfs_quotactl routine; define vflush flags
e
s 00004/00002/00377
d D 7.18 90/03/20 16:25:53 mckusick 18 17
c avoid multiple free's of mbufs (from tmt@osf and dab@cray)
e
s 00008/00011/00371
d D 7.17 90/03/06 23:35:03 mckusick 17 16
c m_fsid is now m_stat.f_fsid; m_bsize is now m_stat.f_bsize;
c nm_host and nm_path are now found in m_stat
e
s 00000/00005/00382
d D 7.16 90/02/17 10:39:51 mckusick 16 15
c get rid of unneeded header files
e
s 00075/00070/00312
d D 7.15 90/02/16 15:36:17 mckusick 15 14
c socket specific code moves to nfs_socket.c;
c vrele and vput the root vnode only after all errors are checked
e
s 00001/00000/00381
d D 7.14 90/02/08 18:51:40 marc 14 13
c but now it needs buf.h.  see, we should include every header in every file ;)...
e
s 00001/00001/00380
d D 7.13 90/02/08 15:30:34 mckusick 13 12
c missing parameter to mntflushbuf (from noemi@osf.org)
e
s 00030/00000/00351
d D 7.12 90/02/03 17:54:55 mckusick 12 11
c Add code in mountnfs() and nfs_unmount() to hold and release respectively,
c the vnode/nfsnode representing the remote root. If this action is not taken
c and the vnode is dropped from the cache because of heavy activity, there is
c no way to identify the remote root vnode during ".." traversal of the mount
c point. (from gmf@osf.org)
e
s 00031/00048/00320
d D 7.11 89/12/20 18:14:44 mckusick 11 10
c "December update from Rick Macklem"
e
s 00003/00003/00365
d D 7.10 89/11/30 22:49:38 mckusick 10 9
c now use mntflushbuf and mntinvalbuf in place of bflush and binval
e
s 00002/00003/00366
d D 7.9 89/11/10 12:43:38 mckusick 9 8
c nfs_nflush now uses vflush
e
s 00008/00001/00361
d D 7.8 89/11/03 15:30:30 mckusick 8 7
c lint
e
s 00002/00001/00360
d D 7.7 89/10/31 16:56:00 mckusick 7 6
c nothing to do when doing mount update; delete printf
e
s 00003/00001/00358
d D 7.6 89/10/29 23:53:23 mckusick 6 5
c add file system initialization routine
e
s 00003/00003/00356
d D 7.5 89/10/19 22:35:35 mckusick 5 4
c "update from Rick Macklem"
e
s 00025/00014/00334
d D 7.4 89/08/30 20:30:08 macklem 4 3
c first buffer cache implementation; name cache usage; code cleanups
e
s 00014/00000/00334
d D 7.3 89/08/30 19:40:02 mckusick 3 2
c add nfs_start vfs op
e
s 00011/00001/00323
d D 7.2 89/07/06 17:42:35 mckusick 2 1
c update of July 5th from Rick Macklem
e
s 00324/00000/00000
d D 7.1 89/07/05 11:32:26 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 52
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 52
I 52
D 57
 * Copyright (c) 1989, 1993
E 57
I 57
 * Copyright (c) 1989, 1993, 1995
E 57
 *	The Regents of the University of California.  All rights reserved.
E 52
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 24
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
E 24
I 24
 * %sccs.include.redist.c%
E 24
 *
 *	%W% (Berkeley) %G%
 */

D 48
#include "param.h"
I 25
#include "conf.h"
#include "ioctl.h"
E 25
#include "signal.h"
D 26
#include "user.h"
E 26
#include "proc.h"
I 27
#include "namei.h"
E 27
D 16
#include "uio.h"
#include "ucred.h"
I 11
D 15
#include "systm.h"
E 11
D 2
#include "dir.h"
E 2
I 2
#include "../ufs/dir.h"
E 15
I 15
#include "ufs/dir.h"
E 15
E 2
#include "namei.h"
E 16
#include "vnode.h"
I 36
#include "kernel.h"
E 36
#include "mount.h"
D 26
#include "errno.h"
E 26
D 16
#include "malloc.h"
E 16
D 15
#include "mbuf.h"
E 15
I 14
#include "buf.h"
I 15
#include "mbuf.h"
E 15
E 14
D 20
#undef	m_data
E 20
#include "socket.h"
D 15
#include "socketvar.h"
#include "../netinet/in.h"
E 15
I 15
#include "systm.h"
E 48
I 48
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <sys/proc.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/kernel.h>
#include <sys/mount.h>
#include <sys/buf.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
I 57
#include <sys/socketvar.h>
E 57
#include <sys/systm.h>
E 48
I 26

E 26
I 25
D 36
#include "../net/if.h"
#include "../net/route.h"
#include "../netinet/in.h"
E 36
I 36
D 48
#include "net/if.h"
#include "net/route.h"
#include "netinet/in.h"
E 48
I 48
#include <net/if.h>
#include <net/route.h>
#include <netinet/in.h>
E 48
E 36
I 26

I 36
D 48
#include "rpcv2.h"
E 36
E 26
E 25
E 15
#include "nfsv2.h"
I 36
#include "nfsnode.h"
E 36
D 35
#include "nfsnode.h"
E 35
#include "nfsmount.h"
#include "nfs.h"
I 35
D 36
#include "nfsnode.h"
E 36
E 35
I 21
#include "xdr_subs.h"
#include "nfsm_subs.h"
I 25
#include "nfsdiskless.h"
I 36
#include "nqnfs.h"
E 48
I 48
#include <nfs/rpcv2.h>
D 57
#include <nfs/nfsv2.h>
E 57
I 57
#include <nfs/nfsproto.h>
E 57
#include <nfs/nfsnode.h>
D 57
#include <nfs/nfsmount.h>
E 57
#include <nfs/nfs.h>
I 57
#include <nfs/nfsmount.h>
E 57
#include <nfs/xdr_subs.h>
#include <nfs/nfsm_subs.h>
#include <nfs/nfsdiskless.h>
#include <nfs/nqnfs.h>
E 48
E 36
E 25
E 21

I 57
struct nfsstats nfsstats;
static int nfs_sysctl(int *, u_int, void *, size_t *, void *, size_t,
		      struct proc *);
extern int nfs_ticks;

E 57
D 15
#ifndef shouldbe
#include "conf.h"
#endif

E 15
/*
 * nfs vfs operations.
 */
D 27
int nfs_mount();
I 3
int nfs_start();
E 3
int nfs_unmount();
int nfs_root();
I 19
int nfs_quotactl();
E 19
D 6
extern int nfs_statfs();
E 6
I 6
int nfs_statfs();
E 6
int nfs_sync();
int nfs_fhtovp();
int nfs_vptofh();
I 6
int nfs_init();
E 6

E 27
struct vfsops nfs_vfsops = {
	nfs_mount,
I 3
	nfs_start,
E 3
	nfs_unmount,
	nfs_root,
I 19
	nfs_quotactl,
E 19
	nfs_statfs,
	nfs_sync,
I 41
	nfs_vget,
E 41
	nfs_fhtovp,
	nfs_vptofh,
I 6
	nfs_init,
I 57
	nfs_sysctl
E 57
E 6
};

I 36
/*
 * This structure must be filled in by a primary bootstrap or bootstrap
 * server for a diskless/dataless machine. It is initialized below just
 * to ensure that it is allocated to initialized data (.data not .bss).
 */
struct nfs_diskless nfs_diskless = { 0 };
I 57
int nfs_diskless_valid = 0;
E 57

E 36
D 15
extern struct nfsreq nfsreqh;
E 15
D 11
static long nfs_mntid;
E 11
I 11
D 54
static u_char nfs_mntid;
E 54
I 21
D 57
extern u_long nfs_procids[NFS_NPROCS];
extern u_long nfs_prog, nfs_vers;
E 57
I 25
D 36
struct nfs_diskless nfs_diskless;
E 25
void nfs_disconnect();
E 36
I 36
D 44
void nfs_disconnect(), nfsargs_ntoh();
E 44
I 44
void nfs_disconnect __P((struct nfsmount *));
void nfsargs_ntoh __P((struct nfs_args *));
I 57
int nfs_fsinfo __P((struct nfsmount *, struct vnode *, struct ucred *, 
	struct proc *));
E 57
D 63
static struct mount *nfs_mountdiskless __P((char *, char *, int,
    struct sockaddr_in *, struct nfs_args *, register struct vnode **));
E 63
I 63
static int nfs_mountdiskless __P((char *, char *, int, struct sockaddr_in *,
D 65
	struct nfs_args *, struct vnode **, struct mount **));
E 65
I 65
	struct nfs_args *, struct proc *, struct vnode **, struct mount **));
E 65
E 63
E 44
E 36
E 21
E 11

I 21
D 57
#define TRUE	1
#define	FALSE	0

E 57
E 21
/*
I 21
 * nfs statfs call
 */
I 44
int
E 44
D 27
nfs_statfs(mp, sbp)
E 27
I 27
nfs_statfs(mp, sbp, p)
E 27
	struct mount *mp;
	register struct statfs *sbp;
I 27
	struct proc *p;
E 27
{
	register struct vnode *vp;
D 57
	register struct nfsv2_statfs *sfp;
E 57
I 57
	register struct nfs_statfs *sfp;
E 57
	register caddr_t cp;
D 57
	register long t1;
E 57
I 57
	register u_long *tl;
	register long t1, t2;
E 57
	caddr_t bpos, dpos, cp2;
D 44
	u_long xid;
E 44
D 45
	int error = 0;
E 45
I 45
D 57
	int error = 0, isnq;
E 57
I 57
	struct nfsmount *nmp = VFSTONFS(mp);
	int error = 0, v3 = (nmp->nm_flag & NFSMNT_NFSV3), retattr;
E 57
E 45
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
D 57
	struct nfsmount *nmp;
E 57
	struct ucred *cred;
	struct nfsnode *np;
I 57
	u_quad_t tquad;
E 57

D 57
	nmp = VFSTONFS(mp);
I 45
	isnq = (nmp->nm_flag & NFSMNT_NQNFS);
E 45
	if (error = nfs_nget(mp, &nmp->nm_fh, &np))
E 57
I 57
#ifndef nolint
	sfp = (struct nfs_statfs *)0;
#endif
	error = nfs_nget(mp, (nfsfh_t *)nmp->nm_fh, nmp->nm_fhsize, &np);
	if (error)
E 57
		return (error);
	vp = NFSTOV(np);
D 57
	nfsstats.rpccnt[NFSPROC_STATFS]++;
E 57
	cred = crget();
	cred->cr_ngroups = 1;
D 36
	nfsm_reqhead(nfs_procids[NFSPROC_STATFS], cred, NFSX_FH);
E 36
I 36
D 57
	nfsm_reqhead(vp, NFSPROC_STATFS, NFSX_FH);
E 36
	nfsm_fhtom(vp);
D 23
	nfsm_request(vp, NFSPROC_STATFS, u.u_procp);
E 23
I 23
D 26
	nfsm_request(vp, NFSPROC_STATFS, u.u_procp, 0);
E 26
I 26
D 27
	nfsm_request(vp, NFSPROC_STATFS, curproc, 0);
E 27
I 27
D 36
	nfsm_request(vp, NFSPROC_STATFS, p, 0);
E 27
E 26
E 23
	nfsm_disect(sfp, struct nfsv2_statfs *, NFSX_STATFS);
E 36
I 36
	nfsm_request(vp, NFSPROC_STATFS, p, cred);
D 45
	nfsm_dissect(sfp, struct nfsv2_statfs *, NFSX_STATFS);
E 45
I 45
	nfsm_dissect(sfp, struct nfsv2_statfs *, NFSX_STATFS(isnq));
E 45
E 36
	sbp->f_type = MOUNT_NFS;
	sbp->f_flags = nmp->nm_flag;
D 34
	sbp->f_bsize = fxdr_unsigned(long, sfp->sf_tsize);
	sbp->f_fsize = fxdr_unsigned(long, sfp->sf_bsize);
E 34
I 34
D 36
	sbp->f_iosize = fxdr_unsigned(long, sfp->sf_tsize);
E 36
I 36
	sbp->f_iosize = NFS_MAXDGRAMDATA;
E 36
	sbp->f_bsize = fxdr_unsigned(long, sfp->sf_bsize);
E 34
	sbp->f_blocks = fxdr_unsigned(long, sfp->sf_blocks);
	sbp->f_bfree = fxdr_unsigned(long, sfp->sf_bfree);
	sbp->f_bavail = fxdr_unsigned(long, sfp->sf_bavail);
D 45
	sbp->f_files = 0;
	sbp->f_ffree = 0;
E 45
I 45
	if (isnq) {
		sbp->f_files = fxdr_unsigned(long, sfp->sf_files);
		sbp->f_ffree = fxdr_unsigned(long, sfp->sf_ffree);
E 57
I 57
	if (v3 && (nmp->nm_flag & NFSMNT_GOTFSINFO) == 0)
		(void)nfs_fsinfo(nmp, vp, cred, p);
	nfsstats.rpccnt[NFSPROC_FSSTAT]++;
	nfsm_reqhead(vp, NFSPROC_FSSTAT, NFSX_FH(v3));
	nfsm_fhtom(vp, v3);
	nfsm_request(vp, NFSPROC_FSSTAT, p, cred);
	if (v3)
		nfsm_postop_attr(vp, retattr);
	if (!error)
		nfsm_dissect(sfp, struct nfs_statfs *, NFSX_STATFS(v3));
	sbp->f_iosize = min(nmp->nm_rsize, nmp->nm_wsize);
	if (v3) {
		sbp->f_bsize = NFS_FABLKSIZE;
		fxdr_hyper(&sfp->sf_tbytes, &tquad);
		sbp->f_blocks = (long)(tquad / ((u_quad_t)NFS_FABLKSIZE));
		fxdr_hyper(&sfp->sf_fbytes, &tquad);
		sbp->f_bfree = (long)(tquad / ((u_quad_t)NFS_FABLKSIZE));
		fxdr_hyper(&sfp->sf_abytes, &tquad);
		sbp->f_bavail = (long)(tquad / ((u_quad_t)NFS_FABLKSIZE));
		sbp->f_files = (fxdr_unsigned(long, sfp->sf_tfiles.nfsuquad[1])
			& 0x7fffffff);
		sbp->f_ffree = (fxdr_unsigned(long, sfp->sf_ffiles.nfsuquad[1])
			& 0x7fffffff);
E 57
	} else {
I 57
		sbp->f_bsize = fxdr_unsigned(long, sfp->sf_bsize);
		sbp->f_blocks = fxdr_unsigned(long, sfp->sf_blocks);
		sbp->f_bfree = fxdr_unsigned(long, sfp->sf_bfree);
		sbp->f_bavail = fxdr_unsigned(long, sfp->sf_bavail);
E 57
		sbp->f_files = 0;
		sbp->f_ffree = 0;
	}
E 45
	if (sbp != &mp->mnt_stat) {
		bcopy(mp->mnt_stat.f_mntonname, sbp->f_mntonname, MNAMELEN);
		bcopy(mp->mnt_stat.f_mntfromname, sbp->f_mntfromname, MNAMELEN);
	}
	nfsm_reqdone;
D 36
	nfs_nput(vp);
E 36
I 36
	vrele(vp);
E 36
	crfree(cred);
	return (error);
}

/*
I 57
 * nfs version 3 fsinfo rpc call
 */
int
nfs_fsinfo(nmp, vp, cred, p)
	register struct nfsmount *nmp;
	register struct vnode *vp;
	struct ucred *cred;
	struct proc *p;
{
	register struct nfsv3_fsinfo *fsp;
	register caddr_t cp;
	register long t1, t2;
	register u_long *tl, pref, max;
	caddr_t bpos, dpos, cp2;
	int error = 0, retattr;
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;

	nfsstats.rpccnt[NFSPROC_FSINFO]++;
	nfsm_reqhead(vp, NFSPROC_FSINFO, NFSX_FH(1));
	nfsm_fhtom(vp, 1);
	nfsm_request(vp, NFSPROC_FSINFO, p, cred);
	nfsm_postop_attr(vp, retattr);
	if (!error) {
		nfsm_dissect(fsp, struct nfsv3_fsinfo *, NFSX_V3FSINFO);
		pref = fxdr_unsigned(u_long, fsp->fs_wtpref);
		if (pref < nmp->nm_wsize)
			nmp->nm_wsize = (pref + NFS_FABLKSIZE - 1) &
				~(NFS_FABLKSIZE - 1);
		max = fxdr_unsigned(u_long, fsp->fs_wtmax);
		if (max < nmp->nm_wsize) {
			nmp->nm_wsize = max & ~(NFS_FABLKSIZE - 1);
			if (nmp->nm_wsize == 0)
				nmp->nm_wsize = max;
		}
		pref = fxdr_unsigned(u_long, fsp->fs_rtpref);
		if (pref < nmp->nm_rsize)
			nmp->nm_rsize = (pref + NFS_FABLKSIZE - 1) &
				~(NFS_FABLKSIZE - 1);
		max = fxdr_unsigned(u_long, fsp->fs_rtmax);
		if (max < nmp->nm_rsize) {
			nmp->nm_rsize = max & ~(NFS_FABLKSIZE - 1);
			if (nmp->nm_rsize == 0)
				nmp->nm_rsize = max;
		}
		pref = fxdr_unsigned(u_long, fsp->fs_dtpref);
		if (pref < nmp->nm_readdirsize)
			nmp->nm_readdirsize = (pref + NFS_DIRBLKSIZ - 1) &
				~(NFS_DIRBLKSIZ - 1);
		if (max < nmp->nm_readdirsize) {
			nmp->nm_readdirsize = max & ~(NFS_DIRBLKSIZ - 1);
			if (nmp->nm_readdirsize == 0)
				nmp->nm_readdirsize = max;
		}
		nmp->nm_flag |= NFSMNT_GOTFSINFO;
	}
	nfsm_reqdone;
	return (error);
}

/*
E 57
E 21
D 25
 * Called by vfs_mountroot when nfs is going to be mounted as root
 * Not Yet (By a LONG shot)
E 25
I 25
 * Mount a remote root fs via. nfs. This depends on the info in the
 * nfs_diskless structure that has been filled in properly by some primary
 * bootstrap.
 * It goes something like this:
 * - do enough of "ifconfig" by calling ifioctl() so that the system
 *   can talk to the server
 * - If nfs_diskless.mygateway is filled in, use that address as
 *   a default gateway.
D 36
 *   (This is done the 4.3 way with rtioctl() and should be changed)
E 36
 * - hand craft the swap nfs vnode hanging off a fake mount point
I 36
 *	if swdevt[0].sw_dev == NODEV
E 36
 * - build the rootfs mount point and call mountnfs() to do the rest.
E 25
 */
I 44
int
E 44
nfs_mountroot()
{
D 25
	return (ENODEV);
E 25
I 25
D 63
	register struct mount *mp;
D 44
	register struct mbuf *m;
E 44
I 44
	register struct nfs_diskless *nd = &nfs_diskless;
E 63
I 63
D 65
	struct mount *mp;
E 65
I 65
	struct mount *mp, *swap_mp;
E 65
	struct nfs_diskless *nd = &nfs_diskless;
E 63
E 44
	struct socket *so;
	struct vnode *vp;
I 44
	struct proc *p = curproc;		/* XXX */
E 44
D 38
	int error;
E 38
I 38
D 50
	int error, i;
E 50
I 50
D 54
	int error, i, s;
E 54
I 54
	int error, i;
I 57
	u_long l;
	char buf[128];
E 57
E 54
E 50
E 38

	/*
I 44
	 * XXX time must be non-zero when we init the interface or else
	 * the arp code will wedge...
	 */
	if (time.tv_sec == 0)
		time.tv_sec = 1;

I 57
	/* 
	 * XXX splnet, so networks will receive...
	 */
	splnet();

E 57
#ifdef notyet
	/* Set up swap credentials. */
D 49
	*proc0.p_ucred = nfs_diskless.swap_ucred;
E 49
I 49
	proc0.p_ucred->cr_uid = ntohl(nd->swap_ucred.cr_uid);
	proc0.p_ucred->cr_gid = ntohl(nd->swap_ucred.cr_gid);
	if ((proc0.p_ucred->cr_ngroups = ntohs(nd->swap_ucred.cr_ngroups)) >
		NGROUPS)
		proc0.p_ucred->cr_ngroups = NGROUPS;
	for (i = 0; i < proc0.p_ucred->cr_ngroups; i++)
	    proc0.p_ucred->cr_groups[i] = ntohl(nd->swap_ucred.cr_groups[i]);
E 49
#endif

	/*
E 44
D 36
	 * Do enough of ifconfig(8) so that critical net interface can
E 36
I 36
	 * Do enough of ifconfig(8) so that the critical net interface can
E 36
	 * talk to the server.
	 */
D 44
	if (socreate(nfs_diskless.myif.ifra_addr.sa_family, &so, SOCK_DGRAM, 0))
		panic("nfs ifconf");
D 38
	if (ifioctl(so, SIOCAIFADDR, &nfs_diskless.myif))
E 38
I 38
	if (ifioctl(so, SIOCAIFADDR, &nfs_diskless.myif, curproc)) /* XXX */
E 38
		panic("nfs ifconf2");
E 44
I 44
D 57
	if (error = socreate(nd->myif.ifra_addr.sa_family, &so, SOCK_DGRAM, 0))
		panic("nfs_mountroot: socreate: %d", error);
	if (error = ifioctl(so, SIOCAIFADDR, (caddr_t)&nd->myif, p))
E 57
I 57
	error = socreate(nd->myif.ifra_addr.sa_family, &so, SOCK_DGRAM, 0);
D 63
	if (error)
		panic("nfs_mountroot: socreate(%04x): %d",
E 63
I 63
	if (error) {
		printf("nfs_mountroot: socreate(%04x): %d",
E 63
			nd->myif.ifra_addr.sa_family, error);
I 63
		return (error);
	}
E 63

	/*
	 * We might not have been told the right interface, so we pass
	 * over the first ten interfaces of the same kind, until we get
	 * one of them configured.
	 */

	for (i = strlen(nd->myif.ifra_name) - 1;
		nd->myif.ifra_name[i] >= '0' && 
		nd->myif.ifra_name[i] <= '9';
		nd->myif.ifra_name[i] ++) {
		error = ifioctl(so, SIOCAIFADDR, (caddr_t)&nd->myif, p);
		if(!error) 
			break;
	}
D 63
	if (error)
E 57
		panic("nfs_mountroot: SIOCAIFADDR: %d", error);
E 63
I 63
	if (error) {
		printf("nfs_mountroot: SIOCAIFADDR: %d", error);
		return (error);
	}
E 63
E 44
	soclose(so);

	/*
	 * If the gateway field is filled in, set it as the default route.
	 */
D 36
#ifdef COMPAT_43
	if (nfs_diskless.mygateway.sa_family == AF_INET) {
		struct ortentry rt;
		struct sockaddr_in *sin;
E 36
I 36
D 44
	if (nfs_diskless.mygateway.sin_len != 0) {
E 44
I 44
	if (nd->mygateway.sin_len != 0) {
E 44
D 50
		struct sockaddr_in sin;
		extern struct sockaddr_in icmpmask;
E 50
I 50
		struct sockaddr_in mask, sin;
E 50
E 36

D 36
		sin = (struct sockaddr_in *) &rt.rt_dst;
		sin->sin_len = sizeof (struct sockaddr_in);
		sin->sin_family = AF_INET;
		sin->sin_addr.s_addr = 0;	/* default */
		bcopy((caddr_t)&nfs_diskless.mygateway, (caddr_t)&rt.rt_gateway,
			sizeof (struct sockaddr_in));
		rt.rt_flags = (RTF_UP | RTF_GATEWAY);
		if (rtioctl(SIOCADDRT, (caddr_t)&rt))
E 36
I 36
D 50
		sin.sin_len = sizeof (struct sockaddr_in);
E 50
I 50
		bzero((caddr_t)&mask, sizeof(mask));
		sin = mask;
E 50
		sin.sin_family = AF_INET;
D 50
		sin.sin_addr.s_addr = 0;	/* default */
		in_sockmaskof(sin.sin_addr, &icmpmask);
E 50
I 50
		sin.sin_len = sizeof(sin);
E 50
D 44
		if (rtrequest(RTM_ADD, (struct sockaddr *)&sin,
			(struct sockaddr *)&nfs_diskless.mygateway,
			(struct sockaddr *)&icmpmask,
			RTF_UP | RTF_GATEWAY, (struct rtentry **)0))
E 36
			panic("nfs root route");
E 44
I 44
D 57
		if (error = rtrequest(RTM_ADD, (struct sockaddr *)&sin,
E 57
I 57
		error = rtrequest(RTM_ADD, (struct sockaddr *)&sin,
E 57
		    (struct sockaddr *)&nd->mygateway,
D 50
		    (struct sockaddr *)&icmpmask,
E 50
I 50
		    (struct sockaddr *)&mask,
E 50
D 57
		    RTF_UP | RTF_GATEWAY, (struct rtentry **)0))
E 57
I 57
		    RTF_UP | RTF_GATEWAY, (struct rtentry **)0);
D 63
		if (error)
E 57
			panic("nfs_mountroot: RTM_ADD: %d", error);
E 63
I 63
		if (error) {
			printf("nfs_mountroot: RTM_ADD: %d", error);
			return (error);
		}
E 63
E 44
	}
D 36
#endif	/* COMPAT_43 */
E 36

I 65
	swap_mp = NULL;
E 65
D 57
	/*
	 * If swapping to an nfs node (indicated by swdevt[0].sw_dev == NODEV):
	 * Create a fake mount point just for the swap vnode so that the
	 * swap file can be on a different server from the rootfs.
	 */
	if (swdevt[0].sw_dev == NODEV) {
D 44
		mp = (struct mount *)malloc((u_long)sizeof(struct mount),
			M_MOUNT, M_NOWAIT);
		if (mp == NULL)
			panic("nfs root mount");
		mp->mnt_op = &nfs_vfsops;
		mp->mnt_flag = 0;
D 36
		mp->mnt_exroot = 0;
E 36
		mp->mnt_mounth = NULLVP;
E 44
I 44
		nd->swap_args.fh = (nfsv2fh_t *)nd->swap_fh;
		(void) nfs_mountdiskless(nd->swap_hostnam, "/swap", 0,
E 57
I 57
	if (nd->swap_nblks) {
		/*
		 * Create a fake mount point just for the swap vnode so that the
		 * swap file can be on a different server from the rootfs.
		 */
		nd->swap_args.fh = nd->swap_fh;
		/*
		 * If using nfsv3_diskless, replace NFSX_V2FH with
		 * nd->swap_fhsize.
		 */
		nd->swap_args.fhsize = NFSX_V2FH;
		l = ntohl(nd->swap_saddr.sin_addr.s_addr);
		sprintf(buf,"%ld.%ld.%ld.%ld:%s",
			(l >> 24) & 0xff, (l >> 16) & 0xff,
			(l >>  8) & 0xff, (l >>  0) & 0xff,nd->swap_hostnam);
		printf("NFS SWAP: %s\n",buf);
D 63
		(void) nfs_mountdiskless(buf, "/swap", 0,
E 57
		    &nd->swap_saddr, &nd->swap_args, &vp);
E 63
I 63
		if (error = nfs_mountdiskless(buf, "/swap", 0,
D 65
		    &nd->swap_saddr, &nd->swap_args, &vp, &mp))
E 65
I 65
		    &nd->swap_saddr, &nd->swap_args, p, &vp, &swap_mp))
E 65
			return (error);
I 65
		vfs_unbusy(swap_mp, p);
E 65
E 63
E 44
D 57
	
E 57
I 57

		for (i=0;swdevt[i].sw_dev != NODEV;i++) ;

E 57
		/*
D 44
		 * Set up the diskless nfs_args for the swap mount point
		 * and then call mountnfs() to mount it.
E 44
		 * Since the swap file is not the root dir of a file system,
		 * hack it to a regular file.
		 */
D 44
		nfs_diskless.swap_args.fh = (nfsv2fh_t *)nfs_diskless.swap_fh;
		MGET(m, MT_SONAME, M_DONTWAIT);
		if (m == NULL)
			panic("nfs root mbuf");
		bcopy((caddr_t)&nfs_diskless.swap_saddr, mtod(m, caddr_t),
D 36
			nfs_diskless.swap_saddr.sa_len);
		m->m_len = nfs_diskless.swap_saddr.sa_len;
E 36
I 36
			nfs_diskless.swap_saddr.sin_len);
		m->m_len = (int)nfs_diskless.swap_saddr.sin_len;
		nfsargs_ntoh(&nfs_diskless.swap_args);
E 36
		if (mountnfs(&nfs_diskless.swap_args, mp, m, "/swap",
			nfs_diskless.swap_hostnam, &vp))
			panic("nfs swap");
E 44
		vp->v_type = VREG;
		vp->v_flag = 0;
		swapdev_vp = vp;
		VREF(vp);
D 57
		swdevt[0].sw_vp = vp;
I 36
D 44
		swdevt[0].sw_nblks = ntohl(nfs_diskless.swap_nblks);
E 44
I 44
		swdevt[0].sw_nblks = ntohl(nd->swap_nblks);
E 44
E 36
D 31
		VREF(vp);
		argdev_vp = vp;
E 31
D 46
	}
E 46
I 46
	} else if (bdevvp(swapdev, &swapdev_vp))
		panic("nfs_mountroot: can't setup swapdev_vp");
E 57
I 57
		swdevt[i].sw_vp = vp;
		swdevt[i].sw_nblks = nd->swap_nblks*2;
E 57
E 46

I 57
		if (!swdevt[i].sw_nblks) {
			swdevt[i].sw_nblks = 2048;
			printf("defaulting to %d kbyte.\n",
				swdevt[i].sw_nblks/2);
		} else
			printf("using %d kbyte.\n",swdevt[i].sw_nblks/2);
	}

E 57
	/*
	 * Create the rootfs mount point.
	 */
D 44
	mp = (struct mount *)malloc((u_long)sizeof(struct mount),
		M_MOUNT, M_NOWAIT);
	if (mp == NULL)
		panic("nfs root mount2");
	mp->mnt_op = &nfs_vfsops;
	mp->mnt_flag = MNT_RDONLY;
D 36
	mp->mnt_exroot = 0;
E 36
	mp->mnt_mounth = NULLVP;
E 44
I 44
D 57
	nd->root_args.fh = (nfsv2fh_t *)nd->root_fh;
	mp = nfs_mountdiskless(nd->root_hostnam, "/", MNT_RDONLY,
E 57
I 57
	nd->root_args.fh = nd->root_fh;
	/*
	 * If using nfsv3_diskless, replace NFSX_V2FH with nd->root_fhsize.
	 */
	nd->root_args.fhsize = NFSX_V2FH;
	l = ntohl(nd->swap_saddr.sin_addr.s_addr);
	sprintf(buf,"%ld.%ld.%ld.%ld:%s",
		(l >> 24) & 0xff, (l >> 16) & 0xff,
		(l >>  8) & 0xff, (l >>  0) & 0xff,nd->root_hostnam);
	printf("NFS ROOT: %s\n",buf);
D 63
	mp = nfs_mountdiskless(buf, "/", MNT_RDONLY,
E 57
	    &nd->root_saddr, &nd->root_args, &vp);
E 63
I 63
	if (error = nfs_mountdiskless(buf, "/", MNT_RDONLY,
D 65
	    &nd->root_saddr, &nd->root_args, &vp, &mp))
E 65
I 65
	    &nd->root_saddr, &nd->root_args, p, &vp, &mp)) {
		if (swap_mp) {
			mp->mnt_vfc->vfc_refcount--;
			free(swap_mp, M_MOUNT);
		}
E 65
		return (error);
E 63
E 44
D 65

D 44
	/*
	 * Set up the root fs args and call mountnfs() to do the rest.
	 */
	nfs_diskless.root_args.fh = (nfsv2fh_t *)nfs_diskless.root_fh;
	MGET(m, MT_SONAME, M_DONTWAIT);
	if (m == NULL)
		panic("nfs root mbuf2");
	bcopy((caddr_t)&nfs_diskless.root_saddr, mtod(m, caddr_t),
D 36
		nfs_diskless.root_saddr.sa_len);
	m->m_len = nfs_diskless.root_saddr.sa_len;
E 36
I 36
		nfs_diskless.root_saddr.sin_len);
	m->m_len = (int)nfs_diskless.root_saddr.sin_len;
	nfsargs_ntoh(&nfs_diskless.root_args);
E 36
	if (mountnfs(&nfs_diskless.root_args, mp, m, "/",
		nfs_diskless.root_hostnam, &vp))
		panic("nfs root");
E 44
D 63
	if (vfs_lock(mp))
D 44
		panic("nfs root2");
E 44
I 44
		panic("nfs_mountroot: vfs_lock");
E 63
I 63
	if (error = vfs_lock(mp)) {
		printf("nfs_mountroot: vfs_lock");
		return (error);
E 65
	}
I 65

	simple_lock(&mountlist_slock);
E 65
E 63
E 44
D 53
	rootfs = mp;
	mp->mnt_next = mp;
	mp->mnt_prev = mp;
E 53
I 53
D 60
	TAILQ_INSERT_TAIL(&mountlist, mp, mnt_list);
E 60
I 60
	CIRCLEQ_INSERT_TAIL(&mountlist, mp, mnt_list);
E 60
D 61
	mp->mnt_flag |= MNT_ROOTFS;
E 61
E 53
D 63
	mp->mnt_vnodecovered = NULLVP;
E 63
D 65
	vfs_unlock(mp);
E 65
I 65
	simple_unlock(&mountlist_slock);
E 65
	rootvp = vp;
I 65
	vfs_unbusy(mp, p);
E 65
I 38

	/*
	 * This is not really an nfs issue, but it is much easier to
	 * set hostname here and then let the "/etc/rc.xxx" files
	 * mount the right /var based upon its preset value.
	 */
D 44
	bcopy(nfs_diskless.my_hostnam, hostname, MAXHOSTNAMELEN);
E 44
I 44
	bcopy(nd->my_hostnam, hostname, MAXHOSTNAMELEN);
E 44
	hostname[MAXHOSTNAMELEN - 1] = '\0';
	for (i = 0; i < MAXHOSTNAMELEN; i++)
		if (hostname[i] == '\0')
			break;
	hostnamelen = i;
E 38
D 44
	inittodr((time_t)0);	/* There is no time in the nfs fsstat so ?? */
E 44
I 44
D 49
	inittodr(nfs_diskless.root_time);
E 49
I 49
	inittodr(ntohl(nd->root_time));
E 49
E 44
	return (0);
E 25
}

/*
I 44
 * Internal version of mount system call for diskless setup.
 */
D 63
static struct mount *
nfs_mountdiskless(path, which, mountflag, sin, args, vpp)
E 63
I 63
static int
D 65
nfs_mountdiskless(path, which, mountflag, sin, args, vpp, mpp)
E 65
I 65
nfs_mountdiskless(path, which, mountflag, sin, args, p, vpp, mpp)
E 65
E 63
	char *path;
	char *which;
	int mountflag;
	struct sockaddr_in *sin;
	struct nfs_args *args;
I 65
	struct proc *p;
E 65
D 63
	register struct vnode **vpp;
E 63
I 63
	struct vnode **vpp;
	struct mount **mpp;
E 63
{
D 63
	register struct mount *mp;
	register struct mbuf *m;
	register int error;
I 58
	struct vfsconf *vfsp;
E 63
I 63
	struct mount *mp;
	struct mbuf *m;
	int error;
E 63
E 58

D 58
	mp = (struct mount *)malloc((u_long)sizeof(struct mount),
	    M_MOUNT, M_NOWAIT);
	if (mp == NULL)
		panic("nfs_mountroot: %s mount malloc", which);
E 58
I 58
D 63
	for (vfsp = vfsconf; vfsp; vfsp = vfsp->vfc_next)
		if (!strcmp(vfsp->vfc_name, "nfs"))
			break;
	if (vfsp == NULL)
		panic("nfs_mountroot: NFS not configured");
	mp = malloc((u_long)sizeof(struct mount), M_MOUNT, M_WAITOK);
E 58
I 53
	bzero((char *)mp, (u_long)sizeof(struct mount));
E 53
D 58
	mp->mnt_op = &nfs_vfsops;
E 58
I 58
	mp->mnt_vfc = vfsp;
	mp->mnt_op = vfsp->vfc_vfsops;
E 63
I 63
	if (error = vfs_rootmountalloc("nfs", path, &mp)) {
		printf("nfs_mountroot: NFS not configured");
		return (error);
	}
E 63
E 58
	mp->mnt_flag = mountflag;
D 53
	mp->mnt_mounth = NULLVP;
E 53
D 58

E 58
D 65
	MGET(m, MT_SONAME, M_DONTWAIT);
D 63
	if (m == NULL)
		panic("nfs_mountroot: %s mount mbuf", which);
E 63
I 63
	if (m == NULL) {
		printf("nfs_mountroot: %s mount mbuf", which);
		return (error);
	}
E 65
I 65
	MGET(m, MT_SONAME, M_WAITOK);
E 65
E 63
	bcopy((caddr_t)sin, mtod(m, caddr_t), sin->sin_len);
	m->m_len = sin->sin_len;
D 57
	nfsargs_ntoh(args);
	if (error = mountnfs(args, mp, m, which, path, vpp))
E 57
I 57
D 58
	error = mountnfs(args, mp, m, which, path, vpp);
	if (error)
E 58
I 58
D 63
	if (error = mountnfs(args, mp, m, which, path, vpp))
E 58
E 57
		panic("nfs_mountroot: mount %s on %s: %d", path, which, error);
I 58
	vfsp->vfc_refcount++;
	mp->mnt_stat.f_type = vfsp->vfc_typenum;
	mp->mnt_flag |= (vfsp->vfc_flags & MNT_VISFLAGMASK) | MNT_ROOTFS;
	strncpy(mp->mnt_stat.f_fstypename, vfsp->vfc_name, MFSNAMELEN);
E 58

	return (mp);
E 63
I 63
	if (error = mountnfs(args, mp, m, which, path, vpp)) {
		printf("nfs_mountroot: mount %s on %s: %d", path, which, error);
I 65
		mp->mnt_vfc->vfc_refcount--;
		vfs_unbusy(mp, p);
		free(mp, M_MOUNT);
E 65
		return (error);
	}
	(void) copystr(which, mp->mnt_stat.f_mntonname, MNAMELEN - 1, 0);
	*mpp = mp;
	return (0);
E 63
}
D 63

E 63
D 57
/*
E 44
I 36
 * Convert the integer fields of the nfs_args structure from net byte order
 * to host byte order. Called by nfs_mountroot() above.
 */
void
nfsargs_ntoh(nfsp)
	register struct nfs_args *nfsp;
{
E 57

D 57
	NTOHL(nfsp->sotype);
	NTOHL(nfsp->proto);
	NTOHL(nfsp->flags);
	NTOHL(nfsp->wsize);
	NTOHL(nfsp->rsize);
	NTOHL(nfsp->timeo);
	NTOHL(nfsp->retrans);
	NTOHL(nfsp->maxgrouplist);
	NTOHL(nfsp->readahead);
	NTOHL(nfsp->leaseterm);
	NTOHL(nfsp->deadthresh);
}

E 57
/*
E 36
 * VFS Operations.
 *
 * mount system call
 * It seems a bit dumb to copyinstr() the host and path here and then
 * bcopy() them in mountnfs(), but I wanted to detect errors before
 * doing the sockargs() call because sockargs() allocates an mbuf and
 * an error after that means that I have to release the mbuf.
 */
I 8
/* ARGSUSED */
I 44
int
E 44
E 8
D 27
nfs_mount(mp, path, data, ndp)
E 27
I 27
nfs_mount(mp, path, data, ndp, p)
E 27
	struct mount *mp;
	char *path;
	caddr_t data;
	struct nameidata *ndp;
I 27
	struct proc *p;
E 27
{
	int error;
	struct nfs_args args;
D 21
	struct mbuf *saddr;
E 21
I 21
	struct mbuf *nam;
I 25
	struct vnode *vp;
E 25
E 21
	char pth[MNAMELEN], hst[MNAMELEN];
D 30
	int len;
E 30
I 30
	u_int len;
E 30
D 57
	nfsv2fh_t nfh;
E 57
I 57
	u_char nfh[NFSX_V3FHMAX];
E 57

I 7
D 20
	if (mp->m_flag & M_UPDATE)
E 20
I 20
D 44
	if (mp->mnt_flag & MNT_UPDATE)
E 20
		return (0);
E 44
E 7
D 57
	if (error = copyin(data, (caddr_t)&args, sizeof (struct nfs_args)))
E 57
I 57
	error = copyin(data, (caddr_t)&args, sizeof (struct nfs_args));
	if (error)
E 57
		return (error);
I 59
	if (args.version != NFS_ARGSVERSION)
		return (EPROGMISMATCH);
E 59
D 30
	if (error=copyin((caddr_t)args.fh, (caddr_t)&nfh, sizeof (nfsv2fh_t)))
E 30
I 30
D 57
	if (error = copyin((caddr_t)args.fh, (caddr_t)&nfh, sizeof (nfsv2fh_t)))
E 57
I 57
	error = copyin((caddr_t)args.fh, (caddr_t)nfh, args.fhsize);
	if (error)
E 57
E 30
		return (error);
D 57
	if (error = copyinstr(path, pth, MNAMELEN-1, &len))
E 57
I 57
	error = copyinstr(path, pth, MNAMELEN-1, &len);
	if (error)
E 57
		return (error);
D 30
	bzero(&pth[len], MNAMELEN-len);
E 30
I 30
	bzero(&pth[len], MNAMELEN - len);
E 30
D 57
	if (error = copyinstr(args.hostname, hst, MNAMELEN-1, &len))
E 57
I 57
	error = copyinstr(args.hostname, hst, MNAMELEN-1, &len);
	if (error)
E 57
		return (error);
D 30
	bzero(&hst[len], MNAMELEN-len);
E 30
I 30
	bzero(&hst[len], MNAMELEN - len);
E 30
	/* sockargs() call must be after above copyin() calls */
D 21
	if (error = sockargs(&saddr, (caddr_t)args.addr,
E 21
I 21
D 57
	if (error = sockargs(&nam, (caddr_t)args.addr,
E 21
D 15
		sizeof (struct sockaddr_in), MT_SONAME))
E 15
I 15
D 36
		sizeof (struct sockaddr), MT_SONAME))
E 36
I 36
		args.addrlen, MT_SONAME))
E 57
I 57
	error = sockargs(&nam, (caddr_t)args.addr, args.addrlen, MT_SONAME);
	if (error)
E 57
E 36
E 15
		return (error);
D 57
	args.fh = &nfh;
E 57
I 57
	args.fh = nfh;
E 57
D 21
	error = mountnfs(&args, mp, saddr, pth, hst);
E 21
I 21
D 25
	error = mountnfs(&args, mp, nam, pth, hst);
E 25
I 25
	error = mountnfs(&args, mp, nam, pth, hst, &vp);
E 25
E 21
	return (error);
}

/*
 * Common code for mount and mountroot
 */
I 44
int
E 44
D 21
mountnfs(argp, mp, saddr, pth, hst)
E 21
I 21
D 25
mountnfs(argp, mp, nam, pth, hst)
E 25
I 25
mountnfs(argp, mp, nam, pth, hst, vpp)
E 25
E 21
	register struct nfs_args *argp;
	register struct mount *mp;
D 21
	register struct mbuf *saddr;
E 21
I 21
	struct mbuf *nam;
E 21
	char *pth, *hst;
I 25
	struct vnode **vpp;
E 25
{
	register struct nfsmount *nmp;
I 27
D 36
	struct proc *p = curproc;		/* XXX */
E 36
E 27
I 12
	struct nfsnode *np;
E 12
D 8
	struct nfsnode *np;
E 8
I 2
D 11
#ifdef notdef
E 2
	struct statfs statf, *sbp;
I 2
#endif
E 11
I 11
D 15
	fsid_t tfsid;
E 15
E 11
E 2
D 57
	int error;
E 57
I 57
	int error, maxio;
E 57
I 15
D 54
	fsid_t tfsid;
E 54
E 15

D 15
	nmp = (struct nfsmount *)malloc(sizeof (struct nfsmount), M_NFSMNT,
	    M_WAITOK);
E 15
I 15
D 36
	MALLOC(nmp, struct nfsmount *, sizeof *nmp, M_NFSMNT, M_WAITOK);
	bzero((caddr_t)nmp, sizeof *nmp);
E 36
I 36
D 44
	MALLOC(nmp, struct nfsmount *, sizeof (struct nfsmount), M_NFSMNT,
		M_WAITOK);
	bzero((caddr_t)nmp, sizeof (struct nfsmount));
E 36
E 15
D 20
	mp->m_data = (qaddr_t)nmp;
E 20
I 20
	mp->mnt_data = (qaddr_t)nmp;
E 44
I 44
	if (mp->mnt_flag & MNT_UPDATE) {
		nmp = VFSTONFS(mp);
		/* update paths, file handles, etc, here	XXX */
		m_freem(nam);
		return (0);
	} else {
		MALLOC(nmp, struct nfsmount *, sizeof (struct nfsmount),
		    M_NFSMNT, M_WAITOK);
		bzero((caddr_t)nmp, sizeof (struct nfsmount));
I 57
		TAILQ_INIT(&nmp->nm_uidlruhead);
E 57
		mp->mnt_data = (qaddr_t)nmp;
	}
E 44
E 20
D 11
	mp->m_fsid.val[0] = ++nfs_mntid;
E 11
I 11
D 39
	/*
	 * Generate a unique nfs mount id. The problem is that a dev number
	 * is not unique across multiple systems. The techique is as follows:
	 * 1) Set to nblkdev,0 which will never be used otherwise
	 * 2) Generate a first guess as nblkdev,nfs_mntid where nfs_mntid is
	 *	NOT 0
	 * 3) Loop searching the mount list for another one with same id
	 *	If a match, increment val[0] and try again
	 * NB: I increment val[0] { a long } instead of nfs_mntid { a u_char }
	 *	so that nfs is not limited to 255 mount points
	 *     Incrementing the high order bits does no real harm, since it
	 *     simply makes the major dev number tick up. The upper bound is
	 *     set to major dev 127 to avoid any sign extention problems
	 */
D 17
	mp->m_fsid.val[0] = makedev(nblkdev, 0);
E 11
	mp->m_fsid.val[1] = MOUNT_NFS;
E 17
I 17
D 20
	mp->m_stat.f_fsid.val[0] = makedev(nblkdev, 0);
	mp->m_stat.f_fsid.val[1] = MOUNT_NFS;
E 20
I 20
	mp->mnt_stat.f_fsid.val[0] = makedev(nblkdev, 0);
	mp->mnt_stat.f_fsid.val[1] = MOUNT_NFS;
E 20
E 17
I 11
	if (++nfs_mntid == 0)
		++nfs_mntid;
	tfsid.val[0] = makedev(nblkdev, nfs_mntid);
	tfsid.val[1] = MOUNT_NFS;
D 25
	while (getvfs(&tfsid)) {
E 25
I 25
	while (rootfs && getvfs(&tfsid)) {
E 25
		tfsid.val[0]++;
		nfs_mntid++;
	}
	if (major(tfsid.val[0]) > 127) {
		error = ENOENT;
I 18
D 21
		m_freem(saddr);
E 21
E 18
		goto bad;
	}
D 17
	mp->m_fsid.val[0] = tfsid.val[0];
E 17
I 17
D 20
	mp->m_stat.f_fsid.val[0] = tfsid.val[0];
E 20
I 20
	mp->mnt_stat.f_fsid.val[0] = tfsid.val[0];
E 39
I 39
D 57
	getnewfsid(mp, MOUNT_NFS);
E 57
I 57
	vfs_getnewfsid(mp);
E 57
E 39
E 20
E 17
E 11
	nmp->nm_mountp = mp;
	nmp->nm_flag = argp->flags;
D 15
	nmp->nm_sockaddr = saddr;
	/* Set up the sockets */
	if (error = socreate(AF_INET, &nmp->nm_so, SOCK_DGRAM, 0))
		goto bad;
	if (error = soconnect(nmp->nm_so, saddr))
		goto bad;
I 5
D 7
printf("sosnd=0x%x sorcv=0x%x\n",&nmp->nm_so->so_snd,&nmp->nm_so->so_rcv);
E 7
E 5
	if ((argp->flags & NFSMNT_TIMEO) && argp->timeo >= 1)
		nmp->nm_timeo = argp->timeo;
	else
		nmp->nm_timeo = NFS_TIMEO;
	if ((argp->flags & NFSMNT_RETRANS) && argp->retrans > 0)
		nmp->nm_retrans = argp->retrans;
	else
		nmp->nm_retrans = NFS_RETRANS;
	if ((argp->flags & NFSMNT_WSIZE) &&
	    argp->wsize <= NFS_MAXDATA && argp->wsize > 0 &&
	   (argp->wsize & 0x1ff) == 0)
E 15
I 15
D 36
	nmp->nm_rto = NFS_TIMEO;
	nmp->nm_rtt = -1;
	nmp->nm_rttvar = nmp->nm_rto << 1;
E 36
I 36
D 57
	if ((nmp->nm_flag & (NFSMNT_NQNFS | NFSMNT_MYWRITE)) ==
		(NFSMNT_NQNFS | NFSMNT_MYWRITE)) {
		error = EPERM;
		goto bad;
	}
E 57
D 43
	if ((nmp->nm_flag & (NFSMNT_RDIRALOOK | NFSMNT_LEASETERM)) &&
	    (nmp->nm_flag & NFSMNT_NQNFS) == 0) {
		error = EPERM;
		goto bad;
E 43
I 43
D 51
	if (nmp->nm_flag & (NFSMNT_RDIRALOOK | NFSMNT_LEASETERM)) {
		if ((nmp->nm_flag & NFSMNT_NQNFS) == 0) {
			error = EPERM;
			goto bad;
		}
E 51
I 51
	if (nmp->nm_flag & NFSMNT_NQNFS)
E 51
		/*
		 * We have to set mnt_maxsymlink to a non-zero value so
		 * that COMPAT_43 routines will know that we are setting
		 * the d_type field in directories (and can zero it for
		 * unsuspecting binaries).
		 */
		mp->mnt_maxsymlinklen = 1;
E 43
D 51
	}
E 51
	nmp->nm_timeo = NFS_TIMEO;
E 36
	nmp->nm_retry = NFS_RETRANS;
	nmp->nm_wsize = NFS_WSIZE;
	nmp->nm_rsize = NFS_RSIZE;
I 57
	nmp->nm_readdirsize = NFS_READDIRSIZE;
E 57
I 36
	nmp->nm_numgrps = NFS_MAXGRPS;
	nmp->nm_readahead = NFS_DEFRAHEAD;
	nmp->nm_leaseterm = NQ_DEFLEASE;
	nmp->nm_deadthresh = NQ_DEADTHRESH;
D 55
	nmp->nm_tnext = (struct nfsnode *)nmp;
	nmp->nm_tprev = (struct nfsnode *)nmp;
E 55
I 55
	CIRCLEQ_INIT(&nmp->nm_timerhead);
E 55
	nmp->nm_inprog = NULLVP;
E 36
D 57
	bcopy((caddr_t)argp->fh, (caddr_t)&nmp->nm_fh, sizeof(nfsv2fh_t));
D 17
	bcopy(hst, nmp->nm_host, sizeof nmp->nm_host);
	bcopy(pth, nmp->nm_path, sizeof nmp->nm_path);
E 17
I 17
D 20
	bcopy(hst, mp->m_stat.f_mntfromname, MNAMELEN);
	bcopy(pth, mp->m_stat.f_mntonname, MNAMELEN);
E 20
I 20
	mp->mnt_stat.f_type = MOUNT_NFS;
E 57
I 57
	nmp->nm_fhsize = argp->fhsize;
	bcopy((caddr_t)argp->fh, (caddr_t)nmp->nm_fh, argp->fhsize);
E 57
	bcopy(hst, mp->mnt_stat.f_mntfromname, MNAMELEN);
	bcopy(pth, mp->mnt_stat.f_mntonname, MNAMELEN);
I 21
	nmp->nm_nam = nam;
E 21
E 20
E 17

	if ((argp->flags & NFSMNT_TIMEO) && argp->timeo > 0) {
D 36
		nmp->nm_rto = argp->timeo;
		/* NFS timeouts are specified in 1/10 sec. */
		nmp->nm_rto = (nmp->nm_rto * 10) / NFS_HZ;
		if (nmp->nm_rto < NFS_MINTIMEO)
			nmp->nm_rto = NFS_MINTIMEO;
		else if (nmp->nm_rto > NFS_MAXTIMEO)
			nmp->nm_rto = NFS_MAXTIMEO;
		nmp->nm_rttvar = nmp->nm_rto << 1;
E 36
I 36
		nmp->nm_timeo = (argp->timeo * NFS_HZ + 5) / 10;
		if (nmp->nm_timeo < NFS_MINTIMEO)
			nmp->nm_timeo = NFS_MINTIMEO;
		else if (nmp->nm_timeo > NFS_MAXTIMEO)
			nmp->nm_timeo = NFS_MAXTIMEO;
E 36
	}

D 23
	if ((argp->flags & NFSMNT_RETRANS) && argp->retrans >= 0) {
E 23
I 23
	if ((argp->flags & NFSMNT_RETRANS) && argp->retrans > 1) {
E 23
		nmp->nm_retry = argp->retrans;
		if (nmp->nm_retry > NFS_MAXREXMIT)
			nmp->nm_retry = NFS_MAXREXMIT;
	}

I 57
	if (argp->flags & NFSMNT_NFSV3) {
		if (argp->sotype == SOCK_DGRAM)
			maxio = NFS_MAXDGRAMDATA;
		else
			maxio = NFS_MAXDATA;
	} else
		maxio = NFS_V2MAXDATA;

E 57
	if ((argp->flags & NFSMNT_WSIZE) && argp->wsize > 0) {
E 15
		nmp->nm_wsize = argp->wsize;
D 15
	else
		nmp->nm_wsize = NFS_WSIZE;
	if ((argp->flags & NFSMNT_RSIZE) &&
	    argp->rsize <= NFS_MAXDATA && argp->rsize > 0 &&
	   (argp->rsize & 0x1ff) == 0)
E 15
I 15
		/* Round down to multiple of blocksize */
D 57
		nmp->nm_wsize &= ~0x1ff;
E 57
I 57
		nmp->nm_wsize &= ~(NFS_FABLKSIZE - 1);
E 57
		if (nmp->nm_wsize <= 0)
D 57
			nmp->nm_wsize = 512;
		else if (nmp->nm_wsize > NFS_MAXDATA)
			nmp->nm_wsize = NFS_MAXDATA;
E 57
I 57
			nmp->nm_wsize = NFS_FABLKSIZE;
E 57
	}
I 57
	if (nmp->nm_wsize > maxio)
		nmp->nm_wsize = maxio;
E 57
I 23
	if (nmp->nm_wsize > MAXBSIZE)
		nmp->nm_wsize = MAXBSIZE;
E 23

	if ((argp->flags & NFSMNT_RSIZE) && argp->rsize > 0) {
E 15
		nmp->nm_rsize = argp->rsize;
D 15
	else
		nmp->nm_rsize = NFS_RSIZE;
	bcopy((caddr_t)argp->fh, (caddr_t)&nmp->nm_fh, sizeof(nfsv2fh_t));
	bcopy(pth, nmp->nm_path, MNAMELEN);
	bcopy(hst, nmp->nm_host, MNAMELEN);
E 15
I 15
		/* Round down to multiple of blocksize */
D 57
		nmp->nm_rsize &= ~0x1ff;
E 57
I 57
		nmp->nm_rsize &= ~(NFS_FABLKSIZE - 1);
E 57
		if (nmp->nm_rsize <= 0)
D 57
			nmp->nm_rsize = 512;
		else if (nmp->nm_rsize > NFS_MAXDATA)
			nmp->nm_rsize = NFS_MAXDATA;
E 57
I 57
			nmp->nm_rsize = NFS_FABLKSIZE;
E 57
	}
I 57
	if (nmp->nm_rsize > maxio)
		nmp->nm_rsize = maxio;
E 57
I 23
	if (nmp->nm_rsize > MAXBSIZE)
		nmp->nm_rsize = MAXBSIZE;
I 57

	if ((argp->flags & NFSMNT_READDIRSIZE) && argp->readdirsize > 0) {
		nmp->nm_readdirsize = argp->readdirsize;
		/* Round down to multiple of blocksize */
		nmp->nm_readdirsize &= ~(NFS_DIRBLKSIZ - 1);
		if (nmp->nm_readdirsize < NFS_DIRBLKSIZ)
			nmp->nm_readdirsize = NFS_DIRBLKSIZ;
	}
	if (nmp->nm_readdirsize > maxio)
		nmp->nm_readdirsize = maxio;

E 57
I 36
	if ((argp->flags & NFSMNT_MAXGRPS) && argp->maxgrouplist >= 0 &&
		argp->maxgrouplist <= NFS_MAXGRPS)
		nmp->nm_numgrps = argp->maxgrouplist;
	if ((argp->flags & NFSMNT_READAHEAD) && argp->readahead >= 0 &&
		argp->readahead <= NFS_MAXRAHEAD)
		nmp->nm_readahead = argp->readahead;
	if ((argp->flags & NFSMNT_LEASETERM) && argp->leaseterm >= 2 &&
		argp->leaseterm <= NQ_MAXLEASE)
		nmp->nm_leaseterm = argp->leaseterm;
	if ((argp->flags & NFSMNT_DEADTHRESH) && argp->deadthresh >= 1 &&
		argp->deadthresh <= NQ_NEVERDEAD)
		nmp->nm_deadthresh = argp->deadthresh;
E 36
E 23
	/* Set up the sockets and per-host congestion */
D 18
	if (error = nfs_connect(nmp, saddr))
E 18
I 18
D 21
	if (error = nfs_connect(nmp, saddr)) {
		m_freem(saddr);
E 21
I 21
	nmp->nm_sotype = argp->sotype;
	nmp->nm_soproto = argp->proto;
D 36
	if (error = nfs_connect(nmp))
E 21
E 18
		goto bad;
E 36
I 18
D 21
	}
E 21
E 18

I 17
D 20
	if (error = nfs_statfs(mp, &mp->m_stat))
E 20
I 20
D 27
	if (error = nfs_statfs(mp, &mp->mnt_stat))
E 27
I 27
D 36
	if (error = nfs_statfs(mp, &mp->mnt_stat, p))
E 36
I 36
	/*
	 * For Connection based sockets (TCP,...) defer the connect until
	 * the first request, in case the server is not responding.
	 */
	if (nmp->nm_sotype == SOCK_DGRAM &&
		(error = nfs_connect(nmp, (struct nfsreq *)0)))
E 36
E 27
E 20
		goto bad;
I 36

E 36
E 17
E 15
I 2
D 11
#ifdef notdef
E 2
	sbp = &statf;
E 11
	/*
I 36
	 * This is silly, but it has to be set so that vinifod() works.
	 * We do not want to do an nfs_statfs() here since we can get
	 * stuck on a dead server and we are holding a lock on the mount
	 * point.
	 */
	mp->mnt_stat.f_iosize = NFS_MAXDGRAMDATA;
	/*
E 36
D 11
	 * Kludge City...
	 * To do an interruptable hard mount, turn it into a soft mount
	 * with a retry limit of one and then repeat it so long as it
	 * times out and there is no pending signal for the process.
	 * It is tempting to just let nfs_statfs() sleep at positive
	 * prio, but then you would long jump out without taking the
	 * mount structure back out of the list.
	 * NB: NFSMNT_INT must NEVER be set for nfs_mountroot(), since
	 * the process context is not yet built!!
	 */
	if ((argp->flags && NFSMNT_INT) && (argp->flags & NFSMNT_SOFT) == 0) {
		int savretrans;

		nmp->nm_flag |= NFSMNT_SOFT;
		savretrans = nmp->nm_retrans;
		nmp->nm_retrans = 1;
		do {
			error = nfs_statfs(mp, sbp);
		} while (error == ETIMEDOUT && (u.u_procp->p_sig &
			(sigmask(SIGINT)|sigmask(SIGQUIT)|sigmask(SIGTERM)|
			 sigmask(SIGKILL))) == 0);
		nmp->nm_retrans = savretrans;
		nmp->nm_flag &= ~NFSMNT_SOFT;
		if (error)
			goto bad;
	} else if (error = nfs_statfs(mp, sbp))
		goto bad;
	mp->m_fsize = sbp->f_fsize;

	/*
	 * If the block size is not an exact multiple of CLBYTES
	 * use CLBYTES so that paging in ZMAGIC executables doesn't
	 * get sick. (It is used by vinitfod())
	 */
	if (sbp->f_bsize >= CLBYTES && claligned(sbp->f_bsize))
		mp->m_bsize = sbp->f_bsize;
	else
		mp->m_bsize = CLBYTES;
I 2
#else
	/*
E 11
D 17
	 * Set to CLBYTES so that vinifod() doesn't get confused.
	 * Actually any exact multiple of CLBYTES will do
	 */
	mp->m_bsize = mp->m_fsize = CLBYTES;
I 12
	/*
E 17
	 * A reference count is needed on the nfsnode representing the
	 * remote root.  If this object is not persistent, then backward
	 * traversals of the mount point (i.e. "..") will not work if
	 * the nfsnode gets flushed out of the cache. Ufs does not have
	 * this problem, because one can identify root inodes by their
	 * number == ROOTINO (2).
	 */
D 57
	if (error = nfs_nget(mp, &nmp->nm_fh, &np))
E 57
I 57
	error = nfs_nget(mp, (nfsfh_t *)nmp->nm_fh, nmp->nm_fhsize, &np);
	if (error)
E 57
		goto bad;
D 36
	/*
	 * Unlock it, but keep the reference count.
	 */
	nfs_unlock(NFSTOV(np));
E 36
I 25
	*vpp = NFSTOV(np);
E 25
I 15
D 17

E 17
E 15
E 12
D 11
#endif
E 11
E 2
D 21
	return (0);
E 21
I 17

I 21
	return (0);
E 21
E 17
bad:
I 15
	nfs_disconnect(nmp);
D 36
	FREE(nmp, M_NFSMNT);
E 36
I 36
	free((caddr_t)nmp, M_NFSMNT);
E 36
I 21
	m_freem(nam);
E 21
E 15
D 18
	m_freem(saddr);
E 18
D 15
	free((caddr_t)nmp, M_NFSMNT);
E 15
	return (error);
I 3
}

/*
D 4
 * Make a filesystem operational.
 * Nothing to do at the moment.
 */
nfs_start(mp, flags)
	struct mount *mp;
	int flags;
{

	return (0);
E 3
}

/*
E 4
 * unmount system call
 */
I 44
int
E 44
D 19
nfs_unmount(mp, flags)
E 19
I 19
D 27
nfs_unmount(mp, mntflags)
E 27
I 27
nfs_unmount(mp, mntflags, p)
E 27
E 19
	struct mount *mp;
D 19
	int flags;
E 19
I 19
	int mntflags;
I 27
	struct proc *p;
E 27
E 19
{
	register struct nfsmount *nmp;
D 22
	register struct nfsreq *rep;
	struct nfsreq *rep2;
E 22
I 12
	struct nfsnode *np;
I 15
	struct vnode *vp;
I 19
D 29
	int flags = 0;
E 19
E 15
E 12
	int error;
E 29
I 29
	int error, flags = 0;
D 61
	extern int doforce;
E 61
E 29
D 22
	int s;
E 22

D 19
	if (flags & MNT_FORCE)
E 19
I 19
D 28
	if (mntflags & MNT_FORCE)
E 19
		return (EINVAL);
I 19
	if (mntflags & MNT_FORCE)
E 28
I 28
D 61
	if (mntflags & MNT_FORCE) {
D 29
		if (mp == rootfs)
E 29
I 29
D 53
		if (!doforce || mp == rootfs)
E 53
I 53
D 57
		if (!doforce || (mp->mnt_flag & MNT_ROOTFS))
E 57
I 57
		if (!doforce)
E 57
E 53
E 29
			return (EINVAL);
E 61
I 61
	if (mntflags & MNT_FORCE)
E 61
E 28
		flags |= FORCECLOSE;
I 28
D 61
	}
E 61
E 28
E 19
D 20
	nmp = vfs_to_nfs(mp);
E 20
I 20
	nmp = VFSTONFS(mp);
E 20
	/*
I 4
D 40
	 * Clear out the buffer cache
	 */
D 10
	bflush(mp);
	if (binval(mp))
E 10
I 10
	mntflushbuf(mp, 0);
	if (mntinvalbuf(mp))
E 10
		return (EBUSY);
	/*
E 40
E 4
	 * Goes something like this..
I 12
D 15
	 * - Decrement reference on the nfsnode representing remote root.
	 *   Must do this first, otherwise vflush will return EBUSY.
E 12
D 9
	 * - Call nfs_nflush() to clear out the nfsnode table
E 9
I 9
	 * - Call vflush() to clear out vnodes for this file system
E 9
	 * - Flush out lookup cache
E 15
I 15
	 * - Check for activity on the root vnode (other than ourselves).
	 * - Call vflush() to clear out vnodes for this file system,
	 *   except for the root vnode.
	 * - Decrement reference on the vnode representing remote root.
E 15
	 * - Close the socket
	 * - Free up the data structures
	 */
I 12
	/*
	 * We need to decrement the ref. count on the nfsnode representing
	 * the remote root.  See comment in mountnfs().  The VFS unmount()
	 * has done vput on this vnode, otherwise we would get deadlock!
	 */
D 57
	if (error = nfs_nget(mp, &nmp->nm_fh, &np))
E 57
I 57
	error = nfs_nget(mp, (nfsfh_t *)nmp->nm_fh, nmp->nm_fhsize, &np);
	if (error)
E 57
		return(error);
I 15
	vp = NFSTOV(np);
	if (vp->v_usecount > 2) {
		vput(vp);
		return (EBUSY);
	}
I 36

	/*
	 * Must handshake with nqnfs_clientd() if it is active.
	 */
	nmp->nm_flag |= NFSMNT_DISMINPROG;
	while (nmp->nm_inprog != NULLVP)
		(void) tsleep((caddr_t)&lbolt, PSOCK, "nfsdism", 0);
E 36
D 57
	if (error = vflush(mp, vp, flags)) {
E 57
I 57
	error = vflush(mp, vp, flags);
	if (error) {
E 57
		vput(vp);
I 36
		nmp->nm_flag &= ~NFSMNT_DISMINPROG;
E 36
		return (error);
	}
I 36

E 36
E 15
	/*
D 36
	 * Get rid of two reference counts, and unlock it on the second.
E 36
I 36
	 * We are now committed to the unmount.
	 * For NQNFS, let the server daemon free the nfsmount structure.
E 36
	 */
I 36
	if (nmp->nm_flag & (NFSMNT_NQNFS | NFSMNT_KERB))
		nmp->nm_flag |= NFSMNT_DISMNT;

	/*
	 * There are two reference counts to get rid of here.
	 */
E 36
D 15
	vrele(NFSTOV(np));
	vput(NFSTOV(np));
E 12
D 9
	if (error = nfs_nflush(mp)) {
E 9
I 9
	if (error = vflush(mp, (struct vnode *)0, flags))
E 9
		return (error);
D 9
	}
E 9
	/*
	 * Scan the request list for any requests left hanging about
	 */
	s = splnet();
	rep = nfsreqh.r_next;
D 5
	while (rep) {
E 5
I 5
	while (rep && rep != &nfsreqh) {
E 5
		if (rep->r_mntp == nmp) {
			rep->r_prev->r_next = rep2 = rep->r_next;
D 5
			if (rep->r_next != NULL)
				rep->r_next->r_prev = rep->r_prev;
E 5
I 5
			rep->r_next->r_prev = rep->r_prev;
E 5
			m_freem(rep->r_mreq);
			if (rep->r_mrep != NULL)
				m_freem(rep->r_mrep);
			free((caddr_t)rep, M_NFSREQ);
			rep = rep2;
		} else
			rep = rep->r_next;
	}
	splx(s);
	soclose(nmp->nm_so);
	m_freem(nmp->nm_sockaddr);
E 15
I 15
	vrele(vp);
D 36
	vput(vp);
E 36
I 36
	vrele(vp);
I 37
	vgone(vp);
E 37
E 36
	nfs_disconnect(nmp);
I 21
	m_freem(nmp->nm_nam);
E 21
E 15
D 36
	free((caddr_t)nmp, M_NFSMNT);
E 36
I 36

	if ((nmp->nm_flag & (NFSMNT_NQNFS | NFSMNT_KERB)) == 0)
		free((caddr_t)nmp, M_NFSMNT);
E 36
	return (0);
}

/*
 * Return root of a filesystem
 */
I 44
int
E 44
nfs_root(mp, vpp)
	struct mount *mp;
	struct vnode **vpp;
{
	register struct vnode *vp;
	struct nfsmount *nmp;
	struct nfsnode *np;
	int error;

D 20
	nmp = vfs_to_nfs(mp);
E 20
I 20
	nmp = VFSTONFS(mp);
E 20
D 57
	if (error = nfs_nget(mp, &nmp->nm_fh, &np))
E 57
I 57
	error = nfs_nget(mp, (nfsfh_t *)nmp->nm_fh, nmp->nm_fhsize, &np);
	if (error)
E 57
		return (error);
	vp = NFSTOV(np);
	vp->v_type = VDIR;
	vp->v_flag = VROOT;
	*vpp = vp;
	return (0);
}

I 4
extern int syncprt;

E 4
/*
D 4
 * Since writes are synchronous, I think this is a no-op
 * Maybe write cache on nfs version 3 will require something ??
E 4
I 4
 * Flush out the buffer cache
E 4
 */
I 8
/* ARGSUSED */
I 44
int
E 44
E 8
D 40
nfs_sync(mp, waitfor)
E 40
I 40
nfs_sync(mp, waitfor, cred, p)
E 40
	struct mount *mp;
	int waitfor;
I 40
	struct ucred *cred;
	struct proc *p;
E 40
{
I 4
D 40
	if (syncprt)
D 32
		bufstats();
E 32
I 32
		ufs_bufstats();
E 40
I 40
D 41
	USES_VOP_FSYNC;
	USES_VOP_ISLOCKED;
E 41
	register struct vnode *vp;
	int error, allerror = 0;

E 40
E 32
	/*
	 * Force stale buffer cache information to be flushed.
	 */
D 10
	bflush(mp);
E 10
I 10
D 13
	mntflushbuf(mp);
E 13
I 13
D 40
	mntflushbuf(mp, waitfor == MNT_WAIT ? B_SYNC : 0);
E 13
E 10
E 4
	return (0);
E 40
I 40
loop:
D 53
	for (vp = mp->mnt_mounth; vp; vp = vp->v_mountf) {
E 53
I 53
	for (vp = mp->mnt_vnodelist.lh_first;
	     vp != NULL;
	     vp = vp->v_mntvnodes.le_next) {
E 53
		/*
		 * If the vnode that we are about to sync is no longer
		 * associated with this mount point, start over.
		 */
		if (vp->v_mount != mp)
			goto loop;
D 47
		if (VOP_ISLOCKED(vp) || vp->v_dirtyblkhd == NULL)
E 47
I 47
D 53
		if (VOP_ISLOCKED(vp) || vp->v_dirtyblkhd.le_next == NULL)
E 53
I 53
		if (VOP_ISLOCKED(vp) || vp->v_dirtyblkhd.lh_first == NULL)
E 53
E 47
			continue;
D 53
		if (vget(vp))
E 53
I 53
D 64
		if (vget(vp, 1))
E 64
I 64
		if (vget(vp, LK_EXCLUSIVE, p))
E 64
E 53
			goto loop;
D 57
		if (error = VOP_FSYNC(vp, cred, waitfor, p))
E 57
I 57
		error = VOP_FSYNC(vp, cred, waitfor, p);
		if (error)
E 57
			allerror = error;
		vput(vp);
	}
	return (allerror);
I 41
}

/*
 * NFS flat namespace lookup.
 * Currently unsupported.
 */
/* ARGSUSED */
int
nfs_vget(mp, ino, vpp)
	struct mount *mp;
	ino_t ino;
	struct vnode **vpp;
{

	return (EOPNOTSUPP);
E 41
E 40
}

/*
 * At this point, this should never happen
 */
I 8
/* ARGSUSED */
I 44
int
E 44
E 8
D 36
nfs_fhtovp(mp, fhp, vpp)
E 36
I 36
D 40
nfs_fhtovp(mp, fhp, setgen, vpp)
E 40
I 40
D 42
nfs_fhtovp(mp, fhp, vpp)
E 40
E 36
	struct mount *mp;
E 42
I 42
nfs_fhtovp(mp, fhp, nam, vpp, exflagsp, credanonp)
	register struct mount *mp;
E 42
	struct fid *fhp;
I 42
	struct mbuf *nam;
E 42
I 36
D 40
	int setgen;
E 40
E 36
	struct vnode **vpp;
I 42
	int *exflagsp;
	struct ucred **credanonp;
E 42
{
I 8

E 8
	return (EINVAL);
}

/*
 * Vnode pointer to File handle, should never happen either
 */
I 8
/* ARGSUSED */
I 44
int
E 44
E 8
D 27
nfs_vptofh(mp, fhp, vpp)
	struct mount *mp;
E 27
I 27
nfs_vptofh(vp, fhp)
	struct vnode *vp;
E 27
	struct fid *fhp;
D 27
	struct vnode **vpp;
E 27
{
I 8

E 8
	return (EINVAL);
I 4
}

/*
 * Vfs start routine, a no-op.
 */
I 8
/* ARGSUSED */
I 44
int
E 44
E 8
D 27
nfs_start(mp, flags)
E 27
I 27
nfs_start(mp, flags, p)
E 27
	struct mount *mp;
	int flags;
I 27
	struct proc *p;
E 27
{
I 8

E 8
	return (0);
I 19
}

/*
 * Do operations associated with quotas, not supported
 */
I 33
/* ARGSUSED */
I 44
int
E 44
E 33
D 21
/* ARGSUSED */
E 21
D 27
nfs_quotactl(mp, cmd, uid, arg)
E 27
I 27
nfs_quotactl(mp, cmd, uid, arg, p)
E 27
	struct mount *mp;
	int cmd;
D 33
	uid_t uid;
E 33
I 33
D 40
	u_int uid;
E 40
I 40
	uid_t uid;
E 40
E 33
	caddr_t arg;
I 27
	struct proc *p;
E 27
{
I 22
D 33
#ifdef lint
	mp = mp; cmd = cmd; uid = uid; arg = arg;
#endif /* lint */
E 33
I 33

E 33
E 22
D 21

E 21
	return (EOPNOTSUPP);
E 19
E 4
}
I 57

/*
 * Do that sysctl thang...
 */
static int
nfs_sysctl(int *name, u_int namelen, void *oldp, size_t *oldlenp, void *newp,
	   size_t newlen, struct proc *p)
{
	int rv;

	/*
	 * All names at this level are terminal.
	 */
	if(namelen > 1)
		return ENOTDIR;	/* overloaded */

	switch(name[0]) {
	case NFS_NFSSTATS:
		if(!oldp) {
			*oldlenp = sizeof nfsstats;
			return 0;
		}

		if(*oldlenp < sizeof nfsstats) {
			*oldlenp = sizeof nfsstats;
			return ENOMEM;
		}

		rv = copyout(&nfsstats, oldp, sizeof nfsstats);
		if(rv) return rv;

		if(newp && newlen != sizeof nfsstats)
			return EINVAL;

		if(newp) {
			return copyin(newp, &nfsstats, sizeof nfsstats);
		}
		return 0;

	default:
		return EOPNOTSUPP;
	}
}

E 57
E 1
