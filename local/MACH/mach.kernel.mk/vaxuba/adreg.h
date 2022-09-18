/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	adreg.h,v $
 * Revision 2.3  89/03/09  22:31:13  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  10:59:35  gm0w
 * 	Updated copyright.
 * 	[89/02/23            gm0w]
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)adreg.h	7.1 (Berkeley) 6/5/86
 */

struct addevice {
	short int ad_csr;			/* Control status register */
	short int ad_data;			/* Data buffer */
};

#define AD_CHAN		ADIOSCHAN
#define AD_READ		ADIOGETW
#define ADIOSCHAN	_IOW(a, 0, int)		/* set channel */
#define ADIOGETW	_IOR(a, 1, int)		/* read one word */

/*
 * Unibus CSR register bits
 */

#define AD_START		01
#define AD_SCHMITT		020
#define AD_CLOCK		040
#define AD_IENABLE		0100
#define AD_DONE 		0200
#define AD_INCENABLE		040000
#define AD_ERROR		0100000
