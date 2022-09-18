/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	autoconf.c,v $
 * Revision 1.7.1.12  91/05/03  10:58:23  rvb
 * 	Add alternate port addresses for lpr.
 * 	[91/05/03            rvb]
 * 
 * Revision 1.7.1.11  91/03/28  08:45:19  rvb
 * 	Define cold to keep mt.xinu happy.
 * 	[91/03/25            rvb]
 * 
 * 	Added aha support.
 * 	[91/03/25            rvb]
 * 
 * Revision 1.7.1.10  91/01/11  08:33:37  rvb
 * 	wd8003 -> ns8390
 * 
 * Revision 2.4.1.1  90/11/27  11:39:23  rvb
 * 	No iPSC2 in this branch.
 * 
 * 
 * Revision 2.4  90/11/26  14:48:56  rvb
 * 	jsb bet me to XMK34, sigh ...
 * 	[90/11/26            rvb]
 * 	Synched 2.5 & 3.0 at I386q (r1.7.1.8) & XMK35 (r2.4)
 * 	[90/11/15            rvb]
 * 
 * Revision 2.3  90/10/01  14:22:53  jeffreyh
 * 	added wd ethernet driver
 * 	[90/09/27  18:23:07  jeffreyh]
 * 
 * Revision 1.7.1.7  90/08/25  15:42:34  rvb
 * 	Define take_<>_irq() vs direct manipulations of ivect and friends.
 * 	Replace single Ctlr[] with one per Ctlr type.
 * 	[90/08/20            rvb]
 * 
 * 	Added parallel port printer driver.
 * 	[90/08/14            mg32]
 * 
 * Revision 1.7.1.6  90/07/27  11:22:57  rvb
 * 	Move wd8003 IRQ to IRQ9.
 * 	[90/07/26            rvb]
 * 
 * Revision 1.7.1.5  90/07/10  11:41:45  rvb
 * 	iPSC2: subtype and call dcminit().
 * 	[90/06/16            rvb]
 * 
 * 	Rework probe and attach to be much more bsd flavored.
 * 	[90/06/07            rvb]
 * 
 * Revision 1.7.1.4  90/06/07  08:04:46  rvb
 * 	updated for new hd driver probe/attach	[eugene]
 * 	(Temporarily disabled.)
 * 
 * Revision 1.7.1.3  90/05/14  13:17:45  rvb
 * 	Copy in slave_config() from loose_ends.c
 * 	[90/04/23            rvb]
 * 
 * Revision 2.2  90/05/03  15:40:37  dbg
 * 	Converted for pure kernel.
 * 	[90/04/23            dbg]
 * 
 * Revision 1.7.1.2  90/03/16  18:14:51  rvb
 * 	Add 3com 3c501 ether [bernadat]
 * 	Also clean up things, at least for ether; there are NO
 * 	controllers -- just devices.
 * 
 * Revision 1.7.1.1  89/10/22  11:29:41  rvb
 * 	Call setconf for generic kernels.
 * 	[89/10/17            rvb]
 * 
 * Revision 1.7  89/09/20  17:26:26  rvb
 * 	Support ln for ORC
 * 	[89/09/20            rvb]
 * 
 * Revision 1.6  89/09/09  15:19:19  rvb
 * 	pc586, qd and com are now configured based on the appropriate .h
 * 	files and pccom -> com.
 * 	[89/09/09            rvb]
 * 
 * Revision 1.5  89/07/17  10:34:58  rvb
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 		An almost legitimate probe routine().
 * 	[89/07/11            rvb]
 * 
 * Revision 1.4  89/02/26  12:25:02  gm0w
 * 	Changes for cleanup.
 * 
 */
 
#ifdef	MACH_KERNEL
#include <sys/types.h>
#else	MACH_KERNEL
#include <cpus.h>
#include <cputypes.h>
#include <generic.h>
#include <sys/param.h>
#include <mach/machine.h>
#include <machine/cpu.h>
#endif	MACH_KERNEL
#include <i386/ipl.h>
#include <i386at/atbus.h>

int cold = 0;

#include <hd.h>
#if NHD > 0
extern	struct	isa_driver	hddriver;
extern int			(*hdintrs[])();
#define	SPLHD SPL5
#endif NHD

#include <aha.h>
#if NAHA > 0
extern	struct	isa_driver	ahadriver;
extern int			(*ahaintrs[])();
#define	SPLAHA SPL5
#endif NAHA

#include <fd.h>
#if NFD > 0
extern	struct	isa_driver	fddriver;
extern int			(*fdintrs[])();
#endif NFD

#include <pc586.h>
#if NPC586 > 0
extern	struct	isa_driver	pcdriver;
extern int			(*pc586intrs[])();
#endif NPC586

#include <ns8390.h>
#if NNS8390 > 0
extern	struct	isa_driver	ns8390driver;
extern int			(*ns8390intrs[])();
#endif NNS8390

#include <at3c501.h>
#if NAT3C501 > 0
extern	struct	isa_driver	at3c501driver;
extern int			(*at3c501intrs[])();
#endif NAT3C501

#include <com.h>
#if NCOM > 0
extern	struct	isa_driver	comdriver;
extern int			(*comintrs[])();
#endif NCOM

#include <lpr.h>
#if NLPR > 0
extern	struct	isa_driver	lprdriver;
extern int			(*lprintrs[])();
#endif NLPR

#include <wt.h>
#if NWT > 0
extern	struct	isa_driver	wtdriver;
extern int			(*wtintrs[])();
#endif NWT

#ifdef	MACH_KERNEL
#else	MACH_KERNEL
#if	anyone_cares_anymore
#include <qd.h>
#if NQD > 0
extern	struct	isa_ctlr	qdctlr[];
#endif NQD

#include <ln.h>
#if NLN > 0
extern	struct	isa_ctlr	lnctlr[];
extern	struct	isa_dev	lninfo[];
#endif NLN
#endif	anyone_cares_anymore
#endif	MACH_KERNEL

#if NHD > 0
struct	isa_ctlr	HdCtlrs[] = {
	/*
	    driver	idx   aliv 	 csr	        spl    pic  intrs
					start	    len type fwdp ctp
	 */
	{&hddriver,	 0,    0, (caddr_t)0x1f0,	 SPLHD, 14, hdintrs,
				  (caddr_t)0x1f0,  8},
};
#endif	NHD > 0

#if NAHA > 0
struct	isa_ctlr	AhaCtlrs[] = {
	/*
	    driver	idx   aliv 	 csr	        spl    pic  intrs
					start	    len type fwdp ctp
	 */
	{&ahadriver,	 0,    0, (caddr_t)0x330,	 SPLAHA, 11, ahaintrs,
				  (caddr_t)0x330,  3},
};
#endif	NAHA > 0

#if NFD > 0
struct	isa_ctlr	FdCtlrs[] = {
	{&fddriver,	 0,    0, (caddr_t)0x3f2,	 SPL5, 6, fdintrs,
				  (caddr_t)0x3f2,  6},
};
#endif	NFD > 0

struct	isa_dev	Devs[] = {
	/*
	   driver unit ct sl aliv 	 csr     spl    pic dk flags intrs
					start    len type fwdp ctp
	 */

#if NHD > 0
	{&hddriver,  0, 0, 0, 0, (caddr_t)0x104, SPLHD, 14, 0, 0, hdintrs,
					(caddr_t)0x1f0, 8, 0, 0, &HdCtlrs[0]},
	{&hddriver,  1, 0, 1, 0, (caddr_t)0x118, SPLHD, 14, 1, 0, hdintrs,
					(caddr_t)0x1f0, 8, 0, 0, &HdCtlrs[0]},
#endif NHD > 0

#if NAHA > 0
	{&ahadriver,  0, 0, 0, 0, (caddr_t)0x104, SPLAHA, 11, 0, 0, ahaintrs,
					(caddr_t)0x330, 3, 0, 0, &AhaCtlrs[0]},
	{&ahadriver,  1, 0, 1, 0, (caddr_t)0x118, SPLAHA, 11, 0, 0, ahaintrs,
					(caddr_t)0x330, 3, 0, 0, &AhaCtlrs[0]},
	{&ahadriver,  2, 0, 2, 0, (caddr_t)0x118, SPLAHA, 11, 0, 0, ahaintrs,
					(caddr_t)0x330, 3, 0, 0, &AhaCtlrs[0]},
	{&ahadriver,  3, 0, 3, 0, (caddr_t)0x118, SPLAHA, 11, 0, 0, ahaintrs,
					(caddr_t)0x330, 3, 0, 0, &AhaCtlrs[0]},
#endif AHA > 0

#if NFD > 0
	{&fddriver,  0, 0, 0, 0, (caddr_t)0x3f2, SPL5, 6, 0, 0, fdintrs,
					(caddr_t)0x3f2, 6, 0, 0, &FdCtlrs[0]},
	{&fddriver,  1, 0, 1, 0, (caddr_t)0x3f2, SPL5, 6, 1, 0, fdintrs,
					(caddr_t)0x3f2, 6, 0, 0, &FdCtlrs[0]},
#endif NFD > 0

#if NPC586 > 0
	/* For MACH Default */
	{&pcdriver, 0, -1, 0, 0, (caddr_t)0x0d0000, SPL6, 9, 0, 0, pc586intrs,
				 (caddr_t)0x0d0000, 0, 0, 0, 0},
	/* For Factory Default */
	{&pcdriver, 0, -1, 0, 0, (caddr_t)0x0c0000, SPL6, 5, 0, 0, pc586intrs,
				 (caddr_t)0x0c0000, 0, 0, 0, 0},
	/* For what Intel Ships */
	{&pcdriver, 0, -1, 0, 0, (caddr_t)0xf00000, SPL6, 12, 0, 0, pc586intrs,
				 (caddr_t)0x0f0000, 0, 0, 0, 0},
#endif NPC586 > 0

#if NNS8390 > 0
	{ &ns8390driver, 0, 0, 0, 0, (caddr_t)0x280, SPL6, 9, 0, 0, ns8390intrs,
				      (caddr_t)0x0d0000, 0x2000, 0,  0, 0},
	{ &ns8390driver, 0, 0, 0, 0, (caddr_t)0x2A0, SPL6, 9, 0, 0, ns8390intrs,
				      (caddr_t)0x0d0000, 0x2000, 0,  0, 0},
	{ &ns8390driver, 0, 0, 0, 0, (caddr_t)0x2E0, SPL6, 5, 0, 0, ns8390intrs,
				      (caddr_t)0x0d0000, 0x2000, 0,  0, 0},
	{ &ns8390driver, 0, 0, 0, 0, (caddr_t)0x300, SPL6, 5, 0, 0, ns8390intrs,
				      (caddr_t)0x0d0000, 0x2000, 0,  0, 0},
#endif NNS8390 > 0

#if NAT3C501 > 0
	{ &at3c501driver, 0, 0, 0, 0, (caddr_t)0x300, SPL6, 9, 0, 0, at3c501intrs,
				      (caddr_t)0x300, 0, 0,  0, 0},
#endif NAT3C501 > 0

#if NCOM > 0
	{&comdriver, 0, -1, 0, 0,(caddr_t)0x3f8, SPLTTY, 4, 0, 0, comintrs,
					 (caddr_t) 0x3f8, 8, 0, 0, 0},
	{&comdriver, 1, -1, 0, 0,(caddr_t)0x2f8, SPLTTY, 3, 0, 0, comintrs,
					 (caddr_t) 0x2f8, 8, 0, 0, 0},
	{&comdriver, 2, -1, 0, 0,(caddr_t)0x3e8, SPLTTY, 5, 0, 0, comintrs,
					 (caddr_t) 0x3e8, 8, 0, 0, 0},
	{&comdriver, 3, -1, 0, 0,(caddr_t)0x2e8, SPLTTY, 6, 0, 0, comintrs,
					 (caddr_t) 0x2e8, 8, 0, 0, 0},
#endif NCOM > 0

#if NLPR > 0
	{&lprdriver, 0, -1, 0, 0,(caddr_t)0x378, SPLTTY, 7, 0, 0, lprintrs,
					 (caddr_t) 0x378, 3, 0, 0, 0},
	{&lprdriver, 0, -1, 0, 0,(caddr_t)0x278, SPLTTY, 7, 0, 0, lprintrs,
					 (caddr_t) 0x278, 3, 0, 0, 0},
	{&lprdriver, 0, -1, 0, 0,(caddr_t)0x3bc, SPLTTY, 7, 0, 0, lprintrs,
					 (caddr_t) 0x3bc, 3, 0, 0, 0},
#endif NLPR > 0

#if NWT > 0
	{ &wtdriver, 0, 0, 0, 0, (caddr_t)0x300, SPL5, 5, 0, 0, wtintrs,
				      (caddr_t)0x300, 2, 0,  0, 0},
	{ &wtdriver, 0, 0, 0, 0, (caddr_t)0x288, SPL5, 5, 0, 0, wtintrs,
				      (caddr_t)0x288, 2, 0,  0, 0},
	{ &wtdriver, 0, 0, 0, 0, (caddr_t)0x338, SPL5, 5, 0, 0, wtintrs,
				      (caddr_t)0x288, 2, 0,  0, 0},
#endif NWT > 0

	{(struct isa_driver *) 0}
};

/*
 * probeio:
 *
 *	Probe and subsequently attach devices out on the AT bus.
 *
 *
 */
probeio()

{
	int	i;
	struct	isa_dev	*dev_p;
	struct	isa_driver	*drv_p;

	for (dev_p = Devs; drv_p = dev_p->dev_driver; dev_p++) {
		struct isa_ctlr *ctl_p = dev_p->dev_mi;
#ifdef	DEBUG
		printf("%s%d\n", drv_p->driver_dname, dev_p->dev_unit);
#endif	DEBUG
		if ((int)ctl_p && !ctl_p->ctlr_alive) 
			if (drv_p->driver_probe(ctl_p))
				ctl_p->ctlr_alive = 1;
			else
				continue;

		if (((int)ctl_p ? drv_p->driver_slave :	drv_p->driver_probe)(dev_p)) {
			dev_p->dev_alive = 1;
			drv_p->driver_attach(dev_p);
		}
	}

#ifdef	MACH_KERNEL
#else	MACH_KERNEL
#if	anyone_cares_anymore
#if NLN > 0
	for (i = 0; i < NLN; i++) {
		drv_p = lnctlr[i].ctlr_driver;
		dev_p = (struct isa_dev *)(drv_p->driver_dinfo + i);
		if (drv_p->driver_probe(dev_p->dev_addr, i)) {
			drv_p->driver_attach(dev_p);
		}
	}
#endif NLN

#if NQD > 0
	for (i = 0; i < NQD; i++) {
		drv_p = qdctlr[i].ctlr_driver;
		dev_p = (struct isa_dev *)(drv_p->driver_dinfo + i);
		if (drv_p->driver_probe(dev_p->dev_addr, i)) {
			drv_p->driver_attach(dev_p);
		}
	}
#endif NQD
#endif	anyone_cares_anymore
#endif	MACH_KERNEL
}

take_dev_irq(dev)
struct isa_dev	*dev;
{
	int pic = dev->dev_pic;

	if (intpri[pic] == 0) {
		iunit[pic] = dev->dev_unit;
		ivect[pic] = dev->dev_intr[0];
		intpri[pic] = dev->dev_spl;
		form_pic_mask();
	} else {
		printf("The device below will clobber IRQ %d.\n", pic);
		printf("You have two devices at the same IRQ.\n");
		printf("This won't work.  Reconfigure your hardware and try again.\n");
		printf("XYZ%d: port = %x, spl = %d, pic = %d.\n",
			dev->dev_unit, dev->dev_addr,
			dev->dev_spl, dev->dev_pic);
		while (1);
	}
		
}

take_ctlr_irq(ctlr)
struct isa_ctlr *ctlr;
{
	int pic = ctlr->ctlr_pic;
	if (intpri[pic] == 0) {
		iunit[pic] = ctlr->ctlr_ctlr;
		ivect[pic] = ctlr->ctlr_intr[0];
		intpri[pic] = ctlr->ctlr_spl;
		form_pic_mask();
	} else {
		printf("The device below will clobber IRQ %d.\n", pic);
		printf("You have two devices at the same IRQ.  This won't work.\n");
		printf("Reconfigure your hardware and try again.\n");
		while (1);
	}
}

#ifdef	MACH_KERNEL
#else	MACH_KERNEL
/*
 * Determine mass storage and memory configuration for a machine.
 * Get cpu type, and then switch out to machine specific procedures
 * which will probe adaptors to see what is out there.
 */
configure()
{

	master_cpu = 0;
	set_cpu_number();
#if	NCPUS > 1
	printf("Master cpu at slot %d.\n", master_cpu);
#endif	NCPUS > 1
	machine_slot[master_cpu].is_cpu = TRUE;
	machine_slot[master_cpu].running = TRUE;
	machine_slot[master_cpu].cpu_type = CPU_TYPE_I386;
	cpuspeed = 6;
#ifdef	AT386
	machine_slot[master_cpu].cpu_subtype = CPU_SUBTYPE_AT386;
	probeio();
#endif	AT386

#if	GENERIC > 0
	setconf();
#endif	GENERIC > 0
	return;
}

	/*
	 * slave_config is a temporary artifact which will go away as soon
	 * as kern/slave.c is made conditional on NCPUS > 1
	 */
slave_config()
{
}
#endif	MACH_KERNEL
