/*
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_par.c,v $
 * Revision 2.1.1.4  91/07/15  00:16:59  rvb
 * 	Don't set UNUSED bits in intr_enable.
 * 	[91/06/27            mg32]
 * 
 * Revision 2.1.1.3  91/03/28  08:46:05  rvb
 * 	Changed protocol to utilitize LapLink cables.  Incompatible with
 * 	previous revisions.
 * 	[91/03/15            mg32]
 * 
 * Revision 2.1.1.2  90/09/18  08:39:19  rvb
 * 	Added more documentation on how we use parallel interface.
 * 	[90/09/17            mg32]
 * 
 * Revision 2.1.1.1  90/08/25  15:43:36  rvb
 * 	Created 08/05/90.
 * 	Parallel port network driver.
 * 	[90/08/14            mg32]
 * 
 */

/* 
 *	Parallel port network driver v1.1
 *	All rights reserved.
 */ 

/*
 Subject: parallel network interface

 The printer network driver has the following hardware requirements for the
 interconnection cable:

 Connections:
 Side1		Side2		Function	Side1	 / Side2
 Pin 5		Pin 10	Interrupt strobe: send status (w)/send status (r)
 Pin 2		Pin 15	Data bits	:	write	 / read
 Pin 3		Pin 13	Data bits	:	write	 / read
 Pin 4		Pin 12	Data bits	:	write	 / read
 Pin 6		Pin 11	Data bits	:	write	 / read
 Pin 10		Pin 5
 Pin 11		Pin 6
 Pin 12		Pin 4
 Pin 13		Pin 3
 Pin 15		Pin 2
 Pins 18-25	Pins 18-25 (ground interconnections)

 The cable is "symmetric" in that either side can be plugged into either of the
 computers.  

 The hardware requirements are as follows:
 Port 0x378 must be writable with the following specifications:
 	Bit 4 -> pin 6
	Bit 3 -> pin 5
	Bit 2 -> pin 4
	Bit 1 -> pin 3
	Bit 0 -> pin 2
 Port 0x379 must be readable with the following specifications:
	Bit 7 <- pin 11
	Bit 6 <- pin 10
	Bit 5 <- pin 12
	Bit 4 <- pin 13
	Bit 3 <- pin 15
 Port 0x37a must be readable and writable with the following specifications:
	Bit 4 -> interrupt enable
 So Port 0x378 connects to  Port 0x379 as
	Bit 3 -> pin 5	:  pin 10 -> Bit 6	0x08 -> 0x40

 	Bit 4 -> pin 6	:  pin 11 -> Bit 7	0x08<<1 -> ~ 0x80
	Bit 2 -> pin 4	:  pin 12 -> Bit 5	0x07 -> 0x38
	Bit 1 -> pin 3	:  pin 13 -> Bit 4	0x07 -> 0x38
	Bit 0 -> pin 2	:  pin 15 -> Bit 3	0x07 -> 0x38
 [note: bit 0 is considered the least significant bit, pins on the connector
 are numbered starting with 1, -> represents sending data out on the bus, <-
 represents reading data from the bus]

 Pins 1,7,8,9, and 16 are currently unused, and may be allowed to "float".

 The data is sent in 4 bit "nybbles", with the highest 4 bits being sent first.

 To bring up the interface, all that should be required is 
 	ifconfig par0 <your ip address> <connected machine's ip address> up
 and to bring down the interface
 	ifconfig par0 down
 You may get a warning message (such as printer out of paper) once you down
 the interface, as the port is monitored for both printer and network activity
 depending on whether par0 is up or down, and when you down the interface the
 printer driver will then read whatever is on the port (which will be the last
 message from the other computer).
 */

#include <par.h>
#if NPAR > 0

#include <sys/proc.h>

#include <i386/ipl.h>
#include <i386/pio.h>
#include <i386at/atbus.h>
#include <i386at/if_par.h>

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>

#include <net/if.h>
#include <net/netisr.h>
#include <netinet/in.h>
#include <netinet/in_var.h>

int parintr();
int parioctl();
int parattach();
int paroutput();

int (*oldvect)();
int oldunit;

extern struct isa_dev *lprinfo[];

struct par_softc {
  struct ifnet sc_if;
  char sc_buf[PARMTU+sizeof(struct ifnet *)];
} par_softc[NPAR];

void parintoff(unit)
     int unit;
{
  outb(INTR(lprinfo[unit]->dev_addr),0x07);
  par_softc[unit].sc_if.if_flags &= ~IFF_RUNNING;
  ivect[lprinfo[unit]->dev_pic]=oldvect;
  iunit[lprinfo[unit]->dev_pic]=oldunit;
}

void parinit(unit)
     int unit;
{
  if (ivect[lprinfo[unit]->dev_pic]!=parintr) {
    oldvect=ivect[lprinfo[unit]->dev_pic];
    ivect[lprinfo[unit]->dev_pic]=parintr;
    oldunit=iunit[lprinfo[unit]->dev_pic];
    iunit[lprinfo[unit]->dev_pic]=unit;
  }
  outb(INTR(lprinfo[unit]->dev_addr),0x11);
  par_softc[unit].sc_if.if_flags |= IFF_RUNNING;
  *(struct ifnet **)par_softc[unit].sc_buf = &par_softc[unit].sc_if;
}

int parattach(dev)
     struct isa_dev *dev;
{
  struct ifnet *ifp;
  unchar unit = (unchar)dev->dev_unit;

  if ((unit < 0) || (unit >= NPAR))
    return(0);
  printf("par%d: port = %x, spl = %d, pic = %d.\n",
	 unit, dev->dev_addr, dev->dev_spl, dev->dev_pic);
  ifp = &(par_softc[unit].sc_if);
  ifp->if_unit = unit;
  ifp->if_name = "par";
  ifp->if_mtu = PARMTU;
  ifp->if_flags = IFF_POINTOPOINT;
  ifp->if_output = paroutput;
  ifp->if_ioctl = parioctl;
  ifp->if_snd.ifq_maxlen = IFQ_MAXLEN;
  ifp->if_next = NULL;
  if_attach(ifp);
  return(0);
}

int paroutput(ifp, m, dst)
     struct ifnet *ifp;
     struct mbuf *m;
     struct sockaddr *dst;
{
  int len,i,s;
  caddr_t addr = lprinfo[ifp->if_unit]->dev_addr;
  u_char *mcp,c;
  if (!(ifp->if_flags & IFF_RUNNING)) {
    m_free(m);
    parintoff(ifp->if_unit);
    return(ENETDOWN);
  }
  s = SPLNET();
  do {
    len = m->m_len;
    mcp = mtod(m, u_char *);
    while (len--) {
      c=*mcp++;
      outb(OUTPUT(addr),((c&0x80)>>3) | ((c&0x70)>>4) | 0x08);
      i=MAXSPIN;
      while (!(inb(INPUT(addr))&0x40) && --i);
      outb(OUTPUT(addr),((c&0x08)<<1) | (c&0x07));
      i=MAXSPIN;
      while ((inb(INPUT(addr))&0x40) && --i);
    }
  } while (m = m_free(m));
  outb(OUTPUT(addr),(((c&0x08)<<1) | (c&0x07))^0x17);
  splx(s);
  return (0);
}

int parioctl(ifp, cmd, data)
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
      parintoff(ifp->if_unit);
    else
      parinit(ifp->if_unit);
    break;
  default:
    error=EINVAL;
  }
  splx(s);
  return (error);
}

int parintr(unit)
     int unit;
{
  caddr_t addr=lprinfo[unit]->dev_addr;
  char *trav = par_softc[unit].sc_buf+sizeof(struct ifnet *);
  short len=sizeof(struct ifnet *);
  struct mbuf *top = NULL;
  struct mbuf *m,**m2;
  u_char c,c2;
  int i;
  do {
    c2=inb(INPUT(addr));
    outb(OUTPUT(addr),0x08);
    i=MAXSPIN;
    while(((c=inb(INPUT(addr)))&0x40) && --i);

    c = inb(INPUT(addr));
    outb(OUTPUT(addr),0x00);
    if (!i)
      break;

    if (++len >= PARMTU) {
      trav = par_softc[unit].sc_buf + sizeof(struct ifnet *);
      len = 0;
      continue;
    }
    *trav++ = ((~c2)&0x80) | ((c2&0x38)<<1) | (((~c)&0x80)>>4) | ((c&0x38)>>3);
    i=MAXSPIN;
    while (!((c2=inb(INPUT(addr)))&0x40) && --i)
      if (((c2^0xb8)&0xf8) == (c&0xf8))
	goto end;
  } while (i);

 end:

  outb(OUTPUT(addr),0x00);
  if (len>sizeof(struct ifnet *)) {
    trav = par_softc[unit].sc_buf;
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
