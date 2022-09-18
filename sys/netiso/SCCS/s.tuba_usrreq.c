h63687
s 00002/00002/00284
d D 8.1 93/06/10 23:21:44 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00284
d D 7.9 93/03/25 13:16:00 sklower 9 8
c fix from Francis.Dupont@inria
e
s 00004/00004/00282
d D 7.8 92/11/25 20:09:39 sklower 8 7
c this version supports TCP between two workstations on the same ethernet
e
s 00004/00000/00282
d D 7.7 92/11/20 22:45:25 sklower 7 6
c minor fixes & improvements: swab not in kernel; make sure NSEL is 
c 6 when connecting; don't bother to save extra 2 cksum fudges; change convention
c on who moves pointer past CLNP header; on input, if you have to pull up TCP
c header, do it directly into aligned header.
e
s 00001/00001/00281
d D 7.6 92/11/08 15:31:28 sklower 6 5
c this version works well enough for a simple sender & receiver to talk
e
s 00005/00002/00277
d D 7.5 92/11/05 15:00:41 sklower 5 4
c checkpoint further progress, still doesn't connect tho.
e
s 00014/00007/00265
d D 7.4 92/11/05 07:13:01 sklower 4 3
c checkpoint, doesn't do checksum right yet
e
s 00035/00034/00237
d D 7.3 92/10/15 18:51:33 sklower 3 2
c this version compiles and matches current #include convention
e
s 00001/00001/00270
d D 7.2 92/10/09 01:08:03 sklower 2 1
c correct defective copyright dates
e
s 00271/00000/00000
d D 7.1 92/10/09 00:51:47 sklower 1 0
c date and time created 92/10/09 00:51:47 by sklower
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 2
I 2
D 10
 * Copyright (c) 1992 Regents of the University of California.
E 2
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "param.h"
#include "systm.h"
#include "malloc.h"
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "protosw.h"
#include "errno.h"
#include "stat.h"
E 3
I 3
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>
#include <sys/errno.h>
#include <sys/stat.h>
E 3

D 3
#include "net/if.h"
#include "net/route.h"
E 3
I 3
#include <net/if.h>
#include <net/route.h>
E 3

D 3
#include "in.h"
#include "in_systm.h"
#include "ip.h"
#include "in_pcb.h"
#include "ip_var.h"
#include "tcp.h"
#include "tcp_fsm.h"
#include "tcp_seq.h"
#include "tcp_timer.h"
#include "tcp_var.h"
#include "tcpip.h"
#include "tcp_debug.h"
E 3
I 3
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/in_pcb.h>
#include <netinet/ip_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcpip.h>
#include <netinet/tcp_debug.h>
E 3

D 3
#include "netiso/argo_debug.h"
#include "netiso/iso.h"
#include "netiso/clnp.h"
#include "netiso/iso_pcb.h"
#include "netiso/iso_var.h"
E 3
I 3
#include <netiso/argo_debug.h>
#include <netiso/iso.h>
#include <netiso/clnp.h>
#include <netiso/iso_pcb.h>
#include <netiso/iso_var.h>
D 4
#include <netiso/tuba_addr.h>
E 4
I 4
#include <netiso/tuba_table.h>
E 4
E 3
/*
 * TCP protocol interface to socket abstraction.
 */
extern	char *tcpstates[];
D 5
extern	struct inpcb tcb;
struct	isopcb tuba_isopcb;
E 5
I 5
extern	struct inpcb tuba_inpcb;
extern	struct isopcb tuba_isopcb;
E 5

/*
 * Process a TCP user request for TCP tb.  If this is a send request
 * then m is the mbuf chain of send data.  If this is a timer expiration
 * (called from the software clock routine), then timertype tells which timer.
 */
/*ARGSUSED*/
tuba_usrreq(so, req, m, nam, control)
	struct socket *so;
	int req;
	struct mbuf *m, *nam, *control;
{
	register struct inpcb *inp;
	register struct isopcb *isop;
	register struct tcpcb *tp;
	int s;
	int error = 0;
	int ostate;
D 3
	struct sockaddr_iso siso;
E 3
I 3
	struct sockaddr_iso *siso;
E 3

	if (req == PRU_CONTROL)
		return (iso_control(so, (int)m, (caddr_t)nam,
			(struct ifnet *)control));

	s = splnet();
	inp = sotoinpcb(so);
	/*
	 * When a TCP is attached to a socket, then there will be
	 * a (struct inpcb) pointed at by the socket, and this
	 * structure will point at a subsidary (struct tcpcb).
	 */
	if (inp == 0  && req != PRU_ATTACH) {
		splx(s);
		return (EINVAL);		/* XXX */
	}
	if (inp) {
D 3
		tp = inpcbtotcpcb(inp);
E 3
I 3
		tp = intotcpcb(inp);
E 3
		if (tp == 0)
			panic("tuba_usrreq");
		ostate = tp->t_state;
D 3
		isop = tp->tp_tuba_pcb;
E 3
I 3
		isop = (struct isopcb *)tp->t_tuba_pcb;
E 3
		if (isop == 0)
			panic("tuba_usrreq 2");
	} else
		ostate = 0;
	switch (req) {

	/*
	 * TCP attaches to socket via PRU_ATTACH, reserving space,
	 * and an internet control block.  We also need to
	 * allocate an isopcb and separate the control block from
	 * tcp/ip ones.
	 */
	case PRU_ATTACH:
		if (error = iso_pcballoc(so, &tuba_isopcb))
			break;
D 3
		isop = (struct isopcb *) tp->tp_tuba_pcb = so->so_pcb;
E 3
I 3
D 4
		isop = (struct isopcb *) tp->t_tuba_pcb = so->so_pcb;
E 3
		if (error = tcp_userreq(so, req, m, nam, control)) {
E 4
I 4
		isop = (struct isopcb *)so->so_pcb;
		so->so_pcb = 0;
		if (error = tcp_usrreq(so, req, m, nam, control)) {
E 4
			isop->isop_socket = 0;
D 4
			isop_detach(isop);
E 4
I 4
			iso_pcbdetach(isop);
		} else {
			inp = sotoinpcb(so);
I 5
			remque(inp);
			insque(inp, &tuba_inpcb);
			inp->inp_head = &tuba_inpcb;
E 5
			tp = intotcpcb(inp);
			if (tp == 0)
				panic("tuba_usrreq 3");
			tp->t_tuba_pcb = (caddr_t) isop;
E 4
		}
		goto notrace;

	/*
	 * PRU_DETACH detaches the TCP protocol from the socket.
	 * If the protocol state is non-embryonic, then can't
	 * do this directly: have to initiate a PRU_DISCONNECT,
	 * which may finish later; embryonic TCB's can just
	 * be discarded here.
	 */
	case PRU_DETACH:
		if (tp->t_state > TCPS_LISTEN)
			tp = tcp_disconnect(tp);
		else
			tp = tcp_close(tp);
		if (tp == 0)
			tuba_pcbdetach(isop);
		break;

	/*
	 * Give the socket an address.
	 */
	case PRU_BIND:
		siso = mtod(nam, struct sockaddr_iso *);
		if (siso->siso_tlen && siso->siso_tlen != 2) {
			error = EINVAL;
			break;
		}
		if ((error = iso_pcbbind(isop, nam)) || 
		    (siso = isop->isop_laddr) == 0)
			break;
		bcopy(TSEL(siso), &inp->inp_lport, 2);
		if (siso->siso_nlen &&
D 4
		    !(inp->inp_laddr.s_addr = tuba_lookup(&siso->siso_addr)))
E 4
I 4
D 8
		    !(inp->inp_laddr.s_addr = tuba_lookup(&siso->siso_addr, M_WAITOK)))
E 8
I 8
		    !(inp->inp_laddr.s_addr = tuba_lookup(siso, M_WAITOK)))
E 8
E 4
			error = ENOBUFS;
		break;

	/*
	 * Prepare to accept connections.
	 */
	case PRU_CONNECT:
	case PRU_LISTEN:
		if (inp->inp_lport == 0 &&
		    (error = iso_pcbbind(isop, (struct mbuf *)0)))
			break;
		bcopy(TSEL(isop->isop_laddr), &inp->inp_lport, 2);
D 3
		if (cmd == PRU_LISTEN) {
E 3
I 3
		if (req == PRU_LISTEN) {
E 3
			tp->t_state = TCPS_LISTEN;
			break;
		}
	/*FALLTHROUGH*/
	/*
	 * Initiate connection to peer.
	 * Create a template for use in transmissions on this connection.
	 * Enter SYN_SENT state, and mark socket as connecting.
	 * Start keep-alive timer, and seed output sequence space.
	 * Send initial segment on connection.
	 */
	/* case PRU_CONNECT: */
		if (error = iso_pcbconnect(isop, nam))
			break;
I 7
		if ((siso = isop->isop_laddr) && siso->siso_nlen > 1)
			siso->siso_data[siso->siso_nlen - 1] = ISOPROTO_TCP;
		else
			panic("tuba_usrreq: connect");
E 7
		siso = mtod(nam, struct sockaddr_iso *);
D 4
		if (!(inp->inp_faddr.s_addr = tuba_lookup(&siso->siso_addr))) {
E 4
I 4
D 8
		if (!(inp->inp_faddr.s_addr = tuba_lookup(&siso->siso_addr, M_WAITOK))) {
E 8
I 8
		if (!(inp->inp_faddr.s_addr = tuba_lookup(siso, M_WAITOK))) {
E 8
E 4
		unconnect:
			iso_pcbdisconnect(isop);
			error = ENOBUFS;
			break;
		}
		bcopy(TSEL(isop->isop_faddr), &inp->inp_fport, 2);
D 3
		if ((inp->inp_laddr.s_addr == 0 &&
E 3
I 3
		if (inp->inp_laddr.s_addr == 0 &&
E 3
		     (inp->inp_laddr.s_addr = 
D 4
			    tuba_lookup(&isop->isop_laddr->siso_addr)) == 0)
E 4
I 4
D 8
			    tuba_lookup(&isop->isop_laddr->siso_addr, M_WAITOK)) == 0)
E 8
I 8
			    tuba_lookup(isop->isop_laddr, M_WAITOK)) == 0)
E 8
E 4
			goto unconnect;
		if ((tp->t_template = tcp_template(tp)) == 0)
			goto unconnect;
		soisconnecting(so);
		tcpstat.tcps_connattempt++;
		tp->t_state = TCPS_SYN_SENT;
		tp->t_timer[TCPT_KEEP] = TCPTV_KEEP_INIT;
		tp->iss = tcp_iss; tcp_iss += TCP_ISSINCR/2;
		tcp_sendseqinit(tp);
		error = tcp_output(tp);
		tuba_refcnt(isop, 1);
		break;

	/*
	 * Initiate disconnect from peer.
	 * If connection never passed embryonic stage, just drop;
	 * else if don't need to let data drain, then can just drop anyways,
	 * else have to begin TCP shutdown process: mark socket disconnecting,
	 * drain unread data, state switch to reflect user close, and
	 * send segment (e.g. FIN) to peer.  Socket will be really disconnected
	 * when peer sends FIN and acks ours.
	 *
	 * SHOULD IMPLEMENT LATER PRU_CONNECT VIA REALLOC TCPCB.
	 */
	case PRU_DISCONNECT:
		if ((tp = tcp_disconnect(tp)) == 0)
			tuba_pcbdetach(isop);
		break;

	/*
	 * Accept a connection.  Essentially all the work is
	 * done at higher levels; just return the address
	 * of the peer, storing through addr.
	 */
	case PRU_ACCEPT:
D 6
		bcopy((caddr_t)isop->isop_faddr, mtod(m, caddr_t),
E 6
I 6
		bcopy((caddr_t)isop->isop_faddr, mtod(nam, caddr_t),
E 6
			nam->m_len = isop->isop_faddr->siso_len);
		break;

	/*
	 * Mark the connection as being incapable of further output.
	 */
	case PRU_SHUTDOWN:
		socantsendmore(so);
		tp = tcp_usrclosed(tp);
		if (tp)
			error = tcp_output(tp);
		else
			tuba_pcbdetach(isop);
		break;
	/*
	 * Abort the TCP.
	 */
	case PRU_ABORT:
		if ((tp = tcp_drop(tp, ECONNABORTED)) == 0)
			tuba_pcbdetach(isop);
		break;


	case PRU_SOCKADDR:
		if (isop->isop_laddr)
D 9
			bcopy((caddr_t)isop->isop_laddr, mtod(m, caddr_t),
E 9
I 9
			bcopy((caddr_t)isop->isop_laddr, mtod(nam, caddr_t),
E 9
				nam->m_len = isop->isop_laddr->siso_len);
		break;

	case PRU_PEERADDR:
		if (isop->isop_faddr)
D 9
			bcopy((caddr_t)isop->isop_faddr, mtod(m, caddr_t),
E 9
I 9
			bcopy((caddr_t)isop->isop_faddr, mtod(nam, caddr_t),
E 9
				nam->m_len = isop->isop_faddr->siso_len);
		break;

	default:
		error = tcp_usrreq(so, req, m, nam, control);
		goto notrace;
	}
	if (tp && (so->so_options & SO_DEBUG))
		tcp_trace(TA_USER, ostate, tp, (struct tcpiphdr *)0, req);
notrace:
	splx(s);
	return(error);
}

tuba_ctloutput(op, so, level, optname, mp)
	int op;
	struct socket *so;
	int level, optname;
	struct mbuf **mp;
{
	int clnp_ctloutput(), tcp_ctloutput();

	return ((level != IPPROTO_TCP ? clnp_ctloutput : tcp_ctloutput)
D 8
		(clnp_ctloutput(op, so, level, optname, mp)));
E 8
I 8
			(op, so, level, optname, mp));
E 8
}
E 1
