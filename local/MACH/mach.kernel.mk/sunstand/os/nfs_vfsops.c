/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	nfs_vfsops.c,v $
 * Revision 2.2  89/07/12  01:12:46  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*      @(#)nfs_vfsops.c 1.18 88/03/29 SMI      */

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#include <sys/param.h>
#include "boot/systm.h"
#include <sys/user.h>
#include <sys/vfs.h>
#include "boot/vnode.h"
#include <sys/pathname.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/kernel.h>
#include <netinet/in.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/auth.h>
#include <rpc/clnt.h>
#include <rpc/pmap_rmt.h>
#include <rpc/pmap_prot.h>
#include <rpcsvc/bootparam.h>
#include "boot/nfs.h"
#include <nfs/nfs_clnt.h>
#include <nfs/rnode.h>
#include <sys/mount.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <netinet/if_ether.h>
#include <net/route.h>
#include <rpcsvc/mount.h>
#include <sys/bootconf.h>
#include <sys/ioctl.h>
#include <stand/saio.h>

extern	struct	ifnet	*if_ifwithaf();
struct vnode *nfsrootvp();
struct vnode *makenfsnode();
int nfsmntno;


#ifdef NFSDEBUG
static	int	nfsdebug = 10;
#endif

#undef NFS_RETRIES
#define	    NFS_RETRIES	    10	/* times to retry request */

/*
 * nfs vfs operations.
 */
int nfs_root();
int nfs_statfs();
int nfs_mountroot();
extern int nfs_badop();

struct vfsops nfs_vfsops = {
      nfs_badop,	/* nfs_mount, */
      nfs_badop,	/* nfs_unmount, */
      nfs_root,		/* nfs_root, */
      nfs_statfs,
      nfs_badop,	/* nfs_sync, */
      nfs_badop,
      nfs_mountroot,
      nfs_badop,	/* nfs_swapvp, */
};

/*
 * Fake up a user structure.
 */

#undef	u;
extern	struct	user	u;
int	ethernet_started = 0;

/*
 * Called by vfs_mountroot when nfs is going to be mounted as root
 */
nfs_mountroot(vfsp, vpp, name)
	struct vfs *vfsp;
	struct vnode **vpp;
	char *name;
{
	struct sockaddr_in root_sin;
	struct vnode *rtvp;
	char *root_path;
	char root_hostname[16];
	fhandle_t root_fhandle;
	int rc;
	int	error;


	/*
	 * Extra code to ensure that we open the
	 * ethernet device and initialise the inet
	 * tables.
	 */
	if (ethernet_started == 0) {
		ethersetup();
		domaininit();
		ip_init();
		ethernet_started = 1;
		}
	/*
	 * Ensure that the routing table entry
	 * gets made.
	 */
	error = whoami();
	if (error != 0) {
		printf ("Boot: bad dialog with bootparam server (error 0x%x)\n", error);
		return (error);
	}

	getfsname("root", name);
	root_path = kmem_alloc(MAX_MACHINE_NAME + 1);
	do {
		if (*name) {
			rc = getfile(name, root_hostname,
			    (struct sockaddr *)&root_sin, root_path);
		} else {
			rc = getfile("root", root_hostname,
			    (struct sockaddr *)&root_sin, root_path);
		}
	} while (rc == ETIMEDOUT);
#ifdef	NFSDEBUG
	dprint(nfsdebug, 6,
		"nfs_mountroot: root_path '%s'\n", root_path);
#endif	/* NFSDEBUG */
	if (rc) {
		kmem_free(root_path, MAX_MACHINE_NAME + 1);
		return (rc);
	}
	rc = mountrpc(&root_sin, root_path, &root_fhandle);

	if (rc) {
		printf("Boot: NFS mount of '%s:%s' failed (error 0x%x)\n", root_hostname, root_path, rc);
		kmem_free(root_path, MAX_MACHINE_NAME + 1);
		return (rc);
	}
	rtvp = nfsrootvp(vfsp, &root_sin, &root_fhandle, root_hostname);
	if (rtvp) {
#ifdef	NFSDEBUG
		dprint(nfsdebug, 6,
			"nfs_mountroot: rtvp 0x%x\n", rtvp);
#endif	/* NFSDEBUG */
		if (rc = vfs_add((struct vnode *)0, vfsp, 0)) {
                        kmem_free(root_path, MAX_MACHINE_NAME + 1);
                        return (rc);
                }
                vfs_unlock(rtvp->v_vfsp);
                *vpp = rtvp;
                {
                        register char *nm;
 
                        (void) strcpy(name, root_hostname);
                        for (nm = name; *nm; nm++)
                                ;
                        *nm++ = ':';
                        (void) strcpy(nm, root_path);
                }
                kmem_free(root_path, MAX_MACHINE_NAME + 1);

		return(0);
	}
	printf ("Boot: root file system already mounted\n");
	kmem_free(root_path, MAX_MACHINE_NAME + 1);
        return (EBUSY);

}

/*
 * pmapper remote-call-service interface.
 * This routine is used to call the pmapper remote call service
 * which will look up a service program in the port maps, and then
 * remotely call that routine with the given parameters.  This allows
 * programs to do a lookup and call in one step.
*/
static enum clnt_stat
pmap_rmtcall(call_addr, prog, vers, proc, xdrargs, argsp, xdrres, resp, tout, resp_addr)
        struct sockaddr_in *call_addr;
        u_long prog, vers, proc;
        xdrproc_t xdrargs, xdrres;
        caddr_t argsp, resp;
        struct timeval tout;
        struct sockaddr_in *resp_addr;
{
        register CLIENT *client;
        struct rmtcallargs a;
        struct rmtcallres r;
        enum clnt_stat stat, clntkudp_callit_addr();
        u_long port;


        call_addr->sin_port = htons(PMAPPORT);
        client = clntkudp_create(call_addr, PMAPPROG, PMAPVERS, 10, u.u_cred);
        if (client != (CLIENT *)NULL) {
                a.prog = prog;
                a.vers = vers;
                a.proc = proc;
                a.args_ptr = argsp;
                a.xdr_args = xdrargs;
                r.port_ptr = &port;
                r.results_ptr = resp;
                r.xdr_results = xdrres;
                stat = clntkudp_callit_addr(client, PMAPPROC_CALLIT,
                        xdr_rmtcall_args, (caddr_t)&a, xdr_rmtcallres,
			(caddr_t)&r, tout, resp_addr);
                resp_addr->sin_port = port;
                CLNT_DESTROY(client);
        } else {
		printf("Boot: remote call failed - port mapper failure?");
        }
        return (stat);
}

static struct sockaddr_in bootparam_addr;
extern	struct in_addr my_in_addr;
extern struct  ether_addr      destetheraddr;

static int
whoami()
{
	struct sockaddr_in sa;
	struct ifnet *ifp;
	struct bp_whoami_arg arg;
	struct bp_whoami_res res;
	struct timeval tv;
	ip_addr_t *ip;
	struct in_addr *ip1;
	struct in_addr *inp;
	enum clnt_stat status;
	int error;
	struct rtentry rtentry;
	struct sockaddr_in *sin;
	enum clnt_stat callrpc();

	bzero(&sa, sizeof sa);
	ifp = if_ifwithaf(AF_INET);
        if (ifp == 0) {
		printf ("Boot: cannot open INET interface\n");
                return (EHOSTUNREACH);
        }
	if (!address_known(ifp)) {
                revarp_myaddr(ifp);
        }
	/*
	 * Ensure that the broadcast address for this interface
	 * contains a genuine broadcast address.
	 */
	ip1 = &(((struct sockaddr_in *)&(ifp->if_addrlist->ifa_broadaddr))->sin_addr);
	ip1->s_net = my_in_addr.s_net;
	ip1->s_host = my_in_addr.s_host;
	ip1->s_lh = my_in_addr.s_lh;
	ip1->s_impno = 0;
	if (IN_CLASSA(my_in_addr.s_addr))
	    ip1->s_addr &= IN_CLASSA_NET;
	else if (IN_CLASSB(my_in_addr.s_addr))
	    ip1->s_addr &= IN_CLASSB_NET;
	else if (IN_CLASSC(my_in_addr.s_addr))
	    ip1->s_addr &= IN_CLASSC_NET;
        sa = *((struct sockaddr_in *)&(ifp->if_addrlist->ifa_broadaddr));
	arg.client_address.address_type = IP_ADDR_TYPE;
	ip = &arg.client_address.bp_address.ip_addr;
	inp = &((struct sockaddr_in *)&(ifp->if_addrlist->ifa_addr))->sin_addr;
	ip->net = inp->s_net;
	ip->host = inp->s_host;
	ip->lh = inp->s_lh;
	ip->impno = inp->s_impno;

	tv.tv_sec = 3;
	tv.tv_usec = 999;

	hostnamelen = 0;

	res.client_name = (bp_machine_name_t) kmem_alloc(MAX_MACHINE_NAME + 1);
        if (res.client_name == NULL) {
		printf ("Boot: out of memory\n");
                return (ENOMEM);;
        }
	res.domain_name = (bp_machine_name_t) kmem_alloc(MAX_MACHINE_NAME + 1);
        if (res.domain_name == NULL) {
		printf ("Boot: out of memory\n");
                return (ENOMEM);;
        }
	for (;;) {
                int msg = 0;

		status = pmap_rmtcall(&sa, (u_long)BOOTPARAMPROG,
		     (u_long)BOOTPARAMVERS, BOOTPARAMPROC_WHOAMI,
		     xdr_bp_whoami_arg, (char *)&arg,
                     xdr_bp_whoami_res, (char *)&res,
		     tv, &bootparam_addr);
                if (status == RPC_TIMEDOUT) {
                        if (msg == 0) {
                                printf("%s%s\n", "No bootparam server",
                                        " responding; still trying");
                                msg = 1;
                        }
                        continue;
                } else {
                        if (msg) {
                                printf("%s%s\n", "Bootparam response",
                                        " received");
                        }
			(void) set_ether_addr(bootparam_addr.sin_addr,
			    (struct ether_addr *)&destetheraddr);
                        break;
                }
        }
        if (status != RPC_SUCCESS) {
                printf("Boot: RPC call failed (status %d)\n", status);
                /*
                 * XXX should get real error here
                 */
                return ((int)status);
        }

        hostnamelen = strlen(res.client_name);
        if (hostnamelen > sizeof hostname) {
                printf("Boot: hostname returned by bootparam server is too long");
		printf("Boot: hostname '%s'\n", res.client_name);
                return (ENAMETOOLONG);
        }
        if (hostnamelen > 0) {
                bcopy(res.client_name, hostname, hostnamelen);
		hostname[hostnamelen] = '\0';
        } else {
                printf("Boot: null host name returned by bootparam server\n");
                return (ENXIO);
        }
        kmem_free(res.client_name, MAX_MACHINE_NAME);
        printf("hostname: %s\n", hostname);

        domainnamelen = strlen(res.domain_name);
        if (domainnamelen > sizeof domainname) {
                printf("Boot: domainname returned by bootparam server is too long");
		printf("Boot: domainname '%s'\n", res.domain_name);
                return (ENAMETOOLONG);
        }
        if (domainnamelen > 0) {
                bcopy(res.domain_name, domainname, domainnamelen);
                printf("domainname: %s\n", domainname);
        } else {
                printf("Boot: null domain name returned by bootparam server\n");
        }
        kmem_free(res.domain_name, MAX_MACHINE_NAME);

        if (res.router_address.address_type == IP_ADDR_TYPE) {
                sin = (struct sockaddr_in *) &rtentry.rt_dst;
                bzero(sin, sizeof *sin);
                sin->sin_family = AF_INET;
                sin = (struct sockaddr_in *) &rtentry.rt_gateway;
                bzero(sin, sizeof *sin);
                sin->sin_family = AF_INET;
                sin->sin_addr.s_net = res.router_address.bp_address.ip_addr.net;
                sin->sin_addr.s_host = res.router_address.bp_address.ip_addr.host;
                sin->sin_addr.s_lh = res.router_address.bp_address.ip_addr.lh;
                sin->sin_addr.s_impno =
                        res.router_address.bp_address.ip_addr.impno;
                rtentry.rt_flags = RTF_GATEWAY | RTF_UP;
                error = rtrequest(SIOCADDRT, &rtentry);
#ifdef	NFSDEBUG
                if (error) {
                        printf("Boot: bad routing request (error %d)\n", error);
                } else	{
			dprint(nfsdebug, 6, "whoami: rtrequest OK\n");
		}
#endif	/* NFSDEBUG */
        } else {
                printf("Boot: bootparam sever returned unknown gateway addr family %d\n",
                        res.router_address.address_type);
        }
        return (0);

}

static enum clnt_stat
callrpc(sin, prognum, versnum, procnum, inproc, in, outproc, out)
        struct sockaddr_in *sin;
        int prognum, versnum, procnum;
        xdrproc_t inproc, outproc;
        char *in, *out;
{
        CLIENT *cl;
        struct timeval tv;
        enum clnt_stat cl_stat;

        cl = clntkudp_create(sin, (u_long)prognum, (u_long)versnum, 10, u.u_cred);

        tv.tv_sec = 3;
        tv.tv_usec = 0;
        cl_stat = CLNT_CALL(cl, procnum, inproc, in, outproc, out, tv);
        AUTH_DESTROY(cl->cl_auth);
        CLNT_DESTROY(cl);

        return (cl_stat);
}

static int
getfile(fileid, server_name, server_address, server_path)
	char *fileid;
	char *server_name;
	struct sockaddr *server_address;
	char *server_path;
{
	struct bp_getfile_arg arg;
	struct bp_getfile_res res;
	enum clnt_stat status;
	int tries;
	int error;

	arg.client_name = hostname;
	arg.file_id = fileid;
	bzero(&res, sizeof res);
	if (bootparam_addr.sin_addr.s_addr == 0) {
		error = whoami();
		if (error) {
			printf ("Boot: dialog with bootparam server failed\n");
			return (error);
		}
	}
	res.server_name = (bp_machine_name_t) kmem_alloc(MAX_MACHINE_NAME + 1);
	res.server_path = (bp_machine_name_t) kmem_alloc(MAX_MACHINE_NAME + 1);
	if (res.server_name == NULL || res.server_path == NULL) {
		printf ("Boot: out of memory\n");
		error = ENOMEM;
		goto bad;
	}
        for (tries = 0; tries < 20; tries++) {
                int msg = 0;

                status = callrpc(&bootparam_addr, BOOTPARAMPROG, BOOTPARAMVERS,
                        BOOTPARAMPROC_GETFILE, xdr_bp_getfile_arg, (char *)&arg,
                        xdr_bp_getfile_res, (char *)&res);
                if (status == RPC_TIMEDOUT) {
			if (msg == 0) {
				printf("%s%s\n", "No bootparam server",
					" responding; still trying");
                                msg = 1;
                        }
                        continue;
                } else {
			if (msg == 1)	{
				printf("%s%s\n", "Response received from",
					" bootparams server");
			}
                        break;
                }
        }
        if (status != RPC_SUCCESS) {
                if (status == RPC_TIMEDOUT) {
			printf ("Boot: dialog with bootparam server timed out\n");
                        error = ETIMEDOUT;
                } else {
                        error = (int)status;
			printf ("Boot: dialog with bootparam server failed (error 0x%x)\n", error);
                }
                goto bad;
        }
        (void) strcpy(server_name, res.server_name);
	printf("server name '%s'\n", server_name);
        switch (res.server_address.address_type) {
        case IP_ADDR_TYPE:
                bzero(server_address, sizeof *server_address);
                server_address->sa_family = AF_INET;
                ((struct sockaddr_in *)server_address)->sin_addr.s_net =
                        res.server_address.bp_address.ip_addr.net;
                ((struct sockaddr_in *)server_address)->sin_addr.s_host =
                        res.server_address.bp_address.ip_addr.host;
                ((struct sockaddr_in *)server_address)->sin_addr.s_lh =
                        res.server_address.bp_address.ip_addr.lh;
                ((struct sockaddr_in *)server_address)->sin_addr.s_impno =
                        res.server_address.bp_address.ip_addr.impno;
		/*
		 * Set the server ether_address.
		 */
		(void) set_ether_addr(((struct sockaddr_in *)server_address)->sin_addr,
			&destetheraddr);
                break;
        default:
                printf("Boot: bootparam server returned unknown address type %d\n",
                        res.server_address.address_type);
                error = EPROTONOSUPPORT;
                goto bad;
        }
        (void) strcpy(server_path, res.server_path);
	printf("root pathname '%s'\n", server_path);
        kmem_free(res.server_name, MAX_MACHINE_NAME + 1);
        kmem_free(res.server_path, MAX_MACHINE_NAME + 1);
        if (*server_name == '\0' || *server_path == '\0' ||
            res.server_address.bp_address.ip_addr.net == 0 &&
            res.server_address.bp_address.ip_addr.host == 0 &&
            res.server_address.bp_address.ip_addr.lh == 0 &&
            res.server_address.bp_address.ip_addr.impno == 0) {
                return (-1);
        } else {
                return (0);
        }
bad:
	printf("Boot: can't get bootparam server to answer for this client (error 0x%x)\n", error);
        if (res.server_name) {
                kmem_free(res.server_name, MAX_MACHINE_NAME + 1);
        }
        if (res.server_path) {
                kmem_free(res.server_path, MAX_MACHINE_NAME + 1);
        }
	return (error);
}

/*
 * Call mount daemon on server sin to mount path.
 * sin_port is set to nfs port and fh is the fhandle
 * returned from the server.
 */
static
mountrpc(sin, path, fh)
	struct sockaddr_in *sin;
	char *path;
	fhandle_t *fh;
{
	struct fhstatus fhs;
	int error;
	enum clnt_stat status;


	error = pmap_kgetport(sin, (u_long)MOUNTPROG,
	    (u_long)MOUNTVERS, (u_long)IPPROTO_UDP);
	if (error) {
		printf("Boot: cannot get port for mount service");
		printf("Boot: unable to mount '%s' (error %d)\n", path, error);
	}
	do {
	    status = callrpc(sin, MOUNTPROG, MOUNTVERS, MOUNTPROC_MNT, xdr_bp_path_t,
		(char *)&path, xdr_fhstatus, (char *)&fhs);
	} while (status == RPC_TIMEDOUT);

	if (status != RPC_SUCCESS) {
		printf("Boot: unable to mount '%s' (error %d)\n", path, status);
		return((int)status);
	}
	sin->sin_port = htons(NFS_PORT);
	*fh = fhs.fhs_fh;
	return (fhs.fhs_status);
}

struct vnode *
nfsrootvp(vfsp, sin, fh, servername)
        struct vfs *vfsp;               /* vfs of fs, if NULL amke one */
        struct sockaddr_in *sin;        /* server address */
        fhandle_t *fh;                  /* swap file fhandle */
        char *servername;               /* swap server name */
{
	struct vnode *rtvp = NULL;      /* the server's root */
        struct mntinfo *mi = NULL;      /* mount info, pointed at by vfs */
        struct vattr va;                /* root vnode attributes */
        struct nfsfattr na;             /* root vnode attributes in nfs form */
        struct statfs sb;               /* server's file system stats */
        struct ifnet *ifp;              /* interface */
        extern struct ifnet loif;

	/*
         * Get the internet address for the first AF_INET interface
         * using reverse arp. This is not quite right because the
         * interface may not be ethernet! XXX
         */
        if ((ifp = if_ifwithaf(AF_INET)) == 0 /* NEVER || ifp == &loif */) {
		printf("Boot:: no INET interface\n");
                return (NULL);
        }
        if (!address_known(ifp)) {
                revarp_myaddr(ifp);
        }

        /*
         * create a mount record and link it to the vfs struct
         */
        mi = (struct mntinfo *)kmem_alloc((u_int)sizeof(*mi));
        bzero((caddr_t)mi, sizeof(*mi));
        mi->mi_hard = 1;
        mi->mi_addr = *sin;
        mi->mi_retrans = NFS_RETRIES;
        mi->mi_timeo = NFS_TIMEO;
        mi->mi_mntno = nfsmntno++;
        bcopy(servername, mi->mi_hostname, HOSTNAMESZ);

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
		printf ("Boot: unable to make a root vnode\n");
                goto bad;
        }
        rtvp->v_flag |= VROOT;

        if (VOP_GETATTR(rtvp, &va, u.u_cred)) {
		printf ("Boot: unable to get attributes of root\n");
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
        if (VFS_STATFS(vfsp, &sb)) {
		printf ("Boot: unable to stat root file system\n");
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
	printf("nfsrootvp: bad\n");
        if (mi) {
                kmem_free((caddr_t)mi, sizeof (*mi));
        }
        return (NULL);
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
#ifdef NFSDEBUG
	dprint(nfsdebug, 4, "nfs_statfs vfs %x\n", vfsp);
#endif
	error = rfscall(mi, RFS_STATFS, xdr_fhandle,
	    (caddr_t)fh, xdr_statfs, (caddr_t)&fs, u.u_cred);
	if (!error) {
		error = geterrno(fs.fs_status);
	} else {
		printf ("Boot: can't stat file system (error 0x%x)\n", error);
		goto bad;
	}
	if (!error) {
		if (mi->mi_stsize) {
			mi->mi_stsize = MIN(mi->mi_stsize, fs.fs_tsize);
		} else {
			mi->mi_stsize = fs.fs_tsize;
		}
		sbp->f_bsize = fs.fs_bsize;
		sbp->f_blocks = fs.fs_blocks;
		sbp->f_bfree = fs.fs_bfree;
		sbp->f_bavail = fs.fs_bavail;
		/*
		 * XXX This is wrong - should be a real fsid
		 */
		bcopy((caddr_t)&vfsp->vfs_fsid,
		    (caddr_t)&sbp->f_fsid, sizeof (fsid_t));
	} else
		printf ("Boot: bad stat from file system (error 0x%x)\n", error);
bad:
#ifdef NFSDEBUG
	dprint(nfsdebug, 4, "nfs_statfs returning %d\n", error);
#endif
	return (error);
}
