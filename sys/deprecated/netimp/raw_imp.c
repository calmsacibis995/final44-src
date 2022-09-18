/*
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)raw_imp.c	7.7 (Berkeley) 10/11/92
 */

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/socketvar.h>
#include <sys/errno.h>

#include <net/if.h>
#include <net/route.h>
#include <net/raw_cb.h>

#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/in_pcb.h>
#include <netimp/if_imp.h>

/*
 * Raw interface to IMP.
 */

/*
 * Generate IMP leader and pass packet to impoutput.
 * The user must create a skeletal leader in order to
 * communicate message type, message subtype, etc.
 * We fill in holes where needed and verify parameters
 * supplied by user.
 */
rimp_output(m, so)
	register struct mbuf *m;
	struct socket *so;
{
	struct mbuf *n;
	int len, error = 0;
	register struct imp_leader *ip;
	register struct sockaddr_in *sin;
	register struct raw_inpcb *rp = sotorawinpcb(so);
	struct in_ifaddr *ia;
	struct control_leader *cp;

	/*
	 * Verify user has supplied necessary space
	 * for the leader and check parameters in it.
	 */
	if ((m->m_len < sizeof(struct control_leader)) &&
	    (m = m_pullup(m, sizeof(struct control_leader))) == 0) {
		error = EMSGSIZE;	/* XXX */
		goto bad;
	}
	cp = mtod(m, struct control_leader *);
	if (cp->dl_mtype == IMPTYPE_DATA)
		if (m->m_len < sizeof(struct imp_leader) &&
		    (m = m_pullup(m, sizeof(struct imp_leader))) == 0) {
			error = EMSGSIZE;	/* XXX */
			goto bad;
		}
	ip = mtod(m, struct imp_leader *);
	if (ip->il_format != IMP_NFF) {
		error = EMSGSIZE;		/* XXX */
		goto bad;
	}
#ifdef notdef
	if (ip->il_link != IMPLINK_IP &&
	    (ip->il_link<IMPLINK_LOWEXPER || ip->il_link>IMPLINK_HIGHEXPER)) {
		error = EPERM;
		goto bad;
	}
#endif

	/*
	 * Fill in IMP leader -- impoutput refrains from rebuilding
	 * the leader when it sees the protocol family PF_IMPLINK.
	 * (message size calculated by walking through mbuf's)
	 */
	for (len = 0, n = m; n; n = n->m_next)
		len += n->m_len;
	ip->il_length = htons((u_short)(len << 3));
	sin = (struct sockaddr_in *)rp->rinp_rcb.rcb_faddr;
	imp_addr_to_leader((struct control_leader *)ip, sin->sin_addr.s_addr);
	/* no routing here */
	ia = in_iaonnetof(in_netof(sin->sin_addr));
	if (ia)
		return (impoutput(ia->ia_ifp, m, (struct sockaddr *)sin));
	error = ENETUNREACH;
bad:
	m_freem(m);
	return (error);
}
