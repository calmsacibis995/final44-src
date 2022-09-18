h13056
s 00451/00182/00648
d D 8.5 95/03/30 11:26:35 mckusick 47 46
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00063/00081/00767
d D 8.4 94/08/18 23:33:41 mckusick 46 45
c conversion to queue.h list manipulation (from mycroft)
e
s 00001/00002/00847
d D 8.3 94/01/04 22:07:41 bostic 45 44
c lint
e
s 00004/00004/00845
d D 8.2 93/12/30 16:19:48 mckusick 44 43
c new queue structure
e
s 00002/00002/00847
d D 8.1 93/06/10 23:39:17 bostic 43 42
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00133/00047/00716
d D 7.37 93/02/02 15:20:48 mckusick 42 41
c update for 4.4BSD from Rick Macklem
e
s 00001/00000/00762
d D 7.36 92/11/01 23:14:50 mckusick 41 40
c uninitialized variable
e
s 00001/00001/00761
d D 7.35 92/10/11 12:35:13 bostic 40 39
c make kernel includes standard
e
s 00031/00035/00731
d D 7.34 92/10/08 00:25:21 mckusick 39 38
c use new queue routines to manage list of I/O requests; new include syntax
e
s 00009/00012/00757
d D 7.33 92/10/02 00:44:35 mckusick 38 36
c now use modern list management methods
e
s 00009/00012/00757
d R 7.33 92/10/02 00:15:15 mckusick 37 36
c now use modern list management methods
e
s 00010/00008/00759
d D 7.32 92/07/10 20:46:10 torek 36 35
c ANSIfy syscall args
e
s 00000/00001/00767
d D 7.31 92/05/06 11:08:14 mckusick 35 32
c AIX interoperability
e
s 00030/00000/00768
d D 7.30.1.1 92/03/16 21:49:16 mckusick 34 32
c code to verify zapsock does the right thing
e
s 00030/00000/00768
d R 7.30.1.1 92/03/16 21:10:45 mckusick 33 32
c code to verify zapsock does the right thing
e
s 00076/00049/00692
d D 7.30 92/03/16 15:38:43 mckusick 32 31
c fix from Rick Macklem for multiple free's of NFSD structures
e
s 00068/00062/00673
d D 7.29 92/03/09 22:27:33 mckusick 31 30
c first cut at fixing discconect/reconnect hanging confusion
e
s 00010/00013/00725
d D 7.28 92/02/04 00:26:50 mckusick 30 29
c new namei calling convention
e
s 00529/00133/00209
d D 7.27 92/01/14 12:41:24 mckusick 29 27
c update from Rick Macklem (including leases)
e
s 00006/00000/00342
d D 7.26.1.1 91/05/19 14:26:03 mckusick 28 27
c name resolution checking (need kern/kern_malloc.c 7.25.1.1,
c kern/vfs_lookup.c 7.31.1.1, kern/vfs_syscalls.c 7.70.1.1,
c nfs/nfs_serv.c 7.40.1.1, nfs/nfs_syscalls.c 7.26.1.1,
c ufs/ufs_vnops.c 7.64.1.1, and hp300/hp300/trap.c 7.14.1.1
e
s 00003/00002/00339
d D 7.26 91/04/16 00:40:03 mckusick 27 26
c use passed in proc pointers
e
s 00003/00003/00338
d D 7.25 91/03/19 11:24:47 karels 26 25
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; consolidate *nullops()
e
s 00003/00001/00338
d D 7.24 91/03/04 23:17:02 mckusick 25 24
c eliminate u.u_nd
e
s 00032/00017/00307
d D 7.23 91/03/04 22:52:14 mckusick 24 23
c misc fixes plus diskless support from Rick Macklem
e
s 00005/00005/00319
d D 7.22 91/03/04 14:10:14 karels 23 22
c first pass at proc reorg
e
s 00003/00005/00321
d D 7.21 91/01/10 23:53:15 mckusick 22 21
c add synamically allocated file descriptors
e
s 00002/00002/00324
d D 7.20 90/10/02 10:46:14 mckusick 21 20
c fixes for compressed NFS (from Macklem)
e
s 00027/00002/00299
d D 7.19 90/10/01 14:17:09 mckusick 20 19
c add Rick Macklem's compressed NFS
e
s 00001/00011/00300
d D 7.18 90/06/28 21:52:52 bostic 19 18
c new copyright notice
e
s 00009/00009/00302
d D 7.17 90/06/28 17:29:31 karels 18 17
c RETURN => return, remove syscontext.h
e
s 00028/00021/00283
d D 7.16 90/06/21 11:46:38 mckusick 17 16
c "update from Rick Macklem"
e
s 00002/00002/00302
d D 7.15 90/06/05 10:23:22 mckusick 16 15
c make the kernel self consistent
e
s 00107/00027/00197
d D 7.14 90/05/14 11:45:05 mckusick 15 14
c "update from Rick Macklem adding TCP support to NFS"
e
s 00001/00001/00223
d D 7.13 90/05/04 20:52:42 mckusick 14 13
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00001/00001/00223
d D 7.12 90/05/02 18:19:03 mckusick 13 12
c NFSiod waits at PWAIT rather than PRIBIO
e
s 00009/00006/00215
d D 7.11 90/04/04 21:30:26 karels 12 10
c new tsleep, unwind on signal; server exit when signal received;
c don't free nonexistent mbuf when nfs_getreq returns error
e
s 00007/00005/00216
d R 7.11 90/04/04 21:20:12 karels 11 10
c new tsleep, unwind on signal; server exit when signal received
e
s 00000/00052/00221
d D 7.10 90/03/08 15:59:35 mckusick 10 9
c eliminate exportfs; functionality merged into mount
e
s 00001/00001/00272
d D 7.9 90/03/06 23:35:37 mckusick 9 8
c f_fsid is now found in m_stat.f_fsid
e
s 00007/00001/00266
d D 7.8 90/03/01 14:10:19 mckusick 8 7
c add validity indication to nfsrv_updatecache
e
s 00001/00001/00266
d D 7.7 90/02/16 14:04:24 mckusick 7 6
c generalize nfs_send routine (see nfs_socket.c)
e
s 00003/00001/00264
d D 7.6 90/02/08 16:44:18 marc 6 5
c tsleep
e
s 00040/00020/00225
d D 7.5 89/12/20 18:13:22 mckusick 5 4
c "December update from Rick Macklem"
e
s 00004/00004/00241
d D 7.4 89/11/03 15:30:32 mckusick 4 3
c lint
e
s 00013/00007/00232
d D 7.3 89/10/19 22:35:17 mckusick 3 2
c "update from Rick Macklem"
e
s 00042/00000/00197
d D 7.2 89/08/30 20:30:10 macklem 2 1
c first buffer cache implementation; name cache usage; code cleanups
e
s 00197/00000/00000
d D 7.1 89/07/05 11:32:25 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
f b 
t
T
I 1
/*
D 43
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 43
I 43
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 43
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 19
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
E 19
I 19
 * %sccs.include.redist.c%
E 19
 *
 *	%W% (Berkeley) %G%
 */

D 39
#include "param.h"
#include "systm.h"
D 17
#include "user.h"
E 17
I 17
D 18
#include "syscontext.h"
E 18
I 18
D 26
#include "user.h"
E 26
E 18
E 17
#include "kernel.h"
#include "file.h"
#include "stat.h"
I 27
D 29
#include "namei.h"
E 29
E 27
#include "vnode.h"
#include "mount.h"
#include "proc.h"
I 29
#include "uio.h"
E 29
D 26
#include "uio.h"
E 26
#include "malloc.h"
I 2
#include "buf.h"
E 2
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
I 15
#include "domain.h"
#include "protosw.h"
I 26
D 29

E 26
D 16
#include "netinet/in.h"
#include "netinet/tcp.h"
E 16
I 16
#include "../netinet/in.h"
#include "../netinet/tcp.h"
I 26

E 29
I 29
#include "namei.h"
#include "netinet/in.h"
#include "netinet/tcp.h"
E 39
I 39
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/malloc.h>
#include <sys/buf.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/namei.h>
I 42
#include <sys/syslog.h>
E 42
I 40

E 40
#include <netinet/in.h>
#include <netinet/tcp.h>
E 39
#ifdef ISO
D 39
#include "netiso/iso.h"
E 39
I 39
#include <netiso/iso.h>
E 39
#endif
I 47
#include <nfs/xdr_subs.h>
E 47
D 39
#include "machine/endian.h"
#include "rpcv2.h"
E 29
E 26
E 16
E 15
#include "nfsv2.h"
#include "nfs.h"
I 5
#include "nfsrvcache.h"
I 29
#include "nfsmount.h"
#include "nqnfs.h"
E 39
I 39
D 40
#include <machine/endian.h>
E 40
#include <nfs/rpcv2.h>
D 47
#include <nfs/nfsv2.h>
E 47
I 47
#include <nfs/nfsproto.h>
E 47
#include <nfs/nfs.h>
I 47
#include <nfs/nfsm_subs.h>
E 47
#include <nfs/nfsrvcache.h>
#include <nfs/nfsmount.h>
I 44
#include <nfs/nfsnode.h>
E 44
#include <nfs/nqnfs.h>
I 42
#include <nfs/nfsrtt.h>
E 42
E 39
E 29
I 6
D 12
#include "tsleep.h"
E 12
E 6
E 5

I 47
void	nfsrv_zapsock	__P((struct nfssvc_sock *));

E 47
/* Global defs. */
D 47
extern u_long nfs_prog, nfs_vers;
extern int (*nfsrv_procs[NFS_NPROCS])();
E 47
I 47
extern int (*nfsrv3_procs[NFS_NPROCS])();
E 47
I 2
D 38
extern struct buf nfs_bqueue;
E 38
I 38
D 39
extern struct buf *nfs_bqueuehead, **nfs_bqueuetail;
E 39
I 39
D 44
extern struct queue_entry nfs_bufq;
E 44
E 39
E 38
D 3
extern int nfs_iodwant;
E 3
I 3
D 24
extern int nfs_asyncdaemons;
E 24
I 24
D 29
extern int nfs_numasync;
E 29
E 24
D 15
extern struct proc *nfs_iodwant[MAX_ASYNCDAEMON];
E 15
I 15
extern struct proc *nfs_iodwant[NFS_MAXASYNCDAEMON];
D 29
extern int nfs_tcpnodelay;
E 15
E 3
E 2
D 22
struct file *getsock();
E 22
I 20
struct mbuf *nfs_compress();
E 29
I 29
extern int nfs_numasync;
extern time_t nqnfsstarttime;
D 46
extern struct nfsrv_req nsrvq_head;
extern struct nfsd nfsd_head;
E 46
extern int nqsrv_writeslack;
I 42
extern int nfsrtton;
I 47
extern struct nfsstats nfsstats;
extern int nfsrvw_procrastinate;
E 47
E 42
struct nfssvc_sock *nfs_udpsock, *nfs_cltpsock;
int nuidhash_max = NFS_MAXUIDHASH;
static int nfs_numnfsd = 0;
int nfsd_waiting = 0;
static int notstarted = 1;
static int modify_flag = 0;
I 42
static struct nfsdrt nfsdrt;
E 42
void nfsrv_cleancache(), nfsrv_rcv(), nfsrv_wakenfsd(), nfs_sndunlock();
I 42
static void nfsd_rt();
E 42
I 31
D 32
void nfsrv_slpderef();
E 32
I 32
D 47
void nfsrv_slpderef(), nfsrv_init();
E 47
I 47
void nfsrv_slpderef();
E 47
E 32
E 31
E 29
E 20

I 8
#define	TRUE	1
#define	FALSE	0

I 24
static int nfs_asyncdaemon[NFS_MAXASYNCDAEMON];
E 24
I 20
D 29
static int compressreply[NFS_NPROCS] = {
	FALSE,
	TRUE,
	TRUE,
	FALSE,
	TRUE,
	TRUE,
	FALSE,
	FALSE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
};
E 29
E 20
E 8
/*
 * NFS server system calls
 * getfh() lives here too, but maybe should move to kern/vfs_syscalls.c
 */
D 17
#define RETURN(value)	{ u.u_error = (value); return; }
E 17

/*
 * Get file handle system call
 */
I 36
struct getfh_args {
	char	*fname;
	fhandle_t *fhp;
};
I 47
int
E 47
E 36
D 17
getfh()
{
	register struct a {
E 17
I 17
D 29
/* ARGSUSED */
E 29
getfh(p, uap, retval)
	struct proc *p;
D 36
	register struct args {
E 17
		char	*fname;
		fhandle_t *fhp;
D 17
	} *uap = (struct a *)u.u_ap;
E 17
I 17
	} *uap;
E 36
I 36
	register struct getfh_args *uap;
E 36
	int *retval;
{
E 17
D 25
	register struct nameidata *ndp = &u.u_nd;
E 25
I 25
D 30
	register struct nameidata *ndp;
E 30
E 25
	register struct vnode *vp;
	fhandle_t fh;
	int error;
I 25
	struct nameidata nd;
E 25

	/*
	 * Must be super user
	 */
D 17
	if (error = suser(u.u_cred, &u.u_acflag))
E 17
I 17
D 23
	if (error = suser(ndp->ni_cred, &u.u_acflag))
E 23
I 23
D 47
	if (error = suser(p->p_ucred, &p->p_acflag))
E 47
I 47
	error = suser(p->p_ucred, &p->p_acflag);
	if(error)
E 47
E 23
E 17
D 18
		RETURN (error);
E 18
I 18
		return (error);
I 25
D 30
	ndp = &nd;
E 25
E 18
	ndp->ni_nameiop = LOOKUP | LOCKLEAF | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
D 23
	if (error = namei(ndp))
E 23
I 23
	if (error = namei(ndp, p))
E 30
I 30
	NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, uap->fname, p);
D 47
	if (error = namei(&nd))
E 47
I 47
	error = namei(&nd);
	if (error)
E 47
E 30
E 23
D 18
		RETURN (error);
E 18
I 18
		return (error);
E 18
D 30
	vp = ndp->ni_vp;
E 30
I 30
	vp = nd.ni_vp;
E 30
	bzero((caddr_t)&fh, sizeof(fh));
D 9
	fh.fh_fsid = vp->v_mount->m_fsid;
E 9
I 9
D 14
	fh.fh_fsid = vp->v_mount->m_stat.f_fsid;
E 14
I 14
	fh.fh_fsid = vp->v_mount->mnt_stat.f_fsid;
E 14
E 9
	error = VFS_VPTOFH(vp, &fh.fh_fid);
	vput(vp);
	if (error)
D 18
		RETURN (error);
E 18
I 18
		return (error);
E 18
	error = copyout((caddr_t)&fh, (caddr_t)uap->fhp, sizeof (fh));
D 18
	RETURN (error);
E 18
I 18
	return (error);
E 18
}

I 29
D 46
static struct nfssvc_sock nfssvc_sockhead;

E 46
I 34
#define SLP_DEREFFREE	0x100
#define SLP_CLRFREE	0x200

E 34
E 29
/*
D 10
 * Mark a mount point in the filesystem exported
 */
exportfs()
{
	register struct a {
		char	*fname;
		int	rootuid;
		int	exflags;
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
	register struct vnode *vp;
	register struct mount *mp;
	int error;

	/*
	 * Must be super user
	 */
	if (error = suser(u.u_cred, &u.u_acflag))
		RETURN (error);
	ndp->ni_nameiop = LOOKUP | LOCKLEAF | FOLLOW;	/* Or NOFOLLOW ?? */
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
	if (error = namei(ndp))
		RETURN (error);
	vp = ndp->ni_vp;
	if (vp->v_type != VDIR) {
		vput(vp);
		RETURN (ENOENT);
	}
	mp = vp->v_mount;

	/*
	 * If the filesystem has already been exported, just relax
	 * security as required.
	 * Otherwise export it with the given security
	 */
	if (mp->m_flag & M_EXPORTED) {
		if (uap->rootuid == 0)
			mp->m_exroot = 0;
		if ((uap->exflags & M_EXRDONLY) == 0)
			mp->m_flag &= ~M_EXRDONLY;
	} else {
		mp->m_exroot = uap->rootuid;
		if (uap->exflags & M_EXRDONLY)
			mp->m_flag |= M_EXRDONLY;
		mp->m_flag |= M_EXPORTED;
	}
	vput(vp);
	RETURN (0);
}

/*
E 10
 * Nfs server psuedo system call for the nfsd's
D 29
 * Never returns unless it fails or gets killed
E 29
I 29
 * Based on the flag value it either:
 * - adds a socket to the selection list
 * - remains in the kernel as an nfsd
 * - remains in the kernel as an nfsiod
E 29
 */
I 36
struct nfssvc_args {
	int flag;
	caddr_t argp;
};
I 47
int
E 47
E 36
D 17
nfssvc()
{
	register struct a {
E 17
I 17
D 29
/* ARGSUSED */
E 29
nfssvc(p, uap, retval)
	struct proc *p;
D 36
	register struct args {
E 17
D 29
		int s;
I 5
D 15
		u_long ormask;
		u_long matchbits;
E 15
I 15
		caddr_t mskval;
		int msklen;
		caddr_t mtchval;
		int mtchlen;
E 29
I 29
		int flag;
		caddr_t argp;
E 29
E 15
E 5
D 17
	} *uap = (struct a *)u.u_ap;
E 17
I 17
	} *uap;
E 36
I 36
	register struct nfssvc_args *uap;
E 36
	int *retval;
{
E 17
D 29
	register struct mbuf *m;
	register int siz;
	register struct ucred *cr;
E 29
I 29
	struct nameidata nd;
E 29
	struct file *fp;
D 29
	struct mbuf *mreq, *mrep, *nam, *md;
I 15
	struct mbuf msk, mtch;
E 15
	struct socket *so;
	caddr_t dpos;
D 4
	int proc;
E 4
I 4
D 15
	int procid;
E 15
I 15
D 17
	int procid, repstat, error, cacherep, solock = 0;
E 17
I 17
D 20
	int procid, repstat, error, cacherep;
E 20
I 20
	int procid, repstat, error, cacherep, wascomp;
E 20
E 17
E 15
E 4
	u_long retxid;
E 29
I 29
	struct mbuf *nam;
	struct nfsd_args nfsdarg;
	struct nfsd_srvargs nfsd_srvargs, *nsd = &nfsd_srvargs;
	struct nfsd_cargs ncd;
	struct nfsd *nfsd;
	struct nfssvc_sock *slp;
D 47
	struct nfsuid *nuidp, **nuh;
E 47
I 47
	struct nfsuid *nuidp;
E 47
	struct nfsmount *nmp;
	int error;
E 29
I 5
D 15
	u_long msk, mtch;
	int repstat;
E 5
	int error;
E 15

	/*
	 * Must be super user
	 */
D 23
	if (error = suser(u.u_cred, &u.u_acflag))
E 23
I 23
D 47
	if (error = suser(p->p_ucred, &p->p_acflag))
E 47
I 47
	error = suser(p->p_ucred, &p->p_acflag);
	if(error)
E 47
E 23
D 15
		RETURN (error);
D 12
	fp = getsock(uap->s);
E 12
I 12
	fp = getsock(uap->s, &error);
E 15
I 15
D 22
		goto bad;
	fp = getsock(uap->s);
E 15
E 12
	if (fp == 0)
D 12
		return;
E 12
I 12
D 15
		RETURN (error);
E 15
I 15
		return;
E 22
I 22
		return (error);
D 29
	if (error = getsock(p->p_fd, uap->s, &fp))
		return (error);
E 29
I 29
D 32
	if (nfssvc_sockhead.ns_next == NULL) {
		nfs_udpsock = (struct nfssvc_sock *)
		    malloc(sizeof (struct nfssvc_sock), M_NFSSVC, M_WAITOK);
		bzero((caddr_t)nfs_udpsock, sizeof (struct nfssvc_sock));
		nfs_cltpsock = (struct nfssvc_sock *)
		    malloc(sizeof (struct nfssvc_sock), M_NFSSVC, M_WAITOK);
		bzero((caddr_t)nfs_cltpsock, sizeof (struct nfssvc_sock));
		nfssvc_sockhead.ns_next = nfs_udpsock;
		nfs_udpsock->ns_next = nfs_cltpsock;
		nfs_cltpsock->ns_next = &nfssvc_sockhead;
		nfssvc_sockhead.ns_prev = nfs_cltpsock;
		nfs_cltpsock->ns_prev = nfs_udpsock;
		nfs_udpsock->ns_prev = &nfssvc_sockhead;
		nfs_udpsock->ns_lrunext = nfs_udpsock->ns_lruprev =
			(struct nfsuid *)nfs_udpsock;
		nfs_cltpsock->ns_lrunext = nfs_cltpsock->ns_lruprev =
			(struct nfsuid *)nfs_cltpsock;
		nfsd_head.nd_next = nfsd_head.nd_prev = &nfsd_head;
		nfsd_head.nd_flag = 0;
E 32
I 32
D 46
	while (nfssvc_sockhead.ns_flag & SLP_INIT) {
		nfssvc_sockhead.ns_flag |= SLP_WANTINIT;
E 46
I 46
	while (nfssvc_sockhead_flag & SLP_INIT) {
D 47
		nfssvc_sockhead_flag |= SLP_WANTINIT;
E 47
I 47
		 nfssvc_sockhead_flag |= SLP_WANTINIT;
E 47
E 46
		(void) tsleep((caddr_t)&nfssvc_sockhead, PSOCK, "nfsd init", 0);
E 32
	}
	if (uap->flag & NFSSVC_BIOD)
		error = nfssvc_iod(p);
	else if (uap->flag & NFSSVC_MNTD) {
D 47
		if (error = copyin(uap->argp, (caddr_t)&ncd, sizeof (ncd)))
E 47
I 47
		error = copyin(uap->argp, (caddr_t)&ncd, sizeof (ncd));
		if (error)
E 47
			return (error);
D 30
		nd.ni_nameiop = LOOKUP | FOLLOW | LOCKLEAF;
		nd.ni_segflg = UIO_USERSPACE;
		nd.ni_dirp = ncd.ncd_dirp;
		if (error = namei(&nd, p))
E 30
I 30
		NDINIT(&nd, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE,
			ncd.ncd_dirp, p);
D 47
		if (error = namei(&nd))
E 47
I 47
		error = namei(&nd);
		if (error)
E 47
E 30
			return (error);
		if ((nd.ni_vp->v_flag & VROOT) == 0)
			error = EINVAL;
		nmp = VFSTONFS(nd.ni_vp->v_mount);
		vput(nd.ni_vp);
		if (error)
			return (error);
D 42
		else if (nmp->nm_flag & NFSMNT_MNTD)
E 42
I 42
		if ((nmp->nm_flag & NFSMNT_MNTD) &&
			(uap->flag & NFSSVC_GOTAUTH) == 0)
E 42
			return (0);
		nmp->nm_flag |= NFSMNT_MNTD;
D 30
		error = nqnfs_clientd(nmp, p->p_ucred, &ncd, uap->flag, uap->argp, p);
E 30
I 30
		error = nqnfs_clientd(nmp, p->p_ucred, &ncd, uap->flag,
			uap->argp, p);
E 30
	} else if (uap->flag & NFSSVC_ADDSOCK) {
D 30
		if (error = copyin(uap->argp, (caddr_t)&nfsdarg, sizeof (nfsdarg)))
E 30
I 30
D 47
		if (error = copyin(uap->argp, (caddr_t)&nfsdarg,
		    sizeof(nfsdarg)))
E 47
I 47
		error = copyin(uap->argp, (caddr_t)&nfsdarg, sizeof(nfsdarg));
		if (error)
E 47
E 30
			return (error);
D 47
		if (error = getsock(p->p_fd, nfsdarg.sock, &fp))
E 47
I 47
		error = getsock(p->p_fd, nfsdarg.sock, &fp);
		if (error)
E 47
			return (error);
		/*
		 * Get the client address for connected sockets.
		 */
		if (nfsdarg.name == NULL || nfsdarg.namelen == 0)
			nam = (struct mbuf *)0;
D 47
		else if (error = sockargs(&nam, nfsdarg.name, nfsdarg.namelen,
			MT_SONAME))
			return (error);
E 47
I 47
		else {
			error = sockargs(&nam, nfsdarg.name, nfsdarg.namelen,
				MT_SONAME);
			if (error)
				return (error);
		}
E 47
		error = nfssvc_addsock(fp, nam);
	} else {
D 47
		if (error = copyin(uap->argp, (caddr_t)nsd, sizeof (*nsd)))
E 47
I 47
		error = copyin(uap->argp, (caddr_t)nsd, sizeof (*nsd));
		if (error)
E 47
			return (error);
D 47
		if ((uap->flag & NFSSVC_AUTHIN) && (nfsd = nsd->nsd_nfsd) &&
D 31
			nfsd->nd_sref == nfsd->nd_slp->ns_sref) {
E 31
I 31
			(nfsd->nd_slp->ns_flag & SLP_VALID)) {
E 31
			slp = nfsd->nd_slp;
E 47
I 47
		if ((uap->flag & NFSSVC_AUTHIN) && ((nfsd = nsd->nsd_nfsd)) &&
			(nfsd->nfsd_slp->ns_flag & SLP_VALID)) {
			slp = nfsd->nfsd_slp;
E 47
D 42
			if (slp->ns_numuids < nuidhash_max) {
E 42
I 42

			/*
			 * First check to see if another nfsd has already
			 * added this credential.
			 */
D 46
			nuidp = slp->ns_uidh[NUIDHASH(nsd->nsd_uid)];
			while (nuidp) {
E 46
I 46
D 47
			for (nuidp = NUIDHASH(slp, nsd->nsd_uid)->lh_first;
E 47
I 47
			for (nuidp = NUIDHASH(slp,nsd->nsd_cr.cr_uid)->lh_first;
E 47
			    nuidp != 0; nuidp = nuidp->nu_hash.le_next) {
E 46
D 47
				if (nuidp->nu_uid == nsd->nsd_uid)
E 47
I 47
				if (nuidp->nu_cr.cr_uid == nsd->nsd_cr.cr_uid &&
				    (!nfsd->nfsd_nd->nd_nam2 ||
				     netaddr_match(NU_NETFAM(nuidp),
				     &nuidp->nu_haddr, nfsd->nfsd_nd->nd_nam2)))
E 47
					break;
D 46
				nuidp = nuidp->nu_hnext;
E 46
			}
D 46
			if (!nuidp) {
E 46
I 46
D 47
			if (nuidp == 0) {
E 47
I 47
			if (nuidp) {
			    nfsrv_setcred(&nuidp->nu_cr,&nfsd->nfsd_nd->nd_cr);
			    nfsd->nfsd_nd->nd_flag |= ND_KERBFULL;
			} else {
E 47
E 46
			    /*
			     * Nope, so we will.
			     */
			    if (slp->ns_numuids < nuidhash_max) {
E 42
				slp->ns_numuids++;
				nuidp = (struct nfsuid *)
D 42
				   malloc(sizeof (struct nfsuid), M_NFSUID, M_WAITOK);
			} else
E 42
I 42
				   malloc(sizeof (struct nfsuid), M_NFSUID,
					M_WAITOK);
			    } else
E 42
				nuidp = (struct nfsuid *)0;
D 31
			if (slp->ns_sref != nfsd->nd_sref) {
E 31
I 31
D 42
			if ((slp->ns_flag & SLP_VALID) == 0) {
E 31
			    if (nuidp)
				free((caddr_t)nuidp, M_NFSUID);
			} else {
			    if (nuidp == (struct nfsuid *)0) {
				nuidp = slp->ns_lruprev;
				remque(nuidp);
				if (nuidp->nu_hprev)
					nuidp->nu_hprev->nu_hnext = nuidp->nu_hnext;
				if (nuidp->nu_hnext)
					nuidp->nu_hnext->nu_hprev = nuidp->nu_hprev;
E 42
I 42
			    if ((slp->ns_flag & SLP_VALID) == 0) {
				if (nuidp)
				    free((caddr_t)nuidp, M_NFSUID);
			    } else {
				if (nuidp == (struct nfsuid *)0) {
D 46
				    nuidp = slp->ns_lruprev;
				    remque(nuidp);
				    if (nuidp->nu_hprev)
					nuidp->nu_hprev->nu_hnext =
					    nuidp->nu_hnext;
				    if (nuidp->nu_hnext)
					nuidp->nu_hnext->nu_hprev =
					    nuidp->nu_hprev;
E 46
I 46
				    nuidp = slp->ns_uidlruhead.tqh_first;
				    LIST_REMOVE(nuidp, nu_hash);
				    TAILQ_REMOVE(&slp->ns_uidlruhead, nuidp,
					nu_lru);
I 47
				    if (nuidp->nu_flag & NU_NAM)
					m_freem(nuidp->nu_nam);
E 47
E 46
			        }
I 47
				nuidp->nu_flag = 0;
E 47
				nuidp->nu_cr = nsd->nsd_cr;
				if (nuidp->nu_cr.cr_ngroups > NGROUPS)
D 47
					nuidp->nu_cr.cr_ngroups = NGROUPS;
E 47
I 47
				    nuidp->nu_cr.cr_ngroups = NGROUPS;
E 47
				nuidp->nu_cr.cr_ref = 1;
D 47
				nuidp->nu_uid = nsd->nsd_uid;
E 47
I 47
				nuidp->nu_timestamp = nsd->nsd_timestamp;
				nuidp->nu_expire = time.tv_sec + nsd->nsd_ttl;
				/*
				 * and save the session key in nu_key.
				 */
				bcopy(nsd->nsd_key, nuidp->nu_key,
				    sizeof (nsd->nsd_key));
				if (nfsd->nfsd_nd->nd_nam2) {
				    struct sockaddr_in *saddr;

				    saddr = mtod(nfsd->nfsd_nd->nd_nam2,
					 struct sockaddr_in *);
				    switch (saddr->sin_family) {
				    case AF_INET:
					nuidp->nu_flag |= NU_INETADDR;
					nuidp->nu_inetaddr =
					     saddr->sin_addr.s_addr;
					break;
				    case AF_ISO:
				    default:
					nuidp->nu_flag |= NU_NAM;
					nuidp->nu_nam = m_copym(
					    nfsd->nfsd_nd->nd_nam2, 0,
					     M_COPYALL, M_WAIT);
					break;
				    };
				}
E 47
D 46
				insque(nuidp, (struct nfsuid *)slp);
				nuh = &slp->ns_uidh[NUIDHASH(nsd->nsd_uid)];
				if (nuidp->nu_hnext = *nuh)
				    nuidp->nu_hnext->nu_hprev = nuidp;
				nuidp->nu_hprev = (struct nfsuid *)0;
				*nuh = nuidp;
E 46
I 46
				TAILQ_INSERT_TAIL(&slp->ns_uidlruhead, nuidp,
D 47
				    nu_lru);
E 47
I 47
					nu_lru);
E 47
				LIST_INSERT_HEAD(NUIDHASH(slp, nsd->nsd_uid),
D 47
				    nuidp, nu_hash);
E 47
I 47
					nuidp, nu_hash);
				nfsrv_setcred(&nuidp->nu_cr,
				    &nfsd->nfsd_nd->nd_cr);
				nfsd->nfsd_nd->nd_flag |= ND_KERBFULL;
E 47
E 46
E 42
			    }
D 42
			    nuidp->nu_cr = nsd->nsd_cr;
			    nuidp->nu_cr.cr_ref = 1;
			    nuidp->nu_uid = nsd->nsd_uid;
			    insque(nuidp, (struct nfsuid *)slp);
			    nuh = &slp->ns_uidh[NUIDHASH(nsd->nsd_uid)];
			    if (nuidp->nu_hnext = *nuh)
				nuidp->nu_hnext->nu_hprev = nuidp;
			    nuidp->nu_hprev = (struct nfsuid *)0;
			    *nuh = nuidp;
E 42
			}
		}
		if ((uap->flag & NFSSVC_AUTHINFAIL) && (nfsd = nsd->nsd_nfsd))
D 47
			nfsd->nd_flag |= NFSD_AUTHFAIL;
E 47
I 47
			nfsd->nfsd_flag |= NFSD_AUTHFAIL;
E 47
		error = nfssvc_nfsd(nsd, uap->argp, p);
	}
	if (error == EINTR || error == ERESTART)
		error = 0;
	return (error);
}

/*
 * Adds a socket to the list for servicing by nfsds.
 */
I 47
int
E 47
nfssvc_addsock(fp, mynam)
	struct file *fp;
	struct mbuf *mynam;
{
	register struct mbuf *m;
	register int siz;
	register struct nfssvc_sock *slp;
	register struct socket *so;
	struct nfssvc_sock *tslp;
	int error, s;

E 29
E 22
E 15
E 12
	so = (struct socket *)fp->f_data;
D 15
	cr = u.u_cred = crcopy(u.u_cred);	/* Copy it so others don't see changes */
I 5
	msk = uap->ormask;
	mtch = uap->matchbits;
E 15
I 15
D 29
	if (sosendallatonce(so))
		siz = NFS_MAXPACKET;
E 29
I 29
	tslp = (struct nfssvc_sock *)0;
	/*
	 * Add it to the list, as required.
	 */
	if (so->so_proto->pr_protocol == IPPROTO_UDP) {
		tslp = nfs_udpsock;
		if (tslp->ns_flag & SLP_VALID) {
			m_freem(mynam);
			return (EPERM);
		}
#ifdef ISO
	} else if (so->so_proto->pr_protocol == ISOPROTO_CLTP) {
		tslp = nfs_cltpsock;
		if (tslp->ns_flag & SLP_VALID) {
			m_freem(mynam);
			return (EPERM);
		}
#endif /* ISO */
D 31
	} else {
		slp = nfs_cltpsock->ns_next;
		while (slp != &nfssvc_sockhead) {
			if ((slp->ns_flag & SLP_VALID) == 0) {
				tslp = slp;
				break;
			}
			slp = slp->ns_next;
		}
E 31
	}
	if (so->so_type == SOCK_STREAM)
		siz = NFS_MAXPACKET + sizeof (u_long);
E 29
	else
D 29
		siz = NFS_MAXPACKET + sizeof(u_long);
D 17
	if (error = soreserve(so, siz, siz * 4))
E 17
I 17
	if (error = soreserve(so, siz, siz))
E 17
		goto bad;
	if (error = sockargs(&nam, uap->mskval, uap->msklen, MT_SONAME))
		goto bad;
	bcopy((caddr_t)nam, (caddr_t)&msk, sizeof (struct mbuf));
	msk.m_data = msk.m_dat;
	m_freem(nam);
	if (error = sockargs(&nam, uap->mtchval, uap->mtchlen, MT_SONAME))
		goto bad;
	bcopy((caddr_t)nam, (caddr_t)&mtch, sizeof (struct mbuf));
	mtch.m_data = mtch.m_dat;
	m_freem(nam);
E 29
I 29
		siz = NFS_MAXPACKET;
D 47
	if (error = soreserve(so, siz, siz)) {
E 47
I 47
	error = soreserve(so, siz, siz); 
	if (error) {
E 47
		m_freem(mynam);
		return (error);
	}
E 29

D 29
	/* Copy the cred so others don't see changes */
D 23
	cr = u.u_cred = crcopy(u.u_cred);
E 23
I 23
	cr = p->p_ucred = crcopy(p->p_ucred);
E 23

E 29
E 15
E 5
	/*
I 15
	 * Set protocol specific options { for now TCP only } and
	 * reserve some space. For datagram sockets, this can get called
	 * repeatedly for the same socket, but that isn't harmful.
	 */
D 29
	if (so->so_proto->pr_flags & PR_CONNREQUIRED) {
E 29
I 29
	if (so->so_type == SOCK_STREAM) {
E 29
		MGET(m, M_WAIT, MT_SOOPTS);
		*mtod(m, int *) = 1;
		m->m_len = sizeof(int);
		sosetopt(so, SOL_SOCKET, SO_KEEPALIVE, m);
	}
	if (so->so_proto->pr_domain->dom_family == AF_INET &&
D 29
	    so->so_proto->pr_protocol == IPPROTO_TCP &&
	    nfs_tcpnodelay) {
E 29
I 29
	    so->so_proto->pr_protocol == IPPROTO_TCP) {
E 29
		MGET(m, M_WAIT, MT_SOOPTS);
		*mtod(m, int *) = 1;
		m->m_len = sizeof(int);
		sosetopt(so, IPPROTO_TCP, TCP_NODELAY, m);
	}
	so->so_rcv.sb_flags &= ~SB_NOINTR;
	so->so_rcv.sb_timeo = 0;
	so->so_snd.sb_flags &= ~SB_NOINTR;
	so->so_snd.sb_timeo = 0;
I 29
	if (tslp)
		slp = tslp;
	else {
		slp = (struct nfssvc_sock *)
			malloc(sizeof (struct nfssvc_sock), M_NFSSVC, M_WAITOK);
I 34
		printf("Alloc nfssvc_sock 0x%x\n", slp);
E 34
		bzero((caddr_t)slp, sizeof (struct nfssvc_sock));
D 46
		slp->ns_prev = nfssvc_sockhead.ns_prev;
		slp->ns_prev->ns_next = slp;
		slp->ns_next = &nfssvc_sockhead;
		nfssvc_sockhead.ns_prev = slp;
		slp->ns_lrunext = slp->ns_lruprev = (struct nfsuid *)slp;
E 46
I 46
D 47
		slp->ns_uidhashtbl =
		    hashinit(NUIDHASHSIZ, M_NFSSVC, &slp->ns_uidhash);
E 47
		TAILQ_INIT(&slp->ns_uidlruhead);
		TAILQ_INSERT_TAIL(&nfssvc_sockhead, slp, ns_chain);
E 46
	}
	slp->ns_so = so;
	slp->ns_nam = mynam;
	fp->f_count++;
	slp->ns_fp = fp;
	s = splnet();
	so->so_upcallarg = (caddr_t)slp;
	so->so_upcall = nfsrv_rcv;
	slp->ns_flag = (SLP_VALID | SLP_NEEDQ);
D 31
	nfsd_head.nd_flag |= NFSD_CHECKSLP;
E 31
	nfsrv_wakenfsd(slp);
	splx(s);
	return (0);
}
E 29

I 29
/*
 * Called by nfssvc() for nfsds. Just loops around servicing rpc requests
 * until it is killed by a signal.
 */
I 47
int
E 47
nfssvc_nfsd(nsd, argp, p)
	struct nfsd_srvargs *nsd;
	caddr_t argp;
	struct proc *p;
{
D 47
	register struct mbuf *m, *nam2;
E 47
I 47
	register struct mbuf *m;
E 47
	register int siz;
	register struct nfssvc_sock *slp;
	register struct socket *so;
	register int *solockp;
I 31
D 45
	struct nfssvc_sock *oslp;
E 45
E 31
D 47
	struct nfsd *nd = nsd->nsd_nfsd;
	struct mbuf *mreq, *nam;
I 42
	struct timeval starttime;
E 47
I 47
	struct nfsd *nfsd = nsd->nsd_nfsd;
	struct nfsrv_descript *nd = NULL;
	struct mbuf *mreq;
E 47
	struct nfsuid *uidp;
E 42
D 47
	int error, cacherep, s;
	int sotype;
E 47
I 47
	int error = 0, cacherep, s, sotype, writes_todo;
	u_quad_t cur_usec;
E 47

I 47
#ifndef nolint
	cacherep = RC_DOIT;
	writes_todo = 0;
#endif
E 47
I 31
	s = splnet();
E 31
D 47
	if (nd == (struct nfsd *)0) {
		nsd->nsd_nfsd = nd = (struct nfsd *)
E 47
I 47
	if (nfsd == (struct nfsd *)0) {
		nsd->nsd_nfsd = nfsd = (struct nfsd *)
E 47
			malloc(sizeof (struct nfsd), M_NFSD, M_WAITOK);
D 47
		bzero((caddr_t)nd, sizeof (struct nfsd));
D 31
		nd->nd_cr.cr_ref = 1;
E 31
		nd->nd_procp = p;
D 31
		s = splnet();
E 31
I 31
		nd->nd_cr.cr_ref = 1;
E 31
D 46
		insque(nd, &nfsd_head);
E 46
I 46
		TAILQ_INSERT_TAIL(&nfsd_head, nd, nd_chain);
E 46
I 41
		nd->nd_nqlflag = NQL_NOVAL;
E 47
I 47
		bzero((caddr_t)nfsd, sizeof (struct nfsd));
		nfsd->nfsd_procp = p;
		TAILQ_INSERT_TAIL(&nfsd_head, nfsd, nfsd_chain);
E 47
E 41
D 31
		splx(s);
E 31
		nfs_numnfsd++;
	}
E 29
	/*
E 15
D 5
	 * Just loop arround doin our stuff until SIGKILL
E 5
I 5
D 29
	 * Just loop around doin our stuff until SIGKILL
E 29
I 29
	 * Loop getting rpc requests until SIGKILL.
E 29
E 5
	 */
	for (;;) {
D 29
		if (error = nfs_getreq(so, nfs_prog, nfs_vers, NFS_NPROCS-1,
D 4
			&nam, &mrep, &md, &dpos, &retxid, &proc, cr)) {
E 4
I 4
D 5
			&nam, &mrep, &md, &dpos, &retxid, &procid, cr)) {
E 5
I 5
D 15
		   &nam, &mrep, &md, &dpos, &retxid, &procid, cr, msk, mtch)) {
E 15
I 15
D 17
		   &nam, &mrep, &md, &dpos, &retxid, &procid, cr, &solock,
E 17
I 17
		   &nam, &mrep, &md, &dpos, &retxid, &procid, cr,
E 17
D 20
		   &msk, &mtch)) {
E 20
I 20
		   &msk, &mtch, &wascomp)) {
E 20
E 15
E 5
E 4
D 12
			m_freem(nam);
E 12
I 12
			if (nam)
				m_freem(nam);
D 15
			if (error == ERESTART || error == EINTR)
				RETURN (EINTR);
E 15
I 15
			if (error == EPIPE || error == EINTR ||
D 17
			    error == ERESTART)
E 17
I 17
			    error == ERESTART) {
				error = 0;
E 17
				goto bad;
E 29
I 29
D 47
		if ((nd->nd_flag & NFSD_REQINPROG) == 0) {
D 31
			s = splnet();
E 31
			while (nd->nd_slp == (struct nfssvc_sock *)0 &&
E 47
I 47
		if ((nfsd->nfsd_flag & NFSD_REQINPROG) == 0) {
			while (nfsd->nfsd_slp == (struct nfssvc_sock *)0 &&
E 47
D 46
				 (nfsd_head.nd_flag & NFSD_CHECKSLP) == 0) {
E 46
I 46
			    (nfsd_head_flag & NFSD_CHECKSLP) == 0) {
E 46
D 47
				nd->nd_flag |= NFSD_WAITING;
E 47
I 47
				nfsd->nfsd_flag |= NFSD_WAITING;
E 47
				nfsd_waiting++;
D 31
				if (tsleep((caddr_t)nd, PSOCK | PCATCH, "nfsd", 0)) {
					nfsd_waiting--;
					splx(s);
					goto done;
				}
E 31
I 31
D 47
				error = tsleep((caddr_t)nd, PSOCK | PCATCH, "nfsd", 0);
E 47
I 47
				error = tsleep((caddr_t)nfsd, PSOCK | PCATCH,
				    "nfsd", 0);
E 47
E 31
				nfsd_waiting--;
I 31
				if (error)
					goto done;
E 31
E 29
I 17
			}
E 17
D 29
			so->so_error = 0;
E 15
E 12
			continue;
		}
E 29
I 29
D 47
			if (nd->nd_slp == (struct nfssvc_sock *)0 &&
E 47
I 47
			if (nfsd->nfsd_slp == (struct nfssvc_sock *)0 &&
E 47
D 46
				(nfsd_head.nd_flag & NFSD_CHECKSLP)) {
				slp = nfssvc_sockhead.ns_next;
				while (slp != &nfssvc_sockhead) {
E 46
I 46
			    (nfsd_head_flag & NFSD_CHECKSLP) != 0) {
				for (slp = nfssvc_sockhead.tqh_first; slp != 0;
				    slp = slp->ns_chain.tqe_next) {
E 46
D 31
				    if ((slp->ns_flag & SLP_VALID) &&
					(slp->ns_flag & (SLP_NEEDQ | SLP_DISCONN))) {
E 31
I 31
				    if ((slp->ns_flag & (SLP_VALID | SLP_DOREC))
					== (SLP_VALID | SLP_DOREC)) {
					    slp->ns_flag &= ~SLP_DOREC;
I 32
					    slp->ns_sref++;
E 32
E 31
D 47
					    nd->nd_slp = slp;
E 47
I 47
					    nfsd->nfsd_slp = slp;
E 47
D 31
					    nd->nd_sref = slp->ns_sref;
E 31
					    break;
				    }
D 46
				    slp = slp->ns_next;
E 46
				}
D 46
				if (slp == &nfssvc_sockhead)
					nfsd_head.nd_flag &= ~NFSD_CHECKSLP;
E 46
I 46
				if (slp == 0)
					nfsd_head_flag &= ~NFSD_CHECKSLP;
E 46
			}
D 31
			if ((slp = nd->nd_slp) == (struct nfssvc_sock *)0) {
				splx(s);
				continue;
			}
			if (slp->ns_flag & SLP_DISCONN) {
				slp->ns_flag &= ~SLP_DISCONN;
				(void) nfs_sndlock(&slp->ns_solock,
					(struct nfsreq *)0);
				if (nd->nd_sref == slp->ns_sref)
					nfsrv_zapsock(slp, p);
				nfs_sndunlock(&slp->ns_solock);
E 31
I 31
D 32
			if ((slp = nd->nd_slp) == (struct nfssvc_sock *)0 ||
			    (slp->ns_flag & SLP_VALID) == 0) {
E 31
				nd->nd_slp = (struct nfssvc_sock *)0;
E 32
I 32
D 47
			if ((slp = nd->nd_slp) == (struct nfssvc_sock *)0)
E 47
I 47
			if ((slp = nfsd->nfsd_slp) == (struct nfssvc_sock *)0)
E 47
E 32
D 31
				splx(s);
E 31
				continue;
I 32
			if (slp->ns_flag & SLP_VALID) {
				if (slp->ns_flag & SLP_DISCONN)
					nfsrv_zapsock(slp);
				else if (slp->ns_flag & SLP_NEEDQ) {
					slp->ns_flag &= ~SLP_NEEDQ;
					(void) nfs_sndlock(&slp->ns_solock,
						(struct nfsreq *)0);
					nfsrv_rcv(slp->ns_so, (caddr_t)slp,
						M_WAIT);
					nfs_sndunlock(&slp->ns_solock);
				}
D 47
				error = nfsrv_dorec(slp, nd);
				nd->nd_flag |= NFSD_REQINPROG;
E 47
I 47
				error = nfsrv_dorec(slp, nfsd, &nd);
				cur_usec = (u_quad_t)time.tv_sec * 1000000 +
					(u_quad_t)time.tv_usec;
				if (error && slp->ns_tq.lh_first &&
				    slp->ns_tq.lh_first->nd_time <= cur_usec) {
					error = 0;
					cacherep = RC_DOIT;
					writes_todo = 1;
				} else
					writes_todo = 0;
				nfsd->nfsd_flag |= NFSD_REQINPROG;
E 47
E 32
			}
D 31
			if (slp->ns_flag & SLP_NEEDQ) {
E 31
I 31
D 32
			slp->ns_sref++;
			if (slp->ns_flag & SLP_DISCONN)
				nfsrv_zapsock(slp);
			else if (slp->ns_flag & SLP_NEEDQ) {
E 31
				slp->ns_flag &= ~SLP_NEEDQ;
				(void) nfs_sndlock(&slp->ns_solock,
					(struct nfsreq *)0);
D 31
				if (nd->nd_sref == slp->ns_sref) {
				    if (slp->ns_so->so_rcv.sb_cc > 0)
					nfsrv_rcv(slp->ns_so, (caddr_t)slp,
						M_WAIT);
				    else if (slp->ns_so->so_type == SOCK_STREAM)
					(void) nfsrv_getstream(slp, M_WAIT);
				}
E 31
I 31
				nfsrv_rcv(slp->ns_so, (caddr_t)slp, M_WAIT);
E 31
				nfs_sndunlock(&slp->ns_solock);
			}
			error = nfsrv_dorec(slp, nd);
D 31
			splx(s);
			if (error) {
				nd->nd_slp = (struct nfssvc_sock *)0;
				continue;
			}
E 31
			nd->nd_flag |= NFSD_REQINPROG;
E 32
D 31
		} else
E 31
I 31
		} else {
			error = 0;
E 31
D 47
			slp = nd->nd_slp;
E 47
I 47
			slp = nfsd->nfsd_slp;
E 47
I 31
		}
		if (error || (slp->ns_flag & SLP_VALID) == 0) {
D 47
			nd->nd_slp = (struct nfssvc_sock *)0;
			nd->nd_flag &= ~NFSD_REQINPROG;
E 47
I 47
			if (nd) {
				free((caddr_t)nd, M_NFSRVDESC);
				nd = NULL;
			}
			nfsd->nfsd_slp = (struct nfssvc_sock *)0;
			nfsd->nfsd_flag &= ~NFSD_REQINPROG;
E 47
			nfsrv_slpderef(slp);
			continue;
		}
		splx(s);
E 31
		so = slp->ns_so;
		sotype = so->so_type;
E 29
D 4
		if (error = (*(nfsrv_procs[proc]))(mrep, md, dpos,
E 4
I 4
D 5
		if (error = (*(nfsrv_procs[procid]))(mrep, md, dpos,
E 4
			cr, retxid, &mreq)) {
			m_freem(nam);
			nfsstats.srv_errs++;
			continue;
		} else
E 5
I 5
D 15
		switch (nfsrv_getcache(nam, retxid, procid, &mreq)) {
E 15
I 15
D 42

D 29
		if (nam)
			cacherep = nfsrv_getcache(nam, retxid, procid, &mreq);
E 29
I 29
		/*
		 * Check to see if authorization is needed.
		 */
		if (nd->nd_flag & NFSD_NEEDAUTH) {
			nd->nd_flag &= ~NFSD_NEEDAUTH;
			nsd->nsd_uid = nd->nd_cr.cr_uid;
			nsd->nsd_haddr =
			    mtod(slp->ns_nam, struct sockaddr_in *)->sin_addr.s_addr;
			nsd->nsd_authlen = nd->nd_authlen;
			(void) copyout(nd->nd_authstr, nsd->nsd_authstr,
				 nd->nd_authlen);
			(void) copyout((caddr_t)nsd, argp, sizeof (*nsd));
			return (ENEEDAUTH);
		}
E 42
I 42
D 47
		starttime = time;
E 47
E 42
		if (so->so_proto->pr_flags & PR_CONNREQUIRED)
			solockp = &slp->ns_solock;
E 29
		else
I 29
			solockp = (int *)0;
D 35
		nd->nd_repstat = 0;
E 35
D 47
		/*
		 * nam == nam2 for connectionless protocols such as UDP
		 * nam2 == NULL for connection based protocols to disable
		 *    recent request caching.
		 */
D 42
		nam2 = nd->nd_nam;

		if (nam2) {
E 42
I 42
		if (nam2 = nd->nd_nam) {
E 42
			nam = nam2;
D 42
			cacherep = nfsrv_getcache(nam2, nd, &mreq);
E 42
I 42
			cacherep = RC_CHECKIT;
E 42
		} else {
			nam = slp->ns_nam;
E 29
			cacherep = RC_DOIT;
I 29
		}
E 47
I 47
		if (nd) {
		    nd->nd_starttime = time;
		    if (nd->nd_nam2)
			nd->nd_nam = nd->nd_nam2;
		    else
			nd->nd_nam = slp->ns_nam;
E 47

D 47
		/*
I 42
		 * Check to see if authorization is needed.
		 */
		if (nd->nd_flag & NFSD_NEEDAUTH) {
			static int logauth = 0;
E 47
I 47
		    /*
		     * Check to see if authorization is needed.
		     */
		    if (nfsd->nfsd_flag & NFSD_NEEDAUTH) {
			nfsd->nfsd_flag &= ~NFSD_NEEDAUTH;
			nsd->nsd_haddr = mtod(nd->nd_nam,
			    struct sockaddr_in *)->sin_addr.s_addr;
			nsd->nsd_authlen = nfsd->nfsd_authlen;
			nsd->nsd_verflen = nfsd->nfsd_verflen;
			if (!copyout(nfsd->nfsd_authstr,nsd->nsd_authstr,
				nfsd->nfsd_authlen) &&
			    !copyout(nfsd->nfsd_verfstr, nsd->nsd_verfstr,
				nfsd->nfsd_verflen) &&
			    !copyout((caddr_t)nsd, argp, sizeof (*nsd)))
			    return (ENEEDAUTH);
			cacherep = RC_DROPIT;
		    } else
			cacherep = nfsrv_getcache(nd, slp, &mreq);
E 47

D 47
			nd->nd_flag &= ~NFSD_NEEDAUTH;
			/*
			 * Check for a mapping already installed.
			 */
D 46
			uidp = slp->ns_uidh[NUIDHASH(nd->nd_cr.cr_uid)];
			while (uidp) {
E 46
I 46
			for (uidp = NUIDHASH(slp, nd->nd_cr.cr_uid)->lh_first;
			    uidp != 0; uidp = uidp->nu_hash.le_next) {
E 46
				if (uidp->nu_uid == nd->nd_cr.cr_uid)
					break;
D 46
				uidp = uidp->nu_hnext;
E 46
			}
D 46
			if (!uidp) {
E 46
I 46
			if (uidp == 0) {
E 46
			    nsd->nsd_uid = nd->nd_cr.cr_uid;
			    if (nam2 && logauth++ == 0)
				log(LOG_WARNING, "Kerberized NFS using UDP\n");
			    nsd->nsd_haddr =
			      mtod(nam, struct sockaddr_in *)->sin_addr.s_addr;
			    nsd->nsd_authlen = nd->nd_authlen;
			    if (copyout(nd->nd_authstr, nsd->nsd_authstr,
				nd->nd_authlen) == 0 &&
				copyout((caddr_t)nsd, argp, sizeof (*nsd)) == 0)
				return (ENEEDAUTH);
			    cacherep = RC_DROPIT;
			}
		}
		if (cacherep == RC_CHECKIT)
			cacherep = nfsrv_getcache(nam2, nd, &mreq);

		/*
E 42
		 * Check for just starting up for NQNFS and send
		 * fake "try again later" replies to the NQNFS clients.
		 */
		if (notstarted && nqnfsstarttime <= time.tv_sec) {
E 47
I 47
		    /*
		     * Check for just starting up for NQNFS and send
		     * fake "try again later" replies to the NQNFS clients.
		     */
		    if (notstarted && nqnfsstarttime <= time.tv_sec) {
E 47
			if (modify_flag) {
				nqnfsstarttime = time.tv_sec + nqsrv_writeslack;
				modify_flag = 0;
			} else
				notstarted = 0;
D 47
		}
		if (notstarted) {
			if (nd->nd_nqlflag == NQL_NOVAL)
E 47
I 47
		    }
		    if (notstarted) {
			if ((nd->nd_flag & ND_NQNFS) == 0)
E 47
				cacherep = RC_DROPIT;
			else if (nd->nd_procnum != NFSPROC_WRITE) {
				nd->nd_procnum = NFSPROC_NOOP;
				nd->nd_repstat = NQNFS_TRYLATER;
				cacherep = RC_DOIT;
			} else
				modify_flag = 1;
D 47
		} else if (nd->nd_flag & NFSD_AUTHFAIL) {
			nd->nd_flag &= ~NFSD_AUTHFAIL;
E 47
I 47
		    } else if (nfsd->nfsd_flag & NFSD_AUTHFAIL) {
			nfsd->nfsd_flag &= ~NFSD_AUTHFAIL;
E 47
			nd->nd_procnum = NFSPROC_NOOP;
D 47
			nd->nd_repstat = NQNFS_AUTHERR;
E 47
I 47
			nd->nd_repstat = (NFSERR_AUTHERR | AUTH_TOOWEAK);
E 47
			cacherep = RC_DOIT;
I 47
		    }
E 47
		}

E 29
D 47
		switch (cacherep) {
E 15
		case RC_DOIT:
D 29
			if (error = (*(nfsrv_procs[procid]))(mrep, md, dpos,
D 27
				cr, retxid, &mreq, &repstat)) {
E 27
I 27
				cr, retxid, &mreq, &repstat, p)) {
E 27
I 8
D 15
				nfsrv_updatecache(nam, retxid, procid,
					FALSE, repstat, mreq);
E 8
				m_freem(nam);
E 15
				nfsstats.srv_errs++;
I 15
				if (nam) {
					nfsrv_updatecache(nam, retxid, procid,
						FALSE, repstat, mreq);
					m_freem(nam);
E 29
I 29
			error = (*(nfsrv_procs[nd->nd_procnum]))(nd,
				nd->nd_mrep, nd->nd_md, nd->nd_dpos, &nd->nd_cr,
				nam, &mreq);
I 31
			if (nd->nd_cr.cr_ref != 1) {
				printf("nfssvc cref=%d\n", nd->nd_cr.cr_ref);
				panic("nfssvc cref");
			}
E 47
I 47
		/*
		 * Loop to get all the write rpc relies that have been
		 * gathered together.
		 */
		do {
		    switch (cacherep) {
		    case RC_DOIT:
			if (writes_todo || (nd->nd_procnum == NFSPROC_WRITE &&
			    nfsrvw_procrastinate > 0 && !notstarted))
			    error = nfsrv_writegather(&nd, slp,
				nfsd->nfsd_procp, &mreq);
			else
			    error = (*(nfsrv3_procs[nd->nd_procnum]))(nd,
				slp, nfsd->nfsd_procp, &mreq);
			if (mreq == NULL)
				break;
E 47
E 31
			if (error) {
				if (nd->nd_procnum != NQNFSPROC_VACATED)
					nfsstats.srv_errs++;
D 47
				if (nam2) {
					nfsrv_updatecache(nam2, nd, FALSE, mreq);
					m_freem(nam2);
E 29
				}
E 47
I 47
				nfsrv_updatecache(nd, FALSE, mreq);
				if (nd->nd_nam2)
					m_freem(nd->nd_nam2);
E 47
E 15
				break;
			}
E 5
D 4
			nfsstats.srvrpccnt[proc]++;
E 4
I 4
D 29
			nfsstats.srvrpccnt[procid]++;
E 4
D 5
		m = mreq;
		siz = 0;
		while (m) {
			siz += m->m_len;
			m = m->m_next;
		}
		if (siz <= 0 || siz > 9216) {
			printf("mbuf siz=%d\n",siz);
			panic("Bad nfs svc reply");
		}
		error = nfs_udpsend(so, nam, mreq, 0, siz);
		m_freem(nam);
E 5
I 5
D 8
			nfsrv_updatecache(nam, retxid, procid, repstat, mreq);
E 8
I 8
D 15
			nfsrv_updatecache(nam, retxid, procid, TRUE,
				repstat, mreq);
E 15
I 15
			if (nam)
				nfsrv_updatecache(nam, retxid, procid, TRUE,
					repstat, mreq);
E 15
E 8
			mrep = (struct mbuf *)0;
E 29
I 29
			nfsstats.srvrpccnt[nd->nd_procnum]++;
D 47
			if (nam2)
				nfsrv_updatecache(nam2, nd, TRUE, mreq);
E 47
I 47
			nfsrv_updatecache(nd, TRUE, mreq);
E 47
			nd->nd_mrep = (struct mbuf *)0;
E 29
D 47
		case RC_REPLY:
E 47
I 47
		    case RC_REPLY:
E 47
			m = mreq;
			siz = 0;
			while (m) {
				siz += m->m_len;
				m = m->m_next;
			}
D 15
			if (siz <= 0 || siz > 9216) {
E 15
I 15
			if (siz <= 0 || siz > NFS_MAXPACKET) {
E 15
				printf("mbuf siz=%d\n",siz);
				panic("Bad nfs svc reply");
			}
D 7
			error = nfs_udpsend(so, nam, mreq, 0, siz);
E 7
I 7
D 15
			error = nfs_send(so, nam, mreq, 0, siz);
E 7
			m_freem(nam);
E 15
I 15
D 29
			mreq->m_pkthdr.len = siz;
			mreq->m_pkthdr.rcvif = (struct ifnet *)0;
I 20
			if (wascomp && compressreply[procid]) {
D 21
				m = nfs_compress(m);
				siz = m->m_pkthdr.len;
E 21
I 21
				mreq = nfs_compress(mreq);
				siz = mreq->m_pkthdr.len;
E 21
			}
E 29
I 29
			m = mreq;
			m->m_pkthdr.len = siz;
			m->m_pkthdr.rcvif = (struct ifnet *)0;
E 29
E 20
			/*
D 29
			 * For non-atomic protocols, prepend a Sun RPC
E 29
I 29
			 * For stream protocols, prepend a Sun RPC
E 29
			 * Record Mark.
			 */
D 29
			if (!sosendallatonce(so)) {
				M_PREPEND(mreq, sizeof(u_long), M_WAIT);
				*mtod(mreq, u_long *) = htonl(0x80000000 | siz);
E 29
I 29
			if (sotype == SOCK_STREAM) {
				M_PREPEND(m, NFSX_UNSIGNED, M_WAIT);
				*mtod(m, u_long *) = htonl(0x80000000 | siz);
E 29
			}
D 17
			if (so->so_proto->pr_flags & PR_CONNREQUIRED)
				nfs_solock(&solock, 0);
E 17
D 29
			error = nfs_send(so, nam, mreq, (struct nfsreq *)0);
D 17
			if (so->so_proto->pr_flags & PR_CONNREQUIRED)
				nfs_sounlock(&solock);
E 17
			if (nam)
				m_freem(nam);
E 15
			if (mrep)
				m_freem(mrep);
I 15
			if (error) {
				if (error == EPIPE || error == EINTR ||
				    error == ERESTART)
					goto bad;
				so->so_error = 0;
E 29
I 29
			if (solockp)
				(void) nfs_sndlock(solockp, (struct nfsreq *)0);
D 31
			if (nd->nd_sref == slp->ns_sref)
E 31
I 31
			if (slp->ns_flag & SLP_VALID)
E 31
D 47
			    error = nfs_send(so, nam2, m, (struct nfsreq *)0);
E 47
I 47
			    error = nfs_send(so, nd->nd_nam2, m, NULL);
E 47
			else {
			    error = EPIPE;
			    m_freem(m);
E 29
			}
I 42
			if (nfsrtton)
D 47
				nfsd_rt(&starttime, sotype, nd, nam, cacherep);
E 42
I 29
			if (nam2)
				MFREE(nam2, m);
E 47
I 47
				nfsd_rt(sotype, nd, cacherep);
			if (nd->nd_nam2)
				MFREE(nd->nd_nam2, m);
E 47
			if (nd->nd_mrep)
				m_freem(nd->nd_mrep);
			if (error == EPIPE)
D 31
				nfsrv_zapsock(slp, p);
E 31
I 31
				nfsrv_zapsock(slp);
E 31
			if (solockp)
				nfs_sndunlock(solockp);
D 31
			if (error == EINTR || error == ERESTART)
E 31
I 31
			if (error == EINTR || error == ERESTART) {
I 47
				free((caddr_t)nd, M_NFSRVDESC);
E 47
				nfsrv_slpderef(slp);
				s = splnet();
E 31
				goto done;
I 31
			}
E 31
E 29
E 15
			break;
D 47
		case RC_DROPIT:
E 47
I 47
		    case RC_DROPIT:
E 47
I 42
			if (nfsrtton)
D 47
				nfsd_rt(&starttime, sotype, nd, nam, cacherep);
E 47
I 47
				nfsd_rt(sotype, nd, cacherep);
E 47
E 42
D 29
			m_freem(mrep);
			m_freem(nam);
E 29
I 29
			m_freem(nd->nd_mrep);
D 47
			m_freem(nam2);
E 47
I 47
			m_freem(nd->nd_nam2);
E 47
E 29
			break;
D 47
		};
E 47
I 47
		    };
		    if (nd) {
			FREE((caddr_t)nd, M_NFSRVDESC);
			nd = NULL;
		    }

		    /*
		     * Check to see if there are outstanding writes that
		     * need to be serviced.
		     */
		    cur_usec = (u_quad_t)time.tv_sec * 1000000 +
			(u_quad_t)time.tv_usec;
		    s = splsoftclock();
		    if (slp->ns_tq.lh_first &&
			slp->ns_tq.lh_first->nd_time <= cur_usec) {
			cacherep = RC_DOIT;
			writes_todo = 1;
		    } else
			writes_todo = 0;
		    splx(s);
		} while (writes_todo);
E 47
I 29
D 31
		nd->nd_flag &= ~NFSD_REQINPROG;
		nd->nd_slp = (struct nfssvc_sock *)0;
E 31
I 31
		s = splnet();
D 47
		if (nfsrv_dorec(slp, nd)) {
			nd->nd_flag &= ~NFSD_REQINPROG;
			nd->nd_slp = (struct nfssvc_sock *)0;
E 47
I 47
		if (nfsrv_dorec(slp, nfsd, &nd)) {
			nfsd->nfsd_flag &= ~NFSD_REQINPROG;
			nfsd->nfsd_slp = NULL;
E 47
			nfsrv_slpderef(slp);
		}
E 31
E 29
I 28
#ifdef DIAGNOSTIC
		if (p->p_spare[0])
			panic("nfssvc: M_NAMEI");
		if (p->p_spare[1])
			panic("nfssvc: STARTSAVE");
#endif
E 28
E 5
	}
I 15
D 29
bad:
E 29
I 29
done:
D 31
	s = splnet();
E 31
D 46
	remque(nd);
E 46
I 46
D 47
	TAILQ_REMOVE(&nfsd_head, nd, nd_chain);
E 47
I 47
	TAILQ_REMOVE(&nfsd_head, nfsd, nfsd_chain);
E 47
E 46
	splx(s);
D 47
	free((caddr_t)nd, M_NFSD);
E 47
I 47
	free((caddr_t)nfsd, M_NFSD);
E 47
	nsd->nsd_nfsd = (struct nfsd *)0;
D 32
	if (--nfs_numnfsd == 0) {
		slp = nfssvc_sockhead.ns_next;
		while (slp != &nfssvc_sockhead) {
			if (slp->ns_flag & SLP_VALID)
D 31
				nfsrv_zapsock(slp, p);
E 31
I 31
				nfsrv_zapsock(slp);
			oslp = slp;
E 31
			slp = slp->ns_next;
I 31
			free((caddr_t)oslp, M_NFSSVC);
E 31
		}
I 31
		nfssvc_sockhead.ns_next = (struct nfssvc_sock *)0;
E 31
		nfsrv_cleancache();	/* And clear out server cache */
	}
E 32
I 32
	if (--nfs_numnfsd == 0)
		nfsrv_init(TRUE);	/* Reinitialize everything */
E 32
E 29
D 18
	RETURN (error);
E 18
I 18
	return (error);
E 18
E 15
}
I 2

D 3
#ifndef notyet
E 3
/*
D 29
 * Nfs pseudo system call for asynchronous i/o daemons.
 * These babies just pretend to be disk interrupt service routines
D 3
 * for client nfs. They are mainly here for read ahead
E 3
I 3
 * for client nfs. They are mainly here for read ahead/write behind.
E 3
 * Never returns unless it fails or gets killed
E 29
I 29
 * Asynchronous I/O daemons for client nfs.
D 42
 * These babies just pretend to be disk interrupt service routines.
 * They are mainly here for read ahead/write behind.
E 42
I 42
 * They do read-ahead and write-behind operations on the block I/O cache.
E 42
 * Never returns unless it fails or gets killed.
E 29
 */
I 47
int
E 47
D 17
async_daemon()
E 17
I 17
D 29
/* ARGSUSED */
async_daemon(p, uap, retval)
E 29
I 29
nfssvc_iod(p)
E 29
	struct proc *p;
D 29
	struct args *uap;
	int *retval;
E 29
E 17
{
D 45
	register struct buf *bp, *dp;
E 45
I 45
D 47
	register struct buf *bp;
E 47
I 47
	register struct buf *bp, *nbp;
E 47
E 45
I 24
	register int i, myiod;
E 24
D 29
	int error;
E 29
I 29
D 47
	int error = 0;
E 47
I 47
	struct vnode *vp;
	int error = 0, s;
E 47
E 29
I 3
D 24
	int myiod;
E 24
E 3

	/*
D 29
	 * Must be super user
	 */
D 23
	if (error = suser(u.u_cred, &u.u_acflag))
E 23
I 23
	if (error = suser(p->p_ucred, &p->p_acflag))
E 23
D 18
		RETURN (error);
E 18
I 18
		return (error);
E 18
I 3
	/*
E 29
	 * Assign my position or return error if too many already running
	 */
D 15
	if (nfs_asyncdaemons > MAX_ASYNCDAEMON)
E 15
I 15
D 24
	if (nfs_asyncdaemons > NFS_MAXASYNCDAEMON)
E 24
I 24
	myiod = -1;
	for (i = 0; i < NFS_MAXASYNCDAEMON; i++)
		if (nfs_asyncdaemon[i] == 0) {
			nfs_asyncdaemon[i]++;
			myiod = i;
			break;
		}
	if (myiod == -1)
E 24
E 15
D 18
		RETURN (EBUSY);
E 18
I 18
		return (EBUSY);
E 18
D 24
	myiod = nfs_asyncdaemons++;
E 24
I 24
	nfs_numasync++;
E 24
E 3
D 38
	dp = &nfs_bqueue;
E 38
	/*
D 3
	 * Just loop arround doin our stuff until SIGKILL
E 3
I 3
	 * Just loop around doin our stuff until SIGKILL
E 3
	 */
	for (;;) {
D 24
		while (dp->b_actf == NULL) {
D 3
			nfs_iodwant++;
			sleep((caddr_t)&nfs_iodwant, PZERO+1);
E 3
I 3
D 17
			nfs_iodwant[myiod] = u.u_procp;
E 17
I 17
			nfs_iodwant[myiod] = p;
E 17
D 6
			sleep((caddr_t)&nfs_iodwant[myiod], PZERO+1);
E 6
I 6
D 12
			tsleep((caddr_t)&nfs_iodwant[myiod], PZERO+1, 
				SLP_NFS_IOD, 0);
E 12
I 12
			if (error = tsleep((caddr_t)&nfs_iodwant[myiod],
D 13
			    PRIBIO | PCATCH, "nfsidl", 0))
E 13
I 13
D 15
			    PWAIT | PCATCH, "nfsidl", 0))
E 15
I 15
				PWAIT | PCATCH, "nfsidl", 0))
E 15
E 13
D 18
				RETURN (error);
E 18
I 18
				return (error);
E 24
I 24
D 38
		while (dp->b_actf == NULL && error == 0) {
E 38
I 38
D 39
		while (nfs_bqueuehead == NULL && error == 0) {
E 39
I 39
D 44
		while (nfs_bufq.qe_next == NULL && error == 0) {
E 44
I 44
D 47
		while (nfs_bufq.tqh_first == NULL && error == 0) {
E 44
E 39
E 38
D 26
			nfs_iodwant[myiod] = u.u_procp;
E 26
I 26
D 27
			nfs_iodwant[myiod] = curproc;
E 27
I 27
			nfs_iodwant[myiod] = p;
E 27
E 26
			error = tsleep((caddr_t)&nfs_iodwant[myiod],
				PWAIT | PCATCH, "nfsidl", 0);
D 42
			nfs_iodwant[myiod] = (struct proc *)0;
E 42
E 24
E 18
E 12
E 6
E 3
		}
D 24
		/* Take one off the end of the list */
		bp = dp->b_actl;
		if (bp->b_actl == dp) {
			dp->b_actf = dp->b_actl = (struct buf *)0;
		} else {
			dp->b_actl = bp->b_actl;
			bp->b_actl->b_actf = dp;
E 24
I 24
D 38
		while (dp->b_actf != NULL) {
			/* Take one off the end of the list */
			bp = dp->b_actl;
			if (bp->b_actl == dp) {
				dp->b_actf = dp->b_actl = (struct buf *)0;
			} else {
				dp->b_actl = bp->b_actl;
				bp->b_actl->b_actf = dp;
			}
E 38
I 38
D 39
		while ((bp = nfs_bqueuehead) != NULL) {
E 39
I 39
D 44
		while ((bp = nfs_bufq.qe_next) != NULL) {
E 44
I 44
		while ((bp = nfs_bufq.tqh_first) != NULL) {
E 44
E 39
			/* Take one off the front of the list */
D 39
			if (dp = bp->b_actf)
				dp->b_actb = bp->b_actb;
			else
				nfs_bqueuetail = bp->b_actb;
			*bp->b_actb = dp;
E 39
I 39
D 44
			queue_remove(&nfs_bufq, bp, struct buf *, b_freelist);
E 44
I 44
			TAILQ_REMOVE(&nfs_bufq, bp, b_freelist);
E 44
E 39
E 38
D 29
			(void) nfs_doio(bp);
E 29
I 29
D 42
			(void) nfs_doio(bp, (struct proc *)0);
E 42
I 42
			if (bp->b_flags & B_READ)
			    (void) nfs_doio(bp, bp->b_rcred, (struct proc *)0);
			else
			    (void) nfs_doio(bp, bp->b_wcred, (struct proc *)0);
E 42
E 29
E 24
		}
D 24
		(void) nfs_doio(bp);
E 24
I 24
		if (error) {
			nfs_asyncdaemon[myiod] = 0;
			nfs_numasync--;
			return (error);
		}
E 24
	}
E 47
I 47
	    while (nfs_bufq.tqh_first == NULL && error == 0) {
		nfs_iodwant[myiod] = p;
		error = tsleep((caddr_t)&nfs_iodwant[myiod],
			PWAIT | PCATCH, "nfsidl", 0);
	    }
	    while ((bp = nfs_bufq.tqh_first) != NULL) {
		/* Take one off the front of the list */
		TAILQ_REMOVE(&nfs_bufq, bp, b_freelist);
		if (bp->b_flags & B_READ)
		    (void) nfs_doio(bp, bp->b_rcred, (struct proc *)0);
		else do {
		    /*
		     * Look for a delayed write for the same vnode, so I can do 
		     * it now. We must grab it before calling nfs_doio() to
		     * avoid any risk of the vnode getting vclean()'d while
		     * we are doing the write rpc.
		     */
		    vp = bp->b_vp;
		    s = splbio();
		    for (nbp = vp->v_dirtyblkhd.lh_first; nbp;
			nbp = nbp->b_vnbufs.le_next) {
			if ((nbp->b_flags &
			    (B_BUSY|B_DELWRI|B_NEEDCOMMIT|B_NOCACHE))!=B_DELWRI)
			    continue;
			bremfree(nbp);
			nbp->b_flags |= (B_BUSY|B_ASYNC);
			break;
		    }
		    splx(s);
		    /*
		     * For the delayed write, do the first part of nfs_bwrite()
		     * up to, but not including nfs_strategy().
		     */
		    if (nbp) {
			nbp->b_flags &= ~(B_READ|B_DONE|B_ERROR|B_DELWRI);
			reassignbuf(nbp, nbp->b_vp);
			nbp->b_vp->v_numoutput++;
		    }
		    (void) nfs_doio(bp, bp->b_wcred, (struct proc *)0);
		} while (bp = nbp);
	    }
	    if (error) {
		nfs_asyncdaemon[myiod] = 0;
		nfs_numasync--;
		return (error);
	    }
	}
E 47
I 29
}

/*
 * Shut down a socket associated with an nfssvc_sock structure.
 * Should be called with the send lock set, if required.
 * The trick here is to increment the sref at the start, so that the nfsds
 * will stop using it and clear ns_flag at the end so that it will not be
 * reassigned during cleanup.
 */
I 47
void
E 47
D 31
nfsrv_zapsock(slp, p)
E 31
I 31
nfsrv_zapsock(slp)
E 31
	register struct nfssvc_sock *slp;
D 31
	struct proc *p;
E 31
{
D 46
	register struct nfsuid *nuidp, *onuidp;
E 46
I 46
	register struct nfsuid *nuidp, *nnuidp;
E 46
D 47
	register int i;
E 47
I 47
	register struct nfsrv_descript *nwp, *nnwp;
E 47
	struct socket *so;
	struct file *fp;
	struct mbuf *m;
I 47
	int s;
E 47

I 31
D 32
	slp->ns_flag = 0;
E 32
I 32
	slp->ns_flag &= ~SLP_ALLFLAGS;
E 32
E 31
D 47
	if (fp = slp->ns_fp) {
E 47
I 47
	fp = slp->ns_fp;
	if (fp) {
E 47
		slp->ns_fp = (struct file *)0;
D 31
		slp->ns_sref++;
E 31
		so = slp->ns_so;
I 31
		so->so_upcall = NULL;
E 31
		soshutdown(so, 2);
D 31
		closef(fp, p);
E 31
I 31
		closef(fp, (struct proc *)0);
E 31
		if (slp->ns_nam)
			MFREE(slp->ns_nam, m);
		m_freem(slp->ns_raw);
		m_freem(slp->ns_rec);
D 46
		nuidp = slp->ns_lrunext;
		while (nuidp != (struct nfsuid *)slp) {
			onuidp = nuidp;
			nuidp = nuidp->nu_lrunext;
			free((caddr_t)onuidp, M_NFSUID);
E 46
I 46
		for (nuidp = slp->ns_uidlruhead.tqh_first; nuidp != 0;
		    nuidp = nnuidp) {
			nnuidp = nuidp->nu_lru.tqe_next;
			LIST_REMOVE(nuidp, nu_hash);
			TAILQ_REMOVE(&slp->ns_uidlruhead, nuidp, nu_lru);
I 47
			if (nuidp->nu_flag & NU_NAM)
				m_freem(nuidp->nu_nam);
E 47
			free((caddr_t)nuidp, M_NFSUID);
E 46
		}
I 47
		s = splsoftclock();
		for (nwp = slp->ns_tq.lh_first; nwp; nwp = nnwp) {
			nnwp = nwp->nd_tq.le_next;
			LIST_REMOVE(nwp, nd_tq);
			free((caddr_t)nwp, M_NFSRVDESC);
		}
		LIST_INIT(&slp->ns_tq);
		splx(s);
E 47
D 46
		slp->ns_lrunext = slp->ns_lruprev = (struct nfsuid *)slp;
		for (i = 0; i < NUIDHASHSIZ; i++)
			slp->ns_uidh[i] = (struct nfsuid *)0;
E 46
D 31
		slp->ns_flag = 0;
E 31
	}
}

/*
 * Get an authorization string for the uid by having the mount_nfs sitting
 * on this mount point porpous out of the kernel and do it.
 */
D 47
nfs_getauth(nmp, rep, cred, auth_type, auth_str, auth_len)
E 47
I 47
int
nfs_getauth(nmp, rep, cred, auth_str, auth_len, verf_str, verf_len, key)
E 47
	register struct nfsmount *nmp;
	struct nfsreq *rep;
	struct ucred *cred;
D 47
	int *auth_type;
E 47
	char **auth_str;
	int *auth_len;
I 47
	char *verf_str;
	int *verf_len;
	NFSKERBKEY_T key;		/* return session key */
E 47
{
	int error = 0;

	while ((nmp->nm_flag & NFSMNT_WAITAUTH) == 0) {
		nmp->nm_flag |= NFSMNT_WANTAUTH;
		(void) tsleep((caddr_t)&nmp->nm_authtype, PSOCK,
			"nfsauth1", 2 * hz);
D 47
		if (error = nfs_sigintr(nmp, rep, rep->r_procp)) {
E 47
I 47
		error = nfs_sigintr(nmp, rep, rep->r_procp);
		if (error) {
E 47
			nmp->nm_flag &= ~NFSMNT_WANTAUTH;
			return (error);
		}
	}
	nmp->nm_flag &= ~(NFSMNT_WAITAUTH | NFSMNT_WANTAUTH);
	nmp->nm_authstr = *auth_str = (char *)malloc(RPCAUTH_MAXSIZ, M_TEMP, M_WAITOK);
I 47
	nmp->nm_authlen = RPCAUTH_MAXSIZ;
	nmp->nm_verfstr = verf_str;
	nmp->nm_verflen = *verf_len;
E 47
	nmp->nm_authuid = cred->cr_uid;
	wakeup((caddr_t)&nmp->nm_authstr);

	/*
	 * And wait for mount_nfs to do its stuff.
	 */
	while ((nmp->nm_flag & NFSMNT_HASAUTH) == 0 && error == 0) {
		(void) tsleep((caddr_t)&nmp->nm_authlen, PSOCK,
			"nfsauth2", 2 * hz);
		error = nfs_sigintr(nmp, rep, rep->r_procp);
	}
	if (nmp->nm_flag & NFSMNT_AUTHERR) {
		nmp->nm_flag &= ~NFSMNT_AUTHERR;
		error = EAUTH;
	}
	if (error)
		free((caddr_t)*auth_str, M_TEMP);
	else {
D 47
		*auth_type = nmp->nm_authtype;
E 47
		*auth_len = nmp->nm_authlen;
I 47
		*verf_len = nmp->nm_verflen;
		bcopy((caddr_t)nmp->nm_key, (caddr_t)key, sizeof (key));
E 47
	}
	nmp->nm_flag &= ~NFSMNT_HASAUTH;
	nmp->nm_flag |= NFSMNT_WAITAUTH;
	if (nmp->nm_flag & NFSMNT_WANTAUTH) {
		nmp->nm_flag &= ~NFSMNT_WANTAUTH;
		wakeup((caddr_t)&nmp->nm_authtype);
	}
	return (error);
I 31
}

/*
I 47
 * Get a nickname authenticator and verifier.
 */
int
nfs_getnickauth(nmp, cred, auth_str, auth_len, verf_str, verf_len)
	struct nfsmount *nmp;
	struct ucred *cred;
	char **auth_str;
	int *auth_len;
	char *verf_str;
	int verf_len;
{
	register struct nfsuid *nuidp;
	register u_long *nickp, *verfp;
	struct timeval ktvin, ktvout;
	NFSKERBKEYSCHED_T keys;	/* stores key schedule */

#ifdef DIAGNOSTIC
	if (verf_len < (4 * NFSX_UNSIGNED))
		panic("nfs_getnickauth verf too small");
#endif
	for (nuidp = NMUIDHASH(nmp, cred->cr_uid)->lh_first;
	    nuidp != 0; nuidp = nuidp->nu_hash.le_next) {
		if (nuidp->nu_cr.cr_uid == cred->cr_uid)
			break;
	}
	if (!nuidp || nuidp->nu_expire < time.tv_sec)
		return (EACCES);

	/*
	 * Move to the end of the lru list (end of lru == most recently used).
	 */
	TAILQ_REMOVE(&nmp->nm_uidlruhead, nuidp, nu_lru);
	TAILQ_INSERT_TAIL(&nmp->nm_uidlruhead, nuidp, nu_lru);

	nickp = (u_long *)malloc(2 * NFSX_UNSIGNED, M_TEMP, M_WAITOK);
	*nickp++ = txdr_unsigned(RPCAKN_NICKNAME);
	*nickp = txdr_unsigned(nuidp->nu_nickname);
	*auth_str = (char *)nickp;
	*auth_len = 2 * NFSX_UNSIGNED;

	/*
	 * Now we must encrypt the verifier and package it up.
	 */
	verfp = (u_long *)verf_str;
	*verfp++ = txdr_unsigned(RPCAKN_NICKNAME);
	if (time.tv_sec > nuidp->nu_timestamp.tv_sec ||
	    (time.tv_sec == nuidp->nu_timestamp.tv_sec &&
	     time.tv_usec > nuidp->nu_timestamp.tv_usec))
		nuidp->nu_timestamp = time;
	else
		nuidp->nu_timestamp.tv_usec++;
	ktvin.tv_sec = txdr_unsigned(nuidp->nu_timestamp.tv_sec);
	ktvin.tv_usec = txdr_unsigned(nuidp->nu_timestamp.tv_usec);

	/*
	 * Now encrypt the timestamp verifier in ecb mode using the session
	 * key.
	 */
#ifdef NFSKERB
	XXX
#endif

	*verfp++ = ktvout.tv_sec;
	*verfp++ = ktvout.tv_usec;
	*verfp = 0;
	return (0);
}

/*
 * Save the current nickname in a hash list entry on the mount point.
 */
int
nfs_savenickauth(nmp, cred, len, key, mdp, dposp, mrep)
	register struct nfsmount *nmp;
	struct ucred *cred;
	int len;
	NFSKERBKEY_T key;
	struct mbuf **mdp;
	char **dposp;
	struct mbuf *mrep;
{
	register struct nfsuid *nuidp;
	register u_long *tl;
	register long t1;
	struct mbuf *md = *mdp;
	struct timeval ktvin, ktvout;
	u_long nick;
	NFSKERBKEYSCHED_T keys;
	char *dpos = *dposp, *cp2;
	int deltasec, error = 0;

	if (len == (3 * NFSX_UNSIGNED)) {
		nfsm_dissect(tl, u_long *, 3 * NFSX_UNSIGNED);
		ktvin.tv_sec = *tl++;
		ktvin.tv_usec = *tl++;
		nick = fxdr_unsigned(u_long, *tl);

		/*
		 * Decrypt the timestamp in ecb mode.
		 */
#ifdef NFSKERB
		XXX
#endif
		ktvout.tv_sec = fxdr_unsigned(long, ktvout.tv_sec);
		ktvout.tv_usec = fxdr_unsigned(long, ktvout.tv_usec);
		deltasec = time.tv_sec - ktvout.tv_sec;
		if (deltasec < 0)
			deltasec = -deltasec;
		/*
		 * If ok, add it to the hash list for the mount point.
		 */
		if (deltasec <= NFS_KERBCLOCKSKEW) {
			if (nmp->nm_numuids < nuidhash_max) {
				nmp->nm_numuids++;
				nuidp = (struct nfsuid *)
				   malloc(sizeof (struct nfsuid), M_NFSUID,
					M_WAITOK);
			} else {
				nuidp = nmp->nm_uidlruhead.tqh_first;
				LIST_REMOVE(nuidp, nu_hash);
				TAILQ_REMOVE(&nmp->nm_uidlruhead, nuidp,
					nu_lru);
			}
			nuidp->nu_flag = 0;
			nuidp->nu_cr.cr_uid = cred->cr_uid;
			nuidp->nu_expire = time.tv_sec + NFS_KERBTTL;
			nuidp->nu_timestamp = ktvout;
			nuidp->nu_nickname = nick;
			bcopy(key, nuidp->nu_key, sizeof (key));
			TAILQ_INSERT_TAIL(&nmp->nm_uidlruhead, nuidp,
				nu_lru);
			LIST_INSERT_HEAD(NMUIDHASH(nmp, cred->cr_uid),
				nuidp, nu_hash);
		}
	} else
		nfsm_adv(nfsm_rndup(len));
nfsmout:
	*mdp = md;
	*dposp = dpos;
	return (error);
}

/*
E 47
 * Derefence a server socket structure. If it has no more references and
 * is no longer valid, you can throw it away.
 */
void
nfsrv_slpderef(slp)
	register struct nfssvc_sock *slp;
{
	if (--(slp->ns_sref) == 0 && (slp->ns_flag & SLP_VALID) == 0) {
I 34
#ifdef NOTYET
E 34
D 46
		slp->ns_prev->ns_next = slp->ns_next;
		slp->ns_next->ns_prev = slp->ns_prev;
E 46
I 46
		TAILQ_REMOVE(&nfssvc_sockhead, slp, ns_chain);
E 46
		free((caddr_t)slp, M_NFSSVC);
I 34
#else
		if (slp->ns_flag & SLP_DEREFFREE)
			panic("deref dup free 0x%x of deref free\n", slp);
		else {
			slp->ns_prev->ns_next = slp->ns_next;
			slp->ns_next->ns_prev = slp->ns_prev;
		}
		if (slp->ns_flag & SLP_CLRFREE)
			panic("deref dup free 0x%x of clrall free\n", slp);
		slp->ns_flag |= SLP_DEREFFREE;
		printf("Free deref sock 0x%x\n", slp);
#endif
E 34
I 32
	}
}

/*
 * Initialize the data structures for the server.
 * Handshake with any new nfsds starting up to avoid any chance of
 * corruption.
 */
void
nfsrv_init(terminating)
	int terminating;
{
D 46
	register struct nfssvc_sock *slp;
	struct nfssvc_sock *oslp;
E 46
I 46
	register struct nfssvc_sock *slp, *nslp;
E 46

D 46
	if (nfssvc_sockhead.ns_flag & SLP_INIT)
E 46
I 46
	if (nfssvc_sockhead_flag & SLP_INIT)
E 46
		panic("nfsd init");
D 46
	nfssvc_sockhead.ns_flag |= SLP_INIT;
E 46
I 46
	nfssvc_sockhead_flag |= SLP_INIT;
E 46
	if (terminating) {
D 46
		slp = nfssvc_sockhead.ns_next;
		while (slp != &nfssvc_sockhead) {
E 46
I 46
		for (slp = nfssvc_sockhead.tqh_first; slp != 0; slp = nslp) {
			nslp = slp->ns_chain.tqe_next;
E 46
			if (slp->ns_flag & SLP_VALID)
				nfsrv_zapsock(slp);
D 46
			slp->ns_next->ns_prev = slp->ns_prev;
			slp->ns_prev->ns_next = slp->ns_next;
			oslp = slp;
			slp = slp->ns_next;
I 34
#ifdef NOTYET
E 34
			free((caddr_t)oslp, M_NFSSVC);
E 46
I 46
			TAILQ_REMOVE(&nfssvc_sockhead, slp, ns_chain);
			free((caddr_t)slp, M_NFSSVC);
E 46
I 34
#else
			if (oslp->ns_flag & SLP_DEREFFREE)
				panic("clrall dup free 0x%x of deref free\n",
					oslp);
			if (oslp->ns_flag & SLP_CLRFREE)
				panic("clrall dup free 0x%x of clrall free\n",
					oslp);
			oslp->ns_flag |= SLP_CLRFREE;
			printf("Free all socks 0x%x\n", oslp);
#endif
E 34
		}
		nfsrv_cleancache();	/* And clear out server cache */
	}
I 46

	TAILQ_INIT(&nfssvc_sockhead);
	nfssvc_sockhead_flag &= ~SLP_INIT;
	if (nfssvc_sockhead_flag & SLP_WANTINIT) {
		nfssvc_sockhead_flag &= ~SLP_WANTINIT;
		wakeup((caddr_t)&nfssvc_sockhead);
	}

	TAILQ_INIT(&nfsd_head);
	nfsd_head_flag &= ~NFSD_CHECKSLP;

E 46
	nfs_udpsock = (struct nfssvc_sock *)
	    malloc(sizeof (struct nfssvc_sock), M_NFSSVC, M_WAITOK);
I 34
	printf("Alloc nfs_udpsock 0x%x\n", nfs_udpsock);
E 34
	bzero((caddr_t)nfs_udpsock, sizeof (struct nfssvc_sock));
I 46
D 47
	nfs_udpsock->ns_uidhashtbl =
	    hashinit(NUIDHASHSIZ, M_NFSSVC, &nfs_udpsock->ns_uidhash);
E 47
	TAILQ_INIT(&nfs_udpsock->ns_uidlruhead);
	TAILQ_INSERT_HEAD(&nfssvc_sockhead, nfs_udpsock, ns_chain);

E 46
	nfs_cltpsock = (struct nfssvc_sock *)
	    malloc(sizeof (struct nfssvc_sock), M_NFSSVC, M_WAITOK);
I 34
	printf("Alloc nfs_cltpsock 0x%x\n", nfs_cltpsock);
E 34
	bzero((caddr_t)nfs_cltpsock, sizeof (struct nfssvc_sock));
D 46
	nfssvc_sockhead.ns_next = nfs_udpsock;
	nfs_udpsock->ns_next = nfs_cltpsock;
	nfs_cltpsock->ns_next = &nfssvc_sockhead;
	nfssvc_sockhead.ns_prev = nfs_cltpsock;
	nfs_cltpsock->ns_prev = nfs_udpsock;
	nfs_udpsock->ns_prev = &nfssvc_sockhead;
	nfs_udpsock->ns_lrunext = nfs_udpsock->ns_lruprev =
		(struct nfsuid *)nfs_udpsock;
	nfs_cltpsock->ns_lrunext = nfs_cltpsock->ns_lruprev =
		(struct nfsuid *)nfs_cltpsock;
	nfsd_head.nd_next = nfsd_head.nd_prev = &nfsd_head;
	nfsd_head.nd_flag = 0;
	nfssvc_sockhead.ns_flag &= ~SLP_INIT;
	if (nfssvc_sockhead.ns_flag & SLP_WANTINIT) {
		nfssvc_sockhead.ns_flag &= ~SLP_WANTINIT;
		wakeup((caddr_t)&nfssvc_sockhead);
E 32
	}
E 46
I 46
D 47
	nfs_cltpsock->ns_uidhashtbl =
	    hashinit(NUIDHASHSIZ, M_NFSSVC, &nfs_cltpsock->ns_uidhash);
E 47
	TAILQ_INIT(&nfs_cltpsock->ns_uidlruhead);
	TAILQ_INSERT_TAIL(&nfssvc_sockhead, nfs_cltpsock, ns_chain);
E 46
I 42
}

/*
 * Add entries to the server monitor log.
 */
static void
D 47
nfsd_rt(startp, sotype, nd, nam, cacherep)
	struct timeval *startp;
E 47
I 47
nfsd_rt(sotype, nd, cacherep)
E 47
	int sotype;
D 47
	register struct nfsd *nd;
	struct mbuf *nam;
E 47
I 47
	register struct nfsrv_descript *nd;
E 47
	int cacherep;
{
	register struct drt *rt;

	rt = &nfsdrt.drt[nfsdrt.pos];
	if (cacherep == RC_DOIT)
		rt->flag = 0;
	else if (cacherep == RC_REPLY)
		rt->flag = DRT_CACHEREPLY;
	else
		rt->flag = DRT_CACHEDROP;
	if (sotype == SOCK_STREAM)
		rt->flag |= DRT_TCP;
D 47
	if (nd->nd_nqlflag != NQL_NOVAL)
E 47
I 47
	if (nd->nd_flag & ND_NQNFS)
E 47
		rt->flag |= DRT_NQNFS;
I 47
	else if (nd->nd_flag & ND_NFSV3)
		rt->flag |= DRT_NFSV3;
E 47
	rt->proc = nd->nd_procnum;
D 47
	if (mtod(nam, struct sockaddr *)->sa_family == AF_INET)
		rt->ipadr = mtod(nam, struct sockaddr_in *)->sin_addr.s_addr;
E 47
I 47
	if (mtod(nd->nd_nam, struct sockaddr *)->sa_family == AF_INET)
	    rt->ipadr = mtod(nd->nd_nam, struct sockaddr_in *)->sin_addr.s_addr;
E 47
	else
D 47
		rt->ipadr = INADDR_ANY;
	rt->resptime = ((time.tv_sec - startp->tv_sec) * 1000000) +
		(time.tv_usec - startp->tv_usec);
E 47
I 47
	    rt->ipadr = INADDR_ANY;
	rt->resptime = ((time.tv_sec - nd->nd_starttime.tv_sec) * 1000000) +
		(time.tv_usec - nd->nd_starttime.tv_usec);
E 47
	rt->tstamp = time;
	nfsdrt.pos = (nfsdrt.pos + 1) % NFSRTTLOGSIZ;
E 42
E 31
E 29
}
D 3
#endif
E 3
E 2
E 1
