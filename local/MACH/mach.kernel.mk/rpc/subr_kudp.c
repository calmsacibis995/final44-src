/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	subr_kudp.c,v $
 * Revision 2.5  89/08/02  08:06:36  jsb
 * 	Eliminated MACH conditionals.
 * 	[89/07/31  16:56:52  jsb]
 * 
 * Revision 2.4  89/03/09  20:59:19  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:15:00  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:03:10  jsb
 * 	Define udpmsgbuf_alloc, udpmsgbuf_free.
 * 	[89/01/17  14:26:38  jsb]
 * 
 */
/* @(#)subr_kudp.c	1.2 87/08/18 3.2/4.3NFSSRC */
/* @(#)subr_kudp.c	1.3 87/03/19 NFSSRC */
#ifndef	lint
static char sccsid[] = "@(#)subr_kudp.c 1.1 86/09/24 Copyr 1984 Sun Micro";
#endif

/*
 * subr_kudp.c
 * Subroutines to do UDP/IP sendto and recvfrom in the kernel
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */
#include <sys/param.h>
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
#include <vm/vm_kern.h>

struct mbuf     *mclgetx();

/*
 * General kernel udp stuff.
 * The routines below are used by both the client and the server side
 * rpc code.
 */

/*
 * Kernel recvfrom.
 * Pull address mbuf and data mbuf chain off socket receive queue.
 */
struct mbuf *
ku_recvfrom(so, from)
	struct socket *so;
	struct sockaddr_in *from;
{
	register struct mbuf	*m;
	register struct mbuf	*m0;
	struct mbuf		*nextrecord;
	register struct sockbuf	*sb = &so->so_rcv;
	register int		len = 0;

#ifdef	RPCDEBUG
	rpc_debug(4, "urrecvfrom so=%X\n", so);
#endif
	m = sb->sb_mb;
	if (m == NULL) {
		return (m);
	}
	nextrecord = m->m_act;

	*from = *mtod(m, struct sockaddr_in *);

	/*
	 * Advance to the data part of the packet,
	 * freeing the address part (and rights if present).
	 */
	for (m0 = m; m0 && m0->m_type != MT_DATA; ) {
		sbfree(sb, m0);
		m0 = m_free(m0);
	}
	if (m0 == NULL) {
		printf("ku_recvfrom: no body!\n");
		sb->sb_mb = nextrecord;
		return (m0);
	}

	/*
	 * Transfer ownership of the remainder of the packet
	 * record away from the socket and advance the socket
	 * to the next record.  Calculate the record's length
	 * while we're at it.
	 */
	for (m = m0; m; m = m->m_next) {
		sbfree(sb, m);
		len += m->m_len;
	}
	sb->sb_mb = nextrecord;

	if (len > UDPMSGSIZE) {
		printf("ku_recvfrom: len = %d\n", len);
	}

#ifdef	RPCDEBUG
	rpc_debug(4, "urrecvfrom %d from %X\n", len, from->sin_addr.s_addr);
#endif
	return (m0);
}

int Sendtries = 0;
int Sendok = 0;

/*
 * Kernel sendto.
 * Set addr and send off via UDP.
 * Use ku_fastsend if possible.
 */
int
ku_sendto_mbuf(so, m, addr)
	struct socket *so;
	struct mbuf *m;
	struct sockaddr_in *addr;
{
#ifdef	SLOWSEND
	register struct inpcb *inp = sotoinpcb(so);
        struct in_addr laddr;
	int s;
#endif
	int error;

#ifdef	RPCDEBUG
	rpc_debug(4, "ku_sendto_mbuf %X\n", addr->sin_addr.s_addr);
#endif
	Sendtries++;
#ifdef	SLOWSEND
	s = splnet();
        laddr = inp->inp_laddr;
	if (error = in_pcbsetaddr(inp, addr)) {
		printf("pcbsetaddr failed %d\n", error);
		(void) splx(s);
		m_freem(m);
		return (error);
	}
	error = udp_output(inp, m);
	in_pcbdisconnect(inp);
        inp->inp_laddr = laddr;
	(void) splx(s);
#else
	error = ku_fastsend(so, m, addr);
#endif
	Sendok++;
#ifdef	RPCDEBUG
	rpc_debug(4, "ku_sendto returning %d\n", error);
#endif
	return (error);
}

#ifdef	RPCDEBUG
int rpcdebug = 2;

/*VARARGS2*/
rpc_debug(level, str, a1, a2, a3, a4, a5, a6, a7, a8, a9)
        int level;
        char *str;
        int a1, a2, a3, a4, a5, a6, a7, a8, a9;
{

        if (level <= rpcdebug)
                printf(str, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}
#endif

struct mbuf *udpmsgbuf_freelist = 0;

struct mbuf *udpmsgbuf_alloc()
{
	struct mbuf *udpmsgbuf;
	int s;

	s = splimp();
	if (udpmsgbuf_freelist) {
		udpmsgbuf = udpmsgbuf_freelist;
		udpmsgbuf_freelist = udpmsgbuf->m_next;
	} else {
		udpmsgbuf = (struct mbuf *) kmem_mb_alloc(mb_map, UDPMSGSIZE);
		if (udpmsgbuf == 0) {
			panic("udpmsgbuf_alloc");
		}
	}
	splx(s);
	return udpmsgbuf;
}

udpmsgbuf_free(udpmsgbuf)
struct mbuf *udpmsgbuf;
{
	int s;

	s = splimp();
	udpmsgbuf->m_next = udpmsgbuf_freelist;
	udpmsgbuf_freelist = udpmsgbuf;
	splx(s);
}
