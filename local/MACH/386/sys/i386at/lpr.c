/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	lpr.c,v $
 * Revision 2.1.1.2  91/07/15  00:16:56  rvb
 * 	Don't set UNUSED bits in intr_enable.
 * 	[91/06/27            mg32]
 * 
 * Revision 2.1.1.1  90/08/25  15:43:25  rvb
 * 	Use take_<>_irq() vs direct manipulations of ivect and friends.
 * 	[90/08/20            rvb]
 * 
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
  
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/systm.h>
#include <sys/uio.h>
#include <sys/file.h>
  
#include <i386/ipl.h>
#include <i386/pio.h>
#include <i386at/atbus.h>
#include <i386at/lprreg.h>
  
#if NPAR > 0
extern int	parattach();
#endif

extern void 	splx();
extern int	spltty();
extern void 	timeout();
extern void 	ttrstrt();

/* 
 * Driver information for auto-configuration stuff.
 */

int 	lprprobe(), lprattach(), lprintr(), lprstart(), lprstop();

int (*lprintrs[])() = {lprintr, 0};
struct isa_driver lprdriver = {lprprobe, 0, lprattach, "lpr", 0, 0, 0};
struct isa_dev *lprinfo[NLPR];
     
struct tty	lpr_tty[NLPR];
     
int lprprobe(dev)
     struct isa_dev *dev;
{
  outb(INTR_ENAB(dev->dev_addr),0x07);
  outb(DATA(dev->dev_addr),0x00);
  return(!inb(DATA(dev->dev_addr)));
}

int lprattach(dev)
     struct isa_dev *dev;
{
  u_char unit = dev->dev_unit;
  struct tty *tp = &lpr_tty[unit];
  caddr_t addr = dev->dev_addr;

  take_dev_irq(dev);
  printf("lpr%d: port = %x, spl = %d, pic = %d.\n",
	 unit, dev->dev_addr, dev->dev_spl, dev->dev_pic);
  lprinfo[unit] = dev;
  
  outb(INTR_ENAB(addr), inb(INTR_ENAB(addr)) & 0x0f);
#if NPAR > 0
  parattach(dev);
#endif
  return;
}

int lpropen(dev, flag)
     int dev;
     int flag;
{
  int unit = minor(dev);
  struct isa_dev *isai;
  struct tty *tp;
  caddr_t addr;
  
  if (unit >= NLPR || (isai = lprinfo[unit]) == 0 || isai->dev_alive == 0)
    return(ENXIO);
  tp = &lpr_tty[unit];
  if (tp->t_state & TS_XCLUDE && u.u_uid != 0)
    return(EBUSY);
  addr = isai->dev_addr;
  tp->t_dev = dev;
  tp->t_addr = addr;
  tp->t_oproc = lprstart;
  tp->t_state |= TS_WOPEN;
  if ((tp->t_state & TS_ISOPEN) == 0)
    ttychars(tp);
  outb(INTR_ENAB(addr), inb(INTR_ENAB(addr)) | 0x10);
  tp->t_state |= TS_CARR_ON;
  return ((*linesw[tp->t_line].l_open)(dev, tp));
}

int lprclose(dev, flag)
     int dev;
     int flag;
{
  int 		unit = minor(dev);
  struct	tty	*tp = &lpr_tty[unit];
  caddr_t		addr = 	lprinfo[unit]->dev_addr;
  
  (*linesw[tp->t_line].l_close)(tp);
  ttyclose(tp);
  if (tp->t_state&TS_HUPCLS || (tp->t_state&TS_ISOPEN)==0) {
    outb(INTR_ENAB(addr), inb(INTR_ENAB(addr)) & 0x0f);
  } 
}

int lprwrite(dev, uio)
     int dev;
     struct uio *uio;
{
  struct tty *tp= &lpr_tty[minor(dev)];
  
  return ((*linesw[tp->t_line].l_write)(tp, uio));
}

int lprioctl(dev, cmd, addr, mode)
     int dev;
     int cmd;
     caddr_t addr;
     int mode;
{
  int s, error;
  int unit = minor(dev);
  struct tty *tp = &lpr_tty[unit];
  
  error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, addr,mode);
  if (error >= 0)
    return(error);
  error = ttioctl(tp, cmd, addr,mode);
  if (error >= 0)
    return (error);
  s = spltty();
  switch (cmd) {
  default:
    splx(s);
    return(ENOTTY);
  }
  splx(s);
  return(0);
}

int lprintr(unit)
     int unit;
{
  register struct tty *tp = &lpr_tty[unit];
  int s;
  
  s = spltty();
  tp->t_state &= ~TS_BUSY;
  if (tp->t_state&TS_FLUSH)
    tp->t_state &=~TS_FLUSH;
  if (tp->t_line)
    (*linesw[tp->t_line].l_start)(tp);
  else
    lprstart(tp);
  splx(s);
}   

int lprstart(tp)
     struct tty *tp;
{
  int s = spltty();
  caddr_t addr = (caddr_t)tp->t_addr;
  int status = inb(STATUS(addr));
  char nch;
  
  if (tp->t_state & (TS_TIMEOUT|TS_TTSTOP|TS_BUSY)) {
    splx(s);
    return(0);
  }

  if (status & 0x20) {
    printf("Printer out of paper!\n");
    splx(s);
    return(0);
  }

  if (tp->t_outq.c_cc <= TTLOWAT(tp)) {
    if (tp->t_state & TS_ASLEEP) {
      tp->t_state &= ~TS_ASLEEP;
      wakeup ((caddr_t)&tp->t_outq);
    }
    if (tp->t_wsel) {
      selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
      tp->t_wsel = 0;
      tp->t_state &= ~TS_WCOLL;
    }
  }
  if (tp->t_outq.c_cc == 0) {
    splx(s);
    return(0);
  }
  if (tp->t_flags & (RAW|LITOUT))
    nch = ndqb(&tp->t_outq,0);
  else {
    nch = ndqb(&tp->t_outq, 0200);
    if (nch == 0) {
      nch = getc(&tp->t_outq);
      timeout(ttrstrt,(caddr_t)tp,(nch&0x7f)+6);
      tp->t_state |= TS_TIMEOUT;
      splx(s);
      return(0);
    }
  }
  if (nch) {
    nch=getc(&tp->t_outq);
      outb(DATA(addr), nch);
      outb(INTR_ENAB(addr),inb(INTR_ENAB(addr)) | 0x01);
      outb(INTR_ENAB(addr),inb(INTR_ENAB(addr)) & 0x1e);
    tp->t_state |= TS_BUSY;
  }
  splx(s);
  return(0);
}

int lprstop(tp, flag)
     struct tty *tp;
{
  int s = spltty();
  
  if ((tp->t_state&TS_BUSY) && (!(tp->t_state&TS_TTSTOP)))
      tp->t_state |= TS_FLUSH;
  splx(s);
}

lprpr(unit)
{
  lprpr_addr(lprinfo[unit]->dev_addr);
  return 0;
}

lprpr_addr(addr)
{
  printf("DATA(%x) %x, STATUS(%x) %x, INTR_ENAB(%x) %x\n",
	 DATA(addr), inb(DATA(addr)),
	 STATUS(addr), inb(STATUS(addr)),
	 INTR_ENAB(addr), inb(INTR_ENAB(addr)));
}
#endif NLPR
