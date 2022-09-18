h30931
s 00018/00018/00257
d D 1.7 90/12/16 16:49:42 bostic 7 6
c kernel reorg
e
s 00004/00002/00271
d D 1.6 90/09/04 19:23:04 mckusick 6 5
c remove last of the inode dependencies
e
s 00017/00013/00256
d D 1.5 90/09/03 17:26:38 karels 5 4
c sleep => tsleep; attempt to make compile
e
s 00014/00014/00255
d D 1.4 90/06/21 20:44:34 mckusick 4 3
c eliminate u.u_error; new namei and getvnode calling conventions
e
s 00007/00011/00262
d D 1.3 90/06/21 20:20:00 karels 3 2
c new mbufs
e
s 00000/00001/00273
d D 1.2 90/02/17 10:18:01 mckusick 2 1
c get rid of dir.h
e
s 00274/00000/00000
d D 1.1 89/08/15 18:34:15 karels 1 0
c current version from monet
e
u
U
t
T
I 1
D 3

E 3
/*
 * Datakit driver
 * Common subroutines for all drivers
 *	SCCSID[] = "@(#)dksub.c	1.2 Garage 84/03/27"
I 3
 *		   "%W% (Berkeley) %G%"
E 3
 */

#include "datakit.h"
#if NDATAKIT>0

D 7
#include "param.h"
#include "../machine/pte.h"
#include "signal.h"
#include "errno.h"
#include "seg.h"
D 2
#include "dir.h"
E 2
#include "user.h"
#include "ioctl.h"
#include "tty.h"
#include "syslog.h"
#include "conf.h"
#include "file.h"
D 5
#include "inode.h"
E 5
#include "systm.h"
#include "proc.h"
#include "mbuf.h"
#include "buf.h"
#include "uio.h"
I 6
#include "vnode.h"
#include "specdev.h"
E 7
I 7
#include "../include/pte.h"
#include "sys/param.h"
#include "sys/signal.h"
#include "sys/errno.h"
#include "sys/seg.h"
#include "sys/user.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/syslog.h"
#include "sys/conf.h"
#include "sys/file.h"
#include "sys/systm.h"
#include "sys/proc.h"
#include "sys/mbuf.h"
#include "sys/buf.h"
#include "sys/uio.h"
#include "sys/vnode.h"
#include "sys/specdev.h"
E 7
E 6
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
D 3
		register struct mbuf *p;
		MCLALLOC(p, 1);
		if (p == 0)
E 3
I 3
		MCLGET(mm, M_WAIT);
		if ((mm->m_flags & M_EXT) == 0)
E 3
			goto nopages;
D 3
		mm->m_off = (int)p - (int)mm;
		blen = CLBYTES;
E 3
I 3
		blen = MCLBYTES;
E 3
	} else {
nopages:
		blen = MIN(MLEN, uio->uio_resid);
	}

D 5
	if (setjmp(&u.u_qsave)) {
		s = spl5();
		if (dk_status(chan) & DK_RCV)
			(void) dk_rabort(chan, dkrdone, (caddr_t) tp) ;
		splx(s);
		m_freem(mm);
D 4
		u.u_error = EINTR;
E 4
		return EINTR ;
	}
		
E 5
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
D 5
			sleep((caddr_t)(tp), TTOPRI) ;
E 5
I 5
			if (err = tsleep((caddr_t)(tp), TTIPRI, ttyin, 0)) {
				if (dk_status(chan) & DK_RCV)
					(void) dk_rabort(chan, dkrdone,
					    (caddr_t) tp);
				splx(s);
				goto done;
			}
E 5
		splx(s) ;

		len -= tp->d_rresid ;
		if (len)
			err = uiomove(mtod(mm, caddr_t), len, UIO_READ, uio);
		if (tp->d_rdone != DKR_FULL)
			break ;
	}
I 5
done:
E 5
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
D 5
			sleep((caddr_t)(&tp->d_state), TTOPRI) ;
E 5
I 5
			if (error = tsleep((caddr_t)(&tp->d_state), TTOPRI,
			    ttyout, 0)) {
				splx(s);
				return (error);
			}
E 5
		}
		splx(s) ;

		iov = uio->uio_iov;
		if (iov->iov_len) {
			MGET(m, M_WAIT, DKMT_DATA);
			if (m == NULL)
				return ENOBUFS;
			if (iov->iov_len >= MLEN) {
D 3
				register struct mbuf *p;
				MCLALLOC(p, 1);
				if (p == 0)
E 3
I 3
				MCLGET(m, M_WAIT);
				if ((m->m_flags & M_EXT) == 0)
E 3
					goto nopages;
D 3
				m->m_off = (int)p - (int)m;
				len = MIN(CLBYTES, iov->iov_len);
E 3
I 3
				len = MIN(MCLBYTES, iov->iov_len);
E 3
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
I 5
	int error;
E 5

	tp = &dkdev[chan] ;
	while ((tp->d_state & DKSPLICED) == 0)
D 5
		sleep((caddr_t) tp, TTOPRI) ;
E 5
I 5
		if (error = tsleep((caddr_t) tp, TTOPRI, ttopen, 0))
			return (error);
	return (0);
E 5
}

/* convert file desciptor to Datakit channel */
D 4
dkgetdev(fildes)
E 4
I 4
dkgetdev(fildes, devnop)
	int fildes, *devnop;
E 4
{
D 4
	extern struct file *getinode();
	register struct file *fp;
	register struct inode *ip ;
E 4
I 4
	struct file *fp;
	register struct vnode *vp ;
	int error;
E 4

D 4
	fp = getinode(fildes) ;
	ip = (struct inode *)fp->f_data;
	if ((ip->i_mode & IFMT) != IFCHR ) {
		u.u_error = ENOTTY ;
		return(-1) ;
E 4
I 4
	if (error = getvnode(u.u_ofile, fildes, &fp))
		return error;
	vp = (struct vnode *)fp->f_data;
	if (vp->v_type != VCHR)
		return ENOTTY;
D 6
	if (dkdevtype((dev_t) vp->v_rdev)) {
		*devnop = minor(ip->i_rdev);
E 6
I 6
	if (dkdevtype(vp->v_rdev)) {
		*devnop = minor(vp->v_rdev);
E 6
		return 0;
E 4
	}
D 4
	if (dkdevtype((dev_t) ip->i_rdev))
		return(minor(ip->i_rdev)) ;
	u.u_error = EINVAL ;
	return(-1) ;
E 4
I 4
	return EINVAL;
E 4
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
E 1
