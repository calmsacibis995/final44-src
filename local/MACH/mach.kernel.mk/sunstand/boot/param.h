/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	param.h,v $
 * Revision 2.2  89/07/12  00:11:38  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 * @(#)param.h 1.3 88/02/08 Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * We redefine these things here to prevent header file madness
 */

#define	NBBY	8		/* bits per byte */

#define	MAXBSIZE	8192	/* max FS block size */
#define	MAXFRAG		8	/* max frags per block */

#define	DEV_BSIZE	512
#define	SECSIZE		512

/*
 * Size of protocol work area allocated by Ethernet drivers
 * Must be multiple of pagesize for all machines
 */
#define	PROTOSCRATCH	8192
