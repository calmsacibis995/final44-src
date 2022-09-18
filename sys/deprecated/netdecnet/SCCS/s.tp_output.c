h27965
s 00002/00006/00033
d D 1.3 82/10/09 05:50:17 wnj 3 2
c fix header files
e
s 00001/00000/00038
d D 1.2 82/05/15 21:53:23 sam 2 1
c add keywords
e
s 00038/00000/00000
d D 1.1 82/05/15 21:46:28 sam 1 0
c date and time created 82/05/15 21:46:28 by sam
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
D 3
#include "../h/clock.h"
E 3
#include "../h/mbuf.h"
#include "../h/protosw.h"
#include "../h/socket.h"
D 3
#include "../net/in.h"
#include "../net/in_systm.h"
E 3
#include "../net/if.h"
D 3
#include "../net/tp.h"
#include "../net/tp_var.h"

E 3
I 3
#include "../netdecnet/tp.h"
#include "../netdecnet/tp_var.h"
E 3

/*
 * Transport output routine.  Fill in the
 * transport header and pass it off to the
 * interface.
 */
tp_output(m, dstnode)
	register struct mbuf *m;
	u_short dstnode;
{
	register struct tprh *t;

	if (tpstate != TPS_RUN)
		return (1);
	if (dstnode > tprp.tprp_nn)		/* node number out of range? */
		return (1);
	m->m_off -= sizeof (struct tprh);
	m->m_len += sizeof (struct tprh);
	t = mtod(m, struct tprh *);
	t->tprh_rtflg = TP_RH;
	AD_SHORT(t->tprh_srcnode, tp_host);
	AD_SHORT(t->tprh_dstnode, dstnode);
	t->tprh_forward = 0;
	return ((*tpifp->if_output)(tpifp, m, PF_DECNET));
}
E 1
