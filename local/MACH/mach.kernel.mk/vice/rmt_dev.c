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
 * $Log:	rmt_dev.c,v $
 * Revision 2.5  89/03/09  22:45:39  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/26  11:14:11  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/07  22:55:37  mwyoung
 * Code cleanup cataclysm.
 * 
 * 20-Mar-87  David Black (dlb) at Carnegie-Mellon University
 *	Added parentheses to keep Multimax compiler happy.
 *
 * 17-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Fixed a bug in rmtread - was using 'return' instead of the
 *	desired 'return(0)'.
 *
 *  3-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Support for MACH wrt select bogosities.
 *
 * 22-Oct-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Created from Andrew's rmt_dev.c.
 *
 */
/*	rmt_dev.c	CMU	86/10/22	*/

/*
 * ITC Remote file system - device communications module
 */

/*
 * 5799-CGZ (C) COPYRIGHT IBM CORPORATION  1986
 * LICENSED MATERIALS - PROPERTY OF IBM
 * REFER TO COPYRIGHT INSTRUCTIONS FORM NUMBER G120-2083
 */

#include <vicefs.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/proc.h>
#include <sys/inode.h>
#include <sys/file.h>
#include <sys/conf.h>
#include <sys/buf.h>
#include <sys/uio.h>
#include <sys/vicermt.h>

struct remote remote[NVICEFS];

/* rmt_maj -- Major device number for the rmt character pseudo device. */
int rmt_maj	= RMT_MAJ;	/* Should not be defined using a manifest */


#define rmt_rbuf_attached() ((rmt.rt_flags & RT_RBUF) && \
			     rmt.rt_imr.im_client == u.u_procp->p_pid)

#define rmt_wbuf_attached() ((rmt.rt_flags & RT_WBUF) && \
			     rmt.rt_imw.im_client == u.u_procp->p_pid)

/* rmtopen -- open entry for pseudo device rmt, called by agent process */
rmtopen(dev)
    dev_t dev;
{
    devhack(dev);
    if (minor(dev) >= NVICEFS)
	return (ENXIO);
    if (rmt.rt_open)
	return (EBUSY);
    rmt.rt_open = 1;
    rmt.rt_selproc = 0;
    return(0);
}

/* rmtclose -- close entry for pseudo device rmt, called by agent process */
rmtclose(dev) {
    devhack(dev);
    rmt.rt_open = 0;
    wakeup(&rmt.rt_attach); /* wakeup clients so they can die */
    wakeup(&rmt.rt_reply);
}

/* rmtcleanup -- cleanup after a system call */
rmtcleanup (dev)
    dev_t dev;
{
    devhack(dev);
    if (rmt_rbuf_attached())
	rmt_detach_rbuf(dev);
    if (rmt_wbuf_attached())
	rmt_detach_wbuf(dev);
    u.u_procp->p_rmt_seq = 0;
}

/* rmt_attach_rbuf -- attach an initialized message buffer to send to the agent */
rmt_attach_rbuf(dev,hang)	/* Buffer returned is rmt.rt_imr */
    dev_t dev;
    int hang;			/* 1 if should wait for the buffer no
				   matter what */
{
    devhack(dev);
    for(;;) {
	if (!hang && (!rmt.rt_open  || rmt_wbuf_attached()))
	    return;
        if ((rmt.rt_flags & RT_RBUF) == 0)
	    break;
	sleep (&rmt.rt_attach, RMT_NOINT_PRI);
    }
    rmt.rt_flags |= RT_RBUF;
    rmt.rt_imr.im_type = RT_BOGUS;/* Just in case we forget to set it
				   later... */
    rmt.rt_imr.im_client = u.u_procp -> p_pid;
    rmt.rt_imr.im_uid = u.u_uid;
    rmt.rt_imr.im_gid = u.u_gid;
    rmt.rt_imr.im_seq = ++rmt.rt_seq;
    bzero((caddr_t) rmt.rt_imr.im_arg, sizeof (rmt.rt_imr.im_arg));
    rmt.rt_imr.im_error = 0;
    rmt.rt_imr.im_dsize = 0;
    rmt.rt_imr.im_follow1 = u.u_rmt_follow1;
    rmt.rt_imr.im_follow2 = u.u_rmt_follow2;
    rmt.rt_imr.im_pag = u.u_rmt_pag;
    bcopy(u.u_rmtWd.fid, rmt.rt_imr.im_wdfid, sizeof(rmt.rt_imr.im_wdfid));
}

rmt_detach_wbuf (dev)
    dev_t dev;
{
    devhack(dev);
    rmt.rt_flags &= ~RT_WBUF;
    wakeup (&rmt.rt_attach);
}

rmt_detach_rbuf(dev)
    dev_t dev;
{
    devhack(dev);
    rmt.rt_flags &= ~(RT_RBUF|RT_SENDING|RT_SIGNAL);
    wakeup (&rmt.rt_attach);
}

/* rmt_send -- send a message to an agent; wait for a reply */
rmt_send(dev, imtype)
   dev_t dev;		/* Device to communicate with agent */
   u_short imtype;	/* The type of the message             */
   /* rmt.rt_imr	   The message itself		       */
   /* rmt.rt_imw	   The returned message from the agent */
{
   devhack(dev);
   label_t lsave;
   int sendSignal = 0, signalSent = 0;
   if (rmt_wbuf_attached())
       panic("rmt_send:	 RT_WBUF attached!!"); /* otherwise we could have deadlock */
   rmt.rt_imr.im_type = imtype;
   u.u_procp->p_rmt_seq = rmt.rt_imr.im_seq; /* sequence number initialized in rmt_attach_rbuf */
#ifdef	MACH
   if (rmt.rt_selproc)
#else	MACH
   if (rmt.rt_selproc && rmt.rt_selproc->p_wchan == (caddr_t)&selwait)
#endif	MACH
       selwakeup(rmt.rt_selproc, 0);
   lsave = u.u_qsave;
   while (setjmp(&u.u_qsave)) {
       sendSignal = 1;
   }
   while (rmt.rt_open && rmt_rbuf_attached()) {
       if (sendSignal)
            rmt.rt_flags |= RT_SIGNAL;
       sleep(&rmt.rt_reply, RMT_INTOK_PRI);
   }
   while (setjmp(&u.u_qsave)) {
       sendSignal = 1;
   }
   while (rmt.rt_open) {
       if (rmt_wbuf_attached()) {
           if (rmt.rt_imw.im_seq == u.u_procp->p_rmt_seq)
	       break;
	   rmt_detach_wbuf(dev);
       }
       if (sendSignal != signalSent) {
	   rmt_attach_rbuf(dev,0);
	   if (!rmt_rbuf_attached())
	   	break; /* the reply has arrived before we could send signal */
           rmt.rt_flags |= RT_SENDING;
	   rmt.rt_imr.im_seq = u.u_procp->p_rmt_seq; /* Reuse the old sequence number */
	   rmt.rt_imr.im_type = RT_signal;
#ifdef	MACH
	   if (rmt.rt_selproc)
#else	MACH
   	   if (rmt.rt_selproc && rmt.rt_selproc->p_wchan == (caddr_t)&selwait)
#endif	MACH
       		selwakeup(rmt.rt_selproc, 0);
	   signalSent = 1;
       }
       sleep(&rmt.rt_reply, RMT_INTOK_PRI);
   }
   if (rmt_rbuf_attached())
       rmt_detach_rbuf(dev);
   if (rmt.rt_open == 0)
       u.u_error = ENXIO;
   u.u_qsave = lsave;
   u.u_procp->p_rmt_seq = 0;	/* to guard against a second write attempt by the agent, which
    				   would block--causing the rmt.rt_imw to be tied up until
				   this process had another remote request */
   if (!u.u_error)
           u.u_error = rmt.rt_imw.im_error;
   if (u.u_error == EINTR || u.u_error == EPIPE /* for kazar */)
       u.u_eosys = RESTARTSYS;
}

rmtselect(dev, flag)
    dev_t dev;
    int flag;
{
    devhack(dev);
    switch(flag) {
	case FREAD:
		if (rmt.rt_flags&RT_RBUF)
			return(1);
#ifdef	MACH
		rmt.rt_selproc = (struct proc *) current_thread();
#else	MACH
		rmt.rt_selproc = u.u_procp;
#endif	MACH
		break;
    }
    return(0);
}


/* rmtread -- device driver entry for rmt; called by agent to read an fs intercept message */
rmtread(dev, uio)
    dev_t dev;		/* device number -- user minor device to decide which agent */
    struct uio *uio;	/* standard unix i/o structure for a device driver */
{
    devhack(dev);
    int error;
    if ((rmt.rt_flags & RT_RBUF) == 0)
	return(0);	/* Caller must be prepared for 0 return; note:
			   this code used to wait, but a change to the
			   signal handling in rmt_send can cause a pending
			   message (signal) to be aborted.  Venus should
			   not hang waiting for the non-message */
    error = uiomove((caddr_t) &rmt.rt_imr, RT_HEADERSIZE + rmt.rt_imr.im_dsize,
    	        UIO_READ, uio);
    if (error) {
	printf("remote read:  error on uiomove\n");
	error = EINVAL;	/* see comment in rmtwrite */
    }
    if (rmt.rt_flags & RT_SIGNAL)
    	wakeup(&rmt.rt_reply);
    rmt_detach_rbuf(dev);
    return(error);
}


/* rmtwrite -- device driver entry for rmt; called by agent to reply to an fs intercept message */
rmtwrite(dev, uio)
    dev_t dev;		/* device number -- user minor device to decide which agent */
    struct uio *uio;	/* standard unix i/o structure for a device driver */
{
    devhack(dev);
    struct proc *p;
    int error;
    while (rmt.rt_flags & RT_WBUF)
	sleep(&rmt.rt_attach,RMT_INTOK_PRI);
    rmt.rt_flags |= RT_WBUF;
    error = uiomove((caddr_t) &rmt.rt_imw, sizeof (rmt.rt_imw),
    	        UIO_WRITE, uio);
    if (error) {
	printf("Remote write:  error on uiomove\n");
	rmt_detach_wbuf(dev);
	return(EINVAL);	/* uiomove doesn't set u.u_error or error reasonably (not a user
			   level error number).  The errors that have been seen here
			   have all arisen because of bad arguments (i.e. no & on the
			   structure name passed to the write call), hence EINVAL */
    }
    p = pfind(rmt.rt_imw.im_client);        
    if (p == NULL || rmt.rt_imw.im_seq != p->p_rmt_seq) {
	rmt_detach_wbuf(dev);
	return(ESRCH); /* no such process */
    }
    wakeup(&rmt.rt_reply);
    wakeup(&rmt.rt_attach);	/* Bletch... */
    return(0);
}
