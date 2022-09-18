h22066
s 00002/00002/00320
d D 8.1 93/06/10 23:21:35 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00002/00317
d D 7.12 93/02/12 14:49:45 sklower 12 11
c revise to match most recent version of tcp_input.c
e
s 00026/00015/00293
d D 7.11 92/11/25 20:09:37 sklower 11 10
c this version supports TCP between two workstations on the same ethernet
e
s 00042/00044/00266
d D 7.10 92/11/20 22:45:23 sklower 10 9
c minor fixes & improvements: swab not in kernel; make sure NSEL is 
c 6 when connecting; don't bother to save extra 2 cksum fudges; change convention
c on who moves pointer past CLNP header; on input, if you have to pull up TCP
c header, do it directly into aligned header.
e
s 00031/00025/00279
d D 7.9 92/11/19 02:38:18 sklower 9 8
c changes thought to be required for new pseudo-header, not tested
e
s 00017/00016/00287
d D 7.8 92/11/08 15:31:26 sklower 8 7
c this version works well enough for a simple sender & receiver to talk
e
s 00024/00074/00279
d D 7.7 92/11/05 15:00:36 sklower 7 6
c checkpoint further progress, still doesn't connect tho.
e
s 00080/00026/00273
d D 7.6 92/11/05 13:48:54 sklower 6 5
c checkpoint somewhat working checksum code . . .
e
s 00035/00023/00264
d D 7.5 92/11/05 07:12:58 sklower 5 4
c checkpoint, doesn't do checksum right yet
e
s 00064/00058/00223
d D 7.4 92/10/15 18:51:31 sklower 4 3
c this version compiles and matches current #include convention
e
s 00049/00018/00232
d D 7.3 92/10/09 03:26:18 sklower 3 2
c have to worry about tcp_respond when there is no tcpcb
e
s 00004/00005/00246
d D 7.2 92/10/09 01:08:02 sklower 2 1
c correct defective copyright dates
e
s 00251/00000/00000
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
 * Copyright (c) 1982, 1986, 1988, 1990 Regents of the University of California.
E 2
I 2
D 12
 * Copyright (c) 1992 Regents of the University of California.
E 12
I 12
D 13
 * Copyright (c) 1992, 1993 Regents of the University of California.
E 12
E 2
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 4
#include "param.h"
#include "proc.h"
#include "systm.h"
#include "malloc.h"
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "protosw.h"
#include "errno.h"
E 4
I 4
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/systm.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/protosw.h>
#include <sys/errno.h>
E 4

D 4
#include "../net/route.h"
#include "../net/if.h"
E 4
I 4
#include <net/route.h>
#include <net/if.h>
E 4

D 4
#include "in.h"
#include "in_systm.h"
#include "ip.h"
#include "in_pcb.h"
#include "ip_var.h"
#include "ip_icmp.h"
#include "tcp.h"
#include "tcp_fsm.h"
#include "tcp_seq.h"
#include "tcp_timer.h"
#include "tcp_var.h"
#include "tcpip.h"
E 4
I 4
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/in_pcb.h>
#include <netinet/ip_var.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcpip.h>
#include <netinet/tcp_debug.h>
E 4

D 4
#include "netiso/argo_debug.h"
#include "netiso/iso.h"
#include "netiso/clnp.h"
#include "netiso/iso_pcb.h"
#include "netiso/iso_var.h"
E 4
I 4
#include <netiso/argo_debug.h>
#include <netiso/iso.h>
#include <netiso/clnp.h>
#include <netiso/iso_pcb.h>
#include <netiso/iso_var.h>
D 5
#include <netiso/tuba_addr.h>
E 5
I 5
#include <netiso/tuba_table.h>
E 5
E 4

D 4
#include "tuba_addr.h"
I 3
static struct sockaddr_iso null_siso = { sizeof(null_siso), AF_ISO, };
E 4
I 4
D 7
static struct	sockaddr_iso null_siso = { sizeof(null_siso), AF_ISO, };
extern struct	isopcb tuba_isopcb;
extern int	tuba_table_size;
extern int	tcppcbcachemiss, tcppredack, tcppreddat, tcprexmtthresh;
extern struct 	inpcb *tcp_last_inpcb;
extern struct	tcpiphdr tcp_saveti;
E 7
I 7
static	struct	sockaddr_iso null_siso = { sizeof(null_siso), AF_ISO, };
D 8
extern	int	tuba_table_size;
E 8
I 8
extern	int	tuba_table_size, tcp_keepidle, tcp_keepintvl, tcp_maxidle;
E 8
extern	int	tcppcbcachemiss, tcppredack, tcppreddat, tcprexmtthresh;
extern	struct	tcpiphdr tcp_saveti;
D 8
struct	inpcb	*tuba_last_inpcb;
E 8
struct	inpcb	tuba_inpcb;
I 8
struct	inpcb	*tuba_last_inpcb = &tuba_inpcb;
E 8
struct	isopcb	tuba_isopcb;
E 7
E 4
E 3
/*
 * Tuba initialization
 */
tuba_init()
{
D 2

	extern struct isopcb tuba_isopcb;

	tuba_isopcb.isop_next = tuba_isopcb.isop_prev = &tuba_isopcb;
E 2
#define TUBAHDRSIZE (3 /*LLC*/ + 9 /*CLNP Fixed*/ + 42 /*Addresses*/ \
		     + 6 /*CLNP Segment*/ + 20 /*TCP*/)
I 2
D 4
	extern struct isopcb tuba_isopcb;
E 4
E 2

I 7
	tuba_inpcb.inp_next = tuba_inpcb.inp_prev = &tuba_inpcb;
E 7
I 2
	tuba_isopcb.isop_next = tuba_isopcb.isop_prev = &tuba_isopcb;
I 3
D 4
	tuba_isopcb.isop_faddr = &tuba_isop.isop_sfaddr;
	tuba_isopcb.isop_laddr = &tuba_isop.isop_sladdr;
E 4
I 4
	tuba_isopcb.isop_faddr = &tuba_isopcb.isop_sfaddr;
	tuba_isopcb.isop_laddr = &tuba_isopcb.isop_sladdr;
E 4
E 3
E 2
	if (max_protohdr < TUBAHDRSIZE)
		max_protohdr = TUBAHDRSIZE;
	if (max_linkhdr + TUBAHDRSIZE > MHLEN)
		panic("tuba_init");
I 2
D 4
	tuba_timer_init();
E 4
I 4
D 5
	tuba_table_init();
E 5
E 4
E 2
}

I 9
struct addr_arg {
	int	error;
	int	offset;
	u_long	sum;
};

I 10
/*
 * Calculate contribution to fudge factor for TCP checksum,
 * and coincidentally set pointer for convenience of clnp_output
 * if we are are responding when there is no isopcb around.
 */
E 10
E 9
D 3
tuba_output(tp, m)
	struct tcpcb *tp;
E 3
I 3
static void
D 9
tuba_getaddr(error, sum, siso, index)
	int *error;
D 5
	u_long *sum;
E 5
I 5
	register u_long *sum;
E 9
I 9
tuba_getaddr(arg, siso, index)
	register struct addr_arg *arg;
E 9
E 5
D 8
	struct sockaddr_iso *siso;
E 8
I 8
	struct sockaddr_iso **siso;
E 8
	u_long index;
{
	register struct tuba_cache *tc;
D 5
	if (index < tuba_table_size && (tc = tuba_table[index])) {
E 5
I 5
	if (index <= tuba_table_size && (tc = tuba_table[index])) {
E 5
D 8
		if (siso) {
			*siso = null_siso;
			siso->siso_addr = tc->tc_addr;
		}
E 8
I 8
		if (siso)
			*siso = &tc->tc_siso;
E 8
D 4
		sum += tc->tc_sum_out
E 4
I 4
D 5
		sum += tc->tc_sum_out;
E 5
I 5
D 9
		REDUCE(*sum, *sum + tc->tc_sum_out);
E 9
I 9
D 10
		arg->sum += (arg->offset & 1 ? tc->tc_ssum_d : tc->tc_sum_d);
E 10
I 10
		arg->sum += (arg->offset & 1 ? tc->tc_ssum : tc->tc_sum)
				+ (0xffff ^ index);
E 10
		arg->offset += tc->tc_siso.siso_nlen + 1;
E 9
E 5
E 4
	} else
D 9
		*error = 1;
E 9
I 9
		arg->error = 1;
E 9
}
I 6
D 7
int tuba_noisy = 1;
E 7
E 6

tuba_output(m, tp)
E 3
	register struct mbuf *m;
I 3
	struct tcpcb *tp;
E 3
{
D 3
	struct isopcb *isop = (struct isopcb *)tp->t_tuba_pcb;
	register struct tcpiphdr *n = tp->tp_template;
E 3
I 3
D 9
	struct isopcb *isop;
E 9
D 6
	register struct tcpiphdr *n;
	u_long sum, i;
E 6
I 6
D 7
	register struct tcpiphdr *n, *h;
	struct mbuf *p = m_gethdr(M_DONTWAIT, MT_DATA);
	u_long sum = 0, i = 0, k1, k2, k3, k4, k5, lindex, findex, len;
E 7
I 7
	register struct tcpiphdr *n;
D 9
	u_long sum, i;
E 9
I 9
	struct	isopcb *isop;
	struct	addr_arg arg;
E 9
E 7
E 6
E 3

I 6
D 7
	if ((m->m_flags & M_PKTHDR) == 0)
		panic("tuba_output");
	if (p == 0)
		panic("tuba_output 2");
	m = m_pullup(m, 40);
	if (m == 0) {
		printf("heisenberg hit us\n");
		(void)m_free(p);
		return (ENOBUFS);
	}
	n = mtod(m, struct tcpiphdr *);
	h = mtod(p, struct tcpiphdr *);
	lindex = n->ti_src.s_addr;
	findex = n->ti_dst.s_addr;
	len = m->m_pkthdr.len;
	bzero((caddr_t)h, sizeof(*h));
	h->ti_pr = ISOPROTO_TCP;
	h->ti_dst.s_addr = findex;
	h->ti_src.s_addr = lindex;
	h->ti_len = htons((u_short)len - 20);
	m->m_data += 20;
	m->m_len -= 20;
	k1 = in_cksum(m, len - 20);
	p->m_len = 20;
	p->m_next = m;
	k2 = in_cksum(p, 20);
	k3 = in_cksum(p, len);
	m->m_data -= 20;
	m->m_len += 20;

	if (tuba_noisy) {
		printf("old ti_sum is 0x%x\n", n->ti_sum);
		printf("in_cksum for old TCP part is 0x%x\n", k1);
		printf("in_cksum for ph(idx) is 0x%x\n", k2);
		printf("in_cksum for ph + TCP is 0x%x\n", k3);
	}
E 7
E 6
I 3
D 4
	if (tp == 0 || (n = tp->tp_template) == 0) {
E 4
I 4
D 5
	if (tp == 0 || (n = tp->t_template) == 0) {
E 5
I 5
	if (tp == 0 || (n = tp->t_template) == 0 || 
	    (isop = (struct isopcb *)tp->t_tuba_pcb) == 0) {
E 5
E 4
		isop = &tuba_isopcb;
D 5
		i = sum = 0;
E 5
		n = mtod(m, struct tcpiphdr *);
I 5
D 6
		i = sum = 0;
E 5
D 4
		tuba_getaddr(&i, &sum, tuba_isop.isop_faddr, n->ti_dst.s_addr);
		tuba_getaddr(&i, &sum, tuba_isop.isop_laddr, n->ti_src.s_addr);
E 4
I 4
		tuba_getaddr(&i, &sum, tuba_isopcb.isop_faddr,
				n->ti_dst.s_addr);
		tuba_getaddr(&i, &sum, tuba_isopcb.isop_laddr,
				n->ti_src.s_addr);
E 6
I 6
D 7
		tuba_getaddr(&i, &sum, tuba_isopcb.isop_faddr, findex);
		tuba_getaddr(&i, &sum, tuba_isopcb.isop_laddr, lindex);
E 7
I 7
D 9
		i = sum = 0;
D 8
		tuba_getaddr(&i, &sum, tuba_isopcb.isop_faddr,
E 8
I 8
		tuba_getaddr(&i, &sum, &tuba_isopcb.isop_faddr,
E 8
				n->ti_dst.s_addr);
D 8
		tuba_getaddr(&i, &sum, tuba_isopcb.isop_laddr,
E 8
I 8
		tuba_getaddr(&i, &sum, &tuba_isopcb.isop_laddr,
E 8
				n->ti_src.s_addr);
E 9
I 9
		arg.error = arg.sum = arg.offset = 0;
		tuba_getaddr(&arg, &tuba_isopcb.isop_faddr, n->ti_dst.s_addr);
		tuba_getaddr(&arg, &tuba_isopcb.isop_laddr, n->ti_src.s_addr);
		REDUCE(arg.sum, arg.sum);
E 9
E 7
E 6
E 4
		goto adjust;
	}
D 5
	isop = (struct isopcb *)tp->t_tuba_pcb;
E 5
E 3
D 4
	if (n->ni_sum == 0) {
E 4
I 4
	if (n->ti_sum == 0) {
E 4
D 3
		register struct inpcb *inp = tp->tp_inpcb;
		register struct tuba_cache *tc;
		u_long cksum_fixup;

		if ((tc = tuba_table[inp->in_faddr.s_addr]) == 0)
			return (ENOBUFS);
		cksum_fixup = tc->tc_sum_out; /* includes -index */
		if ((tc = tuba_table[inp->in_laddr.s_addr]) == 0)
			return (ENOBUFS);
		ICKSUM(cksum_fixup, cksum_fixup + tc->tc_sum_out);
		n->ti_sum = cksum_fixup;
E 3
I 3
D 6
		i = sum = 0;
		tuba_getaddr(&i, &sum, (struct sockaddr_iso *)0,
				n->ti_dst.s_addr);
		tuba_getaddr(&i, &sum, (struct sockaddr_iso *)0,
				n->ti_src.s_addr);
E 6
I 6
D 7
		tuba_getaddr(&i, &sum, (struct sockaddr_iso *)0, findex);
		tuba_getaddr(&i, &sum, (struct sockaddr_iso *)0, lindex);
E 7
I 7
D 9
		i = sum = 0;
D 8
		tuba_getaddr(&i, &sum, (struct sockaddr_iso *)0,
E 8
I 8
		tuba_getaddr(&i, &sum, (struct sockaddr_iso **)0,
E 8
				n->ti_dst.s_addr);
D 8
		tuba_getaddr(&i, &sum, (struct sockaddr_iso *)0,
E 8
I 8
		tuba_getaddr(&i, &sum, (struct sockaddr_iso **)0,
E 8
				n->ti_src.s_addr);
E 7
E 6
D 5
		ICKSUM(sum, sum);
E 5
		n->ti_sum = sum;
E 9
I 9
		arg.error = arg.sum = arg.offset = 0;
		tuba_getaddr(&arg, (struct sockaddr_iso **)0, n->ti_dst.s_addr);
		tuba_getaddr(&arg, (struct sockaddr_iso **)0, n->ti_src.s_addr);
		REDUCE(arg.sum, arg.sum);
		n->ti_sum = arg.sum;
E 9
E 3
		n = mtod(m, struct tcpiphdr *);
D 3
		ICKSUM(n->ti_sum, cksum_fixup + n->ti_sum);
E 3
I 3
	adjust:
D 9
		if (i) {
E 9
I 9
		if (arg.error) {
E 9
			m_freem(m);
I 6
D 7
			(void)m_free(p);
E 7
E 6
D 5
			return (ENOBUFS);
E 5
I 5
			return (EADDRNOTAVAIL);
E 5
		}
D 5
		ICKSUM(n->ti_sum, sum + n->ti_sum);
E 5
I 5
D 9
		REDUCE(n->ti_sum, n->ti_sum + (0xffff ^ sum));
E 9
I 9
		REDUCE(n->ti_sum, n->ti_sum + (0xffff ^ arg.sum));
E 9
E 5
E 3
	}
I 6
D 7
	h->ti_dst.s_addr = tuba_table[findex]->tc_sum_in;
	h->ti_src.s_addr = tuba_table[lindex]->tc_sum_in;
E 7
E 6
	m->m_len -= sizeof (struct ip);
	m->m_pkthdr.len -= sizeof (struct ip);
	m->m_data += sizeof (struct ip);
I 6
D 7
	k1 = in_cksum(m, len - 20);
	k2 = in_cksum(p, 20);
	k3 = in_cksum(p, len);
	REDUCE(k4, h->ti_dst.s_addr + h->ti_src.s_addr + h->ti_len 
			+ ntohs((u_short)ISOPROTO_TCP) + (0xffff ^ k1));
	k4 = 0xffff ^ k4;
	if (tuba_noisy) {
		printf("new ti_sum is 0x%x\n", n->ti_sum);
		printf("adjustment is 0x%x\n", sum);
		printf("in_cksum for new TCP part is 0x%x\n", k1);
		printf("in_cksum for ph(EIDSUM) is 0x%x\n", k2);
		printf("in_cksum for ph + TCP is 0x%x\n", k3);
		printf("calculated in the funky way is 0x%x\n", k4);
	}
	(void)m_free(p);
E 7
E 6
D 8
	return (clnp_output(m, isop, m->m_pkthdr.len, 0));
E 8
I 8
D 9
	i = clnp_output(m, isop, m->m_pkthdr.len, 0);
	return (i);
E 9
I 9
	return (clnp_output(m, isop, m->m_pkthdr.len, 0));
E 9
E 8
}

I 7
D 8

E 8
E 7
tuba_refcnt(isop, delta)
	struct isopcb *isop;
{
	register struct tuba_cache *tc;
D 3
	unsigned index;
E 3
I 3
	unsigned index, sum;
E 3

	if (delta != 1)
		delta = -1;
	if (isop == 0 || isop->isop_faddr == 0 || isop->isop_laddr == 0 ||
	    (delta == -1 && isop->isop_tuba_cached == 0) ||
	    (delta == 1 && isop->isop_tuba_cached != 0))
		return;
	isop->isop_tuba_cached = (delta == 1);
D 4
	if ((index = tuba_lookup(&isop->isop_faddr.siso_addr)) != 0 &&
	    (tc = tuba_cache[index]) != 0 && (delta == 1 || tc->tc_refcnt > 0))
E 4
I 4
D 5
	if ((index = tuba_lookup(&isop->isop_sfaddr.siso_addr)) != 0 &&
E 5
I 5
D 11
	if ((index = tuba_lookup(&isop->isop_sfaddr.siso_addr, M_DONTWAIT)) != 0 &&
E 11
I 11
	if ((index = tuba_lookup(isop->isop_faddr, M_DONTWAIT)) != 0 &&
E 11
E 5
	    (tc = tuba_table[index]) != 0 && (delta == 1 || tc->tc_refcnt > 0))
E 4
		tc->tc_refcnt += delta;
D 4
	if ((index = tuba_lookup(&isop->isop_laddr.siso_addr)) != 0 &&
	    (tc = tuba_cache[index]) != 0 && (delta == 1 || tc->tc_refcnt > 0))
E 4
I 4
D 5
	if ((index = tuba_lookup(&isop->isop_sladdr.siso_addr)) != 0 &&
E 5
I 5
D 11
	if ((index = tuba_lookup(&isop->isop_sladdr.siso_addr, M_DONTWAIT)) != 0 &&
E 11
I 11
	if ((index = tuba_lookup(isop->isop_laddr, M_DONTWAIT)) != 0 &&
E 11
E 5
	    (tc = tuba_table[index]) != 0 && (delta == 1 || tc->tc_refcnt > 0))
E 4
		tc->tc_refcnt += delta;
}

tuba_pcbdetach(isop)
	struct isopcb *isop;
{
	if (isop == 0)
		return;
	tuba_refcnt(isop, -1);
	isop->isop_socket = 0;
	iso_pcbdetach(isop);
}

D 3
static struct sockaddr_iso null_siso = { sizeof(null_siso), AF_ISO, };
E 3
/*
 * Avoid  in_pcbconnect in faked out tcp_input()
 */
tuba_pcbconnect(inp, nam)
	register struct inpcb *inp;
	struct mbuf *nam;
{
D 4
	register struct sockaddr_iso *siso = mtod(m, struct sockaddr_iso *);
	struct sockaddr_in *sin = mtod(m, struct sockaddr_in *);
E 4
I 4
D 11
	register struct sockaddr_iso *siso = mtod(nam, struct sockaddr_iso *);
E 11
I 11
	register struct sockaddr_iso *siso;
E 11
	struct sockaddr_in *sin = mtod(nam, struct sockaddr_in *);
E 4
	struct tcpcb *tp = intotcpcb(inp);
D 11
	unsigned index = sin->sin_addr.s_addr;
	struct tuba_cache *tc = tuba_table[index];
E 11
D 4
	struct isopcb *isop = (struct isopcb *)tp->tp_tuba_pcb;
E 4
I 4
	struct isopcb *isop = (struct isopcb *)tp->t_tuba_pcb;
E 4
	int error;

D 11
	inp->inp_faddr.s_addr = index;
E 11
I 11
	/* hardwire iso_pcbbind() here */
	siso = isop->isop_laddr = &isop->isop_sladdr;
	*siso = tuba_table[inp->inp_laddr.s_addr]->tc_siso;
	siso->siso_tlen = sizeof(inp->inp_lport);
	bcopy((caddr_t)&inp->inp_lport, TSEL(siso), sizeof(inp->inp_lport));

	/* hardwire in_pcbconnect() here without assigning route */
E 11
	inp->inp_fport = sin->sin_port;
D 8
	*siso = null_siso;
	siso->siso_addr = tc->tc_addr;
E 8
I 8
D 11
	*siso = tc->tc_siso;
E 11
I 11
	inp->inp_faddr = sin->sin_addr;

	/* reuse nam argument to call iso_pcbconnect() */
	nam->m_len = sizeof(*siso);
	siso = mtod(nam, struct sockaddr_iso *);
	*siso = tuba_table[inp->inp_faddr.s_addr]->tc_siso;
E 11
E 8
	siso->siso_tlen = sizeof(inp->inp_fport);
	bcopy((caddr_t)&inp->inp_fport, TSEL(siso), sizeof(inp->inp_fport));
D 11
	nam->m_len = sizeof(*siso);
E 11
I 11

E 11
	if ((error = iso_pcbconnect(isop, nam)) == 0)
		tuba_refcnt(isop, 1);
	return (error);
}

I 5
D 7
tuba_badcksum() {} /* XXX - to set breakpoints */

E 7
E 5
/*
 * CALLED FROM:
 * 	clnp's input routine, indirectly through the protosw.
 * FUNCTION and ARGUMENTS:
D 4
 * Take a packet (m) from clnp, strip off the clnp header and give it to tcp
 * or udp.
E 4
I 4
 * Take a packet (m) from clnp, strip off the clnp header
 * and do tcp input processing.
E 4
 * No return value.  
 */
D 4
ProtoHook
tpclnp_input(m, src, dst, clnp_len, ce_bit)
E 4
I 4
D 10
tuba_tcpinput(m, src, dst, clnp_len, ce_bit)
E 10
I 10
tuba_tcpinput(m, src, dst)
E 10
E 4
	register struct mbuf *m;
	struct sockaddr_iso *src, *dst;
D 10
	int clnp_len, ce_bit;
E 10
{
D 8
	int s = splnet();
E 8
D 4
	unsigned long fix_csum, lindex, findex;
E 4
I 4
D 5
	unsigned long fix_cksum, lindex, findex;
E 5
I 5
	unsigned long sum, lindex, findex;
E 5
E 4
	register struct tcpiphdr *ti;
	register struct inpcb *inp;
D 5
	struct mbuf *om = 0;
E 5
I 5
D 11
	struct mbuf *om;
E 11
I 11
D 12
	struct mbuf *om = 0;
E 12
I 12
	caddr_t optp = NULL;
	int optlen;
E 12
E 11
E 5
	int len, tlen, off;
	register struct tcpcb *tp = 0;
	int tiflags;
	struct socket *so;
	int todrop, acked, ourfinisacked, needoutput = 0;
	short ostate;
	struct in_addr laddr;
	int dropsocket = 0, iss = 0;
I 12
	u_long tiwin, ts_val, ts_ecr;
	int ts_present = 0;
E 12

D 5
	if ((m->m_flags & M_PKTHDR) == 0)
		panic("tuba_input");
E 5
I 5
D 10
	if ((m->m_flags & M_PKTHDR) == 0) {
		om = m_gethdr(M_DONTWAIT, MT_DATA);
		if (om == 0)
			goto drop;
		om->m_next = m;
D 6
	} else
		om = m;
	for (len = 0; m; m = m->m_next)
		len += m->m_len;
	m = om;
E 6
I 6
		for (len = 0; m; m = m->m_next)
			len += m->m_len;
		m = om;
		m->m_pkthdr.len = len;
	}
E 6
	om = 0;
E 10
I 10
	if ((m->m_flags & M_PKTHDR) == 0)
		panic("tuba_tcpinput");
E 10
D 6
	m->m_pkthdr.len = len;
E 6
E 5
	/*
	 * Do some housekeeping looking up CLNP addresses.
	 * If we are out of space might as well drop the packet now.
	 */
	tcpstat.tcps_rcvtotal++;
D 4
	if ((lindex = tuba_lookup(&dst->siso_addr) == 0 ||
E 4
I 4
D 5
	if ((lindex = tuba_lookup(&dst->siso_addr) == 0) ||
E 4
	    (findex = tuba_lookup(&dst->siso_addr) == 0))
E 5
I 5
D 11
	lindex = tuba_lookup(&dst->siso_addr, M_DONTWAIT);
D 9
	findex = tuba_lookup(&dst->siso_addr, M_DONTWAIT);
E 9
I 9
	findex = tuba_lookup(&src->siso_addr, M_DONTWAIT);
E 11
I 11
	lindex = tuba_lookup(dst, M_DONTWAIT);
	findex = tuba_lookup(src, M_DONTWAIT);
E 11
E 9
	if (lindex == 0 || findex == 0)
E 5
		goto drop;
	/*
D 10
	 * Get CLNP and TCP header together in first mbuf.
E 10
	 * CLNP gave us an mbuf chain WITH the clnp header pulled up,
D 10
	 * and the length of the clnp header.
E 10
I 10
	 * but the data pointer pushed past it.
E 10
	 */
D 10
	len = clnp_len + sizeof(struct tcphdr);
	if (m->m_len < len) {
		if ((m = m_pullup(m, len)) == 0) {
			tcpstat.tcps_rcvshort++;
			return;
		}
	}
	/*
	 * Calculate checksum of extended TCP header and data,
	 * by adjusting the checksum for missing parts of the header.
	 */
	m->m_data += clnp_len;
	m->m_len -= clnp_len;
	tlen = m->m_pkthdr.len -= clnp_len;
E 10
I 10
	len = m->m_len;
	tlen = m->m_pkthdr.len;
E 10
D 5
	ICKSUM(fix_cksum, tuba_table[findex]->tc_sum_in + htons((u_short)tlen)
E 5
I 5
D 6
	REDUCE(sum, tuba_table[findex]->tc_sum_in + htons((u_short)tlen)
		+ htons((u_short)ISOPROTO_TCP)
E 5
		+ tuba_table[lindex]->tc_sum_in + in_cksum(m, tlen));
D 5
	if (fix_cksum != 0xffff) {
E 5
I 5
	if (sum) {
E 5
		tcpstat.tcps_rcvbadsum++;
I 5
		tuba_badcksum();
E 5
		goto drop;
	}
E 6
	m->m_data -= sizeof(struct ip);
	m->m_len += sizeof(struct ip);
	m->m_pkthdr.len += sizeof(struct ip);
I 11
	m->m_flags &= ~(M_MCAST|M_BCAST); /* XXX should do this in clnp_input */
E 11
	/*
	 * The reassembly code assumes it will be overwriting a useless
D 5
	 * part of the packet, which is why we need to have ti point
E 5
I 5
	 * part of the packet, which is why we need to have it point
E 5
	 * into the packet itself.
	 *
	 * Check to see if the data is properly alligned
	 * so that we can save copying the tcp header.
	 * This code knows way too much about the structure of mbufs!
	 */
D 4
	off = ((sizeof (long) - 1) & ((m->m_flags & EXT) ?
		(m->m_data - m->m_ext.ext_buf) :  (m->m_data - m_pktdat)));
E 4
I 4
	off = ((sizeof (long) - 1) & ((m->m_flags & M_EXT) ?
		(m->m_data - m->m_ext.ext_buf) :  (m->m_data - m->m_pktdat)));
E 4
D 10
	if (off) {
D 4
		struct mbuf *m0 = m_gethdr(M_DONTWAIT, MT_DATA)
E 4
I 4
		struct mbuf *m0 = m_gethdr(M_DONTWAIT, MT_DATA);
E 4
		if (m0 == 0) {
E 10
I 10
	if (off || len < sizeof(struct tcphdr)) {
		struct mbuf *m0 = m;

		MGETHDR(m, M_DONTWAIT, MT_DATA);
		if (m == 0) { 
			m = m0;
E 10
			goto drop;
		}
I 6
D 10
		m0->m_data += max_linkhdr;
E 6
		bcopy(mtod(m, caddr_t) + sizeof(struct ip),
		      mtod(m0, caddr_t) + sizeof(struct ip),
		      sizeof(struct tcphdr));
		m->m_data += sizeof(struct tcpiphdr);
I 8
		m->m_len -= sizeof(struct tcpiphdr);
E 8
		m0->m_next = m;
		m0->m_pkthdr = m->m_pkthdr;
D 4
		m0->m_flags = m->m_pkthdr & M_COPYFLAGS;
E 4
I 4
		m0->m_flags = m->m_flags & M_COPYFLAGS;
E 4
		m0->m_len = sizeof(struct tcpiphdr);
		m = m0;
E 10
I 10
		m->m_next = m0;
		m->m_data += max_linkhdr;
D 11
		m->m_pkthdr = m->m_pkthdr;
		m->m_flags = m->m_flags & M_COPYFLAGS;
E 11
I 11
		m->m_pkthdr = m0->m_pkthdr;
		m->m_flags = m0->m_flags & M_COPYFLAGS;
E 11
		if (len < sizeof(struct tcphdr)) {
I 11
			m->m_len = 0;
E 11
			if ((m = m_pullup(m, sizeof(struct tcpiphdr))) == 0) {
				tcpstat.tcps_rcvshort++;
				return;
			}
		} else {
D 11
			bcopy(mtod(m, caddr_t) + sizeof(struct ip),
			      mtod(m0, caddr_t) + sizeof(struct ip),
E 11
I 11
			bcopy(mtod(m0, caddr_t) + sizeof(struct ip),
			      mtod(m, caddr_t) + sizeof(struct ip),
E 11
			      sizeof(struct tcphdr));
			m0->m_len -= sizeof(struct tcpiphdr);
			m0->m_data += sizeof(struct tcpiphdr);
			m->m_len = sizeof(struct tcpiphdr);
		}
E 10
	}
I 10
	/*
	 * Calculate checksum of extended TCP header and data,
	 * replacing what would have been IP addresses by
	 * the IP checksum of the CLNP addresses.
	 */
E 10
	ti = mtod(m, struct tcpiphdr *);
I 6
D 9
	ti->ti_src.s_addr = tuba_table[findex]->tc_sum_in;
	ti->ti_dst.s_addr = tuba_table[lindex]->tc_sum_in;
E 9
I 9
	ti->ti_dst.s_addr = tuba_table[lindex]->tc_sum;
	if (dst->siso_nlen & 1)
		ti->ti_src.s_addr = tuba_table[findex]->tc_sum;
	else
		ti->ti_src.s_addr = tuba_table[findex]->tc_ssum;
E 9
	ti->ti_prev = ti->ti_next = 0;
	ti->ti_x1 = 0; ti->ti_pr = ISOPROTO_TCP;
	ti->ti_len = htons((u_short)tlen);
	if (ti->ti_sum = in_cksum(m, m->m_pkthdr.len)) {
		tcpstat.tcps_rcvbadsum++;
D 7
		tuba_badcksum();
E 7
		goto drop;
	}
D 7
	if (tuba_noisy)
		printf("Hurray!\n");
E 7
E 6
	ti->ti_src.s_addr = findex;
	ti->ti_dst.s_addr = lindex;
D 5
	ti->ti_len = tlen;
E 5
	/*
	 * Now include the rest of TCP input
	 */
D 4
#define TUBA_INPUT
E 4
I 4
#define TUBA_INCLUDE
E 4
D 7
#define in_pcbconnect	tuba_pcbconnect
E 7
I 7
#define	in_pcbconnect	tuba_pcbconnect
#define	tcb		tuba_inpcb
#define tcp_last_inpcb	tuba_last_inpcb
E 7

D 4
#include "../netinet/tcp_input.c"
E 4
I 4
#include <netinet/tcp_input.c>
E 4
}
I 8

#define tcp_slowtimo	tuba_slowtimo
#define tcp_fasttimo	tuba_fasttimo
I 10

E 10
#include <netinet/tcp_timer.c>
E 8
E 1
