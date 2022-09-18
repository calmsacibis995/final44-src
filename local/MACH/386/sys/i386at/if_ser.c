/*
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_ser.c,v $
 * Revision 2.1.1.1  91/07/14  23:54:35  rvb
 * 	Created from if_par.c
 * 	[91/06/27            mg32]
 * 
 */

/* 
 *	Serial port network driver v1.0
 */ 

#include <ser.h>
#if NSER > 0

#include <sys/proc.h>

#include <i386/ipl.h>
#include <i386/pio.h>
#include <i386at/atbus.h>
#include <i386at/comreg.h>
#define MAXSPIN		5000
#define SERMTU		8192
#define SPLNET		spl6

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>

#include <net/if.h>
#include <net/netisr.h>
#include <netinet/in.h>
#include <netinet/in_var.h>

int foo = 0;

#define off(addr) {outb(INTR_ENAB(addr),0x00);outb(MODEM_CTL(addr),0x00);}
#define on(addr) {inb(MODEM_STAT(addr));outb(MODEM_CTL(addr),iOUT2);outb(INTR_ENAB(addr),iMODEM_ENAB);}

int serintr();
int serioctl();
int serattach();
int seroutput();

int (*oldvect)();
int oldunit;

extern struct isa_dev *cominfo[];

struct ser_softc {
  struct ifnet sc_if;
  char sc_buf[SERMTU+sizeof(struct ifnet *)];
} ser_softc[NSER];

void serintoff(unit)
     int unit;
{
  off(cominfo[unit]->dev_pic);
  ser_softc[unit].sc_if.if_flags &= ~IFF_RUNNING;
  ivect[cominfo[unit]->dev_pic]=oldvect;
  iunit[cominfo[unit]->dev_pic]=oldunit;
}

void serinit(unit)
     int unit;
{
  if (ivect[cominfo[unit]->dev_pic]!=serintr) {
    oldvect=ivect[cominfo[unit]->dev_pic];
    ivect[cominfo[unit]->dev_pic]=serintr;
    oldunit=iunit[cominfo[unit]->dev_pic];
    iunit[cominfo[unit]->dev_pic]=unit;
  }
  outb(LINE_CTL(cominfo[unit]->dev_addr), iDLAB);
  outb(BAUD_LSB(cominfo[unit]->dev_addr), 0x01);
  outb(BAUD_MSB(cominfo[unit]->dev_addr), 0x00);
  outb(LINE_CTL(cominfo[unit]->dev_addr), i8BITS);
  on(cominfo[unit]->dev_addr);
  ser_softc[unit].sc_if.if_flags |= IFF_RUNNING;
  *(struct ifnet **)ser_softc[unit].sc_buf = &ser_softc[unit].sc_if;
}

int serattach(dev)
     struct isa_dev *dev;
{
  struct ifnet *ifp;
  unchar unit = (unchar)dev->dev_unit;

  if ((unit < 0) || (unit >= NSER))
    return(0);
  printf("ser%d: port = %x, spl = %d, pic = %d.\n",
	 unit, dev->dev_addr, dev->dev_spl, dev->dev_pic);
  ifp = &(ser_softc[unit].sc_if);
  ifp->if_unit = unit;
  ifp->if_name = "ser";
  ifp->if_mtu = SERMTU;
  ifp->if_flags = IFF_POINTOPOINT;
  ifp->if_output = seroutput;
  ifp->if_ioctl = serioctl;
  ifp->if_snd.ifq_maxlen = IFQ_MAXLEN;
  ifp->if_next = NULL;
  if_attach(ifp);
  return(0);
}

int bar, baz;

int seroutput(ifp, m, dst)
     struct ifnet *ifp;
     struct mbuf *m;
     struct sockaddr *dst;
{
  int len,i,s;
  caddr_t addr = cominfo[ifp->if_unit]->dev_addr;
  u_char *mcp,b;
  s = spl6();
  off(addr);
  foo ++;
  if (!(ifp->if_flags & IFF_RUNNING)) {
    printf("Not running!\n");
    m_free(m);
    serintoff(ifp->if_unit);
    foo --;
    splx(s);
    return(ENETDOWN);
  }
  outb(MODEM_CTL(addr),iRTS);
  i = MAXSPIN;
  while (!(inb(MODEM_STAT(addr))&iDSR) && --i);
  if (!i) {
    printf("Sender aborting - no reciever ack!\n");
    while (m = m_free(m));
    foo --;
    on(addr);
    splx(s);
    return(0);
  }
  bar = 0;
  do {
    len = m->m_len;
    mcp = mtod(m, u_char *);
    while (len--) {
      baz=1;
      bar++;
      outb(TXRX(addr),*mcp++);
      baz=0;
      while (!(inb(LINE_STAT(addr))&iTHRE));
    }
  } while (m = m_free(m));
  bar = 0;
  outb(MODEM_CTL(addr),0x00);
  i = MAXSPIN;
  while ((inb(MODEM_STAT(addr))&iDSR) && --i);
  if (!i)
    printf("Sender never received EOPacket ack!\n");
  foo --;
  on(addr);
  splx(s);
  return (0);
}

int serioctl(ifp, cmd, data)
     struct ifnet *ifp;
     int cmd;
     caddr_t data;
{
  int s=SPLNET();
  struct ifaddr *ifa = (struct ifaddr *)data;
  int error=0;
  switch (cmd) {
  case SIOCSIFADDR:
    ifp->if_flags |= IFF_UP;
    break;
  case SIOCSIFDSTADDR:
    break;
  case SIOCSIFFLAGS:
    if (!(ifp->if_flags & IFF_UP))
      serintoff(ifp->if_unit);
    else
      serinit(ifp->if_unit);
    break;
  default:
    error=EINVAL;
  }
  splx(s);
  return (error);
}

int serintr(unit)
     int unit;
{
  caddr_t addr=cominfo[unit]->dev_addr;
  char *trav = ser_softc[unit].sc_buf+sizeof(struct ifnet *);
  short len=sizeof(struct ifnet *);
  struct mbuf *top = NULL;
  struct mbuf *m,**m2;
  int c,c2,i;
  int s;
  if (foo) {
    compr(0);
    printf("Nested call! bar = %d baz = %d\n",bar,baz);
  }
  off(addr);
  if (!(inb(MODEM_STAT(addr))&iCTS)) {
    printf("Early return!\n");
    on(addr);
    return;
  }
  outb(MODEM_CTL(addr),iDTR);
  s = splhi();
  while (1) {
    i = MAXSPIN;
    if ((!(inb(LINE_STAT(addr))&iDR)) && (!(inb(MODEM_STAT(addr))&iCTS)))
      break;
    while (!(inb(LINE_STAT(addr))&iDR) && --i);
    if (!i) {
      if ((inb(MODEM_STAT(addr))&iCTS))
	printf("Timeout inputting - sender quit!\n");
      else
	printf("Timeout inputting - quantum expired!\n");
      break;
    }
    c = inb(TXRX(addr));
    if (++len >= SERMTU) {
      printf("Packet full!\n");
      trav = ser_softc[unit].sc_buf + sizeof(struct ifnet *);
      len = 0;
      continue;
    }
    *trav++= c;
  }
  splx(s);
  on(addr);
  if (len>sizeof(struct ifnet *)) {
    trav = ser_softc[unit].sc_buf;
    m2 = &top;
    while (len) {
      MGET(m, M_DONTWAIT, MT_DATA);
      if (len >= MSIZE*2) {
	MCLGET(m);
	i=MIN(len,CLBYTES);
      }
      else
	i=MIN(len,MLEN);
      bcopy(trav, mtod(m, caddr_t), i);
      m->m_len = i;
      *m2 = m;
      m2 = &m->m_next;
      len-=i;
      trav+=i;
    }
    if (IF_QFULL(&ipintrq)) {
      IF_DROP(&ipintrq); 
      m_freem(top); 
    }
    else {
      schednetisr(NETISR_IP);
      IF_ENQUEUE(&ipintrq, top);
    }
  }
  return(0);
}

#endif
