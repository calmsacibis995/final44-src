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
 * $Log:	drbreg.h,v $
 * Revision 2.3  89/03/09  22:33:10  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:01:43  gm0w
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

/*	drbreg.h	CMU	3/25/82	*/

#ifdef	KERNEL

#define DRBUNIT(dev)	dr_logunit(DRUNIT(dev)) /* extract */
					/*  DR11-B logical unit number */
					/*  from device number */

#define NDRBBUF		2		/* number of buffer headers per */
					/* unit for DMA */

#define DRB_RCOM	(0)		/* default read function bits */
#define DRB_WCOM	(DRCSR_FUNC1)	/* default write function bits */


/*  Unit state (index by logical unit number)  */
struct drbstat
{
    struct buf	 drbs_buf[NDRBBUF];	/* I/O buffer header */
    struct buf  *drbs_bufp;		/* current buffer header */
    u_short	 drbs_open;		/* open count */
    u_short	 drbs_rcom;		/* read operation function bits */
    u_short	 drbs_wcom;		/* read operation function bits */
};

#endif	KERNEL


/*
 *  Pull in DR11-B/W definitiions for user processes only including
 *  <sys/drbreg.h>.
 */

#ifndef	DRCSR_BITS
#include <sys/drreg.h>
#endif


/*
 *  Parameter structure for GETP/SETP
 */
struct drbparam
{
    short drbp_rcom;			/* read function bits */
    short drbp_wcom;			/* write function bits */
    long  drbp_mbz[9];			/* reserved for future expansion */
};
#define DRBRBITS	(DRCSR_FUNC1|DRCSR_FUNC2|DRCSR_FUNC3|DRCSR_CYCLE)
#define DRBWBITS	(DRCSR_FUNC1|DRCSR_FUNC2|DRCSR_FUNC3|DRCSR_CYCLE)


/*
 *  DR11-B ioctl definitions needed by user process
 *
 *  (codes 220-239 reserved for DRB)
 */

#define DRBIOCGETP	_IOR (D, 239, struct drbparam)
#define DRBIOCSETP	_IOW (D, 238, struct drbparam)
