h05944
s 00002/00002/00829
d D 8.1 93/06/11 15:54:08 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00018/00813
d D 7.5 92/10/11 10:20:09 bostic 10 9
c make kernel includes standard
e
s 00014/00001/00817
d D 7.4 92/05/20 16:52:30 bostic 9 8
c Don't loop forever in weintr.  Unfortunately, I can't explain why
c it was looping, but this fix keeps the machine from hanging, and
c it doesn't even cause problems with future packets.
c from Pace Willisson (pace@blitz.com)
e
s 00001/00001/00817
d D 7.3 91/05/21 14:19:02 bostic 8 7
c format police
e
s 00001/00039/00817
d D 7.2 91/05/12 19:39:40 william 7 6
c cleaning pass, removed dead code, updated comments, found boners
e
s 00329/00254/00527
d D 7.1 91/05/09 21:31:58 william 6 5
c newer versions
e
s 00000/00000/00781
d D 5.5 91/01/08 19:13:24 william 5 4
c  npx.c wd.c wt.c
e
s 00001/00001/00780
d D 5.4 90/11/18 11:32:02 bill 4 3
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00009/00030/00772
d D 5.3 90/11/08 19:40:54 bill 3 2
c fully working version
e
s 00245/00214/00557
d D 5.2 90/11/08 19:38:45 bill 2 1
c 1st working version
e
s 00771/00000/00000
d D 5.1 90/04/22 17:50:11 william 1 0
c date and time created 90/04/22 17:50:11 by william
e
u
U
t
T
I 1
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
D 8
 * Tim L. Tucker
E 8
I 8
 * Tim L. Tucker.
E 8
 *
D 6
 * %sccs.include.noredist.c%
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Modification history
 *
D 2
 * 8/28/89 - Initial version, Tim L Tucker
E 2
I 2
 * 8/28/89 - Initial version(if_wd.c), Tim L Tucker
E 2
 */
 
D 2
#include "wd.h"
#if	NWD > 0
E 2
I 2
#include "we.h"
D 10
#if	NWE > 0
E 10
I 10
#if NWE > 0
E 10
E 2
/*
 * Western Digital 8003 ethernet/starlan adapter
 *
 * Supports the following interface cards:
D 3
 * WD8003E, WD8003EBT, WD8003S, WD8003SBT
E 3
I 3
 * WD8003E, WD8003EBT, WD8003S, WD8003SBT, WD8013EBT
E 3
 *
 * The Western Digital card is one of many AT/MCA ethernet interfaces
D 3
 * based on the National N8390/NS32490 Network Interface chip set.
E 3
I 3
 * based on the National DS8390 Network Interface chip set.
E 3
 */
D 10
#include "param.h"
#include "mbuf.h"
#include "socket.h"
#include "ioctl.h"
#include "errno.h"
#include "syslog.h"
E 10
I 10
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/syslog.h>
E 10

D 6
#include "../net/if.h"
#include "../net/netisr.h"
E 6
I 6
D 10
#include "net/if.h"
#include "net/netisr.h"
E 10
I 10
#include <net/if.h>
#include <net/netisr.h>
E 10
E 6

#ifdef INET
D 6
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
#include "../netinet/in_var.h"
#include "../netinet/ip.h"
#include "../netinet/if_ether.h"
E 6
I 6
D 10
#include "netinet/in.h"
#include "netinet/in_systm.h"
#include "netinet/in_var.h"
#include "netinet/ip.h"
#include "netinet/if_ether.h"
E 10
I 10
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
E 10
E 6
#endif

#ifdef NS
D 6
#include "../netns/ns.h"
#include "../netns/ns_if.h"
E 6
I 6
D 10
#include "netns/ns.h"
#include "netns/ns_if.h"
E 10
I 10
#include <netns/ns.h>
#include <netns/ns_if.h>
E 10
E 6
#endif

D 2
#include "if_wdreg.h"
#include "../isa/isavar.h"
E 2
I 2
D 6
#include "machine/isa/if_wereg.h"
D 4
#include "machine/isa/device.h"
E 4
I 4
#include "machine/isa/isa_device.h"
E 6
I 6
D 10
#include "i386/isa/if_wereg.h"
#include "i386/isa/isa_device.h"
E 10
I 10
#include <i386/isa/if_wereg.h>
#include <i386/isa/isa_device.h>
E 10
E 6
E 4
E 2
 
/*
D 2
 * This constant should really be 60 because the wd adds 4 bytes of crc.
E 2
I 2
 * This constant should really be 60 because the we adds 4 bytes of crc.
E 2
 * However when set to 60 our packets are ignored by deuna's , 3coms are
 * okay ??????????????????????????????????????????
 */
#define ETHER_MIN_LEN 64
#define	ETHER_ADDR_LEN 6
#define ETHER_HDR_SIZE 14
 
/*
 * Ethernet software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * qe_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its address, ...
 */
D 2
struct	wd_softc {
	struct	arpcom wd_ac;		/* Ethernet common part 	*/
#define	wd_if	wd_ac.ac_if		/* network-visible interface 	*/
#define	wd_addr	wd_ac.ac_enaddr		/* hardware Ethernet address 	*/
E 2
I 2
struct	we_softc {
	struct	arpcom we_ac;		/* Ethernet common part 	*/
#define	we_if	we_ac.ac_if		/* network-visible interface 	*/
#define	we_addr	we_ac.ac_enaddr		/* hardware Ethernet address 	*/
E 2

D 2
	u_char	wd_flags;		/* software state		*/
E 2
I 2
	u_char	we_flags;		/* software state		*/
E 2
#define	WDF_RUNNING	0x01
#define WDF_TXBUSY	0x02

D 2
	u_char	wd_type;		/* interface type code		*/
	u_short	wd_vector;		/* interrupt vector 		*/
	caddr_t	wd_io_ctl_addr;		/* i/o bus address, control	*/
	caddr_t	wd_io_nic_addr;		/* i/o bus address, NS32490	*/
E 2
I 2
	u_char	we_type;		/* interface type code		*/
	u_short	we_vector;		/* interrupt vector 		*/
D 6
	caddr_t	we_io_ctl_addr;		/* i/o bus address, control	*/
D 3
	caddr_t	we_io_nic_addr;		/* i/o bus address, NS32490	*/
E 3
I 3
	caddr_t	we_io_nic_addr;		/* i/o bus address, DS8390	*/
E 6
I 6
	short	we_io_ctl_addr;		/* i/o bus address, control	*/
	short	we_io_nic_addr;		/* i/o bus address, DS8390	*/
E 6
E 3
E 2

D 2
	caddr_t	wd_vmem_addr;		/* card RAM virtual memory base */
	u_long	wd_vmem_size;		/* card RAM bytes		*/
	caddr_t	wd_vmem_ring;		/* receive ring RAM vaddress	*/
} wd_softc[NWD];
E 2
I 2
	caddr_t	we_vmem_addr;		/* card RAM virtual memory base */
	u_long	we_vmem_size;		/* card RAM bytes		*/
	caddr_t	we_vmem_ring;		/* receive ring RAM vaddress	*/
I 6
	caddr_t	we_vmem_end;		/* receive ring RAM end	*/
E 6
} we_softc[NWE];
E 2

D 2
int	wdprobe(), wdattach(), wdintr();
int	wdinit(), wdoutput(), wdioctl(), wdreset();
E 2
I 2
D 6
int	weprobe(), weattach(), weintr();
int	weinit(), weoutput(), weioctl(), wereset();
E 6
I 6
int	weprobe(), weattach(), weintr(), westart();
int	weinit(), ether_output(), weioctl(), wereset(), wewatchdog();
E 6

struct	isa_driver wedriver = {
	weprobe, weattach, "we",
};
E 2
 
/*
 * Probe the WD8003 to see if it's there
 */
D 2
wdprobe(reg, is)
	caddr_t reg;
E 2
I 2
weprobe(is)
E 2
	struct isa_device *is;
{
	register int i;
D 2
	register struct wd_softc *sc = &wd_softc[is->is_unit];
	union wd_mem_sel wdm;
E 2
I 2
	register struct we_softc *sc = &we_softc[is->id_unit];
	union we_mem_sel wem;
E 2
	u_char sum;
 
	/*
	 * Here we check the card ROM, if the checksum passes, and the
	 * type code and ethernet address check out, then we know we have
	 * a wd8003 card.
	 *
	 * Autoconfiguration: No warning message is printed on error.
	 */
	for (sum = 0, i = 0; i < 8; ++i)
D 2
	    sum += INB(reg + WD_ROM_OFFSET + i);
E 2
I 2
	    sum += inb(is->id_iobase + WD_ROM_OFFSET + i);
E 2
	if (sum != WD_CHECKSUM)
            return (0);
D 2
	sc->wd_type = INB(reg + WD_ROM_OFFSET + 6);
	if ((sc->wd_type != WD_ETHER) && (sc->wd_type != WD_STARLAN))
E 2
I 2
	sc->we_type = inb(is->id_iobase + WD_ROM_OFFSET + 6);
	if ((sc->we_type != WD_ETHER) && (sc->we_type != WD_STARLAN)
	&& (sc->we_type != WD_ETHER2))
E 2
            return (0);

	/*
	 * Setup card RAM area and i/o addresses
	 * Kernel Virtual to segment C0000-DFFFF?????
	 */
D 2
	sc->wd_io_ctl_addr = reg;
	sc->wd_io_nic_addr = sc->wd_io_ctl_addr + WD_NIC_OFFSET;
	sc->wd_vector = is->is_vector;
	sc->wd_vmem_addr = (caddr_t)is->is_mem;
	sc->wd_vmem_size = is->is_memsize;
	sc->wd_vmem_ring = sc->wd_vmem_addr + (WD_PAGE_SIZE * WD_TXBUF_SIZE);
E 2
I 2
	sc->we_io_ctl_addr = is->id_iobase;
	sc->we_io_nic_addr = sc->we_io_ctl_addr + WD_NIC_OFFSET;
	sc->we_vector = is->id_irq;
	sc->we_vmem_addr = (caddr_t)is->id_maddr;
	sc->we_vmem_size = is->id_msize;
	sc->we_vmem_ring = sc->we_vmem_addr + (WD_PAGE_SIZE * WD_TXBUF_SIZE);
I 6
	sc->we_vmem_end = sc->we_vmem_addr + is->id_msize;
E 6
E 2

	/*
	 * Save board ROM station address
	 */
	for (i = 0; i < ETHER_ADDR_LEN; ++i)
D 2
	    sc->wd_addr[i] = INB(sc->wd_io_ctl_addr + WD_ROM_OFFSET + i);
E 2
I 2
	    sc->we_addr[i] = inb(sc->we_io_ctl_addr + WD_ROM_OFFSET + i);
E 2

	/*
	 * Mapin interface memory, setup memory select register
	 */
D 2
	wdm.ms_addr = (u_long)sc->wd_vmem_addr >> 13; 
	wdm.ms_enable = 1;
	wdm.ms_reset = 0;
	OUTB(sc->wd_io_ctl_addr, wdm.ms_byte);
E 2
I 2
D 6
	/* wem.ms_addr = (u_long)sc->we_vmem_addr >> 13;  */
	wem.ms_addr = (u_long)(0xd0000)>> 13; 
E 6
I 6
	/* wem.ms_addr = (u_long)sc->we_vmem_addr >> 13; */
	wem.ms_addr = (u_long)(0xd0000)>> 13;
E 6
	wem.ms_enable = 1;
	wem.ms_reset = 0;
	outb(sc->we_io_ctl_addr, wem.ms_byte);
E 2

	/*
	 * clear interface memory, then sum to make sure its valid
	 */
D 2
	for (i = 0; i < sc->wd_vmem_size; ++i)
	    sc->wd_vmem_addr[i] = 0x0;
	for (sum = 0, i = 0; i < sc->wd_vmem_size; ++i)
	    sum += sc->wd_vmem_addr[i];
E 2
I 2
	for (i = 0; i < sc->we_vmem_size; ++i)
	    sc->we_vmem_addr[i] = 0x0;
	for (sum = 0, i = 0; i < sc->we_vmem_size; ++i)
	    sum += sc->we_vmem_addr[i];
E 2
	if (sum != 0x0) {
D 2
            printf("wd%d: wd8003 dual port RAM address error\n", is->is_unit);
E 2
I 2
            printf("we%d: wd8003 dual port RAM address error\n", is->id_unit);
E 2
	    return (0);
	}

	return (WD_IO_PORTS);
}
 
/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 */
D 2
wdattach(is)
E 2
I 2
weattach(is)
E 2
	struct isa_device *is;
{
D 2
	register struct wd_softc *sc = &wd_softc[is->is_unit];
	register struct ifnet *ifp = &sc->wd_if;
E 2
I 2
	register struct we_softc *sc = &we_softc[is->id_unit];
	register struct ifnet *ifp = &sc->we_if;
I 6
	union we_command wecmd;
E 6
E 2
 
I 6
	wecmd.cs_byte = inb(sc->we_io_nic_addr + WD_P0_COMMAND);
	wecmd.cs_stp = 1;
	wecmd.cs_sta = 0;
	wecmd.cs_ps = 0;
	outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
E 6
	/*
	 * Initialize ifnet structure
	 */
D 2
	ifp->if_unit = is->is_unit;
	ifp->if_name = "wd";
E 2
I 2
	ifp->if_unit = is->id_unit;
D 6
	ifp->if_name = "we";
E 6
I 6
	ifp->if_name = "we" ;
E 6
E 2
	ifp->if_mtu = ETHERMTU;
D 6
	ifp->if_flags = IFF_BROADCAST|IFF_NOTRAILERS;
E 6
I 6
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_NOTRAILERS ;
E 6
D 2
	ifp->if_init = wdinit;
	ifp->if_output = wdoutput;
	ifp->if_ioctl = wdioctl;
	ifp->if_reset = wdreset;
E 2
I 2
	ifp->if_init = weinit;
D 6
	ifp->if_output = weoutput;
E 6
I 6
	ifp->if_output = ether_output;
	ifp->if_start = westart;
E 6
	ifp->if_ioctl = weioctl;
	ifp->if_reset = wereset;
E 2
D 6
	ifp->if_watchdog = 0;
E 6
I 6
	ifp->if_watchdog = wewatchdog;
E 6
	if_attach(ifp);
 
	/*
	 * Banner...
	 */
D 2
	printf("wd%d: %s, hardware address %s\n", is->is_unit,
		((sc->wd_type == WD_ETHER) ? "ethernet" : "starlan"),
		ether_sprintf(sc->wd_addr));
E 2
I 2
	printf(" %s address %s",
		((sc->we_type != WD_STARLAN) ? "ethernet" : "starlan"),
		ether_sprintf(sc->we_addr));
E 2
}
 
/*
 * Reset of interface.
 */
D 2
wdreset(unit, uban)
E 2
I 2
wereset(unit, uban)
E 2
	int unit, uban;
{
D 2
	if (unit >= NWD)
E 2
I 2
	if (unit >= NWE)
E 2
		return;
D 2
	printf("wd%d: reset\n", unit);
	wd_softc[unit].wd_flags &= ~WDF_RUNNING;
	wdinit(unit);
E 2
I 2
	printf("we%d: reset\n", unit);
D 6
	we_softc[unit].we_flags &= ~WDF_RUNNING;
E 6
I 6
/*	we_softc[unit].we_flags &= ~WDF_RUNNING; */
E 6
	weinit(unit);
E 2
}
 
/*
 * Take interface offline.
 */
D 2
wdstop(unit)
E 2
I 2
westop(unit)
E 2
	int unit;
{
D 2
	register struct wd_softc *sc = &wd_softc[unit];
	union wd_command wdcmd;
E 2
I 2
	register struct we_softc *sc = &we_softc[unit];
	union we_command wecmd;
E 2
	int s;
 
	/*
D 3
	 * Shutdown NS32490
E 3
I 3
	 * Shutdown DS8390
E 3
	 */
	s = splimp();
D 2
	wdcmd.cs_byte = INB(sc->wd_io_nic_addr + WD_P0_COMMAND);
	wdcmd.cs_stp = 1;
	wdcmd.cs_sta = 0;
	wdcmd.cs_ps = 0;
	OUTB(sc->wd_io_nic_addr + WD_P0_COMMAND, wdcmd.cs_byte);
E 2
I 2
	wecmd.cs_byte = inb(sc->we_io_nic_addr + WD_P0_COMMAND);
	wecmd.cs_stp = 1;
	wecmd.cs_sta = 0;
	wecmd.cs_ps = 0;
	outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
E 2
	(void) splx(s);
}

I 6
wewatchdog(unit) {

	log(LOG_WARNING,"we%d: soft reset\n", unit);
D 7
printf("we: reset!\n");
E 7
	westop(unit);
D 7
DELAY(100000);
E 7
	weinit(unit);
}

static Bdry;
E 6
/*
D 3
 * Initialization of interface (really just NS32490). 
E 3
I 3
 * Initialization of interface (really just DS8390). 
E 3
 */
D 2
wdinit(unit)
E 2
I 2
weinit(unit)
E 2
	int unit;
{
D 2
	register struct wd_softc *sc = &wd_softc[unit];
	register struct ifnet *ifp = &sc->wd_if;
	union wd_command wdcmd;
E 2
I 2
	register struct we_softc *sc = &we_softc[unit];
	register struct ifnet *ifp = &sc->we_if;
	union we_command wecmd;
E 2
	int i, s;
 
	/* address not known */
	if (ifp->if_addrlist == (struct ifaddr *)0)
		return;

	/* already running */
D 2
	if (sc->wd_flags & WDF_RUNNING)
E 2
I 2
D 6
	if (sc->we_flags & WDF_RUNNING)
E 2
		return;
E 6
I 6
D 7
/*	if (sc->we_flags & WDF_RUNNING)*/
E 7
	/*if (ifp->if_flags & IFF_RUNNING) return; */
E 6

	/*
D 3
	 * Initialize NS32490 in order given in NSC NIC manual.
E 3
I 3
	 * Initialize DS8390 in order given in NSC NIC manual.
E 3
	 * this is stock code...please see the National manual for details.
	 */
D 2
	s = splhi();
	wdcmd.cs_byte = INB(sc->wd_io_nic_addr + WD_P0_COMMAND);
	wdcmd.cs_stp = 1;
	wdcmd.cs_sta = 0;
	wdcmd.cs_ps = 0;
	OUTB(sc->wd_io_nic_addr + WD_P0_COMMAND, wdcmd.cs_byte);
	OUTB(sc->wd_io_nic_addr + WD_P0_DCR, WD_D_CONFIG);
	OUTB(sc->wd_io_nic_addr + WD_P0_RBCR0, 0);
	OUTB(sc->wd_io_nic_addr + WD_P0_RBCR1, 0);
	OUTB(sc->wd_io_nic_addr + WD_P0_RCR, WD_R_MON);
	OUTB(sc->wd_io_nic_addr + WD_P0_TCR, WD_T_CONFIG);
	OUTB(sc->wd_io_nic_addr + WD_P0_TPSR, 0);
	OUTB(sc->wd_io_nic_addr + WD_P0_PSTART, WD_TXBUF_SIZE);
	OUTB(sc->wd_io_nic_addr + WD_P0_PSTOP,
		sc->wd_vmem_size / WD_PAGE_SIZE);
	OUTB(sc->wd_io_nic_addr + WD_P0_BNRY, WD_TXBUF_SIZE);
	OUTB(sc->wd_io_nic_addr + WD_P0_ISR, 0xff);
	OUTB(sc->wd_io_nic_addr + WD_P0_IMR, WD_I_CONFIG);
	wdcmd.cs_ps = 1;
	OUTB(sc->wd_io_nic_addr + WD_P0_COMMAND, wdcmd.cs_byte);
E 2
I 2
	s = splhigh();
I 6
Bdry = 0;
E 6
	wecmd.cs_byte = inb(sc->we_io_nic_addr + WD_P0_COMMAND);
	wecmd.cs_stp = 1;
	wecmd.cs_sta = 0;
	wecmd.cs_ps = 0;
	outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
	outb(sc->we_io_nic_addr + WD_P0_DCR, WD_D_CONFIG);
	outb(sc->we_io_nic_addr + WD_P0_RBCR0, 0);
	outb(sc->we_io_nic_addr + WD_P0_RBCR1, 0);
	outb(sc->we_io_nic_addr + WD_P0_RCR, WD_R_MON);
	outb(sc->we_io_nic_addr + WD_P0_TCR, WD_T_CONFIG);
	outb(sc->we_io_nic_addr + WD_P0_TPSR, 0);
	outb(sc->we_io_nic_addr + WD_P0_PSTART, WD_TXBUF_SIZE);
	outb(sc->we_io_nic_addr + WD_P0_PSTOP,
		sc->we_vmem_size / WD_PAGE_SIZE);
	outb(sc->we_io_nic_addr + WD_P0_BNRY, WD_TXBUF_SIZE);
	outb(sc->we_io_nic_addr + WD_P0_ISR, 0xff);
D 3
#define WD_I_CONFIG	0xff
E 3
	outb(sc->we_io_nic_addr + WD_P0_IMR, WD_I_CONFIG);
	wecmd.cs_ps = 1;
	outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
E 2
	for (i = 0; i < ETHER_ADDR_LEN; ++i)
D 2
	    OUTB(sc->wd_io_nic_addr + WD_P1_PAR0 + i, sc->wd_addr[i]);
E 2
I 2
	    outb(sc->we_io_nic_addr + WD_P1_PAR0 + i, sc->we_addr[i]);
E 2
	for (i = 0; i < ETHER_ADDR_LEN; ++i)	/* == broadcast addr */
D 2
	    OUTB(sc->wd_io_nic_addr + WD_P1_MAR0 + i, 0xff);
	OUTB(sc->wd_io_nic_addr + WD_P1_CURR, WD_TXBUF_SIZE);
	wdcmd.cs_ps = 0;
	wdcmd.cs_stp = 0;
	wdcmd.cs_sta = 1;
	wdcmd.cs_rd = 0x4;
	OUTB(sc->wd_io_nic_addr + WD_P1_COMMAND, wdcmd.cs_byte);
	OUTB(sc->wd_io_nic_addr + WD_P0_RCR, WD_R_CONFIG);
E 2
I 2
	    outb(sc->we_io_nic_addr + WD_P1_MAR0 + i, 0xff);
	outb(sc->we_io_nic_addr + WD_P1_CURR, WD_TXBUF_SIZE);
	wecmd.cs_ps = 0;
	wecmd.cs_stp = 0;
	wecmd.cs_sta = 1;
	wecmd.cs_rd = 0x4;
	outb(sc->we_io_nic_addr + WD_P1_COMMAND, wecmd.cs_byte);
	outb(sc->we_io_nic_addr + WD_P0_RCR, WD_R_CONFIG);
E 2

	/*
	 * Take the interface out of reset, program the vector, 
	 * enable interrupts, and tell the world we are up.
	 */
D 6
	ifp->if_flags |= IFF_UP | IFF_RUNNING;
D 2
	sc->wd_flags |= WDF_RUNNING;
	sc->wd_flags &= ~WDF_TXBUSY;
E 2
I 2
	sc->we_flags |= WDF_RUNNING;
E 6
I 6
	ifp->if_flags |= IFF_RUNNING;
E 6
	sc->we_flags &= ~WDF_TXBUSY;
E 2
	(void) splx(s);
D 2
	wdstart(unit);
E 2
I 2
D 6
	westart(unit);
E 6
I 6
	westart(ifp);
E 6
E 2
}
 
/*
 * Start output on interface.
 */
D 2
wdstart(unit)
E 2
I 2
D 6
westart(unit)
E 2
	int unit;
E 6
I 6
westart(ifp)
	struct ifnet *ifp;
E 6
{
D 2
	register struct wd_softc *sc = &wd_softc[unit];
E 2
I 2
D 6
	register struct we_softc *sc = &we_softc[unit];
E 6
I 6
	register struct we_softc *sc = &we_softc[ifp->if_unit];
E 6
E 2
	struct mbuf *m0, *m;
	register caddr_t buffer;
D 6
	int len = 0, s;
E 6
I 6
	int len, s;
E 6
D 2
	union wd_command wdcmd;
E 2
I 2
	union we_command wecmd;
E 2
 
	/*
D 3
	 * The NS32490 has only one transmit buffer, if it is busy we
E 3
I 3
	 * The DS8390 has only one transmit buffer, if it is busy we
E 3
	 * must wait until the transmit interrupt completes.
	 */
D 2
	s = splhi();
	if (sc->wd_flags & WDF_TXBUSY) {
E 2
I 2
	s = splhigh();
	if (sc->we_flags & WDF_TXBUSY) {
E 2
		(void) splx(s);
		return;
	}
D 2
	IF_DEQUEUE(&sc->wd_if.if_snd, m);
E 2
I 2
	IF_DEQUEUE(&sc->we_if.if_snd, m);
E 2
	if (m == 0) {
		(void) splx(s);
		return;
	}
D 2
	sc->wd_flags |= WDF_TXBUSY; 
E 2
I 2
	sc->we_flags |= WDF_TXBUSY; 
E 2
	(void) splx(s);

	/*
	 * Copy the mbuf chain into the transmit buffer
	 */
D 2
	buffer = sc->wd_vmem_addr;
E 2
I 2
	buffer = sc->we_vmem_addr;
I 6
	len = 0;
D 7
/*printf("\nT   "); */
E 7
E 6
E 2
	for (m0 = m; m != 0; m = m->m_next) {
I 6
D 7
/*int j;*/
E 7
E 6
		bcopy(mtod(m, caddr_t), buffer, m->m_len);
I 6
D 7
/*for(j=0; j < m->m_len;j++) {

	puthex(buffer[j]);
	if (j == sizeof(struct ether_header)-1)
		printf("|");
}*/
E 7
E 6
		buffer += m->m_len;
        	len += m->m_len;
	}
I 6
D 7
/*printf("|%d ", len);*/
E 7
E 6

D 6
	/*
	 * If this was a broadcast packet loop it
	 * back because the hardware can't hear its own
	 * transmits.
	 */
I 2
D 3
#ifdef notyet
E 3
E 2
	if (bcmp((caddr_t)(mtod(m0, struct ether_header *)->ether_dhost),
	   (caddr_t)etherbroadcastaddr,
	   sizeof(etherbroadcastaddr)) == 0) {
D 2
		wdread(sc, m0);
E 2
I 2
		weread(sc, m0);
E 2
	} else {
I 2
D 3
#endif
E 3
E 2
		m_freem(m0);
I 2
D 3
#ifdef notyet
E 3
E 2
	}
E 6
I 6
	m_freem(m0);
E 6
I 2
D 3
#endif
E 3
E 2

	/*
	 * Init transmit length registers, and set transmit start flag.
	 */
D 2
	s = splhi();
E 2
I 2
	s = splhigh();
E 2
	len = MAX(len, ETHER_MIN_LEN);
I 6
D 7
/*printf("L %d ", len);
	if (len < 70) len=70;*/
E 7
E 6
D 2
	wdcmd.cs_byte = INB(sc->wd_io_nic_addr + WD_P0_COMMAND);
	wdcmd.cs_ps = 0;
	OUTB(sc->wd_io_nic_addr + WD_P0_COMMAND, wdcmd.cs_byte);
	OUTB(sc->wd_io_nic_addr + WD_P0_TBCR0, len & 0xff);
	OUTB(sc->wd_io_nic_addr + WD_P0_TBCR1, len >> 8);
	wdcmd.cs_txp = 1;
	OUTB(sc->wd_io_nic_addr + WD_P0_COMMAND, wdcmd.cs_byte);
E 2
I 2
	wecmd.cs_byte = inb(sc->we_io_nic_addr + WD_P0_COMMAND);
	wecmd.cs_ps = 0;
	outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
	outb(sc->we_io_nic_addr + WD_P0_TBCR0, len & 0xff);
	outb(sc->we_io_nic_addr + WD_P0_TBCR1, len >> 8);
	wecmd.cs_txp = 1;
	outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
E 2
	(void) splx(s);
}
 
/*
 * Ethernet interface interrupt processor
 */
D 2
wdintr(unit)
E 2
I 2
weintr(unit)
E 2
	int unit;
{
D 2
	register struct wd_softc *sc = &wd_softc[unit];
	union wd_command wdcmd;
	union wd_interrupt wdisr;
E 2
I 2
D 6
	register struct we_softc *sc = &we_softc[0];
E 6
I 6
	register struct we_softc *sc = &we_softc[unit];
E 6
	union we_command wecmd;
	union we_interrupt weisr;
I 9
	int nloops = 10;
E 9
E 2
D 6
	int s;
E 6
I 6

E 6
I 2
	unit =0;
E 2
 
	/* disable onboard interrupts, then get interrupt status */
D 2
	s = splhi();
	wdcmd.cs_byte = INB(sc->wd_io_nic_addr + WD_P0_COMMAND);
	wdcmd.cs_ps = 0;
	OUTB(sc->wd_io_nic_addr + WD_P0_COMMAND, wdcmd.cs_byte);
	OUTB(sc->wd_io_nic_addr + WD_P0_IMR, 0);
	wdisr.is_byte = INB(sc->wd_io_nic_addr + WD_P0_ISR);
	OUTB(sc->wd_io_nic_addr + WD_P0_ISR, 0xff);
E 2
I 2
D 6
	s = splhigh();
E 6
	wecmd.cs_byte = inb(sc->we_io_nic_addr + WD_P0_COMMAND);
	wecmd.cs_ps = 0;
	outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
D 3
	/* outb(sc->we_io_nic_addr + WD_P0_IMR, 0); */
E 3
I 3
D 6
	outb(sc->we_io_nic_addr + WD_P0_IMR, 0);
E 6
I 6
D 7
	/*outb(sc->we_io_nic_addr + WD_P0_IMR, 0);*/
E 7
E 6
E 3
	weisr.is_byte = inb(sc->we_io_nic_addr + WD_P0_ISR);
D 3
#ifdef notdef
printf("weintr %x ", inb(sc->we_io_nic_addr + WD_P0_ISR));
outb(sc->we_io_nic_addr+WD_P0_IMR,0xff);
#endif
E 3
D 6
	outb(sc->we_io_nic_addr + WD_P0_ISR, 0xff);
E 2
	(void) splx(s);
E 6
I 6
loop:
	outb(sc->we_io_nic_addr + WD_P0_ISR, weisr.is_byte);
E 6

	/* transmit error */
D 2
	if (wdisr.is_txe) {
E 2
I 2
	if (weisr.is_txe) {
D 3
printf("txe\n");
E 3
E 2
		/* need to read these registers to clear status */
D 2
		sc->wd_if.if_collisions +=
		    INB(sc->wd_io_nic_addr + WD_P0_TBCR0);
		++sc->wd_if.if_oerrors;
E 2
I 2
		sc->we_if.if_collisions +=
		    inb(sc->we_io_nic_addr + WD_P0_TBCR0);
		++sc->we_if.if_oerrors;
E 2
	}

	/* receiver error */
D 2
	if (wdisr.is_rxe) {
E 2
I 2
	if (weisr.is_rxe) {
D 3
printf("rxe\n");
E 3
E 2
		/* need to read these registers to clear status */
D 2
		(void) INB(sc->wd_io_nic_addr + 0xD);
		(void) INB(sc->wd_io_nic_addr + 0xE);
		(void) INB(sc->wd_io_nic_addr + 0xF);
		++sc->wd_if.if_ierrors;
E 2
I 2
		(void) inb(sc->we_io_nic_addr + 0xD);
		(void) inb(sc->we_io_nic_addr + 0xE);
		(void) inb(sc->we_io_nic_addr + 0xF);
		++sc->we_if.if_ierrors;
E 2
	}

	/* normal transmit complete */
D 2
	if (wdisr.is_ptx)
		wdtint (unit);
E 2
I 2
D 6
	if (weisr.is_ptx)
E 6
I 6
	if (weisr.is_ptx || weisr.is_txe)
E 6
		wetint (unit);
E 2

	/* normal receive notification */
D 2
	if (wdisr.is_prx)
		wdrint (unit);
E 2
I 2
D 6
	if (weisr.is_prx)
E 6
I 6
	if (weisr.is_prx || weisr.is_rxe)
E 6
		werint (unit);
E 2

	/* try to start transmit */
D 2
	wdstart(unit);
E 2
I 2
D 6
	westart(unit);
E 6
I 6
	westart(&sc->we_if);
E 6
E 2

	/* re-enable onboard interrupts */
D 2
	wdcmd.cs_byte = INB(sc->wd_io_nic_addr + WD_P0_COMMAND);
	wdcmd.cs_ps = 0;
	OUTB(sc->wd_io_nic_addr + WD_P0_COMMAND, wdcmd.cs_byte);
	OUTB(sc->wd_io_nic_addr + WD_P0_IMR, WD_I_CONFIG);
E 2
I 2
	wecmd.cs_byte = inb(sc->we_io_nic_addr + WD_P0_COMMAND);
	wecmd.cs_ps = 0;
	outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
D 6
	outb(sc->we_io_nic_addr + WD_P0_IMR, WD_I_CONFIG);
E 6
I 6
	outb(sc->we_io_nic_addr + WD_P0_IMR, 0xff/*WD_I_CONFIG*/);
	weisr.is_byte = inb(sc->we_io_nic_addr + WD_P0_ISR);
D 9
	if (weisr.is_byte) goto loop;
E 9
I 9
	if (weisr.is_byte) {
		/*
		 * I caught it looping forever here a couple of times,
		 * but I haven't had time to figure out why.  Just
		 * returning seems to be safe, and it does not appear
		 * to interfere with future packets.    - Pace 5/19/92
		 */
		if (--nloops <= 0) {
			printf ("we0: weintr is looping\n");
			return;
		}
		goto loop;
	}
E 9
E 6
E 2
}
 
/*
 * Ethernet interface transmit interrupt.
 */
D 2
wdtint(unit)
E 2
I 2
wetint(unit)
E 2
	int unit;
{
D 2
	register struct wd_softc *sc = &wd_softc[unit];
E 2
I 2
	register struct we_softc *sc = &we_softc[unit];
E 2

	/*
	 * Do some statistics (assume page zero of NIC mapped in)
	 */
D 2
	sc->wd_flags &= ~WDF_TXBUSY; 
	sc->wd_if.if_timer = 0;
	++sc->wd_if.if_opackets;
	sc->wd_if.if_collisions += INB(sc->wd_io_nic_addr + WD_P0_TBCR0);
E 2
I 2
	sc->we_flags &= ~WDF_TXBUSY; 
	sc->we_if.if_timer = 0;
	++sc->we_if.if_opackets;
	sc->we_if.if_collisions += inb(sc->we_io_nic_addr + WD_P0_TBCR0);
E 2
}
 
/*
 * Ethernet interface receiver interrupt.
 */
D 2
wdrint(unit)
E 2
I 2
werint(unit)
E 2
	int unit;
{
D 2
	register struct wd_softc *sc = &wd_softc[unit];
E 2
I 2
	register struct we_softc *sc = &we_softc[unit];
E 2
D 6
	register struct mbuf **m;
	int mlen, len, count;
E 6
	u_char bnry, curr;
I 6
	long len;
E 6
D 2
	union wd_command wdcmd;
	struct wd_ring *wdr;
E 2
I 2
	union we_command wecmd;
	struct we_ring *wer;
E 2
D 6
	struct mbuf *m0;
	caddr_t pkt, endp;
I 2
static Bdry;
E 6
E 2
 
	/*
	 * Traverse the receive ring looking for packets to pass back.
	 * The search is complete when we find a descriptor not in use.
	 */
D 2
	wdcmd.cs_byte = INB(sc->wd_io_nic_addr + WD_P0_COMMAND);
	wdcmd.cs_ps = 0;
	OUTB(sc->wd_io_nic_addr + WD_P0_COMMAND, wdcmd.cs_byte);
	bnry = INB(sc->wd_io_nic_addr + WD_P0_BNRY);
	wdcmd.cs_ps = 1;
	OUTB(sc->wd_io_nic_addr + WD_P0_COMMAND, wdcmd.cs_byte);
	curr = INB(sc->wd_io_nic_addr + WD_P1_CURR);
E 2
I 2
	wecmd.cs_byte = inb(sc->we_io_nic_addr + WD_P0_COMMAND);
	wecmd.cs_ps = 0;
	outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
	bnry = inb(sc->we_io_nic_addr + WD_P0_BNRY);
	wecmd.cs_ps = 1;
	outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
	curr = inb(sc->we_io_nic_addr + WD_P1_CURR);
D 3
printf("Bd %x cur %x ", bnry, curr);
if(Bdry && Bdry > bnry){
E 3
I 3
D 6
if(Bdry && Bdry > bnry)
E 6
I 6
if(Bdry)
E 6
E 3
	bnry =Bdry;
I 6

D 7
/*printf("B %d c %d ", bnry, curr);*/
E 7
E 6
D 3
printf("bd %x! ", bnry);
}
E 3
E 2
	while (bnry != curr)
	{
		/* get pointer to this buffer header structure */
D 2
		wdr = (struct wd_ring *)(sc->wd_vmem_addr + (bnry << 8));
        	len = wdr->wd_count - 4;	/* count includes CRC */
		pkt = (caddr_t)(wdr + 1) - 2;	/* 2 - word align pkt data */
        	count = len + 2;		/* copy two extra bytes */
		endp = (caddr_t)(sc->wd_vmem_addr + sc->wd_vmem_size);
		++sc->wd_if.if_ipackets;
E 2
I 2
		wer = (struct we_ring *)(sc->we_vmem_addr + (bnry << 8));
D 6
        	len = wer->we_count - 4;	/* count includes CRC */
D 3
printf("l %d", len);
E 3
		pkt = (caddr_t)(wer + 1) /*- 2*/;	/* 2 - word align pkt data */
        	count = len /*+ 2*/;		/* copy two extra bytes */
		endp = (caddr_t)(sc->we_vmem_addr + sc->we_vmem_size);
		++sc->we_if.if_ipackets;
E 6
E 2

D 6
		/* pull packet out of dual ported RAM */
		m = &m0; m0 = 0;
		while (count > 0)
		{
		    /* drop chain if can't get another buffer */
		    MGET(*m, M_DONTWAIT, MT_DATA);
		    if (*m == 0)
		    {
			m_freem(m0);
			goto outofbufs;
		    }
E 6
I 6
		/* count includes CRC */
		len = wer->we_count - 4;
		if (len > 30 && len <= ETHERMTU+100
			/*&& (*(char *)wer  == 1 || *(char *) wer == 0x21)*/)
			weread(sc, (caddr_t)(wer + 1), len);
		else printf("reject %d", len);
E 6

D 6
		    /* fill mbuf and attach to packet list */
		    mlen = MIN(MLEN, count);
		    mlen = MIN(mlen, endp - pkt);
		    bcopy(pkt, mtod(*m, caddr_t), mlen);
		    (*m)->m_len = mlen;
		    m = &((*m)->m_next);
		    pkt += mlen;
		    count -= mlen;

		    /* wrap memory pointer around circ buffer */
		    if (pkt == endp)
D 2
			pkt = (caddr_t)sc->wd_vmem_ring;
E 2
I 2
			pkt = (caddr_t)sc->we_vmem_ring;
E 2
		}

		/* skip aligment bytes, send packet up to higher levels */
		if (m0 != 0)
		{
D 2
		    m0->m_off += 2;
		    wdread(sc, m0);
E 2
I 2
/*		    m0->m_off += 2*/;
		    weread(sc, m0);
E 2
		}

E 6
outofbufs:
D 6
		/* advance on chip Boundry register */
D 2
		bnry = wdr->wd_next_packet;
		wdcmd.cs_byte = INB(sc->wd_io_nic_addr + WD_P0_COMMAND);
		wdcmd.cs_ps = 0;
		OUTB(sc->wd_io_nic_addr + WD_P0_COMMAND, wdcmd.cs_byte);
E 2
I 2
D 3
printf("nx %x ", wer->we_next_packet);
E 3
		bnry = wer->we_next_packet;
E 6
		wecmd.cs_byte = inb(sc->we_io_nic_addr + WD_P0_COMMAND);
		wecmd.cs_ps = 0;
		outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
E 2

D 6
		/* watch out for NIC overflow, reset Boundry if invalid */
		if ((bnry - 1) < WD_TXBUF_SIZE) {
#ifdef notdef
D 2
		    wdreset(unit, 0);
E 2
I 2
		    wereset(unit, 0);
E 2
		    break;
#else
D 2
		    OUTB(sc->wd_io_nic_addr + WD_P0_BNRY,
			(sc->wd_vmem_size / WD_PAGE_SIZE) - 1);
E 2
I 2
		    outb(sc->we_io_nic_addr + WD_P0_BNRY,
			(sc->we_vmem_size / WD_PAGE_SIZE) - 1);
E 2
#endif
E 6
I 6
		/* advance on chip Boundry register */
		if((caddr_t) wer + WD_PAGE_SIZE - 1 > sc->we_vmem_end) {
			bnry = WD_TXBUF_SIZE;
			outb(sc->we_io_nic_addr + WD_P0_BNRY,
					sc->we_vmem_size / WD_PAGE_SIZE-1);
	
		} else {
			if (len > 30 && len <= ETHERMTU+100)
				bnry = wer->we_next_packet;
			else bnry = curr;

			/* watch out for NIC overflow, reset Boundry if invalid */
			if ((bnry - 1) < WD_TXBUF_SIZE) {
		    		outb(sc->we_io_nic_addr + WD_P0_BNRY,
					(sc->we_vmem_size / WD_PAGE_SIZE) - 1);
				bnry = WD_TXBUF_SIZE;
			} else
				outb(sc->we_io_nic_addr + WD_P0_BNRY, bnry-1);
E 6
		}
D 2
		OUTB(sc->wd_io_nic_addr + WD_P0_BNRY, bnry - 1);
E 2
I 2
D 6
		outb(sc->we_io_nic_addr + WD_P0_BNRY, bnry-1);
E 6
E 2

		/* refresh our copy of CURR */
D 2
		wdcmd.cs_ps = 1;
		OUTB(sc->wd_io_nic_addr + WD_P0_COMMAND, wdcmd.cs_byte);
		curr = INB(sc->wd_io_nic_addr + WD_P1_CURR);
E 2
I 2
		wecmd.cs_ps = 1;
		outb(sc->we_io_nic_addr + WD_P0_COMMAND, wecmd.cs_byte);
		curr = inb(sc->we_io_nic_addr + WD_P1_CURR);
I 6
D 7
/*printf("b %d c %d ", bnry, curr); */
E 7
E 6
D 3
printf("bd %x cur %x ", bnry-1, curr);
E 3
E 2
	}
I 2
D 3
printf("bD %x\n", bnry);
E 3
Bdry = bnry;
E 2
}

I 6
#ifdef shit
E 6
/*
D 6
 * Ethernet output routine.
 * Encapsulate a packet of type family for the local net.
E 6
I 6
 * Process an ioctl request.
E 6
 */
D 2
wdoutput(ifp, m0, dst)
E 2
I 2
D 6
weoutput(ifp, m0, dst)
E 2
	struct ifnet *ifp;
	struct mbuf *m0;
	struct sockaddr *dst;
E 6
I 6
weioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
E 6
{
D 6
	int type, s, error;
	u_char edst[6];
	struct in_addr idst;
D 2
	register struct wd_softc *sc = &wd_softc[ifp->if_unit];
E 2
I 2
	register struct we_softc *sc = &we_softc[ifp->if_unit];
E 2
	register struct mbuf *m = m0;
	register struct ether_header *eh;
	int usetrailers;
E 6
I 6
	struct we_softc *sc = &we_softc[ifp->if_unit];
	struct ifaddr *ifa = (struct ifaddr *)data;
	int s = splimp(), error = 0;
E 6
 
D 6
	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
		error = ENETDOWN;
		goto bad;
	}

	switch (dst->sa_family) {
E 6
I 6
	switch (cmd) {
E 6
 
I 6
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		weinit(ifp->if_unit);
		switch(ifa->ifa_addr->sa_family) {
E 6
#ifdef INET
D 6
	case AF_INET:
		/* Note: we ignore usetrailers */
		idst = ((struct sockaddr_in *)dst)->sin_addr;
D 2
		if (!arpresolve(&sc->wd_ac, m, &idst, edst, &usetrailers))
E 2
I 2
		if (!arpresolve(&sc->we_ac, m, &idst, edst, &usetrailers))
E 2
			return (0);	/* if not yet resolved */
		type = ETHERTYPE_IP;
		break;
E 6
I 6
		case AF_INET:
			((struct arpcom *)ifp)->ac_ipaddr =
				IA_SIN(ifa)->sin_addr;
			arpwhohas((struct arpcom *)ifp, &IA_SIN(ifa)->sin_addr);
			break;
E 6
#endif
#ifdef NS
D 6
	case AF_NS:
		type = ETHERTYPE_NS;
 		bcopy((caddr_t)&(((struct sockaddr_ns *)dst)->sns_addr.x_host),
		    (caddr_t)edst, sizeof (edst));
		break;
E 6
I 6
		case AF_NS:
		    {
			register struct ns_addr *ina = &(IA_SNS(ifa)->sns_addr);
			
			if (ns_nullhost(*ina))
				ina->x_host = *(union ns_host *)(sc->we_addr);
			else
				wesetaddr(ina->x_host.c_host, ifp->if_unit);
			break;
		    }
E 6
#endif
I 6
		}
		break;
E 6

D 6
 
	case AF_UNSPEC:
		eh = (struct ether_header *)dst->sa_data;
 		bcopy((caddr_t)eh->ether_dhost, (caddr_t)edst, sizeof (edst));
		type = eh->ether_type;
E 6
I 6
	case SIOCSIFFLAGS:
		if (((ifp->if_flags & IFF_UP) == 0) &&
		   (sc->we_flags & WDF_RUNNING)) {
			westop(ifp->if_unit);
		} else if (((ifp->if_flags & IFF_UP) == IFF_UP) &&
		   ((sc->we_flags & WDF_RUNNING) == 0))
			weinit(ifp->if_unit);
E 6
		break;
D 6
 
E 6
I 6

E 6
	default:
D 2
		printf("wd%d: can't handle af%d\n", ifp->if_unit,
E 2
I 2
D 6
		printf("we%d: can't handle af%d\n", ifp->if_unit,
E 2
			dst->sa_family);
		error = EAFNOSUPPORT;
		goto bad;
	}
E 6
I 6
		error = EINVAL;
E 6
 
D 6
	/*
	 * Add local net header.  If no space in first mbuf,
	 * allocate another.
	 */
	if (m->m_off > MMAXOFF || MMINOFF + ETHER_HDR_SIZE > m->m_off) {
		m = m_get(M_DONTWAIT, MT_HEADER);
		if (m == 0) {
			error = ENOBUFS;
			goto bad;
		}
		m->m_next = m0;
		m->m_off = MMINOFF;
		m->m_len = ETHER_HDR_SIZE;
	} else {
		m->m_off -= ETHER_HDR_SIZE;
		m->m_len += ETHER_HDR_SIZE;
E 6
	}
D 6
	eh = mtod(m, struct ether_header *);
	eh->ether_type = htons((u_short)type);
 	bcopy((caddr_t)edst, (caddr_t)eh->ether_dhost, sizeof (edst));
D 2
 	bcopy((caddr_t)sc->wd_addr, (caddr_t)eh->ether_shost,
		sizeof (sc->wd_addr));
E 2
I 2
 	bcopy((caddr_t)sc->we_addr, (caddr_t)eh->ether_shost,
		sizeof (sc->we_addr));
E 2
 
	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
	s = splimp();
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
		(void) splx(s);
		m_freem(m);
		return (ENOBUFS);
	}
	IF_ENQUEUE(&ifp->if_snd, m);
E 6
	(void) splx(s);
D 2
	wdstart(ifp->if_unit);
E 2
I 2
D 6
	westart(ifp->if_unit);
E 2
	return (0);
 
bad:
	m_freem(m0);
E 6
	return (error);
}
I 6
#endif
E 6
 
/*
 * Process an ioctl request.
 */
D 2
wdioctl(ifp, cmd, data)
E 2
I 2
weioctl(ifp, cmd, data)
E 2
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
I 6
	register struct ifaddr *ifa = (struct ifaddr *)data;
E 6
D 2
	struct wd_softc *sc = &wd_softc[ifp->if_unit];
E 2
I 2
	struct we_softc *sc = &we_softc[ifp->if_unit];
E 2
D 6
	struct ifaddr *ifa = (struct ifaddr *)data;
E 6
I 6
	struct ifreq *ifr = (struct ifreq *)data;
E 6
	int s = splimp(), error = 0;
D 6
 
E 6
I 6


E 6
	switch (cmd) {
D 6
 
E 6
I 6

E 6
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
D 2
		wdinit(ifp->if_unit);
E 2
I 2
D 6
		weinit(ifp->if_unit);
E 2
		switch(ifa->ifa_addr.sa_family) {
E 6
I 6

		switch (ifa->ifa_addr->sa_family) {
E 6
#ifdef INET
		case AF_INET:
I 6
			weinit(ifp->if_unit);	/* before arpwhohas */
E 6
			((struct arpcom *)ifp)->ac_ipaddr =
				IA_SIN(ifa)->sin_addr;
			arpwhohas((struct arpcom *)ifp, &IA_SIN(ifa)->sin_addr);
			break;
#endif
#ifdef NS
		case AF_NS:
		    {
			register struct ns_addr *ina = &(IA_SNS(ifa)->sns_addr);
D 6
			
E 6
I 6

E 6
			if (ns_nullhost(*ina))
D 2
				ina->x_host = *(union ns_host *)(sc->wd_addr);
E 2
I 2
D 6
				ina->x_host = *(union ns_host *)(sc->we_addr);
E 2
			else
D 2
				wdsetaddr(ina->x_host.c_host, ifp->if_unit);
E 2
I 2
				wesetaddr(ina->x_host.c_host, ifp->if_unit);
E 6
I 6
				ina->x_host = *(union ns_host *)(sc->ns_addr);
			else {
				/* 
				 * The manual says we can't change the address 
				 * while the receiver is armed,
				 * so reset everything
				 */
				ifp->if_flags &= ~IFF_RUNNING; 
				bcopy((caddr_t)ina->x_host.c_host,
				    (caddr_t)sc->ns_addr, sizeof(sc->ns_addr));
			}
			weinit(ifp->if_unit); /* does ne_setaddr() */
E 6
E 2
			break;
		    }
#endif
I 6
		default:
			weinit(ifp->if_unit);
			break;
E 6
		}
		break;

	case SIOCSIFFLAGS:
D 6
		if (((ifp->if_flags & IFF_UP) == 0) &&
D 2
		   (sc->wd_flags & WDF_RUNNING)) {
			wdstop(ifp->if_unit);
E 2
I 2
		   (sc->we_flags & WDF_RUNNING)) {
E 6
I 6
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    ifp->if_flags & IFF_RUNNING) {
			ifp->if_flags &= ~IFF_RUNNING;
E 6
			westop(ifp->if_unit);
E 2
D 6
		} else if (((ifp->if_flags & IFF_UP) == IFF_UP) &&
D 2
		   ((sc->wd_flags & WDF_RUNNING) == 0))
			wdinit(ifp->if_unit);
E 2
I 2
		   ((sc->we_flags & WDF_RUNNING) == 0))
E 6
I 6
		} else if (ifp->if_flags & IFF_UP &&
		    (ifp->if_flags & IFF_RUNNING) == 0)
E 6
			weinit(ifp->if_unit);
E 2
		break;

I 6
#ifdef notdef
	case SIOCGHWADDR:
		bcopy((caddr_t)sc->sc_addr, (caddr_t) &ifr->ifr_data,
			sizeof(sc->sc_addr));
		break;
#endif

E 6
	default:
		error = EINVAL;
D 6
 
E 6
	}
D 6
	(void) splx(s);
E 6
I 6
	splx(s);
E 6
	return (error);
}
D 6
 
E 6
/*
 * set ethernet address for unit
 */
D 2
wdsetaddr(physaddr, unit)
E 2
I 2
wesetaddr(physaddr, unit)
E 2
	u_char *physaddr;
	int unit;
{
D 2
	register struct wd_softc *sc = &wd_softc[unit];
E 2
I 2
	register struct we_softc *sc = &we_softc[unit];
E 2
	register int i;

	/*
	 * Rewrite ethernet address, and then force restart of NIC
	 */
	for (i = 0; i < ETHER_ADDR_LEN; i++)
D 2
		sc->wd_addr[i] = physaddr[i];
	sc->wd_flags &= ~WDF_RUNNING;
	wdinit(unit);
E 2
I 2
		sc->we_addr[i] = physaddr[i];
	sc->we_flags &= ~WDF_RUNNING;
	weinit(unit);
E 2
}
 
I 6
#define	wedataaddr(sc, eh, off, type) \
	((type) ((caddr_t)((eh)+1)+(off) >= (sc)->we_vmem_end) ? \
		(((caddr_t)((eh)+1)+(off))) - (sc)->we_vmem_end \
		+ (sc)->we_vmem_ring: \
		((caddr_t)((eh)+1)+(off)))
E 6
/*
 * Pass a packet to the higher levels.
D 6
 * NO TRAILER PROTOCOL!
E 6
I 6
 * We deal with the trailer protocol here.
E 6
 */
D 2
wdread(sc, m)
	register struct wd_softc *sc;
E 2
I 2
D 6
weread(sc, m)
E 6
I 6
weread(sc, buf, len)
E 6
	register struct we_softc *sc;
E 2
D 6
    	struct mbuf *m;
E 6
I 6
	char *buf;
	int len;
E 6
{
D 6
	struct ether_header *eh;
	int scn, type, s;
	struct ifqueue *inq;
 
E 6
I 6
	register struct ether_header *eh;
    	struct mbuf *m, *weget();
	int off, resid;

E 6
	/*
D 6
	 * Get ethernet protocol type out of ether header
E 6
I 6
	 * Deal with trailer protocol: if type is trailer type
	 * get true type from first 16-bit word past data.
	 * Remember that type was trailer by setting off.
E 6
	 */
D 6
	eh = mtod(m, struct ether_header *);
	type = ntohs((u_short)eh->ether_type);
E 6
I 6
	eh = (struct ether_header *)buf;
	eh->ether_type = ntohs((u_short)eh->ether_type);
	if (eh->ether_type >= ETHERTYPE_TRAIL &&
	    eh->ether_type < ETHERTYPE_TRAIL+ETHERTYPE_NTRAILER) {
		off = (eh->ether_type - ETHERTYPE_TRAIL) * 512;
		if (off >= ETHERMTU) return;		/* sanity */
		eh->ether_type = ntohs(*wedataaddr(sc, eh, off, u_short *));
		resid = ntohs(*(wedataaddr(sc, eh, off+2, u_short *)));
		if (off + resid > len) return;		/* sanity */
		len = off + resid;
	} else	off = 0;
E 6

I 6
	len -= sizeof(struct ether_header);
	if (len <= 0) return;

E 6
	/*
D 6
	 * Drop ethernet header
E 6
I 6
	 * Pull packet off interface.  Off is nonzero if packet
	 * has trailing header; neget will then force this header
	 * information to be at the front, but we still have to drop
	 * the type and length which are at the front of any trailer data.
E 6
	 */
D 6
	m->m_off += ETHER_HDR_SIZE;
	m->m_len -= ETHER_HDR_SIZE;
	
	/*
	 * Insert ifp pointer at start of packet
	 */
	m->m_off -= sizeof (struct ifnet *);
	m->m_len += sizeof (struct ifnet *);
D 2
	*(mtod(m, struct ifnet **)) = &sc->wd_if;
E 2
I 2
	*(mtod(m, struct ifnet **)) = &sc->we_if;
E 6
I 6
	m = weget(buf, len, off, &sc->we_if, sc);
	if (m == 0) return;
	ether_input(&sc->we_if, eh, m);
}
E 6
E 2

I 2
D 3
printf("ty %x ", type);
E 3
E 2
D 6
	switch (type) {
E 6
I 6
/*
 * Supporting routines
 */
E 6

D 6
#ifdef INET
	case ETHERTYPE_IP:
I 2
D 3
printf("ip ");
E 3
E 2
		scn = NETISR_IP;
		inq = &ipintrq;
		break;
E 6
I 6
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
weget(buf, totlen, off0, ifp, sc)
	caddr_t buf;
	int totlen, off0;
	struct ifnet *ifp;
	struct we_softc *sc;
{
	struct mbuf *top, **mp, *m, *p;
	int off = off0, len;
	register caddr_t cp = buf;
	char *epkt;
D 7
int tc =totlen;
E 7
I 7
	int tc =totlen;
E 7
E 6

D 6
	case ETHERTYPE_ARP:
D 2
		arpinput(&sc->wd_ac, m);
E 2
I 2
D 3
printf("arp ");
E 3
		arpinput(&sc->we_ac, m);
E 2
		return;
#endif
#ifdef NS
	case ETHERTYPE_NS:
		scn = NETISR_NS;
		inq = &nsintrq;
		break;
E 6
I 6
D 7
/*
printf("\nR");
{ int j;
for(j=0; j < sizeof(struct ether_header);j++) puthex(buf[j]);
printf("|");
}*/
E 7
	buf += sizeof(struct ether_header);
	cp = buf;
	epkt = cp + totlen;
E 6

I 6
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

	top = 0;
	mp = &top;
	while (totlen > 0) {
		if (top) {
			MGET(m, M_DONTWAIT, MT_DATA);
			if (m == 0) {
				m_freem(top);
				return (0);
			}
			m->m_len = MLEN;
		}
		len = min(totlen, epkt - cp);
D 7
#ifdef nope
		/* only do up to end of buffer */
		if (epkt > sc->we_vmem_end)
			len = min(len, sc->we_vmem_end - cp);
E 6
#endif
E 7
D 6
 
	default:
		m_freem(m);
		return;
E 6
I 6
		if (len >= MINCLSIZE) {
			MCLGET(m, M_DONTWAIT);
			if (m->m_flags & M_EXT)
				m->m_len = len = min(len, MCLBYTES);
			else
				len = m->m_len;
		} else {
			/*
			 * Place initial small packet/header at end of mbuf.
			 */
			if (len < m->m_len) {
				if (top == 0 && len + max_linkhdr <= m->m_len)
					m->m_data += max_linkhdr;
				m->m_len = len;
			} else
				len = m->m_len;
		}

		totlen -= len;
		/* only do up to end of buffer */
		if (cp+len > sc->we_vmem_end) {
			unsigned toend = sc->we_vmem_end - cp;

			bcopy(cp, mtod(m, caddr_t), toend);
			cp = sc->we_vmem_ring;
			bcopy(cp, mtod(m, caddr_t)+toend, len - toend);
			cp += len - toend;
			epkt = cp + totlen;
		} else {
			bcopy(cp, mtod(m, caddr_t), (unsigned)len);
			cp += len;
		}
D 7
/*{ int j;
for(j=0; j < m->m_len;j++) puthex(mtod(m, char *)[j]);
printf("|");
}*/
E 7
		*mp = m;
		mp = &m->m_next;
		if (cp == epkt) {
			cp = buf;
			epkt = cp + tc;
		}
E 6
	}
D 6
 
	s = splimp();
	if (IF_QFULL(inq)) {
		IF_DROP(inq);
		m_freem(m);
	} else
		IF_ENQUEUE(inq, m);
	schednetisr(scn);
	(void) splx(s);
E 6
I 6
D 7
/*printf("%d ",tc); */
E 7
	return (top);
E 6
D 7
}

I 6
puthex(c){
	printf("%x",(c>>4)&0xf);
	printf("%x",c&0xf);
E 7
}
E 6
#endif
E 1
