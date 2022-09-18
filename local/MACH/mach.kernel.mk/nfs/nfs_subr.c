/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	nfs_subr.c,v $
 * Revision 2.14  91/04/03  13:10:00  mbj
 * 	nfs changes for omron
 * 	[91/03/07  11:32:38  rvb]
 * 
 * Revision 2.13  90/07/03  16:46:35  mrt
 * 	Removed include of vm_pager.h. It was for the obsolete non-
 * 	external pager interface.
 * 	[90/06/29            mrt]
 * 	   Merged mt Xinu 2.6MSD Changes.
 * 	   [90/05/17  18:10:48  mrt]
 * 
 * Revision 2.11.1.1  90/05/22  15:16:08  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:10:48  mrt]
 * 
 * Revision 2.12  89/10/03  19:26:39  rpd
 * 	Merged with NeXT.  Only affects NBC code.
 * 	[89/10/02  15:56:31  rpd]
 * 
 * Revision 2.11  89/08/02  08:04:47  jsb
 * 	Eliminated MACH conditionals. Replaced kallocs with zallocs.
 * 	[89/07/31  16:23:15  jsb]
 * 
 * Revision 2.10  89/06/12  14:52:15  jsb
 * 	Changed initialization of vm_info fields to use vm_info_init.
 * 	[89/06/12  11:36:09  jsb]
 * 
 * Revision 2.9  89/05/30  10:39:54  rvb
 * 	Mips has needs cons to be an array.
 * 	[89/05/30  08:30:22  rvb]
 * 
 * Revision 2.8  89/05/11  15:40:10  gm0w
 * 	Minor fixes for NBC code from rfr.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.7  89/05/01  18:01:48  rpd
 * 	Fixed bug in nattr_to_vattr which stripped type info from mode.
 * 	[89/05/01  17:52:56  jsb]
 * 
 * Revision 2.6  89/04/22  15:25:52  gm0w
 * 	Minor changes for HC.
 * 	[89/04/22            gm0w]
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	Removed FIFO code.  Picked up new NBC code from rfr.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.5  89/03/09  20:54:25  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:09:37  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/01/31  01:21:22  rpd
 * 	Multimax hackaround due to lack of virtual console.
 * 	[88/11/28            dlb]
 * 
 * Revision 2.2  89/01/18  00:56:10  jsb
 * 	Include file references; invisibly rename interrupted() to avoid
 * 	conflict with variable of same name in kdb; change vm_pager_null to
 * 	MEMORY_OBJECT_NULL.
 * 	[89/01/17  14:15:55  jsb]
 * 
 *
 * 28-Oct-87  Peter King (king) at NeXT, Inc.
 *	Original Sun source, ported to Mach.
 */ 

/* @(#)nfs_subr.c	1.5 87/09/14 3.2/4.3NFSSRC */

#include <mach_nbc.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <kern/mfs.h>
#include <sys/kernel.h>
#include <sys/buf.h>
#include <sys/inode.h>
#include <sys/proc.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <sys/ioctl.h>
#include <sys/tty.h>	/*  Added for new extern declaration  */
#include <net/if.h>
#include <netinet/in.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/auth.h>
#include <rpc/clnt.h>
#include <nfs/nfs.h>
#include <nfs/nfs_clnt.h>
#include <nfs/rnode.h>

/* avoid conflict with variable of same name in kdb */
#define interrupted()	nfsInterrupted()

#ifdef	NFSDEBUG
int nfsdebug = 0;
#endif

#ifdef	multimax

/*
 *	Multimax does not support virtual console.  Following hackaround
 *	MUST MATCH mmax/conf.c
 */
extern struct tty	slc_tty[];
#define cons		(slc_tty[0])

#else	multimax

/*  Extern var 'cons' was added to take the place of consdev(and rconsdev).  
    'cons' is initially defined in ../vax/cons.c  */
#ifdef	mips
extern struct tty cons[];
#else	mips
#ifdef	luna88k
extern	struct	tty cons_tty[];
#define cons	(cons_tty[0])
#else	luna88k
extern struct tty cons;
#endif	luna88k
#endif	mips


#endif	multimax
struct inode *iget();
struct rnode *rfind();

/*
 * Client side utilities
 */

/*
 * client side statistics
 */
struct {
	int	nclsleeps;		/* client handle waits */
	int	nclgets;		/* client handle gets */
	int	ncalls;			/* client requests */
	int	nbadcalls;		/* rpc failures */
	int	reqs[32];		/* count of each request */
} clstat;


#define MAXCLIENTS	6
struct chtab {
	int	ch_timesused;
	bool_t	ch_inuse;
	CLIENT	*ch_client;
} chtable[MAXCLIENTS];

int	clwanted = 0;

CLIENT *
clget(mi, cred)
	struct mntinfo *mi;
	struct ucred *cred;
{
	register struct chtab *ch;
	int retrans;

	/*
	 * If soft mount and server is down just try once
	 */
	if (!mi->mi_hard && mi->mi_down) {
		retrans = 1;
	} else {
		retrans = mi->mi_retrans;
	}

	/*
	 * Find an unused handle or create one if not at limit yet.
	 */
	for (;;) {
		clstat.nclgets++;
		for (ch = chtable; ch < &chtable[MAXCLIENTS]; ch++) {
			if (!ch->ch_inuse) {
				ch->ch_inuse = TRUE;
				if (ch->ch_client == NULL) {
					ch->ch_client =
					    clntkudp_create(&mi->mi_addr,
					    NFS_PROGRAM, NFS_VERSION,
					    retrans, cred);
				} else {
					clntkudp_init(ch->ch_client,
					    &mi->mi_addr, retrans, cred);
				}
				if (ch->ch_client == NULL) {
					panic("clget: null client");
				}
				ch->ch_timesused++;
				return (ch->ch_client);
			}
		}
		/*
		 * If we got here there are no available handles
		 */
		clwanted++;
		clstat.nclsleeps++;
		(void) sleep((caddr_t)chtable, PRIBIO);
	}
}

clfree(cl)
	CLIENT *cl;
{
	register struct chtab *ch;

	for (ch = chtable; ch < &chtable[MAXCLIENTS]; ch++) {
		if (ch->ch_client == cl) {
			ch->ch_inuse = FALSE;
			break;
		}
	}
	if (clwanted) {
		clwanted = 0;
		wakeup((caddr_t)chtable);
	}
}

/*
 *  XXX
 *  This is used as a value for enum clnt_stat below.  It is not defined
 *  in rpc/clnt.h because it is specific to the NFS implementation.
 *  Beware of changes to clnt.h which override this value!
 */
#define RPC_INTR	((enum clnt_stat) 18)
char *rfsnames[] = {
	"null", "getattr", "setattr", "unused", "lookup", "readlink", "read",
	"unused", "write", "create", "remove", "rename", "link", "symlink",
	"mkdir", "rmdir", "readdir", "fsstat" };

/*
 * Back off for retransmission timeout, MAXTIMO is in 10ths of a sec
 */
#define MAXTIMO	300
#define backoff(tim)	((((tim) << 2) > MAXTIMO) ? MAXTIMO : ((tim) << 2))

int
rfscall(mi, which, xdrargs, argsp, xdrres, resp, cred)
	register struct mntinfo *mi;
	int	 which;
	xdrproc_t xdrargs;
	caddr_t	argsp;
	xdrproc_t xdrres;
	caddr_t	resp;
	struct ucred *cred;
{
	CLIENT *client;
	register enum clnt_stat status;
	struct rpc_err rpcerr;
	struct timeval wait;
	struct ucred *newcred;
	int timeo;
	int user_told;
	bool_t tryagain;

#ifdef	NFSDEBUG
	dprint(nfsdebug, 6, "rfscall: %x, %d, %x, %x, %x, %x\n",
	    mi, which, xdrargs, argsp, xdrres, resp);
#endif
	clstat.ncalls++;
	clstat.reqs[which]++;

	rpcerr.re_errno = 0;
	newcred = NULL;
	timeo = mi->mi_timeo;
	user_told = 0;
retry:
	client = clget(mi, cred);

	/*
	 * If hard mounted fs, retry call forever unless hard error occurs
	 */
	do {
		tryagain = FALSE;

		wait.tv_sec = timeo / 10;
		wait.tv_usec = 100000 * (timeo % 10);
		status = CLNT_CALL(client, which, xdrargs, argsp,
		    xdrres, resp, wait);
		switch (status) {
		case RPC_SUCCESS:
			break;

		/*
		 * Unrecoverable errors: give up immediately
		 */
		case RPC_AUTHERROR:
		case RPC_CANTENCODEARGS:
		case RPC_CANTDECODERES:
		case RPC_VERSMISMATCH:
		case RPC_PROGVERSMISMATCH:
		case RPC_CANTDECODEARGS:
			break;

		default:
			if (mi->mi_hard) {
				if (mi->mi_int && interrupted()) {
					status = RPC_INTR;
					rpcerr.re_status = RPC_SYSTEMERROR;
					rpcerr.re_errno = EINTR;
					tryagain = FALSE;
					break;
				} else {
					tryagain = TRUE;
					timeo = backoff(timeo);
					if (!mi->mi_printed) {
						mi->mi_printed = 1;
	printf("NFS server %s not responding still trying\n", mi->mi_hostname);
					}
					if (!user_told && u.u_ttyp &&
#ifdef	mips
					    u.u_ttyd != cons[0].t_dev) 
#else	mips
					    u.u_ttyd != cons.t_dev) 
#endif	mips
					{
						user_told = 1;
	uprintf("NFS server %s not responding still trying\n", mi->mi_hostname);
					}
				}
			}
		}
	} while (tryagain);

	if (status != RPC_SUCCESS) {
		CLNT_GETERR(client, &rpcerr);
		clstat.nbadcalls++;
		mi->mi_down = 1;
		printf("NFS %s failed for server %s: %s\n", rfsnames[which],
			mi->mi_hostname, clnt_sperrno(status));
#ifdef	mips
		if (u.u_ttyp && u.u_ttyd != cons[0].t_dev) 
#else	mips
		if (u.u_ttyp && u.u_ttyd != cons.t_dev) 
#endif	mips
		{
			uprintf("NFS %s failed for server %s: %s\n",
				rfsnames[which], mi->mi_hostname,
			  	clnt_sperrno(status)); 
		}
	} else if (resp && *(int *)resp == EACCES &&
	    newcred == NULL && cred->cr_uid == 0 && cred->cr_ruid != 0) {
		/*
		 * Boy is this a kludge!  If the reply status is EACCES
		 * it may be because we are root (no root net access).
		 * Check the real uid, if it isn't root make that
		 * the uid instead and retry the call.
		 */
		newcred = crdup(cred);
		cred = newcred;
		cred->cr_uid = cred->cr_ruid;
		clfree(client);
		goto retry;
	} else if (mi->mi_hard) {
		if (mi->mi_printed) {
			printf("NFS server %s ok\n", mi->mi_hostname);
			mi->mi_printed = 0;
		}
		if (user_told) {
			uprintf("NFS server %s ok\n", mi->mi_hostname);
		}
	} else {
		mi->mi_down = 0;
	}

	clfree(client);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 7, "rfscall: returning %d\n", rpcerr.re_errno);
#endif
	if (newcred) {
		crfree(newcred);
	}
	return (rpcerr.re_errno);
}

/*
 * Check if this process got an interrupt from the keyboard while sleeping
 */
int
interrupted() 
{
	int s, smask, intr;
	extern wakeup();
	struct proc *p = u.u_procp;

#define bit(a) 	(1<<(a-1))

	s = spl6();
	smask = p->p_sigmask;
	p->p_sigmask |= 
		~(bit(SIGHUP) | bit(SIGINT) | bit(SIGQUIT) | bit(SIGTERM));

	if (ISSIG(u.u_procp)) {
		intr = TRUE;
	} else {
		intr = FALSE;
	}
	p->p_sigmask = smask;
	(void) splx(s);

	return(intr);
}

u_short
nfsftypetomode(type)
enum nfsftype type;
{
	switch (type) {
	case NFCHR:
		return(IFCHR);
	case NFDIR:
		return(IFDIR);
	case NFBLK:
		return(IFBLK);
	case NFREG:
		return(IFREG);
	case NFLNK:
		return(IFLNK);
	case NFNON:
	default:
		return(IFREG);	/* XXX */
	}
}

nattr_to_vattr(na, vap)
	register struct nfsfattr *na;
	register struct vattr *vap;
{
	vap->va_mode = na->na_mode;
	vap->va_uid = (uid_t)na->na_uid;
	vap->va_gid = (gid_t)na->na_gid;
	vap->va_fsid = na->na_fsid;
	vap->va_nodeid = na->na_nodeid;
	vap->va_nlink = na->na_nlink;
	vap->va_size = na->na_size;
	vap->va_atime.tv_sec  = na->na_atime.tv_sec;
	vap->va_atime.tv_usec = na->na_atime.tv_usec;
	vap->va_mtime.tv_sec  = na->na_mtime.tv_sec;
	vap->va_mtime.tv_usec = na->na_mtime.tv_usec;
	vap->va_ctime.tv_sec  = na->na_ctime.tv_sec;
	vap->va_ctime.tv_usec = na->na_ctime.tv_usec;
	vap->va_rdev = na->na_rdev;
	vap->va_blocks = na->na_blocks;
	switch(na->na_type) {

	case NFBLK:
		vap->va_blocksize = BLKDEV_IOSIZE;
		break;

	case NFCHR:
		vap->va_blocksize = MAXBSIZE;
		break;

	default:
		vap->va_blocksize = na->na_blocksize;
		break;
	}
}

vattr_to_sattr(vap, sa)
	register struct vattr *vap;
	register struct nfssattr *sa;
{
	sa->sa_mode = vap->va_mode;
	sa->sa_uid = (u_long)vap->va_uid;
	sa->sa_gid = (u_long)vap->va_gid;
	sa->sa_size = vap->va_size;
	sa->sa_atime.tv_sec  = vap->va_atime.tv_sec;
	sa->sa_atime.tv_usec = vap->va_atime.tv_usec;
	sa->sa_mtime.tv_sec  = vap->va_mtime.tv_sec;
	sa->sa_mtime.tv_usec = vap->va_mtime.tv_usec;
}

setdiropargs(da, nm, dvp)
	struct nfsdiropargs *da;
	char *nm;
	struct vnode *dvp;
{

	da->da_fhandle = *vtofh(dvp);
	da->da_name = nm;
}

struct rnode *rpfreelist = NULL;
int rreuse, rnew, ractive;

/*
 * return a vnode for the given fhandle.
 * If no rnode exists for this fhandle create one and put it
 * in a table hashed by fh_fsid and fs_fid.  If the rnode for
 * this fhandle is already in the table return it (ref count is
 * incremented by rfind.  The rnode will be flushed from the
 * table when nfs_inactive calls runsave.
 */
struct vnode *
makenfsnode(fh, attr, vfsp)
	fhandle_t *fh;
	struct nfsfattr *attr;
	struct vfs *vfsp;
{
	register struct rnode *rp;
	struct vm_info *vitmp;
	char newnode = 0;

	if ((rp = rfind(fh, vfsp)) == NULL) {
		register struct vnode *vp;

		if (rpfreelist) {
			rp = rpfreelist;
			rpfreelist = rnode_next(rp);
			rreuse++;
		} else {
			ZALLOC(nfs_rnode_zone, rp, struct rnode *);
			rtov(rp)->v_vm_info = VM_INFO_NULL;
			vm_info_init(rtov(rp));
			rnew++;
		}
		vp = rtov(rp);
		vitmp = vp->v_vm_info;
		bzero((caddr_t)rp, sizeof(*rp));
		vp->v_vm_info = vitmp;
#if	MACH_NBC
		/*
		 *	Flush the vnode from the file map cache.
		 */
		mfs_uncache(vp);
#endif	MACH_NBC
		vp->v_vm_info->pager = MEMORY_OBJECT_NULL;
		vp->v_vm_info->inode_size = rp->r_size;
		rp->r_fh = *fh;
		vp->v_count = 1;
		vp->v_type = ITYPE_NFS;
		if (attr) {
			vp->v_mode = (vp->v_mode&~VFMT) | nfsftypetomode(attr->na_type);
			vp->v_rdev = attr->na_rdev;
		}
		vp->v_vfsp = vfsp;
		rsave(rp);
		((struct mntinfo *)(vfsp->vfs_data))->mi_refct++;
		newnode++;
	}
	if (attr) {
		nfs_attrcache(rtov(rp), attr, (newnode? NOFLUSH: SFLUSH));
	}
	return (rtov(rp));
}

/*
 * Rnode lookup stuff.
 * These routines maintain a table of rnodes hashed by fhandle so
 * that the rnode for an fhandle can be found if it already exists.
 * NOTE: RTABLESIZE must be a power of 2 for rtablehash to work!
 */

#define RTABLESIZE	16
#define rtablehash(fh) \
    ((fh->fh_data[2] ^ fh->fh_data[5] ^ fh->fh_data[15]) & (RTABLESIZE-1))

struct rnode *rtable[RTABLESIZE];

/*
 * Put a rnode in the hash table
 */
rsave(rp)
	struct rnode *rp;
{

	rtov(rp)->v_next = rtov(rtable[rtablehash(rtofh(rp))]);
	rtable[rtablehash(rtofh(rp))] = rp;
}

/*
 * Remove a rnode from the hash table
 */
runsave(rp)
	struct rnode *rp;
{
	struct rnode *rt;
	struct rnode *rtprev = NULL;
	 
	rt = rtable[rtablehash(rtofh(rp))]; 
	while (rt != NULL) { 
		if (rt == rp) { 
			if (rtprev == NULL) {
				rtable[rtablehash(rtofh(rp))] = rnode_next(rt);
			} else {
				rtov(rtprev)->v_next = rtov(rt)->v_next;
			}
			return; 
		}	
		rtprev = rt;
		rt = rnode_next(rt);
	}	
}

/*
 * Put an rnode on the free list and take it out if
 * the hash table.
 */
rfree(rp)
	register struct rnode *rp;
{
	runsave(rp);
	rtov(rp)->v_next = rtov(rpfreelist);
	rpfreelist = rp;
}

/*
 * Lookup a rnode by fhandle
 */
struct rnode *
rfind(fh, vfsp)
	fhandle_t *fh;
	struct vfs *vfsp;
{
	register struct rnode *rt;
	 
	rt = rtable[rtablehash(fh)]; 
	while (rt != NULL) { 
		if (bcmp((caddr_t)rtofh(rt), (caddr_t)fh, sizeof(*fh)) == 0 &&
		    vfsp == rtov(rt)->v_vfsp) { 
			rtov(rt)->v_count++; 
			ractive++;
			return (rt); 
		}	
		rt = rnode_next(rt);
	}	
	return (NULL);
}

/*
 * remove buffers from the buffer cache that have this vfs.
 * NOTE: assumes buffers have been written already.
 */
rinval(vfsp)
	struct vfs *vfsp;
{
	int	i;
	register struct rnode *rp, *rptmp;

	for (i = 0; i < RTABLESIZE; i++) {
		for (rp = rtable[i]; rp; ) {
			if (rp->r_vnode.v_vfsp == vfsp) {
				/*
				 * Need to hold the vp because binval releases
				 * it which will call rfree if the ref count
				 * goes to zero and rfree will mess up rtable.
				 */
				VN_HOLD(rtov(rp));
				rptmp = rp;
				rp = rnode_next(rp);
				binvalfree(rtov(rptmp));
				VN_RELE(rtov(rptmp));
			} else {
				rp = rnode_next(rp);
			}
		}
	}
}

/*
 * Flush dirty buffers for all vnodes in this vfs
 */
rflush(vfsp)
	struct vfs *vfsp;
{
	int	i;
	register struct rnode *rp;

	for (i = 0; i < RTABLESIZE; i++) {
		for (rp = rtable[i]; rp; rp = rnode_next(rp)) {
			if (rp->r_vnode.v_vfsp == vfsp) {
				bflush(rtov(rp));
			}
		}
	}
}

#define PREFIXLEN	4
static char prefix[PREFIXLEN+1] = ".nfs";

char *
newname()
{
	char *news;
	register char *s1, *s2;
	unsigned int id;
	static int newnum;

	ZALLOC(nfs_name_zone, news, char *);
	for (s1 = news, s2 = prefix; s2 < &prefix[PREFIXLEN]; ) {
		*s1++ = *s2++;
	}
	if (newnum == 0) {
		newnum = time.tv_sec & 0xffff;
	}
	id = newnum++;
	while (id) {
		*s1++ = "0123456789ABCDEF"[id & 0x0f];
		id = id >> 4;
	}
	*s1 = '\0';
	return (news);
}

/*
 * General utilities
 */

/*
 * Returns the prefered transfer size in bytes based on
 * what network interfaces are available.
 */
nfstsize()
{
	register struct ifnet *ifp;

	for (ifp = ifnet; ifp; ifp = ifp->if_next) {
		if (ifp->if_name[0] == 'e' && ifp->if_name[1] == 'c') {
#ifdef	NFSDEBUG
			dprint(nfsdebug, 3, "nfstsize: %d\n", ECTSIZE);
#endif
			return (ECTSIZE);
		}
	}
#ifdef	NFSDEBUG
	dprint(nfsdebug, 3, "nfstsize: %d\n", IETSIZE);
#endif
	return (IETSIZE);
}

#ifdef	NFSDEBUG
/*
 * Utilities used by both client and server
 * Standard bits:
 * 0) no debugging (not used)
 * 1) hard failures
 * 2) soft failures
 * 3) current test software
 * 4) main procedure entry points
 * 5) main procedure exit points
 * 6) utility procedure entry points
 * 7) utility procedure exit points
 * 8) obscure procedure entry points
 * 9) obscure procedure exit points
 * 10) random stuff
 * 11) all <= 1
 * 12) all <= 2
 * 13) all <= 3
 * ...
 */

/*VARARGS2*/
dprint(var, level, str, a1, a2, a3, a4, a5, a6, a7, a8, a9)
	int var;
	int level;
	char *str;
	int a1, a2, a3, a4, a5, a6, a7, a8, a9;
{
	if (var & (1 << level))
		printf(str, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
#endif
