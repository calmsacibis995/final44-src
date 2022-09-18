/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ms.c,v $
 * Revision 2.7  90/02/19  15:14:10  jjc
 * 	Picked up SunOS 3.5 driver and modified for Mach.
 * 	[90/02/13            jjc]
 * 
 */
#ifndef lint
static	char sccsid[] = "@(#)ms.c 1.1 87/12/21";
#endif

/*
 * Copyright (c) 1986, 1987 by Sun Microsystems, Inc.
 */

/*
 * Mouse line discipline
 */

#include <ms.h>
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/buf.h>
#include <sys/systm.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <sys/tty.h>
#include <sys/vmmac.h>
#include <sys/kernel.h>

#ifdef	MACH
#else	MACH
#include <machine/pte.h>
#endif	MACH
#include <machine/mmu.h>
#include <machine/scb.h>
#include <sundev/vuid_event.h>
#include <sundev/msreg.h>
#include <sundev/msio.h>


/*
 * Mouse select management is done by utilizing the tty mechanism.
 * We place a single character on the tty raw input queue whenever
 * there is some amount of mouse data available to be read.  Once,
 * all the data has been read, the tty raw input queue is flushed.
 *
 * Note: It is done in order to get around the fact that line
 * disiplines don't have select operations because they are always
 * expected to be ttys that stuff characters when they get them onto
 * a queue.
 *
 * Note: We use spl5 for the mouse because it is functionally the
 * same as spl6 and the tty mechanism is using spl5.  The original
 * code that was doing its own select processing was using spl6.
 */
#define	spl_ms	spl5

#define ABS(x)          ((x) < 0 ? -(x) : (x))
#define BYTECLIP(x)     (char)((x) > 127 ? 127 : ((x) < -128 ? -128 : (x)))

struct msdata {
    struct ms_softc msd_softc;
    struct tty     *msd_tp;
    short           msd_xerox;
    char            msd_oldbutt;
    short           msd_state;
    short           msd_jitter;
};

/*
 * Input routine states. See msinput().
 */
#define MS_WAIT_BUTN    0
#define MS_WAIT_X       1
#define MS_WAIT_Y       2
#define MS_WAIT_X2      3
#define MS_WAIT_Y2      4

struct msdata   msdata[NMS];
struct msdata  *mstptomsd();
static void	msincr();

int             ms_overrun_msg;	/* Message when overrun circular buffer */
int             ms_overrun_cnt;	/* Increment when overrun circular buffer */

/*
 * Max pixel delta of jitter controlled. As this number increases the jumpiness
 * of the ms increases, i.e., the coarser the motion for medium speeds. 
 */
int             ms_jitter_thresh = 1;

/*
 * ms_jitter_thresh is the maximum number of jitters suppressed. Thus,
 * hz/ms_jitter_thresh is the maximum interval of jitters suppressed. As
 * ms_jitter_thresh increases, a wider range of jitter is suppressed. However,
 * the more inertia the mouse seems to have, i.e., the slower the mouse is to
 * react. 
 */

/*
 * Measure how many (ms_speed_count) ms deltas exceed threshold
 * (ms_speedlimit). If ms_speedlaw then throw away deltas over ms_speedlimit.
 * This is to keep really bad mice that jump around from getting too far. 
 */
int             ms_speedlimit = 48;
int             ms_speedlaw = 0;
int             ms_speed_count;
int             msjitterrate = 12;

#define	JITTER_TIMEOUT (hz/msjitterrate)

int             msjittertimeout;/* Timeout used when mstimeout in affect */
/*
 * Mouse buffer size in bytes.  Place here as variable so that one could
 * massage it using adb if it turns out to be too small. 
 */
int             MS_BUF_BYTES = 4096;

int             MS_DEBUG;

/*
 * Mouse line discipline 
 */

/*
 * Open a mouse. Calls sets mouse line characteristics 
 */
/* ARGSUSED */
msopen(dev, tp)
    dev_t           dev;
    struct tty     *tp;
{
    register int    err, i;
    struct sgttyb   sg;
    register struct mousebuf *b;
    register struct ms_softc *ms;
    register struct msdata *msd;
#ifdef	MACH
#else	MACH
    caddr_t         zmemall();
#endif	MACH
    register struct cdevsw *dp;

    /*
     * See if tp is being used to drive ms already. 
     */
    for (i = 0; i < NMS; ++i)
	if (msdata[i].msd_tp == tp)
	    return (0);
    /*
     * Get next free msdata. 
     */
    for (i = 0; i < NMS; ++i)
	if (msdata[i].msd_tp == 0)
	    goto found;
    return (EBUSY);
found:
    /*
     * Open tty. 
     */
    if (err = ttyopen(dev, tp))
	return (err);
    /*
     * Setup tty flags 
     */
    dp = &cdevsw[major(dev)];
    if (err = (*dp->d_ioctl) (dev, TIOCGETP, (caddr_t) & sg, 0))
	goto error;
    sg.sg_flags = RAW + ANYP;
    sg.sg_ispeed = sg.sg_ospeed = B1200;
    if (err = (*dp->d_ioctl) (dev, TIOCSETP, (caddr_t) & sg, 0))
	goto error;
    /*
     * Set up private data. 
     */
    msd = &msdata[i];
    msd->msd_state = MS_WAIT_BUTN;
    msd->msd_tp = tp;
    ms = &msd->msd_softc;
    /*
     * Allocate buffer and initialize data. 
     */
    if (ms->ms_buf == 0) {
	ms->ms_bufbytes = MS_BUF_BYTES;
#ifdef	MACH
		b = (struct mousebuf *)sun_kmem_alloc(ms->ms_bufbytes);
#else	MACH
	b = (struct mousebuf *) zmemall(memall, ms->ms_bufbytes);
#endif	MACH
	if (b == 0) {
	    err = EINVAL;
	    goto error;
	}
	b->mb_size = 1 + (ms->ms_bufbytes - sizeof(struct mousebuf))
	    / sizeof(struct mouseinfo);
	ms->ms_buf = b;
	ms->ms_vuidaddr = VKEY_FIRST;
	msjittertimeout = JITTER_TIMEOUT;
	msflush(msd);
    }
    return (0);
error:
    bzero((caddr_t) msd, sizeof(*msd));
    bzero((caddr_t) ms, sizeof(*ms));
    return (err);
}

/*
 * Close the mouse 
 */
msclose(tp)
    struct tty     *tp;
{
    register struct msdata *msd = mstptomsd(tp);
    register struct ms_softc *ms;

    if (msd == 0)
	return;
    ms = &msd->msd_softc;
    /* Free mouse buffer */
    if (ms->ms_buf != NULL)
#ifdef	MACH
	sun_kmem_free((caddr_t)ms->ms_buf, ms->ms_bufbytes);
    /* Close line discipline */
    ttylclose(tp);
#else	MACH
	wmemfree((caddr_t) ms->ms_buf, ms->ms_bufbytes);
    /* Close tty */
    ttyclose(tp);
#endif	MACH
    /* Zero structures */
    bzero((caddr_t) msd, sizeof(*msd));
    bzero((caddr_t) ms, sizeof(*ms));
}

/*
 * Read from the mouse buffer 
 */
msread(tp, uio)
    struct tty     *tp;
    struct uio     *uio;
{
    register struct msdata *msd = mstptomsd(tp);
    register struct ms_softc *ms;
    register struct mousebuf *b;
    register struct mouseinfo *mi;
    register int    error = 0, pri, send_event, hwbit;
    register char   c;
    Firm_event      fe;

    if (msd == 0)
	return (EINVAL);
    ms = &msd->msd_softc;
    b = ms->ms_buf;
    pri = spl_ms();
    /*
     * Wait on tty raw queue if this queue is empty since the tty is
     * controlling the select/wakeup/sleep stuff. 
     */
    while (tp->t_rawq.c_cc <= 0) {
	if (tp->t_state & TS_NBIO) {
	    (void) splx(pri);
	    return (EWOULDBLOCK);
	}
	(void) sleep((caddr_t) & tp->t_rawq, TTIPRI);
    }
    while (!error && (ms->ms_oldoff1 || ms->ms_oldoff != b->mb_off)) {
	mi = &b->mb_info[ms->ms_oldoff];
	switch (ms->ms_readformat) {

	  case MS_3BYTE_FORMAT:
	    if (uio->uio_resid == 0)
		goto done;
	    switch (ms->ms_oldoff1++) {

	      case 0:
		c = 0x80 | mi->mi_buttons;
		/* Update read buttons */
		ms->ms_readbuttons = mi->mi_buttons;
		break;

	      case 1:
		c = mi->mi_x;
		break;

	      case 2:
		c = -mi->mi_y;
		ms->ms_oldoff++;
		if (ms->ms_oldoff >= b->mb_size)
		    ms->ms_oldoff = 0;
		ms->ms_oldoff1 = 0;
		break;
	    }
	    /* lower pri to avoid mouse droppings */
	    (void) splx(pri);
	    error = ureadc(c, uio);
	    pri = spl_ms();
	    break;

	  case MS_VUID_FORMAT:
	    if (uio->uio_resid < sizeof(Firm_event))
		goto done;
	    send_event = 0;
	    switch (ms->ms_oldoff1++) {

	      case 0:		/* Send x if changed */
		if (mi->mi_x != 0) {
		    fe.id = vuid_id_addr(ms->ms_vuidaddr) | vuid_id_offset(LOC_X_DELTA);
		    fe.pair_type = FE_PAIR_ABSOLUTE;
		    fe.pair = LOC_X_ABSOLUTE;
		    fe.value = mi->mi_x;
		    send_event = 1;
		}
		break;

	      case 1:		/* Send y if changed */
		if (mi->mi_y != 0) {
		    fe.id = vuid_id_addr(ms->ms_vuidaddr) | vuid_id_offset(LOC_Y_DELTA);
		    fe.pair_type = FE_PAIR_ABSOLUTE;
		    fe.pair = LOC_Y_ABSOLUTE;
		    fe.value = -mi->mi_y;
		    send_event = 1;
		}
		break;

	      default:		/* Send buttons if changed */
		hwbit = MS_HW_BUT1 >> (ms->ms_oldoff1 - 3);
		if ((ms->ms_readbuttons & hwbit) != (mi->mi_buttons & hwbit)) {
		    fe.id = vuid_id_addr(ms->ms_vuidaddr) |
			vuid_id_offset(BUT(1) + (ms->ms_oldoff1 - 3));
		    fe.pair_type = FE_PAIR_NONE;
		    fe.pair = 0;
		    /* Update read buttons and set value */
		    if (mi->mi_buttons & hwbit) {
			fe.value = 0;
			ms->ms_readbuttons |= hwbit;
		    } else {
			fe.value = 1;
			ms->ms_readbuttons &= ~hwbit;
		    }
		    send_event = 1;
		}
		/* Increment mouse buffer pointer */
		if (ms->ms_oldoff1 == 5) {
		    ms->ms_oldoff++;
		    if (ms->ms_oldoff >= b->mb_size)
			ms->ms_oldoff = 0;
		    ms->ms_oldoff1 = 0;
		}
		break;

	    }
	    if (send_event) {
		fe.time = mi->mi_time;
		ms->ms_vuidcount--;
		/* lower pri to avoid mouse droppings */
		(void) splx(pri);
		error = uiomove((caddr_t) & fe, sizeof(fe),
				UIO_READ, uio);
		/* spl_ms should return same priority as pri */
		pri = spl_ms();
	    }
	    break;

	}
    }
done:
    /* Flush tty if no more to read */
    if ((ms->ms_oldoff1 == 0) && (ms->ms_oldoff == b->mb_off))
	ttyflush(tp, FREAD);
    /* Release protection AFTER ttyflush or will get out of sync with tty */
    (void) splx(pri);
    return (0);
}

/*
 * Mouse ioctl 
 */
msioctl(tp, cmd, data, flag)
    struct tty     *tp;
    int             cmd;
    caddr_t         data;
    int             flag;
{
    register struct msdata *msd = mstptomsd(tp);
    register struct ms_softc *ms;
    int             err = 0;
    Vuid_addr_probe *addr_probe;

    if (MS_DEBUG)
	printf("ms_ioctl(%X,%X,%X,%X)\n", tp, cmd, data, flag);
    if (msd == 0)
	return (EINVAL);
    ms = &msd->msd_softc;
    switch (cmd) {
      case FIONREAD:
	switch (ms->ms_readformat) {
	  case MS_3BYTE_FORMAT:
	    *(int *) data = ms->ms_samplecount;
	    break;

	  case MS_VUID_FORMAT:
	    *(int *) data = sizeof(Firm_event) * ms->ms_vuidcount;
	    break;
	}
	break;

      case VUIDSFORMAT:
	if (*(int *) data == ms->ms_readformat)
	    break;
	ms->ms_readformat = *(int *) data;
	/*
	 * Flush mouse buffer because otherwise ms_*counts get out of sync and
	 * some of the offsets can too. 
	 */
	msflush(msd);
	break;

      case VUIDGFORMAT:
	*(int *) data = ms->ms_readformat;
	break;

      case VUIDSADDR:
	addr_probe = (Vuid_addr_probe *) data;
	if (addr_probe->base != VKEY_FIRST) {
	    err = ENODEV;
	    break;
	}
	ms->ms_vuidaddr = addr_probe->data.next;
	break;

      case VUIDGADDR:
	addr_probe = (Vuid_addr_probe *) data;
	if (addr_probe->base != VKEY_FIRST) {
	    err = ENODEV;
	    break;
	}
	addr_probe->data.current = ms->ms_vuidaddr;
	break;

      case TIOCSETD:
	/*
	 * Don't let the line discipline change once it has been set to a
	 * mouse.  Changing the ldisc causes msclose to be called even if the
	 * ldisc of the tp is the same. We can't let this happen because the
	 * window system may have a handle on the mouse buffer. The basic
	 * problem is one of having anything depending on the continued
	 * existence of ldisc related data. The fix is to have: 1) a way of
	 * handing data to the dependent entity, and 2) notifying the dependent
	 * entity that the ldisc has been closed. 
	 */
	break;

      case MSIOGETBUF:
	*(int *) data = (int) ms->ms_buf;
	break;

      case MSIOGETPARMS:
	if (MS_DEBUG)
	    printf("ms_getparms\n");
    	err = ms_getparms((Ms_parms *)data);
	break;

      case MSIOSETPARMS:
	if (MS_DEBUG)
	    printf("ms_setparms\n");
	err = ms_setparms((Ms_parms *)data);
	break;

      default:
	err = ttioctl(tp, cmd, data, flag);
    }
    return (err);
}

ms_getparms(data)
    register Ms_parms	*data;
{
    data->jitter_thresh = ms_jitter_thresh;
    data->speed_law = ms_speedlaw;
    data->speed_limit = ms_speedlimit;
    return 0;
}

ms_setparms(data)
    register Ms_parms	*data;
{
    ms_jitter_thresh = data->jitter_thresh;
    ms_speedlaw = data->speed_law;
    ms_speedlimit = data->speed_limit;
    return 0;
}

msflush(msd)
    register struct msdata *msd;
{
    register struct ms_softc *ms = &msd->msd_softc;
    int             s = spl_ms();

    ms->ms_oldoff = 0;
    ms->ms_oldoff1 = 0;
    ms->ms_buf->mb_off = 0;
    ms->ms_vuidcount = 0;
    ms->ms_samplecount = 0;
    ms->ms_readbuttons = MS_HW_BUT1 | MS_HW_BUT2 | MS_HW_BUT3;
    msd->msd_oldbutt = ms->ms_readbuttons;
    ttyflush(msd->msd_tp, FREAD);
    (void) splx(s);
}

/*
 * Mouse input routine; process a byte received from a mouse and
 * assemble into a mouseinfo message for the window system.
 * Handles both XEROX mice and Mouse Systems mice.
 *
 * The MSC mice send a five-byte packet organized as 
 *	button, dx, dy, dx, dy
 * where dx and dy can be any signed byte value. The mouseinfo message
 * is organized as
	dx, dy, button, timestamp
 * Our strategy, then, is to split the MSC packet into two mouseinfo
 * messages, retaining the button information for the second message.
 *
 * Xerox mice are similar but the packet is only three bytes long:
 * 	button, dx, dy
 * Xerox mice have button byte 0x88; MSC mice have button byte
 * 0x80, both with button values in low 3 bits. We'll use this to
 * distinguish between them.
 *
 * Basic algorithm: throw away bytes until we get a [potential]
 * button byte. Collect button, dx, dy, and send. MSC mouse?
 * Save button, collect new dx, dy, and send. Repeat.
 *
 * Watch out for overflow!
 */
/* ARGSUSED */
msinput(c, tp)
    register char   c;
    struct tty     *tp;
{
    register struct msdata *msd = mstptomsd(tp);
    register struct ms_softc *ms;
    register struct mousebuf *b;
    register struct mouseinfo *mi;
    register int    jitter_radius;
    register int    but_dif;
    register int    temp;

    if (msd == 0)
	return;
    ms = &msd->msd_softc;
    b = ms->ms_buf;
    if (b == NULL)
	return;
    mi = &b->mb_info[b->mb_off];

    switch (msd->msd_state) {

    case MS_WAIT_BUTN:
	if ((c & 0xf0) != 0x80) {
#ifdef MS_DEBUG
	    printf("Mouse input char %x discarded\n", (int) c & 0xff);
#endif
	    return;
	}

	/*
	 * Probably a button byte.  Lower 3 bits are left, middle, right.
	 * We're going to try to use the allegation that Xerox mice set bit 3
	 * (0x08) to decide what to do next.
	 */
	mi->mi_buttons = c & (MS_HW_BUT1 | MS_HW_BUT2 | MS_HW_BUT3);
#ifndef IGNORE_XEROX
	msd->msd_xerox = c & 8;
#endif
	break;

    case MS_WAIT_X:
	/*
	 * Delta X byte.  Add the delta X from this sample to the delta X
	 * we're accumulating in the current event.
	 */
	temp = (int) (mi->mi_x + c);
	mi->mi_x = BYTECLIP(temp);
	uniqtime(&mi->mi_time);	/* record time when sample arrived */
	break;

    case MS_WAIT_Y:
	/*
	 * Delta Y byte.  Add the delta Y from this sample to the delta Y
	 * we're accumulating in the current event. (Subtract, actually,
	 * because the mouse reports increasing Y up the screen.)
	 */
	temp = (int) (mi->mi_y - c);
	mi->mi_y = BYTECLIP(temp);
	break;

    case MS_WAIT_X2:
	/*
	 * Second delta X byte. Only for MSC mice.
	 */
	temp = (int) (mi->mi_x + c);
	mi->mi_x = BYTECLIP(temp);
	uniqtime(&mi->mi_time);
	break;

    case MS_WAIT_Y2:
	/*
	 * Second delta Y byte. Only for MSC mice.
	 */
	temp = (int) (mi->mi_y - c);
	mi->mi_y = BYTECLIP(temp);
	break;

    }

    /*
     * Done yet?
     */
    if ( (msd->msd_state == MS_WAIT_Y2) ||
	 (msd->msd_xerox && (msd->msd_state == MS_WAIT_Y)) )
	msd->msd_state = MS_WAIT_BUTN;		/* BONG. Start again. */
    else {
	msd->msd_state += 1;
	return;
    }

    if (msd->msd_jitter) {
	untimeout(msincr, (caddr_t) msd);
	msd->msd_jitter = 0;
    }

    if (mi->mi_buttons == msd->msd_oldbutt) {
	/*
	 * Buttons did not change; did position?
	 */
	if (mi->mi_x == 0 && mi->mi_y == 0) {
	    return;	/* no, position did not change - boring event */
	}

	/*
	 * Did the mouse move more than the jitter threshhold?
	 */
	jitter_radius = ms_jitter_thresh;
#ifndef IGNORE_XEROX
	if (msd->msd_xerox)
	    /*
	     * Account for double resolution of xerox mouse.
	     */
	    jitter_radius *= 2;
#endif
	if (ABS((int) mi->mi_x) <= jitter_radius &&
	    ABS((int) mi->mi_y) <= jitter_radius) {
	    /*
	     * Mouse moved less than the jitter threshhold. Don't indicate an
	     * event; keep accumulating motions. After "msjittertimeout"
	     * ticks expire, treat the accumulated delta as the real delta.
	     */
	    msd->msd_jitter = 1;
	    timeout(msincr, (caddr_t) msd, msjittertimeout);
	    return;
	}
    } else {
	/* Update vuid event count for buttons */
	but_dif = msd->msd_oldbutt ^ mi->mi_buttons;
	if (but_dif & MS_HW_BUT1)
	    ms->ms_vuidcount++;
	if (but_dif & MS_HW_BUT2)
	    ms->ms_vuidcount++;
	if (but_dif & MS_HW_BUT3)
	    ms->ms_vuidcount++;
    }
    msd->msd_oldbutt = mi->mi_buttons;
    msincr(msd);
}

/*
 * Increment the mouse sample pointer.
 * Called either immediately after a sample or after a jitter timeout.
 */
static void
msincr(msd)
    struct msdata  *msd;
{
    register struct ms_softc *ms = &msd->msd_softc;
    register struct mousebuf *b = ms->ms_buf;
    register struct mouseinfo *mi;
    char            oldbutt;
    register short  xc, yc;
    register int    wake;
    register int    speedlimit = ms_speedlimit;
    register int    xabs, yabs;
    int             s;

    if (b == NULL)
	return;
    s = spl_ms();
    mi = &b->mb_info[b->mb_off];

    if (ms_speedlaw) {
#ifndef IGNORE_XEROX
	if (msd->msd_xerox)
	    /*
	     * Account for double resolution of Xerox mouse. 
	     */
	    speedlimit *= 2;
#endif
	xabs = ABS((int) mi->mi_x);
	yabs = ABS((int) mi->mi_y);
	if (xabs > speedlimit || yabs > speedlimit)
	    ms_speed_count++;
	if (xabs > speedlimit)
	    mi->mi_x = 0;
	if (yabs > speedlimit)
	    mi->mi_y = 0;
    }

    oldbutt = mi->mi_buttons;

#ifndef IGNORE_XEROX
    /*
     * XEROX mice are 200/inch; scale to 100/inch. 
     */
    if (msd->msd_xerox) {
	/*
	 * Xc and yc carry over fractional part. You might think that we have
	 * to worry about mi->mi_[xy] being negative here, but remember that
	 * using shift to divide always leaves a positive remainder! 
	 */
	xc = mi->mi_x & 1;
	yc = mi->mi_y & 1;
	mi->mi_x >>= 1;
	mi->mi_y >>= 1;
    } else
#endif
	xc = yc = 0;

    /* Update sample and event counts */
    ms->ms_samplecount++;
    if (mi->mi_x)
	ms->ms_vuidcount++;
    if (mi->mi_y)
	ms->ms_vuidcount++;
    /* See if need to wake up anyone waiting for input */
    wake = b->mb_off == ms->ms_oldoff;

    /* Adjust circular buffer pointer */
    if (++b->mb_off >= b->mb_size) {
	b->mb_off = 0;
	mi = b->mb_info;
    } else {
	mi++;
    }

    /*
     * If over-took read index then flush buffer so that mouse state (e.g.,
     * vuidcount) is consistent. 
     */
    if (b->mb_off == ms->ms_oldoff) {
	if (ms_overrun_msg)
	    printf("Mouse buffer flushed when overrun.\n");
	msflush(msd);
	ms_overrun_cnt++;
	mi = b->mb_info;
    }

    /* Remember current buttons and fractional part of x & y */
    mi->mi_buttons = oldbutt;
    mi->mi_x = (char) xc;
    mi->mi_y = (char) yc;
    if (wake)
	/* Place character on tty raw input queue to trigger select */
	ttyinput('\0', msd->msd_tp);
    (void) splx(s);
}

/*
 * Match tp to msdata. 
 */
struct msdata  *
mstptomsd(tp)
    struct tty     *tp;
{
    register        i;

    /*
     * Get next free msdata. 
     */
    for (i = 0; i < NMS; ++i)
	if (msdata[i].msd_tp == tp)
	    return (&msdata[i]);
    printf("mstptomsd called with unknown tp %X\n", tp);
    return (0);
}
