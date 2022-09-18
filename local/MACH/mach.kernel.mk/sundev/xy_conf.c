/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	xy_conf.c,v $
 * Revision 2.4  90/07/03  16:49:39  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:16:30  mrt]
 * 
 * Revision 2.3  89/03/09  21:49:46  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:59:24  gm0w
 * 	Changes for cleanup.
 * 
 */
#ifndef	lint
static  char sccsid[] = "@(#)xy_conf.c 1.1 86/09/25";
#endif

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */
#include <xy.h>

/*
 * Config dependent data structures for the Xylogics 450 driver.
 */
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/disklabel.h>
#include <sundev/mbvar.h>
#include <sundev/xyvar.h>

int nxy = NXY;			/* So the driver can use these defines */
int nxyc = NXYC;

/*
 * Unit structures.
 */
struct xyunit xyunits[NXY];

/*
 * Controller structures.
 */
struct xyctlr xyctlrs[NXYC];

/*
 * Generic structures.
 */
struct	mb_ctlr *xycinfo[NXYC];
struct	mb_device *xydinfo[NXY];

