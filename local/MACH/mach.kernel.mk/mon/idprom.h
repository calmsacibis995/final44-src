/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	idprom.h,v $
 * Revision 2.5  90/12/17  17:10:56  berman
 * 	Added lines (from sunOS 4.0.3c) for additional sun4
 * 	implementations.
 * 	[90/09/10            berman]
 * 
 * Revision 2.4  89/07/11  13:37:36  jjc
 * 	[89/07/05  20:17:43  jjc]
 * 
 *	Picked up from SunOS 4.0 for Sun 4.
 * 	[89/04/02            jjc]
 * 
 * Revision 2.3  89/03/09  20:37:56  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:52:59  gm0w
 * 	Changes for cleanup.
 * 
 */

/*	@(#)idprom.h 1.9 88/02/08 SMI	*/

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

/*
 * Structure declaration for ID prom in CPU and Ethernet boards
 */
struct idprom {
	unsigned char	id_format;	/* format identifier */
	/* The following fields are valid only in format IDFORM_1. */
	unsigned char	id_machine;	/* machine type */
	unsigned char	id_ether[6];	/* ethernet address */
	long		id_date;	/* date of manufacture */
	unsigned	id_serial:24;	/* serial number */
	unsigned char	id_xsum;	/* xor checksum */
	unsigned char	id_undef[16];	/* undefined */
};

#define IDFORM_1	1	/* Format number for first ID proms */

/*
 * The machine type field assignments are constrained such that the
 * IDM_ARCH_MASK bits define the CPU architecture and the remaining bits
 * identify the individual implementation of that architecture.
 */
#define	IDM_ARCH_MASK	0xf0	/* mask for architecture bits */
#define	IDM_ARCH_SUN2	0x00	/* arch value for Sun-2 */
#define	IDM_ARCH_SUN3	0x10	/* arch value for Sun-3 */
#define	IDM_ARCH_SUN4	0x20	/* arch value for Sun-4 */
#define	IDM_ARCH_SUN386	0x30	/* arch value for sun386 */
#define	IDM_ARCH_SUN3X	0x40	/* arch value for Sun-3x */
#define	IDM_ARCH_SUN4C	0x50	/* arch value for Sun-4c */

/* All possible values of the id_machine field (so far): */
#define IDM_SUN2_MULTI	1	/* Machine type for Multibus CPU board */
#define IDM_SUN2_VME	2	/* Machine type for VME CPU board */
#define IDM_SUN3_CARRERA 0x11	/* Carrera CPU */
#define IDM_SUN3_M25	0x12	/* M25 CPU */
#define IDM_SUN3_SIRIUS 0x13	/* Sirius CPU */
#define IDM_SUN3_PRISM  0x14    /* Prism CPU */
#define IDM_SUN3_F      0x17    /* Sun3F CPU */
#define IDM_SUN3_E      0x18    /* Sun3E CPU */
#define IDM_SUN4        0x21    /* Sparc CPU */
#define IDM_SUN4_COBRA  0x22    /* Cobra CPU */
#define	IDM_SUN4_STINGRAY       0x23    /* Stingray CPU	*/
#define	IDM_SUN386		0x31	/* Roadrunner CPU */
#define	IDM_SUN3X_PEGASUS       0x41    /* Pegasus CPU	*/
#define IDM_SUN3X_HYDRA         0x42    /* HYDRA CPU    */
#define	IDM_SUN4C_60		0x51    /* Campus-1 CPU	*/
