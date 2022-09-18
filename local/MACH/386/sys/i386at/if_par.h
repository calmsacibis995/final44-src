/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_par.h,v $
 * Revision 2.1.1.2  91/03/28  08:48:14  rvb
 * 		Changed protocol to utilitize LapLink cables.  Incompatible with
 * 	previous revisions.
 * 		[91/03/15            mg32]
 * 
 * 
 * Revision 2.1.1.1  90/08/25  15:43:59  rvb
 * 	Created 08/05/90.
 * 		Parallel port network driver.
 * 	[90/08/14            mg32]
 * 
 */
 
/* 
 *	Parallel port network driver v1.0
 *	All rights reserved.
 */ 
#define OUTPUT(addr) (addr + 0)
#define INPUT(addr)  (addr + 1)
#define INTR(addr)   (addr + 2)

#define SPLNET		spl6
#define PARMTU		8192
#define MAXSPIN		10000
