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
 * $Log:	autoconf.c,v $
 * Revision 2.22  94/12/15  15:27:03  dbg
 * 	Combine bus_device and bus_ctlr structures.  Give real names to
 * 	'irq' and 'priority' fields instead of 'sysdep', 'sysdep1'.
 * 	[94/07/20            dbg]
 * 
 * 	Rewrite to use standard IOCONF.  Only probe for remote
 * 	console if COM device is configured.
 * 	[94/06/16            dbg]
 * 
 * Revision 2.21  93/11/17  16:41:08  dbg
 * 	Added 174x driver (dherity@cs.tcd.ie & ralf@chpc.org)
 * 	[93/10/06            af]
 * 	Lint.
 * 	[93/05/08  11:20:03  af]
 * 
 * 	Made it possible to have two Adaptec boards.
 * 	[93/05/07  18:37:34  af]
 * 
 * 	Added include of standard types.
 * 	[93/05/06  09:30:11  af]
 * 
 * Revision 2.20  93/10/20  15:54:10  dbg
 * 	Add clockmc, clockpit for real-time Mach.  Purge non-
 * 	MACH_KERNEL code.  Add ANSI function prototypes.
 * 	[93/05/18            dbg]
 * 
 * Revision 2.19  93/08/10  15:57:38  mrt
 * 	Iff rcline != -1, then proberc will turn on the com line first
 * 	thing.  So the rest of the probe will be reported thru rconsole.
 * 	[93/06/08            rvb]
 * 
 * Revision 2.18  93/05/10  23:24:01  rvb
 * 	Added TTD teledebug code used to initialize the teledebugger and
 * 	begin setup debugging.
 * 	[93/03/01            grm]
 * 
 * Revision 2.17  93/05/10  21:18:41  rvb
 * 	Lint.
 * 	[93/05/08  11:20:03  af]
 * 
 * 	Made it possible to have two Adaptec boards.
 * 	[93/05/07  18:37:34  af]
 * 
 * 	Added include of standard types.
 * 	[93/05/06  09:30:11  af]
 * 
 * Revision 2.16  92/04/03  12:08:35  rpd
 * 	Use port 0x250, 0x350 for irq 5 bnc, thick respectively.
 * 	[92/04/02            rvb]
 * 	Tossing (0x3bc) below is the WRONG thing to do!!
 * 	[92/03/10            rvb]
 * 
 * Revision 2.15  92/03/06  13:38:29  rpd
 * 	Removed 0x3bc entry for lprdriver until someone can come up
 * 	with a better fix.
 * 	[92/03/06  13:16:43  jsb]
 * 
 * Revision 2.14  92/02/19  16:29:36  elf
 * 	Re-oder device probes -- disks first.
 * 	[92/02/18            rvb]
 * 
 * Revision 2.13  92/02/19  15:08:08  elf
 * 	Made take_dev_irq() print device name instead of XYZ in case of
 * 	failure.
 * 	[92/01/20            kivinen]
 * 
 * 	Added more possible configurations for ns8390driver to be able to
 * 	use two wd cards simultaneously.
 * 	[92/01/20            kivinen]
 * 
 * Revision 2.12  92/01/14  16:43:46  rpd
 * 	Flush com3 it is hardly every available and would use irq 6 -- a no-no.
 * 	[92/01/08            rvb]
 * 
 * Revision 2.11  91/10/07  17:25:07  af
 * 	Allow for second fd controller and fix hd entry.
 * 	[91/10/01  15:26:32  rvb]
 * 
 * 	Synchronize with 2.5 tables.
 * 	[91/09/04            rvb]
 * 
 * Revision 2.10  91/08/24  11:57:16  af
 * 	Use new MI autoconf procedures. Added SCSI.
 * 	[91/08/02  02:52:15  af]
 * 
 * Revision 2.9  91/06/19  11:55:44  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:45:33  rvb]
 * 
 * Revision 2.8  91/05/14  16:19:38  mrt
 * 	Correcting copyright
 * 
 * Revision 2.7  91/02/05  17:15:58  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  17:41:36  mrt]
 * 
 * Revision 2.6  91/01/09  19:56:29  rpd
 * 	Converted from wd8003 to ns8390.
 * 	[91/01/08            rpd]
 * 
 * Revision 2.4  90/11/26  14:48:56  rvb
 * 	jsb beat me to XMK34, sigh ...
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
 
#include <mach_ttd.h>

#include <mach/std_types.h>
#include <kern/kern_io.h>
#include <i386/ipl.h>
#include <chips/busses.h>

/*
 * probeio:
 *
 *	Probe and subsequently attach devices out on the AT bus.
 *
 *
 */
void probeio(void)
{
	register struct	bus_device	*device;
	register struct	bus_device	*master;
	int				i = 0;

	for (master = bus_master_init; master->driver; master++) {
	    (void) configure_bus_master(master->name, master->address,
				master->phys_address, i, "atbus");
	}

	for (device = bus_device_init; device->driver; device++) {
	    /* ignore what we (should) have found already */
	    if (device->alive || device->ctlr != -1)
		continue;
	    (void) configure_bus_device(device->name, device->address,
				device->phys_address, i, "atbus");
	}

#if	MACH_TTD
	/*
	 * Initialize Remote kernel debugger.
	 */
	ttd_init();
#endif	/* MACH_TTD */
}

void proberc(void)
{
#if	NCOM > 0
	register struct	bus_device	*device;
	int				i = 0;
	extern int			rcline;
	extern struct bus_driver	comdriver;

	if (rcline == -1)
	    return;

	for (device = bus_device_init; device->driver; device++) {
	    if (device->driver == &comdriver && device->unit == rcline)
		(void) configure_bus_device(device->name, device->address,
					device->phys_address, i, "atbus");
	}
#endif	/* NCOM > 0 */
}

void take_dev_irq(
	struct bus_device *dev)
{
	int pic = (int)dev->irq;

	if (intpri[pic] == 0) {
	    iunit[pic] = dev->unit;
	    ivect[pic] = (int (*)()) dev->intr;	/* XXX */
	    intpri[pic] = (spl_t)dev->priority;
	    form_pic_mask();
	} else {
	    printf("The device below will clobber IRQ %d.\n", pic);
	    printf("You have two devices at the same IRQ.\n");
	    printf("This won't work.  Reconfigure your hardware and try again.\n");
	    printf("%s%d: port = %x, spl = %d, pic = %d.\n",
		   dev->name, dev->unit, dev->address,
		   dev->priority, dev->irq);
	    while (1);
	}
		
}

