h47506
s 00002/00002/00691
d D 8.1 93/06/06 11:41:32 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00692
d D 5.4 92/02/09 08:49:05 pendry 4 3
c merge in new release
e
s 00018/00009/00675
d D 5.3 91/05/12 15:56:15 pendry 3 2
c checkpoint for network tape
e
s 00088/00042/00596
d D 5.2 91/03/17 13:34:08 pendry 2 1
c from amd5.3 alpha11
e
s 00638/00000/00000
d D 5.1 90/06/29 12:01:20 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: srvr_nfs.c,v 5.2 90/06/23 22:20:02 jsp Rel $
E 2
I 2
D 3
 * $Id: srvr_nfs.c,v 5.2.1.3 91/03/17 17:44:37 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: srvr_nfs.c,v 5.2.1.6 91/05/07 22:18:36 jsp Alpha $
E 4
I 4
 * $Id: srvr_nfs.c,v 5.2.2.1 1992/02/09 15:09:06 jsp beta $
E 4
 *
E 3
 */

/*
 * NFS server modeling
 */

#include "am.h"
#include <netdb.h>
#include <rpc/pmap_prot.h>
#include "mount.h"

extern qelem nfs_srvr_list;
qelem nfs_srvr_list = { &nfs_srvr_list, &nfs_srvr_list };

typedef struct nfs_private {
	u_short np_mountd;	/* Mount daemon port number */
D 2
	char np_mountd_inval;	/* Port may be invalid */
E 2
I 2
	char np_mountd_inval;	/* Port *may* be invalid */
E 2
	int np_ping;		/* Number of failed ping attempts */
	time_t np_ttl;		/* Time when server is thought dead */
	int np_xid;		/* RPC transaction id for pings */
	int np_error;		/* Error during portmap request */
} nfs_private;

static int np_xid;	/* For NFS pings */
#define	NPXID_ALLOC()	(++np_xid)
/*#define	NPXID_ALLOC()	((++np_xid&0x0fffffff) == 0 ? npxid_gc() : np_xid)*/

/*
 * Number of pings allowed to fail before host is declared down
 * - three-fifths of the allowed mount time...
#define	MAX_ALLOWED_PINGS	((((ALLOWED_MOUNT_TIME + 5 * AM_PINGER - 1) * 3) / 5) / AM_PINGER)
 */
#define	MAX_ALLOWED_PINGS	(3 + /* for luck ... */ 1)

/*
 * How often to ping when starting a new server
 */
#define	FAST_NFS_PING		3

#if (FAST_NFS_PING * MAX_ALLOWED_PINGS) >= ALLOWED_MOUNT_TIME
 #error: sanity check failed
/*
 you cannot do things this way...
 sufficient fast pings must be given the chance to fail
 within the allowed mount time
 */
#endif /* (FAST_NFS_PING * MAX_ALLOWED_PINGS) >= ALLOWED_MOUNT_TIME */

static int ping_len;
static char ping_buf[sizeof(struct rpc_msg) + 32];

/*
I 2
 * Flush any cached data
 */
void flush_srvr_nfs_cache P((void));
void flush_srvr_nfs_cache()
{
	fserver *fs = 0;

	ITER(fs, fserver, &nfs_srvr_list) {
		nfs_private *np = (nfs_private *) fs->fs_private;
		if (np) {
			np->np_mountd_inval = TRUE;
			np->np_error = -1;
		}
	}
}

/*
E 2
 * Startup the NFS ping
 */
I 2
static void start_ping(P_void);
E 2
static void start_ping()
{
	XDR ping_xdr;
	struct rpc_msg ping_msg;

	rpc_msg_init(&ping_msg, NFS_PROGRAM, NFS_VERSION, NFSPROC_NULL);

	/*
	 * Create an XDR endpoint
	 */
	xdrmem_create(&ping_xdr, ping_buf, sizeof(ping_buf), XDR_ENCODE);

	/*
	 * Create the NFS ping message
	 */
	if (!xdr_callmsg(&ping_xdr, &ping_msg)) {
		plog(XLOG_ERROR, "Couldn't create ping RPC message");
		going_down(3);
	}

	/*
	 * Find out how long it is
	 */
	ping_len = xdr_getpos(&ping_xdr);

	/*
	 * Destroy the XDR endpoint - we don't need it anymore
	 */
	xdr_destroy(&ping_xdr);
}


/*
 * Called when a portmap reply arrives
 */
I 2
/*ARGSUSED*/
static void got_portmap P((voidp pkt, int len, struct sockaddr_in *sa, struct sockaddr_in *ia, voidp idv, int done));
E 2
static void got_portmap(pkt, len, sa, ia, idv, done)
voidp pkt;
int len;
D 2
struct sockaddr_in *sa, *ia;
E 2
I 2
struct sockaddr_in *sa;
struct sockaddr_in *ia;
E 2
voidp idv;
int done;
{
	fserver *fs2 = (fserver *) idv;
	fserver *fs = 0;
I 2

	/*
	 * Find which fileserver we are talking about
	 */
E 2
	ITER(fs, fserver, &nfs_srvr_list)
		if (fs == fs2)
			break;

	if (fs == fs2) {
		u_long port = 0;	/* XXX - should be short but protocol is naff */
		int error = done ? pickup_rpc_reply(pkt, len, (voidp) &port, xdr_u_long) : -1;
		nfs_private *np = (nfs_private *) fs->fs_private;
		if (!error && port) {
#ifdef DEBUG
			dlog("got port (%d) for mountd on %s", port, fs->fs_host);
#endif /* DEBUG */
			/*
			 * Grab the port number.  Portmap sends back
			 * an unsigned long in native ordering, so it
			 * needs converting to a unsigned short in
			 * network ordering.
			 */
			np->np_mountd = htons((u_short) port);
			np->np_mountd_inval = FALSE;
			np->np_error = 0;
		} else {
#ifdef DEBUG
			dlog("Error fetching port for mountd on %s", fs->fs_host);
#endif /* DEBUG */
			/*
			 * Almost certainly no mountd running on remote host
			 */
			np->np_error = error ? error : ETIMEDOUT;
		}
		if (fs->fs_flags & FSF_WANT)
			wakeup_srvr(fs);
	} else if (done) {
#ifdef DEBUG
		dlog("Got portmap for old port request");
#endif /* DEBUG */
	} else {
#ifdef DEBUG
		dlog("portmap request timed out");
#endif /* DEBUG */
	}
}

/*
 * Obtain portmap information
 */
I 2
static int call_portmap P((fserver *fs, AUTH *auth, unsigned long prog, unsigned long vers, unsigned long prot));
E 2
static int call_portmap(fs, auth, prog, vers, prot)
fserver *fs;
AUTH *auth;
unsigned long prog, vers, prot;
{
	struct rpc_msg pmap_msg;
	int len;
	char iobuf[UDPMSGSIZE];
	int error;
	struct pmap pmap;

	rpc_msg_init(&pmap_msg, PMAPPROG, PMAPVERS, (unsigned long) 0);
	pmap.pm_prog = prog;
	pmap.pm_vers = vers;
	pmap.pm_prot = prot;
	pmap.pm_port = 0;
	len = make_rpc_packet(iobuf, sizeof(iobuf), PMAPPROC_GETPORT,
			&pmap_msg, (voidp) &pmap, xdr_pmap, auth);
	if (len > 0) {
		struct sockaddr_in sin;
		bzero((voidp) &sin, sizeof(sin));
		sin = *fs->fs_ip;
		sin.sin_port = htons(PMAPPORT);
		error = fwd_packet(RPC_XID_PORTMAP, (voidp) iobuf, len,
				&sin, &sin, (voidp) fs, got_portmap);
	} else {
		error = -len;
	}
	return error;
}

static void nfs_keepalive P((fserver*));

static void recompute_portmap P((fserver *fs));
static void recompute_portmap(fs)
fserver *fs;
{				
D 3
	if (!nfs_auth)
		nfs_auth = authunix_create_default();
	if (!nfs_auth) {
E 3
I 3
	int error;

	if (nfs_auth)
		error = 0;
	else
		error = make_nfs_auth();

	if (error) {
E 3
		nfs_private *np = (nfs_private *) fs->fs_private;
D 3
		np->np_error = ENOBUFS;
E 3
I 3
		np->np_error = error;
E 3
	} else {
		call_portmap(fs, nfs_auth, MOUNTPROG,
			MOUNTVERS, (unsigned long) IPPROTO_UDP);
	}
}

/*
 * This is called when we get a reply to an RPC ping.
 * The value of id was taken from the nfs_private
 * structure when the ping was transmitted.
 */
/*ARGSUSED*/
I 2
static void nfs_pinged P((voidp pkt, int len, struct sockaddr_in *sp, struct sockaddr_in *tsp, voidp idv, int done));
E 2
static void nfs_pinged(pkt, len, sp, tsp, idv, done)
voidp pkt;
int len;
D 2
struct sockaddr_in *sp, *tsp;
E 2
I 2
struct sockaddr_in *sp;
struct sockaddr_in *tsp;
E 2
voidp idv;
int done;
{
	int xid = (int) idv;
	fserver *fs;
I 2
#ifdef DEBUG
E 2
	int found_map = 0;
I 2
#endif /* DEBUG */
E 2

	if (!done)
		return;

	/*
	 * For each node...
	 */
	ITER(fs, fserver, &nfs_srvr_list) {
		nfs_private *np = (nfs_private *) fs->fs_private;
		if (np->np_xid == xid) {
			/*
			 * Reset the ping counter.
			 * Update the keepalive timer.
			 * Log what happened.
			 */
			if (fs->fs_flags & FSF_DOWN) {
				fs->fs_flags &= ~FSF_DOWN;
				if (fs->fs_flags & FSF_VALID) {
					srvrlog(fs, "is up");
				} else {
D 2
					srvrlog(fs, "ok");
E 2
I 2
					if (np->np_ping > 1)
						srvrlog(fs, "ok");
#ifdef DEBUG
					else
						srvrlog(fs, "starts up");
#endif
E 2
					fs->fs_flags |= FSF_VALID;
				}

#ifdef notdef
				/* why ??? */
				if (fs->fs_flags & FSF_WANT)
					wakeup_srvr(fs);
#endif /* notdef */
I 3
				map_flush_srvr(fs);
E 3
			} else {
				if (fs->fs_flags & FSF_VALID) {
#ifdef DEBUG
					dlog("file server %s type nfs is still up", fs->fs_host);
#endif /* DEBUG */
				} else {
D 2
					srvrlog(fs, "ok");
E 2
I 2
					if (np->np_ping > 1)
						srvrlog(fs, "ok");
E 2
					fs->fs_flags |= FSF_VALID;
				}
			}

			/*
			 * Adjust ping interval
			 */
			untimeout(fs->fs_cid);
			fs->fs_cid = timeout(fs->fs_pinger, nfs_keepalive, (voidp) fs);

			/*
			 * Update ttl for this server
			 */
			np->np_ttl = clocktime() +
				(MAX_ALLOWED_PINGS - 1) * FAST_NFS_PING + fs->fs_pinger - 1;

			/*
			 * New RPC xid...
			 */
			np->np_xid = NPXID_ALLOC();

			/*
			 * Failed pings is zero...
			 */
			np->np_ping = 0;

			/*
			 * Recompute portmap information if not known
			 */
			if (np->np_mountd_inval)
				recompute_portmap(fs);

I 2
#ifdef DEBUG	
E 2
			found_map++;
I 2
#endif /* DEBUG */
E 2
			break;
		}
	}

#ifdef DEBUG
	if (found_map == 0)
		dlog("Spurious ping packet");
#endif /* DEBUG */
}

/*
 * Called when no ping-reply received
 */
static void nfs_timed_out P((fserver *fs));
static void nfs_timed_out(fs)
fserver *fs;
{
	nfs_private *np = (nfs_private *) fs->fs_private;

	/*
I 2
	 * Another ping has failed
	 */
	np->np_ping++;

	/*
E 2
	 * Not known to be up any longer
	 */
	if (FSRV_ISUP(fs)) {
		fs->fs_flags &= ~FSF_VALID;
D 2
		srvrlog(fs, "not responding");
E 2
I 2
		if (np->np_ping > 1)
			srvrlog(fs, "not responding");
E 2
	}

	/*
D 2
	 * Another ping has failed
	 */
	np->np_ping++;

	/*
E 2
	 * If ttl has expired then guess that it is dead
	 */
	if (np->np_ttl < clocktime()) {
I 3
		int oflags = fs->fs_flags;
E 3
		if ((fs->fs_flags & FSF_DOWN) == 0) {
			/*
			 * Server was up, but is now down.
			 */
			srvrlog(fs, "is down");
			fs->fs_flags |= FSF_DOWN|FSF_VALID;
D 2
			if (fs->fs_flags & FSF_WANT)
				wakeup_srvr(fs);
E 2
			/*
			 * Since the server is down, the portmap
			 * information may now be wrong, so it
			 * must be flushed from the local cache
			 */
			flush_nfs_fhandle_cache(fs);
			np->np_error = -1;
I 2
#ifdef notdef
E 2
			/*
			 * Pretend just one ping has failed now
			 */
			np->np_ping = 1;
I 2
#endif
E 2
		} else {
			/*
			 * Known to be down
			 */
D 3
			fs->fs_flags |= FSF_VALID;
E 3
I 2
#ifdef DEBUG
D 3
			srvrlog(fs, "starts down");
E 3
I 3
			if ((fs->fs_flags & FSF_VALID) == 0)
				srvrlog(fs, "starts down");
E 3
#endif
I 3
			fs->fs_flags |= FSF_VALID;
E 3
E 2
		}
I 2
D 3
		if (fs->fs_flags & FSF_WANT)
E 3
I 3
		if (oflags != fs->fs_flags && (fs->fs_flags & FSF_WANT))
E 3
			wakeup_srvr(fs);
E 2
	} else {
#ifdef DEBUG
		if (np->np_ping > 1)
			dlog("%d pings to %s failed - at most %d allowed", np->np_ping, fs->fs_host, MAX_ALLOWED_PINGS);
#endif /* DEBUG */
	}

	/*
	 * Run keepalive again
	 */
	nfs_keepalive(fs);
}

/*
 * Keep track of whether a server is alive
 */
static void nfs_keepalive P((fserver *fs));
static void nfs_keepalive(fs)
fserver *fs;
{
	int error;
	nfs_private *np = (nfs_private *) fs->fs_private;
	int fstimeo = -1;

	/*
	 * Send an NFS ping to this node
	 */

	if (ping_len == 0)
		start_ping();

	/*
	 * Queue the packet...
	 */
	error = fwd_packet(MK_RPC_XID(RPC_XID_NFSPING, np->np_xid), (voidp) ping_buf,
		ping_len, fs->fs_ip, (struct sockaddr_in *) 0, (voidp) np->np_xid, nfs_pinged);

	/*
	 * See if a hard error occured
	 */
	switch (error) {
	case ENETDOWN:
	case ENETUNREACH:
	case EHOSTDOWN:
	case EHOSTUNREACH:
		np->np_ping = MAX_ALLOWED_PINGS;	/* immediately down */
		np->np_ttl = (time_t) 0;
		/*
		 * This causes an immediate call to nfs_timed_out
		 * whenever the server was thought to be up.
		 * See +++ below.
		 */
		fstimeo = 0;
		break;

	case 0:
#ifdef DEBUG
		dlog("Sent NFS ping to %s", fs->fs_host);
#endif /* DEBUG */
		break;
	}

#ifdef DEBUG
	/*dlog("keepalive, ping = %d", np->np_ping);*/
#endif /* DEBUG */

	/*
	 * Back off the ping interval if we are not getting replies and
	 * the remote system is know to be down.
	 */
	switch (fs->fs_flags & (FSF_DOWN|FSF_VALID)) {
	case FSF_VALID:			/* Up */
		if (fstimeo < 0)	/* +++ see above */
			fstimeo = FAST_NFS_PING;
		break;

	case FSF_VALID|FSF_DOWN:	/* Down */
		fstimeo = fs->fs_pinger;
		break;

	default:			/* Unknown */
		fstimeo = FAST_NFS_PING;
		break;
	}

#ifdef DEBUG
	dlog("NFS timeout in %d seconds", fstimeo);
#endif /* DEBUG */

	fs->fs_cid = timeout(fstimeo, nfs_timed_out, (voidp) fs);
}

I 2
int nfs_srvr_port P((fserver *fs, u_short *port, voidp wchan));
E 2
int nfs_srvr_port(fs, port, wchan)
fserver *fs;
u_short *port;
voidp wchan;
{
	int error = -1;
	if ((fs->fs_flags & FSF_VALID) == FSF_VALID) {
		if ((fs->fs_flags & FSF_DOWN) == 0) {
			nfs_private *np = (nfs_private *) fs->fs_private;
			if (np->np_error == 0) {
				*port = np->np_mountd;
D 2
				/*
				 * Now go get it again in case it changed
				 */
				np->np_mountd_inval = TRUE;
E 2
				error = 0;
			} else {
D 2
				if (np->np_error < 0)
					recompute_portmap(fs);
E 2
				error = np->np_error;
			}
I 2
			/*
			 * Now go get the port mapping again in case it changed.
			 * Note that it is used even if (np_mountd_inval)
			 * is True.  The flag is used simply as an
			 * indication that the mountd may be invalid, not
			 * that it is known to be invalid.
			 */
			if (np->np_mountd_inval)
				recompute_portmap(fs);
			else
				np->np_mountd_inval = TRUE;
E 2
		} else {
			error = EWOULDBLOCK;
		}
	}
	if (error < 0 && wchan && !(fs->fs_flags & FSF_WANT)) {
		/*
		 * If a wait channel is supplied, and no
		 * error has yet occured, then arrange
		 * that a wakeup is done on the wait channel,
		 * whenever a wakeup is done on this fs node.
		 * Wakeup's are done on the fs node whenever
		 * it changes state - thus causing control to
		 * come back here and new, better things to happen.
		 */
		fs->fs_flags |= FSF_WANT;
		sched_task(wakeup_task, wchan, (voidp) fs);
	}
	return error;
}

static void start_nfs_pings P((fserver *fs, int pingval));
static void start_nfs_pings(fs, pingval)
fserver *fs;
int pingval;
{
	if (!(fs->fs_flags & FSF_PINGING)) {
		fs->fs_flags |= FSF_PINGING;
		if (fs->fs_cid)
			untimeout(fs->fs_cid);
		if (pingval < 0) {
			srvrlog(fs, "wired up");
			fs->fs_flags |= FSF_VALID;
			fs->fs_flags &= ~FSF_DOWN;
		} else {
			nfs_keepalive(fs);
		}
	} else {
#ifdef DEBUG
		dlog("Already running pings to %s", fs->fs_host);
#endif /* DEBUG */
	}
}

/*
 * Find an nfs server for a host.
 */
fserver *find_nfs_srvr P((mntfs *mf));
fserver *find_nfs_srvr(mf)
mntfs *mf;
{
	fserver *fs;
	struct hostent *hp = 0;
	char *host = mf->mf_fo->opt_rhost;
	struct sockaddr_in *ip;
	nfs_private *np;
	int pingval;

	/*
	 * Get ping interval from mount options.
	 * Current only used to decide whether pings
	 * are required or not.  < 0 = no pings.
	 */
	{ struct mntent mnt;
D 2
	  mnt.mnt_opts = mf->mf_fo->opt_opts;
E 2
I 2
	  mnt.mnt_opts = mf->mf_mopts;
E 2
	  pingval = hasmntval(&mnt, "ping");
#ifdef HAS_TCP_NFS
	  /*
	   * Over TCP mount, don't bother to do pings.
	   * This is experimental - maybe you want to
	   * do pings anyway...
	   */
	  if (pingval == 0 && hasmntopt(&mnt, "tcp"))
		pingval = -1;
#endif /* HAS_TCP_NFS */
	}


D 2
top:
E 2
	/*
D 2
	 * Scan the list of known servers looking
	 * for one with the same name
E 2
I 2
	 * lookup host address and canonical name
E 2
	 */
I 2
	hp = gethostbyname(host);

	/*
	 * New code from Bob Harris <harris@basil-rathbone.mit.edu>
	 * Use canonical name to keep track of file server
	 * information.  This way aliases do not generate
	 * multiple NFS pingers.  (Except when we're normalizing
	 * hosts.)
	 */
	if (hp && !normalize_hosts) host = hp->h_name;

E 2
	ITER(fs, fserver, &nfs_srvr_list) {
		if (STREQ(host, fs->fs_host)) {
			start_nfs_pings(fs, pingval);
			fs->fs_refc++;
			return fs;
		}
	}

D 2
	/*
	 * If the name is not known, it may be
	 * because it was an alternate name for
	 * the same machine.  So do a lookup and
	 * try again with the primary name if that
	 * is different.
	 * All that assuming it wasn't normalized
	 * earlier of course...
	 */
	if (hp == 0) {
		hp = gethostbyname(host);
		if (hp && !STREQ(host, hp->h_name) && !normalize_hosts) {
			host = hp->h_name;
			goto top;
		}
	}
E 2

I 2

E 2
	/*
	 * Get here if we can't find an entry
	 */
	if (hp) {
		switch (hp->h_addrtype) {
		case AF_INET:
			ip = ALLOC(sockaddr_in);
			bzero((voidp) ip, sizeof(*ip));
			ip->sin_family = AF_INET;
D 2
			ip->sin_addr = *(struct in_addr *) hp->h_addr;
E 2
I 2
			bcopy((voidp) hp->h_addr, (voidp) &ip->sin_addr, sizeof(ip->sin_addr));

E 2
			ip->sin_port = htons(NFS_PORT);
			break;

		default:
			ip = 0;
			break;
		}
	} else {
I 2
		plog(XLOG_USER, "Unknown host: %s", host);
E 2
		ip = 0;
	}

	/*
	 * Allocate a new server
	 */
	fs = ALLOC(fserver);
	fs->fs_refc = 1;
	fs->fs_host = strdup(hp ? hp->h_name : "unknown_hostname");
D 2
	host_normalize(&fs->fs_host);
E 2
I 2
	if (normalize_hosts) host_normalize(&fs->fs_host);
E 2
	fs->fs_ip = ip;
	fs->fs_cid = 0;
	if (ip) {
		fs->fs_flags = FSF_DOWN;	/* Starts off down */
	} else {
		fs->fs_flags = FSF_ERROR|FSF_VALID;
		mf->mf_flags |= MFF_ERROR;
		mf->mf_error = ENOENT;
	}
	fs->fs_type = "nfs";
	fs->fs_pinger = AM_PINGER;
	np = ALLOC(nfs_private);
	bzero((voidp) np, sizeof(*np));
	np->np_mountd_inval = TRUE;
	np->np_xid = NPXID_ALLOC();
	np->np_error = -1;
	/*
	 * Initially the server will be deemed dead after
	 * MAX_ALLOWED_PINGS of the fast variety have failed.
	 */
	np->np_ttl = clocktime() + MAX_ALLOWED_PINGS * FAST_NFS_PING - 1;
	fs->fs_private = (voidp) np;
	fs->fs_prfree = (void (*)()) free;

	if (!(fs->fs_flags & FSF_ERROR)) {
		/*
		 * Start of keepalive timer
		 */
		start_nfs_pings(fs, pingval);
	}

	/*
	 * Add to list of servers
	 */
	ins_que(&fs->fs_q, &nfs_srvr_list);

	return fs;
}
E 1
