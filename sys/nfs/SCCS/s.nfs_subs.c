h61946
s 00004/00003/01821
d D 8.8 95/05/22 23:01:25 mckusick 89 88
c simpler checkalias protocol
e
s 00002/00001/01822
d D 8.7 95/05/14 00:32:58 mckusick 88 87
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00873/00150/00950
d D 8.6 95/03/30 11:26:25 mckusick 87 85
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00001/00001/01099
d R 8.6 95/02/22 20:14:38 mckusick 86 85
c vgone => VOP_REVOKE
e
s 00018/00024/01082
d D 8.5 94/08/18 23:33:36 mckusick 85 84
c conversion to queue.h list manipulation (from mycroft)
e
s 00002/00000/01104
d D 8.4 94/07/25 00:09:45 mckusick 84 83
c set group size in cred (from mycroft via macklem)
e
s 00000/00001/01104
d D 8.3 94/01/04 22:07:02 bostic 83 82
c lint
e
s 00001/00002/01104
d D 8.2 93/12/30 16:19:13 mckusick 82 81
c new queue structure
e
s 00002/00002/01104
d D 8.1 93/06/16 17:30:15 bostic 81 80
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00016/01099
d D 7.71 93/06/16 17:15:45 mckusick 80 78
c fix for trashed TCP/IP connections from Macklem
e
s 00002/00002/01113
d R 8.1 93/06/10 23:39:11 bostic 79 78
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/01113
d D 7.70 93/03/30 15:32:55 mckusick 78 77
c eliminate flags and generation number in times hack
e
s 00000/00005/01116
d D 7.69 93/03/08 16:40:43 mckusick 77 76
c remove the 8-bit restriction in namei
e
s 00057/00022/01064
d D 7.68 93/02/02 15:18:00 mckusick 76 75
c update for 4.4BSD from Rick Macklem
e
s 00002/00002/01084
d D 7.67 92/11/01 23:16:37 mckusick 75 74
c fix from Jeff Forys for tracking changing NFS file sizes
e
s 00002/00000/01084
d D 7.66 92/10/08 00:26:02 mckusick 74 73
c use new queue routines to manage list of I/O requests
e
s 00009/00016/01075
d D 7.65 92/09/30 16:04:37 mckusick 73 72
c September update from Rick Macklem to add accept protocol to NQMFS
e
s 00000/00020/01091
d D 7.64 92/09/21 15:30:24 mckusick 72 71
c get rid of unised function
e
s 00043/00026/01068
d D 7.63 92/09/16 18:26:06 mckusick 71 70
c update from Rick Macklem
e
s 00002/00001/01092
d D 7.62 92/07/25 20:51:45 mckusick 70 69
c spec_vnodeops_p now declared in specdev.h
e
s 00011/00010/01082
d D 7.61 92/07/22 15:24:55 mckusick 69 68
c update to current hashing techniques
e
s 00001/00001/01091
d D 7.60 92/07/12 17:16:44 pendry 68 67
c MIN -> min, MAX -> max
e
s 00074/00000/01018
d D 7.59 92/07/12 11:17:07 mckusick 67 66
c bring back vfs_addr.c (hopefully temporarily until we can use radix tree)
e
s 00010/00061/01008
d D 7.58 92/07/06 18:48:52 mckusick 66 65
c export validation is now done by the underlying filesystem
e
s 00000/00001/01069
d D 7.57 92/07/03 01:54:03 mckusick 65 64
c delete USES
e
s 00004/00010/01066
d D 7.56 92/07/02 19:54:27 mckusick 64 63
c clean up includes; nfs_netaddr_match goes to vfs_addr.c
e
s 00002/00005/01074
d D 7.55 92/06/25 13:08:23 mckusick 63 62
c drop NOQUAD; FHTOVP drops setgen bogosity
e
s 00024/00013/01055
d D 7.54 92/06/19 19:29:37 mckusick 62 61
c timeval => timespec in vattr and dinode
e
s 00012/00000/01056
d D 7.53 92/05/20 10:55:43 mckusick 61 60
c update for spec and fifo times for NFS (from Macklem)
e
s 00007/00006/01049
d D 7.52 92/05/14 17:39:11 heideman 60 51
c vnode interface conversion
e
s 00007/00006/01049
d R 7.52 92/05/14 15:58:11 heideman 59 51
c vnode interface conversion
e
s 00007/00006/01049
d R 7.52 92/05/14 14:57:43 heideman 58 51
c vnode interface conversion
e
s 00003/00002/01053
d R 7.52 92/05/14 13:04:41 heideman 57 51
c vnode interface conversion
e
s 00003/00002/01053
d R 7.52 92/05/14 12:01:34 heideman 56 51
c vnode interface conversion
e
s 00003/00002/01053
d R 7.52 92/05/14 11:25:02 heideman 55 51
c vnode interface conversion
e
s 00003/00002/01053
d R 7.52 92/05/13 23:20:44 heideman 54 51
c vnode interface conversion
e
s 00003/00002/01053
d R 7.52 92/05/13 19:04:08 heideman 53 51
c vnode interface conversion
e
s 00003/00002/01053
d R 7.52 92/05/13 18:36:24 heideman 52 51
c vnode interface conversion
e
s 00002/00001/01053
d D 7.51 92/05/13 18:09:08 heideman 51 50
c minor syntax change before vnode interface conversion
e
s 00001/00001/01053
d D 7.50 92/05/06 11:08:55 mckusick 50 49
c Donn Seeley's to improve interoperability (via Macklem)
e
s 00028/00026/01026
d D 7.49 92/05/04 16:38:12 mckusick 49 48
c lint; clean up include directives
e
s 00001/00000/01051
d D 7.48 92/03/16 15:27:44 mckusick 48 47
c fix from Rick Macklem for multiple free's of NFSD structures
e
s 00020/00018/01031
d D 7.47 92/02/04 00:24:13 heideman 47 46
c new organization for nameidata
e
s 00001/00001/01048
d D 7.46 92/01/22 09:39:30 heideman 46 45
c lookup converted to new form
e
s 00328/00397/00721
d D 7.45 92/01/14 12:41:10 mckusick 45 44
c update from Rick Macklem (including leases)
e
s 00004/00002/01114
d D 7.44 91/12/19 13:03:20 mckusick 44 43
c va_rsv only exist when _NOQUAD support
e
s 00014/00014/01102
d D 7.43 91/12/16 17:24:14 mckusick 43 42
c new approach for handling aliases (based on local node allocation)
e
s 00002/00002/01114
d D 7.42 91/11/01 16:49:05 bostic 42 41
c ufs moved down one level
e
s 00075/00053/01041
d D 7.41 91/05/15 20:20:07 mckusick 41 40
c update nfs_namei to use lookup instead of namei
e
s 00000/00004/01094
d D 7.40 91/05/08 14:10:09 mckusick 40 39
c get rid of ifdef NVM
e
s 00048/00047/01050
d D 7.39 91/04/16 00:36:24 mckusick 39 38
c use u_long tl in place of u_long p; 
c hack to fix call to namei (must be fixed!)
e
s 00002/00002/01095
d D 7.38 91/03/19 11:24:45 karels 38 37
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; consolidate *nullops()
e
s 00007/00001/01090
d D 7.37 91/03/04 22:52:09 mckusick 37 36
c misc fixes plus diskless support from Rick Macklem
e
s 00009/00017/01082
d D 7.36 91/02/21 23:02:02 mckusick 36 35
c fixes for multiple calls to namei (for rename in NFS)
e
s 00009/00003/01090
d D 7.35 91/01/10 23:54:15 mckusick 35 34
c ugly hack to get correct cdir just got worse
e
s 00004/00000/01089
d D 7.34 91/01/10 18:27:29 mckusick 34 33
c conditionalize neweh VM
e
s 00006/00003/01083
d D 7.33 90/12/05 16:03:44 mckusick 33 32
c update for new VM
e
s 00014/00009/01072
d D 7.32 90/10/06 15:43:09 mckusick 32 31
c more bug fixes for compression from Macklem
e
s 00003/00003/01078
d D 7.31 90/10/02 10:46:10 mckusick 31 30
c fixes for compressed NFS (from Macklem)
e
s 00201/00000/00880
d D 7.30 90/10/01 14:16:36 mckusick 30 29
c add Rick Macklem's compressed NFS
e
s 00007/00006/00873
d D 7.29 90/07/26 15:24:50 mckusick 29 28
c do not duplicate first member of the group (from Macklem)
e
s 00001/00011/00878
d D 7.28 90/06/28 21:52:44 bostic 28 27
c new copyright notice
e
s 00007/00008/00882
d D 7.27 90/06/21 11:19:00 mckusick 27 26
c "update from Rick Macklem"
e
s 00001/00001/00889
d D 7.26 90/06/05 10:25:10 mckusick 26 25
c drop Sun compatibility on choosing device numbers
e
s 00050/00049/00840
d D 7.25 90/05/18 14:58:44 mckusick 25 24
c "nfs_mknod update from Rick Macklem"
e
s 00064/00132/00825
d D 7.24 90/05/14 11:44:36 mckusick 24 23
c "update from Rick Macklem adding TCP support to NFS"
e
s 00001/00001/00956
d D 7.23 90/05/10 16:08:56 mckusick 23 22
c set 0x8000 bit on fsid when doing stat to be compatible with Sun
e
s 00012/00010/00945
d D 7.22 90/05/04 20:52:36 mckusick 22 21
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00002/00002/00953
d D 7.21 90/03/27 15:37:12 mckusick 21 20
c va_size and va_bytes become quads
e
s 00001/00001/00954
d D 7.20 90/03/06 23:33:54 mckusick 20 19
c m_fsid is now m_stat.f_fsid
e
s 00009/00001/00946
d D 7.19 90/03/05 19:16:43 mckusick 19 18
c add support for fifo's; minor bug fix
e
s 00000/00001/00947
d D 7.18 90/02/17 15:23:59 mckusick 18 17
c get rid of bogus `strings.h' include file
e
s 00005/00011/00943
d D 7.17 90/02/17 10:33:01 mckusick 17 16
c get rid of unneeded header files
e
s 00002/00001/00952
d D 7.16 90/01/15 18:28:14 mckusick 16 15
c do all locking through nfs_lock explicitly
e
s 00008/00005/00945
d D 7.15 89/12/20 18:12:30 mckusick 15 14
c "December update from Rick Macklem"
e
s 00001/00002/00949
d D 7.14 89/11/25 15:24:37 mckusick 14 13
c checkalias now sets rdev
e
s 00002/00000/00949
d D 7.13 89/11/22 21:33:37 mckusick 13 12
c increment offset when simulating uiomove
e
s 00010/00012/00939
d D 7.12 89/11/03 15:30:26 mckusick 12 11
c lint
e
s 00006/00005/00945
d D 7.11 89/10/31 16:00:19 mckusick 11 10
c nfs_loadattrcache must update an aliased vnode
e
s 00047/00024/00903
d D 7.10 89/10/29 23:54:14 mckusick 10 9
c special device aliasing is now handled at the vnode level
e
s 00021/00001/00906
d D 7.9 89/10/21 11:33:02 mckusick 9 8
c "bug fixes and cleanups from Rick Macklem"
e
s 00010/00001/00897
d D 7.8 89/10/19 22:34:59 mckusick 8 7
c "update from Rick Macklem"
e
s 00029/00019/00869
d D 7.7 89/08/30 20:30:04 macklem 7 6
c first buffer cache implementation; name cache usage; code cleanups
e
s 00009/00002/00879
d D 7.6 89/08/22 22:15:30 mckusick 6 5
c deal with botch in NFS protocol for older systems
e
s 00001/00001/00880
d D 7.5 89/08/16 18:43:01 mckusick 5 4
c return vap_bytes in bytes
e
s 00003/00001/00878
d D 7.4 89/08/10 15:31:48 mckusick 4 3
c return flags and generation number; post error (from Rick Macklem)
e
s 00031/00115/00848
d D 7.3 89/07/06 17:42:32 mckusick 3 2
c update of July 5th from Rick Macklem
e
s 00012/00004/00951
d D 7.2 89/07/05 11:45:06 mckusick 2 1
c eliminate vn_access; do checks directly
e
s 00955/00000/00000
d D 7.1 89/07/05 11:43:48 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 81
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 81
I 81
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 81
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
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

I 87

E 87
/*
 * These functions support the macros and help fiddle mbuf chains for
 * the nfs op functions. They do things like create the rpc header and
 * copy data between mbuf chains and uio lists.
 */
D 17
#include "strings.h"
E 17
D 10
#include "types.h"
E 10
D 49
#include "param.h"
I 10
D 17
#include "systm.h"
E 17
E 10
I 8
D 38
#include "user.h"
E 38
#include "proc.h"
I 35
#include "filedesc.h"
E 35
E 8
D 17
#include "mount.h"
D 3
#include "dir.h"
E 3
I 3
#include "../ufs/dir.h"
E 3
#include "time.h"
#include "errno.h"
E 17
I 17
#include "systm.h"
E 17
#include "kernel.h"
D 17
#include "malloc.h"
#include "mbuf.h"
E 17
I 17
#include "mount.h"
E 17
#include "file.h"
#include "vnode.h"
I 39
#include "namei.h"
E 39
D 17
#include "uio.h"
#include "namei.h"
#include "ucred.h"
E 17
I 17
#include "mbuf.h"
D 38
#include "errno.h"
E 38
D 18
#include "strings.h"
E 18
E 17
I 7
#include "map.h"
I 45
#include "socket.h"
E 49
I 49
#include <sys/param.h>
#include <sys/proc.h>
D 64
#include <sys/filedesc.h>
E 64
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/mount.h>
D 64
#include <sys/file.h>
E 64
#include <sys/vnode.h>
#include <sys/namei.h>
#include <sys/mbuf.h>
D 64
#include <sys/map.h>
E 64
#include <sys/socket.h>
I 63
#include <sys/stat.h>
I 87
#include <sys/malloc.h>
#ifdef VFS_LKM
#include <sys/sysent.h>
#include <sys/syscall.h>
#endif
E 87
E 63
E 49
E 45
I 38

I 87
#include <vm/vm.h>

E 87
E 38
I 37
D 42
#include "../ufs/quota.h"
#include "../ufs/inode.h"
E 42
I 42
D 49
#include "ufs/ufs/quota.h"
#include "ufs/ufs/inode.h"
I 45
#include "ufs/ufs/ufsmount.h"
E 49
I 49
D 64
#include <vm/vm.h>
E 64
I 64
D 66
#include <ufs/ufs/quota.h>		/* XXX for nfsrv_fhtovp */
#include <ufs/ufs/ufsmount.h>		/* XXX for nfsrv_fhtovp */
E 64
E 49
E 45
E 42
I 38

E 66
E 38
E 37
E 7
D 49
#include "rpcv2.h"
#include "nfsv2.h"
D 43
#include "nfsnode.h"
E 43
D 45
#include "nfs.h"
E 45
I 43
#include "nfsnode.h"
E 43
I 7
D 45
#include "nfsiom.h"
E 45
I 45
#include "nfs.h"
E 45
E 7
#include "xdr_subs.h"
#include "nfsm_subs.h"
I 30
D 45
#include "nfscompress.h"
E 45
I 45
#include "nfsmount.h"
#include "nqnfs.h"
#include "nfsrtt.h"
E 49
I 49
D 64
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufsmount.h>
E 49
E 45
E 30

E 64
I 49
#include <nfs/rpcv2.h>
D 87
#include <nfs/nfsv2.h>
E 87
I 87
#include <nfs/nfsproto.h>
E 87
#include <nfs/nfsnode.h>
#include <nfs/nfs.h>
#include <nfs/xdr_subs.h>
#include <nfs/nfsm_subs.h>
#include <nfs/nfsmount.h>
#include <nfs/nqnfs.h>
#include <nfs/nfsrtt.h>

I 70
#include <miscfs/specfs/specdev.h>

E 70
I 67
#include <netinet/in.h>
#ifdef ISO
#include <netiso/iso.h>
#endif

E 67
E 49
D 87
#define TRUE	1
#define	FALSE	0

E 87
/*
 * Data items converted to xdr at startup, since they are constant
 * This is kinda hokey, but may save a little time doing byte swaps
 */
D 87
u_long nfs_procids[NFS_NPROCS];
E 87
u_long nfs_xdrneg1;
D 45
u_long rpc_call, rpc_vers, rpc_reply, rpc_msgdenied,
	rpc_mismatch, rpc_auth_unix, rpc_msgaccepted;
E 45
I 45
u_long rpc_call, rpc_vers, rpc_reply, rpc_msgdenied, rpc_autherr,
D 87
	rpc_mismatch, rpc_auth_unix, rpc_msgaccepted, rpc_rejectedcred,
E 87
I 87
	rpc_mismatch, rpc_auth_unix, rpc_msgaccepted,
E 87
	rpc_auth_kerb;
E 45
D 87
u_long nfs_vers, nfs_prog, nfs_true, nfs_false;
E 87
I 87
u_long nfs_prog, nqnfs_prog, nfs_true, nfs_false;
E 87
I 45

E 45
/* And other global data */
D 45
static u_long *rpc_uidp = (u_long *)0;
static u_long nfs_xid = 1;
static char *rpc_unixauth;
extern long hostid;
E 45
I 45
static u_long nfs_xid = 0;
E 45
D 25
extern enum vtype v_type[NFLNK+1];
E 25
I 25
D 87
enum vtype ntov_type[7] = { VNON, VREG, VDIR, VBLK, VCHR, VLNK, VNON };
E 87
I 87
enum vtype nv2tov_type[8] = { VNON, VREG, VDIR, VBLK, VCHR, VLNK, VNON, VNON };
enum vtype nv3tov_type[8]={ VNON, VREG, VDIR, VBLK, VCHR, VLNK, VSOCK, VFIFO };
int nfs_mount_type;
int nfs_ticks;

/*
 * Mapping of old NFS Version 2 RPC numbers to generic numbers.
 */
int nfsv3_procid[NFS_NPROCS] = {
	NFSPROC_NULL,
	NFSPROC_GETATTR,
	NFSPROC_SETATTR,
	NFSPROC_NOOP,
	NFSPROC_LOOKUP,
	NFSPROC_READLINK,
	NFSPROC_READ,
	NFSPROC_NOOP,
	NFSPROC_WRITE,
	NFSPROC_CREATE,
	NFSPROC_REMOVE,
	NFSPROC_RENAME,
	NFSPROC_LINK,
	NFSPROC_SYMLINK,
	NFSPROC_MKDIR,
	NFSPROC_RMDIR,
	NFSPROC_READDIR,
	NFSPROC_FSSTAT,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP,
	NFSPROC_NOOP
};

/*
 * and the reverse mapping from generic to Version 2 procedure numbers
 */
int nfsv2_procid[NFS_NPROCS] = {
	NFSV2PROC_NULL,
	NFSV2PROC_GETATTR,
	NFSV2PROC_SETATTR,
	NFSV2PROC_LOOKUP,
	NFSV2PROC_NOOP,
	NFSV2PROC_READLINK,
	NFSV2PROC_READ,
	NFSV2PROC_WRITE,
	NFSV2PROC_CREATE,
	NFSV2PROC_MKDIR,
	NFSV2PROC_SYMLINK,
	NFSV2PROC_CREATE,
	NFSV2PROC_REMOVE,
	NFSV2PROC_RMDIR,
	NFSV2PROC_RENAME,
	NFSV2PROC_LINK,
	NFSV2PROC_READDIR,
	NFSV2PROC_NOOP,
	NFSV2PROC_STATFS,
	NFSV2PROC_NOOP,
	NFSV2PROC_NOOP,
	NFSV2PROC_NOOP,
	NFSV2PROC_NOOP,
	NFSV2PROC_NOOP,
	NFSV2PROC_NOOP,
	NFSV2PROC_NOOP,
};

/*
 * Maps errno values to nfs error numbers.
 * Use NFSERR_IO as the catch all for ones not specifically defined in
 * RFC 1094.
 */
static u_char nfsrv_v2errmap[ELAST] = {
  NFSERR_PERM,	NFSERR_NOENT,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,
  NFSERR_NXIO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,
  NFSERR_IO,	NFSERR_IO,	NFSERR_ACCES,	NFSERR_IO,	NFSERR_IO,
  NFSERR_IO,	NFSERR_EXIST,	NFSERR_IO,	NFSERR_NODEV,	NFSERR_NOTDIR,
  NFSERR_ISDIR,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,
  NFSERR_IO,	NFSERR_FBIG,	NFSERR_NOSPC,	NFSERR_IO,	NFSERR_ROFS,
  NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,
  NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,
  NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,
  NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,
  NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,
  NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,
  NFSERR_IO,	NFSERR_IO,	NFSERR_NAMETOL,	NFSERR_IO,	NFSERR_IO,
  NFSERR_NOTEMPTY, NFSERR_IO,	NFSERR_IO,	NFSERR_DQUOT,	NFSERR_STALE,
  NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,
  NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,	NFSERR_IO,
  NFSERR_IO,
};

/*
 * Maps errno values to nfs error numbers.
 * Although it is not obvious whether or not NFS clients really care if
 * a returned error value is in the specified list for the procedure, the
 * safest thing to do is filter them appropriately. For Version 2, the
 * X/Open XNFS document is the only specification that defines error values
 * for each RPC (The RFC simply lists all possible error values for all RPCs),
 * so I have decided to not do this for Version 2.
 * The first entry is the default error return and the rest are the valid
 * errors for that RPC in increasing numeric order.
 */
static short nfsv3err_null[] = {
	0,
	0,
};

static short nfsv3err_getattr[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_setattr[] = {
	NFSERR_IO,
	NFSERR_PERM,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_INVAL,
	NFSERR_NOSPC,
	NFSERR_ROFS,
	NFSERR_DQUOT,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_NOT_SYNC,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_lookup[] = {
	NFSERR_IO,
	NFSERR_NOENT,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_NOTDIR,
	NFSERR_NAMETOL,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_access[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_readlink[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_INVAL,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_NOTSUPP,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_read[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_NXIO,
	NFSERR_ACCES,
	NFSERR_INVAL,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_write[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_INVAL,
	NFSERR_FBIG,
	NFSERR_NOSPC,
	NFSERR_ROFS,
	NFSERR_DQUOT,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_create[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_EXIST,
	NFSERR_NOTDIR,
	NFSERR_NOSPC,
	NFSERR_ROFS,
	NFSERR_NAMETOL,
	NFSERR_DQUOT,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_NOTSUPP,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_mkdir[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_EXIST,
	NFSERR_NOTDIR,
	NFSERR_NOSPC,
	NFSERR_ROFS,
	NFSERR_NAMETOL,
	NFSERR_DQUOT,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_NOTSUPP,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_symlink[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_EXIST,
	NFSERR_NOTDIR,
	NFSERR_NOSPC,
	NFSERR_ROFS,
	NFSERR_NAMETOL,
	NFSERR_DQUOT,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_NOTSUPP,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_mknod[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_EXIST,
	NFSERR_NOTDIR,
	NFSERR_NOSPC,
	NFSERR_ROFS,
	NFSERR_NAMETOL,
	NFSERR_DQUOT,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_NOTSUPP,
	NFSERR_SERVERFAULT,
	NFSERR_BADTYPE,
	0,
};

static short nfsv3err_remove[] = {
	NFSERR_IO,
	NFSERR_NOENT,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_NOTDIR,
	NFSERR_ROFS,
	NFSERR_NAMETOL,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_rmdir[] = {
	NFSERR_IO,
	NFSERR_NOENT,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_EXIST,
	NFSERR_NOTDIR,
	NFSERR_INVAL,
	NFSERR_ROFS,
	NFSERR_NAMETOL,
	NFSERR_NOTEMPTY,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_NOTSUPP,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_rename[] = {
	NFSERR_IO,
	NFSERR_NOENT,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_EXIST,
	NFSERR_XDEV,
	NFSERR_NOTDIR,
	NFSERR_ISDIR,
	NFSERR_INVAL,
	NFSERR_NOSPC,
	NFSERR_ROFS,
	NFSERR_MLINK,
	NFSERR_NAMETOL,
	NFSERR_NOTEMPTY,
	NFSERR_DQUOT,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_NOTSUPP,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_link[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_EXIST,
	NFSERR_XDEV,
	NFSERR_NOTDIR,
	NFSERR_INVAL,
	NFSERR_NOSPC,
	NFSERR_ROFS,
	NFSERR_MLINK,
	NFSERR_NAMETOL,
	NFSERR_DQUOT,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_NOTSUPP,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_readdir[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_NOTDIR,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_BAD_COOKIE,
	NFSERR_TOOSMALL,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_readdirplus[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_ACCES,
	NFSERR_NOTDIR,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_BAD_COOKIE,
	NFSERR_NOTSUPP,
	NFSERR_TOOSMALL,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_fsstat[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_fsinfo[] = {
	NFSERR_STALE,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_pathconf[] = {
	NFSERR_STALE,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_SERVERFAULT,
	0,
};

static short nfsv3err_commit[] = {
	NFSERR_IO,
	NFSERR_IO,
	NFSERR_STALE,
	NFSERR_BADHANDLE,
	NFSERR_SERVERFAULT,
	0,
};

static short *nfsrv_v3errmap[] = {
	nfsv3err_null,
	nfsv3err_getattr,
	nfsv3err_setattr,
	nfsv3err_lookup,
	nfsv3err_access,
	nfsv3err_readlink,
	nfsv3err_read,
	nfsv3err_write,
	nfsv3err_create,
	nfsv3err_mkdir,
	nfsv3err_symlink,
	nfsv3err_mknod,
	nfsv3err_remove,
	nfsv3err_rmdir,
	nfsv3err_rename,
	nfsv3err_link,
	nfsv3err_readdir,
	nfsv3err_readdirplus,
	nfsv3err_fsstat,
	nfsv3err_fsinfo,
	nfsv3err_pathconf,
	nfsv3err_commit,
};

E 87
E 25
I 8
D 24
extern struct proc *nfs_iodwant[MAX_ASYNCDAEMON];
E 24
I 24
extern struct proc *nfs_iodwant[NFS_MAXASYNCDAEMON];
I 74
D 82
extern struct queue_entry nfs_bufq;
E 82
E 74
E 24
E 8
I 7
D 45
extern struct map nfsmap[NFS_MSIZ];
E 45
I 24
D 85
extern struct nfsreq nfsreqh;
E 85
I 45
D 87
extern int nqnfs_piggy[NFS_NPROCS];
E 87
extern struct nfsrtt nfsrtt;
D 69
extern union nqsrvthead nqthead;
extern union nqsrvthead nqfhead[NQLCHSZ];
E 69
extern time_t nqnfsstarttime;
D 87
extern u_long nqnfs_prog, nqnfs_vers;
E 87
extern int nqsrv_clockskew;
extern int nqsrv_writeslack;
extern int nqsrv_maxlease;
I 87
extern struct nfsstats nfsstats;
extern int nqnfs_piggy[NFS_NPROCS];
extern nfstype nfsv2_type[9];
extern nfstype nfsv3_type[9];
extern struct nfsnodehashhead *nfsnodehashtbl;
extern u_long nfsnodehash;
E 87
E 45
E 24
E 7

I 87
#ifdef VFS_LKM
struct getfh_args;
extern int getfh(struct proc *, struct getfh_args *, int *);
struct nfssvc_args;
extern int nfssvc(struct proc *, struct nfssvc_args *, int *);
#endif

E 87
I 85
LIST_HEAD(nfsnodehashhead, nfsnode);
D 87
extern struct nfsnodehashhead *nfs_hash __P((nfsv2fh_t *));
E 87

E 85
D 45
/* Function ret types */
static char *nfs_unixauth();

E 45
/*
I 6
D 45
 * Maximum number of groups passed through to NFS server.
I 24
 * According to RFC1057 it should be 16.
E 24
 * For release 3.X systems, the maximum value is 8.
D 29
 * For release 4.X systems, the maximum value is 10.
E 29
I 29
 * For some other servers, the maximum value is 10.
E 29
 */
int numgrps = 8;

/*
E 45
E 6
 * Create the header for an rpc request packet
D 45
 * The function nfs_unixauth() creates a unix style authorization string
 * and returns a ptr to it.
E 45
 * The hsiz is the size of the rest of the nfs request header.
 * (just used to decide if a cluster is a good idea)
D 12
 * nb: Note that the prog, vers and proc args are already in xdr byte order
E 12
I 12
D 45
 * nb: Note that the prog, vers and procid args are already in xdr byte order
E 45
E 12
 */
D 12
struct mbuf *nfsm_reqh(prog, vers, proc, cred, hsiz, bpos, mb, retxid)
E 12
I 12
D 45
struct mbuf *nfsm_reqh(prog, vers, procid, cred, hsiz, bpos, mb, retxid)
E 12
	u_long prog;
	u_long vers;
E 45
I 45
struct mbuf *
nfsm_reqh(vp, procid, hsiz, bposp)
	struct vnode *vp;
E 45
D 12
	u_long proc;
E 12
I 12
	u_long procid;
E 12
D 45
	struct ucred *cred;
E 45
	int hsiz;
D 45
	caddr_t *bpos;
	struct mbuf **mb;
	u_long *retxid;
E 45
I 45
	caddr_t *bposp;
E 45
{
D 45
	register struct mbuf *mreq, *m;
E 45
I 45
	register struct mbuf *mb;
E 45
D 39
	register u_long *p;
E 39
I 39
	register u_long *tl;
E 39
D 45
	struct mbuf *m1;
	char *ap;
	int asiz, siz;
E 45
I 45
	register caddr_t bpos;
	struct mbuf *mb2;
	struct nfsmount *nmp;
	int nqflag;
E 45

D 45
	NFSMGETHDR(mreq);
D 6
	asiz = (((cred->cr_ngroups > 10) ? 10 : cred->cr_ngroups)<<2);
E 6
I 6
D 29
	asiz = (((cred->cr_ngroups > numgrps) ? numgrps : cred->cr_ngroups)<<2);
E 29
I 29
	asiz = ((((cred->cr_ngroups - 1) > numgrps) ? numgrps :
		  (cred->cr_ngroups - 1)) << 2);
E 29
E 6
I 3
#ifdef FILLINHOST
E 3
	asiz += nfsm_rndup(hostnamelen)+(9*NFSX_UNSIGNED);
I 3
#else
	asiz += 9*NFSX_UNSIGNED;
#endif
E 3

	/* If we need a lot, alloc a cluster ?? */
	if ((asiz+hsiz+RPC_SIZ) > MHLEN)
D 24
		NFSMCLGET(mreq, M_WAIT);
E 24
I 24
		MCLGET(mreq, M_WAIT);
E 24
	mreq->m_len = NFSMSIZ(mreq);
	siz = mreq->m_len;
	m1 = mreq;
E 45
I 45
	MGET(mb, M_WAIT, MT_DATA);
	if (hsiz >= MINCLSIZE)
		MCLGET(mb, M_WAIT);
	mb->m_len = 0;
	bpos = mtod(mb, caddr_t);
	
E 45
	/*
D 45
	 * Alloc enough mbufs
	 * We do it now to avoid all sleeps after the call to nfs_unixauth()
E 45
I 45
	 * For NQNFS, add lease request.
E 45
	 */
D 45
	while ((asiz+RPC_SIZ) > siz) {
		MGET(m, M_WAIT, MT_DATA);
		m1->m_next = m;
		m->m_len = MLEN;
		siz += MLEN;
		m1 = m;
E 45
I 45
	if (vp) {
		nmp = VFSTONFS(vp->v_mount);
		if (nmp->nm_flag & NFSMNT_NQNFS) {
			nqflag = NQNFS_NEEDLEASE(vp, procid);
			if (nqflag) {
				nfsm_build(tl, u_long *, 2*NFSX_UNSIGNED);
				*tl++ = txdr_unsigned(nqflag);
				*tl = txdr_unsigned(nmp->nm_leaseterm);
			} else {
				nfsm_build(tl, u_long *, NFSX_UNSIGNED);
				*tl = 0;
			}
		}
E 45
	}
D 39
	p = mtod(mreq, u_long *);
	*p++ = *retxid = txdr_unsigned(++nfs_xid);
	*p++ = rpc_call;
	*p++ = rpc_vers;
	*p++ = prog;
	*p++ = vers;
D 12
	*p++ = proc;
E 12
I 12
	*p++ = procid;
E 39
I 39
D 45
	tl = mtod(mreq, u_long *);
	*tl++ = *retxid = txdr_unsigned(++nfs_xid);
E 45
I 45
	/* Finally, return values */
	*bposp = bpos;
	return (mb);
}

/*
 * Build the RPC header and fill in the authorization info.
 * The authorization string argument is only used when the credentials
 * come from outside of the kernel.
 * Returns the head of the mbuf list.
 */
struct mbuf *
D 87
nfsm_rpchead(cr, nqnfs, procid, auth_type, auth_len, auth_str, mrest,
	mrest_len, mbp, xidp)
E 87
I 87
nfsm_rpchead(cr, nmflag, procid, auth_type, auth_len, auth_str, verf_len,
	verf_str, mrest, mrest_len, mbp, xidp)
E 87
	register struct ucred *cr;
D 87
	int nqnfs;
E 87
I 87
	int nmflag;
E 87
	int procid;
	int auth_type;
	int auth_len;
	char *auth_str;
I 87
	int verf_len;
	char *verf_str;
E 87
	struct mbuf *mrest;
	int mrest_len;
	struct mbuf **mbp;
	u_long *xidp;
{
	register struct mbuf *mb;
	register u_long *tl;
	register caddr_t bpos;
	register int i;
	struct mbuf *mreq, *mb2;
	int siz, grpsiz, authsiz;

	authsiz = nfsm_rndup(auth_len);
D 87
	if (auth_type == RPCAUTH_NQNFS)
		authsiz += 2 * NFSX_UNSIGNED;
E 87
	MGETHDR(mb, M_WAIT, MT_DATA);
D 87
	if ((authsiz + 10*NFSX_UNSIGNED) >= MINCLSIZE) {
E 87
I 87
	if ((authsiz + 10 * NFSX_UNSIGNED) >= MINCLSIZE) {
E 87
		MCLGET(mb, M_WAIT);
D 87
	} else if ((authsiz + 10*NFSX_UNSIGNED) < MHLEN) {
		MH_ALIGN(mb, authsiz + 10*NFSX_UNSIGNED);
E 87
I 87
	} else if ((authsiz + 10 * NFSX_UNSIGNED) < MHLEN) {
		MH_ALIGN(mb, authsiz + 10 * NFSX_UNSIGNED);
E 87
	} else {
D 87
		MH_ALIGN(mb, 8*NFSX_UNSIGNED);
E 87
I 87
		MH_ALIGN(mb, 8 * NFSX_UNSIGNED);
E 87
	}
	mb->m_len = 0;
	mreq = mb;
	bpos = mtod(mb, caddr_t);

	/*
	 * First the RPC header.
	 */
D 87
	nfsm_build(tl, u_long *, 8*NFSX_UNSIGNED);
E 87
I 87
	nfsm_build(tl, u_long *, 8 * NFSX_UNSIGNED);
E 87
	if (++nfs_xid == 0)
		nfs_xid++;
	*tl++ = *xidp = txdr_unsigned(nfs_xid);
E 45
	*tl++ = rpc_call;
	*tl++ = rpc_vers;
D 45
	*tl++ = prog;
	*tl++ = vers;
	*tl++ = procid;
E 39
E 12

	/* Now we can call nfs_unixauth() and copy it in */
	ap = nfs_unixauth(cred);
	m = mreq;
	siz = m->m_len-RPC_SIZ;
	if (asiz <= siz) {
D 39
		bcopy(ap, (caddr_t)p, asiz);
E 39
I 39
		bcopy(ap, (caddr_t)tl, asiz);
E 39
		m->m_len = asiz+RPC_SIZ;
E 45
I 45
D 87
	if (nqnfs) {
E 87
I 87
	if (nmflag & NFSMNT_NQNFS) {
E 87
		*tl++ = txdr_unsigned(NQNFS_PROG);
D 87
		*tl++ = txdr_unsigned(NQNFS_VER1);
E 87
I 87
		*tl++ = txdr_unsigned(NQNFS_VER3);
E 87
E 45
	} else {
D 39
		bcopy(ap, (caddr_t)p, siz);
E 39
I 39
D 45
		bcopy(ap, (caddr_t)tl, siz);
E 39
		ap += siz;
		asiz -= siz;
		while (asiz > 0) {
			siz = (asiz > MLEN) ? MLEN : asiz;
			m = m->m_next;
			bcopy(ap, mtod(m, caddr_t), siz);
			m->m_len = siz;
			asiz -= siz;
			ap += siz;
		}
E 45
I 45
		*tl++ = txdr_unsigned(NFS_PROG);
D 87
		*tl++ = txdr_unsigned(NFS_VER2);
E 87
I 87
		if (nmflag & NFSMNT_NFSV3)
			*tl++ = txdr_unsigned(NFS_VER3);
		else
			*tl++ = txdr_unsigned(NFS_VER2);
E 87
E 45
	}
D 45
	
	/* Finally, return values */
	*mb = m;
	*bpos = mtod(m, caddr_t)+m->m_len;
E 45
I 45
D 87
	*tl++ = txdr_unsigned(procid);
E 87
I 87
	if (nmflag & NFSMNT_NFSV3)
		*tl++ = txdr_unsigned(procid);
	else
		*tl++ = txdr_unsigned(nfsv2_procid[procid]);
E 87

	/*
	 * And then the authorization cred.
	 */
	*tl++ = txdr_unsigned(auth_type);
	*tl = txdr_unsigned(authsiz);
	switch (auth_type) {
	case RPCAUTH_UNIX:
		nfsm_build(tl, u_long *, auth_len);
		*tl++ = 0;		/* stamp ?? */
		*tl++ = 0;		/* NULL hostname */
		*tl++ = txdr_unsigned(cr->cr_uid);
		*tl++ = txdr_unsigned(cr->cr_groups[0]);
		grpsiz = (auth_len >> 2) - 5;
		*tl++ = txdr_unsigned(grpsiz);
		for (i = 1; i <= grpsiz; i++)
			*tl++ = txdr_unsigned(cr->cr_groups[i]);
		break;
D 87
	case RPCAUTH_NQNFS:
		nfsm_build(tl, u_long *, 2*NFSX_UNSIGNED);
		*tl++ = txdr_unsigned(cr->cr_uid);
		*tl = txdr_unsigned(auth_len);
E 87
I 87
	case RPCAUTH_KERB4:
E 87
		siz = auth_len;
		while (siz > 0) {
			if (M_TRAILINGSPACE(mb) == 0) {
				MGET(mb2, M_WAIT, MT_DATA);
				if (siz >= MINCLSIZE)
					MCLGET(mb2, M_WAIT);
				mb->m_next = mb2;
				mb = mb2;
				mb->m_len = 0;
				bpos = mtod(mb, caddr_t);
			}
D 68
			i = MIN(siz, M_TRAILINGSPACE(mb));
E 68
I 68
			i = min(siz, M_TRAILINGSPACE(mb));
E 68
			bcopy(auth_str, bpos, i);
			mb->m_len += i;
			auth_str += i;
			bpos += i;
			siz -= i;
		}
D 76
		if ((siz = nfsm_rndup(auth_len) - auth_len) > 0) {
E 76
I 76
		if ((siz = (nfsm_rndup(auth_len) - auth_len)) > 0) {
E 76
			for (i = 0; i < siz; i++)
				*bpos++ = '\0';
			mb->m_len += siz;
		}
		break;
	};
D 87
	nfsm_build(tl, u_long *, 2*NFSX_UNSIGNED);
	*tl++ = txdr_unsigned(RPCAUTH_NULL);
	*tl = 0;
E 87
I 87

	/*
	 * And the verifier...
	 */
	nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
	if (verf_str) {
		*tl++ = txdr_unsigned(RPCAUTH_KERB4);
		*tl = txdr_unsigned(verf_len);
		siz = verf_len;
		while (siz > 0) {
			if (M_TRAILINGSPACE(mb) == 0) {
				MGET(mb2, M_WAIT, MT_DATA);
				if (siz >= MINCLSIZE)
					MCLGET(mb2, M_WAIT);
				mb->m_next = mb2;
				mb = mb2;
				mb->m_len = 0;
				bpos = mtod(mb, caddr_t);
			}
			i = min(siz, M_TRAILINGSPACE(mb));
			bcopy(verf_str, bpos, i);
			mb->m_len += i;
			verf_str += i;
			bpos += i;
			siz -= i;
		}
		if ((siz = (nfsm_rndup(verf_len) - verf_len)) > 0) {
			for (i = 0; i < siz; i++)
				*bpos++ = '\0';
			mb->m_len += siz;
		}
	} else {
		*tl++ = txdr_unsigned(RPCAUTH_NULL);
		*tl = 0;
	}
E 87
	mb->m_next = mrest;
D 87
	mreq->m_pkthdr.len = authsiz + 10*NFSX_UNSIGNED + mrest_len;
E 87
I 87
	mreq->m_pkthdr.len = authsiz + 10 * NFSX_UNSIGNED + mrest_len;
E 87
	mreq->m_pkthdr.rcvif = (struct ifnet *)0;
	*mbp = mb;
E 45
	return (mreq);
}

/*
 * copies mbuf chain to the uio scatter/gather list
 */
I 87
int
E 87
nfsm_mbuftouio(mrep, uiop, siz, dpos)
	struct mbuf **mrep;
D 27
	struct uio *uiop;
E 27
I 27
	register struct uio *uiop;
E 27
	int siz;
	caddr_t *dpos;
{
I 27
	register char *mbufcp, *uiocp;
E 27
	register int xfer, left, len;
	register struct mbuf *mp;
D 27
	register char *mbufcp, *uiocp;
E 27
	long uiosiz, rem;
I 24
	int error = 0;
E 24

	mp = *mrep;
	mbufcp = *dpos;
	len = mtod(mp, caddr_t)+mp->m_len-mbufcp;
	rem = nfsm_rndup(siz)-siz;
	while (siz > 0) {
		if (uiop->uio_iovcnt <= 0 || uiop->uio_iov == NULL)
D 24
			return(EFBIG);
E 24
I 24
			return (EFBIG);
E 24
		left = uiop->uio_iov->iov_len;
		uiocp = uiop->uio_iov->iov_base;
		if (left > siz)
			left = siz;
		uiosiz = left;
		while (left > 0) {
			while (len == 0) {
				mp = mp->m_next;
				if (mp == NULL)
					return (EBADRPC);
				mbufcp = mtod(mp, caddr_t);
				len = mp->m_len;
			}
			xfer = (left > len) ? len : left;
#ifdef notdef
			/* Not Yet.. */
			if (uiop->uio_iov->iov_op != NULL)
				(*(uiop->uio_iov->iov_op))
				(mbufcp, uiocp, xfer);
			else
#endif
			if (uiop->uio_segflg == UIO_SYSSPACE)
				bcopy(mbufcp, uiocp, xfer);
			else
				copyout(mbufcp, uiocp, xfer);
			left -= xfer;
			len -= xfer;
			mbufcp += xfer;
			uiocp += xfer;
I 13
			uiop->uio_offset += xfer;
E 13
			uiop->uio_resid -= xfer;
		}
		if (uiop->uio_iov->iov_len <= siz) {
			uiop->uio_iovcnt--;
			uiop->uio_iov++;
		} else {
			uiop->uio_iov->iov_base += uiosiz;
			uiop->uio_iov->iov_len -= uiosiz;
		}
		siz -= uiosiz;
	}
D 24
	if (rem > 0)
		mbufcp += rem;
E 24
	*dpos = mbufcp;
	*mrep = mp;
D 24
	return(0);
E 24
I 24
	if (rem > 0) {
		if (len < rem)
			error = nfs_adv(mrep, dpos, rem, len);
		else
			*dpos += rem;
	}
	return (error);
E 24
}

/*
 * copies a uio scatter/gather list to an mbuf chain...
 */
I 87
int
E 87
nfsm_uiotombuf(uiop, mq, siz, bpos)
	register struct uio *uiop;
	struct mbuf **mq;
	int siz;
	caddr_t *bpos;
{
D 27
	register struct mbuf *mp;
	struct mbuf *mp2;
D 12
	long xfer, left, uiosiz, off;
E 12
I 12
	long xfer, left, uiosiz;
E 12
	int clflg;
	int rem, len;
	char *cp, *uiocp;
E 27
I 27
	register char *uiocp;
	register struct mbuf *mp, *mp2;
D 45
	register int xfer, left, len;
E 45
I 45
	register int xfer, left, mlen;
E 45
	int uiosiz, clflg, rem;
	char *cp;
E 27

	if (siz > MLEN)		/* or should it >= MCLBYTES ?? */
		clflg = 1;
	else
		clflg = 0;
	rem = nfsm_rndup(siz)-siz;
D 45
	mp2 = *mq;
E 45
I 45
	mp = mp2 = *mq;
E 45
	while (siz > 0) {
		if (uiop->uio_iovcnt <= 0 || uiop->uio_iov == NULL)
D 24
			return(EINVAL);
E 24
I 24
			return (EINVAL);
E 24
		left = uiop->uio_iov->iov_len;
		uiocp = uiop->uio_iov->iov_base;
		if (left > siz)
			left = siz;
		uiosiz = left;
		while (left > 0) {
D 45
			MGET(mp, M_WAIT, MT_DATA);
			if (clflg)
D 24
				NFSMCLGET(mp, M_WAIT);
E 24
I 24
				MCLGET(mp, M_WAIT);
E 24
			mp->m_len = NFSMSIZ(mp);
			mp2->m_next = mp;
			mp2 = mp;
			xfer = (left > mp->m_len) ? mp->m_len : left;
E 45
I 45
			mlen = M_TRAILINGSPACE(mp);
			if (mlen == 0) {
				MGET(mp, M_WAIT, MT_DATA);
				if (clflg)
					MCLGET(mp, M_WAIT);
				mp->m_len = 0;
				mp2->m_next = mp;
				mp2 = mp;
				mlen = M_TRAILINGSPACE(mp);
			}
			xfer = (left > mlen) ? mlen : left;
E 45
#ifdef notdef
			/* Not Yet.. */
			if (uiop->uio_iov->iov_op != NULL)
				(*(uiop->uio_iov->iov_op))
D 45
				(uiocp, mtod(mp, caddr_t), xfer);
E 45
I 45
				(uiocp, mtod(mp, caddr_t)+mp->m_len, xfer);
E 45
			else
#endif
			if (uiop->uio_segflg == UIO_SYSSPACE)
D 45
				bcopy(uiocp, mtod(mp, caddr_t), xfer);
E 45
I 45
				bcopy(uiocp, mtod(mp, caddr_t)+mp->m_len, xfer);
E 45
			else
D 45
				copyin(uiocp, mtod(mp, caddr_t), xfer);
			len = mp->m_len;
			mp->m_len = xfer;
E 45
I 45
				copyin(uiocp, mtod(mp, caddr_t)+mp->m_len, xfer);
			mp->m_len += xfer;
E 45
			left -= xfer;
			uiocp += xfer;
I 13
			uiop->uio_offset += xfer;
E 13
			uiop->uio_resid -= xfer;
		}
		if (uiop->uio_iov->iov_len <= siz) {
			uiop->uio_iovcnt--;
			uiop->uio_iov++;
		} else {
			uiop->uio_iov->iov_base += uiosiz;
			uiop->uio_iov->iov_len -= uiosiz;
		}
		siz -= uiosiz;
	}
	if (rem > 0) {
D 45
		if (rem > (len-mp->m_len)) {
E 45
I 45
		if (rem > M_TRAILINGSPACE(mp)) {
E 45
			MGET(mp, M_WAIT, MT_DATA);
			mp->m_len = 0;
			mp2->m_next = mp;
		}
		cp = mtod(mp, caddr_t)+mp->m_len;
		for (left = 0; left < rem; left++)
			*cp++ = '\0';
		mp->m_len += rem;
		*bpos = cp;
	} else
		*bpos = mtod(mp, caddr_t)+mp->m_len;
	*mq = mp;
D 24
	return(0);
E 24
I 24
	return (0);
E 24
}

/*
 * Help break down an mbuf chain by setting the first siz bytes contiguous
 * pointed to by returned val.
D 80
 * If Updateflg == True we can overwrite the first part of the mbuf data
D 45
 * This is used by the macros nfsm_disect and nfsm_disecton for tough
E 45
I 45
 * (in this case it can never sleep, so it can be called from interrupt level)
 * it may however block when Updateflg == False
E 80
 * This is used by the macros nfsm_dissect and nfsm_dissecton for tough
E 45
 * cases. (The macros use the vars. dpos and dpos2)
 */
I 87
int
E 87
D 80
nfsm_disct(mdp, dposp, siz, left, updateflg, cp2)
E 80
I 80
nfsm_disct(mdp, dposp, siz, left, cp2)
E 80
	struct mbuf **mdp;
	caddr_t *dposp;
	int siz;
	int left;
D 80
	int updateflg;
E 80
	caddr_t *cp2;
{
	register struct mbuf *mp, *mp2;
	register int siz2, xfer;
D 39
	register caddr_t p;
E 39
I 39
D 45
	register caddr_t tl;
E 45
I 45
	register caddr_t p;
E 45
E 39
D 12
	caddr_t p2;
E 12

	mp = *mdp;
	while (left == 0) {
		*mdp = mp = mp->m_next;
		if (mp == NULL)
D 24
			return(EBADRPC);
E 24
I 24
			return (EBADRPC);
E 24
		left = mp->m_len;
		*dposp = mtod(mp, caddr_t);
	}
	if (left >= siz) {
		*cp2 = *dposp;
		*dposp += siz;
D 24
		return(0);
E 24
	} else if (mp->m_next == NULL) {
D 24
		return(EBADRPC);
	} else if (siz > MCLBYTES) {
E 24
I 24
		return (EBADRPC);
	} else if (siz > MHLEN) {
E 24
		panic("nfs S too big");
	} else {
D 80
		/* Iff update, you can overwrite, else must alloc new mbuf */
		if (updateflg) {
			NFSMINOFF(mp);
		} else {
			MGET(mp2, M_WAIT, MT_DATA);
			mp2->m_next = mp->m_next;
			mp->m_next = mp2;
			mp->m_len -= left;
			mp = mp2;
		}
E 80
I 80
		MGET(mp2, M_WAIT, MT_DATA);
		mp2->m_next = mp->m_next;
		mp->m_next = mp2;
		mp->m_len -= left;
		mp = mp2;
E 80
D 24
		/* Alloc cluster iff we need it */
		if (!M_HASCL(mp) && siz > NFSMSIZ(mp)) {
			NFSMCLGET(mp, M_WAIT);
			if (!M_HASCL(mp))
				return(ENOBUFS);
		}
E 24
D 39
		*cp2 = p = mtod(mp, caddr_t);
		bcopy(*dposp, p, left);		/* Copy what was left */
E 39
I 39
D 45
		*cp2 = tl = mtod(mp, caddr_t);
		bcopy(*dposp, tl, left);		/* Copy what was left */
E 45
I 45
		*cp2 = p = mtod(mp, caddr_t);
		bcopy(*dposp, p, left);		/* Copy what was left */
E 45
E 39
		siz2 = siz-left;
D 39
		p += left;
E 39
I 39
D 45
		tl += left;
E 45
I 45
		p += left;
E 45
E 39
		mp2 = mp->m_next;
D 24
		/* Loop arround copying up the siz2 bytes */
E 24
I 24
		/* Loop around copying up the siz2 bytes */
E 24
		while (siz2 > 0) {
			if (mp2 == NULL)
				return (EBADRPC);
			xfer = (siz2 > mp2->m_len) ? mp2->m_len : siz2;
D 24
			bcopy(mtod(mp2, caddr_t), p, xfer);
			NFSMADV(mp2, xfer);
			mp2->m_len -= xfer;
			siz2 -= xfer;
E 24
I 24
			if (xfer > 0) {
D 39
				bcopy(mtod(mp2, caddr_t), p, xfer);
E 39
I 39
D 45
				bcopy(mtod(mp2, caddr_t), tl, xfer);
E 45
I 45
				bcopy(mtod(mp2, caddr_t), p, xfer);
E 45
E 39
				NFSMADV(mp2, xfer);
				mp2->m_len -= xfer;
D 39
				p += xfer;
E 39
I 39
D 45
				tl += xfer;
E 45
I 45
				p += xfer;
E 45
E 39
				siz2 -= xfer;
			}
E 24
			if (siz2 > 0)
				mp2 = mp2->m_next;
		}
		mp->m_len = siz;
		*mdp = mp2;
		*dposp = mtod(mp2, caddr_t);
D 12
		return (0);
E 12
	}
I 12
	return (0);
E 12
}

/*
D 24
 * Advance the position in the mbuf chain with/without freeing mbufs
E 24
I 24
 * Advance the position in the mbuf chain.
E 24
 */
I 87
int
E 87
nfs_adv(mdp, dposp, offs, left)
	struct mbuf **mdp;
	caddr_t *dposp;
	int offs;
	int left;
{
	register struct mbuf *m;
	register int s;

	m = *mdp;
	s = left;
	while (s < offs) {
		offs -= s;
		m = m->m_next;
		if (m == NULL)
D 24
			return(EBADRPC);
E 24
I 24
			return (EBADRPC);
E 24
		s = m->m_len;
	}
	*mdp = m;
	*dposp = mtod(m, caddr_t)+offs;
D 24
	return(0);
E 24
I 24
	return (0);
E 24
}

/*
 * Copy a string into mbufs for the hard cases...
 */
I 87
int
E 87
nfsm_strtmbuf(mb, bpos, cp, siz)
	struct mbuf **mb;
	char **bpos;
	char *cp;
	long siz;
{
D 87
	register struct mbuf *m1, *m2;
E 87
I 87
	register struct mbuf *m1 = 0, *m2;
E 87
	long left, xfer, len, tlen;
D 39
	u_long *p;
E 39
I 39
	u_long *tl;
E 39
	int putsize;

	putsize = 1;
	m2 = *mb;
D 45
	left = NFSMSIZ(m2)-m2->m_len;
E 45
I 45
	left = M_TRAILINGSPACE(m2);
E 45
	if (left > 0) {
D 39
		p = ((u_long *)(*bpos));
		*p++ = txdr_unsigned(siz);
E 39
I 39
		tl = ((u_long *)(*bpos));
		*tl++ = txdr_unsigned(siz);
E 39
		putsize = 0;
		left -= NFSX_UNSIGNED;
		m2->m_len += NFSX_UNSIGNED;
		if (left > 0) {
D 39
			bcopy(cp, (caddr_t) p, left);
E 39
I 39
			bcopy(cp, (caddr_t) tl, left);
E 39
			siz -= left;
			cp += left;
			m2->m_len += left;
			left = 0;
		}
	}
D 45
	/* Loop arround adding mbufs */
E 45
I 45
	/* Loop around adding mbufs */
E 45
	while (siz > 0) {
		MGET(m1, M_WAIT, MT_DATA);
		if (siz > MLEN)
D 24
			NFSMCLGET(m1, M_WAIT);
E 24
I 24
			MCLGET(m1, M_WAIT);
E 24
		m1->m_len = NFSMSIZ(m1);
		m2->m_next = m1;
		m2 = m1;
D 39
		p = mtod(m1, u_long *);
E 39
I 39
		tl = mtod(m1, u_long *);
E 39
		tlen = 0;
		if (putsize) {
D 39
			*p++ = txdr_unsigned(siz);
E 39
I 39
			*tl++ = txdr_unsigned(siz);
E 39
			m1->m_len -= NFSX_UNSIGNED;
			tlen = NFSX_UNSIGNED;
			putsize = 0;
		}
		if (siz < m1->m_len) {
			len = nfsm_rndup(siz);
			xfer = siz;
			if (xfer < len)
D 39
				*(p+(xfer>>2)) = 0;
E 39
I 39
				*(tl+(xfer>>2)) = 0;
E 39
		} else {
			xfer = len = m1->m_len;
		}
D 39
		bcopy(cp, (caddr_t) p, xfer);
E 39
I 39
		bcopy(cp, (caddr_t) tl, xfer);
E 39
		m1->m_len = len+tlen;
		siz -= xfer;
		cp += xfer;
	}
	*mb = m1;
	*bpos = mtod(m1, caddr_t)+m1->m_len;
D 24
	return(0);
E 24
I 24
	return (0);
E 24
}

/*
 * Called once to initialize data structures...
 */
D 10
nfsinit()
E 10
I 10
D 87
nfs_init()
E 87
I 87
int
nfs_init(vfsp)
	struct vfsconf *vfsp;
E 87
E 10
{
	register int i;
I 45
D 83
	union nqsrvthead *lhp;
E 83
E 45

I 87
	/*
	 * Check to see if major data structures haven't bloated.
	 */
	if (sizeof (struct nfsnode) > NFS_NODEALLOC) {
		printf("struct nfsnode bloated (> %dbytes)\n", NFS_NODEALLOC);
		printf("Try reducing NFS_SMALLFH\n");
	}
	if (sizeof (struct nfsmount) > NFS_MNTALLOC) {
		printf("struct nfsmount bloated (> %dbytes)\n", NFS_MNTALLOC);
		printf("Try reducing NFS_MUIDHASHSIZ\n");
	}
	if (sizeof (struct nfssvc_sock) > NFS_SVCALLOC) {
		printf("struct nfssvc_sock bloated (> %dbytes)\n",NFS_SVCALLOC);
		printf("Try reducing NFS_UIDHASHSIZ\n");
	}
	if (sizeof (struct nfsuid) > NFS_UIDALLOC) {
		printf("struct nfsuid bloated (> %dbytes)\n",NFS_UIDALLOC);
		printf("Try unionizing the nu_nickname and nu_flag fields\n");
	}
	nfs_mount_type = vfsp->vfc_typenum;
E 87
I 45
	nfsrtt.pos = 0;
E 45
	rpc_vers = txdr_unsigned(RPC_VER2);
	rpc_call = txdr_unsigned(RPC_CALL);
	rpc_reply = txdr_unsigned(RPC_REPLY);
	rpc_msgdenied = txdr_unsigned(RPC_MSGDENIED);
	rpc_msgaccepted = txdr_unsigned(RPC_MSGACCEPTED);
	rpc_mismatch = txdr_unsigned(RPC_MISMATCH);
I 45
	rpc_autherr = txdr_unsigned(RPC_AUTHERR);
D 87
	rpc_rejectedcred = txdr_unsigned(AUTH_REJECTCRED);
E 87
E 45
	rpc_auth_unix = txdr_unsigned(RPCAUTH_UNIX);
I 45
D 87
	rpc_auth_kerb = txdr_unsigned(RPCAUTH_NQNFS);
E 45
	nfs_vers = txdr_unsigned(NFS_VER2);
E 87
I 87
	rpc_auth_kerb = txdr_unsigned(RPCAUTH_KERB4);
E 87
	nfs_prog = txdr_unsigned(NFS_PROG);
I 87
	nqnfs_prog = txdr_unsigned(NQNFS_PROG);
E 87
	nfs_true = txdr_unsigned(TRUE);
	nfs_false = txdr_unsigned(FALSE);
D 87
	/* Loop thru nfs procids */
	for (i = 0; i < NFS_NPROCS; i++)
		nfs_procids[i] = txdr_unsigned(i);
E 87
I 87
	nfs_xdrneg1 = txdr_unsigned(-1);
	nfs_ticks = (hz * NFS_TICKINTVL + 500) / 1000;
	if (nfs_ticks < 1)
		nfs_ticks = 1;
E 87
I 8
	/* Ensure async daemons disabled */
D 24
	for (i = 0; i < MAX_ASYNCDAEMON; i++)
E 24
I 24
	for (i = 0; i < NFS_MAXASYNCDAEMON; i++)
E 24
		nfs_iodwant[i] = (struct proc *)0;
I 74
D 82
	queue_init(&nfs_bufq);
E 82
I 82
	TAILQ_INIT(&nfs_bufq);
E 82
E 74
E 8
D 25
	v_type[0] = VNON;
	v_type[1] = VREG;
	v_type[2] = VDIR;
	v_type[3] = VBLK;
	v_type[4] = VCHR;
	v_type[5] = VLNK;
E 25
D 87
	nfs_xdrneg1 = txdr_unsigned(-1);
E 87
	nfs_nhinit();			/* Init the nfsnode table */
I 48
	nfsrv_init(0);			/* Init server data structures */
E 48
I 15
	nfsrv_initcache();		/* Init the server request cache */
E 15
I 7
D 45
	rminit(nfsmap, (long)NFS_MAPREG, (long)1, "nfs mapreg", NFS_MSIZ);
E 45
E 7
D 24
	/* And start timer */
E 24
I 24

	/*
I 45
	 * Initialize the nqnfs server stuff.
	 */
	if (nqnfsstarttime == 0) {
		nqnfsstarttime = boottime.tv_sec + nqsrv_maxlease
			+ nqsrv_clockskew + nqsrv_writeslack;
		NQLOADNOVRAM(nqnfsstarttime);
D 87
		nqnfs_prog = txdr_unsigned(NQNFS_PROG);
		nqnfs_vers = txdr_unsigned(NQNFS_VER1);
E 87
D 85
		nqthead.th_head[0] = &nqthead;
		nqthead.th_head[1] = &nqthead;
D 69
		for (i = 0; i < NQLCHSZ; i++) {
			lhp = &nqfhead[i];
			lhp->th_head[0] = lhp;
			lhp->th_head[1] = lhp;
		}
E 69
I 69
		nqfhead = hashinit(NQLCHSZ, M_NQLEASE, &nqfheadhash);
E 85
I 85
		CIRCLEQ_INIT(&nqtimerhead);
		nqfhhashtbl = hashinit(NQLCHSZ, M_NQLEASE, &nqfhhash);
E 85
E 69
	}

	/*
E 45
	 * Initialize reply list and start timer
	 */
D 85
	nfsreqh.r_prev = nfsreqh.r_next = &nfsreqh;
E 85
I 85
	TAILQ_INIT(&nfs_reqq);
E 85
E 24
D 87
	nfs_timer();
E 87
I 87
	nfs_timer(0);
	return (0);
E 87
}

/*
D 45
 * Fill in the rest of the rpc_unixauth and return it
 */
static char *nfs_unixauth(cr)
	register struct ucred *cr;
{
D 39
	register u_long *p;
E 39
I 39
	register u_long *tl;
E 39
	register int i;
	int ngr;

	/* Maybe someday there should be a cache of AUTH_SHORT's */
D 39
	if ((p = rpc_uidp) == NULL) {
E 39
I 39
	if ((tl = rpc_uidp) == NULL) {
E 39
I 3
#ifdef FILLINHOST
E 3
D 29
		i = nfsm_rndup(hostnamelen)+(19*NFSX_UNSIGNED);
E 29
I 29
		i = nfsm_rndup(hostnamelen)+(25*NFSX_UNSIGNED);
E 29
I 3
#else
D 29
		i = 19*NFSX_UNSIGNED;
E 29
I 29
		i = 25*NFSX_UNSIGNED;
E 29
#endif
E 3
D 39
		MALLOC(p, u_long *, i, M_TEMP, M_WAITOK);
		bzero((caddr_t)p, i);
		rpc_unixauth = (caddr_t)p;
		*p++ = txdr_unsigned(RPCAUTH_UNIX);
		p++;	/* Fill in size later */
		*p++ = hostid;
E 39
I 39
		MALLOC(tl, u_long *, i, M_TEMP, M_WAITOK);
		bzero((caddr_t)tl, i);
		rpc_unixauth = (caddr_t)tl;
		*tl++ = txdr_unsigned(RPCAUTH_UNIX);
		tl++;	/* Fill in size later */
		*tl++ = hostid;
E 39
I 3
#ifdef FILLINHOST
E 3
D 39
		*p++ = txdr_unsigned(hostnamelen);
E 39
I 39
		*tl++ = txdr_unsigned(hostnamelen);
E 39
		i = nfsm_rndup(hostnamelen);
D 39
		bcopy(hostname, (caddr_t)p, hostnamelen);
		p += (i>>2);
E 39
I 39
		bcopy(hostname, (caddr_t)tl, hostnamelen);
		tl += (i>>2);
E 39
I 3
#else
D 39
		*p++ = 0;
E 39
I 39
		*tl++ = 0;
E 39
#endif
E 3
D 39
		rpc_uidp = p;
E 39
I 39
		rpc_uidp = tl;
E 39
	}
D 39
	*p++ = txdr_unsigned(cr->cr_uid);
	*p++ = txdr_unsigned(cr->cr_groups[0]);
E 39
I 39
	*tl++ = txdr_unsigned(cr->cr_uid);
	*tl++ = txdr_unsigned(cr->cr_groups[0]);
E 39
D 6
	ngr = (cr->cr_ngroups > 10) ? 10 : cr->cr_ngroups;
E 6
I 6
D 29
	ngr = (cr->cr_ngroups > numgrps) ? numgrps : cr->cr_ngroups;
E 29
I 29
	ngr = ((cr->cr_ngroups - 1) > numgrps) ? numgrps : (cr->cr_ngroups - 1);
E 29
E 6
D 39
	*p++ = txdr_unsigned(ngr);
E 39
I 39
	*tl++ = txdr_unsigned(ngr);
E 39
D 29
	for (i = 0; i < ngr; i++)
E 29
I 29
	for (i = 1; i <= ngr; i++)
E 29
D 39
		*p++ = txdr_unsigned(cr->cr_groups[i]);
E 39
I 39
		*tl++ = txdr_unsigned(cr->cr_groups[i]);
E 39
	/* And add the AUTH_NULL */
D 39
	*p++ = 0;
	*p = 0;
	i = (((caddr_t)p)-rpc_unixauth)-12;
	p = (u_long *)(rpc_unixauth+4);
	*p = txdr_unsigned(i);
E 39
I 39
	*tl++ = 0;
	*tl = 0;
	i = (((caddr_t)tl)-rpc_unixauth)-12;
	tl = (u_long *)(rpc_unixauth+4);
	*tl = txdr_unsigned(i);
E 39
D 24
	return(rpc_unixauth);
E 24
I 24
	return (rpc_unixauth);
E 24
}

/*
E 45
 * Attribute cache routines.
 * nfs_loadattrcache() - loads or updates the cache contents from attributes
 *	that are on the mbuf list
 * nfs_getattrcache() - returns valid attributes if found in cache, returns
 *	error otherwise
 */

/*
D 10
 * Load the attribute cache (that lives in the nfsnode table) with
E 10
I 10
 * Load the attribute cache (that lives in the nfsnode entry) with
E 10
 * the values on the mbuf list and
 * Iff vap not NULL
 *    copy the attributes to *vaper
 */
I 87
int
E 87
D 11
nfs_loadattrcache(vp, mdp, dposp, vaper)
	register struct vnode *vp;
E 11
I 11
nfs_loadattrcache(vpp, mdp, dposp, vaper)
	struct vnode **vpp;
E 11
	struct mbuf **mdp;
	caddr_t *dposp;
	struct vattr *vaper;
{
I 11
	register struct vnode *vp = *vpp;
E 11
	register struct vattr *vap;
I 7
D 87
	register struct nfsv2_fattr *fp;
E 87
I 87
	register struct nfs_fattr *fp;
E 87
I 10
D 43
	extern struct vnodeops spec_nfsv2nodeops;
E 43
I 43
D 51
	extern struct vnodeops spec_nfsv2nodeops, spec_vnodeops;
E 51
I 51
D 60
	extern struct vnodeops spec_nfsv2nodeops;
	extern struct vnodeops spec_vnodeops;
E 60
I 60
	extern int (**spec_nfsv2nodeop_p)();
D 70
	extern int (**spec_vnodeop_p)();
E 70
E 60
E 51
E 43
I 11
D 69
	register struct nfsnode *np;
E 69
I 69
D 85
	register struct nfsnode *np, *nq, **nhpp;
E 85
I 85
	register struct nfsnode *np;
	register struct nfsnodehashhead *nhpp;
E 85
E 69
E 11
E 10
E 7
D 12
	nfsm_vars;
E 12
I 12
	register long t1;
D 87
	caddr_t dpos, cp2;
D 71
	int error = 0;
E 71
I 71
	int error = 0, isnq;
E 87
I 87
	caddr_t cp2;
	int error = 0, rdev;
E 87
E 71
	struct mbuf *md;
E 12
D 11
	struct nfsnode *np;
E 11
I 10
D 45
	enum vtype type;
I 37
	u_short mode;
E 45
I 45
	enum vtype vtyp;
	u_short vmode;
E 45
E 37
D 25
	dev_t rdev;
E 25
I 25
D 87
	long rdev;
E 87
E 25
D 71
	struct timeval mtime;
E 71
I 71
	struct timespec mtime;
E 71
	struct vnode *nvp;
I 87
	quad_t tval;
	int v3 = NFS_ISV3(vp);
E 87
E 10

	md = *mdp;
D 87
	dpos = *dposp;
D 45
	t1 = (mtod(md, caddr_t)+md->m_len)-dpos;
E 45
I 45
	t1 = (mtod(md, caddr_t) + md->m_len) - dpos;
E 45
D 71
	if (error = nfsm_disct(&md, &dpos, NFSX_FATTR, t1, TRUE, &cp2))
E 71
I 71
	isnq = (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS);
D 80
	if (error = nfsm_disct(&md, &dpos, NFSX_FATTR(isnq), t1, TRUE, &cp2))
E 80
I 80
	if (error = nfsm_disct(&md, &dpos, NFSX_FATTR(isnq), t1, &cp2))
E 87
I 87
	t1 = (mtod(md, caddr_t) + md->m_len) - *dposp;
	if (error = nfsm_disct(mdp, dposp, NFSX_FATTR(v3), t1, &cp2))
E 87
E 80
E 71
		return (error);
D 7
	p = (u_long *)cp2;
E 7
I 7
D 87
	fp = (struct nfsv2_fattr *)cp2;
I 10
D 45
	type = nfstov_type(fp->fa_type);
I 37
	mode = fxdr_unsigned(u_short, fp->fa_mode);
	if (type == VNON)
		type = IFTOVT(mode);
E 45
I 45
	vtyp = nfstov_type(fp->fa_type);
	vmode = fxdr_unsigned(u_short, fp->fa_mode);
D 50
	if (vtyp == VNON)
E 50
I 50
	if (vtyp == VNON || vtyp == VREG)
E 50
		vtyp = IFTOVT(vmode);
E 45
E 37
D 25
	rdev = fxdr_unsigned(dev_t, fp->fa_rdev);
E 25
I 25
D 71
	rdev = fxdr_unsigned(long, fp->fa_rdev);
E 25
	fxdr_time(&fp->fa_mtime, &mtime);
E 71
I 71
	if (isnq) {
		rdev = fxdr_unsigned(long, fp->fa_nqrdev);
		fxdr_nqtime(&fp->fa_nqmtime, &mtime);
E 87
I 87
	fp = (struct nfs_fattr *)cp2;
	if (v3) {
		vtyp = nfsv3tov_type(fp->fa_type);
		vmode = fxdr_unsigned(u_short, fp->fa_mode);
		rdev = makedev(fxdr_unsigned(u_char, fp->fa3_rdev.specdata1),
			fxdr_unsigned(u_char, fp->fa3_rdev.specdata2));
		fxdr_nfsv3time(&fp->fa3_mtime, &mtime);
E 87
	} else {
D 87
		rdev = fxdr_unsigned(long, fp->fa_nfsrdev);
		fxdr_nfstime(&fp->fa_nfsmtime, &mtime);
E 87
I 87
		vtyp = nfsv2tov_type(fp->fa_type);
		vmode = fxdr_unsigned(u_short, fp->fa_mode);
		if (vtyp == VNON || vtyp == VREG)
			vtyp = IFTOVT(vmode);
		rdev = fxdr_unsigned(long, fp->fa2_rdev);
		fxdr_nfsv2time(&fp->fa2_mtime, &mtime);

		/*
		 * Really ugly NFSv2 kludge.
		 */
		if (vtyp == VCHR && rdev == 0xffffffff)
			vtyp = VFIFO;
E 87
	}
I 87

E 87
E 71
	/*
	 * If v_type == VNON it is a new node, so fill in the v_type,
	 * n_mtime fields. Check to see if it represents a special 
	 * device, and if so, check for a possible alias. Once the
	 * correct vnode has been obtained, fill in the rest of the
	 * information.
	 */
E 10
E 7
	np = VTONFS(vp);
I 10
	if (vp->v_type == VNON) {
D 25
		vp->v_type = type;
E 25
I 25
D 45
		if (type == VCHR && rdev == 0xffffffff)
			vp->v_type = type = VFIFO;
E 45
I 45
D 87
		if (vtyp == VCHR && rdev == 0xffffffff)
			vp->v_type = vtyp = VFIFO;
E 45
		else
D 45
			vp->v_type = type;
E 45
I 45
			vp->v_type = vtyp;
E 87
I 87
		vp->v_type = vtyp;
E 87
E 45
E 25
I 19
		if (vp->v_type == VFIFO) {
D 87
#ifdef FIFO
E 87
D 60
			extern struct vnodeops fifo_nfsv2nodeops;
			vp->v_op = &fifo_nfsv2nodeops;
E 60
I 60
			extern int (**fifo_nfsv2nodeop_p)();
			vp->v_op = fifo_nfsv2nodeop_p;
E 60
D 87
#else
			return (EOPNOTSUPP);
#endif /* FIFO */
E 87
		}
E 19
		if (vp->v_type == VCHR || vp->v_type == VBLK) {
D 14
			vp->v_rdev = rdev;
E 14
D 60
			vp->v_op = &spec_nfsv2nodeops;
E 60
I 60
			vp->v_op = spec_nfsv2nodeop_p;
E 60
D 14
			if (nvp = checkalias(vp, vp->v_mount)) {
E 14
I 14
D 25
			if (nvp = checkalias(vp, rdev, vp->v_mount)) {
E 25
I 25
D 87
			if (nvp = checkalias(vp, (dev_t)rdev, vp->v_mount)) {
E 87
I 87
			nvp = checkalias(vp, (dev_t)rdev, vp->v_mount);
			if (nvp) {
E 87
E 25
E 14
				/*
I 43
				 * Discard unneeded vnode, but save its nfsnode.
I 89
				 * Since the nfsnode does not have a lock, its
				 * vnode lock has to be carried over.
E 89
				 */
D 69
				remque(np);
E 69
I 69
D 85
				if (nq = np->n_forw)
					nq->n_back = np->n_back;
				*np->n_back = nq;
E 85
I 85
D 89
				LIST_REMOVE(np, n_hash);
E 89
I 89
				nvp->v_vnlock = vp->v_vnlock;
				vp->v_vnlock = NULL;
E 89
E 85
E 69
D 45
				nfs_unlock(vp);
E 45
				nvp->v_data = vp->v_data;
				vp->v_data = NULL;
D 60
				vp->v_op = &spec_vnodeops;
E 60
I 60
				vp->v_op = spec_vnodeop_p;
E 60
				vrele(vp);
				vgone(vp);
				/*
E 43
				 * Reinitialize aliased node.
				 */
D 43
				np = VTONFS(nvp);
E 43
				np->n_vnode = nvp;
D 16
				np->n_flag = NLOCKED;
E 16
I 16
D 43
				np->n_flag = 0;
				nfs_lock(nvp);
E 16
				bcopy((caddr_t)&VTONFS(vp)->n_fh,
					(caddr_t)&np->n_fh, NFSX_FH);
E 43
D 69
				insque(np, nfs_hash(&np->n_fh));
E 69
I 69
D 85
				nhpp = (struct nfsnode **)nfs_hash(&np->n_fh);
				if (nq = *nhpp)
					nq->n_back = &np->n_forw;
				np->n_forw = nq;
				np->n_back = nhpp;
				*nhpp = np;
E 85
I 85
D 87
				nhpp = nfs_hash(&np->n_fh);
E 87
I 87
D 89
				nhpp = NFSNOHASH(nfs_hash(np->n_fhp, np->n_fhsize));
E 87
				LIST_INSERT_HEAD(nhpp, np, n_hash);
E 89
E 85
E 69
D 43
				np->n_attrstamp = 0;
				np->n_sillyrename = (struct sillyrename *)0;
				/*
D 11
				 * Discard unneeded vnode
E 11
I 11
				 * Discard unneeded vnode and update actual one
E 11
				 */
				vput(vp);
D 11
				vp = nvp;
E 11
I 11
D 19
				*vpp = nvp;
E 19
I 19
D 24
				*vpp = vp = nvp;
E 24
I 24
				*vpp = nvp;
E 43
I 43
D 45
				nfs_lock(nvp);
E 45
				*vpp = vp = nvp;
E 43
E 24
E 19
E 11
			}
		}
D 45
		np->n_mtime = mtime.tv_sec;
E 45
I 45
D 71
		if ((VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS) == 0)
			np->n_mtime = mtime.tv_sec;
E 71
I 71
		np->n_mtime = mtime.ts_sec;
E 71
E 45
	}
E 10
	vap = &np->n_vattr;
D 7
	vap->va_type = nfstov_type(*p++);
	vap->va_mode = nfstov_mode(*p++);
	vap->va_nlink = fxdr_unsigned(u_short, *p++);
	vap->va_uid = fxdr_unsigned(uid_t, *p++);
	vap->va_gid = fxdr_unsigned(gid_t, *p++);
	vap->va_size = fxdr_unsigned(u_long, *p++);
E 7
I 7
D 10
	vap->va_type = nfstov_type(fp->fa_type);
E 10
I 10
D 45
	vap->va_type = type;
E 10
D 37
	vap->va_mode = nfstov_mode(fp->fa_mode);
E 37
I 37
	vap->va_mode = (mode & 07777);
E 45
I 45
	vap->va_type = vtyp;
	vap->va_mode = (vmode & 07777);
E 45
E 37
D 87
	vap->va_nlink = fxdr_unsigned(u_short, fp->fa_nlink);
	vap->va_uid = fxdr_unsigned(uid_t, fp->fa_uid);
	vap->va_gid = fxdr_unsigned(gid_t, fp->fa_gid);
E 87
D 71
	vap->va_size = fxdr_unsigned(u_long, fp->fa_size);
D 33
	if ((np->n_flag & NMODIFIED) == 0 || vap->va_size > np->n_size)
E 33
I 33
	if ((np->n_flag & NMODIFIED) == 0 || vap->va_size > np->n_size) {
E 71
I 71
	vap->va_rdev = (dev_t)rdev;
	vap->va_mtime = mtime;
	vap->va_fsid = vp->v_mount->mnt_stat.f_fsid.val[0];
D 87
	if (isnq) {
		fxdr_hyper(&fp->fa_nqsize, &vap->va_size);
		vap->va_blocksize = fxdr_unsigned(long, fp->fa_nqblocksize);
		fxdr_hyper(&fp->fa_nqbytes, &vap->va_bytes);
		vap->va_fileid = fxdr_unsigned(long, fp->fa_nqfileid);
		fxdr_nqtime(&fp->fa_nqatime, &vap->va_atime);
		vap->va_flags = fxdr_unsigned(u_long, fp->fa_nqflags);
		fxdr_nqtime(&fp->fa_nqctime, &vap->va_ctime);
		vap->va_gen = fxdr_unsigned(u_long, fp->fa_nqgen);
		fxdr_hyper(&fp->fa_nqfilerev, &vap->va_filerev);
E 87
I 87
	if (v3) {
		vap->va_nlink = fxdr_unsigned(u_short, fp->fa_nlink);
		vap->va_uid = fxdr_unsigned(uid_t, fp->fa_uid);
		vap->va_gid = fxdr_unsigned(gid_t, fp->fa_gid);
		fxdr_hyper(&fp->fa3_size, &vap->va_size);
		vap->va_blocksize = NFS_FABLKSIZE;
		fxdr_hyper(&fp->fa3_used, &vap->va_bytes);
		vap->va_fileid = fxdr_unsigned(int, fp->fa3_fileid.nfsuquad[1]);
		fxdr_nfsv3time(&fp->fa3_atime, &vap->va_atime);
		fxdr_nfsv3time(&fp->fa3_ctime, &vap->va_ctime);
		vap->va_flags = 0;
		vap->va_filerev = 0;
E 87
	} else {
D 87
		vap->va_size = fxdr_unsigned(u_long, fp->fa_nfssize);
		vap->va_blocksize = fxdr_unsigned(long, fp->fa_nfsblocksize);
		vap->va_bytes = fxdr_unsigned(long, fp->fa_nfsblocks) * NFS_FABLKSIZE;
		vap->va_fileid = fxdr_unsigned(long, fp->fa_nfsfileid);
D 78
		vap->va_atime.ts_sec = fxdr_unsigned(long, fp->fa_nfsatime.nfs_sec);
		vap->va_atime.ts_nsec = 0;
		vap->va_flags = fxdr_unsigned(u_long, fp->fa_nfsatime.nfs_usec);
E 78
I 78
		fxdr_nfstime(&fp->fa_nfsatime, &vap->va_atime);
E 87
I 87
		vap->va_nlink = fxdr_unsigned(u_short, fp->fa_nlink);
		vap->va_uid = fxdr_unsigned(uid_t, fp->fa_uid);
		vap->va_gid = fxdr_unsigned(gid_t, fp->fa_gid);
		vap->va_size = fxdr_unsigned(u_long, fp->fa2_size);
		vap->va_blocksize = fxdr_unsigned(long, fp->fa2_blocksize);
		vap->va_bytes = fxdr_unsigned(long, fp->fa2_blocks) * NFS_FABLKSIZE;
		vap->va_fileid = fxdr_unsigned(long, fp->fa2_fileid);
		fxdr_nfsv2time(&fp->fa2_atime, &vap->va_atime);
E 87
		vap->va_flags = 0;
E 78
D 87
		vap->va_ctime.ts_sec = fxdr_unsigned(long, fp->fa_nfsctime.nfs_sec);
E 87
I 87
		vap->va_ctime.ts_sec = fxdr_unsigned(long, fp->fa2_ctime.nfsv2_sec);
E 87
		vap->va_ctime.ts_nsec = 0;
D 87
		vap->va_gen = fxdr_unsigned(u_long, fp->fa_nfsctime.nfs_usec);
E 87
I 87
		vap->va_gen = fxdr_unsigned(u_long, fp->fa2_ctime.nfsv2_usec);
E 87
		vap->va_filerev = 0;
	}
D 76
	if (vap->va_size > np->n_size) {
E 71
E 33
		np->n_size = vap->va_size;
I 34
D 40
#ifdef NVM
E 40
E 34
I 33
D 49
		vnode_pager_setsize(vp, np->n_size);
E 49
I 49
		vnode_pager_setsize(vp, (u_long)np->n_size);
E 76
I 76
	if (vap->va_size != np->n_size) {
		if (vap->va_type == VREG) {
			if (np->n_flag & NMODIFIED) {
				if (vap->va_size < np->n_size)
					vap->va_size = np->n_size;
				else
					np->n_size = vap->va_size;
			} else
				np->n_size = vap->va_size;
			vnode_pager_setsize(vp, (u_long)np->n_size);
		} else
			np->n_size = vap->va_size;
E 76
E 49
I 34
D 40
#endif
E 40
E 34
	}
E 33
E 7
D 21
	vap->va_size1 = 0;		/* OR -1 ?? */
E 21
I 21
D 44
	vap->va_size_rsv = 0;
E 44
E 21
D 7
	vap->va_blocksize = fxdr_unsigned(long, *p++);
	vap->va_rdev = fxdr_unsigned(dev_t, *p++);
D 5
	vap->va_bytes = fxdr_unsigned(long, *p++);
E 5
I 5
	vap->va_bytes = fxdr_unsigned(long, *p++) * vap->va_blocksize;
E 5
	vap->va_bytes1 = -1;
	vap->va_fsid = fxdr_unsigned(long, *p++);
	vap->va_fileid = fxdr_unsigned(long, *p++);
	fxdr_time(p, &(vap->va_atime));
	p += 2;
	fxdr_time(p, &(vap->va_mtime));
	p += 2;
	fxdr_time(p, &(vap->va_ctime));
E 7
I 7
D 71
	vap->va_blocksize = fxdr_unsigned(long, fp->fa_blocksize);
D 10
	vap->va_rdev = fxdr_unsigned(dev_t, fp->fa_rdev);
E 10
I 10
D 25
	vap->va_rdev = rdev;
E 10
	vap->va_bytes = fxdr_unsigned(long, fp->fa_blocks) * vap->va_blocksize;
E 25
I 25
	vap->va_rdev = (dev_t)rdev;
	vap->va_bytes = fxdr_unsigned(long, fp->fa_blocks) * NFS_FABLKSIZE;
E 25
D 21
	vap->va_bytes1 = 0;
E 21
I 21
D 44
	vap->va_bytes_rsv = 0;
E 44
E 21
D 15
	vap->va_fsid = fxdr_unsigned(long, fp->fa_fsid);
E 15
I 15
D 20
	vap->va_fsid = vp->v_mount->m_fsid.val[0];
E 20
I 20
D 22
	vap->va_fsid = vp->v_mount->m_stat.f_fsid.val[0];
E 22
I 22
D 23
	vap->va_fsid = vp->v_mount->mnt_stat.f_fsid.val[0];
E 23
I 23
D 26
	vap->va_fsid = vp->v_mount->mnt_stat.f_fsid.val[0] | 0x8000;
E 26
I 26
	vap->va_fsid = vp->v_mount->mnt_stat.f_fsid.val[0];
E 26
E 23
E 22
E 20
E 15
	vap->va_fileid = fxdr_unsigned(long, fp->fa_fileid);
D 15
	fxdr_time(&fp->fa_atime, &vap->va_atime);
D 10
	fxdr_time(&fp->fa_mtime, &vap->va_mtime);
E 10
	fxdr_time(&fp->fa_ctime, &vap->va_ctime);
E 15
I 15
D 62
	vap->va_atime.tv_sec = fxdr_unsigned(long, fp->fa_atime.tv_sec);
	vap->va_atime.tv_usec = 0;
E 62
I 62
	vap->va_atime.ts_sec = fxdr_unsigned(long, fp->fa_atime.tv_sec);
	vap->va_atime.ts_nsec = 0;
E 62
	vap->va_flags = fxdr_unsigned(u_long, fp->fa_atime.tv_usec);
E 15
I 10
D 62
	vap->va_mtime = mtime;
E 10
E 7
I 4
D 15
	vap->va_gen = 0;
	vap->va_flags = 0;
E 15
I 15
	vap->va_ctime.tv_sec = fxdr_unsigned(long, fp->fa_ctime.tv_sec);
	vap->va_ctime.tv_usec = 0;
E 62
I 62
	vap->va_mtime.ts_sec = mtime.tv_sec;
	vap->va_mtime.ts_nsec = mtime.tv_usec * 1000;
	vap->va_ctime.ts_sec = fxdr_unsigned(long, fp->fa_ctime.tv_sec);
	vap->va_ctime.ts_nsec = 0;
E 62
	vap->va_gen = fxdr_unsigned(u_long, fp->fa_ctime.tv_usec);
E 71
I 44
D 63
#ifdef _NOQUAD
	vap->va_size_rsv = 0;
	vap->va_bytes_rsv = 0;
#endif
E 63
E 44
E 15
E 4
	np->n_attrstamp = time.tv_sec;
I 9
D 10
	/*
	 * If v_type == VNON it is a new node, so fill in the v_type,
	 * n_mtime fields. For v_type == VCHR also set the vnode ops
	 * and v_rdev fields.
	 */
	if (vp->v_type == VNON) {
		vp->v_type = vap->va_type;
		np->n_mtime = vap->va_mtime.tv_sec;
		/*
		 * Handling special files...
		 * For VCHR, use the nfs_node, but with the nfsv2chr_vnodeops
		 * that are a mix of nfs and blk vnode ops.
		 */
		if (vp->v_type == VCHR) {
			vp->v_rdev = vap->va_rdev;
			vp->v_op = &nfsv2chr_vnodeops;
		}
	}
E 10
E 9
D 87
	*dposp = dpos;
	*mdp = md;
E 87
D 7
	if (vaper != NULL)
E 7
I 7
	if (vaper != NULL) {
E 7
		bcopy((caddr_t)vap, (caddr_t)vaper, sizeof(*vap));
I 76
D 87
#ifdef notdef
E 76
I 7
D 71
		if ((np->n_flag & NMODIFIED) && (np->n_size > vap->va_size))
E 71
I 71
D 75
		if (np->n_size > vap->va_size)
E 75
I 75
		if ((np->n_flag & NMODIFIED) && np->n_size > vap->va_size)
I 76
		if (np->n_size > vap->va_size)
E 76
E 75
E 71
			vaper->va_size = np->n_size;
I 76
#endif
E 87
E 76
I 61
		if (np->n_flag & NCHG) {
D 62
			if (np->n_flag & NACC)
				vaper->va_atime = np->n_atim;
			if (np->n_flag & NUPD)
				vaper->va_mtime = np->n_mtim;
E 62
I 62
D 87
			if (np->n_flag & NACC) {
				vaper->va_atime.ts_sec = np->n_atim.tv_sec;
				vaper->va_atime.ts_nsec =
				    np->n_atim.tv_usec * 1000;
			}
			if (np->n_flag & NUPD) {
				vaper->va_mtime.ts_sec = np->n_mtim.tv_sec;
				vaper->va_mtime.ts_nsec =
				    np->n_mtim.tv_usec * 1000;
			}
E 87
I 87
			if (np->n_flag & NACC)
				vaper->va_atime = np->n_atim;
			if (np->n_flag & NUPD)
				vaper->va_mtime = np->n_mtim;
E 87
E 62
		}
E 61
	}
E 7
	return (0);
}

/*
 * Check the time stamp
 * If the cache is valid, copy contents to *vap and return 0
 * otherwise return an error
 */
I 87
int
E 87
D 76
nfs_getattrcache(vp, vap)
E 76
I 76
nfs_getattrcache(vp, vaper)
E 76
	register struct vnode *vp;
D 76
	struct vattr *vap;
E 76
I 76
	struct vattr *vaper;
E 76
{
D 76
	register struct nfsnode *np;
E 76
I 76
	register struct nfsnode *np = VTONFS(vp);
	register struct vattr *vap;
E 76

D 76
	np = VTONFS(vp);
E 76
D 45
	if ((time.tv_sec-np->n_attrstamp) < NFS_ATTRTIMEO) {
		nfsstats.attrcache_hits++;
		bcopy((caddr_t)&np->n_vattr,(caddr_t)vap,sizeof(struct vattr));
I 7
D 9
		if ((np->n_flag & NMODIFIED) && (np->n_size > vap->va_size))
E 9
I 9
D 33
		if ((np->n_flag & NMODIFIED) == 0)
E 33
I 33
		if ((np->n_flag & NMODIFIED) == 0) {
E 33
			np->n_size = vap->va_size;
I 34
D 40
#ifdef NVM
E 40
E 34
D 33
		else if (np->n_size > vap->va_size)
E 33
I 33
			vnode_pager_setsize(vp, np->n_size);
I 34
D 40
#endif
E 40
E 34
		} else if (np->n_size > vap->va_size)
E 33
E 9
			vap->va_size = np->n_size;
E 7
		return (0);
	} else {
E 45
I 45
D 71
	if (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS) {
E 71
I 71
D 87
	if (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQLOOKLEASE) {
E 71
		if (!NQNFS_CKCACHABLE(vp, NQL_READ) || np->n_attrstamp == 0) {
			nfsstats.attrcache_misses++;
			return (ENOENT);
		}
D 71
	} else if ((time.tv_sec - np->n_attrstamp) >= NFS_ATTRTIMEO) {
E 71
I 71
	} else if ((time.tv_sec - np->n_attrstamp) >= NFS_ATTRTIMEO(np)) {
E 87
I 87
	if ((time.tv_sec - np->n_attrstamp) >= NFS_ATTRTIMEO(np)) {
E 87
E 71
E 45
		nfsstats.attrcache_misses++;
		return (ENOENT);
	}
I 45
	nfsstats.attrcache_hits++;
D 76
	bcopy((caddr_t)&np->n_vattr,(caddr_t)vap,sizeof(struct vattr));
E 76
I 76
	vap = &np->n_vattr;
	if (vap->va_size != np->n_size) {
		if (vap->va_type == VREG) {
			if (np->n_flag & NMODIFIED) {
				if (vap->va_size < np->n_size)
					vap->va_size = np->n_size;
				else
					np->n_size = vap->va_size;
			} else
				np->n_size = vap->va_size;
			vnode_pager_setsize(vp, (u_long)np->n_size);
		} else
			np->n_size = vap->va_size;
	}
	bcopy((caddr_t)vap, (caddr_t)vaper, sizeof(struct vattr));
D 87
#ifdef notdef
E 76
D 71
	if ((np->n_flag & NMODIFIED) == 0) {
E 71
I 71
D 75
	if (vap->va_size > np->n_size) {
E 75
I 75
	if ((np->n_flag & NMODIFIED) == 0) {
E 75
E 71
D 76
		np->n_size = vap->va_size;
E 76
I 76
		np->n_size = vaper->va_size;
E 76
D 49
		vnode_pager_setsize(vp, np->n_size);
E 49
I 49
		vnode_pager_setsize(vp, (u_long)np->n_size);
E 49
D 76
	} else if (np->n_size > vap->va_size)
		vap->va_size = np->n_size;
E 76
I 76
	} else if (np->n_size > vaper->va_size)
	if (np->n_size > vaper->va_size)
		vaper->va_size = np->n_size;
#endif
E 87
E 76
I 61
	if (np->n_flag & NCHG) {
D 62
		if (np->n_flag & NACC)
			vap->va_atime = np->n_atim;
		if (np->n_flag & NUPD)
			vap->va_mtime = np->n_mtim;
E 62
I 62
D 87
		if (np->n_flag & NACC) {
D 76
			vap->va_atime.ts_sec = np->n_atim.tv_sec;
			vap->va_atime.ts_nsec = np->n_atim.tv_usec * 1000;
E 76
I 76
			vaper->va_atime.ts_sec = np->n_atim.tv_sec;
			vaper->va_atime.ts_nsec = np->n_atim.tv_usec * 1000;
E 76
		}
		if (np->n_flag & NUPD) {
D 76
			vap->va_mtime.ts_sec = np->n_mtim.tv_sec;
			vap->va_mtime.ts_nsec = np->n_mtim.tv_usec * 1000;
E 76
I 76
			vaper->va_mtime.ts_sec = np->n_mtim.tv_sec;
			vaper->va_mtime.ts_nsec = np->n_mtim.tv_usec * 1000;
E 76
		}
E 87
I 87
		if (np->n_flag & NACC)
			vaper->va_atime = np->n_atim;
		if (np->n_flag & NUPD)
			vaper->va_mtime = np->n_mtim;
E 87
E 62
	}
E 61
	return (0);
E 45
}

D 3
#ifndef OPFLAG
#define	OPFLAG	(CREATE | DELETE | LOOKUP)
#endif

E 3
/*
D 24
 * nfs_namei - a liitle like namei(), but for one element only
 *	essentially look up file handle, fill in ndp and call VOP_LOOKUP()
E 24
I 24
D 45
 * Set up nameidata for a namei() call and do it
E 45
I 45
 * Set up nameidata for a lookup() call and do it
E 45
E 24
 */
D 41
nfs_namei(ndp, fhp, len, mdp, dposp)
E 41
I 41
D 45
nfs_namei(ndp, fhp, len, mdp, dposp, p)
E 45
I 45
D 87
nfs_namei(ndp, fhp, len, slp, nam, mdp, dposp, p)
E 87
I 87
int
nfs_namei(ndp, fhp, len, slp, nam, mdp, dposp, retdirp, p, kerbflag)
E 87
E 45
E 41
	register struct nameidata *ndp;
	fhandle_t *fhp;
	int len;
I 45
	struct nfssvc_sock *slp;
	struct mbuf *nam;
E 45
	struct mbuf **mdp;
	caddr_t *dposp;
I 87
	struct vnode **retdirp;
E 87
I 41
	struct proc *p;
I 87
	int kerbflag;
E 87
E 41
{
	register int i, rem;
	register struct mbuf *md;
D 41
	register char *cp;
E 41
I 41
	register char *fromcp, *tocp;
E 41
D 22
	struct vnode *dp = (struct vnode *)0;
E 22
I 22
D 24
	struct vnode *dp = NULLVP;
E 24
I 24
D 35
	struct vnode *dp;
E 35
I 35
D 36
	register struct filedesc *fdp = u.u_procp->p_fd;	/* XXX */
	struct vnode *dp, *savedcdir, *savedrdir;
E 36
I 36
	struct vnode *dp;
E 36
E 35
E 24
E 22
D 12
	struct vnode *tdp;
	struct mount *mp;
E 12
D 45
	int flag;
D 24
	int docache;
	int wantparent;
	int lockparent;
D 12
	int rootflg = 0;
E 12
	int error = 0;
E 24
I 24
	int error;
E 45
I 45
D 47
	int flag, error, rdonly;
E 47
I 47
	int error, rdonly;
	struct componentname *cnp = &ndp->ni_cnd;
E 47
E 45
E 24

I 87
	*retdirp = (struct vnode *)0;
E 87
D 22
	ndp->ni_vp = ndp->ni_dvp = (struct vnode *)0;
E 22
I 22
D 24
	ndp->ni_vp = ndp->ni_dvp = NULLVP;
E 24
E 22
D 25
	flag = ndp->ni_nameiop & OPFLAG;
D 24
	wantparent = ndp->ni_nameiop & (LOCKPARENT | WANTPARENT);
	lockparent = ndp->ni_nameiop & LOCKPARENT;
	docache = (ndp->ni_nameiop & NOCACHE) ^ NOCACHE;
	if (flag == DELETE || wantparent)
		docache = 0;

	/* Fill in the nameidata and call lookup */
E 24
I 24
	/*
	 * Copy the name from the mbuf list to the d_name field of ndp
	 * and set the various ndp fields appropriately.
	 */
E 24
	cp = *dposp;
	md = *mdp;
	rem = mtod(md, caddr_t)+md->m_len-cp;
	ndp->ni_hash = 0;
	for (i = 0; i < len;) {
D 24
		if (rem == 0) {
E 24
I 24
		while (rem == 0) {
E 24
			md = md->m_next;
			if (md == NULL)
				return (EBADRPC);
			cp = mtod(md, caddr_t);
			rem = md->m_len;
		}
		if (*cp == '\0' || *cp == '/')
			return (EINVAL);
		if (*cp & 0200)
			if ((*cp&0377) == ('/'|0200) || flag != DELETE)
E 25
I 25
D 41
	if ((ndp->ni_nameiop & HASBUF) == 0) {
D 36
		flag = ndp->ni_nameiop & OPFLAG;
E 36
I 36
		flag = ndp->ni_nameiop & OPMASK;
E 36
		/*
		 * Copy the name from the mbuf list to the d_name field of ndp
		 * and set the various ndp fields appropriately.
		 */
		cp = *dposp;
		md = *mdp;
		rem = mtod(md, caddr_t)+md->m_len-cp;
		ndp->ni_hash = 0;
		for (i = 0; i < len;) {
			while (rem == 0) {
				md = md->m_next;
				if (md == NULL)
					return (EBADRPC);
				cp = mtod(md, caddr_t);
				rem = md->m_len;
E 41
I 41
D 47
	flag = ndp->ni_nameiop & OPMASK;
	MALLOC(ndp->ni_pnbuf, char *, len + 1, M_NAMEI, M_WAITOK);
E 47
I 47
	MALLOC(cnp->cn_pnbuf, char *, len + 1, M_NAMEI, M_WAITOK);
E 47
	/*
	 * Copy the name from the mbuf list to ndp->ni_pnbuf
	 * and set the various ndp fields appropriately.
	 */
	fromcp = *dposp;
D 47
	tocp = ndp->ni_pnbuf;
E 47
I 47
	tocp = cnp->cn_pnbuf;
E 47
	md = *mdp;
	rem = mtod(md, caddr_t) + md->m_len - fromcp;
D 47
	ndp->ni_hash = 0;
E 47
I 47
	cnp->cn_hash = 0;
E 47
	for (i = 0; i < len; i++) {
		while (rem == 0) {
			md = md->m_next;
			if (md == NULL) {
				error = EBADRPC;
				goto out;
E 41
			}
D 41
			if (*cp == '\0' || *cp == '/')
E 25
				return (EINVAL);
D 25
		ndp->ni_dent.d_name[i++] = *cp;
		ndp->ni_hash += (unsigned char)*cp * i;
		cp++;
		rem--;
	}
	*mdp = md;
I 24
	*dposp = cp;
E 24
	len = nfsm_rndup(len)-len;
D 24
	if (len > 0)
		*dposp = cp+len;
	else
		*dposp = cp;
E 24
I 24
	if (len > 0) {
		if (rem < len) {
			if (error = nfs_adv(mdp, dposp, len, rem))
				return (error);
		} else
			*dposp += len;
	}
E 25
I 25
			if (*cp & 0200)
				if ((*cp&0377) == ('/'|0200) || flag != DELETE)
					return (EINVAL);
			ndp->ni_dent.d_name[i++] = *cp;
			ndp->ni_hash += (unsigned char)*cp * i;
			cp++;
			rem--;
E 41
I 41
			fromcp = mtod(md, caddr_t);
			rem = md->m_len;
E 41
		}
D 41
		*mdp = md;
		*dposp = cp;
		len = nfsm_rndup(len)-len;
		if (len > 0) {
			if (rem < len) {
				if (error = nfs_adv(mdp, dposp, len, rem))
					return (error);
			} else
				*dposp += len;
E 41
I 41
		if (*fromcp == '\0' || *fromcp == '/') {
D 87
			error = EINVAL;
E 87
I 87
			error = EACCES;
E 87
			goto out;
E 41
		}
D 41
	} else
		i = len;
E 25
E 24
	ndp->ni_namelen = i;
	ndp->ni_dent.d_namlen = i;
	ndp->ni_dent.d_name[i] = '\0';
I 25
	ndp->ni_segflg = UIO_SYSSPACE;
E 25
D 3
	ndp->ni_pathlen = 0;
E 3
I 3
	ndp->ni_pathlen = 1;
E 3
D 24
	ndp->ni_dirp = ndp->ni_ptr = &ndp->ni_dent.d_name[0];
E 24
I 24
	ndp->ni_pnbuf = ndp->ni_dirp = ndp->ni_ptr = &ndp->ni_dent.d_name[0];
E 24
	ndp->ni_next = &ndp->ni_dent.d_name[i];
D 24
	ndp->ni_loopcnt = 0;	/* Not actually used for now */
	ndp->ni_endoff = 0;
	if (docache)
		ndp->ni_makeentry = 1;
	else
		ndp->ni_makeentry = 0;
	ndp->ni_isdotdot = (i == 2 && 
		ndp->ni_dent.d_name[1] == '.' && ndp->ni_dent.d_name[0] == '.');
E 24
I 24
D 36
	ndp->ni_nameiop |= (NOCROSSMOUNT | REMOTE | HASBUF);
E 24

E 36
I 36
	ndp->ni_nameiop |= (NOCROSSMOUNT | REMOTE | HASBUF | STARTDIR);
E 41
I 41
D 77
		if (*fromcp & 0200)
D 47
			if ((*fromcp&0377) == ('/'|0200) || flag != DELETE) {
E 47
I 47
			if ((*fromcp&0377) == ('/'|0200) || cnp->cn_nameiop != DELETE) {
E 47
				error = EINVAL;
				goto out;
			}
E 77
D 47
		ndp->ni_hash += (unsigned char)*fromcp;
E 47
I 47
		cnp->cn_hash += (unsigned char)*fromcp;
E 47
		*tocp++ = *fromcp++;
		rem--;
	}
	*tocp = '\0';
	*mdp = md;
	*dposp = fromcp;
	len = nfsm_rndup(len)-len;
	if (len > 0) {
		if (rem >= len)
			*dposp += len;
		else if (error = nfs_adv(mdp, dposp, len, rem))
			goto out;
	}
D 47
	ndp->ni_pathlen = tocp - ndp->ni_pnbuf;
	ndp->ni_ptr = ndp->ni_pnbuf;
E 47
I 47
	ndp->ni_pathlen = tocp - cnp->cn_pnbuf;
	cnp->cn_nameptr = cnp->cn_pnbuf;
E 47
E 41
	/*
	 * Extract and set starting directory.
	 */
E 36
D 3
	/*
	 * Must remember if this is root so that cr_uid can be set to
	 * mp->m_exroot at mount points
	 * Then call nfsrv_fhtovp() to get the locked directory vnode
	 */
	if (ndp->ni_cred->cr_uid == 0)
		rootflg++;
E 3
D 24
	if (error = nfsrv_fhtovp(fhp, TRUE, &dp, ndp->ni_cred))
E 24
I 24
D 45
	if (error = nfsrv_fhtovp(fhp, FALSE, &dp, ndp->ni_cred))
E 45
I 45
D 47
	if (error = nfsrv_fhtovp(fhp, FALSE, &dp, ndp->ni_cred, slp, nam, &rdonly))
E 47
I 47
	if (error = nfsrv_fhtovp(fhp, FALSE, &dp, ndp->ni_cnd.cn_cred, slp,
D 87
	    nam, &rdonly))
E 87
I 87
	    nam, &rdonly, kerbflag))
E 87
E 47
E 45
E 24
D 41
		return (error);
E 41
I 41
		goto out;
E 41
I 3
	if (dp->v_type != VDIR) {
D 24
		vput(dp);
E 24
I 24
		vrele(dp);
E 24
D 41
		return (ENOTDIR);
E 41
I 41
		error = ENOTDIR;
		goto out;
E 41
	}
I 87
	VREF(dp);
	*retdirp = dp;
E 87
I 36
	ndp->ni_startdir = dp;
I 41
D 45
	ndp->ni_nameiop |= (NOCROSSMOUNT | REMOTE);
E 45
I 45
	if (rdonly)
D 47
		ndp->ni_nameiop |= (NOCROSSMOUNT | RDONLY);
E 47
I 47
		cnp->cn_flags |= (NOCROSSMOUNT | RDONLY);
E 47
	else
D 47
		ndp->ni_nameiop |= NOCROSSMOUNT;
E 47
I 47
		cnp->cn_flags |= NOCROSSMOUNT;
E 47
E 45
E 41
E 36
I 8
	/*
D 36
	 * Must set current directory here to avoid confusion in namei()
	 * called from rename()
	 */
E 8
D 35
	ndp->ni_cdir = dp;
D 22
	ndp->ni_rdir = (struct vnode *)0;
E 22
I 22
	ndp->ni_rdir = NULLVP;
E 35
I 35
	savedcdir = fdp->fd_cdir;
	savedrdir = fdp->fd_rdir;
	fdp->fd_cdir = dp;
	fdp->fd_rdir = NULLVP;
E 35
E 22
E 3

	/*
E 36
D 3
	 * Handle "..": two special cases.
	 * 1. If at root directory (e.g. after chroot)
	 *    then ignore it so can't get out.
	 * 2. If this vnode is the root of a mounted
	 *    file system, then replace it with the
	 *    vnode which was mounted on so we take the
	 *    .. in the other file system.
E 3
I 3
D 24
	 * Handle "..":
	 * If this vnode is the root of the mounted
	 *    file system, then ignore it so can't get out
E 24
I 24
D 41
	 * And call namei() to do the real work
E 41
I 41
	 * And call lookup() to do the real work
E 41
E 24
E 3
	 */
D 3
	if (ndp->ni_isdotdot) {
		for (;;) {
			if (dp == rootdir) {
				ndp->ni_dvp = dp;
				dp->v_count++;
				goto nextname;
			}
			if ((dp->v_flag & VROOT) == 0)
				break;
			tdp = dp;
			dp = dp->v_mount->m_vnodecovered;
			vput(tdp);
			if ((dp->v_mount->m_flag & M_EXPORTED) == 0)
				return (EACCES);
			VOP_LOCK(dp);
			dp->v_count++;
			if (rootflg)
				ndp->ni_cred->cr_uid = dp->v_mount->m_exroot;
		}
E 3
I 3
D 24
	if (ndp->ni_isdotdot && (dp->v_flag & VROOT)) {
		ndp->ni_dvp = dp;
		ndp->ni_vp = dp;
		VREF(dp);
		goto nextname;
E 3
	}

	/*
	 * We now have a segment name to search for, and a directory to search.
	 */
	if (error = VOP_LOOKUP(dp, ndp)) {
		if (ndp->ni_vp != NULL)
			panic("leaf should be empty");
		/*
		 * If creating and at end of pathname, then can consider
		 * allowing file to be created.
		 */
D 22
		if (ndp->ni_dvp->v_mount->m_flag & (M_RDONLY | M_EXRDONLY))
E 22
I 22
		if (ndp->ni_dvp->v_mount->mnt_flag & (MNT_RDONLY|MNT_EXRDONLY))
E 22
			error = EROFS;
		if (flag == LOOKUP || flag == DELETE || error != ENOENT)
			goto bad;
		/*
		 * We return with ni_vp NULL to indicate that the entry
		 * doesn't currently exist, leaving a pointer to the
		 * (possibly locked) directory inode in ndp->ni_dvp.
		 */
		return (0);	/* should this be ENOENT? */
	}

D 3
	/*
	 * Check for symbolic link
	 */
E 3
	dp = ndp->ni_vp;
D 3
#ifdef notdef
	if ((dp->v_type == VLNK) &&
	    (ndp->ni_nameiop & FOLLOW)) {
		struct iovec aiov;
		struct uio auio;
		int linklen;
E 3

D 3
		if (++ndp->ni_loopcnt > MAXSYMLINKS) {
			error = ELOOP;
			goto bad2;
		}
		MALLOC(cp, char *, MAXPATHLEN, M_NAMEI, M_WAITOK);
		aiov.iov_base = cp;
		aiov.iov_len = MAXPATHLEN;
		auio.uio_iov = &aiov;
		auio.uio_iovcnt = 1;
		auio.uio_offset = 0;
		auio.uio_rw = UIO_READ;
		auio.uio_segflg = UIO_SYSSPACE;
		auio.uio_resid = MAXPATHLEN;
		if (error = VOP_READLINK(dp, &auio, ndp->ni_cred)) {
			free(cp, M_NAMEI);
			goto bad2;
		}
		linklen = MAXPATHLEN - auio.uio_resid;
		if (linklen + ndp->ni_pathlen >= MAXPATHLEN) {
			free(cp, M_NAMEI);
			error = ENAMETOOLONG;
			goto bad2;
		}
		bcopy(ndp->ni_next, cp + linklen, ndp->ni_pathlen);
		ndp->ni_pnbuf = cp;
		} else
			ndp->ni_pnbuf[linklen] = '\0';
		ndp->ni_ptr = cp;
		ndp->ni_pathlen += linklen;
		vput(dp);
		dp = ndp->ni_dvp;
		goto start;
	}
#endif

	/*
	 * Check to see if the vnode has been mounted on;
	 * if so find the root of the mounted file system.
	 * Ignore NFS mount points
	 */
mntloop:
	while (dp->v_type == VDIR && (mp = dp->v_mountedhere) &&
		mp->m_fsid.val[1] != MOUNT_NFS) {
		while(mp->m_flag & M_MLOCK) {
			mp->m_flag |= M_MWAIT;
			sleep((caddr_t)mp, PVFS);
			goto mntloop;
		}
		error = VFS_ROOT(mp, &tdp);
		if (error || (mp->m_flag & M_EXPORTED) == 0)
			goto bad2;
		vput(dp);
		ndp->ni_vp = dp = tdp;
		if (rootflg)
			ndp->ni_cred->cr_uid = mp->m_exroot;
	}

E 3
nextname:
I 3
	ndp->ni_ptr = ndp->ni_next;
E 3
	/*
D 2
	 * Check for read-only file systems and executing texts
E 2
I 2
D 3
	 * Check for read-only file systems.
E 3
I 3
	 * Check for read-only file systems
E 3
E 2
	 */
D 2
	if (flag != LOOKUP && ((dp->v_mount->m_flag & (M_RDONLY | M_EXRDONLY)) ||
		(error = vn_access(dp, VWRITE, ndp->ni_cred))))
		goto bad2;
E 2
I 2
	if (flag == DELETE || flag == RENAME) {
		/*
		 * Disallow directory write attempts on read-only
		 * file systems.
		 */
D 22
		if ((dp->v_mount->m_flag & (M_RDONLY|M_EXRDONLY)) ||
D 3
		    (wantparent && (ndp->ni_dvp->v_mount->m_flag & M_RDONLY))) {
E 3
I 3
		    (wantparent && (ndp->ni_dvp->v_mount->m_flag & (M_RDONLY|M_EXRDONLY)))) {
E 22
I 22
		if ((dp->v_mount->mnt_flag & (MNT_RDONLY|MNT_EXRDONLY)) ||
		    (wantparent &&
		    (ndp->ni_dvp->v_mount->mnt_flag &
		     (MNT_RDONLY|MNT_EXRDONLY)))) {
E 22
E 3
			error = EROFS;
			goto bad2;
		}
	}
E 2

D 3
	/*
	 * Kludge city... This is hokey, but since ufs_rename() calls
	 * namei() and namei() expects ni_cdir to be set, what can I
	 * do. Fortunately rename() holds onto the parent so I don't
	 * have to increment the v_count.
	 */
E 3
	if (!wantparent)
		vrele(ndp->ni_dvp);
D 3
	else
		ndp->ni_cdir = ndp->ni_dvp;
E 3

	if ((ndp->ni_nameiop & LOCKLEAF) == 0)
		VOP_UNLOCK(dp);
	return (0);

bad2:
	if (lockparent)
		VOP_UNLOCK(ndp->ni_dvp);
	vrele(ndp->ni_dvp);
bad:
	vput(dp);
	ndp->ni_vp = NULL;
E 24
I 24
D 39
	error = namei(ndp);
E 39
I 39
D 41
	error = namei(ndp, curproc);		/* XXX XXX XXX */
E 39
I 35
D 36
	fdp->fd_cdir = savedcdir;
	fdp->fd_rdir = savedrdir;
E 35
	vrele(dp);
E 36
I 36
	if (error || (ndp->ni_nameiop & SAVESTARTDIR) == 0)
		vrele(dp);
E 41
I 41
D 47
	if (error = lookup(ndp, p))
E 47
I 47
	cnp->cn_proc = p;
	if (error = lookup(ndp))
E 47
		goto out;
	/*
	 * Check for encountering a symbolic link
	 */
D 46
	if (ndp->ni_more) {
E 46
I 46
D 47
	if (ndp->ni_nameiop & ISSYMLINK) {
E 46
		if ((ndp->ni_nameiop & LOCKPARENT) && ndp->ni_pathlen == 1)
E 47
I 47
	if (cnp->cn_flags & ISSYMLINK) {
		if ((cnp->cn_flags & LOCKPARENT) && ndp->ni_pathlen == 1)
E 47
			vput(ndp->ni_dvp);
		else
			vrele(ndp->ni_dvp);
		vput(ndp->ni_vp);
		ndp->ni_vp = NULL;
		error = EINVAL;
		goto out;
	}
	/*
	 * Check for saved name request
	 */
D 47
	if (ndp->ni_nameiop & (SAVENAME | SAVESTART)) {
		ndp->ni_nameiop |= HASBUF;
E 47
I 47
	if (cnp->cn_flags & (SAVENAME | SAVESTART)) {
		cnp->cn_flags |= HASBUF;
E 47
		return (0);
	}
out:
D 47
	FREE(ndp->ni_pnbuf, M_NAMEI);
E 47
I 47
	FREE(cnp->cn_pnbuf, M_NAMEI);
E 47
E 41
E 36
E 24
	return (error);
}

/*
 * A fiddled version of m_adj() that ensures null fill to a long
 * boundary and only trims off the back end
 */
I 45
void
E 45
nfsm_adj(mp, len, nul)
	struct mbuf *mp;
	register int len;
	int nul;
{
	register struct mbuf *m;
	register int count, i;
	register char *cp;

	/*
	 * Trim from tail.  Scan the mbuf chain,
	 * calculating its length and finding the last mbuf.
	 * If the adjustment only affects this mbuf, then just
	 * adjust and return.  Otherwise, rescan and truncate
	 * after the remaining size.
	 */
	count = 0;
	m = mp;
	for (;;) {
		count += m->m_len;
		if (m->m_next == (struct mbuf *)0)
			break;
		m = m->m_next;
	}
D 4
	if (m->m_len >= len) {
E 4
I 4
	if (m->m_len > len) {
E 4
		m->m_len -= len;
		if (nul > 0) {
			cp = mtod(m, caddr_t)+m->m_len-nul;
			for (i = 0; i < nul; i++)
				*cp++ = '\0';
		}
		return;
	}
	count -= len;
	if (count < 0)
		count = 0;
	/*
	 * Correct length for chain is "count".
	 * Find the mbuf with last data, adjust its length,
	 * and toss data from remaining mbufs on chain.
	 */
	for (m = mp; m; m = m->m_next) {
		if (m->m_len >= count) {
			m->m_len = count;
			if (nul > 0) {
				cp = mtod(m, caddr_t)+m->m_len-nul;
				for (i = 0; i < nul; i++)
					*cp++ = '\0';
			}
			break;
		}
		count -= m->m_len;
	}
D 87
	while (m = m->m_next)
E 87
I 87
	for (m = m->m_next;m;m = m->m_next)
E 87
		m->m_len = 0;
}

/*
I 87
 * Make these functions instead of macros, so that the kernel text size
 * doesn't get too big...
 */
void
nfsm_srvwcc(nfsd, before_ret, before_vap, after_ret, after_vap, mbp, bposp)
	struct nfsrv_descript *nfsd;
	int before_ret;
	register struct vattr *before_vap;
	int after_ret;
	struct vattr *after_vap;
	struct mbuf **mbp;
	char **bposp;
{
	register struct mbuf *mb = *mbp, *mb2;
	register char *bpos = *bposp;
	register u_long *tl;

	if (before_ret) {
		nfsm_build(tl, u_long *, NFSX_UNSIGNED);
		*tl = nfs_false;
	} else {
		nfsm_build(tl, u_long *, 7 * NFSX_UNSIGNED);
		*tl++ = nfs_true;
		txdr_hyper(&(before_vap->va_size), tl);
		tl += 2;
		txdr_nfsv3time(&(before_vap->va_mtime), tl);
		tl += 2;
		txdr_nfsv3time(&(before_vap->va_ctime), tl);
	}
	*bposp = bpos;
	*mbp = mb;
	nfsm_srvpostopattr(nfsd, after_ret, after_vap, mbp, bposp);
}

void
nfsm_srvpostopattr(nfsd, after_ret, after_vap, mbp, bposp)
	struct nfsrv_descript *nfsd;
	int after_ret;
	struct vattr *after_vap;
	struct mbuf **mbp;
	char **bposp;
{
	register struct mbuf *mb = *mbp, *mb2;
	register char *bpos = *bposp;
	register u_long *tl;
	register struct nfs_fattr *fp;

	if (after_ret) {
		nfsm_build(tl, u_long *, NFSX_UNSIGNED);
		*tl = nfs_false;
	} else {
		nfsm_build(tl, u_long *, NFSX_UNSIGNED + NFSX_V3FATTR);
		*tl++ = nfs_true;
		fp = (struct nfs_fattr *)tl;
		nfsm_srvfattr(nfsd, after_vap, fp);
	}
	*mbp = mb;
	*bposp = bpos;
}

void
nfsm_srvfattr(nfsd, vap, fp)
	register struct nfsrv_descript *nfsd;
	register struct vattr *vap;
	register struct nfs_fattr *fp;
{

	fp->fa_nlink = txdr_unsigned(vap->va_nlink);
	fp->fa_uid = txdr_unsigned(vap->va_uid);
	fp->fa_gid = txdr_unsigned(vap->va_gid);
	if (nfsd->nd_flag & ND_NFSV3) {
		fp->fa_type = vtonfsv3_type(vap->va_type);
		fp->fa_mode = vtonfsv3_mode(vap->va_mode);
		txdr_hyper(&vap->va_size, &fp->fa3_size);
		txdr_hyper(&vap->va_bytes, &fp->fa3_used);
		fp->fa3_rdev.specdata1 = txdr_unsigned(major(vap->va_rdev));
		fp->fa3_rdev.specdata2 = txdr_unsigned(minor(vap->va_rdev));
		fp->fa3_fsid.nfsuquad[0] = 0;
		fp->fa3_fsid.nfsuquad[1] = txdr_unsigned(vap->va_fsid);
		fp->fa3_fileid.nfsuquad[0] = 0;
		fp->fa3_fileid.nfsuquad[1] = txdr_unsigned(vap->va_fileid);
		txdr_nfsv3time(&vap->va_atime, &fp->fa3_atime);
		txdr_nfsv3time(&vap->va_mtime, &fp->fa3_mtime);
		txdr_nfsv3time(&vap->va_ctime, &fp->fa3_ctime);
	} else {
		fp->fa_type = vtonfsv2_type(vap->va_type);
		fp->fa_mode = vtonfsv2_mode(vap->va_type, vap->va_mode);
		fp->fa2_size = txdr_unsigned(vap->va_size);
		fp->fa2_blocksize = txdr_unsigned(vap->va_blocksize);
		if (vap->va_type == VFIFO)
			fp->fa2_rdev = 0xffffffff;
		else
			fp->fa2_rdev = txdr_unsigned(vap->va_rdev);
		fp->fa2_blocks = txdr_unsigned(vap->va_bytes / NFS_FABLKSIZE);
		fp->fa2_fsid = txdr_unsigned(vap->va_fsid);
		fp->fa2_fileid = txdr_unsigned(vap->va_fileid);
		txdr_nfsv2time(&vap->va_atime, &fp->fa2_atime);
		txdr_nfsv2time(&vap->va_mtime, &fp->fa2_mtime);
		txdr_nfsv2time(&vap->va_ctime, &fp->fa2_ctime);
	}
}

/*
E 87
 * nfsrv_fhtovp() - convert a fh to a vnode ptr (optionally locked)
 * 	- look up fsid in mount list (if not found ret error)
D 66
 *	- check that it is exported
 *	- get vp by calling VFS_FHTOVP() macro
E 66
I 66
 *	- get vp and export rights by calling VFS_FHTOVP()
 *	- if cred->cr_uid == 0 or MNT_EXPORTANON set it to credanon
E 66
 *	- if not lockflag unlock it with VOP_UNLOCK()
D 22
 *	- if cred->cr_uid == 0 set it to m_exroot
E 22
I 22
D 24
 *	- if cred->cr_uid == 0 set it to mnt_exroot
E 24
I 24
D 45
 *	- if cred->cr_uid == 0 set it to m_exroot
E 45
I 45
D 66
 *	- if cred->cr_uid == 0 or MNT_EXPORTANON set it to neth_anon
E 66
E 45
E 24
E 22
 */
D 45
nfsrv_fhtovp(fhp, lockflag, vpp, cred)
E 45
I 45
D 87
nfsrv_fhtovp(fhp, lockflag, vpp, cred, slp, nam, rdonlyp)
E 87
I 87
int
nfsrv_fhtovp(fhp, lockflag, vpp, cred, slp, nam, rdonlyp, kerbflag)
E 87
E 45
	fhandle_t *fhp;
	int lockflag;
	struct vnode **vpp;
	struct ucred *cred;
I 45
	struct nfssvc_sock *slp;
	struct mbuf *nam;
	int *rdonlyp;
I 87
	int kerbflag;
E 87
E 45
{
I 88
	struct proc *p = curproc;	/* XXX */
E 88
I 60
D 65
	USES_VOP_UNLOCK;
E 65
E 60
	register struct mount *mp;
I 45
D 66
	register struct netaddrhash *np;
	register struct ufsmount *ump;
E 66
	register struct nfsuid *uidp;
I 76
	register int i;
E 76
D 66
	struct sockaddr *saddr;
	int error;
E 66
I 66
	struct ucred *credanon;
	int error, exflags;
E 66
E 45
D 12
	int error;
E 12

I 45
	*vpp = (struct vnode *)0;
E 45
D 87
	if ((mp = getvfs(&fhp->fh_fsid)) == NULL)
E 87
I 87
	mp = vfs_getvfs(&fhp->fh_fsid);
	if (!mp)
E 87
		return (ESTALE);
D 22
	if ((mp->m_flag & M_EXPORTED) == 0)
E 22
I 22
D 66
	if ((mp->mnt_flag & MNT_EXPORTED) == 0)
E 22
		return (EACCES);
D 45
	if (VFS_FHTOVP(mp, &fhp->fh_fid, vpp))
		return (ESTALE);
	if (cred->cr_uid == 0)
D 22
		cred->cr_uid = mp->m_exroot;
E 22
I 22
		cred->cr_uid = mp->mnt_exroot;
E 22
	if (!lockflag)
		VOP_UNLOCK(*vpp);
	return (0);
I 30
}
E 45

E 66
I 66
D 87
	if (error = VFS_FHTOVP(mp, &fhp->fh_fid, nam, vpp, &exflags, &credanon))
E 87
I 87
	error = VFS_FHTOVP(mp, &fhp->fh_fid, nam, vpp, &exflags, &credanon);
	if (error)
E 87
		return (error);
E 66
D 45
/*
 * These two functions implement nfs rpc compression.
 * The algorithm is a trivial run length encoding of '\0' bytes. The high
 * order nibble of hex "e" is or'd with the number of zeroes - 2 in four
 * bits. (2 - 17 zeros) Any data byte with a high order nibble of hex "e"
 * is byte stuffed.
 * The compressed data is padded with 0x0 bytes to an even multiple of
 * 4 bytes in length to avoid any weird long pointer alignments.
 * If compression/uncompression is unsuccessful, the original mbuf list
 * is returned.
 * The first four bytes (the XID) are left uncompressed and the fifth
 * byte is set to 0x1 for request and 0x2 for reply.
 * An uncompressed RPC will always have the fifth byte == 0x0.
 */
struct mbuf *
nfs_compress(m0)
	struct mbuf *m0;
{
	register u_char ch, nextch;
	register int i, rlelast;
	register u_char *ip, *op;
	register int ileft, oleft, noteof;
	register struct mbuf *m, *om;
	struct mbuf **mp, *retm;
	int olen, clget;
E 45
I 45
	/*
D 66
	 * Get the export permission structure for this <mp, client> tuple.
	 */
	ump = VFSTOUFS(mp);
	if (nam) {
E 45

D 45
	i = rlelast = 0;
	noteof = 1;
	m = m0;
	if (m->m_len < 12)
		return (m0);
	if (m->m_pkthdr.len >= MINCLSIZE)
		clget = 1;
	else
		clget = 0;
	ileft = m->m_len - 9;
	ip = mtod(m, u_char *);
D 31
	MGETHDR(om, MT_DATA, M_WAIT);
E 31
I 31
	MGETHDR(om, M_WAIT, MT_DATA);
E 31
	if (clget)
		MCLGET(om, M_WAIT);
	retm = om;
	mp = &om->m_next;
	olen = om->m_len = 5;
	oleft = M_TRAILINGSPACE(om);
	op = mtod(om, u_char *);
D 31
	*((u_long *)op) = *((u_long *)ip);
E 31
I 31
D 32
	bcopy(ip, op, sizeof(u_long));
E 32
I 32
	*((u_long *)op) = *((u_long *)ip);
E 32
E 31
	ip += 7;
	op += 4;
	*op++ = *ip++ + 1;
	nextch = *ip++;
	while (noteof) {
		ch = nextch;
		if (ileft == 0) {
			do {
				m = m->m_next;
			} while (m && m->m_len == 0);
			if (m) {
				ileft = m->m_len;
				ip = mtod(m, u_char *);
			} else {
				noteof = 0;
				nextch = 0x1;
				goto doit;
			}
E 45
I 45
		/*
		 * First search for a network match.
		 */
		np = ump->um_netaddr[NETMASK_HASH];
		while (np) {
D 64
		    if (nfs_netaddr_match(np->neth_family, &np->neth_haddr,
E 64
I 64
		    if (netaddr_match(np->neth_family, &np->neth_haddr,
E 64
			&np->neth_hmask, nam))
			break;
			np = np->neth_next;
E 45
		}
D 45
		nextch = *ip++;
		ileft--;
doit:
		if (ch == '\0') {
			if (++i == NFSC_MAX || nextch != '\0') {
				if (i < 2) {
					nfscput('\0');
				} else {
					if (rlelast == i) {
						nfscput('\0');
						i--;
					}
					if (NFSCRLE(i) == (nextch & 0xff)) {
						i--;
						if (i < 2) {
							nfscput('\0');
						} else {
							nfscput(NFSCRLE(i));
						}
						nfscput('\0');
						rlelast = 0;
					} else {
						nfscput(NFSCRLE(i));
						rlelast = i;
					}
				}
				i = 0;
			}
		} else {
			if ((ch & NFSCRL) == NFSCRL) {
				nfscput(ch);
			}
			nfscput(ch);
			i = rlelast = 0;
E 45
I 45

		/*
		 * If not found, try for an address match.
		 */
		if (np == (struct netaddrhash *)0) {
		    saddr = mtod(nam, struct sockaddr *);
		    np = ump->um_netaddr[NETADDRHASH(saddr)];
		    while (np) {
D 64
			if (nfs_netaddr_match(np->neth_family, &np->neth_haddr,
E 64
I 64
			if (netaddr_match(np->neth_family, &np->neth_haddr,
E 64
			    (struct netaddrhash *)0, nam))
			    break;
			np = np->neth_next;
		    }
E 45
		}
D 45
	}
	if (olen < m0->m_pkthdr.len) {
		m_freem(m0);
		if (i = (olen & 0x3)) {
			i = 4 - i;
D 32
			while (i-- > 0)
E 32
I 32
			while (i-- > 0) {
E 32
				nfscput('\0');
I 32
			}
E 32
		}
		retm->m_pkthdr.len = olen;
I 32
		retm->m_pkthdr.rcvif = (struct ifnet *)0;
E 32
		return (retm);
	} else {
		m_freem(retm);
		return (m0);
	}
}
E 45
I 45
	} else
		np = (struct netaddrhash *)0;
	if (np == (struct netaddrhash *)0) {
E 45

D 45
struct mbuf *
nfs_uncompress(m0)
	struct mbuf *m0;
{
	register u_char cp, nextcp, *ip, *op;
	register struct mbuf *m, *om;
	struct mbuf *retm, **mp;
	int i, j, noteof, clget, ileft, oleft, olen;

	m = m0;
D 32
	if (m->m_pkthdr.len < 6)
E 32
I 32
	i = 0;
	while (m && i < MINCLSIZE) {
		i += m->m_len;
		m = m->m_next;
E 45
I 45
		/*
		 * If no address match, use the default if it exists.
		 */
		if ((mp->mnt_flag & MNT_DEFEXPORTED) == 0)
			return (EACCES);
		np = &ump->um_defexported;
E 45
	}
D 45
	if (i < 6)
E 32
		return (m0);
D 32
	if (m->m_pkthdr.len >= MINCLSIZE)
E 32
I 32
	if (i >= MINCLSIZE)
E 32
		clget = 1;
	else
		clget = 0;
D 31
	MGETHDR(om, MT_DATA, M_WAIT);
E 31
I 31
D 32
	MGETHDR(om, M_WAIT, MT_DATA);
E 32
I 32
	m = m0;
	MGET(om, M_WAIT, MT_DATA);
E 32
E 31
	if (clget)
		MCLGET(om, M_WAIT);
	olen = om->m_len = 8;
	oleft = M_TRAILINGSPACE(om);
	op = mtod(om, u_char *);
	retm = om;
	mp = &om->m_next;
	if (m->m_len >= 6) {
		ileft = m->m_len - 6;
		ip = mtod(m, u_char *);
		*((u_long *)op) = *((u_long *)ip);
		bzero(op + 4, 3);
		ip += 4;
		op += 7;
		if (*ip == '\0') {
			m_freem(om);
			return (m0);
E 45
I 45

	/*
E 66
	 * Check/setup credentials.
	 */
D 66
	if (np->neth_exflags & MNT_EXKERB) {
E 66
I 66
	if (exflags & MNT_EXKERB) {
E 66
D 85
		uidp = slp->ns_uidh[NUIDHASH(cred->cr_uid)];
		while (uidp) {
E 85
I 85
D 87
		for (uidp = NUIDHASH(slp, cred->cr_uid)->lh_first; uidp != 0;
		    uidp = uidp->nu_hash.le_next) {
E 85
			if (uidp->nu_uid == cred->cr_uid)
				break;
D 85
			uidp = uidp->nu_hnext;
E 85
E 45
		}
D 45
		*op++ = *ip++ - 1;
		cp = *ip++;
	} else {
		ileft = m->m_len;
		ip = mtod(m, u_char *);
		nfscget(*op++);
		nfscget(*op++);
		nfscget(*op++);
		nfscget(*op++);
		bzero(op, 3);
		op += 3;
		nfscget(*op);
		if (*op == '\0') {
			m_freem(om);
			return (m0);
		}
		(*op)--;
		op++;
		nfscget(cp);
	}
	noteof = 1;
	while (noteof) {
		if ((cp & NFSCRL) == NFSCRL) {
			nfscget(nextcp);
			if (cp == nextcp) {
				nfscput(cp);
				goto readit;
			} else {
				i = (cp & 0xf) + 2;
				for (j = 0; j < i; j++) {
					nfscput('\0');
				}
				cp = nextcp;
			}
		} else {
			nfscput(cp);
readit:
			nfscget(cp);
		}
	}
	m_freem(m0);
D 32
	if (i = (olen & 0x3)) {
		olen -= i;
E 32
I 32
	if (i = (olen & 0x3))
E 32
		om->m_len -= i;
D 32
	}
	retm->m_pkthdr.len = olen;
E 32
	return (retm);
E 45
I 45
D 85
		if (uidp) {
D 76
			if (cred->cr_ref != 1)
				panic("nsrv fhtovp");
			*cred = uidp->nu_cr;
		} else
E 76
I 76
			cred->cr_uid = uidp->nu_cr.cr_uid;
			for (i = 0; i < uidp->nu_cr.cr_ngroups; i++)
				cred->cr_groups[i] = uidp->nu_cr.cr_groups[i];
I 84
			cred->cr_ngroups = uidp->nu_cr.cr_ngroups;
E 84
		} else {
E 85
I 85
		if (uidp == 0) {
E 87
I 87
		if (!kerbflag) {
E 87
E 85
			vput(*vpp);
E 76
D 87
			return (NQNFS_AUTHERR);
E 87
I 87
			return (NFSERR_AUTHERR | AUTH_TOOWEAK);
E 87
D 66
	} else if (cred->cr_uid == 0 || (np->neth_exflags & MNT_EXPORTANON))
		*cred = np->neth_anon;
D 63
	if (error = VFS_FHTOVP(mp, &fhp->fh_fid, 0, vpp))
E 63
I 63
	if (error = VFS_FHTOVP(mp, &fhp->fh_fid, vpp))
E 63
		return (ESTALE);
	if (np->neth_exflags & MNT_EXRDONLY)
E 66
I 66
D 76
	} else if (cred->cr_uid == 0 || (exflags & MNT_EXPORTANON))
		*cred = *credanon;
E 76
I 76
		}
I 85
D 87
		cred->cr_uid = uidp->nu_cr.cr_uid;
		for (i = 0; i < uidp->nu_cr.cr_ngroups; i++)
			cred->cr_groups[i] = uidp->nu_cr.cr_groups[i];
		cred->cr_ngroups = i;
E 87
I 87
	} else if (kerbflag) {
		vput(*vpp);
		return (NFSERR_AUTHERR | AUTH_TOOWEAK);
E 87
E 85
	} else if (cred->cr_uid == 0 || (exflags & MNT_EXPORTANON)) {
		cred->cr_uid = credanon->cr_uid;
		for (i = 0; i < credanon->cr_ngroups && i < NGROUPS; i++)
			cred->cr_groups[i] = credanon->cr_groups[i];
I 84
		cred->cr_ngroups = i;
E 84
	}
E 76
	if (exflags & MNT_EXRDONLY)
E 66
		*rdonlyp = 1;
	else
		*rdonlyp = 0;
	if (!lockflag)
D 88
		VOP_UNLOCK(*vpp);
E 88
I 88
		VOP_UNLOCK(*vpp, 0, p);
E 88
	return (0);
I 67
}

/*
 * This function compares two net addresses by family and returns TRUE
 * if they are the same host.
 * If there is any doubt, return FALSE.
 * The AF_INET family is handled as a special case so that address mbufs
 * don't need to be saved to store "struct in_addr", which is only 4 bytes.
 */
I 87
int
E 87
D 73
netaddr_match(family, haddr, hmask, nam)
E 73
I 73
netaddr_match(family, haddr, nam)
E 73
	int family;
	union nethostaddr *haddr;
D 73
	union nethostaddr *hmask;
E 73
	struct mbuf *nam;
{
	register struct sockaddr_in *inetaddr;
D 73
#ifdef ISO
	register struct sockaddr_iso *isoaddr1, *isoaddr2;
#endif
E 73

D 73

E 73
	switch (family) {
	case AF_INET:
		inetaddr = mtod(nam, struct sockaddr_in *);
D 73
		if (inetaddr->sin_family != AF_INET)
			return (0);
		if (hmask) {
			if ((inetaddr->sin_addr.s_addr & hmask->had_inetaddr) ==
			    (haddr->had_inetaddr & hmask->had_inetaddr))
				return (1);
		} else if (inetaddr->sin_addr.s_addr == haddr->had_inetaddr)
E 73
I 73
		if (inetaddr->sin_family == AF_INET &&
		    inetaddr->sin_addr.s_addr == haddr->had_inetaddr)
E 73
			return (1);
		break;
#ifdef ISO
	case AF_ISO:
I 73
	    {
		register struct sockaddr_iso *isoaddr1, *isoaddr2;

E 73
		isoaddr1 = mtod(nam, struct sockaddr_iso *);
D 73
		if (isoaddr1->siso_family != AF_ISO)
			return (0);
E 73
		isoaddr2 = mtod(haddr->had_nam, struct sockaddr_iso *);
D 73
		if (isoaddr1->siso_nlen > 0 &&
E 73
I 73
		if (isoaddr1->siso_family == AF_ISO &&
		    isoaddr1->siso_nlen > 0 &&
E 73
		    isoaddr1->siso_nlen == isoaddr2->siso_nlen &&
		    SAME_ISOADDR(isoaddr1, isoaddr2))
			return (1);
		break;
I 73
	    }
E 73
#endif	/* ISO */
	default:
		break;
	};
	return (0);
I 87
}

static nfsuint64 nfs_nullcookie = { 0, 0 };
/*
 * This function finds the directory cookie that corresponds to the
 * logical byte offset given.
 */
nfsuint64 *
nfs_getcookie(np, off, add)
	register struct nfsnode *np;
	off_t off;
	int add;
{
	register struct nfsdmap *dp, *dp2;
	register int pos;

	pos = off / NFS_DIRBLKSIZ;
	if (pos == 0) {
#ifdef DIAGNOSTIC
		if (add)
			panic("nfs getcookie add at 0");
#endif
		return (&nfs_nullcookie);
	}
	pos--;
	dp = np->n_cookies.lh_first;
	if (!dp) {
		if (add) {
			MALLOC(dp, struct nfsdmap *, sizeof (struct nfsdmap),
				M_NFSDIROFF, M_WAITOK);
			dp->ndm_eocookie = 0;
			LIST_INSERT_HEAD(&np->n_cookies, dp, ndm_list);
		} else
			return ((nfsuint64 *)0);
	}
	while (pos >= NFSNUMCOOKIES) {
		pos -= NFSNUMCOOKIES;
		if (dp->ndm_list.le_next) {
			if (!add && dp->ndm_eocookie < NFSNUMCOOKIES &&
				pos >= dp->ndm_eocookie)
				return ((nfsuint64 *)0);
			dp = dp->ndm_list.le_next;
		} else if (add) {
			MALLOC(dp2, struct nfsdmap *, sizeof (struct nfsdmap),
				M_NFSDIROFF, M_WAITOK);
			dp2->ndm_eocookie = 0;
			LIST_INSERT_AFTER(dp, dp2, ndm_list);
			dp = dp2;
		} else
			return ((nfsuint64 *)0);
	}
	if (pos >= dp->ndm_eocookie) {
		if (add)
			dp->ndm_eocookie = pos + 1;
		else
			return ((nfsuint64 *)0);
	}
	return (&dp->ndm_cookies[pos]);
}

/*
 * Invalidate cached directory information, except for the actual directory
 * blocks (which are invalidated separately).
 * Done mainly to avoid the use of stale offset cookies.
 */
void
nfs_invaldir(vp)
	register struct vnode *vp;
{
	register struct nfsnode *np = VTONFS(vp);

#ifdef DIAGNOSTIC
	if (vp->v_type != VDIR)
		panic("nfs: invaldir not dir");
#endif
	np->n_direofoffset = 0;
	np->n_cookieverf.nfsuquad[0] = 0;
	np->n_cookieverf.nfsuquad[1] = 0;
	if (np->n_cookies.lh_first)
		np->n_cookies.lh_first->ndm_eocookie = 0;
}

/*
 * The write verifier has changed (probably due to a server reboot), so all
 * B_NEEDCOMMIT blocks will have to be written again. Since they are on the
 * dirty block list as B_DELWRI, all this takes is clearing the B_NEEDCOMMIT
 * flag. Once done the new write verifier can be set for the mount point.
 */
void
nfs_clearcommit(mp)
	struct mount *mp;
{
	register struct vnode *vp, *nvp;
	register struct buf *bp, *nbp;
	int s;

	s = splbio();
loop:
	for (vp = mp->mnt_vnodelist.lh_first; vp; vp = nvp) {
		if (vp->v_mount != mp)	/* Paranoia */
			goto loop;
		nvp = vp->v_mntvnodes.le_next;
		for (bp = vp->v_dirtyblkhd.lh_first; bp; bp = nbp) {
			nbp = bp->b_vnbufs.le_next;
			if ((bp->b_flags & (B_BUSY | B_DELWRI | B_NEEDCOMMIT))
				== (B_DELWRI | B_NEEDCOMMIT))
				bp->b_flags &= ~B_NEEDCOMMIT;
		}
	}
	splx(s);
}

/*
 * Map errnos to NFS error numbers. For Version 3 also filter out error
 * numbers not specified for the associated procedure.
 */
int
nfsrv_errmap(nd, err)
	struct nfsrv_descript *nd;
	register int err;
{
	register short *defaulterrp, *errp;

	if (nd->nd_flag & ND_NFSV3) {
	    if (nd->nd_procnum <= NFSPROC_COMMIT) {
		errp = defaulterrp = nfsrv_v3errmap[nd->nd_procnum];
		while (*++errp) {
			if (*errp == err)
				return (err);
			else if (*errp > err)
				break;
		}
		return ((int)*defaulterrp);
	    } else
		return (err & 0xffff);
	}
	if (err <= ELAST)
		return ((int)nfsrv_v2errmap[err - 1]);
	return (NFSERR_IO);
E 87
}
D 72

/*
 * Generate a hash code for an iso host address. Used by NETADDRHASH() for
 * iso addresses.
 */
iso_addrhash(saddr)
	struct sockaddr *saddr;
{
#ifdef ISO
	register struct sockaddr_iso *siso;
	register int i, sum;

	sum = 0;
	for (i = 0; i < siso->siso_nlen; i++)
		sum += siso->siso_data[i];
	return (sum & (NETHASHSZ - 1));
#else
	return (0);
#endif	/* ISO */
E 67
E 45
E 30
}
E 72
D 8

E 8
E 1
