h64142
s 00000/00000/00778
d D 5.5 91/01/08 19:13:16 william 5 4
c  npx.c wd.c wt.c
e
s 00001/00001/00777
d D 5.4 90/11/18 11:31:54 bill 4 3
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00000/00001/00778
d D 5.3 90/11/08 21:35:40 bill 3 2
c obselete code
e
s 00042/00074/00737
d D 5.2 90/11/07 11:53:44 bill 2 1
c changed to work with autoconf, bug fixes for kermit, cleanup
e
s 00811/00000/00000
d D 5.1 90/06/23 19:11:47 donahn 1 0
c date and time created 90/06/23 19:11:47 by donahn
e
u
U
t
T
I 1
#include "com.h"
#if NCOM > 0
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Hacked up to work on BSD/386 by Don Ahn.
 *
 *	%W% (Berkeley) %G%
 */
I 2

E 2
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	com.c,v $
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
 * Revision 2.2  89/07/17  10:39:30  rvb
 * 	New from Olivetti.
 * 
 */

/* 
 *	Olivetti serial port driver v1.0
 *	Copyright Ing. C. Olivetti & C. S.p.A. 1988, 1989
 *	All rights reserved.
 *
 */ 
/*
  Copyright 1988, 1989 by Olivetti Advanced Technology Center, Inc.,
Cupertino, California.

		All Rights Reserved

  Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Olivetti
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

  OLIVETTI DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL OLIVETTI BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUR OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

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
D 2
#include "machine/device.h"
E 2
I 2
D 4
#include "machine/isa/device.h"
E 4
I 4
#include "machine/isa/isa_device.h"
E 4
E 2
D 3
#include "atio.h"
E 3
#include "comreg.h"
#include "icu.h"

extern struct timeval   time;           /* system time */
extern void 	splx();
extern int	spltty();
extern void 	timeout();
extern void 	ttrstrt();

I 2
u_char inb();

E 2
/* 
 * Driver information for auto-configuration stuff.
 */

int 	comprobe(), comattach(), comintr(), comstart();
void	comparam(), comreset(), comtmout(), comprog();

/*
struct	i386_dev	cominfo[NCOM] = {
	{0, 0, -1, 0, 0,(caddr_t)0x3f8, 4, 0, 0, 0,(caddr_t)0x3f8,
	 0, -1, 0, 0, 0},
	{0, 1, -1, 0, 0,(caddr_t)0x2f8, 3, 0, 0, 0,(caddr_t)0x2f8,
	 0, -1, 0, 0, 0}
};
*/

D 2
struct	driver comdriver = 
E 2
I 2
struct	isa_driver comdriver = 
E 2
	{comprobe,comattach,"com"};

/*
struct	i386_ctlr	comctlr[NCOM] = {
	{(struct i386_driver *)&comdriver, 0, 1, (caddr_t)0x3f8, 4, 
	 0, (caddr_t)0x3f8, 0},
	{(struct i386_driver *)&comdriver, 0, 1, (caddr_t)0x2f8, 3, 
	 0, (caddr_t)0x2f8, 0}
};
*/

#ifdef undef
static char             comtmrun = 0;   /* timer set up? */
#endif undef

static	int	probed = 0;

char comcprt[] = "Olivetti Motherboard Serial Port Driver v1.0 (HP Extensions)\n";

typedef struct {
	u_short		txrx;
	u_short		baud_lsb;
	u_short		baud_msb;
	u_short		intr_enab;
	u_short		intr_id;
	u_short		line_ctl;
	u_short		modem_ctl;
	u_short		line_stat;
	u_short		modem_stat;
	short 		intr_vec;
	int		timer_cnt;
} COM_STRUCT;

typedef struct  {
        ushort          speed;      /*last programmed baud rate count */
        ushort          com_break;  /* break detect state */
        ushort          carrier;    /* is line local or modem? */
        time_t          last_time;  /* output char watchdog timeout */
} COM_AUX; 


COM_STRUCT 	com_struct[MAX_COM_PORTS] = {
        {
        (u_short)0x3f8,  /* .txrx */
        (u_short)0x3f8,  /* .baud_lsb */
        (u_short)0x3f9,  /* .baud_msb */
        (u_short)0x3f9,  /* .intr_enab */
        (u_short)0x3fa,  /* .intr_id */
        (u_short)0x3fb,  /* .line_ctl */
        (u_short)0x3fc,  /* .modem_ctl */
        (u_short)0x3fd,  /* .line_stat */
        (u_short)0x3fe,  /* .modem_stat */
        (short)0x04,     /* .intr_vec - default */
	(int)-1,	 /* default for watchdog timer */
        },
        {
        (u_short)0x2f8,  /* .txrx */
        (u_short)0x2f8,  /* .baud_lsb */
        (u_short)0x2f9,  /* .baud_msb */
        (u_short)0x2f9,  /* .intr_enab */
        (u_short)0x2fa,  /* .intr_id */
        (u_short)0x2fb,  /* .line_ctl */
        (u_short)0x2fc,  /* .modem_ctl */
        (u_short)0x2fd,  /* .line_stat */
        (u_short)0x2fe,  /* .modem_stat */
        (short)0x03,     /* .intr_vec - default */
	(int)-1,	 /* default for watchdog timer */
        },
};
			
COM_AUX 	com_aux[NCOM];

struct tty	com_tty[NCOM];

ushort combaud[] = {
	0, 0x900, 0x600, 0x417, 0x359, 0x300, 0, 0x180, 
	0x0c0, 0x060, 0x040, 0x030, 0x018, 0x00c, 0x006,
	0x003
};


/* ~~ali */

struct	{
	int		unit;
	COM_STRUCT	*comm;
} vec_2_unit[] = {
		-1, NULL,
		-1, NULL,
		-1, NULL,
		 1, &com_struct[1],		/* COM1 @ 0x2F8 */
		 0, &com_struct[0],		/* COM0 @ 0x3F8 */
		-1, NULL,
		-1, NULL,
		-1, NULL,
		-1, NULL,
		-1, NULL,
		-1, NULL,
		-1, NULL,
		-1, NULL,
		-1, NULL,
		-1, NULL,
		-1, NULL
	};

void	commdm(), comxbe(), comrbf(), comlsr();

void	(*comint_handler[])() = {
		commdm,
		comxbe,
		comrbf,
		comlsr
	};

int
comprobe(dev)
D 2
struct device *dev;
E 2
I 2
struct isa_device *dev;
E 2
{
D 2
	if (!probed) {
E 2
I 2
	/*if (!probed) {
E 2
		probed = 1;
		printf("%s", comcprt);
D 2
	}
E 2
I 2
	}*/
E 2
	/* Make sure FIFO is off */
D 2
	outb(com_struct[dev->unit].intr_id,0);
	if (com_struct[dev->unit].txrx == dev->ioa) {
		if ((inb(com_struct[dev->unit].intr_id) & 0xf8) == 0) {
E 2
I 2
	outb(com_struct[dev->id_unit].intr_id,0);
	if (com_struct[dev->id_unit].txrx == dev->id_iobase) {
		if ((inb(com_struct[dev->id_unit].intr_id) & 0xf8) == 0) {
E 2
			return(1);
		} else {
D 2
			printf("Serial Port %d Not Found At 0x%x\n",
				dev->unit, dev->ioa);
        		com_struct[dev->unit].intr_vec = -1;
E 2
I 2
			/*printf("Serial Port %d Not Found At 0x%x\n",
				dev->unit, dev->ioa);*/
        		com_struct[dev->id_unit].intr_vec = -1;
E 2
			return(0);
		}
	}
/*
	printf("Motherboard Serial Port %d Not Configured At 0x%x\n",
		dev->unit, dev->ioa);
*/
D 2
        com_struct[dev->unit].intr_vec = -1;
E 2
I 2
        com_struct[dev->id_unit].intr_vec = -1;
E 2
	return(0);

}


int
comattach(dev)
D 2
struct device * dev;
E 2
I 2
struct isa_device * dev;
E 2
{
	struct	tty	*tp;
	u_char		unit;

D 2
	unit = dev->unit;
	if ((char *)com_struct[unit].txrx == dev->ioa) {
E 2
I 2
	unit = dev->id_unit;
	if ((char *)com_struct[unit].txrx == dev->id_iobase) {
E 2
		tp = &com_tty[unit];
		tp->t_addr = (caddr_t) tp;
		tp->t_state = 0;
		tp->t_dev = unit;
		com_aux[unit].carrier = 0; /*addr->dev_flags; */
		com_aux[unit].last_time = 0x7fffffffL;
		com_aux[unit].carrier = 0;
	 	com_aux[unit].com_break = 0;
		outb(com_struct[unit].intr_enab, 0);
		outb(com_struct[unit].modem_ctl, 0);
/*
		printf("Motherboard Serial Port %d, Attached vec %d\n",
			unit,com_struct[unit].intr_vec);
*/
D 2
		INTREN(1<<com_struct[unit].intr_vec); /* XXX */
E 2
	}
I 2
#ifdef garbage
E 2
	else
		printf("Motherboard Serial Port %d, Attach Failed\n",unit);
D 2
	return;

E 2
I 2
#endif
E 2
}

int
comopen(dev, flag)
int	dev;
int	flag;
{
	int		o_pri;
	struct 	tty *	tp;
	int		unit;

	unit = minor(dev);
D 2
	if (unit >= NCOM) {
		u.u_error = ENXIO;
		return(-1);
	}
	tp = &com_tty[unit];
	if (tp->t_state & TS_XCLUDE && u.u_uid != 0) {
		return(EBUSY);
	}
E 2
I 2
	if (unit >= NCOM)
		return(ENXIO);
E 2

D 2
	if (!(tp->t_state & (TS_ISOPEN|TS_WOPEN))) {
E 2
I 2
	tp = &com_tty[unit];
	if (!(tp->t_state & TS_ISOPEN)) {
E 2
		ttychars(tp); 	
		tp->t_oproc = comstart;
		tp->t_ospeed = tp->t_ispeed = B9600;
		tp->t_flags = ODDP|EVENP|ECHO|CRMOD;
		tp->t_state &= ~TS_BUSY;
D 2
#ifdef undef
		o_pri = spltty();
		if (!comtmrun) {
			comtmout(unit);
		}
		splx(o_pri);
#endif undef
	}
	if (!(tp->t_state & TS_ISOPEN)) {
E 2
		comreset(unit);
D 2
	}
E 2
I 2
	} else if (tp->t_state & TS_XCLUDE && u.u_uid != 0)
		return(EBUSY);

E 2
	o_pri = spltty();	
	if ((!com_aux[unit].carrier) || 
	    (inb(com_struct[unit].modem_stat) &iRLSD)) {
		tp->t_state |= TS_CARR_ON;
	} 
	else {
		tp->t_state &=~TS_CARR_ON;
	}
	while (!(tp->t_state & TS_CARR_ON)) {
		tp->t_state |= TS_WOPEN;
                if (sleep((caddr_t) &tp->t_rawq, TTIPRI)) {
                        tp->t_state &= ~TS_WOPEN;
		} else {
                	u.u_error = EINTR;
                	splx(o_pri);
                	return(-1);
		}
        }
	splx(o_pri);
D 2
	if ((*linesw[tp->t_line].l_open)(dev, tp)) {
		comclose(dev, flag);
	}
	/* TURN ON FIFO if THERE */
/*
	outb(com_struct[unit].intr_id,0x87);
*/
	return(0);

E 2
I 2
	return ((*linesw[tp->t_line].l_open)(dev, tp));
E 2
}


int
comclose(dev, flag)

int	dev;
int	flag;

{
	struct	tty	*tp;
	int		unit;
	unit = minor(dev);
	tp = &com_tty[unit];

D 2
	/* TURN OFF FIFO if THERE */
/*
	outb(com_struct[unit].intr_id,0);
*/

E 2
	(*linesw[tp->t_line].l_close)(tp);
	if (!(tp->t_state & TS_ISOPEN)) {
		outb(com_struct[unit].intr_enab, 0);
		outb(com_struct[unit].modem_ctl, 0);
		tp->t_state &= ~TS_BUSY;
	}
	return(0);
}


int
comread(dev, uio)

int	dev;
struct	uio	*uio;

{
	struct	tty	*tp;
	int 		unit;
	int		i;
	u_char		c;
  
	unit = minor(dev);
	tp = &com_tty[unit];
	return((*linesw[tp->t_line].l_read)(tp, uio));

}


int
comwrite(dev, uio)

int	dev;
struct	uio *uio;

{
	struct tty *	tp;
	int		unit;

	unit = minor(dev);
	tp = &com_tty[unit];
	return((*linesw[tp->t_line].l_write)(tp, uio));

}


int
comioctl(dev, cmd, addr, mode)
int	dev;
int	cmd;
caddr_t	addr;
int	mode;
{
	int	    	unit;
	struct tty *	tp;
	COM_STRUCT *	a_com_struct;
	register int	o_pri;
	register int	err = 0;

	unit = minor(dev);
	tp = &com_tty[unit];
	a_com_struct = &com_struct[unit];

	if ((err = (*linesw[tp->t_line].l_ioctl)(tp, cmd, addr, mode)) >= 0)
		return(err);
	if ((err = ttioctl(tp, cmd, addr, mode)) >= 0) {
       		if (cmd == TIOCSETP || 
		    cmd == TIOCSETN ||
		    cmd == TIOCLBIS ||
		    cmd == TIOCLBIC || 
		    cmd == TIOCLSET) {
			comparam(unit);
		}
		return (err);
	}
	o_pri = spltty();
	switch (cmd) {
	  case TIOCSBRK: 		/* Set break */
/*
printf("comioctl: setting TIOCSBRK\n");
*/
		outb(a_com_struct->line_ctl,
		     inb(a_com_struct->line_ctl | iSETBREAK));
		break;
	  case TIOCCBRK:		/* Clear break */
/*
printf("comioctl: setting TIOCCBRK\n");
*/
		outb(a_com_struct->modem_ctl,
		     inb(a_com_struct->modem_ctl & ~iSETBREAK));
		break;

	  /* why do interrupts need to be enabled with these request? */
	  case TIOCSDTR:		/* Set DTR and RTS */
/*
printf("comioctl: setting TIOCSDTR\n");
*/
		outb(a_com_struct->modem_ctl, iOUT2|iDTR|iRTS);
		break;
	  case TIOCCDTR:		/* Clear DTR and RTS */
/*
printf("comioctl: setting TIOCCDTR\n");
*/
                outb(a_com_struct->modem_ctl, iOUT2);
		break;
	  case TIOCMSET:
	  case TIOCMBIS:
	  case TIOCMBIC:
	  case TIOCMGET:
  
	  default:
		err = ENOTTY;
		break;
	}
	splx(o_pri);
	return(err);
}



int
comintr(vec)
int	vec;
{
	register COM_STRUCT	*comm;
	register struct	tty *tp;
	register int	unit;
	register u_char	c;
	register u_char	interrupt_id, line_status, modem_status;
	int	o_pri;

	unit = vec_2_unit[vec].unit;
	comm = vec_2_unit[vec].comm;

D 2
	if(!((tp = &com_tty[unit])->t_state & TS_ISOPEN))
		return;
E 2
I 2
	/*if(!((tp = &com_tty[unit])->t_state & TS_ISOPEN))
		return;*/
	tp = &com_tty[unit];
E 2

D 2
	o_pri = spltty();
	com_aux[unit].last_time = 0x7fffffffL;

E 2
	while(!((interrupt_id = inb(comm->intr_id)) & 1)) {
	/*
		printf("vec = %d, unit =%d, id = %d\n",vec,unit,interrupt_id);	
	*/
		(*comint_handler[interrupt_id >> 1])(tp, comm);
	}

D 2
	splx(o_pri);
	return;

E 2
/*
	for (unit = 0; unit < NCOM; unit++) {
		if (com_struct[unit].intr_vec == vec) {
			break;
		}
	}
	
	if (unit >= NCOM) {
		printf("comintr called, returning on a spurios interrupt\n");
		return;
	}

	tp = &com_tty[unit];
	if (!(tp->t_state & TS_ISOPEN)) {
		return;
	}

	interrupt_id = ( inb(com_struct[unit].intr_id) >>1  )  &0x03; 
	line_status  =   inb(com_struct[unit].line_stat);
	modem_status =   inb(com_struct[unit].modem_stat);

	switch(interrupt_id) {
		case INT_MDM:
		case INT_XBE:
		case INT_RBF:
		case INT_LSR:
	}

	if (line_status & iTHRE) {
		tp->t_state &= ~TS_BUSY;
		if (tp->t_state & TS_ASLEEP)	{
			tp->t_state &= ~TS_ASLEEP;
			wakeup ((caddr_t)&tp->t_outq);
		}
		comstart(tp);
	}

	if (line_status & iDR) {
D 2
		c = inb(com_struct[unit].txrx) & 0xff;
E 2
I 2
		c = inb(com_struct[unit].txrx);
E 2
		(*linesw[tp->t_line].l_rint)(c, tp);
	}
#ifdef undef
	if (line_status & iBRKINTR) {
		com_aux[unit].com_break = 1;
	}
	else {
		if (com_aux[unit].com_break) {
			com_aux[unit].com_break = 0;
			if (tp->t_flags & RAW)
				c = 0;
			else
				c = tp->t_intrc;
			(*linesw[tp->t_line].l_rint)(c, tp);
		}
	}
	if (line_status & (iOR|iFE))
		printf("comintr: %s error\n", (line_status & iOR) ? "overrun":
								    "framing");
	if (com_aux[unit].carrier) {		
		if (!(modem_status & iRLSD)) {
			(*linesw[tp->t_line].l_modem)(tp, 0);
		}
		else {
			if (modem_status & iRLSD)
				(*linesw[tp->t_line].l_modem)(tp, 1);
		}
	}
#endif undef
	splx(o_pri);
	return;
*/
}

void
comxbe(tp, comm)
register struct tty	*tp;
register COM_STRUCT	*comm;
{
	tp->t_state &= ~TS_BUSY;
	if(tp->t_state & TS_ASLEEP)	{
		tp->t_state &= ~TS_ASLEEP;
		wakeup((caddr_t)&tp->t_outq);
	}

	comstart(tp);
}

void
comrbf(tp, comm)
register struct tty	*tp;
register COM_STRUCT	*comm;
{
D 2
	(*linesw[tp->t_line].l_rint)(inb(comm->txrx) & 0xFF, tp);
E 2
I 2
	(*linesw[tp->t_line].l_rint)(inb(comm->txrx), tp);
E 2
}

void
commdm(tp, comm)	
register struct tty	*tp;
register COM_STRUCT	*comm;
{
/*
	panic("Unexpected MODEM interrupt.");
*/
}

void
comlsr(tp, comm)	
register struct tty	*tp;
register COM_STRUCT	*comm;
{
/*
	panic("Unexpected LINE STATUS interrupt.");
*/
}

void
comparam(unit)
register int unit;
{
        struct tty *	tp;
	COM_STRUCT *	a_com_struct;
        int 		o_pri;
        unsigned char	xx;

        tp = &com_tty[unit];
	a_com_struct = &com_struct[unit];
        o_pri = spltty();
        if (tp->t_ispeed == B0) {
                tp->t_state |= TS_HUPCLS;
		outb(a_com_struct->modem_ctl, iOUT2);
#ifdef undef
		comreset(unit);
		ttyflush(tp, FREAD|FWRITE);
#endif undef

		/* this is what mCOM was doing ..... */
                /* Clear DTR and RTS */
		/*
                outb(a_com_struct->modem_ctl, iOUT2);
		*/

                splx(o_pri);
                return;
        }

        /* Set the baud rate and initial COM settings */
        comprog(unit, tp->t_ispeed);
        if (tp->t_flags & (RAW | LITOUT | PASS8)) {
                xx = i8BITS;
	} 
	else {
                xx = (i7BITS | iPEN);
	}
        if (tp->t_flags & EVENP) {
                xx |= iEPS;
	}
        if (tp->t_ispeed == B110) {  /* 
					B110 used to set number of 
					stop bits?  Sounds like BS to
					me, but I'll buy it for now...
				      */
                xx |= iSTB;
	}
#ifdef undef
	xx = i8BITS|iSTB;
#endif undef
	xx = i8BITS;
        outb(a_com_struct->line_ctl, xx);
#ifdef undef
	/* Turn on all interrupts */
	outb(a_com_struct->modem_ctl, 
	     inb(a_com_struct->modem_ctl) | iOUT2);
	outb(a_com_struct->intr_enab, 
	     iMODEM_INTR|iTX_INTR|iRX_INTR|iERROR_INTR);
#endif undef
        splx(o_pri);
	return;

}

D 2

E 2
int
comstart(tp)
struct tty	*tp;
{
	int    	o_pri;
	char	c;


	o_pri = spltty();
	if (tp->t_state & (TS_TIMEOUT|TS_TTSTOP|TS_BUSY)) {
		splx(o_pri);
		return;
	}

	if (tp->t_outq.c_cc <= TTLOWAT(tp)) {
		if (tp->t_state & TS_ASLEEP)	{
			tp->t_state &= ~TS_ASLEEP;
			wakeup ((caddr_t)&tp->t_outq);
		}
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel =0;
			tp->t_state &= ~TS_WCOLL;
		}
	}

D 2
	if ((tp->t_outq.c_cc <=0)  || ((c=getc(&tp->t_outq)) == -1)) {
		tp->t_state &= ~TS_BUSY;
E 2
I 2
	if (tp->t_outq.c_cc <=0) {
		outb(com_struct[minor(tp->t_dev)].intr_enab, iRX_ENAB);
E 2
		splx(o_pri);
		return;
	} 
D 2
	else 
	if (tp->t_flags & (RAW|LITOUT) || (c <= 0177)) {
E 2
I 2

	c = getc(&tp->t_outq);
	
	if (tp->t_flags & (RAW|LITOUT|PASS8) || c <= 0177) {
		outb(com_struct[minor(tp->t_dev)].intr_enab, iTX_ENAB|iRX_ENAB);
E 2
		outb(com_struct[minor(tp->t_dev)].txrx,  c);
		tp->t_state |= TS_BUSY;
D 2
#ifdef undef
		com_aux[minor(tp->t_dev)].last_time = time.tv_sec;
#endif undef
	} 
	else {
#ifdef undef
E 2
I 2
	} else {
E 2
		timeout(ttrstrt, (caddr_t)tp,  (c & 0177));
		tp->t_state |= TS_TIMEOUT;
D 2
#endif undef
E 2
I 2
		outb(com_struct[minor(tp->t_dev)].intr_enab, iRX_ENAB);
E 2
	}
	splx(o_pri);
	return;

}
D 2

E 2

void
comreset(unit)
int unit;
{
        unsigned char	flush_regs;
	int	o_pri;

	o_pri = spltty();
        flush_regs = inb(com_struct[unit].intr_id);
        flush_regs = inb(com_struct[unit].line_stat);
        flush_regs = inb(com_struct[unit].modem_stat);
        flush_regs = inb(com_struct[unit].txrx);

	outb(com_struct[unit].line_ctl, iDLAB);
	outb(com_struct[unit].baud_lsb, combaud[B9600] & 0xff);		
	outb(com_struct[unit].baud_msb, combaud[B9600]  >> 8);
	outb(com_struct[unit].line_ctl, i8BITS);
/*	outb(com_struct[unit].intr_enab, iTX_ENAB|iRX_ENAB|iERROR_ENAB); */
	outb(com_struct[unit].intr_enab, iTX_ENAB|iRX_ENAB);
	outb(com_struct[unit].modem_ctl, iDTR|iRTS|iOUT2);
	splx(o_pri);

	return;

}


#ifdef undef
void
comtmout(notused)
caddr_t notused;
{

	int		unit;
	int		o_pri;

	for (unit = 0; unit < NCOM; unit++) {
		if ((time.tv_sec - com_aux[unit].last_time) > MAXTIME)  {
			printf("comtmout - reset\n");
			o_pri = spltty();
			comreset(unit);
			comintr(com_struct[unit].intr_vec); 
			splx(o_pri);
		}
	}
        comtmrun = 1;
        timeout(comtmout, (caddr_t)0,  100);
}
#endif undef


void
comprog(unit, speed)
int	unit;
ushort	speed;
{
        u_char 	save;

	com_aux[unit].speed = speed;
        save = inb(com_struct[unit].line_ctl);
        outb(com_struct[unit].line_ctl, iDLAB);
        outb(com_struct[unit].baud_lsb, combaud[speed] & 0xff);
        outb(com_struct[unit].baud_msb, combaud[speed] >>8);
        outb(com_struct[unit].line_ctl, save);
	return;

}
#endif NCOM
E 1
