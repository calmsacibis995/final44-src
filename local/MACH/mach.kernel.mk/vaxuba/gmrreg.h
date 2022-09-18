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
 * $Log:	gmrreg.h,v $
 * Revision 2.3  89/03/09  22:34:54  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:03:25  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Aug-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Upgraded from 4.1BSD.
 *	[V1(1)]
 *
 * 23-Apr-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created for new DR11-B/W driver (V3.04g).
 *
 */

/*	gmrreg.h	CMU	7/10/81	*/

#ifdef	KERNEL

#define GMRUNIT(dev)	dr_logunit(DRUNIT(dev)) /* extract */
					/*  Grinnell logical unit */
					/*  number from device number */
#define GMRIFVC(dev)	((minor(dev)&~DRUNITMASK)>>DRUNITBITS) /* extract */
					/*  Grinnell image function video */
					/*  card number from device number */
#define NIFVC	4			/* maximum number of IFVC's */

#define GMR_RCOM	(DRCSR_FUNC1)	/* Grinnell read function bits */
#define GMR_WCOM	(0)		/* Grinnell write function bits */


/*
 *  General purpose resource allocation structure
 */
struct gmrresource
{
    short res_flag;			/* flags (see below) */
    dev_t res_dev;			/* sub-device which owns resource */
};
#define RES_WANTED	01		/* process(es) waiting for resource */


/*  
 *  Unit state (index by logical unit number)
 */
struct gmrunit
{
    struct buf	       gmr_buf;		/* I/O buffer header */
    struct gmrresource gmr_line;	/* DMA channel resource */
    struct gmrresource gmr_mem;		/* memory channel bit map resource */
    int 	       gmr_memchan;	/* memory channel bit map */
};

/*  Sub-device state (index by logical unit number and IFVC)  */
struct gmrstat
{
    u_short	 gmrs_open;		/* open count */
    u_short	 gmrs_rcom;		/* read operation function bits */
    u_short	 gmrs_wcom;		/* read operation function bits */
    int		 gmrs_memifvc;		/* memory channel allocation */
};
#endif	KERNEL


/*
 *  Pull in DR11-B/W definitiions for user processes only including
 *  <vaxuba/drb.h>.
 */

#ifndef	DRCSR_BITS
#include <vaxuba/drreg.h>
#endif


/*
 *  Grinell IOCTL calls
 */

#define GMRIOCNOWC	 _IO  (G, 100)
#define GMRIOCWC	 _IO  (G, 101)
#define GMRIOCRESERVE	 _IO  (G, 251)
#define GMRIOCRELEASE	 _IO  (G, 252)
#define GMRIOCCHECKMEM	 _IOR (G, 253, int)
#define GMRIOCALLOCMEM	 _IOW (G, 254, int)
#define GMRIOCDEALLOCMEM _IOW (G, 255, int)
