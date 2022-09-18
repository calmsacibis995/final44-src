/*
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_wd8003.c,v $
 * Revision 2.1.1.7  90/11/27  13:43:18  rvb
 * 	Synched 2.5 & 3.0 at I386q (r2.1.1.7) & XMK35 (r2.3)
 * 	[90/11/15            rvb]
 * 
 * Revision 2.2  90/10/01  14:23:09  jeffreyh
 * 	Changes for MACH_KERNEL. 
 * 	initial checkin.
 * 	[90/09/27  18:22:09  jeffreyh]
 *
 * Revision 2.1.1.6  90/09/18  08:38:39  rvb
 * 	Unfortunately, the switches to bank 0 seem necessary so are back
 * 	in.
 * 	[90/09/08            rvb]
 * 
 * Revision 2.1.1.5  90/08/25  15:42:58  rvb
 * 	Use take_<>_irq() vs direct manipulations of ivect and friends.
 * 	[90/08/20            rvb]
 * 
 * 	Flush unnecessary switches to bank 0. Use error counters
 * 	vs printouts.  Fix DSF_RUNNING.  Some more cleanup.
 * 	[90/08/14            rvb]
 * 
 * Revision 2.1.1.4  90/07/28  10:00:40  rvb
 * 	Get correct counter offsets
 * 
 * Revision 2.1.1.3  90/07/27  17:16:05  rvb
 * 	No multicast for now.
 * 
 * Revision 2.1.1.2  90/07/27  11:25:11  rvb
 * 	Add boardID support for wd80xxyyy family of boards.	[rweiss]
 * 	Bunch of cleanup and ...		[rweiss&rvb]
 * 
 * Revision 2.1.1.1  90/07/10  11:44:46  rvb
 * 	Added to system.
 * 	[90/07/06            rvb]
 *
 *
 *   Author: Ron Weiss (rweiss)
 *
 */
 
/* NOTE:
 *	There are three outstanding bug/features in this implementation.
 * They may even be hardware misfeatures.  The conditions are registered
 * by counters maintained by the software.
 *	1: over_write is a condition that means that the board wants to store
 * packets, but there is no room.  So new packets are lost.  What seems to
 * be happening is that we get an over_write condition, but there are no
 * or just a few packets in the board's ram.  Also it seems that we get
 * several over_writes in a row.
 *	2: Since there is only one transmit buffer, we need a lock to indicate
 * whether it is in use.  We clear this lock when we get a transmit interrupt.
 * Sometimes we go to transmit and although there is no transmit in progress,
 * the lock is set.  (In this case, we just ignore the lock.)  It would look
 * like we can miss transmit interrupts?
 *	3: We tried to clean up the unnecessary switches to bank 0.  
 * Unfortunately, when you do an ifconfig "down", the system tend to lock up
 * a few seconds later (this was when DSF_RUNNING) was not being set before.
 * But even with DSF_RUNNING, on an EISA bus machine we ALWAYS lock up after
 * a few seconds. 
 */

/*
 * Western Digital 8003E Mach Ethernet driver (for intel 80386)
 * Copyright (c) 1990 by Open Software Foundation (OSF).
 */

/*
  Copyright 1990 by Open Software Foundation,
Cambridge, MA.

		All Rights Reserved

  Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appears in all copies and
that both the copyright notice and this permission notice appear in
supporting documentation, and that the name of OSF or Open Software
Foundation not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

  OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#define IF_CNTRS	MACH
#include	<wd8003.h>

#ifdef	MACH_KERNEL
#include	<kern/time_out.h>
#include	<device/device_types.h>
#include	<device/errno.h>
#include	<device/io_req.h>
#include	<device/if_hdr.h>
#include	<device/if_ether.h>
#include	<device/net_status.h>
#include	<device/net_io.h>
#else	MACH_KERNEL
#include	<sys/param.h>
#include	<mach/machine/vm_param.h>
#include	<sys/systm.h>
#include	<sys/mbuf.h>
#include	<sys/buf.h>
#include	<sys/protosw.h>
#include	<sys/socket.h>
#include	<sys/vmmac.h>
#include	<sys/ioctl.h>
#include	<sys/errno.h>
#include	<sys/syslog.h>

#include	<net/if.h>
#include	<net/netisr.h>
#include	<net/route.h>

#ifdef	INET
#include	<netinet/in.h>
#include	<netinet/in_systm.h>
#include	<netinet/in_var.h>
#include	<netinet/ip.h>
#include	<netinet/if_ether.h>
#endif

#ifdef	NS
#include	<netns/ns.h>
#include	<netns/ns_if.h>
#endif
#endif	MACH_KERNEL

#include	<i386/ipl.h>
#include	<i386at/atbus.h>
#include	<i386at/if_wd8003.h>

#define	SPLNET	spl6


int	wd8003probe();
int	wd8003attach();
int	wd8003intr();
int	wd8003init();
int	wd8003output();
int	wd8003ioctl();
int	wd8003reset();
int     wd8003rcv();
int	wd8003watch();
int     wd8003get_CURR();
int     wd8003over_write();

int	(*wd8003intrs[])() = {	wd8003intr, 0};

struct	isa_dev	*wd8003info[NWD8003];

struct	isa_driver	wd8003driver =
	{wd8003probe, 0, wd8003attach, "wd8003", 0, 0, 0};

int	watchdog_id;

typedef struct {
#ifdef	MACH_KERNEL
	struct	ifnet	ds_if;		/* generic interface header */
	u_char	ds_addr[6];		/* Ethernet hardware address */
#else	MACH_KERNEL
	struct	arpcom	wd8003_ac;
#define	ds_if	wd8003_ac.ac_if
#define	ds_addr	wd8003_ac.ac_enaddr
#endif	MACH_KERNEL
	int	flags;
	int     timer;
	int     interrupt;
	char 	*base;
	u_char   address[ETHER_ADDR_SIZE];
#if	CMUCS
	short	mode;
#endif	CMUCS
	int     tbusy;
	char    *sram;  /* beginning of the shared memory RAM buffer */
	int     read_nxtpkt_ptr; /* pointer to next packet available */
	int     pstart_hold;     /* page start hold */
	int     pstop_hold;      /* page stop hold */
	int     tpsr_hold;       /* transmit page start hold */
	int     fifo_depth;      /* NIC fifo threshold */
	int     board_id;
}
wd8003_softc_t;

wd8003_softc_t	wd8003_softc[NWD8003];

struct wd8003_cntrs {
u_int	ovw,
	jabber,
	crc,
	frame,
	miss,
	fifo,
	rcv;
u_int	xmt,
	xmti,
	busy,
	heart;
} wd8003_cntrs[NWD8003];

#ifdef	IF_CNTRS
int wd_narp = 1, wd_arp = 0;
int wd_ein[32], wd_eout[32]; 
int wd_lin[128/8], wd_lout[128/8]; 
static
log_2(no)
unsigned long no;
{
	return ({ unsigned long _temp__;
		asm("bsr %1, %0; jne 0f; xorl %0, %0; 0:" :
		    "=r" (_temp__) : "a" (no));
		_temp__;});
}
#endif	IF_CNTRS

int  imr_hold = PRXE|PTXE|RXEE|TXEE|OVWE|CNTE;  /* Interrupts mask bits */

/*
 * wd8003probe:
 *
 *	This function "probes" or checks for the wd8003 board on the bus to see
 *	if it is there.  As far as I can tell, the best break between this
 *	routine and the attach code is to simply determine whether the board
 *      is configured in properly. Currently my approach to this is to test the
 *      base I/O special offset for the Western Digital unique byte sequence
 *      identifier.  If the bytes match we assume board is there.
 *	The config code expects to see a successful return from the probe
 *	routine before attach will be called.
 *
 * input	: address device is mapped to, and unit # being checked
 * output	: a '1' is returned if the board exists, and a 0 otherwise
 *
 */

wd8003probe(dev)
struct isa_dev	*dev;
{
	caddr_t	base = dev->dev_addr;
	int	unit = dev->dev_unit;

	if ((unit < 0) || (unit > NWD8003)) {
		printf("wd8003 ethernet board %d out of range\n", unit);
		return(0);
	}
	if ((u_char) inb(base+LAR) == (u_char) WD_NODE_ADDR_0)
		if ((u_char) inb(base+LAR2) == (u_char) WD_NODE_ADDR_1)
			if ((u_char) inb(base+LAR3) == (u_char) WD_NODE_ADDR_2) {
				wd8003_softc[unit].base = base;
				return (1);
			}  /* checks the address of the board to verify that it is a WD */
	return(0);

}

/*
 * wd8003attach:
 *
 *	This function attaches a WD8003 board to the "system".  The rest of
 *	runtime structures are initialized here (this routine is called after
 *	a successful probe of the board).  Once the ethernet address is read
 *	and stored, the board's ifnet structure is attached and readied.
 *
 * input	: isa_dev structure setup in autoconfig
 * output	: board structs and ifnet is setup
 *
 */

wd8003attach(dev)
struct isa_dev	*dev;
{
	wd8003_softc_t	*sp;
	struct	ifnet	*ifp;
	u_char		unit;
	caddr_t		base;
	extern int	tcp_recvspace;
	int             temp;

	take_dev_irq(dev);
	unit = (u_char)dev->dev_unit;
	printf("wd%d:  port = %x, spl = %d, pic = %d. ",
		unit, dev->dev_addr, dev->dev_spl, dev->dev_pic);
	wd8003info[unit] = dev;

	sp = &wd8003_softc[unit];
	(volatile char *)sp->sram =
	    (volatile char *) phystokv(dev->dev_start);
	dev->dev_addr = (char *) phystokv(dev->dev_addr);
	sp->timer = -1;
	sp->flags = 0;
	sp->mode  = 0;
	base = sp->base;
	*(sp->ds_addr)      = *(sp->address)      = inb(base+LAR);
	*(sp->ds_addr + 1)  = *(sp->address + 1)  = inb(base+LAR + 1);
	*(sp->ds_addr + 2)  = *(sp->address + 2)  = inb(base+LAR + 2);
	*(sp->ds_addr + 3)  = *(sp->address + 3)  = inb(base+LAR + 3);
	*(sp->ds_addr + 4)  = *(sp->address + 4)  = inb(base+LAR + 4);
	*(sp->ds_addr + 5)  = *(sp->address + 5)  = inb(base+LAR + 5);

	outb(base+MSR, MENB);               /* enable mem access to board */
	wd8003_softc[unit].board_id = wd80xxget_board_id(unit);
	if (!wd8003hwrst(unit)) {
		printf("Could not reset WD8003 board %d in attach\n", unit);
		return;
	}

	printf("ethernet id [%x:%x:%x:%x:%x:%x]\n",
		sp->address[0],sp->address[1],sp->address[2],
		sp->address[3],sp->address[4],sp->address[5]);
	ifp = &(sp->ds_if);
	ifp->if_unit = unit;
	ifp->if_mtu = ETHERMTU;
	ifp->if_flags = IFF_BROADCAST;
#ifdef	MACH_KERNEL
	ifp->if_header_size = sizeof(struct ether_header);
	ifp->if_header_format = HDR_ETHERNET;
	ifp->if_address_size = 6;
	ifp->if_address = (char *)&sp->address[0];
	if_init_queues(ifp);
#else	MACH_KERNEL
	ifp->if_name = "wd";
	ifp->if_init = wd8003init;
	ifp->if_output = wd8003output;
	ifp->if_ioctl = wd8003ioctl;
	ifp->if_reset = wd8003reset;
	ifp->if_next = NULL;
	if_attach(ifp);
#ifdef notdef
	watchdog_id = timeout(wd8003watch, &(ifp->if_unit), 20*HZ);
#endif
#endif	MACH_KERNEL
}

/*
 * wd8003watch():
 *
 */

int
wd8003watch(b_ptr)
caddr_t	b_ptr;
{
	int	x,
		y,
		opri,
		unit;
	int     temp_cr;
	caddr_t base;

	unit = *b_ptr;
#ifdef	MACH_KERNEL
	timeout(wd8003watch,b_ptr,20*HZ);
#else	MACH_KERNEL
	watchdog_id = timeout(wd8003watch,b_ptr,20*HZ);
#endif	MACH_KERNEL
	base = wd8003_softc[unit].base;
	temp_cr = inb(base+CR);
	outb(base + CR, (temp_cr & 0x3f) | PS0);
	printf("<<< ISR=%x CURR=%x rdnxt=%x BNDY=%x>>> ", inb(base + ISR),
		wd8003get_CURR(unit), wd8003_softc[unit].read_nxtpkt_ptr,
		inb(base+BNDY));
	outb(base+CR,temp_cr);
}

#ifdef	MACH_KERNEL
int wd8003start();	/* forward */

/*ARGSUSED*/
wd8003open(dev, flag)
	dev_t	dev;
	int	flag;
{
	register int	unit = minor(dev);

	if (unit < 0 || unit >= NWD8003 ||
		wd8003_softc[unit].base == 0)
	    return (ENXIO);

	wd8003_softc[unit].ds_if.if_flags |= IFF_UP;
	wd8003init(unit);
	return(0);
}



wd8003output(dev, ior)
	dev_t		dev;
	io_req_t	ior;
{
	register int	unit = minor(dev);

	if (unit < 0 || unit >= NWD8003 ||
		wd8003_softc[unit].base == 0)
	    return (ENXIO);
	return (net_write(&wd8003_softc[unit].ds_if, wd8003start, ior));
}

wd8003setinput(dev, receive_port, priority, filter, filter_count)
	dev_t		dev;
	mach_port_t	receive_port;
	int		priority;
	filter_t	filter[];
	unsigned int	filter_count;
{
	register int unit = minor(dev);

	if (unit < 0 || unit >= NWD8003 ||
		wd8003_softc[unit].base == 0)
	    return (ENXIO);

	return (net_set_filter(&wd8003_softc[unit].ds_if,
			receive_port, priority,
			filter, filter_count));
}

#else	MACH_KERNEL
/*
 * wd8003output:
 *
 *	This routine is called by the "if" layer to output a packet to
 *	the network.  This code resolves the local ethernet address, and
 *	puts it into the mbuf if there is room.  If not, then a new mbuf
 *	is allocated with the header information and precedes the data
 *	to be transmitted.  The routine wd8003xmt() which actually
 *      transmits the data expects the ethernet header to precede the
 *      data in the mbuf.
 *
 * input:	ifnet structure pointer, an mbuf with data, and address
 *		to be resolved
 * output:	mbuf is updated to hold enet address, or a new mbuf
 *	  	with the address is added
 *
 */

wd8003output(ifp, m0, dst)
struct ifnet	*ifp;
struct mbuf	*m0;
struct sockaddr *dst;
{
	register wd8003_softc_t		*is = &wd8003_softc[ifp->if_unit];
	u_char				edst[6];
	struct in_addr 			idst;
	register struct mbuf		*m = m0;
	register struct ether_header	*eh;
	register int 			off;
	int				usetrailers;
	int 				type, opri, error;

	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
		printf("\nWD8003 Turning off board %d\n", ifp->if_unit);
		wd8003intoff(ifp->if_unit);
		error = ENETDOWN;
		goto bad;
	}
	switch (dst->sa_family) {
#ifdef INET
	case AF_INET:
		idst = ((struct sockaddr_in *)dst)->sin_addr;
		if (!arpresolve(&is->wd8003_ac, m, &idst, edst, &usetrailers)){
			return (0);	/* if not yet resolved */
		}
		off = ntohs((u_short)mtod(m, struct ip *)->ip_len) - m->m_len;
		if (usetrailers && off > 0 && (off & 0x1ff) == 0 &&
		    m->m_off >= MMINOFF + 2 * sizeof (u_short)) {
			type = ETHERTYPE_TRAIL + (off>>9);
			m->m_off -= 2 * sizeof (u_short);
			m->m_len += 2 * sizeof (u_short);
			*mtod(m, u_short *) = htons((u_short)ETHERTYPE_IP);
			*(mtod(m, u_short *) + 1) = htons((u_short)m->m_len);
			goto gottrailertype;
		}
		type = ETHERTYPE_IP;
		off = 0;
		goto gottype;
#endif
#ifdef NS
	case AF_NS:
		type = ETHERTYPE_NS;
		bcopy((caddr_t)&(((struct sockaddr_ns *)dst)->sns_addr.x_host),
		      (caddr_t)edst,
		      sizeof (edst));
		off = 0;
		goto gottype;
#endif
	case AF_UNSPEC:
		eh = (struct ether_header *)dst->sa_data;
		bcopy((caddr_t)eh->ether_dhost, (caddr_t)edst, sizeof (edst));
		type = eh->ether_type;
		goto gottype;
	default:
		printf("wd8003%d: can't handle af%d\n", ifp->if_unit,
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
	eh->ether_type = htons((u_short)type);
	bcopy((caddr_t)edst, (caddr_t)eh->ether_dhost, sizeof (edst));
	bcopy((caddr_t)is->address,
	      (caddr_t)eh->ether_shost,
	      sizeof(edst));
	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
	opri = SPLNET();
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
		splx(opri);
		m_freem(m);
		return (ENOBUFS);
	}
	IF_ENQUEUE(&ifp->if_snd, m);
	/*
 	 * Some action needs to be added here for checking whether the
	 * board is already transmitting.  If it is, we don't want to
 	 * start it up (ie call wd8003start()).  We will attempt to send
 	 * packets that are queued up after an interrupt occurs.  Some
 	 * flag checking action has to happen here and/or in the start
 	 * routine.  This note is here to remind me that some thought
 	 * is needed and there is a potential problem here.
	 *
	 */
	wd8003start(ifp->if_unit);
	splx(opri);
	return (0);
bad:
	m_freem(m0);
	return (error);
}
#endif MACH_KERNEL

/*
 * wd8003reset:
 *
 *	This routine is in part an entry point for the "if" code.  Since most
 *	of the actual initialization has already (we hope already) been done
 *	by calling wd8003attach().
 *
 * input	: unit number or board number to reset
 * output	: board is reset
 *
 */

int
wd8003reset(unit)
int	unit;
{

	wd8003_softc[unit].ds_if.if_flags &= ~IFF_RUNNING;
	return(wd8003init(unit));
}

/*
 * wd8003init:
 *
 *	Another routine that interfaces the "if" layer to this driver.
 *	Simply resets the structures that are used by "upper layers".
 *	As well as calling wd8003hwrst that does reset the wd8003 board.
 *
 * input	: board number
 * output	: structures (if structs) and board are reset
 *
 */

int
wd8003init(unit)
int	unit;
{
	struct	ifnet	*ifp;
	int		stat;
	unsigned long	oldpri;

	ifp = &(wd8003_softc[unit].ds_if);
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
	if (ifp->if_addrlist == (struct ifaddr *)0) {
		return;
	}
#endif	MACH_KERNEL
	oldpri = SPLNET();
	if ((stat = wd8003hwrst(unit)) == TRUE) {
		wd8003_softc[unit].ds_if.if_flags |= IFF_RUNNING;
		wd8003_softc[unit].flags |= DSF_RUNNING;
		wd8003_softc[unit].tbusy = 0;
		wd8003start(unit);
	} else
		printf("WD8003 trouble resetting board %d\n", unit);
	wd8003_softc[unit].timer = 5;
	splx(oldpri);
	return(stat);
}

/*
 * wd8003start:
 *
 *	This is yet another interface routine that simply tries to output a
 *	in an mbuf after a reset.
 *
 * input	: board number
 * output	: stuff sent to board if any there
 *
 */

wd8003start(unit)
int	unit;
{
	register wd8003_softc_t *is = &wd8003_softc[unit];
	struct	ifnet		*ifp;
#ifdef	MACH_KERNEL
	io_req_t	m;
#else	MACH_KERNEL
	struct	mbuf	*m;
#endif	MACH_KERNEL

	if (is->tbusy) {
		caddr_t base = wd8003_softc[unit].base;
		if (!(inb(base+CR) & TXP)) {
			is->tbusy = 0;
			wd8003_cntrs[unit].busy++;
		} else
			return;
	}

	ifp = &(wd8003_softc[unit].ds_if);

	IF_DEQUEUE(&ifp->if_snd, m);
#ifdef	MACH_KERNEL
	if (m != 0)
#else	MACH_KERNEL
	if (m != (struct mbuf *)0)
#endif	MACH_KERNEL
	{
		is->tbusy++;
		wd8003_cntrs[unit].xmt++;
		wd8003xmt(unit, m);
	}
}

#ifdef	MACH_KERNEL
/*ARGSUSED*/
wd8003getstat(dev, flavor, status, count)
	dev_t		dev;
	int		flavor;
	dev_status_t	status;		/* pointer to OUT array */
	unsigned int	*count;		/* out */
{
	register int	unit = minor(dev);

	if (unit < 0 || unit >= NWD8003 ||
		wd8003_softc[unit].base == 0)
	    return (ENXIO);

	return (net_getstat(&wd8003_softc[unit].ds_if,
			    flavor,
			    status,
			    count));
}
wd8003setstat(dev, flavor, status, count)
	dev_t		dev;
	int		flavor;
	dev_status_t	status;
	unsigned int	count;
{
	register int	unit = minor(dev);
	register wd8003_softc_t *sp;

	if (unit < 0 || unit >= NWD8003 ||
		wd8003_softc[unit].base == 0)
	    return (ENXIO);

	sp = &wd8003_softc[unit];

	switch (flavor) {
	    case NET_STATUS:
	    {
		/*
		 * All we can change are flags, and not many of those.
		 */
		register struct net_status *ns = (struct net_status *)status;
		int	mode = 0;

		if (count < NET_STATUS_COUNT)
		    return (D_INVALID_SIZE);

		if (ns->flags & IFF_ALLMULTI)
		    mode |= MOD_ENAL;
		if (ns->flags & IFF_PROMISC)
		    mode |= MOD_PROM;

		/*
		 * Force a complete reset if the receive mode changes
		 * so that these take effect immediately.
		 */
		if (sp->mode != mode) {
		    sp->mode = mode;
		    if (sp->flags & DSF_RUNNING) {
			sp->flags &= ~(DSF_LOCK | DSF_RUNNING);
			wd8003init(unit);
		    }
		}
		break;
	    }

	    default:
		return (D_INVALID_OPERATION);
	}
	return (D_SUCCESS);
}
#else	MACH_KERNEL
/*
 * wd8003ioctl:
 *
 *	This routine processes an ioctl request from the "if" layer
 *	above.
 *
 * input	: pointer the appropriate "if" struct, command, and data
 * output	: based on command appropriate action is taken on the
 *	 	  wd8003 board(s) or related structures
 * return	: error is returned containing exit conditions
 *
 */

int
wd8003ioctl(ifp, cmd, data)
struct ifnet	*ifp;
int	cmd;
caddr_t	data;
{
	register struct ifaddr	*ifa = (struct ifaddr *)data;
	register wd8003_softc_t *is;
	int			opri, error;
	short			 mode = 0;

	is = &wd8003_softc[ifp->if_unit];
	opri = SPLNET();
	error = 0;
	switch (cmd) {
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		wd8003init(ifp->if_unit);
		switch (ifa->ifa_addr.sa_family) {
#ifdef INET
		case AF_INET:
			((struct arpcom *)ifp)->ac_ipaddr =
			    IA_SIN(ifa)->sin_addr;
			arpwhohas((struct arpcom *)ifp, &IA_SIN(ifa)->sin_addr);
			break;
#endif
#ifdef NS
		case AF_NS:
			{
				register struct ns_addr *ina =
				    &(IA_SNS(ifa)->sns_addr);
				if (ns_nullhost(*ina))
					ina->x_host =
					    *(union ns_host *)(ds->ds_addr);
				else
					wd8003seteh(ina->x_host.c_host,
						    wd8003_softc[ifp->if_unit].base);
				break;
			}
#endif
		}
		break;
	case SIOCSIFFLAGS:
#if	CMUCS
		if (ifp->if_flags & IFF_ALLMULTI)
			mode |= MOD_ENAL;
		if (ifp->if_flags & IFF_PROMISC)
			mode |= MOD_PROM;
		/*
		 * force a complete reset if the receive multicast/
		 * promiscuous mode changes so that these take
		 * effect immediately.
		 *
		 */
		if (is->mode != mode) {
			is->mode = mode;
			if (is->flags & DSF_RUNNING) {
				is->flags &=
				    ~(DSF_LOCK|DSF_RUNNING);
				wd8003init(ifp->if_unit);
			}
		}
#endif	CMUCS
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    is->flags & DSF_RUNNING) {
			printf("\nWD8003 ioctl: turning off board %d\n",
			        ifp->if_unit);
			is->flags &= ~(DSF_LOCK | DSF_RUNNING);
			is->timer = -1;
			wd8003intoff(ifp->if_unit);
			wd8003over_write(ifp->if_unit);
		} else
		    if (ifp->if_flags & IFF_UP &&
		    (is->flags & DSF_RUNNING) == 0)
			wd8003init(ifp->if_unit);
		break;
#ifdef	IF_CNTRS
	case SIOCCIFCNTRS:
		if (!suser()) {
			error = EPERM;
			break;
		}
		bzero((caddr_t)wd_ein, sizeof (wd_ein));
		bzero((caddr_t)wd_eout, sizeof (wd_eout));
		bzero((caddr_t)wd_lin, sizeof (wd_lin));
		bzero((caddr_t)wd_lout, sizeof (wd_lout));
		bzero((caddr_t)&wd_arp, sizeof (int));
		bzero((caddr_t)&wd8003_cntrs, sizeof (wd8003_cntrs));
		break;
#endif	IF_CNTRS
	default:
		error = EINVAL;
	}
	splx(opri);
	return (error);
}
#endif	MACH_KERNEL

/*
 * wd8003hwrst:
 *
 *	This routine resets the wd8003 board that corresponds to the
 *	board number passed in.
 *
 * input	: board number to do a hardware reset
 * output	: board is reset
 *
 */

int
wd8003hwrst(unit)
int unit;
{
	caddr_t base = wd8003_softc[unit].base;
	int	count;
	u_char	stat;

	if (wd8003config(unit) == FALSE) {
		printf("wd8003hwrst(): failed to config\n");
		return(FALSE);
	}

	outb (base+CR, STA|PS0|ABR);
	/* start board again, with page register 0, and cancel reset */

	return(TRUE);
}

/*
 * wd8003intr:
 *
 *	This function is the interrupt handler for the wd8003 ethernet
 *	board.  This routine will be called whenever either a packet
 *	is received, or a packet has successfully been transfered and
 *	the unit is ready to transmit another packet.
 *
 * input	: board number that interrupted
 * output	: either a packet is received, or a packet is transfered
 *
 */
int
wd8003intr(unit)
{
	int	opri, i;
	int     isr_status;
	int     temp_cr;
	caddr_t base = wd8003_softc[unit].base;

	temp_cr = inb(base+CR);
	outb(base+CR, (temp_cr & 0x3f) | PS0);
	outb(base+IMR, 0);                   /* stop board interrupts */
	outb(base+CR, temp_cr);
	while (isr_status = inb(base+ISR)) {
		outb(base+ISR, isr_status);          /* clear interrupt status */

		if ((isr_status & (OVW|RXE)) == RXE) {
			int rsr = inb(base+RSR);
			if (rsr & DFR) wd8003_cntrs[unit].jabber++;
			if (rsr & ~(DFR|PHY|FAE|CRC|PRX))
				printf("wd%d: isr = %x, RSR = %x\n",
					unit, isr_status, rsr);
		} else if (isr_status & OVW) {
			wd8003_cntrs[unit].ovw++;
			wd8003over_write(unit);
		}
		if (isr_status & PRX) {			/* DFR & PRX is possible */
		 	wd8003rcv(unit);
		}

	        if (isr_status & TXE) {
			int tsr = inb(base+TSR);
			tsr &= ~0x2;		/* unadvertised special */
			if (tsr == (CDH|ABT))
				wd8003_cntrs[unit].heart++;
			else
				printf("wd%d: isr = %x, TSR = %x\n",
					unit, isr_status, tsr);
			wd8003_softc[unit].tbusy = 0;
	 		wd8003start(unit);
	        } else if (isr_status & PTX) {
			wd8003_cntrs[unit].xmti++;
			wd8003_softc[unit].tbusy = 0;
	 		wd8003start(unit);
		}

		if (isr_status & CNT) {
			int c0 = inb(base+CNTR0);
			int c1 = inb(base+CNTR1);
			int c2 = inb(base+CNTR2);
			wd8003_cntrs[unit].frame += c0;
			wd8003_cntrs[unit].crc += c1;
			wd8003_cntrs[unit].miss += c2;
#ifdef	COUNTERS
			printf("wd%d: isr = %x, FRAME %x, CRC %x, MISS %x\n",
				unit, isr_status, c0, c1, c2);
			printf("wd%d: TOTAL   , FRAME %x, CRC %x, MISS %x\n",
				unit, wd8003_cntrs[unit].frame,
				wd8003_cntrs[unit].crc,
				wd8003_cntrs[unit].miss);
#endif	COUNTERS
			outb(base+ISR, isr_status);	/* clear interrupt status again */
		}
	}
	temp_cr=inb(base+CR);
	outb(base+CR, (temp_cr & 0x3f) | PS0);
	outb(base+IMR, imr_hold);
	outb(base+CR, temp_cr);
	return(0);
}

/*
 *  Called if on board buffer has been completely filled by wd8003intr.  It stops
 *  the board, reads in all the buffers that are currently in the buffer, and
 *  then restart board.
 */
wd8003over_write(unit)
int unit;
{
	caddr_t	base = wd8003_softc[unit].base;
	int	no;

	outb(base+CR, ABR|STP|PS0);        /* clear the receive buffer */
	outb(base+RBCR0, 0);
	outb(base+RBCR1, 0);
	while(!(inb(base+ISR) & RST));     /* wait for reset to complete */
	no = wd8003rcv(unit);
#ifdef	OVWBUG
	printf("wd%d: WD8003 OVW ... %d.\n", unit, no);
#endif	OVWBUG
	outb(base+TCR, LB1);               /* External loopback mode */
	outb(base+CR, ABR|STA|PS0);
	outb(base+TCR, 0);
	return;
}

/*
 * wd8003rcv:
 *
 *	This routine is called by the interrupt handler to initiate a
 *	packet transfer from the board to the "if" layer above this
 *	driver.  This routine checks if a buffer has been successfully
 *	received by the wd8003.  If so, it does the actual transfer of the
 *      board data (including the ethernet header) into a packet (consisting
 *      of an mbuf chain) and enqueues it to a higher level.
 *      Then check again whether there are any packets in the receive ring,
 *      if so, read the next packet, until there are no more.
 *
 * input	: number of the board to check
 * output	: if a packet is available, it is "sent up"
 */
wd8003rcv(unit)
int unit;
{
	register wd8003_softc_t	*is = &wd8003_softc[unit];
	register struct ifnet	*ifp = &is->ds_if;
	caddr_t			base = is->base;
	int			packets = 0;
	struct ether_header	eh;
	u_short			mlen, len, bytes_in_mbuf, bytes;
	u_short			remaining;
	int			temp_cr;
	u_char			*mb_p;


	/* calculation of pkt size */
	int nic_overcount;         /* NIC says 1 or 2 more than we need */
	int pkt_size;              /* calculated size of received data */
	int wrap_size;             /* size of data before wrapping it */
	int header_nxtpkt_ptr;     /* NIC's next pkt ptr in rcv header */
	int low_byte_count;        /* low byte count of read from rcv header */
	int high_byte_count;       /* calculated high byte count */


	volatile char *sram_nxtpkt_ptr;   /* mem location of next packet */
	volatile char *sram_getdata_ptr;  /* next location to be read */
#ifdef	MACH_KERNEL
	ipc_kmsg_t	new_kmsg;
	struct ether_header *ehp;
	struct packet_header *pkt;
#else	MACH_KERNEL
	struct mbuf *m, *tm;              /* initial allocation of mem; temp */
#endif	MACH_KERNEL


	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
		temp_cr = inb(base+CR); /* get current CR value */
		outb(base+CR,((temp_cr & 0x3F)|PS0|STP));
		outb(base+IMR, 0);      /* Interrupt Mask Register  */
		outb(base+CR, temp_cr);
		return -1;
	}

	while(is->read_nxtpkt_ptr != wd8003get_CURR(unit))   {

		/* while there is a packet to read from the buffer */

		if ((is->read_nxtpkt_ptr < is->pstart_hold) ||
		    (is->read_nxtpkt_ptr >= is->pstop_hold)) {
			wd8003hwrst(unit);
			return -1;
		}    /* if next packet pointer is out of receive ring bounds */

		packets++;
		wd8003_cntrs[unit].rcv++;
		sram_nxtpkt_ptr = (char *) (is->sram + (is->read_nxtpkt_ptr << 8));

		/* get packet size and location of next packet */
		header_nxtpkt_ptr = *(sram_nxtpkt_ptr + 1);
		header_nxtpkt_ptr &= 0xFF;
		low_byte_count = *(sram_nxtpkt_ptr + 2);
		low_byte_count &= 0xFF;

		if ((low_byte_count + NIC_HEADER_SIZE) > NIC_PAGE_SIZE)
			nic_overcount = 2;
		else
			nic_overcount = 1;
		if (header_nxtpkt_ptr > is->read_nxtpkt_ptr) {
			wrap_size = 0;
			high_byte_count = header_nxtpkt_ptr - is->read_nxtpkt_ptr -
			    nic_overcount;
		} else {
			wrap_size = (int) (is->pstop_hold - is->read_nxtpkt_ptr - nic_overcount);
			high_byte_count = is->pstop_hold - is->read_nxtpkt_ptr +
			    header_nxtpkt_ptr - is->pstart_hold - nic_overcount;
		}

		pkt_size = (high_byte_count << 8) | (low_byte_count & 0xFF);
		len = pkt_size;

		len -= sizeof(struct ether_header);
		sram_getdata_ptr = sram_nxtpkt_ptr + NIC_HEADER_SIZE;

		bcopy16 (sram_getdata_ptr,
			     &eh,
			     sizeof(struct ether_header));
		sram_getdata_ptr += sizeof(struct ether_header);
#ifdef	MACH_KERNEL
	  len = 0;/*sizeof(struct ether_header);*/
	  NET_KMSG_GET(new_kmsg);
	  if (new_kmsg == IKM_NULL) {
	    /*
	     * Drop the packet.
	     */
	    is->ds_if.if_rcvdrops++;
			    
	    /*
	     * not only do we want to return, we need to drop the packet on
	     * the floor to clear the interrupt.	     */
	    wd8003lost_frame(unit);
	    return;/* packets;*/
	  }

	  
	  ehp = (struct ether_header *) (&net_kmsg(new_kmsg)->header[0]);
	  pkt = (struct packet_header *) (&net_kmsg(new_kmsg)->packet[0]);
			/*
			 * Get header.
			 */
	  *ehp = eh;

			/*
			 * Get body
			 */
	
	  while (len < pkt_size) {
	    if (sram_getdata_ptr + pkt_size >=
		(volatile char *) (is->sram + (is->pstop_hold << 8))) {
	      /* if needs to wrap */
	      wrap_size = (int) (is->sram + (is->pstop_hold << 8) -
				 sram_getdata_ptr);
	      bcopy (sram_getdata_ptr,
		       (char *) (pkt + 1) + len, /* XXX Fix Me */
		       wrap_size);
              len += wrap_size;
	      sram_getdata_ptr = (volatile char *) (is->sram +
						    (is->pstart_hold << 8));
	    } else {   /* normal getting data from buffer */
	      bcopy (sram_getdata_ptr,
		       (char *) (pkt + 1) + len,
		       pkt_size);
	      sram_getdata_ptr += pkt_size;
              len += pkt_size;
	    }
	  }	
#else	MACH_KERNEL
#define NEW
#ifdef	NEW
		m = (struct mbuf *) 0;
		eh.ether_type = ntohs(eh.ether_type);
		MGET(m, M_DONTWAIT, MT_DATA);
		if (m == (struct mbuf *) 0) {
			printf("wd8003rcv: Lost frame\n");
				wd8003lost_frame(unit); /* update NIC pointers and registers */
				return packets;
		}
m->m_next = (struct mbuf *) 0;
		tm = m;
		m->m_len = MLEN;
		if (len > 2 * MLEN - sizeof (struct ifnet **)) {
			MCLGET(m);
		}
		*(mtod(tm, struct ifnet **)) = ifp;
		mlen = sizeof (struct ifnet **);
		bytes_in_mbuf = m->m_len - sizeof(struct ifnet **);
		mb_p = mtod(tm, u_char *) + sizeof (struct ifnet **);
		bytes = min(bytes_in_mbuf, len);
		remaining =  (int) (is->sram + (is->pstop_hold << 8) -
				    sram_getdata_ptr);
		bytes = min(bytes, remaining);
		do {
			bcopy16 (sram_getdata_ptr,  mb_p, bytes);
			mlen += bytes;

			if (!(bytes_in_mbuf -= bytes)) {
				MGET(tm->m_next, M_DONTWAIT, MT_DATA);
				tm = tm->m_next;
				if (tm == (struct mbuf *)0) {
					printf("wd8003rcv: No mbufs, lost frame\n");
					m_freem(m);              /* free the mbuf chain */
					wd8003lost_frame(unit);  /* update NIC pointers and registers */
					return;
				}
				mlen = 0;
				tm->m_len = MLEN;
				bytes_in_mbuf = MLEN;
				mb_p = mtod(tm, u_char *);
			} else
				mb_p += bytes;

			if (!(len  -= bytes)) {
				tm->m_len = mlen;
				break;
			} else if (bytes == remaining) {
				sram_getdata_ptr = (volatile char *) (is->sram +
				    (is->pstart_hold << 8));
				bytes = len;
				remaining = ETHERMTU;
			} else {
				sram_getdata_ptr += bytes;
			}

			bytes = min(bytes_in_mbuf, len);
		} while(1);
#else	NEW
		m = (struct mbuf *) 0;
		eh.ether_type = ntohs(eh.ether_type);

		while ( len ) {
			if (m == (struct mbuf *) 0) {
				m = m_get(M_DONTWAIT, MT_DATA);
				if (m == (struct mbuf *) 0) {
					printf("wd8003rcv: Lost frame\n");
					wd8003lost_frame(unit); /* update NIC pointers and registers */
					return packets;
				}
				tm = m;
				tm->m_off = MMINOFF;


				/*
				 * first mbuf in the packet must contain a pointer to the
				 * ifnet structure.  other mbufs that follow and make up
				 * the packet do not need this pointer in the mbuf.
				 *
				 */

				*(mtod(tm, struct ifnet **)) = ifp;
				tm->m_len = sizeof(struct ifnet **);

		        /* end of first buffer of packet */
			} else {
				tm->m_next = m_get(M_DONTWAIT, MT_DATA);
				tm = tm->m_next;
				if (tm == (struct mbuf *) 0) {
					printf("wd8003rcv: No mbufs, lost frame\n");
					m_freem(m);              /* free the mbuf chain */
					wd8003lost_frame(unit);  /* update NIC pointers and registers */
					return packets;
				}
				tm->m_off = MMINOFF;
				tm->m_len = 0;
			}

			tlen = MIN( MLEN - tm->m_len, len);
			/* size of mbuf so you know how much you can copy from board */
			tm->m_next = (struct mbuf *) 0;
			if (sram_getdata_ptr + tlen >=
			    (volatile char *) (is->sram + (is->pstop_hold << 8))) {
				/* if needs to wrap */
				wrap_size = (int) (is->sram + (is->pstop_hold << 8) -
				    sram_getdata_ptr);
				bcopy16 (sram_getdata_ptr,
					     mtod(tm, char*) + tm->m_len,
					     wrap_size);
				tm->m_len += wrap_size;
				len -= wrap_size;

				sram_getdata_ptr = (volatile char *) (is->sram +
				    (is->pstart_hold << 8));
			} else {   /* normal getting data from buffer */
			        bcopy16 (sram_getdata_ptr,
					     mtod(tm, char*) + tm->m_len,
					     tlen);
				sram_getdata_ptr += tlen;
				tm->m_len += tlen;
				len -= tlen;

			}
		}

#endif	NEW
#ifdef	IF_CNTRS
		wd_ein[log_2(pkt_size)]++;
		if (pkt_size < 128) wd_lin[pkt_size>>3]++;

		if (eh.ether_type == ETHERTYPE_ARP) {
			wd_arp++;
			if (wd_narp) {
				wd_ein[log_2(pkt_size)]--;
				if (pkt_size < 128) wd_lin[pkt_size>>3]--;
			}
		}
#endif	IF_CNTRS
#endif	MACH_KERNEL
		is->read_nxtpkt_ptr = *(sram_nxtpkt_ptr + 1);
		is->read_nxtpkt_ptr &= 0xFF;

		temp_cr = inb(base+CR);
		outb(base+CR, (temp_cr & 0x3f) | PS0);

		if (is->read_nxtpkt_ptr == wd8003get_CURR(unit))
			if (is->read_nxtpkt_ptr == is->pstart_hold)
				outb(base+BNDY, is->pstop_hold - 1);
			else
				outb(base+BNDY, is->read_nxtpkt_ptr - 1);
		else
			outb(base+BNDY, is->read_nxtpkt_ptr);

		outb(base+CR, temp_cr);

#ifdef	MACH_KERNEL
	    pkt->type = ehp->ether_type;
	    pkt->length = len - sizeof(struct ether_header)
			      + sizeof(struct packet_header);
	  /*
	   * Send the packet through the input filters.
	   */
	  net_filter(ifp, new_kmsg, pkt->length);
#else	MACH_KERNEL

		if (!wd8003send_packet_up(m, &eh, is))
			m_freem(m);
#endif	MACH_KERNEL
	}
	return packets;

}

#ifdef	MACH_KERNEL
#else	MACH_KERNEL
/*
 * Send a packet composed of an mbuf chain to the higher levels
 *
 */
wd8003send_packet_up(m, eh, is)
struct mbuf *m;
struct ether_header *eh;
wd8003_softc_t *is;
{
	register struct ifqueue	*inq;
        int			opri;

	switch (eh->ether_type) {
#ifdef INET
	case ETHERTYPE_IP:
		schednetisr(NETISR_IP);
		inq = &ipintrq;
		break;
	case ETHERTYPE_ARP:
		arpinput(&is->wd8003_ac, m);
		return(TRUE);
#endif
#ifdef NS
	case ETHERTYPE_NS:
		schednetisr(NETISR_NS);
		inq = &nsintrq;
		break;
#endif
	default:
		return(FALSE);
	}
	opri = SPLNET();
	if (IF_QFULL(inq)) {
		IF_DROP(inq);
		splx(opri);
		return(FALSE);
	}
	IF_ENQUEUE(inq, m);
	splx(opri);
	return(TRUE);
}
#endif	MACH_KERNEL

/*
 *  wd8003lost_frame:
 *  this routine called by wd8003read after memory for mbufs could not be
 *  allocated.  It sets the boundary pointers and registers to the next
 *  packet location.
 */

wd8003lost_frame(unit)
int unit;
{
	wd8003_softc_t *is = &wd8003_softc[unit];
	caddr_t        base = is->base;
	volatile char  *sram_nxtpkt_ptr;
	int            temp_cr;



	sram_nxtpkt_ptr = (volatile char *) (is->sram +
	    (is->read_nxtpkt_ptr << 8));

	is->read_nxtpkt_ptr = *(sram_nxtpkt_ptr + 1);
	is->read_nxtpkt_ptr &= 0xFF;

	temp_cr = inb(base+CR);
	outb(base+CR, (temp_cr & 0x3f) | PS0);

	/* update boundary register */
	if (is->read_nxtpkt_ptr == wd8003get_CURR(unit))
		if (is->read_nxtpkt_ptr == is->pstart_hold)
			outb(base+BNDY, is->pstop_hold - 1);
		else
			outb(base+BNDY, is->read_nxtpkt_ptr - 1);
	else
		outb(base+BNDY, is->read_nxtpkt_ptr);

	outb(base+CR, temp_cr);

	return;
}

/*
 * wd8003get_CURR():
 *
 * Returns the value of the register CURR, which points to the next
 * available space for NIC to receive from network unto receive ring.
 *
 */

int
wd8003get_CURR(unit)
int unit;
{
	caddr_t base = wd8003_softc[unit].base;
	int	temp_cr;
	int	ret_val;

	temp_cr = inb(base+CR);                  /* get current CR value */
	outb(base+CR, ((temp_cr & 0x3F) | PS1)); /* select page 1 registers */
	ret_val = inb(base+CURR);                /* read CURR value */
	outb(base+CR, temp_cr);
	return (ret_val & 0xFF);
}

/*
 * wd8003xmt:
 *
 *	This routine fills in the appropriate registers and memory
 *	locations on the WD8003 board and starts the board off on
 *	the transmit.
 *
 * input	: board number of interest, and a pointer to the mbuf
 * output	: board memory and registers are set for xfer and attention
 *
 */

wd8003xmt(unit, m)
int	unit;
#ifdef	MACH_KERNEL
io_req_t	m;
#else	MACH_KERNEL
struct	mbuf	*m;
#endif	MACH_KERNEL
{
	wd8003_softc_t		*is = &wd8003_softc[unit];
	caddr_t			base = is->base;
	struct ether_header	*eh;
	int			i;
	int			opri;
	u_short			count = 0;	/* amount of data already copied */
	volatile char		*sram_write_pkt;
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
	register struct	mbuf	*tm_p;
#endif	MACH_KERNEL
	/* begining of physical address of transmition buffer */

	sram_write_pkt = is->sram; /* init write to begining of SRAM buffer */

#ifdef	MACH_KERNEL
	count = m->io_count;
	bcopy (m->io_data, sram_write_pkt,  count);
#else	MACH_KERNEL
	for(tm_p = m; tm_p != (struct mbuf *)0; tm_p = tm_p->m_next)  {
		if (count + tm_p->m_len > ETHERMTU + sizeof (struct ether_header))
			break;
		if (tm_p->m_len == 0)
			continue;
		bcopy16 (mtod(tm_p, caddr_t),
			     sram_write_pkt + count,
			     tm_p->m_len);
		count += tm_p->m_len;
	}
#ifdef	IF_CNTRS
	wd_eout[log_2(count)]++;
	if (count < 128)  wd_lout[count>>3]++;
#endif	IF_CNTRS
#endif	MACH_KERNEL
	while (count < ETHERMIN+sizeof(struct ether_header)) {
		*(sram_write_pkt + count) = 0;
		count++;
	}
	outb(base+CR, ABR|STA|PS0);		/* select page 0 */
	outb(base+TPSR, is->tpsr_hold);		/* xmt page start at 0 of RAM */
	outb(base+TBCR1, count >> 8);		/* upper byte of count */
	outb(base+TBCR0, count & 0xFF);		/* lower byte of count */
	outb(base+CR, TXP|ABR|STA);		/* start transmission */

#ifdef	MACH_KERNEL
	iodone(m);
	m=0;
#else	MACH_KERNEL
	/* If this is a broadcast packet, loop it back to rcv.  */
	eh = mtod( m, struct ether_header *);
	for (i=0; ((i < 6) && (eh->ether_dhost[i] == 0xff)); i++)  ;
	if (i == 6) {
		if (!wd8003send_packet_up(m, eh, is))
			m_freem(m);
	} else
		m_freem(m);
#endif	MACH_KERNEL
	return;
}

/*
 * wd8003config:
 *
 *	This routine does a standard config of a wd8003 family board, with
 *      the proper modifications to different boards within this family.
 *
 */

wd8003config(unit)
int	unit;
{
	wd8003_softc_t *is = &wd8003_softc[unit];
	caddr_t   base = is->base;
	int       i;
	int       temp;
	int       count;
	int       RAMsize;
	volatile char  *RAMbase;
	int       addr_temp;

	is->tpsr_hold = 0;                           /* transmit page start hold */
	is->pstart_hold = 0x08;                      /* receive page start hold */
	is->fifo_depth = 0x08;                       /* NIC fifo threshold */

	switch (is->board_id & RAM_SIZE_MASK)
	  {
	  case RAM_SIZE_8K:  RAMsize = 0x2000;
	                     break;
	  case RAM_SIZE_16K: RAMsize = 0x4000;
	                     break;
	  case RAM_SIZE_32K: RAMsize = 0x8000;
	                     break;
	  case RAM_SIZE_64K: RAMsize = 0x10000;
	                     break;
	  default:           RAMsize = 0x2000;
                             break;
	                     /* if RAM size unknown, assume 8K */
	  }


       if (((is->board_id & WD8013EBT) == WD8013EBT) &&
	   (is->board_id & SLOT_16BIT)) {
	   outb(base+LAAR, LAN16ENB | LA19| MEM16ENB | SOFTINT);
	 }
                        /* enable 16 bit access from lan controller */

/***?? Should this be after MSR? */
/*	if (is->board_id & STATIC_ID_MASK & WD8003EB) ****/
           /***?? CONFIGURE THE 8003EB to tell it base io, etc... */

	RAMbase = wd8003info[unit]->dev_start;
	addr_temp = ((int)(RAMbase) >> 13) & 0x3f; /* convert to be written to MSR */

	outb(base+MSR, addr_temp | MENB);        /* initialize MSR */
	outb (base+CR, STP|ABR|PS0);             /* soft reset and page 0 */
	count = 0;
	while ((!(inb (base + ISR) & RST)) && (count < 0x1000))
		count++;
	temp = ((is->fifo_depth & 0x0c) << 3) | BMS;    /* fifo depth | not loopback */
	if (is->board_id & SLOT_16BIT)
	  temp |= WTS;				 /* word xfer select (16 bit cards ) */
	outb (base+DCR, temp);
	outb (base+RBCR0, 0);                    /* clear remote byte count */
	outb (base+RBCR1, 0);
	outb (base+RCR, AB);                     /* receive configuration register */
	outb (base+TCR, 0);
	/** Init of Receive Ring RAM Buffer **/
	outb (base+PSTART, is->pstart_hold);    /* recieve ring starts 2k into RAM */
	is->pstop_hold = (((int)RAMsize >> 8) & 0x0ff);      /* rcv page stop hold */
	outb (base+PSTOP, is->pstop_hold); /* stop at last RAM buffer rcv location */
	outb (base+BNDY, is->pstart_hold);      /* boundary pointer for page 0 */
	is->read_nxtpkt_ptr = is->pstart_hold + 1; /* internal next packet pointer */
	outb (base+ISR, 0xff);                  /* clear all interrupt status bits */
	outb (base+IMR, 0);                     /* no interrupts yet */
	outb (base+CR, STP|ABR|PS1);            /* maintain rst | sel page 1 */
	outb (base+CURR, is->read_nxtpkt_ptr);  /* Current page register */
	for(i=0; i<ETHER_ADDR_SIZE; i++) {
		outb (base+PAR0+i, wd8003_softc[unit].ds_addr[i]);
		/* load physical address */
		outb (base+MAR0+i, 0);       /* other multicast bits are 0 */
	}
	outb (base+MAR6, 0);                    /* more multicast address registers */
	outb (base+MAR7, 0);
	outb (base+CR, STA|PS0|ABR);            /* start NIC | select page 0 */
	outb (base+TCR, 0);                     /* allow receiving packets */
	outb (base+IMR, imr_hold);              /* Enable interrupts */

}

/*
 * wd8003intoff:
 *
 *	This function turns interrupts off for the wd8003 board indicated.
 *
 */

wd8003intoff(unit)
int unit;
{
	caddr_t base = wd8003_softc[unit].base;
	int	temp_cr = inb(base+CR);                  /* get current CR value */

	outb(base+CR,((temp_cr & 0x3F)|PS0|STP));
	outb(base+IMR, 0);                       /* Interrupt Mask Register  */
	outb(base+CR, temp_cr|STP);

}

/*
 *   wd80xxget_board_id:
 *
 *   determine which board is being used.
 *   Currently supports:
 *    wd8003E
 *    wd8003EBT
 *    wd8013EBT
 *
 */
int
wd80xxget_board_id(unit)
int unit;
{

      wd8003_softc_t *sp = &wd8003_softc[unit];
      caddr_t        base = sp->base;
      long           board_id = 0;
      int            reg_temp;
      int            rev_num;                    /* revision number */
      int            ram_flag;
      int            intr_temp;


      board_id |= ETHERNET_MEDIA;                /* assume Ethernet media */

    /* check if board is a WD8013EBT */
      if (inb(base+0x0e) == 0x05 )
         {
            /* board is 16 bits */
	    board_id |= BOARD_16BIT;
	    reg_temp &= 0xFE;
	    outb(base + REG_1, reg_temp);
	    /* check if in 16 bit slot */
	    if (inb(base + REG_1) & BID_SIXTEEN_BIT_BIT)
	      board_id |= SLOT_16BIT;
	  }

      rev_num = (inb(base + BOARD_ID_BYTE) & BID_REV_MASK) >> 1;
      if (rev_num < 2)
	{
	   if (board_id & BOARD_16BIT)
	     board_id |= RAM_SIZE_16K;
	   else
	     if (board_id & INTERFACE_CHIP)
	       if (inb(base + REG_1) & BID_MSZ_583)
		 board_id |= RAM_SIZE_32K;
	       else
		 board_id |= RAM_SIZE_8K;
	 }
      else
	{
	   ram_flag = inb(base + BOARD_ID_BYTE) & BID_RAM_SIZE_BIT;
	   switch ((int) (board_id & STATIC_ID_MASK))
	     {
	       case WD8003E:
	       case WD8003EB:
	              if (ram_flag)
			board_id |= RAM_SIZE_32K;
		      else
			board_id |= RAM_SIZE_8K;
                      break;
	       case WD8013EBT:
		      if (ram_flag)
			board_id |= RAM_SIZE_32K;
		      else
			board_id |= RAM_SIZE_16K;
		      break;
	       default :
		      board_id |= RAM_SIZE_8K;
	     }
	 }
      if ((board_id & WD8003EB) == WD8003EB) {
      /* program the WD83C583 EEPROM registers */
	if (ram_flag)
	  outb(base+ICR, inb(base+ICR) | DMAE | IOPE | MSZ);
	else
	  outb(base+ICR, inb(base+ICR) | DMAE | IOPE);
	switch(wd8003info[unit]->dev_pic)
	      /* attempt to set interrupt according to assigned pic */
	  {
 	    case 2: outb(base+IRR, IEN);
	            break;
	    case 3: outb(base+IRR, IEN|IR0);
	            break;
	    case 4: outb(base+IRR, IEN|IR1);
	            break;
	    case 7: outb(base+IRR, IEN|IR0|IR1);
	            break;
	    default: printf("\nWD8003: Could not set WD8003EB Interrupt Request Register according to pic(%d).\n", wd8003info[unit]->dev_pic);
	  }
      }

      return (board_id);

}

wdpr(unit)
{
	caddr_t base = wd8003_softc[unit].base;
	int	temp_cr;
	
	base += CR;
	temp_cr = inb(base);			/* get current CR value */

	printf("CR %x, BNDRY %x, TSR %x, NCR %x, FIFO %x, ISR %x, RSR %x\n",
		inb(base+0x0), inb(base+0x3), inb(base+0x4), inb(base+0x5),
		inb(base+0x6), inb(base+0x7), inb(base+0xc));
	printf("CLD %x:%x, CRD %x:%x, FR %x, CRC %x, Miss %x\n",
		inb(base+0x1), inb(base+0x2),
		inb(base+0x8), inb(base+0x9),
		inb(base+0xd), inb(base+0xe), inb(base+0xf));

	
	outb(base, (temp_cr&0x3f)|PS1);		/* page 1 CR value */
	printf("PHYS %x:%x:%x:%x:%x CUR %x\n",
		inb(base+0x1), inb(base+0x2), inb(base+0x3),
		inb(base+0x4), inb(base+0x5), inb(base+0x6),
		inb(base+0x7));
	printf("MAR %x:%x:%x:%x:%x:%x:%x:%x\n",
		inb(base+0x8), inb(base+0x9), inb(base+0xa), inb(base+0xb),
		inb(base+0xc), inb(base+0xd), inb(base+0xe), inb(base+0xf));
	outb(base, temp_cr);			/* restore current CR value */
}
