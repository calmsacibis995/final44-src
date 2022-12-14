h01799
s 00001/00001/00439
d D 1.6 91/05/16 18:04:32 marc 6 5
c pass flags from device close to l_close
e
s 00014/00014/00426
d D 1.5 90/12/16 16:49:44 bostic 5 4
c kernel reorg
e
s 00004/00013/00436
d D 1.4 90/09/03 17:26:39 karels 4 3
c sleep => tsleep; attempt to make compile
e
s 00034/00032/00415
d D 1.3 90/09/03 16:18:50 karels 3 2
c conversion to termios
e
s 00000/00001/00447
d D 1.2 90/02/17 10:18:27 mckusick 2 1
c get rid of dir.h
e
s 00448/00000/00000
d D 1.1 89/08/15 18:34:16 karels 1 0
c current version from monet
e
u
U
t
T
I 1
/*
 *  Datakit terminal driver
 *	SCCSID[] = "@(#)dktty.c	1.8 Garage 84/05/14"
I 3
 *		   "%W% (Berkeley) %G%"
E 3
 */

#include "dktty.h"
#if NDKTTY>0
#include "datakit.h"

D 5
#include "param.h"
#include "../machine/pte.h"
#include "syslog.h"
#include "errno.h"
#include "signal.h"
#include "conf.h"
D 2
#include "dir.h"
E 2
#include "user.h"
#include "proc.h"
#include "ioctl.h"
#include "tty.h"
#include "file.h"
#include "mbuf.h"
#include "uio.h"
#include "kernel.h"
E 5
I 5
#include "../include/pte.h"
#include "sys/param.h"
#include "sys/syslog.h"
#include "sys/errno.h"
#include "sys/signal.h"
#include "sys/conf.h"
#include "sys/user.h"
#include "sys/proc.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/file.h"
#include "sys/mbuf.h"
#include "sys/uio.h"
#include "sys/kernel.h"
E 5
#include "dkit.h"
#include "dk.h"
#include "dkdev.h"

extern int		dk_nchan;
extern struct dkdev	dkdev[];

struct tty	dkt[NDATAKIT];
caddr_t	dktibuf[NDATAKIT];	/* Input buffer pointers */
int	dktpaused[NDATAKIT];	/* delays for no output mbuf */
I 3

#ifdef notdef
speeds aren't used, don't bother
E 3
int	dktdelay[] = {		/* Time to wait on close before dropping line */
	4, 15, 15, 15, 15, 15, 15, 8,		/* B0-B300 */
	4, 2, 2, 2, 1, 1, 1, 1
};
D 3

int	dktstart();

E 3
static char dkt_tmr[16] = {
	15, 15, 15, 15, 15, 15, 15, 15,
	15, 9, 6, 4, 2, 1, 15, 15
} ;
I 3
#endif
E 3

I 3
int	dktstart();
E 3

I 3

E 3
/*
 * DKT control messages
 */
#define	D_BREAK	0110
#define	D_DELAY	0100

D 3
#define	DKTSPEED	B9600
#define	DKTFLAGS	(EVENP|ODDP|ECHO)

E 3
extern int dkdebug ;

#define	DEBUG	(dkdebug < 512)
#define devDEBUG 	(minor(dev) >= dkdebug)
#define chanDEBUG 	(chan >= dkdebug)
#define tpDEBUG 	((tp - dkt) >= dkdebug)

/*
 * Open a DKT line.
 */
dktopen(dev, flag)
{
	register struct tty	*tp;
	register struct dkdev	*dv;
	register		d;
	int chan;

	d = minor(dev);
	if (d >= dk_nchan) {
		if (DEBUG) log(LOG_ERR, "dkt_open(%d) error\n", dev);
		return ENXIO;
	}
	tp = &dkt[d];
	if ((tp->t_state&TS_XCLUDE) && u.u_uid!=0)
		return (EBUSY);
	if (!dktibuf[d]) {
		struct mbuf *mb;
		mb = m_get(M_WAIT, DKMT_ITTY);
		if (mb == NULL) return ENOBUFS;
		dktibuf[d] = mtod(mb, caddr_t);
	}
	if ((chan = dk_open(d, (int (*)()) NULL)) < 0) {
		return -chan;
	}

	tp->t_oproc = dktstart;
	tp->t_state |= (TS_WOPEN|TS_CARR_ON);
	dv = &dkdev[d];
	if ((tp->t_state&TS_ISOPEN) == 0) {
		ttychars(tp) ;
		if (tp->t_ispeed == 0) {
D 3
			tp->t_ispeed = tp->t_ospeed = DKTSPEED;
			tp->t_flags = DKTFLAGS;
E 3
I 3
			tp->t_iflag = TTYDEF_IFLAG;
			tp->t_oflag = TTYDEF_OFLAG;
			tp->t_lflag = TTYDEF_LFLAG;
			tp->t_cflag = TTYDEF_CFLAG;
			tp->t_ispeed = tp->t_ospeed = TTYDEF_SPEED;
			ttsetwater(tp);
E 3
		}
		if (devDEBUG) log(LOG_ERR, "DKT_open(%x,%o)\n",dev,flag);
	}
	dktfcon(tp);
	if (devDEBUG) log(LOG_ERR, "DKT_open(%x, %x) ok\n", dev, tp);
	dv->d_prot |= DpTTY;
	return (*linesw[tp->t_line].l_open)(dev, tp);
}

/*
 * Close a DKT line.
 */
/*ARGSUSED*/
dktclose(dev, flag)
dev_t dev;
int  flag;
{
	register struct tty	*tp;
	register struct dkdev	*dv;
	register int	d, s;
	extern int dktcflush(), dktrcv(), wakeup();

	d = minor(dev);
	tp = &dkt[d];
	dv = &dkdev[d];
	/*
	 * If called from exit(), give output 30 seconds to drain.
	 * Otherwise let output drain first.
	 */
	if(u.u_signal[SIGKILL] == SIG_IGN){
		s = spl5();
		timeout(dktcflush, (caddr_t) tp, 30*hz);
		ttywflush(tp) ;
		untimeout(dktcflush, (caddr_t) tp);
		tp->t_state &= ~TS_CARR_ON;
		if(dv->d_prot == DpTTY)	/* no other protocols open */
			dk_reset(d);
		splx(s);
	}

D 6
	(*linesw[tp->t_line].l_close)(tp);
E 6
I 6
	(*linesw[tp->t_line].l_close)(tp, flag);
E 6
	if (devDEBUG) log(LOG_ERR, "DKT_clos(%x)\n",dev);
	dv->d_prot &= ~DpTTY;
	tp->t_state &= ~TS_CARR_ON;
I 3
#ifdef notdef
E 3
	/* Wait for output to drain on far end */
	if (dktdelay[tp->t_ispeed] > 0) {
		timeout(wakeup, (caddr_t) tp, dktdelay[tp->t_ispeed] * hz);
		sleep((caddr_t) tp, TTIPRI);
	}
I 3
#endif
E 3
	if(!dv->d_prot){
		(void) dk_close(d);
		(void) dk_takedown(d);
		dv->d_state = 0;
	}
	else (void) dk_rabort(d, dktrcv, (caddr_t) tp);
	ttyclose(tp);
	s = spl5();
	if (dktibuf[d]) {
		(void) m_free(dtom(dktibuf[d]));
		dktibuf[d] = NULL;
	}
	splx(s);
I 4
	return (0);
E 4
}

static
dktcflush(tp)
	struct tty *tp;
{
	ttyflush(tp, (FREAD|FWRITE)) ;
}

/*
 * Read from a DKT line.
 */
D 3
dktread(dev, uio)
E 3
I 3
dktread(dev, uio, flag)
dev_t dev;
E 3
struct uio *uio;
{
	register struct tty *tp;
	int err;

	if (devDEBUG) log(LOG_ERR, "dktread(%x) %d\n", dev, uio->uio_resid) ;
	tp = &dkt[minor(dev)];
D 3
	err = (*linesw[tp->t_line].l_read)(tp, uio);
E 3
I 3
	err = (*linesw[tp->t_line].l_read)(tp, uio, flag);
E 3
	if (devDEBUG)
		log(LOG_ERR, "dktread done(%x) %d err=%d\n", dev, uio->uio_resid, err) ;
	dktfcon(tp);
	return err;
}

/*
 * Write on a DKT line
 */
D 3
dktwrite(dev, uio)
E 3
I 3
dktwrite(dev, uio, flag)
dev_t dev;
E 3
struct uio *uio;
{
	register struct tty *tp;

	if (devDEBUG) log(LOG_ERR, "dktwrite(%x)\n",dev);
	tp = &dkt[minor(dev)];
D 3
	return (*linesw[tp->t_line].l_write)(tp, uio);
E 3
I 3
	return (*linesw[tp->t_line].l_write)(tp, uio, flag);
E 3
}

/*
 * Receive a packet
 */
/*ARGSUSED*/
dktrcv(tp, chan, resid, rmode, rctl)
register struct tty *tp ;
{
	register c ;
	register char *cp ;
	register count ;

	if ((rmode & DKR_ABORT) || (dk_status(chan) & DK_RESET)) {
		dktshut(tp) ;
		return ;
	}
	/* Process input data */
	if (tp->t_state&TS_ISOPEN) {
		cp = dktibuf[tp-dkt];
		count = MLEN - resid ;
		if (count) {
			do {
				/* Should really do parity checking... */
				(*linesw[tp->t_line].l_rint)((*cp++)&0377, tp) ;
			} while (--count);
		}
		if ((c = (rctl & 0377)) != 0) {
			if (chanDEBUG) log(LOG_ERR, "DKT_ctl 0%o on %d\n",c,chan);
D 3
			if (c==D_BREAK) {
				/*
				 * At framing error (break) generate
				 * a null (in raw mode, for getty), or a
				 * interrupt (in cooked/cbreak mode).
				 */
				if (tp->t_flags&RAW)
					c = 0;
				else
					c = tp->t_intrc;
				(*linesw[tp->t_line].l_rint)(c, tp) ;
			}
E 3
I 3
			if (c==D_BREAK)
				(*linesw[tp->t_line].l_rint)(TTY_FE, tp) ;
E 3
		}
	}
	dktfcon(tp) ;
}


/*
 * Input flow control:  queue another receive unless to many chars waiting
 */
dktfcon(tp)
register struct tty *tp;
{
	register int d = tp - dkt;
	register x;

	if ((dk_status(d) & (DK_RCV|DK_OPEN)) != DK_OPEN)
		return ;
	if (dktibuf[d] == NULL) return;
	x = tp->t_rawq.c_cc + tp->t_canq.c_cc;
D 3
	if (x >= TTYHOG/2 && (tp->t_delct>0 || (tp->t_flags&(RAW|CBREAK))))
E 3
I 3
	if (x >= TTYHOG/2 && (!(tp->t_lflag&ICANON) || tp->t_canq.c_cc))
E 3
		return;
	(void) dk_recv(d, dktibuf[d], MLEN,
I 3
#ifdef notdef
E 3
	    DKR_BLOCK | DKR_TIME | (dkt_tmr[tp->t_ispeed]<<8),
I 3
#endif
	    DKR_BLOCK | DKR_TIME | (1<<8),
E 3
	    dktrcv, (caddr_t) tp) ;
}

/*
 * stty/gtty for DKT
 */
dktioctl(dev, cmd, data, flag)
caddr_t data;
{
	register struct tty *tp;
	int error;

	tp = &dkt[minor(dev)];
	error = (*linesw[tp->t_line].l_ioctl)(tp, cmd, data, flag);
	if (error >= 0)
		return error;
	error = ttioctl(tp, cmd, data, flag);
D 4
	if (error >= 0) {
		if (tp->t_ispeed == 0) {
			tp->t_state &= ~TS_CARR_ON;
			if (devDEBUG) log(LOG_ERR, "DKT_ioctl carr off\n");
D 3
			gsignal(tp->t_pgrp, SIGHUP);
			gsignal(tp->t_pgrp, SIGCONT);
E 3
I 3
			gsignal(tp->t_pgid, SIGHUP);
			gsignal(tp->t_pgid, SIGCONT);
E 3
		}
E 4
I 4
	if (error >= 0)
E 4
		return (error);
D 4
	}
E 4

	switch(cmd) {
		case TIOCSBRK:
			dktxpack(tp-dkt, D_BREAK) ;
			return 0;
		case TIOCCBRK:
			return 0;
	}
	return ENOTTY;
}

/*
 * Start (restart) transmission on the given DKT line.
 */
dktstart(tp)
register struct tty *tp;
{
	register d;
	char delay;
	extern dktxdun() ;
	int s, c;
	register int nch;
	register struct mbuf *m;
	extern ttrstrt();

	d = tp - dkt;
	s = spl5() ;

#ifdef notdef
	if (dk_status(d) & DK_SPND)
		dk_cmd(d, DKC_RSME) ;
#endif

	if (tp->t_state & (TS_BUSY|TS_TTSTOP|TS_TIMEOUT))
		goto out;

	/*
	 * If the writer was sleeping on output overflow,
	 * wake the process when low tide is reached.
	 */
D 3
	if (tp->t_outq.c_cc<=TTLOWAT(tp)) {
E 3
I 3
	if (tp->t_outq.c_cc<=tp->t_lowat) {
E 3
		if (tp->t_state&TS_ASLEEP) {
			tp->t_state &= ~TS_ASLEEP;
			wakeup((caddr_t)&tp->t_outq);
		}
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
	}
	/*
	 * Now restart transmission unless the output queue is
	 * empty.
	 */
	if (tp->t_outq.c_cc == 0)
		goto out;

	m = m_get(M_DONTWAIT, DKMT_OTTY);
	if (m == NULL) {
		/* No buffers; arrange to retry in .5 seconds */
		dktpaused[d]++;
		tp->t_state |= TS_TIMEOUT;
		timeout(ttrstrt, (caddr_t) tp, hz/2);
		goto out;
	}
D 3
	if (tp->t_flags & (RAW|LITOUT))
E 3
I 3
	if (1 || !(tp->t_oflag&OPOST))
E 3
		nch = ndqb(&tp->t_outq, 0);
	else {
		nch = ndqb(&tp->t_outq, 0200);
		/*
		 * If first thing on queue is a delay process it.
		 */
		if (nch == 0) {
			nch = getc(&tp->t_outq);
			c = MIN((nch & 0xff) + 6, 0x7f);
			delay = D_DELAY;
			if (tpDEBUG) 
				log(LOG_ERR, "DKT_delay %d\n", c) ;
			while (c) {
				delay++;
				c >>= 1;
			}
			if (dk_xmit(d, (struct mbuf *) NULL, 1, delay, dktxdun, (caddr_t) 0))
				tp->t_state |= TS_BUSY;
			(void) m_free(m);
			goto out;
		}
	}
	/*
	 * If characters to transmit, restart transmission.
	 */
	if (nch) {
		bcopy((caddr_t)tp->t_outq.c_cf, mtod(m, caddr_t), (unsigned) nch);
		m->m_len = nch;
		if (dk_xmit(d, m, 1, 0, dktxdun, (caddr_t) nch))
			tp->t_state |= TS_BUSY;
	}
	else (void) m_free(m);
out: ;
	splx(s) ;
}

dktxpack(chan, cmd)
char cmd;
{
	(void) dk_xmit(chan, (struct mbuf *) NULL, 1, cmd, (int (*)()) 0, (caddr_t) 0);
	if (chanDEBUG) log(LOG_ERR, "DKT_sent %o on %d\n",cmd&0377,chan);
}

/*ARGSUSED*/
dktstop(tp, rw)
register struct tty *tp;
{
	register int s, d;

	d = tp - dkt;
	s = spl5();
	if (tp->t_state & TS_BUSY) {
#ifdef notdef
		dk_cmd(d, DKC_SPND);
#endif
		if ((tp->t_state & TS_TTSTOP) == 0) {
			tp->t_state |= TS_FLUSH;
			dk_cmd(d, DKC_FLUSH);
		}
}
	splx(s);
}

dktshut(tp)
register struct tty *tp;
{
	if (tpDEBUG) log(LOG_ERR, "dktshut %d\n", tp-dkt);
D 4
	if ((tp->t_state&TS_ISOPEN) && (tp->t_state&TS_CARR_ON)) {
D 3
		if (tpDEBUG) log(LOG_ERR, "DKT_sighup %d\n",tp->t_pgrp);
		gsignal(tp->t_pgrp, SIGHUP);
		gsignal(tp->t_pgrp, SIGCONT);
E 3
I 3
		if (tpDEBUG) log(LOG_ERR, "DKT_sighup %d\n",tp->t_pgid);
		gsignal(tp->t_pgid, SIGHUP);
		gsignal(tp->t_pgid, SIGCONT);
E 3
	}
E 4
I 4
	if ((tp->t_state&TS_ISOPEN) && (tp->t_state&TS_CARR_ON))
		(void)(*linesw[tp->t_line].l_modem)(tp, 0);
E 4
	tp->t_state &= ~TS_CARR_ON;
	ttyflush(tp, (FREAD|FWRITE)) ;
	dk_cmd((tp - dkt), DKC_FLUSH);
}


dktxdun(cnt, chan)
{
	register struct tty *tp ;

	tp = &dkt[chan];
	if (tp->t_state & TS_FLUSH) tp->t_state &= ~TS_FLUSH;
	else ndflush(&tp->t_outq, cnt);
	tp->t_state &= ~TS_BUSY;
	if (tp->t_line)
		(*linesw[tp->t_line].l_start)(tp);
	else
		dktstart(tp);
}
#endif
E 1
