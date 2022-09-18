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
 * $Log:	uipc_socket.c,v $
 * Revision 2.9  89/05/20  11:16:08  mrt
 * 	For now, in sosend take MIN of u_resid and space before chosing
 * 	a CLUSTER.  The problem is that under WIERD circumstances the
 * 	hiwat of uipc_domain sockets clamps to 1, though there the
 * 	u_resid is >> 1.  Thus we are forced into a CLUSTER that contains
 * 	one byte.  (NOTE: the changes to the sbcompress code can handle
 * 	this now, but ...)
 * 	[89/05/19            rvb]
 * 
 * Revision 2.8  89/03/09  19:34:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/26  11:30:52  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/09  04:35:55  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  88/12/19  02:34:48  mwyoung
 * 	Removed old MACH conditionals.
 * 	[88/12/13            mwyoung]
 * 
 * Revision 2.4  88/10/11  12:59:27  rpd
 * 	Aggressively use CLBYTES mbufs when copying data in from use, to
 * 	avoid long mbuf chains.
 * 	[88/09/30            rvb]
 * 
 * 09-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS: Added SO_USEPRIV option from ECE to sosetopt() and
 *	sogetopt() cases.
 *	[ V5.1(XF23) ]
 *
 * 28-Jan-88  Daniel Julin (dpj) at Carnegie-Mellon University
 *	MACH_NP: do not send a SIGPIPE in sosend when SO_CANTSIG is on.
 *
 * 26-Oct-87  David Black (dlb) at Carnegie-Mellon University
 *	MACH_EXCEPTION: convert SIGPIPE to new exception technology.
 *
 *  1-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 29-Jun-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  give "network" group privileged socket access
 *	(temporarily hacked to "know" group #38).
 *	[ V5.1(XF12) ]
 *
 * 31-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_INVOKE: added support for split invoke call.
 *
 * 28-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Added VMTP.
 *
 * 15-May-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	MULTIBIND:  added support for SO_MULTIBIND option in sosetopts().
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:	added support for SO_GREEDY option in sosetopts().
 */

#include <vice.h>
#include <multibind.h>
#include <mach_vmtp.h>
#include <mach_np.h>

#define VMTP_INVOKE	1

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)uipc_socket.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/inode.h>
#include <sys/buf.h>
#include <sys/mbuf.h>
#include <sys/un.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <net/route.h>
#include <netinet/in.h>
#include <net/if.h>
#if	MACH_VMTP
#include <netinet/vmtp_so.h>
#endif	MACH_VMTP

#include <mach/exception.h>
#include <builtin/ux_exception.h>
#include <kern/thread.h>

#ifndef	NETWORK_GROUP
#define NETWORK_GROUP	38
#endif	NETWORK_GROUP

/*
 * Socket operation routines.
 * These routines are called by the routines in
 * sys_socket.c or from a system process, and
 * implement the semantics of socket operations by
 * switching out to the protocol specific routines.
 *
 * TODO:
 *	test socketpair
 *	clean up async
 *	out-of-band is a kludge
 */
#if	MACH_VMTP

/*
 *
 * The msg must consist of only one mbuf - the rest is dropped.
 * The segment to be sent is passed as the address in the process address
 * space but the response segment will be an mbuf chain.
 * On return from usrreq the first mbuf in the chain is assumed to
 * contain the mcb and the rest is the segment data.
 */
#if	VMTP_INVOKE
soinvoke(so, func, msg, sendseg, a_respseg)
	int	func;
#else	VMTP_INVOKE
soinvoke(so, msg, sendseg, a_respseg)
#endif	VMTP_INVOKE
	register struct socket *so;
	register struct mbuf *msg;
	register struct mbuf **a_respseg;
	caddr_t sendseg;
{
	register int s = splnet();
	int error;

#ifdef	VMTP_DEBUG
	printf("soinvoke()\n");
#endif
	if (msg->m_next != NULL)
		panic("soinvoke(): msg->next != NULL\n");

	msg->m_next = (struct mbuf *)sendseg;

#ifdef	VMTP_DEBUG
	printf("soinvoke(): calling usrreq\n");
#endif
#if	VMTP_INVOKE
	error =
	    (*so->so_proto->pr_usrreq)(so, PRU_INVOKE, 
		msg, (struct mbuf *)0, (struct mbuf *)0, func);
#else	VMTP_INVOKE
	error =
	    (*so->so_proto->pr_usrreq)(so, PRU_INVOKE,
		msg, (struct mbuf *)0, (struct mbuf *)0);
#endif	VMTP_INVOKE
	splx(s);

#ifdef	VMTP_DEBUG
	printf("soinvoke(): returning\n");
#endif
	if (error)
		return(error);

	*a_respseg = msg->m_next;
	msg->m_next = NULL;

	return (0);
}

/*
 * sorecvreq(so, msg, a_seg)
 *
 * On return from usrreq the first mbuf in the chain is assumed to
 * contain the mcb and the rest is the segment data.
 */
sorecvreq(so, msg, a_seg)
	register struct socket *so;
	register struct mbuf 	*msg,
			**a_seg;
{
	register int s = splnet();
	int error;

#ifdef	VMTP_DEBUG
	printf("sorecvreq()\n");
	printf("sorecvreq(): calling usrreq\n");
#endif

	error =
	    (*so->so_proto->pr_usrreq)(so, PRU_RECVREQ,
		msg, (struct mbuf *)0, (struct mbuf *)0);
	splx(s);
	
	if (error)
		return error;

	*a_seg = msg->m_next;
	msg->m_next = NULL;
#ifdef	VMTP_DEBUG
	printf("sorecvreq(): returning\n");
#endif

	return (0);
}

/*
 * soreply(so, msg, seg)
 *
 * The msg must consist of only one mbuf - the rest is dropped.
 */
soreply(so,msg,segptr)
	register struct socket *so;
	register struct mbuf 	*msg;
	caddr_t		*segptr;
{
	register int s = splnet();
	int error;

#ifdef	VMTP_DEBUG
	printf("soreply()\n");
#endif
	if (msg->m_next != NULL)
		panic("soreply(): msg->next != NULL\n");

	msg->m_next = (struct mbuf *)segptr;

#ifdef	VMTP_DEBUG
	printf("soreply(): calling usrreq\n");
#endif
	error =
	    (*so->so_proto->pr_usrreq)(so, PRU_REPLY,
		msg, (struct mbuf *)0, (struct mbuf *)0);
	splx(s);

#ifdef	VMTP_DEBUG
	printf("soreply(): returning\n");
#endif
	return(error);
}

/*
 * soforward
 */
soforward(so, msg, nam, segptr)
	register struct socket *so;
	register struct mbuf *msg;
	struct mbuf  *nam;
	caddr_t	segptr;
{
	register int s = splnet();
	int error;

	if (msg->m_next != NULL)
		panic("soforward(): msg->next != NULL\n");

	msg->m_next = (struct mbuf *)segptr;

	error =
	    (*so->so_proto->pr_usrreq)(so, PRU_FORWARD,
		msg, nam, (struct mbuf *)0);
	splx(s);

	return error;
} /* soforward */

/*
 * soprobeentity(so, data)
 */
soprobeentity(so, data)
	register struct socket *so;
	struct mbuf *data;
{
	int error;
	register int s = splnet();

	error =
	    (*so->so_proto->pr_usrreq)(so, PRU_PROBE,
		data, (struct mbuf *)0, (struct mbuf *)0);
	splx(s);

	return error;
} /* soprobeentity */

/*
 * sogetreply(so, msg, a_seg)
 *
 * The timeout value is passed to usrreq in the addr parameter!
 *
 * On return from usrreq the first mbuf in the chain is assumed to
 * contain the mcb and the rest is the segment data.
 */
sogetreply(so, msg, a_seg, timeout)
	register struct socket *so;
	register struct mbuf *msg;
	struct mbuf **a_seg;
	int timeout;
{
	register int s = splnet();
	int error;

#ifdef	VMTP_DEBUG
	printf("sogetreply()\n");
	printf("sogetreply(): calling usrreq\n");
#endif

	error =
	    (*so->so_proto->pr_usrreq)(so, PRU_GETREPLY,
		msg, (struct mbuf *)timeout, (struct mbuf *)0);
	splx(s);

	if (error)
		return error;

#ifdef	VMTP_DEBUG
	printf("sogetreply(): returning\n");
#endif

	*a_seg = msg->m_next;
	msg->m_next = NULL;

	return (0);
}


#endif	MACH_VMTP

/*ARGSUSED*/
socreate(dom, aso, type, proto)
	struct socket **aso;
	register int type;
	int proto;
{
	register struct protosw *prp;
	register struct socket *so;
	register struct mbuf *m;
	register int error;

	if (proto)
		prp = pffindproto(dom, proto, type);
	else
		prp = pffindtype(dom, type);
	if (prp == 0)
		return (EPROTONOSUPPORT);
	if (prp->pr_type != type)
		return (EPROTOTYPE);
	m = m_getclr(M_WAIT, MT_SOCKET);
	so = mtod(m, struct socket *);
	so->so_options = 0;
	so->so_state = 0;
	so->so_type = type;
	if (u.u_uid == 0 || groupmember(NETWORK_GROUP))	/* XXX */
		so->so_state = SS_PRIV;
	so->so_proto = prp;
	error =
	    (*prp->pr_usrreq)(so, PRU_ATTACH,
		(struct mbuf *)0, (struct mbuf *)proto, (struct mbuf *)0);
	if (error) {
		so->so_state |= SS_NOFDREF;
		sofree(so);
		return (error);
	}
	*aso = so;
	return (0);
}

sobind(so, nam)
	struct socket *so;
	struct mbuf *nam;
{
	int s = splnet();
	int error;

	error =
	    (*so->so_proto->pr_usrreq)(so, PRU_BIND,
		(struct mbuf *)0, nam, (struct mbuf *)0);
	splx(s);
	return (error);
}

solisten(so, backlog)
	register struct socket *so;
	int backlog;
{
	int s = splnet(), error;

	error =
	    (*so->so_proto->pr_usrreq)(so, PRU_LISTEN,
		(struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0);
	if (error) {
		splx(s);
		return (error);
	}
	if (so->so_q == 0) {
		so->so_q = so;
		so->so_q0 = so;
		so->so_options |= SO_ACCEPTCONN;
	}
	if (backlog < 0)
		backlog = 0;
	so->so_qlimit = MIN(backlog, SOMAXCONN);
	splx(s);
	return (0);
}

sofree(so)
	register struct socket *so;
{

	if (so->so_head) {
		if (!soqremque(so, 0) && !soqremque(so, 1))
			panic("sofree dq");
		so->so_head = 0;
	}
	if (so->so_pcb || (so->so_state & SS_NOFDREF) == 0)
		return;
	sbrelease(&so->so_snd);
	sorflush(so);
	(void) m_free(dtom(so));
}

/*
 * Close a socket on last file table reference removal.
 * Initiate disconnect if connected.
 * Free socket when disconnect complete.
 */
soclose(so)
	register struct socket *so;
{
	int s = splnet();		/* conservative */
	int error;

	if (so->so_options & SO_ACCEPTCONN) {
		while (so->so_q0 != so)
			(void) soabort(so->so_q0);
		while (so->so_q != so)
			(void) soabort(so->so_q);
	}
	if (so->so_pcb == 0)
		goto discard;
	if (so->so_state & SS_ISCONNECTED) {
		if ((so->so_state & SS_ISDISCONNECTING) == 0) {
			error = sodisconnect(so);
			if (error)
				goto drop;
		}
		if (so->so_options & SO_LINGER) {
			if ((so->so_state & SS_ISDISCONNECTING) &&
			    (so->so_state & SS_NBIO))
				goto drop;
			while (so->so_state & SS_ISCONNECTED)
				sleep((caddr_t)&so->so_timeo, PZERO+1);
		}
	}
drop:
	if (so->so_pcb) {
		int error2 =
		    (*so->so_proto->pr_usrreq)(so, PRU_DETACH,
			(struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0);
		if (error == 0)
			error = error2;
	}
discard:
	if (so->so_state & SS_NOFDREF)
		panic("soclose: NOFDREF");
	so->so_state |= SS_NOFDREF;
	sofree(so);
	splx(s);
	return (error);
}

/*
 * Must be called at splnet...
 */
soabort(so)
	struct socket *so;
{

	return (
	    (*so->so_proto->pr_usrreq)(so, PRU_ABORT,
		(struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0));
}

soaccept(so, nam)
	register struct socket *so;
	struct mbuf *nam;
{
	int s = splnet();
	int error;

	if ((so->so_state & SS_NOFDREF) == 0)
		panic("soaccept: !NOFDREF");
	so->so_state &= ~SS_NOFDREF;
	error = (*so->so_proto->pr_usrreq)(so, PRU_ACCEPT,
	    (struct mbuf *)0, nam, (struct mbuf *)0);
	splx(s);
	return (error);
}

soconnect(so, nam)
	register struct socket *so;
	struct mbuf *nam;
{
	int s = splnet();
	int error;

	/*
	 * If protocol is connection-based, can only connect once.
	 * Otherwise, if connected, try to disconnect first.
	 * This allows user to disconnect by connecting to, e.g.,
	 * a null address.
	 */
	if (so->so_state & (SS_ISCONNECTED|SS_ISCONNECTING) &&
	    ((so->so_proto->pr_flags & PR_CONNREQUIRED) ||
	    (error = sodisconnect(so))))
		error = EISCONN;
	else
		error = (*so->so_proto->pr_usrreq)(so, PRU_CONNECT,
		    (struct mbuf *)0, nam, (struct mbuf *)0);
	splx(s);
	return (error);
}

soconnect2(so1, so2)
	register struct socket *so1;
	struct socket *so2;
{
	int s = splnet();
	int error;

	error = (*so1->so_proto->pr_usrreq)(so1, PRU_CONNECT2,
	    (struct mbuf *)0, (struct mbuf *)so2, (struct mbuf *)0);
	splx(s);
	return (error);
}

sodisconnect(so)
	register struct socket *so;
{
	int s = splnet();
	int error;

	if ((so->so_state & SS_ISCONNECTED) == 0) {
		error = ENOTCONN;
		goto bad;
	}
	if (so->so_state & SS_ISDISCONNECTING) {
		error = EALREADY;
		goto bad;
	}
	error = (*so->so_proto->pr_usrreq)(so, PRU_DISCONNECT,
	    (struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0);
bad:
	splx(s);
	return (error);
}

/*
 * Send on a socket.
 * If send must go all at once and message is larger than
 * send buffering, then hard error.
 * Lock against other senders.
 * If must go all at once and not enough room now, then
 * inform user that this would block and do nothing.
 * Otherwise, if nonblocking, send as much as possible.
 */
sosend(so, nam, uio, flags, rights)
	register struct socket *so;
	struct mbuf *nam;
	register struct uio *uio;
	int flags;
	struct mbuf *rights;
{
	struct mbuf *top = 0;
	register struct mbuf *m, **mp;
	register int space;
	int len, rlen = 0, error = 0, s, dontroute, first = 1;

	if (sosendallatonce(so) && uio->uio_resid > so->so_snd.sb_hiwat)
		return (EMSGSIZE);
	dontroute =
	    (flags & MSG_DONTROUTE) && (so->so_options & SO_DONTROUTE) == 0 &&
	    (so->so_proto->pr_flags & PR_ATOMIC);
	u.u_ru.ru_msgsnd++;
	if (rights)
		rlen = rights->m_len;
#define snderr(errno)	{ error = errno; splx(s); goto release; }

restart:
	sblock(&so->so_snd);
#if	0	/* DPJ */
	/*
	 * If we allow several threads to be in send and recv on the
	 * same socket at once, this will guarantee that there is no
	 * interference.
	 *
	 * This is the only place where two socketbufs are locked at
	 * once, so beware!
	 */
	sblock(&so->so_rcv);
#endif	0	/* DPJ */
	do {
		s = splnet();
		if (so->so_state & SS_CANTSENDMORE)
			snderr(EPIPE);
		if (so->so_error) {
			error = so->so_error;
			so->so_error = 0;			/* ??? */
			splx(s);
			goto release;
		}
		if ((so->so_state & SS_ISCONNECTED) == 0) {
			if (so->so_proto->pr_flags & PR_CONNREQUIRED)
				snderr(ENOTCONN);
			if (nam == 0)
				snderr(EDESTADDRREQ);
		}
		if (flags & MSG_OOB)
			space = 1024;
		else {
			space = sbspace(&so->so_snd);
			if (space <= rlen ||
			   (sosendallatonce(so) &&
				space < uio->uio_resid + rlen) ||
			   (uio->uio_resid >= CLBYTES && space < CLBYTES &&
			   so->so_snd.sb_cc >= CLBYTES &&
			   (so->so_state & SS_NBIO) == 0)) {
				if (so->so_state & SS_NBIO) {
					if (first)
						error = EWOULDBLOCK;
					splx(s);
					goto release;
				}
				sbunlock(&so->so_snd);
#if	0	/* DPJ */
				sbunlock(&so->so_rcv);
#endif	0	/* DPJ */
				sbwait(&so->so_snd);
				splx(s);
				goto restart;
			}
		}
		splx(s);
		mp = &top;
		space -= rlen;
		while (space > 0) {
			MGET(m, M_WAIT, MT_DATA);
			len = MIN(uio->uio_resid, space);
			if (len >= 2 * MLEN) {
				MCLGET(m);
				if (m->m_len != CLBYTES)
					goto nopages;
				len = MIN(len, CLBYTES);
			} else {
nopages:
				len = MIN(len, MLEN);
			}
			space -= len;

			error = uiomove(mtod(m, caddr_t), len, UIO_WRITE, uio);
			m->m_len = len;
			*mp = m;
			if (error)
				goto release;
			mp = &m->m_next;
			if (uio->uio_resid <= 0)
				break;
		}
		if (dontroute)
			so->so_options |= SO_DONTROUTE;
		s = splnet();					/* XXX */
		error = (*so->so_proto->pr_usrreq)(so,
		    (flags & MSG_OOB) ? PRU_SENDOOB : PRU_SEND,
		    top, (caddr_t)nam, rights);
		splx(s);
		if (dontroute)
			so->so_options &= ~SO_DONTROUTE;
		rights = 0;
		rlen = 0;
		top = 0;
		first = 0;
		if (error)
			break;
	} while (uio->uio_resid);

release:
	sbunlock(&so->so_snd);
#if	0	/* DPJ */
	sbunlock(&so->so_rcv);
#endif	0	/* DPJ */
	if (top)
		m_freem(top);
#if	MACH_NP
	if ((error == EPIPE) && ((so->so_options & SO_CANTSIG) == 0))
#else	MACH_NP
	if (error == EPIPE)
#endif	MACH_NP
		thread_doexception(current_thread(), EXC_SOFTWARE,
			EXC_UNIX_BAD_PIPE, 0);
	return (error);
}

/*
 * Implement receive operations on a socket.
 * We depend on the way that records are added to the sockbuf
 * by sbappend*.  In particular, each record (mbufs linked through m_next)
 * must begin with an address if the protocol so specifies,
 * followed by an optional mbuf containing access rights if supported
 * by the protocol, and then zero or more mbufs of data.
 * In order to avoid blocking network interrupts for the entire time here,
 * we splx() while doing the actual copy to user space.
 * Although the sockbuf is locked, new data may still be appended,
 * and thus we must maintain consistency of the sockbuf during that time.
 */
soreceive(so, aname, uio, flags, rightsp)
	register struct socket *so;
	struct mbuf **aname;
	register struct uio *uio;
	int flags;
	struct mbuf **rightsp;
{
	register struct mbuf *m;
	register int len, error = 0, s, tomark;
	struct protosw *pr = so->so_proto;
	struct mbuf *nextrecord;
	int moff;

	if (rightsp)
		*rightsp = 0;
	if (aname)
		*aname = 0;
	if (flags & MSG_OOB) {
		m = m_get(M_WAIT, MT_DATA);
		error = (*pr->pr_usrreq)(so, PRU_RCVOOB,
		    m, (struct mbuf *)(flags & MSG_PEEK), (struct mbuf *)0);
		if (error)
			goto bad;
		do {
			len = uio->uio_resid;
			if (len > m->m_len)
				len = m->m_len;
			error =
			    uiomove(mtod(m, caddr_t), (int)len, UIO_READ, uio);
			m = m_free(m);
		} while (uio->uio_resid && error == 0 && m);
bad:
		if (m)
			m_freem(m);
		return (error);
	}

restart:
	sblock(&so->so_rcv);
	s = splnet();

#define rcverr(errno)	{ error = errno; splx(s); goto release; }
	if (so->so_rcv.sb_cc == 0) {
		if (so->so_error) {
			error = so->so_error;
			so->so_error = 0;
			splx(s);
			goto release;
		}
		if (so->so_state & SS_CANTRCVMORE) {
			splx(s);
			goto release;
		}
		if ((so->so_state & SS_ISCONNECTED) == 0 &&
		    (so->so_proto->pr_flags & PR_CONNREQUIRED))
			rcverr(ENOTCONN);
		if (uio->uio_resid == 0)
			goto release;
		if (so->so_state & SS_NBIO)
			rcverr(EWOULDBLOCK);
		sbunlock(&so->so_rcv);
		sbwait(&so->so_rcv);
		splx(s);
		goto restart;
	}
	u.u_ru.ru_msgrcv++;
	m = so->so_rcv.sb_mb;
	if (m == 0)
		panic("receive 1");
	nextrecord = m->m_act;
	if (pr->pr_flags & PR_ADDR) {
		if (m->m_type != MT_SONAME)
			panic("receive 1a");
		if (flags & MSG_PEEK) {
			if (aname)
				*aname = m_copy(m, 0, m->m_len);
			m = m->m_next;
		} else {
			sbfree(&so->so_rcv, m);
			if (aname) {
				*aname = m;
				m = m->m_next;
				(*aname)->m_next = 0;
				so->so_rcv.sb_mb = m;
			} else {
				MFREE(m, so->so_rcv.sb_mb);
				m = so->so_rcv.sb_mb;
			}
			if (m)
				m->m_act = nextrecord;
		}
	}
	if (m && m->m_type == MT_RIGHTS) {
		if ((pr->pr_flags & PR_RIGHTS) == 0)
			panic("receive 2");
		if (flags & MSG_PEEK) {
			if (rightsp)
				*rightsp = m_copy(m, 0, m->m_len);
			m = m->m_next;
		} else {
			sbfree(&so->so_rcv, m);
			if (rightsp) {
				*rightsp = m;
				so->so_rcv.sb_mb = m->m_next;
				m->m_next = 0;
				m = so->so_rcv.sb_mb;
			} else {
				MFREE(m, so->so_rcv.sb_mb);
				m = so->so_rcv.sb_mb;
			}
			if (m)
				m->m_act = nextrecord;
		}
	}
	moff = 0;
	tomark = so->so_oobmark;
	while (m && uio->uio_resid > 0 && error == 0) {
		if (m->m_type != MT_DATA && m->m_type != MT_HEADER)
			panic("receive 3");
		len = uio->uio_resid;
		so->so_state &= ~SS_RCVATMARK;
		if (tomark && len > tomark)
			len = tomark;
		if (len > m->m_len - moff)
			len = m->m_len - moff;
		splx(s);
		error =
		    uiomove(mtod(m, caddr_t) + moff, (int)len, UIO_READ, uio);
		s = splnet();
		if (len == m->m_len - moff) {
			if (flags & MSG_PEEK) {
				m = m->m_next;
				moff = 0;
			} else {
				nextrecord = m->m_act;
				sbfree(&so->so_rcv, m);
				MFREE(m, so->so_rcv.sb_mb);
				m = so->so_rcv.sb_mb;
				if (m)
					m->m_act = nextrecord;
			}
		} else {
			if (flags & MSG_PEEK)
				moff += len;
			else {
				m->m_off += len;
				m->m_len -= len;
				so->so_rcv.sb_cc -= len;
			}
		}
		if ((flags & MSG_PEEK) == 0 && so->so_oobmark) {
			so->so_oobmark -= len;
			if (so->so_oobmark == 0) {
				so->so_state |= SS_RCVATMARK;
				break;
			}
		}
		if (tomark) {
			tomark -= len;
			if (tomark == 0)
				break;
		}
	}
	if ((flags & MSG_PEEK) == 0) {
		if (m == 0)
			so->so_rcv.sb_mb = nextrecord;
		else if (pr->pr_flags & PR_ATOMIC)
			(void) sbdroprecord(&so->so_rcv);
		if (pr->pr_flags & PR_WANTRCVD && so->so_pcb)
			(*pr->pr_usrreq)(so, PRU_RCVD, (struct mbuf *)0,
			    (struct mbuf *)0, (struct mbuf *)0);
		if (error == 0 && rightsp && *rightsp &&
		    pr->pr_domain->dom_externalize)
			error = (*pr->pr_domain->dom_externalize)(*rightsp);
	}
release:
	sbunlock(&so->so_rcv);
	splx(s);
	return (error);
}

soshutdown(so, how)
	register struct socket *so;
	register int how;
{
	register struct protosw *pr = so->so_proto;

	how++;
	if (how & FREAD)
		sorflush(so);
	if (how & FWRITE)
		return ((*pr->pr_usrreq)(so, PRU_SHUTDOWN,
		    (struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0));
	return (0);
}

sorflush(so)
	register struct socket *so;
{
	register struct sockbuf *sb = &so->so_rcv;
	register struct protosw *pr = so->so_proto;
	register int s;
	struct sockbuf asb;

	sblock(sb);
	s = splimp();
	socantrcvmore(so);
	sbunlock(sb);
	asb = *sb;
	bzero((caddr_t)sb, sizeof (*sb));
	splx(s);
	if (pr->pr_flags & PR_RIGHTS && pr->pr_domain->dom_dispose)
		(*pr->pr_domain->dom_dispose)(asb.sb_mb);
	sbrelease(&asb);
}

sosetopt(so, level, optname, m0)
	register struct socket *so;
	int level, optname;
	struct mbuf *m0;
{
	int error = 0;
	register struct mbuf *m = m0;

	if (level != SOL_SOCKET) {
		if (so->so_proto && so->so_proto->pr_ctloutput)
			return ((*so->so_proto->pr_ctloutput)
				  (PRCO_SETOPT, so, level, optname, &m0));
		error = ENOPROTOOPT;
	} else {
		switch (optname) {

		case SO_LINGER:
			if (m == NULL || m->m_len != sizeof (struct linger)) {
				error = EINVAL;
				goto bad;
			}
			so->so_linger = mtod(m, struct linger *)->l_linger;
			/* fall thru... */

		case SO_DEBUG:
		case SO_KEEPALIVE:
		case SO_DONTROUTE:
		case SO_USELOOPBACK:
		case SO_BROADCAST:
		case SO_REUSEADDR:
		case SO_OOBINLINE:
#if	MULTIBIND
		case SO_MULTIBIND:
#endif	MULTIBIND
		case SO_USEPRIV:
			if (m == NULL || m->m_len < sizeof (int)) {
				error = EINVAL;
				goto bad;
			}
			if (*mtod(m, int *))
				so->so_options |= optname;
			else
				so->so_options &= ~optname;
			break;

#if	VICE
		case SO_GREEDY:
			if (so->so_type != SOCK_DGRAM)
			    return EOPNOTSUPP;
			so->so_snd.sb_hiwat = so->so_snd.sb_mbmax = SBMAXCC;
			so->so_rcv.sb_hiwat = so->so_rcv.sb_mbmax = SBMAXCC;
			break;
#endif	VICE

		case SO_SNDBUF:
		case SO_RCVBUF:
		case SO_SNDLOWAT:
		case SO_RCVLOWAT:
		case SO_SNDTIMEO:
		case SO_RCVTIMEO:
			if (m == NULL || m->m_len < sizeof (int)) {
				error = EINVAL;
				goto bad;
			}
			switch (optname) {

			case SO_SNDBUF:
			case SO_RCVBUF:
				if (sbreserve(optname == SO_SNDBUF ? &so->so_snd :
				    &so->so_rcv, *mtod(m, int *)) == 0) {
					error = ENOBUFS;
					goto bad;
				}
				break;

			case SO_SNDLOWAT:
				so->so_snd.sb_lowat = *mtod(m, int *);
				break;
			case SO_RCVLOWAT:
				so->so_rcv.sb_lowat = *mtod(m, int *);
				break;
			case SO_SNDTIMEO:
				so->so_snd.sb_timeo = *mtod(m, int *);
				break;
			case SO_RCVTIMEO:
				so->so_rcv.sb_timeo = *mtod(m, int *);
				break;
			}
			break;

		default:
			error = ENOPROTOOPT;
			break;
		}
	}
bad:
	if (m)
		(void) m_free(m);
	return (error);
}

sogetopt(so, level, optname, mp)
	register struct socket *so;
	int level, optname;
	struct mbuf **mp;
{
	register struct mbuf *m;

	if (level != SOL_SOCKET) {
		if (so->so_proto && so->so_proto->pr_ctloutput) {
			return ((*so->so_proto->pr_ctloutput)
				  (PRCO_GETOPT, so, level, optname, mp));
		} else 
			return (ENOPROTOOPT);
	} else {
		m = m_get(M_WAIT, MT_SOOPTS);
		m->m_len = sizeof (int);

		switch (optname) {

		case SO_LINGER:
			m->m_len = sizeof (struct linger);
			mtod(m, struct linger *)->l_onoff =
				so->so_options & SO_LINGER;
			mtod(m, struct linger *)->l_linger = so->so_linger;
			break;

		case SO_USELOOPBACK:
		case SO_DONTROUTE:
		case SO_DEBUG:
		case SO_KEEPALIVE:
		case SO_REUSEADDR:
		case SO_BROADCAST:
		case SO_OOBINLINE:
		case SO_USEPRIV:
			*mtod(m, int *) = so->so_options & optname;
			break;

		case SO_TYPE:
			*mtod(m, int *) = so->so_type;
			break;

		case SO_ERROR:
			*mtod(m, int *) = so->so_error;
			so->so_error = 0;
			break;

		case SO_SNDBUF:
			*mtod(m, int *) = so->so_snd.sb_hiwat;
			break;

		case SO_RCVBUF:
			*mtod(m, int *) = so->so_rcv.sb_hiwat;
			break;

		case SO_SNDLOWAT:
			*mtod(m, int *) = so->so_snd.sb_lowat;
			break;

		case SO_RCVLOWAT:
			*mtod(m, int *) = so->so_rcv.sb_lowat;
			break;

		case SO_SNDTIMEO:
			*mtod(m, int *) = so->so_snd.sb_timeo;
			break;

		case SO_RCVTIMEO:
			*mtod(m, int *) = so->so_rcv.sb_timeo;
			break;

		default:
			(void)m_free(m);
			return (ENOPROTOOPT);
		}
		*mp = m;
		return (0);
	}
}

sohasoutofband(so)
	register struct socket *so;
{
	struct proc *p;

	if (so->so_pgrp < 0)
		gsignal(-so->so_pgrp, SIGURG);
	else if (so->so_pgrp > 0 && (p = pfind(so->so_pgrp)) != 0)
		psignal(p, SIGURG);
	if (so->so_rcv.sb_sel) {
		selwakeup(so->so_rcv.sb_sel, so->so_rcv.sb_flags & SB_COLL);
		so->so_rcv.sb_sel = 0;
		so->so_rcv.sb_flags &= ~SB_COLL;
	}
}
