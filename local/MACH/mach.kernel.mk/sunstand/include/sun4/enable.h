/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	enable.h,v $
 * Revision 2.2  89/07/11  23:32:14  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*      @(#)enable.h 1.3 88/02/08 SMI      */

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

/*
 * The System Enable register controls overall
 * operation of the system.  When the system is
 * reset, the Enable register is cleared.  The
 * enable register is addressed as a byte in
 * ASI_CTL space.
 */

/*
 * Bits of the Enable Register
 */
#define	ENA_DIAG	0x01		/* r/o - diag switch, 1 = on */
#define	ENA_MONITOR	0x01		/* w/o - monitor bit */
#define ENA_VMERESET	0x02		/* r/w - reset the vme */
#define ENA_CACHERESET	0x04		/* r/w - reset the cache */
#define	ENA_VIDEO	0x08		/* r/w - enable video memory */
#define	ENA_CACHE	0x10		/* r/w - enable external cache */
#define	ENA_SDVMA	0x20		/* r/w - enable system DVMA */
#define	ENA_NOTBOOT	0x80		/* r/w - non-boot state, 1 = normal */


#define	ENABLEREG	0x40000000	/* addr in ASI_CTL space */
