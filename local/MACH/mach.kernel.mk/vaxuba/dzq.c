/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dzq.c,v $
 * Revision 2.3  89/03/09  22:34:08  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:02:39  gm0w
 * 	Changes for cleanup.
 * 
 * 07-Jan-86  Jerry Agin (agin) at Carnegie-Mellon University
 *	Added unix interfaces.
 *
 */
/*
 * Created by Phillip McKerrow 14 Oct 1985
 * This driver created by modifying (extensively) dz.c
 *
 */

/* dzq.c: Special device drivers for the assy vax. */

#include <dzq.h>

#if	NDZQ > 0


#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/file.h>
#include <sys/uio.h>

#include <vaxuba/ubavar.h>
#include <vaxuba/dzqreg.h>
#include <vaxuba/dzqio.h>

#define BUFSIZ 512
#define MARGIN ( BUFSIZ / 4 )

struct dzqbuf {
	char *inptr;
	char *outptr;
	char buf[BUFSIZ];
};

struct dzqtty {
	struct tty tty;		/* The standard unix structure */
	struct dzqbuf readbuf;	/* We supply our own fixed read ... */
	struct dzqbuf writebuf;	/* ... and write buffers */
	int open;
	int outputactive;
	int w_holding;		/* write is holding */
	int r_holdstate;	/* Read hold request:
				 * 0: no problem
				 * 1: overflow imminent, ^S needs to be sent
				 * 2: ^S has been sent
				 * 3: buffer has space, ^Q needs to be sent */
	int r_asleep;		/* Sleep waiting for read */
	struct proc *process;	/* Pointer to the process that opened it */
	int pumamode;		/* Special mode to deal with VAL's
				 * one-character input buffer.  When a
				 * character has been sent, wait for it to echo
				 * before sending any more characters */
	char pumawait;		/* Character we're waiting for */
	int astekmode;		/* Special mode for continuous input data.
				 * Do not take interrupts until a read
				 * request has been made, then turn
				 * interrupts off when read is satisfied */
	int astekrequest;	/* Number or chars initially requested */
	int astekcount;		/* Number of chars still to read */
	struct dzqerr err;	/* Structure to hold error counts */
};
struct dzqtty dzqtty[4];

struct dzqdevice *dzqaddr;

/*
 * Driver information for auto-configuration stuff.
 */
int	dzqprobe(), dzqattach(), dzqrint();
struct	uba_device *dzqdinfo[NDZQ];	/* device structure declared in conf.c */
u_short	dzqstd[] = { 0160100, 0 };
struct	uba_driver dzqdriver =
	{ dzqprobe, 0, dzqattach, 0, dzqstd, "dzq", dzqdinfo };


dzqprobe(reg)
	caddr_t reg;
/* executed at startup by system to find interrupt vector */
/* causes transmit interrupt, from which system determines vector */
{
	register int br, cvec;
	register struct dzqdevice *dzqaddr = (struct dzqdevice *) reg;
#ifdef	lint
	br = 0; cvec = br; br = cvec;
#endif
	cvec = 0;
	dzqaddr->dzqcsr = DZQ_MSE|DZQ_TIE;
	dzqaddr->dzqtcr = DZQ_TXEN0;
	DELAY(100000);
	dzqaddr->dzqcsr = DZQ_CLR;
	if ( cvec == 0 )
	{
		printf ( "dzq not found.\n" );
		return 0;
	}
	else
	{
	    cvec -= 4;	/*get rxint vector from txint vector*/
	    return (sizeof(struct dzqdevice));
	}
}

dzqattach(ui)
	register struct uba_device *ui;
{
	dzqaddr = (struct dzqdevice *) dzqdinfo[0]->ui_addr;
}



dzqinitbuf ( buf )
	struct dzqbuf *buf;
{
	buf->inptr = buf->outptr = buf->buf;
}

int dzqput ( buf, c )
	struct dzqbuf *buf;
	char c;
{
	char *next;

	next = buf->inptr + 1;
	if ( next >= buf->buf + BUFSIZ )
		next = buf->buf;
	if ( next == buf->outptr )
		return 0;	/* buffer is full */
	*buf->inptr = c;
	buf->inptr = next;
	return 1;
}

int dzqputprevious ( buf, c )
	struct dzqbuf *buf;
	char c;
{
	char *prev;

	prev = buf->inptr - 1;
	if ( prev < buf->buf )
		prev = buf->buf + BUFSIZ - 1;
	*prev = c;
}

int dzqtake ( buf, cp )
	struct dzqbuf *buf;
	char *cp;
{
	char *next;

	if ( buf->inptr == buf->outptr )
		return 0;	/* buffer is empty */
	*cp = *buf->outptr;
	next = buf->outptr + 1;
	if ( next >= buf->buf + BUFSIZ )
		next = buf->buf;
	buf->outptr = next;
	return 1;
}

int dzqnchars ( buf )
	struct dzqbuf *buf;
{
	int nchars;

	nchars = buf->inptr - buf->outptr;
	if ( nchars < 0 )
		nchars += BUFSIZ;
	return nchars;
}

int dzq_speeds[] =
	{ 0, 0, 0400, 01000, 01400, 02000, 0, 02400,
	  03000, 03400, 04000, 05000, 06000, 07000, 07400, 0};

dzqrgo ( unit, speed )
/* Turn on input */
{
	unsigned short local_lpr;

	local_lpr = DZQ_8BIT | DZQ_RXENAB | (unit&DZQ_SEL) | dzq_speeds[speed];
	dzqaddr->dzqlpr = local_lpr;
}
 
dzqrstop ( unit )
/* Turn off input */
{
	unsigned short local_lpr;

	/* According to the manual, the RX ENAB bit is turned off only by
	 * BINIT or device Master Clear.  What's more, any write to the LPR
	 * seems to turn on RX ENAB regardless of bit 12.  The following is
	 * counterproductive, hence it's commented out */

	/* local_lpr = DZQ_8BIT | dzq_speeds[B9600] | (unit&DZQ_SEL) ; */
	/* dzqaddr->dzqlpr = local_lpr; */
}

dzqxgo ( unit )
/* Turn on output */
{
	unsigned short local_tcr;

	dzqtty[unit].outputactive = 1;
	local_tcr = dzqaddr->dzqtcr;
	local_tcr |= (1 << unit);
	dzqaddr->dzqtcr = local_tcr;
}

dzqxstop ( unit )
/* Turn off output */
{
	unsigned short local_tcr;

	local_tcr = dzqaddr->dzqtcr;
	local_tcr &= ~ (1 << unit);
	dzqaddr->dzqtcr = local_tcr;
	dzqtty[unit].outputactive = 0;
}

dzq_clear_stats ( dp )
	struct dzqtty *dp;
{
	struct dzqerr *ep;

	ep = &dp->err;
	ep->nparity = 0;
	ep->nframe = 0;
	ep->nover_h = 0;
	ep->nover_s = 0;
	ep->maxchars = 0;
}

dzqopen(dev, flag)
	dev_t dev;
	int flag;		/* ignored */
{
	register int unit;
	struct dzqtty *dp;
	struct tty *tp;
	unsigned short local_csr;

	dzqtrc('#','O');
	unit = minor(dev);
	if ( unit >= 4 ) return ENXIO;

	dp = &dzqtty[unit];
	dzqinitbuf ( &dp->readbuf );
	dzqinitbuf ( &dp->writebuf );
	dp->open = 1;
	dp->outputactive = 0;
	dp->w_holding = 0;
	dp->r_holdstate = 0;
	dp->process = u.u_procp;
	dp->pumamode = 0;
	dp->pumawait = 0;
	dp->astekmode = 1;	/* Default to astek mode */
	dp->astekcount = dp->astekrequest = 0;
	dzq_clear_stats(dp);

	tp = &dp->tty;
	tp->t_dev = dev;
	tp->t_pgrp = u.u_procp->p_pid;
	tp->t_state |= TS_ISOPEN;
	tp->t_flags == RAW | TANDEM;	/* Defaults */
	tp->t_ispeed = tp->t_ospeed = B9600; /* Defaults */

	while ( dzqaddr->dzqcsr & DZQ_CLR ) ; /* Busy wait if master clear
					      * is in progress */
	local_csr = DZQ_MSE | DZQ_RIE | DZQ_TIE;
	dzqaddr->dzqcsr = local_csr;

	return 0;
}

dzqclose(dev, flag)
	dev_t dev;
{
	int unit, s;
	struct dzqtty *dp;
	struct tty *tp;

	unit = minor(dev);
	dp = &dzqtty[unit];
	tp = &dp->tty;

	dzqrstop ( unit );

	/* Don't leave remote system holding with ^S */
	if ( dp->r_holdstate == 2 ) {
		dp->r_holdstate = 3;
		dzqxgo(unit);
	}

	/* Wait for output queue to empty */
	s = spl5();
	while ( dp->outputactive ) {
		tp->t_state |= TS_ASLEEP;
		sleep((caddr_t)&tp->t_outq, TTOPRI);
	}
	splx(s);

	tp->t_state = 0;
	dp->open = 0;
	for ( unit=0; unit<4; unit++ )
		if ( dzqtty[unit].open ) break;
	if ( unit == 4 )	/* No more devices open */
		dzqaddr->dzqcsr = DZQ_CLR;
	dzqtrc('#','C');
}
 
dzqread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	int unit, error, s, nr, nc;
	char c;
	struct dzqtty *dp;
	struct tty *tp;

	unit = minor(dev);
	dp = &dzqtty[unit];
	tp = &dp->tty;

	error = 0;
	nr = uio->uio_resid;
	if ( nr <= 0 ) return 0;
	if ( nr > BUFSIZ-2 ) nr = BUFSIZ - 2;

	if ( dp->astekmode ) {
		dzqinitbuf ( &dp->readbuf );
		dp->astekrequest = dp->astekcount = nr;
		dzqrgo ( unit, tp->t_ispeed );
	}

	s = spl5();
	while ( dzqnchars ( &dp->readbuf ) <= 0
		    || ( dp->astekmode && dp->astekcount ) ) {
		if ( tp->t_state&TS_NBIO )  {
			splx(s);
			return ( EWOULDBLOCK );
		}
		dp->r_asleep = 1;
		sleep((caddr_t)&tp->t_rawq, TTIPRI);
	}
	splx(s);

	while ( !error && uio->uio_resid  && dzqtake ( &dp->readbuf, &c ) )
		error = ureadc ( c, uio );

	s = spl5();
	if ( dp->r_holdstate==2 && dzqnchars(&dp->readbuf) < MARGIN ) {
		dp->r_holdstate = 3;
		dzqxgo ( unit );
	}
	splx(s);

	return (error);
}
 
dzqrint()
{
	int unit, data, nchars, s;
	struct dzqtty *dp;
	struct tty *tp;
	char c;
	int dosig[4];

	for ( unit=0; unit<4; unit++ )
		dosig[unit] = 0;
	while ( ( data = dzqaddr->dzqrbuf ) & DZQ_RXDVALD ) {
		unit = ( data & DZQ_RXLINE ) >> 8;
		dp = &dzqtty[unit];
		tp = &dp->tty;
		c = data & DZQ_RXDATA;
		if ( dp->astekmode ) {
			if ( dp->astekcount <= 0 ) {
				dzqtrc('[','.');
			} else if ( data & DZQ_RXERR ) {
				/* On a read error, start over */
				dzqinitbuf ( &dp->readbuf );
				dp->astekcount = dp->astekrequest;
				dzqtrc ( '#', 'E' );
			} else {
				dzqtrc('<',c);
				dzqput ( &dp->readbuf, c );
				if ( --dp->astekcount == 0 ) {
					dzqrstop ( unit );
					dosig[unit] = 1;
				}
			}
		} else if ( data & DZQ_RXERR ) {
			if ( data & DZQ_RXPE ) dp->err.nparity++;
			else if ( data & DZQ_RXFE ) dp->err.nframe++;
			else if ( data & DZQ_RXDO ) dp->err.nover_h++;
			dzqtrc('#','E');
		} else if ( c == 023 && tp->t_flags&TANDEM ) { /* control-s */
			dp->w_holding = 1;
			dzqtrc('#','S');
		} else if ( c == 021 && tp->t_flags&TANDEM ) { /* control-q */
			dp->w_holding = 0;
			dzqxgo ( unit );
			dzqtrc('#','Q');
		} else {
			if ( ! dzqput ( &dp->readbuf, c ) ) {
				dzqputprevious ( &dp->readbuf, 0377 );
				dzqtrc ( '#', 'B' );
				dp->err.nover_s++;
			}
			else dzqtrc('<',c);
			if ( dp->pumawait && ( c == dp->pumawait ) ) {
				dp->w_holding = 0;
				dp->pumawait = 0;
				dzqxgo(unit);
			}
			nchars = dzqnchars(&dp->readbuf);
			if ( nchars > dp->err.maxchars )
				dp->err.maxchars = nchars;
			if ( tp->t_flags&TANDEM
			    && dp->r_holdstate==0
			    && nchars+MARGIN > BUFSIZ ) {
				dp->r_holdstate = 1;
				dzqxgo ( unit );
			}
			dosig[unit] = 1;
		}
	}
	for ( unit = 0; unit<4; unit++ )
		if ( dosig[unit] ) {
			dp = &dzqtty[unit];
			tp = &dp->tty;
			if ( tp->t_state & TS_ASYNC
			    && dp->process->p_stat) {
				psignal ( dp->process, SIGIO );
			}
			if ( dp->r_asleep ) {
				dp->r_asleep = 0;
				wakeup ( (caddr_t)&tp->t_rawq );
			}
		}
}

dzqwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	int unit, error, s, cnt;
	struct dzqtty *dp;
	struct tty *tp;
	char c;

	unit = minor(dev);
	dp = &dzqtty[unit];
	tp = &dp->tty;

	error = 0;
 	cnt = uio->uio_resid;
 	while ( uio->uio_resid > 0 ) {
		error = uiomove ( &c, 1, UIO_WRITE, uio );
		if ( error ) break;
		s = spl5();
		while ( ! dzqput ( &dp->writebuf, c ) ) {
			if ( tp->t_state&TS_NBIO ) {
				error = ( uio->uio_resid == cnt )
							? EWOULDBLOCK : 0;
				splx ( s );
				return ( error );
			}
			tp->t_state |= TS_ASLEEP;
			sleep ( (caddr_t)&tp->t_outq, TTOPRI );
		}

		if ( ! dp->outputactive && ! dp->w_holding )
			dzqxgo ( unit );
		splx ( s );
	}
	return(error);
}
 

dzqxint()
{
	int unit;
	unsigned short local_csr;
	unsigned char data;
	struct dzqtty *dp;
	struct tty *tp;

	local_csr = dzqaddr->dzqcsr;
	if ( ! local_csr & DZQ_TRDY )
		printf ( "dzqxint: transmitter not ready.  csr=0%o\n", local_csr );

	unit = ( local_csr & DZQ_TLINE ) >> 8;
	dp = &dzqtty[unit];
	tp = &dp->tty;
	if ( dzqnchars ( &dp->writebuf ) <= MARGIN
			&& tp->t_state & TS_ASLEEP ) {
		tp->t_state &= ~TS_ASLEEP;
		wakeup ( (caddr_t) &tp->t_outq );
	}

	if ( dp->r_holdstate==1 ) {
		dzqaddr->dzqtdr = 023; /* control-s */
		dp->r_holdstate = 2;
		dzqtrc('#','s');
	}
	else if ( dp->r_holdstate==3 ) {
		dzqaddr->dzqtdr = 021; /* control-q */
		dp->r_holdstate = 0;
		dzqtrc('#','q');
	}
	else if ( dp->w_holding ) {
		dzqxstop ( unit );
	}
	else if ( ! dzqtake ( &dzqtty[unit].writebuf, &data ) ) {
		dzqxstop ( unit );
	}
	else {
		dzqaddr->dzqtdr = data;
		dzqtrc('>',data);
		if ( dp->pumamode )
		    if ( dp->pumamode == DZQPUMACR
			    && ( data==015 || data==012 )
			 || dp->pumamode == DZQPUMA
			    && data>037 && data<0177 ) {
			dp->w_holding = 1;
			dp->pumawait = data;
		}
	}
}

/* Prefix characters for tracing:
 *	# Control function
 *		O open
 *		C close
 *		E read error
 *		S ^S received in tandem mode
 *		Q ^Q received in tandem mode
 *		B read buffer overflow
 *		s ^S sent in tandem mode
 *		q ^Q sent in tandem mode
 *	> Characters sent
 *	< Characters received
 *	[ Characters received and ignored in astek mode
 */

static char debstring[DZQTRACECHARS];
static char *debptr=debstring;
static char oldprefix = 0;

dzqtrc ( prefix, c )
	char prefix, c;
{
	int s;

	s = spl5();
	if ( prefix != oldprefix ) {
		if ( debptr >= debstring+DZQTRACECHARS )
			debptr = debstring;
		*debptr++ = prefix;
		oldprefix = prefix;
	}
	if ( prefix != '[' ) {
		if ( debptr >= debstring+DZQTRACECHARS )
			debptr = debstring;
		*debptr++ = c;
	}
	splx(s);
}

dzqtrace ( buf )
	char *buf;
{
	/* Print the last 1000 characters traced. */
	char *cp;
	int s;

	s = spl5();
	for ( cp=debptr; cp<debstring+DZQTRACECHARS; cp++ )
		*buf++ = *cp;
	for ( cp=debstring; cp<debptr; cp++ )
		*buf++ = *cp;
	splx(s);
}

dzqioctl(dev, cmd, data, flag)
	dev_t dev;
	caddr_t data;
{
	int unit, flags, s;
	struct dzqtty *dp;
	struct tty *tp;

	unit = minor(dev);
	dp = &dzqtty[unit];
	tp = &dp->tty;
	switch ( cmd ) {

	case FIONREAD:
		*(int *)data = dzqnchars ( &dp->readbuf );
		return 0;
	case TIOCOUTQ:
		*(int *)data = dzqnchars ( &dp->writebuf );
		return 0;
	case DZQTRACE:
		dzqtrace ( ((struct dzqtrace *)data)->trace );
		return 0;
	case DZQREPORT:
		*(struct dzqerr *)data = dp->err;
		return 0;
	case DZQMODE:
		/* Select among local modes */
		spl5();
		dp->pumamode = ( *(int *)data == DZQPUMA ? DZQPUMA
			: *(int *)data == DZQPUMACR ? DZQPUMACR
			: 0 );
		dp->astekmode = ( *(int *)data == DZQASTEK );
		if ( dp->astekmode )
			dzqrstop ( unit );
		else
			dzqrgo ( unit, tp->t_ispeed );
		flags = FREAD | FWRITE;
		goto flush;
	case TIOCFLUSH:
		flags = *(int *)data;
		spl6();
flush:		if ( flags & FREAD ) {
			if ( dp->r_holdstate == 1 ) dp->r_holdstate = 0;
			else if ( dp->r_holdstate == 2 ) {
				dp->r_holdstate = 3;
				dzqxgo(unit);
			}
			dp->astekcount = 0;
			dzqinitbuf ( &dp->readbuf );
			wakeup((caddr_t)&tp->t_rawq);
		}
		if ( flags & FWRITE ) {
			wakeup((caddr_t)&tp->t_outq);
			dzqinitbuf ( &dp->writebuf );
			dp->pumawait = 0;
			dp->w_holding = 0;
		}
		splx ( s );
		return 0;
	case TIOCSETP:
	case TIOCSETN: {
		struct sgttyb *sg;
		sg = (struct sgttyb *) data;
		tp->t_ispeed = sg->sg_ispeed;
		tp->t_ospeed = sg->sg_ospeed;
		if ( ! dp->astekmode )
			dzqrgo ( unit, tp->t_ispeed );
		tp->t_flags = ( tp->t_flags & 0xffff0000 )
				| ( sg->sg_flags & 0x0000ffff );
		return 0;
	}
	case TIOCSTOP:
	case TIOCSTART:
	case TIOCSTI:
		/* These ioctls are disabled */
		return 0;
	default:
		if ( ttioctl ( tp, cmd, data, flag) )
			return ( ENOTTY );
		return 0;
	}
}

/* dzqstart ( tp )
/* 	register struct tty *tp;
/* {
/* 	int unit;
/* 	struct dzqtty *dp;
/* 
/* 	dp = (struct dzqtty *) tp; /* HACK! */
/* 	if ( dzqnchars ( &dp->writebuf ) <= MARGIN
/* 			&& tp->t_state & TS_ASLEEP ) {
/* 		tp->t_state &= ~TS_ASLEEP;
/* 		wakeup ( (caddr_t) &tp->t_outq );
/* 	}
/* 	unit = minor ( tp->t_dev );
/* 	dzqxgo ( unit );
/* }
 */

dzqstop(tp,flag)
	register struct tty *tp;
{
	printf ( "dzqstop.\n" );
}


dzqreset(uban)
	int uban;
{
	printf("dzqreset.\n");
}

#endif	NDZQ > 0
