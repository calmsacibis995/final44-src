h27711
s 00002/00000/00470
d D 1.9 92/05/14 17:30:53 heideman 17 8
c vnode interface conversion
e
s 00002/00000/00470
d R 1.9 92/05/14 15:44:43 heideman 16 8
c vnode interface conversion
e
s 00002/00000/00470
d R 1.9 92/05/14 14:49:52 heideman 15 8
c vnode interface conversion
e
s 00002/00000/00470
d R 1.9 92/05/14 12:53:56 heideman 14 8
c vnode interface conversion
e
s 00002/00000/00470
d R 1.9 92/05/14 11:51:15 heideman 13 8
c vnode interface conversion
e
s 00002/00000/00470
d R 1.9 92/05/14 10:31:29 heideman 12 8
c vnode interface conversion
e
s 00002/00000/00470
d R 1.9 92/05/13 23:10:11 heideman 11 8
c vnode interface conversion
e
s 00002/00000/00470
d R 1.9 92/05/13 18:56:32 heideman 10 8
c vnode interface conversion
e
s 00002/00000/00470
d R 1.9 92/05/13 18:28:33 heideman 9 8
c vnode interface conversion
e
s 00021/00021/00449
d D 1.8 90/12/16 16:49:29 bostic 8 7
c kernel reorg
e
s 00005/00003/00465
d D 1.7 90/09/05 10:34:30 mckusick 7 6
c minimal changes to make clone devices work
e
s 00017/00010/00451
d D 1.6 90/09/03 17:26:35 karels 6 5
c sleep => tsleep; attempt to make compile
e
s 00027/00029/00434
d D 1.5 90/06/21 20:44:29 mckusick 5 4
c eliminate u.u_error; new namei and getvnode calling conventions
e
s 00001/00001/00462
d D 1.4 90/05/10 13:08:40 mckusick 4 3
c eliminate spurious #defines in user.h
e
s 00000/00001/00463
d D 1.3 90/02/17 10:17:12 mckusick 3 2
c get rid of dir.h
e
s 00001/00002/00463
d D 1.2 89/08/15 18:43:29 karels 2 1
c current version from monet
e
s 00465/00000/00000
d D 1.1 89/08/15 18:30:50 karels 1 0
c dk.c.ori from monet
e
u
U
t
T
I 1
/*
 * Datakit driver
 *	SCCSID[] = "@(#)dk.c	2.1 DKHOST 84/07/03"
 */

#include "datakit.h"
#if NDATAKIT>0

D 8
#include "param.h"
#include "../machine/pte.h"
#include "signal.h"
#include "errno.h"
#include "conf.h"
D 3
#include "dir.h"
E 3
#include "user.h"
#include "ioctl.h"
#include "tty.h"
D 5
#include "inode.h"
E 5
I 5
#include "vnode.h"
E 5
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
E 8
I 8
#include "../include/pte.h"
#include "sys/param.h"
#include "sys/signal.h"
#include "sys/errno.h"
#include "sys/conf.h"
#include "sys/user.h"
#include "sys/ioctl.h"
#include "sys/tty.h"
#include "sys/vnode.h"
#include "sys/file.h"
#include "sys/systm.h"
#include "sys/proc.h"
#include "sys/mbuf.h"
#include "sys/buf.h"
#include "sys/uio.h"
#include "sys/kernel.h"
#include "sys/dkit.h"
#include "sys/dkcmc.h"
#include "sys/dk.h"
#include "sys/dkdev.h"
#include "sys/syslog.h"
E 8

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
D 5
	int	s;
E 5
I 5
	int	s, error = 0;
E 5
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
D 5
		u.u_error = copyin(*(caddr_t *)data, (caddr_t) tp->d_param,
E 5
I 5
		error = copyin(*(caddr_t *)data, (caddr_t) tp->d_param,
E 5
		    3*sizeof (short));
D 5
		if (u.u_error) return u.u_error;
		if ((sp_chan = dkgetdev(tp->d_param[0])) <= 0)
			return u.u_error ;
E 5
I 5
		if (error) return error;
		if ((error = dkgetdev(tp->d_param[0], &sp_chan)) <= 0)
			return error ;
E 5
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
D 6
		while (tp->dc_state & DKSETUP)
			sleep((caddr_t) tp, TTOPRI);
		while (tsp->dc_state & DKSETUP)
			sleep((caddr_t) tsp, TTOPRI);
E 6
I 6
		error = 0;
		while (error == 0 && tp->dc_state & DKSETUP)
			error = tsleep((caddr_t)tp, TTOPRI, ttopen, 0);
		while (error == 0 && tsp->dc_state & DKSETUP)
			error = tsleep((caddr_t)tsp, TTOPRI, ttopen, 0);
E 6
		splx(s) ;
I 6
		if (error)
			return (error);
E 6
		if ((dk_status(chan) & DK_RESET) || (dk_status(sp_chan) & DK_RESET))
			return EIO ;
		if (tp->d_error || tsp->d_error) 
			return EIO ;
D 5
		u.u_error = copyout((caddr_t) tp->d_param, *(caddr_t *)data,
E 5
I 5
		error = copyout((caddr_t) tp->d_param, *(caddr_t *)data,
E 5
		    3*sizeof (short));
D 5
		if (u.u_error) return u.u_error;
E 5
I 5
		if (error) return error;
E 5
		break ;

	case DIOCSWAIT:
D 6
		(void) dksplwait(chan) ;
E 6
I 6
		error = dksplwait(chan);
E 6
		break ;

	default:
		if ((cmd & DKIOCMASK) != DKIOCVAL) {
			return ENOTTY ;
		}
		if (cmd == DKIODIAL) {
D 5
			u.u_error = copyin(*(caddr_t *)data, (caddr_t) &dialreq,
E 5
I 5
			error = copyin(*(caddr_t *)data, (caddr_t) &dialreq,
E 5
			    sizeof (struct diocdial));
D 5
			if (u.u_error) return u.u_error;
			if (u.u_error = dkiodial(chan, dialreq.dialstring))
				return u.u_error;
E 5
I 5
			if (error) return error;
			if (error = dkiodial(chan, dialreq.dialstring))
				return error;
E 5
			tp->dc_state |= DKSETUP ;
			chanstat = dk_setup(minor(dev), (int) DKIOCREQ, 0,
			0, 0, (int) u.u_uid, dkidone, (caddr_t)tp) ;
		}
		else {
D 5
			u.u_error = copyin(*(caddr_t *)data, (caddr_t) tp->d_param,
E 5
I 5
			error = copyin(*(caddr_t *)data, (caddr_t) tp->d_param,
E 5
			    3*sizeof (short));
D 5
			if (u.u_error) return u.u_error;
E 5
I 5
			if (error) return error;
E 5
			tp->dc_state |= DKSETUP ;
D 2
			chanstat = dk_setup(minor(dev), cmd, tp->d_param[0],
				tp->d_param[1], tp->d_param[2],
E 2
I 2
			chanstat = dk_setup(minor(dev), cmd, 0, 0, 0,
E 2
				(int) u.u_uid, dkidone, (caddr_t)tp) ;
		}
		if (chanstat) {
			tp->dc_state &= ~DKSETUP ;
			return (chanstat < 0 ? ECONNREFUSED : chanstat);
		}
		s = spl5() ;
D 6
		while (tp->dc_state & DKSETUP)
			sleep((caddr_t)(tp), TTOPRI) ;
E 6
I 6
		error = 0;
		while (error == 0 && tp->dc_state & DKSETUP)
			error = tsleep((caddr_t)(tp), TTOPRI, ttyout, 0) ;
E 6
		splx(s) ;
I 6
		if (error)
			return error;
E 6
D 5
		u.u_error = copyout((caddr_t) tp->d_param, *(caddr_t *)data,
E 5
I 5
		error = copyout((caddr_t) tp->d_param, *(caddr_t *)data,
E 5
		    3*sizeof (short));
D 5
		if (u.u_error) return u.u_error;
E 5
I 5
		if (error) return error;
E 5
		if (dk_status(minor(dev)) & DK_RESET)
			return ENETRESET ;
		if (tp->d_error)
			return EIO ;
		break ;
	}
D 5
	return 0;
E 5
I 5
	return error;
E 5
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
I 17
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
E 17
	register struct	dkdev	*tp;
	register chan;
D 7
	register struct nameidata *ndp = &u.u_nd;
E 7
I 7
	register struct nameidata *ndp = &u.u_nd;	/* XXX */
	struct proc *p = u.u_procp;			/* XXX */
	struct vnode *vp;
E 7
D 5
	struct	inode *ip;
E 5
	struct	file *fp;
D 7
	int	 m;
E 7
I 7
	int	 m, error;
E 7

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
D 4
	if (tp->d_state&DKXCLUDE && u.u_ruid!=0) {
E 4
I 4
	if (tp->d_state&DKXCLUDE && u.u_procp->p_ruid!=0) {
E 4
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
D 5
		 * throw away inode for dk0. (/dev/dk/dial)
E 5
I 5
		 * throw away vnode for dk0. (/dev/dk/dial)
E 5
		 * Build standard name of new one, and ask namei for it.
		 */
D 7
		fp = u.u_ofile[u.u_r.r_val1];
E 7
I 7
		fp = u.u_ofile[-1 - p->p_dupfd];
E 7

		dksnamer(dname, chan);
		/* log(LOG_ERR, "dname=%s chan=%d\n", dname, chan); */
D 5
		u.u_error = 0;
		ndp->ni_nameiop = FOLLOW | LOOKUP;
E 5
I 5
		ndp->ni_nameiop = FOLLOW | LOOKUP | LOCKLEAF;
E 5
		ndp->ni_segflg = UIO_SYSSPACE;
		ndp->ni_dirp = dname;
D 5
		ip = namei(ndp);

		if (ip == NULL) {
E 5
I 5
		if (error = namei(ndp)) {
E 5
			(void) dk_close(chan) ;
D 5
			return ENOENT ;
E 5
I 5
			return (error);
E 5
		}

		/* Give back old one */
D 5
		ilock((struct inode *) fp->f_data);
		iput((struct inode *) fp->f_data);
E 5
I 5
		vp = (struct vnode *) fp->f_data;
		VOP_LOCK(vp);
		vput(vp);
E 5

D 5
		fp->f_data = (caddr_t) ip;
		iunlock(ip);
E 5
I 5
		vp = ndp->ni_vp;
		fp->f_data = (caddr_t) vp;
		VOP_UNLOCK(vp);
E 5
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
D 6
			sleep((caddr_t)(&tp->d_state), TTOPRI) ;
E 6
I 6
			if (tsleep((caddr_t)(&tp->d_state), TTOPRI, ttyout, 0))
				break;
E 6
		}
	}
	else if (tp->d_bufct)
		/* Hmm -- buffers queued.  Let's wait 15 seconds max */
		for (i = 0; tp->d_bufct && i < 15; i++) {
			tp->d_state |= DKWAIT ;
D 6
			timeout(wakeup, (caddr_t) &tp->d_state, hz);
			sleep((caddr_t)(&tp->d_state), TTOPRI) ;
E 6
I 6
			if (tsleep((caddr_t)(&tp->d_state), TTOPRI, ttyout, hz))
				break;
E 6
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
E 1
