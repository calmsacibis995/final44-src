h01257
s 00002/00002/00667
d D 8.1 93/06/11 14:56:55 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00011/00667
d D 7.7 93/03/09 23:41:23 utashiro 7 6
c 
e
s 00027/00027/00651
d D 7.6 92/12/17 02:56:39 utashiro 6 5
c make kernel includes standard
e
s 00004/00001/00674
d D 7.5 92/07/01 02:46:42 utashiro 5 4
c enclose start routine by splclock().
c This is because of some bug in clock handler.  Should be gone soon.
e
s 00008/00001/00667
d D 7.4 92/06/27 14:46:24 utashiro 4 3
c use bxcopy() to copy data to mbufs.
e
s 00017/00026/00651
d D 7.3 92/06/27 03:58:31 utashiro 3 2
c make bpf works
e
s 00001/00003/00676
d D 7.2 92/06/25 18:47:11 utashiro 2 1
c removed enoutput() declaration
e
s 00679/00000/00000
d D 7.1 92/06/04 15:59:10 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: if_en.c,v 4.300 91/06/09 06:25:54 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

#include "en.h"
#include "rawether.h"
#include "bpfilter.h"

#if NEN > 0

/*
 * Interlan Ethernet Communications Controller interface
 */
D 6
#include "types.h"
#include "../include/fix_machine_type.h"
#include "../include/pte.h"
E 6
I 6
#include <sys/types.h>
D 7
#include <machine/fix_machine_type.h>
E 7
#include <machine/pte.h>
E 6

D 6
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "buf.h"
#include "protosw.h"
#include "socket.h"
#include "ioctl.h"
#include "errno.h"
#include "time.h"
#include "cdefs.h"
E 6
I 6
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/cdefs.h>
E 6

D 6
#include "net/if.h"
#include "net/netisr.h"
#include "net/route.h"
E 6
I 6
#include <net/if.h>
#include <net/netisr.h>
#include <net/route.h>
E 6

#ifdef INET
D 6
#include "netinet/in.h"
#include "netinet/in_systm.h"
#include "netinet/in_var.h"
#include "netinet/ip.h"
#include "netinet/if_ether.h"
E 6
I 6
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
E 6
#endif

D 6
#include "../if/if_news.h"
#include "../if/if_en.h"
E 6
I 6
#include <news3400/if/if_news.h>
#include <news3400/if/if_en.h>
E 6

#ifdef CPU_SINGLE
D 6
#include "../hbdev/hbvar.h"
E 6
I 6
#include <news3400/hbdev/hbvar.h>
E 6
#define	iop_device	hb_device
#define	iop_driver	hb_driver
#define	ii_unit		hi_unit
#define	ii_intr		hi_intr
#define	ii_alive	hi_alive
#else
D 6
#include "../iop/iopvar.h"
E 6
I 6
#include <news3400/iop/iopvar.h>
E 6
#endif

int	enprobe(), enattach(), enrint(), enxint();
struct	mbuf *m_devget();

#ifdef CPU_SINGLE
struct	hb_device *eninfo[NEN];
struct	hb_driver endriver = { enprobe, 0, enattach, 0, 0, "en", eninfo };
#else
struct	iop_device *eninfo[NEN];
struct	iop_driver endriver = { enprobe, 0, enattach, 0, "en", eninfo };
#endif

#define	ENUNIT(x)	minor(x)

D 2
int	eninit(),enoutput(),enioctl(),enreset(),enwatch(),enstart();
E 2
I 2
int	eninit(),enioctl(),enreset(),enwatch(),enstart();
E 2
int	endebug = 0;

struct ether_addr {
	u_char	addr[6];
};

extern struct ifnet loif;

struct en_softc en_softc[NEN];
D 3
struct ether_addr myether[NEN];
E 3

#if NBPFILTER > 0
D 6
#include "../net/bpf.h"
E 6
I 6
#include <net/bpf.h>
E 6
D 3
caddr_t	en_bpf[NEN];
E 3
#endif

enprobe(ii)
	struct iop_device *ii;
{

	return (en_probe(ii));
}

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.  A STATUS command is done to get the ethernet
 * address and other interesting data.
 */
enattach(ii)
	register struct iop_device *ii;
{
	register struct en_softc *es = &en_softc[ii->ii_unit];
	register struct ifnet *ifp = &es->es_if;
	extern char *ether_sprintf();

	en_attach(ii->ii_unit);
D 3
	bcopy((caddr_t)es->es_addr, &myether[ii->ii_unit],
		sizeof(struct ether_addr));
E 3
	printf("en%d: hardware address %s\n",
		ii->ii_unit, ether_sprintf((u_char *)es->es_addr));
	ifp->if_unit = ii->ii_unit;
	ifp->if_name = "en";
	ifp->if_mtu = ETHERMTU;
	ifp->if_init = eninit;
	ifp->if_ioctl = enioctl;
	ifp->if_output = ether_output;
#ifdef NOTDEF /* KU:XXX if_reset is obsolete */
	ifp->if_reset = enreset;
#endif
	ifp->if_start = enstart;
D 3
	ifp->if_flags = IFF_BROADCAST;
E 3
I 3
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX;
E 3
#if NBPFILTER > 0
D 3
	{
		static struct bpf_devp dev =
			{ DLT_EN10MB, sizeof(struct ether_header) };

		bpfattach(&en_bpf[ii->ii_unit], ifp, &dev);
	}
E 3
I 3
	bpfattach(&es->es_bpf, ifp, DLT_EN10MB, sizeof(struct ether_header));
E 3
#endif
	if_attach(ifp);
}

/*
 * Reset of interface after IOP reset.
 */
enreset(unit)
	int unit;
{
	register struct iop_device *ii;

	if (unit >= NEN || (ii = eninfo[unit]) == 0 || ii->ii_alive == 0)
		return;
	printf(" en%d", unit);
	en_softc[unit].es_if.if_flags &= ~(IFF_RUNNING|IFF_OACTIVE);
	en_softc[unit].es_flags &= ~ENF_RUNNING;
	eninit(unit);
}

/*
 * Initialization of interface; clear recorded pending
 * operations, and reinitialize IOP usage.
 */
eninit(unit)
	int unit;
{
	register struct en_softc *es = &en_softc[unit];
	register struct ifnet *ifp = &es->es_if;
	int s;

	/* not yet, if address still unknown */
	if (ifp->if_addrlist == (struct ifaddr *)0)
		return;
	if (es->es_flags & ENF_RUNNING)
		return;
	if ((ifp->if_flags & IFF_RUNNING) == 0) {
		if (if_newsinit(&es->es_ifnews,
		    sizeof (struct en_rheader), (int)btoc(ETHERMTU)) == 0) { 
			printf("en%d: can't initialize\n", unit);
			es->es_if.if_flags &= ~IFF_UP;
			return;
		}
		ifp->if_watchdog = enwatch;
		es->es_interval = ENWATCHINTERVAL;
		ifp->if_timer = es->es_interval;
		s = splimp();
		en_init(unit);
		splx(s);
	}
	es->es_if.if_flags |= IFF_RUNNING|IFF_NOTRAILERS;
	es->es_flags |= ENF_RUNNING;
}

/*
 * Start output on interface.
 * Get another datagram to send off of the interface queue,
 * and map it to the interface before starting the output.
 */
enstart(ifp)
	register struct ifnet *ifp;
{
        int unit = ifp->if_unit, len;
	register struct en_softc *es = &en_softc[unit];
	register struct mbuf *m;
I 5
	int s;
E 5

	IF_DEQUEUE(&es->es_if.if_snd, m);
	if (m == 0)
		return(0);
#ifdef CPU_SINGLE
	es->es_ifnews.ifn_waddr = (caddr_t)get_xmit_buffer(unit);
#endif
	len = if_wnewsput(&es->es_ifnews, m);
	/*
	 * Ensure minimum packet length.
	 * This makes the safe assumtion that there are no virtual holes
	 * after the data.
	 * For security, it might be wise to zero out the added bytes,
	 * but we're mainly interested in speed at the moment.
	 */
	if (len - sizeof(struct ether_header) < ETHERMIN)
		len = ETHERMIN + sizeof(struct ether_header);
I 5
	s = splclock();			/* KU:XXX should be gone */
E 5
	en_start(unit, len);
I 5
	es->es_if.if_flags |= IFF_OACTIVE;
	(void) splx(s);			/* KU:XXX */
E 5
#if NBPFILTER > 0
	/*
	 * If bpf is listening on this interface, let it
	 * see the packet before we commit it to the wire.
	 */
D 3
	if (en_bpf[unit]) {
E 3
I 3
	if (es->es_bpf) {
E 3
#ifdef CPU_SINGLE
D 3
		bpf_tap(en_bpf[unit], es->es_ifnews.ifn_waddr, len);
E 3
I 3
		bpf_tap(es->es_bpf, es->es_ifnews.ifn_waddr, len);
E 3
#else
D 3
		bpf_mtap(en_bpf[unit], m);
E 3
I 3
		bpf_mtap(es->es_bpf, m);
E 3
#endif
	}
#endif /* NBPFILTER > 0 */
D 5
	es->es_if.if_flags |= IFF_OACTIVE;
E 5
	return(0);
}

/*
 * Transmit done interrupt.
 */
_enxint(unit, error, collision)
	int unit;
	int error, collision;
{
	register struct en_softc *es = &en_softc[unit];

#ifdef notyet /* KU:XXX */
	intrcnt[INTR_ETHER0 + unit]++;
#endif
	if ((es->es_if.if_flags & IFF_OACTIVE) == 0) {
		printf("en%d: stray xmit interrupt\n", unit);
D 2
/*
E 2
		return;
D 2
*/
E 2
	} else {
		es->es_if.if_flags &= ~IFF_OACTIVE;
		es->es_if.if_opackets++;
	}
D 3
	if (error)
E 3
I 3
D 7
	if (error) {
#ifdef DEBUG
		printf("_enxint: error (unit=%d)\n", unit);
#endif
E 7
I 7
	if (error)
E 7
E 3
		es->es_if.if_oerrors++;
D 3
	if (collision)
E 3
I 3
D 7
	}
	if (collision) {
#ifdef DEBUG
		printf("_enxint: collision (unit=%d)\n", unit);
#endif
E 7
I 7
	if (collision)
E 7
E 3
		es->es_if.if_collisions++;
I 3
D 7
	}
E 7
E 3
	enstart(&es->es_if);
}

/*
 * Ethernet interface receiver interrupt.
 * If input error just drop packet.
 * Otherwise purge input buffered data path and examine 
 * packet to determine type.  If can't determine length
 * from type, then have to drop packet.  Othewise decapsulate
 * packet based on type and pass to type specific higher-level
 * input routine.
 */
_enrint(unit, len)
	int unit;
	register int len;
{
	register struct en_softc *es = &en_softc[unit];
	register struct en_rheader *en;
    	struct mbuf *m;
	int off, resid, s;
D 4
	int	type;
E 4
I 4
	int type;
E 4
	register struct ensw *esp;
	extern struct mbuf *if_rnewsget();
I 4
#if defined(mips) && defined(CPU_SINGLE)
	int bxcopy();
#endif
E 4

#ifdef notyet /* KU:XXX */
	intrcnt[INTR_ETHER0 + unit]++;
#endif
	es->es_if.if_ipackets++;
	if ((es->es_flags & ENF_RUNNING) == 0)
		return;
	en = (struct en_rheader *)(es->es_ifnews.ifn_raddr);
	if (len < ETHERMIN || len > ETHERMTU) {
		es->es_if.if_ierrors++;
		return;
	}
#if NBPFILTER > 0
D 3
#if NRAWETHER > 0
	etherinput(unit, en, len + sizeof(struct en_rheader));
#endif
E 3
	/*
	 * Check if there's a bpf filter listening on this interface.
	 * If so, hand off the raw packet to enet.
	 */
D 3
	if (en_bpf[unit]) {
		bpf_tap(en_bpf[unit], es->es_ifnews.ifn_raddr,
E 3
I 3
	if (es->es_bpf) {
		bpf_tap(es->es_bpf, es->es_ifnews.ifn_raddr,
E 3
			len + sizeof(struct en_rheader));
		/*
		 * Note that the interface cannot be in promiscuous mode if
		 * there are no bpf listeners.	And if we are in promiscuous
		 * mode, we have to check if this packet is really ours.
		 *
		 * XXX This test does not support multicasts.
		 */
		 if ((es->es_if.if_flags & IFF_PROMISC)
		     && bcmp(en->enr_dhost, es->es_addr,
				sizeof(en->enr_dhost)) != 0
		     && bcmp(en->enr_dhost, etherbroadcastaddr,
				sizeof(en->enr_dhost)) != 0)
			return;
	}
D 3
#else /* NBPFILTER > 0 */
#if NRAWETHER > 0
	if (etherinput(unit, en, len + sizeof(struct en_rheader)))
		return;
#endif
E 3
#endif /* NBPFILTER > 0 */
	/*
	 * Deal with trailer protocol: if type is trailer type
	 * get true type from first 16-bit word past data.
	 * Remember that type was trailer by setting off.
	 */
	en->enr_type = ntohs((u_short)en->enr_type);
#define	endataaddr(en, off, type)	((type)(((caddr_t)((en)+1)+(off))))
	if (en->enr_type >= ETHERTYPE_TRAIL &&
	    en->enr_type < ETHERTYPE_TRAIL+ETHERTYPE_NTRAILER) {
		off = (en->enr_type - ETHERTYPE_TRAIL) * 512;
		if (off >= ETHERMTU)
			return;
		en->enr_type = ntohs(*endataaddr(en, off, u_short *));
		resid = ntohs(*(endataaddr(en, off+2, u_short *)));
		if (off + resid > len)
			return;
		len = off + resid;
	} else
		off = 0;
	/*
	 * Pull packet off interface.  Off is nonzero if packet
	 * has trailing header; m_devget will then force this header
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
	 * KU:XXX really?
	 */
	type = en->enr_type;
I 4
#if defined(mips) && defined(CPU_SINGLE)
	m = m_devget((char *)(en + 1), len, off, &es->es_if, bxcopy);
#else
E 4
	m = m_devget((char *)(en + 1), len, off, &es->es_if, 0);
I 4
#endif
E 4
	if (m == 0)
		return;
	ether_input(&es->es_if, (struct ether_header *) en->enr_dhost, m);
}

/*
 * Watchdog routine, request statistics from board.
 */
enwatch(unit)
	int unit;
{
	register struct en_softc *es = &en_softc[unit];
	register struct ifnet *ifp = &es->es_if;

	ifp->if_timer = es->es_interval;
}

/*
 * Process an ioctl request.
 */
enioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
	register struct ifaddr *ifa = (struct ifaddr *)data;
	register struct en_softc *es = &en_softc[ifp->if_unit];
	register struct ensw *esp;
	register int family;
	int s = splimp(), error = 0;

	switch (cmd) {

	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		eninit(ifp->if_unit);
		switch (ifa->ifa_addr->sa_family) {
#ifdef INET
		case AF_INET:
			((struct arpcom *)ifp)->ac_ipaddr =
				IA_SIN(ifa)->sin_addr;
			arpwhohas((struct arpcom *)ifp, &IA_SIN(ifa)->sin_addr);
			break;
#endif
		}
		break;

	case SIOCSIFFLAGS:
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    es->es_flags & ENF_RUNNING) {
			es->es_flags &= ~ENF_RUNNING;
		} else if (ifp->if_flags & IFF_UP &&
		    (es->es_flags & ENF_RUNNING) == 0)
			eninit(ifp->if_unit);
#if NBPFILTER > 0
		else if (ifp->if_flags & IFF_UP &&
		    (ifp->if_flags & IFF_RUNNING) == 0) {
			en_prom_mode(ifp->if_unit,
				ifp->if_flags & IFF_PROMISC);
			ifp->if_flags |= IFF_RUNNING;
		}
#endif
		break;

	default:
		error = EINVAL;
	}
	splx(s);
	return (error);
}

/*
 * set ethernet address for unit
 */
ensetaddr(physaddr, unit)
	u_char *physaddr;
	int unit;
{
	register struct en_softc *es = &en_softc[unit];
	
	if (!(es->es_flags & ENF_RUNNING))
		return;
		
	bcopy((caddr_t)physaddr, (caddr_t)es->es_addr, sizeof es->es_addr);
	es->es_flags &= ~ENF_RUNNING;
	es->es_flags |= ENF_SETADDR;
	eninit(unit);
}

/*
 * Machine dependent functions
 *
 *	en_probe();
 *	en_attach();
 *	en_init();
 *	enxint();
 *	enrint();
 *	en_prom_mode()
 */
#ifdef CPU_SINGLE
D 6
#include "../include/cpu.h"
E 6
I 6
#include <machine/cpu.h>
E 6

en_probe(hi)
	struct hb_device *hi;
{

	return (lance_probe(hi->hi_unit));
}

en_attach(unit)
	int unit;
{
	register struct en_softc *es = &en_softc[unit];
	register u_char *p;
	register int i;
	extern lance_intr();

#if !defined(news700) && !defined(mips)
	register_hb_intr4(lance_intr, unit, eninfo[unit]->ii_intr);
#endif
	if (lance_open(unit) < 0)
		printf("lance initialize error\n");
	lance_get_addr(unit, (caddr_t)es->es_addr);
}

en_init(unit)
	int unit;
{

}

en_start(unit, len)
	int unit;
	int len;
{

	lance_transmit(unit, len);
}

enxint(unit)
	register int unit;
{

	_enxint(unit, lance_xmit_error(unit), lance_collision(unit));
}

enrint(unit)
	register int unit;
{
	register struct en_softc *es = &en_softc[unit];
	caddr_t get_recv_buffer();

	while (es->es_ifnews.ifn_raddr = get_recv_buffer(unit)) {
		_enrint(unit,
		    get_recv_length(unit) - sizeof(struct en_rheader));
		free_recv_buffer(unit);
	}
}

en_prom_mode(unit, mode)
	int unit, mode;
{

	lance_prom_mode(unit, mode);
}
#endif /* CPU_SINGLE */

#ifdef IPC_MRX
#include "../ipc/newsipc.h"
#include "../mrx/h/lancereg.h"
#include "../mrx/h/lance.h"

int	port_enxmit[NEN];
int	port_enrecv[NEN];
int	port_enctrl[NEN];
int	port_enxmit_iop[NEN];
int	port_enrecv_iop[NEN];
int	port_enctrl_iop[NEN];

en_probe(ii)
	register struct iop_device *ii;
{
	int unit = ii->ii_unit;
	int lance_func, *reply;
	char name[32];
	extern char *make_name();

	if (port_enrecv[unit] == 0) {

#define	PT_CREATE(buf, name, unit, func)	\
	port_create(make_name(buf, name, unit), func, unit)
#define	OB_QUERY(buf, name, unit) \
	object_query(make_name(buf, name, unit))

		make_name(name, "@enrecvX", unit);
		port_enrecv[unit] = PT_CREATE(name, "@enrecvX", unit, enrint);
		port_enxmit[unit] = PT_CREATE(name, "@enxmitX", unit, enxint);
		port_enctrl[unit] = PT_CREATE(name, "@enctrlX", unit, NULL);
		/* use NULL action port */
		port_enrecv_iop[unit] = OB_QUERY(name, "lance_inputX", unit);
		port_enxmit_iop[unit] = OB_QUERY(name, "lance_outputX", unit);
		port_enctrl_iop[unit] = OB_QUERY(name, "lance_ctrlX", unit);
	}
	if (port_enctrl_iop[unit] < 0)
		goto bad;
	lance_func = EN_START;
	msg_send(port_enctrl_iop[unit], port_enctrl[unit], &lance_func,
	    sizeof(lance_func), 0);
	msg_recv(port_enctrl[unit], NULL, &reply, NULL, 0);
	if (*reply < 0)
		goto bad;
	lance_func = EN_STOP;
	msg_send(port_enctrl_iop[unit], port_enctrl[unit], &lance_func,
	    sizeof(lance_func), 0);
	msg_recv(port_enctrl[unit], NULL, &reply, NULL, 0);
	return (1);
bad:
	return (0);
}

en_attach(unit)
	int unit;
{
	register struct en_softc *es = &en_softc[unit];
	int lance_func;
	struct ether_addr *ether_addr;

	lance_func = EN_GETADDR;
	msg_send(port_enctrl_iop[unit], port_enctrl[unit], &lance_func,
	    sizeof(lance_func), 0);
	msg_recv(port_enctrl[unit], NULL, &ether_addr, NULL, 0);
	bcopy(ether_addr, es->es_addr, sizeof(struct ether_addr));
	msg_free(port_enctrl[unit]);
}

en_init(unit)
	int unit;
{
	register struct en_softc *es = &en_softc[unit];
	register int port;
	struct lance_ctrl_req req;
	int *reply;

	req.lance_func = EN_SETXMITBUF;
	mapsetup(&req.lance_map, es->es_ifnews.ifn_waddr,
		ETHERMTU + sizeof(struct en_rheader));
	msg_send(port_enctrl_iop[unit], port_enctrl[unit],
	    &req, sizeof(req), 0);
	msg_recv(port_enctrl[unit], NULL, &reply, NULL, 0);

	req.lance_func = EN_START;
	msg_send(port_enctrl_iop[unit], port_enctrl[unit],
	    &req, sizeof(req), 0);
	msg_recv(port_enctrl[unit], NULL, &reply, NULL, 0);
	msg_free(port_enctrl[unit]);

	msg_send(port_enrecv_iop[unit], port_enrecv[unit],
	    es->es_ifnews.ifn_raddr,
	    ETHERMTU + sizeof(struct en_rheader), MSG_INDIRECT);
}

en_start(unit, len)
	int unit;
	int len;
{

	msg_send(port_enxmit_iop[unit], port_enxmit[unit], &len, sizeof(len), 0);
}

enxint(unit)
	register int unit;
{
	int *len;
	struct en_softc *es = &en_softc[unit];

	if (msg_recv(port_enxmit[unit], NULL, &len, NULL, 0) < 0) {
		printf("stray enxint\n");
		return;
	}
	if (es->es_ifnews.ifn_mbuf)
		m_freem(es->es_ifnews.ifn_mbuf);
	_enxint(unit, *len < 0, *len & 0x10000);
}

enrint(unit)
	int unit;
{
	int len;
	int *reply;

	if (msg_recv(port_enrecv[unit], NULL, &reply, NULL, 0) < 0) {
		printf("stray enrint\n");
		return;
	}
	len = *reply - sizeof(struct en_rheader);
	msg_free(port_enrecv[unit]);
#ifdef mips
	/*
	 * cache flush address must aligned long word boundary.
	 * so, add 3 for sanity.
	 */
	clean_k2dcache((int)en_softc[unit].es_ifnews.ifn_raddr & ~03,
	    len + sizeof (struct en_rheader) + 3);
#endif
	_enrint(unit, len);
	msg_send(port_enrecv_iop[unit], port_enrecv[unit],
	    en_softc[unit].es_ifnews.ifn_raddr,
	    ETHERMTU + sizeof(struct en_rheader), MSG_INDIRECT);
}

en_prom_mode(unit, mode)
	int unit, mode;
{
	static int port;
	struct lance_ctrl_req req;
	extern int port_enctrl_iop[];

	req.lance_func = EN_PROMMODE;
	req.lance_mode = mode;
	msg_send(port_enctrl_iop[unit], 0, &req, sizeof(req), 0);
}
#endif /* IPC_MRX */
#endif /* NEN > 0 */
E 1
