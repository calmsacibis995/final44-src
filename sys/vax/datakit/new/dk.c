/*
 * Datakit driver
 *	SCCSID[] = "@(#)dk.c	2.1 DKHOST 84/07/03"
 */

#include "datakit.h"
#if NDATAKIT>0

#include "param.h"
#include "../machine/pte.h"
#include "signal.h"
#include "errno.h"
#include "conf.h"
#include "dir.h"
#include "user.h"
#include "ioctl.h"
#include "tty.h"
#include "inode.h"
#include "file.h"
#include "systm.h"
#include "proc.h"
#include "mbuf.h"
#include "buf.h"
#include "uio.h"
#include "kernel.h"
#include "dkit.h"
#include "dkcmc.h"
#include "dk.h"
#include "dkdev.h"
#include "syslog.h"

extern int dkdebug ;

#define DKBUFUSE	5	/* max buffers /channel */


int	dk_nchan	= NDATAKIT;
struct	dkdev		dkdev[NDATAKIT];
struct	dksetupreq	*dkreq[NDATAKIT];




#ifdef	MONITOR
int dummy ;
int *DKP2 = &dummy ;
#define	M_ON(a)		*DKP2 |= (a)
#define	M_OFF(a)	*DKP2 &= ~(a)

#define	Mread	0400
#define Mrslp	01000
#define	Mrcpy	02000
#define	Mwrite	04000
#define	Mwcpy	010000

#else
#define	M_ON(a)
#define	M_OFF(a)
#endif



/*ARGSUSED*/
dkioctl(dev, cmd, data, flag)
register caddr_t data;
{
	register struct	dkdev	*tp;
	register chanstat ;
	int	chan, sp_chan;
	int	s;
	register short	*pp ;
	struct dkdev *tsp;
	extern dkidone() ;
	struct diocdial dialreq;
	extern int commchan;

	chan = dev = minor(dev);
	tp = &dkdev[chan];
	pp = (short *) data;
	switch(cmd) {
	case DIOCEXCL:
		tp->d_state |= DKXCLUDE ;
		break ;
	case DIOCNXCL:
		tp->d_state &= ~DKXCLUDE ;
		break ;
	case DIOCSETK:
		dkdebug = pp[0] ;
		break;
	case DIOCQQABO:
		pp[0] = tp->d_rresid;
		pp[1] = tp->d_rdone;
		pp[2] = tp->d_rctl;
		break ;
	case DIOCRMODE:
		if (pp[0] & DKR_TIME)
			tp->d_rmode = (DKR_TIME | DKR_BLOCK);
		else tp->d_rmode = pp[0] ;
		break ;
	case DIOCXCTL:
		tp->d_xctl = pp[0] ;
		break ;
	case DIOCFLUSH:
		dk_cmd(chan, DKC_XINIT|DKC_FLUSH);
		break;
	case KIOCINIT:
		dk_cmd(chan, DKC_XINIT);
		break;
	case DIOCXWIN:
		return dk_winsize(chan, (struct diocxwin *)data);
	case DIOCRESET:
		if (chan != 1 && chan != pp[0]) return EACCES;
		if (pp[0] > 1 && pp[0] < commchan) return EINVAL;
		if (pp[0] < 0 || pp[0] >= dk_nchan) return EINVAL;
		if (pp[0] == 0) return -dk_close(0);
		else dk_reset(pp[0]);
		break;
	case DIOCCTYPE:
		if (tp->d_ctype == NULL) {
			struct mbuf *m;

			MGET(m, M_WAIT, DKMT_CTYPE);
			if (m == NULL)
				return ENOBUFS;
			tp->d_ctype = mtod(m, struct diocctype *);
		}
		return bcopy(data, (caddr_t) tp->d_ctype, sizeof (struct diocctype));
	case DIOCINFO:
		((struct diocinfo *)data)->dioc_nchan = dk_nchan;
		((struct diocinfo *)data)->dioc_channum = chan;
		((struct diocinfo *)data)->dioc_commchan = commchan;
		break;
	case DIOCSTAT:
		if (*((int *)data) < 0 || *((int *)data) >= dk_nchan)
			return EINVAL;
		*((int *)data) = dk_status(*((int *)data));
		break;
	case FIONBIO:
		if (*(int *)data)
			tp->dc_state |= DK_NDELAY;
		else
			tp->dc_state &= ~DK_NDELAY;
		break;
	case FIOASYNC:
		if (*(int *)data)
			tp->dc_state |= DK_ASYNC;
		else
			tp->dc_state &= ~DK_ASYNC;
		break;
	case TIOCGPGRP:
		*(int *)data = tp->d_pgrp;
		break;
	case TIOCSPGRP:
		tp->d_pgrp = *(int *)data;
		break;

	/* splice chan to file descriptor */
	case DKIOCSPL:
		u.u_error = copyin(*(caddr_t *)data, (caddr_t) tp->d_param,
		    3*sizeof (short));
		if (u.u_error) return u.u_error;
		if ((sp_chan = dkgetdev(tp->d_param[0])) <= 0)
			return u.u_error ;
		if (sp_chan == chan)
			return EINVAL ;
		tsp = &dkdev[sp_chan] ;
		tp->dc_state |= DKSETUP ;
		tsp->dc_state |= DKSETUP ;
		if (dk_splice(chan, sp_chan, dkidone, (caddr_t) tp,
			(caddr_t) tsp)) {
			tp->dc_state &= ~DKSETUP ;
			tsp->dc_state &= ~DKSETUP ;
			return EIO ;
		}
		s = spl5() ;
		while (tp->dc_state & DKSETUP)
			sleep((caddr_t) tp, TTOPRI);
		while (tsp->dc_state & DKSETUP)
			sleep((caddr_t) tsp, TTOPRI);
		splx(s) ;
		if ((dk_status(chan) & DK_RESET) || (dk_status(sp_chan) & DK_RESET))
			return EIO ;
		if (tp->d_error || tsp->d_error) 
			return EIO ;
		u.u_error = copyout((caddr_t) tp->d_param, *(caddr_t *)data,
		    3*sizeof (short));
		if (u.u_error) return u.u_error;
		break ;

	case DIOCSWAIT:
		(void) dksplwait(chan) ;
		break ;

	default:
		if ((cmd & DKIOCMASK) != DKIOCVAL) {
			return ENOTTY ;
		}
		if (cmd == DKIODIAL) {
			u.u_error = copyin(*(caddr_t *)data, (caddr_t) &dialreq,
			    sizeof (struct diocdial));
			if (u.u_error) return u.u_error;
			if (u.u_error = dkiodial(chan, dialreq.dialstring))
				return u.u_error;
			tp->dc_state |= DKSETUP ;
			chanstat = dk_setup(minor(dev), (int) DKIOCREQ, 0,
			0, 0, (int) u.u_uid, dkidone, (caddr_t)tp) ;
		}
		else {
			u.u_error = copyin(*(caddr_t *)data, (caddr_t) tp->d_param,
			    3*sizeof (short));
			if (u.u_error) return u.u_error;
			tp->dc_state |= DKSETUP ;
			chanstat = dk_setup(minor(dev), cmd, 0, 0, 0,
				(int) u.u_uid, dkidone, (caddr_t)tp) ;
		}
		if (chanstat) {
			tp->dc_state &= ~DKSETUP ;
			return (chanstat < 0 ? ECONNREFUSED : chanstat);
		}
		s = spl5() ;
		while (tp->dc_state & DKSETUP)
			sleep((caddr_t)(tp), TTOPRI) ;
		splx(s) ;
		u.u_error = copyout((caddr_t) tp->d_param, *(caddr_t *)data,
		    3*sizeof (short));
		if (u.u_error) return u.u_error;
		if (dk_status(minor(dev)) & DK_RESET)
			return ENETRESET ;
		if (tp->d_error)
			return EIO ;
		break ;
	}
	return 0;
}

#define DS_SIZE 64
static
dkiodial(chan, user_ds)
register char *user_ds;
{
	register caddr_t ds;
	register n;
	register struct mbuf *mb;
	int u_count;

	mb = m_get(M_WAIT, DKMT_DATA);
	if (mb == NULL) return ENOBUFS;
	ds = mtod(mb, caddr_t);
	for (u_count = 0; u_count < MLEN - 6; u_count++) {
		*ds = *user_ds;
		if (*ds == '\n' || *ds == '\0') break;
		ds++;
		user_ds++;
	}
	*ds = '\n';
	u_count++;

	/* add uid in char decimal */

	ds++;
	u_count++;
	for (n = u.u_uid; n /= 10; ds++) u_count++;
	for (n = u.u_uid;; ds--) {
		*ds = n % 10 + '0';
		if ((n /= 10) == 0) break;
	}

	mb->m_len = u_count;
	if (dk_xmit(chan, mb, 1, 0, (int (*)()) 0, (caddr_t) 0) == 0) {
		return(EIO);
	}
	else return(0);
}
/*
 * End action for ioctl completion
 */
/*ARGSUSED*/
dkidone(tp, chan, err, p0, p1, p2)
register struct dkdev *tp ;
short chan, p0, p1, p2 ;
{
	tp->d_error = err ;
	tp->d_param[0] = p0 ;
	tp->d_param[1] = p1 ;
	tp->d_param[2] = p2 ;
	tp->dc_state &= ~DKSETUP ;
	wakeup((caddr_t)tp) ;
}




/*ARGSUSED*/
dkopen(dev, flag)
{
	register struct	dkdev	*tp;
	register chan;
	register struct nameidata *ndp = &u.u_nd;
	struct	inode *ip;
	struct	file *fp;
	int	 m;

#ifdef lint
	(void) dk_xint(0, 0);
#endif
	dev = minor(dev);
	if (dev == 1) {
		return 0;	/* Maintenance channel */
	}

	chan = dev;
	if (chan >= dk_nchan) {
/* debug */	log(LOG_ERR, "dkopen bad: chan>=NDKCHANS : %d\n",chan);
		return ENXIO;
	}

	tp = &dkdev[chan];
	if ((tp->d_state & DKOPEN) == 0)
		tp->dc_state = 0 ;
	if (tp->d_state&DKXCLUDE && u.u_ruid!=0) {
		return EBUSY;
	}

	if ((m = dk_open(chan, (int (*)()) NULL)) < 0)
		return -m;


	/*
	 * Channel 0 is reserved for maintenance.
	 * An open on channel 0 is interpreted as a request
	 * for an unused channel.
	 */
	if (chan==0) {
		char dname[30];

		chan = m ;
		tp = &dkdev[chan] ;
		tp->dc_state = 0 ;
		/*
		 * throw away inode for dk0. (/dev/dk/dial)
		 * Build standard name of new one, and ask namei for it.
		 */
		fp = u.u_ofile[u.u_r.r_val1];

		dksnamer(dname, chan);
		/* log(LOG_ERR, "dname=%s chan=%d\n", dname, chan); */
		u.u_error = 0;
		ndp->ni_nameiop = FOLLOW | LOOKUP;
		ndp->ni_segflg = UIO_SYSSPACE;
		ndp->ni_dirp = dname;
		ip = namei(ndp);

		if (ip == NULL) {
			(void) dk_close(chan) ;
			return ENOENT ;
		}

		/* Give back old one */
		ilock((struct inode *) fp->f_data);
		iput((struct inode *) fp->f_data);

		fp->f_data = (caddr_t) ip;
		iunlock(ip);
	}
	if ((tp->d_state & DKOPEN) == 0) {
		tp->d_state |= DKOPEN ;
		tp->dc_state = 0;
		tp->d_rmode = 0 ;
		tp->d_xctl = 0 ;
		tp->d_pgrp = 0;
	}
	tp->d_prot |= DpURP;
	return 0;
}

/* Policy decision here -- standard name of dk file known to this routine */
dksnamer(s, n) register char *s;
{
	register char *p = "/dev/dk/dk";

	while (*s++ = *p++)
		;
	s--;
	*s++ = '0' + (n/100); n %= 100;
	*s++ = '0' + (n/10); n %= 10;
	*s++ = '0' + n;
	*s = '\0';
}

/*
 * Close a channel:
 */

/*ARGSUSED*/
dkclose(dev, flag)
dev_t dev;
int flag;
{
	register struct	dkdev	*tp;
	extern wakeup() ;
	extern brelse() ;
	short	s, chan ;
	int i, cl = 0;

	chan = minor(dev);
	tp = &dkdev[chan];
	if (chan == 1) {
		return 0;	/* Maintenance channel */
	}
	s = spl5() ;
	if (u.u_signal[SIGKILL] != SIG_IGN) {	  /* detect close from exit() */
		while (tp->d_bufct) {
			tp->d_state |= DKWAIT ;
			sleep((caddr_t)(&tp->d_state), TTOPRI) ;
		}
	}
	else if (tp->d_bufct)
		/* Hmm -- buffers queued.  Let's wait 15 seconds max */
		for (i = 0; tp->d_bufct && i < 15; i++) {
			tp->d_state |= DKWAIT ;
			timeout(wakeup, (caddr_t) &tp->d_state, hz);
			sleep((caddr_t)(&tp->d_state), TTOPRI) ;
		}
	splx(s) ;
	tp->dc_state = 0;
	tp->d_rmode = 0;
	tp->d_prot &= ~DpURP;
	if(!tp->d_prot){
		cl = dk_close(chan);
		(void) dk_takedown(chan);
		tp->d_state = 0;
	}
	return -cl;
}

dkread(dev, uio)
dev_t dev ;
struct uio *uio;
{
register struct dkdev *tp ;
int err;

	M_ON(Mread) ;
	tp = &dkdev[minor(dev)] ;
	err = dkuread(minor(dev), uio) ;
	tp->d_rresid = uio->uio_resid ;
	M_OFF(Mread) ;
	return err;
}


dkwrite(dev, uio)
struct uio *uio;
dev_t dev ;
{
	int err;

	M_ON(Mwrite) ;
	err = dkuwrite(minor(dev), uio) ;
	M_OFF(Mwrite) ;
	return err;
}

#endif
