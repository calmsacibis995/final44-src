h08128
s 00002/00002/00402
d D 8.1 93/06/06 11:41:10 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00403
d D 5.4 92/02/09 08:48:57 pendry 4 3
c merge in new release
e
s 00003/00002/00401
d D 5.3 91/05/12 15:56:05 pendry 3 2
c checkpoint for network tape
e
s 00007/00005/00396
d D 5.2 91/03/17 13:33:57 pendry 2 1
c from amd5.3 alpha11
e
s 00401/00000/00000
d D 5.1 90/06/29 12:01:17 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: rpc_fwd.c,v 5.2 90/06/23 22:19:57 jsp Rel $
E 2
I 2
D 3
 * $Id: rpc_fwd.c,v 5.2.1.2 91/03/03 20:46:57 jsp Alpha $
E 2
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
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
 * $Id: rpc_fwd.c,v 5.2.1.3 91/05/07 22:18:30 jsp Alpha $
E 4
I 4
 * $Id: rpc_fwd.c,v 5.2.2.1 1992/02/09 15:09:01 jsp beta $
E 4
 *
E 3
 */

/*
 * RPC packet forwarding
 */

#include "am.h"
#include <sys/ioctl.h>
#ifndef F_SETFL
#include <fcntl.h>
#endif /* F_SETFL */
#ifndef FNDELAY
#include <sys/file.h>
#endif /* FNDELAY */

/*
 * Note that the ID field in the external packet is only
 * ever treated as a 32 bit opaque data object, so there
 * is no need to convert to and from network byte ordering.
 */

/*
 * Each pending reply has an rpc_forward structure
 * associated with it.  These have a 15 second lifespan.
 * If a new structure is required, then an expired
 * one will be re-allocated if available, otherwise a fresh
 * one is allocated.  Whenever a reply is received the
 * structure is discarded.
 */
typedef struct rpc_forward rpc_forward;
struct rpc_forward {
	qelem	rf_q;		/* Linked list */
	time_t	rf_ttl;		/* Time to live */
	u_int	rf_xid;		/* Packet id */
	u_int	rf_oldid;	/* Original packet id */
	fwd_fun	rf_fwd;		/* Forwarding function */
	voidp	rf_ptr;
	struct sockaddr_in rf_sin;
};

/*
 * Head of list of pending replies
 */
extern qelem rpc_head;
qelem rpc_head = { &rpc_head, &rpc_head };

static u_int xid;
#define	XID_ALLOC()	(xid++)

#define	MAX_PACKET_SIZE	8192	/* Maximum UDP packet size */

int fwd_sock;

/*
 * Allocate a rely structure
 */
static rpc_forward *fwd_alloc()
{
	time_t now = clocktime();
	rpc_forward *p = 0, *p2;

#ifdef DEBUG
	/*dlog("fwd_alloca: rpc_head = %#x", rpc_head.q_forw);*/
#endif /* DEBUG */
	/*
	 * First search for an existing expired one.
	 */
	ITER(p2, rpc_forward, &rpc_head) {
		if (p2->rf_ttl <= now) {
			p = p2;
			break;
		}
	}

	/*
	 * If one couldn't be found then allocate
	 * a new structure and link it at the
	 * head of the list.
	 */
	if (p) {
		/*
		 * Call forwarding function to say that
		 * this message was junked.
		 */
#ifdef DEBUG
		dlog("Re-using packet forwarding slot - id %#x", p->rf_xid);
#endif /* DEBUG */
		if (p->rf_fwd)
			(*p->rf_fwd)(0, 0, 0, &p->rf_sin, p->rf_ptr, FALSE);
		rem_que(&p->rf_q);
	} else {
		p = ALLOC(rpc_forward);
	}
	ins_que(&p->rf_q, &rpc_head);

	/*
	 * Set the time to live field
	 * Timeout in 43 seconds 
	 */
	p->rf_ttl = now + 43;

#ifdef DEBUG
	/*dlog("fwd_alloca: rpc_head = %#x", rpc_head.q_forw);*/
#endif /* DEBUG */
	return p;
}

/*
 * Free an allocated reply structure.
 * First unlink it from the list, then
 * discard it.
 */
static void fwd_free(p)
rpc_forward *p;
{
#ifdef DEBUG
	/*dlog("fwd_free: rpc_head = %#x", rpc_head.q_forw);*/
#endif /* DEBUG */
	rem_que(&p->rf_q);
#ifdef DEBUG
	/*dlog("fwd_free: rpc_head = %#x", rpc_head.q_forw);*/
#endif /* DEBUG */
D 2
	free(p);
E 2
I 2
	free((voidp) p);
E 2
}

/*
 * Initialise the RPC forwarder
 */
int fwd_init()
{
	int on = 1;

	/*
	 * Create ping socket
	 */
	fwd_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (fwd_sock < 0) {
		plog(XLOG_ERROR, "Unable to create RPC forwarding socket: %m");
		return errno;
	}

	/*
	 * Some things we talk to require a priv port - so make one here
	 */
	if (bind_resv_port(fwd_sock, (unsigned short *) 0) < 0)
		plog(XLOG_ERROR, "can't bind privileged port");

	if (fcntl(fwd_sock, F_SETFL, FNDELAY) < 0 &&
			ioctl(fwd_sock, FIONBIO, &on) < 0) {
		plog(XLOG_ERROR, "Can't set non-block on forwarding socket: %m");
		return errno;
	}

	return 0;
}

/*
 * Locate a packet in the forwarding list
 */
static rpc_forward *fwd_locate(id)
u_int id;
{
	rpc_forward *p;

	ITER(p, rpc_forward, &rpc_head) {
		if (p->rf_xid == id)
			return p;
	}

	return 0;
}

/*
 * This is called to forward a packet to another
 * RPC server.  The message id is changed and noted
 * so that when a reply appears we can tie it up
 * correctly.  Just matching the reply's source address
 * would not work because it might come from a
 * different address.
 */
int fwd_packet(type_id, pkt, len, fwdto, replyto, i, cb)
int type_id;
voidp pkt;
int len;
struct sockaddr_in *fwdto, *replyto;
voidp i;
fwd_fun cb;
{
	rpc_forward *p;
	u_int *pkt_int;
	int error;

	if ((int)amd_state >= (int)Finishing)
		return ENOENT;

	/*
	 * See if the type_id is fully specified.
	 * If so, then discard any old entries
	 * for this id.
	 * Otherwise make sure the type_id is
	 * fully qualified by allocating an id here.
	 */
#ifdef DEBUG
	switch (type_id & RPC_XID_MASK) {
	case RPC_XID_PORTMAP: dlog("Sending PORTMAP request"); break;
	case RPC_XID_MOUNTD: dlog("Sending MOUNTD request %#x", type_id); break;
	case RPC_XID_NFSPING: dlog("Sending NFS ping"); break;
	default: dlog("UNKNOWN RPC XID"); break;
	}
#endif /* DEBUG */

	if (type_id & ~RPC_XID_MASK) {
#ifdef DEBUG
		/*dlog("Fully qualified rpc type provided");*/
#endif /* DEBUG */
		p = fwd_locate(type_id);
		if (p) {
#ifdef DEBUG
			dlog("Discarding earlier rpc fwd handle");
#endif /* DEBUG */
			fwd_free(p);
		}
	} else {
#ifdef DEBUG
		dlog("Allocating a new xid...");
#endif /* DEBUG */
		type_id = MK_RPC_XID(type_id, XID_ALLOC());
	}

	p = fwd_alloc();
	if (!p)
		return ENOBUFS;

	error = 0;

	pkt_int = (u_int *) pkt;

	/*
	 * Get the original packet id
	 */
	p->rf_oldid = *pkt_int;

	/*
	 * Replace with newly allocated id
	 */
	p->rf_xid = *pkt_int = type_id;

	/*
	 * The sendto may fail if, for example, the route
	 * to a remote host is lost because an intermediate
	 * gateway has gone down.  Important to fill in the
	 * rest of "p" otherwise nasty things happen later...
	 */
#ifdef DEBUG
D 2
	dlog("Sending packet id %#x to %#08x.%04x", p->rf_xid, ntohl(fwdto->sin_addr.s_addr), ntohs(fwdto->sin_port));
E 2
I 2
	{ char dq[20]; 
	dlog("Sending packet id %#x to %s.%d", p->rf_xid, inet_dquad(dq, fwdto->sin_addr.s_addr), ntohs(fwdto->sin_port));
	}
E 2
#endif /* DEBUG */
	if (sendto(fwd_sock, (char *) pkt, len, 0,
			(struct sockaddr *) fwdto, sizeof(*fwdto)) < 0)
		error = errno;

	/*
	 * Save callback function and return address
	 */
	p->rf_fwd = cb;
	if (replyto)
		p->rf_sin = *replyto;
	else
		bzero((voidp) &p->rf_sin, sizeof(p->rf_sin));
	p->rf_ptr = i;

	return error;
}

/*
 * Called when some data arrives on the forwarding socket
 */
void fwd_reply()
{
	int len;
#ifdef DYNAMIC_BUFFERS
	voidp pkt;
#else
	u_int pkt[MAX_PACKET_SIZE/sizeof(u_int)+1];
#endif /* DYNAMIC_BUFFERS */
	u_int *pkt_int;
	int rc;
	rpc_forward *p;
	struct sockaddr_in src_addr;
	int src_addr_len;

	/*
	 * Determine the length of the packet
	 */
#ifdef DYNAMIC_BUFFERS
	if (ioctl(fwd_sock, FIONREAD, &len) < 0) {
		plog(XLOG_ERROR, "Error reading packet size: %m");
		return;
	}

	/*
	 * Allocate a buffer
	 */
	pkt = (voidp) malloc((unsigned) len);
	if (!pkt) {
		plog(XLOG_ERROR, "Out of buffers in fwd_reply");
		return;
	}
#else
	len = MAX_PACKET_SIZE;
#endif /* DYNAMIC_BUFFERS */

	/*
	 * Read the packet and check for validity
	 */
again:
	src_addr_len = sizeof(src_addr);
	rc = recvfrom(fwd_sock, (char *) pkt, len, 0,
			(struct sockaddr *) &src_addr, &src_addr_len);
	if (rc < 0 || src_addr_len != sizeof(src_addr) ||
			src_addr.sin_family != AF_INET) {
		if (rc < 0 && errno == EINTR)
			goto again;
		plog(XLOG_ERROR, "Error reading RPC reply: %m");
		goto out;
	}

#ifdef DYNAMIC_BUFFERS
	if (rc != len) {
		plog(XLOG_ERROR, "Short read in fwd_reply");
		goto out;
	}
#endif /* DYNAMIC_BUFFERS */

	/*
	 * Do no more work if finishing soon
	 */
	if ((int)amd_state >= (int)Finishing)
		goto out;

	/*
	 * Find packet reference
	 */
	pkt_int = (u_int *) pkt;

#ifdef DEBUG
	switch (*pkt_int & RPC_XID_MASK) {
	case RPC_XID_PORTMAP: dlog("Receiving PORTMAP reply"); break;
	case RPC_XID_MOUNTD: dlog("Receiving MOUNTD reply %#x", *pkt_int); break;
	case RPC_XID_NFSPING: dlog("Receiving NFS ping %#x", *pkt_int); break;
	default: dlog("UNKNOWN RPC XID"); break;
	}
#endif /* DEBUG */

	p = fwd_locate(*pkt_int);
	if (!p) {
#ifdef DEBUG
		dlog("Can't forward reply id %#x", *pkt_int);
#endif /* DEBUG */
		goto out;
	}

	if (p->rf_fwd) {
		/*
		 * Put the original message id back
		 * into the packet.
		 */
		*pkt_int = p->rf_oldid;

		/*
		 * Call forwarding function
		 */
D 2
		(*p->rf_fwd)(pkt, rc, &src_addr, &p->rf_sin, p->rf_ptr, TRUE);
E 2
I 2
		(*p->rf_fwd)((voidp) pkt, rc, &src_addr, &p->rf_sin, p->rf_ptr, TRUE);
E 2
	}

	/*
	 * Free forwarding info
	 */
	fwd_free(p);

out:;
#ifdef DYNAMIC_BUFFERS
	/*
	 * Free the packet
	 */
D 2
	free(pkt);
E 2
I 2
	free((voidp) pkt);
E 2
#endif /* DYNAMIC_BUFFERS */
}
E 1
