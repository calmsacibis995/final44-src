/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	qd.c,v $
 * Revision 2.3.1.4  90/07/10  11:45:35  rvb
 * 	THIS CODE IS NOW OFFICIALLY BROKEN.  I DOUBT IT CONFIGURES
 * 	PROPERLY.  AND I DON'T HAVE THE HARDWARE TO TEST IT ON.
 * 	SOMEONE WHO KNOWS SHOULD MAKE IT MORE LIKE com.c or hd.c
 * 	IN THE probe and attach FUNCTIONS.
 * 	[90/06/15            rvb]
 * 
 * Revision 2.3.1.3  90/02/28  15:50:53  rvb
 * 	Fix numerous typo's in Olivetti disclaimer.
 * 	[90/02/28            rvb]
 * 
 * Revision 2.3.1.2  90/01/08  13:29:57  rvb
 * 	Add Olivetti copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 2.3.1.1  89/12/28  12:43:48  rvb
 * 	Fix probe to only print out on success.
 * 	[89/12/26            rvb]
 * 
 * Revision 2.3  89/09/25  12:27:15  rvb
 * 	Small typo (a,b) vs (a-b) in i386_ctlr
 * 	[89/09/23            rvb]
 * 
 * Revision 2.2  89/07/17  10:42:43  rvb
 * 	New from Olivetti.
 * 
 */

/*
 *  AST Asynch Cluster Adapter Driver
 *  Copyright Ing. C. Olivetti & S.p.A. 1989
 *  All rights reserved.
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

/* define DEBUGMEBABY in order to do some grungy deboogering */

#include <qd.h>
#if NQD > 0

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
#include <i386at/atbus.h>
#include <i386at/qdregs.h>

extern struct timeval time; 	/* system time */

extern void     splx();
extern int	spltty();
extern void     timeout();
extern void     ttrstrt();

#define PORTS		4	
#define MAX_PORTS	(NQD * PORTS)
#define	MAXTIME		2	/* 2 seconds */

/*
 * Driver information for auto-configuration stuff.
 */
int	qdprobe(), qdattach(), qdintr(), qdstart(), qdmodem();

void	qdxint(), qdrint(), qdmint(), qdparam(),
	qdreset(), qdtmout(), set_poll_m(), qddisable();

extern struct isa_dev 	qdinfo[];

struct isa_driver	qddriver = {
	qdprobe,	/* see if a driver is really there */
	0,		/* see if a slave is there */
	qdattach,	/* setup driver for a slave */
	"qd", 		/* name of a device */
	qdinfo, 	/* backptrs to init structs */
	0,		/* name of a controller */
	0 	  	/* backpointers to init structs */
};

struct isa_ctlr 	qdctlr[ NQD ] = {
	{
	(struct	isa_driver *) &qddriver,
	(long)	0,		/* controller index in driver */
	(long)	1,		/* controller exists */
	(caddr_t) 0x02bf,	/* csr address */
	(long) SPLTTY,		/* SPL level for interrupt */
	(long)	7,		/* pic line upon interrupt */
	(long)	0,		/* interrupt handler */
	(caddr_t)0x02a0,	/* start address in mem space */
	(caddr_t)(0x02bf-0x02a0)/* length of mem space used */
	},
	{
	(struct	isa_driver *) &qddriver,
	(long)	0,		/* controller index in driver */
	(long)	1,		/* controller exists */
	(caddr_t) 0x01bf,	/* csr address */
	(long) SPLTTY,		/* SPL level for interrupt */
	(long)	7,		/* pic line upon interrupt */
	(long)	0,		/* interrupt handler */
	(caddr_t)0x01a0,	/* start address in mem space */
	(caddr_t)(0x01bf-0x01a0)/* length of mem space used */
	}
};

struct isa_dev 	qdinfo[ NQD ] = {
	{
	(struct	isa_driver *) &qddriver,
	(long)	0,		/* unit number on the system */
	(long)	0,		/* ctlr number; -1 if none */
	(long)	0,		/* slave on controller */
	(long)	0,		/* Was it found at config time? */
	(caddr_t) 0x02a0,	/* csr address */
	(long) SPLTTY,		/* SPL level for interrupt */
	(long)	7,		/* pic line upon interrupt */
	(long)	0,		/* if init 1 set to number for iostat */
	(long)	0,		/* parameter from system specification */
	(int)	0,		/* interrupt handler(s) */
	(caddr_t) 0x02a0,	/* start address in mem space */
	(u_long)(0x02bf-0x02a0),	/* length of mem space used */
	(long)	0,		/* driver specific type information */
	(struct	isa_dev *) 0,
	(struct	isa_ctlr *) &qdctlr[0]
	},
	{
	(struct	isa_driver *) 0,
	(long)	1,		/* unit number on the system */
	(long)	1,		/* ctlr number; -1 if none */
	(long)	0,		/* slave on controller */
	(long)	0,		/* Was it found at config time? */
	(caddr_t) 0x02a0,	/* csr address */
	(long) SPLTTY,		/* SPL level for interrupt */
	(long)	7,		/* pic line upon interrupt */
	(long)	0,		/* if init 1 set to number for iostat */
	(long)	0,		/* parameter from system specification */
	(int)	0,		/* interrupt handler(s) */
	(caddr_t) 0x01a0,	/* start address in mem space */
	(u_long)(0x01bf-0x01a0),	/* length of mem space used */
	(long)	0,		/* driver specific type information */
	(struct	isa_dev *) 0,
	(struct	isa_ctlr *) &qdctlr[1]
	}
};

struct tty qd_tty[ MAX_PORTS ];    /* tty structures */
char 	qdprt[] = "Olivetti Summer Quadport Driver v1.0\n";

/* table of board I/O addresses */
int qd_offset[MAX_PORTS];

/* baud rate table of divisor latch values */
static int qd_speeds[] = {
	/* B0		*/	0,
	/* B50		*/	2304,
	/* B75		*/	1536,
	/* B110		*/	1047,
	/* B134		*/	857,
	/* B150		*/	768,
	/* B200		*/	0,
	/* B300		*/	384,
	/* B600		*/	192,
	/* B1200	*/	96,
	/* B1800	*/	64,
	/* B2400	*/	48,
	/* B4800	*/	24,
	/* B9600	*/	12,
	/* EXTA 19200	*/	6,
	/* EXTB 2000	*/	58
};

typedef struct {
	ushort	speed;
	ushort	qd_break;
	ushort	carrier;	/* are we local or a modem? */
	ushort	intr_vec;
	time_t	last_time;
} QD_AUX; 


static QD_AUX	qd_aux[ NQD * PORTS ];

static int	qd_poll[ NQD * PORTS ];

static int	qdtmrun = 0;

int qdprobe( reg, ctlr )
	caddr_t reg;
	int	ctlr;
{
	int i, addr;

	if ( ctlr > NQD ) {
		printf("heinous quad unit %d -- device ignored\n", ctlr );
		return( 0 );
	}

	/* Probe the scratch memory byte of the first UART. If found
	 * assume that all four are present.
	 */
	addr = (int) qdctlr[ctlr].ctlr_start;
	outb( addr + SCR, PROBE );
	if ( inb( addr + SCR ) == PROBE ) {
	  printf("qd%d found at 0x%x\n", ctlr, addr );
	  return( 1 );
	}
	return( 0 );
}

int qdattach( dev )
	struct isa_dev	*dev;
{
#ifdef undef
	struct tty	*tp;
#endif undef

	int ctlr = dev->dev_ctlr;
	int addr = (int)qdctlr[ctlr].ctlr_start;
	int unit = ctlr * PORTS;
	int i;

	qdctlr[ctlr].ctlr_alive = 1;
	for( i = 0; i < PORTS; i++) {
		qd_poll[ unit ] = 0;
 		qd_offset[ ( ctlr*PORTS ) + i ] = addr;
		qddisable( addr );
		addr += 8;
		unit++;
	}
	outb( qdctlr[ctlr].ctlr_addr, 0x80 );	/* enable board interrupts */

	printf( "qd%d attached\n", ctlr);

#ifdef undef
	for ( unit = firstport; unit <= lastport; unit++ ) {
		tp = &qd_tty[ unit ];
		tp->t_addr = (caddr_t) tp;
		tp->t_state = 0;
		tp->t_dev = unit;
		qd_aux[ unit ].carrier = 0;  /* for now, we are just local */
		qd_aux[ unit ].intr_vec = 0; /* gotta fill this in */
		qd_aux[ unit ].last_time = 0x7fffffffL;
	}
#endif undef
}

/*ARGSUSED*/
int qdopen( dev, flag )
	dev_t 	dev;
	int   	flag;
{
	int unit = minor( dev );
	int ctlr = unit / PORTS;
	int addr;
	struct	tty *tp;
	int o_pri;

#ifdef  DEBUGMEBABY
	printf( "qdopen( %d-%d, 0x%x ) called by user %d\n",
			     ctlr, unit, flag, (int) u.u_uid );
#endif  DEBUGMEBABY

	if ( (unit >= MAX_PORTS) ||
             (qdctlr[ctlr].ctlr_alive == 0)) {
		u.u_error = ENXIO;
		return;
	}

	addr = qd_offset[ unit ];
	tp = &qd_tty[ unit ];

	if (tp->t_state & TS_XCLUDE && u.u_uid != 0) {
		return( EBUSY) ;
	}

	if ( !(tp->t_state & (TS_ISOPEN|TS_WOPEN) ) ) {

		tp->t_addr = (caddr_t) tp;
		tp->t_state = 0;
		tp->t_dev = unit;

#ifdef  DEBUGMEBABY
		printf( "qdopen: init dev %x, stat %x, flags %x\n",
			     dev, tp->t_state, tp->t_flags);
#endif  DEBUGMEBABY
		
		if (flag & O_LOOPBACK) {
#ifdef  DEBUGMEBABY
			printf( "qdopen: loopback mode\n" );
#endif  DEBUGMEBABY
			inb( addr+MCR, inb( addr+MCR ) | LOOP );
		}

		qd_poll[ unit ] = addr;

		ttychars( tp );

		/*
		 *	Special support for boot-time rc scripts, which don't
		 *	stty the console.
		 */ 
		tp->t_oproc = qdstart;
		tp->t_ospeed = tp->t_ispeed = B9600;
		tp->t_flags = ODDP|EVENP|ECHO|CRMOD;
		tp->t_state &= ~TS_BUSY;

#ifdef undef
#ifndef NOLOOPBACK
		o_pri = spltty();
		if ( !qdtmrun ) {
			qd_aux[ unit ].last_time = 0x7fffffffL;
			qdtmout( (caddr_t) 0 );
		}
		splx( o_pri );
#endif NOLOOPBACK
#endif undef
		qdparam( unit );
	}
	o_pri = spltty();	
#ifdef undef
	if ( (!qd_aux[ unit ].carrier) || (qdmodem( unit, TURNON )) ) {
		tp->t_state |= TS_CARR_ON;
	} else {
		tp->t_state &= ~TS_CARR_ON;
	}
#endif undef
/* for now assume that the remote terminal is there */
tp->t_state |= TS_CARR_ON;

        while ( !(tp->t_state & TS_CARR_ON) ) {
                tp->t_state |= TS_WOPEN;
                if ( sleep( (caddr_t) &tp->t_rawq, TTIPRI ) ) {
                        tp->t_state &= ~TS_WOPEN;
                } else {
                	u.u_error = EINTR;
                	splx( o_pri );
                	return( -1 );
		}
        }

	if ( (*linesw[ tp->t_line ].l_open)( dev, tp ) ) {
		qdclose( dev, flag );
	}

#ifdef  DEBUGMEBABY
	printf( "qdopen complete\n" );
#endif  DEBUGMEBABY

	splx( o_pri );
	return( 0 );

}	/* qdopen */

int qdclose(dev)
	unsigned dev;
{
	register struct tty *tp;
	register int addr;
	register int unit = minor( dev );

	tp = &qd_tty[ unit ];
	addr = qd_offset[unit];

	(*linesw[ tp->t_line ].l_close)( tp );

       /*
	  We ALWAYS close things down, regardless of TS_WOPEN,
	  TS_HUPCLS, TS_ISOPEN.
	*/

	qd_poll[ unit ] = 0;
	qddisable( addr );	/* had a bogus TURNOFF here....  */
	ttyclose( tp );		/* do we really need to do this? */
}

int qdread( dev, uio )
	int		dev;
	struct	uio * 	uio;

{
	struct	tty*	tp;
	int 		unit;
  
#ifdef  debugmebaby
	printf( "qdread( %d-%d, uio )\n",
			     major(dev), minor(dev) );
#endif  debugmebaby
	unit = minor( dev );
	tp = &qd_tty[ unit ];
	return( (*linesw[tp->t_line].l_read)( tp, uio ) );
}


int qdwrite( dev, uio )
	int		dev;
	struct	uio * 	uio;

{
	struct tty *	tp;
	int		unit;

#ifdef  debugmebaby
	printf( "qdwrite( %d-%d, uio ) called\n",
			     major(dev), minor(dev) );
#endif  debugmebaby
	unit = minor( dev );
	tp = &qd_tty[ unit ];
	return( (*linesw[ tp->t_line ].l_write)( tp, uio ) );
}
 

/*
 * we make the following assumption:
 *	the data parameter is either a pointer to an int, in the event
 *	of an TIOCMGET or an int in case of TIOC[CM]{BRK,DTR,SET,BIS,BIC}.
 * 	In case its one of the latter, we assume it contains the bit
 *	pattern in the lower order byte.  For a TIOCMBIC, we assume that
 *	that the presence of a bit means that bit should be cleared in
 *	the modem control register.  C'est tout.
 */
int qdioctl( dev, cmd, data, mode )
	int	dev;
	int	cmd;
	caddr_t	data;
	int	mode;
{
	int	    	unit;
	struct tty *	tp;
	register int	o_pri;
	register int	err = 0;
	long 		addr;

	unit = minor( dev );
	tp = &qd_tty[ unit ];

	addr = qd_offset[ unit ];
#ifdef debugmebaby
	printf( "qdioctl: writing to unit %d\n", unit );
#endif debugmebaby

	if ( (err = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, mode)) >= 0 )
		return( err );
	if ( (err = ttioctl(tp, cmd, data, mode)) >= 0 ) {
       		if ( cmd == TIOCSETP || 
		     cmd == TIOCSETN ||
		     cmd == TIOCLBIS ||
		     cmd == TIOCLBIC || 
		     cmd == TIOCLSET) {
			qdparam( unit );
			return( err );
		      }
		if (err != EINVAL ) {
		  return( err );
		}
	}
	o_pri = spltty();
	err = 0;
	switch ( cmd ) {
	  case TIOCSBRK: 		/* Set break */
#ifdef DEBUGMEBABY
		printf( "qdioctl: setting TIOCSBRK\n" );
#endif DEBUGMEBABY
		outb( addr+LCR, inb( addr+LCR ) | BREAK );
		break;
	  case TIOCCBRK:		/* Clear break */
#ifdef DEBUGMEBABY
		printf( "qdioctl: clearing TIOCCBRK\n" );
#endif DEBUGMEBABY
		outb( addr+LCR, inb( addr+LCR ) & ~BREAK );
		break;
	  case TIOCSDTR:		/* Set DTR and RTS */
#ifdef DEBUGMEBABY
		printf( "qdioctl: setting DTR and RTS\n" );
#endif DEBUGMEBABY
		outb( addr+MCR, inb( addr+MCR ) | DTR | RTS );
		break;
	  case TIOCCDTR:		/* Clear DTR and RTS */
#ifdef DEBUGMEBABY
		printf( "qdioctl: clearing DTR and RTS\n" );
#endif DEBUGMEBABY
		outb( addr+MCR, inb( addr+MCR ) & ~DTR & ~RTS );
		break;
	  case TIOCMSET:		/* Set all bits */
#ifdef DEBUGMEBABY
		printf( "qdioctl: setting everything in sight\n" );
#endif DEBUGMEBABY
		outb( addr+MCR, DTR | RTS | OUT1 | OUT2 | LOOP );
		break;
	  case TIOCMBIS:		/* Set particular bits */
#ifdef DEBUGMEBABY
		printf( "qdioctl: setting MCR bits %x\n", (int)0xff & (int)data );
#endif DEBUGMEBABY
		outb( addr+MCR, inb( addr+MCR ) | ((int)0xff & (int)data) );
		break;
	  case TIOCMBIC:
#ifdef DEBUGMEBABY
		printf( "qdioctl: clearing MCR bits %x\n", (int)0xff & (int)data );
#endif DEBUGMEBABY
		outb( addr+MCR, inb( addr+MCR ) & ~((int)0xff & (int) data) );
		break;
	  case TIOCMGET:
		*(int *) data = inb( addr+MCR );
#ifdef DEBUGMEBABY
		printf( "qdioctl: read MCR: %x\n", data );
#endif DEBUGMEBABY
		break;
  
	  default:
		err = ENOTTY;
		break;
	}
	splx(o_pri);
#ifdef DEBUGMEBABY
	printf( "qdioctl: returning\n" );
#endif DEBUGMEBABY
	return( err );
}


int qdintr( vec )
	unsigned vec;
{
	register int unit;
	register int addr;
	register int iir;
	register int again = 1;
	int opri;
	unsigned char units;

	opri = spl5();
#ifdef DEBUGMEBABY
	printf( "qdintr( %x ) intr: 0x%x\n", vec, (~units) & 0xf );
	units = inb( 0x01bf );
#endif DEBUGMEBABY

	do {
		again = 0;
		for (unit=0; unit < MAX_PORTS; unit++)
			if (addr = qd_poll[unit]) {
				while ((( iir = inb( addr+IIR ) )&0x01) == 0) 
				{
#ifdef debugmebaby
printf("Unit %d @ 0x%x iir 0x%x\n",unit, addr,iir);
#endif debugmebaby
					again = 1;

					switch (iir & 0x06)
					{
						case 4:	/* receive */
							qdrint( unit ); 
							break;

						case 2:	/* xmit */
							qdxint( unit );
							break;

						case 0: /* modem status */
							qdmint( unit );
							break;

						case 6: /* line status */
							/* should not get */
							inb( addr+LSR );
							break;
						default:
							printf("qdintr: intr error\n");
					}
				}
			      }
	} while (again);
#ifdef DEBUGMEBABY
	if (unit == MAX_PORTS) printf("qdintr: done\n");
#endif DEBUGMEBABY
	outb( 0x2f0 + vec, 0 );
	splx( opri );
}

void qdxint( unit )
	unsigned unit;
{
	register struct tty *	tp = &qd_tty[unit];
	register int 		addr = qd_offset[unit];
	int lsr;

	lsr = inb( addr + LSR );
#ifdef debugmebaby
	printf( "qdxint: unit %d @ 0x%x lsr 0x%x\n", unit, addr, lsr );
#endif debugmebaby
	if ( lsr & THRE ) {
		tp->t_state &= ~TS_BUSY; 	/* why do we 
						   turn TS_BUSY off?? */
		/* the a8 driver does some crazy stuff here */
		if ( tp->t_line ) {
			(*linesw[tp->t_line].l_start)(tp);
		} else {
			qdstart( tp );
		}
	}
#ifdef debugmebaby
	printf( "qdxint: done\n", unit );
#endif debugmebaby
}

void qdrint( unit )
	unsigned unit;
{
	register struct tty 	*tp;
	register int 		addr;
	int			c;
	int			status;

#ifdef debugmebaby
	printf( "qdrint: processing interrupt on unit %d\n", unit );
#endif debugmebaby
	tp = &qd_tty[ unit ];
	addr = qd_offset[ unit ];

	c = inb( addr+RBR );
	status = inb( addr+LSR );


	/* what's the BSD equivalent? */
/*
	flg = tp->t_iflag;

	if (flg & IXON){

		ctmp = c & 0177;
		if (tp->t_state & TTSTOP){
			if (ctmp == CSTART || flg & IXANY)
				(*tp->t_proc)(tp, T_RESUME);
		} else {
			if (ctmp == CSTOP)
				(*tp->t_proc)(tp, T_SUSPEND);
		}
		if (ctmp == CSTART || ctmp == CSTOP)
			return;
	}
*/



	/* check errors */
	if (status & STHRERR)
	{
		if (status & OE) {
			printf("qd over run error on unit %d\n", unit);
		}
		if (status & PE) {
			printf("qd parity error on unit %d\n", unit );
		}
		if (status & FE) {
			printf("qd framing error on unit %d\n", unit );
		}
	}

	/* What's the BSD equivalent? */
	/*
	if (c & CTHRERR) {
		if ((c & 0377) == 0){
			if (flg & IGNBRK) {
				return;
			}
			if (flg & BRKINT) {
				(*linesw[tp->t_line].l_input)(tp, L_BREAK);
				return;
			}
		} else {
			if (flg & IGNPAR)
				return;
		}
	} else {
		if (flg & ISTRIP) {
			c &= 0177;
		} else {
			c &= 0377;
		}
	}
	*/
	(*linesw[tp->t_line].l_rint)( c, tp );
#ifdef debugmebaby
	printf( "qdrint: read <%x> -- done\n", c );
#endif debugmebaby
}

void qdmint(unit)
	unsigned unit;

{
	register struct tty *tp = &qd_tty[unit];
	int addr = qd_offset[unit];
	int status;

	status = inb(addr+MSR);	/* get status and reset interrupt */

	/* Where do we want to squirrel away this state? */
	/*
	if (tp->t_cflag & CLOCAL)
		return;
	*/

	if (status & DDCD) {
		if (status & DCD) {
			if ((tp->t_state & TS_CARR_ON) == 0) {
				tp->t_state |= TS_CARR_ON;
				/* is this the right guy to wakeup? */
                		wakeup(&tp->t_rawq);
			}
		} else {
			if (tp->t_state & TS_CARR_ON) {
				if (tp->t_state & (TS_ISOPEN | TS_WOPEN)) {
					(*linesw[tp->t_line].l_modem)(tp, 0);
					qdmodem( unit, TURNOFF );
				}
				tp->t_state &= ~TS_CARR_ON;
			}
		}
	}
}


void qdparam( unit )
	register int unit;
{
	struct tty 	*tp;
	register int	addr;
	int 		o_pri;
	unsigned char lcr;
	int		n;

	tp = &qd_tty[unit];
	addr = qd_offset[unit];

	o_pri = spltty();

	/* hang up if line speed is 0 */
	if (tp->t_ispeed == B0) {
		(*linesw[tp->t_line].l_modem)(tp, 0);
		qdreset( addr );
		splx( o_pri );
		return;
	}

	/* set up line speed */
	if (n = qd_speeds[tp->t_ispeed]) {
#ifdef debugmebaby
		printf("qd unit %d setting speed divisor to %d\n", unit, n );
#endif debugmebaby
		/* enable access to divisor latch */
		lcr = inb(addr+LCR) | DLAB;
		outb( addr+LCR, lcr);
		/*set baud rate	*/
		outb( addr+DLM , (n >> 8) & 0xff ); 
		outb( addr+DLL , n & 0xff);
		lcr &= ~DLAB;
		/* disable divisor latch access */
		outb( addr+LCR, lcr );
	}

/* this is what the DZ11 driver does, almost verbatim .. */
	if ( tp->t_flags & (RAW | LITOUT | PASS8) ) {
		n = WLS0|WLS1; 
	} else {
		n = WLS1|PEN;
	}

	if (tp->t_flags & EVENP) {
		n |= EPS;
	}

	if (tp->t_ispeed == B110) {  /* This is a kludge.  But there  */
		n |= STB; 	     /* appears to be no clean way to */
	}			     /* specify the number of stop    */
				     /* bits (missing in the ioctl.h  */
				     /* file!).			      */
/* .. which doesn't mean we have to, though. */
	/* Turn on eight bits of character */
	/* For now we always do the default, ie. 2 stop bits, no 
	   parity, no handshake, 8 data bits, no sex drives or
	   handshaking */
	qdreset( addr );
	splx(o_pri);
}

/* 
 * This is really different than the a8 driver. It does a bunch of
 * crap with a "cmd" argument.
 */

int qdstart( tp )
	register struct tty *tp;
{
	int	  	unit;
	int       	o_pri;
	int		addr;
	int		c;

	unit = minor(tp->t_dev);

#ifdef DEBUGMEBABY
	printf( "qdstart( tp ) called\n" );
#endif DEBUGMEBABY
	o_pri = spltty();

	/* If we are stopped, doing a break, or busy, no-op */
	if (tp->t_state & (TS_TIMEOUT|TS_TTSTOP|TS_BUSY))
	{
		splx(o_pri);
#ifdef DEBUGMEBABY
		printf( "qdstart: premature return (state %s %s %s)\n",
			((tp->t_state & TS_TIMEOUT) ? "TIMEOUT" : ""),
			((tp->t_state & TS_TTSTOP) ? "STOP" : ""),
			((tp->t_state & TS_BUSY) ? "BUSY" : "") );
#endif DEBUGMEBABY
		return;
	}

	/*
	   Of the next two sections, which comes first?  dz does it this
	   way, mCOM the other?
	 */
	if (tp->t_outq.c_cc <= TTLOWAT(tp) )
	{
		if (tp->t_state & TS_ASLEEP)	
		{
			tp->t_state &= ~TS_ASLEEP;
			wakeup ( (caddr_t)  &tp->t_outq);
		}
		if (tp->t_wsel)
		{ 
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel =0;
			tp->t_state &= ~TS_WCOLL;
		}
	}

	if ((tp->t_outq.c_cc <=0)  ||
	    ((c=getc(&tp->t_outq)) == -1)) {
#ifdef DEBUGMEBABY
		printf( "qdstart: marking tty ~BUSY\n" );
#endif DEBUGMEBABY
		tp->t_state &=~TS_BUSY;
		splx(o_pri);
		return;
	} else if (tp->t_flags & (RAW|LITOUT) || (c <= 0177)) {
		addr = qd_offset[ unit ];
#ifdef debugmebaby
		printf("qdstart: sending a %c to 0x%x\n", c, addr+THR);
#endif debugmebaby
		outb( addr+THR, c );
		tp->t_state |= TS_BUSY;
		qd_aux[unit].last_time = time.tv_sec;
	} else {
		printf( "qdstart: timing out\n" );
		timeout(ttrstrt, (caddr_t)tp,  (c & 0177));
		tp->t_state |= TS_TIMEOUT;
	}

#ifdef DEBUGMEBABY
	printf( "qdstart: done\n" );
#endif DEBUGMEBABY
	splx(o_pri);
}

void qddisable( addr )
	int addr;
{
	outb( addr+IER, 0 );
	outb( addr+MCR, inb( addr+MCR ) & ~( DTR | RTS ) );
}

void qdreset( addr )
	int 	addr;
{
	outb( addr+IER, (ERBFI | ETBEI) );
	outb( addr+LCR, (WLS0 | WLS1 | STB) );
	outb( addr+MCR, inb(addr+MCR) | DTR | RTS );
}

int qdmodem( unit, cmd )
	unsigned unit, cmd;
{
	register int addr = qd_offset[unit];

	switch(cmd) {
	case TURNON:		/* enable modem ints, set DTR and RTS */
		outb( addr + IER, (inb( addr+IER ) | EDSSI ) );
		outb( addr + MCR, (inb( addr+MCR ) | DTR | RTS ) );
		break;
	case TURNOFF:		/* disable modem ints, drop DTR and RTS */
		outb( addr + IER, (inb( addr+IER ) & ~EDSSI ) );
		outb( addr + MCR, (inb( addr+MCR ) & ~DTR & ~RTS ) );
		break;
	}
	return( inb( addr+MSR ) & DCD );
}


/* ARGSUSED */
void qdtmout( notused )
	caddr_t notused; 
{
	int		unit;
	time_t		diff;
	int    		o_pri;

	for (unit = 0; unit < PORTS; unit++) {
		if (( diff = time.tv_sec - qd_aux[unit].last_time) > MAXTIME) {
			/* assume interrupt was missed & COM has crashed */
			printf( "quad - reset\n" );
			o_pri = spltty();
			qdparam( unit );

			qdintr( qd_aux[unit].intr_vec );
			splx( o_pri );
		}
	}
	qdtmrun = 1;
	timeout( qdtmout, (caddr_t)0, 100 /* HZ <- locate this #define !! */);
}
#endif NQD
