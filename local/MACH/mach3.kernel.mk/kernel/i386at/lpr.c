/* 
 * Mach Operating System
 * Copyright (c) 1994-1990 Carnegie Mellon University
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
 * $Log:	lpr.c,v $
 * Revision 2.10  94/12/15  15:44:30  dbg
 * 	ANSI-fied.
 * 	[93/12/28            dbg]
 * 
 * Revision 2.9  93/05/10  21:19:51  rvb
 * 	Lint.
 * 	[93/05/08  11:18:33  af]
 * 
 * Revision 2.8  93/02/04  07:58:18  danner
 * 	Warning fixups.
 * 	[93/01/27            danner]
 * 
 * Revision 2.7  93/01/24  13:18:12  danner
 * 	Convert lpr_addr to vm_offset_t.
 * 	[93/01/19            rvb]
 * 	Add d-link "600" ethernet device "de"
 * 	[92/08/13            rvb]
 * 
 * Revision 2.6  93/01/14  17:31:37  danner
 * 	Proper spl typing.
 * 	[92/11/30            af]
 * 
 * Revision 2.5  92/07/09  22:54:47  rvb
 * 	More robust probe.  On some hardware, inb's
 * 	return 0x00 vs 0xff.
 * 	[92/06/18            rvb]
 * 
 * Revision 2.4  92/04/03  12:09:11  rpd
 * 	Allow for stupid with more than one lpr as unit 0.
 * 	[92/03/10  10:22:40  rvb]
 * 
 * Revision 2.3  92/02/25  14:18:29  elf
 * 	Added protection against spurious interrupts.
 * 	[92/02/24            danner]
 * 
 * Revision 2.2  92/02/19  16:30:23  elf
 * 	Add lpr and par devices.  (taken from 2.5)
 * 	NOT DEBUGGED
 * 	[92/02/13            rvb]
 * 
 * Revision 2.3  91/07/15  13:43:28  mrt
 * 	Don't set UNUSED bits in intr_enable.
 * 	[91/06/27            mg32]
 * 
 * Revision 2.2  91/04/02  12:12:26  mbj
 * 	Use take_<>_irq() vs direct manipulations of ivect and friends.
 * 	[90/08/20            rvb]
 * 	Created 08/05/90.
 * 	Parallel port printer driver.
 * 	[90/08/14            mg32]
 * 
 */

/* 
 *	Parallel port printer driver v1.0
 *	All rights reserved.
 */ 
  
#include <lpr.h>
#if NLPR > 0
#include <par.h>
#include <de6c.h>
  
#include <mach/std_types.h>
#include <sys/types.h>
#include <sys/time.h>
#include <kern/kern_io.h>
#include <device/conf.h>
#include <device/errno.h>
#include <device/tty.h>
#include <device/io_req.h>
  
#include <machine/machspl.h>
#include <i386/ipl.h>
#include <i386/pio.h>
#include <chips/busses.h>
#include <i386at/lprreg.h>
  
#if NPAR > 0
extern void parattach(struct bus_device *);
#endif

#if NDE6C > 0
extern void de6cattach(struct bus_device *);
#endif

extern void 	timeout();
extern void 	ttrstrt();

/* 
 * Driver information for auto-configuration stuff.
 */
boolean_t lprprobe(
	vm_offset_t	port,
	struct bus_device *dev);
void lprattach(
	struct bus_device *);

void lprstart(
	struct tty *tp);
void lprstop(
	register struct tty *tp,
	int	flags);
io_return_t
lprgetstat(
	int		dev,
	dev_flavor_t	flavor,
	dev_status_t	data,
	natural_t	*count);
io_return_t
lprsetstat(
	int		dev,
	dev_flavor_t	flavor,
	dev_status_t	data,
	natural_t	count);

static vm_offset_t lpr_std[NLPR] = { 0 };

struct bus_device *lprinfo[NLPR];
struct bus_driver lprdriver = {
	lprprobe, 0, lprattach, 0, lpr_std, "lpr", lprinfo, 0, 0, 0};

struct tty	lpr_tty[NLPR];

boolean_t lpr_alive[NLPR] = { FALSE, };

boolean_t lprprobe(
	vm_offset_t	port,
	struct bus_device *dev)
{
	int	unit = dev->unit;

	if (unit < 0 || unit > NLPR) {
		printf("lpr %d out of range\n", unit);
		return FALSE;
	}

	outb(INTR_ENAB(port),0x07);
	outb(DATA(port),0xaa);
	if (inb(DATA(port)) != 0xaa)
		return FALSE;	/* not there */

	if (lpr_alive[unit]) {
		printf("lpr: Multiple alive entries for unit %d.\n", unit);
		printf("lpr: Ignoring entry with address = %x .\n", port);
		return FALSE;
	}
	lpr_alive[unit] = TRUE;
	return TRUE;
}

void lprattach(struct bus_device *dev)
{
	unsigned char	unit = dev->unit;
	unsigned short	addr = (unsigned short) dev->address;

	take_dev_irq(dev);
	printf(", port = %x, spl = %d, pic = %d.",
	       dev->address, dev->priority, dev->irq);
	lprinfo[unit] = dev;
  
	outb(INTR_ENAB(addr), inb(INTR_ENAB(addr)) & 0x0f);

#if NPAR > 0
	parattach(dev);
#endif

#if NDE6C > 0
	de6cattach(dev);
#endif
}

io_return_t lpropen(
	int	unit,
	int	flag,
	io_req_t ior)
{
	struct bus_device *isai;
	struct tty *tp;
	unsigned short addr;
  
	if (unit >= NLPR || (isai = lprinfo[unit]) == 0 || isai->alive == 0)
		return ENXIO;
	tp = &lpr_tty[unit];
	addr = (unsigned short) isai->address;
	tp->t_dev = unit;
	tp->t_addr = (char *) (unsigned int) addr;
	tp->t_oproc = lprstart;
	tp->t_state |= TS_WOPEN;
	tp->t_stop = lprstop;
	tp->t_getstat = lprgetstat;
	tp->t_setstat = lprsetstat;
	if ((tp->t_state & TS_ISOPEN) == 0)
		ttychars(tp);
	outb(INTR_ENAB(addr), inb(INTR_ENAB(addr)) | 0x10);
	tp->t_state |= TS_CARR_ON;
	return char_open(unit, tp, flag, ior);
}

io_return_t lprclose(
	int	unit,
	int	flag)
{
	struct	tty	*tp = &lpr_tty[unit];
	unsigned short	addr = 	(unsigned short) lprinfo[unit]->address;
  
	ttyclose(tp);
	if (tp->t_state&TS_HUPCLS || (tp->t_state&TS_ISOPEN)==0) {
		outb(INTR_ENAB(addr), inb(INTR_ENAB(addr)) & 0x0f);
		tp->t_state &= ~TS_BUSY;
	}
	return D_SUCCESS;
}

io_return_t lprread(
	int	unit,
	io_req_t ior)
{
	return char_read(&lpr_tty[unit], ior);
}

io_return_t lprwrite(
	int	unit,
	io_req_t ior)
{
	return char_write(&lpr_tty[unit], ior);
}

io_return_t
lprgetstat(
	int		dev,
	dev_flavor_t	flavor,
	dev_status_t	data,		/* pointer to OUT array */
	natural_t	*count)		/* out */
{
	return tty_get_status(&lpr_tty[dev], flavor, data, count);
}

io_return_t
lprsetstat(
	int		dev,
	dev_flavor_t	flavor,
	dev_status_t	data,
	natural_t	count)
{
	return tty_set_status(&lpr_tty[dev], flavor, data, count);
}

void lprintr(
	int unit)
{
	register struct tty *tp = &lpr_tty[unit];

	if ((tp->t_state & TS_ISOPEN) == 0)
	  return;

	tp->t_state &= ~TS_BUSY;
	if (tp->t_state&TS_FLUSH)
		tp->t_state &=~TS_FLUSH;
	tt_write_wakeup(tp);
	lprstart(tp);
}   

void lprstart(
	struct tty *tp)
{
	spl_t s = spltty();
	unsigned short addr = (unsigned int) tp->t_addr;
	int status;
	char nch;

	if (tp->t_state & (TS_TIMEOUT|TS_TTSTOP|TS_BUSY)) {
		splx(s);
		return;
	}

	status = inb(STATUS(addr));
	if (status & 0x20) {
		printf("Printer out of paper!\n");
		splx(s);
		return;
	}

	if (tp->t_outq.c_cc <= TTLOWAT(tp)) {
		tt_write_wakeup(tp);
	}
	if (tp->t_outq.c_cc == 0) {
		splx(s);
		return;
	}

	nch = getc(&tp->t_outq);
	if ((tp->t_flags & LITOUT) == 0 && (nch & 0200)) {
		timeout(ttrstrt, (char *)tp, (nch & 0x7f) + 6);
		tp->t_state |= TS_TIMEOUT;
		return;
	}
	outb(DATA(addr), nch);
	outb(INTR_ENAB(addr),inb(INTR_ENAB(addr)) | 0x01);
	outb(INTR_ENAB(addr),inb(INTR_ENAB(addr)) & 0x1e);
	tp->t_state |= TS_BUSY;
	splx(s);
}

void lprstop(
	register struct tty *tp,
	int	flags)
{
	if ((tp->t_state & TS_BUSY) && (tp->t_state & TS_TTSTOP) == 0)
		tp->t_state |= TS_FLUSH;
}

void lprpr_addr(unsigned short addr)
{
	printf("DATA(%x) %x, STATUS(%x) %x, INTR_ENAB(%x) %x\n",
		DATA(addr), inb(DATA(addr)),
		STATUS(addr), inb(STATUS(addr)),
		INTR_ENAB(addr), inb(INTR_ENAB(addr)));
}

void lprpr(int unit)
{
	lprpr_addr(lprinfo[unit]->address);
}

#endif	/* NLPR > 0 */
