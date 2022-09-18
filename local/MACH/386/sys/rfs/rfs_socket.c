/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	rfs_socket.c,v $
 * Revision 2.9  89/04/24  13:23:46  gm0w
 * 	Restored lost MACH_VFS change for ni_nbpp().
 * 	[89/04/24            gm0w]
 * 
 * Revision 2.8  89/04/22  15:27:09  gm0w
 * 	Removed MACH_VFS changes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.7  89/03/15  15:14:32  gm0w
 * 	changed include sys/rfs.h to rfs/rfs/h
 * 
 * Revision 2.6  89/02/25  14:45:07  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/02/09  04:32:31  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.4  89/01/18  00:39:53  jsb
 * 	Vnode support.
 * 	[89/01/16            jsb]
 * 
 * Revision 2.3  88/08/24  01:25:12  mwyoung
 * 	Removed RFS conditional entirely... this file isn't built unless
 * 	CMUCS_RFS is specified.
 * 	[88/08/23            mwyoung]
 * 	
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 *
 * 11-Feb-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted use of timeout(), untimeout(), sbwakeup() functions.
 *	Eliminated rfsShutdown,	which was never being called. 
 *
 * 17-Apr-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Commented out a rfs_printf in rfsEstablish to prevent compiler
 *	schain-botch.
 *
 * 09-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed some timeout miscalculations that were causing operations
 *	to be abandoned too quickly.
 *	[ V5.1(F6) ]
 *
 * 05-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed rfsSend() and rfsReceive() to use new rfsUIOSend() and
 *	rfsUIOReceive() routines that perform socket I/O with
 *	appropriate timeouts and signal handling.  This should fix
 *	problems with connections hanging non-interrupably.
 *	[ V5.1(F5) ]
 *
 * 05-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Updated rfsReceive() to permit new RFST_LREPLY response from
 *	server which provides the trailing part of the original
 *	pathname for which namei() processing should continue locally.
 *	[ V5.1(F2) ]
 *
 * 13-Dec-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created during reorganization for new RFS name.
 *
 */

/*	rfs_socket.c	CMU	85/12/13	*/

#include <mach_vfs.h>

/*
 *  Remote file system - socket interface module
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/dir.h>
#include <sys/file.h>
#include <sys/inode.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <rfs/rfs.h>

#include <net/route.h>
#include <netinet/in_pcb.h>



/*
 *  rfsEstablish - establish TCP connection to port on remote host
 *
 *  rcbp   = remote control block for connection
 *  fcon   = IP address of remote host
 *  fport  = remot port number of connection
 *  lport  = local port number for connection
 *  active = active/passive open flag
 *  retry  = times to attempt to connect if refused before giving up
 *
 *  Establishes a connection between the indicated local port number and the
 *  specified port on the remote host.  The active flag indicates whether or
 *  not an active or passive socket should be created. When a connection
 *  attempt fails because it is refused at the remote end (i.e. there was no
 *  corresponding remot port), it will be retried until the requested number of
 *  attempts have been made.  This is to insure that new connections may be
 *  established to port numbers sent on already established connections because
 *  it may take time on each end to initialize the new ports.
 *
 *  The socket and local port fields of the remote control block are filled in
 *  from the established connection.
 *
 *  Return: 0 or an error number as appropriate.
 */

rfsEstablish(rcbp, fcon, fport, lport, active, retry)
    register struct rfsConnectionBlock *rcbp;
    struct in_addr fcon;
    u_short fport;
    u_short lport;
    int active;
    int retry;
{
    struct socket *so = 0;
    int error = 0;
    label_t tsave;

    rfs_printf4(RFSD_P_TRACEIN, "<Estb fa=%X fp=%x lp=%x\n", fcon, fport, lport);

    bcopy((caddr_t)&u.u_qsave, (caddr_t)&tsave, sizeof(label_t));
    for (;;)
    {
	struct mbuf *m;

	if (error = socreate(AF_INET, &so, SOCK_STREAM, 0))
	    goto out;
	m = rfsSocketName((u_long)0, lport);
	if (m == NULL)
	{
	    error = ENOBUFS;
	    goto oops;
	}
	so->so_options |= SO_REUSEADDR | SO_CANTSIG ;
	error = sobind(so, m);
	m_freem(m);
	if (error)
	    goto oops;
	if (setjmp(&u.u_qsave) != 0)
	{
	    untimeout(rfsTimeOut, (caddr_t) rcbp);
	    error = EINTR;
	    goto oops;
	}
	if (active)
	{
	    m = rfsSocketName(fcon.s_addr, fport);
	    if (m == NULL)
	    {
		error = ENOBUFS;
		goto oops;
	    }
	    error = soconnect(so, m);
	    m_freem(m);
	    if (error)
		goto oops;
	}
	else
	    error = solisten(so, 0);
	if (error == 0)
	{
	    int s;

	    rcbp->rcb_so = so;
	    s = splnet();
	    if ((so->so_state & SS_ISCONNECTED) == 0 &&
		(so->so_proto->pr_flags & PR_CONNREQUIRED))
	    {
		if (so->so_options&SO_ACCEPTCONN)
		{
		    rcbp->rcb_flags |= RFSF_ACCEPT;
		}
		else
		{
		    while ((so->so_state & SS_ISCONNECTING) && so->so_error == 0)
		    {
			timeout(rfsTimeOut, (caddr_t) rcbp, 15*hz);
			sleep((caddr_t)&so->so_timeo, PZERO+1);
			untimeout(rfsTimeOut, (caddr_t) rcbp);
			if (rcbp->rcb_flags&RFSF_TOUT)
			{
			    rcbp->rcb_flags &= ~RFSF_TOUT;
			    so->so_error = ETIMEDOUT;
			}
		    }
		}
		error = so->so_error;
		so->so_error = 0;
	    }
	    splx(s);
	}

	switch (error)
	{
	    case 0:
		rcbp->rcb_lport = ntohs(sotoinpcb(so)->inp_lport);
		goto out;

	    case ECONNREFUSED:
		if (--retry <= 0)
		    goto oops;
		if (soclose(so))
		    ;
		so = 0;
		break;

	    default:
		goto oops;
	}
    }

oops:
    if (so)
	(void) soclose(so);
    rcbp->rcb_so = NULL;
out:
    bcopy((caddr_t)&tsave, (caddr_t)&u.u_qsave, sizeof(label_t));
    rfs_printf2(RFSD_P_TRACEOUT, ">Estb %d\n", error);
    return(error);
}



/*
 *  rfsAccept - accept a returned connection from forked server
 *
 *  rcbp = remote connection block
 *
 *  Block waiting to complete a connection which has not yet been accepted.
 *  These connections occur as the result of a FORK operation which requests
 *  the remote server to replicate its state (presumably in a new remote
 *  process) and create a new connection back to us for use by the new local
 *  process.  At the time of the FORK, the newly created socket is simply
 *  created in the "listen" state without waiting for the remote server to
 *  complete the reconnect operation.  Instead, we do that here when the new
 *  connection is used for the first time (and when the new connection has most
 *  probably already been completed).
 */

rfsAccept(rcbp)
    register struct rfsConnectionBlock *rcbp;
{
    register struct socket *so = rcbp->rcb_so;
    int error;
    int s;

    rfs_printf2(RFSD_P_TRACEIN, ">Acpt %x\n", rcbp);
    s = splnet();
    if ((so->so_state & SS_ISCONNECTED) == 0 &&
	(so->so_proto->pr_flags & PR_CONNREQUIRED))
    {
	if (so->so_options&SO_ACCEPTCONN)
	{
	    while (so->so_qlen == 0 && so->so_error == 0)
	    {
		label_t tsave;

		if (so->so_state & SS_CANTRCVMORE)
		{
		    so->so_error = ECONNABORTED;
		    break;
		}
		bcopy((caddr_t)&u.u_qsave, (caddr_t)&tsave, sizeof(label_t));
		timeout(rfsTimeOut, (caddr_t) rcbp, 15*hz);
		if (setjmp(&u.u_qsave) != 0)
		    so->so_error = EINTR;
		else
		{
		    sleep((caddr_t)&so->so_timeo, PZERO+1);
		    if (rcbp->rcb_flags&RFSF_TOUT)
		    {
			rcbp->rcb_flags &= ~RFSF_TOUT;
			so->so_error = ETIMEDOUT;
		    }
		}
		untimeout(rfsTimeOut, (caddr_t) rcbp);
		bcopy((caddr_t)&tsave, (caddr_t)&u.u_qsave, sizeof(label_t));
	    }
	    if (so->so_error == 0)
	    {
		struct mbuf *m;
		struct socket *nso = so->so_q;

		if (soqremque(nso, 1) == 0)
		    panic("rfsEstablish accept");
		m = m_get(M_WAIT, MT_SONAME);
		(void)soaccept(nso, m);
		m_freem(m);
		if (soclose(so))
		    ;
		so = nso;
		rcbp->rcb_so = so;
	    }
	}
	else
	{
	    panic("rfsAccept1");
	}
	if ((error = so->so_error) == 0)
	    rcbp->rcb_flags &= ~RFSF_ACCEPT;
	so->so_error = 0;
    }
    else
	panic("rfsAccept2");
    splx(s);
    rfs_printf2(RFSD_P_TRACEOUT, ">Acpt %d\n", error);
    return(error);
}



/*
 *  rfsTimeOut - time out a connection attempt
 *
 *  rcbp = remote connection block
 *
 *  Set the "timed out" flag in the specified remote connection block and issue
 *  a wakeup to the process which was waiting for the connection to complete.
 *
 *  This routine is called at high IPL from the soft clock handler as the
 *  result of a timeout() call.
 */

int rfsTimeOut(_rcbp)
    caddr_t _rcbp;
{
    register struct rfsConnectionBlock *rcbp =
    	(struct rfsConnectionBlock *) _rcbp;
    rfs_printf2(RFSD_P_TRACEIN, ">Tout %x\n", rcbp);
    rcbp->rcb_flags |= RFSF_TOUT;
    wakeup((caddr_t)&rcbp->rcb_so->so_timeo);
    rfs_printf1(RFSD_P_TRACEOUT, ">Tout\n");
}



/*
 *  rfsSocketName - create a socket name in an mbuf
 *
 *  addr = IP address
 *  port = TCP port number
 *
 *  Return: an AF_INET socket name mbuf with the specified address or NULL if
 *  an mbuf acnnot be allocated.
 */
 
struct mbuf *
rfsSocketName(addr, port)
    u_long addr;
    u_short port;
{
    register struct mbuf *m;
    struct sockaddr_in *sin;

    m = m_get(M_WAIT, MT_SONAME);
    if (m != 0)
    {
	m->m_len = sizeof(struct sockaddr_in);
	sin = mtod(m, struct sockaddr_in *);
	sin->sin_family = AF_INET;
	sin->sin_port = htons(port);
	sin->sin_addr.s_addr = addr;
	bzero((caddr_t)sin->sin_zero, sizeof(sin->sin_zero));
    }
    return(m);
}



/*
 *  rfsUnEstablish - release a remote connection
 *
 *  rcbp = remote connection block
 *
 *  Close the socket (if any) and clear any error flags so that
 *  the remote connection block appears uninitialized.
 */

void
rfsUnEstablish(rcbp)
    register struct rfsConnectionBlock *rcbp;
{
    if (rcbp->rcb_so)
    {
	(void) soclose(rcbp->rcb_so);
	rcbp->rcb_so = NULL;
	rcbp->rcb_flags &= ~(RFSF_RETRY);
    }
}



/*
 *  rfsSend - send a message to remote host
 *
 *  rcbp  = control block for connection
 *  rmsgp = pointer to message to be sent
 *  len   = length of message to send
 *
 *  Send the supplied message with the specified length on the indicated
 *  connection.
 *
 *  If we are attempting to send something on a connection which has not yet
 *  been accepted, complete the acceptance before attempting to use it.
 *
 *  Return: 0 or an error number as appropriate.  
 */

rfsSend(rcbp, rmsgp, len)
    register struct rfsConnectionBlock *rcbp;
    struct rfsMsg *rmsgp;
    u_int len;
{
    struct uio uio;
    struct iovec iov;
    int error;

    rfs_printf3(RFSD_P_TRACEIN, "<Send t=%d[%d]\n", rmsgp->rmsg_A_code, len);
    if (rcbp->rcb_so == NULL)
    {
	error = ESHUTDOWN;
	goto out;
    }
    if (rcbp->rcb_flags&RFSF_ACCEPT)
    {
	error = rfsAccept(rcbp);
	if (error)
	    goto out;
    }
    iov.iov_base = (caddr_t)rmsgp;
    iov.iov_len = len;
    uio.uio_iov = &iov;
    uio.uio_iovcnt = 1;
    uio.uio_resid = len;
    uio.uio_segflg = UIO_SYSSPACE;

    error = rfsUIOSend(rcbp, &uio);
    if (error)
	rcbp->rcb_flags |= RFSF_RETRY;
out:
    rfs_printf2(RFSD_P_TRACEOUT, ">Send %d\n", error);
    return(error);
}



/*
 *  rfsSendString - send a counted string on a connection
 *
 *  rcbp = remote control block
 *  cp   = string to send
 *  len  = length of string
 *
 *  Send the specified number of bytes of the supplied string on the
 *  indicated connection.  If the pathname length is zero, no bytes
 *  need be sent.
 *
 *  Return: 0 or an error number as appropriate.  
 */

rfsSendString(rcbp, cp, len)
    register struct rfsConnectionBlock *rcbp;
    register char *cp;
    u_int len;
{
    struct uio uio;
    struct iovec iov;
    int error = 0;

    rfs_printf3(RFSD_P_TRACEIN, "<SndS \"%s\"[%d]\n", cp, len);
    if (len != 0)
    {
	uio.uio_segflg = UIO_SYSSPACE;
	iov.iov_base = cp;
	uio.uio_resid = iov.iov_len = len;
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;

	error = rfsUIOSend(rcbp, &uio);
	if (error)
	    rcbp->rcb_flags |= RFSF_RETRY;
    }
    rfs_printf2(RFSD_P_TRACEOUT, ">SndS %d\n", error);
    return (error);
}



/*
 *  rfsUIOSend - Send data on socket with timeout
 *
 *  rcbp = remote control block
 *  uiop = I/O descriptor
 *
 *  Send the specified number of bytes from the indicated area on the
 *  connection.  If the data is in user space, use a maximum timeout
 *  which is bounded by the size of the data being sent, otherwise use
 *  a fixed maximum.
 */

rfsUIOSend(rcbp, uiop)
    register struct rfsConnectionBlock *rcbp;
    struct uio *uiop;
{
    register struct proc *p = u.u_procp;
    int error;
    int mask;

    mask = p->p_sigmask;
    p->p_sigmask = -1;
    timeout(rfsSendOut, (caddr_t) rcbp,
	    (30+(uiop->uio_segflg==UIO_USERSPACE?(uiop->uio_resid>>16):0))*hz);
    error = sosend(rcbp->rcb_so, (struct mbuf *)0, uiop, 0, (struct mbuf *)0);
    untimeout(rfsSendOut, (caddr_t) rcbp);
    p->p_sigmask = mask;
    if (rcbp->rcb_flags&RFSF_TOUT)
    {
	rcbp->rcb_flags &= ~RFSF_TOUT;
	if (error == 0)
	    error = ETIMEDOUT;
    }
    return(error);
}



/*
 *  rfsSendOut - time out send operation
 *
 *  rcbp = remote connection block
 *
 *  Set the "timed out" flag in the specified remote connection block and the
 *  error field in the socket and issue a wakeup to the process which was
 *  waiting for the abort request to be confirmed.  I'm not sure this currently
 *  catches all the cases were a request can be blocked but we'll see.
 *
 *  This routine is called at high IPL from the soft clock handler as the
 *  result of a timeout() call.
 */

int rfsSendOut(_rcbp)
    caddr_t _rcbp;
{
    register struct rfsConnectionBlock *rcbp =
    	(struct rfsConnectionBlock *) _rcbp;
    register struct socket *so = rcbp->rcb_so;

    rfs_printf2(RFSD_P_TRACEIN, "<SendOut %x\n", rcbp);
    rcbp->rcb_flags |= RFSF_TOUT;
    so->so_error = ETIMEDOUT;
    sbwakeup(&so->so_snd);
    rfs_printf1(RFSD_P_TRACEOUT, ">SendOut\n");
}



/*
 *  rfsReceive - receive a message from remote connection
 *
 *  rcbp  = remote control block
 *  rmsgp = pointer to structure for reply
 *  len   = len of reply buffer
 *  type  = reply type expected
 *
 *  Wait for a reply to a previously sent message on the remote connection.
 *  The reply must be of the indicated type and the expected number of bytes
 *  long.  Signals are caught specially for the duration of the socket receive
 *  operation so that the protocol will not be interrupted at an inconvenient
 *  point without special action being taken.
 *
 *  The reply is received in two parts if it exceeds the standard header size.
 *  This is to allow a NOP message to be sent on the connection at any time so
 *  that it can be discarded and the reply awaited for anew.  If the reply were
 *  received as a whole with a trailer, the next message might end up appended
 *  to a NOP where it would be much harder to use.
 *
 *  The reply may also be an LREPLY message which rather than responding to the
 *  original request remotely returns instead a pathname which should be passed
 *  back to namei() to continue local processing.  This is used to force all
 *  references above the root to return to the calling system (and in
 *  particular allows remote "pwd" to behave properly).  The pseudo-error
 *  ELOCAL is used to unwind back to namei() without any further remote
 *  processing.  This type of reply is permitted only when the caller has set
 *  up the pathname buffer in the U area in advance to receive the name
 *  returned from the remote server.
 *
 *  Return: 0 or an error number as appropriate.
 *
 *  TODO:  Complete rewrite.  This routine is OUT OF CONTROL!
 */

rfsReceive(rcbp, rmsgp, len, type)
    register struct rfsConnectionBlock *rcbp;
    struct rfsMsg *rmsgp;
    u_int len;
    int type;
{
#if	MACH_VFS
    char *nbp = (char *)(*ni_nbpp(&u.u_nd));
#else	MACH_VFS
    struct buf *nbp = *ni_nbpp(&u.u_nd);
#endif	MACH_VFS
    struct uio uio;
    struct iovec iov;
    u_int olen;
    int error = 0;

    rfs_printf4(RFSD_P_TRACEIN, "<Recv t=%d[%d],nbp=%X\n", type, len,nbp);
    olen = len;
retry:
    iov.iov_base = (caddr_t)rmsgp;
    iov.iov_len = sizeof(rmsgp->rmsg_header);
    uio.uio_iov = &iov;
    uio.uio_iovcnt = 1;
    uio.uio_segflg = UIO_SYSSPACE;
trailer:
    uio.uio_resid = iov.iov_len;
    len -= iov.iov_len;
    while (uio.uio_resid)
    {
	error = rfsUIOReceive(rcbp, &uio);
	if (error)
	    break;
    }
    if (error)
    {
	rcbp->rcb_flags |= RFSF_RETRY;
	goto out;
    }
    else
    {
	if (rmsgp->rmsg_code == RFST_NOP)
	{
	    rfs_printf1(RFSD_PROTOCOL, "*Recv NOP\n");
	    len = olen;
	    goto retry;
	}
	else if (nbp && rmsgp->rmsg_code == RFST_LREPLY)
	{
	    if (rmsgp->rmsg_rval >= 0 && rmsgp->rmsg_rval <= (MAXPATHLEN-3))
	    {
#if	MACH_VFS
		iov.iov_base = nbp+3; /* plus "/.." prefix */
#else	MACH_VFS
		iov.iov_base = nbp->b_un.b_addr+3; /* plus "/.." prefix */
#endif	MACH_VFS
		iov.iov_len  = rmsgp->rmsg_rval;
		iov.iov_base[iov.iov_len] = 0;
		uio.uio_segflg = UIO_SYSSPACE;
		rfs_printf2(RFSD_PROTOCOL, "*Recv LREPLY [%d]\n",
			    rmsgp->rmsg_rval);
		/*
		 *  We won't get into this code if the name buffer was null on
		 *  entry but we also don't want to return here the second time
		 *  through the loop when we are reading the trailing pathname
		 *  so clear the buffer pointer before we begin pass two.
		 */
		nbp = 0;
		if (len=iov.iov_len)
		    goto trailer;
	    }
	    else
	    {
		rfs_printf3(RFSD_PROTOCOL, "*Recv LREPLY (%d:%d)\n",
			    rmsgp->rmsg_rval, MAXPATHLEN-3);
		error = EIO;
	    }
	}
	else if (len)
	{
	    iov.iov_len = len;
	    goto trailer;
	}
	if ((rmsgp->rmsg_code != RFST_REPLY && rmsgp->rmsg_code != RFST_LREPLY)
	    ||
	    rmsgp->rmsg_rcode != type)
	{
	    rfs_printf3(RFSD_PROTOCOL, "*Recv code=%d,rcode=%d\n",
		        rmsgp->rmsg_code, rmsgp->rmsg_rcode);
	    error = EIO;
	}
    }
    /*
     *  Arrange to continue the name lookup locally (with the trailing
     *  component that is about to be read from the connection).  This is only
     *  a simulated error so we set a state flag to prevent the connection from
     *  being closed down as would normally occur with any protocol errors.
     */
    if (error == 0 && rmsgp->rmsg_code == RFST_LREPLY)
    {
	rcbp->rcb_flags |= RFSF_LREPLY;
	error = ELOCAL;
    }
    /*
     *  If this request was terminated abnormally at the remote end (with the
     *  reception of the SIGURG signal there), then remember that we must also
     *  abort the request locally.  The remote server has the option of
     *  completing the request normally on receipt of the signal (so long as it
     *  is done promptly) and only when the EINTR error number is returned will
     *  the request be aborted.  If the reception of the signal remotely
     *  doesn't interrupt the system call which is currently in progress there,
     *  then the call similarly will not be interrupted locally.
     */
    if
    (
      error == 0 && (rcbp->rcb_flags&RFSF_ABORTING)
      && 
      rmsgp->rmsg_errno == EINTR 
    )
    {
	rcbp->rcb_flags |= RFSF_EINTR;
	error = EINTR;
    }
    else
	rcbp->rcb_flags &= ~RFSF_EINTR;
out:
    rfs_printf2(RFSD_P_TRACEOUT, ">Recv %d\n", error);
    return(error);
}



/*
 *  rfsUIOReceive - receive data from socket with abort
 *
 *  rcbp = remote control block
 *  uiop = I/O descriptor
 *
 *  Receive the specified number of data bytes from the connection into the
 *  indicated area.  If the data area is in user space, allow the operation to
 *  take a maximum time bounded by the length of the data to be received and
 *  prohibit any signals during this period (under the assumption that the
 *  operation is not normally interruptable).  If the data area is in system
 *  space, impose no upper bound on the receive time, however, if a signal is
 *  received, attempt to cancel the current operation by sending an ABORT
 *  message on the connection and allow the remote end to either complete the
 *  request (within a fixed amount of time) or abort as it chooses.  Also,
 *  if an EOF indication is received on the connection, translate this into
 *  a distingusihed error value.
 */

rfsUIOReceive(rcbp, uiop)
    register struct rfsConnectionBlock *rcbp;
    struct uio *uiop;
{
    int error;
    label_t lqsave;
    unsigned ucount;

    bcopy((caddr_t)&u.u_qsave, (caddr_t)&lqsave, sizeof(lqsave));
again:
    ucount = uiop->uio_resid;
    if (setjmp(&u.u_qsave) == 0)
    {
	register struct proc *p = u.u_procp;
	int mask;

	if (uiop->uio_segflg == UIO_USERSPACE)
	{
	    mask = p->p_sigmask;
	    p->p_sigmask = -1;
	    timeout(rfsAbortOut, (caddr_t) rcbp, (30+(int)(ucount>>16))*hz);
	}
	error = soreceive(rcbp->rcb_so, (struct mbuf **)0, uiop,
			  0, (struct mbuf **)0);
	if (uiop->uio_segflg == UIO_USERSPACE)
	{
	    p->p_sigmask = mask;
	    untimeout(rfsAbortOut, (caddr_t) rcbp);
	}
    }
    else
    {
	if ((error=rfsAbort(rcbp)) == 0)
	    goto again;
    }
    rfsUnAbort(rcbp);
    if (rcbp->rcb_flags&RFSF_TOUT)
    {
	rcbp->rcb_flags &= ~RFSF_TOUT;
	if (error == 0)
	    error = ETIMEDOUT;
    }
    if (ucount == uiop->uio_resid && error == 0)
	error = ECONNABORTED;
    bcopy((caddr_t)&lqsave, (caddr_t)&u.u_qsave, sizeof(lqsave));
    return(error);
}



/*
 *  rfsAbort - abort request on RFS connection
 *
 *  rcbp - remote connection block
 *
 *  Set the "aborting" flag in the connection block and send an ABORT message
 *  on the connection in "urgent" mode to cancel the pending request.  Set a
 *  timer to go off if a confirmation doesn't come back in a reasonable time.
 */

rfsAbort(rcbp)
    register struct rfsConnectionBlock *rcbp;
{
    struct rfsMsg rmsg;
    struct uio uio;
    struct iovec iov;
    int error = 0;

    rfs_printf2(RFSD_P_TRACEIN, "<Abort %X\n", rcbp);
    if ((rcbp->rcb_flags&RFSF_ABORTING) == 0)
    {
	iov.iov_base = (caddr_t)&rmsg;
	iov.iov_len = sizeof(rmsg.rmsg_header);
	uio.uio_iov = &iov;
	uio.uio_iovcnt = 1;
	uio.uio_resid = sizeof(rmsg.rmsg_header);
	uio.uio_segflg = UIO_SYSSPACE;
	rmsg.rmsg_Z_code = RFST_ABORT;
	rmsg.rmsg_Z_mbz  = 0;
	rmsg.rmsg_Z_s_param = 0;
	rmsg.rmsg_Z_l_param = 0;
	timeout(rfsAbortOut, (caddr_t) rcbp, 30*hz);
	rcbp->rcb_flags |= RFSF_ABORTING;
        error = sosend(rcbp->rcb_so, (struct mbuf *)0, &uio,
		       MSG_OOB, (struct mbuf *)0);
    }
    rfs_printf2(RFSD_P_TRACEOUT, ">Abort %d\n", error);
    return(error);
}



/*
 *  rfsAbortOut - abort out of a request from timeout
 *
 *  rcbp = remote connection block
 *
 *  Set the "timed out" flag in the specified remote connection block and the
 *  error field in the socket and issue a wakeup to the process which was
 *  waiting for the abort request to be confirmed.  I'm not sure this currently
 *  catches all the cases where a receive request can be blocked but we'll see.
 *
 *  This routine is called at high IPL from the soft clock handler as the
 *  result of a timeout() call.
 */

int rfsAbortOut(_rcbp)
    caddr_t _rcbp;
{
    register struct rfsConnectionBlock *rcbp =
    	(struct rfsConnectionBlock *) _rcbp;
    register struct socket *so = rcbp->rcb_so;

    rfs_printf2(RFSD_P_TRACEIN, ">AbOut %x\n", rcbp);
    rcbp->rcb_flags &= ~RFSF_ABORTING;
    rcbp->rcb_flags |= RFSF_TOUT;
    so->so_error = ETIMEDOUT;
    sbwakeup(&so->so_rcv);
    wakeup((caddr_t)&so->so_timeo);
    rfs_printf1(RFSD_P_TRACEOUT, ">AbOut\n");
}



/*
 *  rfsUnAbort - cancel an abort request on RFS connection
 *
 *  rcbp - remote connection block
 *
 *  If an abort was currently pending, cancel the timeout.
 */

void
rfsUnAbort(rcbp)
    register struct rfsConnectionBlock *rcbp;
{
    if (rcbp->rcb_flags&RFSF_ABORTING)
    {
        untimeout(rfsAbortOut, (caddr_t) rcbp);
        rcbp->rcb_flags &= ~RFSF_ABORTING;
    }
}

#ifdef	notdef
/*
 *  rfsShutdown - prevent any further sends on remote connection
 *
 *  rcbp = remote connection block
 *
 */

void
rfsShutdown(rcbp)
register struct rfsConnectionBlock *rcbp;
{
    (void) soshutdown(rcbp->rcb_so, 1);
}
#endif	notdef
