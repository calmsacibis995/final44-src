/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	com.c,v $
 * Revision 2.3.1.7  91/07/15  00:16:34  rvb
 * 	USER CONTRIBUTED reworking of Parity checking code.
 * 	Add ser device.
 * 	[91/06/27            mg32]
 * 
 * Revision 2.3.1.6  90/11/27  13:41:25  rvb
 * 	Synched 2.5 & 3.0 at I386q (r2.3.1.6) & XMK35 (r2.1)
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
#include <ser.h>

#ifdef	MACH_KERNEL
#include <sys/types.h>
#include <sys/time.h>
#include <device/conf.h>
#include <device/errno.h>
#include <device/tty.h>
#include <device/io_req.h>
#else	MACH_KERNEL
#include <sys/conf.h>
#include <sys/user.h>
#include <sys/tty.h>
#endif	MACH_KERNEL

#include <i386/ipl.h>
#include <i386/pio.h>
#include <i386at/atbus.h>
#include <i386at/comreg.h>

#if NSER > 0
extern int serattach();
#endif

extern void timeout(), ttrstrt();

int comprobe(), comattach(), comintr(), comstart();
void comparam();

int (*comintrs[])() = {comintr, 0};
struct isa_driver comdriver = {comprobe, 0, comattach, "com", 0, 0, 0};
struct isa_dev *cominfo[NCOM];
     
#ifndef	PORTSELECTOR
#define ISPEED	B9600
#define IFLAGS	(EVENP|ODDP|ECHO|CRMOD)
#else
#define ISPEED	B4800
#define IFLAGS	(EVENP|ODDP)
#endif
     
struct tty com_tty[NCOM];
     
u_short divisorreg[] = {
	0,	2304,	1536,	1047,		/*     0,    50,    75,   110*/
	857,	 768,	 576,	 384,	 192,	/*   134.5, 150,   200,   300,   600*/
	 96,	  64,		  48,		/*  1200,  1800,  2000,  2400 */
      		  24,	  	  12,		/*  3600,  4800,  7200,  9600 */
	  6,	   3,	   2};			/* 19200, 38400, 56000 */
     
int comprobe(dev)
     struct isa_dev *dev;
{
  caddr_t addr = dev->dev_addr;
  int	  unit = dev->dev_unit;

  if ((unit < 0) || (unit > NCOM)) {
    printf("com %d out of range\n", unit);
    return(0);
  }
  outb(INTR_ENAB(addr), 0);
  return(!inb(INTR_ENAB(addr)));
}

int comattach(dev)
     struct isa_dev *dev;
{
  u_char unit = dev->dev_unit;
  caddr_t addr = dev->dev_addr;
  
  take_dev_irq(dev);
  printf("com%d: port = %x, spl = %d, pic = %d. (DOS COM%d)\n",
	 unit, dev->dev_addr, dev->dev_spl, dev->dev_pic, unit+1);

  cominfo[unit] = dev;
  
  outb(INTR_ENAB(addr), 0);
  outb(MODEM_CTL(addr), 0);
  while (!(inb(INTR_ID(addr))&1)) {
    inb(LINE_STAT(addr)); inb(TXRX(addr)); inb(MODEM_STAT(addr)); }
#if NSER > 0
  serattach(dev);
#endif
}

int comopen(dev, flag, ior)
     int dev;
     int flag;
#ifdef	MACH_KERNEL
     io_req_t ior;
#else	MACH_KERNEL
#endif	MACH_KERNEL
{
  int unit = minor(dev);
  struct isa_dev *isai;
  struct tty *tp;
#ifdef	MACH_KERNEL
  int	comstop();
#endif	MACH_KERNEL
  
  if (unit >= NCOM || (isai = cominfo[unit]) == 0 || isai->dev_alive == 0)
    return(ENXIO);
  tp = &com_tty[unit];
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
  if (tp->t_state & TS_XCLUDE && u.u_uid != 0)
    return(EBUSY);
#endif	MACH_KERNEL
  tp->t_addr = isai->dev_addr;
  tp->t_dev = dev;
  tp->t_oproc = comstart;
#ifdef	MACH_KERNEL
  tp->t_stop = comstop;
#endif	MACH_KERNEL
  tp->t_state |= TS_WOPEN;
  
  if ((tp->t_state & TS_ISOPEN) == 0) {
    ttychars(tp);
#ifndef	PORTSELECTOR
    if (tp->t_ispeed == 0) {
#else
      tp->t_state |= TS_HUPCLS;
#endif	PORTSELECTOR
      tp->t_ispeed = ISPEED;
      tp->t_ospeed = ISPEED;
      tp->t_flags = IFLAGS;
#ifndef	PORTSELECTOR
    }
#endif	PORTSELECTOR
    comparam(unit);
  }
  tp->t_state |= TS_CARR_ON;

#ifdef	MACH_KERNEL
	return (char_open(dev, tp, flag, ior));
#else	MACH_KERNEL
  return ((*linesw[tp->t_line].l_open)(dev, tp));
#endif	MACH_KERNEL
}

int comclose(dev, flag)
     int dev;
     int flag;
{
  struct tty *tp = &com_tty[minor(dev)];
  caddr_t addr = tp->t_addr;
  
#ifdef	MACH_KERNEL
  {
    int	s = spltty();
    simple_lock(&tp->t_lock);
    ttyclose(tp);
    simple_unlock(&tp->t_lock);
    splx(s);
  }
#else	MACH_KERNEL
  (*linesw[tp->t_line].l_close)(tp);
#endif	MACH_KERNEL
  ttyclose(tp);
  if (tp->t_state&TS_HUPCLS || (tp->t_state&TS_ISOPEN)==0) { 
    tp->t_ispeed = 0;
    outb(INTR_ENAB(addr), 0);
    outb(MODEM_CTL(addr), 0);
  } 
}

int comread(dev, uio)
     int dev;
     struct uio *uio;
{
  struct tty *tp= &com_tty[minor(dev)];
  return ((*linesw[tp->t_line].l_read)(tp, uio));
}

int comwrite(dev, uio)
     int dev;
     struct uio *uio;
{
  struct tty *tp= &com_tty[minor(dev)];
  return ((*linesw[tp->t_line].l_write)(tp, uio));
}

#ifdef	MACH_KERNEL
comportdeath(dev, port)
     dev_t		dev;
     mach_port_t	port;
{
  return (tty_portdeath(&com_tty[minor(dev)], port));
}

io_return_t comgetstat(dev, flavor, data, count)
     dev_t		dev;
     int		flavor;
     int *		data;		/* pointer to OUT array */
     unsigned int	*count;		/* out */
{
	io_return_t	result;

	switch (flavor) {
	    default:
		result = tty_get_status(&com_tty, flavor, data, count);
		break;
	}
	return (result);
}

io_return_t comsetstat(dev, flavor, data, count)
     dev_t		dev;
     int		flavor;
     int *		data;
     unsigned int	count;
{
	io_return_t	result;
	int unit = minor(dev);
	caddr_t dev_addr = cominfo[unit]->dev_addr;

	switch (flavor) {
/*	case TIOCSETP:
	case TIOCSETN:
	case TIOCLBIS:
	case TIOCLBIC:
	case TIOCLSET:
		comparam(unit);
		break;
*/	case TTY_SET_BREAK:
		outb(LINE_CTL(dev_addr), inb(LINE_CTL(dev_addr)) | iSETBREAK); break;
	case TTY_CLEAR_BREAK:
		outb(LINE_CTL(dev_addr), inb(LINE_CTL(dev_addr)) & ~iSETBREAK); break;
/*	case TIOCSDTR:
		outb(MODEM_CTL(dev_addr), iOUT2|iDTR|iRTS); break;
	case TIOCCDTR:
		outb(MODEM_CTL(dev_addr), iOUT2|iRTS); break;
*/	}
	switch (flavor) {
	    default:
		result = tty_set_status(&com_tty, flavor, data, count);
	}
	comparam(unit);		/* ??? */
	return (result);
}
#else	MACH_KERNEL
int comioctl(dev, cmd, addr, mode)
     int dev;
     int cmd;
     caddr_t addr;
     int mode;
{
  int error;
  int unit = minor(dev);
  struct tty *tp = &com_tty[unit];
  caddr_t dev_addr = cominfo[unit]->dev_addr;
  
  error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, addr,mode);
  if (error >= 0)
    return(error);
  error = ttioctl(tp, cmd, addr,mode);
  if (error >= 0) {
    if (cmd == TIOCSETP || cmd == TIOCSETN || cmd == TIOCLBIS ||
	cmd == TIOCLBIC || cmd == TIOCLSET)
      comparam(unit);
    return (error);
  }
  switch (cmd) {
  case TIOCSBRK:
    outb(LINE_CTL(dev_addr), inb(LINE_CTL(dev_addr)) | iSETBREAK); break;
  case TIOCCBRK:
    outb(LINE_CTL(dev_addr), inb(LINE_CTL(dev_addr)) & ~iSETBREAK); break;
  case TIOCSDTR:
    outb(MODEM_CTL(dev_addr), iOUT2|iDTR|iRTS); break;
  case TIOCCDTR:
    outb(MODEM_CTL(dev_addr), iOUT2|iRTS); break;
  case TIOCMSET:
  case TIOCMBIS:
  case TIOCMBIC:
  case TIOCMGET:
    uprintf("modem control not yet implemented\n");
  default:
    return(ENOTTY);
  }
  return(0);
}
#endif	MACH_KERNEL

int comintr(unit)
     int unit;
{
  register struct tty *tp = &com_tty[unit];
  caddr_t addr = cominfo[unit]->dev_addr;
  static char comoverrun = 0;
  char c, line, intr_id;
  while (!((intr_id=inb(INTR_ID(addr))) &1))
    switch (intr_id) { 
    case MODi: inb(MODEM_STAT(addr)); break;
    case TRAi:
      tp->t_state &= ~TS_BUSY;
      if (tp->t_state&TS_FLUSH)
	tp->t_state &=~TS_FLUSH;
      if (tp->t_line)
	(*linesw[tp->t_line].l_start)(tp);
      else
	comstart(tp);
      break;
    case RECi:
      if (tp->t_state&TS_ISOPEN) {
	c = inb(TXRX(addr));
	line = inb(LINE_STAT(addr));
	if (line&iPE &&
	    ((tp->t_flags&(EVENP|ODDP)) == EVENP ||
	     (tp->t_flags&(EVENP|ODDP)) == ODDP)) break;
	if (line&iOR && !comoverrun) {
	  printf("com%d: overrun\n", unit);
	  comoverrun = 1;
	} 
	if (line&(iFE|iBRKINTR))
	    /*
	     * At framing error (break) generate
	     * a null (in raw mode, for getty), or a
	     * interrupt (in cooked/cbreak mode).
	     */
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
	    c = (tp->t_flags&RAW?0:tp->t_intrc);
#endif	MACH_KERNEL
	  (*linesw[tp->t_line].l_rint)(c, tp);
      }
      else
#ifdef	MACH_KERNEL
	/* */;
#else	MACH_KERNEL
	wakeup((caddr_t)&tp->t_rawq);
#endif	MACH_KERNEL
      break;
    case LINi: inb(LINE_STAT(addr)); break;
    }
}

void comparam(unit)
     register int unit;
{
  struct tty *tp = &com_tty[unit];
  caddr_t addr = tp->t_addr;
  
  outb(LINE_CTL(addr), iDLAB);
  outb(BAUD_LSB(addr), divisorreg[tp->t_ispeed] & 0xff);
  outb(BAUD_MSB(addr), divisorreg[tp->t_ispeed] >>8);
  outb(LINE_CTL(addr), ((tp->t_flags&(RAW|LITOUT|PASS8)?i8BITS:i7BITS|iPEN) | 
			tp->t_flags>>3&0x10));
  outb(INTR_ENAB(addr), iTX_ENAB|iRX_ENAB);
  outb(MODEM_CTL(addr), iDTR|iRTS|iOUT2);
}

int comstart(tp)
     struct tty *tp;
{
  char nch;

  /*
   * The line below is a hack.  It seems that under SLIP, we sometimes lose
   * interrupts, sigh.  Someday, this should be fixed.  It also may be that
   * only certain machines manifest this problem.
   */
  comintr(minor(tp->t_dev));

  if (tp->t_state & (TS_TIMEOUT|TS_TTSTOP|TS_BUSY)) {
    return(0);
  }
  if (tp->t_outq.c_cc <= TTLOWAT(tp)) {
#ifdef	MACH_KERNEL
  tt_write_wakeup(tp);
#else	MACH_KERNEL
    if (tp->t_state & TS_ASLEEP) {
      tp->t_state &= ~TS_ASLEEP;
      wakeup ((caddr_t)&tp->t_outq);
    }
    if (tp->t_wsel) {
      selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
      tp->t_wsel = 0;
      tp->t_state &= ~TS_WCOLL;
    }
#endif	MACH_KERNEL
  }
  if (!tp->t_outq.c_cc) {
    return(0);
  }
  if (tp->t_flags & (RAW|LITOUT))
    nch = ndqb(&tp->t_outq,0);
  else {
    nch = ndqb(&tp->t_outq, 0200);
    if (!nch) {
      nch = getc(&tp->t_outq);
      timeout(ttrstrt,(caddr_t)tp,(nch&0x7f)+6);
      tp->t_state |= TS_TIMEOUT;
      return(0);
    }
  }
  if (nch) {
    outb(TXRX(tp->t_addr), getc(&tp->t_outq));
    tp->t_state |= TS_BUSY;
  }
  else
    tp->t_state &= ~TS_BUSY;
  return(0);
}

#ifdef	MACH_KERNEL
comstop(tp, flags)
	register struct tty *tp;
	int	flags;
{
	/*
	 * do nothing - all characters are output by one call to
	 * kdstart.
	 */
}
#else	MACH_KERNEL
int comstop(tp, flag)
     struct tty *tp;
{
  int s = spltty();
  if ((tp->t_state&TS_BUSY) && (!(tp->t_state&TS_TTSTOP)))
    tp->t_state |= TS_FLUSH;
  splx(s);
}
#endif	MACH_KERNEL

compr(unit)
{
  compr_addr(cominfo[unit]->dev_addr);
  return(0);
}

compr_addr(addr)
{
  printf("TXRX(%x) %x, INTR_ENAB(%x) %x, INTR_ID(%x) %x, LINE_CTL(%x) %x,\n\
MODEM_CTL(%x) %x, LINE_STAT(%x) %x, MODEM_STAT(%x) %x\n",
	 TXRX(addr), inb(TXRX(addr)),
	 INTR_ENAB(addr), inb(INTR_ENAB(addr)),
	 INTR_ID(addr), inb(INTR_ID(addr)),
	 LINE_CTL(addr), inb(LINE_CTL(addr)),
	 MODEM_CTL(addr), inb(MODEM_CTL(addr)),
	 LINE_STAT(addr), inb(LINE_STAT(addr)),
	 MODEM_STAT(addr), inb(MODEM_STAT(addr)));
}
#endif NCOM
