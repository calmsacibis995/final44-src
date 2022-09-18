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
 * $Log:	drb.c,v $
 * Revision 2.3  89/03/09  22:33:03  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:01:36  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.
 *	[V1(1)]
 *
 * 23-Apr-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created from previous DR11-B driver (V3.04g).
 *
 */
/*
 *  Generic DR11-B interface for DR11-B/W driver  
 */

/*	drb.c	CMU	3/26/82	*/

#include <drb.h>

#if	NDRB > 0

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/map.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/conf.h>
#include <sys/uio.h>

#include <vax/pte.h>

#include <vaxuba/drreg.h>
#include <vaxuba/drbreg.h>
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>

/*
 *  DR11-B state per logical unit
 */
struct drbstat drbstat[NDRB];

/*
 *  drbopen - open DR11-B device
 *
 *  Show logical DR11-B device now in use.  Set default read and write
 *  function bits.
 *
 *  Return error EBUSY if already open.
 */

/*ARGSUSED*/
drbopen(dev, flag)
{
    register struct drbstat *drbs = &drbstat[DRBUNIT(dev)];

    if (drbs->drbs_open != 0)
	return(EBUSY);
    else
    {
	drbs->drbs_open++;
	drbs->drbs_rcom = DRB_RCOM;
	drbs->drbs_wcom = DRB_WCOM;
    }
    return(0);
}



/*
 *  drbclose - close DR11-B device
 *
 *  Decrement open count on logical device.
 */

/*ARGSUSED*/
drbclose(dev, flag)
{
    register struct drbstat *drbs = &drbstat[DRBUNIT(dev)];

    drbs->drbs_open--;
}


/*
 *  drbphys - set buffer header parameters for DR11-B DMA
 *
 *  Set device function bits for the appropriate operation into the
 *  buffer header and call drphys() to finish up any further DR11
 *  pre-processing of buffer header before transfer.
 *
 *  Called from physio() after buffer header has been assigned and prior
 *  to passing it to the device strategy routine.
 */

unsigned
drbphys(bp)
register struct buf *bp;
{
    register struct drbstat *drbs = &drbstat[DRBUNIT(bp->b_dev)];

    if (bp->b_flags&B_READ)
	dr_com(bp) = drbs->drbs_rcom;
    else
	dr_com(bp) = drbs->drbs_wcom;
    drphys(bp);
}



/*
 *  drbread - initiate read operation on DR11-B
 *
 *  Pick up next buffer header in list and call physio().
 */

drbread(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    register struct drbstat *drbs = &drbstat[DRBUNIT(dev)];
    register struct buf *bp = drbs->drbs_bufp;
    extern drstrategy();

    drbs->drbs_bufp = bp->b_forw;
    return(physio(drstrategy, bp, dev, B_READ, drbphys, uio));
}



/*
 *  drbwrite - initiate write operation on DR11-B
 *
 *  Pick up next buffer header in list and call physio().
 */

drbwrite(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    register struct drbstat *drbs = &drbstat[DRBUNIT(dev)];
    register struct buf *bp = drbs->drbs_bufp;
    extern drstrategy();

    drbs->drbs_bufp = bp->b_forw;

    return(physio(drstrategy, drbs->drbs_bufp, dev, B_WRITE, drbphys, uio));
}

/*
 *  drioctl - DR11-B ioctl call
 *
 *  DRBIOCGETP - get device parameters
 *  DRBIOCSETP - set device parameters
 *
 */

/* ARGSUSED */
drbioctl(dev, cmd, addr, flag)
caddr_t addr;
dev_t dev;
{
    register struct drbstat *drbs = &drbstat[DRBUNIT(dev)];

    switch (cmd)
    {
	/*
	 *  Return device parameters:
	 *  - read function bits
	 *  - write function bits
	 */
	case DRBIOCGETP:
	{
	    struct drbparam *drbp = (struct drbparam *)addr;

	    drbp->drbp_rcom = drbs->drbs_rcom;
	    drbp->drbp_wcom = drbs->drbs_wcom;
	    break;
	}

	/*
	 *  Change device parameters
	 *  - read function bits (mask with DRBRBITS)
	 *  - write function bits (mask with DRBWBITS)
	 */
	case DRBIOCSETP:
	{
	    struct drbparam *drbp = (struct drbparam *)addr;

	    drbs->drbs_rcom = drbp->drbp_rcom&(DRBRBITS);
	    drbs->drbs_wcom = drbp->drbp_wcom&(DRBWBITS);
	    break;
	}

	/*
	 *  If we have never heard of this command, it may possibly
	 *  be a generic DR11-B/W call.
	 */
	default:
	    return (-1);
    }
    return(0);
}

/*
 *  drbintr - interrupt received from DR11-B
 */

/*ARGSUSED*/
drbintr(unit)
{
    /*
     *  No special processing required.
     */
    return(0);
}



/*
 *  drbtout - I/O timeout on DR11-B
 */

/*ARGSUSED*/
drbtout(unit)
{
    /*
     *  No special processing required.
     */
}



/*
 *  drbreset - called after UBA init
 */

/*ARGSUSED*/
drbreset(unit)
{
    /*
     *  No special processing required.
     */
}



/*
 *  drbattach - initialize newly configured DR11-B device
 *
 *  Allocate the next logical DR11-B unit and fill in the
 *  appropriate entry in the physical to logical unit translation
 *  Circularly link the I/O buffer headers together for later
 *  use.
 *
 *  If we are all out of logical DR11-B devices, somebody fouled
 *  up the configuration.
 */

drbattach(unit)
{
    static int ndrb = 0;
    register struct drbstat *drbs = &drbstat[ndrb];
    register int b;

    if (ndrb >= NDRB)
	panic("drbattach");

    dr_logunit(unit) = ndrb++;

    for (b=0; b < NDRBBUF; b++)
    {
	drbs->drbs_buf[b].b_forw = &(drbs->drbs_buf[b==(NDRBBUF-1)?0:(b+1)]);
	drbs->drbs_buf[b].b_back = &(drbs->drbs_buf[b==0?(NDRBBUF-1):(b-1)]);
    }
    drbs->drbs_bufp = &(drbs->drbs_buf[0]);
}
#endif
