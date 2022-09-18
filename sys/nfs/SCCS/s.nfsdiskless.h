h26232
s 00038/00004/00036
d D 8.2 95/03/30 11:26:54 mckusick 7 6
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00002/00002/00038
d D 8.1 93/06/10 23:39:35 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00039
d D 7.5 93/02/02 14:53:58 mckusick 5 4
c update for 4.4BSD from Rick Macklem
e
s 00002/00000/00038
d D 7.4 92/07/12 22:50:30 torek 4 3
c add swap credentials and root timestamp
e
s 00001/00000/00037
d D 7.3 92/02/06 18:05:08 mckusick 3 2
c add hostname to diskless header
e
s 00017/00012/00020
d D 7.2 92/01/14 12:41:36 mckusick 2 1
c update from Rick Macklem (including leases)
e
s 00032/00000/00000
d D 7.1 91/03/04 22:02:13 mckusick 1 0
c from Rick Macklem for diskless support
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 7

#ifndef _NFS_NFSDISKLESS_H_
#define _NFS_NFSDISKLESS_H_

E 7
/*
 * Structure that must be initialized for a diskless nfs client.
 * This structure is used by nfs_mountroot() to set up the root and swap
 * vnodes plus do a partial ifconfig(8) and route(8) so that the critical net
 * interface can communicate with the server.
D 2
 * For now it is statically initialized in swapvmunix.c, but someday a primary
 * bootstrap should fill it in.
E 2
I 2
 * The primary bootstrap is expected to fill in the appropriate fields before
D 7
 * starting vmunix. Whether or not the swap area is nfs mounted is determined
 * by the value in swdevt[0]. (equal to NODEV --> swap over nfs)
E 7
I 7
 * starting the kernel. Whether or not the swap area is nfs mounted is
 * determined by the value in swdevt[0]. (equal to NODEV --> swap over nfs)
E 7
 * Currently only works for AF_INET protocols.
 * NB: All fields are stored in net byte order to avoid hassles with
 * client/server byte ordering differences.
E 2
 */
I 7

/*
 * I have defined a new structure that can handle an NFS Version 3 file handle
 * but the kernel still expects the old Version 2 one to be provided. The
 * changes required in nfs_vfsops.c for using the new are documented there in
 * comments. (I felt that breaking network booting code by changing this
 * structure would not be prudent at this time, since almost all servers are
 * still Version 2 anyhow.)
 */
struct nfsv3_diskless {
	struct ifaliasreq myif;			/* Default interface */
	struct sockaddr_in mygateway;		/* Default gateway */
	struct nfs_args	swap_args;		/* Mount args for swap file */
	int		swap_fhsize;		/* Size of file handle */
	u_char		swap_fh[NFSX_V3FHMAX];	/* Swap file's file handle */
	struct sockaddr_in swap_saddr;		/* Address of swap server */
	char		swap_hostnam[MNAMELEN];	/* Host name for mount pt */
	int		swap_nblks;		/* Size of server swap file */
	struct ucred	swap_ucred;		/* Swap credentials */
	struct nfs_args	root_args;		/* Mount args for root fs */
	int		root_fhsize;		/* Size of root file handle */
	u_char		root_fh[NFSX_V3FHMAX];	/* File handle of root dir */
	struct sockaddr_in root_saddr;		/* Address of root server */
	char		root_hostnam[MNAMELEN];	/* Host name for mount pt */
	long		root_time;		/* Timestamp of root fs */
	char		my_hostnam[MAXHOSTNAMELEN]; /* Client host name */
};

E 7
struct nfs_diskless {
D 2
	struct ifaliasreq myif;		/* Info. for partial ifconfig */
	struct sockaddr	mygateway;	/* Default gateway for "route add" */
	struct nfs_args	swap_args;	/* Mount args for swap file */
	u_char		swap_fh[NFS_FHSIZE]; /* Swap file's file handle */
	struct sockaddr	swap_saddr;	/* Address of swap server */
	char		*swap_hostnam;	/* Host name for mount pt */
	struct nfs_args	root_args;	/* Mount args for root fs */
	u_char		root_fh[NFS_FHSIZE]; /* File handle of root dir */
	struct sockaddr	root_saddr;	/* Address of root server */
	char		*root_hostnam;	/* Host name for mount pt */
E 2
I 2
	struct ifaliasreq myif;			/* Default interface */
	struct sockaddr_in mygateway;		/* Default gateway */
	struct nfs_args	swap_args;		/* Mount args for swap file */
D 7
	u_char		swap_fh[NFS_FHSIZE];	/* Swap file's file handle */
E 7
I 7
	u_char		swap_fh[NFSX_V2FH];	/* Swap file's file handle */
E 7
	struct sockaddr_in swap_saddr;		/* Address of swap server */
	char		swap_hostnam[MNAMELEN];	/* Host name for mount pt */
	int		swap_nblks;		/* Size of server swap file */
I 4
	struct ucred	swap_ucred;		/* Swap credentials */
E 4
	struct nfs_args	root_args;		/* Mount args for root fs */
D 7
	u_char		root_fh[NFS_FHSIZE];	/* File handle of root dir */
E 7
I 7
	u_char		root_fh[NFSX_V2FH];	/* File handle of root dir */
E 7
	struct sockaddr_in root_saddr;		/* Address of root server */
	char		root_hostnam[MNAMELEN];	/* Host name for mount pt */
I 4
D 5
	time_t		root_time;		/* Timestamp of root fs */
E 5
I 5
	long		root_time;		/* Timestamp of root fs */
E 5
E 4
I 3
	char		my_hostnam[MAXHOSTNAMELEN]; /* Client host name */
E 3
E 2
};
I 7

#endif
E 7
E 1
