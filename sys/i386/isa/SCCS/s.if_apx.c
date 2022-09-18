h36778
s 00002/00002/00591
d D 8.1 93/06/11 15:53:48 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00012/00581
d D 7.11 92/10/11 10:20:05 bostic 11 10
c make kernel includes standard
e
s 00014/00002/00579
d D 7.10 92/07/23 16:50:05 sklower 10 9
c two fixes 
e
s 00001/00001/00580
d D 7.9 92/03/31 15:17:38 sklower 9 8
c dumb bug in apx_probe()
e
s 00013/00052/00568
d D 7.8 92/03/05 19:17:42 sklower 8 7
c this version works, has been tidied up for public consumption
e
s 00043/00011/00577
d D 7.7 92/03/05 18:45:02 sklower 7 6
c this version has some debugging code
e
s 00068/00039/00520
d D 7.6 92/03/04 20:02:26 sklower 6 5
c this version almost works, but buffer counts are wiered
e
s 00023/00026/00536
d D 7.5 92/03/03 18:03:44 sklower 5 4
c more prettying up before we circulate this; 
c also make it safe for IP only operation.
e
s 00106/00051/00456
d D 7.4 92/03/03 16:56:06 sklower 4 3
c this version can at least talk to the CSR's of the sgs thompson chip
e
s 00021/00075/00486
d D 7.3 92/02/25 18:33:46 sklower 3 2
c test for aliveness of board by looking at status of timer chip;
c (which needs to have high output to permit interrupts);\ spin loop in uprim
c forgot to increment timo variable.
e
s 00033/00029/00528
d D 7.2 91/08/09 12:43:03 sklower 2 1
c this version compiles, probably doesn't run.
e
s 00557/00000/00000
d D 7.1 91/08/09 12:04:12 sklower 1 0
c Driver for ADAX APC-PCX, an SGS Thompson MK5025 based HDLC board
e
u
U
t
T
I 1
/*
D 12
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Driver for SGS-THOMSON MK5025 based Link level controller.
 * The chip will do LAPB in hardware, although this driver only
 * attempts to use it for HDLC framing.
 *
 * Driver written by Keith Sklower, based on lance AMD7990 
 * driver by Van Jacobsen, and information graciously supplied
 * by the ADAX corporation of Berkeley, CA.
 */

#include "apx.h"
#if NAPX > 0

D 11
#include "param.h"
#include "mbuf.h"
#include "socket.h"
#include "ioctl.h"
#include "errno.h"
#include "syslog.h"
E 11
I 11
#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/syslog.h>
E 11

D 11
#include "net/if.h"
#include "net/netisr.h"
I 2
#include "net/if_types.h"
E 11
I 11
#include <net/if.h>
#include <net/netisr.h>
#include <net/if_types.h>
E 11
I 4
#ifdef CCITT
E 4
E 2
D 11
#include "netccitt/x25.h"
E 11
I 11
#include <netccitt/x25.h>
E 11
I 4
int x25_rtrequest(), x25_ifoutput();
I 7
D 8
struct mbuf_cache {
	int	mbc_size;
	int	mbc_num;
	int	mbc_oldsize;
	struct	mbuf **mbc_cache;
} apx_cache = { 20 };
E 8
E 7
#endif
E 4

D 2
#include "apxreg.h"
E 2
I 2
D 11
#include "if_apxreg.h"
E 11
I 11
#include <i386/isa/if_apxreg.h>
E 11
E 2

int	apxprobe(), apxattach(), apxstart(), apx_uprim(), apx_meminit();
D 2
int	apxinit(), x25_ifoutput(), apxioctl(), apxreset();
E 2
I 2
D 4
int	apxinit(), x25_ifoutput(), x25_rtrequest(), apxioctl(), apxreset();
I 3
int	apxctr();
E 3
E 2
void	apx_ifattach(), apxinput(), apxintr(), apxtint(), apaxrint();
E 4
I 4
D 8
int	apxinit(), apxoutput(), apxioctl(), apxreset(), apxdebug = 1;
E 8
I 8
int	apxinit(), apxoutput(), apxioctl(), apxreset(), apxdebug = 0;
E 8
void	apx_ifattach(), apxtest(), apxinput(), apxintr(), apxtint(), apxrint();
I 7
D 8
int	apxipdebug = 1;
E 8
E 7
E 4

struct apx_softc {
	struct	ifnet apx_if;
D 4
	caddr_t	apx_device;		/* e.g. isa_device */
	u_short	apx_csr4;		/* byte gender, set in mach dep code */
E 4
I 4
	caddr_t	apx_device;		/* e.g. isa_device, vme_device, etc. */
E 4
	struct	apc_reg *apx_reg;	/* control regs for both subunits */
	struct	apc_mem *apx_hmem;	/* Host addr for shared memory */
	struct	apc_mem *apx_dmem;	/* Device (chip) addr for shared mem */
	struct	sgcp *apx_sgcp;		/* IO control port for this subunit */
D 4
	struct	apc_modes apx_modes;	/* Parameters, as amended by ioctls */
E 4
I 4
	int	apx_flags;		/* Flags specific to this driver */
#define APXF_CHIPHERE	0x01		/* mk5025 present */
E 4
	int	apx_rxnum;		/* Last receiver dx we looked at */
	int	apx_txnum;		/* Last tranmistter dx we stomped on */
	int	apx_txcnt;		/* Number of packets queued for tx*/
I 7
	u_int	apx_msize;
D 8
	u_short	apx_csr0;
	u_short	apx_csr1;
E 8
E 7
I 6
	struct	sgae apx_csr23;		/* 24 bit init addr, as seen by chip */
E 6
D 4
} apx_softc[2 * NAPX], *apx_lastsoftc = apx_softc;
E 4
I 4
	u_short	apx_csr4;		/* byte gender, set in mach dep code */
	struct	apc_modes apx_modes;	/* Parameters, as amended by ioctls */
} apx_softc[2 * NAPX];
E 4

struct apxstat {
D 6
	int	nulltx;
	int	pint;
E 6
I 6
	int	rxnull;			/* no rx bufs ready this interrupt */
	int	rxnrdy;			/* expected rx buf not ready */
	int	rx2big;			/* expected rx buf not ready */
	int	txnull;
	int	pint;			/* new primitive available interrupt */
	int	rint;			/* receive interrupts */
	int	tint;			/* transmit interrupts */
	int	anyint;			/* note all interrupts */
	int	queued;			/* got through apxinput */
	int	nxpctd;			/* received while if was down */
I 7
	int	rstfld;			/* reset didn't work */
E 7
E 6
D 2
};
E 2
I 2
} apxstat;
E 2

/* default operating paramters for devices */
struct	apc_modes apx_default_modes = {
 { 1,		/* apm_sgob.lsaddr; */
   3,		/* apm_sgob.rsaddr; */
   -SGMTU,	/* apm_sgob.n1; */
   ((-10)<<8),	/* apm_sgob.n2_scale; */
   -1250,	/* apm_sgob.t1; */
   -10000,	/* apm_sgob.t3; */
   -80,		/* apm_sgob.tp; */
 },
 2,		/* apm_txwin; */
D 6
 5,		/* apm_apxmode; */
 0,		/* apm_apxaltmode; */
E 6
I 6
 1,		/* apm_apxmode: RS_232 connector and modem clock; */
 0,		/* apm_apxaltmode: enable dtr, disable X.21 connector; */
E 6
 IFT_X25,	/* apm_iftype; */
};

/* Begin bus & endian dependence */

D 2
#include "i386/isa/if_apxreg.h"
#include "i386/isa/isa_device.h"
E 2
I 2
D 11
#include "isa_device.h"
E 11
I 11
#include <i386/isa/isa_device.h>
E 11
E 2

struct	isa_driver apxdriver = {
	apxprobe, apxattach, "apx",
};

#define SG_RCSR(apx, csrnum) \
D 2
	 (outw(&(apx->apx_sgcp->sgcp_rap), csrnum << 1),
	  inw(&(apx->apx_sgcp->sgcp_rdp))
E 2
I 2
	 (outw(&(apx->apx_sgcp->sgcp_rap), csrnum << 1), \
	  inw(&(apx->apx_sgcp->sgcp_rdp)))
E 2

#define SG_WCSR(apx, csrnum, data) \
D 2
	 (outw(&(apx->apx_sgcp->sgcp_rap), csrnum << 1),
E 2
I 2
	 (outw(&(apx->apx_sgcp->sgcp_rap), csrnum << 1), \
E 2
	  outw(&(apx->apx_sgcp->sgcp_rdp), data))

#define APX_RCSR(apx, csrname) inb(&(apx->apx_reg->csrname))
#define APX_WCSR(apx, csrname, data) outb(&(apx->apx_reg->csrname), data)

#define TIMO 10000 /* used in apx_uprim */

apxprobe(id)
	register struct	isa_device *id;
{
D 7
	int	moffset, subunit, unit = id->id_unit << 1;
E 7
I 7
D 10
	int	moffset = 0, subunit, unit = id->id_unit << 1;
E 10
I 10
	int	moffset = 0, nchips = 2, unit = id->id_unit << 1, subunit;
E 10
E 7
D 2
	struct	apc_reg *reg = id->id_iobase;
E 2
I 2
	struct	apc_reg *reg = (struct apc_reg *)id->id_iobase;
E 2
	register struct	apx_softc *apx = apx_softc + unit;

D 3
	/* Set and read DTR defeat in channel 0 to test presence of apc */
	outb(&reg->axr_altmode, 4);
	if (inb(&reg->axr_altmode) == 0)
E 3
I 3
D 4
	apx->apx_if.if_unit = unit;
	apx->apx_reg = reg;
	if (apxctr(apx) == 0) {
		apxerror(apx, "no response from timer chip", 0);
E 3
		return 0;			/* No board present */
D 3

E 3
I 3
	}
E 4
E 3
D 5
	for (subunit = 0; subunit < 2; subunit++, apx++) {
E 5
I 5
D 10
	for (subunit = 0; subunit < 2; subunit++) {
E 10
I 10
	/*
	 * Probing for the second MK5025 on all ISA/EISA adax boards
	 * manufactured prior to July 1992 (and some time following)
	 * will hang the bus and the system.  Thus, it is essential
	 * not to probe for the second mk5025 if it is known not to be there.
	 * As the current config scheme for 386BSD does not have a flags
	 * field, we adopt the convention of using the low order bit of
	 * the memsize to warn us that we have a single chip board.
	 */
	if (id->id_msize & 1)
		nchips = 1;
	for (subunit = 0; subunit < nchips; subunit++) {
E 10
E 5
D 4
		/* Set and read DTR mode to test present of SGS thompson chip */
		apx->apx_if.if_unit = unit++;
D 2
		apx->apx_sgcp = reg->axr_sgcb + subunit;
E 2
I 2
		apx->apx_sgcp = reg->axr_sgcp + subunit;
E 2
		SG_WCSR(apx, 5, 0x08);
D 2
		if ((SG_RCSR(apx, 5) & 0xff08) != 0x08)) {
E 2
I 2
		if (((SG_RCSR(apx, 5) & 0xff08) != 0x08)) {
E 2
			apxerror(apx, "no mk5025 for channel", subunit);
			continue;
		}
E 4
D 7
		moffset = subunit ? id->id_msize >> 1 : 0;
E 7
I 7
		apx->apx_msize	= id->id_msize >> 1;
E 7
		apx->apx_hmem	= (struct apc_mem *) (id->id_maddr + moffset);
D 7
		apx->apx_dmem	= (struct apc_mem *) (moffset);
E 7
I 7
		apx->apx_dmem	= (struct apc_mem *) moffset;
E 7
D 4
		apx->apx_modes	= apx_default_modes;
E 4
D 8
		apx->apx_device = (caddr_t) id;
E 8
I 8
		apx->apx_device	= (caddr_t) id;
E 8
		apx->apx_reg	= reg;
D 4
		apx->apx_csr4	= 0x0110;	/* no byte swapping for PC-AT */
E 4
I 4
		apx->apx_sgcp	= reg->axr_sgcp + subunit;
		apx->apx_csr4	= 0x0210;	/* no byte swapping for PC-AT */
		apx->apx_modes	= apx_default_modes;
		apx->apx_if.if_unit = unit++;
D 5
		apxtest(apx);
E 5
I 5
D 9
		apxtest(apx++);
E 9
I 7
		moffset = apx->apx_msize;
I 9
		apxtest(apx++);
E 9
E 7
E 5
E 4
	}
	return 1;
}

apxattach(id)
D 5
	register struct isa_device *id;
E 5
I 5
	struct	isa_device *id;
E 5
{
D 4
	int	unit = id->id_unit + id->id_unit;
E 4
I 4
D 5
	int	unit = id->id_unit << 1;
E 5
I 5
	register struct	apx_softc *apx = apx_softc + (id->id_unit << 1);
E 5
E 4

D 5
	apx_ifattach(unit);
	apx_ifattach(unit + 1);
E 5
I 5
	apx_ifattach(&((apx++)->apx_if));
	apx_ifattach(&(apx->apx_if));
E 5
D 4
	return (0);
E 4
I 4
	return 0;
E 4
}
D 3

E 3
/* End bus & endian dependence */

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 */
I 2
void
E 2
D 5
apx_ifattach(unit)
E 5
I 5
apx_ifattach(ifp)
	register struct ifnet *ifp;
E 5
{
D 5
	register struct ifnet *ifp = &(apx_softc[unit].apx_if);
E 5
	/*
	 * Initialize ifnet structure
	 */
D 5
	if (apx_softc[unit].apx_device == 0)
		return;
E 5
D 4
	ifp->if_name = "apc";
	ifp->if_mtu = SGMTU;
	ifp->if_init = apxinit;
	ifp->if_output = x25_ifoutput;
	ifp->if_start = apxstart;
	ifp->if_ioctl = apxioctl;
	ifp->if_reset = apxreset;
D 2
	ifp->if_type = apx_default_modes.axp_iftype;
E 2
I 2
	ifp->if_type = apx_default_modes.apm_iftype;
E 2
	ifp->if_hdrlen = 5;
	ifp->if_addrlen = 8;
E 4
I 4
	ifp->if_name	= "apc";
	ifp->if_mtu	= SGMTU;
	ifp->if_init	= apxinit;
	ifp->if_output	= apxoutput;
	ifp->if_start	= apxstart;
	ifp->if_ioctl	= apxioctl;
	ifp->if_reset	= apxreset;
	ifp->if_type	= apx_default_modes.apm_iftype;
	ifp->if_hdrlen	= 5;
	ifp->if_addrlen	= 8;
E 4
	if_attach(ifp);
}
/*
 * Initialization of interface
 */
apxinit(unit)
	int unit;
{
	struct ifnet *ifp = &apx_softc[unit].apx_if;
	int s = splimp();

	ifp->if_flags &= ~(IFF_RUNNING|IFF_OACTIVE);
	if (apxreset(unit) && (ifp->if_flags & IFF_UP)) {
		ifp->if_flags |= IFF_RUNNING;
		(void)apxstart(ifp);
	}
	splx(s);
	return 0;
}

I 3
apxctr(apx)
	register struct apx_softc *apx;
{
D 4
	APX_WCSR(apx, axr_ccr, 0xb0); /* select ctr 2, write lsb+msb, mode 0 */
E 4
I 4
D 6
	int i;
E 6
	APX_WCSR(apx, axr_ccr, 0xB0); /* select ctr 2, write lsb+msb, mode 0 */
E 4
	APX_WCSR(apx, axr_cnt2, 0x1);
	APX_WCSR(apx, axr_cnt2, 0x0);
	DELAY(50);
D 4
	APX_WCSR(apx, axr_ccr, 0xD4); /* latch status, ctr 2; */
	return APX_RCSR(apx, axr_cnt2);
E 4
I 4
	APX_WCSR(apx, axr_ccr, 0xE8); /* latch status, ctr 2; */
	return (APX_RCSR(apx, axr_cnt2));
E 4
}

I 4
void
apxtest(apx)
	register struct apx_softc *apx;
{
	int i =  0;

	if ((apx->apx_if.if_unit & 1) == 0 && (i = apxctr(apx)) == 0)
		apxerror(apx, "no response from timer chip", 0);
	if (SG_RCSR(apx, 1) & 0x8000)
		SG_WCSR(apx, 1, 0x8040);
	SG_WCSR(apx, 4, apx->apx_csr4);
D 8
	if (apxdebug && i) {
		apxerror(apx, "counter 2 value", i);
		apxerror(apx, "mk5025 csr4 value", SG_RCSR(apx, 4));
	}
E 8
	SG_WCSR(apx, 5, 0x08);		/* Set DTR mode in SGS thompson chip */
	if (((i = SG_RCSR(apx, 5)) & 0xff08) != 0x08)
		apxerror(apx, "no mk5025, csr5 high bits are", i);
	else
		apx->apx_flags |= APXF_CHIPHERE;
I 6
	(void) apx_uprim(apx, SG_STOP, "stop after probing");
E 6
}

E 4
E 3
apxreset(unit)
	int	unit;
{
	register struct apx_softc *apx = &apx_softc[unit ^ 1];
	u_char apm_apxmode = 0, apm_apxaltmode = 0;
#define MODE(m) (m |= apx->apx_modes.m << ((apx->apx_if.if_unit & 1) ? 1 : 0))

	MODE(apm_apxmode);
	MODE(apm_apxaltmode);
	apx = apx_softc + unit;
	MODE(apm_apxmode);
	MODE(apm_apxaltmode);
	APX_WCSR(apx, axr_mode, apm_apxmode);
	APX_WCSR(apx, axr_altmode, apm_apxaltmode);
D 2
	apx->apx_txnum = apx->apx_rxnum = apx->apx_txcnt = apx->apx_rxnt = 0;
E 2
I 2
D 6
	apx->apx_txnum = apx->apx_rxnum = apx->apx_txcnt = 0;
E 2

	if (apx_uprim(apx, SG_STOP, "stop") ||
	    !(apx->apx_if.if_flags & IFF_UP))
E 6
I 6
	(void) apxctr(apx);
	(void) apx_uprim(apx, SG_STOP, "stop to reset");
	if ((apx->apx_if.if_flags & IFF_UP) == 0)
E 6
		return 0;
D 2
	apx_meminit(apx->apc_mem, apx); /* also sets CSR2 */
E 2
I 2
D 6
	apx_meminit(apx->apx_hmem, apx); /* also sets CSR2 */
E 2
	SG_WCSR(apx, 3, (int)apx->apx_dmem);
E 6
I 6
	apx_meminit(apx->apx_hmem, apx);
E 6
	SG_WCSR(apx, 4, apx->apx_csr4);
I 6
	SG_WCSR(apx, 2, apx->apx_csr23.f_hi);
	SG_WCSR(apx, 3, apx->apx_csr23.lo);
E 6
D 2
	if (apx_uprim(apx, SG_INIT, "init request")) ||
E 2
I 2
	if (apx_uprim(apx, SG_INIT, "init request") ||
E 2
	    apx_uprim(apx, SG_STAT, "status request") ||
D 7
	    apx_uprim(apx, SG_TRANS, "transparent mode"))
E 7
I 7
D 8
	    apx_uprim(apx, SG_TRANS, "transparent mode")) {
		apxstat.rstfld++;
E 8
I 8
	    apx_uprim(apx, SG_TRANS, "transparent mode"))
E 8
E 7
		return 0;
I 7
D 8
	}
E 8
E 7
I 3
D 6
	(void) apxctr(apx);
E 6
E 3
	SG_WCSR(apx, 0, SG_INEA);
D 2
	return 1:
E 2
I 2
	return 1;
E 2
}
I 6
D 8
int apx_doinit = 1, apx_dostat = 1;
int apx_didinit = 0, apx_didstat = 0;
E 8
E 6

apx_uprim(apx, request, ident)
D 5
	int request;
	char *ident;
E 5
	register struct apx_softc *apx;
I 5
	char *ident;
E 5
{
	register int timo = 0;
D 5
	int reply = SG_RCSR(apx, 1);
E 5
I 5
	int reply;
E 5

D 2
	if (reply & x8040)
		SG_WCRS(1, x8040); /* Magic! */
E 2
I 2
D 5
	if (reply & 0x8040)
E 5
I 5
	if ((apx->apx_flags & APXF_CHIPHERE) == 0)
		return 1;	/* maybe even should panic . . . */
I 6
D 8

if (request == SG_STAT) { if (apx_dostat) apx_didstat = 1; else return 0;}
if (request == SG_INIT) { if (apx_doinit) apx_didinit = 1; else return 0;}

E 8
E 6
	if ((reply = SG_RCSR(apx, 1)) & 0x8040)
E 5
D 4
		SG_WCRS(1, 0x8040); /* Magic! */
E 4
I 4
		SG_WCSR(apx, 1, 0x8040); /* Magic! */
I 7
D 8
	apx->apx_csr0 = SG_RCSR(apx, 0);
	if (request == SG_STOP && (apx->apx_csr0 & SG_STOPPED))
E 8
I 8
	if (request == SG_STOP && (SG_RCSR(apx, 0) & SG_STOPPED))
E 8
		return 0;
E 7
E 4
E 2
	SG_WCSR(apx, 1, request | SG_UAV);
	do {
D 4
		reply = SG_RCRS(1);
E 4
I 4
D 7
		reply = SG_RCSR(apx, 1);
E 7
I 7
D 8
		apx->apx_csr1 = reply = SG_RCSR(apx, 1);
E 8
I 8
		reply = SG_RCSR(apx, 1);
E 8
E 7
E 4
D 3
		if (timo >= TIMO | reply & 0x8000) {
E 3
I 3
D 6
		if (timo++ >= TIMO | reply & 0x8000) {
E 3
			apxerror(apx, ident, reply);
			return 1;
E 6
I 6
		if (timo++ >= TIMO || (reply & 0x8000)) {
D 8
			if (request != SG_STOP || apxdebug)
E 8
				apxerror(apx, ident, reply);
D 8
			if (request != SG_STOP)
E 8
				return 1;
E 6
		}
	} while (reply & SG_UAV);
I 7
D 8
	apx->apx_csr0 = SG_RCSR(apx, 0);
E 8
E 7
	return 0;
}

apx_meminit(apc, apx)
	register struct apc_mem *apc;
	struct apx_softc *apx;
{
	register struct apc_mem *apcbase = apx->apx_dmem;
	register int i;
D 2
#define LOWADDR(e) (((u_long)&(apcbase->(e))) & 0xffff)
#define HIADDR(e) ((((u_long)&(apcbase->(e))) >> 16) & 0xff)
E 2
I 2
#define LOWADDR(e) (((u_long)&(apcbase->e)) & 0xffff)
#define HIADDR(e) ((((u_long)&(apcbase->e)) >> 16) & 0xff)
E 2
D 6
#define SET_SGDX(dx, f, a, b, m) \
	{ (dx).sgdx_addr = LOWADDR(a); (dx).sgdx_bcnt = (b);\
	  (dx).sgdx_mcnt = (m); (dx).sgdx_flags = (f) | HIADDR(a); }
E 6
I 6
#define SET_SGAE(d, f, a) {(d).lo = LOWADDR(a); (d).f_hi = (f) | HIADDR(a);}
#define SET_SGDX(d, f, a, b) \
	{SET_SGAE((d).sgdx_ae, f, a); (d).sgdx_mcnt = (d).sgdx_bcnt = (b);}
E 6

D 6
	bzero((caddr_t)apc, LOWADDR(apc_rxmd[0]));
	apc->apc_mode = 0x8040;	/* 2 flag spacing, trans mode, 16bit FCS */
E 6
I 6
	apx->apx_txnum = apx->apx_rxnum = apx->apx_txcnt = 0;
D 7
	bzero((caddr_t)apc, ((caddr_t)(&apc->apc_rxmd[0])) - (caddr_t)apc);
	apc->apc_mode = 0x0008;	/* 2 flag spacing, trans mode, 16bit FCS */
E 7
I 7
D 8
	bzero((caddr_t)apc, apx->apx_msize);
	/*bzero((caddr_t)apc, ((caddr_t)(&apc->apc_rxmd[0])) - (caddr_t)apc);*/
	apc->apc_mode = 0x0108;	/* 2 flag spacing, leave addr&ctl, do CRC16 */
E 8
I 8
	bzero((caddr_t)apc, ((caddr_t)(&apc->apc_rxmd[0])) - (caddr_t)apc);
	apc->apc_mode = 0x0108;	/* 2 flag spacing, leave addr & ctl, do CRC16 */
E 8
E 7
E 6
	apc->apc_sgop = apx->apx_modes.apm_sgop;
D 6
	apc->apc_rlen = SG_RLEN | HIADDR(apc_rxmd[0]);
	apc->apc_rdra = LOWADDR(apc_rxmd[0]);
	apc->apc_rlen = SG_TLEN | apx->apx_modes.apm_txwin |HIADDR(apc_txmd[0]);
	apc->apc_tdra = LOWADDR(apc_txmd[0]);
	SET_SGDX(apc->apc_rxtid, SG_OWN, apc_rxidbuf, -SGMTU, 0);
	SET_SGDX(apc->apc_txtid, 0, apc_txidbuf, -SGMTU, 0);
	apc->apc_stathi = HIADDR(apc_sgsb);
	apc->apc_statlo = LOWADDR(apc_sgsb);
E 6
I 6
	SET_SGAE(apx->apx_csr23, SG_UIE | SG_PROM, apc_mode);
	SET_SGAE(apc->apc_rxdd, SG_RLEN, apc_rxmd[0]);
D 7
	SET_SGAE(apc->apc_txdd, SG_TLEN|apx->apx_modes.apm_txwin, apc_txmd[0]);
E 7
I 7
	i = SG_TLEN | ((apx->apx_modes.apm_txwin)<< 8);
	SET_SGAE(apc->apc_txdd, i, apc_txmd[0]);
E 7
	SET_SGAE(apc->apc_stdd, 0, apc_sgsb);
	SET_SGDX(apc->apc_rxtid, SG_OWN, apc_rxidbuf[0], -SGMTU);
	SET_SGDX(apc->apc_txtid, 0, apc_txidbuf[0], 0);
E 6
	for (i = 0; i < SGRBUF; i++)
D 6
		 SET_SGDX(apc->apc_rxmd[i], SG_OWN, apc_rbuf[i][0], -SGMTU, 0)
E 6
I 6
		 SET_SGDX(apc->apc_rxmd[i], SG_OWN, apc_rbuf[i][0], -SGMTU)
E 6
	for (i = 0; i < SGTBUF; i++)
D 6
		 SET_SGDX(apc->apc_txmd[i], SG_TUI, apc_tbuf[i][0], 0, 0)
	SG_WCSR(apx, 2, SG_UIE | SG_PROM | HIADDR(apc_mode));
E 6
I 6
D 7
		 SET_SGDX(apc->apc_txmd[i], SG_TUI, apc_tbuf[i][0], 0)
E 7
I 7
		 SET_SGDX(apc->apc_txmd[i], 0, apc_tbuf[i][0], 0)
E 7
E 6
}

/*
 * Start output on interface.  Get another datagram to send
 * off of the interface queue, and copy it to the interface
 * before starting the output.
 */
apxstart(ifp)
	struct ifnet *ifp;
{
	register struct apx_softc *apx = &apx_softc[ifp->if_unit];
	register struct sgdx *dx;
D 2
	struct apc_mem *apc = apx->apx_mem;
E 2
I 2
	struct apc_mem *apc = apx->apx_hmem;
E 2
	struct mbuf *m;
	int len;

	if ((ifp->if_flags & IFF_RUNNING) == 0)
		return (0);
	do {
D 2
		dx = apc->apc_txmd + apc->apc_txnum;
E 2
I 2
		dx = apc->apc_txmd + apx->apx_txnum;
E 2
		if (dx->sgdx_flags & SG_OWN)
			return (0);
		IF_DEQUEUE(&ifp->if_snd, m);
		if (m == 0)
			return (0);
		len = min(m->m_pkthdr.len, SGMTU);
D 2
		m_copydata(m, 0, len, apc->apc_txbuf[apx->apx_txnum]);
E 2
I 2
		m_copydata(m, 0, len, apc->apc_tbuf[apx->apx_txnum]);
I 10
		m_freem(m);
E 10
E 2
		dx->sgdx_mcnt = -len;
D 6
		dx->sgdx_flags = SG_OWN | SG_TUI | (0xff & dx->sgdx_flags);
E 6
I 6
		dx->sgdx_flags = (SG_OWN|SG_TUI|SG_SLF|SG_ELF) |
			(0xff & dx->sgdx_flags);
E 6
		SG_WCSR(apx, 0, SG_INEA | SG_TDMD);
I 7
		DELAY(20);
D 8
		apx->apx_csr1 = SG_RCSR(apx, 1);
		apx->apx_csr0 = SG_RCSR(apx, 0);
E 8
E 7
		if (++apx->apx_txnum >= SGTBUF)
			apx->apx_txnum = 0;
	} while (++apx->apx_txcnt < SGTBUF);
D 5
	apx->apx_txcnt = SGTBUF;
E 5
I 5
	apx->apx_txcnt = SGTBUF; /* in case txcnt > SGTBUF by mistake */
E 5
	ifp->if_flags |= IFF_OACTIVE;
	return (0);
}

I 2
void
E 2
apxintr()
{
D 4
	register struct apx_softc *apx = apx_lastsoftc;
	struct apx_softc *apxlim = apx_softc + NAPX + NAPX;
E 4
I 4
	register struct apx_softc *apx;
E 4
	int reply;

I 6
	apxstat.anyint++;
E 6
D 4
	do {
D 2
		if (apx->ap_if.if_flags & IFF_UP)
E 2
I 2
		if (apx->apx_if.if_flags & IFF_UP)
E 4
I 4
	for (apx = apx_softc + NAPX + NAPX; --apx >= apx_softc;) {
		if (apx->apx_flags & APXF_CHIPHERE)
E 4
E 2
		    /* Try to turn off interrupt cause */
D 7
		    while ((reply = SG_RCSR(apx, 0)) & 0xff) {
E 7
I 7
D 8
		    while ((apx->apx_csr0 = SG_RCSR(apx, 0)) & 0xff) {
			reply = apx->apx_csr0;
E 8
I 8
		    while ((reply = SG_RCSR(apx, 0)) & 0xff) {
E 8
E 7
			SG_WCSR(apx, 0, SG_INEA | 0xfe);
			if (reply & (SG_MERR|SG_TUR|SG_ROR)) {
				apxerror(apx, "mem, rx, or tx error", reply);
				apxinit(apx->apx_if.if_unit);
				break;
			}
			if (reply & SG_RINT)
				apxrint(apx);
			if (reply & SG_TINT)
				apxtint(apx);
			if (reply & SG_PINT)
				apxstat.pint++;
		}
D 4
		if (++apx >= apxlim)
			apx = apx_softc;
	} while (apx != apx_lastsoftc);
E 4
I 4
	}
E 4
}

I 2
void
E 2
apxtint(apx)
	register struct apx_softc *apx;
{
D 2
	register struct apc_mem *apc = apx->apx_mem;
E 2
I 2
	register struct apc_mem *apc = apx->apx_hmem;
E 2
	int i, loopcount = 0;

I 6
	apxstat.tint++;
E 6
	do {
		if ((i = apx->apx_txnum - apx->apx_txcnt) < 0)
			i += SGTBUF;
		if (apc->apc_txmd[i].sgdx_flags & SG_OWN) {
			if (loopcount)
				break;
D 6
			apxstat.nulltx++;
E 6
I 6
			apxstat.txnull++;
E 6
			return;
		}
		loopcount++;
		apx->apx_if.if_flags &= ~IFF_OACTIVE;
	} while (--apx->apx_txcnt > 0);
	apxstart(&apx->apx_if);
}

I 4
void
E 4
apxrint(apx)
	register struct apx_softc *apx;
{
D 2
	register struct apc_mem *apc = apx->apx_mem;
E 2
I 2
	register struct apc_mem *apc = apx->apx_hmem;
E 2
	register struct sgdx *dx = apc->apc_rxmd + apx->apx_rxnum;
I 6
	int i = 0;
E 6
#define SGNEXTRXMD \
dx = ++apx->apx_rxnum == SGRBUF ? &apc->apc_rxmd[apx->apx_rxnum = 0] : dx + 1;

I 6
	apxstat.rint++;
E 6
	/*
	 * Out of sync with hardware, should never happen?
	 */
D 6
	if (dx->sgdx_flags & SG_OWN) {
D 5
		apxerror(apx, "out of sync");
E 5
I 5
		apxerror(apx, "out of sync", apx->apx_rxnum);
E 5
		return;
E 6
I 6
	while (dx->sgdx_flags & SG_OWN) {
		apxstat.rxnrdy++;
		if (++i == SGRBUF) {
			apxstat.rxnull++;
			return;
		}
		SGNEXTRXMD;
E 6
	}
	/*
	 * Process all buffers with valid data
	 */
	while ((dx->sgdx_flags & SG_OWN) == 0) {
		if ((dx->sgdx_flags & (SG_SLF|SG_ELF)) != (SG_SLF|SG_ELF)) {
			/*
D 6
			 * Find the end of the packet so we can see how long
			 * it was.  We still throw it away.
E 6
I 6
			 * Find the end of the packet so we synch up.
			 * We throw the data away.
E 6
			 */
D 2
			apxerror(apx, "chained buffer", ds->sgdx_flags);
E 2
I 2
			apxerror(apx, "chained buffer", dx->sgdx_flags);
E 2
			do {
I 6
				apxstat.rx2big++;
E 6
				dx->sgdx_bcnt = 0;
				dx->sgdx_flags = SG_OWN | (0xff&dx->sgdx_flags);
				SGNEXTRXMD;
			} while (!(dx->sgdx_flags & (SG_OWN|SG_SLF|SG_ELF)));
			/*
			 * If search terminated without successful completion
			 * we reset the hardware (conservative).
			 */
			if ((dx->sgdx_flags & (SG_OWN|SG_SLF|SG_ELF)) !=
D 2
			    SG_ENP) {
E 2
I 2
			    SG_ELF) {
E 2
				apxreset(apx->apx_if.if_unit);
				return;
			}
		} else
			apxinput(&apx->apx_if, apc->apc_rbuf[apx->apx_rxnum],
D 6
					-dx->sgdx_bcnt);
E 6
I 6
					-dx->sgdx_mcnt);
E 6
		dx->sgdx_bcnt = 0;
		dx->sgdx_flags = SG_OWN | (0xff & dx->sgdx_flags);
		SGNEXTRXMD;
	}
}

I 2
void
E 2
apxinput(ifp, buffer, len)
D 5
register struct ifnet *ifp;
caddr_t buffer;
E 5
I 5
	register struct ifnet *ifp;
	caddr_t buffer;
E 5
{
I 5
	extern struct ifqueue hdintrq, ipintrq;
E 5
	register struct ifqueue *inq;
I 5
	register u_char *cp = (u_char *)buffer;
E 5
D 3
	struct mbuf *m, *apxget();
E 3
I 3
	struct mbuf *m, *m_devget();
E 3
D 5
	extern struct ifqueue hdintrq, ipintrq;
E 5
	int isr;

	ifp->if_ipackets++;
I 6
	if ((ifp->if_flags & IFF_UP) == 0) {
		apxstat.nxpctd++;
		return;
	}
E 6
D 5
    {
	register u_char *cp = (u_char *)buffer;

E 5
	if (cp[0] == 0xff && cp[1] == 0x3) {
		/* This is a UI HDLC Packet, so we'll assume PPP
		   protocol.  for now, IP only. */
		buffer += 4;
		len -= 4;
		inq = &ipintrq;
		isr = NETISR_IP;
	} else {
I 5
#ifdef CCITT
E 5
		inq = &hdintrq;
		isr = NETISR_CCITT;
	}
D 5
    }
	if (len <= 0)
E 5
I 5
	if (len <= 0) {
#endif
E 5
		return;
D 5

E 5
I 5
	}
E 5
D 3
	m = apxget(buffer, len , 0, ifp);
E 3
I 3
	m = m_devget(buffer, len, 0, ifp, (void (*)())0);
E 3
	if (m == 0)
		return;
I 7
D 8
#ifdef CCITT
	if (apxipdebug)
		mbuf_cache(&apx_cache, m);
#endif
E 8
E 7
D 5

E 5
	if(IF_QFULL(inq)) {
		IF_DROP(inq);
		m_freem(m);
	} else {
I 6
		apxstat.queued++;
E 6
		IF_ENQUEUE(inq, m);
		schednetisr(isr);
	}
D 3
}

/*
 * Routine to copy from board local memory into mbufs.
 */
struct mbuf *
apxget(buf, totlen, off0, ifp)
	char *buf;
	int totlen, off0;
	struct ifnet *ifp;
{
	register struct mbuf *m;
	struct mbuf *top = 0, **mp = &top;
	register int off = off0, len;
	register char *cp;
	char *epkt;

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
		bcopy(cp, mtod(m, caddr_t), (unsigned)len);
		cp += len;
		*mp = m;
		mp = &m->m_next;
		totlen -= len;
		if (cp == epkt)
			cp = buf;
	}
	return (top);
E 3
}

/*
 * Process an ioctl request.
 */
apxioctl(ifp, cmd, data)
	register struct ifnet *ifp;
	int cmd;
	caddr_t data;
{
	register struct ifaddr *ifa = (struct ifaddr *)data;
	int s = splimp(), error = 0;
	struct apx_softc *apx = &apx_softc[ifp->if_unit];

	switch (cmd) {
I 4

	case SIOCSIFADDR:
#ifdef CCITT
D 7
		ifa->ifa_rtrequest = x25_rtrequest;
E 7
I 7
D 8
		if (apxipdebug) {
			ifp->if_flags |= IFF_UP;
			apxinit(ifp->if_unit);
		} else 
			ifa->ifa_rtrequest = x25_rtrequest;
E 8
I 8
		ifa->ifa_rtrequest = x25_rtrequest;
E 8
E 7
		break;

E 4
	case SIOCSIFCONF_X25:
I 4
		ifp->if_output = x25_ifoutput;
E 4
		ifp->if_flags |= IFF_UP;
		error = hd_ctlinput(PRC_IFUP, ifa->ifa_addr);
		if (error == 0)
			apxinit(ifp->if_unit);
I 4
#endif
E 4
		break;

D 4
	case SIOCSIFADDR:
		ifa->ifa_rtrequest = x25_rtrequest;
		break;

E 4
	case SIOCSIFFLAGS:
		if (((ifp->if_flags & IFF_UP) == 0 &&
		     (ifp->if_flags & IFF_RUNNING)) ||
		    (ifp->if_flags & IFF_UP) &&
		     (ifp->if_flags & IFF_RUNNING) == 0)
			apxinit(ifp->if_unit);
		break;

	case SIOCSIFMODE:
		if ((ifp->if_flags & IFF_UP) == 0)
D 2
			apx->apx_modes = *(struct apx_modes *)data;
E 2
I 2
			apx->apx_modes = *(struct apc_modes *)data;
E 2
		else
	default:
			error = EINVAL;

	}
	splx(s);
	return (error);
}

apxerror(apx, msg, data)
	register struct	apx_softc *apx;	
	char	*msg;
{
	log(LOG_WARNING, "apc%d: %s, stat=0x%x\n",
		apx->apx_if.if_unit, msg, data);
}
I 8

E 8
I 4
/*
 * For debugging loopback activity.
 */
D 8
static char pppheader[4] = { -1, 3, 0, 0x21 };

E 8
apxoutput(ifp, m, dst, rt)
register struct ifnet *ifp;
register struct mbuf *m;
struct sockaddr *dst;
struct rtentry *rt;
{
I 8
	int s = splimp(), error = 0;
	static char pppheader[4] = { -1, 3, 0, 0x21 };
E 8
	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
D 8
	int s = splimp(), error = 0;
E 8
I 8
	ifp->if_opackets++;
E 8
	M_PREPEND(m, sizeof pppheader, M_DONTWAIT);
	if (m == 0) {
		splx(s);
		return ENOBUFS;
	}
	bcopy(pppheader, mtod(m, caddr_t), sizeof pppheader);
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
D 8
	    /* printf("%s%d: HDLC says OK to send but queue full, may hang\n",
			ifp->if_name, ifp->if_unit);*/
E 8
		m_freem(m);
		error = ENOBUFS;
	} else {
		IF_ENQUEUE(&ifp->if_snd, m);
		if ((ifp->if_flags & IFF_OACTIVE) == 0)
			(*ifp->if_start)(ifp);
	}
	splx(s);
	return (error);
}
D 8

E 8
E 4
#endif /* NAPX */
E 1
