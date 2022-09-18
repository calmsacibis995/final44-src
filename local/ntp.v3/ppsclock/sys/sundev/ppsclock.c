#ifndef lint
static char rcsid[] =
    "@(#) $Header: ppsclock.c,v 1.5 92/08/20 19:46:35 leres Exp $ (LBL)";
#endif
/*
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66.
 *
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratory.
 * 4. The name of the University may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/* ppsclock streams module */

#define PPSCLOCKLED

#include <sys/param.h>
#include <sys/errno.h>
#include <sys/stream.h>
#include <sys/stropts.h>
#include <sys/time.h>
#include <sys/ttycom.h>
#include <sys/tty.h>
#include <sys/ppsclock.h>

#include <sundev/zsreg.h>
#include <sundev/zscom.h>

#ifdef PPSCLOCKLED
#include <sun4c/auxio.h>

/* In case these aren't defined by auxio.h */
#if !defined(LED_ON) && !defined(LED_OFF)
#define	LED_ON		*(u_char *)AUXIO_REG = AUX_MBO|AUX_EJECT|AUX_LED
#define	LED_OFF		*(u_char *)AUXIO_REG = AUX_MBO|AUX_EJECT
#endif

int ppsclockled;
#endif

int	ppsclock_open();
void	ppsclock_close();
void	ppsclock_wput();
static	void ppsclock_intr();

static	struct module_info stm_info = {
	0x434c,				/* module id number (??) */
	PPSCLOCKSTR,			/* module name */
	0,				/* minimum packet size */
	INFPSZ,				/* infinite maximum packet size */
	STRHIGH,			/* hi-water mark */
	STRLOW,				/* lo-water mark */
};

static struct qinit ppsclock_rinit = {
	(int (*)())ppsclock_wput,	/* put procedure */
	NULL,				/* service procedure */
	ppsclock_open,			/* called on startup */
	(int (*)())ppsclock_close,	/* called on finish */
	NULL,				/* for 3bnet only */
	&stm_info,			/* module information structure */
	NULL				/* module statistics structure */
};

static struct qinit ppsclock_winit = {
	(int (*)())ppsclock_wput,	/* put procedure */
	NULL,				/* service procedure */
	ppsclock_open,			/* called on startup */
	(int (*)())ppsclock_close,	/* called on finish */
	NULL,				/* for 3bnet only */
	&stm_info,			/* module information structure */
	NULL				/* module statistics structure */
};

struct streamtab ppsclockinfo = {
	&ppsclock_rinit,		/* qinit for read side */
	&ppsclock_winit,		/* qinit for write side */
	NULL,				/* mux qinit for read */
	NULL,				/* mux qinit for write */
	NULL				/* list of modules to be pushed */
};

static struct ppsclockev ppsclockev;
static struct zsops *ppssavedzsops;
static struct zsops ppszsops;
static struct zscom *ppssavedzscom;

#ifdef OPENPROMS
extern struct zsaline *zsaline;
#else
extern struct zsaline zsaline[];
#endif

#ifdef PPS_SYNC
/*
 * The hardpps() routine is called at every pps interrupt in order to
 * discipline the cpu clock oscillator. It requires corresponding kernel
 * support.
 */
extern hardpps();			/* pps signal processor */
extern struct timeval time;		/* the real kernel time */
#endif /* PPS_SYNC */

/*
 * open CLOCK STREAMS module
 */
/* ARGSUSED */
int
ppsclock_open(q, dev, flag, sflag)
	register queue_t *q;
	register dev_t dev;
	register int flag;
	register int sflag;
{
	register struct zsaline *za;
	register struct zscom *zs;

	/* We must be called with MODOPEN. */
	if (sflag != MODOPEN)
		return (OPENFAIL);

	/* Hook up our external status interrupt handler */
	if (ppssavedzsops == NULL) {
		za = &zsaline[minor(dev) & 0x7f];
		if ((zs = za->za_common) == NULL)
			return (OPENFAIL);
		ppssavedzsops = zs->zs_ops;
		ppszsops = *ppssavedzsops;
		ppszsops.zsop_xsint = (int (*)())ppsclock_intr;
		zsopinit(zs, &ppszsops);
		ppssavedzscom = zs;
	}
	return (0);
}

void
ppsclock_close(q)
	register queue_t *q;
{

	/* Flush outstanding packets */
	flushq(WR(q), FLUSHALL);

	/* Unhook our external status interrupt handler */
	if (ppssavedzsops) {
		zsopinit(ppssavedzscom, ppssavedzsops);
		ppssavedzscom = NULL;
		ppssavedzsops = NULL;
	}
}


/*
 * Read and write put procedure. Note that we can only get ioctl
 * messages in the "write" case.
 */
void
ppsclock_wput(q, mp)
	register queue_t *q;
	register mblk_t *mp;
{
	register struct iocblk *iocp;
	register mblk_t *datap;

	switch (mp->b_datap->db_type) {

	case M_FLUSH:
		if (*mp->b_rptr & FLUSHW)
			flushq(q, FLUSHDATA);
		putnext(q, mp);
		break;

	case M_IOCTL:
		iocp = (struct iocblk *)mp->b_rptr;
		if (iocp->ioc_cmd == CIOGETEV) {
			datap = allocb(sizeof(struct ppsclockev), BPRI_HI);
			if (datap == NULL) {
				mp->b_datap->db_type = M_IOCNAK;
				iocp->ioc_error = ENOMEM;
				qreply(q, mp);
				break;
			}
			if (mp->b_cont)
				panic("ppsclock b_cont not null");
			mp->b_cont = datap;
			*(struct ppsclockev *)datap->b_wptr = ppsclockev;
			datap->b_wptr +=
			    sizeof(struct ppsclockev) / sizeof(*datap->b_wptr);
			mp->b_datap->db_type = M_IOCACK;
			iocp->ioc_count = sizeof(struct ppsclockev);
			qreply(q, mp);
			break;
		}
		/* fall through */

	default:
		putnext(q, mp);
		break;
	}
}

static void
ppsclock_intr(zs)
	register struct zscom *zs;
{
	register struct zsaline *za = (struct zsaline *)zs->zs_priv;
	register struct zscc_device *zsaddr = zs->zs_addr;
	register u_char s0;
	register struct timeval *tvp = &ppsclockev.tv;
#ifdef PPS_SYNC
	long usec;
#endif /* PPS_SYNC */

	/*
	 * This code captures a timestamp at the designated transition of
	 * the PPS signal. If the PPS_SYNC option has been configured in
	 * the kernel, the code provides a pointer to the timestamp, as
	 * well as the hardware counter value at the capture.
	 */
	s0 = zsaddr->zscc_control;
	if ((s0 ^ za->za_rr0) & ZSRR0_CD) {
		if ((s0 & ZSRR0_CD) != 0) {
#ifdef PPS_SYNC
			usec = time.tv_usec;
#endif /* PPS_SYNC */
#ifdef PPSCLOCKLED
			if (ppsclockled) {
				LED_OFF;
				uniqtime(tvp);
				LED_ON;
			} else
#endif /* PPSCLOCKLED */
				uniqtime(tvp);
			++ppsclockev.serial;
#ifdef PPS_SYNC
			usec = tvp->tv_usec - usec;
			if (usec < 0)
				usec += 1000000;
			hardpps(tvp, usec);
#endif /* PPS_SYNC */
		}
		za->za_rr0 = s0;
		zsaddr->zscc_control = ZSWR0_RESET_STATUS;
		return;
	}

	/* Call real external status interrupt routine */
	(void)(*ppssavedzsops->zsop_xsint)(zs);
}
