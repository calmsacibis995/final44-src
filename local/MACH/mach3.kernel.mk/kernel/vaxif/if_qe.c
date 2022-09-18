/* 
 * Mach Operating System
 * Copyright (c) 1991 Carnegie-Mellon University
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 */
/*
 * HISTORY
 * $Log:	if_qe.c,v $
 * Revision 2.6  93/05/17  10:24:59  rvb
 * 	Type casts, etc to quiet gcc 2.3.3 warnings
 * 
 * Revision 2.5  93/05/15  18:59:17  mrt
 * 	machparam.h -> machspl.h
 * 
 * Revision 2.4  91/05/13  06:08:03  af
 * 	Rid of the "CMU" conditional once and forall.
 * 	[91/05/12  16:36:55  af]
 * 
 * Revision 2.3  91/05/08  13:29:54  dbg
 * 	Add volatile declarations.  Moved br/cvec to memory.
 * 	[91/03/26            dbg]
 * 
 * 	Include vax/machparam.h for SPL definitions.
 * 	[91/03/20            dbg]
 * 
 * Revision 2.2  90/06/02  15:09:16  rpd
 * 	Converted to new IPC.
 * 
 * 	Mangled for MACH_KERNEL.
 * 	[88/10/12            dbg]
 * 
 * 	Lets check for suser before clearing counters.
 * 	[88/09/27            rvb]
 * 
 * Revision 2.1  89/08/03  16:39:26  rwd
 * Created.
 * 
 * Revision 2.7  88/09/27  18:07:09  rvb
 * 	27-Sep-88  Robert Baron (rvb) at Carnegie-Mellon University
 * 	Lets check for suser before clearing counters.
 * 
 * Revision 2.6  88/09/27  17:32:58  rvb
 * 	Fixed Log
 * 
 * Revision 2.5  88/09/27  16:09:26  rvb
 * 	Add counters: qe_[le]{out,in} -- e is log packet size, l is size
 * 	in 8 byte multiples to 128.  in and out are measured at the
 * 	interface.  qe_narp says don't count arp packets qe_arp is
 * 	always the arp count.
 * 	[88/09/23            rvb]
 * 
 * Revision 2.4  88/08/24  03:05:10  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  23:29:20  mwyoung]
 * 
 *
 * Revision 2.3  88/08/22  21:33:26  mja
 * 	Corrected include formats.
 * 	[88/08/19  10:44:54  mja]
 * 	
 * 	Slight changes to make this driver talk to the DELQA, which is
 * 	supposed to be software compatible, but isn't quite [pdb@SEI];
 * 	CMUCS: merge [parker&berman];
 * 	CS_GENERIC => CMUCS [mja].
 * 	[88/08/11  11:50:11  mja]
 * 
 * 31-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	CMUCS: Don't compile qe_setaddr; it isn't used.
 *
 * 28-Oct-87  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	Took a hint from the Ultrix 2.0 driver and clear bits in 
 *	addr->csr in probe code.
 *
 * 06-May-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	DLI:  Add support for new direct data-link interface protocol.
 *	CMUCS:  Add support for IFF_ALLMULTI and IFF_PROMISC
 *	interface status flags.
 *	[ V5.1(F10) ]
 *
 * 30-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  reduced qerestart error message priority to
 *	CS_GENERIC:  reduced qerestart error message priority to
 *	LOG_NOTICE so that it won't show up on the console to annoy
 *	everyone any more.
 *	[ V5.1(F1) ]
 *
 * 18-Aug-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS: Added display of interface hardware address during
 *	attach configuration.
 *
 */ 
 
#include <dli.h>

/*	@(#)if_qe.c	7.1 (Berkeley) 6/5/86 */

/* from  @(#)if_qe.c	1.15	(ULTRIX)	4/16/86 */
 
 
/****************************************************************
 *								*
 *        Licensed from Digital Equipment Corporation 		*
 *                       Copyright (c) 				*
 *               Digital Equipment Corporation			*
 *                   Maynard, Massachusetts 			*
 *                         1985, 1986 				*
 *                    All rights reserved. 			*
 *								*
 *        The Information in this software is subject to change *
 *   without notice and should not be construed as a commitment *
 *   by  Digital  Equipment  Corporation.   Digital   makes  no *
 *   representations about the suitability of this software for *
 *   any purpose.  It is supplied "As Is" without expressed  or *
 *   implied  warranty. 					*
 *								*
 *        If the Regents of the University of California or its *
 *   licensees modify the software in a manner creating  	*
 *   derivative copyright rights, appropriate copyright  	*
 *   legends may be placed on the derivative work in addition   *
 *   to that set forth above. 					*
 *								*
 ****************************************************************/
/* ---------------------------------------------------------------------
 * Modification History 
 *
 * 15-Apr-86  -- afd
 *	Rename "unused_multi" to "qunused_multi" for extending Generic
 *	kernel to MicroVAXen.
 *
 * 18-mar-86  -- jaw     br/cvec changed to NOT use registers.
 *
 * 12 March 86 -- Jeff Chase
 *	Modified to handle the new MCLGET macro
 *	Changed if_qe_data.c to use more receive buffers
 *	Added a flag to poke with adb to log qe_restarts on console
 *
 * 19 Oct 85 -- rjl
 *	Changed the watch dog timer from 30 seconds to 3.  VMS is using
 * 	less than 1 second in their's. Also turned the printf into an
 *	mprintf.
 *
 *  09/16/85 -- Larry Cohen
 * 		Add 43bsd alpha tape changes for subnet routing		
 *
 *  1 Aug 85 -- rjl
 *	Panic on a non-existent memory interrupt and the case where a packet
 *	was chained.  The first should never happen because non-existant 
 *	memory interrupts cause a bus reset. The second should never happen
 *	because we hang 2k input buffers on the device.
 *
 *  1 Aug 85 -- rich
 *      Fixed the broadcast loopback code to handle Clusters without
 *      wedging the system.
 *
 *  27 Feb. 85 -- ejf
 *	Return default hardware address on ioctl request.
 *
 *  12 Feb. 85 -- ejf
 *	Added internal extended loopback capability.
 *
 *  27 Dec. 84 -- rjl
 *	Fixed bug that caused every other transmit descriptor to be used
 *	instead of every descriptor.
 *
 *  21 Dec. 84 -- rjl
 *	Added watchdog timer to mask hardware bug that causes device lockup.
 *
 *  18 Dec. 84 -- rjl
 *	Reworked driver to use q-bus mapping routines.  MicroVAX-I now does
 *	copying instead of m-buf shuffleing.
 *	A number of deficencies in the hardware/firmware were compensated
 *	for. See comments in qestart and qerint.
 *
 *  14 Nov. 84 -- jf
 *	Added usage counts for multicast addresses.
 *	Updated general protocol support to allow access to the Ethernet
 *	header.
 *
 *  04 Oct. 84 -- jf
 *	Added support for new ioctls to add and delete multicast addresses
 *	and set the physical address.
 *	Add support for general protocols.
 *
 *  14 Aug. 84 -- rjl
 *	Integrated Shannon changes. (allow arp above 1024 and ? )
 *
 *  13 Feb. 84 -- rjl
 *
 *	Initial version of driver. derived from IL driver.
 * 
 * ---------------------------------------------------------------------
 */
 
#include <qe.h>
#if	NQE > 0
/*
 * Digital Q-BUS to NI Adapter
 */
#ifdef	MACH_KERNEL
#include <kern/time_out.h>
#include <sys/syslog.h>

#include <device/device_types.h>
#include <device/errno.h>
#include <device/io_req.h>
#include <device/if_hdr.h>
#include <device/if_ether.h>
#include <device/net_status.h>

#include <vax/vm_defs.h>
#include <vax/machspl.h>
#else	MACH_KERNEL
#include <machine/pte.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/vmmac.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/syslog.h>
#include <sys/time.h>
#include <sys/kernel.h>

#include <net/if.h>
#include <net/netisr.h>
#include <net/route.h>

#ifdef INET
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#endif

#ifdef NS
#include <netns/ns.h>
#include <netns/ns_if.h>
#endif

#if	DLI
#include <net/dli_var.h>
struct dli_var qe_dlv[NQE];
#endif	DLI

#include <vax/cpu.h>
#endif	MACH_KERNEL
#include <vax/mtpr.h>

#include <vaxif/if_qereg.h>
#include <vaxif/if_uba.h>

#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>
 
#define NRCV	25	 		/* Receive descriptors		*/
#define NXMT	5	 		/* Transmit descriptors		*/
#define NTOT	(NXMT + NRCV)
 
/*
 * This constant should really be 60 because the qna adds 4 bytes of crc.
 * However when set to 60 our packets are ignored by deuna's , 3coms are
 * okay ??????????????????????????????????????????
 */
#define MINDATA 64
 
/*
 * Ethernet software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * is_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address, ...
 */
struct	qe_softc {
#ifdef	MACH_KERNEL
	struct	ifnet	is_if;		/* generic interface header	*/
	u_char	is_addr[6];		/* ethernet hardware address	*/
#else	MACH_KERNEL
	struct	arpcom is_ac;		/* Ethernet common part		*/
#define	is_if	is_ac.ac_if		/* network-visible interface 	*/
#define	is_addr	is_ac.ac_enaddr		/* hardware Ethernet address 	*/
#endif	MACH_KERNEL
	struct	ifubinfo qe_uba;	/* Q-bus resources 		*/
	struct	ifrw qe_ifr[NRCV];	/*	for receive buffers;	*/
	struct	ifxmt qe_ifw[NXMT];	/*	for xmit buffers;	*/
	int	qe_flags;		/* software state		*/
#define	QEF_RUNNING	0x01
#define	QEF_SETADDR	0x02
	int	setupaddr;		/* mapping info for setup pkts  */
	struct	qe_ring *rringaddr;	/* mapping info for rings	*/
	struct	qe_ring *tringaddr;	/*       ""			*/
	struct	qe_ring rring[NRCV+1];	/* Receive ring descriptors 	*/
	struct	qe_ring tring[NXMT+1];	/* Transmit ring descriptors 	*/
	u_char	setup_pkt[16][8];	/* Setup packet			*/
	int	rindex;			/* Receive index		*/
	int	tindex;			/* Transmit index		*/
	int	otindex;		/* Old transmit index		*/
	int	qe_intvec;		/* Interrupt vector 		*/
	struct	qedevice *addr;		/* device addr			*/
	int 	setupqueued;		/* setup packet queued		*/
	int	nxmit;			/* Transmits in progress	*/
	int	timeout;		/* watchdog			*/
	int	qe_restarts;		/* timeouts			*/
#if	MACH
	u_char  setupmode;		/* currrent multi/prom mode     */
#endif	MACH
} qe_softc[NQE];

struct	uba_device *qeinfo[NQE];
 
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
extern struct timeval time;
extern timeout();
#endif	MACH_KERNEL

int	qeprobe(), qeattach(), qeintr(), qewatch();
int	qeinit(),qeoutput(),qeioctl(),qereset(),qewatch();
 
u_short qestd[] = { 0 };
struct	uba_driver qedriver =
	{ qeprobe, 0, qeattach, 0, qestd, "qe", qeinfo };
 
#define QE_TIMEO	(15)
#define	QEUNIT(x)	minor(x)
static int mask = 0x3ffff;		/* address mask		*/
int qewatchrun = 0;			/* watchdog running	*/
/*
 * The deqna shouldn't receive more than ETHERMTU + sizeof(struct ether_header)
 * but will actually take in up to 2048 bytes. To guard against the receiver
 * chaining buffers (which we aren't prepared to handle) we allocate 2kb 
 * size buffers.
 */
#define MAXPACKETSIZE 2048		/* Should really be ETHERMTU	*/
/*
 * Probe the QNA to see if it's there
 */
extern volatile int	br;
extern volatile int	cvec;

qeprobe(reg)
	caddr_t reg;
{
	register struct qedevice *addr = (struct qedevice *)reg;
	register struct qe_ring *rp; 
	register struct qe_ring *prp; 	/* physical rp 		*/
	register int i, j;
	static int next=0;		/* softc index		*/
	register struct qe_softc *sc = &qe_softc[next++];
 
#ifdef lint
	qeintr(0);
#endif
	/*
	 * Set the address mask for the particular cpu
	 */
	mask = 0x3ffff;
 
#if	MACH
        /*
         * If this is a DELQA, then we have to make sure it's finished
	 * with its self-test, otherwise it won't autoconfig.
	 */

        printf("qe%d: ", next-1);
        for (i=1; i<100; i++) if (addr->qe_vector & QE_SELFTEST)
        	DELAY(1000);
	if (addr->qe_vector & QE_SELFTEST) {
	        printf("DELQA self test never completes\n");
		return 0;
	}
	/* In case DELQA, delay five seconds while registers settle
           down after self-test.  */
	DELAY(50000);
	/* Now see if it's a DEQNA or DELQA */
	addr->qe_vector |= QE_IDENT;
	if (addr->qe_vector & QE_IDENT) {
		printf("DELQA, ");
		addr->qe_vector &= ~QE_IDENT;
		/* If this is a DELQA, check to see if it
		   passed self-test, and check option switches */
		i = addr->qe_vector;
		switch (i & QE_SELFTEST) {
		    case QE_TEST_ROM:
			printf("ROM CRC test failed\n");
			return 0;
		    case QE_TEST_RAM:
			printf("RAM test failed\n");
			return 0;
		    case QE_TEST_68000:
			printf("68000 test failed\n");
			return 0;
		    case QE_TEST_QIC:
			printf("QIC test failed\n");
			return 0;
		    case QE_TEST_QNA2:
			printf("QNA2 test failed\n");
			return 0;
		    case QE_TEST_SAROM:
			printf("SA ROM test failed\n");
			return 0;
		    case QE_TEST_LANCE:
			printf("LANCE test failed\n");
			return 0;
		    default:
			/* everything tests OK */
			break;
		}
		if (i & QE_MODESEL) {
		    if ((i & QE_OPTSWITCH) == 0)
			printf("remote boot ENABLED, ");
		}
		else {
		    printf("DEQNA-lock mode, ");
		}
	}
	else printf("DEQNA, ");
	printf("station address %x-%x-%x-%x-%x-%x\n",
	    addr->qe_sta_addr[0] & 0xff,
	    addr->qe_sta_addr[1] & 0xff,
	    addr->qe_sta_addr[2] & 0xff,
	    addr->qe_sta_addr[3] & 0xff,
	    addr->qe_sta_addr[4] & 0xff,
	    addr->qe_sta_addr[5] & 0xff);
 
#endif	MACH
	/*
	 * The QNA interrupts on i/o operations. To do an I/O operation 
	 * we have to setup the interface by transmitting a setup  packet.
	 */
	addr->qe_csr = QE_RESET;
	addr->qe_vector = (uba_hd[numuba].uh_lastiv -= 4);
 
	/*
	 * Map the communications area and the setup packet.
	 */
	sc->setupaddr =
		uballoc(0, (caddr_t)sc->setup_pkt, sizeof(sc->setup_pkt), 0);
	sc->rringaddr = (struct qe_ring *) uballoc(0, (caddr_t)sc->rring,
		sizeof(struct qe_ring) * (NTOT+2), 0);
	prp = (struct qe_ring *)((int)sc->rringaddr & mask);

#if	MACH
	/* Clear the reset bit to turn the interface on.
	   The DEQNA apparently doesn't require this, but the DELQA does */

        addr->qe_csr &= ~QE_RESET;
#endif	MACH

	/*
	 * The QNA will loop the setup packet back to the receive ring
	 * for verification, therefore we initialize the first 
	 * receive & transmit ring descriptors and link the setup packet
	 * to them.
	 */
	qeinitdesc(sc->tring, (caddr_t)(sc->setupaddr & mask),
	    sizeof(sc->setup_pkt));
	qeinitdesc(sc->rring, (caddr_t)(sc->setupaddr & mask),
	    sizeof(sc->setup_pkt));
 
	rp = (struct qe_ring *)sc->tring;
	rp->qe_setup = 1;
	rp->qe_eomsg = 1;
	rp->qe_flag = rp->qe_status1 = QE_NOTYET;
	rp->qe_valid = 1;
 
	rp = (struct qe_ring *)sc->rring;
	rp->qe_flag = rp->qe_status1 = QE_NOTYET;
	rp->qe_valid = 1;
 
	/*
	 * Get the addr off of the interface and place it into the setup
	 * packet. This code looks strange due to the fact that the address
	 * is placed in the setup packet in col. major order. 
	 */
	for( i = 0 ; i < 6 ; i++ )
		sc->setup_pkt[i][1] = addr->qe_sta_addr[i];
 
	qesetup( sc );
	/*
	 * Start the interface and wait for the packet.
	 */
	j = cvec;
	addr->qe_csr = QE_INT_ENABLE | QE_XMIT_INT | QE_RCV_INT;
	addr->qe_rcvlist_lo = (short)((int)prp);
	addr->qe_rcvlist_hi = (short)((int)prp >> 16);
	prp += NRCV+1;
	addr->qe_xmtlist_lo = (short)((int)prp);
	addr->qe_xmtlist_hi = (short)((int)prp >> 16);
	DELAY(10000);
	/*
	 * All done with the bus resources.
	 */
	ubarelse(0, &sc->setupaddr);
	ubarelse(0, (int *)&sc->rringaddr);
	if( cvec == j ) 
		return 0;		/* didn't interrupt	*/
 
	return( sizeof(struct qedevice) );
}
 
/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 */
qeattach(ui)
	struct uba_device *ui;
{
	register struct qe_softc *sc = &qe_softc[ui->ui_unit];
	register struct ifnet *ifp = &sc->is_if;
	register struct qedevice *addr = (struct qedevice *)ui->ui_addr;
	register int i;
 
	ifp->if_unit = ui->ui_unit;
#ifdef	MACH_KERNEL
	ifp->if_header_size = sizeof(struct ether_header);
	ifp->if_header_format = HDR_ETHERNET;
	ifp->if_address_size = 6;
#else	MACH_KERNEL
	ifp->if_name = "qe";
#endif	MACH_KERNEL
	ifp->if_mtu = ETHERMTU;
	ifp->if_flags = IFF_BROADCAST;

	/*
	 * Read the address from the prom and save it.
	 */
	for( i=0 ; i<6 ; i++ )
		sc->setup_pkt[i][1] = sc->is_addr[i] = addr->qe_sta_addr[i] & 0xff;  
 
	/*
	 * Save the vector for initialization at reset time.
	 */
	sc->qe_intvec = addr->qe_vector;
 
#if	MACH
	printf("qe%d: hardware address %s\n", ui->ui_unit,
		ether_sprintf(sc->is_addr));
#endif	MACH
#ifdef	MACH_KERNEL
	ifp->if_address = (char *)&sc->is_addr[0];
#else	MACH_KERNEL
	ifp->if_init = qeinit;
	ifp->if_output = qeoutput;
	ifp->if_ioctl = qeioctl;
	ifp->if_reset = qereset;
#endif	MACH_KERNEL
	sc->qe_uba.iff_flags = UBA_CANTWAIT;
#ifdef	MACH_KERNEL
	if_init_queues(ifp);
#else	MACH_KERNEL
	if_attach(ifp);
#endif	MACH_KERNEL
}
 
/*
 * Reset of interface after UNIBUS reset.
 * If interface is on specified uba, reset its state.
 */
#ifdef	MACH_KERNEL
qeallreset(uban)
	int	uban;
{
	register int	unit;
	for (unit = 0; unit < NQE; unit++)
	    qereset(unit, uban);
}
#endif	MACH_KERNEL

qereset(unit, uban)
	int unit, uban;
{
	register struct uba_device *ui;
 
	if (unit >= NQE || (ui = qeinfo[unit]) == 0 || ui->ui_alive == 0 ||
		ui->ui_ubanum != uban)
		return;
	printf(" qe%d", unit);
	qe_softc[unit].is_if.if_flags &= ~IFF_RUNNING;
	qeinit(unit);
}
 
/*
 * Initialization of interface. 
 */
qeinit(unit)
	int unit;
{
	register struct qe_softc *sc = &qe_softc[unit];
	register struct uba_device *ui = qeinfo[unit];
	register struct qedevice *addr = (struct qedevice *)ui->ui_addr;
	register struct ifnet *ifp = &sc->is_if;
	register i;
	int s;
 
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
	/* address not known */
	if (ifp->if_addrlist == (struct ifaddr *)0)
			return;
#endif	MACH_KERNEL
	if (sc->qe_flags & QEF_RUNNING)
		return;
 
	if ((ifp->if_flags & IFF_RUNNING) == 0) {
		/*
		 * map the communications area onto the device 
		 */
		sc->rringaddr = (struct qe_ring *)
		    ((int) uballoc(0, (caddr_t)sc->rring,
		    sizeof(struct qe_ring) * (NTOT+2), 0) & mask);
		sc->tringaddr = sc->rringaddr + NRCV + 1;
		sc->setupaddr =	uballoc(0, (caddr_t)sc->setup_pkt,
		    sizeof(sc->setup_pkt), 0) & mask;
		/*
		 * init buffers and maps
		 */
		if (if_ubaminit(&sc->qe_uba, ui->ui_ubanum,
		    sizeof (struct ether_header), (int)btoc(MAXPACKETSIZE),
#ifdef	MACH_KERNEL
		    sc->qe_ifr, NRCV, sc->qe_ifw, NXMT, MINDATA
#else	MACH_KERNEL
		    sc->qe_ifr, NRCV, sc->qe_ifw, NXMT
#endif	MACH_KERNEL
		    		) == 0) {
			printf("qe%d: can't initialize\n", unit);
			sc->is_if.if_flags &= ~IFF_UP;
			return;
		}
#ifdef	MACH_KERNEL
		ifp->if_alloc_size = sc->qe_uba.iff_size;
#endif	MACH_KERNEL
	}
	/*
	 * Init the buffer descriptors and indexes for each of the lists and
	 * loop them back to form a ring.
	 */
	for (i = 0; i < NRCV; i++) {
		qeinitdesc( &sc->rring[i],
		    (caddr_t)(sc->qe_ifr[i].ifrw_info & mask), MAXPACKETSIZE);
		sc->rring[i].qe_flag = sc->rring[i].qe_status1 = QE_NOTYET;
		sc->rring[i].qe_valid = 1;
	}
	qeinitdesc(&sc->rring[i], (caddr_t)NULL, 0);
 
	sc->rring[i].qe_addr_lo = (short)((int)sc->rringaddr);
	sc->rring[i].qe_addr_hi = (short)((int)sc->rringaddr >> 16);
	sc->rring[i].qe_chain = 1;
	sc->rring[i].qe_flag = sc->rring[i].qe_status1 = QE_NOTYET;
	sc->rring[i].qe_valid = 1;
 
	for( i = 0 ; i <= NXMT ; i++ )
		qeinitdesc(&sc->tring[i], (caddr_t)NULL, 0);
	i--;
 
	sc->tring[i].qe_addr_lo = (short)((int)sc->tringaddr);
	sc->tring[i].qe_addr_hi = (short)((int)sc->tringaddr >> 16);
	sc->tring[i].qe_chain = 1;
	sc->tring[i].qe_flag = sc->tring[i].qe_status1 = QE_NOTYET;
	sc->tring[i].qe_valid = 1;
 
	sc->nxmit = sc->otindex = sc->tindex = sc->rindex = 0;
 
	/*
	 * Take the interface out of reset, program the vector, 
	 * enable interrupts, and tell the world we are up.
	 */
	s = splimp();
	addr->qe_vector = sc->qe_intvec;
	sc->addr = addr;
	addr->qe_csr = QE_RCV_ENABLE | QE_INT_ENABLE | QE_XMIT_INT |
	    QE_RCV_INT | QE_ILOOP;
	addr->qe_rcvlist_lo = (short)((int)sc->rringaddr);
	addr->qe_rcvlist_hi = (short)((int)sc->rringaddr >> 16);
	ifp->if_flags |= IFF_UP | IFF_RUNNING;
	sc->qe_flags |= QEF_RUNNING;
	qesetup( sc );
	qestart( unit );
	splx( s );
#if	DLI
	dli_init(&qe_dlv[ui->ui_unit], ifp, sc->is_addr, etherbroadcastaddr,
		 sizeof(etherbroadcastaddr), sizeof(struct ether_header));
#endif	DLI
 
}

#ifdef	MACH_KERNEL
/*ARGSUSED*/
qeopen(dev, flag)
	dev_t	dev;
	int	flag;
{
	register int unit = QEUNIT(dev);
	register struct uba_device *ui;
	register struct qe_softc *sc;

	if (unit >= NQE || (ui = qeinfo[unit]) == 0 || ui->ui_alive == 0)
		return (ENXIO);

	sc = &qe_softc[unit];
	sc->is_if.if_flags |= IFF_UP;
	qeinit(unit);
	return (0);
}
#endif	MACH_KERNEL

#if	PACKET_LENGTH_STATS
int qe_narp = 1, qe_arp = 0;
int qe_ein[32], qe_eout[32]; 
int qe_lin[128/8], qe_lout[128/8]; 
static
log_2(i)
{
	register int no = i;
	register int ffs = -1;
	register int offs;

	while (ffs < 33) {
		offs = ffs;
		ffs++;
#ifdef	__GNUC__
		asm("ffs %1, $32, %2, %0"
		    : "=g" (ffs)
		    : "0" (ffs), "g" (no)
		    );
#else
		asm("ffs r10, $32, r11, r10");
#endif
	}
	return (offs);
}
#endif	PACKET_LENGTH_STATS

/*
 * Start output on interface.
 *
 */
qestart(dev)
	dev_t dev;
{
	int unit = QEUNIT(dev);
	struct uba_device *ui = qeinfo[unit];
	register struct qe_softc *sc = &qe_softc[unit];
	register struct qedevice *addr;
	register struct qe_ring *rp;
	register index;
#ifdef	MACH_KERNEL
	io_req_t	m;
#else	MACH_KERNEL
	struct mbuf *m;
#endif	MACH_KERNEL
	int buf_addr, len, s;
 
	 
	s = splimp();
	addr = (struct qedevice *)ui->ui_addr;
	/*
	 * The deqna doesn't look at anything but the valid bit
	 * to determine if it should transmit this packet. If you have
	 * a ring and fill it the device will loop indefinitely on the
	 * packet and continue to flood the net with packets until you
	 * break the ring. For this reason we never queue more than n-1
	 * packets in the transmit ring. 
	 *
	 * The microcoders should have obeyed their own definition of the
	 * flag and status words, but instead we have to compensate.
	 */
	for( index = sc->tindex; 
		sc->tring[index].qe_valid == 0 && sc->nxmit < (NXMT-1) ;
		sc->tindex = index = ++index % NXMT){
		rp = &sc->tring[index];
		if( sc->setupqueued ) {
			buf_addr = sc->setupaddr;
#if	MACH
			len = 128|(sc->setupmode);
#else	MACH
			len = 128;
#endif	MACH
			rp->qe_setup = 1;
			sc->setupqueued = 0;
		} else {
			IF_DEQUEUE(&sc->is_if.if_snd, m);
			if( m == 0 ){
				splx(s);
				return;
			}
#ifdef	MACH_KERNEL
			if_ubaput(&sc->qe_uba, &sc->qe_ifw[index], m,
				&buf_addr, &len);
#else	MACH_KERNEL
			buf_addr = sc->qe_ifw[index].ifw_info;
			len = if_ubaput(&sc->qe_uba, &sc->qe_ifw[index], m);
#endif	MACH_KERNEL
		}
		/*
		 *  Does buffer end on odd byte ? 
		 */
		if( len & 1 ) {
			len++;
			rp->qe_odd_end = 1;
		}
#if	PACKET_LENGTH_STATS
		qe_eout[log_2(len)]++;
		if (len < 128)  qe_lout[len>>3]++;
#endif	PACKET_LENGTH_STATS
		if( len < MINDATA )
			len = MINDATA;
		rp->qe_buf_len = -(len/2);
		buf_addr &= mask;
		rp->qe_flag = rp->qe_status1 = QE_NOTYET;
		rp->qe_addr_lo = (short)buf_addr;
		rp->qe_addr_hi = (short)(buf_addr >> 16);
		rp->qe_eomsg = 1;
		rp->qe_flag = rp->qe_status1 = QE_NOTYET;
		rp->qe_valid = 1;
		sc->nxmit++;
		/*
		 * If the watchdog time isn't running kick it.
		 */
		sc->timeout=1;
		if (qewatchrun == 0) { 
			qewatchrun++; 
			timeout(qewatch, (caddr_t)0, QE_TIMEO);
		}
			
		/*
		 * See if the xmit list is invalid.
		 */
		if( addr->qe_csr & QE_XL_INVALID ) {
			buf_addr = (int)(sc->tringaddr+index);
			addr->qe_xmtlist_lo = (short)buf_addr;
			addr->qe_xmtlist_hi = (short)(buf_addr >> 16);
		}
	}
	splx( s );
}
 
/*
 * Ethernet interface interrupt processor
 */
qeintr(unit)
	int unit;
{
	register struct qe_softc *sc = &qe_softc[unit];
	struct qedevice *addr = (struct qedevice *)qeinfo[unit]->ui_addr;
	int s, buf_addr, csr;
 
	s = splimp();
	csr = addr->qe_csr;
	addr->qe_csr = QE_RCV_ENABLE | QE_INT_ENABLE | QE_XMIT_INT | QE_RCV_INT | QE_ILOOP;
	if( csr & QE_RCV_INT ) 
		qerint( unit );
	if( csr & QE_XMIT_INT )
		qetint( unit );
	if( csr & QE_NEX_MEM_INT )
		panic("qe: Non existant memory interrupt");
	
	if( addr->qe_csr & QE_RL_INVALID && sc->rring[sc->rindex].qe_status1 == QE_NOTYET ) {
		buf_addr = (int)&sc->rringaddr[sc->rindex];
		addr->qe_rcvlist_lo = (short)buf_addr;
		addr->qe_rcvlist_hi = (short)(buf_addr >> 16);
	}
	splx( s );
}
 
/*
 * Ethernet interface transmit interrupt.
 */
 
qetint(unit)
	int unit;
{
	register struct qe_softc *sc = &qe_softc[unit];
	register struct qe_ring *rp;
	register struct ifxmt *ifxp;
	int status1, setupflag;
	short len;
 
 
	while( sc->otindex != sc->tindex && sc->tring[sc->otindex].qe_status1 != QE_NOTYET && sc->nxmit > 0 ) {
		/*
		 * Save the status words from the descriptor so that it can
		 * be released.
		 */
		rp = &sc->tring[sc->otindex];
		status1 = rp->qe_status1;
		setupflag = rp->qe_setup;
		len = (-rp->qe_buf_len) * 2;
		if( rp->qe_odd_end )
			len++;
		/*
		 * Init the buffer descriptor
		 */
		bzero((caddr_t)rp, sizeof(struct qe_ring));
		if( --sc->nxmit == 0 )
			sc->timeout = 0;
		if( !setupflag ) {
			/*
			 * Do some statistics.
			 */
			sc->is_if.if_opackets++;
			sc->is_if.if_collisions += ( status1 & QE_CCNT ) >> 4;
			if (status1 & QE_ERROR)
				sc->is_if.if_oerrors++;
			/*
			 * If this was a broadcast packet loop it
			 * back because the hardware can't hear its own
			 * transmits.
			 */
			ifxp = &sc->qe_ifw[sc->otindex];
			if (bcmp((caddr_t)ifxp->ifw_addr,
			    (caddr_t)etherbroadcastaddr,
			    sizeof(etherbroadcastaddr)) == 0)
#if	MACH
				qeread(sc, &ifxp->ifrw, len
						  -sizeof(struct ether_header));
#else	MACH
				qeread(sc, &ifxp->ifrw, len);
#endif	MACH
			if (ifxp->ifw_xtofree) {
#ifdef	MACH_KERNEL
				iodone(ifxp->ifw_xtofree);
#else	MACH_KERNEL
				m_freem(ifxp->ifw_xtofree);
#endif	MACH_KERNEL
				ifxp->ifw_xtofree = 0;
			}
		}
		sc->otindex = ++sc->otindex % NXMT;
	}
	qestart( unit );
}
 
/*
 * Ethernet interface receiver interrupt.
 * If can't determine length from type, then have to drop packet.  
 * Othewise decapsulate packet based on type and pass to type specific 
 * higher-level input routine.
 */
qerint(unit)
	int unit;
{
	register struct qe_softc *sc = &qe_softc[unit];
	register struct qe_ring *rp;
	int len, status1, status2;
	int bufaddr;
 
	/*
	 * Traverse the receive ring looking for packets to pass back.
	 * The search is complete when we find a descriptor not in use.
	 *
	 * As in the transmit case the deqna doesn't honor its own protocols
	 * so there exists the possibility that the device can beat us around
	 * the ring. The proper way to guard against this is to insure that
	 * there is always at least one invalid descriptor. We chose instead
	 * to make the ring large enough to minimize the problem. With a ring
	 * size of 4 we haven't been able to see the problem. To be safe we
	 * doubled that to 8.
	 *
	 */
	for( ; sc->rring[sc->rindex].qe_status1 != QE_NOTYET ; sc->rindex = ++sc->rindex % NRCV ){
		rp = &sc->rring[sc->rindex];
		status1 = rp->qe_status1;
		status2 = rp->qe_status2;
		bzero((caddr_t)rp, sizeof(struct qe_ring));
		if( (status1 & QE_MASK) == QE_MASK )
			panic("qe: chained packet");
		len = ((status1 & QE_RBL_HI) | (status2 & QE_RBL_LO)) + 60;
#if	PACKET_LENGTH_STATS
		qe_ein[log_2(len)]++;
		if (len < 128) qe_lin[len>>3]++;
#endif	PACKET_LENGTH_STATS
		sc->is_if.if_ipackets++;
 
		if (status1 & QE_ERROR)
			sc->is_if.if_ierrors++;
		else {
			/*
			 * We don't process setup packets.
			 */
			if( !(status1 & QE_ESETUP) )
				qeread(sc, &sc->qe_ifr[sc->rindex],
					len - sizeof(struct ether_header));
		}
		/*
		 * Return the buffer to the ring
		 */
		bufaddr = (int)sc->qe_ifr[sc->rindex].ifrw_info & mask;
		rp->qe_buf_len = -((MAXPACKETSIZE)/2);
		rp->qe_addr_lo = (short)bufaddr;
		rp->qe_addr_hi = (short)((int)bufaddr >> 16);
		rp->qe_flag = rp->qe_status1 = QE_NOTYET;
		rp->qe_valid = 1;
	}
}
#ifdef	MACH_KERNEL
qeoutput(dev, ior)
	dev_t	dev;
	io_req_t ior;
{
	register int unit = QEUNIT(dev);
	if (unit >= NQE)
	    return (ENXIO);
	return (net_write(&qe_softc[unit].is_if, qestart, ior));
}

qesetinput(dev, receive_port, priority, filter, filter_count)
	dev_t		dev;
	mach_port_t	receive_port;
	int		priority;
	filter_t	filter[];
	unsigned int	filter_count;
{
	register int unit = QEUNIT(dev);
	if (unit >= NQE)
	    return (ENXIO);

	return (net_set_filter(&qe_softc[unit].is_if,
			receive_port, priority,
			filter, filter_count));
}

#else	MACH_KERNEL
/*
 * Ethernet output routine.
 * Encapsulate a packet of type family for the local net.
 * Use trailer local net encapsulation if enough data in first
 * packet leaves a multiple of 512 bytes of data in remainder.
 */
qeoutput(ifp, m0, dst)
	struct ifnet *ifp;
	struct mbuf *m0;
	struct sockaddr *dst;
{
	int type, s, error;
	u_char edst[6];
	struct in_addr idst;
	register struct qe_softc *is = &qe_softc[ifp->if_unit];
	register struct mbuf *m = m0;
	register struct ether_header *eh;
	register int off;
	int usetrailers;
 
	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
		error = ENETDOWN;
		goto bad;
	}

	switch (dst->sa_family) {
 
#ifdef INET
	case AF_INET:
		idst = ((struct sockaddr_in *)dst)->sin_addr;
		if (!arpresolve(&is->is_ac, m, &idst, edst, &usetrailers))
			return (0);	/* if not yet resolved */
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
		    (caddr_t)edst, sizeof (edst));
		off = 0;
		goto gottype;
#endif
#if	DLI
	case AF_DLI:
		if (m->m_len < sizeof(struct ether_header))
		{
			error = EMSGSIZE;
			goto bad;
		}
		eh = mtod(m, struct ether_header *);
 		bcopy(dst->sa_data, (caddr_t)eh->ether_dhost, sizeof (eh->ether_dhost));
		goto gotheader;
#endif	DLI

 
	case AF_UNSPEC:
		eh = (struct ether_header *)dst->sa_data;
 		bcopy((caddr_t)eh->ether_dhost, (caddr_t)edst, sizeof (edst));
		type = eh->ether_type;
		goto gottype;
 
	default:
		printf("qe%d: can't handle af%d\n", ifp->if_unit,
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
#if	DLI
gotheader:
#endif	DLI
 	bcopy((caddr_t)is->is_addr, (caddr_t)eh->ether_shost, sizeof (is->is_addr));
 
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
	qestart(ifp->if_unit);
	splx(s);
	return (0);
 
bad:
	m_freem(m0);
	return (error);
}
#endif	MACH_KERNEL
 
 
#ifdef	MACH_KERNEL
qegetstat(dev, flavor, status, count)
	dev_t	dev;
	int	flavor;
	dev_status_t	status;		/* pointer to OUT array */
	unsigned int	*count;		/* out */
{
	register int unit = QEUNIT(dev);
	register struct uba_device *ui;
	register struct qe_softc *sc;

	if (unit >= NQE || (ui = qeinfo[unit]) == 0 || ui->ui_alive == 0)
		return (ENXIO);

	sc = &qe_softc[unit];

	return (net_getstat(&sc->is_if, flavor, status, count));
}

/*ARGSUSED*/
qesetstat(dev, flavor, status, count)
	dev_t	dev;
	int	flavor;
	dev_status_t	status;
	unsigned int	count;
{
	register int unit = QEUNIT(dev);
	register struct uba_device *ui;
	register struct qe_softc *sc;

	if (unit >= NQE || (ui = qeinfo[unit]) == 0 || ui->ui_alive == 0)
		return (ENXIO);

	sc = &qe_softc[unit];

	switch (flavor) {
	    case NET_STATUS:
	    {
		/*
		 * All we can change are flags, and not many of those
		 */
		register struct net_status *ns = (struct net_status *)status;
		unsigned char	mode = 0;

		if (count < NET_STATUS_COUNT)
		    return (D_INVALID_OPERATION);

		if (ns->flags & IFF_ALLMULTI)
		    mode |= 0x1;
		if (ns->flags & IFF_PROMISC)
		    mode |= 0x2;

		/*
		 * Force a complete reset if the receive multicast or
		 * promiscuous mode changes, so that these take effect
		 * immediately.
		 */
		if (sc->setupmode != mode) {
		    sc->setupmode = mode;
		    if (sc->qe_flags & QEF_RUNNING) {
			((struct qedevice *)ui->ui_addr)->qe_csr = QE_RESET;
			sc->qe_flags &= ~QEF_RUNNING;
		    }
		}
		sc->is_if.if_flags = ns->flags & ~IFF_CANTCHANGE;

		if ((sc->is_if.if_flags & IFF_UP) == 0 &&
			(sc->qe_flags & QEF_RUNNING)) {
		    ((struct qedevice *)ui->ui_addr)->qe_csr = QE_RESET;
		    sc->qe_flags &= ~QEF_RUNNING;
		}
		else
		if ((sc->is_if.if_flags & IFF_UP) &&
			(sc->qe_flags & QEF_RUNNING) == 0) {
		    qerestart(sc);
		}
		break;
	    }

	    case NET_ADDRESS:
	    {
		register union ether_cvt {
		    char	addr[6];
		    int		lwd[2];
		} *ec = (union ether_cvt *)status;

		if (count < sizeof(*ec)/sizeof(int))
		    return (D_INVALID_SIZE);
		ec->lwd[0] = ntohl(ec->lwd[0]);
		ec->lwd[1] = ntohl(ec->lwd[1]);

		qe_setaddr(ec->addr, unit);
		break;
	    }
	    default:
		return (D_INVALID_OPERATION);
	}
	return (D_SUCCESS);
}

#else	MACH_KERNEL
/*
 * Process an ioctl request.
 */
qeioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
	struct qe_softc *sc = &qe_softc[ifp->if_unit];
	struct ifaddr *ifa = (struct ifaddr *)data;
	int s = splimp(), error = 0;
 
	switch (cmd) {
 
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		qeinit(ifp->if_unit);
		switch(ifa->ifa_addr.sa_family) {
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
			register struct ns_addr *ina = &(IA_SNS(ifa)->sns_addr);
			
			if (ns_nullhost(*ina))
				ina->x_host = *(union ns_host *)(sc->is_addr);
			else
				qe_setaddr(ina->x_host.c_host, ifp->if_unit);
			break;
		    }
#endif
		}
		break;

	case SIOCSIFFLAGS:
#ifdef	MACH
	{
		u_char mode = 0;

		if (ifp->if_flags & IFF_ALLMULTI)
			mode |= 1;
		if (ifp->if_flags & IFF_PROMISC)
			mode |= 2;
		/*
		 *  Force a complete reset if the receive multicast/promiscuous
		 *  mode changes so that these take effect immediately.
		 */
		if (sc->setupmode != mode)
		{
			sc->setupmode = mode;
			if (sc->qe_flags & QEF_RUNNING)
			{
				((struct qedevice *)
				   (qeinfo[ifp->if_unit]->ui_addr))->qe_csr =
								       QE_RESET;
				sc->qe_flags &= ~QEF_RUNNING;
			}
		}
	}
#endif	MACH
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    sc->qe_flags & QEF_RUNNING) {
			((struct qedevice *)
			   (qeinfo[ifp->if_unit]->ui_addr))->qe_csr = QE_RESET;
			sc->qe_flags &= ~QEF_RUNNING;
		} else if (ifp->if_flags & IFF_UP &&
		    (sc->qe_flags & QEF_RUNNING) == 0)
			qerestart(sc);
		break;

#if	PACKET_LENGTH_STATS
	case SIOCCIFCNTRS:
		if (!suser()) {
			error = EINVAL;
			break;
		}
		bzero((caddr_t)qe_ein, sizeof (qe_ein));
		bzero((caddr_t)qe_eout, sizeof (qe_eout));
		bzero((caddr_t)qe_lin, sizeof (qe_lin));
		bzero((caddr_t)qe_lout, sizeof (qe_lout));
		bzero((caddr_t)&qe_arp, sizeof (int));
		break;

#endif	PACKET_LENGTH_STATS
	default:
		error = EINVAL;
 
	}
	splx(s);
	return (error);
}
#endif	MACH_KERNEL
 
#if	MACH && !defined(NS)
/*
 * set ethernet address for unit
 */
qe_setaddr(physaddr, unit)
	u_char *physaddr;
	int unit;
{
	register struct qe_softc *sc = &qe_softc[unit];
	register int i;

	for (i = 0; i < 6; i++)
		sc->setup_pkt[i][1] = sc->is_addr[i] = physaddr[i];
	sc->qe_flags |= QEF_SETADDR;
	if (sc->is_if.if_flags & IFF_RUNNING)
		qesetup(sc);
	qeinit(unit);
}
#endif	MACH && !defined(NS)
 
 
/*
 * Initialize a ring descriptor with mbuf allocation side effects
 */
qeinitdesc(rp, addr, len)
	register struct qe_ring *rp;
	caddr_t addr; 			/* mapped address */
	int len;
{
	/*
	 * clear the entire descriptor
	 */
	bzero((caddr_t)rp, sizeof(struct qe_ring));
 
	if( len ) {
		rp->qe_buf_len = -(len/2);
		rp->qe_addr_lo = (short)((int)addr);
		rp->qe_addr_hi = (short)((int)addr >> 16);
	}
}
/*
 * Build a setup packet - the physical address will already be present
 * in first column.
 */
qesetup( sc )
struct qe_softc *sc;
{
	register i, j;
 
	/*
	 * Copy the target address to the rest of the entries in this row.
	 */
	 for ( j = 0; j < 6 ; j++ )
		for ( i = 2 ; i < 8 ; i++ )
			sc->setup_pkt[j][i] = sc->setup_pkt[j][1];
	/*
	 * Duplicate the first half.
	 */
	bcopy((caddr_t)sc->setup_pkt[0], (caddr_t)sc->setup_pkt[8], 64);
	/*
	 * Fill in the broadcast address.
	 */
	for ( i = 0; i < 6 ; i++ )
		sc->setup_pkt[i][2] = 0xff;
	sc->setupqueued++;
}

/*
 * Pass a packet to the higher levels.
 * We deal with the trailer protocol here.
 */
qeread(sc, ifrw, len)
	register struct qe_softc *sc;
	struct ifrw *ifrw;
	int len;
{
#ifdef	MACH_KERNEL
	if_ubaget(&sc->qe_uba, ifrw, len + sizeof(struct ether_header),
		  &sc->is_if);
#else	MACH_KERNEL
	struct ether_header *eh;
    	struct mbuf *m;
	int off, resid;
	struct ifqueue *inq;
 
	/*
	 * Deal with trailer protocol: if type is INET trailer
	 * get true type from first 16-bit word past data.
	 * Remember that type was trailer by setting off.
	 */
 
	eh = (struct ether_header *)ifrw->ifrw_addr;
	eh->ether_type = ntohs((u_short)eh->ether_type);
#define	qedataaddr(eh, off, type)	((type)(((caddr_t)((eh)+1)+(off))))
	if (eh->ether_type >= ETHERTYPE_TRAIL &&
	    eh->ether_type < ETHERTYPE_TRAIL+ETHERTYPE_NTRAILER) {
		off = (eh->ether_type - ETHERTYPE_TRAIL) * 512;
		if (off >= ETHERMTU)
			return;		/* sanity */
		eh->ether_type = ntohs(*qedataaddr(eh,off, u_short *));
		resid = ntohs(*(qedataaddr(eh, off+2, u_short *)));
		if (off + resid > len)
		     return;		/* sanity */
		len = off + resid;
	} else
		off = 0;
	if (len == 0)
		return;
 
	/*
	 * Pull packet off interface.  Off is nonzero if packet
	 * has trailing header; qeget will then force this header
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
	 */
	m = if_ubaget(&sc->qe_uba, ifrw, len, off, &sc->is_if);
 
	if (m == 0)
		return;
 
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
		schednetisr(NETISR_IP);
		inq = &ipintrq;
		break;

	case ETHERTYPE_ARP:
		arpinput(&sc->is_ac, m);
#if	PACKET_LENGTH_STATS
		qe_arp++;
		if (qe_narp) {int l = len + sizeof (struct ether_header);
			qe_ein[log_2(l)]--;
			if (l < 128) qe_lin[l>>3]--;
		}
#endif	PACKET_LENGTH_STATS
		return;
#endif
#ifdef NS
	case ETHERTYPE_NS:
		schednetisr(NETISR_NS);
		inq = &nsintrq;
		break;

#endif
 
	default:
#if	DLI
	{
		eh->ether_type = htons(eh->ether_type);
		dli_input(m, eh->ether_type, &eh->ether_shost[0], 
 			  &qe_dlv[sc->is_if.if_unit], eh);
	}
#else	DLI
		m_freem(m);
#endif	DLI
		return;
	}
 
	if (IF_QFULL(inq)) {
		IF_DROP(inq);
		m_freem(m);
		return;
	}
	IF_ENQUEUE(inq, m);
#endif	MACH_KERNEL
}

/*
 * Watchdog timer routine. There is a condition in the hardware that
 * causes the board to lock up under heavy load. This routine detects
 * the hang up and restarts the device.
 */
qewatch()
{
	register struct qe_softc *sc;
	register int i;
	int inprogress=0;
 
	for (i = 0; i < NQE; i++) {
		sc = &qe_softc[i];
		if (sc->timeout) 
			if (++sc->timeout > 3 ) {
#if	MACH
				log(LOG_NOTICE,
#else	MACH
				log(LOG_ERR,
#endif	MACH
				     "qerestart: restarted qe%d %d\n",
				     i, ++sc->qe_restarts);
				qerestart(sc);
			} else
				inprogress++;
	}
	if (inprogress) {
		timeout(qewatch, (caddr_t)0, QE_TIMEO);
		qewatchrun++;
	} else
		qewatchrun=0;
}
/*
 * Restart for board lockup problem.
 */
qerestart(sc)
	register struct qe_softc *sc;
{
	register struct ifnet *ifp = &sc->is_if;
	register struct qedevice *addr = sc->addr;
	register struct qe_ring *rp;
	register i;
 
	addr->qe_csr = QE_RESET;
	sc->timeout = 0;
	qesetup( sc );
#if	MACH
	addr->qe_csr &= ~QE_RESET;
#endif	MACH
	for (i = 0, rp = sc->tring; i < NXMT; rp++, i++) {
		rp->qe_flag = rp->qe_status1 = QE_NOTYET;
		rp->qe_valid = 0;
	}
	sc->nxmit = sc->otindex = sc->tindex = sc->rindex = 0;
	addr->qe_csr = QE_RCV_ENABLE | QE_INT_ENABLE | QE_XMIT_INT |
	    QE_RCV_INT | QE_ILOOP;
	addr->qe_rcvlist_lo = (short)((int)sc->rringaddr);
	addr->qe_rcvlist_hi = (short)((int)sc->rringaddr >> 16);
	sc->qe_flags |= QEF_RUNNING;
	qestart(ifp->if_unit);
}
#endif
