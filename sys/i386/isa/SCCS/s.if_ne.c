h65315
s 00002/00002/00768
d D 8.1 93/06/11 15:54:02 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00022/00748
d D 7.5 92/10/11 10:20:08 bostic 11 10
c make kernel includes standard
e
s 00008/00004/00762
d D 7.4 91/05/21 10:42:06 bostic 10 9
c format cleanup
e
s 00003/00000/00763
d D 7.3 91/05/12 19:51:50 william 9 8
c cleaned too much...
e
s 00115/00247/00648
d D 7.2 91/05/12 19:39:38 william 8 7
c cleaning pass, removed dead code, updated comments, found boners
e
s 00123/00302/00772
d D 7.1 91/05/09 21:31:56 william 7 6
c newer versions
e
s 00000/00000/01074
d D 1.6 91/01/08 19:13:22 william 6 5
c  npx.c wd.c wt.c
e
s 00001/00001/01073
d D 1.5 90/11/18 11:32:00 bill 5 4
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00001/00001/01073
d D 1.4 90/11/15 13:43:50 bill 4 3
c trivial change (ethernet instead of hardware in printf)
e
s 00045/00025/01029
d D 1.3 90/11/09 11:35:09 bill 3 2
c finally got ring ptrs right, hope error processing didn't break again!
e
s 00123/00039/00931
d D 1.2 90/11/08 19:32:00 bill 2 1
c various bugs fixed, works on local enet
e
s 00970/00000/00000
d D 1.1 90/11/08 19:30:18 bill 1 0
c date and time created 90/11/08 19:30:18 by bill
e
u
U
t
T
I 1
D 10
#include "ne.h"
#if NNE > 0
E 10
D 7
/*
E 7
I 7
/*-
E 7
D 10
 * NE2000 Ethernet driver
D 7
 * Copyright (C) 1990 W. Jolitz
 * %W% (Berkeley) %G%
E 7
I 7
 * Copyright (C) 1990,91 W. Jolitz
E 10
I 10
 * Copyright (c) 1990, 1991 William F. Jolitz.
E 10
D 12
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
E 7
 *
I 7
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 10
 */

/*
 * NE2000 Ethernet driver
E 10
 *
E 7
 * Parts inspired from Tim Tucker's if_wd driver for the wd8003,
 * insight on the ne2000 gained from Robert Clements PC/FTP driver.
 */
I 10

#include "ne.h"
#if NNE > 0
E 10

D 11
#include "param.h"
#include "systm.h"
#include "mbuf.h"
#include "buf.h"
#include "protosw.h"
#include "socket.h"
#include "ioctl.h"
#include "errno.h"
#include "syslog.h"
E 11
I 11
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/syslog.h>
E 11

D 7
#include "../net/if.h"
#include "../net/netisr.h"
#include "../net/route.h"
E 7
I 7
D 11
#include "net/if.h"
#include "net/netisr.h"
#include "net/route.h"
E 11
I 11
#include <net/if.h>
#include <net/netisr.h>
#include <net/route.h>
E 11
E 7

#ifdef INET
D 7
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
#include "../netinet/in_var.h"
#include "../netinet/ip.h"
#include "../netinet/if_ether.h"
E 7
I 7
D 11
#include "netinet/in.h"
#include "netinet/in_systm.h"
#include "netinet/in_var.h"
#include "netinet/ip.h"
#include "netinet/if_ether.h"
E 11
I 11
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
E 11
E 7
#endif

#ifdef NS
D 7
#include "../netns/ns.h"
#include "../netns/ns_if.h"
E 7
I 7
D 11
#include "netns/ns.h"
#include "netns/ns_if.h"
E 11
I 11
#include <netns/ns.h>
#include <netns/ns_if.h>
E 11
E 7
#endif

D 2
#include "../machine/device.h"
E 2
I 2
D 5
#include "machine/isa/device.h"
E 5
I 5
D 7
#include "machine/isa/isa_device.h"
E 5
E 2
#include "if_nereg.h"
#include "icu.h"
E 7
I 7
D 11
#include "i386/isa/isa_device.h"
#include "i386/isa/if_nereg.h"
#include "i386/isa/icu.h"
E 11
I 11
#include <i386/isa/isa_device.h>
#include <i386/isa/if_nereg.h>
#include <i386/isa/icu.h>
E 11
E 7

int	neprobe(), neattach(), neintr();
D 7
int	neinit(), neoutput(), neioctl();
E 7
I 7
int	nestart(),neinit(), ether_output(), neioctl();
E 7

D 2
struct	driver nedriver = {
E 2
I 2
D 7
#include "dbg.h"
E 7
struct	isa_driver nedriver = {
E 2
	neprobe, neattach, "ne",
};

D 2
u_short	neaddr[NNE] = {
	0x360
};

E 2
struct	mbuf *neget();

I 9
#define ETHER_MIN_LEN 64
#define ETHER_MAX_LEN 1536

E 9
/*
 * Ethernet software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * ns_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address, ...
 */
struct	ne_softc {
	struct	arpcom ns_ac;		/* Ethernet common part */
#define	ns_if	ns_ac.ac_if		/* network-visible interface */
#define	ns_addr	ns_ac.ac_enaddr		/* hardware Ethernet address */
	int	ns_flags;
#define	DSF_LOCK	1		/* block re-entering enstart */
	int	ns_oactive ;
	int	ns_mask ;
	int	ns_ba;			/* byte addr in buffer ram of inc pkt */
	int	ns_cur;			/* current page being filled */
	struct	prhdr	ns_ph;		/* hardware header of incoming packet*/
	struct	ether_header ns_eh;	/* header of incoming packet */
	u_char	ns_pb[2048 /*ETHERMTU+sizeof(long)*/];
} ne_softc[NNE] ;
D 8
#define	ENBUFSIZE	(sizeof(struct ether_header) + ETHERMTU + 2 + 64)
E 8
I 8
#define	ENBUFSIZE	(sizeof(struct ether_header) + ETHERMTU + 2 + ETHER_MIN_LEN)
E 8

int nec;

u_short boarddata[16];
 
neprobe(dvp)
D 2
	struct device *dvp;
E 2
I 2
	struct isa_device *dvp;
E 2
{
	int val,i,s;
	register struct ne_softc *ns = &ne_softc[0];

#ifdef lint
	neintr(0);
#endif

D 2
	nec = dvp->ioa;
E 2
I 2
	nec = dvp->id_iobase;
E 2
	s = splimp();

D 8
	/* reset the bastard */
E 8
I 8
	/* Reset the bastard */
E 8
	val = inb(nec+ne_reset);
	DELAY(2000000);
	outb(nec+ne_reset,val);

	outb(nec+ds_cmd, DSCM_STOP|DSCM_NODMA);
D 2
/* install timeout and return 0 if error */
	while ((inb(nec+ds0_isr)&DSIS_RESET) == 0);
E 2
I 2
	
	i = 1000000;
D 7
	while ((inb(nec+ds0_isr)&DSIS_RESET) == 0 && i-- > 0) nulldev();
E 7
I 7
	while ((inb(nec+ds0_isr)&DSIS_RESET) == 0 && i-- > 0);
E 7
	if (i < 0) return (0);

E 2
	outb(nec+ds0_isr, 0xff);

	/* Word Transfers, Burst Mode Select, Fifo at 8 bytes */
	outb(nec+ds0_dcr, DSDC_WTS|DSDC_BMS|DSDC_FT1);

	outb(nec+ds_cmd, DSCM_NODMA|DSCM_PG0|DSCM_STOP);
D 2
/* check cmd reg and fail if not right */
E 2
I 2
	DELAY(10000);

D 8
	/* check cmd reg and fail if not right */
E 8
I 8
	/* Check cmd reg and fail if not right */
E 8
	if ((i=inb(nec+ds_cmd)) != (DSCM_NODMA|DSCM_PG0|DSCM_STOP))
		return(0);

E 2
	outb(nec+ds0_tcr, 0);
	outb(nec+ds0_rcr, DSRC_MON);
	outb(nec+ds0_pstart, RBUF/DS_PGSIZE);
	outb(nec+ds0_pstop, RBUFEND/DS_PGSIZE);
	outb(nec+ds0_bnry, RBUFEND/DS_PGSIZE);
	outb(nec+ds0_imr, 0);
	outb(nec+ds0_isr, 0);
	outb(nec+ds_cmd, DSCM_NODMA|DSCM_PG1|DSCM_STOP);
	outb(nec+ds1_curr, RBUF/DS_PGSIZE);
	outb(nec+ds_cmd, DSCM_NODMA|DSCM_PG0|DSCM_STOP);
D 8
	fetchrom (boarddata, 0, sizeof(boarddata));
E 8
I 8

E 8
I 2
#ifdef NEDEBUG
E 2
D 8
/*{ int i,rom;
	rom=1;
printf("ne ram ");
	for (i = 0; i < 0xfff0; i+=4) {
		int pat;
		pat = 0xa55a+i*37;
		putram(&pat,i,4);
		fetchram(&pat,i,4);
		if (pat == 0xa55a+i*37) {
			if (rom) { rom=0; printf(" %x", i); }
		} else {
			if (!rom) { rom=1; printf("..%x ", i); }
E 8
I 8
#define	PAT(n)	(0xa55a + 37*(n))
#define	RCON	37
	{	int i, rom, pat;

		rom=1;
		printf("ne ram ");
		
		for (i = 0; i < 0xfff0; i+=4) {
			pat = PAT(i);
			neput(&pat,i,4);
			nefetch(&pat,i,4);
			if (pat == PAT(i)) {
				if (rom) {
					rom=0;
					printf(" %x", i);
				}
			} else {
				if (!rom) {
					rom=1;
					printf("..%x ", i);
				}
			}
			pat=0;
			neput(&pat,i,4);
E 8
		}
D 8
		pat=0;
		putram(&pat,i,4);
E 8
I 8
		printf("\n");
E 8
	}
D 8
printf("\n");
}*/
E 8
I 2
#endif
E 2
D 8
/* checksum data? */
	/* extract board address */
E 8
I 8

	/* Extract board address */
	nefetch ((caddr_t)boarddata, 0, sizeof(boarddata));
E 8
	for(i=0; i < 6; i++)  ns->ns_addr[i] = boarddata[i];
D 2
	INTREN(IRQ9);
	INTREN(0x2);
E 2
	splx(s);
	return (1);
}

D 8
fetchrom (up, ad, len) u_short *up; {
E 8
I 8
/*
 * Fetch from onboard ROM/RAM
 */
nefetch (up, ad, len) caddr_t up; {
E 8
	u_char cmd;

	cmd = inb(nec+ds_cmd);
D 8
	outb (nec+ds_cmd, DSCM_NODMA|DSCM_PG0|DSCM_STOP);
E 8
I 8
	outb (nec+ds_cmd, DSCM_NODMA|DSCM_PG0|DSCM_START);

	/* Setup remote dma */
E 8
	outb (nec+ds0_isr, DSIS_RDC);
D 8
	outb (nec+ds0_rbcr0, len&0xff);
	outb (nec+ds0_rbcr1, (len>>8)&0xff);
	outb (nec+ds0_rsar0, ad&0xff);
	outb (nec+ds0_rsar1, (ad>>8)&0xff);
E 8
I 8
	outb (nec+ds0_rbcr0, len);
	outb (nec+ds0_rbcr1, len>>8);
	outb (nec+ds0_rsar0, ad);
	outb (nec+ds0_rsar1, ad>>8);

	/* Execute & extract from card */
E 8
	outb (nec+ds_cmd, DSCM_RREAD|DSCM_PG0|DSCM_START);
	insw (nec+ne_data, up, len/2);
D 2
	while ((inb (nec+ds0_isr) & DSIS_RDC) == 0) nulldev();
E 2
I 2
D 8
	pausestr ("x",1);
	while ((inb (nec+ds0_isr) & DSIS_RDC) == 0) pausestr("fetchrom",0);
E 2
	outb (nec+ds0_isr, DSIS_RDC);
	outb (nec+ds_cmd, cmd);
}
E 8

I 2
D 8
static recur;
E 2
fetchram (up, ad, len) caddr_t up; {
	u_char cmd;

I 2
	recur++;
E 2
	cmd = inb(nec+ds_cmd);
	outb (nec+ds_cmd, DSCM_NODMA|DSCM_PG0|DSCM_START);
E 8
I 8
	/* Wait till done, then shutdown feature */
	while ((inb (nec+ds0_isr) & DSIS_RDC) == 0) ;
E 8
	outb (nec+ds0_isr, DSIS_RDC);
D 8
	outb (nec+ds0_rbcr0, len&0xff);
	outb (nec+ds0_rbcr1, (len>>8)&0xff);
	outb (nec+ds0_rsar0, ad&0xff);
	outb (nec+ds0_rsar1, (ad>>8)&0xff);
	outb (nec+ds_cmd, DSCM_RREAD|DSCM_PG0|DSCM_START);
	insw (nec+ne_data, up, len/2);
D 2
	while ((inb (nec+ds0_isr) & DSIS_RDC) == 0) nulldev();
E 2
I 2
	pausestr ("x",1);
	while ((inb (nec+ds0_isr) & DSIS_RDC) == 0) pausestr("fetchram",0);
E 2
	outb (nec+ds0_isr, DSIS_RDC);
E 8
	outb (nec+ds_cmd, cmd);
I 2
D 8
	recur--;
E 8
E 2
}

D 8
putram (up, ad, len) caddr_t up; {
E 8
I 8
/*
 * Put to onboard RAM
 */
neput (up, ad, len) caddr_t up; {
E 8
	u_char cmd;

I 2
D 8
	recur++;
E 8
E 2
	cmd = inb(nec+ds_cmd);
	outb (nec+ds_cmd, DSCM_NODMA|DSCM_PG0|DSCM_START);
I 8

	/* Setup for remote dma */
E 8
	outb (nec+ds0_isr, DSIS_RDC);
D 8
	if(len&1) len++;
	outb (nec+ds0_rbcr0, len&0xff);
	outb (nec+ds0_rbcr1, (len>>8)&0xff);
	outb (nec+ds0_rsar0, ad&0xff);
	outb (nec+ds0_rsar1, (ad>>8)&0xff);
E 8
I 8
	if(len&1) len++;		/* roundup to words */
	outb (nec+ds0_rbcr0, len);
	outb (nec+ds0_rbcr1, len>>8);
	outb (nec+ds0_rsar0, ad);
	outb (nec+ds0_rsar1, ad>>8);

	/* Execute & stuff to card */
E 8
	outb (nec+ds_cmd, DSCM_RWRITE|DSCM_PG0|DSCM_START);
	outsw (nec+ne_data, up, len/2);
D 2
	while ((inb (nec+ds0_isr) & DSIS_RDC) == 0) nulldev();
E 2
I 2
D 8
	pausestr ("x",1);
	while ((inb (nec+ds0_isr) & DSIS_RDC) == 0)
		if(pausestr("putram",0)<0) break;
E 8
I 8
	
	/* Wait till done, then shutdown feature */
	while ((inb (nec+ds0_isr) & DSIS_RDC) == 0) ;
E 8
E 2
	outb (nec+ds0_isr, DSIS_RDC);
	outb (nec+ds_cmd, cmd);
I 2
D 8
	recur--;
E 8
E 2
}

/*
 * Reset of interface.
 */
nereset(unit, uban)
	int unit, uban;
{
	if (unit >= NNE)
		return;
	printf("ne%d: reset\n", unit);
	ne_softc[unit].ns_flags &= ~DSF_LOCK;
	neinit(unit);
}
 
/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.  We get the ethernet address here.
 */
neattach(dvp)
D 2
	struct device *dvp;
E 2
I 2
	struct isa_device *dvp;
E 2
{
D 2
	int unit = dvp->unit;
E 2
I 2
	int unit = dvp->id_unit;
E 2
	register struct ne_softc *ns = &ne_softc[unit];
	register struct ifnet *ifp = &ns->ns_if;

	ifp->if_unit = unit;
	ifp->if_name = nedriver.name ;
	ifp->if_mtu = ETHERMTU;
D 4
	printf (" physical address %s", ether_sprintf(ns->ns_addr)) ;
E 4
I 4
	printf (" ethernet address %s", ether_sprintf(ns->ns_addr)) ;
E 4
D 7
	ifp->if_flags = IFF_BROADCAST|IFF_NOTRAILERS;
E 7
I 7
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_NOTRAILERS;
E 7
	ifp->if_init = neinit;
D 7
	ifp->if_output = neoutput;
E 7
I 7
	ifp->if_output = ether_output;
	ifp->if_start = nestart;
E 7
	ifp->if_ioctl = neioctl;
	ifp->if_reset = nereset;
	ifp->if_watchdog = 0;
	if_attach(ifp);
}

/*
 * Initialization of interface; set up initialization block
 * and transmit/receive descriptor rings.
 */
neinit(unit)
	int unit;
{
	register struct ne_softc *ns = &ne_softc[unit];
	struct ifnet *ifp = &ns->ns_if;
	int s;
	register i; char *cp;

 	if (ifp->if_addrlist == (struct ifaddr *)0) return;
	if (ifp->if_flags & IFF_RUNNING) return;

	s = splimp();

	/* set physical address on ethernet */
	outb (nec+ds_cmd, DSCM_NODMA|DSCM_PG1|DSCM_STOP);
	for (i=0 ; i < 6 ; i++) outb(nec+ds1_par0+i,ns->ns_addr[i]);

	/* clr logical address hash filter for now */
	for (i=0 ; i < 8 ; i++) outb(nec+ds1_mar0+i,0xff);

	/* init regs */
	outb (nec+ds_cmd, DSCM_NODMA|DSCM_PG0|DSCM_STOP);
	outb (nec+ds0_rbcr0, 0);
	outb (nec+ds0_rbcr1, 0);
	outb (nec+ds0_imr, 0);
	outb (nec+ds0_isr, 0xff);
I 8

E 8
	/* Word Transfers, Burst Mode Select, Fifo at 8 bytes */
	outb(nec+ds0_dcr, DSDC_WTS|DSDC_BMS|DSDC_FT1);
	outb(nec+ds0_tcr, 0);
	outb (nec+ds0_rcr, DSRC_MON);
	outb (nec+ds0_tpsr, 0);
	outb(nec+ds0_pstart, RBUF/DS_PGSIZE);
	outb(nec+ds0_pstop, RBUFEND/DS_PGSIZE);
D 3
	outb(nec+ds0_bnry, RBUFEND/DS_PGSIZE);
E 3
I 3
	outb(nec+ds0_bnry, RBUF/DS_PGSIZE);
E 3
	outb (nec+ds_cmd, DSCM_NODMA|DSCM_PG1|DSCM_STOP);
	outb(nec+ds1_curr, RBUF/DS_PGSIZE);
	ns->ns_cur = RBUF/DS_PGSIZE;
	outb (nec+ds_cmd, DSCM_NODMA|DSCM_PG0|DSCM_START);
	outb (nec+ds0_rcr, DSRC_AB);
	outb(nec+ds0_dcr, DSDC_WTS|DSDC_BMS|DSDC_FT1);
	outb (nec+ds0_imr, 0xff);

	ns->ns_if.if_flags |= IFF_RUNNING;
	ns->ns_oactive = 0; ns->ns_mask = ~0;
D 7
	if (ns->ns_if.if_snd.ifq_head) nestart(ns);
E 7
I 7
	nestart(ifp);
E 7
	splx(s);
}

/*
 * Setup output on interface.
 * Get another datagram to send off of the interface queue,
 * and map it to the interface before starting the output.
 * called only at splimp or interrupt level.
 */
D 7
nestart(ns)
	register struct ne_softc *ns;
E 7
I 7
nestart(ifp)
	struct ifnet *ifp;
E 7
{
I 7
	register struct ne_softc *ns = &ne_softc[ifp->if_unit];
E 7
	struct mbuf *m0, *m;
	int buffer;
D 7
	int len = 0, i;
E 7
I 7
	int len = 0, i, total,t;
E 7

	/*
	 * The DS8390 has only one transmit buffer, if it is busy we
	 * must wait until the transmit interrupt completes.
	 */
	outb(nec+ds_cmd,DSCM_NODMA|DSCM_START);

I 2
	if (ns->ns_flags & DSF_LOCK)
		return;

E 2
	if (inb(nec+ds_cmd) & DSCM_TRANS)
		return;

	if ((ns->ns_if.if_flags & IFF_RUNNING) == 0)
		return;

	IF_DEQUEUE(&ns->ns_if.if_snd, m);
 
	if (m == 0)
		return;

I 7
D 8
	if ((m->m_flags & M_PKTHDR) == 0)
		printf("should panic: no packet header\n");
E 8
E 7
	/*
	 * Copy the mbuf chain into the transmit buffer
	 */

I 2
	ns->ns_flags |= DSF_LOCK;	/* prevent entering nestart */
E 2
	buffer = TBUF; len = i = 0;
I 7
	t = 0;
D 8
#include "machine/dbg.h"
dprintf(DPAGIN,"\n before: ");
E 7
	for (m0 = m; m != 0; m = m->m_next) {
E 8
I 8
	for (m0 = m; m != 0; m = m->m_next)
E 8
I 7
		t += m->m_len;
D 8
dprintf(DPAGIN,"%d ", m->m_len);
	}
E 8
		
	m = m0;
	total = t;
D 8
	if (m->m_flags & M_PKTHDR && total != m->m_pkthdr.len)
		printf("hdr fucked, len %d should be %d\n", total, m->m_pkthdr.len);
dprintf(DPAGIN,"\n after: ");
E 8
	for (m0 = m; m != 0; ) {
		
E 7
D 8
/*int j;*/
E 8
D 7
		putram(mtod(m, caddr_t), buffer, m->m_len);
		buffer += m->m_len;
		len += m->m_len;
E 7
I 7
		if (m->m_len&1 && t > m->m_len) {
D 8
dprintf(DPAGIN|DPAUSE,"+%d:%d ", m->m_len, m->m_next->m_len);
			putram(mtod(m, caddr_t), buffer, m->m_len - 1);
E 8
I 8
			neput(mtod(m, caddr_t), buffer, m->m_len - 1);
E 8
			t -= m->m_len - 1;
			buffer += m->m_len - 1;
			m->m_data += m->m_len - 1;
			m->m_len = 1;
			m = m_pullup(m, 2);
D 8
if(m == 0) panic("bloowie!");
{ struct mbuf *mp;
dprintf(DPAGIN|DPAUSE, "\n rewritten as: ");
	for (mp = m; mp != 0; mp = mp->m_next)
dprintf(DPAGIN,"%d ", mp->m_len);
}
dprintf(DPAGIN,"\n");
E 8
		} else {
D 8
dprintf(DPAGIN|DPAUSE,"%d ", m->m_len);
			putram(mtod(m, caddr_t), buffer, m->m_len);
E 8
I 8
			neput(mtod(m, caddr_t), buffer, m->m_len);
E 8
			buffer += m->m_len;
			t -= m->m_len;
			MFREE(m, m0);
			m = m0;
		}
E 7
D 8
/*for(j=0; i < len;i++,j++) puthex(mtod(m,u_char *)[j]);
printf("|"); */
E 8
	}
I 7
D 8
dprintf(DPAGIN|DPAUSE,"send %d\n", total);
E 8
E 7

	/*
D 7
	 * If this was a broadcast packet loop it
	 * back because the hardware can't hear its own
	 * transmits.
	 */
	/*if (bcmp((caddr_t)(mtod(m0, struct ether_header *)->ether_dhost),
	   (caddr_t)etherbroadcastaddr,
	   sizeof(etherbroadcastaddr)) == 0) {
		neread(ns, m0);
	} else {
*/
		m_freem(m0);
	/*}*/

	/*
E 7
	 * Init transmit length registers, and set transmit start flag.
	 */

D 2
if (len < 60) len = 60;
E 2
I 2
D 3
#ifdef NEDEBUG
E 3
I 3
D 8
#ifdef NEDEBUGx
E 3
if(len < 0 || len > 1536)
pg("T Bogus Length %d\n", len);
dprintf(DEXPAND,"snd %d ", len);
#endif
E 8
D 7
	if (len < 60) len = 60;
E 7
I 7
	len = total;
D 8
	if (len < 64) len = 64;
E 8
I 8
	if (len < ETHER_MIN_LEN) len = ETHER_MIN_LEN;
E 8
E 7
E 2
	outb(nec+ds0_tbcr0,len&0xff);
	outb(nec+ds0_tbcr1,(len>>8)&0xff);
	outb(nec+ds0_tpsr, TBUF/DS_PGSIZE);
	outb(nec+ds_cmd, DSCM_TRANS|DSCM_NODMA|DSCM_START);
}

I 8
/* buffer successor/predecessor in ring? */
E 8
D 3
#define succ(n) (((n)+1 > RBUFEND/DS_PGSIZE) ? RBUF/DS_PGSIZE : (n)+1)
#define pred(n) (((n)-1 < RBUF/DS_PGSIZE) ? RBUFEND/DS_PGSIZE : (n)-1)
E 3
I 3
#define succ(n) (((n)+1 >= RBUFEND/DS_PGSIZE) ? RBUF/DS_PGSIZE : (n)+1)
#define pred(n) (((n)-1 < RBUF/DS_PGSIZE) ? RBUFEND/DS_PGSIZE-1 : (n)-1)
I 8

E 8
E 3
/*
 * Controller interrupt.
 */
D 2
neintr(vec)
E 2
I 2
D 7
neintr(vec, ppl)
E 2
	int vec;
E 7
I 7
neintr(unit)
E 7
{
D 7
	register struct ne_softc *ns = &ne_softc[0];
E 7
I 7
	register struct ne_softc *ns = &ne_softc[unit];
E 7
	u_char cmd,isr;
I 2
D 8
static cnt;
E 8
E 2

D 2
	/* check cmd, clear interrupt */
redo:
E 2
I 2
D 3
redstack();
E 3
D 8
	/* save cmd, clear interrupt */
E 8
I 8
	/* Save cmd, clear interrupt */
E 8
E 2
	cmd = inb (nec+ds_cmd);
D 2
	outb(nec+ds_cmd,DSCM_NODMA|DSCM_STOP);
E 2
I 2
loop:
E 2
	isr = inb (nec+ds0_isr);
I 2
D 3
#ifdef NEDEBUG
E 3
I 3
D 8
#ifdef NEDEBUGx
E 3
dprintf(DEXPAND,"|ppl %x isr %x ", ppl, isr);
#endif

E 8
	outb(nec+ds_cmd,DSCM_NODMA|DSCM_START);
E 2
D 3
	outb (nec+ds0_isr, isr);
E 3
I 3
	outb(nec+ds0_isr, isr);
E 3

D 2
	ns->ns_flags |= DSF_LOCK;	/* prevent entering nestart */
E 2
D 8

D 3
	if (isr & (/*DSIS_RXE|*/DSIS_TXE|DSIS_ROVRN))
E 3
I 3
D 7
	if (isr & (DSIS_RXE|DSIS_TXE|DSIS_ROVRN))
E 7
I 7
	if (isr & (/*DSIS_RXE|DSIS_TXE|*/DSIS_ROVRN))
E 7
E 3
		log(LOG_ERR, "ne%d: error: isr %x\n", ns-ne_softc, isr/*, DSIS_BITS*/);

I 3
#ifdef notdef
E 3
	/* receiver ovverun? */
	if (isr & DSIS_ROVRN) {
		u_char pend,lastfree;

		outb(nec+ds_cmd, DSCM_STOP|DSCM_NODMA);
		outb(nec+ds_cmd, DSCM_STOP|DSCM_NODMA|DSCM_PG1);
		pend = inb(nec+ds1_curr);
		outb(nec+ds_cmd, DSCM_STOP|DSCM_NODMA|DSCM_PG0);
		lastfree = inb(nec+ds0_bnry);
I 2
#ifdef NEDEBUG
E 2
printf("Cur %x pend %x lastfree %x ", ns->ns_cur, pend, lastfree);
I 2
#endif
E 2
		/* have we wrapped */
D 3
		if (lastfree > RBUFEND/DS_PGSIZE)
E 3
I 3
		if (lastfree >= RBUFEND/DS_PGSIZE)
E 3
			lastfree = RBUF/DS_PGSIZE;
		/* something in the buffer? */
		if (pend != succ(lastfree)) {
			u_char nxt;

			fetchram(&ns->ns_ph,ns->ns_cur*DS_PGSIZE, sizeof(ns->ns_ph));
			ns->ns_ba = ns->ns_cur*DS_PGSIZE+sizeof(ns->ns_ph);

			if (ns->ns_ph.pr_status & DSRS_RPC)
				nerecv (ns);

			nxt = ns->ns_ph.pr_nxtpg ;
I 2
#ifdef NEDEBUG
E 2
printf("nxt %x ", nxt);
I 2
#endif
E 2
			/* sanity check */
			if ( nxt >= RBUF/DS_PGSIZE
			&& nxt <= RBUFEND/DS_PGSIZE && nxt <= pend)
				ns->ns_cur = nxt;
			else	ns->ns_cur = nxt = pend;
			lastfree = pred(nxt);
			outb(nec+ds0_bnry, lastfree);
		} else ns->ns_cur = pend;

		outb(nec+ds0_rbcr0,0);
		outb(nec+ds0_rbcr1,0);
		outb(nec+ds0_tcr,DSTC_LB0);
		outb(nec+ds0_rcr, DSRC_MON);
		outb(nec+ds_cmd, DSCM_START|DSCM_NODMA);
		outb (nec+ds0_rcr, DSRC_AB);
		outb(nec+ds0_tcr,0);
I 2
D 3
#ifdef NEDEBUG
E 2
printf("\n");
D 2
		goto redo;
E 2
I 2
#endif
E 3
E 2
	}
I 3
#endif
E 3

	/* receiver error */
E 8
I 8
	/* Receiver error */
E 8
	if (isr & DSIS_RXE) {
		/* need to read these registers to clear status */
		(void) inb(nec+ ds0_rsr);
		(void) inb(nec+ 0xD);
		(void) inb(nec + 0xE);
		(void) inb(nec + 0xF);
		ns->ns_if.if_ierrors++;
	}

I 8
	/* We received something; rummage thru tiny ring buffer */
E 8
D 3
	if (isr & (DSIS_RX|DSIS_RXE)) {
E 3
I 3
	if (isr & (DSIS_RX|DSIS_RXE|DSIS_ROVRN)) {
E 3
		u_char pend,lastfree;

		outb(nec+ds_cmd, DSCM_START|DSCM_NODMA|DSCM_PG1);
		pend = inb(nec+ds1_curr);
		outb(nec+ds_cmd, DSCM_START|DSCM_NODMA|DSCM_PG0);
		lastfree = inb(nec+ds0_bnry);
D 2
#include "dbg.h"
dprintf(DEXPAND,"cur %x pend %x lastfree %x ", ns->ns_cur, pend, lastfree);
E 2
I 2
D 8
#ifdef NEDEBUG
dprintf(DEXPAND,"cur %x pnd %x lfr %x ", ns->ns_cur, pend, lastfree);
#endif
E 2
		/* have we wrapped */
E 8
I 8

		/* Have we wrapped? */
E 8
D 3
		if (lastfree > RBUFEND/DS_PGSIZE)
E 3
I 3
		if (lastfree >= RBUFEND/DS_PGSIZE)
E 3
			lastfree = RBUF/DS_PGSIZE;
I 3
		if (pend < lastfree && ns->ns_cur < pend)
			lastfree = ns->ns_cur;
		else	if (ns->ns_cur > lastfree)
			lastfree = ns->ns_cur;

E 3
D 8
		/* something in the buffer? */
E 8
I 8
		/* Something in the buffer? */
E 8
D 2
		while (pend != succ(lastfree)) {
E 2
I 2
D 3
		if (pend != succ(lastfree)) {
E 3
I 3
		while (pend != lastfree) {
E 3
E 2
			u_char nxt;

D 3
			fetchram(&ns->ns_ph,ns->ns_cur*DS_PGSIZE, sizeof(ns->ns_ph));
			ns->ns_ba = ns->ns_cur*DS_PGSIZE+sizeof(ns->ns_ph);
E 3
I 3
D 8
			fetchram(&ns->ns_ph,lastfree*DS_PGSIZE,
E 8
I 8
			/* Extract header from microcephalic board */
			nefetch(&ns->ns_ph,lastfree*DS_PGSIZE,
E 8
				sizeof(ns->ns_ph));
			ns->ns_ba = lastfree*DS_PGSIZE+sizeof(ns->ns_ph);
E 3

I 3
D 8
			/* paranoia */
E 8
I 8
			/* Incipient paranoia */
E 8
E 3
D 2
			if (ns->ns_ph.pr_status & DSRS_RPC)
E 2
I 2
			if (ns->ns_ph.pr_status == DSRS_RPC ||
I 8
				/* for dequna's */
E 8
				ns->ns_ph.pr_status == 0x21)
E 2
				nerecv (ns);
I 2
#ifdef NEDEBUG
			else  {
D 8
printf("cur %x pnd %x lfr %x ", ns->ns_cur, pend, lastfree);
printf("nxt %x len %x ", ns->ns_ph.pr_nxtpg, (ns->ns_ph.pr_sz1<<8)+
	ns->ns_ph.pr_sz0);
pg("Bogus Sts %x ", ns->ns_ph.pr_status);	
E 8
I 8
				printf("cur %x pnd %x lfr %x ",
					ns->ns_cur, pend, lastfree);
				printf("nxt %x len %x ", ns->ns_ph.pr_nxtpg,
					(ns->ns_ph.pr_sz1<<8)+ ns->ns_ph.pr_sz0);
				printf("Bogus Sts %x\n", ns->ns_ph.pr_status);	
E 8
			}
#endif
E 2

			nxt = ns->ns_ph.pr_nxtpg ;
I 2
D 8
#ifdef NEDEBUG
E 2
dprintf(DEXPAND,"nxt %x ", nxt);
I 2
#endif
E 2
			/* sanity check */
			if ( nxt >= RBUF/DS_PGSIZE
			&& nxt <= RBUFEND/DS_PGSIZE && nxt <= pend)
E 8
I 8

			/* Sanity check */
			if ( nxt >= RBUF/DS_PGSIZE && nxt <= RBUFEND/DS_PGSIZE
				&& nxt <= pend)
E 8
				ns->ns_cur = nxt;
			else	ns->ns_cur = nxt = pend;
I 8

			/* Set the boundaries */
E 8
D 3
			lastfree = pred(nxt);
			outb(nec+ds0_bnry, lastfree);
E 3
I 3
			lastfree = nxt;
			outb(nec+ds0_bnry, pred(nxt));
			outb(nec+ds_cmd, DSCM_START|DSCM_NODMA|DSCM_PG1);
E 3
D 2
		}/* else ns->ns_cur = pend;*/
E 2
I 2
			pend = inb(nec+ds1_curr);
D 3
		} else ns->ns_cur = pend;
E 3
I 3
			outb(nec+ds_cmd, DSCM_START|DSCM_NODMA|DSCM_PG0);
D 8
		} /*else ns->ns_cur = pend;*/
#ifdef NEDEBUG
dprintf(DEXPAND,"cur %x pnd %x lfR %x ", ns->ns_cur, pend, lastfree);
#endif
E 8
I 8
		}
E 8
E 3
E 2
		outb(nec+ds_cmd, DSCM_START|DSCM_NODMA);
D 2
		goto redo;
E 2
	}
I 8

	/* Transmit error */
E 8
	if (isr & DSIS_TXE) {
I 2
D 3
	ns->ns_flags &= ~DSF_LOCK;
E 3
I 3
		ns->ns_flags &= ~DSF_LOCK;
E 3
D 8
#ifdef NEDEBUG
dprintf(DEXPAND," clsn");
#endif
E 2
		/* need to read these registers to clear status */
E 8
I 8
		/* Need to read these registers to clear status */
E 8
		ns->ns_if.if_collisions += inb(nec+ds0_tbcr0);
		ns->ns_if.if_oerrors++;
	}
I 8

	/* Packet Transmitted */
E 8
D 2
	if (isr & (DSIS_TXE| DSIS_TX)) {
E 2
I 2
	if (isr & DSIS_TX) {
D 3
#ifdef NEDEBUG
E 3
I 3
D 8
#ifdef NEDEBUGx
E 3
dprintf(DEXPAND,"tx ");
#endif
E 8
D 3
	ns->ns_flags &= ~DSF_LOCK;
E 3
I 3
		ns->ns_flags &= ~DSF_LOCK;
E 3
E 2
		++ns->ns_if.if_opackets;
D 2
		inb(nec+ds0_bnry);
E 2
D 3
		ns->ns_if.if_collisions +=
		    inb(nec+ds0_tbcr0);
E 3
I 3
		ns->ns_if.if_collisions += inb(nec+ds0_tbcr0);
	}

D 8
	/* receiver ovverun? */
E 8
I 8
	/* Receiver ovverun? */
E 8
	if (isr & DSIS_ROVRN) {
I 8
		log(LOG_ERR, "ne%d: error: isr %x\n", ns-ne_softc, isr
			/*, DSIS_BITS*/);
E 8
		outb(nec+ds0_rbcr0, 0);
		outb(nec+ds0_rbcr1, 0);
		outb(nec+ds0_tcr, DSTC_LB0);
		outb(nec+ds0_rcr, DSRC_MON);
		outb(nec+ds_cmd, DSCM_START|DSCM_NODMA);
		outb(nec+ds0_rcr, DSRC_AB);
		outb(nec+ds0_tcr, 0);
E 3
	}
D 2
dprintf(DEXPAND,"\n");
	ns->ns_flags &= ~DSF_LOCK;
E 2
I 2

I 8
	/* Any more to send? */
E 8
E 2
	outb (nec+ds_cmd, DSCM_NODMA|DSCM_PG0|DSCM_START);
D 7
	nestart(ns);
E 7
I 7
	nestart(&ns->ns_if);
E 7
D 2
	outb (nec+ds_cmd, DSCM_NODMA|DSCM_PG0|DSCM_START);
E 2
I 2
	outb (nec+ds_cmd, cmd);
E 2
	outb (nec+ds0_imr, 0xff);
I 8

	/* Still more to do? */
E 8
I 2
	isr = inb (nec+ds0_isr);
	if(isr) goto loop;
D 8
	
#ifdef NEDEBUG
	if(++cnt % 10 == 0) dprintf(DEXPAND,"\n");
#endif
E 8
E 2
}

/*
 * Ethernet interface receiver interface.
 * If input error just drop packet.
 * Otherwise examine packet to determine type.  If can't determine length
 * from type, then have to drop packet.  Othewise decapsulate
 * packet based on type and pass to type specific higher-level
 * input routine.
 */
nerecv(ns)
	register struct ne_softc *ns;
{
	int len,i;

	ns->ns_if.if_ipackets++;
	len = ns->ns_ph.pr_sz0 + (ns->ns_ph.pr_sz1<<8);
I 2
D 8
if(len < 60 || len > 1536) {
#ifdef NEDEBUG
pg(DEXPAND,"R Bogus Length %d", len);
#endif
return;
}
E 2
	fetchram(ns->ns_pb,ns->ns_ba,min(len,DS_PGSIZE-sizeof(ns->ns_ph)));
I 2
#ifdef NEDEBUG
E 2
if (!bcmp((caddr_t)ns->ns_pb, (caddr_t)ns->ns_addr, 6)
&& !bcmp((caddr_t)ns->ns_pb, (caddr_t)etherbroadcastaddr, 6)) {
printf("G%x ", ns->ns_cur);
return;
}/* else 
printf("P%x ", ns->ns_cur);*/
I 2
#endif
E 2
	if(len > DS_PGSIZE-sizeof(ns->ns_ph)) {
E 8
I 8
	if(len < ETHER_MIN_LEN || len > ETHER_MAX_LEN)
		return;

	/* this need not be so torturous - one/two bcopys at most into mbufs */
	nefetch(ns->ns_pb, ns->ns_ba, min(len,DS_PGSIZE-sizeof(ns->ns_ph)));
	if (len > DS_PGSIZE-sizeof(ns->ns_ph)) {
E 8
		int l = len - (DS_PGSIZE-sizeof(ns->ns_ph)), b ;
		u_char *p = ns->ns_pb + (DS_PGSIZE-sizeof(ns->ns_ph));

D 2
dprintf(DEXPAND,"len %d( %d| ", len, p - ns->ns_pb);
E 2
I 2
D 8
#ifdef NEDEBUG
dprintf(DEXPAND,"len %d(%d|", len, p - ns->ns_pb);
#endif
E 8
E 2
		if(++ns->ns_cur > 0x7f) ns->ns_cur = 0x46;
		b = ns->ns_cur*DS_PGSIZE;
		
		while (l >= DS_PGSIZE) {
D 8
			fetchram(p,b,DS_PGSIZE);
E 8
I 8
			nefetch(p, b, DS_PGSIZE);
E 8
			p += DS_PGSIZE; l -= DS_PGSIZE;
D 8
		if(++ns->ns_cur > 0x7f) ns->ns_cur = 0x46;
		b = ns->ns_cur*DS_PGSIZE;
D 2
dprintf(DEXPAND,"%d| ", p - ns->ns_pb);
E 2
I 2
#ifdef NEDEBUG
dprintf(DEXPAND,"%d|", p - ns->ns_pb);
#endif
E 8
I 8
			if(++ns->ns_cur > 0x7f) ns->ns_cur = 0x46;
			b = ns->ns_cur*DS_PGSIZE;
E 8
E 2
		}
D 2
dprintf(DEXPAND,". %d)\n", l);
E 2
I 2
D 8
#ifdef NEDEBUG
dprintf(DEXPAND,"%d) ", l);
#endif
E 8
E 2
		if (l > 0)
D 8
			fetchram(p,b,l);
E 8
I 8
			nefetch(p, b, l);
E 8
	}
D 8
	len -= 
		sizeof(struct ether_header)
		+ sizeof(long);	/* don't forget checksum! */
E 8
I 8
	/* don't forget checksum! */
	len -= sizeof(struct ether_header) + sizeof(long);
E 8
			
D 8

E 8
	neread(ns,(caddr_t)(ns->ns_pb), len);
}

I 2
D 8
pausestr(s,n) char *s; {
static downcnt;

	if(n) { downcnt = 0xffff; return(0); }
	if(--downcnt > 0) return(0);
#ifdef NEDEBUG
	pg(" <%s> recur %d sts %x ", s, recur, inb (nec+ds0_isr));
#endif
	return(-1);
}
	

E 8
E 2
/*
 * Pass a packet to the higher levels.
 * We deal with the trailer protocol here.
 */
neread(ns, buf, len)
	register struct ne_softc *ns;
	char *buf;
	int len;
{
	register struct ether_header *eh;
    	struct mbuf *m;
	int off, resid;
	register struct ifqueue *inq;

	/*
	 * Deal with trailer protocol: if type is trailer type
	 * get true type from first 16-bit word past data.
	 * Remember that type was trailer by setting off.
	 */
	eh = (struct ether_header *)buf;
	eh->ether_type = ntohs((u_short)eh->ether_type);
#define	nedataaddr(eh, off, type)	((type)(((caddr_t)((eh)+1)+(off))))
	if (eh->ether_type >= ETHERTYPE_TRAIL &&
	    eh->ether_type < ETHERTYPE_TRAIL+ETHERTYPE_NTRAILER) {
		off = (eh->ether_type - ETHERTYPE_TRAIL) * 512;
		if (off >= ETHERMTU) return;		/* sanity */
		eh->ether_type = ntohs(*nedataaddr(eh, off, u_short *));
		resid = ntohs(*(nedataaddr(eh, off+2, u_short *)));
		if (off + resid > len) return;		/* sanity */
		len = off + resid;
	} else	off = 0;

	if (len == 0) return;

	/*
	 * Pull packet off interface.  Off is nonzero if packet
	 * has trailing header; neget will then force this header
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
	 */
	m = neget(buf, len, off, &ns->ns_if);
	if (m == 0) return;

D 7
	if (off) {
		struct ifnet *ifp;

		ifp = *(mtod(m, struct ifnet **));
		m->m_off += 2 * sizeof (u_short);
		m->m_len -= 2 * sizeof (u_short);
		*(mtod(m, struct ifnet **)) = ifp;
	}
	switch (eh->ether_type) {
#ifdef INET
	case ETHERTYPE_IP:
		/*if (ns->ns_ac.ac_ipaddr == 0) goto raw;*/
		schednetisr(NETISR_IP);
		inq = &ipintrq;
		break;

	case ETHERTYPE_ARP:
		arpinput(&ns->ns_ac, m);
		return;
#endif
#ifdef NS
	case ETHERTYPE_NS:
		schednetisr(NETISR_NS);
		inq = &nsintrq;
		break;

#endif
	default:
		m_freem(m);
		return;
	}

	if (IF_QFULL(inq)) {
		IF_DROP(inq);
		m_freem(m);
		return;
	}
	IF_ENQUEUE(inq, m);
E 7
I 7
	ether_input(&ns->ns_if, eh, m);
E 7
}

/*
D 7
 * Ethernet output routine.
 * Encapsulate a packet of type family for the local net.
 * Use trailer local net encapsulation if enough data in first
 * packet leaves a multiple of 512 bytes of data in remainder.
 */
neoutput(ifp, m0, dst)
	struct ifnet *ifp;
	struct mbuf *m0;
	struct sockaddr *dst;
{
	int type, s, error;
	u_char edst[6];
	struct in_addr idst;
	register struct ne_softc *ns = &ne_softc[ifp->if_unit];
	register struct mbuf *m = m0;
	register struct ether_header *eh;
	register int off;
	extern struct ifnet loif;
        struct mbuf *mcopy = (struct mbuf *)0;
	int usetrailers;

	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
		error = ENETDOWN;
		goto bad;
	}

	switch (dst->sa_family) {
#ifdef INET
	case AF_INET:
		idst = ((struct sockaddr_in *)dst)->sin_addr;
		if (!arpresolve(&ns->ns_ac, m, &idst, edst, &usetrailers))
			return (0);	/* if not yet resolved */
		if (!bcmp((caddr_t)edst, (caddr_t)etherbroadcastaddr,
		    sizeof(edst)))
                        mcopy = m_copy(m, 0, (int)M_COPYALL);
		off = ntohs((u_short)mtod(m, struct ip *)->ip_len) - m->m_len;
I 2

E 2

		/* need per host negotiation */
		if (usetrailers && off > 0 && (off & 0x1ff) == 0 &&
		    m->m_off >= MMINOFF + 2 * sizeof (u_short)) {
			type = ETHERTYPE_TRAIL + (off>>9);
			m->m_off -= 2 * sizeof (u_short);
			m->m_len += 2 * sizeof (u_short);
			*mtod(m, u_short *) = ntohs((u_short)ETHERTYPE_IP);
			*(mtod(m, u_short *) + 1) = ntohs((u_short)m->m_len);
			goto gottrailertype;
		}
		type = ETHERTYPE_IP;
		off = 0;
		goto gottype;
#endif
#ifdef NS
	case AF_NS:
 		bcopy((caddr_t)&(((struct sockaddr_ns *)dst)->sns_addr.x_host),
		    (caddr_t)edst, sizeof (edst));

		if (!bcmp((caddr_t)edst, (caddr_t)&ns_broadhost,
			sizeof(edst))) {

				mcopy = m_copy(m, 0, (int)M_COPYALL);
		} else if (!bcmp((caddr_t)edst, (caddr_t)&ns_thishost,
			sizeof(edst))) {

				return(looutput(&loif, m, dst));
		}
		type = ETHERTYPE_NS;
		off = 0;
		goto gottype;
#endif

	case AF_UNSPEC:
		eh = (struct ether_header *)dst->sa_data;
		bcopy((caddr_t)eh->ether_dhost, (caddr_t)edst, sizeof (edst));
		type = eh->ether_type;
		goto gottype;

	default:
		printf("ne%d: can't handle af%d\n", ifp->if_unit,
			dst->sa_family);
		error = EAFNOSUPPORT;
		goto bad;
	}

gottrailertype:
	/*
	 * Packet to be sent as trailer: move first packet
	 * (control information) to end of chain.
	 */
	while (m->m_next)
		m = m->m_next;
	m->m_next = m0;
	m = m0->m_next;
	m0->m_next = 0;
	m0 = m;

gottype:
	/*
	 * Add local net header.  If no space in first mbuf,
	 * allocate another.
	 */
	if (m->m_off > MMAXOFF ||
	    MMINOFF + sizeof (struct ether_header) > m->m_off) {
		m = m_get(M_DONTWAIT, MT_HEADER);
		if (m == 0) {
			error = ENOBUFS;
			goto bad;
		}
		m->m_next = m0;
		m->m_off = MMINOFF;
		m->m_len = sizeof (struct ether_header);
	} else {
		m->m_off -= sizeof (struct ether_header);
		m->m_len += sizeof (struct ether_header);
	}
	eh = mtod(m, struct ether_header *);
	bcopy((caddr_t)edst, (caddr_t)eh->ether_dhost, sizeof (edst));
	bcopy((caddr_t)ns->ns_addr, (caddr_t)eh->ether_shost,
		sizeof (eh->ether_shost));
	eh->ether_type = htons((u_short)type);

	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
	s = splimp();
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
		splx(s);
		m_freem(m);
		return (ENOBUFS);
	}
	IF_ENQUEUE(&ifp->if_snd, m);
	nestart(ns);
	splx(s);
        return (mcopy ? looutput(&loif, mcopy, dst) : 0);

bad:
	m_freem(m0);
	if (mcopy)
		m_freem(mcopy);
	return (error);
}

/*
E 7
 * Supporting routines
 */

/*
 * Pull read data off a interface.
 * Len is length of data, with local net header stripped.
 * Off is non-zero if a trailer protocol was used, and
 * gives the offset of the trailer information.
 * We copy the trailer information and then all the normal
 * data into mbufs.  When full cluster sized units are present
 * we copy into clusters.
 */
struct mbuf *
neget(buf, totlen, off0, ifp)
	caddr_t buf;
	int totlen, off0;
	struct ifnet *ifp;
{
	struct mbuf *top, **mp, *m, *p;
	int off = off0, len;
	register caddr_t cp = buf;
I 7
	char *epkt;
E 7

D 7
	cp = buf + sizeof(struct ether_header);
E 7
I 7
	buf += sizeof(struct ether_header);
	cp = buf;
	epkt = cp + totlen;


	if (off) {
		cp += off + 2 * sizeof(u_short);
		totlen -= 2 * sizeof(u_short);
	}

	MGETHDR(m, M_DONTWAIT, MT_DATA);
	if (m == 0)
		return (0);
	m->m_pkthdr.rcvif = ifp;
	m->m_pkthdr.len = totlen;
	m->m_len = MHLEN;

E 7
	top = 0;
	mp = &top;
	while (totlen > 0) {
D 7
		u_char *mcp;

		MGET(m, M_DONTWAIT, MT_DATA);
		if (m == 0)
			goto bad;
		if (off) {
			len = totlen - off;
			cp = buf + off + sizeof (struct ether_header);
		} else
			len = totlen;
		if (ifp)
			len += sizeof(ifp);
		if (len >= NBPG) {
			MCLGET(m);
			if (m->m_len == CLBYTES)
				m->m_len = len = MIN(len, CLBYTES);
E 7
I 7
		if (top) {
			MGET(m, M_DONTWAIT, MT_DATA);
			if (m == 0) {
				m_freem(top);
				return (0);
			}
			m->m_len = MLEN;
		}
		len = min(totlen, epkt - cp);
		if (len >= MINCLSIZE) {
			MCLGET(m, M_DONTWAIT);
			if (m->m_flags & M_EXT)
				m->m_len = len = min(len, MCLBYTES);
E 7
			else
D 7
				m->m_len = len = MIN(MLEN, len);
E 7
I 7
				len = m->m_len;
E 7
		} else {
D 7
			m->m_len = len = MIN(MLEN, len);
			m->m_off = MMINOFF;
		}
		mcp = mtod(m, u_char *);
		if (ifp) {
E 7
			/*
D 7
			 * Prepend interface pointer to first mbuf.
E 7
I 7
			 * Place initial small packet/header at end of mbuf.
E 7
			 */
D 7
			*(mtod(m, struct ifnet **)) = ifp;
			mcp += sizeof(ifp);
			len -= sizeof(ifp);
			ifp = (struct ifnet *)0;
E 7
I 7
			if (len < m->m_len) {
				if (top == 0 && len + max_linkhdr <= m->m_len)
					m->m_data += max_linkhdr;
				m->m_len = len;
			} else
				len = m->m_len;
E 7
		}
D 7
		bcopy(cp, mcp, len);
		cp += len ; mcp += len ;
E 7
I 7
		bcopy(cp, mtod(m, caddr_t), (unsigned)len);
		cp += len;
E 7
		*mp = m;
		mp = &m->m_next;
D 7
		if (off == 0) {
			totlen -= len;
			continue;
		}
		off += len;
		if (off == totlen) {
			cp = buf + sizeof (struct ether_header);
			off = 0;
			totlen = off0;
		}
E 7
I 7
		totlen -= len;
		if (cp == epkt)
			cp = buf;
E 7
	}
	return (top);
D 7
bad:
	m_freem(top);
	return (0);
E 7
}

/*
D 7
 * Map a chain of mbufs onto a network interface
 * in preparation for an i/o operation.
 * The argument chain of mbufs includes the local network
 * header which is copied to be in the mapped, aligned
 * i/o space.
 */
neput(cp, m)
	register caddr_t cp;
	register struct mbuf *m;
{
	register struct mbuf *mp;
	register int i;
	int x, cc = 0, t;
	caddr_t dp;

	while (m) {
		dp = mtod(m, char *);
		bcopy(mtod(m, caddr_t), cp, (unsigned)m->m_len);
		cp += m->m_len;
		cc += m->m_len;
		MFREE(m, mp);
		m = mp;
	}
	return (max(cc, ETHERMIN + sizeof(struct ether_header)));
}

/*
E 7
 * Process an ioctl request.
 */
neioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
	register struct ifaddr *ifa = (struct ifaddr *)data;
	struct ne_softc *ns = &ne_softc[ifp->if_unit];
	struct ifreq *ifr = (struct ifreq *)data;
	int s = splimp(), error = 0;


	switch (cmd) {

	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;

D 7
		switch (ifa->ifa_addr.sa_family) {
E 7
I 7
		switch (ifa->ifa_addr->sa_family) {
E 7
#ifdef INET
		case AF_INET:
			neinit(ifp->if_unit);	/* before arpwhohas */
			((struct arpcom *)ifp)->ac_ipaddr =
				IA_SIN(ifa)->sin_addr;
			arpwhohas((struct arpcom *)ifp, &IA_SIN(ifa)->sin_addr);
			break;
#endif
#ifdef NS
		case AF_NS:
		    {
			register struct ns_addr *ina = &(IA_SNS(ifa)->sns_addr);

			if (ns_nullhost(*ina))
				ina->x_host = *(union ns_host *)(ns->ns_addr);
			else {
				/* 
				 * The manual says we can't change the address 
				 * while the receiver is armed,
				 * so reset everything
				 */
				ifp->if_flags &= ~IFF_RUNNING; 
				bcopy((caddr_t)ina->x_host.c_host,
				    (caddr_t)ns->ns_addr, sizeof(ns->ns_addr));
			}
			neinit(ifp->if_unit); /* does ne_setaddr() */
			break;
		    }
#endif
		default:
			neinit(ifp->if_unit);
			break;
		}
		break;

	case SIOCSIFFLAGS:
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    ifp->if_flags & IFF_RUNNING) {
			ifp->if_flags &= ~IFF_RUNNING;
			outb(nec+ds_cmd,DSCM_STOP|DSCM_NODMA);
		} else if (ifp->if_flags & IFF_UP &&
		    (ifp->if_flags & IFF_RUNNING) == 0)
			neinit(ifp->if_unit);
		break;

#ifdef notdef
	case SIOCGHWADDR:
		bcopy((caddr_t)ns->ns_addr, (caddr_t) &ifr->ifr_data,
			sizeof(ns->ns_addr));
		break;
#endif

	default:
		error = EINVAL;
	}
	splx(s);
	return (error);
D 8
}

nesetaddr(ifp, sin)
	register struct ifnet *ifp;
	register struct sockaddr_in *sin;
{
#ifdef notdef
	ifp->if_addr = *(struct sockaddr *)sin;
	ifp->if_net = in_netof(sin->sin_addr);
	ifp->if_host[0] = in_lnaof(sin->sin_addr);
	if (nepaddr[ifp->if_unit][0] == '3')
		nepaddr[ifp->if_unit][0] = ifp->if_host[0] << 1;
	sin = (struct sockaddr_in *)&ifp->if_broadaddr;
	sin->sin_family = AF_INET;
	sin->sin_addr = in_makeaddr(ifp->if_net, INADDR_ANY);
	ifp->if_flags |= IFF_BROADCAST;
#endif
E 8
}
#endif
E 1
