h10599
s 00002/00002/00226
d D 8.1 93/06/11 15:54:15 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00000/00217
d D 7.5 93/05/07 15:19:15 mckusick 10 9
c fix lookback bug in network interrupt handling (from cgd@postgres)
e
s 00012/00011/00205
d D 7.4 92/10/11 10:20:11 bostic 9 8
c make kernel includes standard
e
s 00002/00001/00214
d D 7.3 92/05/11 16:39:57 bostic 8 7
c pmap_kernel() -> kernel_pmap; from Pace Willison
e
s 00002/00004/00213
d D 7.2 91/05/13 00:19:21 william 7 6
c gross,rude,...
e
s 00002/00002/00215
d D 7.1 91/05/09 23:32:51 bostic 6 5
c new copyright; att/bsd/shared
e
s 00002/00003/00215
d D 1.5 91/05/09 20:35:51 william 5 4
c interim version, changes for net2 tape
e
s 00016/00008/00202
d D 1.4 91/05/04 17:26:51 william 4 3
c interim version
e
s 00000/00000/00210
d D 1.3 91/01/08 19:13:26 william 3 2
c  npx.c wd.c wt.c
e
s 00132/00000/00078
d D 1.2 90/11/18 11:32:04 bill 2 1
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00078/00000/00000
d D 1.1 90/11/08 20:00:03 bill 1 0
c date and time created 90/11/08 20:00:03 by bill
e
u
U
t
T
I 4
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
E 6
I 6
D 11
 * Copyright (c) 1991 The Regents of the University of California.
E 6
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 6
 * %sccs.include.redist%
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */

E 4
I 1
/*
 * code to manage AT bus
D 4
 * %W% (Berkeley) %G%
E 4
 */

D 9
#include "param.h"
#include "systm.h"
#include "conf.h"
#include "file.h"
D 4
#include "dir.h"
E 4
D 5
#include "user.h"
E 5
#include "buf.h"
D 4
#include "vm.h"
E 4
#include "uio.h"
I 2
#include "syslog.h"
#include "machine/segments.h"
E 2
D 4
#include "machine/pte.h"
I 2
#include "machine/isa/isa_device.h"
#include "machine/isa/icu.h"
E 4
I 4
#include "i386/isa/isa_device.h"
#include "i386/isa/icu.h"
I 8
#include "vm/vm.h"
E 9
I 9
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/buf.h>
#include <sys/uio.h>
#include <sys/syslog.h>

#include <machine/segments.h>
#include <i386/isa/isa_device.h>
#include <i386/isa/icu.h>
#include <vm/vm.h>
E 9
E 8
E 4
E 2

I 2
/*
 * Configure all ISA devices
 */
isa_configure() {
	struct isa_device *dvp;
	struct isa_driver *dp;

	splhigh();
	INTREN(IRQ_SLAVE);
	for (dvp = isa_devtab_bio; config_isadev(dvp,&biomask); dvp++);
	for (dvp = isa_devtab_tty; config_isadev(dvp,&ttymask); dvp++);
	for (dvp = isa_devtab_net; config_isadev(dvp,&netmask); dvp++);
	for (dvp = isa_devtab_null; config_isadev(dvp,0); dvp++);
#include "sl.h"
#if NSL > 0
	netmask |= ttymask;
	ttymask |= netmask;
#endif
I 10

	/*
	 * The problem is... if netmask == 0, then the loopback
	 * code can do some really ugly things.
	 * workaround for this: if netmask == 0, set it to 0x8000, which
	 * is the value used by splsoftclock.  this is nasty, but it
	 * should work until this interrupt system goes away. -- cgd
	 */
	if (netmask == 0)
		netmask = 0x8000;       /* same as for softclock.  XXX */

E 10
	/* biomask |= ttymask ;  can some tty devices use buffers? */
	printf("biomask %x ttymask %x netmask %x\n", biomask, ttymask, netmask);
	splnone();
}

/*
 * Configure an ISA device.
 */
config_isadev(isdp, mp)
	struct isa_device *isdp;
	int *mp;
{
	struct isa_driver *dp;
 
	if (dp = isdp->id_driver) {
		if (isdp->id_maddr) {
D 4
			extern int atdevbase[];
E 4
I 4
			extern int atdevbase;
E 4

			isdp->id_maddr -= 0xa0000;
D 4
			isdp->id_maddr += (int)&atdevbase;
E 4
I 4
			isdp->id_maddr += atdevbase;
E 4
		}
		isdp->id_alive = (*dp->probe)(isdp);
		if (isdp->id_alive) {
			printf("%s%d", dp->name, isdp->id_unit);
			(*dp->attach)(isdp);
			printf(" at 0x%x ", isdp->id_iobase);
			if(isdp->id_irq) {
				int intrno;

				intrno = ffs(isdp->id_irq)-1;
				printf("irq %d ", intrno);
				INTREN(isdp->id_irq);
				if(mp)INTRMASK(*mp,isdp->id_irq);
				setidt(ICU_OFFSET+intrno, isdp->id_intr,
					 SDT_SYS386IGT, SEL_KPL);
			}
			if (isdp->id_drq != -1) printf("drq %d ", isdp->id_drq);
			printf("on isa\n");
		}
		return (1);
	} else	return(0);
}

D 5
#define	IDTVEC(name)	X/**/name
E 5
I 5
#define	IDTVEC(name)	__CONCAT(X,name)
E 5
/* default interrupt vector table */
extern	IDTVEC(intr0), IDTVEC(intr1), IDTVEC(intr2), IDTVEC(intr3),
	IDTVEC(intr4), IDTVEC(intr5), IDTVEC(intr6), IDTVEC(intr7),
	IDTVEC(intr8), IDTVEC(intr9), IDTVEC(intr10), IDTVEC(intr11),
	IDTVEC(intr12), IDTVEC(intr13), IDTVEC(intr14), IDTVEC(intr15);
	
/*
 * Fill in default interrupt table (in case of spuruious interrupt
 * during configuration of kernel, setup interrupt control unit
 */
isa_defaultirq() {

/* first icu */
	setidt(32, &IDTVEC(intr0),  SDT_SYS386IGT, SEL_KPL);
	setidt(33, &IDTVEC(intr1),  SDT_SYS386IGT, SEL_KPL);
	setidt(34, &IDTVEC(intr2),  SDT_SYS386IGT, SEL_KPL);
	setidt(35, &IDTVEC(intr3),  SDT_SYS386IGT, SEL_KPL);
	setidt(36, &IDTVEC(intr4),  SDT_SYS386IGT, SEL_KPL);
	setidt(37, &IDTVEC(intr5),  SDT_SYS386IGT, SEL_KPL);
	setidt(38, &IDTVEC(intr6),  SDT_SYS386IGT, SEL_KPL);
	setidt(39, &IDTVEC(intr7),  SDT_SYS386IGT, SEL_KPL);

/* second icu */
	setidt(40, &IDTVEC(intr8),  SDT_SYS386IGT, SEL_KPL);
	setidt(41, &IDTVEC(intr9),  SDT_SYS386IGT, SEL_KPL);
	setidt(42, &IDTVEC(intr10),  SDT_SYS386IGT, SEL_KPL);
	setidt(43, &IDTVEC(intr11),  SDT_SYS386IGT, SEL_KPL);
	setidt(44, &IDTVEC(intr12),  SDT_SYS386IGT, SEL_KPL);
	setidt(45, &IDTVEC(intr13),  SDT_SYS386IGT, SEL_KPL);
	setidt(46, &IDTVEC(intr14),  SDT_SYS386IGT, SEL_KPL);
	setidt(47, &IDTVEC(intr15),  SDT_SYS386IGT, SEL_KPL);

	/* initialize 8259's */
	outb(0xf1,0);
	outb(0x20,0x11);
	outb(0x21,32);
	outb(0x21,4);
	outb(0x21,1);
	outb(0x21,0xff);

	outb(0xa0,0x11);
	outb(0xa1,40);
	outb(0xa1,2);
	outb(0xa1,1);
	outb(0xa1,0xff);
}

E 2
/* stuff needed for virtual to physical calculations */
D 7
extern char Sysbase;
static unsigned long sbase = (unsigned long) &Sysbase;
E 7

struct buf *dma_bounce[8];
#define MAXDMASZ 512

D 7
/* XXX temporary */
E 7
I 7
/* XXX temporary crud */
E 7
kernel_space(x)
unsigned long x;
{
D 7
	if ((x >= sbase) & (x < sbase + 0x800000)) return 1;
E 7
I 7
	if (x >= KERNBASE) return 1;
E 7
	else return 0;
}


/****************************************************************************/
/*                                 at_dma                                   */
/* set up DMA read/write operation and virtual address addr for nbytes      */
/****************************************************************************/
at_dma(read,addr,nbytes, chan)
int read;
unsigned long addr;
int nbytes;
{
	unsigned long phys;
	int s,raw;
	caddr_t bounce;

	if (kernel_space(addr)) raw = 0;
	else raw = 1;

	if(raw) {
		if (dma_bounce[chan] == 0)
			dma_bounce[chan] = geteblk(MAXDMASZ);
		bounce = dma_bounce[chan]->b_un.b_addr;
	}

	/* copy bounce buffer on write */
	if (raw && !read) bcopy(addr,bounce,nbytes);

	/* Set read/write bytes */
	if (read) {
		outb(0xC,0x46); outb(0xB,0x46);
	} else {
		outb(0xC,0x4A); outb(0xB,0x4A);
	}
	/* Send start address */
	if (raw) phys = (unsigned long) bounce;
	else phys = addr;
	/* translate to physical */
D 5
	phys = phys - sbase;
E 5
I 5
D 8
	phys = pmap_extract(pmap_kernel(), (vm_offset_t)phys);
E 8
I 8
	phys = pmap_extract(kernel_pmap, (vm_offset_t)phys);
E 8
E 5
	outb(0x4,phys & 0xFF);
	outb(0x4,(phys>>8) & 0xFF);
	outb(0x81,(phys>>16) & 0xFF);
	/* Send count */
	nbytes--;
	outb(0x5,nbytes & 0xFF);
	outb(0x5,(nbytes>>8) & 0xFF);
	/* set channel 2 */
	outb(0x0A,chan);
I 2
}

/*
 * Handle a NMI, possibly a machine check.
 * return true to panic system, false to ignore.
 */
isa_nmi(cd) {

	log(LOG_CRIT, "\nNMI port 61 %x, port 70 %x\n", inb(0x61), inb(0x70));
	return(0);
}

/*
 * Caught a stray interrupt, notify
 */
isa_strayintr(d) {

	/* for some reason, we get bursts of intr #7, even if not enabled! */
	log(LOG_ERR,"ISA strayintr %d", ffs(d)-1);
E 2
}
E 1
