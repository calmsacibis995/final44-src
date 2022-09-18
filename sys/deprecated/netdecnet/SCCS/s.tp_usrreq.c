h21903
s 00001/00001/00078
d D 1.4 82/12/18 18:35:30 sam 4 3
c mbufs typed
e
s 00003/00005/00076
d D 1.3 82/10/09 05:50:26 wnj 3 2
c fix header files
e
s 00001/00000/00080
d D 1.2 82/05/15 21:53:25 sam 2 1
c add keywords
e
s 00080/00000/00000
d D 1.1 82/05/15 21:46:29 sam 1 0
c date and time created 82/05/15 21:46:29 by sam
e
u
U
t
T
I 2
/*	%M%	%I%	%E%	*/
E 2
I 1

#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../h/protosw.h"
D 3
#include "../net/dn_systm.h"
#include "../net/if.h"
#include "../net/tp.h"
#include "../net/tp_var.h"
#include "../errno.h"
E 3
I 3
#include "../netdecnet/dn_systm.h"
#include "../netdecnet/tp.h"
#include "../netdecnet/tp_var.h"
E 3

/*
 * Transport protocol interface to socket abstraction.
 * Used ONLY to initialize the Transport layer.  May be
 * used for routing control in the future.
 */

/*
 * Process a Transport user request.  Only allowed
 * operation is PRU_ATTACH to initialize the Transport
 * layer.
 */
tp_usrreq(so, req, m, addr)
	struct socket *so;
	int req;
	struct mbuf *m;
	caddr_t addr;
{
	int s = splimp();
	int error = 0;

	/*
	 */
	if (so->so_pcb != 0 || req != PRU_ATTACH) {
		splx(s);
		return (EINVAL);		/* XXX */
	}
	if (tpstate != TPS_HALT) {
		splx(s);
		return (0);
	}
	if (tp_linit() == 0) {
		splx(s);
		return (EIO);
	}
	sleep((caddr_t)&tpstate, PZERO+1);
	splx(s);
	return (0);
}

/*
 * Perform transport initialization for a line
 */
tp_linit()
{
	register struct mbuf *m;
	register struct tpin *t;
	register int n;

D 4
	m = m_get(0);
E 4
I 4
	m = m_get(MT_CANTWAIT, MT_HEADER);
E 4
	if (m == 0)
		return (0);
	m->m_off = MMINOFF;
	m->m_len = sizeof (struct tpin);
	t = mtod(m, struct tpin *);
	t->tpin_ctlflg = TP_INIT;
	AD_SHORT(t->tpin_srcnode, tp_host);
	t->tpin_tiinfo = TPINNT_NRT;
	AD_SHORT(t->tpin_blksize, 1024);
	t->tpin_ver[0] = 1;
	t->tpin_ver[1] = 3;
	t->tpin_ver[2] = 0;
	t->tpin_res = 0;
	n = (*tpifp->if_output)(tpifp, m, PF_DECNET);
	tpstate = TPS_TIS;
	m_freem(m);
	return (n);
}
E 1
