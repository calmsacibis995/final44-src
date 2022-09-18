/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	lprreg.h,v $
 * Revision 2.1.1.1  90/08/25  15:43:49  rvb
 * 	Created 08/05/90.
 * 		Parallel port printer driver.
 * 	[90/08/14            mg32]
 * 
 * Revision 1.0.0.0  90/08/05  22:30:00  mg32
 * 	     Parallel port printer driver.
 * 	[90/08/05            mg32]
 * Revision 1.0.0.0  90/08/05  22:30:00  mg32
 * 	     Parallel port printer driver.
 * 	[90/08/05            mg32]
 */
 
/* 
 *	Parallel port printer driver v1.0
 *	All rights reserved.
 */ 
  
#define DATA(addr)	(addr + 0)
#define STATUS(addr)	(addr + 1)
#define INTR_ENAB(addr)	(addr + 2)
