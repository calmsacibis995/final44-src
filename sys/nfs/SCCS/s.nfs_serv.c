h22411
s 00002/00002/03309
d D 8.7 95/05/14 00:33:01 mckusick 83 82
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 02134/00703/01177
d D 8.6 95/03/30 11:26:28 mckusick 82 81
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00001/00001/01879
d D 8.5 95/03/19 00:03:12 mckusick 81 80
c reverse arguments to VOP_LINK (to get them right)
e
s 00042/00044/01838
d D 8.4 94/06/04 17:29:06 mckusick 80 79
c ask for eofflag and cookies, and use the result
e
s 00002/00002/01880
d D 8.3 94/01/12 09:32:45 bostic 79 78
c lint
e
s 00005/00006/01877
d D 8.2 94/01/04 22:06:08 bostic 78 77
c lint
e
s 00002/00002/01881
d D 8.1 93/06/10 23:38:54 bostic 77 76
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00000/01878
d D 7.66 93/05/25 15:54:50 mckusick 76 75
c lease buglet from Macklem
e
s 00010/00000/01868
d D 7.65 93/05/21 14:02:12 mckusick 75 74
c protect against malicious clients
e
s 00018/00002/01850
d D 7.64 93/04/29 15:50:08 mckusick 74 73
c allow inode change of running file (from Macklem)
e
s 00006/00008/01846
d D 7.63 93/03/30 15:32:33 mckusick 73 72
c eliminate flags and generation number in times hack
e
s 00002/00001/01852
d D 7.62 92/11/12 10:45:13 mckusick 72 71
c workaround for access problems on NFS exports (try READ and EXEC
c access permission requests separately and return success if either works)
e
s 00001/00000/01852
d D 7.61 92/11/01 23:13:57 mckusick 71 70
c uninitialized variable
e
s 00038/00000/01814
d D 7.60 92/09/30 16:03:17 mckusick 70 69
c September update from Rick Macklem to add accept protocol to NQMFS
e
s 00116/00082/01698
d D 7.59 92/09/16 18:23:10 mckusick 69 68
c update from Rick Macklem
e
s 00007/00001/01773
d D 7.58 92/07/24 11:10:03 mckusick 68 67
c second try at fixing the mysteriously vanishing directory
c (this time for sure)
e
s 00002/00002/01772
d D 7.57 92/07/22 15:40:15 mckusick 67 66
c fix from Macklem for the "empty directory" syndrome
e
s 00001/00000/01773
d D 7.56 92/07/12 17:51:40 pendry 66 65
c needs to include <sys/systm.h>
e
s 00001/00001/01772
d D 7.55 92/07/12 17:16:46 pendry 65 64
c MIN -> min, MAX -> max
e
s 00001/00036/01772
d D 7.54 92/07/03 01:54:31 mckusick 64 63
c delete USES; VOP_VGET => VFS_VGET
e
s 00014/00013/01794
d D 7.53 92/06/25 13:09:29 mckusick 63 62
c use VOP_VGET in place of VFS_FHTOVP with setgen flag;
c READDIR no longer has eofflag
e
s 00002/00002/01805
d D 7.52 92/06/19 19:29:33 mckusick 62 61
c timeval => timespec in vattr and dinode
e
s 00034/00000/01773
d D 7.51 92/05/14 17:38:03 heideman 61 52
c vnode interface conversion
e
s 00034/00000/01773
d R 7.51 92/05/14 15:56:19 heideman 60 52
c vnode interface conversion
e
s 00034/00000/01773
d R 7.51 92/05/14 14:56:45 heideman 59 52
c vnode interface conversion
e
s 00034/00000/01773
d R 7.51 92/05/14 13:02:48 heideman 58 52
c vnode interface conversion
e
s 00034/00000/01773
d R 7.51 92/05/14 12:00:05 heideman 57 52
c vnode interface conversion
e
s 00034/00000/01773
d R 7.51 92/05/14 11:23:40 heideman 56 52
c vnode interface conversion
e
s 00034/00000/01773
d R 7.51 92/05/13 23:19:17 heideman 55 52
c vnode interface conversion
e
s 00034/00000/01773
d R 7.51 92/05/13 19:03:13 heideman 54 52
c vnode interface conversion
e
s 00034/00000/01773
d R 7.51 92/05/13 18:35:29 heideman 53 52
c vnode interface conversion
e
s 00018/00016/01755
d D 7.50 92/05/04 16:38:19 mckusick 52 51
c lint; clean up include directives
e
s 00001/00001/01770
d D 7.49 92/03/13 17:57:14 mckusick 51 50
c must have directory vnode as first op VOP_LINK
e
s 00019/00009/01752
d D 7.48 92/02/25 12:01:35 mckusick 50 49
c fix memory leak introduced in -r7.43; asethetic cleanups
e
s 00004/00000/01757
d D 7.47 92/02/06 18:01:40 mckusick 49 48
c bug fix for leases from Rick Macklem
e
s 00029/00025/01728
d D 7.46 92/02/06 17:59:56 mckusick 48 47
c convert to format defined by dirent.h, not that of ufs on-disk directory
e
s 00051/00040/01702
d D 7.45 92/02/04 00:24:55 heideman 47 46
c new organization for nameidata
e
s 00027/00026/01715
d D 7.44 92/01/22 09:39:34 heideman 46 45
c lookup converted to new form
e
s 00527/00255/01214
d D 7.43 92/01/14 12:41:13 mckusick 45 44
c update from Rick Macklem (including leases)
e
s 00001/00001/01468
d D 7.42 91/12/14 21:12:01 mckusick 44 43
c statfs.f_bsize => statfs.f_iosize; statfs.f_fsize => statfs.f_bsize (for SunOS)
e
s 00003/00003/01466
d D 7.41 91/11/01 16:49:17 bostic 43 41
c ufs moved down one level
e
s 00010/00001/01468
d D 7.40.1.1 91/05/19 14:32:53 mckusick 42 41
c name resolution checking (need kern/kern_malloc.c 7.25.1.1,
c kern/vfs_lookup.c 7.31.1.1, kern/vfs_syscalls.c 7.70.1.1,
c nfs/nfs_serv.c 7.40.1.1, nfs/nfs_syscalls.c 7.26.1.1,
c ufs/ufs_vnops.c 7.64.1.1, and hp300/hp300/trap.c 7.14.1.1)
e
s 00169/00146/01300
d D 7.40 91/05/15 20:24:37 mckusick 41 40
c use new scheme for name lookup
e
s 00002/00002/01444
d D 7.39 91/05/08 19:51:05 mckusick 40 38
c more precise comments
e
s 00001/00001/01445
d R 7.39 91/05/08 19:49:10 mckusick 39 38
c more precise comment
e
s 00000/00011/01446
d D 7.38 91/05/08 13:38:56 karels 38 37
c unifdef NVM
e
s 00114/00090/01343
d D 7.37 91/04/16 00:38:38 mckusick 37 36
c u_long tl used in place of u_long p; nfsrv_ routines get proc pointer; 
c add proc pointers to appropriate VOP operations
e
s 00002/00002/01431
d D 7.36 91/03/19 11:24:42 karels 36 35
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; consolidate *nullops()
e
s 00001/00001/01432
d D 7.35 91/03/04 22:52:15 mckusick 35 34
c misc fixes plus diskless support from Rick Macklem
e
s 00012/00004/01421
d D 7.34 91/02/21 23:01:39 mckusick 34 33
c fixes for multiple calls to namei (for rename in NFS)
e
s 00011/00000/01414
d D 7.33 91/01/10 23:52:40 mckusick 33 32
c make new VM conditional so can share with old VM tree
e
s 00000/00004/01414
d D 7.32 91/01/10 23:51:58 mckusick 32 31
c cdir moves out of the namei data structure
e
s 00007/00008/01411
d D 7.31 91/01/08 16:55:26 mckusick 31 30
c update from Rick Macklem
e
s 00002/00004/01417
d D 7.30 90/12/05 16:03:11 mckusick 30 29
c update for new VM
e
s 00003/00001/01418
d D 7.29 90/10/01 20:51:27 mckusick 29 28
c take symbolic link mode from the client as is done for files
e
s 00011/00014/01408
d D 7.28 90/08/22 12:41:12 mckusick 28 27
c have to do VOP_ACCESS to ensure that quotas are set up
e
s 00001/00001/01421
d D 7.27 90/07/26 19:14:08 bostic 27 26
c NFS_MAXDATA changed, and this can confuse Ultrix 2.2 clients
c from Rick Macklem
e
s 00001/00011/01421
d D 7.26 90/06/28 21:51:59 bostic 26 25
c new copyright notice
e
s 00040/00010/01392
d D 7.25 90/06/21 12:15:10 mckusick 25 24
c have to check for "." when releasing parent directory
e
s 00011/00004/01391
d D 7.24 90/06/21 11:16:36 mckusick 24 23
c "update from Rick Macklem"
e
s 00002/00000/01393
d D 7.23 90/06/04 20:40:56 mckusick 23 22
c set the file type properly on server create
e
s 00003/00001/01390
d D 7.22 90/05/31 15:48:37 mckusick 22 21
c missing vput
e
s 00057/00028/01334
d D 7.21 90/05/30 11:39:55 mckusick 21 20
c VOP_ABORTOP is no longer responsible for unlocking and vreleing vnodes
e
s 00040/00006/01322
d D 7.20 90/05/18 14:54:16 mckusick 20 19
c "nfs_mknod update from Rick Macklem"
e
s 00075/00066/01253
d D 7.19 90/05/14 11:40:34 mckusick 19 18
c "update from Rick Macklem adding TCP support to NFS"
e
s 00007/00007/01312
d D 7.18 90/05/04 20:52:28 mckusick 18 17
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00004/00004/01315
d D 7.17 90/05/03 18:43:37 mckusick 17 16
c vattr_null => VATTR_NULL
e
s 00003/00003/01316
d D 7.16 90/03/06 23:32:44 mckusick 16 15
c m_fsid is now m_stat.f_fsid
e
s 00006/00003/01313
d D 7.15 90/03/05 19:38:16 mckusick 15 14
c readdir fixes from Rick Macklem
e
s 00000/00001/01316
d D 7.14 90/02/17 15:23:54 mckusick 14 13
c get rid of bogus `strings.h' include file
e
s 00004/00011/01313
d D 7.13 90/02/17 10:30:42 mckusick 13 12
c get rid of unneeded header files
e
s 00015/00006/01309
d D 7.12 90/02/16 13:39:56 mckusick 12 11
c compress empty directory blocks out of our reply
e
s 00078/00144/01237
d D 7.11 89/12/20 18:08:41 mckusick 11 10
c "December update from Rick Macklem"
e
s 00006/00003/01375
d D 7.10 89/11/22 21:37:24 mckusick 10 9
c READ/WRITE no longer take offp
e
s 00104/00020/01274
d D 7.9 89/11/03 15:30:19 mckusick 9 8
c lint
e
s 00030/00015/01264
d D 7.8 89/10/19 22:34:03 mckusick 8 7
c "update from Rick Macklem"
e
s 00134/00140/01145
d D 7.7 89/08/30 20:29:56 macklem 7 6
c first buffer cache implementation; name cache usage; code cleanups
e
s 00007/00007/01278
d D 7.6 89/08/22 22:24:12 mckusick 6 5
c convert vap_bytes to blocks for NFS protocol
e
s 00003/00001/01282
d D 7.5 89/07/16 14:21:22 mckusick 5 4
c avoid dangling reference for cdir when doing rename
e
s 00054/00007/01229
d D 7.4 89/07/16 14:17:41 mckusick 4 3
c use precise NFS semantics for access checks
e
s 00056/00068/01180
d D 7.3 89/07/06 17:42:25 mckusick 3 2
c update of July 5th from Rick Macklem
e
s 00004/00003/01244
d D 7.2 89/07/05 11:41:00 mckusick 2 1
c break up vn_access using vn_writechk and VOP_ACCESS as appropriate
e
s 01247/00000/00000
d D 7.1 89/07/05 11:40:02 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
f b 
t
T
I 1
/*
D 77
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 77
I 77
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 77
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 26
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
E 26
I 26
 * %sccs.include.redist.c%
E 26
 *
 *	%W% (Berkeley) %G%
 */

/*
D 82
 * nfs version 2 server calls to vnode ops
E 82
I 82
 * nfs version 2 and 3 server calls to vnode ops
E 82
 * - these routines generally have 3 phases
 *   1 - break down and validate rpc request in mbuf list
 *   2 - do the vnode ops for the request
D 3
 *	 (surprisingly ?? many are very similar to syscalls in vfs_syscalls.c)
E 3
I 3
 *       (surprisingly ?? many are very similar to syscalls in vfs_syscalls.c)
E 3
 *   3 - build the rpc reply in an mbuf list
 *   nb:
 *	- do not mix the phases, since the nfsm_?? macros can return failures
D 19
 *	  on mbuf exhaustion or similar and do not do any vrele() or vput()'s
E 19
I 19
 *	  on a bad rpc or similar and do not do any vrele() or vput()'s
E 19
 *
D 3
 *	- the nfsm_reply() macro generates an nfs rpc reply with the nfs
E 3
I 3
 *      - the nfsm_reply() macro generates an nfs rpc reply with the nfs
E 3
 *	error number iff error != 0 whereas
D 3
 *	 nfsm_srverr simply drops the mbufs and gives up
 *	 (==> nfsm_srverr implies an error here at the server, usually mbuf
E 3
I 3
D 19
 *       nfsm_srverr simply drops the mbufs and gives up
 *       (==> nfsm_srverr implies an error here at the server, usually mbuf
E 3
 *	  exhaustion)
E 19
I 19
 *	returning an error from the server function implies a fatal error
 *	such as a badly constructed rpc request that should be dropped without
 *	a reply.
I 82
 *	For Version 3, nfsm_reply() does not return for the error case, since
 *	most version 3 rpcs return more than the status for error cases.
E 82
E 19
 */

D 13
#include "strings.h"
#include "time.h"
E 13
D 52
#include "param.h"
I 41
#include "proc.h"
E 41
D 13
#include "mount.h"
#include "malloc.h"
#include "mbuf.h"
#include "file.h"
E 13
D 36
#include "user.h"
E 36
D 13
#include "../ufs/dir.h"
E 13
I 13
#include "file.h"
I 37
#include "namei.h"
E 37
E 13
#include "vnode.h"
D 13
#include "uio.h"
#include "ucred.h"
#include "namei.h"
E 13
I 13
#include "mount.h"
#include "mbuf.h"
I 48
#include "dirent.h"
E 52
I 52
#include <sys/param.h>
I 66
#include <sys/systm.h>
E 66
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/mount.h>
I 82
#include <sys/socket.h>
#include <sys/socketvar.h>
E 82
#include <sys/mbuf.h>
#include <sys/dirent.h>
I 63
#include <sys/stat.h>
I 82
#include <sys/kernel.h>
#include <ufs/ufs/dir.h>
E 82
E 63
E 52
E 48
E 13
D 36
#include "errno.h"
E 36
I 36

E 36
I 20
D 43
#include "../ufs/quota.h"
#include "../ufs/inode.h"
I 41
#include "../ufs/dir.h"
E 43
I 43
D 48
#include "ufs/ufs/quota.h"
#include "ufs/ufs/inode.h"
#include "ufs/ufs/dir.h"
E 48
I 48
D 52
#include "ufs/ufs/quota.h"	/* XXX - for ufid */
#include "ufs/ufs/inode.h"	/* XXX - for ufid */
E 52
I 52
#include <vm/vm.h>
E 52
E 48
E 43
E 41
I 36

E 36
E 20
D 13
#include "../ufs/inode.h"
E 13
I 13
D 14
#include "strings.h"
E 14
E 13
D 52
#include "nfsv2.h"
I 45
#include "rpcv2.h"
E 45
#include "nfs.h"
#include "xdr_subs.h"
#include "nfsm_subs.h"
I 45
#include "nqnfs.h"
E 52
I 52
D 63
#include <ufs/ufs/quota.h>	/* XXX - for ufid */
#include <ufs/ufs/inode.h>	/* XXX - for ufid */

E 63
D 82
#include <nfs/nfsv2.h>
E 82
I 82
#include <nfs/nfsproto.h>
E 82
#include <nfs/rpcv2.h>
#include <nfs/nfs.h>
#include <nfs/xdr_subs.h>
#include <nfs/nfsm_subs.h>
#include <nfs/nqnfs.h>
E 52
E 45

D 82
/* Defs */
D 3
#define TRUE	1
#define FALSE	0
E 3
I 3
#define	TRUE	1
#define	FALSE	0
E 3

E 82
/* Global vars */
D 82
extern u_long nfs_procids[NFS_NPROCS];
E 82
extern u_long nfs_xdrneg1;
extern u_long nfs_false, nfs_true;
D 20
nfstype nfs_type[VSOCK+1]={ NFNON, NFREG, NFDIR, NFBLK, NFCHR, NFLNK, NFNON, };
E 20
I 20
D 45
nfstype nfs_type[9]={ NFNON, NFREG, NFDIR, NFBLK, NFCHR, NFLNK, NFNON,
E 45
I 45
D 82
nfstype nfs_type[9] = { NFNON, NFREG, NFDIR, NFBLK, NFCHR, NFLNK, NFNON,
E 82
I 82
extern enum vtype nv3tov_type[8];
extern struct nfsstats nfsstats;
nfstype nfsv2_type[9] = { NFNON, NFREG, NFDIR, NFBLK, NFCHR, NFLNK, NFNON,
E 82
E 45
		      NFCHR, NFNON };
I 82
nfstype nfsv3_type[9] = { NFNON, NFREG, NFDIR, NFBLK, NFCHR, NFLNK, NFSOCK,
		      NFFIFO, NFNON };
int nfsrvw_procrastinate = NFS_GATHERDELAY * 1000;
E 82
E 20

/*
I 70
D 82
 * nqnfs access service
E 82
I 82
 * nfs v3 access service
E 82
 */
D 82
nqnfsrv_access(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv3_access(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
	struct vnode *vp;
D 82
	nfsv2fh_t nfh;
E 82
I 82
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
	register u_long *tl;
	register long t1;
	caddr_t bpos;
D 82
	int error = 0, rdonly, cache, mode = 0;
E 82
I 82
	int error = 0, rdonly, cache, getret;
E 82
	char *cp2;
D 78
	struct mbuf *mb, *mb2, *mreq;
E 78
I 78
D 82
	struct mbuf *mb, *mreq;
E 82
I 82
	struct mbuf *mb, *mreq, *mb2;
	struct vattr vattr, *vap = &vattr;
	u_long testmode, nfsmode;
E 82
E 78
	u_quad_t frev;

I 82
#ifndef nolint
	cache = 0;
#endif
E 82
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 82
	nfsm_dissect(tl, u_long *, 3 * NFSX_UNSIGNED);
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
		nfsm_reply(0);
	if (*tl++ == nfs_true)
		mode |= VREAD;
	if (*tl++ == nfs_true)
		mode |= VWRITE;
	if (*tl == nfs_true)
		mode |= VEXEC;
	error = nfsrv_access(vp, mode, cred, rdonly, nfsd->nd_procp);
E 82
I 82
	nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
		nfsm_reply(NFSX_UNSIGNED);
		nfsm_srvpostop_attr(1, (struct vattr *)0);
		return (0);
	}
	nfsmode = fxdr_unsigned(u_long, *tl);
	if ((nfsmode & NFSV3ACCESS_READ) &&
		nfsrv_access(vp, VREAD, cred, rdonly, procp))
		nfsmode &= ~NFSV3ACCESS_READ;
	if (vp->v_type == VDIR)
		testmode = (NFSV3ACCESS_MODIFY | NFSV3ACCESS_EXTEND |
			NFSV3ACCESS_DELETE);
	else
		testmode = (NFSV3ACCESS_MODIFY | NFSV3ACCESS_EXTEND);
	if ((nfsmode & testmode) &&
		nfsrv_access(vp, VWRITE, cred, rdonly, procp))
		nfsmode &= ~testmode;
	if (vp->v_type == VDIR)
		testmode = NFSV3ACCESS_LOOKUP;
	else
		testmode = NFSV3ACCESS_EXECUTE;
	if ((nfsmode & testmode) &&
		nfsrv_access(vp, VEXEC, cred, rdonly, procp))
		nfsmode &= ~testmode;
	getret = VOP_GETATTR(vp, vap, cred, procp);
E 82
	vput(vp);
D 82
	nfsm_reply(0);
E 82
I 82
	nfsm_reply(NFSX_POSTOPATTR(1) + NFSX_UNSIGNED);
	nfsm_srvpostop_attr(getret, vap);
	nfsm_build(tl, u_long *, NFSX_UNSIGNED);
	*tl = txdr_unsigned(nfsmode);
E 82
	nfsm_srvdone;
}

/*
E 70
 * nfs getattr service
 */
D 11
nfsrv_getattr(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_getattr(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_getattr(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf **mrq;
E 45
I 45
D 82
nfsrv_getattr(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
E 45
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
D 45
	u_long xid;
I 11
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_getattr(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 61
D 64
	USES_VOP_GETATTR;
E 64
E 61
I 7
D 82
	register struct nfsv2_fattr *fp;
E 82
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	register struct nfs_fattr *fp;
E 82
E 7
	struct vattr va;
	register struct vattr *vap = &va;
	struct vnode *vp;
D 82
	nfsv2fh_t nfh;
E 82
I 82
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
D 9
	nfsm_srvars;
E 9
I 9
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
	int error = 0, rdonly, cache;
E 45
	char *cp2;
D 11
	struct mbuf *mb, *mb2;
E 11
I 11
	struct mbuf *mb, *mb2, *mreq;
I 45
	u_quad_t frev;
E 45
E 11
E 9

	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 45
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred))
E 45
I 45
D 82
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
E 82
I 82
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
E 82
E 45
		nfsm_reply(0);
D 37
	error = VOP_GETATTR(vp, vap, cred);
E 37
I 37
D 45
	error = VOP_GETATTR(vp, vap, cred, p);
E 45
I 45
D 82
	nqsrv_getl(vp, NQL_READ);
	error = VOP_GETATTR(vp, vap, cred, nfsd->nd_procp);
E 82
I 82
		return (0);
	}
	nqsrv_getl(vp, ND_READ);
	error = VOP_GETATTR(vp, vap, cred, procp);
E 82
E 45
E 37
	vput(vp);
D 69
	nfsm_reply(NFSX_FATTR);
D 7
	nfsm_build(p, u_long *, NFSX_FATTR);
	*p++ = vtonfs_type(vap->va_type);
	*p++ = vtonfs_mode(vap->va_type, vap->va_mode);
	*p++ = txdr_unsigned(vap->va_nlink);
	*p++ = txdr_unsigned(vap->va_uid);
	*p++ = txdr_unsigned(vap->va_gid);
	*p++ = txdr_unsigned(vap->va_size);
	*p++ = txdr_unsigned(vap->va_blocksize);
	*p++ = txdr_unsigned(vap->va_rdev);
D 6
	*p++ = txdr_unsigned(vap->va_bytes);
E 6
I 6
	*p++ = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
E 6
	*p++ = txdr_unsigned(vap->va_fsid);
	*p++ = txdr_unsigned(vap->va_fileid);
	txdr_time(&(vap->va_atime), p);
	p += 2;
	txdr_time(&(vap->va_mtime), p);
	p += 2;
	txdr_time(&(vap->va_ctime), p);
E 7
I 7
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR);
E 69
I 69
D 82
	nfsm_reply(NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL));
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 69
D 11
	fp->fa_type = vtonfs_type(vap->va_type);
	fp->fa_mode = vtonfs_mode(vap->va_type, vap->va_mode);
	fp->fa_nlink = txdr_unsigned(vap->va_nlink);
	fp->fa_uid = txdr_unsigned(vap->va_uid);
	fp->fa_gid = txdr_unsigned(vap->va_gid);
	fp->fa_size = txdr_unsigned(vap->va_size);
	fp->fa_blocksize = txdr_unsigned(vap->va_blocksize);
	fp->fa_rdev = txdr_unsigned(vap->va_rdev);
	fp->fa_blocks = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
	fp->fa_fsid = txdr_unsigned(vap->va_fsid);
	fp->fa_fileid = txdr_unsigned(vap->va_fileid);
	txdr_time(&vap->va_atime, &fp->fa_atime);
	txdr_time(&vap->va_mtime, &fp->fa_mtime);
	txdr_time(&vap->va_ctime, &fp->fa_ctime);
E 11
I 11
	nfsm_srvfillattr;
E 82
I 82
	nfsm_reply(NFSX_FATTR(nfsd->nd_flag & ND_NFSV3));
	if (error)
		return (0);
	nfsm_build(fp, struct nfs_fattr *, NFSX_FATTR(nfsd->nd_flag & ND_NFSV3));
	nfsm_srvfillattr(vap, fp);
E 82
E 11
E 7
	nfsm_srvdone;
}

/*
 * nfs setattr service
 */
D 11
nfsrv_setattr(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_setattr(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_setattr(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf **mrq;
E 45
I 45
D 82
nfsrv_setattr(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
E 45
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
D 45
	u_long xid;
I 11
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_setattr(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 61
D 64
	USES_VOP_GETATTR;
	USES_VOP_SETATTR;
E 64
E 61
D 82
	struct vattr va;
E 82
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	struct vattr va, preat;
E 82
	register struct vattr *vap = &va;
I 7
	register struct nfsv2_sattr *sp;
D 82
	register struct nfsv2_fattr *fp;
E 82
I 82
	register struct nfs_fattr *fp;
E 82
E 7
	struct vnode *vp;
D 82
	nfsv2fh_t nfh;
E 82
I 82
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
D 9
	nfsm_srvars;
E 9
I 9
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 78
	int error = 0, rdonly, cache, duration2, cache2;
E 78
I 78
D 82
	int error = 0, rdonly, cache;
E 82
I 82
	int error = 0, rdonly, cache, preat_ret = 1, postat_ret = 1;
	int v3 = (nfsd->nd_flag & ND_NFSV3), gcheck = 0;
E 82
E 78
E 45
	char *cp2;
D 11
	struct mbuf *mb, *mb2;
E 11
I 11
	struct mbuf *mb, *mb2, *mreq;
I 45
D 82
	u_quad_t frev, frev2;
E 82
I 82
	u_quad_t frev;
	struct timespec guard;
E 82
E 45
E 11
E 9

	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 7
	nfsm_disect(p, u_long *, NFSX_SATTR);
E 7
I 7
D 45
	nfsm_disect(sp, struct nfsv2_sattr *, NFSX_SATTR);
E 7
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred))
E 45
I 45
D 69
	nfsm_dissect(sp, struct nfsv2_sattr *, NFSX_SATTR);
E 69
I 69
D 82
	nfsm_dissect(sp, struct nfsv2_sattr *, NFSX_SATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 69
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
E 45
		nfsm_reply(0);
D 4
	if (vp->v_mount->m_flag & (M_RDONLY | M_EXRDONLY)) {
		error = EROFS;
E 4
I 4
D 37
	if (error = nfsrv_access(vp, VWRITE, cred))
E 37
I 37
D 45
	if (error = nfsrv_access(vp, VWRITE, cred, p))
E 45
I 45
	nqsrv_getl(vp, NQL_WRITE);
E 82
D 74
	if (error = nfsrv_access(vp, VWRITE, cred, rdonly, nfsd->nd_procp))
E 45
E 37
E 4
		goto out;
E 74
D 4
	}
E 4
D 17
	vattr_null(vap);
E 17
I 17
	VATTR_NULL(vap);
E 17
D 82
	/*
	 * Nah nah nah nah na nah
	 * There is a bug in the Sun client that puts 0xffff in the mode
	 * field of sattr when it should put in 0xffffffff. The u_short
	 * doesn't sign extend.
	 * --> check the low order 2 bytes for 0xffff
	 */
D 7
	if ((fxdr_unsigned(int, *p) & 0xffff) != 0xffff)
		vap->va_mode = nfstov_mode(*p);
	if (*++p != nfs_xdrneg1)
		vap->va_uid = fxdr_unsigned(uid_t, *p);
	if (*++p != nfs_xdrneg1)
		vap->va_gid = fxdr_unsigned(gid_t, *p);
D 3
	if (*++p != nfs_xdrneg1)
E 3
I 3
	if (*++p != nfs_xdrneg1) {
E 3
		vap->va_size = fxdr_unsigned(u_long, *p);
E 7
I 7
	if ((fxdr_unsigned(int, sp->sa_mode) & 0xffff) != 0xffff)
		vap->va_mode = nfstov_mode(sp->sa_mode);
	if (sp->sa_uid != nfs_xdrneg1)
		vap->va_uid = fxdr_unsigned(uid_t, sp->sa_uid);
	if (sp->sa_gid != nfs_xdrneg1)
		vap->va_gid = fxdr_unsigned(gid_t, sp->sa_gid);
D 11
	if (sp->sa_size != nfs_xdrneg1) {
E 11
I 11
D 69
	if (sp->sa_size != nfs_xdrneg1)
E 11
		vap->va_size = fxdr_unsigned(u_long, sp->sa_size);
I 11
	/*
	 * The usec field of sa_atime is overloaded with the va_flags field
	 * for 4.4BSD clients. Hopefully other clients always set both the
	 * sec and usec fields to -1 when not setting the atime.
	 */
	if (sp->sa_atime.tv_sec != nfs_xdrneg1) {
D 62
		vap->va_atime.tv_sec = fxdr_unsigned(long, sp->sa_atime.tv_sec);
		vap->va_atime.tv_usec = 0;
E 62
I 62
		vap->va_atime.ts_sec = fxdr_unsigned(long, sp->sa_atime.tv_sec);
		vap->va_atime.ts_nsec = 0;
E 69
I 69
	if (nfsd->nd_nqlflag == NQL_NOVAL) {
		if (sp->sa_nfssize != nfs_xdrneg1)
			vap->va_size = fxdr_unsigned(u_quad_t, sp->sa_nfssize);
D 73
		/*
		 * The usec field of sa_atime is overloaded with the va_flags field
		 * for 4.4BSD clients. Hopefully other clients always set both the
		 * sec and usec fields to -1 when not setting the atime.
		 */
E 73
		if (sp->sa_nfsatime.nfs_sec != nfs_xdrneg1) {
E 82
I 82
	if (v3) {
		nfsm_srvsattr(vap);
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
		gcheck = fxdr_unsigned(int, *tl);
		if (gcheck) {
			nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
			fxdr_nfsv3time(tl, &guard);
		}
	} else {
		nfsm_dissect(sp, struct nfsv2_sattr *, NFSX_V2SATTR);
		/*
		 * Nah nah nah nah na nah
		 * There is a bug in the Sun client that puts 0xffff in the mode
		 * field of sattr when it should put in 0xffffffff. The u_short
		 * doesn't sign extend.
		 * --> check the low order 2 bytes for 0xffff
		 */
		if ((fxdr_unsigned(int, sp->sa_mode) & 0xffff) != 0xffff)
			vap->va_mode = nfstov_mode(sp->sa_mode);
		if (sp->sa_uid != nfs_xdrneg1)
			vap->va_uid = fxdr_unsigned(uid_t, sp->sa_uid);
		if (sp->sa_gid != nfs_xdrneg1)
			vap->va_gid = fxdr_unsigned(gid_t, sp->sa_gid);
		if (sp->sa_size != nfs_xdrneg1)
			vap->va_size = fxdr_unsigned(u_quad_t, sp->sa_size);
		if (sp->sa_atime.nfsv2_sec != nfs_xdrneg1) {
E 82
D 73
			vap->va_atime.ts_sec = fxdr_unsigned(long, sp->sa_nfsatime.nfs_sec);
E 73
I 73
#ifdef notyet
D 82
			fxdr_nfstime(&sp->sa_nfsatime, &vap->va_atime);
E 82
I 82
			fxdr_nfsv2time(&sp->sa_atime, &vap->va_atime);
E 82
#else
			vap->va_atime.ts_sec =
D 82
				fxdr_unsigned(long, sp->sa_nfsatime.nfs_sec);
E 82
I 82
				fxdr_unsigned(long, sp->sa_atime.nfsv2_sec);
E 82
E 73
			vap->va_atime.ts_nsec = 0;
I 73
#endif
E 73
		}
D 73
		if (sp->sa_nfsatime.nfs_usec != nfs_xdrneg1)
			vap->va_flags = fxdr_unsigned(u_long, sp->sa_nfsatime.nfs_usec);
E 73
D 82
		if (sp->sa_nfsmtime.nfs_sec != nfs_xdrneg1)
			fxdr_nfstime(&sp->sa_nfsmtime, &vap->va_mtime);
	} else {
		fxdr_hyper(&sp->sa_nqsize, &vap->va_size);
		fxdr_nqtime(&sp->sa_nqatime, &vap->va_atime);
		fxdr_nqtime(&sp->sa_nqmtime, &vap->va_mtime);
		vap->va_flags = fxdr_unsigned(u_long, sp->sa_nqflags);
E 82
I 82
		if (sp->sa_mtime.nfsv2_sec != nfs_xdrneg1)
			fxdr_nfsv2time(&sp->sa_mtime, &vap->va_mtime);

E 82
I 74
	}

	/*
I 82
	 * Now that we have all the fields, lets do it.
	 */
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
		nfsm_reply(2 * NFSX_UNSIGNED);
		nfsm_srvwcc_data(preat_ret, &preat, postat_ret, vap);
		return (0);
	}
	nqsrv_getl(vp, ND_WRITE);
	if (v3) {
		error = preat_ret = VOP_GETATTR(vp, &preat, cred, procp);
		if (!error && gcheck &&
			(preat.va_ctime.ts_sec != guard.ts_sec ||
			 preat.va_ctime.ts_nsec != guard.ts_nsec))
			error = NFSERR_NOT_SYNC;
		if (error) {
			vput(vp);
			nfsm_reply(NFSX_WCCDATA(v3));
			nfsm_srvwcc_data(preat_ret, &preat, postat_ret, vap);
			return (0);
		}
	}

	/*
E 82
	 * If the size is being changed write acces is required, otherwise
	 * just check for a read only file system.
	 */
	if (vap->va_size == ((u_quad_t)((quad_t) -1))) {
		if (rdonly || (vp->v_mount->mnt_flag & MNT_RDONLY)) {
			error = EROFS;
			goto out;
		}
	} else {
		if (vp->v_type == VDIR) {
			error = EISDIR;
			goto out;
		} else if (error = nfsrv_access(vp, VWRITE, cred, rdonly,
D 82
			nfsd->nd_procp))
E 82
I 82
			procp))
E 82
			goto out;
E 74
E 69
E 62
E 11
E 7
I 3
	}
E 3
D 7
	if (*++p != nfs_xdrneg1)
		fxdr_time(p, &(vap->va_atime));
	p += 2;
	if (*p != nfs_xdrneg1)
		fxdr_time(p, &(vap->va_mtime));
E 7
I 7
D 11
	if (sp->sa_atime.tv_sec != nfs_xdrneg1)
		fxdr_time(&sp->sa_atime, &vap->va_atime);
E 11
I 11
D 69
	if (sp->sa_atime.tv_usec != nfs_xdrneg1)
		vap->va_flags = fxdr_unsigned(u_long, sp->sa_atime.tv_usec);
E 11
	if (sp->sa_mtime.tv_sec != nfs_xdrneg1)
		fxdr_time(&sp->sa_mtime, &vap->va_mtime);
E 69
E 7
D 37
	if (error = VOP_SETATTR(vp, vap, cred)) {
E 37
I 37
D 45
	if (error = VOP_SETATTR(vp, vap, cred, p)) {
E 45
I 45
D 82
	if (error = VOP_SETATTR(vp, vap, cred, nfsd->nd_procp)) {
E 45
E 37
		vput(vp);
		nfsm_reply(0);
	}
D 37
	error = VOP_GETATTR(vp, vap, cred);
E 37
I 37
D 45
	error = VOP_GETATTR(vp, vap, cred, p);
E 45
I 45
	error = VOP_GETATTR(vp, vap, cred, nfsd->nd_procp);
E 82
I 82
	error = VOP_SETATTR(vp, vap, cred, procp);
	postat_ret = VOP_GETATTR(vp, vap, cred, procp);
	if (!error)
		error = postat_ret;
E 82
E 45
E 37
out:
	vput(vp);
D 45
	nfsm_reply(NFSX_FATTR);
E 45
I 45
D 69
	nfsm_reply(NFSX_FATTR + 2*NFSX_UNSIGNED);
E 45
D 7
	nfsm_build(p, u_long *, NFSX_FATTR);
	*p++ = vtonfs_type(vap->va_type);
	*p++ = vtonfs_mode(vap->va_type, vap->va_mode);
	*p++ = txdr_unsigned(vap->va_nlink);
	*p++ = txdr_unsigned(vap->va_uid);
	*p++ = txdr_unsigned(vap->va_gid);
	*p++ = txdr_unsigned(vap->va_size);
	*p++ = txdr_unsigned(vap->va_blocksize);
	*p++ = txdr_unsigned(vap->va_rdev);
D 6
	*p++ = txdr_unsigned(vap->va_bytes);
E 6
I 6
	*p++ = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
E 6
	*p++ = txdr_unsigned(vap->va_fsid);
	*p++ = txdr_unsigned(vap->va_fileid);
	txdr_time(&(vap->va_atime), p);
	p += 2;
	txdr_time(&(vap->va_mtime), p);
	p += 2;
	txdr_time(&(vap->va_ctime), p);
E 7
I 7
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR);
E 69
I 69
D 82
	nfsm_reply(NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL) + 2*NFSX_UNSIGNED);
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 69
D 11
	fp->fa_type = vtonfs_type(vap->va_type);
	fp->fa_mode = vtonfs_mode(vap->va_type, vap->va_mode);
	fp->fa_nlink = txdr_unsigned(vap->va_nlink);
	fp->fa_uid = txdr_unsigned(vap->va_uid);
	fp->fa_gid = txdr_unsigned(vap->va_gid);
	fp->fa_size = txdr_unsigned(vap->va_size);
	fp->fa_blocksize = txdr_unsigned(vap->va_blocksize);
	fp->fa_rdev = txdr_unsigned(vap->va_rdev);
	fp->fa_blocks = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
	fp->fa_fsid = txdr_unsigned(vap->va_fsid);
	fp->fa_fileid = txdr_unsigned(vap->va_fileid);
	txdr_time(&vap->va_atime, &fp->fa_atime);
	txdr_time(&vap->va_mtime, &fp->fa_mtime);
	txdr_time(&vap->va_ctime, &fp->fa_ctime);
E 11
I 11
	nfsm_srvfillattr;
I 45
	if (nfsd->nd_nqlflag != NQL_NOVAL) {
		nfsm_build(tl, u_long *, 2*NFSX_UNSIGNED);
		txdr_hyper(&frev2, tl);
E 82
I 82
	nfsm_reply(NFSX_WCCORFATTR(v3));
	if (v3) {
		nfsm_srvwcc_data(preat_ret, &preat, postat_ret, vap);
		return (0);
	} else {
		nfsm_build(fp, struct nfs_fattr *, NFSX_V2FATTR);
		nfsm_srvfillattr(vap, fp);
E 82
	}
E 45
E 11
E 7
	nfsm_srvdone;
}

/*
 * nfs lookup rpc
 */
D 11
nfsrv_lookup(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_lookup(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_lookup(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf **mrq;
E 45
I 45
D 82
nfsrv_lookup(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
E 45
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
D 45
	u_long xid;
I 11
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_lookup(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 61
D 64
	USES_VOP_GETATTR;
E 64
E 61
I 7
D 82
	register struct nfsv2_fattr *fp;
E 82
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	register struct nfs_fattr *fp;
E 82
E 7
D 8
	register struct nameidata *ndp = &u.u_nd;
E 8
I 8
D 41
	struct nameidata nami;
	register struct nameidata *ndp = &nami;
E 41
I 41
	struct nameidata nd;
E 41
E 8
D 82
	struct vnode *vp;
	nfsv2fh_t nfh;
E 82
I 82
	struct vnode *vp, *dirp;
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
D 9
	nfsm_srvars;
E 9
I 9
	register caddr_t cp;
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 69
	int error = 0, lflag = 0, rdonly, cache, duration2, cache2, len;
E 69
I 69
D 78
	int error = 0, rdonly, cache, duration2, cache2, len;
E 78
I 78
D 82
	int error = 0, cache, duration2, cache2, len;
E 82
I 82
	int error = 0, cache, len, dirattr_ret = 1;
	int v3 = (nfsd->nd_flag & ND_NFSV3);
E 82
E 78
E 69
E 45
	char *cp2;
D 11
	struct mbuf *mb, *mb2;
E 11
I 11
	struct mbuf *mb, *mb2, *mreq;
E 11
E 9
D 45
	long len;
E 45
D 82
	struct vattr va, *vap = &va;
I 45
	u_quad_t frev, frev2;
E 82
I 82
	struct vattr va, dirattr, *vap = &va;
	u_quad_t frev;
E 82
E 45

I 8
D 41
	ndinit(ndp);
E 41
E 8
	fhp = &nfh.fh_generic;
I 71
D 82
	duration2 = 0;
E 71
I 45
	if (nfsd->nd_nqlflag != NQL_NOVAL) {
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
D 69
		if (*tl) {
			lflag = fxdr_unsigned(int, *tl);
			nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
			duration2 = fxdr_unsigned(int, *tl);
		}
E 69
I 69
		duration2 = fxdr_unsigned(int, *tl);
E 69
	}
E 82
E 45
	nfsm_srvmtofh(fhp);
D 82
	nfsm_srvstrsiz(len, NFS_MAXNAMLEN);
E 82
I 82
	nfsm_srvnamesiz(len);
E 82
D 41
	ndp->ni_cred = cred;
	ndp->ni_nameiop = LOOKUP | LOCKLEAF;
D 3
	ndp->ni_segflg = UIO_SYSSPACE;
E 3
	if (error = nfs_namei(ndp, fhp, len, &md, &dpos))
E 41
I 41
D 47
	nd.ni_cred = cred;
D 45
	nd.ni_nameiop = LOOKUP | LOCKLEAF;
	if (error = nfs_namei(&nd, fhp, len, &md, &dpos, p))
E 45
I 45
	nd.ni_nameiop = LOOKUP | LOCKLEAF | SAVESTART;
E 47
I 47
	nd.ni_cnd.cn_cred = cred;
	nd.ni_cnd.cn_nameiop = LOOKUP;
	nd.ni_cnd.cn_flags = LOCKLEAF | SAVESTART;
E 47
D 50
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos, nfsd->nd_procp))
E 50
I 50
D 82
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos,
	    nfsd->nd_procp))
E 50
E 45
E 41
		nfsm_reply(0);
I 45
	nqsrv_getl(nd.ni_startdir, NQL_READ);
E 82
I 82
	error = nfs_namei(&nd, fhp, len, slp, nam, &md, &dpos,
		&dirp, procp, (nfsd->nd_flag & ND_KERBAUTH));
	if (dirp) {
		if (v3)
			dirattr_ret = VOP_GETATTR(dirp, &dirattr, cred,
				procp);
		vrele(dirp);
	}
	if (error) {
		nfsm_reply(NFSX_POSTOPATTR(v3));
		nfsm_srvpostop_attr(dirattr_ret, &dirattr);
		return (0);
	}
	nqsrv_getl(nd.ni_startdir, ND_READ);
E 82
	vrele(nd.ni_startdir);
I 50
	FREE(nd.ni_cnd.cn_pnbuf, M_NAMEI);
E 50
E 45
D 41
	vp = ndp->ni_vp;
E 41
I 41
	vp = nd.ni_vp;
E 41
	bzero((caddr_t)fhp, sizeof(nfh));
D 16
	fhp->fh_fsid = vp->v_mount->m_fsid;
E 16
I 16
D 18
	fhp->fh_fsid = vp->v_mount->m_stat.f_fsid;
E 18
I 18
	fhp->fh_fsid = vp->v_mount->mnt_stat.f_fsid;
E 18
E 16
D 82
	if (error = VFS_VPTOFH(vp, &fhp->fh_fid)) {
		vput(vp);
		nfsm_reply(0);
	}
D 37
	error = VOP_GETATTR(vp, vap, cred);
E 37
I 37
D 45
	error = VOP_GETATTR(vp, vap, cred, p);
E 45
I 45
D 69
	if (lflag)
		(void) nqsrv_getlease(vp, &duration2, lflag, nfsd,
E 69
I 69
	if (duration2)
		(void) nqsrv_getlease(vp, &duration2, NQL_READ, nfsd,
E 69
			nam, &cache2, &frev2, cred);
	error = VOP_GETATTR(vp, vap, cred, nfsd->nd_procp);
E 82
I 82
	error = VFS_VPTOFH(vp, &fhp->fh_fid);
	if (!error)
		error = VOP_GETATTR(vp, vap, cred, procp);
E 82
E 45
E 37
	vput(vp);
D 45
	nfsm_reply(NFSX_FH+NFSX_FATTR);
E 45
I 45
D 69
	nfsm_reply(NFSX_FH + NFSX_FATTR + 5*NFSX_UNSIGNED);
E 69
I 69
D 82
	nfsm_reply(NFSX_FH + NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL) + 5*NFSX_UNSIGNED);
E 69
	if (nfsd->nd_nqlflag != NQL_NOVAL) {
D 69
		if (lflag) {
E 69
I 69
		if (duration2) {
E 69
			nfsm_build(tl, u_long *, 5*NFSX_UNSIGNED);
D 69
			*tl++ = txdr_unsigned(lflag);
E 69
I 69
			*tl++ = txdr_unsigned(NQL_READ);
E 69
			*tl++ = txdr_unsigned(cache2);
			*tl++ = txdr_unsigned(duration2);
			txdr_hyper(&frev2, tl);
		} else {
			nfsm_build(tl, u_long *, NFSX_UNSIGNED);
			*tl = 0;
		}
E 82
I 82
	nfsm_reply(NFSX_SRVFH(v3) + NFSX_POSTOPORFATTR(v3) + NFSX_POSTOPATTR(v3));
	if (error) {
		nfsm_srvpostop_attr(dirattr_ret, &dirattr);
		return (0);
E 82
	}
E 45
D 82
	nfsm_srvfhtom(fhp);
D 7
	nfsm_build(p, u_long *, NFSX_FATTR);
	*p++ = vtonfs_type(vap->va_type);
	*p++ = vtonfs_mode(vap->va_type, vap->va_mode);
	*p++ = txdr_unsigned(vap->va_nlink);
	*p++ = txdr_unsigned(vap->va_uid);
	*p++ = txdr_unsigned(vap->va_gid);
	*p++ = txdr_unsigned(vap->va_size);
	*p++ = txdr_unsigned(vap->va_blocksize);
	*p++ = txdr_unsigned(vap->va_rdev);
D 6
	*p++ = txdr_unsigned(vap->va_bytes);
E 6
I 6
	*p++ = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
E 6
	*p++ = txdr_unsigned(vap->va_fsid);
	*p++ = txdr_unsigned(vap->va_fileid);
	txdr_time(&(vap->va_atime), p);
	p += 2;
	txdr_time(&(vap->va_mtime), p);
	p += 2;
	txdr_time(&(vap->va_ctime), p);
E 7
I 7
D 69
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR);
E 69
I 69
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 69
D 11
	fp->fa_type = vtonfs_type(vap->va_type);
	fp->fa_mode = vtonfs_mode(vap->va_type, vap->va_mode);
	fp->fa_nlink = txdr_unsigned(vap->va_nlink);
	fp->fa_uid = txdr_unsigned(vap->va_uid);
	fp->fa_gid = txdr_unsigned(vap->va_gid);
	fp->fa_size = txdr_unsigned(vap->va_size);
	fp->fa_blocksize = txdr_unsigned(vap->va_blocksize);
	fp->fa_rdev = txdr_unsigned(vap->va_rdev);
	fp->fa_blocks = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
	fp->fa_fsid = txdr_unsigned(vap->va_fsid);
	fp->fa_fileid = txdr_unsigned(vap->va_fileid);
	txdr_time(&vap->va_atime, &fp->fa_atime);
	txdr_time(&vap->va_mtime, &fp->fa_mtime);
	txdr_time(&vap->va_ctime, &fp->fa_ctime);
E 11
I 11
	nfsm_srvfillattr;
E 82
I 82
	nfsm_srvfhtom(fhp, v3);
	if (v3) {
		nfsm_srvpostop_attr(0, vap);
		nfsm_srvpostop_attr(dirattr_ret, &dirattr);
	} else {
		nfsm_build(fp, struct nfs_fattr *, NFSX_V2FATTR);
		nfsm_srvfillattr(vap, fp);
	}
E 82
E 11
E 7
	nfsm_srvdone;
}

/*
 * nfs readlink service
 */
D 11
nfsrv_readlink(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_readlink(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_readlink(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf **mrq;
E 45
I 45
D 82
nfsrv_readlink(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
E 45
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
D 11
	long xid;
E 11
I 11
D 45
	u_long xid;
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_readlink(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
I 61
D 64
	USES_VOP_READLINK;
E 64
E 61
D 19
	struct iovec iv[NFS_MAXPATHLEN/MLEN+1];
E 19
I 19
	struct iovec iv[(NFS_MAXPATHLEN+MLEN-1)/MLEN];
E 19
	register struct iovec *ivp = iv;
	register struct mbuf *mp;
D 9
	nfsm_srvars;
	struct mbuf *mp2, *mp3;
E 9
I 9
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 82
	int error = 0, rdonly, cache, i, tlen, len;
E 82
I 82
	int error = 0, rdonly, cache, i, tlen, len, getret;
	int v3 = (nfsd->nd_flag & ND_NFSV3);
E 82
E 45
	char *cp2;
D 11
	struct mbuf *mb, *mb2, *mp2, *mp3;
E 11
I 11
	struct mbuf *mb, *mb2, *mp2, *mp3, *mreq;
E 11
E 9
	struct vnode *vp;
D 82
	nfsv2fh_t nfh;
E 82
I 82
	struct vattr attr;
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
	struct uio io, *uiop = &io;
D 45
	int i, tlen, len;
E 45
I 45
	u_quad_t frev;
E 45

I 82
#ifndef nolint
	mp2 = mp3 = (struct mbuf *)0;
#endif
E 82
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
	len = 0;
	i = 0;
	while (len < NFS_MAXPATHLEN) {
		MGET(mp, M_WAIT, MT_DATA);
D 19
		NFSMCLGET(mp, M_WAIT);
E 19
I 19
		MCLGET(mp, M_WAIT);
E 19
		mp->m_len = NFSMSIZ(mp);
		if (len == 0)
			mp3 = mp2 = mp;
D 19
		else
E 19
I 19
		else {
E 19
			mp2->m_next = mp;
I 19
			mp2 = mp;
		}
E 19
		if ((len+mp->m_len) > NFS_MAXPATHLEN) {
			mp->m_len = NFS_MAXPATHLEN-len;
			len = NFS_MAXPATHLEN;
		} else
			len += mp->m_len;
		ivp->iov_base = mtod(mp, caddr_t);
		ivp->iov_len = mp->m_len;
		i++;
		ivp++;
	}
	uiop->uio_iov = iv;
	uiop->uio_iovcnt = i;
	uiop->uio_offset = 0;
	uiop->uio_resid = len;
	uiop->uio_rw = UIO_READ;
	uiop->uio_segflg = UIO_SYSSPACE;
I 37
	uiop->uio_procp = (struct proc *)0;
E 37
D 45
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred)) {
E 45
I 45
D 82
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred, nfsd->nd_slp, nam, &rdonly)) {
E 82
I 82
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
E 82
E 45
		m_freem(mp3);
D 82
		nfsm_reply(0);
E 82
I 82
		nfsm_reply(2 * NFSX_UNSIGNED);
		nfsm_srvpostop_attr(1, (struct vattr *)0);
		return (0);
E 82
	}
	if (vp->v_type != VLNK) {
D 82
		error = EINVAL;
E 82
I 82
		if (v3)
			error = EINVAL;
		else
			error = ENXIO;
E 82
		goto out;
	}
I 45
D 82
	nqsrv_getl(vp, NQL_READ);
E 82
I 82
	nqsrv_getl(vp, ND_READ);
E 82
E 45
	error = VOP_READLINK(vp, uiop, cred);
out:
I 82
	getret = VOP_GETATTR(vp, &attr, cred, procp);
E 82
	vput(vp);
	if (error)
		m_freem(mp3);
D 82
	nfsm_reply(NFSX_UNSIGNED);
E 82
I 82
	nfsm_reply(NFSX_POSTOPATTR(v3) + NFSX_UNSIGNED);
	if (v3) {
		nfsm_srvpostop_attr(getret, &attr);
		if (error)
			return (0);
	}
E 82
	if (uiop->uio_resid > 0) {
		len -= uiop->uio_resid;
		tlen = nfsm_rndup(len);
		nfsm_adj(mp3, NFS_MAXPATHLEN-tlen, tlen-len);
	}
D 37
	nfsm_build(p, u_long *, NFSX_UNSIGNED);
	*p = txdr_unsigned(len);
E 37
I 37
	nfsm_build(tl, u_long *, NFSX_UNSIGNED);
	*tl = txdr_unsigned(len);
E 37
	mb->m_next = mp3;
	nfsm_srvdone;
}

/*
 * nfs read service
 */
D 11
nfsrv_read(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_read(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_read(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf **mrq;
E 45
I 45
D 82
nfsrv_read(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
E 45
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
D 45
	u_long xid;
I 11
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_read(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
I 61
D 64
	USES_VOP_GETATTR;
	USES_VOP_READ;
E 64
E 61
D 19
	struct iovec iv[NFS_MAXDATA/MCLBYTES+1];
	register struct iovec *ivp = iv;
	register struct mbuf *mp;
E 19
I 19
D 24
	struct iovec iv[(NFS_MAXDATA+MLEN-1)/MLEN];
E 24
I 24
	register struct iovec *iv;
	struct iovec *iv2;
E 24
	register struct mbuf *m;
E 19
I 7
D 82
	register struct nfsv2_fattr *fp;
E 82
I 82
	register struct nfs_fattr *fp;
E 82
E 7
D 9
	nfsm_srvars;
E 9
I 9
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
I 82
	register int i;
E 82
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 82
	int error = 0, rdonly, cache, i, cnt, len, left, siz, tlen;
E 82
I 82
	int error = 0, rdonly, cache, cnt, len, left, siz, tlen, getret;
	int v3 = (nfsd->nd_flag & ND_NFSV3), reqlen;
E 82
E 45
	char *cp2;
D 11
	struct mbuf *mb, *mb2;
E 11
I 11
	struct mbuf *mb, *mb2, *mreq;
E 11
E 9
D 19
	struct mbuf *mp2, *mp3;
E 19
I 19
D 45
	struct mbuf *m2, *m3;
E 45
I 45
	struct mbuf *m2;
E 45
E 19
	struct vnode *vp;
D 82
	nfsv2fh_t nfh;
E 82
I 82
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
	struct uio io, *uiop = &io;
	struct vattr va, *vap = &va;
D 19
	int i, tlen, cnt, len, nio, left;
E 19
I 19
D 45
	int i, cnt, len, left, siz, tlen;
E 45
E 19
	off_t off;
I 45
	u_quad_t frev;
E 45

	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 37
	nfsm_disect(p, u_long *, NFSX_UNSIGNED);
	off = fxdr_unsigned(off_t, *p);
E 37
I 37
D 45
	nfsm_disect(tl, u_long *, NFSX_UNSIGNED);
E 45
I 45
D 69
	nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
E 45
	off = fxdr_unsigned(off_t, *tl);
E 69
I 69
D 82
	if (nfsd->nd_nqlflag == NQL_NOVAL) {
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
		off = (off_t)fxdr_unsigned(u_long, *tl);
	} else {
E 82
I 82
	if (v3) {
E 82
		nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
		fxdr_hyper(tl, &off);
I 82
	} else {
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
		off = (off_t)fxdr_unsigned(u_long, *tl);
E 82
	}
E 69
E 37
D 82
	nfsm_srvstrsiz(cnt, NFS_MAXDATA);
D 45
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred))
E 45
I 45
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
E 45
		nfsm_reply(0);
E 82
I 82
	nfsm_srvstrsiz(reqlen, NFS_SRVMAXDATA(nfsd));
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
		nfsm_reply(2 * NFSX_UNSIGNED);
		nfsm_srvpostop_attr(1, (struct vattr *)0);
		return (0);
	}
E 82
I 75
	if (vp->v_type != VREG) {
D 82
		error = (vp->v_type == VDIR) ? EISDIR : EACCES;
		vput(vp);
		nfsm_reply(0);
E 82
I 82
		if (v3)
			error = EINVAL;
		else
			error = (vp->v_type == VDIR) ? EISDIR : EACCES;
E 82
	}
E 75
D 2
	if (error = vn_access(vp, VREAD | VEXEC, cred)) {
E 2
I 2
D 4
	if (error = VOP_ACCESS(vp, VREAD | VEXEC, cred)) {
E 4
I 4
D 37
	if (error = nfsrv_access(vp, VREAD | VEXEC, cred)) {
E 37
I 37
D 45
	if (error = nfsrv_access(vp, VREAD | VEXEC, cred, p)) {
E 45
I 45
D 82
	nqsrv_getl(vp, NQL_READ);
D 72
	if (error = nfsrv_access(vp, VREAD | VEXEC, cred, rdonly, nfsd->nd_procp)) {
E 72
I 72
	if ((error = nfsrv_access(vp, VREAD, cred, rdonly, nfsd->nd_procp)) &&
	    (error = nfsrv_access(vp, VEXEC, cred, rdonly, nfsd->nd_procp))) {
E 72
E 45
E 37
E 4
E 2
		vput(vp);
		nfsm_reply(0);
E 82
I 82
	if (!error) {
	    nqsrv_getl(vp, ND_READ);
	    if (error = nfsrv_access(vp, VREAD, cred, rdonly, procp))
		error = nfsrv_access(vp, VEXEC, cred, rdonly, procp);
E 82
	}
D 45
	len = left = cnt;
D 19
	nio = (cnt+MCLBYTES-1)/MCLBYTES;
	uiop->uio_iov = ivp;
	uiop->uio_iovcnt = nio;
E 19
I 19
	/*
	 * Generate the mbuf list with the uio_iov ref. to it.
	 */
	i = 0;
	m3 = (struct mbuf *)0;
I 20
#ifdef lint
	m2 = (struct mbuf *)0;
#endif /* lint */
I 24
	MALLOC(iv, struct iovec *,
	       ((NFS_MAXDATA+MLEN-1)/MLEN) * sizeof (struct iovec), M_TEMP,
	       M_WAITOK);
	iv2 = iv;
E 24
E 20
	while (left > 0) {
		MGET(m, M_WAIT, MT_DATA);
		if (left > MINCLSIZE)
			MCLGET(m, M_WAIT);
		m->m_len = 0;
		siz = min(M_TRAILINGSPACE(m), left);
		m->m_len = siz;
D 24
		iv[i].iov_base = mtod(m, caddr_t);
		iv[i].iov_len = siz;
E 24
I 24
		iv->iov_base = mtod(m, caddr_t);
		iv->iov_len = siz;
		iv++;
E 24
		i++;
		left -= siz;
		if (m3) {
			m2->m_next = m;
			m2 = m;
		} else
			m3 = m2 = m;
	}
D 24
	uiop->uio_iov = iv;
E 24
I 24
	uiop->uio_iov = iv2;
E 24
	uiop->uio_iovcnt = i;
E 19
	uiop->uio_offset = off;
	uiop->uio_resid = cnt;
	uiop->uio_rw = UIO_READ;
	uiop->uio_segflg = UIO_SYSSPACE;
I 37
	uiop->uio_procp = (struct proc *)0;
E 37
D 19
	for (i = 0; i < nio; i++) {
		MGET(mp, M_WAIT, MT_DATA);
		if (left > MLEN)
			NFSMCLGET(mp, M_WAIT);
		mp->m_len = (M_HASCL(mp)) ? MCLBYTES : MLEN;
		if (i == 0) {
			mp3 = mp2 = mp;
		} else {
			mp2->m_next = mp;
			mp2 = mp;
		}
		if (left > MLEN && !M_HASCL(mp)) {
			m_freem(mp3);
			vput(vp);
			nfsm_srverr;
		}
		ivp->iov_base = mtod(mp, caddr_t);
		if (left > mp->m_len) {
			ivp->iov_len = mp->m_len;
			left -= mp->m_len;
		} else {
			ivp->iov_len = mp->m_len = left;
			left = 0;
		}
		ivp++;
	}
E 19
D 10
	error = VOP_READ(vp, uiop, &off, IO_NODELOCKED, cred);
E 10
I 10
	error = VOP_READ(vp, uiop, IO_NODELOCKED, cred);
	off = uiop->uio_offset;
I 24
	FREE((caddr_t)iv2, M_TEMP);
E 24
E 10
	if (error) {
D 19
		m_freem(mp3);
E 19
I 19
		m_freem(m3);
E 45
I 45
D 82
	if (error = VOP_GETATTR(vp, vap, cred, nfsd->nd_procp)) {
E 82
I 82
	getret = VOP_GETATTR(vp, vap, cred, procp);
	if (!error)
		error = getret;
	if (error) {
E 82
E 45
E 19
		vput(vp);
D 82
		nfsm_reply(0);
E 82
I 82
		nfsm_reply(NFSX_POSTOPATTR(v3));
		nfsm_srvpostop_attr(getret, vap);
		return (0);
E 82
	}
D 37
	if (error = VOP_GETATTR(vp, vap, cred))
E 37
I 37
D 45
	if (error = VOP_GETATTR(vp, vap, cred, p))
E 37
D 19
		m_freem(mp3);
E 19
I 19
		m_freem(m3);
E 19
	vput(vp);
	nfsm_reply(NFSX_FATTR+NFSX_UNSIGNED);
E 45
I 45
	if (off >= vap->va_size)
		cnt = 0;
D 82
	else if ((off + cnt) > vap->va_size)
E 82
I 82
	else if ((off + reqlen) > vap->va_size)
E 82
		cnt = nfsm_rndup(vap->va_size - off);
D 69
	nfsm_reply(NFSX_FATTR+NFSX_UNSIGNED+nfsm_rndup(cnt));
E 45
D 7
	nfsm_build(p, u_long *, NFSX_FATTR+NFSX_UNSIGNED);
	*p++ = vtonfs_type(vap->va_type);
	*p++ = vtonfs_mode(vap->va_type, vap->va_mode);
	*p++ = txdr_unsigned(vap->va_nlink);
	*p++ = txdr_unsigned(vap->va_uid);
	*p++ = txdr_unsigned(vap->va_gid);
	*p++ = txdr_unsigned(vap->va_size);
	*p++ = txdr_unsigned(vap->va_blocksize);
	*p++ = txdr_unsigned(vap->va_rdev);
D 6
	*p++ = txdr_unsigned(vap->va_bytes);
E 6
I 6
	*p++ = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
E 6
	*p++ = txdr_unsigned(vap->va_fsid);
	*p++ = txdr_unsigned(vap->va_fileid);
	txdr_time(&(vap->va_atime), p);
	p += 2;
	txdr_time(&(vap->va_mtime), p);
	p += 2;
	txdr_time(&(vap->va_ctime), p);
	p += 2;
E 7
I 7
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR);
E 69
I 69
D 82
	nfsm_reply(NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL)+NFSX_UNSIGNED+nfsm_rndup(cnt));
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 69
I 45
	nfsm_build(tl, u_long *, NFSX_UNSIGNED);
E 82
I 82
	else
		cnt = reqlen;
	nfsm_reply(NFSX_POSTOPORFATTR(v3) + 3 * NFSX_UNSIGNED+nfsm_rndup(cnt));
	if (v3) {
		nfsm_build(tl, u_long *, NFSX_V3FATTR + 4 * NFSX_UNSIGNED);
		*tl++ = nfs_true;
		fp = (struct nfs_fattr *)tl;
		tl += (NFSX_V3FATTR / sizeof (u_long));
	} else {
		nfsm_build(tl, u_long *, NFSX_V2FATTR + NFSX_UNSIGNED);
		fp = (struct nfs_fattr *)tl;
		tl += (NFSX_V2FATTR / sizeof (u_long));
	}
E 82
	len = left = cnt;
	if (cnt > 0) {
		/*
		 * Generate the mbuf list with the uio_iov ref. to it.
		 */
		i = 0;
		m = m2 = mb;
D 82
		MALLOC(iv, struct iovec *,
		       ((NFS_MAXDATA+MLEN-1)/MLEN) * sizeof (struct iovec),
		       M_TEMP, M_WAITOK);
		iv2 = iv;
E 82
		while (left > 0) {
D 65
			siz = MIN(M_TRAILINGSPACE(m), left);
E 65
I 65
			siz = min(M_TRAILINGSPACE(m), left);
E 65
			if (siz > 0) {
D 82
				m->m_len += siz;
				iv->iov_base = bpos;
				iv->iov_len = siz;
				iv++;
				i++;
E 82
				left -= siz;
I 82
				i++;
E 82
			}
			if (left > 0) {
				MGET(m, M_WAIT, MT_DATA);
				MCLGET(m, M_WAIT);
				m->m_len = 0;
				m2->m_next = m;
				m2 = m;
D 82
				bpos = mtod(m, caddr_t);
E 82
			}
		}
D 82
		uiop->uio_iov = iv2;
E 82
I 82
		MALLOC(iv, struct iovec *, i * sizeof (struct iovec),
		       M_TEMP, M_WAITOK);
		uiop->uio_iov = iv2 = iv;
		m = mb;
		left = cnt;
		i = 0;
		while (left > 0) {
			if (m == NULL)
				panic("nfsrv_read iov");
			siz = min(M_TRAILINGSPACE(m), left);
			if (siz > 0) {
				iv->iov_base = mtod(m, caddr_t) + m->m_len;
				iv->iov_len = siz;
				m->m_len += siz;
				left -= siz;
				iv++;
				i++;
			}
			m = m->m_next;
		}
E 82
		uiop->uio_iovcnt = i;
		uiop->uio_offset = off;
		uiop->uio_resid = cnt;
		uiop->uio_rw = UIO_READ;
		uiop->uio_segflg = UIO_SYSSPACE;
		error = VOP_READ(vp, uiop, IO_NODELOCKED, cred);
		off = uiop->uio_offset;
		FREE((caddr_t)iv2, M_TEMP);
D 82
		if (error || (error = VOP_GETATTR(vp, vap, cred, nfsd->nd_procp))) {
E 82
I 82
		if (error || (getret = VOP_GETATTR(vp, vap, cred, procp))) {
			if (!error)
				error = getret;
E 82
			m_freem(mreq);
			vput(vp);
D 82
			nfsm_reply(0);
E 82
I 82
			nfsm_reply(NFSX_POSTOPATTR(v3));
			nfsm_srvpostop_attr(getret, vap);
			return (0);
E 82
		}
	} else
		uiop->uio_resid = 0;
	vput(vp);
E 45
D 11
	fp->fa_type = vtonfs_type(vap->va_type);
	fp->fa_mode = vtonfs_mode(vap->va_type, vap->va_mode);
	fp->fa_nlink = txdr_unsigned(vap->va_nlink);
	fp->fa_uid = txdr_unsigned(vap->va_uid);
	fp->fa_gid = txdr_unsigned(vap->va_gid);
	fp->fa_size = txdr_unsigned(vap->va_size);
	fp->fa_blocksize = txdr_unsigned(vap->va_blocksize);
	fp->fa_rdev = txdr_unsigned(vap->va_rdev);
	fp->fa_blocks = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
	fp->fa_fsid = txdr_unsigned(vap->va_fsid);
	fp->fa_fileid = txdr_unsigned(vap->va_fileid);
	txdr_time(&vap->va_atime, &fp->fa_atime);
	txdr_time(&vap->va_mtime, &fp->fa_mtime);
	txdr_time(&vap->va_ctime, &fp->fa_ctime);
E 11
I 11
D 82
	nfsm_srvfillattr;
E 82
I 82
	nfsm_srvfillattr(vap, fp);
E 82
E 11
E 7
D 31
	if (uiop->uio_resid > 0) {
		len -= uiop->uio_resid;
		if (len > 0) {
			tlen = nfsm_rndup(len);
E 31
I 31
	len -= uiop->uio_resid;
D 45
	if (len > 0) {
		tlen = nfsm_rndup(len);
		if (cnt != tlen || tlen != len)
E 31
D 19
			nfsm_adj(mp3, cnt-tlen, tlen-len);
E 19
I 19
			nfsm_adj(m3, cnt-tlen, tlen-len);
E 19
D 31
		} else {
D 19
			m_freem(mp3);
			mp3 = (struct mbuf *)0;
E 19
I 19
			m_freem(m3);
			m3 = (struct mbuf *)0;
E 19
		}
E 31
I 31
	} else {
		m_freem(m3);
		m3 = (struct mbuf *)0;
E 31
	}
I 7
D 37
	nfsm_build(p, u_long *, NFSX_UNSIGNED);
E 7
	*p = txdr_unsigned(len);
E 37
I 37
	nfsm_build(tl, u_long *, NFSX_UNSIGNED);
E 45
I 45
	tlen = nfsm_rndup(len);
	if (cnt != tlen || tlen != len)
D 82
		nfsm_adj(mb, cnt-tlen, tlen-len);
E 82
I 82
		nfsm_adj(mb, cnt - tlen, tlen - len);
	if (v3) {
		*tl++ = txdr_unsigned(len);
		if (len < reqlen)
			*tl++ = nfs_true;
		else
			*tl++ = nfs_false;
	}
E 82
E 45
	*tl = txdr_unsigned(len);
E 37
D 19
	mb->m_next = mp3;
E 19
I 19
D 45
	mb->m_next = m3;
E 45
E 19
	nfsm_srvdone;
}

/*
 * nfs write service
 */
D 11
nfsrv_write(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_write(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_write(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf *mrep, *md, **mrq;
E 45
I 45
D 82
nfsrv_write(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
E 45
	caddr_t dpos;
	struct ucred *cred;
D 11
	long xid;
E 11
I 11
D 45
	u_long xid;
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_write(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
I 61
D 64
	USES_VOP_GETATTR;
	USES_VOP_WRITE;
E 64
E 61
	register struct iovec *ivp;
I 82
	register int i, cnt;
E 82
	register struct mbuf *mp;
I 7
D 82
	register struct nfsv2_fattr *fp;
E 7
D 19
	struct iovec iv[MAX_IOVEC];
E 19
I 19
	struct iovec iv[NFS_MAXIOVEC];
E 19
	struct vattr va;
E 82
I 82
	register struct nfs_fattr *fp;
	struct iovec *iv;
	struct vattr va, forat;
E 82
	register struct vattr *vap = &va;
D 9
	nfsm_srvars;
E 9
I 9
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 82
	int error = 0, rdonly, cache, siz, len, xfer;
I 69
	int ioflags = IO_SYNC | IO_NODELOCKED;
E 82
I 82
	int error = 0, rdonly, cache, siz, len, xfer, forat_ret = 1;
	int ioflags, aftat_ret = 1, retlen, zeroing, adjust;
	int stable = NFSV3WRITE_FILESYNC;
	int v3 = (nfsd->nd_flag & ND_NFSV3);
E 82
E 69
E 45
	char *cp2;
D 11
	struct mbuf *mb, *mb2;
E 11
I 11
	struct mbuf *mb, *mb2, *mreq;
E 11
E 9
	struct vnode *vp;
D 82
	nfsv2fh_t nfh;
E 82
I 82
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
	struct uio io, *uiop = &io;
	off_t off;
D 45
	long siz, len, xfer;
E 45
I 45
	u_quad_t frev;
E 45

I 82
	if (mrep == NULL) {
		*mrq = NULL;
		return (0);
	}
E 82
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 37
	nfsm_disect(p, u_long *, 4*NFSX_UNSIGNED);
	off = fxdr_unsigned(off_t, *++p);
	p += 2;
	len = fxdr_unsigned(long, *p);
E 37
I 37
D 45
	nfsm_disect(tl, u_long *, 4*NFSX_UNSIGNED);
E 45
I 45
D 69
	nfsm_dissect(tl, u_long *, 4*NFSX_UNSIGNED);
E 45
	off = fxdr_unsigned(off_t, *++tl);
	tl += 2;
E 69
I 69
D 82
	nfsm_dissect(tl, u_long *, 4 * NFSX_UNSIGNED);
	if (nfsd->nd_nqlflag == NQL_NOVAL) {
E 82
I 82
	if (v3) {
		nfsm_dissect(tl, u_long *, 5 * NFSX_UNSIGNED);
		fxdr_hyper(tl, &off);
		tl += 3;
		stable = fxdr_unsigned(int, *tl++);
	} else {
		nfsm_dissect(tl, u_long *, 4 * NFSX_UNSIGNED);
E 82
		off = (off_t)fxdr_unsigned(u_long, *++tl);
		tl += 2;
D 82
	} else {
		fxdr_hyper(tl, &off);
		tl += 2;
		if (fxdr_unsigned(u_long, *tl++))
			ioflags |= IO_APPEND;
E 82
	}
E 69
D 82
	len = fxdr_unsigned(long, *tl);
E 37
	if (len > NFS_MAXDATA || len <= 0) {
		error = EBADRPC;
		nfsm_reply(0);
	}
	if (dpos == (mtod(md, caddr_t)+md->m_len)) {
		mp = md->m_next;
		if (mp == NULL) {
			error = EBADRPC;
			nfsm_reply(0);
E 82
I 82
	retlen = len = fxdr_unsigned(long, *tl);
	cnt = i = 0;

	/*
	 * For NFS Version 2, it is not obvious what a write of zero length
	 * should do, but I might as well be consistent with Version 3,
	 * which is to return ok so long as there are no permission problems.
	 */
	if (len > 0) {
	    zeroing = 1;
	    mp = mrep;
	    while (mp) {
		if (mp == md) {
			zeroing = 0;
			adjust = dpos - mtod(mp, caddr_t);
			mp->m_len -= adjust;
			if (mp->m_len > 0 && adjust > 0)
				NFSMADV(mp, adjust);
E 82
		}
D 82
	} else {
		mp = md;
		siz = dpos-mtod(mp, caddr_t);
		mp->m_len -= siz;
		NFSMADV(mp, siz);
E 82
I 82
		if (zeroing)
			mp->m_len = 0;
		else if (mp->m_len > 0) {
			i += mp->m_len;
			if (i > len) {
				mp->m_len -= (i - len);
				zeroing	= 1;
			}
			if (mp->m_len > 0)
				cnt++;
		}
		mp = mp->m_next;
	    }
E 82
	}
D 45
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred))
E 45
I 45
D 82
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
E 45
		nfsm_reply(0);
E 82
I 82
	if (len > NFS_MAXDATA || len < 0 || i < len) {
		error = EIO;
		nfsm_reply(2 * NFSX_UNSIGNED);
		nfsm_srvwcc_data(forat_ret, &forat, aftat_ret, vap);
		return (0);
	}
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
		nfsm_reply(2 * NFSX_UNSIGNED);
		nfsm_srvwcc_data(forat_ret, &forat, aftat_ret, vap);
		return (0);
	}
	if (v3)
		forat_ret = VOP_GETATTR(vp, &forat, cred, procp);
E 82
I 75
	if (vp->v_type != VREG) {
D 82
		error = (vp->v_type == VDIR) ? EISDIR : EACCES;
		vput(vp);
		nfsm_reply(0);
E 82
I 82
		if (v3)
			error = EINVAL;
		else
			error = (vp->v_type == VDIR) ? EISDIR : EACCES;
E 82
	}
E 75
D 2
	if (error = vn_access(vp, VWRITE, cred)) {
E 2
I 2
D 4
	if ((error = vn_writechk(vp)) ||
	    (error = VOP_ACCESS(vp, VWRITE, cred))) {
E 4
I 4
D 37
	if (error = nfsrv_access(vp, VWRITE, cred)) {
E 37
I 37
D 45
	if (error = nfsrv_access(vp, VWRITE, cred, p)) {
E 45
I 45
D 82
	nqsrv_getl(vp, NQL_WRITE);
	if (error = nfsrv_access(vp, VWRITE, cred, rdonly, nfsd->nd_procp)) {
E 82
I 82
	if (!error) {
		nqsrv_getl(vp, ND_WRITE);
		error = nfsrv_access(vp, VWRITE, cred, rdonly, procp);
	}
	if (error) {
E 82
E 45
E 37
E 4
E 2
		vput(vp);
D 82
		nfsm_reply(0);
E 82
I 82
		nfsm_reply(NFSX_WCCDATA(v3));
		nfsm_srvwcc_data(forat_ret, &forat, aftat_ret, vap);
		return (0);
E 82
	}
D 82
	uiop->uio_resid = 0;
	uiop->uio_rw = UIO_WRITE;
	uiop->uio_segflg = UIO_SYSSPACE;
I 37
	uiop->uio_procp = (struct proc *)0;
E 82
I 82

	if (len > 0) {
	    MALLOC(ivp, struct iovec *, cnt * sizeof (struct iovec), M_TEMP,
		M_WAITOK);
	    uiop->uio_iov = iv = ivp;
	    uiop->uio_iovcnt = cnt;
	    mp = mrep;
	    while (mp) {
		if (mp->m_len > 0) {
			ivp->iov_base = mtod(mp, caddr_t);
			ivp->iov_len = mp->m_len;
			ivp++;
		}
		mp = mp->m_next;
	    }

	    /*
	     * XXX
	     * The IO_METASYNC flag indicates that all metadata (and not just
	     * enough to ensure data integrity) mus be written to stable storage
	     * synchronously.
	     * (IO_METASYNC is not yet implemented in 4.4BSD-Lite.)
	     */
	    if (stable == NFSV3WRITE_UNSTABLE)
		ioflags = IO_NODELOCKED;
	    else if (stable == NFSV3WRITE_DATASYNC)
		ioflags = (IO_SYNC | IO_NODELOCKED);
	    else
		ioflags = (IO_METASYNC | IO_SYNC | IO_NODELOCKED);
	    uiop->uio_resid = len;
	    uiop->uio_rw = UIO_WRITE;
	    uiop->uio_segflg = UIO_SYSSPACE;
	    uiop->uio_procp = (struct proc *)0;
	    uiop->uio_offset = off;
	    error = VOP_WRITE(vp, uiop, ioflags, cred);
	    nfsstats.srvvop_writes++;
	    FREE((caddr_t)iv, M_TEMP);
	}
	aftat_ret = VOP_GETATTR(vp, vap, cred, procp);
	vput(vp);
	if (!error)
		error = aftat_ret;
	nfsm_reply(NFSX_PREOPATTR(v3) + NFSX_POSTOPORFATTR(v3) +
		2 * NFSX_UNSIGNED + NFSX_WRITEVERF(v3));
	if (v3) {
		nfsm_srvwcc_data(forat_ret, &forat, aftat_ret, vap);
		if (error)
			return (0);
		nfsm_build(tl, u_long *, 4 * NFSX_UNSIGNED);
		*tl++ = txdr_unsigned(retlen);
		if (stable == NFSV3WRITE_UNSTABLE)
			*tl++ = txdr_unsigned(stable);
		else
			*tl++ = txdr_unsigned(NFSV3WRITE_FILESYNC);
		/*
		 * Actually, there is no need to txdr these fields,
		 * but it may make the values more human readable,
		 * for debugging purposes.
		 */
		*tl++ = txdr_unsigned(boottime.tv_sec);
		*tl = txdr_unsigned(boottime.tv_usec);
	} else {
		nfsm_build(fp, struct nfs_fattr *, NFSX_V2FATTR);
		nfsm_srvfillattr(vap, fp);
	}
	nfsm_srvdone;
}

/*
 * NFS write service with write gathering support. Called when
 * nfsrvw_procrastinate > 0.
 * See: Chet Juszczak, "Improving the Write Performance of an NFS Server",
 * in Proc. of the Winter 1994 Usenix Conference, pg. 247-259, San Franscisco,
 * Jan. 1994.
 */
int
nfsrv_writegather(ndp, slp, procp, mrq)
	struct nfsrv_descript **ndp;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
{
	register struct iovec *ivp;
	register struct mbuf *mp;
	register struct nfsrv_descript *wp, *nfsd, *owp, *swp;
	register struct nfs_fattr *fp;
	register int i;
	struct iovec *iov;
	struct nfsrvw_delayhash *wpp;
	struct ucred *cred;
	struct vattr va, forat;
	register u_long *tl;
	register long t1;
	caddr_t bpos, dpos;
	int error = 0, rdonly, cache, len, forat_ret = 1;
	int ioflags, aftat_ret = 1, s, adjust, v3, zeroing;
	char *cp2;
	struct mbuf *mb, *mb2, *mreq, *mrep, *md;
	struct vnode *vp;
	struct uio io, *uiop = &io;
	off_t off;
	u_quad_t frev, cur_usec;

#ifndef nolint
	i = 0;
	len = 0;
#endif
	*mrq = NULL;
	if (*ndp) {
	    nfsd = *ndp;
	    *ndp = NULL;
	    mrep = nfsd->nd_mrep;
	    md = nfsd->nd_md;
	    dpos = nfsd->nd_dpos;
	    cred = &nfsd->nd_cr;
	    v3 = (nfsd->nd_flag & ND_NFSV3);
	    LIST_INIT(&nfsd->nd_coalesce);
	    nfsd->nd_mreq = NULL;
	    nfsd->nd_stable = NFSV3WRITE_FILESYNC;
	    cur_usec = (u_quad_t)time.tv_sec * 1000000 + (u_quad_t)time.tv_usec;
	    nfsd->nd_time = cur_usec + nfsrvw_procrastinate;
    
	    /*
	     * Now, get the write header..
	     */
	    nfsm_srvmtofh(&nfsd->nd_fh);
	    if (v3) {
		nfsm_dissect(tl, u_long *, 5 * NFSX_UNSIGNED);
		fxdr_hyper(tl, &nfsd->nd_off);
		tl += 3;
		nfsd->nd_stable = fxdr_unsigned(int, *tl++);
	    } else {
		nfsm_dissect(tl, u_long *, 4 * NFSX_UNSIGNED);
		nfsd->nd_off = (off_t)fxdr_unsigned(u_long, *++tl);
		tl += 2;
	    }
	    len = fxdr_unsigned(long, *tl);
	    nfsd->nd_len = len;
	    nfsd->nd_eoff = nfsd->nd_off + len;
    
	    /*
	     * Trim the header out of the mbuf list and trim off any trailing
	     * junk so that the mbuf list has only the write data.
	     */
	    zeroing = 1;
	    i = 0;
	    mp = mrep;
	    while (mp) {
		if (mp == md) {
		    zeroing = 0;
		    adjust = dpos - mtod(mp, caddr_t);
		    mp->m_len -= adjust;
		    if (mp->m_len > 0 && adjust > 0)
			NFSMADV(mp, adjust);
		}
		if (zeroing)
		    mp->m_len = 0;
		else {
		    i += mp->m_len;
		    if (i > len) {
			mp->m_len -= (i - len);
			zeroing = 1;
		    }
		}
		mp = mp->m_next;
	    }
	    if (len > NFS_MAXDATA || len < 0  || i < len) {
nfsmout:
		m_freem(mrep);
		error = EIO;
		nfsm_writereply(2 * NFSX_UNSIGNED, v3);
		if (v3)
		    nfsm_srvwcc_data(forat_ret, &forat, aftat_ret, &va);
		nfsd->nd_mreq = mreq;
		nfsd->nd_mrep = NULL;
		nfsd->nd_time = 0;
	    }
    
	    /*
	     * Add this entry to the hash and time queues.
	     */
	    s = splsoftclock();
	    owp = NULL;
	    wp = slp->ns_tq.lh_first;
	    while (wp && wp->nd_time < nfsd->nd_time) {
		owp = wp;
		wp = wp->nd_tq.le_next;
	    }
	    if (owp) {
		LIST_INSERT_AFTER(owp, nfsd, nd_tq);
	    } else {
		LIST_INSERT_HEAD(&slp->ns_tq, nfsd, nd_tq);
	    }
	    if (nfsd->nd_mrep) {
		wpp = NWDELAYHASH(slp, nfsd->nd_fh.fh_fid.fid_data);
		owp = NULL;
		wp = wpp->lh_first;
		while (wp &&
		    bcmp((caddr_t)&nfsd->nd_fh,(caddr_t)&wp->nd_fh,NFSX_V3FH)) {
		    owp = wp;
		    wp = wp->nd_hash.le_next;
		}
		while (wp && wp->nd_off < nfsd->nd_off &&
		    !bcmp((caddr_t)&nfsd->nd_fh,(caddr_t)&wp->nd_fh,NFSX_V3FH)) {
		    owp = wp;
		    wp = wp->nd_hash.le_next;
		}
		if (owp) {
		    LIST_INSERT_AFTER(owp, nfsd, nd_hash);

		    /*
		     * Search the hash list for overlapping entries and
		     * coalesce.
		     */
		    for(; nfsd && NFSW_CONTIG(owp, nfsd); nfsd = wp) {
			wp = nfsd->nd_hash.le_next;
			if (NFSW_SAMECRED(owp, nfsd))
			    nfsrvw_coalesce(owp, nfsd);
		    }
		} else {
		    LIST_INSERT_HEAD(wpp, nfsd, nd_hash);
		}
	    }
	    splx(s);
	}
    
E 82
E 37
	/*
D 19
	 * Do up to MAX_IOVEC mbufs of write each iteration of the
E 19
I 19
D 82
	 * Do up to NFS_MAXIOVEC mbufs of write each iteration of the
E 19
	 * loop until done.
E 82
I 82
	 * Now, do VOP_WRITE()s for any one(s) that need to be done now
	 * and generate the associated reply mbuf list(s).
E 82
	 */
D 82
	while (len > 0 && uiop->uio_resid == 0) {
		ivp = iv;
		siz = 0;
		uiop->uio_iov = ivp;
		uiop->uio_iovcnt = 0;
		uiop->uio_offset = off;
D 19
		while (len > 0 && uiop->uio_iovcnt < MAX_IOVEC && mp != NULL) {
E 19
I 19
		while (len > 0 && uiop->uio_iovcnt < NFS_MAXIOVEC && mp != NULL) {
E 19
			ivp->iov_base = mtod(mp, caddr_t);
			if (len < mp->m_len)
				ivp->iov_len = xfer = len;
E 82
I 82
loop1:
	cur_usec = (u_quad_t)time.tv_sec * 1000000 + (u_quad_t)time.tv_usec;
	s = splsoftclock();
	for (nfsd = slp->ns_tq.lh_first; nfsd; nfsd = owp) {
		owp = nfsd->nd_tq.le_next;
		if (nfsd->nd_time > cur_usec)
		    break;
		if (nfsd->nd_mreq)
		    continue;
		LIST_REMOVE(nfsd, nd_tq);
		LIST_REMOVE(nfsd, nd_hash);
		splx(s);
		mrep = nfsd->nd_mrep;
		nfsd->nd_mrep = NULL;
		cred = &nfsd->nd_cr;
		v3 = (nfsd->nd_flag & ND_NFSV3);
		forat_ret = aftat_ret = 1;
		error = nfsrv_fhtovp(&nfsd->nd_fh, 1, &vp, cred, slp, 
		    nfsd->nd_nam, &rdonly, (nfsd->nd_flag & ND_KERBAUTH));
		if (!error) {
		    if (v3)
			forat_ret = VOP_GETATTR(vp, &forat, cred, procp);
		    if (vp->v_type != VREG) {
			if (v3)
			    error = EINVAL;
E 82
			else
D 82
				ivp->iov_len = xfer = mp->m_len;
#ifdef notdef
			/* Not Yet .. */
			if (M_HASCL(mp) && (((u_long)ivp->iov_base) & CLOFSET) == 0)
				ivp->iov_op = NULL;	/* what should it be ?? */
			else
				ivp->iov_op = NULL;
#endif
			uiop->uio_iovcnt++;
			ivp++;
			len -= xfer;
			siz += xfer;
E 82
I 82
			    error = (vp->v_type == VDIR) ? EISDIR : EACCES;
		    }
		} else
		    vp = NULL;
		if (!error) {
		    nqsrv_getl(vp, ND_WRITE);
		    error = nfsrv_access(vp, VWRITE, cred, rdonly, procp);
		}
    
		if (nfsd->nd_stable == NFSV3WRITE_UNSTABLE)
		    ioflags = IO_NODELOCKED;
		else if (nfsd->nd_stable == NFSV3WRITE_DATASYNC)
		    ioflags = (IO_SYNC | IO_NODELOCKED);
		else
		    ioflags = (IO_METASYNC | IO_SYNC | IO_NODELOCKED);
		uiop->uio_rw = UIO_WRITE;
		uiop->uio_segflg = UIO_SYSSPACE;
		uiop->uio_procp = (struct proc *)0;
		uiop->uio_offset = nfsd->nd_off;
		uiop->uio_resid = nfsd->nd_eoff - nfsd->nd_off;
		if (uiop->uio_resid > 0) {
		    mp = mrep;
		    i = 0;
		    while (mp) {
			if (mp->m_len > 0)
			    i++;
E 82
			mp = mp->m_next;
I 82
		    }
		    uiop->uio_iovcnt = i;
		    MALLOC(iov, struct iovec *, i * sizeof (struct iovec), 
			M_TEMP, M_WAITOK);
		    uiop->uio_iov = ivp = iov;
		    mp = mrep;
		    while (mp) {
			if (mp->m_len > 0) {
			    ivp->iov_base = mtod(mp, caddr_t);
			    ivp->iov_len = mp->m_len;
			    ivp++;
			}
			mp = mp->m_next;
		    }
		    if (!error) {
			error = VOP_WRITE(vp, uiop, ioflags, cred);
			nfsstats.srvvop_writes++;
		    }
		    FREE((caddr_t)iov, M_TEMP);
E 82
		}
D 82
		if (len > 0 && mp == NULL) {
			error = EBADRPC;
			vput(vp);
			nfsm_reply(0);
E 82
I 82
		m_freem(mrep);
		if (vp) {
		    aftat_ret = VOP_GETATTR(vp, &va, cred, procp);
		    vput(vp);
E 82
		}
D 82
		uiop->uio_resid = siz;
D 10
		if (error = VOP_WRITE(vp, uiop, &off, IO_SYNC | IO_NODELOCKED,
E 10
I 10
D 69
		if (error = VOP_WRITE(vp, uiop, IO_SYNC | IO_NODELOCKED,
E 10
			cred)) {
E 69
I 69
		if (error = VOP_WRITE(vp, uiop, ioflags, cred)) {
E 69
			vput(vp);
			nfsm_reply(0);
E 82
I 82

		/*
		 * Loop around generating replies for all write rpcs that have
		 * now been completed.
		 */
		swp = nfsd;
		do {
		    if (error) {
			nfsm_writereply(NFSX_WCCDATA(v3), v3);
			if (v3) {
			    nfsm_srvwcc_data(forat_ret, &forat, aftat_ret, &va);
			}
		    } else {
			nfsm_writereply(NFSX_PREOPATTR(v3) +
			    NFSX_POSTOPORFATTR(v3) + 2 * NFSX_UNSIGNED +
			    NFSX_WRITEVERF(v3), v3);
			if (v3) {
			    nfsm_srvwcc_data(forat_ret, &forat, aftat_ret, &va);
			    nfsm_build(tl, u_long *, 4 * NFSX_UNSIGNED);
			    *tl++ = txdr_unsigned(nfsd->nd_len);
			    *tl++ = txdr_unsigned(swp->nd_stable);
			    /*
			     * Actually, there is no need to txdr these fields,
			     * but it may make the values more human readable,
			     * for debugging purposes.
			     */
			    *tl++ = txdr_unsigned(boottime.tv_sec);
			    *tl = txdr_unsigned(boottime.tv_usec);
			} else {
			    nfsm_build(fp, struct nfs_fattr *, NFSX_V2FATTR);
			    nfsm_srvfillattr(&va, fp);
			}
		    }
		    nfsd->nd_mreq = mreq;
		    if (nfsd->nd_mrep)
			panic("nfsrv_write: nd_mrep not free");

		    /*
		     * Done. Put it at the head of the timer queue so that
		     * the final phase can return the reply.
		     */
		    s = splsoftclock();
		    if (nfsd != swp) {
			nfsd->nd_time = 0;
			LIST_INSERT_HEAD(&slp->ns_tq, nfsd, nd_tq);
		    }
		    nfsd = swp->nd_coalesce.lh_first;
		    if (nfsd) {
			LIST_REMOVE(nfsd, nd_tq);
		    }
		    splx(s);
		} while (nfsd);
		s = splsoftclock();
		swp->nd_time = 0;
		LIST_INSERT_HEAD(&slp->ns_tq, swp, nd_tq);
		splx(s);
		goto loop1;
	}
	splx(s);

	/*
	 * Search for a reply to return.
	 */
	s = splsoftclock();
	for (nfsd = slp->ns_tq.lh_first; nfsd; nfsd = nfsd->nd_tq.le_next)
		if (nfsd->nd_mreq) {
		    LIST_REMOVE(nfsd, nd_tq);
		    *mrq = nfsd->nd_mreq;
		    *ndp = nfsd;
		    break;
E 82
		}
I 10
D 82
		off = uiop->uio_offset;
E 82
I 82
	splx(s);
	return (0);
}

/*
 * Coalesce the write request nfsd into owp. To do this we must:
 * - remove nfsd from the queues
 * - merge nfsd->nd_mrep into owp->nd_mrep
 * - update the nd_eoff and nd_stable for owp
 * - put nfsd on owp's nd_coalesce list
 * NB: Must be called at splsoftclock().
 */
void
nfsrvw_coalesce(owp, nfsd)
        register struct nfsrv_descript *owp;
        register struct nfsrv_descript *nfsd;
{
        register int overlap;
        register struct mbuf *mp;

        LIST_REMOVE(nfsd, nd_hash);
        LIST_REMOVE(nfsd, nd_tq);
        if (owp->nd_eoff < nfsd->nd_eoff) {
            overlap = owp->nd_eoff - nfsd->nd_off;
            if (overlap < 0)
                panic("nfsrv_coalesce: bad off");
            if (overlap > 0)
                m_adj(nfsd->nd_mrep, overlap);
            mp = owp->nd_mrep;
            while (mp->m_next)
                mp = mp->m_next;
            mp->m_next = nfsd->nd_mrep;
            owp->nd_eoff = nfsd->nd_eoff;
        } else
            m_freem(nfsd->nd_mrep);
        nfsd->nd_mrep = NULL;
        if (nfsd->nd_stable == NFSV3WRITE_FILESYNC)
            owp->nd_stable = NFSV3WRITE_FILESYNC;
        else if (nfsd->nd_stable == NFSV3WRITE_DATASYNC &&
            owp->nd_stable == NFSV3WRITE_UNSTABLE)
            owp->nd_stable = NFSV3WRITE_DATASYNC;
        LIST_INSERT_HEAD(&owp->nd_coalesce, nfsd, nd_tq);
}

/*
 * Sort the group list in increasing numerical order.
 * (Insertion sort by Chris Torek, who was grossed out by the bubble sort
 *  that used to be here.)
 */
void
nfsrvw_sort(list, num)
        register gid_t *list;
        register int num;
{
	register int i, j;
	gid_t v;

	/* Insertion sort. */
	for (i = 1; i < num; i++) {
		v = list[i];
		/* find correct slot for value v, moving others up */
		for (j = i; --j >= 0 && v < list[j];)
			list[j + 1] = list[j];
		list[j + 1] = v;
E 82
E 10
	}
D 37
	error = VOP_GETATTR(vp, vap, cred);
E 37
I 37
D 45
	error = VOP_GETATTR(vp, vap, cred, p);
E 45
I 45
D 82
	error = VOP_GETATTR(vp, vap, cred, nfsd->nd_procp);
E 45
E 37
	vput(vp);
D 69
	nfsm_reply(NFSX_FATTR);
D 7
	nfsm_build(p, u_long *, NFSX_FATTR);
	*p++ = vtonfs_type(vap->va_type);
	*p++ = vtonfs_mode(vap->va_type, vap->va_mode);
	*p++ = txdr_unsigned(vap->va_nlink);
	*p++ = txdr_unsigned(vap->va_uid);
	*p++ = txdr_unsigned(vap->va_gid);
	*p++ = txdr_unsigned(vap->va_size);
	*p++ = txdr_unsigned(vap->va_blocksize);
	*p++ = txdr_unsigned(vap->va_rdev);
D 6
	*p++ = txdr_unsigned(vap->va_bytes);
E 6
I 6
	*p++ = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
E 6
	*p++ = txdr_unsigned(vap->va_fsid);
	*p++ = txdr_unsigned(vap->va_fileid);
	txdr_time(&(vap->va_atime), p);
	p += 2;
	txdr_time(&(vap->va_mtime), p);
	p += 2;
	txdr_time(&(vap->va_ctime), p);
E 7
I 7
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR);
E 69
I 69
	nfsm_reply(NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL));
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 69
D 11
	fp->fa_type = vtonfs_type(vap->va_type);
	fp->fa_mode = vtonfs_mode(vap->va_type, vap->va_mode);
	fp->fa_nlink = txdr_unsigned(vap->va_nlink);
	fp->fa_uid = txdr_unsigned(vap->va_uid);
	fp->fa_gid = txdr_unsigned(vap->va_gid);
	fp->fa_size = txdr_unsigned(vap->va_size);
	fp->fa_blocksize = txdr_unsigned(vap->va_blocksize);
	fp->fa_rdev = txdr_unsigned(vap->va_rdev);
	fp->fa_blocks = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
	fp->fa_fsid = txdr_unsigned(vap->va_fsid);
	fp->fa_fileid = txdr_unsigned(vap->va_fileid);
	txdr_time(&vap->va_atime, &fp->fa_atime);
	txdr_time(&vap->va_mtime, &fp->fa_mtime);
	txdr_time(&vap->va_ctime, &fp->fa_ctime);
E 11
I 11
	nfsm_srvfillattr;
I 49
	if (nfsd->nd_nqlflag != NQL_NOVAL) {
		nfsm_build(tl, u_long *, 2*NFSX_UNSIGNED);
		txdr_hyper(&vap->va_filerev, tl);
	}
E 49
E 11
E 7
	nfsm_srvdone;
E 82
}

/*
I 82
 * copy credentials making sure that the result can be compared with bcmp().
 */
void
nfsrv_setcred(incred, outcred)
	register struct ucred *incred, *outcred;
{
	register int i;

	bzero((caddr_t)outcred, sizeof (struct ucred));
	outcred->cr_ref = 1;
	outcred->cr_uid = incred->cr_uid;
	outcred->cr_ngroups = incred->cr_ngroups;
	for (i = 0; i < incred->cr_ngroups; i++)
		outcred->cr_groups[i] = incred->cr_groups[i];
	nfsrvw_sort(outcred->cr_groups, outcred->cr_ngroups);
}

/*
E 82
 * nfs create service
 * now does a truncate to 0 length via. setattr if it already exists
 */
D 11
nfsrv_create(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_create(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_create(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf *mrep, *md, **mrq;
E 45
I 45
D 82
nfsrv_create(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
E 45
	caddr_t dpos;
	struct ucred *cred;
D 11
	long xid;
E 11
I 11
D 45
	u_long xid;
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_create(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 61
D 64
	USES_VOP_ABORTOP;
	USES_VOP_CREATE;
	USES_VOP_GETATTR;
	USES_VOP_MKNOD;
	USES_VOP_SETATTR;
E 64
E 61
I 7
D 82
	register struct nfsv2_fattr *fp;
E 7
	struct vattr va;
E 82
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	register struct nfs_fattr *fp;
	struct vattr va, dirfor, diraft;
E 82
	register struct vattr *vap = &va;
I 69
	register struct nfsv2_sattr *sp;
	register u_long *tl;
E 69
D 8
	register struct nameidata *ndp = &u.u_nd;
E 8
I 8
D 41
	struct nameidata nami;
	register struct nameidata *ndp = &nami;
E 41
I 41
	struct nameidata nd;
E 41
E 8
D 9
	nfsm_srvars;
E 9
I 9
	register caddr_t cp;
D 37
	register u_long *p;
E 37
I 37
D 69
	register u_long *tl;
E 69
E 37
	register long t1;
	caddr_t bpos;
I 20
D 45
	long rdev;
E 20
	int error = 0;
E 45
I 45
D 69
	int error = 0, rdev, cache, len;
E 69
I 69
D 82
	int error = 0, rdev, cache, len, tsize;
E 82
I 82
	int error = 0, rdev, cache, len, tsize, dirfor_ret = 1, diraft_ret = 1;
	int v3 = (nfsd->nd_flag & ND_NFSV3), how, exclusive_flag = 0;
E 82
E 69
E 45
	char *cp2;
D 11
	struct mbuf *mb, *mb2;
E 11
I 11
	struct mbuf *mb, *mb2, *mreq;
E 11
E 9
D 82
	struct vnode *vp;
	nfsv2fh_t nfh;
E 82
I 82
	struct vnode *vp, *dirp = (struct vnode *)0;
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
D 45
	long len;
E 45
I 45
D 82
	u_quad_t frev;
E 82
I 82
	u_quad_t frev, tempsize;
	u_char cverf[NFSX_V3CREATEVERF];
E 82
E 45

I 82
#ifndef nolint
	rdev = 0;
#endif
E 82
D 8
	ndp->ni_vp = ndp->ni_dvp = (struct vnode *)0;
E 8
I 8
D 41
	ndinit(ndp);
E 41
I 41
D 47
	nd.ni_nameiop = 0;
E 47
I 47
	nd.ni_cnd.cn_nameiop = 0;
E 47
E 41
E 8
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 82
	nfsm_srvstrsiz(len, NFS_MAXNAMLEN);
E 82
I 82
	nfsm_srvnamesiz(len);
E 82
D 41
	ndp->ni_cred = cred;
	ndp->ni_nameiop = CREATE | LOCKPARENT | LOCKLEAF;
D 3
	ndp->ni_segflg = UIO_SYSSPACE;
E 3
	if (error = nfs_namei(ndp, fhp, len, &md, &dpos))
E 41
I 41
D 47
	nd.ni_cred = cred;
	nd.ni_nameiop = CREATE | LOCKPARENT | LOCKLEAF | SAVESTART;
E 47
I 47
	nd.ni_cnd.cn_cred = cred;
	nd.ni_cnd.cn_nameiop = CREATE;
	nd.ni_cnd.cn_flags = LOCKPARENT | LOCKLEAF | SAVESTART;
E 47
D 45
	if (error = nfs_namei(&nd, fhp, len, &md, &dpos, p))
E 45
I 45
D 50
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos, nfsd->nd_procp))
E 50
I 50
D 82
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos,
	    nfsd->nd_procp))
E 50
E 45
E 41
		nfsm_reply(0);
E 82
I 82
	error = nfs_namei(&nd, fhp, len, slp, nam, &md, &dpos,
		&dirp, procp, (nfsd->nd_flag & ND_KERBAUTH));
	if (dirp) {
		if (v3)
			dirfor_ret = VOP_GETATTR(dirp, &dirfor, cred,
				procp);
		else {
			vrele(dirp);
			dirp = (struct vnode *)0;
		}
	}
	if (error) {
		nfsm_reply(NFSX_WCCDATA(v3));
		nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
		if (dirp)
			vrele(dirp);
		return (0);
	}
E 82
D 17
	vattr_null(vap);
E 17
I 17
	VATTR_NULL(vap);
E 17
D 20
	nfsm_disect(p, u_long *, NFSX_UNSIGNED);
E 20
I 20
D 37
	nfsm_disect(p, u_long *, NFSX_SATTR);
E 37
I 37
D 45
	nfsm_disect(tl, u_long *, NFSX_SATTR);
E 45
I 45
D 69
	nfsm_dissect(tl, u_long *, NFSX_SATTR);
E 69
I 69
D 82
	nfsm_dissect(sp, struct nfsv2_sattr *, NFSX_SATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 82
I 82
	if (v3) {
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
		how = fxdr_unsigned(int, *tl);
		switch (how) {
		case NFSV3CREATE_GUARDED:
			if (nd.ni_vp) {
				error = EEXIST;
				break;
			}
		case NFSV3CREATE_UNCHECKED:
			nfsm_srvsattr(vap);
			break;
		case NFSV3CREATE_EXCLUSIVE:
			nfsm_dissect(cp, caddr_t, NFSX_V3CREATEVERF);
			bcopy(cp, cverf, NFSX_V3CREATEVERF);
			exclusive_flag = 1;
			if (nd.ni_vp == NULL)
				vap->va_mode = 0;
			break;
		};
		vap->va_type = VREG;
	} else {
		nfsm_dissect(sp, struct nfsv2_sattr *, NFSX_V2SATTR);
		vap->va_type = IFTOVT(fxdr_unsigned(u_long, sp->sa_mode));
		if (vap->va_type == VNON)
			vap->va_type = VREG;
		vap->va_mode = nfstov_mode(sp->sa_mode);
		switch (vap->va_type) {
		case VREG:
			tsize = fxdr_unsigned(long, sp->sa_size);
			if (tsize != -1)
				vap->va_size = (u_quad_t)tsize;
			break;
		case VCHR:
		case VBLK:
		case VFIFO:
			rdev = fxdr_unsigned(long, sp->sa_size);
			break;
		};
	}

E 82
E 69
E 45
E 37
E 20
	/*
	 * Iff doesn't exist, create it
	 * otherwise just truncate to 0 length
	 *   should I set the mode too ??
	 */
D 41
	if (ndp->ni_vp == NULL) {
E 41
I 41
	if (nd.ni_vp == NULL) {
E 41
D 20
		vap->va_type = VREG;
		vap->va_mode = nfstov_mode(*p++);
		if (error = VOP_CREATE(ndp, vap))
E 20
I 20
D 37
		vap->va_type = IFTOVT(fxdr_unsigned(u_long, *p));
E 37
I 37
D 69
		vap->va_type = IFTOVT(fxdr_unsigned(u_long, *tl));
E 69
I 69
D 82
		vap->va_type = IFTOVT(fxdr_unsigned(u_long, sp->sa_mode));
E 69
E 37
I 23
		if (vap->va_type == VNON)
			vap->va_type = VREG;
E 23
D 37
		vap->va_mode = nfstov_mode(*p);
		rdev = fxdr_unsigned(long, *(p+3));
E 37
I 37
D 69
		vap->va_mode = nfstov_mode(*tl);
		rdev = fxdr_unsigned(long, *(tl+3));
E 69
I 69
		vap->va_mode = nfstov_mode(sp->sa_mode);
		if (nfsd->nd_nqlflag == NQL_NOVAL)
			rdev = fxdr_unsigned(long, sp->sa_nfssize);
		else
			rdev = fxdr_unsigned(long, sp->sa_nqrdev);
E 82
E 69
E 37
D 35
		if (vap->va_type == VREG) {
E 35
I 35
		if (vap->va_type == VREG || vap->va_type == VSOCK) {
I 42
			p->p_spare[1]--;
E 42
E 35
D 37
			if (error = VOP_CREATE(ndp, vap))
E 37
I 37
D 41
			if (error = VOP_CREATE(ndp, vap, p))
E 41
I 41
			vrele(nd.ni_startdir);
D 45
			if (error = VOP_CREATE(&nd, vap, p))
E 45
I 45
D 82
			nqsrv_getl(nd.ni_dvp, NQL_WRITE);
D 46
			if (error = VOP_CREATE(&nd, vap, nfsd->nd_procp))
E 46
I 46
			if (error = VOP_CREATE(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, vap))
E 46
E 45
E 41
E 37
				nfsm_reply(0);
I 41
D 47
			FREE(nd.ni_pnbuf, M_NAMEI);
E 47
I 47
			FREE(nd.ni_cnd.cn_pnbuf, M_NAMEI);
E 82
I 82
			nqsrv_getl(nd.ni_dvp, ND_WRITE);
			error = VOP_CREATE(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, vap);
			if (!error) {
				FREE(nd.ni_cnd.cn_pnbuf, M_NAMEI);
				if (exclusive_flag) {
					exclusive_flag = 0;
					VATTR_NULL(vap);
					bcopy(cverf, (caddr_t)&vap->va_atime,
						NFSX_V3CREATEVERF);
					error = VOP_SETATTR(nd.ni_vp, vap, cred,
						procp);
				}
			}
E 82
E 47
E 41
		} else if (vap->va_type == VCHR || vap->va_type == VBLK ||
			vap->va_type == VFIFO) {
			if (vap->va_type == VCHR && rdev == 0xffffffff)
				vap->va_type = VFIFO;
D 82
			if (vap->va_type == VFIFO) {
#ifndef FIFO
E 82
I 82
			if (error = suser(cred, (u_short *)0)) {
				vrele(nd.ni_startdir);
				free(nd.ni_cnd.cn_pnbuf, M_NAMEI);
E 82
D 41
				VOP_ABORTOP(ndp);
I 21
				vput(ndp->ni_dvp);
E 41
I 41
D 46
				VOP_ABORTOP(&nd);
E 46
I 46
				VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
				vput(nd.ni_dvp);
E 41
E 21
D 82
				error = ENXIO;
D 41
				nfsm_reply(0);
E 41
I 41
				goto out;
E 41
#endif /* FIFO */
D 45
			} else if (error = suser(cred, (short *)0)) {
E 45
I 45
			} else if (error = suser(cred, (u_short *)0)) {
E 45
D 41
				VOP_ABORTOP(ndp);
I 21
				vput(ndp->ni_dvp);
E 21
				nfsm_reply(0);
E 41
I 41
D 46
				VOP_ABORTOP(&nd);
E 46
I 46
				VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
				vput(nd.ni_dvp);
				goto out;
E 82
I 82
				nfsm_reply(0);
				return (error);
E 82
E 41
			} else
				vap->va_rdev = (dev_t)rdev;
D 37
			if (error = VOP_MKNOD(ndp, vap, cred))
E 37
I 37
D 41
			if (error = VOP_MKNOD(ndp, vap, cred, p))
E 41
I 41
D 45
			if (error = VOP_MKNOD(&nd, vap, cred, p)) {
E 45
I 45
D 82
			nqsrv_getl(nd.ni_dvp, NQL_WRITE);
E 82
I 82
			nqsrv_getl(nd.ni_dvp, ND_WRITE);
E 82
D 46
			if (error = VOP_MKNOD(&nd, vap, cred, nfsd->nd_procp)) {
E 46
I 46
			if (error = VOP_MKNOD(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, vap)) {
E 46
E 45
I 42
				p->p_spare[1]--;
E 42
				vrele(nd.ni_startdir);
E 41
E 37
				nfsm_reply(0);
D 41
			ndp->ni_nameiop = LOOKUP | LOCKLEAF | HASBUF;
			if (error = nfs_namei(ndp, fhp, len, &md, &dpos))
E 41
I 41
			}
D 47
			nd.ni_nameiop &= ~(OPMASK | LOCKPARENT | SAVESTART);
			nd.ni_nameiop |= LOOKUP;
I 42
			p->p_spare[1]--;
E 42
D 45
			if (error = lookup(&nd, p)) {
E 45
I 45
			if (error = lookup(&nd, nfsd->nd_procp)) {
E 45
				free(nd.ni_pnbuf, M_NAMEI);
E 47
I 47
			nd.ni_cnd.cn_nameiop = LOOKUP;
			nd.ni_cnd.cn_flags &= ~(LOCKPARENT | SAVESTART);
D 82
			nd.ni_cnd.cn_proc = nfsd->nd_procp;
			nd.ni_cnd.cn_cred = nfsd->nd_procp->p_ucred;
E 82
I 82
			nd.ni_cnd.cn_proc = procp;
			nd.ni_cnd.cn_cred = cred;
E 82
			if (error = lookup(&nd)) {
				free(nd.ni_cnd.cn_pnbuf, M_NAMEI);
E 47
E 41
				nfsm_reply(0);
I 41
			}
D 47
			FREE(nd.ni_pnbuf, M_NAMEI);
D 46
			if (nd.ni_more) {
E 46
I 46
			if (nd.ni_nameiop & ISSYMLINK) {
E 47
I 47
			FREE(nd.ni_cnd.cn_pnbuf, M_NAMEI);
			if (nd.ni_cnd.cn_flags & ISSYMLINK) {
E 47
E 46
				vrele(nd.ni_dvp);
				vput(nd.ni_vp);
D 46
				VOP_ABORTOP(&nd);
E 46
I 46
				VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
				error = EINVAL;
				nfsm_reply(0);
			}
E 41
		} else {
I 82
			vrele(nd.ni_startdir);
			free(nd.ni_cnd.cn_pnbuf, M_NAMEI);
E 82
D 41
			VOP_ABORTOP(ndp);
I 21
			vput(ndp->ni_dvp);
E 41
I 41
D 46
			VOP_ABORTOP(&nd);
E 46
I 46
			VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
			vput(nd.ni_dvp);
E 41
E 21
			error = ENXIO;
E 20
D 41
			nfsm_reply(0);
E 41
I 41
D 82
			goto out;
E 82
E 41
I 20
		}
E 20
I 3
D 41
		vp = ndp->ni_vp;
E 41
I 41
		vp = nd.ni_vp;
E 41
E 3
	} else {
I 42
		p->p_spare[1]--;
E 42
I 3
D 41
		vp = ndp->ni_vp;
D 18
		ndp->ni_vp = (struct vnode *)0;
E 18
I 18
		ndp->ni_vp = NULLVP;
E 18
		VOP_ABORTOP(ndp);
I 21
D 25
		vput(ndp->ni_dvp);
E 25
I 25
		if (ndp->ni_dvp == vp)
			vrele(ndp->ni_dvp);
E 41
I 41
		vrele(nd.ni_startdir);
D 47
		free(nd.ni_pnbuf, M_NAMEI);
E 47
I 47
		free(nd.ni_cnd.cn_pnbuf, M_NAMEI);
E 47
		vp = nd.ni_vp;
		if (nd.ni_dvp == vp)
			vrele(nd.ni_dvp);
E 41
		else
D 41
			vput(ndp->ni_dvp);
E 41
I 41
			vput(nd.ni_dvp);
D 46
		VOP_ABORTOP(&nd);
E 46
I 46
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
E 41
E 25
E 21
E 3
D 69
		vap->va_size = 0;
D 3
		if (error = VOP_SETATTR(ndp->ni_vp, vap, cred)) {
			VOP_ABORTOP(ndp);
E 3
I 3
D 22
		if (error = VOP_SETATTR(vp, vap, cred))
E 22
I 22
D 37
		if (error = VOP_SETATTR(vp, vap, cred)) {
E 37
I 37
D 45
		if (error = VOP_SETATTR(vp, vap, cred, p)) {
E 45
I 45
		nqsrv_getl(vp, NQL_WRITE);
		if (error = VOP_SETATTR(vp, vap, cred, nfsd->nd_procp)) {
E 45
E 37
			vput(vp);
E 22
E 3
			nfsm_reply(0);
E 69
I 69
D 82
		if (nfsd->nd_nqlflag == NQL_NOVAL) {
			tsize = fxdr_unsigned(long, sp->sa_nfssize);
			if (tsize != -1)
				vap->va_size = (u_quad_t)tsize;
			else
				vap->va_size = -1;
		} else
			fxdr_hyper(&sp->sa_nqsize, &vap->va_size);
E 82
		if (vap->va_size != -1) {
I 76
D 82
			if (error = nfsrv_access(vp, VWRITE, cred,
			    (nd.ni_cnd.cn_flags & RDONLY), nfsd->nd_procp)) {
				vput(vp);
				nfsm_reply(0);
E 82
I 82
			error = nfsrv_access(vp, VWRITE, cred,
			    (nd.ni_cnd.cn_flags & RDONLY), procp);
			if (!error) {
				nqsrv_getl(vp, ND_WRITE);
				tempsize = vap->va_size;
				VATTR_NULL(vap);
				vap->va_size = tempsize;
				error = VOP_SETATTR(vp, vap, cred,
					 procp);
E 82
			}
E 76
D 82
			nqsrv_getl(vp, NQL_WRITE);
			if (error = VOP_SETATTR(vp, vap, cred, nfsd->nd_procp)) {
E 82
I 82
			if (error)
E 82
				vput(vp);
D 82
				nfsm_reply(0);
			}
E 82
E 69
I 22
		}
E 22
D 3
		}
		vput(ndp->ni_dvp);
E 3
	}
D 3
	vp = ndp->ni_vp;
E 3
D 82
	bzero((caddr_t)fhp, sizeof(nfh));
D 16
	fhp->fh_fsid = vp->v_mount->m_fsid;
E 16
I 16
D 18
	fhp->fh_fsid = vp->v_mount->m_stat.f_fsid;
E 18
I 18
	fhp->fh_fsid = vp->v_mount->mnt_stat.f_fsid;
E 18
E 16
	if (error = VFS_VPTOFH(vp, &fhp->fh_fid)) {
E 82
I 82
	if (!error) {
		bzero((caddr_t)fhp, sizeof(nfh));
		fhp->fh_fsid = vp->v_mount->mnt_stat.f_fsid;
		error = VFS_VPTOFH(vp, &fhp->fh_fid);
		if (!error)
			error = VOP_GETATTR(vp, vap, cred, procp);
E 82
		vput(vp);
D 82
		nfsm_reply(0);
E 82
	}
D 37
	error = VOP_GETATTR(vp, vap, cred);
E 37
I 37
D 45
	error = VOP_GETATTR(vp, vap, cred, p);
E 45
I 45
D 82
	error = VOP_GETATTR(vp, vap, cred, nfsd->nd_procp);
E 45
E 37
	vput(vp);
D 69
	nfsm_reply(NFSX_FH+NFSX_FATTR);
E 69
I 69
	nfsm_reply(NFSX_FH+NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 69
	nfsm_srvfhtom(fhp);
D 7
	nfsm_build(p, u_long *, NFSX_FATTR);
	*p++ = vtonfs_type(vap->va_type);
	*p++ = vtonfs_mode(vap->va_type, vap->va_mode);
	*p++ = txdr_unsigned(vap->va_nlink);
	*p++ = txdr_unsigned(vap->va_uid);
	*p++ = txdr_unsigned(vap->va_gid);
	*p++ = txdr_unsigned(vap->va_size);
	*p++ = txdr_unsigned(vap->va_blocksize);
	*p++ = txdr_unsigned(vap->va_rdev);
D 6
	*p++ = txdr_unsigned(vap->va_bytes);
E 6
I 6
	*p++ = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
E 6
	*p++ = txdr_unsigned(vap->va_fsid);
	*p++ = txdr_unsigned(vap->va_fileid);
	txdr_time(&(vap->va_atime), p);
	p += 2;
	txdr_time(&(vap->va_mtime), p);
	p += 2;
	txdr_time(&(vap->va_ctime), p);
E 7
I 7
D 69
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR);
E 69
I 69
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 69
D 11
	fp->fa_type = vtonfs_type(vap->va_type);
	fp->fa_mode = vtonfs_mode(vap->va_type, vap->va_mode);
	fp->fa_nlink = txdr_unsigned(vap->va_nlink);
	fp->fa_uid = txdr_unsigned(vap->va_uid);
	fp->fa_gid = txdr_unsigned(vap->va_gid);
	fp->fa_size = txdr_unsigned(vap->va_size);
	fp->fa_blocksize = txdr_unsigned(vap->va_blocksize);
	fp->fa_rdev = txdr_unsigned(vap->va_rdev);
	fp->fa_blocks = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
	fp->fa_fsid = txdr_unsigned(vap->va_fsid);
	fp->fa_fileid = txdr_unsigned(vap->va_fileid);
	txdr_time(&vap->va_atime, &fp->fa_atime);
	txdr_time(&vap->va_mtime, &fp->fa_mtime);
	txdr_time(&vap->va_ctime, &fp->fa_ctime);
E 11
I 11
	nfsm_srvfillattr;
E 11
E 7
	return (error);
E 82
I 82
	if (v3) {
		if (exclusive_flag && !error &&
			bcmp(cverf, (caddr_t)&vap->va_atime, NFSX_V3CREATEVERF))
			error = EEXIST;
		diraft_ret = VOP_GETATTR(dirp, &diraft, cred, procp);
		vrele(dirp);
	}
	nfsm_reply(NFSX_SRVFH(v3) + NFSX_FATTR(v3) + NFSX_WCCDATA(v3));
	if (v3) {
		if (!error) {
			nfsm_srvpostop_fh(fhp);
			nfsm_srvpostop_attr(0, vap);
		}
		nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
	} else {
		nfsm_srvfhtom(fhp, v3);
		nfsm_build(fp, struct nfs_fattr *, NFSX_V2FATTR);
		nfsm_srvfillattr(vap, fp);
	}
	return (0);
E 82
nfsmout:
D 41
	VOP_ABORTOP(ndp);
I 21
D 25
	vput(ndp->ni_dvp);
E 25
I 25
	if (ndp->ni_dvp == ndp->ni_vp)
		vrele(ndp->ni_dvp);
E 41
I 41
D 47
	if (nd.ni_nameiop)
E 47
I 47
D 82
	if (nd.ni_cnd.cn_nameiop || nd.ni_cnd.cn_flags)
E 82
I 82
	if (dirp)
		vrele(dirp);
	if (nd.ni_cnd.cn_nameiop) {
E 82
E 47
D 42
		vrele(nd.ni_startdir);
I 82
		free((caddr_t)nd.ni_cnd.cn_pnbuf, M_NAMEI);
	}
E 82
E 42
I 42
		p->p_spare[1]--, vrele(nd.ni_startdir);
E 42
D 46
	VOP_ABORTOP(&nd);
E 46
I 46
	VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
	if (nd.ni_dvp == nd.ni_vp)
		vrele(nd.ni_dvp);
E 41
	else
D 41
		vput(ndp->ni_dvp);
E 25
	if (ndp->ni_vp)
		vput(ndp->ni_vp);
E 41
I 41
		vput(nd.ni_dvp);
	if (nd.ni_vp)
		vput(nd.ni_vp);
E 41
E 21
	return (error);
I 41
D 82

out:
I 42
	p->p_spare[1]--;
E 42
	vrele(nd.ni_startdir);
D 47
	free(nd.ni_pnbuf, M_NAMEI);
E 47
I 47
	free(nd.ni_cnd.cn_pnbuf, M_NAMEI);
E 47
	nfsm_reply(0);
E 82
E 41
}

/*
D 82
 * nfs remove service
E 82
I 82
 * nfs v3 mknod service
E 82
 */
D 11
nfsrv_remove(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_remove(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_remove(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf *mrep, *md, **mrq;
E 45
I 45
D 82
nfsrv_remove(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
E 45
	caddr_t dpos;
	struct ucred *cred;
D 11
	long xid;
E 11
I 11
D 45
	u_long xid;
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_mknod(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 61
D 64
	USES_VOP_ABORTOP;
	USES_VOP_REMOVE;
E 64
E 61
D 8
	register struct nameidata *ndp = &u.u_nd;
E 8
I 8
D 41
	struct nameidata nami;
	register struct nameidata *ndp = &nami;
E 41
I 41
D 82
	struct nameidata nd;
E 82
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	register struct nfs_fattr *fp;
	struct vattr va, dirfor, diraft;
	register struct vattr *vap = &va;
E 82
E 41
E 8
D 9
	nfsm_srvars;
E 9
I 9
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
I 82
	struct nameidata nd;
	register caddr_t cp;
E 82
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 82
	int error = 0, cache, len;
E 82
I 82
	int error = 0, cache, len, tsize, dirfor_ret = 1, diraft_ret = 1;
	u_long major, minor;
	enum vtype vtyp;
E 82
E 45
	char *cp2;
D 11
	struct mbuf *mb;
E 11
I 11
D 82
	struct mbuf *mb, *mreq;
E 11
E 9
	struct vnode *vp;
	nfsv2fh_t nfh;
E 82
I 82
	struct mbuf *mb, *mb2, *mreq;
	struct vnode *vp, *dirp = (struct vnode *)0;
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
D 45
	long len;
E 45
I 45
	u_quad_t frev;
E 45

I 82
	nd.ni_cnd.cn_nameiop = 0;
E 82
I 8
D 41
	ndinit(ndp);
E 41
E 8
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 82
	nfsm_srvstrsiz(len, NFS_MAXNAMLEN);
E 82
I 82
	nfsm_srvnamesiz(len);
E 82
D 41
	ndp->ni_cred = cred;
	ndp->ni_nameiop = DELETE | LOCKPARENT | LOCKLEAF;
D 3
	ndp->ni_segflg = UIO_SYSSPACE;
E 3
	if (error = nfs_namei(ndp, fhp, len, &md, &dpos))
E 41
I 41
D 47
	nd.ni_cred = cred;
	nd.ni_nameiop = DELETE | LOCKPARENT | LOCKLEAF;
E 47
I 47
	nd.ni_cnd.cn_cred = cred;
D 82
	nd.ni_cnd.cn_nameiop = DELETE;
	nd.ni_cnd.cn_flags = LOCKPARENT | LOCKLEAF;
E 47
D 45
	if (error = nfs_namei(&nd, fhp, len, &md, &dpos, p))
E 45
I 45
D 50
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos, nfsd->nd_procp))
E 50
I 50
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos,
	    nfsd->nd_procp))
E 50
E 45
E 41
		nfsm_reply(0);
D 41
	vp = ndp->ni_vp;
E 41
I 41
	vp = nd.ni_vp;
E 41
	if (vp->v_type == VDIR &&
D 45
		(error = suser(cred, (short *)0)))
E 45
I 45
		(error = suser(cred, (u_short *)0)))
E 82
I 82
	nd.ni_cnd.cn_nameiop = CREATE;
	nd.ni_cnd.cn_flags = LOCKPARENT | LOCKLEAF | SAVESTART;
	error = nfs_namei(&nd, fhp, len, slp, nam, &md, &dpos,
		&dirp, procp, (nfsd->nd_flag & ND_KERBAUTH));
	if (dirp)
		dirfor_ret = VOP_GETATTR(dirp, &dirfor, cred, procp);
	if (error) {
		nfsm_reply(NFSX_WCCDATA(1));
		nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
		if (dirp)
			vrele(dirp);
		return (0);
	}
	nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
	vtyp = nfsv3tov_type(*tl);
	if (vtyp != VCHR && vtyp != VBLK && vtyp != VSOCK && vtyp != VFIFO) {
		vrele(nd.ni_startdir);
		free((caddr_t)nd.ni_cnd.cn_pnbuf, M_NAMEI);
		error = NFSERR_BADTYPE;
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
		vput(nd.ni_dvp);
E 82
E 45
		goto out;
I 82
	}
	VATTR_NULL(vap);
	nfsm_srvsattr(vap);
	if (vtyp == VCHR || vtyp == VBLK) {
		nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
		major = fxdr_unsigned(u_long, *tl++);
		minor = fxdr_unsigned(u_long, *tl);
		vap->va_rdev = makedev(major, minor);
	}

E 82
	/*
D 40
	 * Don't unlink a mounted file.
E 40
I 40
D 82
	 * The root of a mounted filesystem cannot be deleted.
E 82
I 82
	 * Iff doesn't exist, create it.
E 82
E 40
	 */
D 82
	if (vp->v_flag & VROOT) {
		error = EBUSY;
E 82
I 82
	if (nd.ni_vp) {
		vrele(nd.ni_startdir);
		free((caddr_t)nd.ni_cnd.cn_pnbuf, M_NAMEI);
		error = EEXIST;
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
		vput(nd.ni_dvp);
E 82
		goto out;
	}
D 82
	if (vp->v_flag & VTEXT)
I 33
D 38
#ifdef NVM
E 38
E 33
D 30
		xrele(vp);	/* try once to free text */
E 30
I 30
		(void) vnode_pager_uncache(vp);
I 33
D 38
#else
		xrele(vp);	/* try once to free text */
#endif
E 38
E 33
E 30
out:
D 21
	if (error)
		VOP_ABORTOP(ndp);
	else
E 21
I 21
	if (!error) {
E 21
D 37
		error = VOP_REMOVE(ndp);
E 37
I 37
D 41
		error = VOP_REMOVE(ndp, p);
E 41
I 41
D 45
		error = VOP_REMOVE(&nd, p);
E 45
I 45
		nqsrv_getl(nd.ni_dvp, NQL_WRITE);
		nqsrv_getl(vp, NQL_WRITE);
D 46
		error = VOP_REMOVE(&nd, nfsd->nd_procp);
E 46
I 46
		error = VOP_REMOVE(nd.ni_dvp, nd.ni_vp, &nd.ni_cnd);
E 82
I 82
	vap->va_type = vtyp;
	if (vtyp == VSOCK) {
		vrele(nd.ni_startdir);
		nqsrv_getl(nd.ni_dvp, ND_WRITE);
		error = VOP_CREATE(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, vap);
		if (!error)
			FREE(nd.ni_cnd.cn_pnbuf, M_NAMEI);
E 82
E 46
E 45
E 41
E 37
I 21
	} else {
D 41
		VOP_ABORTOP(ndp);
D 25
		vput(ndp->ni_dvp);
E 25
I 25
		if (ndp->ni_dvp == vp)
			vrele(ndp->ni_dvp);
E 41
I 41
D 46
		VOP_ABORTOP(&nd);
E 46
I 46
D 82
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
		if (nd.ni_dvp == vp)
			vrele(nd.ni_dvp);
E 41
		else
E 82
I 82
		if (error = suser(cred, (u_short *)0)) {
			vrele(nd.ni_startdir);
			free((caddr_t)nd.ni_cnd.cn_pnbuf, M_NAMEI);
			VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 82
D 41
			vput(ndp->ni_dvp);
E 41
I 41
			vput(nd.ni_dvp);
I 82
			goto out;
		}
		nqsrv_getl(nd.ni_dvp, ND_WRITE);
		if (error = VOP_MKNOD(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, vap)) {
			vrele(nd.ni_startdir);
			goto out;
		}
		nd.ni_cnd.cn_nameiop = LOOKUP;
		nd.ni_cnd.cn_flags &= ~(LOCKPARENT | SAVESTART);
		nd.ni_cnd.cn_proc = procp;
		nd.ni_cnd.cn_cred = procp->p_ucred;
		error = lookup(&nd);
		FREE(nd.ni_cnd.cn_pnbuf, M_NAMEI);
		if (error)
			goto out;
		if (nd.ni_cnd.cn_flags & ISSYMLINK) {
			vrele(nd.ni_dvp);
			vput(nd.ni_vp);
			VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
			error = EINVAL;
		}
	}
out:
	vp = nd.ni_vp;
	if (!error) {
		bzero((caddr_t)fhp, sizeof(nfh));
		fhp->fh_fsid = vp->v_mount->mnt_stat.f_fsid;
		error = VFS_VPTOFH(vp, &fhp->fh_fid);
		if (!error)
			error = VOP_GETATTR(vp, vap, cred, procp);
E 82
E 41
E 25
		vput(vp);
	}
E 21
D 82
	nfsm_reply(0);
E 82
I 82
	diraft_ret = VOP_GETATTR(dirp, &diraft, cred, procp);
	vrele(dirp);
	nfsm_reply(NFSX_SRVFH(1) + NFSX_POSTOPATTR(1) + NFSX_WCCDATA(1));
	if (!error) {
		nfsm_srvpostop_fh(fhp);
		nfsm_srvpostop_attr(0, vap);
	}
	nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
	return (0);
nfsmout:
	if (dirp)
		vrele(dirp);
	if (nd.ni_cnd.cn_nameiop) {
		vrele(nd.ni_startdir);
		free((caddr_t)nd.ni_cnd.cn_pnbuf, M_NAMEI);
	}
	VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
	if (nd.ni_dvp == nd.ni_vp)
		vrele(nd.ni_dvp);
	else
		vput(nd.ni_dvp);
	if (nd.ni_vp)
		vput(nd.ni_vp);
	return (error);
}

/*
 * nfs remove service
 */
int
nfsrv_remove(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
{
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	struct nameidata nd;
	register u_long *tl;
	register long t1;
	caddr_t bpos;
	int error = 0, cache, len, dirfor_ret = 1, diraft_ret = 1;
	int v3 = (nfsd->nd_flag & ND_NFSV3);
	char *cp2;
	struct mbuf *mb, *mreq, *mb2;
	struct vnode *vp, *dirp;
	struct vattr dirfor, diraft;
	nfsfh_t nfh;
	fhandle_t *fhp;
	u_quad_t frev;

#ifndef nolint
	vp = (struct vnode *)0;
#endif
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
	nfsm_srvnamesiz(len);
	nd.ni_cnd.cn_cred = cred;
	nd.ni_cnd.cn_nameiop = DELETE;
	nd.ni_cnd.cn_flags = LOCKPARENT | LOCKLEAF;
	error = nfs_namei(&nd, fhp, len, slp, nam, &md, &dpos,
		&dirp, procp, (nfsd->nd_flag & ND_KERBAUTH));
	if (dirp) {
		if (v3)
			dirfor_ret = VOP_GETATTR(dirp, &dirfor, cred,
				procp);
		else
			vrele(dirp);
	}
	if (!error) {
		vp = nd.ni_vp;
		if (vp->v_type == VDIR &&
			(error = suser(cred, (u_short *)0)))
			goto out;
		/*
		 * The root of a mounted filesystem cannot be deleted.
		 */
		if (vp->v_flag & VROOT) {
			error = EBUSY;
			goto out;
		}
		if (vp->v_flag & VTEXT)
			(void) vnode_pager_uncache(vp);
out:
		if (!error) {
			nqsrv_getl(nd.ni_dvp, ND_WRITE);
			nqsrv_getl(vp, ND_WRITE);
			error = VOP_REMOVE(nd.ni_dvp, nd.ni_vp, &nd.ni_cnd);
		} else {
			VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
			if (nd.ni_dvp == vp)
				vrele(nd.ni_dvp);
			else
				vput(nd.ni_dvp);
			vput(vp);
		}
	}
	if (dirp && v3) {
		diraft_ret = VOP_GETATTR(dirp, &diraft, cred, procp);
		vrele(dirp);
	}
	nfsm_reply(NFSX_WCCDATA(v3));
	if (v3) {
		nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
		return (0);
	}
E 82
	nfsm_srvdone;
}

/*
 * nfs rename service
D 3
 * malloc() the tond structure to avoid blowing the kernel stack
E 3
 */
D 11
nfsrv_rename(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_rename(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_rename(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf *mrep, *md, **mrq;
E 45
I 45
D 82
nfsrv_rename(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
E 45
	caddr_t dpos;
	struct ucred *cred;
D 11
	long xid;
E 11
I 11
D 45
	u_long xid;
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_rename(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
I 61
D 64
	USES_VOP_ABORTOP;
	USES_VOP_RENAME;
E 64
E 61
D 3
	struct nameidata *nam, *tond;
E 3
I 3
D 41
	register struct nameidata *ndp;
E 41
E 3
D 9
	nfsm_srvars;
E 9
I 9
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 79
	int error = 0, rdonly, cache, len, len2;
E 79
I 79
D 82
	int error = 0, cache, len, len2;
E 82
I 82
	int error = 0, cache, len, len2, fdirfor_ret = 1, fdiraft_ret = 1;
	int tdirfor_ret = 1, tdiraft_ret = 1;
	int v3 = (nfsd->nd_flag & ND_NFSV3);
E 82
E 79
E 45
	char *cp2;
D 11
	struct mbuf *mb;
E 11
I 11
D 82
	struct mbuf *mb, *mreq;
E 82
I 82
	struct mbuf *mb, *mreq, *mb2;
E 82
E 11
E 9
I 3
D 8
	struct nameidata tond;
E 8
I 8
D 41
	struct nameidata nami, tond;
E 41
I 41
	struct nameidata fromnd, tond;
E 41
E 8
E 3
D 82
	struct vnode *fvp, *tvp, *tdvp;
	nfsv2fh_t fnfh, tnfh;
E 82
I 82
	struct vnode *fvp, *tvp, *tdvp, *fdirp = (struct vnode *)0;
	struct vnode *tdirp = (struct vnode *)0;
	struct vattr fdirfor, fdiraft, tdirfor, tdiraft;
	nfsfh_t fnfh, tnfh;
E 82
	fhandle_t *ffhp, *tfhp;
D 45
	long len, len2;
	int rootflg = 0;
E 45
I 45
	u_quad_t frev;
	uid_t saved_uid;
E 45

I 82
#ifndef nolint
	fvp = (struct vnode *)0;
#endif
E 82
D 3
	nam = &u.u_nd;
	MALLOC(tond, struct nameidata *, sizeof(*tond), M_TEMP, M_WAITOK);
	ndinit(tond);
	nam->ni_vp = nam->ni_dvp = (struct vnode *)0;
E 3
I 3
D 8
	ndp = &u.u_nd;
	ndp->ni_vp = ndp->ni_dvp = (struct vnode *)0;
E 8
I 8
D 41
	ndp = &nami;
	ndinit(ndp);
E 41
E 8
E 3
	ffhp = &fnfh.fh_generic;
	tfhp = &tnfh.fh_generic;
I 41
D 47
	fromnd.ni_nameiop = 0;
	tond.ni_nameiop = 0;
E 47
I 47
	fromnd.ni_cnd.cn_nameiop = 0;
	tond.ni_cnd.cn_nameiop = 0;
E 47
E 41
	nfsm_srvmtofh(ffhp);
D 82
	nfsm_srvstrsiz(len, NFS_MAXNAMLEN);
E 82
I 82
	nfsm_srvnamesiz(len);
E 82
	/*
D 45
	 * Remember if we are root so that we can reset cr_uid before
	 * the second nfs_namei() call
E 45
I 45
	 * Remember our original uid so that we can reset cr_uid before
	 * the second nfs_namei() call, in case it is remapped.
E 45
	 */
D 45
	if (cred->cr_uid == 0)
		rootflg++;
E 45
I 45
	saved_uid = cred->cr_uid;
E 45
D 3
	nam->ni_cred = cred;
	nam->ni_nameiop = DELETE | WANTPARENT;
	nam->ni_segflg = UIO_SYSSPACE;
	if (error = nfs_namei(nam, ffhp, len, &md, &dpos))
E 3
I 3
D 41
	ndp->ni_cred = cred;
D 34
	ndp->ni_nameiop = DELETE | WANTPARENT;
E 34
I 34
	ndp->ni_nameiop = DELETE | WANTPARENT | SAVESTARTDIR;
E 34
	if (error = nfs_namei(ndp, ffhp, len, &md, &dpos))
E 41
I 41
D 47
	fromnd.ni_cred = cred;
	fromnd.ni_nameiop = DELETE | WANTPARENT | SAVESTART;
E 47
I 47
	fromnd.ni_cnd.cn_cred = cred;
	fromnd.ni_cnd.cn_nameiop = DELETE;
	fromnd.ni_cnd.cn_flags = WANTPARENT | SAVESTART;
E 47
D 45
	if (error = nfs_namei(&fromnd, ffhp, len, &md, &dpos, p))
E 45
I 45
D 50
	if (error = nfs_namei(&fromnd, ffhp, len, nfsd->nd_slp, nam, &md, &dpos, nfsd->nd_procp))
E 50
I 50
D 82
	if (error = nfs_namei(&fromnd, ffhp, len, nfsd->nd_slp, nam, &md,
	    &dpos, nfsd->nd_procp))
E 50
E 45
E 41
E 3
		nfsm_reply(0);
E 82
I 82
	error = nfs_namei(&fromnd, ffhp, len, slp, nam, &md,
		&dpos, &fdirp, procp, (nfsd->nd_flag & ND_KERBAUTH));
	if (fdirp) {
		if (v3)
			fdirfor_ret = VOP_GETATTR(fdirp, &fdirfor, cred,
				procp);
		else {
			vrele(fdirp);
			fdirp = (struct vnode *)0;
		}
	}
	if (error) {
		nfsm_reply(2 * NFSX_WCCDATA(v3));
		nfsm_srvwcc_data(fdirfor_ret, &fdirfor, fdiraft_ret, &fdiraft);
		nfsm_srvwcc_data(tdirfor_ret, &tdirfor, tdiraft_ret, &tdiraft);
		if (fdirp)
			vrele(fdirp);
		return (0);
	}
E 82
I 3
D 41
	fvp = ndp->ni_vp;
E 41
I 41
	fvp = fromnd.ni_vp;
E 41
E 3
	nfsm_srvmtofh(tfhp);
D 19
	nfsm_srvstrsiz(len2, NFS_MAXNAMLEN);
E 19
I 19
	nfsm_strsiz(len2, NFS_MAXNAMLEN);
E 19
D 45
	if (rootflg)
		cred->cr_uid = 0;
E 45
I 45
	cred->cr_uid = saved_uid;
E 45
D 3
	tond->ni_cred = cred;
	crhold(cred);
	tond->ni_nameiop = RENAME | LOCKPARENT | LOCKLEAF | NOCACHE;
	tond->ni_segflg = UIO_SYSSPACE;
	error = nfs_namei(tond, tfhp, len2, &md, &dpos);
	fvp = nam->ni_vp;
	tdvp = tond->ni_dvp;
	tvp = tond->ni_vp;
E 3
I 3
D 8
	nddup(ndp, &tond);
E 8
I 8
D 41
	ndinit(&tond);
	crhold(cred);
E 41
D 47
	tond.ni_cred = cred;
E 8
D 34
	tond.ni_nameiop = RENAME | LOCKPARENT | LOCKLEAF | NOCACHE;
E 34
I 34
	tond.ni_nameiop = RENAME | LOCKPARENT | LOCKLEAF | NOCACHE
D 41
		| SAVESTARTDIR;
E 34
D 21
	error = nfs_namei(&tond, tfhp, len2, &md, &dpos);
E 21
I 21
	if (error = nfs_namei(&tond, tfhp, len2, &md, &dpos)) {
		VOP_ABORTOP(ndp);
		vrele(ndp->ni_dvp);
E 41
I 41
		| SAVESTART;
E 47
I 47
	tond.ni_cnd.cn_cred = cred;
	tond.ni_cnd.cn_nameiop = RENAME;
	tond.ni_cnd.cn_flags = LOCKPARENT | LOCKLEAF | NOCACHE | SAVESTART;
E 47
D 45
	if (error = nfs_namei(&tond, tfhp, len2, &md, &dpos, p)) {
E 45
I 45
D 50
	if (error = nfs_namei(&tond, tfhp, len2, nfsd->nd_slp, nam, &md, &dpos, nfsd->nd_procp)) {
E 50
I 50
D 82
	if (error = nfs_namei(&tond, tfhp, len2, nfsd->nd_slp, nam, &md,
	    &dpos, nfsd->nd_procp)) {
E 82
I 82
	error = nfs_namei(&tond, tfhp, len2, slp, nam, &md,
		&dpos, &tdirp, procp, (nfsd->nd_flag & ND_KERBAUTH));
	if (tdirp) {
		if (v3)
			tdirfor_ret = VOP_GETATTR(tdirp, &tdirfor, cred,
				procp);
		else {
			vrele(tdirp);
			tdirp = (struct vnode *)0;
		}
	}
	if (error) {
E 82
E 50
E 45
D 46
		VOP_ABORTOP(&fromnd);
E 46
I 46
		VOP_ABORTOP(fromnd.ni_dvp, &fromnd.ni_cnd);
E 46
		vrele(fromnd.ni_dvp);
E 41
		vrele(fvp);
		goto out1;
	}
E 21
	tdvp = tond.ni_dvp;
	tvp = tond.ni_vp;
E 3
	if (tvp != NULL) {
		if (fvp->v_type == VDIR && tvp->v_type != VDIR) {
D 82
			error = EISDIR;
E 82
I 82
			if (v3)
				error = EEXIST;
			else
				error = EISDIR;
E 82
			goto out;
		} else if (fvp->v_type != VDIR && tvp->v_type == VDIR) {
D 82
			error = ENOTDIR;
E 82
I 82
			if (v3)
				error = EEXIST;
			else
				error = ENOTDIR;
E 82
			goto out;
		}
I 45
		if (tvp->v_type == VDIR && tvp->v_mountedhere) {
D 82
			error = EXDEV;
E 82
I 82
			if (v3)
				error = EXDEV;
			else
				error = ENOTEMPTY;
E 82
			goto out;
		}
E 45
	}
I 45
	if (fvp->v_type == VDIR && fvp->v_mountedhere) {
D 82
		error = EBUSY;
E 82
I 82
		if (v3)
			error = EXDEV;
		else
			error = ENOTEMPTY;
E 82
		goto out;
	}
E 45
D 21
	if (error) {
D 3
		VOP_ABORTOP(nam);
E 3
I 3
		VOP_ABORTOP(ndp);
E 3
		goto out1;
	}
E 21
	if (fvp->v_mount != tdvp->v_mount) {
D 82
		error = EXDEV;
E 82
I 82
		if (v3)
			error = EXDEV;
		else
			error = ENOTEMPTY;
E 82
		goto out;
	}
D 41
	if (fvp == tdvp || fvp == tvp)
E 41
I 41
	if (fvp == tdvp)
E 41
D 82
		error = EINVAL;
E 82
I 82
		if (v3)
			error = EINVAL;
		else
			error = ENOTEMPTY;
E 82
I 41
	/*
	 * If source is the same as the destination (that is the
	 * same vnode with the same name in the same directory),
	 * then there is nothing to do.
	 */
	if (fvp == tvp && fromnd.ni_dvp == tdvp &&
D 47
	    fromnd.ni_namelen == tond.ni_namelen &&
	    !bcmp(fromnd.ni_ptr, tond.ni_ptr, fromnd.ni_namelen))
E 47
I 47
	    fromnd.ni_cnd.cn_namelen == tond.ni_cnd.cn_namelen &&
	    !bcmp(fromnd.ni_cnd.cn_nameptr, tond.ni_cnd.cn_nameptr,
	      fromnd.ni_cnd.cn_namelen))
E 47
		error = -1;
E 41
out:
D 21
	if (error) {
D 3
		VOP_ABORTOP(tond);
		VOP_ABORTOP(nam);
E 3
I 3
		VOP_ABORTOP(&tond);
		VOP_ABORTOP(ndp);
E 3
	} else {
E 21
I 21
	if (!error) {
E 21
I 8
D 32
		VREF(ndp->ni_cdir);
E 8
I 5
		VREF(tond.ni_cdir);
E 32
E 5
D 3
		error = VOP_RENAME(nam, tond);
E 3
I 3
D 37
		error = VOP_RENAME(ndp, &tond);
E 37
I 37
D 41
		error = VOP_RENAME(ndp, &tond, p);
E 41
I 41
D 45
		error = VOP_RENAME(&fromnd, &tond, p);
E 45
I 45
D 82
		nqsrv_getl(fromnd.ni_dvp, NQL_WRITE);
		nqsrv_getl(tdvp, NQL_WRITE);
E 82
I 82
		nqsrv_getl(fromnd.ni_dvp, ND_WRITE);
		nqsrv_getl(tdvp, ND_WRITE);
E 82
		if (tvp)
D 82
			nqsrv_getl(tvp, NQL_WRITE);
E 82
I 82
			nqsrv_getl(tvp, ND_WRITE);
E 82
D 46
		error = VOP_RENAME(&fromnd, &tond, nfsd->nd_procp);
E 46
I 46
		error = VOP_RENAME(fromnd.ni_dvp, fromnd.ni_vp, &fromnd.ni_cnd,
				   tond.ni_dvp, tond.ni_vp, &tond.ni_cnd);
E 46
E 45
E 41
E 37
I 8
D 32
		vrele(ndp->ni_cdir);
E 8
I 5
		vrele(tond.ni_cdir);
E 32
I 21
	} else {
D 46
		VOP_ABORTOP(&tond);
E 46
I 46
		VOP_ABORTOP(tond.ni_dvp, &tond.ni_cnd);
E 46
D 25
		vput(tdvp);
E 25
I 25
		if (tdvp == tvp)
			vrele(tdvp);
		else
			vput(tdvp);
E 25
		if (tvp)
			vput(tvp);
D 41
		VOP_ABORTOP(ndp);
		vrele(ndp->ni_dvp);
E 41
I 41
D 46
		VOP_ABORTOP(&fromnd);
E 46
I 46
		VOP_ABORTOP(fromnd.ni_dvp, &fromnd.ni_cnd);
E 46
		vrele(fromnd.ni_dvp);
E 41
		vrele(fvp);
I 82
		if (error == -1)
			error = 0;
E 82
E 21
E 5
E 3
	}
I 42
	p->p_spare[1]--;
E 42
I 34
	vrele(tond.ni_startdir);
I 41
D 47
	FREE(tond.ni_pnbuf, M_NAMEI);
E 47
I 47
	FREE(tond.ni_cnd.cn_pnbuf, M_NAMEI);
E 47
E 41
E 34
out1:
I 82
	if (fdirp) {
		fdiraft_ret = VOP_GETATTR(fdirp, &fdiraft, cred, procp);
		vrele(fdirp);
	}
	if (tdirp) {
		tdiraft_ret = VOP_GETATTR(tdirp, &tdiraft, cred, procp);
		vrele(tdirp);
	}
E 82
I 42
	p->p_spare[1]--;
E 42
I 34
D 41
	vrele(ndp->ni_startdir);
E 34
D 3
	crfree(tond->ni_cred);
	FREE((caddr_t)tond, M_TEMP);
E 3
I 3
D 5
	ndrele(&tond);
E 5
I 5
D 8
	ndrele(ndp);
E 8
I 8
	crfree(cred);
E 41
I 41
	vrele(fromnd.ni_startdir);
D 47
	FREE(fromnd.ni_pnbuf, M_NAMEI);
E 47
I 47
	FREE(fromnd.ni_cnd.cn_pnbuf, M_NAMEI);
E 47
E 41
E 8
E 5
E 3
D 82
	nfsm_reply(0);
	return (error);
E 82
I 82
	nfsm_reply(2 * NFSX_WCCDATA(v3));
	if (v3) {
		nfsm_srvwcc_data(fdirfor_ret, &fdirfor, fdiraft_ret, &fdiraft);
		nfsm_srvwcc_data(tdirfor_ret, &tdirfor, tdiraft_ret, &tdiraft);
	}
	return (0);
E 82
I 41

E 41
nfsmout:
I 34
D 41
	if (ndp->ni_nameiop & SAVESTARTDIR)
		vrele(ndp->ni_startdir);
E 34
D 3
	VOP_ABORTOP(nam);
	free((caddr_t)tond, M_TEMP);
E 3
I 3
	VOP_ABORTOP(ndp);
I 21
	vrele(ndp->ni_dvp);
	vrele(fvp);
E 41
I 41
D 47
	if (tond.ni_nameiop) {
E 47
I 47
D 82
	if (tond.ni_cnd.cn_nameiop || tond.ni_cnd.cn_flags) {
E 82
I 82
	if (fdirp)
		vrele(fdirp);
	if (tdirp)
		vrele(tdirp);
	if (tond.ni_cnd.cn_nameiop) {
E 82
E 47
I 42
		p->p_spare[1]--;
E 42
		vrele(tond.ni_startdir);
D 47
		FREE(tond.ni_pnbuf, M_NAMEI);
E 47
I 47
		FREE(tond.ni_cnd.cn_pnbuf, M_NAMEI);
E 47
	}
D 47
	if (fromnd.ni_nameiop) {
E 47
I 47
D 82
	if (fromnd.ni_cnd.cn_nameiop || fromnd.ni_cnd.cn_flags) {
E 82
I 82
	if (fromnd.ni_cnd.cn_nameiop) {
E 82
E 47
I 42
		p->p_spare[1]--;
E 42
		vrele(fromnd.ni_startdir);
D 47
		FREE(fromnd.ni_pnbuf, M_NAMEI);
E 47
I 47
		FREE(fromnd.ni_cnd.cn_pnbuf, M_NAMEI);
E 47
D 46
		VOP_ABORTOP(&fromnd);
E 46
I 46
		VOP_ABORTOP(fromnd.ni_dvp, &fromnd.ni_cnd);
E 46
		vrele(fromnd.ni_dvp);
		vrele(fvp);
	}
E 41
E 21
E 3
	return (error);
}

/*
 * nfs link service
 */
D 11
nfsrv_link(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_link(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_link(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf *mrep, *md, **mrq;
E 45
I 45
D 82
nfsrv_link(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
E 45
	caddr_t dpos;
	struct ucred *cred;
D 11
	long xid;
E 11
I 11
D 45
	u_long xid;
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_link(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
I 61
D 64
	USES_VOP_ABORTOP;
	USES_VOP_LINK;
E 64
E 61
D 8
	register struct nameidata *ndp = &u.u_nd;
E 8
I 8
D 41
	struct nameidata nami;
	register struct nameidata *ndp = &nami;
E 41
I 41
	struct nameidata nd;
E 41
E 8
D 9
	nfsm_srvars;
E 9
I 9
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 82
	int error = 0, rdonly, cache, len;
E 82
I 82
	int error = 0, rdonly, cache, len, dirfor_ret = 1, diraft_ret = 1;
	int getret = 1, v3 = (nfsd->nd_flag & ND_NFSV3);
E 82
E 45
	char *cp2;
D 11
	struct mbuf *mb;
E 11
I 11
D 82
	struct mbuf *mb, *mreq;
E 11
E 9
	struct vnode *vp, *xp;
	nfsv2fh_t nfh, dnfh;
E 82
I 82
	struct mbuf *mb, *mreq, *mb2;
	struct vnode *vp, *xp, *dirp = (struct vnode *)0;
	struct vattr dirfor, diraft, at;
	nfsfh_t nfh, dnfh;
E 82
	fhandle_t *fhp, *dfhp;
D 45
	long len;
E 45
I 45
	u_quad_t frev;
E 45

I 8
D 41
	ndinit(ndp);
E 41
E 8
	fhp = &nfh.fh_generic;
	dfhp = &dnfh.fh_generic;
	nfsm_srvmtofh(fhp);
	nfsm_srvmtofh(dfhp);
D 82
	nfsm_srvstrsiz(len, NFS_MAXNAMLEN);
D 45
	if (error = nfsrv_fhtovp(fhp, FALSE, &vp, cred))
E 45
I 45
	if (error = nfsrv_fhtovp(fhp, FALSE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
E 45
		nfsm_reply(0);
E 82
I 82
	nfsm_srvnamesiz(len);
	if (error = nfsrv_fhtovp(fhp, FALSE, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
		nfsm_reply(NFSX_POSTOPATTR(v3) + NFSX_WCCDATA(v3));
		nfsm_srvpostop_attr(getret, &at);
		nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
		return (0);
	}
E 82
D 45
	if (vp->v_type == VDIR && (error = suser(cred, NULL)))
E 45
I 45
	if (vp->v_type == VDIR && (error = suser(cred, (u_short *)0)))
E 45
		goto out1;
D 41
	ndp->ni_cred = cred;
	ndp->ni_nameiop = CREATE | LOCKPARENT;
D 3
	ndp->ni_segflg = UIO_SYSSPACE;
E 3
	if (error = nfs_namei(ndp, dfhp, len, &md, &dpos))
E 41
I 41
D 47
	nd.ni_cred = cred;
	nd.ni_nameiop = CREATE | LOCKPARENT;
E 47
I 47
	nd.ni_cnd.cn_cred = cred;
	nd.ni_cnd.cn_nameiop = CREATE;
	nd.ni_cnd.cn_flags = LOCKPARENT;
E 47
D 45
	if (error = nfs_namei(&nd, dfhp, len, &md, &dpos, p))
E 45
I 45
D 50
	if (error = nfs_namei(&nd, dfhp, len, nfsd->nd_slp, nam, &md, &dpos, nfsd->nd_procp))
E 50
I 50
D 82
	if (error = nfs_namei(&nd, dfhp, len, nfsd->nd_slp, nam, &md, &dpos,
	    nfsd->nd_procp))
E 82
I 82
	error = nfs_namei(&nd, dfhp, len, slp, nam, &md, &dpos,
		&dirp, procp, (nfsd->nd_flag & ND_KERBAUTH));
	if (dirp) {
		if (v3)
			dirfor_ret = VOP_GETATTR(dirp, &dirfor, cred,
				procp);
		else {
			vrele(dirp);
			dirp = (struct vnode *)0;
		}
	}
	if (error)
E 82
E 50
E 45
E 41
		goto out1;
D 41
	xp = ndp->ni_vp;
E 41
I 41
	xp = nd.ni_vp;
E 41
	if (xp != NULL) {
		error = EEXIST;
		goto out;
	}
D 41
	xp = ndp->ni_dvp;
E 41
I 41
	xp = nd.ni_dvp;
E 41
	if (vp->v_mount != xp->v_mount)
		error = EXDEV;
out:
D 21
	if (error)
		VOP_ABORTOP(ndp);
	else
E 21
I 21
	if (!error) {
E 21
D 37
		error = VOP_LINK(vp, ndp);
E 37
I 37
D 41
		error = VOP_LINK(vp, ndp, p);
E 41
I 41
D 45
		error = VOP_LINK(vp, &nd, p);
E 45
I 45
D 82
		nqsrv_getl(vp, NQL_WRITE);
		nqsrv_getl(xp, NQL_WRITE);
E 82
I 82
		nqsrv_getl(vp, ND_WRITE);
		nqsrv_getl(xp, ND_WRITE);
E 82
D 46
		error = VOP_LINK(vp, &nd, nfsd->nd_procp);
E 46
I 46
D 51
		error = VOP_LINK(vp, nd.ni_dvp, &nd.ni_cnd);
E 51
I 51
D 81
		error = VOP_LINK(nd.ni_dvp, vp, &nd.ni_cnd);
E 81
I 81
		error = VOP_LINK(vp, nd.ni_dvp, &nd.ni_cnd);
E 81
E 51
E 46
E 45
E 41
E 37
I 21
	} else {
D 41
		VOP_ABORTOP(ndp);
D 25
		vput(ndp->ni_dvp);
E 25
I 25
		if (ndp->ni_dvp == ndp->ni_vp)
			vrele(ndp->ni_dvp);
E 41
I 41
D 46
		VOP_ABORTOP(&nd);
E 46
I 46
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
		if (nd.ni_dvp == nd.ni_vp)
			vrele(nd.ni_dvp);
E 41
		else
D 41
			vput(ndp->ni_dvp);
E 25
		if (ndp->ni_vp)
			vrele(ndp->ni_vp);
E 41
I 41
			vput(nd.ni_dvp);
		if (nd.ni_vp)
			vrele(nd.ni_vp);
E 41
	}
E 21
out1:
I 82
	if (v3)
		getret = VOP_GETATTR(vp, &at, cred, procp);
	if (dirp) {
		diraft_ret = VOP_GETATTR(dirp, &diraft, cred, procp);
		vrele(dirp);
	}
E 82
	vrele(vp);
D 82
	nfsm_reply(0);
E 82
I 82
	nfsm_reply(NFSX_POSTOPATTR(v3) + NFSX_WCCDATA(v3));
	if (v3) {
		nfsm_srvpostop_attr(getret, &at);
		nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
		return (0);
	}
E 82
	nfsm_srvdone;
}

/*
 * nfs symbolic link service
 */
D 11
nfsrv_symlink(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_symlink(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_symlink(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf *mrep, *md, **mrq;
E 45
I 45
D 82
nfsrv_symlink(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
E 45
	caddr_t dpos;
	struct ucred *cred;
D 11
	long xid;
E 11
I 11
D 45
	u_long xid;
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_symlink(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 61
D 64
	USES_VOP_ABORTOP;
	USES_VOP_SYMLINK;
E 64
E 61
D 82
	struct vattr va;
E 82
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	struct vattr va, dirfor, diraft;
E 82
D 8
	register struct nameidata *ndp = &u.u_nd;
E 8
I 8
D 41
	struct nameidata nami;
	register struct nameidata *ndp = &nami;
E 41
I 41
	struct nameidata nd;
E 41
E 8
	register struct vattr *vap = &va;
D 9
	nfsm_srvars;
E 9
I 9
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
I 29
	struct nfsv2_sattr *sp;
E 29
D 82
	caddr_t bpos;
E 82
I 82
	char *bpos, *cp, *pathcp = (char *)0, *cp2;
E 82
I 19
	struct uio io;
	struct iovec iv;
E 19
D 45
	int error = 0;
E 45
I 45
D 79
	int error = 0, rdonly, cache, len, len2;
E 79
I 79
D 82
	int error = 0, cache, len, len2;
E 79
E 45
D 19
	char *cp2;
E 19
I 19
	char *pathcp, *cp2;
E 19
D 11
	struct mbuf *mb;
E 11
I 11
	struct mbuf *mb, *mreq;
E 11
E 9
D 21
	struct vnode *vp;
E 21
	nfsv2fh_t nfh;
E 82
I 82
	int error = 0, cache, len, len2, dirfor_ret = 1, diraft_ret = 1;
	int v3 = (nfsd->nd_flag & ND_NFSV3);
	struct mbuf *mb, *mreq, *mb2;
	struct vnode *dirp = (struct vnode *)0;
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
D 20
	long len, tlen, len2;
E 20
I 20
D 45
	long len, len2;
E 45
I 45
	u_quad_t frev;
E 45
E 20

I 19
D 82
	pathcp = (char *)0;
E 82
I 82
	nd.ni_cnd.cn_nameiop = 0;
E 82
E 19
D 8
	ndp->ni_vp = ndp->ni_dvp = (struct vnode *)0;
E 8
I 8
D 41
	ndinit(ndp);
E 41
E 8
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 82
	nfsm_srvstrsiz(len, NFS_MAXNAMLEN);
E 82
I 82
	nfsm_srvnamesiz(len);
E 82
D 41
	ndp->ni_cred = cred;
	ndp->ni_nameiop = CREATE | LOCKPARENT;
D 3
	ndp->ni_segflg = UIO_SYSSPACE;
E 3
	if (error = nfs_namei(ndp, fhp, len, &md, &dpos))
E 41
I 41
D 47
	nd.ni_cred = cred;
	nd.ni_nameiop = CREATE | LOCKPARENT;
E 47
I 47
	nd.ni_cnd.cn_cred = cred;
	nd.ni_cnd.cn_nameiop = CREATE;
D 82
	nd.ni_cnd.cn_flags = LOCKPARENT;
E 47
D 45
	if (error = nfs_namei(&nd, fhp, len, &md, &dpos, p))
E 45
I 45
D 50
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos, nfsd->nd_procp))
E 50
I 50
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos,
	    nfsd->nd_procp))
E 82
I 82
	nd.ni_cnd.cn_flags = LOCKPARENT | SAVESTART;
	error = nfs_namei(&nd, fhp, len, slp, nam, &md, &dpos,
		&dirp, procp, (nfsd->nd_flag & ND_KERBAUTH));
	if (dirp) {
		if (v3)
			dirfor_ret = VOP_GETATTR(dirp, &dirfor, cred,
				procp);
		else {
			vrele(dirp);
			dirp = (struct vnode *)0;
		}
	}
	if (error)
E 82
E 50
E 45
E 41
D 21
		goto out1;
E 21
I 21
		goto out;
I 82
	VATTR_NULL(vap);
	if (v3)
		nfsm_srvsattr(vap);
E 82
E 21
D 19
	nfsm_srvstrsiz(len2, NFS_MAXPATHLEN);
	tlen = nfsm_rndup(len2);
	if (len2 == tlen) {
		nfsm_disect(cp2, caddr_t, tlen+NFSX_UNSIGNED);
		*(cp2+tlen) = '\0';
	} else {
		nfsm_disect(cp2, caddr_t, tlen);
	}
E 19
I 19
	nfsm_strsiz(len2, NFS_MAXPATHLEN);
	MALLOC(pathcp, caddr_t, len2 + 1, M_TEMP, M_WAITOK);
	iv.iov_base = pathcp;
	iv.iov_len = len2;
	io.uio_resid = len2;
	io.uio_offset = 0;
	io.uio_iov = &iv;
	io.uio_iovcnt = 1;
	io.uio_segflg = UIO_SYSSPACE;
	io.uio_rw = UIO_READ;
I 37
	io.uio_procp = (struct proc *)0;
E 37
	nfsm_mtouio(&io, len2);
I 29
D 45
	nfsm_disect(sp, struct nfsv2_sattr *, NFSX_SATTR);
E 45
I 45
D 69
	nfsm_dissect(sp, struct nfsv2_sattr *, NFSX_SATTR);
E 69
I 69
D 82
	nfsm_dissect(sp, struct nfsv2_sattr *, NFSX_SATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 82
I 82
	if (!v3) {
		nfsm_dissect(sp, struct nfsv2_sattr *, NFSX_V2SATTR);
		vap->va_mode = fxdr_unsigned(u_short, sp->sa_mode);
	}
E 82
E 69
E 45
E 29
	*(pathcp + len2) = '\0';
E 19
D 21
	vp = ndp->ni_vp;
	if (vp) {
E 21
I 21
D 41
	if (ndp->ni_vp) {
		VOP_ABORTOP(ndp);
D 25
		vput(ndp->ni_dvp);
E 25
I 25
		if (ndp->ni_dvp == ndp->ni_vp)
			vrele(ndp->ni_dvp);
E 41
I 41
	if (nd.ni_vp) {
I 82
		vrele(nd.ni_startdir);
		free(nd.ni_cnd.cn_pnbuf, M_NAMEI);
E 82
D 46
		VOP_ABORTOP(&nd);
E 46
I 46
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
		if (nd.ni_dvp == nd.ni_vp)
			vrele(nd.ni_dvp);
E 41
		else
D 41
			vput(ndp->ni_dvp);
E 25
		vrele(ndp->ni_vp);
E 41
I 41
			vput(nd.ni_dvp);
		vrele(nd.ni_vp);
E 41
E 21
		error = EEXIST;
		goto out;
	}
D 21
	vp = ndp->ni_dvp;
E 21
D 17
	vattr_null(vap);
E 17
I 17
D 82
	VATTR_NULL(vap);
E 17
D 29
	vap->va_mode = 0777;
E 29
I 29
	vap->va_mode = fxdr_unsigned(u_short, sp->sa_mode);
E 29
I 21
D 37
	error = VOP_SYMLINK(ndp, vap, pathcp);
E 37
I 37
D 41
	error = VOP_SYMLINK(ndp, vap, pathcp, p);
E 41
I 41
D 45
	error = VOP_SYMLINK(&nd, vap, pathcp, p);
E 45
I 45
	nqsrv_getl(nd.ni_dvp, NQL_WRITE);
E 82
I 82
	nqsrv_getl(nd.ni_dvp, ND_WRITE);
E 82
D 46
	error = VOP_SYMLINK(&nd, vap, pathcp, nfsd->nd_procp);
E 46
I 46
	error = VOP_SYMLINK(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, vap, pathcp);
I 82
	if (error)
		vrele(nd.ni_startdir);
	else {
	    if (v3) {
		nd.ni_cnd.cn_nameiop = LOOKUP;
		nd.ni_cnd.cn_flags &= ~(LOCKPARENT | SAVESTART | FOLLOW);
		nd.ni_cnd.cn_flags |= (NOFOLLOW | LOCKLEAF);
		nd.ni_cnd.cn_proc = procp;
		nd.ni_cnd.cn_cred = cred;
		error = lookup(&nd);
		if (!error) {
			bzero((caddr_t)fhp, sizeof(nfh));
			fhp->fh_fsid = nd.ni_vp->v_mount->mnt_stat.f_fsid;
			error = VFS_VPTOFH(nd.ni_vp, &fhp->fh_fid);
			if (!error)
				error = VOP_GETATTR(nd.ni_vp, vap, cred,
					procp);
			vput(nd.ni_vp);
		}
	    } else
		vrele(nd.ni_startdir);
	    FREE(nd.ni_cnd.cn_pnbuf, M_NAMEI);
	}
E 82
E 46
E 45
E 41
E 37
E 21
out:
D 21
	if (error)
		VOP_ABORTOP(ndp);
	else
D 19
		error = VOP_SYMLINK(ndp, vap, cp2);
E 19
I 19
		error = VOP_SYMLINK(ndp, vap, pathcp);
E 19
out1:
E 21
I 19
	if (pathcp)
		FREE(pathcp, M_TEMP);
E 19
D 82
	nfsm_reply(0);
	return (error);
E 82
I 82
	if (dirp) {
		diraft_ret = VOP_GETATTR(dirp, &diraft, cred, procp);
		vrele(dirp);
	}
	nfsm_reply(NFSX_SRVFH(v3) + NFSX_POSTOPATTR(v3) + NFSX_WCCDATA(v3));
	if (v3) {
		if (!error) {
			nfsm_srvpostop_fh(fhp);
			nfsm_srvpostop_attr(0, vap);
		}
		nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
	}
	return (0);
E 82
nfsmout:
I 82
	if (nd.ni_cnd.cn_nameiop) {
		vrele(nd.ni_startdir);
		free(nd.ni_cnd.cn_pnbuf, M_NAMEI);
	}
	if (dirp)
		vrele(dirp);
E 82
D 41
	VOP_ABORTOP(ndp);
I 21
D 25
	vput(ndp->ni_dvp);
E 25
I 25
	if (ndp->ni_dvp == ndp->ni_vp)
		vrele(ndp->ni_dvp);
E 41
I 41
D 46
	VOP_ABORTOP(&nd);
E 46
I 46
	VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
	if (nd.ni_dvp == nd.ni_vp)
		vrele(nd.ni_dvp);
E 41
	else
D 41
		vput(ndp->ni_dvp);
E 25
	if (ndp->ni_vp);
		vrele(ndp->ni_vp);
E 41
I 41
		vput(nd.ni_dvp);
	if (nd.ni_vp)
		vrele(nd.ni_vp);
E 41
E 21
I 19
	if (pathcp)
		FREE(pathcp, M_TEMP);
E 19
	return (error);
}

/*
 * nfs mkdir service
 */
D 11
nfsrv_mkdir(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_mkdir(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_mkdir(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf *mrep, *md, **mrq;
E 45
I 45
D 82
nfsrv_mkdir(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
E 45
	caddr_t dpos;
	struct ucred *cred;
D 11
	long xid;
E 11
I 11
D 45
	u_long xid;
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_mkdir(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 61
D 64
	USES_VOP_ABORTOP;
	USES_VOP_GETATTR;
	USES_VOP_MKDIR;
E 64
E 61
D 82
	struct vattr va;
E 82
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	struct vattr va, dirfor, diraft;
E 82
	register struct vattr *vap = &va;
I 7
D 82
	register struct nfsv2_fattr *fp;
E 82
I 82
	register struct nfs_fattr *fp;
E 82
E 7
D 8
	register struct nameidata *ndp = &u.u_nd;
E 8
I 8
D 41
	struct nameidata nami;
	register struct nameidata *ndp = &nami;
E 41
I 41
	struct nameidata nd;
E 41
E 8
D 9
	nfsm_srvars;
E 9
I 9
	register caddr_t cp;
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 78
	int error = 0, rdonly, cache, len;
E 78
I 78
D 82
	int error = 0, cache, len;
E 82
I 82
	int error = 0, cache, len, dirfor_ret = 1, diraft_ret = 1;
	int v3 = (nfsd->nd_flag & ND_NFSV3);
E 82
E 78
E 45
	char *cp2;
D 11
	struct mbuf *mb, *mb2;
E 11
I 11
	struct mbuf *mb, *mb2, *mreq;
E 11
E 9
D 82
	struct vnode *vp;
	nfsv2fh_t nfh;
E 82
I 82
	struct vnode *vp, *dirp = (struct vnode *)0;
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
D 45
	long len;
E 45
I 45
	u_quad_t frev;
E 45

D 8
	ndp->ni_vp = ndp->ni_dvp = (struct vnode *)0;
E 8
I 8
D 41
	ndinit(ndp);
E 41
E 8
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 82
	nfsm_srvstrsiz(len, NFS_MAXNAMLEN);
E 82
I 82
	nfsm_srvnamesiz(len);
E 82
D 41
	ndp->ni_cred = cred;
D 34
	ndp->ni_nameiop = CREATE | LOCKPARENT;
E 34
I 34
	ndp->ni_nameiop = CREATE | LOCKPARENT | SAVESTARTDIR;
E 34
D 3
	ndp->ni_segflg = UIO_SYSSPACE;
E 3
	if (error = nfs_namei(ndp, fhp, len, &md, &dpos))
E 41
I 41
D 47
	nd.ni_cred = cred;
	nd.ni_nameiop = CREATE | LOCKPARENT;
E 47
I 47
	nd.ni_cnd.cn_cred = cred;
	nd.ni_cnd.cn_nameiop = CREATE;
	nd.ni_cnd.cn_flags = LOCKPARENT;
E 47
D 45
	if (error = nfs_namei(&nd, fhp, len, &md, &dpos, p))
E 45
I 45
D 50
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos, nfsd->nd_procp))
E 50
I 50
D 82
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos,
	    nfsd->nd_procp))
E 50
E 45
E 41
		nfsm_reply(0);
D 37
	nfsm_disect(p, u_long *, NFSX_UNSIGNED);
E 37
I 37
D 45
	nfsm_disect(tl, u_long *, NFSX_UNSIGNED);
E 45
I 45
	nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
E 82
I 82
	error = nfs_namei(&nd, fhp, len, slp, nam, &md, &dpos,
		&dirp, procp, (nfsd->nd_flag & ND_KERBAUTH));
	if (dirp) {
		if (v3)
			dirfor_ret = VOP_GETATTR(dirp, &dirfor, cred,
				procp);
		else {
			vrele(dirp);
			dirp = (struct vnode *)0;
		}
	}
	if (error) {
		nfsm_reply(NFSX_WCCDATA(v3));
		nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
		if (dirp)
			vrele(dirp);
		return (0);
	}
E 82
E 45
E 37
D 17
	vattr_null(vap);
E 17
I 17
	VATTR_NULL(vap);
I 82
	if (v3) {
		nfsm_srvsattr(vap);
	} else {
		nfsm_dissect(tl, u_long *, NFSX_UNSIGNED);
		vap->va_mode = nfstov_mode(*tl++);
	}
E 82
E 17
	vap->va_type = VDIR;
D 37
	vap->va_mode = nfstov_mode(*p++);
E 37
I 37
D 82
	vap->va_mode = nfstov_mode(*tl++);
E 82
E 37
D 41
	vp = ndp->ni_vp;
E 41
I 41
	vp = nd.ni_vp;
E 41
	if (vp != NULL) {
D 41
		VOP_ABORTOP(ndp);
I 21
D 25
		vput(ndp->ni_dvp);
E 25
I 25
		if (ndp->ni_dvp == vp)
			vrele(ndp->ni_dvp);
E 41
I 41
D 46
		VOP_ABORTOP(&nd);
E 46
I 46
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
		if (nd.ni_dvp == vp)
			vrele(nd.ni_dvp);
E 41
		else
D 41
			vput(ndp->ni_dvp);
E 41
I 41
			vput(nd.ni_dvp);
E 41
E 25
		vrele(vp);
I 34
D 41
		vrele(ndp->ni_startdir);
E 41
E 34
E 21
		error = EEXIST;
D 82
		nfsm_reply(0);
E 82
I 82
		goto out;
E 82
	}
D 34
	if (error = VOP_MKDIR(ndp, vap))
E 34
I 34
D 37
	error = VOP_MKDIR(ndp, vap);
E 37
I 37
D 41
	error = VOP_MKDIR(ndp, vap, p);
E 37
	vrele(ndp->ni_startdir);
	if (error)
E 41
I 41
D 45
	if (error = VOP_MKDIR(&nd, vap, p))
E 45
I 45
D 82
	nqsrv_getl(nd.ni_dvp, NQL_WRITE);
D 46
	if (error = VOP_MKDIR(&nd, vap, nfsd->nd_procp))
E 46
I 46
	if (error = VOP_MKDIR(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, vap))
E 46
E 45
E 41
E 34
		nfsm_reply(0);
D 41
	vp = ndp->ni_vp;
E 41
I 41
	vp = nd.ni_vp;
E 41
	bzero((caddr_t)fhp, sizeof(nfh));
D 16
	fhp->fh_fsid = vp->v_mount->m_fsid;
E 16
I 16
D 18
	fhp->fh_fsid = vp->v_mount->m_stat.f_fsid;
E 18
I 18
	fhp->fh_fsid = vp->v_mount->mnt_stat.f_fsid;
E 18
E 16
	if (error = VFS_VPTOFH(vp, &fhp->fh_fid)) {
E 82
I 82
	nqsrv_getl(nd.ni_dvp, ND_WRITE);
	error = VOP_MKDIR(nd.ni_dvp, &nd.ni_vp, &nd.ni_cnd, vap);
	if (!error) {
		vp = nd.ni_vp;
		bzero((caddr_t)fhp, sizeof(nfh));
		fhp->fh_fsid = vp->v_mount->mnt_stat.f_fsid;
		error = VFS_VPTOFH(vp, &fhp->fh_fid);
		if (!error)
			error = VOP_GETATTR(vp, vap, cred, procp);
E 82
		vput(vp);
D 82
		nfsm_reply(0);
E 82
	}
D 37
	error = VOP_GETATTR(vp, vap, cred);
E 37
I 37
D 45
	error = VOP_GETATTR(vp, vap, cred, p);
E 45
I 45
D 82
	error = VOP_GETATTR(vp, vap, cred, nfsd->nd_procp);
E 45
E 37
	vput(vp);
D 69
	nfsm_reply(NFSX_FH+NFSX_FATTR);
E 69
I 69
	nfsm_reply(NFSX_FH+NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 69
	nfsm_srvfhtom(fhp);
D 7
	nfsm_build(p, u_long *, NFSX_FATTR);
	*p++ = vtonfs_type(vap->va_type);
	*p++ = vtonfs_mode(vap->va_type, vap->va_mode);
	*p++ = txdr_unsigned(vap->va_nlink);
	*p++ = txdr_unsigned(vap->va_uid);
	*p++ = txdr_unsigned(vap->va_gid);
	*p++ = txdr_unsigned(vap->va_size);
	*p++ = txdr_unsigned(vap->va_blocksize);
	*p++ = txdr_unsigned(vap->va_rdev);
D 6
	*p++ = txdr_unsigned(vap->va_bytes);
E 6
I 6
	*p++ = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
E 6
	*p++ = txdr_unsigned(vap->va_fsid);
	*p++ = txdr_unsigned(vap->va_fileid);
	txdr_time(&(vap->va_atime), p);
	p += 2;
	txdr_time(&(vap->va_mtime), p);
	p += 2;
	txdr_time(&(vap->va_ctime), p);
E 7
I 7
D 69
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR);
E 69
I 69
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR(nfsd->nd_nqlflag != NQL_NOVAL));
E 69
D 11
	fp->fa_type = vtonfs_type(vap->va_type);
	fp->fa_mode = vtonfs_mode(vap->va_type, vap->va_mode);
	fp->fa_nlink = txdr_unsigned(vap->va_nlink);
	fp->fa_uid = txdr_unsigned(vap->va_uid);
	fp->fa_gid = txdr_unsigned(vap->va_gid);
	fp->fa_size = txdr_unsigned(vap->va_size);
	fp->fa_blocksize = txdr_unsigned(vap->va_blocksize);
	fp->fa_rdev = txdr_unsigned(vap->va_rdev);
	fp->fa_blocks = txdr_unsigned(vap->va_bytes / vap->va_blocksize);
	fp->fa_fsid = txdr_unsigned(vap->va_fsid);
	fp->fa_fileid = txdr_unsigned(vap->va_fileid);
	txdr_time(&vap->va_atime, &fp->fa_atime);
	txdr_time(&vap->va_mtime, &fp->fa_mtime);
	txdr_time(&vap->va_ctime, &fp->fa_ctime);
E 11
I 11
	nfsm_srvfillattr;
E 11
E 7
	return (error);
E 82
I 82
out:
	if (dirp) {
		diraft_ret = VOP_GETATTR(dirp, &diraft, cred, procp);
		vrele(dirp);
	}
	nfsm_reply(NFSX_SRVFH(v3) + NFSX_POSTOPATTR(v3) + NFSX_WCCDATA(v3));
	if (v3) {
		if (!error) {
			nfsm_srvpostop_fh(fhp);
			nfsm_srvpostop_attr(0, vap);
		}
		nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
	} else {
		nfsm_srvfhtom(fhp, v3);
		nfsm_build(fp, struct nfs_fattr *, NFSX_V2FATTR);
		nfsm_srvfillattr(vap, fp);
	}
	return (0);
E 82
nfsmout:
I 82
	if (dirp)
		vrele(dirp);
E 82
D 41
	VOP_ABORTOP(ndp);
I 21
D 25
	vput(ndp->ni_dvp);
E 25
I 25
	if (ndp->ni_dvp == ndp->ni_vp)
		vrele(ndp->ni_dvp);
E 41
I 41
D 46
	VOP_ABORTOP(&nd);
E 46
I 46
	VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
	if (nd.ni_dvp == nd.ni_vp)
		vrele(nd.ni_dvp);
E 41
	else
D 41
		vput(ndp->ni_dvp);
E 25
	if (ndp->ni_vp)
		vrele(ndp->ni_vp);
E 41
I 41
		vput(nd.ni_dvp);
	if (nd.ni_vp)
		vrele(nd.ni_vp);
E 41
E 21
	return (error);
}

/*
 * nfs rmdir service
 */
D 11
nfsrv_rmdir(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_rmdir(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_rmdir(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf *mrep, *md, **mrq;
E 45
I 45
D 82
nfsrv_rmdir(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
E 45
	caddr_t dpos;
	struct ucred *cred;
D 11
	long xid;
E 11
I 11
D 45
	u_long xid;
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_rmdir(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
I 61
D 64
	USES_VOP_ABORTOP;
	USES_VOP_RMDIR;
E 64
E 61
D 8
	register struct nameidata *ndp = &u.u_nd;
E 8
I 8
D 41
	struct nameidata nami;
	register struct nameidata *ndp = &nami;
E 41
E 8
D 9
	nfsm_srvars;
E 9
I 9
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 78
	int error = 0, rdonly, cache, len;
E 78
I 78
D 82
	int error = 0, cache, len;
E 82
I 82
	int error = 0, cache, len, dirfor_ret = 1, diraft_ret = 1;
	int v3 = (nfsd->nd_flag & ND_NFSV3);
E 82
E 78
E 45
	char *cp2;
D 11
	struct mbuf *mb;
E 11
I 11
D 82
	struct mbuf *mb, *mreq;
E 11
E 9
	struct vnode *vp;
	nfsv2fh_t nfh;
E 82
I 82
	struct mbuf *mb, *mreq, *mb2;
	struct vnode *vp, *dirp = (struct vnode *)0;
	struct vattr dirfor, diraft;
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
D 45
	long len;
E 45
I 41
	struct nameidata nd;
I 45
	u_quad_t frev;
E 45
E 41

I 8
D 41
	ndinit(ndp);
E 41
E 8
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 82
	nfsm_srvstrsiz(len, NFS_MAXNAMLEN);
E 82
I 82
	nfsm_srvnamesiz(len);
E 82
D 41
	ndp->ni_cred = cred;
	ndp->ni_nameiop = DELETE | LOCKPARENT | LOCKLEAF;
D 3
	ndp->ni_segflg = UIO_SYSSPACE;
E 3
	if (error = nfs_namei(ndp, fhp, len, &md, &dpos))
E 41
I 41
D 47
	nd.ni_cred = cred;
	nd.ni_nameiop = DELETE | LOCKPARENT | LOCKLEAF;
E 47
I 47
	nd.ni_cnd.cn_cred = cred;
	nd.ni_cnd.cn_nameiop = DELETE;
	nd.ni_cnd.cn_flags = LOCKPARENT | LOCKLEAF;
E 47
D 45
	if (error = nfs_namei(&nd, fhp, len, &md, &dpos, p))
E 45
I 45
D 50
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos, nfsd->nd_procp))
E 50
I 50
D 82
	if (error = nfs_namei(&nd, fhp, len, nfsd->nd_slp, nam, &md, &dpos,
	    nfsd->nd_procp))
E 50
E 45
E 41
		nfsm_reply(0);
E 82
I 82
	error = nfs_namei(&nd, fhp, len, slp, nam, &md, &dpos,
		&dirp, procp, (nfsd->nd_flag & ND_KERBAUTH));
	if (dirp) {
		if (v3)
			dirfor_ret = VOP_GETATTR(dirp, &dirfor, cred,
				procp);
		else {
			vrele(dirp);
			dirp = (struct vnode *)0;
		}
	}
	if (error) {
		nfsm_reply(NFSX_WCCDATA(v3));
		nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
		if (dirp)
			vrele(dirp);
		return (0);
	}
E 82
D 41
	vp = ndp->ni_vp;
E 41
I 41
	vp = nd.ni_vp;
E 41
	if (vp->v_type != VDIR) {
		error = ENOTDIR;
		goto out;
	}
	/*
	 * No rmdir "." please.
	 */
D 41
	if (ndp->ni_dvp == vp) {
E 41
I 41
	if (nd.ni_dvp == vp) {
E 41
		error = EINVAL;
		goto out;
	}
	/*
D 40
	 * Don't unlink a mounted file.
E 40
I 40
	 * The root of a mounted filesystem cannot be deleted.
E 40
	 */
	if (vp->v_flag & VROOT)
		error = EBUSY;
out:
D 21
	if (error)
		VOP_ABORTOP(ndp);
	else
E 21
I 21
	if (!error) {
E 21
D 37
		error = VOP_RMDIR(ndp);
E 37
I 37
D 41
		error = VOP_RMDIR(ndp, p);
E 41
I 41
D 45
		error = VOP_RMDIR(&nd, p);
E 45
I 45
D 82
		nqsrv_getl(nd.ni_dvp, NQL_WRITE);
		nqsrv_getl(vp, NQL_WRITE);
E 82
I 82
		nqsrv_getl(nd.ni_dvp, ND_WRITE);
		nqsrv_getl(vp, ND_WRITE);
E 82
D 46
		error = VOP_RMDIR(&nd, nfsd->nd_procp);
E 46
I 46
		error = VOP_RMDIR(nd.ni_dvp, nd.ni_vp, &nd.ni_cnd);
E 46
E 45
E 41
E 37
I 21
	} else {
D 41
		VOP_ABORTOP(ndp);
D 25
		vput(ndp->ni_dvp);
E 25
I 25
		if (ndp->ni_dvp == ndp->ni_vp)
			vrele(ndp->ni_dvp);
E 41
I 41
D 46
		VOP_ABORTOP(&nd);
E 46
I 46
		VOP_ABORTOP(nd.ni_dvp, &nd.ni_cnd);
E 46
		if (nd.ni_dvp == nd.ni_vp)
			vrele(nd.ni_dvp);
E 41
		else
D 41
			vput(ndp->ni_dvp);
E 41
I 41
			vput(nd.ni_dvp);
E 41
E 25
		vput(vp);
	}
E 21
D 82
	nfsm_reply(0);
E 82
I 82
	if (dirp) {
		diraft_ret = VOP_GETATTR(dirp, &diraft, cred, procp);
		vrele(dirp);
	}
	nfsm_reply(NFSX_WCCDATA(v3));
	if (v3) {
		nfsm_srvwcc_data(dirfor_ret, &dirfor, diraft_ret, &diraft);
		return (0);
	}
E 82
	nfsm_srvdone;
}

/*
 * nfs readdir service
 * - mallocs what it thinks is enough to read
D 3
 *      count rounded up to a multiple of DIRBLKSIZ <= MAX_READDIR
E 3
I 3
D 19
 *	count rounded up to a multiple of DIRBLKSIZ <= MAX_READDIR
E 19
I 19
D 37
 *	count rounded up to a multiple of DIRBLKSIZ <= NFS_MAXREADDIR
E 37
I 37
 *	count rounded up to a multiple of NFS_DIRBLKSIZ <= NFS_MAXREADDIR
E 37
E 19
E 3
 * - calls VOP_READDIR()
D 12
 * - loops arround building the reply
E 12
I 12
 * - loops around building the reply
E 12
D 3
 *      if the output generated exceeds count break out of loop
 *      The nfsm_clget macro is used here so that the reply will be packed
 *      tightly in mbuf clusters.
E 3
I 3
 *	if the output generated exceeds count break out of loop
 *	The nfsm_clget macro is used here so that the reply will be packed
 *	tightly in mbuf clusters.
E 3
 * - it only knows that it has encountered eof when the VOP_READDIR()
D 3
 *      reads nothing
E 3
I 3
 *	reads nothing
E 3
 * - as such one readdir rpc will return eof false although you are there
D 3
 *      and then the next will return eof
E 3
I 3
 *	and then the next will return eof
E 3
D 48
 * - it trims out records with d_ino == 0
E 48
I 48
 * - it trims out records with d_fileno == 0
E 48
D 3
 *      this doesn't matter for Unix clients, but they might confuse clients
 *      for other os'.
E 3
I 3
 *	this doesn't matter for Unix clients, but they might confuse clients
 *	for other os'.
E 3
 * NB: It is tempting to set eof to true if the VOP_READDIR() reads less
D 3
 *      than requested, but this may not apply to all filesystems. For
 *      example, client NFS does not { although it is never remote mounted
 *      anyhow }
E 3
I 3
 *	than requested, but this may not apply to all filesystems. For
 *	example, client NFS does not { although it is never remote mounted
 *	anyhow }
I 45
D 82
 *     The alternate call nqnfsrv_readdirlook() does lookups as well.
E 82
I 82
 *     The alternate call nfsrv_readdirplus() does lookups as well.
E 82
E 45
E 3
 * PS: The NFS protocol spec. does not clarify what the "count" byte
D 3
 *      argument is a count of.. just name strings and file id's or the
 *      entire reply rpc or ...
 *      I tried just file name and id sizes and it confused the Sun client,
 *      so I am using the full rpc size now. The "paranoia.." comment refers
 *      to including the status longwords that are not a part of the dir.
 *      "entry" structures, but are in the rpc.
E 3
I 3
 *	argument is a count of.. just name strings and file id's or the
 *	entire reply rpc or ...
 *	I tried just file name and id sizes and it confused the Sun client,
 *	so I am using the full rpc size now. The "paranoia.." comment refers
 *	to including the status longwords that are not a part of the dir.
 *	"entry" structures, but are in the rpc.
E 3
 */
D 11
nfsrv_readdir(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_readdir(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_readdir(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf **mrq;
E 45
I 45
struct flrep {
D 82
	u_long fl_cachable;
	u_long fl_duration;
D 67
	u_quad_t fl_frev;
E 67
I 67
	u_long fl_frev[2];
E 67
	nfsv2fh_t fl_nfh;
D 69
	struct nfsv2_fattr fl_fattr;
E 69
I 69
	u_long fl_fattr[NFSX_NQFATTR / sizeof (u_long)];
E 82
I 82
	nfsuint64	fl_off;
	u_long		fl_postopok;
	u_long		fl_fattr[NFSX_V3FATTR / sizeof (u_long)];
	u_long		fl_fhok;
	u_long		fl_fhsize;
	u_long		fl_nfh[NFSX_V3FH / sizeof (u_long)];
E 82
E 69
};

D 82
nfsrv_readdir(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
E 45
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
D 45
	u_long xid;
I 11
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_readdir(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
I 61
D 64
	USES_VOP_READDIR;
	USES_VOP_UNLOCK;
E 64
E 61
	register char *bp, *be;
	register struct mbuf *mp;
D 48
	register struct direct *dp;
E 48
I 48
	register struct dirent *dp;
E 48
D 9
	nfsm_srvars;
E 9
I 9
	register caddr_t cp;
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
	char *cp2;
D 11
	struct mbuf *mb, *mb2;
E 11
I 11
	struct mbuf *mb, *mb2, *mreq;
E 11
E 9
	char *cpos, *cend;
	int len, nlen, rem, xfer, tsiz, i;
E 45
I 45
	struct mbuf *mb, *mb2, *mreq, *mp2;
	char *cpos, *cend, *cp2, *rbuf;
E 45
	struct vnode *vp;
D 45
	struct mbuf *mp2, *mp3;
E 45
D 82
	nfsv2fh_t nfh;
E 82
I 82
	struct vattr at;
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
	struct uio io;
	struct iovec iv;
D 15
	int siz, cnt, fullsiz;
E 15
I 15
D 45
	int siz, cnt, fullsiz, eofflag;
E 45
I 45
D 78
	struct vattr va;
E 78
D 82
	int len, nlen, rem, xfer, tsiz, i, error = 0;
	int siz, cnt, fullsiz, eofflag, rdonly, cache;
	u_quad_t frev;
E 45
E 15
D 69
	u_long on;
D 45
	char *rbuf;
E 45
	off_t off, toff;
E 69
I 69
D 80
	u_long on, off, toff;
E 80
I 80
	u_long off, *cookiebuf, *cookie;
	int ncookies;
E 82
I 82
	int len, nlen, rem, xfer, tsiz, i, error = 0, getret = 1;
	int siz, cnt, fullsiz, eofflag, rdonly, cache, ncookies;
	int v3 = (nfsd->nd_flag & ND_NFSV3);
	u_quad_t frev, off, toff, verf;
	u_long *cookies = NULL, *cookiep;
E 82
E 80
E 69

	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 37
	nfsm_disect(p, u_long *, 2*NFSX_UNSIGNED);
	toff = fxdr_unsigned(off_t, *p++);
	off = (toff & ~(DIRBLKSIZ-1));
	on = (toff & (DIRBLKSIZ-1));
	cnt = fxdr_unsigned(int, *p);
D 19
	siz = ((cnt+DIRBLKSIZ) & ~(DIRBLKSIZ-1));
	if (cnt > MAX_READDIR)
		siz = MAX_READDIR;
E 19
I 19
	siz = ((cnt+DIRBLKSIZ-1) & ~(DIRBLKSIZ-1));
E 37
I 37
D 45
	nfsm_disect(tl, u_long *, 2*NFSX_UNSIGNED);
E 45
I 45
D 82
	nfsm_dissect(tl, u_long *, 2*NFSX_UNSIGNED);
E 45
D 69
	toff = fxdr_unsigned(off_t, *tl++);
E 69
I 69
D 80
	toff = fxdr_unsigned(u_long, *tl++);
E 69
	off = (toff & ~(NFS_DIRBLKSIZ-1));
	on = (toff & (NFS_DIRBLKSIZ-1));
E 80
I 80
	off = fxdr_unsigned(u_long, *tl++);
E 82
I 82
	if (v3) {
		nfsm_dissect(tl, u_long *, 5 * NFSX_UNSIGNED);
		fxdr_hyper(tl, &toff);
		tl += 2;
		fxdr_hyper(tl, &verf);
		tl += 2;
	} else {
		nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
		toff = fxdr_unsigned(u_quad_t, *tl++);
	}
	off = toff;
E 82
E 80
	cnt = fxdr_unsigned(int, *tl);
D 82
	siz = ((cnt+NFS_DIRBLKSIZ-1) & ~(NFS_DIRBLKSIZ-1));
E 37
	if (cnt > NFS_MAXREADDIR)
		siz = NFS_MAXREADDIR;
E 82
I 82
	siz = ((cnt + DIRBLKSIZ - 1) & ~(DIRBLKSIZ - 1));
	xfer = NFS_SRVMAXDATA(nfsd);
	if (siz > xfer)
		siz = xfer;
E 82
E 19
	fullsiz = siz;
I 80
D 82
	ncookies = siz / 16;	/* Guess at the number of cookies needed. */
E 80
D 45
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred))
E 45
I 45
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
E 45
		nfsm_reply(0);
D 2
	if (error = vn_access(vp, VEXEC, cred)) {
E 2
I 2
D 4
	if (error = VOP_ACCESS(vp, VEXEC, cred)) {
E 4
I 4
D 37
	if (error = nfsrv_access(vp, VEXEC, cred)) {
E 37
I 37
D 45
	if (error = nfsrv_access(vp, VEXEC, cred, p)) {
E 45
I 45
	nqsrv_getl(vp, NQL_READ);
	if (error = nfsrv_access(vp, VEXEC, cred, rdonly, nfsd->nd_procp)) {
E 82
I 82
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
		nfsm_reply(NFSX_UNSIGNED);
		nfsm_srvpostop_attr(getret, &at);
		return (0);
	}
	nqsrv_getl(vp, ND_READ);
	if (v3) {
		error = getret = VOP_GETATTR(vp, &at, cred, procp);
		if (!error && toff && verf != at.va_filerev)
			error = NFSERR_BAD_COOKIE;
	}
	if (!error)
		error = nfsrv_access(vp, VEXEC, cred, rdonly, procp);
	if (error) {
E 82
E 45
E 37
E 4
E 2
		vput(vp);
D 82
		nfsm_reply(0);
E 82
I 82
		nfsm_reply(NFSX_POSTOPATTR(v3));
		nfsm_srvpostop_attr(getret, &at);
		return (0);
E 82
	}
D 83
	VOP_UNLOCK(vp);
E 83
I 83
	VOP_UNLOCK(vp, 0, procp);
E 83
	MALLOC(rbuf, caddr_t, siz, M_TEMP, M_WAITOK);
I 80
D 82
	MALLOC(cookiebuf, u_long *, ncookies * sizeof(*cookiebuf), M_TEMP,
	    M_WAITOK);
E 82
E 80
again:
	iv.iov_base = rbuf;
	iv.iov_len = fullsiz;
	io.uio_iov = &iv;
	io.uio_iovcnt = 1;
D 69
	io.uio_offset = off;
E 69
I 69
	io.uio_offset = (off_t)off;
E 69
	io.uio_resid = fullsiz;
	io.uio_segflg = UIO_SYSSPACE;
	io.uio_rw = UIO_READ;
I 37
	io.uio_procp = (struct proc *)0;
E 37
D 10
	error = VOP_READDIR(vp, &io, &off, cred);
E 10
I 10
D 15
	error = VOP_READDIR(vp, &io, cred);
E 15
I 15
D 63
	error = VOP_READDIR(vp, &io, cred, &eofflag);
E 63
I 63
D 80
	error = VOP_READDIR(vp, &io, cred);
E 80
I 80
D 82
	error = VOP_READDIR(vp, &io, cred, &eofflag, cookiebuf, ncookies);
	cookie = cookiebuf;
E 82
I 82
	eofflag = 0;
	if (cookies) {
		free((caddr_t)cookies, M_TEMP);
		cookies = NULL;
	}
	error = VOP_READDIR(vp, &io, cred, &eofflag, &ncookies, &cookies);
E 82
E 80
E 63
E 15
D 69
	off = io.uio_offset;
E 69
I 69
	off = (off_t)io.uio_offset;
I 82
	if (!cookies && !error)
		error = NFSERR_PERM;
	if (v3) {
		getret = VOP_GETATTR(vp, &at, cred, procp);
		if (!error)
			error = getret;
	}
E 82
E 69
E 10
	if (error) {
		vrele(vp);
I 80
D 82
		free((caddr_t)cookiebuf, M_TEMP);
E 82
E 80
		free((caddr_t)rbuf, M_TEMP);
D 82
		nfsm_reply(0);
E 82
I 82
		if (cookies)
			free((caddr_t)cookies, M_TEMP);
		nfsm_reply(NFSX_POSTOPATTR(v3));
		nfsm_srvpostop_attr(getret, &at);
		return (0);
E 82
	}
I 63
D 80
	if (io.uio_resid < fullsiz)
		eofflag = 0;
	else
		eofflag = 1;
E 80
E 63
	if (io.uio_resid) {
		siz -= io.uio_resid;

		/*
		 * If nothing read, return eof
		 * rpc reply
		 */
		if (siz == 0) {
			vrele(vp);
D 82
			nfsm_reply(2*NFSX_UNSIGNED);
D 37
			nfsm_build(p, u_long *, 2*NFSX_UNSIGNED);
			*p++ = nfs_false;
			*p = nfs_true;
E 37
I 37
			nfsm_build(tl, u_long *, 2*NFSX_UNSIGNED);
E 82
I 82
			nfsm_reply(NFSX_POSTOPATTR(v3) + NFSX_COOKIEVERF(v3) +
				2 * NFSX_UNSIGNED);
			if (v3) {
				nfsm_srvpostop_attr(getret, &at);
				nfsm_build(tl, u_long *, 4 * NFSX_UNSIGNED);
				txdr_hyper(&at.va_filerev, tl);
				tl += 2;
			} else
				nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
E 82
			*tl++ = nfs_false;
			*tl = nfs_true;
I 80
D 82
			FREE((caddr_t)cookiebuf, M_TEMP);
E 82
E 80
E 37
			FREE((caddr_t)rbuf, M_TEMP);
I 82
			FREE((caddr_t)cookies, M_TEMP);
E 82
			return (0);
		}
	}
D 12
	cpos = rbuf+on;
	cend = rbuf+siz;
	dp = (struct direct *)cpos;
E 12
I 12

E 12
	/*
	 * Check for degenerate cases of nothing useful read.
D 12
	 * If so  go try again
E 12
I 12
	 * If so go try again
E 12
	 */
D 12
	if (cpos >= cend || (dp->d_ino == 0 && (cpos+dp->d_reclen) >= cend)) {
E 12
I 12
D 80
	cpos = rbuf + on;
E 80
I 80
	cpos = rbuf;
E 80
	cend = rbuf + siz;
D 48
	dp = (struct direct *)cpos;
	while (cpos < cend && dp->d_ino == 0) {
E 48
I 48
D 80
	dp = (struct dirent *)cpos;
	while (cpos < cend && dp->d_fileno == 0) {
E 48
		cpos += dp->d_reclen;
E 80
I 80
D 82
	while (cpos < cend) {
E 82
I 82
	dp = (struct dirent *)cpos;
	cookiep = cookies;
	while (dp->d_fileno == 0 && cpos < cend && ncookies > 0) {
		cpos += dp->d_reclen;
E 82
E 80
D 48
		dp = (struct direct *)cpos;
E 48
I 48
		dp = (struct dirent *)cpos;
I 80
D 82
		if (dp->d_fileno == 0) {
			cpos += dp->d_reclen;
			cookie++;
		} else
			break;
E 82
I 82
		cookiep++;
		ncookies--;
E 82
E 80
E 48
	}
D 82
	if (cpos >= cend) {
E 82
I 82
	if (cpos >= cend || ncookies == 0) {
		toff = off;
E 82
E 12
D 80
		toff = off;
E 80
		siz = fullsiz;
D 80
		on = 0;
E 80
		goto again;
	}
I 12

D 80
	cpos = rbuf + on;
	cend = rbuf + siz;
D 48
	dp = (struct direct *)cpos;
E 48
I 48
	dp = (struct dirent *)cpos;
E 80
E 48
I 45
D 82
	len = 3*NFSX_UNSIGNED;	/* paranoia, probably can be 0 */
	nfsm_reply(siz);
E 82
I 82
	len = 3 * NFSX_UNSIGNED;	/* paranoia, probably can be 0 */
	nfsm_reply(NFSX_POSTOPATTR(v3) + NFSX_COOKIEVERF(v3) + siz);
	if (v3) {
		nfsm_srvpostop_attr(getret, &at);
		nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
		txdr_hyper(&at.va_filerev, tl);
	}
E 82
	mp = mp2 = mb;
	bp = bpos;
	be = bp + M_TRAILINGSPACE(mp);

	/* Loop through the records and build reply */
D 82
	while (cpos < cend) {
E 82
I 82
	while (cpos < cend && ncookies > 0) {
E 82
D 48
		if (dp->d_ino != 0) {
E 48
I 48
		if (dp->d_fileno != 0) {
E 48
			nlen = dp->d_namlen;
			rem = nfsm_rndup(nlen)-nlen;
D 82
			len += (4*NFSX_UNSIGNED + nlen + rem);
E 82
I 82
			len += (4 * NFSX_UNSIGNED + nlen + rem);
			if (v3)
				len += 2 * NFSX_UNSIGNED;
E 82
			if (len > cnt) {
				eofflag = 0;
				break;
			}
D 48
	
			/* Build the directory record xdr from the direct entry */
E 48
I 48
			/*
			 * Build the directory record xdr from
			 * the dirent entry.
			 */
E 48
			nfsm_clget;
			*tl = nfs_true;
			bp += NFSX_UNSIGNED;
I 82
			if (v3) {
				nfsm_clget;
				*tl = 0;
				bp += NFSX_UNSIGNED;
			}
E 82
			nfsm_clget;
D 48
			*tl = txdr_unsigned(dp->d_ino);
E 48
I 48
			*tl = txdr_unsigned(dp->d_fileno);
E 48
			bp += NFSX_UNSIGNED;
			nfsm_clget;
			*tl = txdr_unsigned(nlen);
			bp += NFSX_UNSIGNED;
	
			/* And loop around copying the name */
			xfer = nlen;
			cp = dp->d_name;
			while (xfer > 0) {
				nfsm_clget;
				if ((bp+xfer) > be)
					tsiz = be-bp;
				else
					tsiz = xfer;
				bcopy(cp, bp, tsiz);
				bp += tsiz;
				xfer -= tsiz;
				if (xfer > 0)
					cp += tsiz;
			}
			/* And null pad to a long boundary */
			for (i = 0; i < rem; i++)
				*bp++ = '\0';
			nfsm_clget;
	
			/* Finish off the record */
D 80
			toff += dp->d_reclen;
			*tl = txdr_unsigned(toff);
E 80
I 80
D 82
			*tl = txdr_unsigned(*cookie);
E 82
I 82
			if (v3) {
				*tl = 0;
				bp += NFSX_UNSIGNED;
				nfsm_clget;
			}
			*tl = txdr_unsigned(*cookiep);
E 82
E 80
			bp += NFSX_UNSIGNED;
D 80
		} else
			toff += dp->d_reclen;
E 80
I 80
		}
E 80
		cpos += dp->d_reclen;
D 48
		dp = (struct direct *)cpos;
E 48
I 48
		dp = (struct dirent *)cpos;
I 80
D 82
		cookie++;
E 82
I 82
		cookiep++;
		ncookies--;
E 82
E 80
E 48
	}
E 45
E 12
	vrele(vp);
I 45
	nfsm_clget;
	*tl = nfs_false;
	bp += NFSX_UNSIGNED;
	nfsm_clget;
	if (eofflag)
		*tl = nfs_true;
	else
		*tl = nfs_false;
	bp += NFSX_UNSIGNED;
	if (mp != mb) {
		if (bp < be)
			mp->m_len = bp - mtod(mp, caddr_t);
	} else
		mp->m_len += bp - bpos;
I 80
D 82
	FREE(cookiebuf, M_TEMP);
E 80
	FREE(rbuf, M_TEMP);
E 82
I 82
	FREE((caddr_t)rbuf, M_TEMP);
	FREE((caddr_t)cookies, M_TEMP);
E 82
	nfsm_srvdone;
}

D 82
nqnfsrv_readdirlook(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_readdirplus(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
I 63
D 64
	USES_VOP_VGET;
E 63
I 61
	USES_VOP_GETATTR;
	USES_VOP_READDIR;
	USES_VOP_UNLOCK;
E 64
E 61
	register char *bp, *be;
	register struct mbuf *mp;
D 48
	register struct direct *dp;
E 48
I 48
	register struct dirent *dp;
E 48
	register caddr_t cp;
	register u_long *tl;
	register long t1;
	caddr_t bpos;
	struct mbuf *mb, *mb2, *mreq, *mp2;
	char *cpos, *cend, *cp2, *rbuf;
	struct vnode *vp, *nvp;
	struct flrep fl;
D 63
	struct ufid *ufp = (struct ufid *)&fl.fl_nfh.fh_generic.fh_fid;
	struct mount *mntp;
E 63
D 82
	nfsv2fh_t nfh;
	fhandle_t *fhp;
E 82
I 82
	nfsfh_t nfh;
	fhandle_t *fhp, *nfhp = (fhandle_t *)fl.fl_nfh;
E 82
	struct uio io;
	struct iovec iv;
D 82
	struct vattr va, *vap = &va;
	struct nfsv2_fattr *fp;
	int len, nlen, rem, xfer, tsiz, i, error = 0, duration2, cache2;
	int siz, cnt, fullsiz, eofflag, rdonly, cache;
	u_quad_t frev, frev2;
D 69
	u_long on;
	off_t off, toff;
E 69
I 69
D 80
	u_long on, off, toff;
E 80
I 80
	u_long off, *cookiebuf, *cookie;
	int ncookies;
E 82
I 82
	struct vattr va, at, *vap = &va;
	struct nfs_fattr *fp;
	int len, nlen, rem, xfer, tsiz, i, error = 0, getret = 1;
	int siz, cnt, fullsiz, eofflag, rdonly, cache, dirlen, ncookies;
	u_quad_t frev, off, toff, verf;
	u_long *cookies = NULL, *cookiep;
E 82
E 80
E 69

	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 82
	nfsm_dissect(tl, u_long *, 3*NFSX_UNSIGNED);
D 69
	toff = fxdr_unsigned(off_t, *tl++);
E 69
I 69
D 80
	toff = fxdr_unsigned(u_long, *tl++);
E 69
	off = (toff & ~(NFS_DIRBLKSIZ-1));
	on = (toff & (NFS_DIRBLKSIZ-1));
E 80
I 80
	off = fxdr_unsigned(u_long, *tl++);
E 80
	cnt = fxdr_unsigned(int, *tl++);
	duration2 = fxdr_unsigned(int, *tl);
	siz = ((cnt+NFS_DIRBLKSIZ-1) & ~(NFS_DIRBLKSIZ-1));
	if (cnt > NFS_MAXREADDIR)
		siz = NFS_MAXREADDIR;
E 82
I 82
	nfsm_dissect(tl, u_long *, 6 * NFSX_UNSIGNED);
	fxdr_hyper(tl, &toff);
	tl += 2;
	fxdr_hyper(tl, &verf);
	tl += 2;
	siz = fxdr_unsigned(int, *tl++);
	cnt = fxdr_unsigned(int, *tl);
	off = toff;
	siz = ((siz + DIRBLKSIZ - 1) & ~(DIRBLKSIZ - 1));
	xfer = NFS_SRVMAXDATA(nfsd);
	if (siz > xfer)
		siz = xfer;
E 82
	fullsiz = siz;
I 80
D 82
	ncookies = siz / 16;	/* Guess at the number of cookies needed. */
E 80
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
		nfsm_reply(0);
	nqsrv_getl(vp, NQL_READ);
	if (error = nfsrv_access(vp, VEXEC, cred, rdonly, nfsd->nd_procp)) {
E 82
I 82
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
		nfsm_reply(NFSX_UNSIGNED);
		nfsm_srvpostop_attr(getret, &at);
		return (0);
	}
	error = getret = VOP_GETATTR(vp, &at, cred, procp);
	if (!error && toff && verf != at.va_filerev)
		error = NFSERR_BAD_COOKIE;
	if (!error) {
		nqsrv_getl(vp, ND_READ);
		error = nfsrv_access(vp, VEXEC, cred, rdonly, procp);
	}
	if (error) {
E 82
		vput(vp);
D 82
		nfsm_reply(0);
E 82
I 82
		nfsm_reply(NFSX_V3POSTOPATTR);
		nfsm_srvpostop_attr(getret, &at);
		return (0);
E 82
	}
D 83
	VOP_UNLOCK(vp);
E 83
I 83
	VOP_UNLOCK(vp, 0, procp);
E 83
	MALLOC(rbuf, caddr_t, siz, M_TEMP, M_WAITOK);
I 80
D 82
	MALLOC(cookiebuf, u_long *, ncookies * sizeof(*cookiebuf), M_TEMP,
	    M_WAITOK);
E 82
E 80
again:
	iv.iov_base = rbuf;
	iv.iov_len = fullsiz;
	io.uio_iov = &iv;
	io.uio_iovcnt = 1;
D 69
	io.uio_offset = off;
E 69
I 69
	io.uio_offset = (off_t)off;
E 69
	io.uio_resid = fullsiz;
	io.uio_segflg = UIO_SYSSPACE;
	io.uio_rw = UIO_READ;
	io.uio_procp = (struct proc *)0;
D 63
	error = VOP_READDIR(vp, &io, cred, &eofflag);
E 63
I 63
D 80
	error = VOP_READDIR(vp, &io, cred);
E 80
I 80
D 82
	error = VOP_READDIR(vp, &io, cred, &eofflag, cookiebuf, ncookies);
	cookie = cookiebuf;
E 80
E 63
D 69
	off = io.uio_offset;
E 69
I 69
	off = (u_long)io.uio_offset;
E 82
I 82
	eofflag = 0;
	if (cookies) {
		free((caddr_t)cookies, M_TEMP);
		cookies = NULL;
	}
	error = VOP_READDIR(vp, &io, cred, &eofflag, &ncookies, &cookies);
	off = (u_quad_t)io.uio_offset;
	getret = VOP_GETATTR(vp, &at, cred, procp);
	if (!cookies && !error)
		error = NFSERR_PERM;
	if (!error)
		error = getret;
E 82
E 69
	if (error) {
		vrele(vp);
I 80
D 82
		free((caddr_t)cookiebuf, M_TEMP);
E 82
I 82
		if (cookies)
			free((caddr_t)cookies, M_TEMP);
E 82
E 80
		free((caddr_t)rbuf, M_TEMP);
D 82
		nfsm_reply(0);
E 82
I 82
		nfsm_reply(NFSX_V3POSTOPATTR);
		nfsm_srvpostop_attr(getret, &at);
		return (0);
E 82
	}
I 63
D 80
	if (io.uio_resid < fullsiz)
		eofflag = 0;
	else
		eofflag = 1;
E 80
E 63
	if (io.uio_resid) {
		siz -= io.uio_resid;

		/*
		 * If nothing read, return eof
		 * rpc reply
		 */
		if (siz == 0) {
			vrele(vp);
D 69
			nfsm_reply(2*NFSX_UNSIGNED);
			nfsm_build(tl, u_long *, 2*NFSX_UNSIGNED);
E 69
I 69
D 82
			nfsm_reply(2 * NFSX_UNSIGNED);
			nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
E 82
I 82
			nfsm_reply(NFSX_V3POSTOPATTR + NFSX_V3COOKIEVERF +
				2 * NFSX_UNSIGNED);
			nfsm_srvpostop_attr(getret, &at);
			nfsm_build(tl, u_long *, 4 * NFSX_UNSIGNED);
			txdr_hyper(&at.va_filerev, tl);
			tl += 2;
E 82
E 69
			*tl++ = nfs_false;
			*tl = nfs_true;
I 80
D 82
			FREE((caddr_t)cookiebuf, M_TEMP);
E 82
I 82
			FREE((caddr_t)cookies, M_TEMP);
E 82
E 80
			FREE((caddr_t)rbuf, M_TEMP);
			return (0);
		}
	}

	/*
	 * Check for degenerate cases of nothing useful read.
	 * If so go try again
	 */
D 80
	cpos = rbuf + on;
E 80
I 80
	cpos = rbuf;
E 80
	cend = rbuf + siz;
D 48
	dp = (struct direct *)cpos;
	while (cpos < cend && dp->d_ino == 0) {
E 48
I 48
D 80
	dp = (struct dirent *)cpos;
	while (cpos < cend && dp->d_fileno == 0) {
E 48
		cpos += dp->d_reclen;
E 80
I 80
D 82
	while (cpos < cend) {
E 82
I 82
	dp = (struct dirent *)cpos;
	cookiep = cookies;
	while (dp->d_fileno == 0 && cpos < cend && ncookies > 0) {
		cpos += dp->d_reclen;
E 82
E 80
D 48
		dp = (struct direct *)cpos;
E 48
I 48
		dp = (struct dirent *)cpos;
I 80
D 82
		if (dp->d_fileno == 0) {
			cpos += dp->d_reclen;
			cookie++;
		} else
			break;
E 82
I 82
		cookiep++;
		ncookies--;
E 82
E 80
E 48
	}
D 82
	if (cpos >= cend) {
E 82
I 82
	if (cpos >= cend || ncookies == 0) {
		toff = off;
E 82
D 80
		toff = off;
E 80
		siz = fullsiz;
D 80
		on = 0;
E 80
		goto again;
	}

D 80
	cpos = rbuf + on;
	cend = rbuf + siz;
D 48
	dp = (struct direct *)cpos;
E 48
I 48
	dp = (struct dirent *)cpos;
E 80
E 48
E 45
D 3
	len = 3*NFSX_UNSIGNED;  /* paranoia, probably can be 0 */
E 3
I 3
D 69
	len = 3*NFSX_UNSIGNED;	/* paranoia, probably can be 0 */
E 69
I 69
D 82
	len = 3 * NFSX_UNSIGNED;	/* paranoia, probably can be 0 */
E 69
E 3
D 45
	bp = be = (caddr_t)0;
	mp3 = (struct mbuf *)0;
E 45
	nfsm_reply(siz);
E 82
I 82
	dirlen = len = NFSX_V3POSTOPATTR + NFSX_V3COOKIEVERF + 2 * NFSX_UNSIGNED;
	nfsm_reply(cnt);
	nfsm_srvpostop_attr(getret, &at);
	nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
	txdr_hyper(&at.va_filerev, tl);
E 82
I 45
	mp = mp2 = mb;
	bp = bpos;
	be = bp + M_TRAILINGSPACE(mp);
D 63
	mntp = vp->v_mount;
E 63
E 45

	/* Loop through the records and build reply */
D 82
	while (cpos < cend) {
E 82
I 82
	while (cpos < cend && ncookies > 0) {
E 82
D 48
		if (dp->d_ino != 0) {
E 48
I 48
		if (dp->d_fileno != 0) {
E 48
			nlen = dp->d_namlen;
			rem = nfsm_rndup(nlen)-nlen;
D 3

E 3
I 3
	
E 3
			/*
D 45
			 * As noted above, the NFS spec. is not clear about what
			 * should be included in "count" as totalled up here in
			 * "len".
E 45
I 45
			 * For readdir_and_lookup get the vnode using
			 * the file number.
E 45
			 */
D 45
			len += (4*NFSX_UNSIGNED+nlen+rem);
E 45
I 45
D 63
			bzero((caddr_t)&fl.fl_nfh, sizeof (nfsv2fh_t));
			ufp->ufid_len = sizeof (struct ufid);
D 48
			ufp->ufid_ino = dp->d_ino;
E 48
I 48
			ufp->ufid_ino = dp->d_fileno;
E 48
			fl.fl_nfh.fh_generic.fh_fsid = mntp->mnt_stat.f_fsid;
			if (VFS_FHTOVP(mntp, (struct fid *)ufp, 1, &nvp))
E 63
I 63
D 64
			if (VOP_VGET(vp, dp->d_fileno, &nvp))
E 64
I 64
			if (VFS_VGET(vp->v_mount, dp->d_fileno, &nvp))
E 64
E 63
				goto invalid;
I 68
D 82
			bzero((caddr_t)&fl.fl_nfh, sizeof (nfsv2fh_t));
			fl.fl_nfh.fh_generic.fh_fsid =
E 82
I 82
			bzero((caddr_t)nfhp, NFSX_V3FH);
			nfhp->fh_fsid =
E 82
				nvp->v_mount->mnt_stat.f_fsid;
D 82
			if (VFS_VPTOFH(nvp, &fl.fl_nfh.fh_generic.fh_fid)) {
E 82
I 82
			if (VFS_VPTOFH(nvp, &nfhp->fh_fid)) {
E 82
				vput(nvp);
				goto invalid;
			}
E 68
D 69
			(void) nqsrv_getlease(nvp, &duration2, NQL_READ, nfsd,
				nam, &cache2, &frev2, cred);
I 63
D 68
			bzero((caddr_t)&fl.fl_nfh, sizeof (nfsv2fh_t));
E 68
E 63
			fl.fl_duration = txdr_unsigned(duration2);
			fl.fl_cachable = txdr_unsigned(cache2);
D 67
			txdr_hyper(&frev2, &fl.fl_frev);
E 67
I 67
			txdr_hyper(&frev2, fl.fl_frev);
E 69
I 69
D 82
			if (duration2) {
				(void) nqsrv_getlease(nvp, &duration2, NQL_READ,
					nfsd, nam, &cache2, &frev2, cred);
				fl.fl_duration = txdr_unsigned(duration2);
				fl.fl_cachable = txdr_unsigned(cache2);
				txdr_hyper(&frev2, fl.fl_frev);
			} else
				fl.fl_duration = 0;
E 69
E 67
			if (VOP_GETATTR(nvp, vap, cred, nfsd->nd_procp)) {
E 82
I 82
			if (VOP_GETATTR(nvp, vap, cred, procp)) {
E 82
				vput(nvp);
				goto invalid;
			}
			vput(nvp);
D 69
			fp = &fl.fl_fattr;
E 69
I 69
D 82
			fp = (struct nfsv2_fattr *)&fl.fl_fattr;
E 69
			nfsm_srvfillattr;
			len += (4*NFSX_UNSIGNED + nlen + rem + NFSX_FH
D 69
				+ NFSX_FATTR);
E 69
I 69
				+ NFSX_NQFATTR);
E 69
E 45
D 19
			if (len > cnt)
E 19
I 19
			if (len > cnt) {
E 82
I 82

			/*
			 * If either the dircount or maxcount will be
			 * exceeded, get out now. Both of these lengths
			 * are calculated conservatively, including all
			 * XDR overheads.
			 */
			len += (7 * NFSX_UNSIGNED + nlen + rem + NFSX_V3FH +
				NFSX_V3POSTOPATTR);
			dirlen += (6 * NFSX_UNSIGNED + nlen + rem);
			if (len > cnt || dirlen > fullsiz) {
E 82
				eofflag = 0;
E 19
				break;
I 19
			}
I 82

E 82
E 19
D 3

E 3
I 3
D 48
	
E 3
			/* Build the directory record xdr from the direct entry */
E 48
I 48
			/*
			 * Build the directory record xdr from
			 * the dirent entry.
			 */
I 82
			fp = (struct nfs_fattr *)&fl.fl_fattr;
			nfsm_srvfillattr(vap, fp);
			fl.fl_fhsize = txdr_unsigned(NFSX_V3FH);
			fl.fl_fhok = nfs_true;
			fl.fl_postopok = nfs_true;
			fl.fl_off.nfsuquad[0] = 0;
			fl.fl_off.nfsuquad[1] = txdr_unsigned(*cookiep);

E 82
E 48
			nfsm_clget;
D 37
			*p = nfs_true;
E 37
I 37
			*tl = nfs_true;
E 37
			bp += NFSX_UNSIGNED;
I 45
D 82

			/*
			 * For readdir_and_lookup copy the stuff out.
			 */
			xfer = sizeof (struct flrep);
			cp = (caddr_t)&fl;
			while (xfer > 0) {
				nfsm_clget;
				if ((bp+xfer) > be)
					tsiz = be-bp;
				else
					tsiz = xfer;
				bcopy(cp, bp, tsiz);
				bp += tsiz;
				xfer -= tsiz;
				if (xfer > 0)
					cp += tsiz;
			}
E 82
E 45
			nfsm_clget;
I 82
			*tl = 0;
			bp += NFSX_UNSIGNED;
			nfsm_clget;
E 82
D 37
			*p = txdr_unsigned(dp->d_ino);
E 37
I 37
D 48
			*tl = txdr_unsigned(dp->d_ino);
E 48
I 48
			*tl = txdr_unsigned(dp->d_fileno);
E 48
E 37
			bp += NFSX_UNSIGNED;
			nfsm_clget;
D 37
			*p = txdr_unsigned(nlen);
E 37
I 37
			*tl = txdr_unsigned(nlen);
E 37
			bp += NFSX_UNSIGNED;
D 3

E 3
I 3
	
E 3
D 45
			/* And loop arround copying the name */
E 45
I 45
			/* And loop around copying the name */
E 45
			xfer = nlen;
			cp = dp->d_name;
			while (xfer > 0) {
				nfsm_clget;
D 82
				if ((bp+xfer) > be)
					tsiz = be-bp;
E 82
I 82
				if ((bp + xfer) > be)
					tsiz = be - bp;
E 82
				else
					tsiz = xfer;
				bcopy(cp, bp, tsiz);
				bp += tsiz;
				xfer -= tsiz;
				if (xfer > 0)
					cp += tsiz;
			}
			/* And null pad to a long boundary */
			for (i = 0; i < rem; i++)
				*bp++ = '\0';
D 82
			nfsm_clget;
E 82
D 3

E 3
I 3
	
E 3
D 82
			/* Finish off the record */
D 80
			toff += dp->d_reclen;
D 37
			*p = txdr_unsigned(toff);
E 37
I 37
			*tl = txdr_unsigned(toff);
E 80
I 80
			*tl = txdr_unsigned(*cookie);
E 80
E 37
			bp += NFSX_UNSIGNED;
E 82
I 82
			/*
			 * Now copy the flrep structure out.
			 */
			xfer = sizeof (struct flrep);
			cp = (caddr_t)&fl;
			while (xfer > 0) {
				nfsm_clget;
				if ((bp + xfer) > be)
					tsiz = be - bp;
				else
					tsiz = xfer;
				bcopy(cp, bp, tsiz);
				bp += tsiz;
				xfer -= tsiz;
				if (xfer > 0)
					cp += tsiz;
			}
E 82
D 80
		} else
E 80
I 80
		}
E 80
I 45
invalid:
E 45
D 80
			toff += dp->d_reclen;
E 80
		cpos += dp->d_reclen;
D 48
		dp = (struct direct *)cpos;
E 48
I 48
		dp = (struct dirent *)cpos;
I 80
D 82
		cookie++;
E 82
I 82
		cookiep++;
		ncookies--;
E 82
E 80
E 48
	}
I 45
	vrele(vp);
E 45
	nfsm_clget;
D 37
	*p = nfs_false;
E 37
I 37
	*tl = nfs_false;
E 37
	bp += NFSX_UNSIGNED;
	nfsm_clget;
D 15
	*p = nfs_false;
E 15
I 15
	if (eofflag)
D 37
		*p = nfs_true;
E 37
I 37
		*tl = nfs_true;
E 37
	else
D 37
		*p = nfs_false;
E 37
I 37
		*tl = nfs_false;
E 37
E 15
	bp += NFSX_UNSIGNED;
D 45
	if (bp < be)
		mp->m_len = bp-mtod(mp, caddr_t);
	mb->m_next = mp3;
E 45
I 45
	if (mp != mb) {
		if (bp < be)
			mp->m_len = bp - mtod(mp, caddr_t);
	} else
		mp->m_len += bp - bpos;
I 80
D 82
	FREE(cookiebuf, M_TEMP);
E 80
E 45
	FREE(rbuf, M_TEMP);
E 82
I 82
	FREE((caddr_t)cookies, M_TEMP);
	FREE((caddr_t)rbuf, M_TEMP);
E 82
	nfsm_srvdone;
}

/*
I 82
 * nfs commit service
 */
int
nfsrv_commit(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
{
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	struct vattr bfor, aft;
	struct vnode *vp;
	nfsfh_t nfh;
	fhandle_t *fhp;
	register u_long *tl;
	register long t1;
	caddr_t bpos;
	int error = 0, rdonly, for_ret = 1, aft_ret = 1, cnt, cache;
	char *cp2;
	struct mbuf *mb, *mb2, *mreq;
	u_quad_t frev, off;

#ifndef nolint
	cache = 0;
#endif
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
	nfsm_dissect(tl, u_long *, 3 * NFSX_UNSIGNED);

	/*
	 * XXX At this time VOP_FSYNC() does not accept offset and byte
	 * count parameters, so these arguments are useless (someday maybe).
	 */
	fxdr_hyper(tl, &off);
	tl += 2;
	cnt = fxdr_unsigned(int, *tl);
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
		nfsm_reply(2 * NFSX_UNSIGNED);
		nfsm_srvwcc_data(for_ret, &bfor, aft_ret, &aft);
		return (0);
	}
	for_ret = VOP_GETATTR(vp, &bfor, cred, procp);
	error = VOP_FSYNC(vp, cred, MNT_WAIT, procp);
	aft_ret = VOP_GETATTR(vp, &aft, cred, procp);
	vput(vp);
	nfsm_reply(NFSX_V3WCCDATA + NFSX_V3WRITEVERF);
	nfsm_srvwcc_data(for_ret, &bfor, aft_ret, &aft);
	if (!error) {
		nfsm_build(tl, u_long *, NFSX_V3WRITEVERF);
		*tl++ = txdr_unsigned(boottime.tv_sec);
		*tl = txdr_unsigned(boottime.tv_usec);
	} else
		return (0);
	nfsm_srvdone;
}

/*
E 82
 * nfs statfs service
 */
D 11
nfsrv_statfs(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_statfs(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_statfs(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf **mrq;
E 45
I 45
D 82
nfsrv_statfs(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
E 45
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
D 45
	u_long xid;
I 11
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_statfs(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
	register struct statfs *sf;
I 7
D 82
	register struct nfsv2_statfs *sfp;
E 82
I 82
	register struct nfs_statfs *sfp;
E 82
E 7
D 9
	nfsm_srvars;
E 9
I 9
D 37
	register u_long *p;
E 37
I 37
	register u_long *tl;
E 37
	register long t1;
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 69
	int error = 0, rdonly, cache;
E 69
I 69
D 82
	int error = 0, rdonly, cache, isnq;
E 82
I 82
	int error = 0, rdonly, cache, getret = 1;
	int v3 = (nfsd->nd_flag & ND_NFSV3);
E 82
E 69
E 45
	char *cp2;
D 11
	struct mbuf *mb, *mb2;
E 11
I 11
	struct mbuf *mb, *mb2, *mreq;
E 11
E 9
	struct vnode *vp;
D 82
	nfsv2fh_t nfh;
E 82
I 82
	struct vattr at;
	nfsfh_t nfh;
E 82
	fhandle_t *fhp;
	struct statfs statfs;
I 45
D 82
	u_quad_t frev;
E 82
I 82
	u_quad_t frev, tval;
E 82
E 45

I 82
#ifndef nolint
	cache = 0;
#endif
E 82
	fhp = &nfh.fh_generic;
I 69
D 82
	isnq = (nfsd->nd_nqlflag != NQL_NOVAL);
E 82
E 69
	nfsm_srvmtofh(fhp);
D 45
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred))
E 45
I 45
D 82
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
E 45
		nfsm_reply(0);
E 82
I 82
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
		nfsm_reply(NFSX_UNSIGNED);
		nfsm_srvpostop_attr(getret, &at);
		return (0);
	}
E 82
	sf = &statfs;
D 37
	error = VFS_STATFS(vp->v_mount, sf);
E 37
I 37
D 45
	error = VFS_STATFS(vp->v_mount, sf, p);
E 45
I 45
D 82
	error = VFS_STATFS(vp->v_mount, sf, nfsd->nd_procp);
E 82
I 82
	error = VFS_STATFS(vp->v_mount, sf, procp);
	getret = VOP_GETATTR(vp, &at, cred, procp);
E 82
E 45
E 37
	vput(vp);
D 69
	nfsm_reply(NFSX_STATFS);
D 7
	nfsm_build(p, u_long *, NFSX_STATFS);
D 3
	*p++ = txdr_unsigned(sf->f_bsize);
E 3
I 3
	*p++ = txdr_unsigned(NFS_MAXDATA);
E 3
	*p++ = txdr_unsigned(sf->f_fsize);
	*p++ = txdr_unsigned(sf->f_blocks);
	*p++ = txdr_unsigned(sf->f_bfree);
	*p = txdr_unsigned(sf->f_bavail);
E 7
I 7
	nfsm_build(sfp, struct nfsv2_statfs *, NFSX_STATFS);
E 69
I 69
D 82
	nfsm_reply(NFSX_STATFS(isnq));
	nfsm_build(sfp, struct nfsv2_statfs *, NFSX_STATFS(isnq));
E 69
D 27
	sfp->sf_tsize = txdr_unsigned(NFS_MAXDATA);
E 27
I 27
	sfp->sf_tsize = txdr_unsigned(NFS_MAXDGRAMDATA);
E 27
D 44
	sfp->sf_bsize = txdr_unsigned(sf->f_fsize);
E 44
I 44
	sfp->sf_bsize = txdr_unsigned(sf->f_bsize);
E 44
	sfp->sf_blocks = txdr_unsigned(sf->f_blocks);
	sfp->sf_bfree = txdr_unsigned(sf->f_bfree);
	sfp->sf_bavail = txdr_unsigned(sf->f_bavail);
I 69
	if (isnq) {
		sfp->sf_files = txdr_unsigned(sf->f_files);
		sfp->sf_ffree = txdr_unsigned(sf->f_ffree);
E 82
I 82
	nfsm_reply(NFSX_POSTOPATTR(v3) + NFSX_STATFS(v3));
	if (v3)
		nfsm_srvpostop_attr(getret, &at);
	if (error)
		return (0);
	nfsm_build(sfp, struct nfs_statfs *, NFSX_STATFS(v3));
	if (v3) {
		tval = (u_quad_t)sf->f_blocks;
		tval *= (u_quad_t)sf->f_bsize;
		txdr_hyper(&tval, &sfp->sf_tbytes);
		tval = (u_quad_t)sf->f_bfree;
		tval *= (u_quad_t)sf->f_bsize;
		txdr_hyper(&tval, &sfp->sf_fbytes);
		tval = (u_quad_t)sf->f_bavail;
		tval *= (u_quad_t)sf->f_bsize;
		txdr_hyper(&tval, &sfp->sf_abytes);
		sfp->sf_tfiles.nfsuquad[0] = 0;
		sfp->sf_tfiles.nfsuquad[1] = txdr_unsigned(sf->f_files);
		sfp->sf_ffiles.nfsuquad[0] = 0;
		sfp->sf_ffiles.nfsuquad[1] = txdr_unsigned(sf->f_ffree);
		sfp->sf_afiles.nfsuquad[0] = 0;
		sfp->sf_afiles.nfsuquad[1] = txdr_unsigned(sf->f_ffree);
		sfp->sf_invarsec = 0;
	} else {
		sfp->sf_tsize = txdr_unsigned(NFS_MAXDGRAMDATA);
		sfp->sf_bsize = txdr_unsigned(sf->f_bsize);
		sfp->sf_blocks = txdr_unsigned(sf->f_blocks);
		sfp->sf_bfree = txdr_unsigned(sf->f_bfree);
		sfp->sf_bavail = txdr_unsigned(sf->f_bavail);
E 82
	}
E 69
E 7
	nfsm_srvdone;
}

/*
I 82
 * nfs fsinfo service
 */
int
nfsrv_fsinfo(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
{
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	register u_long *tl;
	register struct nfsv3_fsinfo *sip;
	register long t1;
	caddr_t bpos;
	int error = 0, rdonly, cache, getret = 1, pref;
	char *cp2;
	struct mbuf *mb, *mb2, *mreq;
	struct vnode *vp;
	struct vattr at;
	nfsfh_t nfh;
	fhandle_t *fhp;
	u_quad_t frev;

#ifndef nolint
	cache = 0;
#endif
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
		nfsm_reply(NFSX_UNSIGNED);
		nfsm_srvpostop_attr(getret, &at);
		return (0);
	}
	getret = VOP_GETATTR(vp, &at, cred, procp);
	vput(vp);
	nfsm_reply(NFSX_V3POSTOPATTR + NFSX_V3FSINFO);
	nfsm_srvpostop_attr(getret, &at);
	nfsm_build(sip, struct nfsv3_fsinfo *, NFSX_V3FSINFO);

	/*
	 * XXX
	 * There should be file system VFS OP(s) to get this information.
	 * For now, assume ufs.
	 */
	if (slp->ns_so->so_type == SOCK_DGRAM)
		pref = NFS_MAXDGRAMDATA;
	else
		pref = NFS_MAXDATA;
	sip->fs_rtmax = txdr_unsigned(NFS_MAXDATA);
	sip->fs_rtpref = txdr_unsigned(pref);
	sip->fs_rtmult = txdr_unsigned(NFS_FABLKSIZE);
	sip->fs_wtmax = txdr_unsigned(NFS_MAXDATA);
	sip->fs_wtpref = txdr_unsigned(pref);
	sip->fs_wtmult = txdr_unsigned(NFS_FABLKSIZE);
	sip->fs_dtpref = txdr_unsigned(pref);
	sip->fs_maxfilesize.nfsuquad[0] = 0xffffffff;
	sip->fs_maxfilesize.nfsuquad[1] = 0xffffffff;
	sip->fs_timedelta.nfsv3_sec = 0;
	sip->fs_timedelta.nfsv3_nsec = txdr_unsigned(1);
	sip->fs_properties = txdr_unsigned(NFSV3FSINFO_LINK |
		NFSV3FSINFO_SYMLINK | NFSV3FSINFO_HOMOGENEOUS |
		NFSV3FSINFO_CANSETTIME);
	nfsm_srvdone;
}

/*
 * nfs pathconf service
 */
int
nfsrv_pathconf(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
{
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	register u_long *tl;
	register struct nfsv3_pathconf *pc;
	register long t1;
	caddr_t bpos;
	int error = 0, rdonly, cache, getret = 1, linkmax, namemax;
	int chownres, notrunc;
	char *cp2;
	struct mbuf *mb, *mb2, *mreq;
	struct vnode *vp;
	struct vattr at;
	nfsfh_t nfh;
	fhandle_t *fhp;
	u_quad_t frev;

#ifndef nolint
	cache = 0;
#endif
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
	if (error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam,
		 &rdonly, (nfsd->nd_flag & ND_KERBAUTH))) {
		nfsm_reply(NFSX_UNSIGNED);
		nfsm_srvpostop_attr(getret, &at);
		return (0);
	}
	error = VOP_PATHCONF(vp, _PC_LINK_MAX, &linkmax);
	if (!error)
		error = VOP_PATHCONF(vp, _PC_NAME_MAX, &namemax);
	if (!error)
		error = VOP_PATHCONF(vp, _PC_CHOWN_RESTRICTED, &chownres);
	if (!error)
		error = VOP_PATHCONF(vp, _PC_NO_TRUNC, &notrunc);
	getret = VOP_GETATTR(vp, &at, cred, procp);
	vput(vp);
	nfsm_reply(NFSX_V3POSTOPATTR + NFSX_V3PATHCONF);
	nfsm_srvpostop_attr(getret, &at);
	if (error)
		return (0);
	nfsm_build(pc, struct nfsv3_pathconf *, NFSX_V3PATHCONF);

	pc->pc_linkmax = txdr_unsigned(linkmax);
	pc->pc_namemax = txdr_unsigned(namemax);
	pc->pc_notrunc = txdr_unsigned(notrunc);
	pc->pc_chownrestricted = txdr_unsigned(chownres);

	/*
	 * These should probably be supported by VOP_PATHCONF(), but
	 * until msdosfs is exportable (why would you want to?), the
	 * Unix defaults should be ok.
	 */
	pc->pc_caseinsensitive = nfs_false;
	pc->pc_casepreserving = nfs_true;
	nfsm_srvdone;
}

/*
E 82
 * Null operation, used by clients to ping server
 */
I 9
/* ARGSUSED */
E 9
D 11
nfsrv_null(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_null(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_null(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf **mrq;
E 45
I 45
D 82
nfsrv_null(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
E 45
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
D 45
	u_long xid;
I 11
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_null(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
D 9
	nfsm_srvars;
E 9
I 9
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
D 82
	int error = VNOVAL, cache;
E 82
I 82
	int error = NFSERR_RETVOID, cache;
E 82
E 45
D 11
	struct mbuf *mb;
E 11
I 11
	struct mbuf *mb, *mreq;
I 45
	u_quad_t frev;
E 45
E 11
E 9

I 82
#ifndef nolint
	cache = 0;
#endif
E 82
D 45
	error = VNOVAL;
E 45
	nfsm_reply(0);
D 9
	nfsm_srvdone;
E 9
I 9
D 82
	return (error);
E 82
I 82
	return (0);
E 82
E 9
}

/*
 * No operation, used for obsolete procedures
 */
I 9
/* ARGSUSED */
E 9
D 11
nfsrv_noop(mrep, md, dpos, cred, xid, mrq)
E 11
I 11
D 37
nfsrv_noop(mrep, md, dpos, cred, xid, mrq, repstat)
E 37
I 37
D 45
nfsrv_noop(mrep, md, dpos, cred, xid, mrq, repstat, p)
E 37
E 11
	struct mbuf **mrq;
E 45
I 45
D 82
nfsrv_noop(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
E 45
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
D 45
	u_long xid;
I 11
	int *repstat;
I 37
	struct proc *p;
E 45
I 45
	struct mbuf *nam, **mrq;
E 82
I 82
int
nfsrv_noop(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 82
E 45
E 37
E 11
{
I 82
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 82
D 9
	nfsm_srvars;
E 9
I 9
	caddr_t bpos;
D 45
	int error = 0;
E 45
I 45
	int error, cache;
E 45
D 11
	struct mbuf *mb;
E 11
I 11
	struct mbuf *mb, *mreq;
I 45
	u_quad_t frev;
E 45
E 11
E 9

I 82
#ifndef nolint
	cache = 0;
#endif
E 82
D 45
	error = EPROCUNAVAIL;
E 45
I 45
	if (nfsd->nd_repstat)
		error = nfsd->nd_repstat;
	else
		error = EPROCUNAVAIL;
E 45
	nfsm_reply(0);
D 9
	nfsm_srvdone;
E 9
I 9
D 82
	return (error);
E 82
I 82
	return (0);
E 82
E 9
}
I 3

I 4
/*
 * Perform access checking for vnodes obtained from file handles that would
 * refer to files already opened by a Unix client. You cannot just use
 * vn_writechk() and VOP_ACCESS() for two reasons.
D 18
 * 1 - You must check for M_EXRDONLY as well as M_RDONLY for the write case
E 18
I 18
D 45
 * 1 - You must check for MNT_EXRDONLY as well as MNT_RDONLY for the write case
E 45
I 45
 * 1 - You must check for exported rdonly as well as MNT_RDONLY for the write case
E 45
E 18
 * 2 - The owner is to be given access irrespective of mode bits so that
 *     processes that chmod after opening a file don't break. I don't like
 *     this because it opens a security hole, but since the nfs server opens
 *     a security hole the size of a barn door anyhow, what the heck.
 */
I 82
int
E 82
D 37
nfsrv_access(vp, flags, cred)
E 37
I 37
D 45
nfsrv_access(vp, flags, cred, p)
E 45
I 45
nfsrv_access(vp, flags, cred, rdonly, p)
E 45
E 37
	register struct vnode *vp;
	int flags;
	register struct ucred *cred;
I 45
	int rdonly;
E 45
I 37
	struct proc *p;
E 37
{
I 61
D 64
	USES_VOP_ACCESS;
	USES_VOP_GETATTR;
E 64
E 61
	struct vattr vattr;
	int error;
	if (flags & VWRITE) {
D 18
		/* Just vn_writechk() changed to check M_EXRDONLY */
E 18
I 18
D 45
		/* Just vn_writechk() changed to check MNT_EXRDONLY */
E 45
I 45
		/* Just vn_writechk() changed to check rdonly */
E 45
E 18
		/*
		 * Disallow write attempts on read-only file systems;
		 * unless the file is a socket or a block or character
		 * device resident on the file system.
		 */
D 18
		if ((vp->v_mount->m_flag & (M_RDONLY | M_EXRDONLY)) &&
E 18
I 18
D 28
		if ((vp->v_mount->mnt_flag & (MNT_RDONLY | MNT_EXRDONLY)) &&
E 18
			vp->v_type != VCHR &&
			vp->v_type != VBLK &&
			vp->v_type != VSOCK)
E 28
I 28
D 45
		if (vp->v_mount->mnt_flag & (MNT_RDONLY | MNT_EXRDONLY)) {
E 45
I 45
		if (rdonly || (vp->v_mount->mnt_flag & MNT_RDONLY)) {
E 45
			switch (vp->v_type) {
			case VREG: case VDIR: case VLNK:
E 28
				return (EROFS);
I 28
			}
		}
E 28
		/*
		 * If there's shared text associated with
		 * the inode, try to free it up once.  If
		 * we fail, we can't allow writing.
		 */
I 33
D 38
#ifdef NVM
E 38
E 33
D 30
		if (vp->v_flag & VTEXT)
			xrele(vp);
		if (vp->v_flag & VTEXT)
E 30
I 30
		if ((vp->v_flag & VTEXT) && !vnode_pager_uncache(vp))
E 30
			return (ETXTBSY);
I 33
D 38
#else
		if (vp->v_flag & VTEXT)
			xrele(vp);
		if (vp->v_flag & VTEXT)
			return (ETXTBSY);
#endif
E 38
E 33
D 28
		if (error = VOP_GETATTR(vp, &vattr, cred))
			return (error);
		if (cred->cr_uid == vattr.va_uid)
			return (0);
	} else {
		if (error = VOP_GETATTR(vp, &vattr, cred))
			return (error);
		if (cred->cr_uid == vattr.va_uid)
			return (0);
E 28
	}
D 28
	return (VOP_ACCESS(vp, flags, cred));
E 28
I 28
D 37
	if (error = VOP_GETATTR(vp, &vattr, cred))
E 37
I 37
	if (error = VOP_GETATTR(vp, &vattr, cred, p))
E 37
		return (error);
D 37
	if ((error = VOP_ACCESS(vp, flags, cred)) &&
E 37
I 37
	if ((error = VOP_ACCESS(vp, flags, cred, p)) &&
E 37
	    cred->cr_uid != vattr.va_uid)
		return (error);
	return (0);
E 28
}
E 4
E 3
E 1
