/*
 * HISTORY
 * $Log:	rfs_ticket.c,v $
 * Revision 2.5  91/11/05  18:28:16  mja
 * 	Perform all common and per-type ticketd request message
 * 	processing in ticketdGetTicket() but expect caller to print any
 * 	desired diagnostics.
 * 	[91/11/05  00:32:51  mja]
 * 
 * Revision 2.4  91/09/04  12:06:16  berman
 * 	Only print warnings about ticketd failures when the
 * 	cause of the failure is expired tickets.
 * 	[91/09/03  17:51:07  chs]
 * 
 * Revision 2.3  91/08/29  21:50:14  berman
 * 	Add trigger variable for new ticketd reply protocol.
 * 	[91/08/27  11:06:39  chs]
 * 
 * 	Add an error code to the ticketd protocol and uprintf 
 * 	error messages on apropriate kerberos errors
 * 	(mainly expired tickets).
 * 	[91/08/23  16:06:05  chs]
 * 
 * Revision 2.2  91/08/01  15:25:43  berman
 * 	Allow for ticketd requests that aren't replied to.
 * 	[91/07/27  17:15:46  chs]
 * 
 * 	Created.
 * 	[91/07/22  11:52:24  chs]
 * 
 */
/*
 *  Module for interacting with the ticketd.
 *
 *  (note:  this isn't really part of rfs, but it's intimately
 *   related in the current implementation, so it goes here anyway.)
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <rfs/rfs.h>
#include <rfs/ticketd.h>
#include <sys/inode.h>

char ticketd_socket_path[] = TICKETD_SOCKET_PATH;
struct inode *ticketd_ip = NULL;

int ticketd_error_code_in_reply = 1;

/*
 * ticketdSendOut - time out on sending to the ticketd
 */

ticketdSendOut(_so)
caddr_t _so;
{
    struct socket *so = (struct socket *)_so;

    so->so_error = ETIMEDOUT;
    sbwakeup(&so->so_snd);
}



/*
 * ticketdSend - send a request to the ticketd
 */

ticketdSend(so, cp, len)
struct socket *so;
caddr_t cp;
int len;
{
    int error = 0, mask;
    struct uio uio;
    struct iovec iov;
    struct proc *p = u.u_procp;

    iov.iov_base = cp;
    iov.iov_len = len;
    uio.uio_iov = &iov;
    uio.uio_iovcnt = 1;
    uio.uio_resid = len;
    uio.uio_segflg = UIO_SYSSPACE;

    mask = p->p_sigmask;
    p->p_sigmask = -1;

    timeout(ticketdSendOut, (caddr_t)so, 15*hz);
    error = sosend(so, (struct mbuf *)0, &uio, 0, (struct mbuf *)0);
    untimeout(ticketdSendOut, (caddr_t)so);

    p->p_sigmask = mask;

    return(error);
}



/*
 * ticketdReceiveOut - time out on receiving from the ticketd
 */

ticketdReceiveOut(_so)
caddr_t _so;
{
    struct socket *so = (struct socket *)_so;

    so->so_error = ETIMEDOUT;
    sbwakeup(&so->so_rcv);
}



/*
 * ticketdReceive - receive a reply from the ticketd
 */

ticketdReceive(so, cp, len)
struct socket *so;
caddr_t cp;
int len;
{
    int error = 0;
    struct uio uio;
    struct iovec iov;
    label_t lqsave;

    iov.iov_base = cp;
    iov.iov_len = len;
    uio.uio_iov = &iov;
    uio.uio_iovcnt = 1;
    uio.uio_resid = len;
    uio.uio_segflg = UIO_SYSSPACE;
    uio.uio_offset = 0;

    bcopy((caddr_t)&u.u_qsave, (caddr_t)&lqsave, sizeof(lqsave));

    if (setjmp(&u.u_qsave) == 0) {
	timeout(ticketdReceiveOut, (caddr_t)so, 15*hz);
	error = soreceive(so, (struct mbuf *)0, &uio, 0, (struct mbuf *)0);
    }
    else
	error = EINTR;

    untimeout(ticketdReceiveOut, (caddr_t)so);

    /* if we got no data back, the request has failed */
    if (uio.uio_offset == 0)
	error = ECONNABORTED;

    bcopy((caddr_t)&lqsave, (caddr_t)&u.u_qsave, sizeof(lqsave));
    return(error);
}



/*
 *  ticketdGetTicket - make a request of the ticketd
 *
 *  Send the request packet in req to the ticketd and receive the reply.
 *
 *  Return:  0 or an error number as appropriate.
 *  N.B.  The reply structure must be kfree()'d by the caller.
 */

ticketdGetTicket(req, replyp, errorp)
union ticketd_req_un *req;
struct ticketd_reply **replyp;
int *errorp;
{
    int error = EIO;
    int reqlen;
    struct ticketd_reply *reply = NULL;
    struct socket *so = NULL, *so2 = NULL;
    label_t lqsave;
    char *path;
    register struct rfsWho *rwp;

    *errorp = 0;
    if (replyp)
	*replyp = NULL;

    /*
     *  XXX  The ticket file is currently an RFS specific data structure
     *  although it shouldn't be...
     */
    rwp = rfsCurrentProcessEntry->rpe_rwp;
    if (rwp == NULL || rwp->rw_tktfile[0] == 0) {
	error = ENOENT;
	*errorp = 76;	/* NO_TKT_FIL */
	goto fail;
    }
    if (rwp->rw_flags & RFSWHO_BADTKTFILE) {
	error = ENOENT;
	*errorp = rwp->rw_badcode;
	goto fail;
    }

    if (! ticketd_ip) {
	error = ENOTCONN;
	goto fail;
    }

    if (error = socreate(AF_UNIX, &so, SOCK_STREAM, 0))
	goto fail;

    bcopy((caddr_t)&u.u_qsave, (caddr_t)&lqsave, sizeof(lqsave));

    if (setjmp(&u.u_qsave) != 0) {
	error = EINTR;
	goto fail;
    }

    /* this code stolen from bsd/uipc_usrreq.c */
    so2 = ticketd_ip->i_socket;
    if (so2 == 0 || (so2->so_options&SO_ACCEPTCONN) == 0
	|| (so2 = sonewconn(so2)) == 0) {
	error = ECONNREFUSED;
	goto fail;
    }
    error = unp_connect2(so, so2);

    bcopy((caddr_t)&lqsave, (caddr_t)&u.u_qsave, sizeof(lqsave));

    if (error)
	goto fail;

    /*
     *  Initialize common fields of the request header.
     */
    req->generic.header.uid = u.u_uid;
    switch (req->generic.header.type) {
	case TICKETD_REQ_DESTTKT:
	    path = &req->desttkt.path[0];
	    req->desttkt.pathlen = rwp->rw_ltktfile;
	    reqlen = sizeof(struct ticketd_req_desttkt);
	    break;
	case TICKETD_REQ_GENERIC:
	    path = &req->generic.path[0];
	    req->generic.pathlen = rwp->rw_ltktfile;
	    reqlen = sizeof(struct ticketd_req_generic);
	    break;
	case TICKETD_REQ_RFS:
	    path = &req->rfs.path[0];
	    req->rfs.pathlen = rwp->rw_ltktfile;
	    reqlen = sizeof(struct ticketd_req_rfs);
	    break;
	default:
	    panic("ticketdGetTicket");
	    break;
    }
    bcopy(rwp->rw_tktfile, path, rwp->rw_ltktfile);
    reqlen += rwp->rw_ltktfile;

    error = ticketdSend(so, (caddr_t)req, reqlen);
    if (error)
	goto fail;

    if (replyp != 0) {
	error = ticketdReceive(so, (caddr_t)errorp, sizeof(*errorp));
	if (error)
	    goto fail;

	switch (*errorp) {
	  case 0:	/* KSUCCESS */
	    break;
	  case 26:	/* MK_AP_TGTEXP */
	  case 76:	/* NO_TKT_FIL */
	    rwp->rw_badcode = *errorp;
    	    rwp->rw_flags |= RFSWHO_BADTKTFILE;
	    /* fall through */
	  case 32:	/* RD_AP_EXP */
	    /* TGT is still okay so this one isn't permanent */
	  default:
	    error = ECONNABORTED;
	    goto fail;
	}

	reply = (struct ticketd_reply *)kalloc(sizeof(struct ticketd_reply));
	if (reply == NULL) {
	    error = ENOMEM;
	    goto fail;
	}
	    
	bzero(reply, sizeof(struct ticketd_reply));

	error = ticketdReceive(so, (caddr_t)reply, sizeof(struct ticketd_reply));

	if (error)
	    goto fail;
	*replyp = reply;
    }

    (void) soclose(so);

    return 0;

  fail:
    if (so)
	(void) soclose(so);
    if (reply)
	kfree(reply, sizeof (struct ticketd_reply));

    return (error);
}
