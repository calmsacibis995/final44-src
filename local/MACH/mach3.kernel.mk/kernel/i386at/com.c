/* 
 * Mach Operating System
 * Copyright (c) 1994,1993,1992,1991,1990 Carnegie Mellon University
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
 * $Log:	com.c,v $
 * Revision 2.22  94/12/15  15:37:31  dbg
 * 	Use real names instead of 'sysdep', 'sysdep1'.
 * 	[94/07/20            dbg]
 * 
 * 	Made comopen probe for the COM port if it was not found at
 * 	autoconfiguration time.  This handles PCMCIA modems, which may
 * 	be added at any point.
 * 	[94/03/13            dbg]
 * 
 * 	Removed portdeath routine.
 * 	[94/01/11            dbg]
 * 
 * Revision 2.21  93/11/17  16:42:59  dbg
 * 	Restore earlier fix: can`t use ttymodem "flow control" since
 * 	modem drops carrier but still talks to machine.  Shut down FIFO
 * 	on close.
 * 	[93/06/15            dbg]
 * 
 * 	Include kern/time_out.h for hz.
 * 	[93/06/04            dbg]
 * 
 * Revision 2.20  93/08/10  15:57:14  mrt
 * 	Add computc(char ch, int unit) puts a character out on the
 * 	give serial line.  For mice, etc.
 * 	Add comgetc(int unit) for same.
 * 	Add comparm(int unit, int baud, int intr, int mode, int modem)
 * 	[93/06/06            rvb]
 * 
 * Revision 2.19  93/05/30  21:08:04  rvb
 * 	Changed to use MI modem code, adding commctl.
 * 	Does CTS/RTS flow control now.
 * 	[93/05/29  09:52:46  af]
 * 
 * Revision 2.18  93/05/15  19:31:09  mrt
 * 	machparam.h -> machspl.h
 * 
 * Revision 2.17  93/05/14  15:09:59  rvb
 * 	Berman is right; check txbusy first then write for comrc_put
 * 	[93/05/14            rvb]
 * 
 * Revision 2.16  93/05/11  13:20:16  rvb
 * 	Accept either keyboard in cn_dogetc
 * 
 * Revision 2.15  93/05/10  21:18:46  rvb
 * 	Removed 2.5 compat cruft. FIFOs work, but needs more work.
 * 	Added watchdog to cure lost xmit interrupts [there is a
 * 	bug somewhere else because I am losing them even on a
 * 	chip that has no hardware bugs].  Do input buffering
 * 	at all speeds higher than 300 bauds.
 * 	[93/05/06  09:29:11  af]
 * 
 * Revision 2.14  93/05/10  17:47:18  rvb
 * 	I spend a little time working out rconsole with Steve Berman
 * 	and don't want to lose the code.  It's not quite done yet
 * 	but it seems close.
 * 	[93/05/10            rvb]
 * 
 * Revision 2.13  93/03/09  10:54:24  danner
 * 	Don Lindsay kindly provides us with:
 * 	  Bug fix in comopen() - cleans up chip status.
 * 	  Change in debug routine compr_addr() to print line state first,
 * 	    because touching other things changes the line state.
 * 	  Made comparam() static, since no outside uses.
 * 	  Added several (void)s and fixed some function return types.
 * 	  Changed a return; to return 0; in comparam().
 * 	[93/03/05            af]
 * 
 * Revision 2.12  93/01/24  13:15:06  danner
 * 	[93/01/19  11:03:26  rvb]
 * 
 *	convert com_addr to vm_offset_t.
 * 
 * Revision 2.11  93/01/14  17:30:00  danner
 * 	Always disable fifo in comprobe().
 * 	[92/12/12            dbg]
 * 	Added changes suggested from Finland for FIFOs.
 * 	They still do not work, but we'll get there eventually...
 * 	[92/12/19  10:55:22  af]
 * 
 * 	Disabled FIFOs until we have good code for them.
 * 	Do input buffering at 9600 and over.
 * 	[92/12/10            af]
 * 
 * 	Proper spl typing.
 * 	[92/11/30            af]
 * 
 * Revision 2.10  92/05/22  13:08:34  jfriedl
 * 	Moved disable of FIFO in comprobe().
 * 	From Jordan K. Hubbard <jkh@meepmeep.pcs.com>
 * 
 * Revision 2.9  92/02/19  15:08:12  elf
 * 	Made comprobe more selective. Try to recognize chip.
 * 	[92/01/20            kivinen]
 * 
 * Revision 2.8  92/01/03  20:10:27  dbg
 * 	Don't drop software CARR_ON if carrier drops - modem drops
 * 	carrier but still can talk to machine.
 * 	[91/10/30            dbg]
 * 
 * Revision 2.7  91/10/07  17:25:14  af
 * 	Add some improvements from 2.5 version.
 * 	[91/09/04  22:05:25  rvb]
 * 
 * Revision 2.6  91/08/24  11:57:21  af
 * 	New MI autoconf.
 * 	[91/08/02  02:50:03  af]
 * 
 * Revision 2.5  91/05/14  16:21:14  mrt
 * 	Correcting copyright
 * 
 * Revision 2.4  91/02/14  14:42:06  mrt
 * 	Merge of dbg's latest working com.c onto the old com.c
 * 	with the new autoconf and other major changes.
 * 	[91/01/28  15:26:13  rvb]
 * 
 * Revision 2.3  91/02/05  17:16:33  mrt
 * 	Changed to new Mach copyright
 * 	[91/02/01  17:42:21  mrt]
 * 
 * Revision 2.2  90/11/26  14:49:26  rvb
 * 	jsb beat me to XMK34, sigh ...
 * 	[90/11/26            rvb]
 * 	Apparently first version is r2.2
 * 	[90/11/25  10:44:41  rvb]
 * 
 * 	Synched 2.5 & 3.0 at I386q (r2.3.1.6) & XMK35 (r2.2)
 * 	[90/11/15            rvb]
 * 
 * Revision 2.3.1.5  90/08/25  15:43:06  rvb
 * 	I believe that nothing of the early Olivetti code remains.
 * 	Copyright gone.
 * 	[90/08/21            rvb]
 * 
 * 	Use take_<>_irq() vs direct manipulations of ivect and friends.
 * 	[90/08/20            rvb]
 * 
 * 		Moved and rewrote much of the code to improve performance.
 * 	     Still suffers from overruns.
 * 	[90/08/14            mg32]
 * 
 * Revision 2.3.1.4  90/07/10  11:43:07  rvb
 * 	Rewrote several functions to look more like vax-BSD dh.c.
 * 	[90/06/25            mg32]
 * 
 * 	New style probe/attach.
 * 	Also com_struct has been radically reworked, ...
 * 	[90/06/15            rvb]
 * 
 * Revision 2.3.1.3  90/02/28  15:49:12  rvb
 * 	Fix numerous typo's in Olivetti disclaimer.
 * 	[90/02/28            rvb]
 * 
 * Revision 2.3.1.2  90/01/08  13:32:00  rvb
 * 	Add Olivetti copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 2.3.1.1  89/12/21  18:01:29  rvb
 * 	Changes from Ali Ezzet.
 * 
 * Revision 2.2.0.0  89/07/17  10:39:30  rvb
 * 	New from Olivetti.
 * 
 */

#include <com.h>
#if NCOM > 0

#include <mach/std_types.h>
#include <sys/types.h>
#include <kern/kern_io.h>
#include <kern/time_out.h>
#include <device/conf.h>
#include <device/errno.h>
#include <device/tty.h>
#include <device/io_req.h>

#include <i386/ipl.h>
#include <i386/pio.h>
#include <i386/machspl.h>
#include <chips/busses.h>
#include <i386at/comreg.h>

extern void ttrstrt();

/*
 *	Forward declarations
 */
boolean_t comprobe(
	vm_offset_t	port,
	struct bus_device *dev);
void comattach(
	struct bus_device *dev);
void comintr(
	int unit);
void comstart(
	struct tty *tp);
void fix_modem_state(
	int	unit,
	int	modem_stat);
int commctl(
	struct tty	*tp,
	int	bits,
	int	how);
static void comparam(
	register int unit);
void comtimer(void *);
void comstop(
	register struct tty *tp,
	int	flags);
void commodem_intr(
	int	unit,
	int	stat);
io_return_t comgetstat(
	int		dev,
	dev_flavor_t	flavor,
	dev_status_t	data,
	natural_t	*count);
io_return_t comsetstat(
	int		dev,
	dev_flavor_t	flavor,
	dev_status_t	data,
	natural_t	count);


static vm_offset_t com_std[] = { 0 };
struct bus_device *cominfo[NCOM];
struct bus_driver comdriver = {
	comprobe, 0, comattach, 0, com_std, "com", cominfo, 0, 0, 0};

struct tty com_tty[NCOM];
int commodem[NCOM];
int comcarrier[NCOM] = {0, 0,};
boolean_t comfifo[NCOM];
boolean_t comtimer_active;
int comtimer_state[NCOM];

#ifndef	PORTSELECTOR
#define ISPEED	B9600
#define IFLAGS	(EVENP|ODDP|ECHO|CRMOD)
#else
#define ISPEED	B4800
#define IFLAGS	(EVENP|ODDP)
#endif

unsigned short divisorreg[] = {
	0,	2304,	1536,	1047,		/*     0,    50,    75,   110 */
	857,	 768,	 576,	 384,		/*   134.5, 150,   200,   300 */
	192,					/*   600 */
	 96,	  64,		  48,		/*  1200,  1800,  2000,  2400 */
      		  24,	  	  12,		/*  3600,  4800,  7200,  9600 */
	  6,	   3,	   2};			/* 19200, 38400, 56000 */

/*
 *
 * Probes are called during kernel boot: return 1 to mean that
 * the relevant device is present today.
 *
 */
boolean_t
comprobe(
	vm_offset_t	port,
	struct bus_device *dev)
{
	unsigned short	addr = dev->address;
	int	unit = dev->unit;
	int     oldctl, oldmsb;
	char    *type = "8250";
	int     i;

	if (unit < 0 || unit >= NCOM) {
		printf("com %d out of range\n", unit);
		return FALSE;
	}
	oldctl = inb(LINE_CTL(addr));	 /* Save old value of LINE_CTL */
	oldmsb = inb(BAUD_MSB(addr));	 /* Save old value of BAUD_MSB */
	outb(LINE_CTL(addr), 0);	 /* Select INTR_ENAB */    
	outb(BAUD_MSB(addr), 0);
	if (inb(BAUD_MSB(addr)) != 0)
	  {
	    outb(LINE_CTL(addr), oldctl);
	    outb(BAUD_MSB(addr), oldmsb);
	    return FALSE;
	  }
	outb(LINE_CTL(addr), iDLAB);	 /* Select BAUD_MSB */
	outb(BAUD_MSB(addr), 255);
	if (inb(BAUD_MSB(addr)) != 255)
	  {
	    outb(LINE_CTL(addr), oldctl);
	    outb(BAUD_MSB(addr), oldmsb);
	    return FALSE;
	  }
	outb(LINE_CTL(addr), 0);	 /* Select INTR_ENAB */
	if (inb(BAUD_MSB(addr)) != 0)	 /* Check that it has kept its value*/
	  {
	    outb(LINE_CTL(addr), oldctl);
	    outb(BAUD_MSB(addr), oldmsb);
	    return FALSE;
	  }

	/* Com port found, now check what chip it has */
	
	for(i = 0; i < 256; i++)	 /* Is there Scratch register */
	  {
	    outb(SCR(addr), i);
	    if (inb(SCR(addr)) != i)
	      break;
	  }
	if (i == 256)
	  {				 /* Yes == 450 or 460 */
	    outb(SCR(addr), 0);
	    type = "82450 or 16450";
	    outb(FIFO_CTL(addr), iFIFOENA | iFIFO14CH);	 /* Enable fifo */
	    if ((inb(FIFO_CTL(addr)) & iFIFO14CH) != 0)
	      {				 /* Was it successfull */
		/* if both bits are not set then broken xx550 */
		if ((inb(FIFO_CTL(addr)) & iFIFO14CH) == iFIFO14CH)
		  {
		    type = "82550 or 16550";
		    comfifo[unit] = TRUE;
		  }
		else
		  {
		    type = "82550 or 16550 with non-working FIFO";
		  }
		outb(INTR_ID(addr), 0x00); /* Disable fifos */
	      }
	  }
	printf("com%d: %s chip.\n", unit, type);
	return TRUE;
}

/*
 *
 * Device Attach's are called during kernel boot, but only if the matching
 * device Probe returned a 1.
 *
 */
void comattach(
	struct bus_device *dev)
{
	u_char	unit = dev->unit;
	u_short	addr = dev->address;

	take_dev_irq(dev);
	printf(", port = %x, spl = %d, pic = %d. (DOS COM%d)",
		dev->address, dev->priority, dev->irq, unit+1);

	cominfo[unit] = dev;
/*	comcarrier[unit] = addr->flags;*/
	commodem[unit] = 0;

	outb(INTR_ENAB(addr), 0);
	outb(MODEM_CTL(addr), 0);
	while (!(inb(INTR_ID(addr))&1)) {
		(void) inb(LINE_STAT (addr)); 	/* reset overrun error etc */
		(void) inb(TXRX      (addr)); 	/* reset data-ready */
		(void) inb(MODEM_STAT(addr)); 	/* reset modem status reg */
	}
}

/*
 *	Probe for COM<dev> after autoconfiguration.
 *	Used to handle PCMCIA modems, which may appear
 *	at any time.
 */
boolean_t com_reprobe(
	int	unit)
{
	struct bus_device	*device;

	/*
	 *	Look for COM device <unit> in the device
	 *	initialization list.  It must not be alive
	 *	(otherwise we would have opened it already).
	 */
	for (device = bus_device_init; device->driver; device++) {
	    if (device->driver == &comdriver && device->unit == unit &&
		!device->alive && device->ctlr == (char)-1)
	    {
		/*
		 *	Found an entry for com port <unit>.
		 *	Probe it.
		 */
		if (configure_bus_device(device->name,
					 device->address,
					 device->phys_address,
					 0,
					 "atbus"))
		    return TRUE;
	    }
	}
	return FALSE;
}

io_return_t comopen(
	int	unit,
	int	flag,
	io_req_t ior)
{
	u_short		addr;
	struct bus_device	*isai;
	struct tty	*tp;
	spl_t		s;
	io_return_t	result;

	if (unit >= NCOM)
	    return ENXIO;	/* no such device */
	if ((isai = cominfo[unit]) == 0 || isai->alive == 0) {
	    /*
	     *	Try to probe it again
	     */
	    if (!com_reprobe(unit))
		return ENXIO;
	}
	tp = &com_tty[unit];

	if ((tp->t_state & (TS_ISOPEN|TS_WOPEN)) == 0) {
		ttychars(tp);
		tp->t_addr = (char *)isai->address;
		tp->t_dev = unit;
		tp->t_oproc = comstart;
		tp->t_stop = comstop;
		tp->t_mctl = commctl;
		tp->t_getstat = comgetstat;
		tp->t_setstat = comsetstat;
#ifndef	PORTSELECTOR
		if (tp->t_ispeed == 0) {
#else
			tp->t_state |= TS_HUPCLS;
#endif	/* PORTSELECTOR */
			tp->t_ispeed = ISPEED;
			tp->t_ospeed = ISPEED;
			tp->t_flags = IFLAGS;
			tp->t_state &= ~TS_BUSY;
#ifndef	PORTSELECTOR
		}
#endif	/* PORTSELECTOR */
	}
/*rvb	tp->t_state |= TS_WOPEN; */
	if ((tp->t_state & TS_ISOPEN) == 0)
		comparam(unit);
	addr = (int)tp->t_addr;

	s = spltty();
	if (!comcarrier[unit])	/* not originating */
		tp->t_state |= TS_CARR_ON;
	else {
		int modem_stat = inb(MODEM_STAT(addr));
		if (modem_stat & iRLSD)
			tp->t_state |= TS_CARR_ON;
		else
			tp->t_state &= ~TS_CARR_ON;
		fix_modem_state(unit, modem_stat);
	} 
	splx(s);

	result = char_open(unit, tp, flag, ior);

	if (!comtimer_active) {
		comtimer_active = TRUE;
		comtimer(0);
	}

	s = spltty();
	while(!(inb(INTR_ID(addr))&1)) { /* while pending interrupts */
		(void) inb(LINE_STAT (addr)); /* reset overrun error  */
		(void) inb(TXRX      (addr)); /* reset data-ready	    */
		(void) inb(MODEM_STAT(addr)); /* reset modem status   */
	}
	splx(s);
	return result;
}

io_return_t comclose(
	int	unit,
	int	flag)
{
	struct tty	*tp = &com_tty[unit];
	unsigned short	addr = (int)tp->t_addr;

	ttyclose(tp);
	if (tp->t_state&TS_HUPCLS || (tp->t_state&TS_ISOPEN)==0) { 
		outb(INTR_ENAB(addr), 0);
		outb(MODEM_CTL(addr), 0);
		tp->t_state &= ~TS_BUSY;
		commodem[unit] = 0;
		if (comfifo[unit])
			outb(INTR_ID(addr), 0x00); /* Disable fifos */
	}
	return 0;
}

io_return_t comread(
	int	unit,
	io_req_t ior)
{
	return char_read(&com_tty[unit], ior);
}

io_return_t comwrite(
	int	unit,
	io_req_t ior)
{
	return char_write(&com_tty[unit], ior);
}

io_return_t
comgetstat(
	int		unit,
	dev_flavor_t	flavor,
	dev_status_t	data,		/* pointer to OUT array */
	natural_t	*count)		/* out */
{
	io_return_t	result = D_SUCCESS;

	switch (flavor) {
	case TTY_MODEM:
		fix_modem_state(unit, inb(MODEM_STAT(cominfo[unit]->address)));
		*data = commodem[unit];
		*count = 1;
		break;
	default:
		result = tty_get_status(&com_tty[unit], flavor, data, count);
		break;
	}
	return result;
}

io_return_t
comsetstat(
	int		unit,
	dev_flavor_t	flavor,
	dev_status_t	data,
	natural_t	count)
{
	io_return_t	result = D_SUCCESS;
	struct tty	*tp = &com_tty[unit];

	switch (flavor) {
	case TTY_SET_BREAK:
		commctl(tp, TM_BRK, DMBIS);
		break;
	case TTY_CLEAR_BREAK:
		commctl(tp, TM_BRK, DMBIC);
		break;
	case TTY_MODEM:
		commctl(tp, *data, DMSET);
		break;
	default:
		result = tty_set_status(&com_tty[unit], flavor, data, count);
		if (result == D_SUCCESS && flavor == TTY_STATUS)
			comparam(unit);
		return result;
	}
	return D_SUCCESS;
}

void comintr(
	int unit)
{
	register struct tty	*tp = &com_tty[unit];
	u_short			addr = cominfo[unit]->address;
	static char 		comoverrun = 0;
	char			c, line, intr_id;
	int			line_stat;

	while (! ((intr_id=(inb(INTR_ID(addr))&MASKi)) & 1))
	    switch (intr_id) { 
		case MODi: 
		    /* modem change */
			commodem_intr(unit, inb(MODEM_STAT(addr)));
			break;

		case TRAi:
			comtimer_state[unit] = 0;
			tp->t_state &= ~(TS_BUSY|TS_FLUSH);
			tt_write_wakeup(tp);
			comstart(tp);
			break;
		case RECi:
		case CTIi:         /* Character timeout indication */
			if (tp->t_state&TS_ISOPEN) {
				while ((line = inb(LINE_STAT(addr))) & iDR) {
					c = inb(TXRX(addr));
					ttyinput(c, tp);
				}
			} else
				tt_open_wakeup(tp);
			break;
		case LINi: 
			line_stat = inb(LINE_STAT(addr));

			if ((line_stat & iPE) &&
			    ((tp->t_flags&(EVENP|ODDP)) == EVENP ||
			     (tp->t_flags&(EVENP|ODDP)) == ODDP)) {
				/* parity error */;
			} else 	if (line&iOR && !comoverrun) {
				printf("com%d: overrun\n", unit);
				comoverrun = 1;
			} else if (line_stat & (iFE | iBRKINTR)) {
				/* framing error or break */
				ttyinput(tp->t_breakc, tp);
			}
			break;
		}
}

static void
comparam(
	register int unit)
{
	struct tty	*tp = &com_tty[unit];
	u_short		addr = (int)tp->t_addr;
	spl_t		s = spltty();
	int		mode;

        if (tp->t_ispeed == B0) {
		tp->t_state |= TS_HUPCLS;
		outb(MODEM_CTL(addr), iOUT2);
		commodem[unit] = 0;
		splx(s);
		return;
	}

	/* Do input buffering */
	if (tp->t_ispeed >= B300)
		tp->t_state |= TS_MIN;

	outb(LINE_CTL(addr), iDLAB);
	outb(BAUD_LSB(addr), divisorreg[tp->t_ispeed] & 0xff);
	outb(BAUD_MSB(addr), divisorreg[tp->t_ispeed] >> 8);

	if (tp->t_flags & (RAW|LITOUT|PASS8))
		mode = i8BITS;
	else
		mode = i7BITS | iPEN;
	if (tp->t_flags & EVENP)
		mode |= iEPS;
	if (tp->t_ispeed == B110)
		/*
		 * 110 baud uses two stop bits -
		 * all other speeds use one
		 */
		mode |= iSTB;

	outb(LINE_CTL(addr), mode);

	outb(INTR_ENAB(addr), iTX_ENAB|iRX_ENAB|iMODEM_ENAB|iERROR_ENAB);
	if (comfifo[unit])
		outb(FIFO_CTL(addr), iFIFOENA|iFIFO14CH);
	outb(MODEM_CTL(addr), iDTR|iRTS|iOUT2);
	commodem[unit] |= (TM_DTR|TM_RTS);
        splx(s);
}

void computc(char ch, int unit)
{
	u_short addr = (u_short)(cominfo[unit]->address);

	/* send the char */
	outb(addr, ch);

	/* wait for transmitter to empty */
	while((inb(LINE_STAT(addr)) & iTHRE) == 0);	
}

int comgetc(int unit)
{
	u_short		addr = (u_short)(cominfo[unit]->address);
	spl_t		s = spltty();
	natural_t	c;

	while((inb(LINE_STAT(addr)) & iDR) == 0) ;

	c = inb(TXRX(addr));
	splx(s);
	return c;
}

void comparm(int unit, int baud, int intr, int mode, int modem)
{
	u_short addr = (u_short)(cominfo[unit]->address);
	spl_t	s = spltty();

	if (unit != 0 && unit != 1) {
		printf("comparm(unit, baud, mode, intr, modem)\n");
		splx(s);
		return;
	}
	outb(LINE_CTL(addr), iDLAB);
	outb(BAUD_LSB(addr), divisorreg[baud] & 0xff);
	outb(BAUD_MSB(addr), divisorreg[baud] >> 8);
	outb(LINE_CTL(addr), mode);
	outb(INTR_ENAB(addr), intr);
	outb(MODEM_CTL(addr), modem);
	splx(s);
}

int comst_1, comst_2, comst_3, comst_4, comst_5 = 14;

void comstart(
	struct tty *tp)
{
	char nch;
#if 0
	int i;
#endif

	if (tp->t_state & (TS_TIMEOUT|TS_TTSTOP|TS_BUSY)) {
comst_1++;
		return;
	}
	if ((!queue_empty(&tp->t_delayed_write)) &&
	    (tp->t_outq.c_cc <= TTLOWAT(tp))) {
comst_2++;
		tt_write_wakeup(tp);
	}
	if (!tp->t_outq.c_cc) {
comst_3++;
		return;
	}

#if 0
	i = (comfifo[minor(tp->t_dev)]) ? /*14*/comst_5 : 1;

	tp->t_state |= TS_BUSY;
	while (i-- > 0) {
		nch = getc(&tp->t_outq);
		if (nch == -1) break;
		if ((nch & 0200) && ((tp->t_flags & LITOUT) == 0)) {
		    timeout(ttrstrt, (char *)tp, (nch & 0x7f) + 6);
		    tp->t_state |= TS_TIMEOUT;
comst_4++;
		    return;
		}
		outb(TXRX((int)tp->t_addr), nch);
	}
#else
	nch = getc(&tp->t_outq);
	if ((nch & 0200) && ((tp->t_flags & LITOUT) == 0)) {
	    timeout(ttrstrt, (char *)tp, (nch & 0x7f) + 6);
	    tp->t_state |= TS_TIMEOUT;
comst_4++;
	    return;
	}
	outb(TXRX((int)tp->t_addr), nch);
	tp->t_state |= TS_BUSY;
#endif
	return;
}

/* Check for stuck xmitters */
int comtimer_interval = 5;

void comtimer(void *param)
{
	spl_t	s = spltty();
	struct tty *tp = com_tty;
	int i, nch;

	for (i = 0; i < NCOM; i++, tp++) {
		if ((tp->t_state & TS_ISOPEN) == 0)
			continue;
		if (!tp->t_outq.c_cc)
			continue;
		if (++comtimer_state[i] < 2)
			continue;
		/* Its stuck */
printf("Tty %#x was stuck\n", (vm_offset_t)tp);
		nch = getc(&tp->t_outq);
		outb(TXRX((int)tp->t_addr), nch);
	}

	splx(s);
	timeout(comtimer, 0, comtimer_interval*hz);
}

/*
 * Set receive modem state from modem status register.
 */
void fix_modem_state(
	int	unit,
	int	modem_stat)
{
	int	stat = 0;

	if (modem_stat & iCTS)
	    stat |= TM_CTS;	/* clear to send */
	if (modem_stat & iDSR)
	    stat |= TM_DSR;	/* data set ready */
	if (modem_stat & iRI)
	    stat |= TM_RNG;	/* ring indicator */
	if (modem_stat & iRLSD)
	    stat |= TM_CAR;	/* carrier? */

	commodem[unit] = (commodem[unit] & ~(TM_CTS|TM_DSR|TM_RNG|TM_CAR))
				| stat;
}

/*
 * Modem change (input signals)
 */
void commodem_intr(
	int	unit,
	int	stat)
{
	int	changed;

	changed = commodem[unit];
	fix_modem_state(unit, stat);
	stat = commodem[unit];

	/* Assumption: if the other party can handle
	   modem signals then it should handle all
	   the necessary ones. Else fix the cable. */

	changed ^= stat;	/* what changed ? */

	if (changed & TM_CTS)
		tty_cts( &com_tty[unit], stat & TM_CTS );

#if 0
	if (changed & TM_CAR)
		ttymodem( &com_tty[unit], stat & TM_CAR );
#endif

}

/*
 * Set/get modem bits
 */
int commctl(
	register struct tty	*tp,
	int	bits,
	int	how)
{
	spl_t		s;
	int		unit;
	vm_offset_t	dev_addr;
	register int	b;

	unit = minor(tp->t_dev);

	if (bits == TM_HUP) { /* close line (internal) */
		bits = TM_DTR | TM_RTS;
		how = DMBIC;
	}

	if (how == DMGET) return commodem[unit];

	dev_addr = cominfo[unit]->address;

	s = spltty();

	switch (how) {
	case DMSET:
		b = bits; break;
	case DMBIS:
		b = commodem[unit] | bits; break;
	case DMBIC:
		b = commodem[unit] & ~bits; break;
	}
	commodem[unit] = b;

	if (bits & TM_BRK) {
		if (b & TM_BRK) {
			outb(LINE_CTL(dev_addr), inb(LINE_CTL(dev_addr)) | iSETBREAK);
		} else {
			outb(LINE_CTL(dev_addr), inb(LINE_CTL(dev_addr)) & ~iSETBREAK);
		}
	}

#if 0
	/* do I need to do something on this ? */
	if (bits & TM_LE) {	/* line enable */
	}
#endif
#if 0
	/* Unsupported */
	if (bits & TM_ST) {	/* secondary transmit */
	}
	if (bits & TM_SR) {	/* secondary receive */
	}
#endif
	if (bits & (TM_DTR|TM_RTS)) {	/* data terminal ready, request to send */
		how = iOUT2;
		if (b & TM_DTR) how |= iDTR;
		if (b & TM_RTS) how |= iRTS;
		outb(MODEM_CTL(dev_addr), how);
	}

	splx(s);

	/* the rest are inputs */
	return commodem[unit];
}

void comstop(
	register struct tty *tp,
	int	flags)
{
	if ((tp->t_state & TS_BUSY) && (tp->t_state & TS_TTSTOP) == 0)
	    tp->t_state |= TS_FLUSH;
}

/*
 *
 * Code to be called from debugger.
 *
 */
void compr_addr(int addr)
{
	/* The two line_stat prints may show different values, since
	*  touching some of the registers constitutes changing them.
	*/
	printf("LINE_STAT(%x) %x\n",
		LINE_STAT(addr), inb(LINE_STAT(addr)));

	printf("TXRX(%x) %x, INTR_ENAB(%x) %x, INTR_ID(%x) %x, LINE_CTL(%x) %x,\n\
MODEM_CTL(%x) %x, LINE_STAT(%x) %x, MODEM_STAT(%x) %x\n",
	TXRX(addr), 	 inb(TXRX(addr)),
	INTR_ENAB(addr), inb(INTR_ENAB(addr)),
	INTR_ID(addr), 	 inb(INTR_ID(addr)),
	LINE_CTL(addr),  inb(LINE_CTL(addr)),
	MODEM_CTL(addr), inb(MODEM_CTL(addr)),
	LINE_STAT(addr), inb(LINE_STAT(addr)),
	MODEM_STAT(addr),inb(MODEM_STAT(addr)));
}

int compr(int unit)
{
	compr_addr(cominfo[unit]->address);
	return(0);
}

int rcline = -1;
int rcbaud = B9600;
void comrc_put(
	int	ch)
{
    static int		opened = 0;
    u_short		addr;

    if (cominfo[rcline] == 0) return;

    addr = (u_short)(cominfo[rcline]->address);

    if (!opened) {	/* whap down chip config for rconsole */
	int	mode = i7BITS | iPEN;

	opened = 1;
	outb(LINE_CTL(addr), iDLAB);
	outb(BAUD_LSB(addr), divisorreg[rcbaud] & 0xff);
	outb(BAUD_MSB(addr), divisorreg[rcbaud] >>8);
	outb(LINE_CTL(addr), mode);
	outb(INTR_ENAB(addr), 0);
	outb(MODEM_CTL(addr), iDTR|iRTS|iOUT2);
    }

    /* wait for transmitter to empty */
    while((inb(LINE_STAT(addr)) & iTHRE) == 0);	
    /* send the char */
    outb(addr, ch);
}

int comrc_may(
	boolean_t	wait)
{
    unsigned char	c;
    u_short		addr;

    if (cominfo[rcline] == 0) return -1;

    addr = (u_short)(cominfo[rcline]->address);

    if ((inb(LINE_STAT(addr)) & iDR) == 0) {
	    return -1;
    }

    c = inb(TXRX(addr));
    return (c & 0x7f);
}

int
comrc_get(
	boolean_t	wait)
{
    unsigned char	c;
    u_short		addr;


    addr = (u_short)(cominfo[rcline]->address);

    while((inb(LINE_STAT(addr)) & iDR) == 0) {
	if (!wait)
	    return -1;
    }

    c = inb(TXRX(addr));
    return (c & 0x7f);
}

#endif	/* NCOM */
