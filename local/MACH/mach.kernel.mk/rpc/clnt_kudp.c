/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	clnt_kudp.c,v $
 * Revision 2.9  89/08/02  08:05:57  jsb
 * 	Eliminated MACH conditionals. Replaced kallocs with zallocs.
 * 	[89/07/31  16:55:24  jsb]
 * 
 * Revision 2.8  89/04/22  15:27:40  gm0w
 * 	Added include of <vfs/vfs.h> to get new macro definitions.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.7  89/03/09  20:58:14  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  19:13:47  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/01/27  10:21:25  rvb
 * 	Define mclgetx for GCC.
 * 	[89/01/25            rvb]
 * 
 * Revision 2.4  89/01/24  12:24:57  af
 * 	Fix for GCC -- pass2.
 * 	[89/01/24            rvb]
 * 
 * Revision 2.3  89/01/23  15:27:24  rvb
 * 	Forward declarations for GCC.
 * 	[89/01/22            rvb]
 * 
 * Revision 2.2  89/01/18  00:59:28  jsb
 * 	Use udpmsgbuf_alloc instead of kalloc to allocate space which is later
 * 	mclgetx'd. This is because some sun network interfaces are finicky
 * 	about where such memory is allocated from, requiring us to allocate
 * 	from the mb_map, and we don't want kalloc to allocate from the mb_map,
 * 	for various reasons too awful to put into words...  best to hide such
 * 	unpleasantness in a special purpose routine like udpmsgbuf_alloc.
 * 	(Also, use udpmsgbuf_free instead of kfree.)
 * 	[89/01/17  14:21:26  jsb]
 * 
 *
 * 28-Oct-87  Peter King (king) at NeXT, Inc.
 *	Original Sun source, ported to Mach
 */ 

/* @(#)clnt_kudp.c	1.3 87/09/09 3.2/4.3NFSSRC */
/* @(#)clnt_kudp.c	1.5 87/02/27 NFSSRC */
/*      @(#)clnt_kudp.c 1.1 86/09/24 SMI      */

/*
 * clnt_kudp.c
 * Implements a kernel UPD/IP based, client side RPC.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/mbuf.h>
#include <net/if.h>
#include <net/route.h>
#include <netinet/in.h>
#include <netinet/in_pcb.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/auth.h>
#include <rpc/clnt.h>
#include <rpc/rpc_msg.h>
#include <vfs/vfs.h>
#include <kern/xpr.h>

struct mbuf	*ku_recvfrom();
int		ckuwakeup();
extern int	wakeup();
#ifdef	__GNU__
static int	bindresvport();
static bool_t	clntkudp_freeres();
struct mbuf	*mclgetx();
#else	__GNU__
bool_t		clntkudp_freeres();
#endif	__GNU__

enum clnt_stat	clntkudp_callit();
void		clntkudp_abort();
void		clntkudp_error();
void		clntkudp_destroy();

void		xdrmbuf_init();

zone_t rpc_cku_zone;

/*
 * Operations vector for UDP/IP based RPC
 */
static struct clnt_ops udp_ops = {
	clntkudp_callit,	/* do rpc call */
	clntkudp_abort,		/* abort call */
	clntkudp_error,		/* return error status */
	clntkudp_freeres,	/* free results */
	clntkudp_destroy	/* destroy rpc handle */
};

/*
 * Private data per rpc handle.  This structure is allocated by
 * clntkudp_create, and freed by cku_destroy.
 */
struct cku_private {
	u_int			 cku_flags;	/* see below */
	CLIENT			 cku_client;	/* client handle */
	int			 cku_retrys;	/* request retrys */
	struct socket		*cku_sock;	/* open udp socket */
	struct sockaddr_in	 cku_addr;	/* remote address */
	struct rpc_err		 cku_err;	/* error status */
	XDR			 cku_outxdr;	/* xdr routine for output */
	XDR			 cku_inxdr;	/* xdr routine for input */
	u_int			 cku_outpos;	/* position of in output mbuf */
	char			*cku_outbuf;	/* output buffer */
	char			*cku_inbuf;	/* input buffer */
	struct mbuf		*cku_inmbuf;	/* input mbuf */
	struct ucred		*cku_cred;	/* credentials */
};

struct {
	int	rccalls;
	int	rcbadcalls;
	int	rcretrans;
	int	rcbadxids;
	int	rctimeouts;
	int	rcwaits;
	int	rcnewcreds;
} rcstat;


#define ptoh(p)		(&((p)->cku_client))
#define htop(h)		((struct cku_private *)((h)->cl_private))

/* cku_flags */
#define CKU_TIMEDOUT	0x001
#define CKU_BUSY	0x002
#define CKU_WANTED	0x004
#define CKU_BUFBUSY	0x008
#define CKU_BUFWANTED	0x010

/* Times to retry */
#define RECVTRIES	2
#define SNDTRIES	4

int	clntkudpxid;		/* transaction id used by all clients */

static
noop()
{
}

static
buffree(p)
	struct cku_private *p;
{
#if	0
	XPR(XPR_FS, ("buffree clearing CKU_BUFBUSY: thread = 0x%x p = 0x%x\n",
		     current_thread(), p));
#endif	0
	p->cku_flags &= ~CKU_BUFBUSY;
	if (p->cku_flags & CKU_BUFWANTED) {
		p->cku_flags &= ~CKU_BUFWANTED;
		wakeup((caddr_t)&p->cku_outbuf);
	}
}

/*
 * Create an rpc handle for a udp rpc connection.
 * Allocates space for the handle structure and the private data, and
 * opens a socket.  Note sockets and handles are one to one.
 */
CLIENT *
clntkudp_create(addr, pgm, vers, retrys, cred)
	struct sockaddr_in *addr;
	u_long pgm;
	u_long vers;
	int retrys;
	struct ucred *cred;
{
	register CLIENT *h;
	register struct cku_private *p;
	int error = 0;
	struct rpc_msg call_msg;
	struct mbuf *m, *mclgetx();
	extern int nfs_portmon;

#ifdef	RPCDEBUG
	rpc_debug(4, "clntkudp_create(%X, %d, %d, %d\n",
	    addr->sin_addr.s_addr, pgm, vers, retrys);
#endif
	ZALLOC(rpc_cku_zone, p, struct cku_private *);
	bzero((caddr_t)p, sizeof (*p));
	h = ptoh(p);

	if (!clntkudpxid) {
		clntkudpxid = time.tv_usec;
	}

	/* handle */
	h->cl_ops = &udp_ops;
	h->cl_private = (caddr_t) p;
	h->cl_auth = authkern_create();

	/* call message, just used to pre-serialize below */
	call_msg.rm_xid = 0;
	call_msg.rm_direction = CALL;
	call_msg.rm_call.cb_rpcvers = RPC_MSG_VERSION;
	call_msg.rm_call.cb_prog = pgm;
	call_msg.rm_call.cb_vers = vers;

	/* private */
	clntkudp_init(h, addr, retrys, cred);

	p->cku_outbuf = (char *)udpmsgbuf_alloc();
	m = mclgetx(noop, 0, p->cku_outbuf, UDPMSGSIZE, M_DONTWAIT);
	if (m == NULL)
		goto bad;
	xdrmbuf_init(&p->cku_outxdr, m, XDR_ENCODE);

	/* pre-serialize call message header */
	if (! xdr_callhdr(&(p->cku_outxdr), &call_msg)) {
		printf("clntkudp_create - Fatal header serialization error.");
		(void) m_freem(m);
		goto bad;
	}
	p->cku_outpos = XDR_GETPOS(&(p->cku_outxdr));
	(void) m_free(m);

	/* open udp socket */
	error = socreate(AF_INET, &p->cku_sock, SOCK_DGRAM, IPPROTO_UDP);
	if (error) {
		printf("clntkudp_create: socket creation problem, %d", error);
		goto bad;
	}
	if (error = bindresvport(p->cku_sock)) {
		printf("clntkudp_create: socket bind problem, %d", error);
		goto bad;
	}
	return (h);

bad:
	udpmsgbuf_free(p->cku_outbuf);
	ZFREE(rpc_cku_zone, p);
#ifdef	RPCDEBUG
	rpc_debug(4, "create failed\n");
#endif
	return ((CLIENT *)NULL);
}

clntkudp_init(h, addr, retrys, cred)
	CLIENT *h;
	struct sockaddr_in *addr;
	int retrys;
	struct ucred *cred;
{
	struct cku_private *p = htop(h);

	p->cku_retrys = retrys;
	p->cku_addr = *addr;
	p->cku_cred = cred;
    /* 
     * deleted the line that set flags = 0...  it was causing client buffers
     * that were already busy to be reused before their time
     */
}

/*
 * Time out back off function. tim is in hz
 */
#define MAXTIMO	(60 * hz)
#define backoff(tim)	((((tim) << 1) > MAXTIMO) ? MAXTIMO : ((tim) << 1))

/*
 * Call remote procedure.
 * Most of the work of rpc is done here.  We serialize what is left
 * of the header (some was pre-serialized in the handle), serialize
 * the arguments, and send it off.  We wait for a reply or a time out.
 * Timeout causes an immediate return, other packet problems may cause
 * a retry on the receive.  When a good packet is received we deserialize
 * it, and check verification.  A bad reply code will cause one retry
 * with full (longhand) credentials.
 */
enum clnt_stat 
clntkudp_callit(h, procnum, xdr_args, argsp, xdr_results, resultsp, wait)
	register CLIENT	*h;
	u_long		procnum;
	xdrproc_t	xdr_args;
	caddr_t		argsp;
	xdrproc_t	xdr_results;
	caddr_t		resultsp;
	struct timeval	wait;
{
	register struct cku_private *p = htop(h);
	register XDR	   	   *xdrs;
	register struct socket	   *so = p->cku_sock;
	int			   rtries;
	int			   stries = p->cku_retrys;
	struct sockaddr_in	   from;
	struct rpc_msg		   reply_msg;
	int			   s;
	struct ucred		   *tmpcred;
	struct mbuf		   *m;
	int timohz;
	u_long xid;

#ifdef	RPCDEBUG
	rpc_debug(4, "cku_callit\n");
#endif
	rcstat.rccalls++;

	while (p->cku_flags & CKU_BUSY) {
		rcstat.rcwaits++;
		p->cku_flags |= CKU_WANTED;
		(void) sleep((caddr_t)h, PZERO-2);
	}
	p->cku_flags |= CKU_BUSY;

	/*
	 * Set credentials into the u structure
	 */
	tmpcred = u.u_cred;
	u.u_cred = p->cku_cred;

	xid = clntkudpxid++;

	/*
	 * This is dumb but easy: keep the time out in units of hz
	 * so it is easy to call timeout and modify the value.
	 */
	timohz = wait.tv_sec * hz + (wait.tv_usec * hz) / 1000000;

call_again:

	/*
	 * Wait til buffer gets freed then make a type 2 mbuf point at it
	 * The buffree routine clears CKU_BUFBUSY and does a wakeup when
	 * the mbuf gets freed.
	 */
	s = splimp();
	while (p->cku_flags & CKU_BUFBUSY) {
#if	0
	XPR(XPR_FS, ("CKU_BUFWANTED: thread = 0x%x p = 0x%x\n",
		     current_thread(), p));
#endif	0
		p->cku_flags |= CKU_BUFWANTED;
		/*
		 * This is a kludge to avoid deadlock in the case of a
		 * loop-back call.  The client can block wainting for
		 * the server to free the mbuf while the server is blocked
		 * waiting for the client to free the reply mbuf.  Avoid this
		 * by flushing the input queue every once in a while while
		 * we are waiting.
		 */
		timeout(wakeup, (caddr_t)&p->cku_outbuf, hz);
		(void) sleep((caddr_t)&p->cku_outbuf, PZERO-3);
		sbflush(&so->so_rcv);
	}
#if	0
	XPR(XPR_FS, ("CKU_BUFBUSY: set: thread = 0x%x p = 0x%x\n",
		     current_thread(), p));
#endif	0
	p->cku_flags |= CKU_BUFBUSY;
	(void) splx(s);
	m = mclgetx(buffree, (int)p, p->cku_outbuf, UDPMSGSIZE, M_WAIT);
	if (m == NULL) {
		p->cku_err.re_status = RPC_SYSTEMERROR;
		p->cku_err.re_errno = ENOBUFS;
		buffree(p);
		goto done;
	}

	/*
	 * The transaction id is the first thing in the
	 * preserialized output buffer.
	 */
	(*(u_long *)(p->cku_outbuf)) = xid;

	xdrmbuf_init(&p->cku_outxdr, m, XDR_ENCODE);
	xdrs = &p->cku_outxdr;
	XDR_SETPOS(xdrs, p->cku_outpos);

	/*
	 * Serialize dynamic stuff into the output buffer.
	 */
	if ((! XDR_PUTLONG(xdrs, (long *)&procnum)) ||
	    (! AUTH_MARSHALL(h->cl_auth, xdrs)) ||
	    (! (*xdr_args)(xdrs, argsp))) {
		p->cku_err.re_status = RPC_CANTENCODEARGS;
		p->cku_err.re_errno = EIO;
		(void) m_freem(m);
		goto done;
	}

	if (m->m_next == 0) {		/* XXX */
		m->m_len = XDR_GETPOS(&(p->cku_outxdr));
	}
	if (p->cku_err.re_errno =
	    ku_sendto_mbuf(so, m, &p->cku_addr)) {
		p->cku_err.re_status = RPC_CANTSEND;
		p->cku_err.re_errno = EIO;
		goto done;
	}

	reply_msg.acpted_rply.ar_verf = _null_auth;
	reply_msg.acpted_rply.ar_results.where = resultsp;
	reply_msg.acpted_rply.ar_results.proc = xdr_results;

	for (rtries = RECVTRIES; rtries; rtries--) {
		s = splnet();
		while (so->so_rcv.sb_cc == 0) {
			/*
			 * Set timeout then wait for input or timeout
			 */
#ifdef	RPCDEBUG
			rpc_debug(3, "callit: waiting %d\n", timohz);
#endif
			timeout(ckuwakeup, (caddr_t)p, timohz);
			so->so_rcv.sb_flags |= SB_WAIT;
			(void) sleep((caddr_t)&so->so_rcv.sb_cc, PRIBIO);

			untimeout(ckuwakeup, (caddr_t)p);
			if (p->cku_flags & CKU_TIMEDOUT) {
				p->cku_flags &= ~CKU_TIMEDOUT;
				(void) splx(s);
				p->cku_err.re_status = RPC_TIMEDOUT;
				p->cku_err.re_errno = ETIMEDOUT;
				rcstat.rctimeouts++;
				goto done;
			}
		}

		if (so->so_error) {
			so->so_error = 0;
			(void) splx(s);
			continue;
		}

		p->cku_inmbuf = ku_recvfrom(so, &from);
		(void) splx(s);
		if (p->cku_inmbuf == NULL) {
			continue;
		}
		p->cku_inbuf = mtod(p->cku_inmbuf, char *);

		if (p->cku_inmbuf->m_len < sizeof(u_long)) {
			m_freem(p->cku_inmbuf);
			continue;
		}
		/*
		 * If reply transaction id matches id sent
		 * we have a good packet.
		 */
		if (*((u_long *)(p->cku_inbuf))
		    != *((u_long *)(p->cku_outbuf))) {
			rcstat.rcbadxids++;
			m_freem(p->cku_inmbuf);
			continue;
		}
		/*
		 * Flush the rest of the stuff on the input queue
		 * for the socket.
		 */
		s = splnet();
		sbflush(&so->so_rcv);
		(void) splx(s);
		break;
	} 

	if (rtries == 0) {
		p->cku_err.re_status = RPC_CANTRECV;
		goto done;
	}

	/*
	 * Process reply
	 */

	xdrs = &(p->cku_inxdr);
	xdrmbuf_init(xdrs, p->cku_inmbuf, XDR_DECODE);

	/*
	 * Decode and validate the response.
	 */
	if (xdr_replymsg(xdrs, &reply_msg)) {
		_seterr_reply(&reply_msg, &(p->cku_err));

		if (p->cku_err.re_status == RPC_SUCCESS) {
			/*
			 * Reply is good, check auth.
			 */
			if (! AUTH_VALIDATE(h->cl_auth,
			    &reply_msg.acpted_rply.ar_verf)) {
				p->cku_err.re_status = RPC_AUTHERROR;
				p->cku_err.re_why = AUTH_INVALIDRESP;
			}
			if (reply_msg.acpted_rply.ar_verf.oa_base != NULL) {
				/* free auth handle */
				xdrs->x_op = XDR_FREE;
				(void)xdr_opaque_auth(xdrs,
				    &(reply_msg.acpted_rply.ar_verf));
			} 
		}
	} else {
		p->cku_err.re_status = RPC_CANTDECODERES;
	}
	m_freem(p->cku_inmbuf);

#ifdef	RPCDEBUG
	rpc_debug(4, "cku_callit done\n");
#endif
done:
	if ( (p->cku_err.re_status != RPC_SUCCESS) &&
	     (p->cku_err.re_status != RPC_CANTENCODEARGS) &&
	     (--stries > 0) ) {
		rcstat.rcretrans++;
		timohz = backoff(timohz);
		if (p->cku_err.re_status == RPC_SYSTEMERROR ||
		    p->cku_err.re_status == RPC_CANTSEND) {
			/*
			 * Errors due to lack o resources, wait a bit
			 * and try again.
			 */
			(void) sleep((caddr_t)&lbolt, PZERO-4);
		}
		goto call_again;
	}
	u.u_cred = tmpcred;
	p->cku_flags &= ~CKU_BUSY;
	if (p->cku_flags & CKU_WANTED) {
		p->cku_flags &= ~CKU_WANTED;
		wakeup((caddr_t)h);
	}
	if (p->cku_err.re_status != RPC_SUCCESS) {
		rcstat.rcbadcalls++;
	}
	return (p->cku_err.re_status);
}

/*
 * Wake up client waiting for a reply.
 */
ckuwakeup(p)
	register struct cku_private *p;
{

#ifdef	RPCDEBUG
	rpc_debug(4, "cku_timeout\n");
#endif
	p->cku_flags |= CKU_TIMEDOUT;
	sbwakeup(&p->cku_sock->so_rcv);
}

/*
 * Return error info on this handle.
 */
void
clntkudp_error(h, err)
	CLIENT *h;
	struct rpc_err *err;
{
	register struct cku_private *p = htop(h);

	*err = p->cku_err;
}

static bool_t
clntkudp_freeres(cl, xdr_res, res_ptr)
	CLIENT *cl;
	xdrproc_t xdr_res;
	caddr_t res_ptr;
{
	register struct cku_private *p = (struct cku_private *)cl->cl_private;
	register XDR *xdrs = &(p->cku_outxdr);

	xdrs->x_op = XDR_FREE;
	return ((*xdr_res)(xdrs, res_ptr));
}

void 
clntkudp_abort()
{
}

/*
 * Destroy rpc handle.
 * Frees the space used for output buffer, private data, and handle
 * structure, and closes the socket for this handle.
 */
void
clntkudp_destroy(h)
	CLIENT *h;
{
	register struct cku_private *p = htop(h);

#ifdef	RPCDEBUG
	rpc_debug(4, "cku_destroy %x\n", h);
#endif
	(void) soclose(p->cku_sock);
	udpmsgbuf_free(p->cku_outbuf);
	ZFREE(rpc_cku_zone, p);
}

/*
 * try to bind to a reserved port
 */
static
bindresvport(so)
	struct socket *so;
{
	struct sockaddr_in *sin;
	struct mbuf *m;
	u_short i;
	int error;
	uid_t saveuid;

#define MAX_PRIV	(IPPORT_RESERVED-1)
#define MIN_PRIV	(IPPORT_RESERVED/2)

	m = m_get(M_WAIT, MT_SONAME);
	if (m == NULL) {
		printf("bindresvport: couldn't alloc mbuf");
		return(ENOBUFS);
	}

	sin = mtod(m, struct sockaddr_in *);
	sin->sin_family = AF_INET;
	sin->sin_addr.s_addr = INADDR_ANY;
	m->m_len = sizeof(struct sockaddr_in);

	saveuid = u.u_uid;
	u.u_uid = 0;
	error = EADDRINUSE;
	for (i = MAX_PRIV; error == EADDRINUSE && i >= MIN_PRIV; i--) {
		sin->sin_port = htons(i);
		error = sobind(so, m);
	}
	u.u_uid = saveuid;

	(void) m_freem(m);
	return (error);
}

clnt_kudp_zone_init()
{
	rpc_cku_zone		= zinit(sizeof(struct cku_private),
					1024*1024, 0, FALSE, "rpc cku");
}
