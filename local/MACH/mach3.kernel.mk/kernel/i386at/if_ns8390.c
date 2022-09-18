/*
 * Mach Operating System
 * Copyright (c) 1994,1993,1992,1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	if_ns8390.c,v $
 * Revision 2.24  94/12/15  15:42:11  dbg
 * 	ANSI-fied.
 * 	[93/12/28            dbg]
 * 
 * Revision 2.23  93/11/17  16:47:47  dbg
 * 	Changed HZ to hz.  Removed non-MACH_KERNEL code.
 * 	[93/05/24            dbg]
 * 
 * Revision 2.22  93/05/10  23:24:07  rvb
 * 	Added TTD teledebug code to use the ns8390 as a remote ethernet
 * 	debugging device.
 * 	[93/03/01            grm]
 * 
 * Revision 2.21  93/05/10  21:19:20  rvb
 * 	Lint.
 * 	[93/05/08  11:20:50  af]
 * 
 * Revision 2.20  93/01/24  13:17:18  danner
 * 	Sigh! Sometimes the reported length of the packet is zero.  But
 * 	the rest of the chain looked OK.  So we'll just skip the packet.
 * 	[92/10/27            rvb]
 * 
 * Revision 2.19  93/01/14  17:30:37  danner
 * 	Proper spl typing.
 * 	[92/11/30            af]
 * 
 * Revision 2.18  92/08/03  17:17:43  jfriedl
 * 	Fixed bug in wd80xxget_board_id, that made the machine hang on
 * 	reboot when using wd8013EP boards.
 * 	[92/07/13            kivinen]
 * 
 * Revision 2.17  92/07/09  22:54:18  rvb
 * 	Say whether EtherLink II is thick or thin.
 * 	[92/06/18            rvb]
 * 
 * Revision 2.16  92/04/03  12:15:19  rpd
 * 	Use port 0x250, 0x350 for irq 5 bnc, thick respectively.
 * 	[92/04/02            rvb]
 * 
 * Revision 2.15  92/02/19  15:08:22  elf
 * 	Made wd driver work with 16 bit cards. Better recognize different
 * 	cards. Print card name when probing. Tested on wd8003, wd8013EP,
 * 	wd8003EP.
 * 	Add IFWD_ prefix to defines.
 * 	[92/01/20            kivinen]
 * 
 * Revision 2.14  91/11/12  11:09:39  rvb
 * 	Undo "strict" wrong change to probe()
 * 	[91/10/25            rvb]
 * 
 * Revision 2.13  91/10/09  16:07:43  af
 * 	Fixes from 2.5 (from rvb), made sure two WD boards work (with
 * 	help from jeffreyh).
 * 
 * Revision 2.12  91/08/24  11:58:01  af
 * 	New MI autoconf.
 * 	[91/08/02  02:55:17  af]
 * 
 * Revision 2.11  91/05/14  16:24:56  mrt
 * 	Correcting copyright
 * 
 * Revision 2.10  91/05/13  06:02:41  af
 * 	Made code under CMUCS standard.
 * 	[91/05/12  15:50:35  af]
 * 
 * Revision 2.9  91/03/16  14:46:23  rpd
 * 	Changed net_filter to net_packet.
 * 	[91/01/15            rpd]
 * 
 * Revision 2.8  91/02/14  14:42:44  mrt
 * 	Distinguish EtherLinkII vs WD8003 on open.  Get packet
 * 	size right for statistics.  Fix 3.0 buf that sometimes
 * 	reported packets too large.
 * 	[91/01/28  15:31:22  rvb]
 * 
 * Revision 2.7  91/02/05  17:17:52  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  17:44:04  mrt]
 * 
 * Revision 2.6  91/01/09  16:07:19  rpd
 * 	Fixed typo in ns8390probe.
 * 	[91/01/09            rpd]
 * 
 * Revision 2.5  91/01/08  17:35:46  rpd
 * 	Changed NET_KMSG_GET to net_kmsg_get.
 * 	[91/01/08            rpd]
 * 
 * Revision 2.4  91/01/08  17:33:05  rpd
 * 	A few bug fixes.
 * 	[91/01/08  16:41:04  rvb]
 * 
 * 	Make this a generic driver for ns8390 from wd8003 because
 * 	we now will also support etherlink ii.
 * 	[91/01/04  12:25:21  rvb]
 * 
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
<INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#define IF_CNTRS	MACH
#include	<ns8390.h>

#include	<mach_ttd.h>
#include	<kern/kern_io.h>
#include	<kern/memory.h>
#include	<kern/time_out.h>
#include	<device/device_types.h>
#include	<device/errno.h>
#include	<device/io_req.h>
#include	<device/if_hdr.h>
#include	<device/if_ether.h>
#include	<device/net_status.h>
#include	<device/net_io.h>

#include	<i386/ipl.h>
#include	<i386/pio.h>
#include	<chips/busses.h>
#include	<i386at/if_ns8390.h>
#include	<i386at/if_wd8003.h>
#include	<i386at/if_3c503.h>

#if	MACH_TTD
#include <ttd/ttd_stub.h>
#endif	/* MACH_TTD */


#define	SPLNET	spl6

int wd_debug = 0;
  
boolean_t ns8390probe(
	vm_offset_t	port,
	struct bus_device	*dev);
void	ns8390attach(
	struct bus_device	*dev);
int	ns8390intr(int unit);
int	ns8390init(int unit);
boolean_t ns8390hwrst(int unit);
int	ns8390reset(int unit);
int	ns8390rcv(int unit);
void ns8390lost_frame(int unit);
void	ns8390watch(void *b_ptr);
int	ns8390get_CURR(int unit);
void ns8390xmt(
	int	unit,
	io_req_t	m);
void	ns8390over_write(int unit);
boolean_t config_nic(
	int unit);
boolean_t config_wd8003(
	int	unit);
boolean_t config_3c503(
	int	unit);
int wd80xxget_board_id(
	struct bus_device	*dev);
int wd80xxget_eeprom_info(
	unsigned short hdwbase,
	long	board_id);
void en_16bit_access(
	unsigned short hdwbase,
	long	board_id);
void dis_16bit_access(
	unsigned short hdwbase,
	long	board_id);

struct	bus_device	*ns8390info[NNS8390];	/* ???? */

static vm_offset_t ns8390_std[NNS8390] = { 0 };
static struct bus_device *ns8390_info[NNS8390];
struct	bus_driver	ns8390driver =
	{ns8390probe, 0, ns8390attach, 0, ns8390_std, "ns8390", ns8390_info, 0, 0, 0};

int	watchdog_id;

char *wd8003_card = "wd";
char *elii_card = "el";
/*		  2e0, 2a0, 280,  250,   350,   330,   310, 300*/
int elii_irq[8] = {5,   2,   2,     5,     5, 0x711, 0x711,  5};
int elii_bnc[8] = {1,   0,   1,     1,     0, 0x711, 0x711,  0};
/*int elii_bnc[8] = {0, 1,   1,     1,     1,     1,     0,  1}; */

typedef struct {
	struct	ifnet	ds_if;		/* generic interface header */
	u_char	ds_addr[6];		/* Ethernet hardware address */
	int	flags;
	int     timer;
	int     interrupt;
	vm_offset_t nic;		/* address of IO ports */
	u_char   address[ETHER_ADDR_SIZE];
	short	mode;
	int     tbusy;
	char    *sram;		/* beginning of the shared memory RAM buffer */
	int     read_nxtpkt_ptr;/* pointer to next packet available */
	int     pstart;		/* page start hold */
	int     pstop;		/* page stop hold */
	int     tpsr;		/* transmit page start hold */
	int     fifo_depth;	/* NIC fifo threshold */
	char	*card;
	int     board_id;
}
ns8390_softc_t;

ns8390_softc_t	ns8390_softc[NNS8390];

struct ns8390_cntrs {
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
} ns8390_cntrs[NNS8390];

#if	MACH_TTD	
boolean_t ttd_poll_loop;

void ns8390poll_receive(int unit);
void ns8390transmit_ttd(
	int unit,
	char * packet,
	int len);
#endif	/* MACH_TTD */

#ifdef	IF_CNTRS
int ns_narp = 1, ns_arp = 0;
int ns_ein[32], ns_eout[32]; 
int ns_lin[128/8], ns_lout[128/8]; 

static int log_2(
	unsigned long no)
{
	return ({ unsigned long _temp__;
		asm("bsr %1, %0; jne 0f; xorl %0, %0; 0:" :
		    "=r" (_temp__) : "a" (no));
		_temp__;});
}
#endif	/* IF_CNTRS */

int  imr_hold = PRXE|PTXE|RXEE|TXEE|OVWE|CNTE;  /* Interrupts mask bits */

/*
 * ns8390probe:
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

boolean_t ns8390probe(
	vm_offset_t	port,
	struct bus_device	*dev)
{
	vm_offset_t	hdwbase = dev->address;
	int		unit = dev->unit;
	ns8390_softc_t	*sp = &ns8390_softc[unit];
	int		tmp;

	if (unit < 0 || unit > NNS8390) {
		printf("ns8390 ethernet unit %d out of range\n", unit);
		return FALSE;
	}
	if (((u_char) inb(hdwbase+IFWD_LAR_0) == (u_char) WD_NODE_ADDR_0) &&
	    ((u_char) inb(hdwbase+IFWD_LAR_1) == (u_char) WD_NODE_ADDR_1) &&
	    ((u_char) inb(hdwbase+IFWD_LAR_2) == (u_char) WD_NODE_ADDR_2)) {
			ns8390info[unit] = dev;
			sp->card = wd8003_card;
			dev->name = wd8003_card;
			sp->nic = hdwbase + OFF_8390;
				/* enable mem access to board */
			sp->board_id = wd80xxget_board_id(dev);

			*(sp->address)      = inb(hdwbase+IFWD_LAR_0);
			*(sp->address + 1)  = inb(hdwbase+IFWD_LAR_1);
			*(sp->address + 2)  = inb(hdwbase+IFWD_LAR_2);
			*(sp->address + 3)  = inb(hdwbase+IFWD_LAR_3);
			*(sp->address + 4)  = inb(hdwbase+IFWD_LAR_4);
			*(sp->address + 5)  = inb(hdwbase+IFWD_LAR_5);
			return TRUE;
		}  /* checks the address of the board to verify that it is a WD */
	if ((tmp = inb(hdwbase+BCFR)) != 0) {
		switch(tmp) {
		case (1<<7):	sp->board_id = 7; break;	/*irq5 xvcr*/
#ifdef	not_currently_possible
		case (1<<6):	sp->board_id = 6; break;
		case (1<<5):	sp->board_id = 5; break;
#endif	/* not_currently_possible */
		case (1<<4):	sp->board_id = 4; break;
		case (1<<3):	sp->board_id = 3; break;
		case (1<<2):	sp->board_id = 2; break;	/*irq2 bnc*/
		case (1<<1):	sp->board_id = 1; break;	/*irq2 xvcr*/
		case (1<<0):	sp->board_id = 0; break;	/*irq5 bnc*/
		default:	return FALSE;
		}
		switch (inb(hdwbase+PCFR)) {
		case (1<<7):	dev->phys_address = 0xDC000; break;
		case (1<<6):	dev->phys_address = 0xD8000; break;
#ifdef	not_currently_possible
		case (1<<5):	dev->phys_address = 0xCC000; break;
		case (1<<4):	dev->phys_address = 0xC8000; break;
#endif	/* not_currently_possible */
		default:
			printf("EtherLink II with NO memory configured\n");
			return FALSE;
		}
		ns8390info[unit] = dev;
		dev->irq = elii_irq[sp->board_id];
		if (dev->irq == 2)
			dev->irq = 9;
		sp->card = elii_card;
		dev->name = elii_card;
		sp->nic = hdwbase;
		return TRUE;
	}
	return FALSE;
}

/*
 * ns8390attach:
 *
 *	This function attaches a ns8390 board to the "system".  The rest of
 *	runtime structures are initialized here (this routine is called after
 *	a successful probe of the board).  Once the ethernet address is read
 *	and stored, the board's ifnet structure is attached and readied.
 *
 * input	: bus_device structure setup in autoconfig
 * output	: board structs and ifnet is setup
 *
 */

void ns8390attach(
	struct bus_device	*dev)
{
	ns8390_softc_t	*sp;
	struct	ifnet	*ifp;
	u_char		unit;

	take_dev_irq(dev);
	unit = (u_char)dev->unit;
	sp = &ns8390_softc[unit];
	printf(", port = %x, spl = %d, pic = %d. ",
		dev->address, dev->priority, dev->irq);

	if (sp->card == elii_card) {
		if (elii_bnc[sp->board_id])
			printf("cheapernet ");
		else
			printf("ethernet ");
	} else
		printf("ethernet ");

	(volatile char *)sp->sram =
	    (volatile char *) phystokv(dev->phys_address);
	dev->address = (vm_offset_t) phystokv(dev->address);
	sp->timer = -1;
	sp->flags = 0;
	sp->mode  = 0;

	if (!ns8390hwrst(unit)) {
		printf("%s%d: attach(): reset failed.\n",
			sp->card, unit);
		return;
	}
		/* N.B. sp->address is not determined till
		 * hwrst time. */
	*(sp->ds_addr)      = *(sp->address);
	*(sp->ds_addr + 1)  = *(sp->address + 1);
	*(sp->ds_addr + 2)  = *(sp->address + 2);
	*(sp->ds_addr + 3)  = *(sp->address + 3);
	*(sp->ds_addr + 4)  = *(sp->address + 4);
	*(sp->ds_addr + 5)  = *(sp->address + 5);

	printf("id [%x:%x:%x:%x:%x:%x]",
		sp->address[0],sp->address[1],sp->address[2],
		sp->address[3],sp->address[4],sp->address[5]);
	ifp = &sp->ds_if;
	ifp->if_unit = unit;
	ifp->if_mtu = ETHERMTU;
	ifp->if_flags = IFF_BROADCAST;
	ifp->if_header_size = sizeof(struct ether_header);
	ifp->if_header_format = HDR_ETHERNET;
	ifp->if_address_size = 6;
	ifp->if_address = (char *)&sp->address[0];
	if_init_queues(ifp);

#if	MACH_TTD
	if (!ttd_get_packet) {
		ttd_device_unit = unit;
		ttd_get_packet = ns8390poll_receive;
		ttd_send_packet = ns8390transmit_ttd;
		ttd_host_ether_id.array[0] = *(sp->address);
		ttd_host_ether_id.array[1] = *(sp->address + 1);
		ttd_host_ether_id.array[2] = *(sp->address + 2);
		ttd_host_ether_id.array[3] = *(sp->address + 3);
		ttd_host_ether_id.array[4] = *(sp->address + 4);
		ttd_host_ether_id.array[5] = *(sp->address + 5);
	}
#endif	/* MACH_TTD */
}

/*
 * ns8390watch():
 *
 */

void
ns8390watch(void *b_ptr)
{
	int	unit;
	int     temp_cr;
	vm_offset_t nic;

	unit = *(char *)b_ptr;
	timeout(ns8390watch,b_ptr,20*hz);
	nic = ns8390_softc[unit].nic;
	temp_cr = inb(nic+CR);
	outb(nic + CR, (temp_cr & 0x3f) | PS0);
	printf("<<< ISR=%x CURR=%x rdnxt=%x BNDY=%x>>> ",
		inb(nic + ISR),
		ns8390get_CURR(unit), ns8390_softc[unit].read_nxtpkt_ptr,
		inb(nic+BNDY));
	outb(nic+CR,temp_cr);
}

void ns8390start(
	int	unit);	/* forward */

/*ARGSUSED*/
io_return_t wd8003open(
	int	unit,
	int	flag)
{
	if (ns8390_softc[unit].card != wd8003_card)
	    return ENXIO;
	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return ENXIO;

	ns8390_softc[unit].ds_if.if_flags |= IFF_UP;
	(void) ns8390init(unit);
	return D_SUCCESS;
}

io_return_t eliiopen(
	int	unit,
	int	flag)
{
	if (ns8390_softc[unit].card != elii_card)
	    return ENXIO;
	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return ENXIO;

	ns8390_softc[unit].ds_if.if_flags |= IFF_UP;
	(void) ns8390init(unit);
	return D_SUCCESS;
}

io_return_t ns8390output(
	int		unit,
	io_req_t	ior)
{
	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return ENXIO;
	return net_write(&ns8390_softc[unit].ds_if, ns8390start, ior);
}

io_return_t ns8390setinput(
	int		unit,
	ipc_port_t	receive_port,
	int		priority,
	filter_t	filter[],
	natural_t	filter_count)
{
	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return ENXIO;

	return net_set_filter(&ns8390_softc[unit].ds_if,
			receive_port, priority,
			filter, filter_count);
}


/*
 * ns8390reset:
 *
 *	This routine is in part an entry point for the "if" code.  Since most
 *	of the actual initialization has already (we hope already) been done
 *	by calling ns8390attach().
 *
 * input	: unit number or board number to reset
 * output	: board is reset
 *
 */

int
ns8390reset(
	int	unit)
{
	ns8390_softc[unit].ds_if.if_flags &= ~IFF_RUNNING;
	return ns8390init(unit);
}

/*
 * ns8390init:
 *
 *	Another routine that interfaces the "if" layer to this driver.
 *	Simply resets the structures that are used by "upper layers".
 *	As well as calling ns8390hwrst that does reset the ns8390 board.
 *
 * input	: board number
 * output	: structures (if structs) and board are reset
 *
 */

int
ns8390init(
	int	unit)
{
	struct	ifnet	*ifp;
	int		stat;
	spl_t		oldpri;

	ifp = &ns8390_softc[unit].ds_if;
	oldpri = SPLNET();
	if ((stat = ns8390hwrst(unit)) == TRUE) {
		ns8390_softc[unit].ds_if.if_flags |= IFF_RUNNING;
		ns8390_softc[unit].flags |= DSF_RUNNING;
		ns8390_softc[unit].tbusy = 0;
		ns8390start(unit);
	} else
		printf("%s%d init(): trouble resetting board\n",
			ns8390_softc[unit].card, unit);
	ns8390_softc[unit].timer = 5;
	splx(oldpri);
	return stat;
}

/*
 * ns8390start:
 *
 *	This is yet another interface routine that simply tries to output a
 *	in an mbuf after a reset.
 *
 * input	: board number
 * output	: stuff sent to board if any there
 *
 */

void ns8390start(
	int	unit)
{
	register ns8390_softc_t *is = &ns8390_softc[unit];
	struct	ifnet		*ifp;
	io_req_t	m;

	if (is->tbusy) {
		vm_offset_t nic = ns8390_softc[unit].nic;
		if (!(inb(nic+CR) & TXP)) {
			is->tbusy = 0;
			ns8390_cntrs[unit].busy++;
		} else
			return;
	}

	ifp = &ns8390_softc[unit].ds_if;

	IF_DEQUEUE(&ifp->if_snd, m);
	if (m != 0) {
		is->tbusy++;
		ns8390_cntrs[unit].xmt++;
		ns8390xmt(unit, m);
	}
}

/*ARGSUSED*/
io_return_t ns8390getstat(
	int		unit,
	dev_flavor_t	flavor,
	dev_status_t	status,		/* pointer to OUT array */
	natural_t	*count)		/* out */
{
	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return ENXIO;

	return net_getstat(&ns8390_softc[unit].ds_if,
			   flavor,
			   status,
			   count);
}

io_return_t ns8390setstat(
	int		unit,
	dev_flavor_t	flavor,
	dev_status_t	status,
	natural_t	count)
{
	register ns8390_softc_t *sp;

	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return ENXIO;

	sp = &ns8390_softc[unit];

	switch (flavor) {
	    case NET_STATUS:
	    {
		/*
		 * All we can change are flags, and not many of those.
		 */
		register struct net_status *ns = (struct net_status *)status;
		int	mode = 0;

		if (count < NET_STATUS_COUNT)
		    return D_INVALID_SIZE;

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
			(void) ns8390init(unit);
		    }
		}
		break;
	    }

	    default:
		return D_INVALID_OPERATION;
	}
	return D_SUCCESS;
}

/*
 * ns8390hwrst:
 *
 *	This routine resets the ns8390 board that corresponds to the
 *	board number passed in.
 *
 * input	: board number to do a hardware reset
 * output	: board is reset
 *
 */

boolean_t ns8390hwrst(
	int unit)
{
	spl_t	spl = SPLNET();

	if (ns8390_softc[unit].card == wd8003_card && 
	    config_wd8003(unit) == FALSE) {
		printf("%s%d hwrst(): config_wd8003 failed.\n",
			ns8390_softc[unit].card, unit);
		splx(spl);
		return FALSE;
	}
	if (ns8390_softc[unit].card == elii_card && 
	    config_3c503(unit) == FALSE) {
		printf("%s%d hwrst(): config_3c503 failed.\n",
			ns8390_softc[unit].card, unit);
		splx(spl);
		return FALSE;
	}
	if (config_nic(unit) == FALSE) {
		printf("%s%d hwrst(): config_nic failed.\n",
			ns8390_softc[unit].card, unit);
		splx(spl);
		return FALSE;
	}
	splx(spl);
	return TRUE;
}

/*
 * ns8390intr:
 *
 *	This function is the interrupt handler for the ns8390 ethernet
 *	board.  This routine will be called whenever either a packet
 *	is received, or a packet has successfully been transfered and
 *	the unit is ready to transmit another packet.
 *
 * input	: board number that interrupted
 * output	: either a packet is received, or a packet is transfered
 *
 */
int
ns8390intr(int unit)
{
	int     isr_status;
	int     temp_cr;
	vm_offset_t nic = ns8390_softc[unit].nic;

	temp_cr = inb(nic+CR);
	outb(nic+CR, (temp_cr & 0x3f) | PS0);
	outb(nic+IMR, 0);                   /* stop board interrupts */
	outb(nic+CR, temp_cr);
	while ((isr_status = inb(nic+ISR)) != 0) {
		outb(nic+ISR, isr_status);          /* clear interrupt status */

		if ((isr_status & (OVW|RXE)) == RXE) {
			int rsr = inb(nic+RSR);
			if (rsr & DFR) ns8390_cntrs[unit].jabber++;
			if (rsr & ~(DFR|PHY|FAE|CRC|PRX))
				printf("%s%d intr(): isr = %x, RSR = %x\n",
					ns8390_softc[unit].card, unit,
					isr_status, rsr);
		} else if (isr_status & OVW) {
			ns8390_cntrs[unit].ovw++;
			ns8390over_write(unit);
		}
		if (isr_status & PRX) {		/* DFR & PRX is possible */
		 	(void) ns8390rcv(unit);

#if	MACH_TTD
			if (kttd_active)
				ttd_poll_loop = FALSE;
#endif	/* MACH_TTD */
		}

	        if (isr_status & TXE) {
			int tsr = inb(nic+TSR);
			tsr &= ~0x2;		/* unadvertised special */
#if	MACH_TTD
			if (!kttd_active)
#endif	/* MACH_TTD */
			{
				if (tsr == (CDH|ABT))
					ns8390_cntrs[unit].heart++;
				else
					printf("%s%d intr(): isr = %x, TSR = %x\n",
					       ns8390_softc[unit].card, unit,
					       isr_status, tsr);
				ns8390_softc[unit].tbusy = 0;
				ns8390start(unit);
			}
	        } else if (isr_status & PTX) {
#if	MACH_TTD
			if (!kttd_active)
#endif	/* MACH_TTD */
			{
				ns8390_cntrs[unit].xmti++;
				ns8390_softc[unit].tbusy = 0;
				ns8390start(unit);
			}
		}

		if (isr_status & CNT) {
			int c0 = inb(nic+CNTR0);
			int c1 = inb(nic+CNTR1);
			int c2 = inb(nic+CNTR2);
			ns8390_cntrs[unit].frame += c0;
			ns8390_cntrs[unit].crc += c1;
			ns8390_cntrs[unit].miss += c2;
#ifdef	COUNTERS
			printf("%s%d intr(): isr = %x, FRAME %x, CRC %x, MISS %x\n",
				ns8390_softc[unit].card, unit,
				isr_status, c0, c1, c2);
			printf("%s%d intr(): TOTAL   , FRAME %x, CRC %x, MISS %x\n",
				ns8390_softc[unit].card, unit,
				ns8390_cntrs[unit].frame,
				ns8390_cntrs[unit].crc,
				ns8390_cntrs[unit].miss);
#endif	/* COUNTERS */
			outb(nic+ISR, isr_status);	/* clear interrupt status again */
		}
	}
	temp_cr=inb(nic+CR);
	outb(nic+CR, (temp_cr & 0x3f) | PS0);
	outb(nic+IMR, imr_hold);
	outb(nic+CR, temp_cr);
	return(0);
}

/*
 *  Called if on board buffer has been completely filled by ns8390intr.  It
 *  stops the board, reads in all the buffers that are currently in the buffer,
 *  and then restarts board.
 */
void ns8390over_write(
	int unit)
{
	vm_offset_t nic = ns8390_softc[unit].nic;
	int	no;
	int	count = 0;

	outb(nic+CR, ABR|STP|PS0);        /* clear the receive buffer */
	outb(nic+RBCR0, 0);
	outb(nic+RBCR1, 0);  
	while ((!(inb (nic + ISR) & RST)) && (count < 10000))
		count++;
	if (count == 10000) {
		printf("%s%d: over_write(): would not reset.\n",
			ns8390_softc[unit].card, unit);
	}
	no = ns8390rcv(unit);
#ifdef	OVWBUG
	printf("%s%d over_write(): ns8390 OVW ... %d.\n",
		ns8390_softc[unit].card, unit, no);
#endif	/* OVWBUG */
	outb(nic+TCR, LB1);               /* External loopback mode */
	outb(nic+CR, ABR|STA|PS0);
	outb(nic+TCR, 0);
	return;
}

/*
 * ns8390rcv:
 *
 *	This routine is called by the interrupt handler to initiate a
 *	packet transfer from the board to the "if" layer above this
 *	driver.  This routine checks if a buffer has been successfully
 *	received by the ns8390.  If so, it does the actual transfer of the
 *      board data (including the ethernet header) into a packet (consisting
 *      of an mbuf chain) and enqueues it to a higher level.
 *      Then check again whether there are any packets in the receive ring,
 *      if so, read the next packet, until there are no more.
 *
 * input	: number of the board to check
 * output	: if a packet is available, it is "sent up"
 */
int ns8390rcv(
	int unit)
{
	register ns8390_softc_t	*is = &ns8390_softc[unit];
	register struct ifnet	*ifp = &is->ds_if;
	vm_offset_t		nic = is->nic;
	int			packets = 0;
	struct ether_header	eh;
	u_short			len;
	int			temp_cr;
	int                     board_id = is->board_id;
	vm_offset_t             hdwbase = ns8390info[unit]->address;
	spl_t			s;

	/* calculation of pkt size */
	int nic_overcount;         /* NIC says 1 or 2 more than we need */
	int pkt_size;              /* calculated size of received data */
	int wrap_size;             /* size of data before wrapping it */
	int header_nxtpkt_ptr;     /* NIC's next pkt ptr in rcv header */
	int low_byte_count;        /* low byte count of read from rcv header */
	int high_byte_count;       /* calculated high byte count */


	volatile char *sram_nxtpkt_ptr;   /* mem location of next packet */
	volatile char *sram_getdata_ptr;  /* next location to be read */
	ipc_kmsg_t	new_kmsg;
	struct ether_header *ehp;
	struct packet_header *pkt;


#if	MACH_TTD
	if (((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) &&
	    !kttd_active) {
#else
	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
#endif	/* MACH_TTD */
		temp_cr = inb(nic+CR); /* get current CR value */
		outb(nic+CR,((temp_cr & 0x3F)|PS0|STP));
		outb(nic+IMR, 0);      /* Interrupt Mask Register  */
		outb(nic+CR, temp_cr);
		return -1;
	}

	while(is->read_nxtpkt_ptr != ns8390get_CURR(unit))   {

		/* while there is a packet to read from the buffer */

		if ((is->read_nxtpkt_ptr < is->pstart) ||
		    (is->read_nxtpkt_ptr >= is->pstop)) {
			ns8390hwrst(unit);
			return -1;
		}    /* if next packet pointer is out of receive ring bounds */

#if	MACH_TTD
		if (!kttd_active)
#endif	/* MACH_TTD */
		{
			packets++;
			ns8390_cntrs[unit].rcv++;
		}

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
			wrap_size = (int) (is->pstop - is->read_nxtpkt_ptr - nic_overcount);
			high_byte_count = is->pstop - is->read_nxtpkt_ptr +
			    header_nxtpkt_ptr - is->pstart - nic_overcount;
		}
		pkt_size = (high_byte_count << 8) | (low_byte_count & 0xFF);
		/* does not seem to include NIC_HEADER_SIZE */
		if (!pkt_size) {
			printf("%s%d rcv(): zero length.\n",
				ns8390_softc[unit].card, unit);
			goto next_pkt;
		}
		len = pkt_size;

		sram_getdata_ptr = sram_nxtpkt_ptr + NIC_HEADER_SIZE;
		if (board_id & IFWD_SLOT_16BIT) {
#if	MACH_TTD
			if (!kttd_active)
#endif	/* MACH_TTD */
			{ s = splhi(); }

			en_16bit_access(hdwbase, board_id);
			bcopy16 (sram_getdata_ptr,
				 &eh,
				 sizeof(struct ether_header));
			dis_16bit_access (hdwbase, board_id);
#if	MACH_TTD
			if (!kttd_active)
#endif	/* MACH_TTD */
			{ splx(s); }

		} else {
			bcopy16 (sram_getdata_ptr,
				 &eh,
				 sizeof(struct ether_header));
		}		    
		sram_getdata_ptr += sizeof(struct ether_header);
		len -= (sizeof(struct ether_header) + 4);	/* crc size */
#if	MACH_TTD
		if (kttd_active) {
			new_kmsg = (ipc_kmsg_t)ttd_request_msg;
		}else
#endif	/* MACH_TTD */
		{
			new_kmsg = net_kmsg_get();
			if (new_kmsg == IKM_NULL) {
				/*
				 * Drop the packet.
				 */
				is->ds_if.if_rcvdrops++;    
				/*
				 * not only do we want to return, we need to drop
				 * the packet on the floor to clear the interrupt.
				 */
				ns8390lost_frame(unit);
				return packets;
			}
		}

#if	DEBUG_TTD
		dump_ether_header("ns8390wire",&eh);
#endif	/* DEBUG_TTD */

		ehp = (struct ether_header *) (&net_kmsg(new_kmsg)->header[0]);
		pkt = (struct packet_header *) (&net_kmsg(new_kmsg)->packet[0]);

#if	DEBUG_TTD
		printf("!ehp = 0x%x, pkt = 0x%x!",ehp, pkt);
#endif	/* DEBUG_TTD */

		*ehp = eh;
		if (len >
		    (wrap_size = (is->sram + (is->pstop << 8) - sram_getdata_ptr))) {
			/* if needs to wrap */
			if (board_id & IFWD_SLOT_16BIT) {
#if	MACH_TTD
				if (!kttd_active)
#endif	/* MACH_TTD */
				{ s = splhi(); }

				en_16bit_access(hdwbase, board_id);
				bcopy16 (sram_getdata_ptr, (char *) (pkt + 1),
					 wrap_size);
				dis_16bit_access (hdwbase, board_id);
#if	MACH_TTD
				if (!kttd_active)
#endif	/* MACH_TTD */
				{ splx(s); }
			} else {
				bcopy ((char *)sram_getdata_ptr,
				       (char *) (pkt + 1),
				       wrap_size);
			}
			sram_getdata_ptr = (volatile char *)
			    (is->sram + (is->pstart << 8));
		} else {   /* normal getting data from buffer */
			wrap_size = 0;
		}
		if (board_id & IFWD_SLOT_16BIT) {
#if	MACH_TTD
			if (!kttd_active)
#endif	/* MACH_TTD */
			{ s = splhi(); }
			en_16bit_access(hdwbase, board_id);
			bcopy16 (sram_getdata_ptr,
				 (char *) (pkt + 1) + wrap_size,
				 len - wrap_size);
			dis_16bit_access (hdwbase, board_id);
#if	MACH_TTD
			if (!kttd_active)
#endif	/* MACH_TTD */
			{ splx(s); }
		} else {
			bcopy ((char *)sram_getdata_ptr,
			       (char *) (pkt + 1) + wrap_size,
			       len - wrap_size);
		}

		pkt->type = ehp->ether_type;
		pkt->length = len + sizeof(struct packet_header);

#if	MACH_TTD
		/*
		 * Don't want to call net_packet if we are polling
		 * for a packet.
		 */
		if (!kttd_active)
#endif	/* MACH_TTD */
		{
			/*
			 * Hand the packet to the network module.
			 */
			net_packet(ifp, new_kmsg, pkt->length,
				   ethernet_priority(new_kmsg));
		}


next_pkt:
		is->read_nxtpkt_ptr = *(sram_nxtpkt_ptr + 1);
		is->read_nxtpkt_ptr &= 0xFF;

#if	MACH_TTD
		if (!kttd_active)
#endif	/* MACH_TTD */
		{
			temp_cr = inb(nic+CR);
			outb(nic+CR, (temp_cr & 0x3f) | PS0);
		}

		if (is->read_nxtpkt_ptr == ns8390get_CURR(unit))
			if (is->read_nxtpkt_ptr == is->pstart)
				outb(nic+BNDY, is->pstop - 1);
			else
				outb(nic+BNDY, is->read_nxtpkt_ptr - 1);
		else
			outb(nic+BNDY, is->read_nxtpkt_ptr);

#if	MACH_TTD
		if (!kttd_active)
#endif	/* MACH_TTD */
		{ outb(nic+CR, temp_cr); }

#if	MACH_TTD
		/*
		 * Hand the packet back to the TTD server, if active.
		 */
		if (kttd_active && pkt_size)
			return 1;
#endif	/* MACH_TTD */


	}
	return packets;

}

#if	MACH_TTD
/*
 * Polling routines for the TTD debugger.
 */
void ns8390poll_receive(
	int	unit)
{
	int s;
	int orig_cr;
	int orig_imr;
	int isr_status;
	int pkts;
	
	ttd_poll_loop = TRUE;

	
	/*
	 * Should already in at splhigh.  Is this necessary? XXX
	 */
	s = splhigh();

#if	0
	if (kttd_debug)
		printf("ns8390poll_receive: beginning polling loop\n");
#endif	/* DEBUG_TTD */

	/*
	 * Loop until packet arrives.
	 */
	while(ttd_poll_loop) {

		/*
		 * Call intr routine
		 */

		ns8390intr(unit);
	}

#if	0
	if (kttd_debug)
		printf("ns8390poll_receive: got packet exiting loop\n");
#endif	/* DEBUG_TTD */

	splx(s);
}

void ns8390transmit_ttd(
	int unit,
	char * packet,
	int len)
{
	ns8390_softc_t	*is = &ns8390_softc[unit];
	vm_offset_t	nic = is->nic;
	u_short		count = 0;	/* amount of data already copied */
	volatile char	*sram_write_pkt;
	int     	board_id = is->board_id;
	vm_offset_t	hdwbase = ns8390info[unit]->address;
	int		s;
	int 		orig_cr;
	int 		orig_imr;
	int 		isr_status;
	boolean_t	loop = TRUE;

#if	0
	dump_ipudpbootp("Beg of xmit",packet);
#endif

	s = splhigh();

	/* begining of physical address of transmition buffer */

	sram_write_pkt = is->sram + is->tpsr * 0x100; 

	count = len;
	if (board_id & IFWD_SLOT_16BIT) {
		en_16bit_access(hdwbase, board_id);
		bcopy16 (packet, sram_write_pkt,  count);
		dis_16bit_access (hdwbase, board_id);
	} else {
		bcopy (packet, sram_write_pkt,  count);
	}

	while (count < ETHERMIN+sizeof(struct ether_header)) {
		*(sram_write_pkt + count) = 0;
		count++;
	}
	outb(nic+CR, ABR|STA|PS0);		/* select page 0 */
	outb(nic+TPSR, is->tpsr);		/* xmt page start at 0 of RAM */
	outb(nic+TBCR1, count >> 8);		/* upper byte of count */
	outb(nic+TBCR0, count & 0xFF);		/* lower byte of count */
	outb(nic+CR, TXP|ABR|STA);		/* start transmission */

	ns8390intr(unit);

	splx(s);
}
#endif	/* MACH_TTD */


/*
 *  ns8390lost_frame:
 *  this routine called by ns8390read after memory for mbufs could not be
 *  allocated.  It sets the boundary pointers and registers to the next
 *  packet location.
 */

void ns8390lost_frame(
	int unit)
{
	ns8390_softc_t	*is = &ns8390_softc[unit];
	vm_offset_t	nic = is->nic;
	volatile char	*sram_nxtpkt_ptr;
	int		temp_cr;

	sram_nxtpkt_ptr = (volatile char *) (is->sram +
	    (is->read_nxtpkt_ptr << 8));

	is->read_nxtpkt_ptr = *(sram_nxtpkt_ptr + 1);
	is->read_nxtpkt_ptr &= 0xFF;

	temp_cr = inb(nic+CR);
	outb(nic+CR, (temp_cr & 0x3f) | PS0);

	/* update boundary register */
	if (is->read_nxtpkt_ptr == ns8390get_CURR(unit))
		if (is->read_nxtpkt_ptr == is->pstart)
			outb(nic+BNDY, is->pstop - 1);
		else
			outb(nic+BNDY, is->read_nxtpkt_ptr - 1);
	else
		outb(nic+BNDY, is->read_nxtpkt_ptr);

	outb(nic+CR, temp_cr);

	return;
}

/*
 * ns8390get_CURR():
 *
 * Returns the value of the register CURR, which points to the next
 * available space for NIC to receive from network unto receive ring.
 *
 */

int ns8390get_CURR(
	int unit)
{
	vm_offset_t nic = ns8390_softc[unit].nic;
	int	temp_cr;
	int	ret_val;
	spl_t   s;
  
	s = SPLNET();

	temp_cr = inb(nic+CR);                  /* get current CR value */
	outb(nic+CR, ((temp_cr & 0x3F) | PS1)); /* select page 1 registers */
	ret_val = inb(nic+CURR);                /* read CURR value */
	outb(nic+CR, temp_cr);
	splx(s);
	return (ret_val & 0xFF);
}

/*
 * ns8390xmt:
 *
 *	This routine fills in the appropriate registers and memory
 *	locations on the ns8390 board and starts the board off on
 *	the transmit.
 *
 * input	: board number of interest, and a pointer to the mbuf
 * output	: board memory and registers are set for xfer and attention
 *
 */

void ns8390xmt(
	int	unit,
	io_req_t	m)
{
	ns8390_softc_t		*is = &ns8390_softc[unit];
	vm_offset_t		nic = is->nic;
	u_short			count = 0;	/* amount of data already copied */
	volatile char		*sram_write_pkt;
	int			board_id = is->board_id;
	vm_offset_t		hdwbase = ns8390info[unit]->address;
	spl_t     s;

	/* begining of physical address of transmition buffer */

	sram_write_pkt = is->sram + is->tpsr * 0x100; 

	count = m->io_count;
	if (board_id & IFWD_SLOT_16BIT) {
		s = splhi();
		en_16bit_access(hdwbase, board_id);
		bcopy16 (m->io_data, sram_write_pkt,  count);
		dis_16bit_access (hdwbase, board_id);
		splx(s);
	} else {
		bcopy (m->io_data, (char *) sram_write_pkt,  count);
	}
	while (count < ETHERMIN+sizeof(struct ether_header)) {
		*(sram_write_pkt + count) = 0;
		count++;
	}
	outb(nic+CR, ABR|STA|PS0);		/* select page 0 */
	outb(nic+TPSR, is->tpsr);		/* xmt page start at 0 of RAM */
	outb(nic+TBCR1, count >> 8);		/* upper byte of count */
	outb(nic+TBCR0, count & 0xFF);		/* lower byte of count */
	outb(nic+CR, TXP|ABR|STA);		/* start transmission */

	iodone(m);
}

boolean_t config_nic(
	int unit)
{
	ns8390_softc_t *is = &ns8390_softc[unit];
	vm_offset_t nic = is->nic;
	int       i;
	int       temp;
	int       count = 0;
	spl_t     s;

	outb (nic+CR, PS0|ABR|STP);             /* soft reset and page 0 */
	while ((!(inb (nic + ISR) & RST)) && (count < 10000))
		count++;
	if (count == 10000) {
		printf("%s%d: config_nic(): would not reset.\n",
			ns8390_softc[unit].card, unit);
	}

	temp = ((is->fifo_depth & 0x0c) << 3) | BMS;    /* fifo depth | not loopback */
	if (is->board_id & IFWD_SLOT_16BIT)
		temp |= WTS;			/* word xfer select (16 bit cards ) */
	outb (nic+DCR, temp);
	outb (nic+TCR, 0);
	outb (nic+RCR, MON);			/* receive configuration register */
	outb (nic+PSTART, is->pstart);		/* recieve ring starts 2k into RAM */
	outb (nic+PSTOP, is->pstop);		/* stop at last RAM buffer rcv location */
	outb (nic+BNDY, is->pstart);		/* boundary pointer for page 0 */
	s = SPLNET();

	outb (nic+CR, PS1|ABR|STP);		/* maintain rst | sel page 1 */
	is->read_nxtpkt_ptr = is->pstart + 1;	/* internal next packet pointer */
	outb (nic+CURR, is->read_nxtpkt_ptr);	/* Current page register */
	for(i=0; i<ETHER_ADDR_SIZE; i++)
		outb (nic+PAR0+i, is->address[i]);
	for(i=0; i<8; i++)
		outb (nic+MAR0+i, 0);

	outb (nic+CR, PS0|STP|ABR);
	splx(s);
	outb (nic+ISR, 0xff);			/* clear all interrupt status bits */
	outb (nic+IMR, imr_hold);		/* Enable interrupts */
	outb (nic+RBCR0, 0);			/* clear remote byte count */
	outb (nic+RBCR1, 0);

	outb (nic+CR, PS0|STA|ABR);		/* start NIC | select page 0 */
	outb (nic+RCR, AB);			/* receive configuration register */

	return TRUE;
}

/*
 * config_ns8390:
 *
 *	This routine does a standard config of a wd8003 family board, with
 *      the proper modifications to different boards within this family.
 *
 */
boolean_t config_wd8003(
	int	unit)
{
	ns8390_softc_t *is = &ns8390_softc[unit];
	vm_offset_t   hdwbase = ns8390info[unit]->address;
	int       RAMsize;
	volatile char  *RAMbase;
	int       addr_temp;

	is->tpsr = 0;			/* transmit page start hold */
	is->pstart = 0x06;		/* receive page start hold */
	is->read_nxtpkt_ptr = is->pstart + 1; /* internal next packet pointer */
	is->fifo_depth = 0x08;		/* NIC fifo threshold */
	switch (is->board_id & IFWD_RAM_SIZE_MASK) {
	      case IFWD_RAM_SIZE_8K:  
		RAMsize =  0x2000;	break;
	      case IFWD_RAM_SIZE_16K: 
		RAMsize =  0x4000;	break;
	      case IFWD_RAM_SIZE_32K: 
		RAMsize =  0x8000;	break;
	      case IFWD_RAM_SIZE_64K: 
		RAMsize = 0x10000;	break;
	      default:           
		RAMsize =  0x2000;	break;
	}
	is->pstop = (((int)RAMsize >> 8) & 0x0ff);      /* rcv page stop hold */
	RAMbase = (volatile char *)ns8390info[unit]->phys_address;
	addr_temp = ((int)(RAMbase) >> 13) & 0x3f; /* convert to be written to MSR */
	outb(hdwbase+IFWD_MSR, addr_temp | IFWD_MENB); /* initialize MSR */
	/* enable 16 bit access from lan controller */
	if (is->board_id & IFWD_SLOT_16BIT) {
		if (is->board_id & IFWD_INTERFACE_CHIP) {
			outb(hdwbase+IFWD_REG_5,
			     (inb(hdwbase + IFWD_REG_5) & IFWD_REG5_MEM_MASK) |
			     IFWD_LAN16ENB);
		} else {
			outb(hdwbase+IFWD_REG_5, (IFWD_LAN16ENB | IFWD_LA19));
		}
	}
	/*
	  outb(hdwbase+LAAR, LAN16ENB | LA19| MEM16ENB | SOFTINT);
	  */
	
	return TRUE;
}

/*
 * config_ns8390:
 *
 *	This routine does a standard config of a 3 com etherlink II board.
 *
 */
boolean_t config_3c503(
	int	unit)
{
	ns8390_softc_t	*is = &ns8390_softc[unit];
	struct bus_device	*dev = ns8390info[unit];
	vm_offset_t		hdwbase = dev->address;
	int		RAMsize = dev->am;
	int		i;

	is->tpsr =   0x20;		/* transmit page start hold */
	is->sram = (char *)phystokv(dev->phys_address) - is->tpsr * 0x100;
					/* When NIC says page 20, this means go to
					   the beginning of the sram range */
	is->pstart = 0x26;		/* receive page start hold */
	is->read_nxtpkt_ptr = is->pstart + 1; /* internal next packet pointer */
	is->fifo_depth = 0x08;		/* NIC fifo threshold */
	is->pstop = is->tpsr + ((RAMsize >> 8) & 0x0ff);      /* rcv page stop hold */

	outb(hdwbase+CTLR, CTLR_RST|CTLR_THIN);
	outb(hdwbase+CTLR, CTLR_THIN);
	outb(hdwbase+CTLR, CTLR_STA_ADDR|CTLR_THIN);
	for (i = 0; i < 6; i++)
		is->address[i] = inb(hdwbase+i);
	outb(hdwbase+CTLR, elii_bnc[is->board_id]?CTLR_THIN:CTLR_THICK);
	outb(hdwbase+PSTR, is->pstart);
	outb(hdwbase+PSPR, is->pstop);
	outb(hdwbase+IDCFR, IDCFR_IRQ2 << (elii_irq[is->board_id] - 2));
	outb(hdwbase+GACFR, GACFR_TCM|GACFR_8K);
	/* BCFR & PCRFR ro */
	/* STREG ro & dma */
	outb(hdwbase+DQTR, 0);
	outb(hdwbase+DAMSB, 0);
	outb(hdwbase+DALSB, 0);
	outb(hdwbase+VPTR2, 0);
	outb(hdwbase+VPTR1, 0);
	outb(hdwbase+VPTR0, 0);
	outb(hdwbase+RFMSB, 0);
	outb(hdwbase+RFLSB, 0);
	return TRUE;
}

/*
 *   wd80xxget_board_id:
 *
 *   determine which board is being used.
 *   Currently supports:
 *    wd8003E (tested)
 *    wd8003EBT
 *    wd8003EP (tested)
 *    wd8013EP (tested)
 *
 */
int wd80xxget_board_id(
	struct bus_device	*dev)
{
	vm_offset_t    hdwbase = dev->address;
	long           unit = dev->unit;
	long           board_id = 0;
	int            reg_temp;
	int            rev_num;			/* revision number */
	int            ram_flag;
	int	       i;
	boolean_t      register_aliasing;

	rev_num = (inb(hdwbase + IFWD_BOARD_ID) & IFWD_BOARD_REV_MASK) >> 1;
	printf("%s%d: ", ns8390_softc[unit].card, unit);
	
	if (rev_num == 0) {
		printf("rev 0x00\n");
		/* It must be 8000 board */
		return 0;
	}
	
	/* Check if register aliasing is true, that is reading from register
	   offsets 0-7 will return the contents of register offsets 8-f */
	
	register_aliasing = TRUE;
	for (i = 1; i < 5; i++) {
		if (inb(hdwbase + IFWD_REG_0 + i) !=
		    inb(hdwbase + IFWD_LAR_0 + i))
		    register_aliasing = FALSE;
	}
	if (inb(hdwbase + IFWD_REG_7) != inb(hdwbase + IFWD_CHKSUM))
	    register_aliasing = FALSE;
	
	
	if (register_aliasing == FALSE) {
		/* Check if board has interface chip */
		
		reg_temp = inb(hdwbase + IFWD_REG_7);   /* save old */
		outb(hdwbase + IFWD_REG_7, 0x35);	/* write value */
		inb(hdwbase + IFWD_REG_0);		/* dummy read */
		if ((inb(hdwbase + IFWD_REG_7) & 0xff) == 0x35) {
			outb(hdwbase + IFWD_REG_7, 0x3a);/* Try another value*/
			inb(hdwbase + IFWD_REG_0);	/* dummy read */
			if ((inb(hdwbase + IFWD_REG_7) & 0xff) == 0x3a) {
				board_id |= IFWD_INTERFACE_CHIP;
				outb(hdwbase + IFWD_REG_7, reg_temp);
				/* restore old value */
			}
		}
		
		/* Check if board is 16 bit by testing if bit zero in
		   register 1 is unchangeable by software. If so then
		   card has 16 bit capability */
		reg_temp = inb(hdwbase + IFWD_REG_1);
		outb(hdwbase + IFWD_REG_1, reg_temp ^ IFWD_16BIT);
		inb(hdwbase + IFWD_REG_0);		     /* dummy read */
		if ((inb(hdwbase + IFWD_REG_1) & IFWD_16BIT) ==
		    (reg_temp & IFWD_16BIT)) {        /* Is bit unchanged */
			board_id |= IFWD_BOARD_16BIT; /* Yes == 16 bit */
			reg_temp &= 0xfe;	      /* For 16 bit board
							 always reset bit 0 */
		}
		outb(hdwbase + IFWD_REG_1, reg_temp);    /* write value back */
		
		/* Test if 16 bit card is in 16 bit slot by reading bit zero in
		   register 1. */
		if (board_id & IFWD_BOARD_16BIT) {
			if (inb(hdwbase + IFWD_REG_1) & IFWD_16BIT) {
				board_id |= IFWD_SLOT_16BIT;
			}
		}
	}
	
	/* Get media type */
	
	if (inb(hdwbase + IFWD_BOARD_ID) & IFWD_MEDIA_TYPE) {
		board_id |= IFWD_ETHERNET_MEDIA;
	} else if (rev_num == 1) {
		board_id |= IFWD_STARLAN_MEDIA;
	} else {
		board_id |= IFWD_TWISTED_PAIR_MEDIA;
	}

	if (rev_num == 2) {
		if (inb(hdwbase + IFWD_BOARD_ID) & IFWD_SOFT_CONFIG) {
			if ((board_id & IFWD_STATIC_ID_MASK) == WD8003EB ||
			    (board_id & IFWD_STATIC_ID_MASK) == WD8003W) {
				board_id |= IFWD_ALTERNATE_IRQ_BIT;
			}
		}
		/* Check for memory size */
		
		ram_flag = inb(hdwbase + IFWD_BOARD_ID) & IFWD_MEMSIZE;
	    
		switch (board_id & IFWD_STATIC_ID_MASK) {
		      case WD8003E: /* same as WD8003EBT */
		      case WD8003S: /* same as WD8003SH */
		      case WD8003WT:
		      case WD8003W:
		      case WD8003EB: /* same as WD8003EP */
			if (ram_flag)
			    board_id |= IFWD_RAM_SIZE_32K;
			else
			    board_id |= IFWD_RAM_SIZE_8K;
			break;
		      case WD8003ETA:
		      case WD8003STA:
		      case WD8003EA:
		      case WD8003SHA:
		      case WD8003WA:
			board_id |= IFWD_RAM_SIZE_16K;
			break;
		      case WD8013EBT:
			if (board_id & IFWD_SLOT_16BIT) {
				if (ram_flag)
				    board_id |= IFWD_RAM_SIZE_64K;
				else
				    board_id |= IFWD_RAM_SIZE_16K;
			} else {
				if (ram_flag)
				    board_id |= IFWD_RAM_SIZE_32K;
				else
				    board_id |= IFWD_RAM_SIZE_8K;
			}
			break;
		      default:
			board_id |= IFWD_RAM_SIZE_UNKNOWN;
			break;
		}
	} else if (rev_num >= 3) {
		board_id &= (long) ~IFWD_MEDIA_MASK;   /* remove media info */
		board_id |= IFWD_INTERFACE_584_CHIP;
		board_id |= wd80xxget_eeprom_info(hdwbase, board_id);
	} else {
		/* Check for memory size */
		if (board_id & IFWD_BOARD_16BIT) {
			if (board_id & IFWD_SLOT_16BIT)
			    board_id |= IFWD_RAM_SIZE_16K;
			else
			    board_id |= IFWD_RAM_SIZE_8K;
		} else if (board_id & IFWD_MICROCHANNEL)
		    board_id |= IFWD_RAM_SIZE_16K;
		else if (board_id & IFWD_INTERFACE_CHIP) {
			if (inb(hdwbase + IFWD_REG_1) & IFWD_MEMSIZE)
			    board_id |= IFWD_RAM_SIZE_32K;
			else
			    board_id |= IFWD_RAM_SIZE_8K;
		} else
		    board_id |= IFWD_RAM_SIZE_UNKNOWN;
		
		/* No support for 690 chip yet. It should be checked here */
	}
	
	switch (board_id & IFWD_STATIC_ID_MASK) {
	      case WD8003E: printf("WD8003E or WD8003EBT"); break;
	      case WD8003S: printf("WD8003S or WD8003SH"); break;
	      case WD8003WT: printf("WD8003WT"); break;
	      case WD8003W: printf("WD8003W"); break;
	      case WD8003EB:
		if (board_id & IFWD_INTERFACE_584_CHIP)
		    printf("WD8003EP");
		else
		    printf("WD8003EB");
		break;
	      case WD8003EW: printf("WD8003EW"); break;
	      case WD8003ETA: printf("WD8003ETA"); break;
	      case WD8003STA: printf("WD8003STA"); break;
	      case WD8003EA: printf("WD8003EA"); break;
	      case WD8003SHA: printf("WD8003SHA"); break;
	      case WD8003WA: printf("WD8003WA"); break;
	      case WD8013EBT: printf("WD8013EBT"); break;
	      case WD8013EB:
		if (board_id & IFWD_INTERFACE_584_CHIP)
		    printf("WD8013EP");
		else
		    printf("WD8013EB");
		break;
	      case WD8013W: printf("WD8013W"); break;
	      case WD8013EW: printf("WD8013EW"); break;
	      default: printf("unknown"); break;
	}
	printf(" rev 0x%02x", rev_num);
	switch(board_id & IFWD_RAM_SIZE_RES_7) {
	      case IFWD_RAM_SIZE_UNKNOWN:
		break;
	      case IFWD_RAM_SIZE_8K:
		printf(" 8 kB ram");
		break;
	      case IFWD_RAM_SIZE_16K:
		printf(" 16 kB ram");
		break;
	      case IFWD_RAM_SIZE_32K:
		printf(" 32 kB ram");
		break;
	      case IFWD_RAM_SIZE_64K:
		printf(" 64 kB ram");
		break;
	      default:
		printf("wd: Internal error ram size value invalid %d\n",
		       (board_id & IFWD_RAM_SIZE_RES_7)>>16);
	}
	
	if (board_id & IFWD_BOARD_16BIT) {
		if (board_id & IFWD_SLOT_16BIT) {
			printf(", in 16 bit slot");
		} else {
			printf(", 16 bit board in 8 bit slot");
		}
	}
	if (board_id & IFWD_INTERFACE_CHIP) {
		if (board_id & IFWD_INTERFACE_584_CHIP) {
			printf(", 584 chip");
		} else {
			printf(", 583 chip");
		}
	}
	if ((board_id & IFWD_INTERFACE_CHIP) == IFWD_INTERFACE_CHIP) {
		/* program the WD83C583 EEPROM registers */
		int irr_temp, icr_temp;
		
		icr_temp = inb(hdwbase + IFWD_ICR);
		irr_temp = inb(hdwbase + IFWD_IRR);
		
		irr_temp &= ~(IFWD_IR0 | IFWD_IR1);
		irr_temp |= IFWD_IEN;
		
		icr_temp &= IFWD_WTS;
		
		if (!(board_id & IFWD_INTERFACE_584_CHIP)) {
			icr_temp |= IFWD_DMAE | IFWD_IOPE;
			if (ram_flag)
			    icr_temp |= IFWD_MSZ;
		}
		
		if (board_id & IFWD_INTERFACE_584_CHIP) {
			switch(ns8390info[unit]->irq) {
			      case 10:
				icr_temp |= IFWD_DMAE;
				break;
			      case 2:
			      case 9: /* Same as 2 */
				break;
			      case 11:
				icr_temp |= IFWD_DMAE;
				/*FALLTHROUGH*/
			      case 3:
				irr_temp |= IFWD_IR0;
				break;
			      case 15:
				icr_temp |= IFWD_DMAE;
				/*FALLTHROUGH*/
			      case 5:
				irr_temp |= IFWD_IR1;
				break;
			      case 4:
				icr_temp |= IFWD_DMAE;
				/*FALLTHROUGH*/
			      case 7:
				irr_temp |= IFWD_IR0 | IFWD_IR1;
				break;
			      default:
				printf("%s%d: wd80xx_get_board_id(): Could not set Interrupt Request Register according to pic(%d).\n",
				       ns8390_softc[unit].card, unit,
				       ns8390info[unit]->irq);
				break;
			}
		} else {
			switch(ns8390info[unit]->irq) {
				/* attempt to set interrupt according to assigned pic */
			      case 2:
			      case 9: /* Same as 2 */
				break;
			      case 3:
				irr_temp |= IFWD_IR0;
				break;
			      case 4:
				irr_temp |= IFWD_IR1;
				break;
			      case 5:
				irr_temp |= IFWD_IR1 | IFWD_AINT;
				break;
			      case 7: 
				irr_temp |= IFWD_IR0 | IFWD_IR1;
				break;
			      default: 
				printf("%s%d: wd80xx_get_board_id(): Could not set Interrupt Request Register according to pic(%d).\n",
				       ns8390_softc[unit].card, unit,
				       ns8390info[unit]->irq);
			}
		}
		outb(hdwbase + IFWD_IRR, irr_temp);
		outb(hdwbase + IFWD_ICR, icr_temp);
	}
	printf("\n");
	return board_id;
}

int wd80xxget_eeprom_info(
	unsigned short hdwbase,
	long	board_id)
{
  unsigned long new_bits = 0;
  int 		reg_temp;
  
  outb(hdwbase + IFWD_REG_1,
       ((inb(hdwbase + IFWD_REG_1) & IFWD_ICR_MASK) | IFWD_OTHER_BIT));
  outb(hdwbase + IFWD_REG_3,
       ((inb(hdwbase + IFWD_REG_3) & IFWD_EAR_MASK) | IFWD_ENGR_PAGE));
  outb(hdwbase + IFWD_REG_1,
       ((inb(hdwbase + IFWD_REG_1) & IFWD_ICR_MASK) |
	(IFWD_RLA | IFWD_OTHER_BIT)));
  while (inb(hdwbase + IFWD_REG_1) & IFWD_RECALL_DONE_MASK)
      ;
  
  reg_temp = inb(hdwbase + IFWD_EEPROM_1);
  switch (reg_temp & IFWD_EEPROM_BUS_TYPE_MASK) {
	case IFWD_EEPROM_BUS_TYPE_AT:
	  if (wd_debug & 1) printf("wd: AT bus, ");
	  break;
	case IFWD_EEPROM_BUS_TYPE_MCA:
	  if (wd_debug & 1) printf("wd: MICROCHANNEL, ");
	  new_bits |= IFWD_MICROCHANNEL;
	  break;
	default:
	  break;
  }
  switch (reg_temp & IFWD_EEPROM_BUS_SIZE_MASK) {
	case IFWD_EEPROM_BUS_SIZE_8BIT:
	  if (wd_debug & 1) printf("8 bit bus size, ");
	  break;
	case IFWD_EEPROM_BUS_SIZE_16BIT:
	  if (wd_debug & 1) printf("16 bit bus size ");
	  new_bits |= IFWD_BOARD_16BIT;
	  if (inb(hdwbase + IFWD_REG_1) & IFWD_16BIT) {
		  new_bits |= IFWD_SLOT_16BIT;
		  if (wd_debug & 1)
		      printf("in 16 bit slot, ");
	  } else {
		  if (wd_debug & 1)
		      printf("in 8 bit slot (why?), ");
	  }
	  break;
	default:
	  if (wd_debug & 1) printf("bus size other than 8 or 16 bit, ");
	  break;
  }
  reg_temp = inb(hdwbase + IFWD_EEPROM_0);
  switch (reg_temp & IFWD_EEPROM_MEDIA_MASK) {
	case IFWD_STARLAN_TYPE:
	  if (wd_debug & 1) printf("Starlan media, ");
	  new_bits |= IFWD_STARLAN_MEDIA;
	  break;
	case IFWD_TP_TYPE:
	  if (wd_debug & 1) printf("Twisted pair media, ");
	  new_bits |= IFWD_TWISTED_PAIR_MEDIA;
	  break;
	case IFWD_EW_TYPE:
	  if (wd_debug & 1) printf("Ethernet and twisted pair media, ");
	  new_bits |= IFWD_EW_MEDIA;
	  break;
	case IFWD_ETHERNET_TYPE: /*FALLTHROUGH*/
	default:
	  if (wd_debug & 1) printf("ethernet media, ");
	  new_bits |= IFWD_ETHERNET_MEDIA;
	  break;
  }
  switch (reg_temp & IFWD_EEPROM_IRQ_MASK) {
	case IFWD_ALTERNATE_IRQ_1:
	  if (wd_debug & 1) printf("Alternate irq 1\n");
	  new_bits |= IFWD_ALTERNATE_IRQ_BIT;
	  break;
	default:
	  if (wd_debug & 1) printf("\n");
	  break;
  }
  switch (reg_temp & IFWD_EEPROM_RAM_SIZE_MASK) {
	case IFWD_EEPROM_RAM_SIZE_8K:
	  new_bits |= IFWD_RAM_SIZE_8K;
	  break;
	case IFWD_EEPROM_RAM_SIZE_16K:
	  if ((new_bits & IFWD_BOARD_16BIT) && (new_bits & IFWD_SLOT_16BIT))
	      new_bits |= IFWD_RAM_SIZE_16K;
	  else
	      new_bits |= IFWD_RAM_SIZE_8K;
	  break;
	case IFWD_EEPROM_RAM_SIZE_32K:
	  new_bits |= IFWD_RAM_SIZE_32K;
	  break;
	case IFWD_EEPROM_RAM_SIZE_64K:
	  if ((new_bits & IFWD_BOARD_16BIT) && (new_bits & IFWD_SLOT_16BIT))
	      new_bits |= IFWD_RAM_SIZE_64K;
	  else
	      new_bits |= IFWD_RAM_SIZE_32K;
	  break;
	default:
	  new_bits |= IFWD_RAM_SIZE_UNKNOWN;
	  break;
  }
  outb(hdwbase + IFWD_REG_1,
       ((inb(hdwbase + IFWD_REG_1) & IFWD_ICR_MASK) | IFWD_OTHER_BIT));
  outb(hdwbase + IFWD_REG_3,
       ((inb(hdwbase + IFWD_REG_3) & IFWD_EAR_MASK) | IFWD_EA6));
  outb(hdwbase + IFWD_REG_1,
       ((inb(hdwbase + IFWD_REG_1) & IFWD_ICR_MASK) | IFWD_RLA));
  return new_bits;
}

void wdpr(int unit)
{
	vm_offset_t nic = ns8390_softc[unit].nic;
	spl_t	s;
	int	temp_cr;

	s = SPLNET();
	temp_cr = inb(nic);		/* get current CR value */

	printf("CR %x, BNDRY %x, TSR %x, NCR %x, FIFO %x, ISR %x, RSR %x\n",
		inb(nic+0x0), inb(nic+0x3), inb(nic+0x4), inb(nic+0x5),
		inb(nic+0x6), inb(nic+0x7), inb(nic+0xc));
	printf("CLD %x:%x, CRD %x:%x, FR %x, CRC %x, Miss %x\n",
		inb(nic+0x1), inb(nic+0x2),
		inb(nic+0x8), inb(nic+0x9),
		inb(nic+0xd), inb(nic+0xe), inb(nic+0xf));

	
	outb(nic, (temp_cr&0x3f)|PS1);		/* page 1 CR value */
	printf("PHYS %x:%x:%x:%x:%x:%x CUR %x\n",
		inb(nic+0x1), inb(nic+0x2), inb(nic+0x3),
		inb(nic+0x4), inb(nic+0x5), inb(nic+0x6),
		inb(nic+0x7));
	printf("MAR %x:%x:%x:%x:%x:%x:%x:%x\n",
		inb(nic+0x8), inb(nic+0x9), inb(nic+0xa), inb(nic+0xb),
		inb(nic+0xc), inb(nic+0xd), inb(nic+0xe), inb(nic+0xf));
	outb(nic, temp_cr);			/* restore current CR value */
	splx(s);
}


/*
  This sets bit 7 (0 justified) of register offset 0x05. It will enable
  the host to access shared RAM 16 bits at a time. It will also maintain
  the LAN16BIT bit high in addition, this routine maintains address bit 19
  (previous cards assumed this bit high...we must do it manually)
  
  note 1: this is a write only register
  note 2: this routine should be called only after interrupts are disabled
    and they should remain disabled until after the routine 'dis_16bit_access'
    is called
*/

void en_16bit_access(
	unsigned short hdwbase,
	long	board_id)
{
	if (board_id & IFWD_INTERFACE_CHIP)
	    outb(hdwbase+IFWD_REG_5,
		 (inb(hdwbase+IFWD_REG_5) & IFWD_REG5_MEM_MASK)
		 | IFWD_MEM16ENB | IFWD_LAN16ENB);
        else
            outb(hdwbase+IFWD_REG_5, (IFWD_MEM16ENB | IFWD_LAN16ENB |
				      IFWD_LA19));
}

/*
  This resets bit 7 (0 justified) of register offset 0x05. It will disable
  the host from accessing shared RAM 16 bits at a time. It will maintain the
  LAN16BIT bit high in addition, this routine maintains address bit 19
  (previous cards assumed this bit high...we must do it manually)

  note: this is a write only register
*/

void dis_16bit_access(
	unsigned short hdwbase,
	long	board_id)
{
	if (board_id & IFWD_INTERFACE_CHIP)
	    outb(hdwbase+IFWD_REG_5,
		 ((inb(hdwbase+IFWD_REG_5) & IFWD_REG5_MEM_MASK) |
		  IFWD_LAN16ENB));
	else
	    outb(hdwbase+IFWD_REG_5, (IFWD_LAN16ENB | IFWD_LA19));
}

