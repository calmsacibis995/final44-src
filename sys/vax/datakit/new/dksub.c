/*
 * Datakit driver
 * Common subroutines for all drivers
 *	SCCSID[] = "@(#)dksub.c	1.2 Garage 84/03/27"
 */

#include "datakit.h"
#if NDATAKIT>0

#include "param.h"
#include "../machine/pte.h"
#include "signal.h"
#include "errno.h"
#include "seg.h"
#include "dir.h"
#include "user.h"
#include "ioctl.h"
#include "tty.h"
#include "syslog.h"
#include "conf.h"
#include "file.h"
#include "inode.h"
#include "systm.h"
#include "proc.h"
#include "mbuf.h"
#include "buf.h"
#include "uio.h"
#include "dkit.h"
#include "dk.h"
#include "dkdev.h"

#define DKBUFUSE	5	/* max buffers /channel */


extern struct dkdev dkdev[] ;

int	dksubdebug = 512;


dkuread(chan, uio)
register struct uio *uio;
{
	register int len, blen ;
	register struct dkdev *tp ;
	short chanstat ;
	struct mbuf *mm ;
	int err = 0, s;
	extern wakeup() ;
	extern dkrdone() ;

	tp = &dkdev[chan];
	MGET(mm, M_WAIT, DKMT_DATA);
	if (mm == NULL)
		return ENOBUFS;
	if (uio->uio_resid >= MLEN) {
		register struct mbuf *p = mm;
		MCLGET(p, M_WAIT);
		if ((p->m_flags & M_EXT) == 0)
			goto nopages;
		blen = CLBYTES;
	} else {
nopages:
		blen = MIN(MLEN, uio->uio_resid);
	}

	if (setjmp(&u.u_qsave)) {
		s = spl5();
		if (dk_status(chan) & DK_RCV)
			(void) dk_rabort(chan, dkrdone, (caddr_t) tp) ;
		splx(s);
		m_freem(mm);
		u.u_error = EINTR;
		return EINTR ;
	}
		
	while (uio->uio_resid && !err) {
		len = MIN(uio->uio_resid, blen) ;
		chanstat = dk_recv(chan, mtod(mm, caddr_t), len, tp->d_rmode, dkrdone, (caddr_t) tp) ;
		if (chanstat == 0) {
			if ((dk_status(chan) & DK_RESET) == 0)
				err = EIO ;
			break;
		}
		if ((tp->dc_state & DK_NDELAY) && (dk_status(chan) & DK_RCV)) {
			err = EWOULDBLOCK;
			break;
		}

		s = spl5() ;
		while (dk_status(chan) & DK_RCV)
			sleep((caddr_t)(tp), TTOPRI) ;
		splx(s) ;

		len -= tp->d_rresid ;
		if (len)
			err = uiomove(mtod(mm, caddr_t), len, UIO_READ, uio);
		if (tp->d_rdone != DKR_FULL)
			break ;
	}
	m_freem(mm) ;
	return err;
}


/*ARGSUSED*/
dkrdone(tp, chan, resid, rdone, rctl)
register struct dkdev *tp ;
{
	tp->d_rresid = resid ;
	tp->d_rdone = rdone ; 
	tp->d_rctl = rctl ;
	wakeup((caddr_t) tp) ;
}




dkuwrite(chan, uio) register struct uio *uio;
{
extern wakeup() ;
extern dkwdone() ;
register struct dkdev *tp ;
register len ;
register struct mbuf *m;
register struct iovec *iov;
int s, error, eob;
short xc;

	tp = &dkdev[chan] ;
	do {
		s = spl5() ;
		while (tp->d_bufct > DKBUFUSE) {
			if (tp->dc_state & DK_NDELAY) {
				splx(s);
				return EWOULDBLOCK;
			}
			tp->d_state |= DKWAIT ;
			sleep((caddr_t)(&tp->d_state), TTOPRI) ;
		}
		splx(s) ;

		iov = uio->uio_iov;
		if (iov->iov_len) {
			MGET(m, M_WAIT, DKMT_DATA);
			if (m == NULL)
				return ENOBUFS;
			if (iov->iov_len >= MLEN) {
				register struct mbuf *p = m;
				MCLGET(m, M_WAIT);
				if ((m->m_flags & M_EXT) == 0)
					goto nopages;
				len = MIN(CLBYTES, iov->iov_len);
			} else {
nopages:
				len = MIN(MLEN, iov->iov_len);
			}
			error = uiomove(mtod(m, caddr_t), len, UIO_WRITE, uio);
			if (error) {
				(void) m_free(m);
				return error;
			}
			m->m_len = len;
		}
		else m = NULL;

		s = spl5();
		tp->d_bufct++;
		eob = (uio->uio_resid == 0);
		if (eob) {
			xc = tp->d_xctl;
			tp->d_xctl = 0;
		}
		else xc = 0;
		if (dk_xmit(chan, m, eob, xc, dkwdone, (caddr_t) 0) == 0) {
			tp->d_bufct-- ;
			return EIO ;
		}
		splx(s);
	} while (uio->uio_resid);
	return 0;
}

/*ARGSUSED*/
dkwdone(x, chan)
{
	register struct dkdev *tp ;

	tp = &dkdev[chan] ;
	if (chan > dksubdebug)
		log(LOG_ERR, "dkwdone %d: state=0%o bufct=%d\n", chan, tp->d_state,
		    tp->d_bufct);
	if (tp->d_bufct)
		tp->d_bufct-- ;
	if (tp->d_state & DKWAIT) {
		tp->d_state &= ~DKWAIT ;
		wakeup((caddr_t) &tp->d_state) ;
	}
}

/* wakeup and reinitialize channel upon receipt of reconnection message */
dkrsplice(chan)
{
	register struct dkdev *tp ;

	tp = &dkdev[chan] ;
	tp->d_state |= DKSPLICED ;
	wakeup((caddr_t) tp) ;
	dk_cmd(chan, DKC_XINIT) ;
}

/* wait for reconnection message indicating that splice completed */
dksplwait(chan)
{
	register struct dkdev *tp ;

	tp = &dkdev[chan] ;
	while ((tp->d_state & DKSPLICED) == 0)
		sleep((caddr_t) tp, TTOPRI) ;
}

/* convert file desciptor to Datakit channel */
dkgetdev(fildes)
{
	extern struct file *getinode();
	register struct file *fp;
	register struct inode *ip ;

	fp = getinode(fildes) ;
	ip = (struct inode *)fp->f_data;
	if ((ip->i_mode & IFMT) != IFCHR ) {
		u.u_error = ENOTTY ;
		return(-1) ;
	}
	if (dkdevtype((dev_t) ip->i_rdev))
		return(minor(ip->i_rdev)) ;
	u.u_error = EINVAL ;
	return(-1) ;
}

/* validate device number as belonging to Datakit */
dkdevtype(dev) dev_t dev;
{
	extern dkopen();
#if NDKTTY > 0
	extern dktopen();
#endif
#if NDKXQT > 0
	extern dkxopen();
#endif
#if NDKI > 0
	extern dkiopen();
#endif
	register md = major(dev) ;

	if ((cdevsw[md].d_open == dkopen)
#if NDKTTY > 0
		|| (cdevsw[md].d_open == dktopen)
#endif
#if NDKI > 0
		|| (cdevsw[md].d_open == dkiopen && md > 0)
#endif
#if NDKXQT > 0
		|| (cdevsw[md].d_open == dkxopen)
#endif
	    )
			return(1);
	else
		return(0);
}

#endif
