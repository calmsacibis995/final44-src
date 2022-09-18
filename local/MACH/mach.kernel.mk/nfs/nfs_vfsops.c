/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	nfs_vfsops.c,v $
 * Revision 2.13  91/04/05  14:43:18  mbj
 * 	Set the struct statfs f_type to be MOUNT_NFS, ala Reno.
 * 	[91/03/18            dlc]
 * 	Zero the entire address structure SetupNetworkInterface().
 * 	[90/12/04  16:19:42  britt@venera.isi.edu]
 * 
 * Revision 2.12  91/04/03  13:10:27  mbj
 * 	nfs changes for omron
 * 	[91/03/07  11:32:58  rvb]
 * 
 * Revision 2.11  90/12/17  16:49:00  berman
 * 	Zero the entire address structure SetupNetworkInterface().
 * 	[90/12/04  16:19:42  britt@venera.isi.edu]
 * 
 * Revision 2.10  89/08/02  09:22:51  jsb
 * 	Tmp for PMAX (read ULTRIX) shift over flag parameter for
 * 	nfs_mount to correspond to what ULTRIX application programs set.
 * 	[89/08/02  09:21:14  jsb]
 * 
 * 	Eliminated MACH conditionals. Replaced kallocs with zallocs.
 * 	[89/07/31  16:24:48  jsb]
 * 
 * Revision 2.9  89/08/02  08:26:50  jsb
 * 	Eliminated MACH conditionals. Replaced kallocs with zallocs.
 * 	[89/07/31  16:24:48  jsb]
 * 
 * Revision 2.7  89/04/22  15:26:00  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.6  89/03/09  20:54:33  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  19:09:44  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  89/01/31  01:21:30  rpd
 * 	Don't even think about using an nfs root on multimax.
 * 	[88/10/13            dlb]
 * 
 * Revision 2.3  89/01/23  15:26:35  rvb
 * 	Forward declarations for GCC.
 * 	[89/01/22            rvb]
 * 
 * Revision 2.2  89/01/18  00:56:33  jsb
 * 	Added some really gross testing code for mounting an nfs file system
 * 	as root. This code should go away real soon.
 * 	[89/01/17  14:11:35  jsb]
 * 
 *
 * 28-Oct-87  Peter King (king) at NeXT, Inc.
 *	Original Sun source, ported to  Mach.
 */ 

/* @(#)nfs_vfsops.c	1.6 87/09/11 3.2/4.3NFSSRC */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/inode.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/mount.h>
#include <netinet/in.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/auth.h>
#include <rpc/clnt.h>
#include <nfs/nfs.h>
#include <nfs/nfs_clnt.h>
#include <nfs/rnode.h>
#include <nfs/nfs_mount.h>
#include <net/if.h>

#include <sys/ioctl.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/if_ether.h>

#ifdef	NFSDEBUG
extern int nfsdebug;
#endif


struct vnode *nfsrootvp();
struct vnode *makenfsnode();
#ifdef	__GNU__
static int addr_to_str();
#endif	__GNU__
int nfsmntno;

/*
 * nfs vfs operations.
 */
int nfs_mount();
int nfs_unmount();
int nfs_root();
int nfs_statfs();
int nfs_sync();
extern int nfs_badop();

struct vfsops nfs_vfsops = {
	nfs_mount,
	nfs_unmount,
	nfs_root,
	nfs_statfs,
	nfs_sync,
	nfs_badop
};


/*
 * nfs mount vfsop
 * Set up mount info record and attach it to vfs struct.
 */
/*ARGSUSED*/
nfs_mount(vfsp, path, data)
	struct vfs *vfsp;
	char *path;
	caddr_t data;
{
	int error;
	struct vnode *rtvp = NULL;	/* the server's root */
	struct mntinfo *mi;		/* mount info, pointed at by vfs */
	fhandle_t fh;			/* root fhandle */
	struct sockaddr_in saddr;	/* server's address */
	char hostname[HOSTNAMESZ];	/* server's name */
	struct nfs_args args;		/* nfs mount arguments */

	/*
	 * get arguments
	 */
	error = copyin(data, (caddr_t)&args, sizeof (args));
	if (error) {
		goto errout;
	}
#ifdef	PMAX
	args.flags = ((args.flags & 0x7e) >> 1) | ((args.flags & 0x100) ? 0x40 : 0);
#endif	PMAX

	/*
	 * Get server address
	 */
	error = copyin((caddr_t)args.addr, (caddr_t)&saddr,
	    sizeof(saddr));
	if (error) {
		goto errout;
	}
	/*
	 * For now we just support AF_INET
	 */
	if (saddr.sin_family != AF_INET) {
		error = EPFNOSUPPORT;
		goto errout;
	}

	/*
	 * Get the root fhandle
	 */
	error = copyin((caddr_t)args.fh, (caddr_t)&fh, sizeof(fh));
	if (error) {
		goto errout;
	}

	/*
	 * Get server's hostname
	 */
	if (args.flags & NFSMNT_HOSTNAME) {
		error = copyin((caddr_t)args.hostname, (caddr_t)hostname,
		    HOSTNAMESZ);
		if (error) {
			goto errout;
		}
	} else {
		addr_to_str(&saddr, hostname);
	}

	/*
	 * Get root vnode.
	 */
	rtvp = nfsrootvp(vfsp, &saddr, &fh, hostname);
	if (!rtvp) {
		error = EBUSY;
		goto errout;
	}

	/*
	 * Set option fields in mount info record
	 */
	mi = vtomi(rtvp);
	mi->mi_hard = ((args.flags & NFSMNT_SOFT) == 0);
	mi->mi_int = ((args.flags & NFSMNT_INT) == NFSMNT_INT);
	if (args.flags & NFSMNT_RETRANS) {
		mi->mi_retrans = args.retrans;
		if (args.retrans < 0) {
			error = EINVAL;
			goto errout;
		}
	}
	if (args.flags & NFSMNT_TIMEO) {
		mi->mi_timeo = args.timeo;
		if (args.timeo <= 0) {
			error = EINVAL;
			goto errout;
		}
	}
	if (args.flags & NFSMNT_RSIZE) {
		if (args.rsize <= 0) {
			error = EINVAL;
			goto errout;
		}
		mi->mi_tsize = MIN(mi->mi_tsize, args.rsize);
	}
	if (args.flags & NFSMNT_WSIZE) {
		if (args.wsize <= 0) {
			error = EINVAL;
			goto errout;
		}
		mi->mi_stsize = MIN(mi->mi_stsize, args.wsize);
	}

#ifdef	NFSDEBUG
	dprint(nfsdebug, 1,
	    "nfs_mount: hard %d timeo %d retries %d wsize %d rsize %d\n",
	    mi->mi_hard, mi->mi_timeo, mi->mi_retrans, mi->mi_stsize,
	    mi->mi_tsize);
#endif
errout:
	if (error) {
		if (rtvp) {
			VN_RELE(rtvp);
		}
	}
	return (error);
}

#if	PROTO
int	slownfs = 0;
#endif	PROTO

struct vnode *
nfsrootvp(vfsp, sin, fh, hostname)
	struct vfs *vfsp;		/* vfs of fs, if NULL amke one */
	struct sockaddr_in *sin;	/* server address */
	fhandle_t *fh;			/* swap file fhandle */
	char *hostname;			/* swap server name */
{
	struct vnode *rtvp = NULL;	/* the server's root */
	struct mntinfo *mi = NULL;	/* mount info, pointed at by vfs */
	struct vattr va;		/* root vnode attributes */
	struct nfsfattr na;		/* root vnode attributes in nfs form */
	struct statfs sb;		/* server's file system stats */
	extern struct ifnet loif;
int ERROR;

	/*
	 * create a mount record and link it to the vfs struct
	 */
	ZALLOC(nfs_mntinfo_zone, mi, struct mntinfo *);
	bzero((caddr_t)mi, sizeof(*mi));
	mi->mi_hard = 1;
	mi->mi_addr = *sin;
	mi->mi_retrans = NFS_RETRIES;
	mi->mi_timeo = NFS_TIMEO;
	mi->mi_mntno = nfsmntno++;
	bcopy(hostname, mi->mi_hostname, HOSTNAMESZ);

	/*
	 * Make a vfs struct for nfs.  We do this here instead of below
	 * because rtvp needs a vfs before we can do a getattr on it.
	 */
	vfsp->vfs_fsid.val[0] = mi->mi_mntno;
	vfsp->vfs_fsid.val[1] = MOUNT_NFS;
	vfsp->vfs_data = (caddr_t)mi;

	/*
	 * Make the root vnode, use it to get attributes, then remake it
	 * with the attributes
	 */
	rtvp = makenfsnode(fh, (struct nfsfattr *) 0, vfsp);
	if ((rtvp->v_flag & VROOT) != 0) {
		goto bad;
	}
	if (ERROR = VOP_GETATTR(rtvp, &va, u.u_cred)) {
		goto bad;
	}
	VN_RELE(rtvp);
	vattr_to_nattr(&va, &na);
	rtvp = makenfsnode(fh, &na, vfsp);
	rtvp->v_flag |= VROOT;
	mi->mi_rootvp = rtvp;

	/*
	 * Get server's filesystem stats.  Use these to set transfer
	 * sizes, filesystem block size, and read-only.
	 */
	if (ERROR = VFS_STATFS(vfsp, &sb)) {
		goto bad;
	}
	mi->mi_tsize = min(NFS_MAXDATA, (u_int)nfstsize());

	/*
	 * Set filesystem block size to at least CLBYTES and at most MAXBSIZE
	 */
	mi->mi_bsize = MAX(va.va_blocksize, CLBYTES);
	mi->mi_bsize = MIN(mi->mi_bsize, MAXBSIZE);
	vfsp->vfs_bsize = mi->mi_bsize;

	/*
	 * Need credentials in the rtvp so do_bio can find them.
	 */
	crhold(u.u_cred);
	vtor(rtvp)->r_cred = u.u_cred;

	return (rtvp);
bad:
	if (mi) {
		ZFREE(nfs_mntinfo_zone, mi);
	}
	if (rtvp) {
		VN_RELE(rtvp);
	}
	return (NULL);
}

#if	defined(multimax) || defined (luna88k)
#else	defined(multimax) || defined (luna88k)
getstring(string)
char *string;
{
	char _s[256], *s = _s;

	printf("[%s] ", string);
	gets(s);
	if (*s == 0) {
		return;
	}
	while (*s) {
		*string = *s;
		string++, s++;
	}
	*string = 0;
}

getdecimal(j)
int *j;
{
	char _s[64], *s;
	int i;

again:
	i = 0, s = _s;
	printf("[%d] ", *j);
	gets(s);
	if (s[0] == 0) {
		return;
	}
	while (*s) {
		if (*s < '0' || *s > '9') {
			printf("You did it wrong again, STUPID\n");
			goto again;
		}
		i = i * 10 + (*s - '0');
		s++;
	}
	*j = i;
}

gethex(j)
int *j;
{
	char _s[64], *s;
	int i;

again:
	i = 0, s = _s;
	printf("[0x%x] ", *j);
	gets(s);
	if (s[0] == 0) {
		return;
	}
	while (*s) {
		if (*s >= 'a' && *s <= 'f') {
			i = i * 16 + (*s + 10 - 'a');
		} else if (*s >= 'A' && *s <= 'F') {
			i = i * 16 + (*s + 10 - 'A');
		} else if (*s >= '0' && *s <= '9') {
			i = i * 16 + (*s - '0');
		} else {
			printf("You did it wrong again, STUPID\n");
			goto again;
		}
		s++;
	}
	*j = i;
}

/*
 *  These are all things which we must more elegantly learn,
 *  i.e. via a server that we could rpc to
 *  to get all this info.
 */
char MY_IF[64] = "lan0";		/* rt token ring */
int  MY_ADDR   = 0x8002d90c;		/* bullwinkle.mach */

struct sockaddr_in NFS_SERVER_ADDR = {
	2,
	2049,
	{ 0x8002da05 },
	0
};

struct foobar {
	long val[2];
	unsigned short fid_len;
	char fid[40];
} NFS_SERVER_FH = {
	{ 0x10e, 0x0 },
	10,
	{ 0, 0, 0, 0, 0, 2, 0, 0, 0, 0 }
};

char NFS_SERVER_NAME[64] = "jsb";

#endif	defined(multimax) || defined (luna88k)

struct barfoo {
	unsigned short fid_len;
	char fid[40];
};

int absurd_fid_length = 24;

print_file_id(fid)
struct barfoo *fid;
{
	int j;
	int len = fid->fid_len;

	if (fid == 0) {
		printf("print_file_id: null file id!\n");
		return;
	}
	printf("file id     0x%x:\n", fid);
	printf("\tfid_len = %d\n", len);
	if (len == 0) {
		printf("\tfid     = ()");
		return;
	}
	if (len > absurd_fid_length) {
		printf("WARNING: ABSURD FID LENGTH %d (TRUNCATED TO 10)\n",
			len);
		len = 10;
	}
	printf("\tfid     = (");
	for (j = 0; j < len; j++) {
		if (j < len - 1) {
			printf("%d,", fid->fid[j]);
		} else if (len != fid->fid_len) {
			printf("%d,...)\n", fid->fid[j]);
		} else {
			printf("%d)\n", fid->fid[j]);
		}
	}
}

#if	defined(multimax) || defined (luna88k)
#else	defined(multimax) || defined (luna88k)

print_file_handle(fh)
struct foobar *fh;
{
	int j;
	int len = fh->fid_len;

	if (fh == 0) {
		printf("print_file_handle: null file handle!\n");
		return;
	}
	printf("file handle 0x%x:\n", fh);
	printf("\tval[0]  = 0x%x\n", fh->val[0]);
	printf("\tval[1]  = 0x%x\n", fh->val[1]);
	printf("\tfid_len = %d\n", fh->fid_len);
	printf("\tfid     = (");
	for (j = 0; j < len; j++) {
		if (j < len - 1) {
			printf("%d,", fh->fid[j]);
		} else {
			printf("%d)\n", fh->fid[j]);
		}
	}
}

#endif	defined(multimax) || defined (luna88k)

#if	defined(multimax) || defined (luna88k)

/*
 *	Don't even think about using an nfs partition for root on multimax.
 */

nfs_mountroot()
{
	return (ufs_mountroot());
}

#else	defined(multimax) || defined (luna88k)

int try_nfs_mountroot = 0;

int really_do_nfs_mountroot()
{
	char answer[64];

	if (! try_nfs_mountroot) {
		return 0;
	}
	printf("Do you want to mount an nfs partition as root? ");
	strcpy(answer, "no");
	getstring(answer);
	return (answer[0] == 'y' || answer[0] == 'Y');
}

get_nfs_mount_info()
{
	static char answer[64];
	int j, len;
	int i;

	printf("your network interface "); getstring(MY_IF);
	printf("your address "); gethex(&MY_ADDR);
	i = NFS_SERVER_ADDR.sin_port;
	printf("nfs server port "); getdecimal(&i);
	NFS_SERVER_ADDR.sin_port = i;
	printf("nfs server address ");gethex(&NFS_SERVER_ADDR.sin_addr.s_addr);
	printf("nfs server name "); getstring(NFS_SERVER_NAME);
	printf("fh val #0 "); gethex(&NFS_SERVER_FH.val[0]);
	printf("fh val #1 "); gethex(&NFS_SERVER_FH.val[1]);
	print_file_handle(&NFS_SERVER_FH);
	printf("Are these file handle values correct? ");
	strcpy(answer, "yes");
	getstring(answer);
	if (answer[0] == 'y' || answer[0] == 'Y') {
		return;
	}
	i = NFS_SERVER_FH.fid_len;
	printf("fh fid len "); getdecimal(&i);
	NFS_SERVER_FH.fid_len = (short) i;
	len = i;
	for (j = 0; j < len; j++) {
		printf("fh fid[%d] ", j);
		i = (unsigned long) NFS_SERVER_FH.fid[j];
		getdecimal(&i);
		NFS_SERVER_FH.fid[j] = (char) i;
	}
	print_file_handle(&NFS_SERVER_FH);
}

nfs_mountroot()
{
	struct vfs *vfsp;
	register int error;
	struct vnode *rtvp = NULL;
	struct mntinfo *mi;	/* mount info, pointed at by vfs */

	/*
	 *  Make sure we want to do nfs_mountroot.
	 */
	if (! really_do_nfs_mountroot()) {
		return ufs_mountroot();
	}
	/*
	 *  Correct any information likely to be wrong.
	 */
	get_nfs_mount_info();
	/*
	 *  Do an in-the-kernel ifconfig. Yuck.
	 */
	error = SetupNetworkInterface(MY_IF, MY_ADDR);
	if (error) {
		printf("nfs_mountroot: SetupNetworkInterface failed.\n");
		goto errout;
	}
	ZALLOC(vfs_vfs_zone, vfsp, struct vfs *);
	VFS_INIT(vfsp, &nfs_vfsops, (caddr_t)0);
	error = vfs_add((struct vnode *)0, vfsp, 0);
	if (error) {
		panic("vfs_add in nfs_mountroot: %d", error);
	}
	rtvp = nfsrootvp(vfsp, &NFS_SERVER_ADDR, &NFS_SERVER_FH,
			 NFS_SERVER_NAME);
	if (!rtvp) {
		panic("nfsrootvp in nfs_mountroot");
		error = EBUSY;
		goto errout;
	}
	/*
	 * Set option fields in mount info record
	 */
	mi = vtomi(rtvp);
	mi->mi_hard = TRUE;
	mi->mi_int = FALSE;
	mi->mi_timeo = 20;
	mi->mi_tsize = 1024;
	mi->mi_stsize = 1024;
	vfs_unlock(vfsp);
errout:
	if (error) {
		if (rtvp) {
			VN_RELE(rtvp);
		}
		ZFREE(vfs_vfs_zone, vfsp);
	}
	return(error);
}

/*
 *  boot_dev will be like "ie0", "le0", "lo0", etc.
 *  boot_addr is your own internet address.
 *  Thus call as SetupNetworkInterface("ie", 0x8002fa95),
 */
SetupNetworkInterface(boot_dev, boot_addr)
char *boot_dev;
u_long boot_addr;
{
	register int error;
	struct sockaddr_in saddr;
	struct sockaddr_in netmask;
	struct socket *so;
	struct ifreq ifr;	/* Interface request */
	int flags;

	error = socreate(AF_INET, &so, SOCK_DGRAM, 0);
	if (error) {
		printf("nfs_mountroot: couldn't create a socket\n");
		return(error);
	}
	strncpy(ifr.ifr_name, boot_dev, sizeof(ifr.ifr_name));
	/* Get the interface flags */
	if (error = ifioctl(so, SIOCGIFFLAGS, (caddr_t)&ifr)) {
		printf("nfs_mountroot: SIOCGIFFLAGS failed.\n");
		goto errout;
	}
	flags = ifr.ifr_flags;
	/* Clear the netmask for now to reduce confusion */
	bzero(&netmask, sizeof(netmask));
	netmask.sin_family = AF_INET;
	ifr.ifr_addr = *(struct sockaddr *)&netmask;
	if (error = ifioctl(so, SIOCSIFNETMASK, (caddr_t)&ifr)) {
		printf("nfs_mountroot: SIOCSIFNETMASK failed.\n");
		goto errout;
	}
	/* Now set the interface address */
	bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = 0;
	saddr.sin_addr.s_addr = boot_addr;
	ifr.ifr_addr = *(struct sockaddr *) &saddr;
	if (error = ifioctl(so, SIOCSIFADDR, (caddr_t)&ifr)) {
		printf("nfs_mountroot: SIOCSIFADDR failed.\n");
		goto errout;
	}
	/* Now flag the interface as up */
	ifr.ifr_flags = flags|IFF_UP;
	if (error = ifioctl(so, SIOCSIFFLAGS, (caddr_t)&ifr)) {
		printf("nfs_mountroot: SIOCSIFFLAGS failed.\n");
		goto errout;
	}
errout:
	soclose(so);
	return error;
}

#endif	defined(multimax) || defined (luna88k)

/*
 * vfs operations
 */

nfs_unmount(vfsp)
	struct vfs *vfsp;
{
	struct mntinfo *mi = (struct mntinfo *)vfsp->vfs_data;

#ifdef	NFSDEBUG
        dprint(nfsdebug, 4, "nfs_unmount(%x) mi = %x\n", vfsp, mi);
#endif
	rflush(vfsp);
	rinval(vfsp);

	if (mi->mi_refct != 1 || mi->mi_rootvp->v_count != 1) {
		return (EBUSY);
	}
	VN_RELE(mi->mi_rootvp);
	ZFREE(nfs_mntinfo_zone, mi);
	return(0);
}

/*
 * find root of nfs
 */
int
nfs_root(vfsp, vpp)
	struct vfs *vfsp;
	struct vnode **vpp;
{

	*vpp = (struct vnode *)((struct mntinfo *)vfsp->vfs_data)->mi_rootvp;
	(*vpp)->v_count++;
#ifdef	NFSDEBUG
        dprint(nfsdebug, 4, "nfs_root(0x%x) = %x\n", vfsp, *vpp);
#endif
	return(0);
}

/*
 * Get file system statistics.
 */
int
nfs_statfs(vfsp, sbp)
register struct vfs *vfsp;
struct statfs *sbp;
{
	struct nfsstatfs fs;
	struct mntinfo *mi;
	fhandle_t *fh;
	int error = 0;

	mi = vftomi(vfsp);
	fh = vtofh(mi->mi_rootvp);
#ifdef	NFSDEBUG
        dprint(nfsdebug, 4, "nfs_statfs vfs %x\n", vfsp);
#endif
	error = rfscall(mi, RFS_STATFS, xdr_fhandle,
	    (caddr_t)fh, xdr_statfs, (caddr_t)&fs, u.u_cred);
	if (!error) {
		error = geterrno(fs.fs_status);
	}
	if (!error) {
		if (mi->mi_stsize) {
			mi->mi_stsize = MIN(mi->mi_stsize, fs.fs_tsize);
		} else {
			mi->mi_stsize = fs.fs_tsize;
		}
    /*
     * Man page says f_type is 0, but let's set it the way Reno does for
     * application source compatibility
     */
		sbp->f_type = MOUNT_NFS;
		sbp->f_bsize = fs.fs_bsize;
		sbp->f_blocks = fs.fs_blocks;
		sbp->f_bfree = fs.fs_bfree;
		sbp->f_bavail = fs.fs_bavail;

    /*  The Man page for statfs says that undefined fields are set to -1  */
		sbp->f_files = -1;
		sbp->f_ffree = -1;
		/*
		 * XXX This is wrong - should be a real fsid
		 */
		bcopy((caddr_t)&vfsp->vfs_fsid,
		    (caddr_t)&sbp->f_fsid, sizeof (fsid_t));
	}
#ifdef	NFSDEBUG
        dprint(nfsdebug, 5, "nfs_statfs returning %d\n", error);
#endif
	return (error);
}

/*
 * Flush any pending I/O.
 */
int
nfs_sync(vfsp)
	struct vfs * vfsp;
{

#ifdef	NFSDEBUG
        dprint(nfsdebug, 5, "nfs_sync %x\n", vfsp);
#endif
	rflush(vfsp);
	return(0);
}

static char *
itoa(n, str)
	u_char n;
	char *str;
{
	char prbuf[11];
	register char *cp;

	cp = prbuf;
	do {
		*cp++ = "0123456789"[n%10];
		n /= 10;
	} while (n);
	do {
		*str++ = *--cp;
	} while (cp > prbuf);
	return (str);
}

/*
 * Convert a INET address into a string for printing
 */
static
addr_to_str(addr, str)
	struct sockaddr_in *addr;
	char *str;
{
	u_char *ucp = (u_char *)&addr->sin_addr.s_addr;

        str = itoa(ucp[0], str);
        *str++ = '.';
        str = itoa(ucp[1], str);
        *str++ = '.';
        str = itoa(ucp[2], str);
        *str++ = '.';
        str = itoa(ucp[3], str);
	*str = '\0';
}
