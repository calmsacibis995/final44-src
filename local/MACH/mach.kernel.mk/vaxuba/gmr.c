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
 * $Log:	gmr.c,v $
 * Revision 2.3  89/03/09  22:34:43  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:03:17  gm0w
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

/*	gmr.c	CMU	3/26/82	*/

/*
 *  Grinnell Systems frame buffer driver interface for DR11-B/W
 *
 */
#include <gmr.h>

#if	NGMR > 0

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
#include <vaxuba/gmrreg.h>
#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>

/*
 *  Grinnell state per logical unit
 */
struct gmrunit gmrunit[NGMR];

/*
 *  Grinnell state per sub-device
 */
struct gmrstat gmrstat[NGMR][NIFVC];

/*
 *  gmropen - open Grinnell sub-device
 *
 *  Show Grinnell sub-device now in use.  Set default read and
 *  write function bits.
 *
 *  Return error ENXIO if IFVC number too large, EBUSY if already open.
 */

/*ARGSUSED*/
gmropen(dev, flag)
{

    register int ifvc = GMRIFVC(dev);
    register struct gmrstat *gmrs;

    if (ifvc >= NIFVC)
    {
	return(ENXIO);
    }
    gmrs = &gmrstat[GMRUNIT(dev)][ifvc];
    if (gmrs->gmrs_open != 0)
	return(EBUSY);
    gmrs->gmrs_open++;
    gmrs->gmrs_rcom = GMR_RCOM;
    gmrs->gmrs_wcom = GMR_WCOM;
    return(0);
}



/*
 *  gmrclose - close Grinnell sub-device
 *
 *  Release DMA line if currently held by this sub-device.  Free all
 *  memory channels allocated to this sub-device.  Release memory
 *  channel bit map if held by this sub-device.  Decrement open count
 *  on sub-device.
 */

/*ARGSUSED*/
gmrclose(dev, flag)
{
    register struct gmrstat *gmrs = &gmrstat[GMRUNIT(dev)][GMRIFVC(dev)];
    register struct gmrunit *gmr = &gmrunit[GMRUNIT(dev)];

    if (gmr->gmr_line.res_dev == dev)
	(void)gmrrelease(dev, &(gmr->gmr_line));
    gmr->gmr_memchan &= ~gmrs->gmrs_memifvc;
    gmrs->gmrs_memifvc = 0;
    if (gmr->gmr_mem.res_dev == dev)
	(void)gmrrelease(dev, &(gmr->gmr_mem));
    gmrs->gmrs_open--;
}



/*
 *  gmrphys - set buffer header parameters for Grinnell DMA
 *
 *  Set device function bits for the appropriate operation into the
 *  buffer header and call drphys() to finish up any further DR11
 *  pre-processing of buffer header before transfer.
 *
 *  Called from physio() after buffer header has been assigned and prior
 *  to passing it to the device strategy routine.
 */

unsigned
gmrphys(bp)
register struct buf *bp;
{
    register struct gmrstat *gmrs = &gmrstat[GMRUNIT(bp->b_dev)][GMRIFVC(bp->b_dev)];

    if (bp->b_flags&B_READ)
	dr_com(bp) = gmrs->gmrs_rcom;
    else
	dr_com(bp) = gmrs->gmrs_wcom;
    drphys(bp);
}



/*
 *  gmrread - initiate read operation on Grinnell
 *
 *  Reserve the DMA line if not currently held by this sub-device.
 *  Call physio() to perform the read operation.  Release the
 *  DMA line if it was reserved before the call.
 */

gmrread(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    register struct gmrunit *gmr = &gmrunit[GMRUNIT(dev)];
    int needline = (gmr->gmr_line.res_dev != dev);
    int error;
    extern drstrategy();

    if (needline)
	gmrreserve(dev, &gmr->gmr_line);
    error = physio(drstrategy, &(gmr->gmr_buf), dev, B_READ, gmrphys, uio);
    if (needline)
	(void)gmrrelease(dev, &gmr->gmr_line);
    return(error);
}



/*
 *  gmrwrite - initiate write operation on Grinnell
 *
 *  Reserve the DMA line if not currently held by this sub-device.
 *  Call physio() to perform the write operation.  Release the
 *  DMA line if it was reserved before the call.
 */

gmrwrite(dev, uio)
    dev_t dev;
    struct uio *uio;
{
    register struct gmrunit *gmr = &gmrunit[GMRUNIT(dev)];
    int needline = (gmr->gmr_line.res_dev != dev);
    int error;
    extern drstrategy();

    if (needline)
	gmrreserve(dev, &gmr->gmr_line);
    error = physio(drstrategy, &(gmr->gmr_buf), dev, B_WRITE, gmrphys, uio);
    if (needline)
	(void)gmrrelease(dev, &gmr->gmr_line);
    return(error);
}

/*
 *  gmrioctl - Grinnell ioctl call
 *
 *  GMRIOCNOWC	     - disable word count check for packed-byte writes
 *  GMRIOCWC	     - enable word count check
 *  GMRIOCRESERVE    - reserve the DMA line
 *  GMRIOCRELEASE    - release the DMA line
 *  GMRIOCCHECKMEM   - reserve and return memory channel bit map
 *  GMRIOCALLOCMEM   - allocate memory channels from bit map and release it
 *  GMRIOCDEALLOCMEM - deallocate memory channels to bit map
 */

/* ARGSUSED */
gmrioctl(dev, cmd, addr, flag)
caddr_t addr;
dev_t dev;
{
    register struct gmrstat *gmrs = &gmrstat[GMRUNIT(dev)][GMRIFVC(dev)];
    register struct gmrunit *gmr = &gmrunit[GMRUNIT(dev)];

    switch (cmd)
    {
	/*
	 *  Disable word count check
	 */
	case GMRIOCNOWC:
	    gmrs->gmrs_wcom |= DRCSR_FUNC2;
	    break;

	/*
	 *  Enable word count check
	 */
	case GMRIOCWC:
	    gmrs->gmrs_wcom &= ~DRCSR_FUNC2;
	    break;

	/*
	 *  Reserve the DMA line
 	 */
	case GMRIOCRESERVE:
	    gmrreserve(dev, &(gmr->gmr_line));
	    break;

	/*
	 *  Release the DMA line
	 */
	case GMRIOCRELEASE:
	    return(gmrrelease(dev, &(gmr->gmr_line)));
	    
	/*
	 *  Reserve the memory channel bit map and return the current
	 *  state of the map.
	 */
	case GMRIOCCHECKMEM:
	    gmrreserve(dev, &(gmr->gmr_mem));
	    *((int *)addr) = gmr->gmr_memchan;
	    break;

	/*
	 *  Allocate some subset of the memory channel bit map to
	 *  this sub-device and release the map.
	 *
	 *  Return error EBUSY if the requested allocation conflicts with
	 *  the current allocation (but still release the map).
	 */
	case GMRIOCALLOCMEM:
	{
	    int memchan = *((int *)addr);
	    int error = 0;
	    int gerror = 0;

	    gmrreserve(dev, &(gmr->gmr_mem));
	    if (gmr->gmr_memchan & memchan)
		error = EBUSY;
	    else
	    {
		gmr->gmr_memchan |= memchan;
		gmrs->gmrs_memifvc |= memchan;
	    }
	    gerror = gmrrelease(dev, &(gmr->gmr_mem));
 	    return(error?error:gerror);
	}

	/*
	 *  Deallocate some subset of the memory channel bit map
	 *  assigned to this sub-device.
	 *
	 *  Return error EPERM (without deallocating anything) if any
	 *  portion of this subset conflicts is not allocated to this
	 *  sub-device.
	 *
	 *  (Note: This may safely be done independent of which (if any)
	 *  sub-device has reserved the memory channel bit map, since
	 *  the subset is being returned to the map)   
	 */  
	case GMRIOCDEALLOCMEM:
	{
	    int memchan = *((int *)addr);

	    if ((gmrs->gmrs_memifvc & memchan) != memchan)
		return(EPERM);
	    else
	    {
		gmr->gmr_memchan &= ~memchan;
		gmrs->gmrs_memifvc &= ~memchan;
	    } 
	    break;
	}

	/*
	 *  If we have never heard of this command, it may possibly
	 *  be a generic DR11-B/W call so don't set u_error;  return
	 *  the -1 value instead to be used if the main driver
	 *  does not recognize the command either.
	 */
	default:
	    return (-1);
    }
    return(0);
}

/*
 *  gmrreserve - reserve a resource
 *
 *  Assign the specified resource to this sub-device.  Block until the
 *  resource becomes available if it it currently assigned to some
 *  other sub-device.  Return immediately without error if the resource
 *  is already allocated to this sub-device.
 */

gmrreserve(dev, res)
dev_t dev;
struct gmrresource *res;
{
    if (res->res_dev == dev)
	return;
    while (res->res_dev)
    {
	res->res_flag |= RES_WANTED;
	sleep((caddr_t)res, PPIPE);
    }
    res->res_dev = dev;
}



/*
 *  gmrrelease - release a resource
 *
 *  Release the specified resource which is currently assigned to this
 *  sub-device and wakeup anyone waiting for it to become available.
 *
 *  Return error EPERM if the resource is not currently assigned to
 *  this subdevice.
 */

gmrrelease(dev, res)
dev_t dev;
struct gmrresource *res;
{
    if (res->res_dev != dev)
    {
	return(EPERM);
    }
    res->res_dev = 0;
    if (res->res_flag & RES_WANTED)
    {
	res->res_flag &= ~(RES_WANTED);
	wakeup((caddr_t)res);
    }
    return(0);
}

/*
 *  gmrintr - interrupt received from Grinnell
 */

/*ARGSUSED*/
gmrintr(unit)
{
    /*
     *  No special processing required.
     */
    return(0);
}



/*
 *  gmrtout - I/O timeout on Grinnell
 */

/*ARGSUSED*/
gmrtout(unit)
{
    /*
     *  No special processing required.
     */
}



/*
 *  gmrreset - called after UBA init
 */

/*ARGSUSED*/
gmrreset(unit)
{

}



/*
 *  gmrattach - initialize newly configured Grinnell device
 *
 *  Allocate the next logical Grinnell unit and fill in the
 *  appropriate entry in the driver physical to logical unit
 *  translation table.
 *
 *  If we are all out of logical Grinnell devices, somebody fouled
 *  up the configuration.
 */

gmrattach(unit)
{
    static int ngmr = 0;

    if (ngmr >= NGMR)
	panic("gmrattach");

    dr_logunit(unit) = ngmr++;
}
#endif
